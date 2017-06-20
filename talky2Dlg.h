// written by André Betz 
// http://www.andrebetz.de

#include "resource.h"

#ifndef SOCKY
#include "sock.h"
#define SOCKY
#endif

class CTalky2Dlg : public CDialog
{
public:
	CTalky2Dlg(CString adr,UINT port);	// standard constructor
	~CTalky2Dlg();
	//{{AFX_DATA(CTalky2Dlg)
	enum { IDD = IDD_TALKY2_DIALOG };
	CString	m_Eingabe;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CTalky2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	void Sendy(CString snd);
	UINT m_Port;
	CString m_Adr;
	char m_txt[255];
	char m_buffy[255];
	CString m_user;
	CSocken* m_socky;
	//{{AFX_MSG(CTalky2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnOk();
	afx_msg void OnEnde();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
