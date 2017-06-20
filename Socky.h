// written by André Betz 
// http://www.andrebetz.de

#include <winsock.h> /* link WSock32.lib */

class CSocky
{
public:
	CSocky();
	~CSocky();
	BOOL OpenServer(UINT port,UINT logs);
protected:
	struct sockaddr_in	m_ServAdr;
};