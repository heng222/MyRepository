          // ConstructRequest.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "ConstructRequest.h"
#include "MainFrm.h"
#include "DdmlxdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CConstructRequest dialog


CConstructRequest::CConstructRequest(CWnd* pParent /*=NULL*/)
	: CDialog(CConstructRequest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstructRequest)
	m_strEdit1 = _T("第");
	m_strEdit3 = _T("号请求");
	m_iKind = 0;
	m_strContent = _T("");
	m_strEdit2 = _T("施 工  请 求 内 容");
	m_strAsker = _T("");
	m_strWatcher = _T("");
	m_strOrder = _T("");
	m_strMendKind = _T("");
	m_strStation = _T("");
	m_timeDateTime = CTime::GetCurrentTime();
	m_iConsumeTime = 50;
	//}}AFX_DATA_INIT
	m_bSaved = FALSE;
	m_MendTemplate.ReadFile(theApp.m_strExePath + MENDTEMPLATEPATHNAME);
}


void CConstructRequest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstructRequest)
	DDX_Control(pDX, IDC_STATION, m_ctrlStation);
	DDX_Control(pDX, IDC_MENDKIND, m_ctrlMendKind);
	DDX_Control(pDX, IDC_ORDER, m_ctrlOrder);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrlDateTime);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit1);
	DDX_Text(pDX, IDC_EDIT3, m_strEdit3);
	DDX_Radio(pDX, IDC_REGISTER, m_iKind);
	DDX_Text(pDX, IDC_CONTENT, m_strContent);
	DDX_Text(pDX, IDC_EDIT2, m_strEdit2);
	DDX_Text(pDX, IDC_ASKER, m_strAsker);
	DDX_Text(pDX, IDC_WATCHER, m_strWatcher);
	DDX_Text(pDX, IDC_ORDER, m_strOrder);
	DDX_CBString(pDX, IDC_MENDKIND, m_strMendKind);
	DDX_Text(pDX, IDC_STATION, m_strStation);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timeDateTime);
	DDX_Text(pDX, IDC_CONSUMETIME, m_iConsumeTime);
	DDV_MinMaxInt(pDX, m_iConsumeTime, 0, 9999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstructRequest, CDialog)
	//{{AFX_MSG_MAP(CConstructRequest)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_CLICKED(IDC_REGISTER, OnRadioRegister)
	ON_BN_CLICKED(IDC_NEWREGISTER, OnNewregister)
	ON_BN_CLICKED(IDC_DELETE, OnBDelete)
	ON_BN_CLICKED(IDC_REQUEST, OnBRequestCommand)
	ON_CBN_SELCHANGE(IDC_MENDKIND, OnSelchangeMendkind)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_CLOSEREG, OnRadioRegister)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConstructRequest message handlers

BOOL CConstructRequest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//连接到数据库
	if ( !m_adoLogConnect.ConnectOracle(theApp.m_strDBDataSource,theApp.m_strDBUserID,theApp.m_strDBPassword))
	{		
		MessageBox("程序无法连接到数据库服务器！无法执行此操作!","致命错误",MB_ICONERROR);
		OnCancel();
		return FALSE;
	}
	//--------------------------------------------------------
	m_pMainFrame = ((CMainFrame*)AfxGetMainWnd());
	
	//
	SetWindowText(CTime::GetCurrentTime().Format("%Y年%m月%d日的施工记录"));
	
	//设置日期格式
	m_ctrlDateTime.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));

	//设置施工类别
	((CComboBox*)GetDlgItem(IDC_MENDKIND))->SetCurSel(0);

	//加入站场名字
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	int iLength = pStationInf->GetLength();
	for ( int i = 0; i< iLength; i++ )
	{
		CString strName = pStationInf->GetAt(i)->strName;
		((CComboBox*)GetDlgItem(IDC_STATION))->AddString(strName);
	}
	int iOrder = pStationInf->GetItem(pStationInf->GetActiveStation())->iIndex;
	((CComboBox*)GetDlgItem(IDC_STATION))->SetCurSel(iOrder);
	
	//设置列的标题
	m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlList.SetHeadings( _T("序号,60;请求站,80;登记时间,150;施工请求人,100;登记值班员,100;施工所需时间(分),120;施工种类,80;登记内容,300;消记时间,150; 消记请求人,100; 消记值班员,100; 消记内容,300;") );
	m_ctrlList.LoadColumnInfo();

	//
	//
	
	//
	DisplayRecord();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//========================================================================
