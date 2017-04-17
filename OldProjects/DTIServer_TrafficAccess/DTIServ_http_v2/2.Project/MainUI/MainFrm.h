// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once

//////////////////////////////////////////////////////////////////////////

#define WM_ICONNOTIFY  WM_USER + 909 // ����������ͼ����Ӧ��Ϣ(lParam)
#define ID_TASKBARICON 100           // ����(wParam)

#include "InterfaceEx.h"
#include "QueryDlgBar.h"

/************************************************************************/

// �Զ�����Ϣ (wParam = PTImcMsg; lParam = 0)
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
// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
    //ϵͳ���̾��
    NOTIFYICONDATA  m_hTaskIconData;  
	CStatusBar  m_wndStatusBar;
    CReBar m_wndRebar;
	CToolBar    m_wndToolBar;
    CQueryDlgBar	m_wndDialogBar;

// ���ɵ���Ϣӳ�亯��
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


