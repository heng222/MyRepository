// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__5687BE00_8D93_440B_8384_C56633F25E35__INCLUDED_)
#define AFX_MAINFRM_H__5687BE00_8D93_440B_8384_C56633F25E35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DoubleConnection.h"
#include "ConstructQuery.h"
#include "ConstructRequest.h"
#include "ShowCommand.h"
#include "UserManageDlg.h"
#include "ReceiveQueue.h"



#include "InfPromptDlg.h"

class CWarnLogDlg;
class CWarnNoteDlg;


class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

	//施工请求对话框指针
//	CConstructRequest*		m_pRequestDlg;

	//施工查询对话框指针
//	CConstructQuery*		m_pQueryDlg;

	//消息提示框
	CInfPromptDlg*			m_pInfPromptDlg;	//非模式对话框

	CWarnLogDlg*			m_pWarnLogDlg;
	CWarnNoteDlg*			m_pWarnNoteDlg;


	//---------------------
	BYTE BufferTmp[4096];
	CDoubleConnection m_socketClient;
	CStatusBar  m_wndStatusBar;
	CReceiveQueue m_receiveQueue;
	BOOL m_bConnected;//网络是否连接的标记
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetConnection(BOOL);
	BOOL RequireStationStatus();
	
	//-------------------------------------
	void OnReceive();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	
	
//	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOperatorConstructrequest();
	afx_msg void OnOperateConstructquery();
	afx_msg void OnSystemUsermanage();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateOperatorConstructrequest(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSystemUsermanage(CCmdUI* pCmdUI);
	afx_msg void OnViewShowwarnlog();
	afx_msg void OnViewNewmessage();
	afx_msg void OnUpdateViewNewmessage(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnUpdateConnection(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:

	//连接到自律机
	BOOL ConnectToALServer();
	
	//发送确认帧
	VOID SendConfirmFrame(DWORD dwOrder);
	
	//分析收到的调度命令
	void AnalyseDispatchFrame(LPBYTE pFrame);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__5687BE00_8D93_440B_8384_C56633F25E35__INCLUDED_)
