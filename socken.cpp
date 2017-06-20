// written by André Betz 
// http://www.andrebetz.de

#include "stdafx.h"
#include "socken.h"
#include "Talky2Dlg.h"
#include "sockenDlg.h"
#include "Setup.h"

BEGIN_MESSAGE_MAP(CSockenApp, CWinApp)
	//{{AFX_MSG_MAP(CSockenApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

CSockenApp theApp;

BOOL CSockenApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CSetup set;
	if(set.DoModal()==IDOK)
	{
		if(!set.GetServ())
		{
			CSockenDlg dlg(set.GetPort(),set.GetUser());
			dlg.DoModal();
		}
		else
		{
			CTalky2Dlg dlg(set.GetAdr(),set.GetPort());
			dlg.DoModal();
		}
	}
	return FALSE;
}
