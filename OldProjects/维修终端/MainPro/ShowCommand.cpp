// ShowCommand.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "ShowCommand.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowCommand dialog
extern CMaintainApp theApp;

CShowCommand::CShowCommand(BYTE byKind,/*= 0*/ BYTE byOrder,/*= 0*/CString strPathName/*=""*/,CWnd* pParent /*=NULL*/)
	: CDialog(CShowCommand::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowCommand)
	m_strContent = _T("");
	m_strDispatcher = _T("");
	m_strOrder = _T("");
	m_strStations = _T("");
	m_strSendTime = _T("");
	m_strChecker = _T("");
	m_strCheckTime = _T("");
	m_strCopyFor = _T("");
	m_strOrgReceive = _T("");
	m_strOrgSend = _T("");
	m_strTitle = _T("");
	m_strReciver = _T("");
	m_strRecBurName = _T("");
	m_strRecSubBurName = _T("");
	m_strSendBurName = _T("");
	m_strSendDispName = _T("");
	m_strSendSubBurName = _T("");
	//}}AFX_DATA_INIT
	m_byKind = byKind; 
	m_byOrder = byOrder;
	m_strPathName = strPathName;
	m_bSignFor = FALSE;
}

void CShowCommand::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowCommand)
	DDX_Control(pDX, IDC_BTN_SIGNFOR, m_ctrlSignFor);
	DDX_Text(pDX, IDC_CONTENT, m_strContent);
	DDX_Text(pDX, IDC_DISPATCHER, m_strDispatcher);
	DDX_Text(pDX, IDC_ORDER, m_strOrder);
	DDX_Text(pDX, IDC_STATIONS, m_strStations);
	DDX_Text(pDX, IDC_SENDTIME, m_strSendTime);
	DDX_Text(pDX, IDC_SHOWDIS_CHECKER, m_strChecker);
	DDX_Text(pDX, IDC_SHOWDIS_CHECKTIME, m_strCheckTime);
	DDX_Text(pDX, IDC_SHOWDIS_COPYFOR, m_strCopyFor);
	DDX_Text(pDX, IDC_SHOWDIS_ORGRECEIVE, m_strOrgReceive);
	DDX_Text(pDX, IDC_SHOWDIS_ORGSEND, m_strOrgSend);
	DDX_Text(pDX, IDC_SHOWDIS_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_RECIVER, m_strReciver);
	DDX_Text(pDX, IDC_EDIT_RECBUR, m_strRecBurName);
	DDX_Text(pDX, IDC_EDIT_RECSUBBUR, m_strRecSubBurName);
	DDX_Text(pDX, IDC_EDIT_SENDBUR, m_strSendBurName);
	DDX_Text(pDX, IDC_EDIT_SENDDISPID, m_strSendDispName);
	DDX_Text(pDX, IDC_EDIT_SENDSUBBUR, m_strSendSubBurName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowCommand, CDialog)
	//{{AFX_MSG_MAP(CShowCommand)
	ON_BN_CLICKED(IDC_BTN_SIGNFOR, OnBtnSignFor)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowCommand message handlers

