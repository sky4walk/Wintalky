// written by André Betz 
// http://www.andrebetz.de

class CAsync
{
public:
	int		m_nr;
	int		m_sock;
	int		m_blen;
	int		m_tlen;
	int		m_len;
	char*	m_buf;
	char*	m_temp;
	LPVOID	m_verw;
	CAsync		(int sock,LPVOID verw,int nr);
	~CAsync		();
	int	Send	(const void* buf,int buflen);
	int Wait	();
	int Load	(int l, char* buf);
};