//=========================================================================
//更新LISTCTRL控件
void CConstructRequest::UpdateListCtrl()
{
	m_adoLogSet = m_adoLogConnect.Execute
		("SELECT * FROM MENDRECORD  WHERE to_char(R_DateTime,'YYYY-MM-DD') = to_char(SYSDATE,'YYYY-MM-DD') OR to_char(CR_DateTime,'YYYY-MM-DD') = to_char(SYSDATE,'YYYY-MM-DD') ORDER BY T_Order ");

	m_ctrlList.DeleteAllItems();
	//
	m_adoLogSet.MoveFirst();
	//
	CString strGroup[30];
	//COleDateTime R_DateTime;
	
	//从记录集中取出记录并加入到LISTCTRL中
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	while(!m_adoLogSet.IsEOF())
	{
		int i = 0,iTemp;

		m_adoLogSet.GetCollect("T_ORDER",iTemp);
		strGroup[i++].Format("%d",iTemp);

		m_adoLogSet.GetCollect("T_STATION",iTemp);
		strGroup[i++].Format("%s",pStationInf->GetName(iTemp));
		

		m_adoLogSet.GetCollect( "R_DATETIME", strGroup[i++] );
		m_adoLogSet.GetCollect("R_ASKER",strGroup[i++]);
		m_adoLogSet.GetCollect("R_WATCHER" ,strGroup[i++]);
		m_adoLogSet.GetCollect("R_ConsumeTime" ,iTemp);
		strGroup[i++].Format("%d",iTemp);
		
		m_adoLogSet.GetCollect("R_MendKind" ,iTemp);
		strGroup[i++].Format("%s",m_MendTemplate.GetName(iTemp));

		m_adoLogSet.GetCollect("R_CONTENT",strGroup[i++]);
		
		
		//m_adoLogSet.GetCollect("CC_ORDER",strGroup[i++]);
		//m_adoLogSet.GetCollect("CC_DATETIME",strGroup[i++]);
		//m_adoLogSet.GetCollect("CC_DISPATCHER" ,strGroup[i++]);
		//m_adoLogSet.GetCollect("CC_STATIONS" ,strGroup[i++]);
		//m_adoLogSet.GetCollect("CC_CONTENT"  ,strGroup[i++]);
		
		
		m_adoLogSet.GetCollect("CR_DATETIME" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CR_ASKER" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CR_WATCHER" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CR_CONTENT",strGroup[i++]);
		
		
		//m_adoLogSet.GetCollect("OC_ORDER" ,strGroup[i++]);
		//m_adoLogSet.GetCollect("OC_DATETIME" ,strGroup[i++]);
		//m_adoLogSet.GetCollect( "OC_DISPATCHER", strGroup[i++] );
		//m_adoLogSet.GetCollect( "OC_CONTENT", strGroup[i++] );
		
		//添加记录
		m_ctrlList.AddItem(strGroup[0],
			strGroup[1],	strGroup[2],	strGroup[3],	strGroup[4],	strGroup[5],	strGroup[6],	strGroup[7],
			strGroup[8],	strGroup[9],	strGroup[10],	strGroup[11]);
			//,	strGroup[12],
			//strGroup[13],	strGroup[14],	strGroup[15],	strGroup[16],
			//strGroup[17],	strGroup[18],	strGroup[19],	strGroup[20]);
		//
		m_adoLogSet.MoveNext();
	}
}
//更新IDC_ORDER,使IDC_ORDER中显示最大记录数加1。
void CConstructRequest::UpdateOrderEdit()
{
	CString strSQL;
	strSQL.Format("SELECT MAX(T_Order) AS T_Order FROM MENDRECORD");
	m_adoLogSet = m_adoLogConnect.Execute(strSQL);
	//
	int T_Order;
	m_adoLogSet.GetCollect("T_ORDER",T_Order);
	m_strOrder.Format("%d",T_Order + 1);
	m_ctrlOrder.SetWindowText(m_strOrder);
	//m_ctrlOrder.EnableWindow(true);
}

//==========================================================================
//==========================================================================

//单击LISTCTRL时，根据RADIO的状态更新IDC_ORDER
void CConstructRequest::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//得到单击行的序号
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	UpdateData();
	if(nItem != -1 && m_iKind == 1)
	{
		
		//使IDC_STATION显示单击行的站场名字
		//m_strStation = m_ctrlList.GetItemText(nItem,1);
		//m_ctrlStation.SetCurSel(pStationInf->GetOrder(m_strStation) - 1);
		//if(m_iKind == 0)//登记
		//{
			//UpdateOrderEdit();
		//}
		//else if(m_iKind == 1 )//消记
		//{
			m_strOrder = m_ctrlList.GetItemText(nItem,0);
		//}
		UpdateData(false);
	}

	//=====================
	*pResult = 0;
}

