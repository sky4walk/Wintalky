// written by André Betz 
// http://www.andrebetz.de

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
class CSockenApp : public CWinApp
{
public:
	//{{AFX_VIRTUAL(CSockenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CSockenApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
