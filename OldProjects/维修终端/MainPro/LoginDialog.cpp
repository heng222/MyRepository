// LoginDialog.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "LoginDialog.h"
#include "OperatorInf.h"

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
	m_strPassword = _T("");
	m_nDegree=0;
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDialog)
	DDX_Control(pDX, IDC_LOGIN_NAME, m_ctrlName);
	DDX_Text(pDX, IDC_LOGIN_PASSWORD, m_strPassword);
	DDX_CBString(pDX, IDC_LOGIN_NAME, m_strName);
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

	//----------------------------------------------------------------
	//���Ϸ��û��ļ�
	if ( !m_cOperatorInf.ReadFile(theApp.m_strExePath + OPERATORINFOPATHNAME) )
	{
		//�ļ������ڣ����ʼ��һ���û�(�û�����Administrator�����룺123)
		m_cOperatorInf.AddAdministrator();
		m_cOperatorInf.WriteFile();
	}
	//����ע���û������������б��
	for ( int i = 0; i<m_cOperatorInf.GetLength(); i++ )
	{
		m_ctrlName.AddString(m_cOperatorInf.GetName(i));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDialog::OnOK() 
{
	UpdateData();
	//---------------------------------------
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
	//------------------------------------------
	
	BOOL bRight = false;
	if ( m_cOperatorInf.IsExistUser(m_strName) == m_strPassword )
	{
		bRight = true;
	}
	
	//------------------------------------------
	if(!bRight)
	{
		if(m_nDegree>2)
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
	//-------------------------------------------
	//���û�����Ϣ����theApp�ĳ�Ա���Ա�����
	m_cOperatorInf.FindUser( m_strName,theApp.m_sCurOperator );
	CDialog::OnOK();
}
