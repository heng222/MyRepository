// ddmlxdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Maintain.h"
#include "ddmlxdDlg.h"
#include "StationsEditDlg.h"
#include "ReadResponse.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////

//in .rc  old use EXSTYLE WS_EX_APPWINDOW
CDdmlxdDlg::CDdmlxdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDdmlxdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDdmlxdDlg)
	m_strContent = _T("");
	m_strStation = _T("");
	m_strCopyFor = _T("");
	m_strDestination = _T("");
	m_strChecker = _T("");
	m_strCheckTime = _T("");
	m_iDisNum = 0;
	m_tSendTime = COleDateTime::GetCurrentTime();
	m_strTitle = _T("");
	m_strDispatcher = _T("");
	m_strOrgReceive = _T("");
	m_strOrgSend = _T("");
	m_strSendDispatchID = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_wComKind = DISPHKINDCLOSE;
	m_bChecked = FALSE;
}

void CDdmlxdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDdmlxdDlg)
	DDX_Control(pDX, IDC_COMBO_DDML_SNEDDISPATCHID, m_ctrlSendDispatchID);
	DDX_Control(pDX, IDC_COMBO_DDML_RECSUBBUREAU, m_ctrlRecSubBureau);
	DDX_Control(pDX, IDC_COMBO_DDML_RECEIVEBUREAU, m_ctrlRecBureau);
	DDX_Control(pDX, IDC_COMBO_DDML_SENDSUBBUREAU, m_ctrlSendSubBureau);
	DDX_Control(pDX, IDC_COMBO_DDML_SENDBUREAU, m_ctrlSendBureau);
	DDX_Control(pDX, IDC_OPERATE_DESTINATION, m_ctrlDestination);
	DDX_Control(pDX, IDC_LIST_RESINFO, m_ctrlCFStation);
	DDX_Control(pDX, IDC_OPERATE_NAME, m_ctrlTitle);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrlSendTime);
	DDX_Control(pDX, IDC_OPERATE_CONTENT, m_ctrlEdit);
	DDX_Text(pDX, IDC_OPERATE_CONTENT, m_strContent);
	DDV_MaxChars(pDX, m_strContent, 400);
	DDX_Text(pDX, IDC_OPERATE_COPYFOR, m_strCopyFor);
	DDX_Text(pDX, IDC_OPERATE_DESTINATION, m_strDestination);
	DDX_Text(pDX, IDC_CHECKER, m_strChecker);
	DDV_MaxChars(pDX, m_strChecker, 20);
	DDX_Text(pDX, IDC_CHECKTIME, m_strCheckTime);
	DDX_Text(pDX, IDC_OPERATE_NUMBER, m_iDisNum);
	DDV_MinMaxInt(pDX, m_iDisNum, 1000, 9999);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_tSendTime);
	DDX_CBString(pDX, IDC_OPERATE_NAME, m_strTitle);
	DDX_CBString(pDX, IDC_SENDNAME, m_strDispatcher);
	DDX_Text(pDX, IDC_RECUNIT, m_strOrgReceive);
	DDX_Text(pDX, IDC_SENDUNIT, m_strOrgSend);
	DDX_CBString(pDX, IDC_COMBO_DDML_SNEDDISPATCHID, m_strSendDispatchID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDdmlxdDlg, CDialog)
	//{{AFX_MSG_MAP(CDdmlxdDlg)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_DSEND, OnDsend)
	ON_CBN_SELCHANGE(IDC_OPERATE_NAME, OnSelchangeTiltle)
	ON_BN_CLICKED(IDC_OPERATE_EXTEND, OnOperateExtend)
	ON_CBN_SELCHANGE(IDC_COMBO_DDML_RECEIVEBUREAU, OnSelchangeComboDdmlReceivebureau)
	ON_CBN_SELCHANGE(IDC_COMBO_DDML_SENDBUREAU, OnSelchangeComboDdmlSendbureau)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDdmlxdDlg message handlers

