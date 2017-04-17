// WarnNoteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "WarnNoteDlg.h"
#include "AlarmInfo.h"
#include "MainFrm.h"
#include "INI.h"
#include "WarnLogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CWarnNoteDlg dialog


CWarnNoteDlg::CWarnNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWarnNoteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWarnNoteDlg)
	m_strContent = _T("");
	m_strDate = _T("");
	m_strNum = _T("");
	m_strSource = _T("");
	m_strStation = _T("");
	m_strTime = _T("");
	m_strLevel = _T("");
	//}}AFX_DATA_INIT
}


void CWarnNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWarnNoteDlg)
	DDX_Text(pDX, IDC_WARNNOTEDLG_CONTENT, m_strContent);
	DDX_Text(pDX, IDC_WARNNOTEDLG_DATE, m_strDate);
	DDX_Text(pDX, IDC_WARNNOTEDLG_NUM, m_strNum);
	DDX_Text(pDX, IDC_WARNNOTEDLG_SOURCE, m_strSource);
	DDX_Text(pDX, IDC_WARNNOTEDLG_STATION, m_strStation);
	DDX_Text(pDX, IDC_WARNNOTEDLG_TIME, m_strTime);
	DDX_Text(pDX, IDC_WARNNOTEDLG_LEVEL, m_strLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWarnNoteDlg, CDialog)
	//{{AFX_MSG_MAP(CWarnNoteDlg)
	ON_BN_CLICKED(IDC_WARNNOTEDLG_PREV, OnWarnnotedlgPrev)
	ON_BN_CLICKED(IDC_WARNNOTEDLG_NEXT, OnWarnnotedlgNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWarnNoteDlg message handlers

/*========================================================================
	Name:		更新面板上报警内容函数
    ----------------------------------------------------------
	Params:		dwNum	要打开的报警信息的序号
    ----------------------------------------------------------
	Remarks:	
==========================================================================*/
void CWarnNoteDlg::RefreshAll(DWORD dwNum,CTime ct)
{
	CAlarmInfo m_cAlarm;
	AINode aNode;
	if(!m_cAlarm.OpenFile(CAlarmInfo::modeRead,ct.Format("%Y-%m-%d.alm")))
		return;
	if ( m_cAlarm.FindItem(dwNum,aNode ) )
	{
			m_strNum.Format("%d",aNode.m_wOrder);
			m_strDate = aNode.m_time.Format("%Y-%m-%d");
			m_strTime = aNode.m_time.Format(" %H:%M:%S");
			m_strContent = aNode.m_sContent;
			m_strLevel.Format("%d级报警",aNode.m_byLevel);
			m_strSource=aNode.m_sSource;
			m_strStation=aNode.m_sStation;
			//
	}
	m_cAlarm.CloseFile();

	UpdateData(FALSE);
}

void CWarnNoteDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}

BOOL CWarnNoteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_WARNNOTEDLG_PREV))->SetWindowText("↑");
	((CButton*)GetDlgItem(IDC_WARNNOTEDLG_NEXT))->SetWindowText("↓");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWarnNoteDlg::OnWarnnotedlgPrev() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CWarnLogDlg* m_pLogDlg=((CMainFrame*)AfxGetMainWnd())->m_pWarnLogDlg;
	if (m_pLogDlg != NULL && m_pLogDlg->m_bActive && m_pLogDlg->m_nItem >= 0) 
	{
		if (m_pLogDlg->m_nItem > 0) 
		{
			m_pLogDlg->m_nItem-=1;
			CString strN=m_pLogDlg->m_ctrlList.GetItemText(m_pLogDlg->m_nItem,1);
			RefreshAll(atoi(strN),CTime::GetCurrentTime());
			m_pLogDlg->m_ctrlList.SetItemState(m_pLogDlg->m_nItem, LVIS_SELECTED, LVIS_SELECTED);
		}
	}
	else
		RefreshAll(atoi(m_strNum)-1,CTime::GetCurrentTime());
}

