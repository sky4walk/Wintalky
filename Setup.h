// written by André Betz 
// http://www.andrebetz.de

class CSetup : public CDialog
{
public:
	CSetup(CWnd* pParent = NULL);
	UINT GetPort();
	UINT GetUser();
	CString GetAdr();
	BOOL GetServ();
	//{{AFX_DATA(CSetup)
	enum { IDD = IDD_SETUP };
	CString	m_Adr;
	UINT	m_Port;
	UINT	m_User;
	int		m_Server;
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(CSetup)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
