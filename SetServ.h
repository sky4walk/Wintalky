// written by André Betz 
// http://www.andrebetz.de

// SetServ.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetServ dialog

class CSetServ : public CDialog
{
// Construction
public:
	CSetServ(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetServ)
	enum { IDD = IDD_SETSERV };
	UINT	m_port;
	UINT	m_maxLogs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetServ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetServ)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