//单击RADIO控件
void CConstructRequest::OnRadioRegister() 
{
	m_bSaved = FALSE;
	UpdateData();
	GetDlgItem(IDC_NEWREGISTER)->EnableWindow(true);
	//GetDlgItem(IDC_REQUEST)->EnableWindow(FALSE);
	//
	m_timeDateTime = CTime::GetCurrentTime();
	if(m_iKind == 0)
	{
		m_strEdit1 = "第";
		//m_strEdit2 = "施 工 登 记 请 求 内 容";
		m_strContent = m_MendTemplate.GetContent(m_ctrlMendKind.GetCurSel()+1,true);
//		GetDlgItem(IDC_NEWREGISTER)->SetWindowText("(&N)新增登记");
		
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(true);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(true);

		//更新IDC_ORDER控件
		UpdateOrderEdit();
	}
	else
	{
		//更新STATION和ORDER
		POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
		int nItem=m_ctrlList.GetNextSelectedItem(lpos);
		if(nItem != -1)
		{
			//Station
			//m_strStation = m_ctrlList.GetItemText(nItem,1);
			
			//Order
			m_strOrder = m_ctrlList.GetItemText(nItem,0);
		}
		else
		{
			MessageBox("请先在列表框中选择要消记的记录。再进行消记请求！","提示",MB_ICONINFORMATION);
			m_iKind = 0;
			UpdateData(false);
			return;
		}

		m_strEdit1 = "消记第";
		//m_strEdit2 = "施 工 消 记 请 求 内 容";
		m_strContent = m_MendTemplate.GetContent(1,false);
//		GetDlgItem(IDC_NEWREGISTER)->SetWindowText("(&N)新增消记");

		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(false);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(false);
	}
	//
	UpdateData(false);
}
//当MENDKIND变化时
void CConstructRequest::OnSelchangeMendkind() 
{
	UpdateData();
	m_strContent = m_MendTemplate.GetContent(m_strMendKind,!m_iKind);
	UpdateData(false);	
}
//新增记录
void CConstructRequest::OnNewregister() 
{
	GetDlgItem(IDC_REQUEST)->EnableWindow(true);
	GetDlgItem(IDC_NEWREGISTER)->EnableWindow(false);
	//
	if ( !AddNewData() )
	{
		MessageBox("操作不成功!","提示",MB_ICONINFORMATION);
	}
}
BOOL CConstructRequest::AddNewData()
{
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	//若前前记录已经保存
	if ( m_bSaved )
	{
		return TRUE;
	}
	else
	{
		m_bSaved = TRUE;
	}

	UpdateData();
	if ( m_strAsker.IsEmpty() || m_strWatcher.IsEmpty() || m_iConsumeTime == 0)
	{
		MessageBox("请求人，值班员或所需时间中有一项为空，保存失败！","",MB_ICONINFORMATION);
		return FALSE;
	}
	//-------------------------
	CString strSQL;
	//将请求时间转化为字符串型
	CString strDateTime;
	strDateTime = m_timeDateTime.Format("%Y-%m-%d %H:%M:%S");
	
	if(m_iKind==0)//新增登记
	{
		//得到相应车站的站码
		int iStation = pStationInf->GetStationID(m_strStation);
		//得到施工种类的序号
		int iMendKind = ((CComboBox*)GetDlgItem(IDC_MENDKIND))->GetCurSel() + 1;

		strSQL.Format("INSERT INTO MENDRECORD(T_Order,T_Station,R_DateTime,R_Asker,R_Watcher,R_ConsumeTime,R_MendKind,R_Content) VALUES(%s,%d,to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%s','%s',%d,%d,'%s')",
			m_strOrder,iStation,strDateTime,m_strAsker,m_strWatcher,m_iConsumeTime,iMendKind,m_strContent);
	}
	else//更新消记
	{
		//得到最大记录号
		m_adoLogSet = m_adoLogConnect.Execute("SELECT MAX(T_Order) AS T_Order FROM MENDRECORD");
		int T_Order;
		m_adoLogSet.GetCollect("T_ORDER",T_Order);
		//当要消记的记录有效时
		if ( atoi(m_strOrder) > T_Order || atoi(m_strOrder) <= 0 )
		{
			CString strInf;
			strInf.Format("不存在记录号为%d的施工，无法进行消记！\n提示：先在列表框中选择要消记的施工。",atoi(m_strOrder));
		
			MessageBox(strInf,"提示",MB_ICONEXCLAMATION);
			return FALSE;
		}
		//
		strSQL.Format("UPDATE MENDRECORD SET CR_DateTime = to_Date('%s','yyyy-mm-dd HH24:mi:ss'), CR_Asker = '%s',CR_Watcher = '%s',CR_Content = '%s' WHERE T_Order = %s",
			strDateTime,m_strAsker,m_strWatcher,m_strContent,m_strOrder);	
	}
	//执行SQL语句
	m_adoLogConnect.Execute(strSQL);
	//刷新记录集
	//m_adoLogSet = m_adoLogConnect.Execute("SELECT * FROM MENDRECORD ORDER BY T_Order");
	UpdateListCtrl();
	//----------------------------------------------------------------------------------
	if( m_iKind == 0)//若是新增登记，则更新IDC_ORDER控件。
	{
		//更新IDC_ORDER控件
		//UpdateOrderEdit();
	}
	return TRUE;
}