BOOL CDdmlxdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ----------------------------------------------
	m_pMainFrame = ((CMainFrame*)AfxGetMainWnd());
	
	//设置列的标题(调度命令回执信息)
	m_ctrlCFStation.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlCFStation.SetHeadings( _T("命令号,60;回执站,80;回执人,80;回执时间,200;") );
	m_ctrlCFStation.LoadColumnInfo();
	
	//设置发令时间的格式
	m_ctrlSendTime.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));

	//添加所有路局及其分局
	m_Bureau.ReadFile(theApp.m_strExePath + "ini\\路局分局代码.ini");
	CString strValue;
	for ( int i = 0; i<m_Bureau.GetBureauNumber(); i++ )
	{
		strValue = m_Bureau.GetRoadBureauName(i+1);
		m_ctrlSendBureau.AddString(strValue);
		m_ctrlRecBureau.AddString(strValue);
	}
	m_ctrlSendBureau.SetCurSel(0);
	m_ctrlRecBureau.SetCurSel(0);
	for (int i = 0; i<m_Bureau.GetSubBureauNumber(1); i++)
	{
		strValue = m_Bureau.GetSubBureauName(1,i+1);
		m_ctrlSendSubBureau.AddString(strValue);
		m_ctrlRecSubBureau.AddString(strValue);
	}
	m_ctrlSendSubBureau.SetCurSel(0);
	m_ctrlRecSubBureau.SetCurSel(0);
	//---------------------------------------------------------------
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//根据审核状态显示相应内容
//读取当天的回执信息
//更新相应控件的使用状态
void CDdmlxdDlg::ShowDetailedInf()
{
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	//
	m_strChecker.Empty();
	m_strCheckTime.Empty();
	//发令时间
	m_tSendTime = COleDateTime::GetCurrentTime();
	
	//根据 m_wComKind　显示对话框标题
	if ( m_wComKind == DISPHKINDCLOSE )
	{
		this->SetWindowText("编辑封锁调度命令");
	}
	else
	{
		this->SetWindowText("编辑开通调度命令");
	}
	//--------------------------------------------------------------------------------
	
	if ( m_bChecked == false )//当调度命令未审核时
	{
		//从配置文件中读取命令号
		CString strTmp;
		GetPrivateProfileString("ComOrder","DateTime","",strTmp.GetBuffer(15),15,theApp.m_strExePath+STATIONINFOPATHNAME);
		strTmp.ReleaseBuffer();
		if ( strTmp.CompareNoCase(CTime::GetCurrentTime().Format("%Y-%m-%d")) != 0 )
		{
			m_iDisNum = DISPHCOMINITNUM;
		}
		else
		{
			m_iDisNum = GetPrivateProfileInt("ComOrder","Order",0,theApp.m_strExePath+STATIONINFOPATHNAME)+1;
		}

		//根据m_wComKind取出调度命令模板
		if ( m_wComKind == DISPHKINDCLOSE )
		{
			m_adoSet = m_pMainFrame->m_adoLogConnect.Execute("SELECT * FROM DDMLMB WHERE D_KIND='施工封锁命令'");//
		}
		else if ( m_wComKind == DISPHKINDOPEN )
		{
			m_adoSet = m_pMainFrame->m_adoLogConnect.Execute("SELECT * FROM DDMLMB WHERE D_KIND='施工开通命令'");//
		}

		m_ctrlTitle.ResetContent();
		
		m_adoSet.MoveFirst();
		while(!m_adoSet.IsEOF())
		{
			CString mc;
			m_adoSet.GetCollect("D_NAME",mc);
			m_ctrlTitle.AddString(mc);
			//
			m_adoSet.MoveNext();
		}
		m_strTitle.Empty();
		
	}
	else//调度命令已经过审核，此时 m_iOrder　有效　
	{
		ASSERT( m_iOrder > 0 );
		CString strSQL;
		CString strTemp;
		strSQL.Format("SELECT * FROM MENDRECORD WHERE T_ORDER = %d",m_iOrder);
		//从数据库中取出记录
		m_adoSet = m_pMainFrame->m_adoLogConnect.Execute(strSQL);
		//更新面板上的所有信息控件
		if ( m_wComKind == DISPHKINDCLOSE )//封锁命令
		{
			m_adoSet.GetCollect("CC_ORDER",			strTemp);
			m_iDisNum = atoi(strTemp);

			m_adoSet.GetCollect("CC_DATETIME",		m_tSendTime);
			m_adoSet.GetCollect("CC_DISPATCHER",	m_strDispatcher);
			m_adoSet.GetCollect("CC_STATIONS",		strTemp);
			m_strDestination = pStationInf->CovNumToName(strTemp);	//转换站码列表为车站名列表
			m_adoSet.GetCollect("CC_ORGSEND",		m_strOrgSend);
			m_adoSet.GetCollect("CC_ORGRECEIVE",	m_strOrgReceive);
			m_adoSet.GetCollect("CC_CHECKER",		m_strChecker);
			m_adoSet.GetCollect("CC_CHECKTIME",		m_strCheckTime);
			m_adoSet.GetCollect("CC_COPYFOR",		m_strCopyFor);
			m_adoSet.GetCollect("CC_TITLE",			m_strTitle);
			m_adoSet.GetCollect("CC_CONTENT",		m_strContent);
		}
		else if ( m_wComKind == DISPHKINDOPEN )//开通命令
		{
			m_adoSet.GetCollect("OC_ORDER",			strTemp);
			m_iDisNum = atoi(strTemp);

			m_adoSet.GetCollect("OC_DATETIME",		m_tSendTime);
			m_adoSet.GetCollect("OC_DISPATCHER",	m_strDispatcher);
			m_adoSet.GetCollect("OC_STATIONS",		strTemp);
			m_strDestination = pStationInf->CovNumToName(strTemp);	//转换站码列表为车站名列表			m_adoSet.GetCollect("OC_ORGSEND",		m_strOrgSend);
			m_adoSet.GetCollect("OC_ORGRECEIVE",	m_strOrgReceive);
			m_adoSet.GetCollect("OC_CHECKER",		m_strChecker);
			m_adoSet.GetCollect("OC_CHECKTIME",		m_strCheckTime);
			m_adoSet.GetCollect("OC_COPYFOR",		m_strCopyFor);
			m_adoSet.GetCollect("OC_TITLE",			m_strTitle);
			m_adoSet.GetCollect("OC_CONTENT",		m_strContent);
		}

	}
	////更新
	UpdateData(false);
	ShowResponse();
	UpdateCtrlComponet();
}

