// written by André Betz 
// http://www.andrebetz.de

#include "stdafx.h"
#include "socken.h"
#include "sockenDlg.h"

CSockenDlg::~CSockenDlg()
{
	delete socky;
	delete m_buffy;
}

CSockenDlg::CSockenDlg(UINT port,UINT usr):CDialog(CSockenDlg::IDD, NULL)
{
	m_Adr		= NULL;
	m_port		= port;
	m_maxlogs	= usr;
	m_sc		= TRUE;
}

void CSockenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSockenDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSockenDlg, CDialog)
	//{{AFX_MSG_MAP(CSockenDlg)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSockenDlg::OnInitDialog()
{
	m_buffy = new char[255];
	socky = new CSocken(m_port,m_maxlogs,GetSafeHwnd());
	CDialog::OnInitDialog();
	return TRUE;
}

void CSockenDlg::OnPaint() 
{
		CDialog::OnPaint();
}

BOOL CSockenDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	
	
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CSockenDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	
	
	return CDialog::OnCommand(wParam, lParam);
}

LRESULT CSockenDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message==WM_USER+1)
	{
		m_blen = lParam;
		socky->Load(wParam,lParam,m_buffy);
	}
	if(message==WM_USER+2)
	{
		socky->Send(m_buffy,m_blen);
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CSockenDlg::OnOK() 
{
	
	
	CDialog::OnOK();
}

void CSockenDlg::OnClose() 
{
	
	
	CDialog::OnClose();
}