//单击删除按钮
void CConstructRequest::OnBDelete() 
{
	UpdateData(TRUE);
	//-----------------------------------------------------
	//得到LISTCTRL被选择的行号（Based Zero）
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	
	if ( nItem == -1)
	{
		MessageBox("请先在列表框中选择要删除行!","提示",MB_OK | MB_ICONINFORMATION);
		return;
	}
	if( MessageBox("确定要删除选中的记录吗？不可恢复！","警告",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDNO)
	{
		return;
	}
	
	//得到未删除前的最大序号
	m_adoLogSet = m_adoLogConnect.Execute("SELECT MAX(T_Order) AS T_Order FROM MENDRECORD");
	int maxOrder;
	m_adoLogSet.GetCollect("T_ORDER",maxOrder);

	//得到要删除的记录序号并删除指定的记录
	CString strSQL;
	CString strCurOrder = m_ctrlList.GetItemText(nItem,0);
	strSQL.Format("DELETE FROM MendRecord WHERE T_Order = %s", strCurOrder);
	m_adoLogConnect.Execute( strSQL );

	//当删除的记录不是最大记录序号时,
	//将序号最大的记录号设置为已删除的记录的序号
	if ( maxOrder != atoi(strCurOrder) )
	{
		strSQL.Format("UPDATE MENDRECORD SET T_Order = %s WHERE T_Order = %d",strCurOrder,maxOrder);
		m_adoLogConnect.Execute(strSQL);
	}
	
	//清空所有显示控件，然后更新LISTCTRL
	//InitRecContent();
	//m_adoLogSet = m_adoLogConnect.Execute("SELECT * FROM MENDRECORD ORDER BY T_Order");
	UpdateListCtrl();
	//更新序号控件
	if ( m_iKind == 0 )
	{
		UpdateOrderEdit();
	}
	else
	{
		m_strOrder = "0";
		UpdateData(FALSE);
	}
}
//清空请求人和值班员控件的内容
void CConstructRequest::InitRecContent()
{
	//m_oleDateTime.SetStatus(COleDateTime::null);

	GetDlgItem(IDC_ASKER)->SetWindowText("");
	GetDlgItem(IDC_STATION)->SetWindowText("");
	GetDlgItem(IDC_MENDKIND)->SetWindowText("");
	GetDlgItem(IDC_CONSUMETIME)->SetWindowText("");
	GetDlgItem(IDC_WATCHER)->SetWindowText("");
	GetDlgItem(IDC_CONTENT)->SetWindowText("");
}

//-------------------------------------------------------------------------
//==========================================================================
//编辑调度命令
void CConstructRequest::OnBRequestCommand() 
{
	UpdateData();
	
	if ( !AddNewData() )
	{
		return;
	}
	//参数1：对应的序号
	//参数2：施工种类(对应开通命令或封锁命令)
	WORD wComKind;
	if ( m_iKind == 0 )//m_iKind == 0　说明要编辑封锁命令
	{
		wComKind = DISPHKINDCLOSE;
	}
	else//编辑开通命令
	{
		wComKind = DISPHKINDOPEN;
	}

	//this->ShowWindow(SW_HIDE);
	OnOK();

	//---------------------------------------------
	ASSERT( atoi(m_strOrder) != 0 );


	//设置调度命令对话框参数并弹出对话框
	m_pMainFrame->m_pDdmlxdDlg->SetOrder(atoi(m_strOrder));	//记录号
	m_pMainFrame->m_pDdmlxdDlg->SetComKind(wComKind);//命令种类
	m_pMainFrame->m_pDdmlxdDlg->SetRCDateTime(m_timeDateTime);//相对应施工请求的登销记时间
	m_pMainFrame->m_pDdmlxdDlg->SetChecked(FALSE);//未审核
	m_pMainFrame->m_pDdmlxdDlg->ShowDetailedInf();
//	m_pMainFrame->m_pDdmlxdDlg->ShowResponse();

	m_pMainFrame->m_pDdmlxdDlg->ShowWindow(SW_SHOW);
	//----------------------------------------------
	
}


//双击LISTCTRL
void CConstructRequest::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_byConKind != 0 || m_byOrder != 0 )
		//当查看由维修终端发来的请求时，不做任何操作
	{
		return;
	}
	
	//UpdateData(TRUE);
	GetDlgItem(IDC_NEWREGISTER)->EnableWindow(false);
	//得到LISTCTRL的双击行
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	if ( nItem == -1)
	{
		return;
	}
	//得到选择记录的序号
	CString strOrder = m_ctrlList.GetItemText(nItem,0);
	CString strSQL;
	//从数据库中找出序号为指定值的一组记录
	strSQL.Format("SELECT * FROM MENDRECORD WHERE T_ORDER = %s",strOrder);
	m_adoLogSet = m_adoLogConnect.Execute(strSQL);

	m_strOrder = strOrder;
	int iStation;
	m_adoLogSet.GetCollect("T_Station",iStation);
	m_ctrlStation.SetCurSel(iStation-1);

	if(m_iKind == 0)
	{
		COleDateTime oleTime;
		m_adoLogSet.GetCollect("R_DateTime",oleTime);
		m_ctrlDateTime.SetTime(oleTime);
		m_ctrlDateTime.GetTime(m_timeDateTime);

		m_adoLogSet.GetCollect("R_Asker",m_strAsker);
		m_adoLogSet.GetCollect("R_Watcher",m_strWatcher);
		m_adoLogSet.GetCollect("R_ConsumeTime",m_iConsumeTime);

		int iMendKind;
		m_adoLogSet.GetCollect("R_MendKind",iMendKind);
		m_strMendKind = m_MendTemplate.GetName(iMendKind);
		m_ctrlMendKind.SetCurSel(iMendKind-1);
		
		m_adoLogSet.GetCollect("R_Content",m_strContent);
	}
	else
	{
		COleDateTime oleTime;
		m_adoLogSet.GetCollect("CR_DateTime",oleTime);
		m_ctrlDateTime.SetTime(oleTime);
		m_ctrlDateTime.GetTime(m_timeDateTime);

		m_adoLogSet.GetCollect("CR_Asker",m_strAsker);
		m_adoLogSet.GetCollect("CR_Watcher",m_strWatcher);
		m_adoLogSet.GetCollect("R_ConsumeTime",m_iConsumeTime);
		m_adoLogSet.GetCollect("CR_Content",m_strContent);
	}
	UpdateData(false);
	//
	*pResult = 0;
}

