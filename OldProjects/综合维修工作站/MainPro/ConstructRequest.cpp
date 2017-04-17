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
	m_strEdit1 = _T("��");
	m_strEdit3 = _T("������");
	m_iKind = 0;
	m_strContent = _T("");
	m_strEdit2 = _T("ʩ ��  �� �� �� ��");
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
	//���ӵ����ݿ�
	if ( !m_adoLogConnect.ConnectOracle(theApp.m_strDBDataSource,theApp.m_strDBUserID,theApp.m_strDBPassword))
	{		
		MessageBox("�����޷����ӵ����ݿ���������޷�ִ�д˲���!","��������",MB_ICONERROR);
		OnCancel();
		return FALSE;
	}
	//--------------------------------------------------------
	m_pMainFrame = ((CMainFrame*)AfxGetMainWnd());
	
	//
	SetWindowText(CTime::GetCurrentTime().Format("%Y��%m��%d�յ�ʩ����¼"));
	
	//�������ڸ�ʽ
	m_ctrlDateTime.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));

	//����ʩ�����
	((CComboBox*)GetDlgItem(IDC_MENDKIND))->SetCurSel(0);

	//����վ������
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	int iLength = pStationInf->GetLength();
	for ( int i = 0; i< iLength; i++ )
	{
		CString strName = pStationInf->GetAt(i)->strName;
		((CComboBox*)GetDlgItem(IDC_STATION))->AddString(strName);
	}
	int iOrder = pStationInf->GetItem(pStationInf->GetActiveStation())->iIndex;
	((CComboBox*)GetDlgItem(IDC_STATION))->SetCurSel(iOrder);
	
	//�����еı���
	m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlList.SetHeadings( _T("���,60;����վ,80;�Ǽ�ʱ��,150;ʩ��������,100;�Ǽ�ֵ��Ա,100;ʩ������ʱ��(��),120;ʩ������,80;�Ǽ�����,300;����ʱ��,150; ����������,100; ����ֵ��Ա,100; ��������,300;") );
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
//����LISTCTRL�ؼ�
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
	
	//�Ӽ�¼����ȡ����¼�����뵽LISTCTRL��
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
		
		//��Ӽ�¼
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
//����IDC_ORDER,ʹIDC_ORDER����ʾ����¼����1��
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

//����LISTCTRLʱ������RADIO��״̬����IDC_ORDER
void CConstructRequest::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//�õ������е����
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	UpdateData();
	if(nItem != -1 && m_iKind == 1)
	{
		
		//ʹIDC_STATION��ʾ�����е�վ������
		//m_strStation = m_ctrlList.GetItemText(nItem,1);
		//m_ctrlStation.SetCurSel(pStationInf->GetOrder(m_strStation) - 1);
		//if(m_iKind == 0)//�Ǽ�
		//{
			//UpdateOrderEdit();
		//}
		//else if(m_iKind == 1 )//����
		//{
			m_strOrder = m_ctrlList.GetItemText(nItem,0);
		//}
		UpdateData(false);
	}

	//=====================
	*pResult = 0;
}

//����RADIO�ؼ�
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
		m_strEdit1 = "��";
		//m_strEdit2 = "ʩ �� �� �� �� �� �� ��";
		m_strContent = m_MendTemplate.GetContent(m_ctrlMendKind.GetCurSel()+1,true);
//		GetDlgItem(IDC_NEWREGISTER)->SetWindowText("(&N)�����Ǽ�");
		
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(true);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(true);

		//����IDC_ORDER�ؼ�
		UpdateOrderEdit();
	}
	else
	{
		//����STATION��ORDER
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
			MessageBox("�������б����ѡ��Ҫ���ǵļ�¼���ٽ�����������","��ʾ",MB_ICONINFORMATION);
			m_iKind = 0;
			UpdateData(false);
			return;
		}

		m_strEdit1 = "���ǵ�";
		//m_strEdit2 = "ʩ �� �� �� �� �� �� ��";
		m_strContent = m_MendTemplate.GetContent(1,false);
