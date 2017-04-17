// ConstructRequest.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "ConstructRequest.h"
#include "mainfrm.h"


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
	m_strEdit2 = _T("施 工 登 记 请 求 内 容");
	m_strAsker = _T("");
	m_strWatcher = _T("");
	m_strOrder = _T("");
	m_strMendKind = _T("");
	m_strStation = _T("");
	m_timeDateTime = CTime::GetCurrentTime();
	m_iConsumeTime = 30;
	//}}AFX_DATA_INIT

	//读取施工模板
	m_MendTemplate.ReadFile(theApp.m_strExePath+MENDTEMPLATEPATHNAME);

}


void CConstructRequest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstructRequest)
	DDX_Control(pDX, IDC_MENDKIND, m_ctrlMendKind);
	DDX_Control(pDX, IDC_ORDER, m_ctrlOrder);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrlDateTime);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit1);
	DDX_Text(pDX, IDC_EDIT3, m_strEdit3);
	DDX_Radio(pDX, IDC_REGISTER, m_iKind);
	DDX_Text(pDX, IDC_CONTENT, m_strContent);
	DDV_MaxChars(pDX, m_strContent, 300);
	DDX_Text(pDX, IDC_EDIT2, m_strEdit2);
	DDX_Text(pDX, IDC_ASKER, m_strAsker);
	DDV_MaxChars(pDX, m_strAsker, 20);
	DDX_Text(pDX, IDC_WATCHER, m_strWatcher);
	DDV_MaxChars(pDX, m_strWatcher, 20);
	DDX_Text(pDX, IDC_ORDER, m_strOrder);
	DDX_CBString(pDX, IDC_MENDKIND, m_strMendKind);
	DDX_Text(pDX, IDC_STATION, m_strStation);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timeDateTime);
	DDX_Text(pDX, IDC_CONSUMETIME, m_iConsumeTime);
	DDV_MinMaxInt(pDX, m_iConsumeTime, 0, 100000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstructRequest, CDialog)
	//{{AFX_MSG_MAP(CConstructRequest)
	ON_BN_CLICKED(IDC_REGISTER, OnRadioRegister)
	ON_BN_CLICKED(IDC_DELETE, OnBDelete)
	ON_BN_CLICKED(IDC_REQUEST, OnBRequestCommand)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_CBN_SELCHANGE(IDC_MENDKIND, OnSelchangeMendkind)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioRegister)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConstructRequest message handlers

BOOL CConstructRequest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	/////////////////////////////////////////////////////////////////////////////////////
	m_pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
	COleDateTime oleDateTime = COleDateTime::GetCurrentTime();
	//设置对话框的标题
	this->SetWindowText(oleDateTime.Format("%Y年%m月%d日的施工记录"));

	//设置日期格式
	m_ctrlDateTime.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));

	//设置施工种类(天窗修、区间修)
	m_ctrlMendKind.SetCurSel(0);

	//加入站场名字
	m_strStation = CReadStationInf::GetInstance()->GetName(CReadStationInf::GetActiveStation());//theApp.m_strStationName;
	
	//设置列的标题
	m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlList.SetHeadings( _T("序号,60;请求站,80;登记时间,150;施工请求人,100;登记值班员,100;施工所需时间(分),120;施工种类,80;登记内容,300;消记时间,150; 消记请求人,100; 消记值班员,100; 消记内容,300;") );
	m_ctrlList.LoadColumnInfo();

	//打开当天的记录文件并将内容写入到 对象 Records 中
	Records.ReadRecords(theApp.m_strExePath + REACORDPATHNAME+oleDateTime.Format("%Y-%m-%d.rec"));
	
	//初始化施工请求内容
	m_strContent = m_MendTemplate.GetContent(1,!m_iKind);

	//更新ListCtrl控件
	UpdateListCtrl();
	
	//更新序号控件
	UpdateOrderEdit();

	UpdateData(false);
	//////////////////////////////////////////////////////////////////////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//根据成员变量 Records 更新 LISTCTRL
