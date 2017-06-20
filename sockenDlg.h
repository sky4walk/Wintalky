// written by André Betz 
// http://www.andrebetz.de

#include "resource.h"

#ifndef SOCKY
#include "sock.h"
#define SOCKY
#endif

class CSockenDlg : public CDialog
{
public:
	CSockenDlg(UINT port,UINT usr);
	~CSockenDlg();
	//{{AFX_DATA(CSockenDlg)
	enum { IDD = IDD_SOCKEN_DIALOG };
	//}}AFX_DATA

protected:
	LPCTSTR	m_Adr;
	UINT	m_port;
	UINT	m_maxlogs;
	BOOL	m_sc;
	int		m_blen;
	char*	m_buffy;
	CSocken* socky;

	//{{AFX_VIRTUAL(CSockenDlg)
	public:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CSockenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
