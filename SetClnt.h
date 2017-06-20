// written by André Betz 
// http://www.andrebetz.de

// SetClnt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetClnt dialog

class CSetClnt : public CDialog
{
// Construction
public:
	CSetClnt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetClnt)
	enum { IDD = IDD_SETCLNT };
	CString	m_Adr;
	UINT	m_Port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetClnt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetClnt)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
