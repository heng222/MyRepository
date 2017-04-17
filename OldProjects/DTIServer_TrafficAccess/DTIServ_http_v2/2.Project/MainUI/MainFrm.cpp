// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "MainUI.h"
#include "SheetConfig.h"
#include ".\mainfrm.h"
#include "LogView.h"
#include "RawTfcView.h"
#include "ParsedTfcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CMainUIApp theApp;

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_MESSAGE(UM_NEW_IMCMSG,OnRecvUserMsg)
    ON_MESSAGE(WM_ICONNOTIFY,OnTrayNotification)
    ON_WM_SIZE()
    ON_COMMAND(ID_VIEW_CONFIG, OnViewConfig)
    ON_BN_CLICKED(IDC_DLGBAR_BTN, OnBnClickedDlgbarBtn)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	/*ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,*/
    ID_INDICATOR_CORP,		//公司名称
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
    m_bCloseTip = TRUE;
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CMDIFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs
    cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX |WS_SIZEBOX|
        WS_MAXIMIZEBOX |  WS_MAXIMIZE;

    cs.style &= ~FWS_ADDTOTITLE;

    // Size the window to full screen size  
    cs.cy = ::GetSystemMetrics(SM_CYSCREEN);
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN);
    return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG



BOOL CMainFrame::CreateExToolbar()
{
#if 0
    if(!m_wndRebar.Create(this,RBS_BANDBORDERS, 
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_TOP|CBRS_FLYBY| CBRS_SIZE_DYNAMIC ))
    {
        return FALSE;
    }
    //m_wndRebar.EnableDocking(CBRS_ALIGN_ANY);

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
        | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
    {
        return FALSE;      
    }

    // TODO: Delete these three lines if you don't want the toolbar to
    //  be dockable
    /*m_wndRebar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndRebar);*/


    m_wndToolBar.GetToolBarCtrl().SetButtonWidth(40, 80);

    struct TButAttri 
    {
        UINT nID;
        CString strText;
        UINT nStyle;
        UINT nIconRsc;
    };
    TButAttri btnArray[] = { { ID_START_SERVICE,    _T("启动服务"),     TBBS_BUTTON,        IDI_TOOLBAR_START },
                             { ID_STOP_SERVICE,     _T("停止服务"),     TBBS_BUTTON,        IDI_TOOLBAR_STOP },
                             { 0,                   _T(""),         TBBS_SEPARATOR,         0       },
                             { ID_VIEW_OPTION,      _T("选项"),     TBBS_BUTTON,            IDI_TOOLBAR_CONFIG },
                             { ID_VIEW_NETLOG,      _T("日志"),     TBBS_BUTTON,            IDI_TOOLBAR_LOGS},
                             { 0,                   "",             TBBS_SEPARATOR,         0 },
                             { ID_APP_EXIT,         _T("退出"),     TBBS_BUTTON,            IDI_TOOLBAR_EXIT }
                          };
    int iBtnCount = sizeof(btnArray)/sizeof(btnArray[0]);

    CImageList imgList;

    // 
    imgList.Create(16,16, ILC_COLOR8|ILC_MASK, iBtnCount,1);
    imgList.SetBkColor(::GetSysColor(COLOR_BTNFACE));
    for (int ii=0; ii<iBtnCount; ii++)
    {
        if (btnArray[ii].nID !=0 )
        {
            imgList.Add(AfxGetApp()->LoadIcon(btnArray[ii].nIconRsc));
        }
    }
    m_wndToolBar.GetToolBarCtrl().SetImageList(&imgList); // 
    imgList.Detach();

    // 
    imgList.Create(17, 17, ILC_COLOR8|ILC_MASK,iBtnCount,1);
    imgList.SetBkColor(::GetSysColor(COLOR_BTNFACE));	
    for ( int ii=0; ii<iBtnCount; ii++ )
    {
        if (btnArray[ii].nID !=0 )
        {
            imgList.Add(AfxGetApp()->LoadIcon(btnArray[ii].nIconRsc));
        }
    }
    m_wndToolBar.GetToolBarCtrl().SetHotImageList(&imgList); // Hot image list
    imgList.Detach();


    // 改变属性
    m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT |CBRS_TOOLTIPS | TBSTYLE_TRANSPARENT|TBBS_CHECKBOX );
    m_wndToolBar.SetButtons(NULL,iBtnCount);


    for (int ii=0,iImg=0; ii<iBtnCount; ii++,iImg++)
    {
        if (btnArray[ii].nID !=0 )
        {
            m_wndToolBar.SetButtonInfo(ii, btnArray[ii].nID,btnArray[ii].nStyle, iImg);   
            m_wndToolBar.SetButtonText(ii, btnArray[ii].strText);	
        }
        else
        {
            m_wndToolBar.SetButtonInfo(ii,0,btnArray[ii].nStyle, 0);
            iImg--;
        }
    }

    // 设置按钮的大小
    CRect rectToolBar;
    m_wndToolBar.GetItemRect(0, &rectToolBar);
    m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(15,15));

    // 在Rebar中加入ToolBar
    m_wndRebar.AddBar(&m_wndToolBar);

    // 改变一些属性
    REBARBANDINFO rbbi;
    rbbi.cbSize = sizeof(rbbi);
    rbbi.fMask = RBBIM_CHILDSIZE | RBBIM_IDEALSIZE | RBBIM_SIZE|RBBIM_BACKGROUND;;//    
    rbbi.cxMinChild = rectToolBar.Width();
    rbbi.cyMinChild = rectToolBar.Height();
    // 下面这行代码是为工具条加入背景位图，请注意上rbbi.fMask中RBBIM_BACKGROUND标志
    //rbbi.hbmBack = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_TOOLBAR_BKG));
    rbbi.cx = rbbi.cxIdeal = rectToolBar.Width() * 10;

    m_wndRebar.GetReBarCtrl().SetBandInfo(0, &rbbi);
    imgList.DeleteImageList(); 
