// SheetConfig.cpp : 实现文件
//

#include "stdafx.h"
#include <TSockAddr.h>
#include "mainsheet.h"
#include "UserColors.h"
#include "NetWorkInterface.h"
#include "DataModulInterface.h"
#include "SPPrototocol.h"
#include "MobileFrameMgr_bin.h"
#include "MobileFrameMgr_char.h"
#include "BusinessFrmMgr.h"
#include ".\mainsheet.h"
#include "GlobalMacro.h"


//－－－－－－－－－－－－－－－ CMainSheet －－－－－－－－－－－－－－－－－－－

IMPLEMENT_DYNAMIC(CMainSheet, CPropertySheet)
CMainSheet::CMainSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CMainSheet::CMainSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
    m_ToolTipCtrl = NULL;
    AddPage(&m_blanceserverPage);
    AddPage(&m_mobilesPage);
    //AddPage(&m_weatherPage);
}

CMainSheet::~CMainSheet()
{
    if (m_ToolTipCtrl!=NULL)
    {
        delete m_ToolTipCtrl;
    }
}


BEGIN_MESSAGE_MAP(CMainSheet, CPropertySheet)
    ON_WM_CREATE()
    ON_WM_SIZE()
END_MESSAGE_MAP()



BOOL CMainSheet::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类

    return CPropertySheet::PreTranslateMessage(pMsg);
}
int CMainSheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    // Set for Scrolling Tabs style
    EnableStackedTabs(FALSE);

    if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    //  Create a ToolTip control
    m_ToolTipCtrl = new CToolTipCtrl;
    if (!m_ToolTipCtrl->Create(this,WS_POPUP|WS_EX_TOOLWINDOW|TTS_ALWAYSTIP))
    {
        TRACE("Unable To create ToolTip\n");           
        return -1;
    }

    return 0;
}
BOOL CMainSheet::OnInitDialog()
{
    BOOL bResult = CPropertySheet::OnInitDialog();

    CTabCtrl *pTabCtrl = GetTabControl ();
    // Add icon to the Tab ctrl
    if (pTabCtrl!=NULL)
    {
        m_imageList.Create(32,32, ILC_COLOR8|ILC_MASK, 5,1);
        m_imageList.Add(AfxGetApp()->LoadIcon(IDI_BALANCESERVER));
        m_imageList.Add(AfxGetApp()->LoadIcon(IDI_MOBUSER_ACTIVE));
        m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_WEATHER));
        m_imageList.Add(AfxGetApp()->LoadIcon(IDI_TRAFFIC));
        pTabCtrl->SetImageList (&m_imageList);

        TC_ITEM item;
        item.mask = TCIF_IMAGE;
        for (int i = 0; i <GetPageCount(); i++)
        {
            item.iImage = i;
            pTabCtrl->SetItem (i, &item );
        }
    }

    // 1. Associate the tooltip control to the tab control of CMainSheet.
    pTabCtrl->SetToolTips(m_ToolTipCtrl);
    // Get the bounding rectangle of each tab in the tab control of the
    // property sheet. Use this rectangle when registering a tool with 
    // the tool tip control.
    int count = pTabCtrl->GetItemCount();
    int iTipID = IDS_MAINSHEET_TAB1;
    CRect rectTabltem;
    for (int i = 0; i < count; i++,iTipID++)
    {
        pTabCtrl->GetItemRect(i, &rectTabltem);
        VERIFY(m_ToolTipCtrl->AddTool(pTabCtrl, iTipID, &rectTabltem, iTipID));
    }
    // Activate the tooltip control.
    m_ToolTipCtrl->Activate(TRUE);

    return bResult;
}

void CMainSheet::OnSize(UINT nType, int cx, int cy)
{
    CPropertySheet::OnSize(nType, cx, cy);

    
}

void CMainSheet::ActivePage(CMainSheet::TPageName aPageName)
{
    switch(aPageName)
    {
    case EPN_BALANCESERVER:
        SetActivePage(&m_blanceserverPage);
    	break;
    case EPN_SERVICEPROVIDER:
        //SetActivePage(&m_sp);
    	break;
    case EPN_MOBILECLIENT:
        SetActivePage(&m_mobilesPage);
        break;
    /*case EPN_WEATHERPAGE:
        SetActivePage(&m_weatherPage);
        break;*/
    }
}
void CMainSheet::AddNetLog(PIMsgNetLog pNetLog)
{
    if ( pNetLog->iProtocolType==TMobileFrameBin::E_PRO_FLAG||
         pNetLog->iProtocolType==TMobileFrame_Char::E_PRO_FLAG )
    {
        if (pNetLog->iLogType==IMsgNetLog::ELGT_Network)
        {
            m_mobilesPage.AddNewNetLog(pNetLog);
        }
    }
    else if (pNetLog->iProtocolType==TBusinessFrm::E_PRO_FLAG)
    {
    }
    else if (pNetLog->iProtocolType==TSpFrame::E_PRO_FLAG)
    {
    }
}
void CMainSheet::SetActivedFldID(int aProType,DWORD dwID)
{
    m_mobilesPage.SetActivedComField(aProType,dwID);
}