//显示当天的回执信息
void CDdmlxdDlg::ShowResponse()
{
	m_ctrlCFStation.DeleteAllItems();
	//
	CReadResponse ResponseInfo;
	if (!ResponseInfo.ReadFile(theApp.m_strExePath+RESPONSEINFPATHNAME+CTime::GetCurrentTime().Format("%Y-%m-%d")))
	{
		return;
	}
	//
	CString strTemp[4];
	for (DWORD i = 0; i<ResponseInfo.GetLength(); i++ )
	{
		strTemp[0].Format("%d",ResponseInfo.GetAt(i)->dwOrder);
		strTemp[1] = ResponseInfo.GetAt(i)->strStationName;
		strTemp[2] = ResponseInfo.GetAt(i)->strReceiver;
		strTemp[3] = ResponseInfo.GetAt(i)->tTime.Format("%Y-%m-%d %H:%M:%S");
		//
		m_ctrlCFStation.AddItem(strTemp[0],strTemp[1],strTemp[2],strTemp[3]);
	}
}


//上传调度命令
void CDdmlxdDlg::OnSend() 
{
	UpdateData(TRUE);
	if ( m_strDestination.IsEmpty() )
	{
		MessageBox("受令站不能为空！","错误",MB_ICONERROR);
		return;
	}

	if ( m_strDispatcher.IsEmpty() )
	{
		MessageBox("调度员姓名不能为空！","错误",MB_ICONERROR);
		return;
	}

	if ( !m_pMainFrame->m_socketClient.IsOpen() )
	{
		MessageBox("网络连接存在问题，无法下达！","警告",MB_ICONEXCLAMATION);
		return;
	}
	
	if (m_bChecked == FALSE)
	{
		MessageBox("审核请求已发往列调中心。","提示",MB_ICONINFORMATION);

		//存时间与命令号
		StoreComOrder();

		//命令保存
		AddNewData();
		
		SendDisComFrame( DISPHCHECKSTATUSS );
	}
	else
	{
		MessageBox("此命令已经过审核，不能再一次请示审核!");
		return;
	}
}

