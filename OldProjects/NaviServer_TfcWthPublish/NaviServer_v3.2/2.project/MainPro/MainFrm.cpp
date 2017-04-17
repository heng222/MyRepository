// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "NaviServer.h"
#include "AppConfigSheet.h"
#include "FeeUsersDlg.h"
#include ".\mainfrm.h"
#include "UserColors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CNaviServerApp theApp;

#define ID_CLOCK_RUNTIME	    111     // 显示程序已运行的时间
#define INTERVAL_RUNTIME        60000   // ms

#define ID_CLOCK_CLEANUP	    112     // 网络清理


#define ID_CLOCK_DBTEST         113     // 检测数据库
#ifdef _DEBUG
    #define INTERVAL_DBTEST         1800000 // 30m
#else
    #define INTERVAL_DBTEST         3600000
#endif


#define ID_CLOCK_MEM_CHECK      114     // 内存检测间隔时间
#ifdef _DEBUG
    #define INTERVAL_MEMCHECK       1    // 分钟
#else
    #define INTERVAL_MEMCHECK       30    // 分钟
#endif



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	
    ON_WM_CREATE()
	ON_WM_TIMER()
    ON_WM_CLOSE()	
    ON_WM_SIZE()

    ON_MESSAGE(UM_NEW_IMCMSG,OnRecvUserMsg)
	ON_MESSAGE(WM_ICONNOTIFY,OnTrayNotification)

    ON_COMMAND(ID_VIEW_OPTION, OnViewOption)
    ON_COMMAND(ID_FEE_MUSERS, OnFeeMusers)
    ON_COMMAND(ID_FEE_SREQ, OnFeeSreq)
    ON_COMMAND(ID_FEE_SRSP, OnFeeSrsp)
    ON_COMMAND(ID_FEE_REGUSERS, OnFeeRegusers)
    ON_COMMAND(ID_VIEW_NETLOG, OnViewQuerylog)
    ON_WM_CTLCOLOR()
    ON_WM_PAINT()
    ON_COMMAND(ID_START_SERVICE, OnStartService)
    ON_COMMAND(ID_STOP_SERVICE, OnStopService)
    ON_UPDATE_COMMAND_UI(ID_START_SERVICE, OnUpdateStartService)
    ON_UPDATE_COMMAND_UI(ID_STOP_SERVICE, OnUpdateStopService)
    ON_COMMAND(ID_RESTART_APP, OnRestartApp)
    ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 显示最新事件
	ID_INDICATOR_DATABASE,	// 数据库状态
	ID_INDICATOR_TIME,		// 运行时间
	ID_INDICATOR_CORP,		// 公司名称
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    bServiceState = FALSE;
    m_pLiveLogView = NULL;
    m_pSelectTreeView = NULL;
    m_pMainVew = NULL;

	// TODO: add member initialization code here
	m_cRunTime = CTime::GetCurrentTime(); 
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

    //cs.dwExStyle |= WS_EX_TOPMOST;

	cs.style &= ~FWS_ADDTOTITLE;
    //cs.style &= ~WS_TILED;

	// Size the window to full screen size  
	cs.cy = ::GetSystemMetrics(SM_CYSCREEN);
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

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
    /*if(!m_wndRebar.Create(this,RBS_BANDBORDERS, 
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_TOP|CBRS_FLYBY| CBRS_SIZE_DYNAMIC ))*/
    if(!m_wndRebar.Create(this))
    {
        return FALSE;
    }

    /*if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
        | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))*/
    if(!m_wndToolBar.CreateEx(this))
    {
        return FALSE;      
    }

    // 如果不需要工具提示，则将此移除
    m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
        CBRS_TOOLTIPS | CBRS_FLYBY);

    m_wndToolBar.GetToolBarCtrl().SetButtonWidth(40, 80);

    struct TBtnAttri 
    {
        UINT nID;
        CString strText;
        UINT nStyle;
        UINT nIconRsc;
    };
    TBtnAttri btnArray[] = { { ID_START_SERVICE,    _T("启动服务"),     TBBS_BUTTON,        IDI_TOOLBAR_START },
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
    strcpy(m_hTaskIconData.szTip, "NaviServer - 导航服务器"); 
    Shell_NotifyIcon(NIM_ADD, &m_hTaskIconData);
}

