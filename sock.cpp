// written by André Betz 
// http://www.andrebetz.de

#include "stdafx.h"
#include <winsock.h>
#include "Async.h"
#include "Sock.h"

UINT Acpt(LPVOID pParam);

CSocken::CSocken(const char* nam,unsigned int port,HWND hwnd)
{
	int		status = 0;
	m_con	= 0;
	WSADATA	Data;
	m_SSock	= 0;
	m_Port	= port;
	m_Hwnd	= hwnd;
	m_con	= 1;
	m_clients = new LPVOID[m_con];
	status	= WSAStartup(MAKEWORD(1, 1), &Data);
	m_clients[0] = NULL;
	m_err = OpenClt(nam);
}

int CSocken::GetErr()
{
	return m_err;
}

CSocken::CSocken(unsigned int port,int con,HWND hwnd)
{
	int		status = 0,i;
	m_con	= con;
	WSADATA	Data;
	m_SSock	= 0;
	m_Port	= port;
	m_Hwnd	= hwnd;
	status	= WSAStartup(MAKEWORD(1, 1), &Data);
	m_clients = new LPVOID[m_con];
	
	for(i=0;i<m_con;i++)
	{
		m_clients[i] = NULL;
	}

	OpenSrv();
	Accept();
}

CSocken::~CSocken()
{
	int status = 0,i;
	if(m_SSock)	status  = closesocket(m_SSock);
	m_SSock = 0;
	Sleep(500);
	if(m_clients)
	{
		for(i=0;i<m_con;i++)
		{
			if(m_clients[i])
				delete m_clients[i];
		}
		delete m_clients;
	}
	status  = WSACleanup();
}

int CSocken::OpenSrv()
{
	int					sock	= 0;
	int					status	= 0;
	struct sockaddr_in	srvAddr;

	if(m_SSock)	status  = closesocket(m_SSock);
	
	memset(&srvAddr,0,sizeof(struct sockaddr_in));
	srvAddr.sin_port         = htons(m_Port);
	srvAddr.sin_family       = AF_INET;
	srvAddr.sin_addr.s_addr  = htonl(INADDR_ANY);

	sock	= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	status	= bind(sock,(struct sockaddr*)&srvAddr,sizeof(struct sockaddr_in));
	status	= listen(sock,5);

	m_SSock	= sock;
	
	return sock;
}

int CSocken::OnClose(int n)
{
	delete m_clients[n];
	m_clients[n] = NULL;
	return 0;
}

int CSocken::Send(const void* buf, int len)
{
	int i;
	for(i = 0;i<m_con;i++)
	{
		if(m_clients[i]!=NULL)
		{
			((CAsync*)m_clients[i])->Send(buf,len);
		}
	}
	return 0;
}

int CSocken::Accept()
{
	AfxBeginThread(Acpt,(LPVOID)this);
	return 0;
}

int CSocken::OnAccept(int sock)
{
	int i;
	for(i = 0;i<m_con;i++)
	{
		if(m_clients[i]==NULL)
		{
			m_clients[i] = new CAsync(sock,this,i);
			break;
		}
	}
	return 0;
}

int	CSocken::OnRecieve(int n,int l)
{
	if(m_Hwnd)	SendMessage(m_Hwnd,WM_USER+1,n,(LPARAM)l);
	return 0;
}

int	CSocken::Load(int n,int l,char* buf)
{
	((CAsync*)m_clients[n])->Load(l,buf);
	return 0;
}

int	CSocken::LoadEnd(int n)
{	
	if(m_Hwnd)	SendMessage(m_Hwnd,WM_USER+2,n,1);
	return 0;
}

int CSocken::OpenClt(const char* nam)
{
	struct sockaddr_in	srvAddr;
	struct hostent*		he;
	u_long				nblock;
	u_long				adr;
	int					sock = 0;
	int					status;
	struct timeval	TimeOut;
	fd_set			writefds;

	TimeOut.tv_sec	= 0;
	TimeOut.tv_usec	= 2000;
	
	memset(&srvAddr,0,sizeof(struct sockaddr_in));
	srvAddr.sin_port		= htons(m_Port);
	srvAddr.sin_family		= AF_INET;
	adr						= inet_addr(nam);

	if(adr == INADDR_NONE)
	{
		he = gethostbyname(nam);
		memcpy((char*)&srvAddr.sin_addr,he->h_addr,he->h_length);
    }
	else
	{
		srvAddr.sin_addr.s_addr	= adr;
	}

	nblock	= 1;
	sock	= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	status	= ioctlsocket(sock,FIONBIO,(u_long FAR*)&nblock);
	
	for(int i=0;i<10;i++)
	{
		FD_ZERO(&writefds);
		FD_SET(sock,&writefds);

		status	= connect(sock,(struct sockaddr*)&srvAddr,sizeof(struct sockaddr_in));
		select(FD_SETSIZE,NULL,&writefds,NULL,&TimeOut);
		if(FD_ISSET(sock,&writefds))
		{
			status = 1;
			nblock	= 0;
			status	= ioctlsocket(sock,FIONBIO,(u_long FAR*)&nblock);
			m_clients[0] = new CAsync(sock,this,0);
			return sock;
		}
	}
	
	closesocket(sock);
	return status;
}

UINT Acpt(LPVOID pParam)
{
	struct sockaddr_in	clntAddr;
	int					clnt	= 0;
	int					status	= 0;
	int					addrLen;
	struct timeval		TimeOut;
	fd_set				readfds;
	CSocken*			cla = (CSocken*)pParam;

	TimeOut.tv_sec	= 0;
	TimeOut.tv_usec	= 0;

	FD_ZERO(&readfds);
	FD_SET(cla->m_SSock,&readfds);

	select(FD_SETSIZE,&readfds,NULL,NULL,&TimeOut);

	addrLen = sizeof(struct sockaddr_in);

	while(cla->m_SSock)
	{
//		if(FD_ISSET(cla->m_SSock,&readfds))
		{
			clnt = accept(cla->m_SSock,(struct sockaddr*)&clntAddr,&addrLen);
			if(clnt!=-1)	cla->OnAccept(clnt);
		}
	}

	return 0;
}