//下达命令
void CDdmlxdDlg::OnDsend() 
{
	UpdateData(TRUE);
	if ( m_strDestination.IsEmpty() )
	{
		MessageBox("受令站不能为空！","错误",MB_ICONERROR);
		return;
	}
	if ( m_strDispatcher.IsEmpty() )
	{
		MessageBox("调度员姓名不能为空！","错误",MB_ICONERROR);
		return;
	}
	if ( !m_pMainFrame->m_socketClient.IsOpen() )
	{
		MessageBox("网络连接存在问题，无法下达！","警告",MB_ICONEXCLAMATION);
		return;
	}

	if ( m_bChecked == FALSE )//未审核	
	{
		if ( MessageBox("此调度命令尚未审核，直接下达可能出现事故，确认要直接下达吗？","警告",MB_ICONEXCLAMATION | MB_YESNO) == IDNO )
		{
			return;
		}
		else
		{
			//存时间与命令号
			StoreComOrder();
			//将命令保存
			AddNewData();
			//发送调度命令
			SendDisComFrame( DISPHCHECKSTATUSF );			
		}
	}
	else//已审核
	{
		//发送调度命令
		SendDisComFrame(DISPHCHECKSTATUST);
	}

}

//打包调度命令数据帧并发送
void CDdmlxdDlg::SendDisComFrame(int iStatus)
{
	UpdateData(TRUE);
	//---------------------------------------------------------------
	BYTE byFrame[DISPHFRAMEMAXLEN];
	WORD nFrameLen = 0;

	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	WORD wTmp;

	//------------
	//功能码(BYTE)
	byFrame[nFrameLen++] = DISPHFUNTCODE;

	//命令来源(48: 表示由维修台编写的调度命令)
	byFrame[nFrameLen++] = DISPHFROMMEND;

	//是否需要审批及审批状态
	byFrame[nFrameLen++] = (BYTE)iStatus;
	
	//发令局代码(BYTE)
	byFrame[nFrameLen++] = m_ctrlSendBureau.GetCurSel()+1;
	//发令分局代码(BYTE)
	byFrame[nFrameLen++] = m_ctrlSendSubBureau.GetCurSel() + 1;
	//发令调度台ID(WORD)
	wTmp = 1;
	memcpy(byFrame+nFrameLen,&wTmp,2);
	nFrameLen += 2;

	//受令局代码(BYTE)
	byFrame[nFrameLen++] = m_ctrlRecBureau.GetCurSel() + 1;
	//受令分局代码(BYTE)
	byFrame[nFrameLen++] = m_ctrlRecSubBureau.GetCurSel() + 1;
	
	//受令站码长度(WORD)
	wTmp = (WORD)( pStationInf->CovNameToNum(m_strDestination).GetLength() );
	memcpy(byFrame+nFrameLen,&wTmp,2);
	nFrameLen += 2;
	//受令站码字符串（以/为间隔）
	memcpy(byFrame+nFrameLen,pStationInf->CovNameToNum(m_strDestination),wTmp);
	nFrameLen += wTmp;
	
	//命令编号(4BYTE)int
	memcpy(byFrame+nFrameLen,&m_iDisNum,4);
	nFrameLen += 4;
	//命令代码(WORD)(1:封锁命令　2:开通命令)
	memcpy(byFrame+nFrameLen,&m_wComKind,2);
	nFrameLen += 2;
	//发令时间(7BYTE)
	WORD wYear = m_tSendTime.GetYear();
	memcpy(byFrame+nFrameLen,&wYear,2);
	nFrameLen += 2;
	//byFrame[nFrameLen++] = (BYTE)(m_tSendTime.GetYear()/100);
	//byFrame[nFrameLen++] = (BYTE)(m_tSendTime.GetYear()%100);
	byFrame[nFrameLen++] = (BYTE)(m_tSendTime.GetMonth());
	byFrame[nFrameLen++] = (BYTE)(m_tSendTime.GetDay());
	byFrame[nFrameLen++] = (BYTE)(m_tSendTime.GetHour());
	byFrame[nFrameLen++] = (BYTE)(m_tSendTime.GetMinute());
	byFrame[nFrameLen++] = (BYTE)(m_tSendTime.GetSecond());

	//发令机构(20BYTE)
	int i = 0;
	for ( i = 0; i<20; i++ )
	{
		if ( i<m_strOrgSend.GetLength() )
		{
			byFrame[nFrameLen++] = (BYTE)(m_strOrgSend.GetAt(i));
		}
		else
		{
			byFrame[nFrameLen++] = 0;
		}
	}

	//发令者(20BYTE)
	for ( i = 0; i<20; i++ )
	{
		if ( i<m_strDispatcher.GetLength() )
		{
			byFrame[nFrameLen++] = (BYTE)(m_strDispatcher.GetAt(i));
		}
		else
		{
			byFrame[nFrameLen++] = 0;
		}
	}

	//受令机构(20BYTE)
	for ( i = 0; i<20; i++ )
	{
		if ( i<m_strOrgReceive.GetLength() )
		{
			byFrame[nFrameLen++] = (BYTE)(m_strOrgReceive.GetAt(i));
		}
		else
		{
			byFrame[nFrameLen++] = 0;
		}
	}

	//值班主任姓名(20BYTE)
	for ( i = 0; i<20; i++ )
	{
		if ( i<m_strChecker.GetLength() )
		{
			byFrame[nFrameLen++] = (BYTE)(m_strChecker.GetAt(i));
		}
		else
		{
			byFrame[nFrameLen++] = 0;
		}
	}

	//审核时间
	COleDateTime oleTime;
	if ( m_strCheckTime.IsEmpty() )
	{
		for ( i = 0; i<7; i++ )
		{
			byFrame[nFrameLen++] = 0;
		}
	}
	else
	{

		oleTime.ParseDateTime(m_strCheckTime);
		wYear = oleTime.GetYear();
		memcpy(byFrame+nFrameLen,&wYear,2);
		nFrameLen += 2;
		//byFrame[nFrameLen++] = (BYTE)(oleTime.GetYear()/100);
		//byFrame[nFrameLen++] = (BYTE)(oleTime.GetYear()%100);
		byFrame[nFrameLen++] = (BYTE)(oleTime.GetMonth());
		byFrame[nFrameLen++] = (BYTE)(oleTime.GetDay());
		byFrame[nFrameLen++] = (BYTE)(oleTime.GetHour());
		byFrame[nFrameLen++] = (BYTE)(oleTime.GetMinute());
		byFrame[nFrameLen++] = (BYTE)(oleTime.GetSecond());
	}
	
	//登记消记时间(7 BYTE)
	wYear = m_tDateTime.GetYear();
	memcpy(byFrame+nFrameLen,&wYear,2);
	nFrameLen += 2;
	
	byFrame[nFrameLen++] = (BYTE)(m_tDateTime.GetMonth());
	byFrame[nFrameLen++] = (BYTE)(m_tDateTime.GetDay());
	byFrame[nFrameLen++] = (BYTE)(m_tDateTime.GetHour());
	byFrame[nFrameLen++] = (BYTE)(m_tDateTime.GetMinute());
	byFrame[nFrameLen++] = (BYTE)(m_tDateTime.GetSecond());

	//抄送目标长度(WORD)
	wTmp = (WORD)(m_strCopyFor.GetLength());
	memcpy(byFrame + nFrameLen, &wTmp, 2 );
	nFrameLen += 2;
	//抄送目标
	memcpy(byFrame+nFrameLen, m_strCopyFor, wTmp );
	nFrameLen += wTmp;

	//标题(40BYTE)
	for ( i = 0; i<40; i++ )
	{
		if ( i<m_strTitle.GetLength() )
		{
			byFrame[nFrameLen++] = (BYTE)(m_strTitle.GetAt(i));
		}
		else
		{
			byFrame[nFrameLen++] = 0;
		}
	}

	//命令正文长度(WORD)
	wTmp = (WORD)( m_strContent.GetLength() );
	memcpy(byFrame + nFrameLen, &wTmp, 2 );
	nFrameLen += 2;
	//命令正文
	memcpy(byFrame+nFrameLen, m_strContent, wTmp );
	nFrameLen += wTmp;

	//车次长度(WORD)
	wTmp = 0;
	memcpy(byFrame + nFrameLen, &wTmp, 2 );
	nFrameLen += 2;
	//车次ID字符串
	//机车号长度(WORD)
	memcpy(byFrame + nFrameLen, &wTmp, 2 );
	nFrameLen += 2;
	//机车号字符串
	//-------------------------------------------------------------------------------------
	
	//发送数据帧
	m_pMainFrame->m_socketClient.WriteComm(DISPHFRAMEKIND,0X01,byFrame,nFrameLen,INFINITE);
	
}

