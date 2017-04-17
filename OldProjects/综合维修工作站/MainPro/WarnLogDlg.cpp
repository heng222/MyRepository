// WarnLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "WarnLogDlg.h"
#include "AlarmInfo.h"
#include "MainFrm.h"
#include "WarnNoteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CWarnLogDlg dialog

static CString  WType[]={"报警","报警","信息"};
CWarnLogDlg::CWarnLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWarnLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWarnLogDlg)
	//}}AFX_DATA_INIT
	m_bActive=FALSE;
	nCode=0;
	nType=0;
}


void CWarnLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWarnLogDlg)
	DDX_Control(pDX, IDC_WARNLOGDLG_STATION, m_ctrlStation);
	DDX_Control(pDX, IDC_WARNLOGDLG_DATE, m_ctrlDate);
	DDX_Control(pDX, IDC_WARNLOGDLG_LIST, m_ctrlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWarnLogDlg, CDialog)
	//{{AFX_MSG_MAP(CWarnLogDlg)
	ON_CBN_SELCHANGE(IDC_WARNLOGDLG_DATE, OnSelchangeWarnlogdlgDate)
	ON_NOTIFY(NM_DBLCLK, IDC_WARNLOGDLG_LIST, OnDblclkWarnlogdlgList)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_WARNLOGDLG_STATION, OnSelchangeWarnlogdlgStation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWarnLogDlg message handlers

BOOL CWarnLogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrlStation.ResetContent();
	m_ctrlStation.AddString("全部站场");
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	for(int i=0; i<pStationInf->GetLength();i++)
	{
		m_ctrlStation.AddString(pStationInf->GetAt(i)->strName);
	}
	m_ctrlStation.SetCurSel(0);
	
	m_ImageList1.Create (IDB_WARNTYPEL, 32, 3, RGB(0,255,0));
	m_ImageList2.Create (IDB_WARNTYPES, 16, 3, RGB(0,255,0));
	m_ctrlList.SetImageList(&m_ImageList1,TVSIL_NORMAL);
	m_ctrlList.SetImageList(&m_ImageList2,LVSIL_SMALL);
	//设置列的标题
	::SendMessage(m_ctrlList.m_hWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT);//LVS_EX_GRIDLINES|
//	m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlList.SetHeadings( _T("类型,80;序号,50;站名,100;时间,80;内容,200;级别,50;来源,100") );
	m_ctrlList.LoadColumnInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWarnLogDlg::OnSelchangeWarnlogdlgDate() 
{
	// TODO: Add your control notification handler code here
	m_ctrlStation.SetCurSel(0);
	InitList();
}

/*========================================================================
	Name:		更新列表框内容函数
    ----------------------------------------------------------
	Params:		ct	要打开的报警文件的日期
    ----------------------------------------------------------
	Remarks:	
==========================================================================*/
void CWarnLogDlg::InitList()
{
	CAlarmInfo	m_cAlarm;
	CString strSta,strTmp[6];
	int nSelDate;

	m_nItem=-1;
	((CMainFrame*)AfxGetMainWnd())->m_pWarnNoteDlg->ShowWindow(SW_HIDE);

	nSelDate = m_ctrlDate.GetCurSel();
	CTime  ct( (CTime::GetCurrentTime()).GetTime() - nSelDate*86400L );

	m_ctrlStation.GetLBText(m_ctrlStation.GetCurSel(),strSta);
	
	m_ctrlList.DeleteAllItems();

	if ( !m_cAlarm.OpenFile(CAlarmInfo::modeRead,ct.Format("%Y-%m-%d.alm")) )
	{
		//AfxMessageBox("没有报警记录!");
		return;
	}
	m_cAlarm.ReadFile();
	while ( m_cAlarm.ReadNext() )
	{
		int iLength = m_cAlarm.GetCurLength();
		int nLevel;
		CString strHead;
		//	
		for ( int i = 0; i<iLength; i++ )
		{
			if(strSta == "全部站场" ||  m_cAlarm.GetAt(i)->m_sStation == strSta)
			{
				strTmp[0].Format("%d",m_cAlarm.GetAt(i)->m_wOrder);
				strTmp[1] = m_cAlarm.GetAt(i)->m_sStation;
				strTmp[2] = m_cAlarm.GetAt(i)->m_time.Format("%H:%M:%S");
				strTmp[3] = m_cAlarm.GetAt(i)->m_sContent;
				nLevel=m_cAlarm.GetAt(i)->m_byLevel;
				strTmp[4].Format("%d",nLevel);
				strTmp[5] = m_cAlarm.GetAt(i)->m_sSource;
				nLevel-=1;
				m_ctrlList.AddItemAndImage(nLevel,WType[nLevel],strTmp[0],strTmp[1],strTmp[2],strTmp[3],strTmp[4],strTmp[5]);
			}
		}
	}
	m_cAlarm.CloseFile();
}

