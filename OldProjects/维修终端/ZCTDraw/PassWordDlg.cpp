// PassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PassWordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXFRAMELEN 8
/////////////////////////////////////////////////////////////////////////////
// CPassWordDlg dialog
CPassWordDlg::CPassWordDlg(CString str,CString strCaption,CWnd* pParent /* = NULL */)
	: CDialog(CPassWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPassWordDlg)
	m_strTrainNumber = _T("");
	//}}AFX_DATA_INIT
	m_strSysKeyCode = str;
	m_strTitle = strCaption;
}

CPassWordDlg::~CPassWordDlg()
{
}


void CPassWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPassWordDlg)
	DDX_Text(pDX, IDC_PASSDLG_EDIT, m_strTrainNumber);
	DDV_MaxChars(pDX, m_strTrainNumber, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPassWordDlg, CDialog)
	//{{AFX_MSG_MAP(CPassWordDlg)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTON0, OnButton0)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_PASSDLG_BUTTONDEL, OnButtondel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassWordDlg message handlers
void CPassWordDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if( stricmp ( m_strTrainNumber ,m_strSysKeyCode ) )	
	{
		MessageBeep(MB_ICONEXCLAMATION);
		MessageBox("√‹¬Î¥ÌŒÛ£¨«Î÷ÿ–¬ ‰»Î£°","æØ∏Ê",MB_OK|MB_ICONEXCLAMATION);
		m_strTrainNumber="";
		UpdateData(FALSE);
		return;
	}
	else 
	{
		CDialog::OnOK();
	}
}

void CPassWordDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CPassWordDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	OnButton("1");
}

void CPassWordDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	OnButton("2");
}

void CPassWordDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	OnButton("3");
}

void CPassWordDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	OnButton("4");
}

void CPassWordDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	OnButton("5");
}

void CPassWordDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	OnButton("6");
}

void CPassWordDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	OnButton("7");
}

void CPassWordDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	OnButton("8");
}

void CPassWordDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	OnButton("9");
}

void CPassWordDlg::OnButton0() 
{
	// TODO: Add your control notification handler code here
	OnButton("0");
}

void CPassWordDlg::OnButtondel() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int l=m_strTrainNumber.GetLength();
	if (l>=1){
		m_strTrainNumber = m_strTrainNumber.Left(l-1); 
		UpdateData(FALSE);
	}
}

BOOL CPassWordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_strTitle + "√‹¬Î ‰»ÎøÚ");
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPassWordDlg::OnButton(CString strN)
{
	UpdateData();
	if (m_strTrainNumber.GetLength()<MAXFRAMELEN){ 
		m_strTrainNumber=m_strTrainNumber+strN;
		UpdateData(FALSE);
	}
}
