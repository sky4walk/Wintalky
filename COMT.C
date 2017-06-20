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

int*		clnt;
int		serv;
int		maxclnt;
char**		buf;
pthread_t*	thr;

void Senden(int nr,int len)
{
	int numsnd;
	int i = nr;
	int x;
	
	for(i=0;i<maxclnt;i++)
	{	
		if(clnt[i]!=0)
		{
			for(x=0;x<len;x++)
			{
				numsnd = send(clnt[i],&buf[nr][x],1,0);
				if(numsnd!=1) break;
			}
		}
	}			
} 

void *Wait(void *s)
{
	int	len=0;
	char	chget;
	int	numrcv;
	int	nr = (int)s;
	char	ein[] = "eingeloggt!!!\n";
	char	aus[] = "ausgeloggt!!!\n";
	
	printf("eingeloggt: %d !!!\n",nr);
				
	memcpy(buf[nr],ein,strlen(ein));
	Senden(nr,strlen(ein));
	
	for(;;)
	{
		numrcv = recv(clnt[nr],&chget,1,0);
		buf[nr][len] = chget;
		len++;
		if(chget==13)
		{	
			buf[nr][len] = 0;
			Senden(nr,len);			
			len = 0;
		}
		if(numrcv!=1) break;		
	}

	memcpy(buf[nr],aus,strlen(aus));
	Senden(nr,strlen(aus));
		
	if(clnt[nr]!=0) close(clnt[nr]);
	clnt[nr] = 0;
	
	if(buf[nr]!=NULL) free(buf[nr]);
	buf[nr] = NULL;
	
	printf("ausgeloggt: %d !!!\n",nr);
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
		
		if(clnt[i]!=0)
		{
			close(clnt[i]);
			clnt[i] = 0;
		}
	}
	
	free(buf);
	free(clnt);
	free(thr);
	
	close(serv);
	
	printf("Server beendet!!!\n");
	
	exit(0);	
}

int main(int argc,char** argv)
{
	struct sockaddr_in	servSockAddr;
	struct sockaddr_in	clntSockAddr;
	int			addrLen;
	int			stat;
	int			port;
	int			newc;
	int			i;
		
	
	signal(SIGINT,catcher);

	if(argc!=3)	
	{
		printf("usage: %s [port] [maximal clients]\n",argv[0]);
		exit(0);
	}
	
	maxclnt = atoi(argv[2]);
	port	= atoi(argv[1]);
	
	printf("Server startet: %d %d\n",port,maxclnt);
	
	clnt = (int*)malloc(maxclnt*sizeof(int));
	buf  = (char**)malloc(maxclnt*sizeof(char*));
	thr  = (pthread_t*)malloc(maxclnt*sizeof(pthread_t));
	
	if((clnt==NULL)||(buf==NULL)||(thr==NULL))
	{
		printf("Kein speicher frei!!!\n");
		exit(0);
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
	
	serv = socket(AF_INET,SOCK_STREAM,0);
	stat = bind(serv,(struct sockaddr*)&servSockAddr,sizeof(servSockAddr));
	stat = listen(serv,4);
	
	if((serv<1)||(stat<0))
	{
		printf("Netzwerkfehler!!!\n");
		exit(0);
	}
	
	for(;;)
	{
		newc = accept(serv,(struct sockaddr*)&clntSockAddr,&addrLen);
		printf("Client klopft an!!!\n");
		
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
							printf("Threadfehler!!!\n");
							clnt[i] = 0;
							close(newc);
						}
						i = maxclnt;
					}
					else printf("Zuwenig Speicher!!!\n");
				}
			}
		}
		else printf("Einloggfehler!!!\n");	
	}
	
	catcher(0);
		
	return 1;
}