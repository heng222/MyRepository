// InfPromptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "InfPromptDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfPromptDlg dialog


CInfPromptDlg::CInfPromptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfPromptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfPromptDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInfPromptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfPromptDlg)
	DDX_Control(pDX, IDC_COMBO_DETAILEDINF, m_ctrlDetailedInf);
	DDX_Control(pDX, IDC_STATIC_INF, m_ctrlPromptInf);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfPromptDlg, CDialog)
	//{{AFX_MSG_MAP(CInfPromptDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SHOWNEWMSG, OnButtonShowNewMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfPromptDlg message handlers

BOOL CInfPromptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pMainFrame = (CMainFrame*)AfxGetMainWnd();

	//----------------------------------------------------------------
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInfPromptDlg::OnClose() 
{
	m_ctrlDetailedInf.ResetContent();
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

void CInfPromptDlg::PostNcDestroy() 
{
	delete this;
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
}


//�鿴����Ϣ
void CInfPromptDlg::OnButtonShowNewMsg() 
{
	if ( m_ctrlDetailedInf.GetCount() == 0 )
	{
		return;
	}
	
	//--------------------------------------------------------
	int		iCurNo = m_ctrlDetailedInf.GetCurSel();
	CString strMsg = m_newMessage.GetAt(iCurNo)->m_strMsgKind;
	
	int		iOrder = m_newMessage.GetAt(iCurNo)->m_iOrder;
	CString strFullPathName = m_newMessage.GetAt(iCurNo)->m_strPathName;

	//ɾ���鿴�˵���Ϣ
	m_newMessage.DeleteItem( iCurNo );
	ShowNewMsg();

	if ( strMsg.CompareNoCase("ʩ����������") == 0 )
	{
		/*m_pMainFrame->m_pShowComdDlg = new CShowCommand(DISPHKINDCLOSE,iOrder,strFullPathName);
		m_pMainFrame->m_pShowComdDlg->Create(CShowCommand::IDD,this);
		m_pMainFrame->m_pShowComdDlg->ShowWindow(SW_SHOW);*/
		CShowCommand dlg(DISPHKINDCLOSE,iOrder,strFullPathName);
		dlg.DoModal();

	}
	else if ( strMsg.CompareNoCase("ʩ����ͨ����") == 0 )
	{
		/*m_pMainFrame->m_pShowComdDlg = new CShowCommand(DISPHKINDOPEN,iOrder,strFullPathName);
		m_pMainFrame->m_pShowComdDlg->Create(CShowCommand::IDD,this);
		m_pMainFrame->m_pShowComdDlg->ShowWindow(SW_SHOW);*/
		CShowCommand dlg(DISPHKINDOPEN,iOrder,strFullPathName);
		dlg.DoModal();
	}
	//
	//m_newMessage.DeleteItem( iCurNo );
	//
	//ShowNewMsg();

}

//����δ�鿴����Ϣ����COMBOBOX��
void CInfPromptDlg::ShowNewMsg()
{
	//ȡ��δ����Ϣ�ĸ���
	CString strInf;

	int iNewmsgCount = m_newMessage.GetLength();
	if ( iNewmsgCount > 0 )
	{
		strInf.Format("��ʾ������%d���µ���Ϣ����ע����ա�", iNewmsgCount);
	}
	else
	{
		strInf.Format("û���յ��µ���Ϣ��");
	}
	
	m_ctrlPromptInf.SetWindowText(strInf);

	//ȡ����ϸ��Ϣ
	m_ctrlDetailedInf.ResetContent();
	for ( int i = 0; i<m_newMessage.GetLength(); i++ )
	{
		strInf.Format("<%s> %s",m_newMessage.GetAt(i)->m_strMsgKind,
			m_newMessage.GetAt(i)->m_tTime.Format("%Y-%m-%d %H:%M:%S"));

		m_ctrlDetailedInf.AddString(strInf);
	}
	if ( m_ctrlDetailedInf.GetCount() > 0 )
	{
		m_ctrlDetailedInf.SetCurSel( m_ctrlDetailedInf.GetCount()-1 );
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
}
