// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__85520B33_FF17_402E_AEC2_2DD408DB650E__INCLUDED_)
#define AFX_MAINFRM_H__85520B33_FF17_402E_AEC2_2DD408DB650E__INCLUDED_

#define WM_ICONNOTIFY  WM_USER + 909 //图标响应消息(lParam)
#define ID_TASKBARICON 100           //参数(wParam)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InterfaceEx.h"
#include "MainView.h"
#include "LiveLogView.h"
#include "SelectionTreeView.h"
#include "DlgUsersRegedMgr.h"

/************************************************************************/

// 自定义消息 (wParam = PTImcMsg; lParam = 0)
#define		UM_NEW_IMCMSG  		(WM_USER+100)
 

class CMainFrame : public CMDIFrameWnd
{
	friend class CNaviServerApp;
	DECLARE_DYNAMIC(CMainFrame)

public:
    BOOL m_bCloseTip;

	CMainFrame();

    void FullScreen();

    void ActiveEvents();
    void StartTimers();
    void StopTimers();

// Operations
protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:  // control bar embedded members
    CLiveLogView* m_pLiveLogView;
    CSelectionTreeView* m_pSelectTreeView;
    CMainView* m_pMainVew;

    //系统托盘句柄
    NOTIFYICONDATA  m_hTaskIconData;  

    //
	CStatusBar  m_wndStatusBar;
    CReBar      m_wndRebar;
	CToolBar    m_wndToolBar;

	CTime	m_cRunTime;

    CRect m_FullScreenWindowRect ;


// Generated message map functions
protected:
	BOOL CreateExToolbar();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnClose();
    afx_msg void OnViewOption();
    afx_msg void OnFeeMusers();
    afx_msg void OnFeeSreq();
    afx_msg void OnFeeSrsp();
    afx_msg void OnFeeRegusers();
	

    void    AddShellNotify();
	void	OnFrameMinimize() ;
	LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	void	OnSize(UINT nType, int cx, int cy);

public:
	afx_msg LRESULT OnRecvUserMsg(WPARAM wParam,LPARAM lParam);


private:
    BOOL    bServiceState;

public:
    afx_msg void OnViewQuerylog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnPaint();
    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle = WS_OVERLAPPEDWINDOW, const RECT& rect = rectDefault, CWnd* pParentWnd = NULL, LPCTSTR lpszMenuName = NULL, DWORD dwExStyle = 0, CCreateContext* pContext = NULL);
    afx_msg void OnStartService();
    afx_msg void OnStopService();
    afx_msg void OnUpdateStartService(CCmdUI *pCmdUI);
    afx_msg void OnUpdateStopService(CCmdUI *pCmdUI);
    afx_msg void OnRestartApp();
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__85520B33_FF17_402E_AEC2_2DD408DB650E__INCLUDED_)
