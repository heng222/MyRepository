// AppStartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "AppStartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppStartDlg dialog


CAppStartDlg::CAppStartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppStartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppStartDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAppStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppStartDlg)
	DDX_Control(pDX, IDC_STATIC_INFOR, m_ctrlInfor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppStartDlg, CDialog)
	//{{AFX_MSG_MAP(CAppStartDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppStartDlg message handlers

void CAppStartDlg::SetInformation(const CString &strInf)
{
	m_ctrlInfor.SetWindowText(strInf);
}