//////////////////////////////////////////////////////////////////////////
//                  CBlanceServerPage 对话框
IMPLEMENT_DYNAMIC(CBlanceServerPage, CPropertyPage)
CBlanceServerPage::CBlanceServerPage()
	: CPropertyPage(CBlanceServerPage::IDD)
    , m_uBalSvrPort(0)
{
}

CBlanceServerPage::~CBlanceServerPage()
{
}

void CBlanceServerPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_GROUP_BALANCE, m_ctrlGroup);
    DDX_Control(pDX, IDC_CNT_STATE, m_ctrlCntState);
    DDX_Control(pDX, IDC_IPADDRESS1, m_ctrlBalSvrIP);
    DDX_Text(pDX, IDC_EDIT1, m_uBalSvrPort);
}


BEGIN_MESSAGE_MAP(CBlanceServerPage, CPropertyPage)
    ON_WM_SIZE()
    ON_WM_PAINT()
    ON_BN_CLICKED(IDC_BTN_CONNECT, OnBnClickedBtnConnect )
END_MESSAGE_MAP()


BOOL CBlanceServerPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // 网络状态
    TImcMsg msg(EMSG_TEST_BALANCESERVER,ID_MODULE_USERIF,ID_MODULE_NETWORK);
    NbsSendModuleMsg(&msg);
    if (msg.m_wParam>0)
    {
        m_ctrlCntState.SetIcon( AfxGetApp()->LoadIcon(IDI_CONNECTED) );
        GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(FALSE);
    }
    else
    {
        m_ctrlCntState.SetIcon( AfxGetApp()->LoadIcon(IDI_DISCONNECTED) );
        GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(TRUE);
    }

    // 从配置文件中读取
    CString strProfilepath = GetExePath()+CString(PATH_CONFIGURE_FILE);
    char cTemp[300];
    GetPrivateProfileString(CFG_APPNAME_NETWORK,"BALANCE_SERVER_IP",0,cTemp,300,strProfilepath);
    m_ctrlBalSvrIP.SetAddress(TSockAddr(cTemp).IPAddr()); 
    m_uBalSvrPort = GetPrivateProfileInt(CFG_APPNAME_NETWORK,"BALANCE_SERVER_PORT",0,strProfilepath);

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CBlanceServerPage::OnPaint()
{

    CPaintDC dc(this); 
    CDC* pDC = &dc;

#if 0
    // 双缓冲处理
    CRect rectClient;
    GetClientRect(&rectClient);

    CDC MemDC;
    MemDC.CreateCompatibleDC(&dc);

    CBitmap MemBitmap;
    MemBitmap.CreateCompatibleBitmap(&dc, rectClient.Width(), rectClient.Height());

    MemDC.SelectObject(&MemBitmap);
    MemDC.FillSolidRect(0, 0, rectClient.Width(), rectClient.Height(),CLR_WHITE);// 填充背景色

    // do something here...
    //CBitmap bmpBkg;
    //CBrush brushBkg;
    //bmpBkg.LoadBitmap(IDB_BMP_LOG);
    ////brushBkg.CreatePatternBrush(&bmpBkg);
    //brushBkg.CreateHatchBrush(HS_CROSS,CLR_BKG_2);
    //MemDC.FillRect(rectClient,&brushBkg);


    // 将内存中的图拷贝到屏幕上进行显示
    dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(),&MemDC,0,0,SRCCOPY);

    // 绘图完成后的清理
    MemBitmap.DeleteObject();
    MemDC.DeleteDC();

#endif
}

void CBlanceServerPage::OnBnClickedBtnConnect()
{

    TImcMsg msg(EMSG_CNNT_BALANCESERVER,ID_MODULE_USERIF,ID_MODULE_NETWORK);
    NbsSendModuleMsg(&msg);
}


void CBlanceServerPage::OnSize(UINT nType, int cx, int cy)
{
    CPropertyPage::OnSize(nType, cx, cy);

    // 
    // TODO: 在此处添加消息处理程序代码
    if (m_ctrlGroup.GetSafeHwnd()!=NULL)
    {
        CRect clientRect;
        GetClientRect(clientRect);

        // Adjust Group control
        CPoint groupStartPt(0,0);
        m_ctrlGroup.SetWindowPos(NULL,groupStartPt.x,groupStartPt.y,
            clientRect.right,clientRect.bottom,SWP_NOZORDER);
    }
}




