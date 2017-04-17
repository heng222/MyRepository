// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Maintain.h"
#include "MainFrm.h"

#include "ConstructRequest.h"
#include "ConstructQuery.h"

#include "MaintainView.h"
#include "UserManageDlg.h"
#include "AlarmInfo.h"
#include "WarnLogDlg.h"
#include "WarnNoteDlg.h"
#include "RailwayBureau.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_OPERATOR_CONSTRUCTREQUEST, OnOperatorConstructrequest)
	ON_COMMAND(ID_OPERATE_CONSTRUCTQUERY, OnOperateConstructquery)
	ON_COMMAND(ID_SYSTEM_USERMANAGE, OnSystemUsermanage)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_OPERATOR_CONSTRUCTREQUEST, OnUpdateOperatorConstructrequest)
	ON_UPDATE_COMMAND_UI(ID_SYSTEM_USERMANAGE, OnUpdateSystemUsermanage)
	ON_COMMAND(ID_VIEW_SHOWWARNLOG, OnViewShowwarnlog)
	ON_COMMAND(ID_VIEW_NEWMESSAGE, OnViewNewmessage)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NEWMESSAGE, OnUpdateViewNewmessage)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_UPDATE_CONNECTION, OnUpdateConnection)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_WAN,
	ID_INDICATOR_TIME,
	ID_INDICATOR_UNIT,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bConnected	= FALSE;

//	m_pShowComdDlg	= NULL;
//	m_pRequestDlg	= NULL;
//	m_pQueryDlg		= NULL;
//	m_pUserMngDlg	= NULL;
	
	m_pWarnLogDlg	= NULL;
	m_pWarnNoteDlg	= NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
/*	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
*/
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
/*	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
*/


	//创建AlarmNote 显示框
	m_pWarnNoteDlg = new CWarnNoteDlg;
	m_pWarnNoteDlg->Create(CWarnNoteDlg::IDD,this);

	//连接到自律机
	/*if ( ConnectToALServer() == FALSE )
	{
		int iResultID = MessageBox("连接到自律机失败，你可能无法进行行车信息的实时监视，但仍然可以进行施工查询等本地所操作。是否继续启动程序？","提示",MB_ICONEXCLAMATION | MB_YESNO );
		if ( iResultID == IDNO )
		{
			PostMessage(WM_CLOSE);
			return -1;
		}
	}*/
	
	//启动计时器
	SetTimer(ID_CLOCK_MAINFRAME,1000,NULL);
	//
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX | WS_MAXIMIZE;
	cs.style &= ~(LONG) FWS_ADDTOTITLE;
	
    // Size the window to full screen size  
	cs.cy = ::GetSystemMetrics(SM_CYSCREEN); 
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN); 
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnReceive()
{	
	BYTE byFrameKind = BufferTmp[0];	//帧类型
	BYTE byVersion   = BufferTmp[1];	//数据版本号
	
	WORD wDataLength;//数据长度
	memcpy(&wDataLength,BufferTmp+2,2);
	BYTE *pFrame;	
	pFrame = new BYTE[wDataLength];
	memcpy( pFrame, BufferTmp+4, wDataLength);//将数据暂存于缓冲中

	if( byFrameKind == DISPHFRAMEKIND )//若收到的是调度命令
	{

		//(先取出受令站码长度)
		WORD wReceiverLen = 0;
		memcpy(&wReceiverLen,pFrame+9,sizeof(wReceiverLen));
		wReceiverLen += 11;
		DWORD dwOrder;//命令编号
		memcpy(&dwOrder,pFrame+wReceiverLen,sizeof(dwOrder));//取出命令编号

		//自动发送调度命令回执帧(机器回执)
		//PostMessage(WM_SENDCONFIRMFRAME, dwOrder);
		SendConfirmFrame(dwOrder);


		//分析收到的调度命令
		//PostMessage(WM_ANALYSEDISPATCHFRAME,(WPARAM)pFrame);		
		AnalyseDispatchFrame(pFrame);
		
	}
	
	else
	{
		//--------------------------------
		POSITION pos = theApp.m_pDocTemplate->GetFirstDocPosition();
		if ( !pos )
		{
			return;
		}
		CMaintainDoc*	pDoc = (CMaintainDoc*)theApp.m_pDocTemplate->GetNextDoc(pos);
		//----------------------------------

		//更新站场图
		pDoc->m_ZCTMag.OnReceive(BufferTmp);
	}
	
	//释放缓冲
	delete[] pFrame;
}