void CConstructRequest::UpdateListCtrl()
{
	//先删除LISTCTRL中原有的内容
	m_ctrlList.DeleteAllItems();
	//
	CString strGroup[25];
	for ( BYTE j=1; j<=Records.GetRecordNum(); j++)//j为当前记录号
	{
		BYTE i = 0;//i指向LISTCTRL的当前列号

		//---------------------------------------
		strGroup[i++] = Records.GetValue(j,"T_Station");
		strGroup[i++] = Records.GetValue(j,"R_DateTime");	
		strGroup[i++] = Records.GetValue(j,"R_Asker");		
		strGroup[i++] = Records.GetValue(j,"R_Watcher");		
		strGroup[i++] = Records.GetValue(j,"R_ConsumeTime");	
		strGroup[i++] = Records.GetValue(j,"R_MendKind");	
		strGroup[i++] = Records.GetValue(j,"R_Content");

		
		strGroup[i++] = Records.GetValue(j,"CR_DateTime");	
		strGroup[i++] = Records.GetValue(j,"CR_Asker");	
		strGroup[i++] = Records.GetValue(j,"CR_Watcher");	
		strGroup[i++] = Records.GetValue(j,"CR_Content");
		

		//添加记录到LISTCTRL中去
		CString strOrder;
		strOrder.Format("%d",j);

		m_ctrlList.AddItem(strOrder,strGroup[0],
			strGroup[1],	strGroup[2],	strGroup[3],	strGroup[4],	strGroup[5],	strGroup[6],
			strGroup[7],	strGroup[8],	strGroup[9],	strGroup[10]);
	}
	
}

//根据记录数更新IDC_ORDER
void CConstructRequest::UpdateOrderEdit()
{
	m_strOrder.Format( "%d", Records.GetRecordNum() + 1);
	m_ctrlOrder.SetWindowText(m_strOrder);
}


//双击LISTCTRL
void CConstructRequest::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	
	CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	if (nItem < 0)	return;
	//Order
	BYTE byOrder = (BYTE)atoi( m_ctrlList.GetItemText(nItem,0) );
	//Station
	m_strOrder = m_ctrlList.GetItemText(nItem,0);
	m_strStation = pStationInf->GetName(atoi(Records.GetValue(byOrder,"T_Station")));
	//------------------
	COleDateTime oleTime;
	if ( m_iKind == 0 )
	{
		oleTime.ParseDateTime( Records.GetValue(byOrder, "R_DateTime") );
		m_ctrlDateTime.SetTime(oleTime);
		m_ctrlDateTime.GetTime(m_timeDateTime);

		m_strAsker = Records.GetValue(byOrder, "R_Asker");
		m_strWatcher = Records.GetValue(byOrder, "R_Watcher");
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(true);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(true);
		m_iConsumeTime = atoi(Records.GetValue(byOrder, "R_ConsumeTime"));
		m_strMendKind = m_MendTemplate.GetName( atoi(Records.GetValue(byOrder, "R_MendKind")) );
		m_strContent = Records.GetValue(byOrder, "R_Content");
	}
	else
	{
		if ( Records.GetValue(byOrder, "CR_DateTime").IsEmpty() )
		{
			MessageBox("此条记录尚未消记! 无消记信息。","提示",MB_ICONINFORMATION);
			return;
		}
		oleTime.ParseDateTime( Records.GetValue(byOrder, "CR_DateTime") );
		m_ctrlDateTime.SetTime(oleTime);
		m_ctrlDateTime.GetTime(m_timeDateTime);
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(false);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(false);
		m_strAsker = Records.GetValue(byOrder, "CR_Asker");
		m_strWatcher = Records.GetValue(byOrder, "CR_Watcher");
		m_strContent = Records.GetValue(byOrder, "CR_Content");

	}
	UpdateData(false);
	//------------------------------------------
	*pResult = 0;
}
//当MENDKIND变化时
void CConstructRequest::OnSelchangeMendkind() 
{
	UpdateData();
	m_strContent = m_MendTemplate.GetContent(m_strMendKind,!m_iKind);
	UpdateData(false);
	
}
//单击RADIO控件
void CConstructRequest::OnRadioRegister() 
{
	UpdateData();
	//---------------------------------------------
	if(m_iKind == 0)
	{
		//m_strStation = theApp.m_strStationName;
		m_strEdit2 = "施 工 登 记 请 求 内 容";
		m_strEdit1 = "第";
		//m_strContent = theApp.m_MendTemplate.GetContent(m_ctrlMendKind.GetCurSel()+1,TRUE);
		
		GetDlgItem(IDC_REQUEST)->SetWindowText("请求封锁");
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(true);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(true);
		//更新IDC_ORDER
		UpdateOrderEdit();
	}
	else
	{
		POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
		int nItem=m_ctrlList.GetNextSelectedItem(lpos);
		if(nItem != -1)
		{
			m_strOrder = m_ctrlList.GetItemText(nItem,0);
		}
		else
		{
			MessageBox("请先在上面的列表框中选择要消记的记录。","提示",MB_ICONINFORMATION);
			m_iKind = 0;
			UpdateData(FALSE);
			return;
		}
		m_strEdit1 = "消记第";
		m_strEdit2 = "施 工 消 记 请 求 内 容";		
		m_strContent = m_MendTemplate.GetContent(m_ctrlMendKind.GetCurSel()+1,FALSE);

		GetDlgItem(IDC_REQUEST)->SetWindowText("请求开通");
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(false);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(false);
	}
	//更改时间
	m_timeDateTime = CTime::GetCurrentTime();
	//-------------------------------------------------------------------------
	UpdateData(FALSE);
}

