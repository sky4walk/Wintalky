// written by André Betz 
// http://www.andrebetz.de

#include "stdafx.h"
#include "socken.h"
#include "Setup.h"

CSetup::CSetup(CWnd* pParent):CDialog(CSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetup)
	m_Adr = _T("ep163");
	m_Port = 2001;
	m_User = 10;
	m_Server = TRUE;
	//}}AFX_DATA_INIT
}

void CSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetup)
	DDX_Text(pDX, IDC_ADR, m_Adr);
	DDV_MaxChars(pDX, m_Adr, 20);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDV_MinMaxUInt(pDX, m_Port, 0, 4000);
	DDX_Text(pDX, IDC_USER2, m_User);
	DDV_MinMaxUInt(pDX, m_User, 1, 20);
	DDX_Radio(pDX, IDC_SERVER, m_Server);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetup, CDialog)
	//{{AFX_MSG_MAP(CSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSetup::OnOK() 
{
	UpdateData(TRUE);
	CDialog::OnOK();
}

UINT CSetup::GetPort()
{
	return m_Port;
}

UINT CSetup::GetUser()
{
	return m_User;
}

CString CSetup::GetAdr()
{
	return m_Adr;
}

BOOL CSetup::GetServ()
{
	return m_Server;
}