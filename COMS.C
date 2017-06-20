// written by André Betz 
// http://www.andrebetz.de

/*
	make: gcc -o coms coms.c -lpthread
*/
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>

#define MAXBUF	256
#define CODE 100
#define INTLEN 4

int*		clnt;
int		serv;
int		maxclnt;
char**		buf;
pthread_t*	thr;

void Senden(int nr,int len)
{
	char tempbuf[MAXBUF+INTLEN];
	int numsnd;
	int i = nr;
	
	memcpy(tempbuf,&len,INTLEN);
	memcpy((tempbuf+INTLEN),buf[nr],len);
	
	for(i=0;i<maxclnt;i++)
	{
		if(clnt[i]!=0)
		{
			printf("Thread %d sendet an %d l:%d \n",nr,i,len);	
			numsnd = send(clnt[i],tempbuf,len+INTLEN,0);
		}
	}			
} 

void *Wait(void *s)
{
	int	len;
	int	numrcv;
	int	nr = (int)s;
	
	printf("Thread %d an\n",nr);
		
	while(clnt[nr]!=0)
	{
		numrcv = recv(clnt[nr],&len,INTLEN,0);
		if(numrcv!=INTLEN) break;		
		else numrcv = recv(clnt[nr],buf[nr],len,0);
		if(numrcv!=len)	break;		
		else
		{
			Senden(nr,len);
		}
	}
	
	if(clnt[nr]!=0) close(clnt[nr]);
	clnt[nr] = 0;
	
	if(buf[nr]!=NULL) free(buf[nr]);
	buf[nr] = NULL;
	
	printf("Thread %d aus\n",nr);
	return NULL;
}

void catcher(int a)
{
	int i;
	
	for(i=0;i<maxclnt;i++)
	{
		if(buf[i]!=NULL)
		{
			free(buf[i]);
			buf[i] = NULL;
		}
		
		if(clnt!=NULL)
		{
			if(clnt[i]!=0)
			{
				close(clnt[i]);
				clnt[i] = 0;
			}
		}
	}
	
	if(buf!=NULL) free(buf);
	if(clnt!=NULL)free(clnt);
	if(thr!=NULL)free(thr);
	
	if(serv!=0) close(serv);
	
	printf("beendet\n");
	exit(0);	
}

int server(int port)
{
	struct sockaddr_in	servSockAddr;
	struct sockaddr_in	clntSockAddr;
	int			addrLen;
	int			stat;
	int			newc;
	int			i;
		
	clnt = (int*)malloc(maxclnt*sizeof(int));
	buf  = (char**)malloc(maxclnt*sizeof(char*));
	thr  = (pthread_t*)malloc(maxclnt*sizeof(pthread_t));
	
	if((clnt==NULL)||(buf==NULL)||(thr==NULL))
	{
		printf("zuwenig Speicher\n");
		catcher(0);
	}
	
	for(i=0;i<maxclnt;i++)	
	{
		clnt[i] = 0;
		buf[i] = NULL;
	}
	
	addrLen	= sizeof(servSockAddr);
	memset(&servSockAddr,0,sizeof(servSockAddr));
	servSockAddr.sin_port		= htons(port);
	servSockAddr.sin_family		= AF_INET;
	servSockAddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	
	serv = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	stat = bind(serv,(struct sockaddr*)&servSockAddr,sizeof(servSockAddr));
	stat = listen(serv,5);
	
	if(serv<1)
	{
		printf("Netzwerkfehler\n");
		catcher(0);
	}
	
	for(;;)
	{
		newc = accept(serv,(struct sockaddr*)&clntSockAddr,&addrLen);
		printf("Client hat angeklopft!!!\n");		
		if(newc>0)
		{
			for(i=0;i<maxclnt;i++)
			{
				if(clnt[i]==0)
				{
					clnt[i] = newc;
					buf[i] = (char*)malloc(MAXBUF*sizeof(char));
					if(buf[i]!=NULL)
					{
						stat = pthread_create(&thr[i],NULL,Wait,(int*)i);
						if(stat!=0)
						{
							printf("Threadfehler\n");
							close(newc);
							free(buf[i]);
							buf[i] = NULL;
							clnt[i] = 0;
						}
						break;
					}
				}
			}
			
			if(i==maxclnt)
			{
				printf("Server voll!!!\n");
				close(newc);
			}
		}
		else printf("Clientfehler!!!\n");	
	}
	
	catcher(0);
		
	return 1;
}