//将新施工登记或消记加入Records中
void CConstructRequest::AddNewData()
{
	BYTE byRecordIndex = atoi(m_strOrder);
	//
	CString strTemp;
	if(m_iKind==0)//新增登记
	{
		Records.SetValue(byRecordIndex,"T_Station",CReadStationInf::GetInstance()->GetName(CReadStationInf::GetActiveStation()));
		Records.SetValue(byRecordIndex,"R_DateTime",m_timeDateTime.Format("%Y-%m-%d %H:%M:%S"));
		Records.SetValue(byRecordIndex,"R_Asker",m_strAsker);
		Records.SetValue(byRecordIndex,"R_Watcher",m_strWatcher);
		Records.SetValue(byRecordIndex,"R_ConsumeTime",m_iConsumeTime);
		Records.SetValue(byRecordIndex,"R_MendKind",m_strMendKind);
		Records.SetValue(byRecordIndex,"R_Content",m_strContent);
		//UpdateOrderEdit();
	}
	else//更新消记
	{
		ASSERT ( byRecordIndex<=Records.GetRecordNum() );

		Records.SetValue(byRecordIndex,"CR_DateTime",m_timeDateTime.Format("%Y-%m-%d %H:%M:%S"));
		Records.SetValue(byRecordIndex,"CR_Asker",m_strAsker);
		Records.SetValue(byRecordIndex,"CR_Watcher",m_strWatcher);
		Records.SetValue(byRecordIndex,"CR_Content",m_strContent);
	}

	//更新列表控件
	UpdateListCtrl();

	//将更新后的记录集保存到文件中
	Records.WriteRecords();
}