//将命令保存到数据库中
void CDdmlxdDlg::AddNewData()
{
	UpdateData(TRUE);
	//
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	CString strSQL;
	if ( m_iOrder != 0 )//已经编写了相应的登记或销记
	{
		if ( m_wComKind == 1 )
		{
			strSQL.Format("UPDATE MENDRECORD SET CC_Order = '%d', CC_DateTime = to_Date('%s','yyyy-mm-dd HH24:mi:ss'), CC_Dispatcher = '%s',CC_Stations = '%s',CC_OrgSend = '%s',CC_OrgReceive = '%s',CC_CopyFor = '%s',CC_Title = '%s',CC_Content = '%s' WHERE T_Order = %d",
				m_iDisNum,m_tSendTime.Format("%Y-%m-%d %H:%M:%S"),m_strDispatcher,pStationInf->CovNameToNum(m_strDestination),m_strOrgSend,m_strOrgReceive,m_strCopyFor,m_strTitle,m_strContent,m_iOrder);
		}
		else
		{
			strSQL.Format("UPDATE MENDRECORD SET OC_Order = '%d', OC_DateTime = to_Date('%s','yyyy-mm-dd HH24:mi:ss'), OC_Dispatcher = '%s',OC_Stations = '%s',OC_OrgSend = '%s',OC_OrgReceive = '%s',OC_CopyFor = '%s',OC_Title = '%s',OC_Content = '%s' WHERE T_Order = %d",
				m_iDisNum,m_tSendTime.Format("%Y-%m-%d %H:%M:%S"),m_strDispatcher,pStationInf->CovNameToNum(m_strDestination),m_strOrgSend,m_strOrgReceive,m_strCopyFor,m_strTitle,m_strContent,m_iOrder);
		}
	}
	else//没有编写相应的登销记
	{
		//取出数据库中已有记录数
		int iOrder = 0;
		m_adoSet = m_pMainFrame->m_adoLogConnect.Execute("SELECT MAX(T_ORDER) AS T_Order FROM MENDRECORD ");
		m_adoSet.GetCollect("T_Order",iOrder);
		iOrder++;

		//检查此命令是否已经保存过
		if ( m_wComKind == 1)
		{
			strSQL.Format("SELECT COUNT(*) FROM MENDRECORD WHERE to_Char(CC_DateTime,'yyyy-mm-dd HH24:mi:ss') = '%s'",m_tSendTime.Format("%Y-%m-%d %H:%M:%S"));
		}
		else
		{
			strSQL.Format("SELECT COUNT(*) FROM MENDRECORD WHERE to_Char(OC_DateTime,'yyyy-mm-dd HH24:mi:ss') = '%s'",m_tSendTime.Format("%Y-%m-%d %H:%M:%S"));
		}
		
		m_adoSet = m_pMainFrame->m_adoLogConnect.Execute(strSQL);
		int iCount;
		m_adoSet.GetCollect("COUNT(*)",iCount);
		if ( iCount == 0 )//此调度命令尚未保存
		{
			if ( m_wComKind == 1 )
			{
				strSQL.Format("INSERT INTO MENDRECORD(T_Order,R_DateTime,CC_Order, CC_DateTime, CC_Dispatcher,CC_Stations,CC_OrgSend,CC_OrgReceive,CC_CopyFor,CC_Title,CC_Content) VALUES(%d,to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%d',to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%s','%s','%s','%s','%s','%s','%s')",
					iOrder,m_tDateTime.Format("%Y-%m-%d %H:%M:%S"),m_iDisNum,m_tSendTime.Format("%Y-%m-%d %H:%M:%S"),m_strDispatcher,pStationInf->CovNameToNum(m_strDestination),m_strOrgSend,m_strOrgReceive,m_strCopyFor,m_strTitle,m_strContent);
			}
			else
			{
				strSQL.Format("INSERT INTO MENDRECORD(T_Order,CR_DateTime,OC_Order, OC_DateTime, OC_Dispatcher,OC_Stations,OC_OrgSend,OC_OrgReceive,OC_CopyFor,OC_Title,OC_Content) VALUES(%d,to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%d',to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%s','%s','%s','%s','%s','%s','%s')",
					iOrder,m_tDateTime.Format("%Y-%m-%d %H:%M:%S"),m_iDisNum,m_tSendTime.Format("%Y-%m-%d %H:%M:%S"),m_strDispatcher,pStationInf->CovNameToNum(m_strDestination),m_strOrgSend,m_strOrgReceive,m_strCopyFor,m_strTitle,m_strContent);
			}
		}
	}
	//Execute the SQL sentence
	m_pMainFrame->m_adoLogConnect.Execute(strSQL);
}

