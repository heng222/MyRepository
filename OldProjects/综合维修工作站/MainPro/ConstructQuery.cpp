// ConstructQuery.cpp : implementation file
//

#include "stdafx.h"
#include "ConstructQuery.h"
#include "MainFrm.h"
#include "Maintain.h"
#include ".\constructquery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConstructQuery dialog
//extern CMaintainApp theApp;

CConstructQuery::CConstructQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CConstructQuery::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstructQuery)
	m_oleRDateTime = COleDateTime::GetCurrentTime();
	m_bCheck1 = FALSE;
	m_bCheck2 = FALSE;
	m_bCheck3 = FALSE;
	m_strComAsker = _T("");
	m_strComWatcher = _T("");
	m_bCheck4 = FALSE;
	m_strAskStation = _T("");
	m_iKindReg = -0;
	m_iKindCom = -0;
	m_strAsker = _T("");
	m_strAskTime = _T("");
	m_strChecker = _T("");
	m_strCheckTime = _T("");
	m_strComContent = _T("");
	m_strComOrder = _T("");
	m_strComTitle = _T("");
	m_iConsumeTime = 0;
	m_strCopyFor = _T("");
	m_strDispatcher = _T("");
	m_strOrgReceive = _T("");
	m_strOrgSend = _T("");
	m_strRegContent = _T("");
	m_strRegTitle = _T("��        ��");
	m_strSendTime = _T("");
	m_strStations = _T("");
	m_strWatcher = _T("");
	m_strMendKind = _T("");
	m_strStation = _T("");
	//}}AFX_DATA_INIT
}


void CConstructQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstructQuery)
	DDX_Control(pDX, IDC_STATICMENDKIND, m_ctrlSMendKind);
	DDX_Control(pDX, IDC_STATICCONSUMETIME, m_ctrlSConsumeTime);
	DDX_Control(pDX, IDC_CONSUMETIME, m_ctrlConsumeTime);
	DDX_Control(pDX, IDC_MENDKIND, m_ctrlMendKind);
	DDX_Control(pDX, IDC_ASKSTATION, m_ctrlAskStation);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Control(pDX, IDC_CONDATETIME, m_ctrlRDateTime);
	DDX_Control(pDX, IDC_COMBORWATER, m_ctrlRWatcher);
	DDX_Control(pDX, IDC_COMBOASKER, m_ctrlRAsker);
	DDX_DateTimeCtrl(pDX, IDC_CONDATETIME, m_oleRDateTime);
	DDX_Check(pDX, IDC_CHECK1, m_bCheck1);
	DDX_Check(pDX, IDC_CHECK2, m_bCheck2);
	DDX_Check(pDX, IDC_CHECK3, m_bCheck3);
	DDX_CBString(pDX, IDC_COMBOASKER, m_strComAsker);
	DDX_CBString(pDX, IDC_COMBORWATER, m_strComWatcher);
	DDX_Check(pDX, IDC_CHECK4, m_bCheck4);
	DDX_CBString(pDX, IDC_ASKSTATION, m_strAskStation);
	DDX_Radio(pDX, IDC_RREG, m_iKindReg);
	DDX_Radio(pDX, IDC_RCCOMAND, m_iKindCom);
	DDX_Text(pDX, IDC_ASKER, m_strAsker);
	DDX_Text(pDX, IDC_ASKTIME, m_strAskTime);
	DDX_Text(pDX, IDC_CHECKER, m_strChecker);
	DDX_Text(pDX, IDC_CHECKTIME, m_strCheckTime);
	DDX_Text(pDX, IDC_COMCONTENT, m_strComContent);
	DDX_Text(pDX, IDC_COMORDER, m_strComOrder);
	DDX_Text(pDX, IDC_COMTITLE, m_strComTitle);
	DDX_Text(pDX, IDC_CONSUMETIME, m_iConsumeTime);
	DDV_MinMaxInt(pDX, m_iConsumeTime, 0, 9999);
	DDX_Text(pDX, IDC_COPYFOR, m_strCopyFor);
	DDX_Text(pDX, IDC_DISPATCHER, m_strDispatcher);
	DDX_Text(pDX, IDC_ORGRECEIVE, m_strOrgReceive);
	DDX_Text(pDX, IDC_ORGSEND, m_strOrgSend);
	DDX_Text(pDX, IDC_REGONTENT, m_strRegContent);
	DDX_Text(pDX, IDC_REGTITLE, m_strRegTitle);
	DDX_Text(pDX, IDC_SENDTIME, m_strSendTime);
	DDX_Text(pDX, IDC_STATIONS, m_strStations);
	DDX_Text(pDX, IDC_WATCHER, m_strWatcher);
	DDX_Text(pDX, IDC_MENDKIND, m_strMendKind);
	DDX_Text(pDX, IDC_STATION, m_strStation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstructQuery, CDialog)
	//{{AFX_MSG_MAP(CConstructQuery)
	ON_BN_CLICKED(IDC_QUERY, OnBQuery)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_CLEAR, OnBClear)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_SAVE, OnBSave)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_RREG, OnRadioReg)
	ON_BN_CLICKED(IDC_RCCOMAND, OnRadioCcomand)
	ON_BN_CLICKED(IDC_RCREG, OnRadioReg)
	ON_BN_CLICKED(IDC_ROCOMMAND, OnRadioCcomand)
	//}}AFX_MSG_MAP
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_CONDATETIME, OnDtnDatetimechangeCondatetime)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConstructQuery message handlers