BOOL CMainFrame::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle , const RECT& rect , CWnd* pParentWnd , LPCTSTR lpszMenuName , DWORD dwExStyle , CCreateContext* pContext)
{
    // TODO: 在此添加专用代码和/或调用基类

    return CMDIFrameWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, lpszMenuName, dwExStyle, pContext);
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
        return -1;      // fail to create
    }

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	/*m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/
    AddShellNotify();

    //
    //FullScreen();

	return 0;
}

void CMainFrame::ActiveEvents()
{
    StartTimers();

    // 得到视图指针
    m_pLiveLogView = (CLiveLogView*)(theApp.GetView(RUNTIME_CLASS(CLiveLogView)));
    m_pSelectTreeView = (CSelectionTreeView*)(theApp.GetView(RUNTIME_CLASS(CSelectionTreeView)));
    m_pMainVew = (CMainView*)(theApp.GetView(RUNTIME_CLASS(CMainView)));


    // 初始化所有的Page
    int nCount = m_pMainVew->GetPageCount();
    for (int i=0; i<nCount; i++)
    {
        m_pMainVew->ActivePage(i);
    }
    m_pMainVew->ActivePage(CMainSheet::EPN_BALANCESERVER);// 设置默认PAGE

    
    // 数据库检测
    IMsgDBCntTest msg;
    msg.SetType(IMsgDBCntTest::E_REQUEST);
    NbsSendModuleMsg(&msg);

    // 启动服务
    OnStartService();

}

void CMainFrame::StartTimers()
{
    //*  时间显示计时器                                      
    SetTimer(ID_CLOCK_RUNTIME,INTERVAL_RUNTIME,NULL);

    //*  网络清理计时器                                      
    SetTimer(ID_CLOCK_CLEANUP,10000,NULL);

    //* 数据库检测计时器                                           
    SetTimer(ID_CLOCK_DBTEST,INTERVAL_DBTEST,NULL);
}
void CMainFrame::StopTimers()
{
    KillTimer(ID_CLOCK_RUNTIME);
    KillTimer(ID_CLOCK_CLEANUP);
    KillTimer(ID_CLOCK_MEM_CHECK);
    KillTimer(ID_CLOCK_DBTEST);
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnClose()
{
    Shell_NotifyIcon(NIM_DELETE, &m_hTaskIconData);

    if (m_bCloseTip)
    {
        CString strTip = "警告：你确定要关闭服务器？";

        int iRC = MessageBox(strTip,"安全提示",
            MB_ICONQUESTION|MB_YESNOCANCEL|MB_DEFBUTTON2);

        if (iRC==IDYES)
        {
            StopTimers();

            // 
            IMsgAppLogs aLog;
            aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
            aLog.strComments.Format(_T("用户选择关闭程序！"));
            NbsSendModuleMsg(&aLog);

            // 
            NbsTermination();

            // 
            CMDIFrameWnd::OnClose();
        }
    }
    else
    {
        CMDIFrameWnd::OnClose();
    }
}
void CMainFrame::OnTimer(UINT nIDEvent)
{
	int iIndex = 0;
	CString strContent;

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
        //
	case ID_CLOCK_RUNTIME:
		{			
			// 时间显示
			iIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIME);
			CTimeSpan timeSpan;
			timeSpan = CTime::GetCurrentTime() - m_cRunTime;
			CString strTime = timeSpan.Format("已运行%D天%H小时%M分");					
			m_wndStatusBar.SetPaneText(iIndex,(LPCTSTR)strTime);
		}
		break;


        //
	case ID_CLOCK_CLEANUP:
		{
            // 清理网络
            IMsgNetWorkCleanUp sckMsg;
            NbsSendModuleMsg(&sckMsg);
		}
	    break;

    case ID_CLOCK_DBTEST:
        {
            // 数据库检测
            IMsgDBCntTest msg;
            msg.SetType(IMsgDBCntTest::E_REQUEST);
            NbsSendModuleMsg(&msg);
        }
        break;

        // 检查内存可用量
	case ID_CLOCK_MEM_CHECK:
        {
            CStdioFile memLogFile;
            if (!memLogFile.Open(_T("memcheck.log"),CFile::shareDenyNone|CFile::modeReadWrite))
            {
                memLogFile.Open(_T("memcheck.log"),CFile::modeCreate|CFile::shareDenyNone|CFile::modeReadWrite);
            }
            memLogFile.SeekToEnd();
            
            MEMORYSTATUS mem_stat;
            ::GlobalMemoryStatus(&mem_stat);            
            COleDateTime curTime = COleDateTime::GetCurrentTime();
            CString strLine;
            strLine.Format( _T("%s\t 总内存= %ldKB\t 可用内存= %ldKB\n"), 
                curTime.Format(_T("%Y-%m-%d %H:%M")),
                mem_stat.dwTotalPhys/1024,mem_stat.dwAvailPhys/1024);
            
            memLogFile.WriteString(strLine);
        }
	    break;
	}

	CMDIFrameWnd::OnTimer(nIDEvent);
}



BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	return CMDIFrameWnd::PreTranslateMessage(pMsg);
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

	if ( nType == SIZE_MINIMIZED )
	{
		OnFrameMinimize();
	}  	
}

// Option
void CMainFrame::OnViewOption()
{
    CAppConfigSheet cPropertiesSheet;
    cPropertiesSheet.DoModal();
}

// 
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

        // 得到视图指针
        m_pLiveLogView = (CLiveLogView*)(theApp.GetView(RUNTIME_CLASS(CLiveLogView)));
        m_pSelectTreeView = (CSelectionTreeView*)(theApp.GetView(RUNTIME_CLASS(CSelectionTreeView)));
        m_pMainVew = (CMainView*)(theApp.GetView(RUNTIME_CLASS(CMainView)));

        if (m_pMainVew)
        {
            m_pMainVew->AddNewLogs(pNewLog);
        }
        if (m_pLiveLogView)
        {
            m_pLiveLogView->AddLiveLog(pNewLog);
        }
        if (m_pSelectTreeView)
        {
            m_pSelectTreeView->AddNewLogs(pNewLog);
        }

        if (pNewLog)
        {
            // 显示最新消息
            int iIndex = m_wndStatusBar.CommandToIndex(ID_SEPARATOR);
            m_wndStatusBar.SetPaneText(iIndex,pNewLog->strComments);
        }

    }
    else if (EDB_CONNECTION_STATE==wMsgType)
    {
        PIMsgDBCntTest pDBTest = (PIMsgDBCntTest)pUserMsg;
        int iIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_DATABASE);

        if (pDBTest->bResult)
        {         
            m_wndStatusBar.SetPaneText(iIndex,_T("数据库：√"));
        }
        else
        {
            m_wndStatusBar.SetPaneText(iIndex,_T("数据库：×"));
        }
    }

    
    return 0L;
}


//---------- 注册用户查询 -------------------//
void CMainFrame::OnFeeRegusers()
{
    CDlgUsersRegedMgr dlg;
    dlg.DoModal();
}

//----------  查询包月用户信息 -------------//
void CMainFrame::OnFeeMusers()
{
    CFeeUsersDlg dlg;
    dlg.DoModal();
}

//----------  服务请求记录 -----------------//
void CMainFrame::OnFeeSreq()
{
    
}

//----------  服务回复记录 -----------------//
void CMainFrame::OnFeeSrsp()
{
    
}


void CMainFrame::OnViewQuerylog()
{
    // TODO: 在此添加命令处理程序代码
    CNetLogDlg  NetLogDlg;
    if (NetLogDlg.DoModal()==IDOK)
    {
    }
}
HBRUSH CMainFrame::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CMDIFrameWnd::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  在此更改 DC 的任何属性

    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
    return hbr;
}

void CMainFrame::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CMDIFrameWnd::OnPaint()

    //CRect   rect; 
    //GetWindowRect(&rect);//得到客户区区域 
    //CBrush brush;
    //brush.CreateSolidBrush(CLR_RED);
    //dc.FillRect(rect,&brush);

    //CDC   memDC; 
    //CBitmap   bmp; 
    //bmp.LoadBitmap(IDB_BMP_LOG);//加载你的图片资源 
    //memDC.CreateCompatibleDC(&dc); 
    //memDC.SelectObject(&bmp); 
    ////可将BitBlt()函数换成StretchBlt(),关于StretchBlt函数可查阅MSDN相关说明 
    //dc.SetStretchBltMode(COLORONCOLOR); 
    //dc.StretchBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0, 341,345,SRCCOPY);//400×300可根据你图片的具体大小来改变 
    //memDC.DeleteDC(); 
}


void CMainFrame::OnStartService()
{
    TImcMsg msg(EMSG_START_SERVICE,ID_MODULE_USERIF,ID_MODULE_NETWORK);
    NbsSendModuleMsg(&msg);

    bServiceState = BOOL(msg.m_wParam);

    if (!bServiceState)
    {
        CAppConfigSheet cPropertiesSheet;
        cPropertiesSheet.SetActivePage(1);
        cPropertiesSheet.DoModal();
    }
}

void CMainFrame::OnStopService()
{
    CString strTip = "确定要停止服务？";

    int iRC = MessageBox(strTip,"安全提示",MB_ICONQUESTION|MB_YESNOCANCEL|MB_DEFBUTTON2);

    if (iRC==IDYES)
    {
        TImcMsg showWndMsg(EMSG_SHOW_TIPWND,ID_MODULE_USERIF,ID_MODULE_USERIF);
        NbsSendModuleMsg(&showWndMsg);


        IMsgAppLogs aLog;
        aLog.strComments.Format(_T("正在停止服务……"));
        NbsSendModuleMsg(&aLog);

        //
        TImcMsg msg(EMSG_STOP_SERVICE,ID_MODULE_USERIF,ID_MODULE_NETWORK);
        NbsSendModuleMsg(&msg);

        bServiceState = FALSE;


        TImcMsg closeWndMsg(EMSG_CLOSE_TIPWND,ID_MODULE_USERIF,ID_MODULE_USERIF);
        NbsSendModuleMsg(&closeWndMsg);
    }
}

void CMainFrame::OnUpdateStartService(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!bServiceState);
}

void CMainFrame::OnUpdateStopService(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码
    pCmdUI->Enable(bServiceState);
}

void CMainFrame::OnRestartApp()
{
    int iRc = ::MessageBox(NULL,"是否立即重启？","系统提示",MB_ICONINFORMATION|MB_YESNO);

    if (iRc==IDYES)
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
        aLog.strComments.Format(_T("重启程序……"));
        NbsSendModuleMsg(&aLog);


        // Restart
        TImcMsg msg(ESYS_RESTART_APP,ID_MODULE_USERIF,ID_MODULE_USERIF);
        NbsSendModuleMsg(&msg);
    }
}

void CMainFrame::FullScreen()
{

    RECT rectDesktop;
    WINDOWPLACEMENT wpNew;

    GetWindowPlacement (&wpNew);

    m_wndStatusBar.ShowWindow(SW_HIDE);
    m_wndToolBar.ShowWindow(SW_HIDE);

    ::GetWindowRect ( ::GetDesktopWindow(), &rectDesktop );
    ::AdjustWindowRectEx(&rectDesktop, GetStyle(), TRUE,GetExStyle());
    m_FullScreenWindowRect = rectDesktop;
    wpNew.showCmd = SW_SHOWNORMAL;
    wpNew.rcNormalPosition = rectDesktop;
    SetWindowPlacement ( &wpNew );

}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    /*lpMMI->ptMaxSize.y = m_FullScreenWindowRect.Height();
    lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
    lpMMI->ptMaxSize.x = m_FullScreenWindowRect.Width();
    lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;*/

    CMDIFrameWnd::OnGetMinMaxInfo(lpMMI);
}