//将当前时间与命令号存入配置文件
void CDdmlxdDlg::StoreComOrder()
{
	//将配置文件中的时间与序号更新
	CString strTmp;
	strTmp = CTime::GetCurrentTime().Format("%Y-%m-%d");
	WritePrivateProfileString("ComOrder","DateTime",strTmp,theApp.m_strExePath+STATIONINFOPATHNAME);
	
	strTmp.Format("%d",m_iDisNum);
	WritePrivateProfileString("ComOrder","Order",strTmp,theApp.m_strExePath+STATIONINFOPATHNAME);
	
	//
	//m_iDisNum++;
	//UpdateData(FALSE);
}
/////////////////////////////////////////////////
//设置此调度命令对应　的登销记时间
void CDdmlxdDlg::SetRCDateTime(COleDateTime tDT)
{
	m_tDateTime = tDT;
}


void CDdmlxdDlg::SetRCDateTime(CTime tDT)
{
	m_tDateTime.SetDateTime(tDT.GetYear(),tDT.GetMonth(),tDT.GetDay(),
		tDT.GetHour(),tDT.GetMinute(),tDT.GetSecond());
}

//设置审核状态
void CDdmlxdDlg::SetChecked(BOOL bChecked)
{
	m_bChecked = bChecked;
}
//////////////////////////////////////////////////////


