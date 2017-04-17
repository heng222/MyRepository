// UserManageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "UserManageDlg.h"
#include "OperatorInf.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserManageDlg dialog
extern CMaintainApp theApp;

CUserManageDlg::CUserManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserManageDlg)
	m_strName = _T("");
	m_strPassword = _T("");
	m_strPWConfirm = _T("");
	m_iUserKind = -1;
	//}}AFX_DATA_INIT
}


void CUserManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserManageDlg)
	DDX_Control(pDX, IDC_USERMANAGE_USERKIND, m_ctrlUserKind);
	DDX_Control(pDX, IDC_USERMANAGE_NAME, m_ctrlName);
	DDX_CBString(pDX, IDC_USERMANAGE_NAME, m_strName);
	DDX_Text(pDX, IDC_USERMANAGE_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_USERMANAGE_PASSWORD_CONFIRM, m_strPWConfirm);
	DDX_CBIndex(pDX, IDC_USERMANAGE_USERKIND, m_iUserKind);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserManageDlg, CDialog)
	//{{AFX_MSG_MAP(CUserManageDlg)
	ON_BN_CLICKED(ID_USERMANAGE_ADD, OnUsermanageAdd)
	ON_BN_CLICKED(ID_USERMANAGE_DEL, OnUsermanageDel)
	ON_BN_CLICKED(ID_USERMANAGE_MODIPAS, OnUsermanageModiPas)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserManageDlg message handlers

void CUserManageDlg::OnUsermanageAdd() 
{
	UpdateData();
	//合法性检查
	if ( !IsValidUserInfo(1) )
	{
		return;
	}
	//
	OperatorNode sNode;
	sNode.strName = m_strName;
	sNode.strPassword = m_strPassword;
	sNode.iKind = m_iUserKind + 1;

	m_cOperatorInf.Add(sNode);
	//m_cOperatorInf.WriteFile();
	//给出提示
	if (MessageBox("用户"+m_strName+"的信息已写入文件！是否继续","操作成功",MB_ICONINFORMATION | MB_YESNO) == IDNO )
	{
		OnCancel();
	}
	else
	{
		ClearUserInfo();
	}
}
void CUserManageDlg::OnUsermanageModiPas() 
{
	UpdateData();
	//合法性检查
	if ( !IsValidUserInfo(3) )
	{
		return;
	}	
	//
	m_cOperatorInf.ModifyUserPassword(m_strName,m_strPassword);
	//m_cOperatorInf.WriteFile();
	////给出提示
	if (MessageBox("用户"+m_strName+"的密码已经更改！是否继续？","操作成功",MB_ICONINFORMATION | MB_YESNO) == IDNO )
	{
		OnCancel();
	}
	else
	{
		ClearUserInfo();
	}

}
void CUserManageDlg::OnUsermanageDel() 
{
	UpdateData();

	//合法性检查
	if ( !IsValidUserInfo(2) )
	{
		return;
	}

	//删除用户
	m_cOperatorInf.DelUser(m_strName);
	//m_cOperatorInf.WriteFile();

	//给出提示
	if (MessageBox("用户"+m_strName+"的信息已已经部删除！是否继续？","操作成功",MB_ICONINFORMATION | MB_YESNO) == IDNO )
	{
		DestroyWindow();
	}
	else
	{
		ClearUserInfo();
	}
}

BOOL CUserManageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//----------------------------------------------------------------
	if ( !m_cOperatorInf.ReadFile(theApp.m_strExePath + OPERATORINFOPATHNAME) )
	{
		m_cOperatorInf.WriteFile();
		m_cOperatorInf.ReadFile();
	}
	//将名字填入
	for ( int i = 0; i<m_cOperatorInf.GetLength(); i++ )
	{
		m_ctrlName.AddString( m_cOperatorInf.GetName(i) );
	}
	//----------------------------------------------------------------
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



BOOL CUserManageDlg::IsValidUserInfo(int iFlag/* = 1*/)
{
	//合法性检查
	if ( m_strName.IsEmpty() || m_strPassword.IsEmpty() )
	{
		MessageBox("用户名或密码不能为空！","提示",MB_ICONINFORMATION);
		return false;
	}
	if ( m_strPassword.Compare(m_strPWConfirm) )
	{
		MessageBox("两次输入的密码不一致！请重新输入密码！","提示",MB_ICONINFORMATION);
		m_strPassword.Empty();
		m_strPWConfirm.Empty();
		UpdateData(false);
		return false;
	}
	//新增用户时检查
	if ( iFlag == 1 )
	{
		if ( m_cOperatorInf.IsExistUser(m_strName) != "" )
		{
			MessageBox("用户"+m_strName+"已经存在，请另指定用户名！","提示",MB_ICONINFORMATION);
			m_strName.Empty();
			m_ctrlName.SetFocus();
			UpdateData(false);
			return false;
		}
		if ( m_iUserKind < 0 )
		{
			MessageBox("请选择一种用户类型!","提示",MB_ICONINFORMATION);
			m_ctrlUserKind.SetFocus();
			return false;
		}
	}//----
	//删除用户时检查
	else if ( iFlag == 2 )
	{
		if ( m_strName == "Administrator" )
		{
			MessageBox("用户Administrator是系统内置的帐户，无法删除！","警告",MB_ICONINFORMATION);
			return false;
		}
		if ( m_cOperatorInf.IsExistUser(m_strName).IsEmpty() )
		{
			MessageBox("不存在用户"+m_strName+"，无法完成删除操作","提示",MB_ICONINFORMATION);
			//m_strName.Empty();
			//UpdateData(false);
			return false;
		}
	}
	//更改密码时检查
	else if ( iFlag == 3 )
	{
		if ( m_cOperatorInf.IsExistUser(m_strName).IsEmpty() )
		{
			MessageBox("不存在用户"+m_strName+"，无法完成更改密码操作","提示",MB_ICONINFORMATION);
			//m_strName.Empty();
			//UpdateData(false);
			return false;
		}
	}
	//
	return true;
}

void CUserManageDlg::ClearUserInfo()
{
	m_strName.Empty();
	m_strPassword.Empty();
	m_strPWConfirm.Empty();
	m_ctrlUserKind.SetCurSel(-1);
	UpdateData(false);
}

BOOL CUserManageDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DestroyWindow();
}

void CUserManageDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	//( (CMainFrame*)(AfxGetMainWnd()) )->m_pUserMngDlg = NULL;
	//delete this;
	CDialog::PostNcDestroy();
}

void CUserManageDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	//DestroyWindow();
	CDialog::OnCancel();
}
