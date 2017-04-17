 // MainFrm.cpp : implementation of the CMainFrame class
//
#include ".\dbado\Ado.h"
#include "stdafx.h"
#include "Maintain.h"
#include "DdmlxdDlg.h"
#include "MainFrm.h"
#include "MaintainView.h"
#include "MultStaView.h"
#include "ConstructRequest.h"
#include "ConstructQuery.h"
#include "ReadResponse.h"
#include "MaintainView.h"
#include "AlarmInfo.h"
#include "WarnLogDlg.h"
#include "WarnNoteDlg.h"
#include "InfPromptDlg.h"


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
	ON_COMMAND(ID_OPERATOR_SENDDISPACTHER, OnOperatorSenddispacther)
	ON_UPDATE_COMMAND_UI(ID_OPERATOR_SENDDISPACTHER, OnUpdateOperatorSenddispacther)
	ON_COMMAND(ID_OPERATOR_SENDOPENDISPACTHER, OnOperatorSendopendispacther)
	ON_UPDATE_COMMAND_UI(ID_OPERATOR_SENDOPENDISPACTHER, OnUpdateOperatorSendopendispacther)
	ON_UPDATE_COMMAND_UI(ID_OPERATE_CONSTRUCTQUERY, OnUpdateOperateConstructquery)
	ON_UPDATE_COMMAND_UI(ID_OPERATOR_CONSTRUCTREQUEST, OnUpdateOperatorConstructrequest)
	ON_COMMAND(ID_VIEW_SHOWWARNLOG, OnViewShowwarnlog)
	ON_COMMAND(ID_VIEW_NEWMESSAGE, OnViewNewmessage)
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_OPERATOR_SINSTASHOW, OnOperatorSinstashow)
	ON_UPDATE_COMMAND_UI(ID_OPERATOR_SINSTASHOW, OnUpdateOperatorSinstashow)
	ON_COMMAND(ID_OPERATOR_MULSTASHOW, OnOperatorMulstashow)
	ON_UPDATE_COMMAND_UI(ID_OPERATOR_MULSTASHOW, OnUpdateOperatorMulstashow)
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

	m_pDdmlxdDlg	= NULL;

	m_pWarnLogDlg	= NULL;
	m_pWarnNoteDlg	= NULL;

	m_bSingleStaShow = TRUE;
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

	//启动计时器
	SetTimer(ID_CLOCK_MAINFRAME,1000,NULL);
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX |WS_SIZEBOX|
		WS_MAXIMIZEBOX |  WS_MAXIMIZE;
	
	cs.style &= ~FWS_ADDTOTITLE;
	
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
	BYTE byFrameKind	= BufferTmp[0];		//帧类型
	BYTE byVersion		= BufferTmp[1];		//数据版本号
	WORD wStation;
	memcpy(&wStation,BufferTmp+4,2);//取出站码
	

	//将缓冲里的数据取出暂存
	WORD wLength;	//数据内容的长度
	BYTE *pFrame;	//缓冲区指针
	memcpy(&wLength,BufferTmp+2,2);

	pFrame = new BYTE[wLength];
	memcpy( pFrame,BufferTmp+4,wLength);
	//---------------------------------------------------

	//收到施工请求帧
	//条件：　帧类型为0X28
	if ( byFrameKind == CONSTFRAMEKIND )	{
		AnalyseAskFrame(pFrame);
	}

	//收到调度命令
	//条件：　帧类型为0X07
	else if( (byFrameKind == DISPHFRAMEKIND)  )	{		
		//发送机器回执
		//(先取出受令站码长度)
		WORD wReceiverLen = 0;
		memcpy(&wReceiverLen,pFrame+9,sizeof(wReceiverLen));
		wReceiverLen += 11;
		DWORD dwOrder;//命令编号
		memcpy(&dwOrder,pFrame+wReceiverLen,sizeof(dwOrder));//取出命令编号
		SendConfirmFrame(dwOrder);

		//分析收到的调度命令
		AnalyseDispatchFrame(pFrame);
	}
	
	//收到调度命令回执帧
	//条件：帧类型为0X08
	else if ( (byFrameKind == DISPHCONFIRMKIND) )	{
		AnalyseResponseFrame(pFrame);
	}
	
	else{
		//更新站场图
		theApp.m_ZCTMag.OnReceive(BufferTmp);
	}

	//--------------
	delete[] pFrame;//释放自定义的缓冲	
}