//标题变化时,重新截入施工模板
void CDdmlxdDlg::OnSelchangeTiltle() 
{
	UpdateData(TRUE);
	m_ctrlTitle.GetLBText(m_ctrlTitle.GetCurSel(),m_strTitle);
	//
	CString strSQL;
	strSQL.Format("SELECT D_CONTENT FROM DDMLMB WHERE D_NAME='%s'",m_strTitle);
	m_adoSet = m_pMainFrame->m_adoLogConnect.Execute(strSQL);//
	m_adoSet.GetCollect("D_CONTENT",m_strContent);
	//
	UpdateData(false);
}

//编辑受令车站
void CDdmlxdDlg::OnOperateExtend() 
{
	CStationsEditDlg dlg;
	if( dlg.DoModal() == IDOK)
	{
		m_strDestination = dlg.GetStations();
		m_ctrlDestination.SetWindowText(m_strDestination);
	}
}


void CDdmlxdDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialog::PostNcDestroy();
}

void CDdmlxdDlg::OnCancel() 
{
	ShowWindow(SW_HIDE);
}

//设置命令种类
void CDdmlxdDlg::SetComKind(BYTE wComKind)
{
	m_wComKind = wComKind;
}

WORD CDdmlxdDlg::GetComKind()
{
	return m_wComKind;
}