//////////////////////////////////////////////////////////////////////////
//                        CMobileClientPage 对话框

IMPLEMENT_DYNAMIC(CMobileClientPage, CPropertyPage)
CMobileClientPage::CMobileClientPage()
	: CPropertyPage(CMobileClientPage::IDD)
{
}

CMobileClientPage::~CMobileClientPage()
{
}

void CMobileClientPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ctrlListLogs);
    DDX_Control(pDX, IDC_STATIC_GROUP, m_ctrlGroup);
    DDX_Control(pDX, IDC_EDIT1, m_ctrlUserName);
    DDX_Control(pDX, IDC_EDIT2, m_ctrlUpTime);
    DDX_Control(pDX, IDC_EDIT3, m_ctrlDataSent);
    DDX_Control(pDX, IDC_EDIT4, m_ctrlDataRecved);
}


BEGIN_MESSAGE_MAP(CMobileClientPage, CPropertyPage)
    ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CMobileClientPage::OnInitDialog()
{
    BOOL bResult = CPropertyPage::OnInitDialog();

    // 1. Initialize the list control
    m_ctrlListLogs.SetExtendedStyle(LVS_EX_GRIDLINES | 
        LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlListLogs.SetHeadings( _T("时间,140;事件,100;客户IP,120;端口,40;内容,300") );
    m_ctrlListLogs.LoadColumnInfo();

    return bResult;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CMobileClientPage::OnSize(UINT nType, int cx, int cy)
{
    CPropertyPage::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    if (m_ctrlListLogs.GetSafeHwnd()!=NULL)
    {
        CRect clientRect;
        GetClientRect(clientRect);

        // Adjust List control
        CPoint listStartPt(0,ELA_Height_fixed+EHeightGapGT);
        m_ctrlListLogs.SetWindowPos(NULL,listStartPt.x,listStartPt.y,
            clientRect.right-listStartPt.x,clientRect.bottom-listStartPt.y,SWP_NOZORDER);

        // Adjust Group control
        CPoint groupStartPt(0,0);
        m_ctrlGroup.SetWindowPos(NULL,groupStartPt.x,groupStartPt.y,
            clientRect.right-groupStartPt.x,ELA_Height_fixed,SWP_NOZORDER);
    }
}
void CMobileClientPage::SetActivedComField(int aProType,DWORD dwID)
{
    /*if (m_activedComFiledID == dwID)
    {
        return;
    }*/

    m_iProtocolType = aProType;
    m_activedComFiledID = dwID;

    // retrieve the attribute of the ComFiled-Object.
    IMsgRetrivComfldAttri msgRetrivAttri;
    msgRetrivAttri.dwComfieldID = dwID;
    msgRetrivAttri.iProtocolType = aProType;
    NbsSendModuleMsg(&msgRetrivAttri);

    if (msgRetrivAttri.pFieldAttri!=NULL)
    {
        // basic information
        CString strDataFormat;
        m_ctrlUserName.SetWindowText(msgRetrivAttri.pFieldAttri->m_strUserName);
        m_ctrlUpTime.SetWindowText(msgRetrivAttri.pFieldAttri->m_upTime.Format(_T("%Y-%m-%d %H:%M:%S")));
        strDataFormat.Format("%ld",msgRetrivAttri.pFieldAttri->m_dwLenDataSent);
        m_ctrlDataSent.SetWindowText(strDataFormat);
        strDataFormat.Format("%ld",msgRetrivAttri.pFieldAttri->m_dwLenDataRecv);
        m_ctrlDataRecved.SetWindowText(strDataFormat);

        // Logs
        m_ctrlListLogs.DeleteAllItems();
        CNetLogList* pLogList = &(msgRetrivAttri.pFieldAttri->m_NetWorkLogList);
        POSITION pos = pLogList->GetHeadPosition();
        while (pos)
        {
            PIMsgNetLog pLog = pLogList->GetNext(pos);
            AddNewNetLog(pLog);
        }
    }
    else
    {
        // Logical Error!
        IMsgAppLogs aLogicalErrorLog;
        aLogicalErrorLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLogicalErrorLog.strComments.Format(_T("在Sokcet模块没有找到标识符为%d的通信域！"),dwID);
    }
}

void CMobileClientPage::AddNewNetLog(PIMsgNetLog pNetLog)
{
    if (pNetLog->dwComfieldID==m_activedComFiledID)
    {
        // retrieve the attribute of the ComFiled-Object.
        IMsgRetrivComfldAttri msgRetrivAttri;
        msgRetrivAttri.dwComfieldID = m_activedComFiledID;
        msgRetrivAttri.iProtocolType = m_iProtocolType;
        NbsSendModuleMsg(&msgRetrivAttri);

        // basic information
        CString strDataFormat;
        m_ctrlUserName.SetWindowText(msgRetrivAttri.pFieldAttri->m_strUserName);
        m_ctrlUpTime.SetWindowText(msgRetrivAttri.pFieldAttri->m_upTime.Format(_T("%Y-%m-%d %H:%M:%S")));
        strDataFormat.Format("%ld",msgRetrivAttri.pFieldAttri->m_dwLenDataSent);
        m_ctrlDataSent.SetWindowText(strDataFormat);
        strDataFormat.Format("%ld",msgRetrivAttri.pFieldAttri->m_dwLenDataRecv);
        m_ctrlDataRecved.SetWindowText(strDataFormat);

        // 显示日志
        CString strUserName;
        if (!pNetLog->strUserName.IsEmpty())
        {
            strUserName.Format(_T(" 用户名:%s"),pNetLog->strUserName);
        }

        CString strClientIP,strClientPort;
        pNetLog->GetStrIp(strClientIP);
        pNetLog->GetStrPort(strClientPort);

        CString strEvent;
        pNetLog->GetEventType_str(strEvent);

        // Insert a new line.
        m_ctrlListLogs.InsertItemA(0,pNetLog->logTime.Format(" %Y-%m-%d %H:%M:%S"),
            " "+strEvent,
            " "+strClientIP,
            " "+strClientPort,
            " "+pNetLog->strComments+strUserName);


        // Set text colors
        COLORREF crText = ::GetSysColor(COLOR_WINDOWTEXT);
        COLORREF crBkgnd = ::GetSysColor(COLOR_WINDOW);
        switch(pNetLog->iEventType)
        {
            // 客户连接事件
        case IMsgNetLog::ENLT_NEWCONNECTION:
            crText = CLR_BLUE;
            break;

            // 客户断开事件
        case IMsgNetLog::ENLT_DELCONNECTION:
            crText = CLR_RED;
            break;

        }
        //int nItem = m_ctrlListLogs.GetItemCount()-1;
        m_ctrlListLogs.SetItemColor(0,1,crText,crBkgnd);

        // VIEW中只显示部分日志
        if (m_ctrlListLogs.GetItemCount()>500)
        {
            m_ctrlListLogs.DeleteAllItems();
        }
    }

}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// CPageWeather 对话框

IMPLEMENT_DYNAMIC(CWeatherPage, CPropertyPage)
CWeatherPage::CWeatherPage()
: CPropertyPage(CWeatherPage::IDD)
{
}

CWeatherPage::~CWeatherPage()
{
}
void CWeatherPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWeatherPage, CPropertyPage)
    ON_WM_SIZE()
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CWeatherPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  在此添加额外的初始化


    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CWeatherPage::OnSize(UINT nType, int cx, int cy)
{
    CPropertyPage::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd)
    {
        //LPARAM lParam = MAKELONG(cx,cy);
        //pChildWnd->PostMessage(WM_SIZE,(WPARAM)nType,lParam);
        pChildWnd->MoveWindow(0,0,cx,cy);
    }
}

void CWeatherPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CPropertyPage::OnShowWindow(bShow, nStatus);

    // TODO: 在此处添加消息处理程序代码
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd && bShow)
    {
        pChildWnd->SetFocus();
    }
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//                     CTrafficPage 对话框

IMPLEMENT_DYNAMIC(CTrafficPage, CPropertyPage)
CTrafficPage::CTrafficPage()
	: CPropertyPage(CTrafficPage::IDD)
{
}

CTrafficPage::~CTrafficPage()
{
}

void CTrafficPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTrafficPage, CPropertyPage)
    ON_WM_SIZE()
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()



BOOL CTrafficPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  在此添加额外的初始化

    return TRUE; 
}

void CTrafficPage::OnSize(UINT nType, int cx, int cy)
{
    CPropertyPage::OnSize(nType, cx, cy);

    // TODO: 在此处添加消息处理程序代码
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd)
    {
        pChildWnd->MoveWindow(0,0,cx,cy);
    }
}

void CTrafficPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CPropertyPage::OnShowWindow(bShow, nStatus);

    // TODO: 在此处添加消息处理程序代码
    CWnd* pChildWnd = GetTopWindow();
    if (pChildWnd && bShow)
    {
        pChildWnd->SetFocus();
    }
}


