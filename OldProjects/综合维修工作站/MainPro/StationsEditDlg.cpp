// StationsEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "StationsEditDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStationsEditDlg dialog
extern CMaintainApp theApp;

CStationsEditDlg::CStationsEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStationsEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStationsEditDlg)
	m_strAllStation = _T("");
	m_strCurStation = _T("");
	//}}AFX_DATA_INIT
}


void CStationsEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStationsEditDlg)
	DDX_Control(pDX, IDC_LISTCURSTATION, m_ctrlCurStation);
	DDX_Control(pDX, IDC_LISTALLSTATION, m_ctrlAllStation);
	DDX_LBString(pDX, IDC_LISTALLSTATION, m_strAllStation);
	DDX_LBString(pDX, IDC_LISTCURSTATION, m_strCurStation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStationsEditDlg, CDialog)
	//{{AFX_MSG_MAP(CStationsEditDlg)
	ON_BN_CLICKED(IDC_SATION_ADD, OnSationAdd)
	ON_BN_CLICKED(IDC_STATION_DELETE, OnStationDelete)
	ON_BN_CLICKED(IDC_STATION_ADDALL, OnStationAddall)
	ON_BN_CLICKED(IDC_STATION_DELALL, OnStationDelall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStationsEditDlg message handlers

void CStationsEditDlg::OnSationAdd() 
{
	int i = m_ctrlAllStation.GetCurSel();
	CString strTemp;
	if ( i == -1)
	{
		MessageBox("��������ߵ��б���е���Ҫ��ӵĳ�վ��","��ʾ",MB_ICONINFORMATION);
		return;
	}
	//-------------------------------------------
	m_ctrlAllStation.GetText(i,strTemp);
	//����վû�б����ʱ������ǰ��վ������
	if ( m_ctrlCurStation.FindString(-1,strTemp) == LB_ERR )
	{
		m_ctrlCurStation.AddString(strTemp);
	}
	
}

void CStationsEditDlg::OnStationDelete() 
{
	int i = m_ctrlCurStation.GetCurSel();
	if ( i == -1 )
	{
		MessageBox("�������ұߵ��б���е���Ҫɾ���ĳ�վ��","��ʾ",MB_ICONINFORMATION);
		return;
	}
	//------------------------
	m_ctrlCurStation.DeleteString(i);
}

void CStationsEditDlg::OnStationAddall() 
{
	m_ctrlCurStation.ResetContent();

	for ( int i = 0; i<m_ctrlAllStation.GetCount(); i++)
	{
		CString strTemp;
		m_ctrlAllStation.GetText(i,strTemp);
		m_ctrlCurStation.AddString(strTemp);
	}
}

void CStationsEditDlg::OnStationDelall() 
{
	m_ctrlCurStation.ResetContent();	
}

void CStationsEditDlg::OnOK() 
{
	for ( int i = 0; i<m_ctrlCurStation.GetCount(); i++)
	{
		CString strTemp;
		m_ctrlCurStation.GetText(i,strTemp);
		if (i<m_ctrlCurStation.GetCount()-1)
		{
			m_strStations =m_strStations + strTemp + ',';
		}
		else
		{
			m_strStations =m_strStations + strTemp;
		}
	}
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CStationsEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//
	m_pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//������վ��������ListBox��
	const CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	for ( int i = 0; i<pStationInf->GetLength(); i++)
	{
		m_ctrlAllStation.AddString( pStationInf->GetAt(i)->strName);
	}
	//----------------------------------------------------------------
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CStationsEditDlg::GetStations()
{
	return m_strStations;
}