//		GetDlgItem(IDC_NEWREGISTER)->SetWindowText("(&N)��������");

		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(false);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(false);
	}
	//
	UpdateData(false);
}
//��MENDKIND�仯ʱ
void CConstructRequest::OnSelchangeMendkind() 
{
	UpdateData();
	m_strContent = m_MendTemplate.GetContent(m_strMendKind,!m_iKind);
	UpdateData(false);	
}
//������¼
void CConstructRequest::OnNewregister() 
{
	GetDlgItem(IDC_REQUEST)->EnableWindow(true);
	GetDlgItem(IDC_NEWREGISTER)->EnableWindow(false);
	//
	if ( !AddNewData() )
	{
		MessageBox("�������ɹ�!","��ʾ",MB_ICONINFORMATION);
	}
}
BOOL CConstructRequest::AddNewData()
{
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	//��ǰǰ��¼�Ѿ�����
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
		MessageBox("�����ˣ�ֵ��Ա������ʱ������һ��Ϊ�գ�����ʧ�ܣ�","",MB_ICONINFORMATION);
		return FALSE;
	}
	//-------------------------
	CString strSQL;
	//������ʱ��ת��Ϊ�ַ�����
	CString strDateTime;
	strDateTime = m_timeDateTime.Format("%Y-%m-%d %H:%M:%S");
	
	if(m_iKind==0)//�����Ǽ�
	{
		//�õ���Ӧ��վ��վ��
		int iStation = pStationInf->GetStationID(m_strStation);
		//�õ�ʩ����������
		int iMendKind = ((CComboBox*)GetDlgItem(IDC_MENDKIND))->GetCurSel() + 1;

		strSQL.Format("INSERT INTO MENDRECORD(T_Order,T_Station,R_DateTime,R_Asker,R_Watcher,R_ConsumeTime,R_MendKind,R_Content) VALUES(%s,%d,to_Date('%s','yyyy-mm-dd HH24:mi:ss'),'%s','%s',%d,%d,'%s')",
			m_strOrder,iStation,strDateTime,m_strAsker,m_strWatcher,m_iConsumeTime,iMendKind,m_strContent);
	}
	else//��������
	{
		//�õ�����¼��
		m_adoLogSet = m_adoLogConnect.Execute("SELECT MAX(T_Order) AS T_Order FROM MENDRECORD");
		int T_Order;
		m_adoLogSet.GetCollect("T_ORDER",T_Order);
		//��Ҫ���ǵļ�¼��Чʱ
		if ( atoi(m_strOrder) > T_Order || atoi(m_strOrder) <= 0 )
		{
			CString strInf;
			strInf.Format("�����ڼ�¼��Ϊ%d��ʩ�����޷��������ǣ�\n��ʾ�������б����ѡ��Ҫ���ǵ�ʩ����",atoi(m_strOrder));
		
			MessageBox(strInf,"��ʾ",MB_ICONEXCLAMATION);
			return FALSE;
		}
		//
		strSQL.Format("UPDATE MENDRECORD SET CR_DateTime = to_Date('%s','yyyy-mm-dd HH24:mi:ss'), CR_Asker = '%s',CR_Watcher = '%s',CR_Content = '%s' WHERE T_Order = %s",
			strDateTime,m_strAsker,m_strWatcher,m_strContent,m_strOrder);	
	}
	//ִ��SQL���
	m_adoLogConnect.Execute(strSQL);
	//ˢ�¼�¼��
	//m_adoLogSet = m_adoLogConnect.Execute("SELECT * FROM MENDRECORD ORDER BY T_Order");
	UpdateListCtrl();
	//----------------------------------------------------------------------------------
	if( m_iKind == 0)//���������Ǽǣ������IDC_ORDER�ؼ���
	{
		//����IDC_ORDER�ؼ�
		//UpdateOrderEdit();
	}
	return TRUE;
}

