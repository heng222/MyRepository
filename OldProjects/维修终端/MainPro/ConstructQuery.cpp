// ConstructQuery.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "ConstructQuery.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CConstructQuery dialog


CConstructQuery::CConstructQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CConstructQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstructQuery)
	m_oleRDateTime = COleDateTime::GetCurrentTime();
	m_strAsker = _T("");
	m_strAskStation = _T("");
	m_strAskTime = _T("");
	m_strChecker = _T("");
	m_strCheckTime = _T("");
	m_strComContent = _T("");
	m_strComTitle = _T("");
	m_strComOrder = _T("");
	m_strCopyFor = _T("");
	m_strDispatcher = _T("");
	m_strMendKind = _T("");
	m_strOrgReceive = _T("");
	m_strOrgSend = _T("");
	m_iComKind = 0;
	m_iRegKind = 0;
	m_strRegContent = _T("");
	m_strRegTitle = _T("");
	m_strSendTime = _T("");
	m_strStations = _T("");
	m_strWatcher = _T("");
	m_strConsumeTime = _T("");
	//}}AFX_DATA_INIT
}


void CConstructQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstructQuery)
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Control(pDX, IDC_CONDATETIME, m_ctrlRDateTime);
	DDX_DateTimeCtrl(pDX, IDC_CONDATETIME, m_oleRDateTime);
	DDX_Text(pDX, IDC_ASKER, m_strAsker);
	DDX_Text(pDX, IDC_ASKSTATION, m_strAskStation);
	DDX_Text(pDX, IDC_ASKTIME, m_strAskTime);
	DDX_Text(pDX, IDC_CHECKER, m_strChecker);
	DDX_Text(pDX, IDC_CHECKTIME, m_strCheckTime);
	DDX_Text(pDX, IDC_COMCONTENT, m_strComContent);
	DDX_Text(pDX, IDC_COMMANDTITLE, m_strComTitle);
	DDX_Text(pDX, IDC_COMORDER, m_strComOrder);
	DDX_Text(pDX, IDC_COPYFOR, m_strCopyFor);
	DDX_Text(pDX, IDC_DISPATCHER, m_strDispatcher);
	DDX_Text(pDX, IDC_MENDKIND, m_strMendKind);
	DDX_Text(pDX, IDC_ORGRECEIVE, m_strOrgReceive);
	DDX_Text(pDX, IDC_ORGSEND, m_strOrgSend);
	DDX_Radio(pDX, IDC_RADIOCCOM, m_iComKind);
	DDX_Radio(pDX, IDC_RADIOREG, m_iRegKind);
	DDX_Text(pDX, IDC_REGCONTENT, m_strRegContent);
	DDX_Text(pDX, IDC_REGTITLE, m_strRegTitle);
	DDX_Text(pDX, IDC_SENDTIME, m_strSendTime);
	DDX_Text(pDX, IDC_STATIONS, m_strStations);
	DDX_Text(pDX, IDC_WATCHER, m_strWatcher);
	DDX_Text(pDX, IDC_CONSUMETIME, m_strConsumeTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstructQuery, CDialog)
	//{{AFX_MSG_MAP(CConstructQuery)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_CLEAR, OnBClear)
	ON_NOTIFY(DTN_CLOSEUP, IDC_CONDATETIME, OnCloseupCondatetime)
	ON_BN_CLICKED(IDC_RADIOREG, OnRadioReg)
	ON_BN_CLICKED(IDC_RADIOCCOM, OnRadioCCom)
	ON_BN_CLICKED(IDC_RADIOCREG, OnRadioReg)
	ON_BN_CLICKED(IDC_RADIOOCOM, OnRadioCCom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConstructQuery message handlers

BOOL CConstructQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	m_pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
	//���öԻ���ı���
	this->SetWindowText("��ѯʩ����¼");
	//------------------------------------------
	
	//����������ʾ��ʽ
	m_ctrlRDateTime.SetFormat(_T("yyyy��MM��dd��"));

	//�����еı���
	m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlList.SetHeadings( _T("���,60;����վ,80;�Ǽ�ʱ��,150;ʩ��������,100;�Ǽ�ֵ��Ա,100;ʩ������ʱ��(��),120;ʩ������,80;�Ǽ�����,300;���������,100; ����������ʱ��,150; ��������Ա,100;�����,80;����־�,80;�������̨,100;�����,80;����־�,80;����վ�б�,100; �������,80;�������,80;�����,80;���ʱ��,100;����Ŀ��,100;����,100;��������,300;����ʱ��,150; ����������,100; ����ֵ��Ա,100; ��������,300;��ͨ�����,100; ����ͨ����ʱ��,150; ��ͨ����Ա,100;�����,80;����־�,80;�������̨,100;�����,80;����־�,80; ����վ�б�,100; �������,80;�������,80;�����,80;���ʱ��,100;����Ŀ��,100;����,100;��ͨ����,300") );
	m_ctrlList.LoadColumnInfo();

	//
	
	//����¼�ļ�
	COleDateTime oleDateTime = COleDateTime::GetCurrentTime();
	if( !Records.ReadRecords(theApp.m_strExePath+REACORDPATHNAME+oleDateTime.Format("%Y-%m-%d.rec")) )
	{
		MessageBox( m_oleRDateTime.Format("û���ҵ�%Y-%m-%d��ʩ����¼��"),"��ʾ",MB_OK | MB_ICONINFORMATION );
	}
	
	
	//�����б�ؼ�
	UpdateListCtrl();
	
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//����CReadRecord��ʵ��Records����LISTCTRL
void CConstructQuery::UpdateListCtrl()
{
	//�ȳ�LISTCTRL��ԭ�е�����
	m_ctrlList.DeleteAllItems();
	//
	CString strGroup[50];
	for ( BYTE j=1; j<=Records.GetRecordNum(); j++)//jΪ��ǰ��¼��
	{
		BYTE i = 0;//iָ��LISTCTRL�ĵ�ǰ�к�

		//Station
		strGroup[i++] = Records.GetValue(j,"T_Station");
		strGroup[i++] = Records.GetValue(j,"R_DateTime");	
		strGroup[i++] = Records.GetValue(j,"R_Asker");		
		strGroup[i++] = Records.GetValue(j,"R_Watcher");		
		strGroup[i++] = Records.GetValue(j,"R_ConsumeTime");
		//MendKind
		strGroup[i++] = Records.GetValue(j,"R_MendKind");
		strGroup[i++] = Records.GetValue(j,"R_Content");


		strGroup[i++] = Records.GetValue(j,"CC_Order");
		strGroup[i++] = Records.GetValue(j,"CC_DateTime");	
		strGroup[i++] = Records.GetValue(j,"CC_Dispatcher");
		strGroup[i++] = Records.GetValue(j,"CC_SendBureauName");
		strGroup[i++] = Records.GetValue(j,"CC_SendSubBurName");
		strGroup[i++] = Records.GetValue(j,"CC_SendDispName");
		strGroup[i++] = Records.GetValue(j,"CC_RecBureauName");
		strGroup[i++] = Records.GetValue(j,"CC_RecSubBurName");
		strGroup[i++] = Records.GetValue(j,"CC_Stations");	
		strGroup[i++] = Records.GetValue(j,"CC_OrgSend");
		strGroup[i++] = Records.GetValue(j,"CC_OrgReceive");
		strGroup[i++] = Records.GetValue(j,"CC_Checker");
		strGroup[i++] = Records.GetValue(j,"CC_CheckTime");
		strGroup[i++] = Records.GetValue(j,"CC_CopyFor");
		strGroup[i++] = Records.GetValue(j,"CC_Title");
		strGroup[i++] = Records.GetValue(j,"CC_Content");
		
		strGroup[i++] = Records.GetValue(j,"CR_DateTime");	
		strGroup[i++] = Records.GetValue(j,"CR_Asker");	
		strGroup[i++] = Records.GetValue(j,"CR_Watcher");	
		strGroup[i++] = Records.GetValue(j,"CR_Content");
		
		strGroup[i++] = Records.GetValue(j,"OC_Order");	
		strGroup[i++] = Records.GetValue(j,"OC_DateTime");	
		strGroup[i++] = Records.GetValue(j,"OC_Dispatcher");
		strGroup[i++] = Records.GetValue(j,"OC_SendBureauName");
		strGroup[i++] = Records.GetValue(j,"OC_SendSubBurName");
		strGroup[i++] = Records.GetValue(j,"OC_SendDispName");
		strGroup[i++] = Records.GetValue(j,"OC_RecBureauName");
		strGroup[i++] = Records.GetValue(j,"OC_RecSubBurName");
		strGroup[i++] = Records.GetValue(j,"OC_Stations");	
		strGroup[i++] = Records.GetValue(j,"OC_OrgSend");
		strGroup[i++] = Records.GetValue(j,"OC_OrgReceive");
		strGroup[i++] = Records.GetValue(j,"OC_Checker");
		strGroup[i++] = Records.GetValue(j,"OC_CheckTime");
		strGroup[i++] = Records.GetValue(j,"OC_CopyFor");
		strGroup[i++] = Records.GetValue(j,"OC_Title");
		strGroup[i++] = Records.GetValue(j,"OC_Content");

		//��Ӽ�¼��LISTCTRL��ȥ
		CString strOrder;
		strOrder.Format("%d",j);

		m_ctrlList.AddItem(strOrder,	strGroup[0],
			strGroup[1],	strGroup[2],	strGroup[3],	strGroup[4],	strGroup[5],	strGroup[6],	strGroup[7],
			strGroup[8],	strGroup[9],	strGroup[10],	strGroup[11],	strGroup[12],	strGroup[13],	strGroup[14],
			strGroup[15],	strGroup[16],	strGroup[17],	strGroup[18],	strGroup[19],	strGroup[20],	strGroup[21],
			strGroup[22],	strGroup[23],	strGroup[24],	strGroup[25],	strGroup[26],	strGroup[27],	strGroup[28],	strGroup[29],	strGroup[30],
			strGroup[31],	strGroup[32],	strGroup[33],	strGroup[34],	strGroup[35],	strGroup[36],	strGroup[37],
			strGroup[38],	strGroup[39],	strGroup[40],	strGroup[41],	strGroup[42],	strGroup[43]);
	}
	
}

//˫��LIST
void CConstructQuery::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ShowDetailedInf();
	//-------------------------------------------------------------
	*pResult = 0;
}

