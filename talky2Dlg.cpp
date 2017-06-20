// written by André Betz 
// http://www.andrebetz.de

#include "stdafx.h"
#include "talky2Dlg.h"

CTalky2Dlg::CTalky2Dlg(CString adr,UINT port):CDialog(CTalky2Dlg::IDD,NULL)
{
	m_Adr = adr;
	m_Port = port;
	//{{AFX_DATA_INIT(CTalky2Dlg)
	m_Eingabe = _T("");
	//}}AFX_DATA_INIT
}

CTalky2Dlg::~CTalky2Dlg()
{
	delete m_socky;
}

void CTalky2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTalky2Dlg)
	DDX_Text(pDX, IDC_INPUT, m_Eingabe);
	DDV_MaxChars(pDX, m_Eingabe, 200);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTalky2Dlg, CDialog)
	//{{AFX_MSG_MAP(CTalky2Dlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CTalky2Dlg::OnInitDialog()
{
	DWORD len = 40;
	char user[40];
	CDialog::OnInitDialog();
	m_socky = new CSocken((LPCTSTR)m_Adr,m_Port,GetSafeHwnd());
	if(m_socky->GetErr() == -1) return FALSE;
	GetUserName(user,&len);
	m_user = user;
	
	CString tst;
	tst.Format("%s ist eingeloggt !!!",(LPCTSTR)m_user);
	Sendy(tst);

	return TRUE;
}

void CTalky2Dlg::OnPaint() 
{
	CDialog::OnPaint();
}

LRESULT CTalky2Dlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message==WM_USER+1)
	{
		memset(m_buffy,0,255);
		m_socky->Load(wParam,lParam,m_buffy);
	}
	if(message==WM_USER+2)
	{
		int i = 0;
		while(m_buffy[i]!=0)
		{
			m_buffy[i] = m_buffy[i] - 100;
			i++;
		}

		CListBox* lst = (CListBox*)GetDlgItem(IDC_OUTPUT);
		lst->InsertString(0,(LPCTSTR)m_buffy);
	}
	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CTalky2Dlg::OnOK() 
{

}
void CTalky2Dlg::OnOk() 
{
	int len;
	CString snd;
	CEdit* pwnd = (CEdit*)GetDlgItem(IDC_INPUT);
	memset(m_txt,0,255);
	len = pwnd->GetLine(0,(LPTSTR)m_txt,255);
	pwnd->SetSel(0,len);
	pwnd->Clear();
	snd.Format("%s:%s",(LPCSTR)m_user,m_txt);
	Sendy(snd);
}

void CTalky2Dlg::Sendy(CString snd)
{
	int z = snd.GetLength();
	if(z>255) z = 255;
	memcpy(m_txt,(LPCTSTR)snd,z);

	for(int i=0;i<snd.GetLength();i++)
	{
		m_txt[i] = m_txt[i] + 100;
	}
	m_socky->Send(m_txt,snd.GetLength());
}

void CTalky2Dlg::OnClose() 
{
	CString tst;
	tst.Format("%s ist ausgeloggt",(LPCTSTR)m_user);
	Sendy(tst);
	Sleep(1000);
	CDialog::OnClose();
}