BOOL CConstructQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	
	//ȷ��ϵͳ��ǰ·��
	char cTemp[MAX_PATH];
	CString strExePath;
	GetCurrentDirectory(MAX_PATH,cTemp);
	strExePath.Format("%s\\",cTemp);
	
	
	//��ȡ��Ϣ
	m_MendTemplate.ReadFile(strExePath + MENDTEMPLATEPATHNAME);
	
	
	//���ӵ����ݿ�
	CString strDBDataSource,strDBUserID,strDBPassword;
	//��ȡ���ݿ����
	GetPrivateProfileString("Database","DataSource",0,cTemp,MAX_PATH,strExePath+STATIONINFOPATHNAME);
	strDBDataSource = cTemp;
	GetPrivateProfileString("Database","UserID",0,cTemp,MAX_PATH,strExePath+STATIONINFOPATHNAME);
	strDBUserID = cTemp;
	GetPrivateProfileString("Database","Password",0,cTemp,MAX_PATH,strExePath+STATIONINFOPATHNAME);
	strDBPassword = cTemp;
	if ( !m_adoLogConnect.ConnectOracle(strDBDataSource,strDBUserID,strDBPassword))
	{		
		MessageBox("�����޷����ӵ����ݿ���������޷�ִ�д˲���!","����",MB_ICONERROR);
		OnCancel();
		return FALSE;
	}
	
	
	//------------------------------------------
	m_pMainFrame = ((CMainFrame*)AfxGetMainWnd());

	
	//�����еı���
	m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlList.SetHeadings( _T("���,60;����վ,80;�Ǽ�ʱ��,150;ʩ��������,100;�Ǽ�ֵ��Ա,100;ʩ������ʱ��(��),120;ʩ������,80;�Ǽ�����,300;���������,100; ����������ʱ��,150; ��������Ա,100;����վ�б�,100; �������,80;�������,80;�����,80;���ʱ��,100;����Ŀ��,100;����,100;��������,300;����ʱ��,150; ����������,100; ����ֵ��Ա,100; ��������,300;��ͨ�����,100; ����ͨ����ʱ��,150; ��ͨ����Ա,100; ����վ�б�,100; �������,80;�������,80;�����,80;���ʱ��,100;����Ŀ��,100;����,100;��ͨ����,300") );
	m_ctrlList.LoadColumnInfo();

	//
	//
	//UpdateListCtrl("SELECT * FROM MENDRECORD");
	UpdateComboBox();
	////////////////////////////////////////////////

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//========================================================================
//=========================================================================
//�õ�ǰ�ļ�¼��(m_adoLogSet)����LISTCTRL�ؼ�
void CConstructQuery::UpdateListCtrl(CString strSQL)
{
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	//
	m_adoLogSet = m_adoLogConnect.Execute(strSQL);
	m_ctrlList.DeleteAllItems();

	
	CString strGroup[50];
	CString strTemp;
	//�Ӽ�¼����ȡ����¼�����뵽LISTCTRL��
	m_adoLogSet.MoveFirst();
	while(!m_adoLogSet.IsEOF())
	{
		int i = 0,iTemp;

		m_adoLogSet.GetCollect("T_ORDER",iTemp);
		strGroup[i++].Format("%d",iTemp);

		m_adoLogSet.GetCollect("T_STATION",iTemp);
		strGroup[i++].Format("%s",pStationInf->GetName(iTemp));
		

		m_adoLogSet.GetCollect("R_DATETIME", strGroup[i++] );
		m_adoLogSet.GetCollect("R_ASKER",strGroup[i++]);
		m_adoLogSet.GetCollect("R_WATCHER" ,strGroup[i++]);
		m_adoLogSet.GetCollect("R_ConsumeTime" ,iTemp);
		strGroup[i++].Format("%d",iTemp);
		m_adoLogSet.GetCollect("R_MendKind" ,iTemp);
		strGroup[i++].Format("%s",m_MendTemplate.GetName(iTemp));
		m_adoLogSet.GetCollect("R_CONTENT",strGroup[i++]);
		
		
		m_adoLogSet.GetCollect("CC_ORDER",strGroup[i++]);
		m_adoLogSet.GetCollect("CC_DATETIME",strGroup[i++]);
		m_adoLogSet.GetCollect("CC_DISPATCHER" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CC_STATIONS", strTemp );
		strGroup[i++] = pStationInf->CovNumToName(strTemp);	//����վ���б�ת���ɳ�վ�����б�
		m_adoLogSet.GetCollect("CC_ORGSEND" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CC_ORGRECEIVE" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CC_CHECKER" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CC_CHECKTIME" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CC_COPYFOR" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CC_TITLE" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CC_CONTENT"  ,strGroup[i++]);
		
		
		m_adoLogSet.GetCollect("CR_DATETIME" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CR_ASKER" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CR_WATCHER" ,strGroup[i++]);
		m_adoLogSet.GetCollect("CR_CONTENT",strGroup[i++]);
		
		
		m_adoLogSet.GetCollect("OC_ORDER" ,strGroup[i++]);
		m_adoLogSet.GetCollect("OC_DATETIME" ,strGroup[i++]);
		m_adoLogSet.GetCollect("OC_DISPATCHER", strGroup[i++] );
		m_adoLogSet.GetCollect("OC_STATIONS", strTemp );
		strGroup[i++] = pStationInf->CovNumToName(strTemp);	//����վ���б�ת���ɳ�վ�����б�
		m_adoLogSet.GetCollect("OC_ORGSEND" ,strGroup[i++]);
		m_adoLogSet.GetCollect("OC_ORGRECEIVE" ,strGroup[i++]);
		m_adoLogSet.GetCollect("OC_CHECKER" ,strGroup[i++]);
		m_adoLogSet.GetCollect("OC_CHECKTIME" ,strGroup[i++]);
		m_adoLogSet.GetCollect("OC_COPYFOR" ,strGroup[i++]);
		m_adoLogSet.GetCollect("OC_TITLE" ,strGroup[i++]);
		m_adoLogSet.GetCollect("OC_CONTENT", strGroup[i++] );
		
		//��Ӽ�¼
		m_ctrlList.AddItem(strGroup[0],
			strGroup[1],	strGroup[2],	strGroup[3],	strGroup[4],	strGroup[5],	strGroup[6],	strGroup[7],
			strGroup[8],	strGroup[9],	strGroup[10],	strGroup[11],	strGroup[12],
			strGroup[13],	strGroup[14],	strGroup[15],	strGroup[16],
			strGroup[17],	strGroup[18],	strGroup[19],	strGroup[20],	strGroup[21],	strGroup[22],	strGroup[23],
			strGroup[24],	strGroup[25],	strGroup[26],	strGroup[27],	strGroup[28],	strGroup[29],	strGroup[30],
			strGroup[31],	strGroup[32],	strGroup[33],	strGroup[34]);
		//---
		m_adoLogSet.MoveNext();
	}
}
//�����ݿ���ȡ��T_Station,R_ASKER��R_WATCHER�У������뵽COMBOBOX��
void CConstructQuery::UpdateComboBox()
{
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	CString strGroup;
	//���R_Asker
	m_ctrlRAsker.ResetContent();
	m_adoLogSet = m_adoLogConnect.Execute("SELECT  R_Asker FROM MENDRECORD GROUP BY R_Asker");
	m_adoLogSet.MoveFirst();
	while(!m_adoLogSet.IsEOF())
	{
		m_adoLogSet.GetCollect("R_Asker",strGroup);
		//��Ӽ�¼
		if ( strGroup.IsEmpty() == FALSE )
		{
			m_ctrlRAsker.AddString(strGroup);
		}
		
		m_adoLogSet.MoveNext();
	}

	//���R_Watcher
	m_ctrlRWatcher.ResetContent();
	m_adoLogSet = m_adoLogConnect.Execute("SELECT  R_Watcher FROM MENDRECORD GROUP BY R_Watcher");
	m_adoLogSet.MoveFirst();
	while(!m_adoLogSet.IsEOF())
	{
		m_adoLogSet.GetCollect("R_WATCHER" ,strGroup);
		//��Ӽ�¼
		if ( strGroup.IsEmpty() == FALSE )
		{
			m_ctrlRWatcher.AddString(strGroup);
		}
		
		
		m_adoLogSet.MoveNext();
	}

	//���T_Station
	m_ctrlAskStation.ResetContent();
	m_adoLogSet = m_adoLogConnect.Execute("SELECT  T_Station FROM MENDRECORD GROUP BY T_Station");
	m_adoLogSet.MoveFirst();
	while(!m_adoLogSet.IsEOF())
	{
		m_adoLogSet.GetCollect("T_Station" ,strGroup);
		//��Ӽ�¼
		if ( strGroup.IsEmpty() == FALSE )
		{
			m_ctrlAskStation.AddString(pStationInf->GetName(atoi(strGroup)));
		}
				
		//
		m_adoLogSet.MoveNext();
	}
	///////////////////////////////////////////////
	if( m_ctrlAskStation.GetCount() > -1 )
	{
		m_ctrlAskStation.SetCurSel(0);
	}
	if(m_ctrlRAsker.GetCount() > -1 )
	{
		m_ctrlRAsker.SetCurSel(0);
	}
	if(m_ctrlRWatcher.GetCount() > -1 )
	{
		m_ctrlRWatcher.SetCurSel(0);
	}
}


void CConstructQuery::OnBQuery() 
{
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	//���LISTCTRL�ؼ��е�����Ԫ��
	m_ctrlList.DeleteAllItems();

	//-------------------------
	UpdateData();
	//-------------------------
	CString strSQL = "SELECT * FROM MENDRECORD ";
	BOOL bHaveCondition = false;
	
	if(m_bCheck1)
	{
		CString strTemp;

		strTemp = m_oleRDateTime.Format("%Y-%m-%d");
		strSQL = strSQL + "WHERE to_char(R_DateTime,'yyyy-mm-dd') = '" + strTemp + "'";
		bHaveCondition = true;
	}

	if(m_bCheck2 && !m_strComAsker.IsEmpty() )
	{
		if(bHaveCondition)
		{
			strSQL =strSQL + "AND R_ASKER = '" + m_strComAsker + "'";
		}
		else
		{
			strSQL = strSQL + "WHERE R_ASKER = '" + m_strComAsker + "'";
		}
		bHaveCondition = true;
	}
	
	if(m_bCheck3 && !m_strComWatcher.IsEmpty() )
	{
		if( bHaveCondition)
		{
			strSQL = strSQL + "AND R_WATCHER = '" + m_strComWatcher + "'";
		}
		else
		{
			strSQL =strSQL + "WHERE R_WATCHER = '" + m_strComWatcher + "'";
		}
		bHaveCondition = true;
	}
	
	if(m_bCheck4 && !m_strAskStation.IsEmpty() )
	{
		CString strTemp;
		if( bHaveCondition)
		{
			strTemp.Format(" AND T_Station = '%d' ",pStationInf->GetStationID(m_strAskStation));
			strSQL = strSQL + strTemp;
		}
		else
		{
			strTemp.Format( " WHERE T_Station = '%d' ",pStationInf->GetStationID(m_strAskStation) );
			strSQL =strSQL + strTemp;
		}
		bHaveCondition = true;
	}
	//--------------------------------------------
	strSQL += " ORDER BY T_Order";
	
	UpdateListCtrl(strSQL);
}

//˫��LIST��һ��
void CConstructQuery::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ShowDetailedInf();
	*pResult = 0;
}