void CConstructQuery::OnBClear() 
{
	m_strAsker.Empty();
	m_strAskTime.Empty();
	m_strChecker.Empty();
	m_strCheckTime.Empty();
	m_strComContent.Empty();

	m_strComOrder.Empty();
	m_strComTitle.Empty();
	m_strConsumeTime.Empty();
	m_strCopyFor.Empty();

	m_strDispatcher.Empty();
	m_strMendKind.Empty();
	m_strOrgReceive.Empty();
	m_strOrgSend.Empty();
	m_strRegContent.Empty();

	m_strRegTitle.Empty();
	m_strSendTime.Empty();
	m_strStations.Empty();
	m_strWatcher.Empty();
	//
	UpdateData(false);
	//
	m_ctrlList.DeleteAllItems();
}

void CConstructQuery::OnCloseupCondatetime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	//
	OnBClear();
	//char cPath[100];
	//GetCurrentDirectory(100,cPath);
	CString strPathName;

	if ( !Records.ReadRecords(theApp.m_strExePath+REACORDPATHNAME+m_oleRDateTime.Format("%Y-%m-%d.rec")) )
	{
		MessageBox( m_oleRDateTime.Format("û���ҵ�%Y-%m-%d��ʩ����¼��"),"��ʾ",MB_OK | MB_ICONINFORMATION );
	}
	else
	{
		UpdateListCtrl();
	}
	//
	*pResult = 0;
}
//////////////////////////////////////////////////////////////////////

