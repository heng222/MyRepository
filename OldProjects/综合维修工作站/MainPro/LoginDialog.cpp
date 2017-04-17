// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "LoginDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog


CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDialog)
	m_strName = _T("");
	m_strPassword = _T("");
	m_nDegree=0;
	//}}AFX_DATA_INIT
}


void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDialog)
	DDX_Control(pDX, IDC_LOGIN_NAME, m_ctrlName);
	DDX_Text(pDX, IDC_LOGIN_NAME, m_strName);
	DDX_Text(pDX, IDC_LOGIN_PASSWORD, m_strPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	//{{AFX_MSG_MAP(CLoginDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog message handlers

BOOL CLoginDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDialog::OnOK() 
{
	BeginWaitCursor();
	//--------------------------------------
	CAdoConnection adoConnect;
	CAdoRecordSet  adoSet;
	if (adoConnect.ConnectOracle(theApp.m_strDBDataSource,theApp.m_strDBUserID,theApp.m_strDBPassword))
	{
		adoSet = adoConnect.Execute("SELECT * FROM OPERATORINF");
	}
	else
	{
		AfxMessageBox("���ݿ�����ʧ��!\n�޷���ɵ�¼����!");
		CDialog::OnCancel();
		return;
	}
	// ---------------------------------------------------
	UpdateData();
	if( m_strName.IsEmpty() )
	{
		AfxMessageBox("�û����Ʋ���Ϊ��!");
		return;
	}
	if( m_strPassword.IsEmpty() )
	{
		AfxMessageBox("�����Ϊ��!");
		return;
	}
	m_nDegree+=1;

	//--------------------------------
	CString strName,strPassword;
	BOOL bRight=FALSE;

	adoSet.MoveFirst();
	while(!adoSet.IsEOF())
	{
		adoSet.GetCollect("C_NAME",strName);
		adoSet.GetCollect("C_PASSWORD",strPassword);

		if(strName == m_strName && strPassword == m_strPassword)
		{
			bRight=TRUE;
			break;
		}
		adoSet.MoveNext();
	}
	if(!bRight)
	{
		if( m_nDegree == 3 )
		{
			AfxMessageBox("�û����Ϳ���У�����δ���,������ϵͳ�ĺϷ��û�!");
			OnCancel();
			return;
		}
		else
		{
			AfxMessageBox("������û����Ϳ���У�����,����������!");
			return;
		}
	}
	//------------------------
	EndWaitCursor();
	CDialog::OnOK();
}
