// written by André Betz 
// http://www.andrebetz.de

// SetServ.cpp : implementation file
//

#include "stdafx.h"
#include "socken.h"
#include "SetServ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetServ dialog


CSetServ::CSetServ(CWnd* pParent /*=NULL*/)
	: CDialog(CSetServ::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetServ)
	m_port = 2000;
	m_maxLogs = 4;
	//}}AFX_DATA_INIT
}


void CSetServ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetServ)
	DDX_Text(pDX, IDC_EDIT2, m_port);
	DDV_MinMaxUInt(pDX, m_port, 0, 65000);
	DDX_Text(pDX, IDC_EDIT3, m_maxLogs);
	DDV_MinMaxUInt(pDX, m_maxLogs, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetServ, CDialog)
	//{{AFX_MSG_MAP(CSetServ)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetServ message handlers