void CConstructQuery::OnBClear() 
{/*
//	m_strCCAsker.Empty();
	m_strCCStations.Empty();
	m_strCCDispatcher.Empty();
	m_strCCOrder.Empty();
//	m_strCCWatcher.Empty();
	m_strCCContent.Empty();
	m_strCCDateTime.Empty();

	m_strCRAsker.Empty();
	m_strCRContent.Empty();
	m_strCRWatcher.Empty();
	m_strCRDateTime.Empty();

//	m_strOCAsker.Empty();
	m_strOCContent.Empty();
	m_strOCDispatcher.Empty();
	m_strOCOrder.Empty();
	m_strOCDateTime.Empty();
	m_strOCStations.Empty();
//	m_strOCWatcher.Empty();

	m_strRAsker.Empty();
	m_strRContent.Empty();
	m_strRWatcher.Empty();
	m_strRDateTime.Empty();
	//
	UpdateData(false);
	//
	*/
	m_ctrlList.DeleteAllItems();
}

void CConstructQuery::OnCheck1() 
{
	UpdateData();
	if(m_bCheck1)
	{
		m_ctrlRDateTime.EnableWindow();
	}
	else
	{
		m_ctrlRDateTime.EnableWindow(false);
	}
	
}
void CConstructQuery::OnCheck4() 
{
	UpdateData();
	if(m_bCheck4)
	{
		m_ctrlAskStation.EnableWindow();
	}
	else
	{
		m_ctrlAskStation.EnableWindow(false);
	}
}
void CConstructQuery::OnCheck2() 
{
	UpdateData();
	if(m_bCheck2)
	{
		m_ctrlRAsker.EnableWindow();
	}
	else
	{
		m_ctrlRAsker.EnableWindow(false);
	}		
}

