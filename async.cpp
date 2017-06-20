// written by André Betz 
// http://www.andrebetz.de

#include "stdafx.h"
#include "async.h"
#include "sock.h"
#include <winsock.h> /* link WSock32.lib */

UINT Recv(LPVOID pParam);
UINT SEND(LPVOID pParam);
UINT LOAD(LPVOID pParam);

CAsync::CAsync(int sock,LPVOID verw,int nr)
{
	m_nr	= nr;
	m_verw	= verw;
	m_sock	= sock;
	m_len	= 0;
	m_buf	= NULL;
	Wait();
}

CAsync::~CAsync()
{
	if(m_sock)	closesocket(m_sock);
	m_sock	= 0;
	m_blen	= 0;
	m_len	= 0;
	if(m_buf) delete m_buf;
	m_buf = NULL;
}

int CAsync::Wait()
{
	AfxBeginThread(Recv,(LPVOID)this);
	return 0;
}

int CAsync::Load(int l, char* buf)
{
	m_buf	= buf;
	m_blen	= l;
	AfxBeginThread(LOAD,(LPVOID)this);
	return 0;
}

int CAsync::Send(const void* buf,int buflen)
{
	m_temp = new char[buflen];
	memcpy(m_temp,buf,buflen);
	m_tlen	= buflen;
	AfxBeginThread(SEND,(LPVOID)this);
	return 0;
}

UINT SEND(LPVOID pParam)
{
	CAsync* Inf = (CAsync*)pParam;

	int				len = Inf->m_tlen;
	int				numsnt;
	char*			pos;
	char*			sendbuf = (char*)Inf->m_temp;
	struct timeval	TimeOut;
	fd_set			writefds;

	TimeOut.tv_sec	= 0;
	TimeOut.tv_usec	= 2000;
	
	FD_ZERO(&writefds);
	FD_SET(Inf->m_sock,&writefds);

	pos = sendbuf;

	numsnt  = send(Inf->m_sock,(char*)&len,sizeof(int),0);
	if((numsnt == -1)||(numsnt == 0))
	{
		((CSocken*)((CAsync*)pParam)->m_verw)->OnClose(Inf->m_nr);
		return 0;
	}

	while(len>0)
	{
		select(FD_SETSIZE,NULL,&writefds,NULL,&TimeOut);
		if(FD_ISSET(Inf->m_sock,&writefds))
		{
			numsnt  = send(Inf->m_sock,pos,len,0);
			len     -= numsnt;
			pos     += numsnt;

			if(numsnt == -1)
			{
				delete sendbuf;
				((CSocken*)((CAsync*)pParam)->m_verw)->OnClose(Inf->m_nr);
				return 0;
			}
		}
	}
	delete sendbuf;
	return 0;
}

UINT Recv(LPVOID pParam)
{
	CAsync* Inf = (CAsync*)pParam;

	int		len		= 0;
	int		numrcv	= 0;
	int		status	= 0;
	
	numrcv  = recv(Inf->m_sock,(char*)&len,sizeof(int),0);
	if((numrcv == -1)||(numrcv == 0))
	{
		((CSocken*)((CAsync*)pParam)->m_verw)->OnClose(Inf->m_nr);
		return 0;
	}
		
	((CSocken*)((CAsync*)pParam)->m_verw)->OnRecieve(Inf->m_nr,len);

	return 0;
}

UINT LOAD(LPVOID pParam)
{
	CAsync* Inf = (CAsync*)pParam;

	int		len		= 0;
	int		numrcv	= 0;
	int		status	= 0;
	char*	pos		= NULL;

	len	= Inf->m_blen;
	pos = Inf->m_buf;
		
	while(len>0)
	{
		numrcv  = recv(Inf->m_sock,pos,len,0);
		len     -= numrcv;
		pos     += numrcv;
                
		if((numrcv == -1)||(numrcv == 0))
		{
			((CSocken*)((CAsync*)pParam)->m_verw)->OnClose(Inf->m_nr);
			return 0;
		}
	}
	
	((CSocken*)((CAsync*)pParam)->m_verw)->LoadEnd(Inf->m_nr);
	Inf->Wait();

	return 0;
}
