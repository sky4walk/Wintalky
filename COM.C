// written by André Betz 
// http://www.andrebetz.de

/*
	make: gcc -o com com.c -lpthread
*/

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define MAXBUF	255
#define CODE	0

int 		sock;
char		bufempf[MAXBUF];
char		bufsend[MAXBUF];
pthread_t 	thr;

void *Empfangen(void *a)
{
	int		len;
	int		i;
	int		numrcv;
	

	for(;;)
	{	
		memset(bufempf,0,MAXBUF);
		numrcv = recv(sock,&len,4,0);
		if((numrcv==0)||(numrcv==-1))	break;
		numrcv = recv(sock,bufempf,len,0);
		if((numrcv==0)||(numrcv==-1))	break;
		for(i=0;i<len;i++)	bufempf[i] -= CODE;
		printf("%s\n",bufempf);
	}
	
	return NULL;
}

void Senden()
{
	int		len;
	int 		i;
	int		numsnd;
	
	for(;;)
        {
        	memset(bufsend,0,MAXBUF);
		gets(bufsend);
		len = strlen(bufsend)+1;
		
 		for(i=0;i<len;i++)      bufsend[i] += CODE;
	        numsnd = send(sock,&len,4,0);
	        if((numsnd==0)||(numsnd==-1))	break;
	        numsnd = send(sock,bufsend,len,0);
		if((numsnd==0)||(numsnd==-1))	break;
	}
}

void catcher(int a)
{
	int		len;
	int		i;	
	
	memset(bufsend,0,MAXBUF);	
	memset(bufempf,0,MAXBUF);

	strcmp(bufempf,"ausgelockt!!!");
	printf("%s\n",bufempf);
	len = strlen(bufsend);

	memcpy(bufsend,&len,4);
	memcpy(bufsend+4,&bufempf,len);
	
	for(i=0;i<len;i++)	bufsend[i] += CODE;
	send(sock,bufsend,4,0);
	
	close(sock);
}
      
int main(int argc,char** argv)
{
	struct sockaddr_in 	blah;
        struct hostent 		*he;
        int			port;
        int			len;
        int 			i;
        char			*server;
	unsigned char		buf[MAXBUF];
	        
        signal(SIGINT, catcher);
        
        if(argc<2)	
        {
        	printf("%s [Servername] [Portnummer]\n",argv[0]);
        	exit(-1);
	}        
        
	port = atoi(argv[2]);
	server = argv[1];
	        
   	if((sock = socket(AF_INET,SOCK_STREAM,0))==-1)
        {
        	perror("socket()");
                exit(-1);
        }
	
	memset((char*)&blah,0,sizeof(blah));
        blah.sin_family		= AF_INET;
        blah.sin_addr.s_addr	= inet_addr(server);
        blah.sin_port		= htons(port);

	if ((he = gethostbyname(server)) != NULL) 
	{
        	memcpy((char*)&blah.sin_addr,he->h_addr,he->h_length);
	}
        else 
        {
		if ((blah.sin_addr.s_addr = inet_addr(server)) < 0) 
		{
	        	perror("gethostbyname()");
	                return(-3);
	       	}
        }
	
	printf("Verbindung herstellen ...\n");                                                                                     
        if (connect(sock,(struct sockaddr *)&blah,16)==-1) 
        {
	        perror("connect()");
                close(sock);
                return(-4);
        }	
        
        memset(bufsend,0,MAXBUF);
        strcpy(bufsend,"eingeloggt!!!");
	len = strlen(bufsend)+1;
        for(i=0;i<len;i++)      bufsend[i] += CODE;
        send(sock,&len,4,0);
        send(sock,bufsend,len,0);
 	
       	pthread_create(&thr,NULL,Empfangen,NULL);	
	Senden(sock);
	catcher(1);
}