//调度命令回执（机器回执）
void CMainFrame::SendConfirmFrame(DWORD dwOrder)
{
	BYTE	byFrame[DISPHCONFIRMMAXLEN];
	WORD	nFrameSend = 0;	//回执帧下标


	//功能码(有关维修的调度命令)(BYTE)
	byFrame[nFrameSend++] = DISPHFUNTCODE;

	//子功能码(机器回执)(BYTE)
	byFrame[nFrameSend++] = DISPHCONFIRMMACHINE; 
	
	
	//受令站码
	WORD wStationNum = CReadStationInf::GetActiveStation();
	memcpy(byFrame+nFrameSend,&wStationNum,2);
	nFrameSend += 2;

	//命令编号
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
	//


	//发送回执帧
	m_socketClient.WriteComm(DISPHCONFIRMKIND,0X01,byFrame,nFrameSend,INFINITE);
}

void CMainFrame::AnalyseDispatchFrame(LPBYTE pFrame)
{
	CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	WORD wFrameIndex = 3;
	int i = 0;
	CRailwayBureau sBureau;	//保存路局及其分局的信息
	if ( sBureau.ReadFile(theApp.m_strExePath + "ini\\路局分局代码.ini") == FALSE )
	{
		MessageBox("Cannot open the \"路局分局代码.ini\" file!","Error!",MB_ICONERROR);
	}

	//---------------------------------------------------
	//发令局代码
	int iRoadID = pFrame[wFrameIndex++];
	CString strSendBureauName = sBureau.GetRoadBureauName( iRoadID );

	//发令分局/分界口
	CString strSendSubBureauName = sBureau.GetSubBureauName(iRoadID,pFrame[wFrameIndex++]);

	//发令调度台ID
	WORD wSendDispatchID;
	memcpy(&wSendDispatchID,pFrame+wFrameIndex,2);
	CString strSendDispatchName;
	strSendDispatchName.Format("调度台%d",wSendDispatchID);
	wFrameIndex+=2;

	//受令局
	iRoadID = pFrame[wFrameIndex++];
	CString strRecBureauName = sBureau.GetRoadBureauName(iRoadID);

	//受令分局/分界口
	CString strRecSubBureauName = sBureau.GetSubBureauName(iRoadID,pFrame[wFrameIndex++]);

	//受令站码长度
	WORD wStationsLen;
	memcpy(&wStationsLen,pFrame+wFrameIndex,2);
	wFrameIndex += 2;
	//受令站码（字符串）
	CString strStations;
	memcpy(strStations.GetBuffer(wStationsLen),pFrame+wFrameIndex,wStationsLen);
	strStations.ReleaseBuffer();
	strStations = pStationInf->CovNumToName(strStations);
	wFrameIndex += wStationsLen;
	
	//命令编号
	WORD wOrder;
	memcpy(&wOrder,pFrame+wFrameIndex,4);
	wFrameIndex += 4;

	//命令代码(1为封锁命令，2为开通命令)
	WORD wCommandKind;
	memcpy( &wCommandKind, pFrame+wFrameIndex, 2 );
	wFrameIndex += 2;
	ASSERT( wCommandKind>0 && wCommandKind <3 );

	//发令时间
	COleDateTime oleCMTime;
	WORD wYear;
	memcpy(&wYear,pFrame+wFrameIndex,2);
	oleCMTime.SetDateTime( wYear,
		pFrame[wFrameIndex+2],
		pFrame[wFrameIndex+3],
		pFrame[wFrameIndex+4],
		pFrame[wFrameIndex+5],
		pFrame[wFrameIndex+6]
		);
	wFrameIndex += 7;
	CString strCMTime;
	strCMTime = oleCMTime.Format("%Y-%m-%d %H:%M:%S");

	//发令机构(20BYTE)
	CString strOrgSend;
	for ( i=0; i<20; i++)
	{
		if(pFrame[wFrameIndex] != 0)
		{
			strOrgSend += pFrame[wFrameIndex];
		}
		wFrameIndex++;
	}

	//调度员姓名(发令者)
	CString strDispatcher;
	for ( i=0; i<20; i++)
	{
		if(pFrame[wFrameIndex] != 0)
		{
			strDispatcher += pFrame[wFrameIndex];
		}
		wFrameIndex++;
	}
	//受令机构
	CString strOrgReceive;
	for ( i=0; i<20; i++)
	{
		if(pFrame[wFrameIndex] != 0)
		{
			strOrgReceive += pFrame[wFrameIndex];
		}
		wFrameIndex++;
	}

	//审核人(20 BYTE)
	CString strChecker;
	for ( i=0; i<20; i++)
	{
		if(pFrame[wFrameIndex] != 0)
		{
			strChecker += pFrame[wFrameIndex];
		}
		wFrameIndex++;
	}
	//审核时间(7BYTE)
	COleDateTime oleCheckTime;
	memcpy(&wYear,pFrame+wFrameIndex,2);
	oleCheckTime.SetDateTime( wYear,
		pFrame[wFrameIndex+2],
		pFrame[wFrameIndex+3],
		pFrame[wFrameIndex+4],
		pFrame[wFrameIndex+5],
		pFrame[wFrameIndex+6]);
	wFrameIndex += 7;

	CString strCheckTime;
	if ( oleCheckTime.GetStatus() == COleDateTime::valid )
	{
		strCheckTime = oleCheckTime.Format("%Y-%m-%d %H:%M:%S");
	}

	//登消记时间
	COleDateTime olePRTime;
	memcpy(&wYear,pFrame+wFrameIndex,2);
	olePRTime.SetDateTime( wYear,
		pFrame[wFrameIndex+2],
		pFrame[wFrameIndex+3],
		pFrame[wFrameIndex+4],
		pFrame[wFrameIndex+5],
		pFrame[wFrameIndex+6]);
	wFrameIndex += 7;

	CString strPRTime;
	CString strFileName;
	strPRTime = olePRTime.Format("%Y-%m-%d %H:%M:%S");
	strFileName = olePRTime.Format("%Y-%m-%d.rec");

	//抄送目标长度
	WORD wDesLen;
	memcpy( &wDesLen, pFrame+wFrameIndex,2);
	wFrameIndex += 2;
	//抄送目标
	CString strCopyFor;
	memcpy(strCopyFor.GetBuffer(wDesLen),pFrame+wFrameIndex,wDesLen);
	strCopyFor.ReleaseBuffer();
	wFrameIndex += wDesLen;

	//标题(40 BYTE)
	CString strTitle;
	for ( i=0; i<40; i++)
	{
		if(pFrame[wFrameIndex] != 0)
		{
			strTitle += pFrame[wFrameIndex];
		}
		wFrameIndex++;
	}

	//命令长度
	WORD wContentLen;
	memcpy(&wContentLen, pFrame+wFrameIndex, 2);
	wFrameIndex += 2;
	//命令正文
	CString strContent;
	memcpy(strContent.GetBuffer(wContentLen), pFrame+wFrameIndex, wContentLen);
	strContent.ReleaseBuffer();
	//--------------

	
	//--------------------------------------------------------------------
	//确定系统当前路径以及得到记录所在的文件名
	CString strFullPathName;
	strFullPathName.Format("%s%s%s",theApp.m_strExePath,REACORDPATHNAME,strFileName);
	//从文件中读取记录
	CReadRecord Records;
	
	if ( !Records.ReadRecords(strFullPathName) )
	{
		//若不存在此文件，则说明本车站没有进行施工请求，可能是其它站
		//进行施工或是由中心编写的请求,进而收到调度命令
	}
	//-----------------------------------
	//将调度命令更新到记录集中
	BYTE iOrder;
	if ( wCommandKind == DISPHKINDCLOSE )//封锁命令
	{
		//得到要更新的记录号
		iOrder = Records.GetOrderByDT("R_DateTime",strPRTime);
		if ( iOrder == 0 ) //说明是其它站进行的请求或是工作站直接下达的命令，
			//故本站无登记信息，所以新增一个记录
		{
			iOrder = Records.GetRecordNum() + 1;
			Records.SetValue(iOrder,"R_DateTime",strPRTime);
		}

		//根据记录号更新其它内容
		Records.SetValue(iOrder,"CC_Order",wOrder);
		Records.SetValue(iOrder,"CC_DateTime",strCMTime);
		Records.SetValue(iOrder,"CC_Dispatcher",strDispatcher);

		Records.SetValue(iOrder,"CC_SendBureauName",strSendBureauName);
		Records.SetValue(iOrder,"CC_SendSubBurName",strSendSubBureauName);
		Records.SetValue(iOrder,"CC_SendDispName",strSendDispatchName);
		Records.SetValue(iOrder,"CC_RecBureauName",strRecBureauName);
		Records.SetValue(iOrder,"CC_RecSubBurName",strRecSubBureauName);
				

		Records.SetValue(iOrder,"CC_Stations",strStations);
		Records.SetValue(iOrder,"CC_OrgSend",strOrgSend);
		Records.SetValue(iOrder,"CC_OrgReceive",strOrgReceive);
		Records.SetValue(iOrder,"CC_Checker",strChecker);
		Records.SetValue(iOrder,"CC_CheckTime",strCheckTime);
		Records.SetValue(iOrder,"CC_CopyFor",strCopyFor);
		Records.SetValue(iOrder,"CC_Title",strTitle);
		Records.SetValue(iOrder,"CC_Content",strContent);
	}
	else if ( wCommandKind == DISPHKINDOPEN )//开通命令
	{
		//得到要更新的记录号
		iOrder = Records.GetOrderByDT("CR_DateTime",strPRTime);
		if ( iOrder == 0 )//说明是其它站进行的请求或是工作站直接下达的命令，
			//故本站无消记信息，所以新增一个记录
		{
			iOrder = Records.GetRecordNum() + 1;
			Records.SetValue(iOrder,"CR_DateTime",strPRTime);
			
		}
		//根据记录号更新其它内容
		Records.SetValue(iOrder,"OC_Order",wOrder);
		Records.SetValue(iOrder,"OC_DateTime",strCMTime);
		Records.SetValue(iOrder,"OC_Dispatcher",strDispatcher);

		Records.SetValue(iOrder,"OC_SendBureauName",strSendBureauName);
		Records.SetValue(iOrder,"OC_SendSubBurName",strSendSubBureauName);
		Records.SetValue(iOrder,"OC_SendDispName",strSendDispatchName);
		Records.SetValue(iOrder,"OC_RecBureauName",strRecBureauName);
		Records.SetValue(iOrder,"OC_RecSubBurName",strRecSubBureauName);

		Records.SetValue(iOrder,"OC_Stations",strStations);
		Records.SetValue(iOrder,"OC_OrgSend",strOrgSend);
		Records.SetValue(iOrder,"OC_OrgReceive",strOrgReceive);
		Records.SetValue(iOrder,"OC_Checker",strChecker);
		Records.SetValue(iOrder,"OC_CheckTime",strCheckTime);
		Records.SetValue(iOrder,"OC_CopyFor",strCopyFor);
		Records.SetValue(iOrder,"OC_Title",strTitle);
		Records.SetValue(iOrder,"OC_Content",strContent);
	}
	else
	{
		MessageBox("The received frame error! Variable:wCommandKind in CMainFrame","Error!",MB_ICONERROR);
		return;
	}
	//将记录集写入文件中
	Records.WriteRecords();

	//播出声音
	PlaySound(theApp.m_strExePath + "\\wav\\NewMessage.wav",NULL,SND_SYNC );
	
	//提示收到新的消息......
	NewMsgNode itemNode;
	itemNode.m_iOrder = iOrder;
	itemNode.m_strPathName = strFullPathName;
	if ( wCommandKind == DISPHKINDCLOSE )
	{
		itemNode.m_strMsgKind = "施工封锁命令";
		itemNode.m_tTime.ParseDateTime(strCMTime);
	}
	else if ( wCommandKind == DISPHKINDOPEN )
	{
		itemNode.m_strMsgKind = "施工开通命令";
		itemNode.m_tTime.ParseDateTime(strCMTime);
	}
	m_pInfPromptDlg->m_newMessage.Add(itemNode);
	m_pInfPromptDlg->ShowNewMsg();
	m_pInfPromptDlg->ShowWindow(SW_SHOW);
}

