// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "MainUI.h"

#include "SheetConfig.h"
#include ".\mainfrm.h"

#include "LogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CMainUIApp theApp;

// Message ID used for tray notifications
#define WM_MY_TRAY_NOTIFICATION WM_USER + 0x500

//////////////////////////////////////////////////////////////////////////

#define ID_CLOCK_DBTEST         113     // ������ݿ�
#ifdef _DEBUG
#define INTERVAL_DBTEST         1800000 // 30m
#else
#define INTERVAL_DBTEST         3600000
#endif


//////////////////////////////////////////////////////////////////////////

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_MESSAGE(UM_NEW_IMCMSG,OnRecvUserMsg)
    ON_MESSAGE(WM_MY_TRAY_NOTIFICATION, OnTrayNotification)
    ON_WM_SIZE()
    ON_COMMAND(ID_VIEW_CONFIG, OnViewConfig)
    ON_BN_CLICKED(IDC_DLGBAR_BTN, OnBnClickedDlgbarBtn)
    ON_COMMAND(ID_VIEW_LOGS, OnViewLogs)
    ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	/*ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,*/
    ID_INDICATOR_CORP,		//��˾����
};


// CMainFrame ����/����

CMainFrame::CMainFrame():m_TrayIcon(IDR_MENU_TRAY)
{
    m_bCloseTip = TRUE;
    m_pMainView = NULL;
    m_pLogView = NULL;
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


// CMainFrame ���

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
    TButAttri btnArray[] = { { ID_START_SERVICE,    _T("��������"),     TBBS_BUTTON,        IDI_TOOLBAR_START },
                             { ID_STOP_SERVICE,     _T("ֹͣ����"),     TBBS_BUTTON,        IDI_TOOLBAR_STOP },
                             { 0,                   _T(""),         TBBS_SEPARATOR,         0       },
                             { ID_VIEW_OPTION,      _T("ѡ��"),     TBBS_BUTTON,            IDI_TOOLBAR_CONFIG },
                             { ID_VIEW_NETLOG,      _T("��־"),     TBBS_BUTTON,            IDI_TOOLBAR_LOGS},
                             { 0,                   "",             TBBS_SEPARATOR,         0 },
                             { ID_APP_EXIT,         _T("�˳�"),     TBBS_BUTTON,            IDI_TOOLBAR_EXIT }
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


    // �ı�����
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

    // ���ð�ť�Ĵ�С
    CRect rectToolBar;
    m_wndToolBar.GetItemRect(0, &rectToolBar);
    m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(15,15));

    // ��Rebar�м���ToolBar
    m_wndRebar.AddBar(&m_wndToolBar);

    // �ı�һЩ����
    REBARBANDINFO rbbi;
    rbbi.cbSize = sizeof(rbbi);
    rbbi.fMask = RBBIM_CHILDSIZE | RBBIM_IDEALSIZE | RBBIM_SIZE|RBBIM_BACKGROUND;;//    
    rbbi.cxMinChild = rectToolBar.Width();
    rbbi.cyMinChild = rectToolBar.Height();
    // �������д�����Ϊ���������뱳��λͼ����ע����rbbi.fMask��RBBIM_BACKGROUND��־
    //rbbi.hbmBack = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_TOOLBAR_BKG));
    rbbi.cx = rbbi.cxIdeal = rectToolBar.Width() * 10;

    m_wndRebar.GetReBarCtrl().SetBandInfo(0, &rbbi);
    imgList.DeleteImageList(); 
#endif
    return TRUE;
}

void CMainFrame::AddShellNotify()
{ 
    // Set up tray icon
    m_TrayIcon.SetNotificationWnd(this, WM_MY_TRAY_NOTIFICATION);
    m_TrayIcon.SetIcon(IDR_MAINFRAME);
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
		TRACE(_T("δ�ܴ���״̬��\n"));
		return -1;      // δ�ܴ���
	}


    // Set up tray icon
    AddShellNotify();

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	/*m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/


    // �����Ҫ����DlgBar�������_CREAT_DLGBAR
#ifdef _CREAT_DLGBAR
    if (!m_wndDialogBar.CreateSelf(this, CBRS_TOP|CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
    {
        TRACE0("Failed to create dialog bar\n");
        return -1;      // fail to create
    }
    //SetDlgItemText(IDC_DLGBAR_BTN, _T("��ť(&A)"));
    /*m_wndDialogBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndDialogBar);*/