//分析从车站传送来的施工请求帧
void CMainFrame::AnalyseAskFrame(BYTE* pFrame)
{
	//----------开始分析收到的数据帧
	//指向数据帧的当前下标
	WORD nFrameIndex = 0;

	//请求站站码(WORD)
	WORD wStationNum;
	memcpy(&wStationNum,pFrame+nFrameIndex,2);
	nFrameIndex += 2;
	
	//请求类别(BYTE)(0为登记请求，1为消记请求)
	BYTE byAskKind = pFrame[nFrameIndex++];

	//施工登记日期(4 BYTES)
	DWORD dwTemp;
	memcpy(&dwTemp,pFrame+nFrameIndex,4);
	CString strRegTime = CTime(dwTemp).Format("%Y-%m-%d %H:%M:%S");
	nFrameIndex += 4;

	//消记请求日期(4 BYTES)
	memcpy(&dwTemp,pFrame+nFrameIndex,4);
	CString strCRTime; 
	if ( byAskKind == 1 )
	{
		strCRTime = CTime(dwTemp).Format("%Y-%m-%d %H:%M:%S");
	}
	nFrameIndex += 4;

	//请求人(20 BYTES)
	int i = 0;
	CString strAsker;
	for ( i=0; i<20; i++)
	{
		if(pFrame[nFrameIndex] != 0)
		{
			strAsker +=pFrame[nFrameIndex];
		}
		nFrameIndex++;
	}

	//值班员(20 BYTES)
	CString strWatcher;
	for ( i=0; i<20; i++)
	{
		if(pFrame[nFrameIndex] != 0)
		{
			strWatcher += pFrame[nFrameIndex];
		}
		nFrameIndex++;
	}

	
	//施工类别(天窗修、区间修) (BYTE)
	//1为天窗修,2为区间修
	BYTE byMendKind = pFrame[nFrameIndex++];

	//所需时间(WORD)
	WORD dConsumeTime;
	memcpy(&dConsumeTime,pFrame+nFrameIndex,2);
	nFrameIndex += 2;

	//请求内容长度
	WORD wDataLen;
	memcpy(&wDataLen,pFrame+nFrameIndex,2);
	nFrameIndex += 2;

	//请求内容
	CString strContent;
	for( i=0; i<wDataLen; i++)
	{
		strContent += pFrame[nFrameIndex++];
	}
	//数据帧分析完毕-----------------------------------


	
	//连接到数据库并根据收到的数据帧更新数据库
	CAdoRecordSet  adoLogSet;
	int iOrder = 0;
	
	CString strSQL;
	adoLogSet = m_adoLogConnect.Execute("SELECT MAX(T_ORDER) AS T_Order FROM MENDRECORD ");
	adoLogSet.GetCollect("T_Order",iOrder);
	
	//-------------------------------
	if( byAskKind == CONSTREGISTER )//登记请求
	{
		strSQL.Format("INSERT INTO MENDRECORD(T_Order,T_Station,R_DateTime,R_Asker,R_Watcher,R_ConsumeTime,R_MendKind,R_Content) VALUES(%d,%d,to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%s','%s',%d,%d,'%s')",
			iOrder+1,wStationNum,strRegTime,strAsker,strWatcher,dConsumeTime,byMendKind,strContent);
		//iOrder指向新增的记录
		iOrder++;
	}
	else if ( byAskKind == CONSTCLEARREG )//消记请求
	{
		//找到消记对应的记录号
		strSQL.Format("SELECT T_Order FROM MENDRECORD WHERE T_Station = %d AND to_Char(R_DateTime,'yyyy-mm-dd HH24:mi:ss') = '%s'",
			wStationNum,strRegTime);
		adoLogSet = m_adoLogConnect.Execute(strSQL);
		adoLogSet.GetCollect("T_Order",iOrder);
		//将消记记录更新到数据库
		strSQL.Format("UPDATE MENDRECORD SET CR_DateTime = to_Date('%s','yyyy-mm-dd HH24:mi:ss'), CR_Asker = '%s',CR_Watcher = '%s',CR_Content = '%s' WHERE T_Order = %d",
			strCRTime,strAsker,strWatcher,strContent,iOrder);
	}
	//执行SQL语句
	m_adoLogConnect.Execute(strSQL);

	//声音提示
	PlaySound(theApp.m_strExePath+"\\wav\\NewMessage.wav",NULL,SND_SYNC);

	//提示收到新的消息......
	NewMsgNode itemNode;
	itemNode.m_iOrder = iOrder;
	if ( byAskKind == CONSTREGISTER )
	{
		itemNode.m_strMsgKind = "施工登记请求";
		itemNode.m_tTime.ParseDateTime(strRegTime);
	}
	else if ( byAskKind == CONSTCLEARREG )
	{
		itemNode.m_strMsgKind = "施工消记请求";
		itemNode.m_tTime.ParseDateTime(strCRTime);
	}
	m_pInfPromptDlg->m_newMessage.Add(itemNode);
	m_pInfPromptDlg->ShowNewMsg();
	m_pInfPromptDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::AnalyseDispatchFrame(BYTE* pFrame)
{
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
	memcpy(&wYear, pFrame+wFrameIndex, 2);
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
	strPRTime = olePRTime.Format("%Y-%m-%d %H:%M:%S");

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
	//---------------------------
	
	//--------------------------------------------------------------------
	//将收到的调度命令存入数据库
	//根据收到的数据帧更新数据库
	CAdoRecordSet  adoLogSet;
	int iOrder = 0;
	//连接到数据库并将数据库的数据取出放入LISTCTRL中
	
	CString strSQL;
	//若是封锁命令,则找R_DateTime。
	//若是开通命令,则找CR_DateTime
	if ( wCommandKind == DISPHKINDCLOSE )
	{
		strSQL.Format("SELECT T_ORDER FROM MENDRECORD WHERE to_Char(R_DateTime,'yyyy-mm-dd HH24:mi:ss') = '%s'",
			strPRTime);
		//取出此调度命令相对应的记录号
		adoLogSet = m_adoLogConnect.Execute(strSQL);
		adoLogSet.GetCollect("T_Order",iOrder);
		//格式化SQL语句
		strSQL.Format("UPDATE MENDRECORD SET CC_Order = '%d', CC_DateTime = to_Date('%s','yyyy-mm-dd HH24:mi:ss'), CC_Dispatcher = '%s',CC_Stations = '%s',CC_ORGSEND = '%s',CC_OrgReceive = '%s',CC_Checker = '%s',CC_CheckTime = to_Date('%s','yyyy-mm-dd HH24:mi:ss'),CC_CopyFor = '%s',CC_Title = '%s',CC_Content = '%s' WHERE T_Order = %d",
			wOrder,strCMTime,strDispatcher,strStations,strOrgSend,strOrgReceive,strChecker,strCheckTime,strCopyFor,strTitle,strContent,iOrder);
		
	}
	else if ( wCommandKind == DISPHKINDOPEN )
	{
		strSQL.Format("SELECT T_ORDER FROM MENDRECORD WHERE to_Char(CR_DateTime,'yyyy-mm-dd HH24:mi:ss') = '%s'",
			strPRTime);
		//取出此调度命令相对应的记录号
		adoLogSet = m_adoLogConnect.Execute(strSQL);
		adoLogSet.GetCollect("T_Order",iOrder);
		//格式化SQL语句
		strSQL.Format("UPDATE MENDRECORD SET OC_Order = '%d', OC_DateTime = to_Date('%s','yyyy-mm-dd HH24:mi:ss'), OC_Dispatcher = '%s',OC_Stations = '%s',OC_ORGSEND = '%s',OC_OrgReceive = '%s',OC_Checker = '%s',OC_CheckTime = to_Date('%s','yyyy-mm-dd HH24:mi:ss'),OC_CopyFor = '%s',OC_Title = '%s',OC_Content = '%s' WHERE T_Order = %d",
			wOrder,strCMTime,strDispatcher,strStations,strOrgSend,strOrgReceive,strChecker,strCheckTime,strCopyFor,strTitle,strContent,iOrder);
		
	}
	//执行SQL语句
	m_adoLogConnect.Execute(strSQL);

	ASSERT( iOrder != 0 );

	//声音提示
	PlaySound(theApp.m_strExePath+"\\wav\\NewMessage.wav",NULL,SND_SYNC);
	
	//弹出消息提示框
	NewMsgNode itemNode;
	itemNode.m_iOrder = iOrder;
	itemNode.m_tTime.ParseDateTime(strCMTime);
	itemNode.m_tSpeTime = olePRTime;
	if ( wCommandKind == DISPHKINDCLOSE )
	{
		itemNode.m_strMsgKind = "施工封锁命令";
		
	}
	else if ( wCommandKind == DISPHKINDOPEN )
	{
		itemNode.m_strMsgKind = "施工开通命令";
	}

	m_pInfPromptDlg->m_newMessage.Add(itemNode);
	m_pInfPromptDlg->ShowNewMsg();
	m_pInfPromptDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::AnalyseResponseFrame(LPBYTE pFrame)//分析机器回执或人工回执帧
{
	BYTE byIndex = 1;
	//取出子功能码
	BYTE bySubFunCode = pFrame[byIndex++];

	//取出回执帧中的站码并将站码转换为站场名	
	WORD wStationNum;
	memcpy(&wStationNum,pFrame+byIndex,sizeof(wStationNum));
	const CReadStationInf	*pStationInf = CReadStationInf::GetInstance();
	CString strStationName = pStationInf->GetName(wStationNum);
	if ( strStationName.IsEmpty() )
	{
		strStationName = "列调";
	}
	byIndex += sizeof(wStationNum);
	
	//取出命令编号
	DWORD dwOrder;
	memcpy(&dwOrder,pFrame+byIndex,sizeof(dwOrder));
	CString strOrder;
	strOrder.Format("%d",dwOrder);
	byIndex += sizeof(dwOrder);
	
	//取出回执帧中的回执时间
	COleDateTime tConfirmTime;
	WORD wYear = tConfirmTime.GetYear();
	memcpy(&wYear,pFrame+byIndex,2);
	
	tConfirmTime.SetDateTime( wYear,
		pFrame[byIndex+2],
		pFrame[byIndex+3],
		pFrame[byIndex+4],
		pFrame[byIndex+5],
		pFrame[byIndex+6]);
	CString strConfirmTime = tConfirmTime.Format("%Y-%m-%d %H:%M:%S");
	byIndex += 7;

	//当为人工回执时，取出受令者和受令结果
	CString strReciver;
	BYTE	byResult;
	if ( bySubFunCode == DISPHCONFIRMHUMAN )
	{
		//取出受令者长度
		WORD wLength;
		memcpy(&wLength,pFrame+byIndex,2);
		byIndex += 2;

		//取出受令者
		memcpy(strReciver.GetBuffer(wLength),pFrame+byIndex,wLength);
		strReciver.ReleaseBuffer();
		byIndex += wLength;

		//取出受令结果
		byResult = pFrame[byIndex++];
		
		//人工回执时声音提示
		PlaySound(theApp.m_strExePath+"\\wav\\Response.wav",NULL,SND_SYNC);
	}
	else
	{
		strReciver = "机器";
	}
	//-------------------------

	
	
	//将回执信息存储至相应的文件中
	CReadResponse ResInfo;
	ResInfo.ReadFile(theApp.m_strExePath+RESPONSEINFPATHNAME+tConfirmTime.Format("%Y-%m-%d"));
	ResInfo.Add(dwOrder,strStationName,tConfirmTime,strReciver);
	ResInfo.WriteFile();
	
	//将命令编号，站场名字,确认时间填入LIST表中
	m_pDdmlxdDlg->ShowResponse();
	if ( m_pDdmlxdDlg->m_iDisNum == dwOrder && m_pDdmlxdDlg->IsWindowVisible() )
	{
		if ( strStationName == "列调")
		{
			m_pDdmlxdDlg->GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
		}
		else
		{
			m_pDdmlxdDlg->GetDlgItem(IDC_DSEND)->EnableWindow(FALSE);
		}
		
	}

/*	//弹出消息提示框
	NewMsgNode itemNode;
	itemNode.m_iOrder = iOrder;
	itemNode.m_tTime.ParseDateTime(strConfirmTime);
	if ( byAskKind == DISPHCONFIRMHUMAN )
	{
		itemNode.m_strMsgKind = "人工回执";
		
	}
	else if ( byAskKind == DISPHKINDOPEN )
	{
		itemNode.m_strMsgKind = "机器回执";
	}
	m_pInfPromptDlg->ShowNewMsg();
	m_pInfPromptDlg->ShowWindow(SW_SHOW);
*/
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
	
	pBuffer[0] = LOCAL_MACHINE_CODE;
	WORD wStationNo = 0xFFFF;
	memcpy(pBuffer+1,&wStationNo,2);
	
	//请求全场帧信息
	m_socketClient.WriteComm(ACKALLSTATIONINFO_FRAME_TYPE,0x01,pBuffer,3,INFINITE);

	ZeroMemory( pBuffer , 4 );	
	//*(WORD*)pBuffer = 0xFFFF;
	*(WORD*)pBuffer = CReadStationInf::GetActiveStation();
	pBuffer[2] = LOCAL_MACHINE_CODE;
	pBuffer[3] = 0x01;
	
	//请求全部封锁信息
	m_socketClient.WriteComm(ACKLOCK_FRAME_TYPE,0x01,pBuffer, 4, INFINITE);

	//申请全部站的车次框(含队列帧)内容帧
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

		theApp.m_ZCTMag.InvalidateInf(FALSE);

		//
		bAdd = TRUE;
		byLev = 3;
		strCon = "网络连接成功!";
		
		//请求全场帧信息
		RequireStationStatus();

		//重连到数据库服务器
		ConnectToDBServer();
	}
	else if(m_bConnected && !bConnected)//由连到断
	{
		//
		theApp.m_ZCTMag.InvalidateInf(TRUE);

		bAdd=TRUE;
		byLev=1;
		strCon="网络通讯中断!";

		//隐藏相应的对话框
//		m_pRequestDlg->ShowWindow(SW_HIDE);
		m_pDdmlxdDlg->ShowWindow(SW_HIDE);
		
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
		
		sNode.m_sStation = "综合维修工作站";
		sNode.m_time = CTime::GetCurrentTime();
		sNode.m_sContent = strCon;
		sNode.m_byLevel = byLev;
		sNode.m_sSource = "综合维修工作站";
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

//直接下达封锁命令
void CMainFrame::OnOperatorSenddispacther() 
{
	if ( m_pDdmlxdDlg->GetComKind() == DISPHKINDCLOSE )
	{
		//m_pDdmlxdDlg->SetComKind(DISPHKINDCLOSE);
	}
	else
	{
		m_pDdmlxdDlg->SetComKind(DISPHKINDCLOSE);	
	}
	m_pDdmlxdDlg->SetOrder(0);
	m_pDdmlxdDlg->SetChecked(FALSE);
	m_pDdmlxdDlg->SetRCDateTime(CTime::GetCurrentTime());
	
	m_pDdmlxdDlg->ShowDetailedInf();
	m_pDdmlxdDlg->ShowResponse();

	m_pDdmlxdDlg->ShowWindow(SW_SHOW);
}
void CMainFrame::OnUpdateOperatorSenddispacther(CCmdUI* pCmdUI) 
{
	if ( m_socketClient.IsOpen() )
	{
		
		if ( m_pDdmlxdDlg->IsWindowVisible() == TRUE )
		{
			pCmdUI->Enable( m_pDdmlxdDlg->GetComKind() != DISPHKINDCLOSE );	
		}
		else
		{
			pCmdUI->Enable(TRUE);
		}
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
	
}
//-----------------------------------------------------------------------


//直接下达开通命令
void CMainFrame::OnOperatorSendopendispacther() 
{
	if ( m_pDdmlxdDlg->GetComKind() == DISPHKINDOPEN )
	{
		//m_pDdmlxdDlg->SetComKind(DISPHKINDOPEN);
	}
	else
	{
		m_pDdmlxdDlg->SetComKind(DISPHKINDOPEN);	
	}
	m_pDdmlxdDlg->ShowWindow(SW_SHOW);

	m_pDdmlxdDlg->SetOrder(0);
	m_pDdmlxdDlg->SetChecked(FALSE);
	m_pDdmlxdDlg->SetRCDateTime(CTime::GetCurrentTime());
	
	m_pDdmlxdDlg->ShowDetailedInf();
	m_pDdmlxdDlg->ShowResponse();

}

void CMainFrame::OnUpdateOperatorSendopendispacther(CCmdUI* pCmdUI) 
{
	if ( m_bConnected )
	{
		if ( m_pDdmlxdDlg->IsWindowVisible() == TRUE )
		{
			pCmdUI->Enable( m_pDdmlxdDlg->GetComKind() != DISPHKINDOPEN );	
		}
		else
		{
			pCmdUI->Enable(TRUE);
		}
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}
//--------------------------------------------------------------------
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

//施工命令查询
void CMainFrame::OnOperateConstructquery() 
{
	CConstructQuery dlg;
	dlg.DoModal();
}
void CMainFrame::OnUpdateOperateConstructquery(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable( !m_pQueryDlg->IsWindowVisible() && m_bConnected );
	//pCmdUI->Enable( m_bConnected );
	
}
//----------------------------------------------------------------------
//施工命令请求
void CMainFrame::OnOperatorConstructrequest() 
{
	//m_pRequestDlg->UpdateListCtrl();
	//m_pRequestDlg->UpdateOrderEdit();
/*	m_pRequestDlg->m_byConKind = 0;
	m_pRequestDlg->m_byOrder = 0;
	m_pRequestDlg->ShowWindow(SW_SHOW);
	m_pRequestDlg->DisplayRecord();*/
	CConstructRequest dlg;
	dlg.m_byConKind = 0;
	dlg.m_byOrder = 0;
	dlg.DoModal();
	//dlg.DisplayRecord();
}
void CMainFrame::OnUpdateOperatorConstructrequest(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable( !m_pRequestDlg->IsWindowVisible()  && m_bConnected );
	//pCmdUI->Enable( m_bConnected );
}

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
	if (m_bConnected) {	
		theApp.m_ZCTMag.InvalidateInf(FALSE);
	}
		
	return m_bConnected;
}

void CMainFrame::OnViewShowwarnlog() 
{
/*	if (m_pWarnLogDlg == NULL) 
	{
		m_pWarnLogDlg = new CWarnLogDlg;
		m_pWarnLogDlg->Create(CWarnLogDlg::IDD,this);
	}
*/
	m_pWarnLogDlg->ShowWindow(SW_SHOW);	
}

void CMainFrame::CreateSpeDialog()
{
	//施工请求
//	m_pRequestDlg = new CConstructRequest;
//	m_pRequestDlg->Create(CConstructRequest::IDD,this);
	
	//施工查询
//	m_pQueryDlg	= new CConstructQuery;
//	m_pQueryDlg->Create(CConstructQuery::IDD,this);
	
	//调度命令下达
	m_pDdmlxdDlg = new CDdmlxdDlg;
	m_pDdmlxdDlg->Create(CDdmlxdDlg::IDD,this);
				
	//报警日志
	m_pWarnLogDlg = new CWarnLogDlg;
	m_pWarnLogDlg->Create(CWarnLogDlg::IDD,this);

	//当前报警
	m_pWarnNoteDlg = new CWarnNoteDlg;
	m_pWarnNoteDlg->Create(CWarnNoteDlg::IDD,this);
				
	//新消息提示框
	m_pInfPromptDlg = new CInfPromptDlg;
	m_pInfPromptDlg->Create(CInfPromptDlg::IDD,this);
}

//查看新消息
void CMainFrame::OnViewNewmessage() 
{
	m_pInfPromptDlg->ShowNewMsg();
	m_pInfPromptDlg->ShowWindow(SW_SHOW);
}

BOOL CMainFrame::ConnectToDBServer()
{
	//连接到数据库并删除一个月前的所有记录
	if ( !m_adoLogConnect.ConnectOracle(theApp.m_strDBDataSource,theApp.m_strDBUserID,theApp.m_strDBPassword))
	{		
		return FALSE;
	}
	else
	{
		CString strSQL;
		//删除一个月前的记录
		strSQL.Format("DELETE FROM MENDRECORD WHERE R_DATETIME < ADD_MONTHS(ROUND(SYSDATE,'dd'),-1) OR CR_DATETIME < ADD_MONTHS( ROUND(SYSDATE,'dd'),-1)" );
		m_adoLogConnect.Execute(strSQL);
		
		
		//创建序列
		strSQL.Format("CREATE SEQUENCE MR_sOrder MAXVALUE 99999");
		m_adoLogConnect.Execute(strSQL);
		
		//更新剩余记录的序号
		strSQL.Format("UPDATE MENDRECORD SET T_Order = MR_sOrder.NEXTVAL");
		m_adoLogConnect.Execute(strSQL);
		
		//删除序列
		strSQL.Format("DROP SEQUENCE MR_sOrder");
		m_adoLogConnect.Execute(strSQL);

		return TRUE;
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


void CMainFrame::SendConfirmFrame(DWORD dwOrder)
{
	BYTE	byFrame[DISPHCONFIRMMAXLEN];
	WORD	nFrameSend = 0;	//回执帧下标


	//功能码(有关维修的调度命令)(BYTE)
	byFrame[nFrameSend++] = DISPHFUNTCODE;

	//子功能码(机器回执)(BYTE)
	byFrame[nFrameSend++] = DISPHCONFIRMMACHINE; 
	
	
	//受令站码
	WORD wStationNum = 0;//站码为0表示由维修工作站回执，不是车站回执
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

BOOL CMainFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	//SetCursor(LoadCursorFromFile(theApp.m_strExePath+"\\res\\Starcraft arrow.cur"));
	//return TRUE;
	return CMDIFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CMainFrame::OnOperatorSinstashow() 
{
	m_bSingleStaShow = TRUE;
	// TODO: Add your command handler code here
	SwitchToView(theApp.m_pSingleStaDocTemplate,RUNTIME_CLASS(CMaintainView));
}

void CMainFrame::OnUpdateOperatorSinstashow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_bSingleStaShow);
}

void CMainFrame::OnOperatorMulstashow() 
{
	// TODO: Add your command handler code here
	m_bSingleStaShow = FALSE;
	SwitchToView(theApp.m_pMultiStatDocTemplate,RUNTIME_CLASS(CMultStaView));
	
}

void CMainFrame::OnUpdateOperatorMulstashow(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bSingleStaShow);
}

void CMainFrame::SwitchToView(CDocTemplate* pTemplate,CRuntimeClass *pViewClass)
{

	//获得当前激活的子窗口
	CMDIChildWnd* pMDIActive = MDIGetActive();
	//pTemplate->
	ASSERT( pMDIActive );
	CDocument* pDoc = pMDIActive->GetActiveDocument();
	ASSERT( pDoc );

	//遍历文档的视图列表，判断pViewClass指向的视图是否存在，若存在则
	//激活它，否则用当前文件模板创建并激活它
	CView* pView;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos)
	{
		pView = pDoc->GetNextView(pos);
		if( pView->IsKindOf(pViewClass))
		{
			pView->GetParentFrame()->ActivateFrame();
			return;
		}
	}

	//
	CMDIChildWnd* pNewFrame = (CMDIChildWnd*)(pTemplate->CreateNewFrame(pDoc,NULL));
	//pTemplate->CreateNewDocument();
	if( !pNewFrame )
	{
		return;
	}
	ASSERT_KINDOF(CMDIChildWnd,pNewFrame);
	pTemplate->InitialUpdateFrame(pNewFrame,pDoc);	
}


