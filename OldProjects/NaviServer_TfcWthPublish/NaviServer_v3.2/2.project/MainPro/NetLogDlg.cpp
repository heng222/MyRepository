// NetLogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NaviServer.h"
#include "NetLogDlg.h"
#include "GlobalMacro.h"


// CNetLogDlg 对话框

IMPLEMENT_DYNAMIC(CNetLogDlg, CDialog)
CNetLogDlg::CNetLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetLogDlg::IDD, pParent)
{
    m_NetLogMgr.SetMode(CAppLogMgr::ELM_READONLY);
}

CNetLogDlg::~CNetLogDlg()
{
}

void CNetLogDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_NL, m_ctrlNLList);
    DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrlDateTime);
    DDX_Control(pDX, IDC_CMB_EVENT, m_ctrlCmbEvent);
    DDX_Control(pDX, IDC_CMB_ADDRESS, m_ctrlCmbIPAddr);
    DDX_Control(pDX, IDC_CHECK2, m_ctrlEventCheck);
    DDX_Control(pDX, IDC_CHECK3, m_ctrlIPAddrCheck);
}


BEGIN_MESSAGE_MAP(CNetLogDlg, CDialog)
    ON_CBN_SELCHANGE(IDC_CMB_ADDRESS, OnCbnSelchangeCmbAddress)
    ON_BN_CLICKED(IDC_BTN_QUERY, OnBnClickedBtnQuery)
    ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK3, OnBnClickedCheck3)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDtnDatetimechangeDatetimepicker1)
    ON_NOTIFY(NM_THEMECHANGED, IDC_DATETIMEPICKER1, OnNMThemeChangedDatetimepicker1)
    ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKER1, OnDtnCloseupDatetimepicker1)
END_MESSAGE_MAP()

BOOL CNetLogDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_ctrlCmbEvent.EnableWindow(FALSE);
    m_ctrlCmbIPAddr.EnableWindow(FALSE);

    //
    m_ctrlDateTime.GetTime(m_DTSelection);
    //设置列的标题
    m_ctrlNLList.SetExtendedStyle(LVS_EX_GRIDLINES | 
        LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlNLList.SetHeadings( _T("时间,140;事件,100;客户IP,120;端口,40;内容,500") );
    m_ctrlNLList.LoadColumnInfo();
    
    //
    LoadLogs();

    OnBnClickedBtnQuery();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CNetLogDlg::OnCbnSelchangeCmbAddress()
{
    // TODO: 在此添加控件通知处理程序代码
}

// [查询] 按钮
void CNetLogDlg::OnBnClickedBtnQuery()
{
    m_ctrlNLList.DeleteAllItems();
    
    //事件条件
    int iEventType = 0;
    if (m_ctrlEventCheck.GetCheck()==BST_CHECKED)
    {
        iEventType = m_ctrlCmbEvent.GetCurSel();
    }

    //IP地址条件
    CString strIPAddr=_T("");
    if (m_ctrlIPAddrCheck.GetCheck()==BST_CHECKED)
    {
        m_ctrlCmbIPAddr.GetWindowText(strIPAddr);
    }

    //写入LIST中
    CAppLogList  logList;
    m_NetLogMgr.GetAllLogList(logList);
    POSITION pos = logList.GetHeadPosition();
    while (pos)
    {
        PIMsgAppLogs pLog = logList.GetNext(pos);

        //
        CString strEvent=_T("");
        CString strClientIP=_T(""),strClientPort=_T("");
        pLog->GetLogType_str(strEvent);


        if (pLog->IsKindOf(RUNTIME_CLASS(IMsgNetLog)))
        {
            PIMsgNetLog pNetLog = (PIMsgNetLog)pLog;

            strClientIP.Format("%d.%d.%d.%d",pNetLog->byClientIP[0],pNetLog->byClientIP[1],
                pNetLog->byClientIP[2],pNetLog->byClientIP[3]);         

            // 端口
            strClientPort.Format("%d",pNetLog->uClientPort); 
            
            // 事件
            pNetLog->GetEventType_str(strEvent);

            if (  (iEventType!=0 && iEventType!=pNetLog->iEventType) ||
                  (!strIPAddr.IsEmpty() && strClientIP!=strIPAddr && strIPAddr!="0.0.0.0")  )
            {
                continue;
            }
        }
        else
        {
            if (iEventType!=0 || !strIPAddr.IsEmpty())
            {
                continue;
            }
        }

        // Add log to the list
        m_ctrlNLList.AddItem( pLog->logTime.Format(" %Y-%m-%d %H:%M:%S"),
            " "+strEvent,
            " "+strClientIP,
            " "+strClientPort,
            " "+pLog->strComments);
        
    }
}


void CNetLogDlg::OnBnClickedCheck2()
{
    // 事件条件
    int iState = m_ctrlEventCheck.GetCheck();
    if (iState==BST_CHECKED)
    {
        m_ctrlCmbEvent.EnableWindow(TRUE);
    }
    else if (iState==BST_UNCHECKED)
    {
        m_ctrlCmbEvent.EnableWindow(FALSE);
    }
}

void CNetLogDlg::OnBnClickedCheck3()
{
    // IP地址条件
    int iState = m_ctrlIPAddrCheck.GetCheck();
    if (iState==BST_CHECKED)
    {
        m_ctrlCmbIPAddr.EnableWindow(TRUE);
    }
    else if (iState==BST_UNCHECKED)
    {
        m_ctrlCmbIPAddr.EnableWindow(FALSE);
    }
}


void CNetLogDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
   
    *pResult = 0;
}


void CNetLogDlg::OnNMThemeChangedDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // 该功能要求使用 Windows XP 或更高版本。
    // 符号 _WIN32_WINNT 必须 >= 0x0501。
    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}

// 根据日期控件中的日期从日志文件中读取日志
void CNetLogDlg::LoadLogs(void)
{
    COleDateTime logTime;
    m_ctrlDateTime.GetTime(logTime);

    CString strFileName = GetExePath()+CString(PATH_APP_LOG)+logTime.Format("%Y-%m-%d.nel");
    if(!m_NetLogMgr.ReadFromFile(strFileName))
    {
        m_NetLogMgr.ClearCache();
        MessageBox(logTime.Format("没有找到%Y-%m-%d的日志文件。"),"提示",
            MB_ICONEXCLAMATION);
        return;
    }
    else
    {
        m_ctrlCmbIPAddr.ResetContent();
        m_ctrlCmbIPAddr.AddString("0.0.0.0");
        //
        CStringList strIPAddrList;
        m_NetLogMgr.GetIPAddr(strIPAddrList);
        //
        POSITION pos = strIPAddrList.GetHeadPosition();
        while (pos)
        {
            CString strIP = strIPAddrList.GetNext(pos);
            m_ctrlCmbIPAddr.AddString(strIP);
        }
    }
}

void CNetLogDlg::OnDtnCloseupDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
    COleDateTime    dtCurrent;
    m_ctrlDateTime.GetTime(dtCurrent);
    if (m_DTSelection != dtCurrent)
    {
        LoadLogs();
        m_DTSelection = dtCurrent;
    }

    OnBnClickedBtnQuery();

    *pResult = 0;
}