//����ɾ����ť
void CConstructRequest::OnBDelete() 
{
	UpdateData(TRUE);
	//-----------------------------------------------------
	//�õ�LISTCTRL��ѡ����кţ�Based Zero��
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	
	if ( nItem == -1)
	{
		MessageBox("�������б����ѡ��Ҫɾ����!","��ʾ",MB_OK | MB_ICONINFORMATION);
		return;
	}
	if( MessageBox("ȷ��Ҫɾ��ѡ�еļ�¼�𣿲��ɻָ���","����",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDNO)
	{
		return;
	}
	
	//�õ�δɾ��ǰ��������
	m_adoLogSet = m_adoLogConnect.Execute("SELECT MAX(T_Order) AS T_Order FROM MENDRECORD");
	int maxOrder;
	m_adoLogSet.GetCollect("T_ORDER",maxOrder);

	//�õ�Ҫɾ���ļ�¼��Ų�ɾ��ָ���ļ�¼
	CString strSQL;
	CString strCurOrder = m_ctrlList.GetItemText(nItem,0);
	strSQL.Format("DELETE FROM MendRecord WHERE T_Order = %s", strCurOrder);
	m_adoLogConnect.Execute( strSQL );

	//��ɾ���ļ�¼��������¼���ʱ,
	//��������ļ�¼������Ϊ��ɾ���ļ�¼�����
	if ( maxOrder != atoi(strCurOrder) )
	{
		strSQL.Format("UPDATE MENDRECORD SET T_Order = %s WHERE T_Order = %d",strCurOrder,maxOrder);
		m_adoLogConnect.Execute(strSQL);
	}
	
	//���������ʾ�ؼ���Ȼ�����LISTCTRL
	//InitRecContent();
	//m_adoLogSet = m_adoLogConnect.Execute("SELECT * FROM MENDRECORD ORDER BY T_Order");
	UpdateListCtrl();
	//������ſؼ�
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
//��������˺�ֵ��Ա�ؼ�������
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
//�༭��������
void CConstructRequest::OnBRequestCommand() 
{
	UpdateData();
	
	if ( !AddNewData() )
	{
		return;
	}
	//����1����Ӧ�����
	//����2��ʩ������(��Ӧ��ͨ������������)
	WORD wComKind;
	if ( m_iKind == 0 )//m_iKind == 0��˵��Ҫ�༭��������
	{
		wComKind = DISPHKINDCLOSE;
	}
	else//�༭��ͨ����
	{
		wComKind = DISPHKINDOPEN;
	}

	//this->ShowWindow(SW_HIDE);
	OnOK();

	//---------------------------------------------
	ASSERT( atoi(m_strOrder) != 0 );


	//���õ�������Ի�������������Ի���
	m_pMainFrame->m_pDdmlxdDlg->SetOrder(atoi(m_strOrder));	//��¼��
	m_pMainFrame->m_pDdmlxdDlg->SetComKind(wComKind);//��������
	m_pMainFrame->m_pDdmlxdDlg->SetRCDateTime(m_timeDateTime);//���Ӧʩ������ĵ�����ʱ��
	m_pMainFrame->m_pDdmlxdDlg->SetChecked(FALSE);//δ���
	m_pMainFrame->m_pDdmlxdDlg->ShowDetailedInf();
//	m_pMainFrame->m_pDdmlxdDlg->ShowResponse();

	m_pMainFrame->m_pDdmlxdDlg->ShowWindow(SW_SHOW);
	//----------------------------------------------
	
}


//˫��LISTCTRL
void CConstructRequest::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_byConKind != 0 || m_byOrder != 0 )
		//���鿴��ά���ն˷���������ʱ�������κβ���
	{
		return;
	}
	
	//UpdateData(TRUE);
	GetDlgItem(IDC_NEWREGISTER)->EnableWindow(false);
	//�õ�LISTCTRL��˫����
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	if ( nItem == -1)
	{
		return;
	}
	//�õ�ѡ���¼�����
	CString strOrder = m_ctrlList.GetItemText(nItem,0);
	CString strSQL;
	//�����ݿ����ҳ����Ϊָ��ֵ��һ���¼
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

//���� m_byConKind, m_byOrder ��ֵ��ʾ��Ӧ����Ϣ
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
		if( m_byConKind == CONSTREGISTER )//��ʾ�Ǽ�����
		{
			m_iKind = 0;
			m_strEdit1 = "��";
			//m_strEdit2 = "ʩ �� �� �� �� �� �� ��";
			
			
			m_adoLogSet.GetCollect("R_DateTime",oleDateTime);
			m_ctrlDateTime.SetTime(oleDateTime);
			m_adoLogSet.GetCollect("R_Asker",m_strAsker);
			m_adoLogSet.GetCollect("R_Watcher",m_strWatcher);
			m_adoLogSet.GetCollect("R_MendKind",iTemp);
			m_ctrlMendKind.SetCurSel(iTemp-1);
			m_adoLogSet.GetCollect("R_ConsumeTime",m_iConsumeTime);
			m_adoLogSet.GetCollect("R_Content",m_strContent);
		}
		else//��ʾ��������
		{
			m_iKind = 1;
			m_strEdit1 = "���ǵ�";
			//m_strEdit2 = "ʩ �� �� �� �� �� �� ��";
			
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
	if(m_byConKind == 0 && m_byOrder == 0 )//˵������ά�޹���վ��дʩ������
	{
		UpdateOrderEdit();
		
		//LIST
		//m_ctrlList.EnableWindow(TRUE);

		//������ѡ��ť
		GetDlgItem(IDC_REGISTER)->EnableWindow(TRUE);
		GetDlgItem(IDC_CLOSEREG)->EnableWindow(TRUE);
		
		//ɾ����ť�����水ť
		GetDlgItem(IDC_DELETE)->EnableWindow(TRUE);
		GetDlgItem(IDC_NEWREGISTER)->EnableWindow(TRUE);
		
		//��վ
		GetDlgItem(IDC_STATION)->EnableWindow(TRUE);

		//��������ֵ����
		((CEdit*)GetDlgItem(IDC_ASKER) )->SetReadOnly(FALSE);
		((CEdit*)GetDlgItem(IDC_WATCHER))->SetReadOnly(FALSE);
		
		//����ʱ���ʩ������
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(true);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(true);
	}

	else
	{
		//LIST
		//m_ctrlList.ShowWindow(SW_HIDE);

		//������ѡ��ť
		GetDlgItem(IDC_REGISTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLOSEREG)->EnableWindow(FALSE);

		//ɾ����ť�����水ť
		GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_NEWREGISTER)->EnableWindow(FALSE);
		
		//��վ
		GetDlgItem(IDC_STATION)->EnableWindow(FALSE);
	
		//��������ֵ����
		((CEdit*)GetDlgItem(IDC_ASKER))->SetReadOnly(TRUE);
		((CEdit*)GetDlgItem(IDC_WATCHER))->SetReadOnly(TRUE);

		if( m_byConKind == CONSTREGISTER )//�Ǽ�
		{
			//����ʱ���ʩ������
			GetDlgItem(IDC_CONSUMETIME)->EnableWindow(true);
			GetDlgItem(IDC_MENDKIND)->EnableWindow(true);
		}
		else//����
		{
			//����ʱ���ʩ������
			GetDlgItem(IDC_CONSUMETIME)->EnableWindow(false);
			GetDlgItem(IDC_MENDKIND)->EnableWindow(false);
		}
	}
}