void CWarnNoteDlg::OnWarnnotedlgNext() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CWarnLogDlg* m_pLogDlg=((CMainFrame*)AfxGetMainWnd())->m_pWarnLogDlg;
	if (m_pLogDlg != NULL && m_pLogDlg->m_bActive && m_pLogDlg->m_nItem >= 0) 
	{
		if (m_pLogDlg->m_nItem < m_pLogDlg->m_ctrlList.GetItemCount()-1) 
		{
			m_pLogDlg->m_nItem+=1;
			CString strN=m_pLogDlg->m_ctrlList.GetItemText(m_pLogDlg->m_nItem,1);
			RefreshAll(atoi(strN),CTime::GetCurrentTime());
			m_pLogDlg->m_ctrlList.SetItemState(m_pLogDlg->m_nItem, LVIS_SELECTED, LVIS_SELECTED);
		}
	}
	else
		RefreshAll(atoi(m_strNum)+1,CTime::GetCurrentTime());
}

BOOL CWarnNoteDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
/*	int nLen;
	BYTE* pbyTemp;
	
	switch(pMsg->message) {
	case WM_REC_ALARM:
		ShowWindow(SW_HIDE);
		if(((CMainFrame*)AfxGetMainWnd())->m_pWarnLogDlg != NULL)
			((CMainFrame*)AfxGetMainWnd())->m_pWarnLogDlg->ShowWindow(SW_HIDE);
		pbyTemp=(BYTE*)pMsg->wParam;
		nLen=pMsg->lParam;
		TransactAlarmInfo(pbyTemp,nLen);
		delete pbyTemp;
		break;
	default:
		break;
	}
*/
	return CDialog::PreTranslateMessage(pMsg);
}

void CWarnNoteDlg::TransactAlarmInfo(BYTE* pRecBuf,int nLength)
{
	int nSource,nLevel,nStationNo=pRecBuf[1]*256+pRecBuf[0];
	CString strSta,strSou=_T(""),strCon,strComp;
	time_t tT;
	
	CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	if (nStationNo <= 0 || nStationNo > pStationInf->GetLength() )//theApp.m_strlName[0].GetCount()) 
	{
		return;
	}
	strSta = pStationInf->GetName(nStationNo);//theApp.m_strlName[0].GetAt(theApp.m_strlName[0].FindIndex(nStationNo-1));
	nSource=pRecBuf[2];
	CIniReader IniFile(theApp.m_strExePath+"ini\\AlarmInfo.ini");
	strCon.Format("%d",nSource);
	strSou=IniFile.getKeyValue(strCon,"WorkStation Code");
	if (strSou.IsEmpty()) 
	{
		return;
	}

	WORD dw;
	memcpy(&dw,pRecBuf+4,2);
	switch(pRecBuf[3]) {
	case 1://网络通信断
		{
			CString s1,s2;
			s1.Format("%d",dw);
			s2.Format("%d",pRecBuf[6]);
			strCon.Format("%s--%s网络通信断!",IniFile.getKeyValue(s1,"WorkStation Code"),
				IniFile.getKeyValue(s2,"WorkStation Code"));
			break;
		}
	case 2://与联锁机通信断
		strCon="与联锁机通信断!";
		break;
	case 3://与无线通信断
		strCon="与无线通信断!";
		break;
	case 4://无线调度命令发送失败
		strCon="无线调度命令发送失败!";
		break;
	case 5://接车进路预告失败
		strCon.Format("接车进路预告失败! 进路号%d",dw);
		break;
	case 6://列车进路无法建立
		strCon.Format("列车进路无法建立! 进路号%d",dw);
		break;
	case 7://调车进路无法建立
		strCon.Format("调车进路无法建立! 进路号%d",dw);
		break;
	case 8://调车进路超时报警
		strCon.Format("调车进路超时报警! 进路号%d",dw);
		break;
	case 9://信号非正常关闭
		strCon.Format("信号非正常关闭! 信号机号%d",dw);
		break;
	case 10://倒机切换
		if (dw =1) 
			strComp="主机";
		else
			strComp="备机";
		strCon.Format("%s倒机切换!",strComp);
		break;
	default:
		break;
	}
	nLevel=pRecBuf[7];
	memcpy(&tT,pRecBuf+8,4);
	
	CAlarmInfo	m_cAlarm;
	m_cAlarm.OpenFile();
	AINode sNode;
	int nNum=m_cAlarm.GetTotalNumber()+1;
	sNode.m_wOrder = nNum;
	
	sNode.m_sStation = strSta;
	sNode.m_time = tT;
	sNode.m_sContent = strCon;
	sNode.m_byLevel = nLevel;
	sNode.m_sSource = strSou;
	//
	m_cAlarm.Add(sNode);
	m_cAlarm.CloseFile();

	RefreshAll(nNum,CTime::GetCurrentTime());
	ShowWindow(SW_SHOW);
}