void *Empfangen(void *a)
{
	int len;
	int i;
	int numrcv;
	
	for(;;)
	{
		memset(buf[0],0,MAXBUF);
		numrcv = recv(serv,&len,INTLEN,0);
		if(numrcv!=INTLEN) break;
		numrcv = recv(serv,buf[0],len,0);
		if(numrcv!=len) break;
		for(i=0;i<len;i++)	buf[0][i] -= CODE;
		printf("%s\n",buf[0]);
	}
	return NULL;
}

void ClntSenden()
{
	int len;
	int i;
	int numsnd;
	
	for(;;)
	{	
		memset(buf[1],0,MAXBUF);	
		gets(buf[1]);
		len = strlen(buf[1]);
		
		
		for(i=0;i<len;i++)	buf[1][i] += CODE;
		numsnd = send(serv,&len,INTLEN,0);
		if(numsnd!=INTLEN) break;
		numsnd = send(serv,buf[1],len,0);
		if(numsnd!=len) break;
	}
}

int client(char* server,int port)
{
        struct sockaddr_in      blah;
        struct hostent          *he;
        int                     len;
        int                     i;

        if((serv = socket(AF_INET,SOCK_STREAM,0))==-1)
        {
        	perror("socket()");
                exit(-1);
        }
 	
 	buf = (char**)malloc(maxclnt*sizeof(char*));
 	buf[0] = (char*)malloc(MAXBUF*sizeof(char));
 	buf[1] = (char*)malloc(MAXBUF*sizeof(char));
 	thr = (pthread_t*)malloc(maxclnt*sizeof(pthread_t));
 	
 	if((buf==NULL)||(buf[0]==NULL)||(thr==NULL))
 	{
 		printf("Zu wenig Speicher!!!\n");
 		catcher(0);
 	}
 	
 	memset((char*)&blah,0,sizeof(blah));
        blah.sin_family         = AF_INET;
        blah.sin_addr.s_addr    = inet_addr(server);
        blah.sin_port           = htons(port);
        
        if((he = gethostbyname(server)) != NULL)
        {
        	memcpy((char*)&blah.sin_addr,he->h_addr,he->h_length);
        }
        else
        {
        	if((blah.sin_addr.s_addr = inet_addr(server)) < 0)
        	{
                	perror("gethostbyname()");
                        return(-3);
                }
       	}
        
        printf("Verbindung herstellen ...\n");
        
        if (connect(serv,(struct sockaddr *)&blah,16)==-1)
        {
        	perror("connect()");
                close(serv);
                return(-4);
        }
      	
      	memset(buf[1],0,MAXBUF);
      	strcpy(buf[1],"eingeloggt!!!");
        len = strlen(buf[1]);
        for(i=0;i<len;i++)      buf[1][i] += CODE;
        send(serv,&len,4,0);
        send(serv,buf[1],len,0);

     	pthread_create(&thr[0],NULL,Empfangen,NULL);
        ClntSenden();
             
        catcher(0);
}
                             
int main(int argc,char** argv)
{
	int port;
	
       	signal(SIGINT,catcher);
	
	thr = NULL;
	clnt = NULL;
	buf = NULL;
	
   	if(argc!=4)
        {	
        	printf("Unix-Talky by Andre Betz 1998\n");
        	printf("Server: %s s [port] [maximal clients]\n",argv[0]);
        	printf("Client: %s c [host] [port]\n",argv[0]); 
                exit(0);
      	}                                                               
	
	if(argv[1][0] == 's')
	{
		printf("Server\n");
		maxclnt = atoi(argv[3]);
		port	= atoi(argv[2]);
		server(port);	
	}
	
	if(argv[1][0] == 'c')
	{
		printf("Client\n");
		maxclnt = 2;
		port = atoi(argv[3]);
		client(argv[2],port);
	} 	 
}