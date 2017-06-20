// written by André Betz 
// http://www.andrebetz.de

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

class CTalky2App : public CWinApp
{
public:
	CTalky2App();

	//{{AFX_VIRTUAL(CTalky2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTalky2App)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
