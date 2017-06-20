// written by André Betz 
// http://www.andrebetz.de

// ServClnt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServClnt dialog

class CServClnt : public CDialog
{
// Construction
public:
	CServClnt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CServClnt)
	enum { IDD = IDD_SERVCLNT };
	//}}AFX_DATA
	BOOL GetIt();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServClnt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		m_ServClnt;
	// Generated message map functions
	//{{AFX_MSG(CServClnt)
	afx_msg void OnServ();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
