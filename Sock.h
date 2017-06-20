// written by André Betz 
// http://www.andrebetz.de

class CSocken
{
public:
	CSocken(const char* nam,unsigned int port,HWND hwnd);
	CSocken(unsigned int port,int con,HWND hwnd);
	~CSocken();
	int OnAccept(int sock);
	int OnClose(int n);
	int	OnRecieve(int n,int l);
	int Send(const void* buf, int len);
	int	Load(int n,int l,char* buf);
	int	LoadEnd(int n);
	int GetErr();
	int m_SSock;
	int m_Port;
	int	m_con;
	HWND m_Hwnd;
	LPVOID *m_clients;
protected:
	int m_err;
	int OpenSrv();
	int OpenClt(const char* nam);
	int Accept();
};
