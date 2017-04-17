// MainFrm.h : CMainFrame 类的接口
//


#pragma once

//////////////////////////////////////////////////////////////////////////

#define WM_ICONNOTIFY  WM_USER + 909 // 快速启动栏图标响应消息(lParam)
#define ID_TASKBARICON 100           // 参数(wParam)

#include "InterfaceEx.h"
#include "QueryDlgBar.h"

/************************************************************************/

// 自定义消息 (wParam = PTImcMsg; lParam = 0)
#define		UM_NEW_IMCMSG  		(WM_USER+100)
 


// 
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:

    BOOL m_bCloseTip;

	CMainFrame();

    void ActiveEvents();
    void StartTimers();
    void StopTimers();
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
    //系统托盘句柄
    NOTIFYICONDATA  m_hTaskIconData;  
	CStatusBar  m_wndStatusBar;
    CReBar m_wndRebar;
	CToolBar    m_wndToolBar;
    CQueryDlgBar	m_wndDialogBar;

// 生成的消息映射函数
protected:
	BOOL CreateExToolbar();
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnClose();
    void    AddShellNotify();
	void	OnFrameMinimize() ;
    LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
    afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	afx_msg LRESULT OnRecvUserMsg(WPARAM wParam,LPARAM lParam);
    afx_msg void OnViewConfig();
    afx_msg void OnBnClickedDlgbarBtn();
};