//根据 m_byConKind, m_byOrder 的值显示相应的信息
void CConstructRequest::DisplayRecord()
{
	
	if(m_byConKind == 0 && m_byOrder == 0 )
	{
		m_timeDateTime = CTime::GetCurrentTime();
		UpdateOrderEdit();
	}
	else
	{

		CString strSQL;
		strSQL.Format("SELECT * FROM MENDRECORD WHERE T_ORDER = %d",m_byOrder);
		m_adoLogSet = m_adoLogConnect.Execute(strSQL);
		int iTemp;

		//Order
		m_strOrder.Format("%d",m_byOrder);
		//AskStation
		m_adoLogSet.GetCollect("T_Station",iTemp);
		m_ctrlStation.SetCurSel(iTemp-1);

		COleDateTime oleDateTime;
		if( m_byConKind == CONSTREGISTER )//显示登记内容
		{
			m_iKind = 0;
			m_strEdit1 = "第";
			//m_strEdit2 = "施 工 登 记 请 求 内 容";
			
			
			m_adoLogSet.GetCollect("R_DateTime",oleDateTime);
			m_ctrlDateTime.SetTime(oleDateTime);
			m_adoLogSet.GetCollect("R_Asker",m_strAsker);
			m_adoLogSet.GetCollect("R_Watcher",m_strWatcher);
			m_adoLogSet.GetCollect("R_MendKind",iTemp);
			m_ctrlMendKind.SetCurSel(iTemp-1);
			m_adoLogSet.GetCollect("R_ConsumeTime",m_iConsumeTime);
			m_adoLogSet.GetCollect("R_Content",m_strContent);
		}
		else//显示消记内容
		{
			m_iKind = 1;
			m_strEdit1 = "消记第";
			//m_strEdit2 = "施 工 消 记 请 求 内 容";
			
			m_adoLogSet.GetCollect("CR_DateTime",oleDateTime);
			m_ctrlDateTime.SetTime(oleDateTime);
			m_adoLogSet.GetCollect("CR_Asker",m_strAsker);
			m_adoLogSet.GetCollect("CR_Watcher",m_strWatcher);
			m_adoLogSet.GetCollect("CR_Content",m_strContent);
		}
		m_ctrlDateTime.GetTime(m_timeDateTime);
	}
	//-------------------------------------------------------------
	UpdateListCtrl();
	UpdateCtrlComponent();
	UpdateData(false);
 }


