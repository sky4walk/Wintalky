// written by André Betz 
// http://www.andrebetz.de

// SetClnt.cpp : implementation file
//

#include "stdafx.h"
#include "socken.h"
#include "SetClnt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetClnt dialog


CSetClnt::CSetClnt(CWnd* pParent /*=NULL*/)
	: CDialog(CSetClnt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetClnt)
	m_Adr = _T("ep163");
	m_Port = 2000;
	//}}AFX_DATA_INIT
}


void CSetClnt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetClnt)
	DDX_Text(pDX, IDC_EDIT1, m_Adr);
	DDV_MaxChars(pDX, m_Adr, 16);
	DDX_Text(pDX, IDC_EDIT2, m_Port);
	DDV_MinMaxUInt(pDX, m_Port, 0, 65000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetClnt, CDialog)
	//{{AFX_MSG_MAP(CSetClnt)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetClnt message handlers