/*========================================================================
	Name:		请求站场状态函数
    ----------------------------------------------------------
	Remarks:	在站场切换时和网络恢复连接时调用.
				请求内容包括(全场帧、股道区间的全部封锁信息、车次框内容)
==========================================================================*/
BOOL CMainFrame::RequireStationStatus()
{
	BYTE pBuffer[4]={0};
	
	pBuffer[0]=LOCAL_MACHINE_CODE;
	//请求全场帧信息
	m_socketClient.WriteComm(ASKALLSTATIONINFO_FRAME_TYPE,0x01,pBuffer,1,INFINITE);

	ZeroMemory( pBuffer , 4 );
	*(WORD*)pBuffer = 0xFFFF;
	pBuffer[2] = LOCAL_MACHINE_CODE;
	pBuffer[3] = 0x01;
	//请求全部封锁信息
	m_socketClient.WriteComm(ASKLOCK_FRAME_TYPE,0x01,pBuffer, 4, INFINITE);

	//申请全站的车次框(含队列帧)内容帧
	m_socketClient.WriteComm(TRAINFRAMEREQ_FRAME_TYPE,0x01,pBuffer, 4, INFINITE);
	return TRUE;
}

/*========================================================================
	Name:		检测网络连接函数
    ----------------------------------------------------------
	Remarks:	
==========================================================================*/
void CMainFrame::SetConnection(BOOL bConnected)
{
	BOOL bAdd = FALSE;
	BYTE byLev;
	CString strCon = _T("");

	if (!m_bConnected && bConnected) //由断到连
	{
		bAdd = TRUE;
		byLev = 3;
		strCon = "网络连接成功!";
		RequireStationStatus();
	}
	else if(m_bConnected && !bConnected)//由连到断
	{
		bAdd=TRUE;
		byLev=1;
		strCon="网络通讯中断!";
	}
	m_bConnected = bConnected;
	//
	if (bAdd) 
	{
		CAlarmInfo	m_cAlarm;
		m_cAlarm.OpenFile();
		AINode sNode;
		int nNum=m_cAlarm.GetTotalNumber()+1;
		sNode.m_wOrder = nNum;
		
		sNode.m_sStation = CReadStationInf::GetInstance()->GetName(CReadStationInf::GetActiveStation());
		sNode.m_time = CTime::GetCurrentTime();
		sNode.m_sContent = strCon;
		sNode.m_byLevel = byLev;
		sNode.m_sSource = "维修终端";
		//
		m_cAlarm.Add(sNode);
		m_cAlarm.CloseFile();
		
		if (m_pWarnLogDlg != NULL) 
		{
			m_pWarnLogDlg->ShowWindow(SW_HIDE);
		}
		
		if(byLev == 1)
		{
			m_pWarnNoteDlg->RefreshAll(nNum,CTime::GetCurrentTime());
			m_pWarnNoteDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			m_pWarnNoteDlg->ShowWindow(SW_HIDE);
		}
		
	}
}