void CConstructRequest::UpdateCtrlComponent()
{
	if(m_byConKind == 0 && m_byOrder == 0 )//说明是由维修工作站编写施工请求。
	{
		UpdateOrderEdit();
		
		//LIST
		//m_ctrlList.EnableWindow(TRUE);

		//两个单选按钮
		GetDlgItem(IDC_REGISTER)->EnableWindow(TRUE);
		GetDlgItem(IDC_CLOSEREG)->EnableWindow(TRUE);
		
		//删除按钮、保存按钮
		GetDlgItem(IDC_DELETE)->EnableWindow(TRUE);
		GetDlgItem(IDC_NEWREGISTER)->EnableWindow(TRUE);
		
		//车站
		GetDlgItem(IDC_STATION)->EnableWindow(TRUE);

		//请求人与值班人
		((CEdit*)GetDlgItem(IDC_ASKER) )->SetReadOnly(FALSE);
		((CEdit*)GetDlgItem(IDC_WATCHER))->SetReadOnly(FALSE);
		
		//所需时间和施工种类
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(true);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(true);
	}

	else
	{
		//LIST
		//m_ctrlList.ShowWindow(SW_HIDE);

		//两个单选按钮
		GetDlgItem(IDC_REGISTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLOSEREG)->EnableWindow(FALSE);

		//删除按钮、保存按钮
		GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEWREGISTER)->EnableWindow(FALSE);
		
		//车站
		GetDlgItem(IDC_STATION)->EnableWindow(FALSE);
	
		//请求人与值班人
		((CEdit*)GetDlgItem(IDC_ASKER))->SetReadOnly(TRUE);
		((CEdit*)GetDlgItem(IDC_WATCHER))->SetReadOnly(TRUE);

		if( m_byConKind == CONSTREGISTER )//登记
		{
			//所需时间和施工种类
			GetDlgItem(IDC_CONSUMETIME)->EnableWindow(true);
			GetDlgItem(IDC_MENDKIND)->EnableWindow(true);
		}
		else//消记
		{
			//所需时间和施工种类
			GetDlgItem(IDC_CONSUMETIME)->EnableWindow(false);
			GetDlgItem(IDC_MENDKIND)->EnableWindow(false);
		}
	}
}

