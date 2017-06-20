// written by André Betz 
// http://www.andrebetz.de

// ServClnt.cpp : implementation file
//

#include "stdafx.h"
#include "socken.h"
#include "ServClnt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServClnt dialog


CServClnt::CServClnt(CWnd* pParent /*=NULL*/)
	: CDialog(CServClnt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServClnt)
	m_ServClnt = 0;
	//}}AFX_DATA_INIT
}


void CServClnt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServClnt)
	DDX_Radio(pDX, IDC_SERV, m_ServClnt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServClnt, CDialog)
	//{{AFX_MSG_MAP(CServClnt)
	ON_BN_CLICKED(IDC_SERV, OnServ)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServClnt message handlers

void CServClnt::OnServ() 
{
	UpdateData(TRUE);	
}

void CServClnt::OnRadio2() 
{
	UpdateData(TRUE);
	
}

BOOL CServClnt::GetIt()
{
	if(m_ServClnt==0) return TRUE;
	if(m_ServClnt==1) return FALSE;
	
	return FALSE;
}