#endif

#ifdef _DEBUG
    // �õ���������
    CString strAppName;
    strAppName.LoadString(AFX_IDS_APP_TITLE);
#endif

    //AddShellNotify();


	return 0;
}

void CMainFrame::InitViewPointer()
{
    // �õ���ͼָ��
    m_pLogView = (CLogView*)(theApp.GetView(RUNTIME_CLASS(CLogView)));
    m_pMainView = (CMainUIView*)(theApp.GetView(RUNTIME_CLASS(CMainUIView)));
}

void CMainFrame::ActiveEvents()
{
    // ������ʱ��
    StartTimers();

    // �����¼�...

    // ���ݿ���
    IMsgDBCntTest msg;
    msg.SetType(IMsgDBCntTest::E_REQUEST);
    NbsSendModuleMsg(&msg);

}
void CMainFrame::StartTimers()
{
    //* ���ݿ����ʱ��                                           
    SetTimer(ID_CLOCK_DBTEST,INTERVAL_DBTEST,NULL);
}
void CMainFrame::StopTimers()
{
}
void CMainFrame::OnClose()
{
    //Shell_NotifyIcon(NIM_DELETE, &m_hTaskIconData);

    if (m_bCloseTip)
    {
        CString strTip = _T("ȷ��Ҫ�رճ���");

        int iRC = MessageBox(strTip,_T("��ȫ��ʾ"),
            MB_ICONQUESTION|MB_YESNOCANCEL|MB_DEFBUTTON2);

        if (iRC==IDYES)
        {
            IMsgAppLogs aLog;
            aLog.iLogLevel = IMsgAppLogs::ELL_WARNING;
            aLog.strComments.Format(_T("�û�ѡ��رճ���"));
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


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
    CMDIFrameWnd::OnSize(nType, cx, cy);

    
    /*
    if ( nType == SIZE_MINIMIZED )
        {
        }
    */
    
}

// Option
void CMainFrame::OnViewConfig()
{
    CSheetConfig dlgCfg(_T("����"));
    dlgCfg.DoModal();
}

LRESULT CMainFrame::OnRecvUserMsg(WPARAM wParam,LPARAM lParam)
{
    // ȡ�ظ���ͼָ��
    InitViewPointer();

    //
    PTImcMsg pUserMsg = (PTImcMsg)wParam;

    ASSERT(pUserMsg!=NULL);

    WORD wMsgType = pUserMsg->GetMsgType();

    PIMsgAppLogs pNewLog;
    if (wMsgType==ESYS_NEW_LOG)
    {
        // �����ͼ������Ϣ
        pNewLog = (PIMsgAppLogs)wParam;
        if (pNewLog)
        {
            // ��ʾ������Ϣ
            int iIndex = m_wndStatusBar.CommandToIndex(ID_SEPARATOR);
            m_wndStatusBar.SetPaneText(iIndex,pNewLog->strComments);
        }
        
        if (m_pLogView->GetSafeHwnd()!=NULL)
        {
            m_pLogView->AddLiveLog(pNewLog);
        }
    }
    
    return 0L;
}

// 
void CMainFrame::OnBnClickedDlgbarBtn()
{
    // 
}

// �鿴��־
void CMainFrame::OnViewLogs()
{
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
    int iIndex = 0;
    CString strContent;

    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    switch(nIDEvent)
    {

    case ID_CLOCK_DBTEST:
        {
            // ���ݿ���
            IMsgDBCntTest msg;
            msg.SetType(IMsgDBCntTest::E_REQUEST);
            NbsSendModuleMsg(&msg);
        }
        break;
    }

    CMDIFrameWnd::OnTimer(nIDEvent);
}

//---------------------------------------------------------------------------
// OnTrayNotification
//
// Handle notification from tray icon: display a message.
//---------------------------------------------------------------------------
LRESULT CMainFrame::OnTrayNotification(WPARAM uID, LPARAM lEvent)
{
    // let tray icon do default stuff
    return m_TrayIcon.OnTrayNotification(uID, lEvent);
}