//------------------------------------------------------

//施工命令请求
void CMainFrame::OnOperatorConstructrequest() 
{
/*	m_pRequestDlg=new CConstructRequest;
	m_pRequestDlg->Create(CConstructRequest::IDD,this);
	m_pRequestDlg->ShowWindow(SW_SHOW);*/
	CConstructRequest dlg;
	dlg.DoModal();
}
void CMainFrame::OnUpdateOperatorConstructrequest(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable(m_pRequestDlg==NULL);
	
}

//----------------------------------------------------------------------
//施工命令查询
void CMainFrame::OnOperateConstructquery() 
{
/*	m_pQueryDlg = new CConstructQuery;
	m_pQueryDlg->Create(CConstructQuery::IDD,this);
	m_pQueryDlg->ShowWindow(SW_SHOW);*/
	CConstructQuery dlg;
	dlg.DoModal();
}


//------------------------------------------------------------------------
//用户管理
void CMainFrame::OnSystemUsermanage() 
{
/*	if ( m_pUserMngDlg == NULL )
	{
		m_pUserMngDlg = new CUserManageDlg;
		m_pUserMngDlg->Create(CUserManageDlg::IDD,this);
		m_pUserMngDlg->ShowWindow(SW_SHOW);
	}
*/
	CUserManageDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnUpdateSystemUsermanage(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable(m_pUserMngDlg == NULL);
}
//-------------------------------------------------------------
LRESULT CMainFrame::OnUpdateConnection(WPARAM wParam, LPARAM lParam)
{
	UINT uEvent = (UINT) wParam;
	CSocketManager* pManager = reinterpret_cast<CSocketManager*>( lParam );
	
	SockAddrIn addrin;
	pManager->GetPeerName( addrin );	
	LONG  uAddr = addrin.GetIPAddr();
	BYTE* sAddr = (BYTE*) &uAddr;
	short nPort = ntohs( addrin.GetPort() );
	CString strAddr;
	// Address is stored in network format...
	strAddr.Format(_T("IP: %u.%u.%u.%u, Port: %d"),
				(UINT)(sAddr[0]), (UINT)(sAddr[1]),
				(UINT)(sAddr[2]), (UINT)(sAddr[3]), nPort);
	CString strMsg;

	if ( pManager != NULL)
	{
		// Server socket is now connected, we need to pick a new one
		if (uEvent == EVT_CONSUCCESS)
		{
			strMsg = _T("客户端连接: ") + strAddr + CString("\r\n");
		}
		else if (uEvent == EVT_CONFAILURE || uEvent == EVT_CONDROP)
		{
			pManager->StopComm();
			strMsg = _T("失去客户端连接: ") + strAddr + CString("\r\n");
		}
	}
	Invalidate();
	return 1L;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch( pMsg->message ) 
	{
	
		//分析收到的调度命令
	case WM_ANALYSEDISPATCHFRAME:
		//
		//AnalyseDispatchFrame( (LPBYTE)(pMsg->wParam) );
		break;

		//发送调度命令机器回执
	case WM_SENDCONFIRMFRAME:
		//SendConfirmFrame(pMsg->wParam);
		break;
	
	}
	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}

//连接到自律机
BOOL CMainFrame::ConnectToALServer()
{
	m_socketClient.SetMessageWindow( this );
	m_socketClient.SetServerState( false );	// run as client
	m_socketClient.SetSmartAddressing( false );	// always send to server
	m_receiveQueue.SetMessageWindow(this);
	m_receiveQueue.WatchCheck();
	//
	m_bConnected = m_socketClient.IniConnectTo(AF_INET,SOCK_STREAM);
	//
	return m_bConnected;
}

void CMainFrame::OnViewShowwarnlog() 
{
	if (m_pWarnLogDlg == NULL) 
	{
		m_pWarnLogDlg = new CWarnLogDlg;
		m_pWarnLogDlg->Create(CWarnLogDlg::IDD,this);
	}
	m_pWarnLogDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnViewNewmessage() 
{
	m_pInfPromptDlg->ShowNewMsg();
	m_pInfPromptDlg->ShowWindow(SW_SHOW);
	
}

void CMainFrame::OnUpdateViewNewmessage(CCmdUI* pCmdUI) 
{
	if ( m_pInfPromptDlg->IsWindowVisible() )
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if ( nIDEvent == ID_CLOCK_MAINFRAME )
	{
		//Time status
		int iIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIME);
		m_wndStatusBar.SetPaneText(iIndex,CTime::GetCurrentTime().Format("%H:%M:%S"));

		//Network status
		iIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_WAN);
		SetConnection(m_socketClient.IsOpen());
		if(m_bConnected)
		{
			m_wndStatusBar.SetPaneText(iIndex,"网络状态: √");
		}
		else
		{
			m_wndStatusBar.SetPaneText(iIndex,"网络状态: ×");
		}
	}

	
	CMDIFrameWnd::OnTimer(nIDEvent);
}