#endif
    return TRUE;
}

void CMainFrame::AddShellNotify()
{ 

    m_hTaskIconData.cbSize				= sizeof(NOTIFYICONDATA);   
    m_hTaskIconData.hWnd				= m_hWnd;;   
    m_hTaskIconData.uID					= ID_TASKBARICON; //发出的消息中的wParam参数   
    m_hTaskIconData.uFlags				= NIF_ICON|NIF_MESSAGE|NIF_TIP;   
    m_hTaskIconData.uCallbackMessage	= WM_ICONNOTIFY; //点击托盘图标系统发出的消息（即发出的消息中的lParam参数）  
    m_hTaskIconData.hIcon				= AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    CString strAppName;
    strAppName.LoadString(AFX_IDS_APP_TITLE);
    strcpy(m_hTaskIconData.szTip, strAppName); 
    Shell_NotifyIcon(NIM_ADD, &m_hTaskIconData);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


    if (!CreateExToolbar())
        return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	/*m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/


    // 如果需要创建DlgBar，则定义宏_CREAT_DLGBAR
#ifdef _CREAT_DLGBAR
    if (!m_wndDialogBar.CreateSelf(this, CBRS_TOP|CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
    {
        TRACE0("Failed to create dialog bar\n");
        return -1;      // fail to create
    }
    //SetDlgItemText(IDC_DLGBAR_BTN, _T("按钮(&A)"));
    /*m_wndDialogBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndDialogBar);*/
#endif

#ifdef _DEBUG
    // 得到程序名称
    CString strAppName;
    strAppName.LoadString(AFX_IDS_APP_TITLE);
#endif

    AddShellNotify();

	return 0;
}
void CMainFrame::ActiveEvents()
{
    StartTimers();

    // 
    CRawTfcView* pRoadView = (CRawTfcView*)(theApp.GetView(RUNTIME_CLASS(CRawTfcView)));
    IMsgCreateTfcView msg1;
    msg1.pRefWnd = pRoadView;
    NbsSendModuleMsg(&msg1);

    // 
    CParsedTfcView* pLinkView = (CParsedTfcView*)(theApp.GetView(RUNTIME_CLASS(CParsedTfcView)));
    TImcMsg msg2(EMSG_CREATE_TFCPARASEVIEW,ID_MODULE_USERIF,ID_MODULE_DATABASE);
    msg2.m_wParam = (WPARAM)pLinkView;
    NbsSendModuleMsg(&msg2);

}
void CMainFrame::StartTimers()
{

}
void CMainFrame::StopTimers()
{
}
void CMainFrame::OnClose()
{
    Shell_NotifyIcon(NIM_DELETE, &m_hTaskIconData);

    if (m_bCloseTip)
    {
        CString strTip = "确定要关闭程序？";

        int iRC = MessageBox(strTip,"安全提示",
            MB_ICONQUESTION|MB_YESNOCANCEL|MB_DEFBUTTON2);

        if (iRC==IDYES)
        {
            IMsgAppLogs aLog;
            aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
            aLog.strComments.Format(_T("用户选择关闭程序！"));
            NbsSendModuleMsg(&aLog);
            // 
            NbsTermination();
            //---------------------------

            CMDIFrameWnd::OnClose();
        }
    }
    else
    {
        CMDIFrameWnd::OnClose();
    }
}

void CMainFrame::OnFrameMinimize() 
{
    Shell_NotifyIcon(NIM_ADD, &m_hTaskIconData); //加入图标
    ShowWindow(SW_HIDE); //隐藏窗体
}
LRESULT CMainFrame::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
    //如果在托盘图标上双击左键  
    if ((wParam == ID_TASKBARICON) && 
        (lParam == WM_LBUTTONDBLCLK))   
    {   
        ShowWindow(SW_MAXIMIZE); //显示窗体
        Shell_NotifyIcon(NIM_DELETE, &m_hTaskIconData); //删除系统托盘图标  
    }
    return 0;
}
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
    CMDIFrameWnd::OnSize(nType, cx, cy);

    // 
    if ( nType == SIZE_MINIMIZED )
    {
        OnFrameMinimize();
    }
}

// Option
void CMainFrame::OnViewConfig()
{
    CSheetConfig dlgCfg("配置");
    dlgCfg.DoModal();
}

LRESULT CMainFrame::OnRecvUserMsg(WPARAM wParam,LPARAM lParam)
{
    PTImcMsg pUserMsg = (PTImcMsg)wParam;

    ASSERT(pUserMsg!=NULL);

    WORD wMsgType = pUserMsg->GetMsgType();

    PIMsgAppLogs pNewLog;
    if (wMsgType==ESYS_NEW_LOG)
    {
        // 向各视图发送消息
        pNewLog = (PIMsgAppLogs)wParam;
        // 显示最新消息
        int iIndex = m_wndStatusBar.CommandToIndex(ID_SEPARATOR);
        m_wndStatusBar.SetPaneText(iIndex,pNewLog->strComments);

        //
        CLogView* pLogView = (CLogView*)(theApp.GetView(RUNTIME_CLASS(CLogView)));
        if ( pLogView->GetSafeHwnd()!=NULL )
        {
            pLogView->AddLiveLog(pNewLog);
        }

    }
    
    return 0L;
}

void CMainFrame::OnBnClickedDlgbarBtn()
{
    // TODO: 在此添加控件通知处理程序代码
}