//单击删除按钮
void CConstructRequest::OnBDelete()
{
	//得到LISTCTRL被选择的行号（Based Zero）
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	//
	if ( nItem == -1)
	{
		MessageBox("请先在列表框中选择要删除的行!","提示",MB_OK | MB_ICONINFORMATION);
		return;
	}
	if( MessageBox("确定要删除选中的记录吗？不可恢复！","警告",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDNO)
	{
		return;
	}

	//得到记录的序号
	CString strOrder = m_ctrlList.GetItemText(nItem,0);
	//删除选中的记录并将更改后的内容写入文件
	Records.DeleteRecord( (BYTE)atoi(strOrder) );
	Records.WriteRecords();

	//刷新LISTCTRL
	UpdateListCtrl();

	//刷新IDC_ORDER控件
	if ( m_iKind == 0 )
	{
		//UpdateOrderEdit();
	}
	else
	{
		//m_strOrder = "0";
		//m_ctrlOrder.SetWindowText(m_strOrder);
	}
}

void CConstructRequest::OnBRequestCommand() 
{
	UpdateData(TRUE);
	if (m_strAsker.IsEmpty())
	{
		MessageBox("请求人不能为空!","错误提示",MB_ICONERROR);
		return;
	}

	if ( m_strWatcher.IsEmpty() )
	{
		MessageBox("值班员不能为空!","错误提示",MB_ICONERROR);
		return;
	}

	if ( m_iConsumeTime == 0)
	{
		MessageBox("所需时间不能为零!","错误提示",MB_ICONERROR);
		return;
	}

	//发送数据帧
	//检测网络状态
	BOOL bIsConnect = ((CMainFrame*)AfxGetMainWnd())->m_socketClient.IsOpen();
	if ( 1 )
	{
		BYTE byFrame[CONSTFAMEMAXLEN];
		WORD nFrameLen = 0;
		
		//打包数据帧
		GetFrame(byFrame,nFrameLen);
		((CMainFrame*)AfxGetMainWnd())->m_socketClient.WriteComm(CONSTFRAMEKIND,0X01,byFrame,nFrameLen,INFINITE);
		MessageBox("请求已发出，请注意接收回执命令。","提示",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("网络连接存在问题，请稍后发送。","提示：网络不通",MB_ICONINFORMATION);
	}
	
	//将数据保存到文件中
	AddNewData();
}

//打包数据帧
void CConstructRequest::GetFrame(LPBYTE byFrame,WORD& nFrameLen)
{
	//byFrame为待发送的帧，nFrameLen为帧的有效长度。
	UpdateData();

	//-----------------------
	nFrameLen = 0;
	//WORD wTemp;

	//请求站站码(WORD)
	//CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	//WORD wOrder = pStationInf->GetStationID(theApp.m_strStationName);
	WORD wOrder = CReadStationInf::GetActiveStation();
	memcpy(byFrame+nFrameLen,&wOrder,2);
	nFrameLen += 2;

	//请求类别(登记，消记) (BYTE)
	//0为登记,1为消记
	if ( m_iKind == 0 )
	{
		byFrame[nFrameLen++] = CONSTREGISTER;
	}
	else if (m_iKind == 1)
	{
		byFrame[nFrameLen++] = CONSTCLEARREG;
	}
	
	//登记日期时间(DWORD)
	DWORD dwTemp;
	
	if( m_iKind == 1 )//消记
	{
		//从相应的文件中得到登记日期
		COleDateTime oleRDateTime;
		CTime tDT1,tDT2;
		oleRDateTime.ParseDateTime(Records.GetValue(atoi(m_strOrder),"R_DateTime"));
		m_ctrlDateTime.GetTime(tDT2);
		m_ctrlDateTime.SetTime(oleRDateTime);
		m_ctrlDateTime.GetTime(tDT1);
		dwTemp = tDT1.GetTime();
		m_ctrlDateTime.SetTime(&tDT2);
	}
	else//登记
	{
		dwTemp = m_timeDateTime.GetTime();
	}
	memcpy( byFrame+nFrameLen, &dwTemp, 4 );
	nFrameLen += 4;
	
	//消记日期时间 (DWORD)
	if( m_iKind == 1 )//消记
	{
		dwTemp = m_timeDateTime.GetTime();
	}
	else
	{
		dwTemp = 0;
	}
	memcpy( byFrame+nFrameLen, &dwTemp, 4 );
	nFrameLen += 4;


	//请求人(20 BYTES)
	int i = 0;
	for (i = 0; i<20; i++)
	{
		if( i<m_strAsker.GetLength() )
		{
			byFrame[nFrameLen++] = m_strAsker.GetAt(i);
		}
		else
		{
			byFrame[nFrameLen++] = 0;
		}
	}

	//值班员(20 BYTES)
	for (i = 0; i<20; i++)
	{
		if( i<m_strWatcher.GetLength() )
		{
			byFrame[nFrameLen++] = m_strWatcher.GetAt(i);
		}
		else
		{
			byFrame[nFrameLen++] = 0;
		}
	}


	//施工类别(天窗修、区间修) (BYTE)
	//1为天窗修,2为区间修, ......
	if( m_iKind == 0 )
	{
		byFrame[nFrameLen++] = m_ctrlMendKind.GetCurSel() + 1;
	}
	else
	{
		byFrame[nFrameLen++] = 0;
	}
	
	//施工所需时间(WORD)
	if( m_iKind == 0 )
	{
		memcpy( byFrame+nFrameLen, &m_iConsumeTime, 2 );
		nFrameLen += 2;
	}
	else
	{
		byFrame[nFrameLen++] = 0;
		byFrame[nFrameLen++] = 0;
	}

	//请求内容长度
	WORD wContentLen = m_strContent.GetLength();
	memcpy(byFrame+nFrameLen,&wContentLen,2);
	nFrameLen += 2;

	//请求内容
	memcpy(byFrame+nFrameLen,m_strContent,wContentLen);

	//--------------------------------------
	//得到数据帧的有效长度
	nFrameLen += wContentLen;
}
//===============================================================================

void CConstructRequest::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//DestroyWindow();
	CDialog::OnCancel();
}

void CConstructRequest::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	//delete this;
	CDialog::PostNcDestroy();
	
}

BOOL CConstructRequest::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
//	( (CMainFrame*)AfxGetMainWnd() )->m_pRequestDlg = NULL;
	return CDialog::DestroyWindow();
}

