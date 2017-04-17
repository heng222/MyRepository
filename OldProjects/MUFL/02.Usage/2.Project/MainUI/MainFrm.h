// MainFrm.h : CMainFrame 类的接口
//


#pragma once

#include "TrayIcon.h"

//////////////////////////////////////////////////////////////////////////

//#define WM_ICONNOTIFY  WM_USER + 909 // 快速启动栏图标响应消息(lParam)
#define ID_TASKBARICON 100           // 参数(wParam)

#include "InterfaceEx.h"
#include "QueryDlgBar.h"
#include "MainUiview.h"
#include "LogView.h"

/************************************************************************/

// New message (wParam = PTImcMsg; lParam = 0)
#define		UM_NEW_IMCMSG  		(WM_USER+100)
 


// 
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)

// 实现
public:

    CMainFrame();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 重写
public:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected: 

    //系统托盘句柄
    //NOTIFYICONDATA  m_hTaskIconData;  
	CStatusBar      m_wndStatusBar;
    CReBar          m_wndRebar;
	CToolBar        m_wndToolBar;
    CQueryDlgBar    m_wndDialogBar;

// 生成的消息映射函数
protected:

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnClose();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnViewConfig();
    afx_msg void OnBnClickedDlgbarBtn();
    afx_msg void OnViewLogs();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg LRESULT OnTrayNotification(WPARAM wp, LPARAM lp);

    afx_msg LRESULT OnRecvUserMsg(WPARAM wParam,LPARAM lParam);


    //
public:

    BOOL    m_bCloseTip;

    void    InitViewPointer();
    void    ActiveEvents();

    void    StartTimers();
    void    StopTimers();

    // New functions
private:

    BOOL    CreateExToolbar();
    void    AddShellNotify();

private:

    CTrayIcon	m_TrayIcon;		// my tray icon
    CLogView*       m_pLogView;
    CMainUIView*    m_pMainView;

};