//设置要显示的命令对应的序号
void CDdmlxdDlg::SetOrder(int iOrder)
{
	m_iOrder = iOrder;
}

void CDdmlxdDlg::UpdateCtrlComponet()
{
	if ( m_bChecked )
	{
		m_ctrlTitle.EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(FALSE);
		GetDlgItem(IDC_SENDUNIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
		GetDlgItem(IDC_SENDNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_RECUNIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_OPERATE_COPYFOR)->EnableWindow(FALSE);
		GetDlgItem(IDC_OPERATE_CONTENT)->EnableWindow(FALSE);
		GetDlgItem(IDC_OPERATE_EXTEND)->EnableWindow(FALSE);
		m_ctrlSendBureau.EnableWindow(FALSE);
		m_ctrlSendSubBureau.EnableWindow(FALSE);
		m_ctrlSendDispatchID.EnableWindow(FALSE);
		m_ctrlRecBureau.EnableWindow(FALSE);
		m_ctrlRecSubBureau.EnableWindow(FALSE);
	}
	else
	{
		m_ctrlTitle.EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(TRUE);
		GetDlgItem(IDC_SENDUNIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_SEND)->EnableWindow(TRUE);
		GetDlgItem(IDC_SENDNAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_RECUNIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_OPERATE_COPYFOR)->EnableWindow(TRUE);
		GetDlgItem(IDC_OPERATE_CONTENT)->EnableWindow(TRUE);
		GetDlgItem(IDC_DSEND)->EnableWindow(TRUE);
		GetDlgItem(IDC_OPERATE_EXTEND)->EnableWindow(TRUE);
		m_ctrlSendBureau.EnableWindow(TRUE);
		m_ctrlSendSubBureau.EnableWindow(TRUE);
		m_ctrlSendDispatchID.EnableWindow(TRUE);
		m_ctrlRecBureau.EnableWindow(TRUE);
		m_ctrlRecSubBureau.EnableWindow(TRUE);
	}
}

//发令局改变时
void CDdmlxdDlg::OnSelchangeComboDdmlSendbureau() 
{
	m_ctrlSendSubBureau.ResetContent();
	// TODO: Add your control notification handler code here
	CString strSubBureauName;
	int iRoadBureauID = m_ctrlSendBureau.GetCurSel() + 1;
	for ( int i = 0; i<m_Bureau.GetSubBureauNumber(iRoadBureauID); i++ )
	{
		strSubBureauName = m_Bureau.GetSubBureauName(iRoadBureauID,i+1);
		m_ctrlSendSubBureau.AddString(strSubBureauName);
	}
	if ( m_ctrlSendSubBureau.GetCount() > 0 )
	{
		m_ctrlSendSubBureau.SetCurSel(0);
	}
}

//受令局改变时
void CDdmlxdDlg::OnSelchangeComboDdmlReceivebureau() 
{
	m_ctrlRecSubBureau.ResetContent();
	// TODO: Add your control notification handler code here
	CString strSubBureauName;
	int iRoadBureauID = m_ctrlRecBureau.GetCurSel() + 1;
	for ( int i = 0; i<m_Bureau.GetSubBureauNumber(iRoadBureauID); i++ )
	{
		strSubBureauName = m_Bureau.GetSubBureauName(iRoadBureauID,i+1);
		m_ctrlRecSubBureau.AddString(strSubBureauName);
	}

	if ( m_ctrlRecSubBureau.GetCount() > 0 )
	{
		m_ctrlRecSubBureau.SetCurSel(0);
	}
	
}


HBRUSH CDdmlxdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if ( pWnd->GetDlgCtrlID() == IDC_OPERATE_NUMBER )
	{
		pDC->SetTextColor(RGB(255,0,0));
	}
	//if ( pWnd->GetDlgCtrlID() == IDC_)
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