void CWarnLogDlg::OnDblclkWarnlogdlgList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelDate = m_ctrlDate.GetCurSel();
	if (nSelDate > 0) 
		return;
	
	((CMainFrame*)AfxGetMainWnd())->m_pWarnNoteDlg->ShowWindow(SW_HIDE);
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	m_nItem=m_ctrlList.GetNextSelectedItem(lpos);
	if(m_nItem >= 0)
	{
		int nNum=atoi(m_ctrlList.GetItemText(m_nItem,1));
//		CTime  tt( (CTime::GetCurrentTime()).GetTime() - nSelDate*86400L );
		((CMainFrame*)AfxGetMainWnd())->m_pWarnNoteDlg->RefreshAll(nNum,CTime::GetCurrentTime());
		((CMainFrame*)AfxGetMainWnd())->m_pWarnNoteDlg->ShowWindow(SW_SHOW);
	}
	*pResult = 0;
}

void CWarnLogDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}

void CWarnLogDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	m_nItem=-1;
	if(bShow)//显示
	{
		m_bActive=TRUE;
		m_ctrlDate.ResetContent();
		CTime tToday = CTime::GetCurrentTime();
		time_t tt = tToday.GetTime();
		do 
		{
			m_ctrlDate.AddString( CTime(tt).Format( "%Y年%m月%d日" ) );
			tt -= 86400L;
		}
		while( CTime(tt).GetDay()!=tToday.GetDay() );
		//	m_ctrlDate.AddString( "读磁盘文件" );
		m_ctrlDate.SetCurSel(0);
		m_ctrlStation.SetCurSel(0);
		InitList();
	}
	else
	{
		((CMainFrame*)AfxGetMainWnd())->m_pWarnNoteDlg->ShowWindow(SW_HIDE);
		m_bActive=FALSE;
	}
}

void CWarnLogDlg::OnOK() 
{
	// TODO: Add extra validation here
	ShowWindow(SW_HIDE);
	CDialog::OnOK();

/*
	BYTE* byB= new BYTE[12];
	int n;
	if (nCode == 5)
		nCode=0;
	nCode++;
	if(nType == 10)
		nType=0;
	nType++;
	memcpy(byB,&nCode,2);
	byB[2]=16;
	byB[3]=nType;
	switch(nType) {
	case 1:
		n=64;
		memcpy(byB+4,&n,2);
		byB[6]=32;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		memcpy(byB+4,&nCode,2);
		break;
	case 10:
		n =(int) fmod(CTime::GetCurrentTime().GetSecond(),2);
		memcpy(byB+4,&n,2);
		break;
	default:
		break;
	}
	byB[7]=nType/nCode;
	if (byB[7]>3) 
		byB[7]=3;
	time_t tt=CTime::GetCurrentTime().GetTime();
	memcpy(byB+8,&tt,4);
	((CMainFrame*)AfxGetMainWnd())->m_pWarnNoteDlg->PostMessage(WM_REC_ALARM,(long)byB,12);
*/
}

void CWarnLogDlg::OnCancel()
{
	// TODO: Add extra validation here
	ShowWindow(SW_HIDE);
	CDialog::OnCancel();
}

void CWarnLogDlg::OnSelchangeWarnlogdlgStation() 
{
	// TODO: Add your control notification handler code here
	InitList();
}