void CConstructQuery::OnCheck3() 
{
	UpdateData();
	if(m_bCheck3)
	{
		m_ctrlRWatcher.EnableWindow();
	}
	else
	{
		m_ctrlRWatcher.EnableWindow(false);
	}
	
}

//����ɾ����ť
//DEL void CConstructQuery::OnBDelete() 
//DEL {
//DEL 	//�õ�LISTCTRL��ѡ����кţ�Based Zero��
//DEL 	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
//DEL 	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
//DEL 	//
//DEL 	
//DEL 	if ( nItem == -1)
//DEL 	{
//DEL 		MessageBox("�������б����ѡ��Ҫɾ������!","��ʾ",MB_OK | MB_ICONINFORMATION);
//DEL 		return;
//DEL 	}
//DEL 	if( MessageBox("ȷ��Ҫɾ��ѡ�еļ�¼�𣿲��ɻָ���","����",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDNO)
//DEL 	{
//DEL 		return;
//DEL 	}
//DEL 	//
//DEL 	CString strOrder = m_ctrlList.GetItemText(nItem,0);
//DEL 	CString strSQL;
//DEL 	//ִ��ɾ����¼��SQL���
//DEL 	strSQL.Format("DELETE FROM MendRecord WHERE T_Order = %s", strOrder);
//DEL 	m_adoLogConnect.Execute( strSQL );
//DEL 	//
//DEL 	m_adoLogSet = m_adoLogConnect.Execute("SELECT * FROM MENDRECORD ORDER BY T_Order");
//DEL 	UpdateListCtrl();
//DEL }