BOOL CShowCommand::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//--------------------------------------------

	if ( m_strPathName.IsEmpty() == FALSE )
	{
		CReadRecord Records;
		Records.ReadRecords(m_strPathName);

		m_strStations = Records.GetValue(m_byOrder,"CC_Stations");
		//取出记录中的相关信息并更新到对话框中
		if ( m_byKind == DISPHKINDCLOSE )//要显示封锁命令
		{
			m_strOrder		= Records.GetValue(m_byOrder,	"CC_Order");
			m_strSendTime	= Records.GetValue(m_byOrder,	"CC_DateTime");
			m_strDispatcher = Records.GetValue(m_byOrder,	"CC_Dispatcher");

			m_strSendBurName	= Records.GetValue(m_byOrder,	"CC_SendBureauName");
			m_strSendSubBurName = Records.GetValue(m_byOrder,	"CC_SendSubBurName");
			m_strSendDispName	= Records.GetValue(m_byOrder,	"CC_SendDispName");
			m_strRecBurName		= Records.GetValue(m_byOrder,	"CC_RecBureauName");
			m_strRecSubBurName	= Records.GetValue(m_byOrder,	"CC_RecSubBurName");

			m_strTitle		= Records.GetValue(m_byOrder,	"CC_Title");
			m_strStations	= Records.GetValue(m_byOrder,	"CC_Stations");
			m_strOrgSend	= Records.GetValue(m_byOrder,	"CC_OrgSend");
			m_strOrgReceive	= Records.GetValue(m_byOrder,	"CC_OrgReceive");
			m_strChecker	= Records.GetValue(m_byOrder,	"CC_Checker");
			m_strCheckTime	= Records.GetValue(m_byOrder,	"CC_CheckTime");
			m_strCopyFor	= Records.GetValue(m_byOrder,	"CC_CopyFor");
			m_strContent	= Records.GetValue(m_byOrder,	"CC_Content");
		}
		else if ( m_byKind == DISPHKINDOPEN )//要显示开通命令
		{
			m_strOrder		= Records.GetValue(m_byOrder,	"OC_Order");
			m_strSendTime	= Records.GetValue(m_byOrder,	"OC_DateTime");
			m_strDispatcher = Records.GetValue(m_byOrder,	"OC_Dispatcher");

			m_strSendBurName	= Records.GetValue(m_byOrder,	"OC_SendBureauName");
			m_strSendSubBurName = Records.GetValue(m_byOrder,	"OC_SendSubBurName");
			m_strSendDispName	= Records.GetValue(m_byOrder,	"OC_SendDispName");
			m_strRecBurName		= Records.GetValue(m_byOrder,	"OC_RecBureauName");
			m_strRecSubBurName	= Records.GetValue(m_byOrder,	"OC_RecSubBurName");

			m_strTitle		= Records.GetValue(m_byOrder,	"OC_Title");
			m_strStations	= Records.GetValue(m_byOrder,	"OC_Stations");
			m_strOrgSend	= Records.GetValue(m_byOrder,	"OC_OrgSend");
			m_strOrgReceive	= Records.GetValue(m_byOrder,	"OC_OrgReceive");
			m_strChecker	= Records.GetValue(m_byOrder,	"OC_Checker");
			m_strCheckTime	= Records.GetValue(m_byOrder,	"OC_CheckTime");
			m_strCopyFor	= Records.GetValue(m_byOrder,	"OC_CopyFor");
			m_strContent	= Records.GetValue(m_byOrder,	"OC_Content");
		}
		UpdateData(false);
	}
	//------------------------------------------------
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//人工回执
void CShowCommand::OnBtnSignFor() 
{
	UpdateData();
	if ( m_strReciver.IsEmpty() )
	{
		MessageBox("签收人一栏不能为空！","警告",MB_ICONINFORMATION);
		return;
	}
	//----------------------------------------
	BYTE	byFrame[DISPHCONFIRMMAXLEN];
	WORD	nFrameSend = 0;	//回执帧下标

	
	//功能码(有关维修的调度命令)(BYTE)
	byFrame[nFrameSend++] = DISPHFUNTCODE;

	//子功能码(人工回执)(BYTE)
	byFrame[nFrameSend++] = DISPHCONFIRMHUMAN; 


	
	//受令站码
	WORD wStationNum = CReadStationInf::GetActiveStation();
	memcpy(byFrame+nFrameSend,&wStationNum,2);
	nFrameSend += 2;

	//命令编号
	DWORD dwOrder = (DWORD)atoi(m_strOrder);
	memcpy(byFrame+nFrameSend,&dwOrder,4);
	nFrameSend += 4;
	
	//回执时间(7BYTE)
	CTime tConfirmTime = CTime::GetCurrentTime();
	WORD wYear = tConfirmTime.GetYear();
	memcpy(byFrame+nFrameSend,&wYear,2);
	nFrameSend += 2;
	byFrame[nFrameSend++] = tConfirmTime.GetMonth();
	byFrame[nFrameSend++] = tConfirmTime.GetDay();
	byFrame[nFrameSend++] = tConfirmTime.GetHour();
	byFrame[nFrameSend++] = tConfirmTime.GetMinute();
	byFrame[nFrameSend++] = tConfirmTime.GetSecond();

	//受令者长度
	WORD wRecLength = m_strReciver.GetLength();
	memcpy(byFrame+nFrameSend,&wRecLength,2);
	nFrameSend += 2;
	//受令者
	for ( WORD i = 0; i<wRecLength; i++)
	{
		byFrame[nFrameSend++] = m_strReciver.GetAt(i);
	}

	//受令结果(必须接受)
	byFrame[nFrameSend++] = 0x01;

	//发送人工回执帧
	if ( ((CMainFrame*)AfxGetMainWnd())->m_socketClient.IsOpen() )
	{
	
		((CMainFrame*)AfxGetMainWnd())->m_socketClient.WriteComm(DISPHCONFIRMKIND,0X01,byFrame,nFrameSend,INFINITE);
		m_bSignFor = TRUE;
		if ( MessageBox("人工回执已发送。是否关闭此窗口？","提示",MB_ICONQUESTION | MB_YESNO) == IDYES )
		{
			OnOK();
		}
	}
	else
	{
		MessageBox("网络不通，请稍后发送人工回执。","提示：网络不通",MB_ICONINFORMATION);
		return;
	}
	//
	m_ctrlSignFor.EnableWindow(FALSE);
	
}

void CShowCommand::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if ( m_bSignFor == FALSE )
	{
		int iResultID = MessageBox("此调度命令尚未进行人工签收! 确认要退出吗？","提示",MB_ICONQUESTION | MB_YESNOCANCEL);
		if ( iResultID == IDYES )
		{
			CDialog::OnClose();
		}
		else if ( iResultID == IDNO )
		{
			return;
		}
		else
		{
			return;
		}
	}
	//
	CDialog::OnClose();
}
