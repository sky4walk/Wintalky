// written by André Betz 
// http://www.andrebetz.de

#include "stdafx.h"
#include "Socky.h"

static int	ServOn;

UINT ServerAccept(LPVOID pParam);

CSocky::CSocky()
{
	WSADATA	Data;
	int	status	= WSAStartup(MAKEWORD(1,1),&Data);
	Logs = 0;
}

BOOL CSocky::OpenServer(UINT port,UINT logs)
{
	AfxBeginThread(ServerAccept,(LPVOID)this);

	return 0;
}	

/*
 
	AfxBeginThread(ServerAccept,(LPVOID)this);

*/

CSocky::~CSocky()
{
	ServOn = 0;
	if(Sock)	closesocket(Sock);
	WSACleanup(); 
}

UINT ServerAccept(LPVOID pParam)
{
	int                     serverSocket;
	int                     clientSocket;
	int                     addrLen;
	int                     status;
	struct sockaddr_in      serverSockAddr;
	struct sockaddr_in      clientSockAddr;

	addrLen = sizeof(serverSockAddr);
	memset(&serverSockAddr,0,sizeof(serverSockAddr));
	serverSockAddr.sin_port         = htons(port);
	serverSockAddr.sin_family       = AF_INET;
	serverSockAddr.sin_addr.s_addr  = htonl(INADDR_ANY);

	serverSocket    = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	status          = bind(serverSocket,(struct sockaddr*)&serverSockAddr,sizeof(serverSockAddr));
	status          = listen(serverSocket,4);

	while(ServOn)		        
	{
		clientSocket    = accept(serverSocket,(struct sockaddr*)&clientSockAddr,&addrLen);
		AfxBeginThread(ServerAccept,(LPVOID)this);
	}
}