void CConstructQuery::OnRadioReg() 
{
	ShowDetailedInf();
}

void CConstructQuery::OnRadioCCom() 
{
	ShowDetailedInf();	
}

void CConstructQuery::ShowDetailedInf()
{
	UpdateData();
	//--------------------------------------------------------
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	//
	if( nItem >= 0 )
	{
		//byIndexΪ��¼���
		BYTE byIndex = atoi(m_ctrlList.GetItemText(nItem,0));
		//����վ
		m_strAskStation	= Records.GetValue(byIndex, "T_Station");
		//--------------------------------------------------------------
		if ( m_iRegKind == 0 )//��ʾ�Ǽ���Ϣ
		{
			m_strAskTime	= Records.GetValue(byIndex,	"R_DateTime");
			m_strAsker		= Records.GetValue(byIndex,	"R_Asker");
			m_strWatcher	= Records.GetValue(byIndex,	"R_Watcher");
			m_strConsumeTime= Records.GetValue(byIndex,	"R_ConsumeTime");
			m_strMendKind	= Records.GetValue(byIndex, "R_MendKind");
			m_strRegContent	= Records.GetValue(byIndex,	"R_Content");
		}
		else//��ʾ������Ϣ
		{
			m_strAskTime	= Records.GetValue(byIndex,	"CR_DateTime");
			if (m_strAskTime.IsEmpty())
			{
				m_strAskStation.Empty();
			}
			m_strAsker		= Records.GetValue(byIndex,	"CR_Asker");
			m_strWatcher	= Records.GetValue(byIndex,	"CR_Watcher");
			m_strConsumeTime= "";
			m_strMendKind	= "";
			m_strRegContent	= Records.GetValue(byIndex,	"CR_Content");
		}
		//--------------------------------------------------------------
		if ( m_iComKind == 0 )//��ʾ����������Ϣ
		{
			m_strComOrder	= Records.GetValue(byIndex,	"CC_Order");
			m_strSendTime	= Records.GetValue(byIndex,	"CC_DateTime");
			m_strDispatcher = Records.GetValue(byIndex, "CC_Dispatcher");
			m_strStations	= Records.GetValue(byIndex,"CC_Stations");	
			m_strOrgSend	= Records.GetValue(byIndex, "CC_OrgSend");
			m_strOrgReceive = Records.GetValue(byIndex, "CC_OrgReceive");
			m_strChecker	= Records.GetValue(byIndex, "CC_Checker");
			m_strCheckTime	= Records.GetValue(byIndex, "CC_CheckTime");
			m_strCopyFor	= Records.GetValue(byIndex, "CC_CopyFor");
			m_strComContent	= Records.GetValue(byIndex,	"CC_Content");
		}
		else//��ʾ��ͨ������Ϣ
		{
			m_strComOrder	= Records.GetValue(byIndex,	"OC_Order");
			m_strSendTime	= Records.GetValue(byIndex,	"OC_DateTime");
			m_strDispatcher = Records.GetValue(byIndex, "OC_Dispatcher");
			m_strStations	= Records.GetValue(byIndex,"OC_Stations");	
			m_strOrgSend	= Records.GetValue(byIndex, "OC_OrgSend");
			m_strOrgReceive = Records.GetValue(byIndex, "OC_OrgReceive");
			m_strChecker	= Records.GetValue(byIndex, "OC_Checker");
			m_strCheckTime	= Records.GetValue(byIndex, "OC_CheckTime");
			m_strCopyFor	= Records.GetValue(byIndex, "OC_CopyFor");
			m_strComContent	= Records.GetValue(byIndex,	"OC_Content");
		}
	}
	//-----------------------------------
	UpdateData(false);
}

void CConstructQuery::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	//delete this;
	CDialog::PostNcDestroy();
}

void CConstructQuery::OnCancel() 
{
	//this->DestroyWindow();
	CDialog::OnCancel();
}

BOOL CConstructQuery::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
//	((CMainFrame*)AfxGetMainWnd())->m_pQueryDlg = NULL;	
	return CDialog::DestroyWindow();
}