//�������水ť
void CConstructQuery::OnBSave() 
{
	COleDateTime oleDateTime = COleDateTime::GetCurrentTime();
	CString strFileName;
	strFileName.Format("%d��%d��%d��%d���ѯ���",oleDateTime.GetYear(),
		oleDateTime.GetMonth(),oleDateTime.GetDay(),oleDateTime.GetHour());
	//
	CFileDialog fDlg(false,"txt",strFileName,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Text Files (*.txt)|*.txt|All Files (*.*)|*.*|");

	if(fDlg.DoModal() == IDOK)
	{
		CStdioFile sFile;
		try
		{
			CFileException e;
			if(!sFile.Open(fDlg.GetPathName(),CFile::modeCreate | CFile::modeWrite,&e))
			{
				throw(&e);
			}
		}
		catch(CFileException* e)
		{
			if(e->m_cause == 3)
			{
				MessageBox("�ļ����Ƿ���\n������ָ���ļ���!","����",MB_OK | MB_ICONEXCLAMATION);
			}
			else
			{
				e->ReportError();
				MessageBox("�޷�����ָ�����ļ�!","����",MB_OK | MB_ICONERROR);
			}
			e->Delete();
			return;
		}

		//
		UpdateData();
		CString strWriteLine;
		sFile.WriteString("[��ѯ����]\n");
		if(!m_bCheck1 && !m_bCheck2 && !m_bCheck3)
		{
			sFile.WriteString("��ѯ���м�¼\n");
		}
		else
		{
			if(m_bCheck1)
			{
				sFile.WriteString(m_oleRDateTime.Format("ʩ������ = %Y-%m-%d"));
			}
			if(m_bCheck4)
			{
				strWriteLine.Format("����վ = %s\n",m_strAskStation);
			}
			if(m_bCheck2)
			{
				strWriteLine.Format("ʩ�������� =  %s\n",m_strComAsker);
				sFile.WriteString(strWriteLine);
			}
			if(m_bCheck3)
			{
				strWriteLine.Format("ʩ��ֵ��Ա =  %s\n",m_strComWatcher);
				sFile.WriteString(strWriteLine);
			}
		}
		sFile.WriteString("\n");
		strWriteLine.Format( "[���ҵ� %d ����¼]\n\n", m_ctrlList.GetItemCount() );
		sFile.WriteString(strWriteLine);

		//----------------------
		for ( int i = 0; i<m_ctrlList.GetItemCount(); i++)
		{
			strWriteLine.Format( "[�� %d ����¼]\n", i+1 );
			sFile.WriteString(strWriteLine);
			//----------------------------------------------------------------
			for ( int j = 0; j<m_ctrlList.GetHeaderCtrl()->GetItemCount(); j++)
			{
				switch(j)
				{
				case 0:
					strWriteLine.Format("%2d���������     =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 1:
					strWriteLine.Format("%2d������վվ��   =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;
				
				case 2:
					strWriteLine.Format("%2d���Ǽ�ʱ��     =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 3:
					strWriteLine.Format("%2d���Ǽ�������   =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 4:
					strWriteLine.Format("%2d���Ǽ�ֵ��Ա   =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 5:
					strWriteLine.Format("%2d������ʱ��     =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 6:
					strWriteLine.Format("%2d��ʩ������     =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 7:
					strWriteLine.Format("%2d���Ǽ�����     =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 8:
					strWriteLine.Format("%2d�����������   =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 9:
					strWriteLine.Format("%2d����������ʱ�� =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 10:
					strWriteLine.Format("%2d����������Ա   =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 11:
					strWriteLine.Format("%2d������վ       =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 12:
					strWriteLine.Format("%2d����������     =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 13:
					strWriteLine.Format("%2d������ʱ��     =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 14:
					strWriteLine.Format("%2d������������   =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 15:
					strWriteLine.Format("%2d������ֵ��Ա   =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;


				case 16:
					strWriteLine.Format("%2d����������     =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 17:
					strWriteLine.Format("%2d����ͨ�����   =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 18:
					strWriteLine.Format("%2d����ͨ����ʱ�� =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 19:
					strWriteLine.Format("%2d����ͨ����Ա   =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;

				case 20:
					strWriteLine.Format("%2d����ͨ����     =  %s\n",j+1,m_ctrlList.GetItemText(i,j));
					break;
				}
				sFile.WriteString(strWriteLine);
			}//-----------------------------------
			sFile.WriteString("\n\n");
		}
		//
		sFile.Close();
	}
}

void CConstructQuery::OnRadioReg() 
{
	ShowDetailedInf();	
}

void CConstructQuery::OnRadioCcomand() 
{
	ShowDetailedInf();	
}

//������ʾ��ϸ��Ϣ�����пؼ�
void CConstructQuery::ShowDetailedInf()
{
	UpdateData();
	//
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	//
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	//
	if( nItem >= 0 )
	{
		//�õ���ǰ��¼�����
		CString strSQL;
		strSQL.Format("SELECT * FROM MENDRECORD WHERE T_Order = %s",
			m_ctrlList.GetItemText(nItem,0));
		//�����ݿ��м�����¼��Ϊ��ǰ��¼�ŵ�һ����¼
		m_adoLogSet = m_adoLogConnect.Execute(strSQL);
		//��ʾ��ϸ��Ϣ
		//-------------------------------------------------------------
		int iTemp;
		CString strTemp;
		//Ask Station
		m_adoLogSet.GetCollect("T_Station",iTemp);
		m_strStation = pStationInf->GetName(iTemp);
		
		//
		if ( m_iKindReg == 0 )//��ʾ�Ǽ���Ϣ
		{
			m_adoLogSet.GetCollect("R_DateTime",m_strAskTime);
			m_adoLogSet.GetCollect("R_Asker",m_strAsker);
			m_adoLogSet.GetCollect("R_Watcher",m_strWatcher);
			m_adoLogSet.GetCollect("R_ConsumeTime",m_iConsumeTime);
			
			//��ʾ�ĸ��ؼ�
			m_ctrlConsumeTime.ShowWindow(SW_SHOW   );
			m_ctrlMendKind.ShowWindow(SW_SHOW   );
			m_ctrlSConsumeTime.ShowWindow(SW_SHOW   );
			m_ctrlSMendKind.ShowWindow(SW_SHOW   );
			
			m_adoLogSet.GetCollect("R_MendKind",iTemp);
			m_strMendKind = m_MendTemplate.GetName(iTemp);
			
			m_adoLogSet.GetCollect("R_Content",m_strRegContent);
		}
		else//��ʾ������Ϣ
		{
			m_adoLogSet.GetCollect("CR_DateTime",m_strAskTime);
			m_adoLogSet.GetCollect("CR_Asker",m_strAsker);
			m_adoLogSet.GetCollect("CR_Watcher",m_strWatcher);
			//�����ĸ��ؼ�
			m_ctrlConsumeTime.ShowWindow(SW_HIDE);
			m_ctrlMendKind.ShowWindow(SW_HIDE);
			m_ctrlSConsumeTime.ShowWindow(SW_HIDE);
			m_ctrlSMendKind.ShowWindow(SW_HIDE);
			//m_iConsumeTime = 0;
			//m_strMendKind = "";
			m_adoLogSet.GetCollect("CR_Content",m_strRegContent);
		}
		
		//
		if ( m_iKindCom == 0 )//��ʾ����������Ϣ
		{
			m_adoLogSet.GetCollect("CC_Order",m_strComOrder);
			m_adoLogSet.GetCollect("CC_DateTime",m_strSendTime);
			m_adoLogSet.GetCollect("CC_Dispatcher",m_strDispatcher);
			m_adoLogSet.GetCollect("CC_Stations",strTemp);
			m_strStations = pStationInf->CovNumToName(strTemp);	//��վ���б�ת��Ϊ�����б�
			m_adoLogSet.GetCollect("CC_ORGSEND",m_strOrgSend);
			m_adoLogSet.GetCollect("CC_ORGRECEIVE",m_strOrgReceive);
			m_adoLogSet.GetCollect("CC_Checker",m_strChecker);
			m_adoLogSet.GetCollect("CC_CheckTime",m_strCheckTime);
			m_adoLogSet.GetCollect("CC_CopyFor",m_strCopyFor);
			m_adoLogSet.GetCollect("CC_Title",m_strComTitle);
			m_adoLogSet.GetCollect("CC_Content",m_strComContent);
		}
		else//��ʾ��ͨ������Ϣ
		{
			m_adoLogSet.GetCollect("OC_Order",m_strComOrder);
			m_adoLogSet.GetCollect("OC_DateTime",m_strSendTime);
			m_adoLogSet.GetCollect("OC_Dispatcher",m_strDispatcher);
			m_adoLogSet.GetCollect("OC_Stations",strTemp);
			m_strStations = pStationInf->CovNumToName(strTemp);	//��վ���б�ת��Ϊ�����б�
			m_adoLogSet.GetCollect("OC_ORGSEND",m_strOrgSend);
			m_adoLogSet.GetCollect("OC_ORGRECEIVE",m_strOrgReceive);
			m_adoLogSet.GetCollect("OC_Checker",m_strChecker);
			m_adoLogSet.GetCollect("OC_CheckTime",m_strCheckTime);
			m_adoLogSet.GetCollect("OC_CopyFor",m_strCopyFor);
			m_adoLogSet.GetCollect("OC_Title",m_strComTitle);
			m_adoLogSet.GetCollect("OC_Content",m_strComContent);
		}		
		
	}
	
	//
	UpdateData(false);
}

void CConstructQuery::OnDtnDatetimechangeCondatetime(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    *pResult = 0;
}
