// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__5687BE00_8D93_440B_8384_C56633F25E35__INCLUDED_)
#define AFX_MAINFRM_H__5687BE00_8D93_440B_8384_C56633F25E35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
#include "DoubleConnection.h"
#include "DdmlxdDlg.h"
#include "ReceiveQueue.h"


class CWarnLogDlg;
class CWarnNoteDlg;
class CInfPromptDlg;

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

	//指向调试命令编写对话框的指针
	CDdmlxdDlg*			m_pDdmlxdDlg;

	//报警信息框
	CWarnLogDlg*		m_pWarnLogDlg;
	CWarnNoteDlg*		m_pWarnNoteDlg;

	//消息提示框
	CInfPromptDlg*		m_pInfPromptDlg;//必须为非模式对话框

	//-------------------------------------
	BYTE				BufferTmp[4096];
	CDoubleConnection	m_socketClient;
	CAdoConnection		m_adoLogConnect;
	CReceiveQueue		m_receiveQueue;
	
// Operations
public:
	
	BOOL	m_bSingleStaShow;//当前在哪个视图里
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-------------------------------------
	void SetConnection(BOOL);
	BOOL RequireStationStatus();
	void OnReceive();
	void CreateSpeDialog();

	//连接到数据库服务器和应用服务器
	BOOL ConnectToDBServer();
	BOOL ConnectToALServer();

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	BOOL		m_bConnected;//网络是否连接的标记
	CStatusBar	m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	void SwitchToView(CDocTemplate* pTemplate,CRuntimeClass* pViewClass);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOperatorConstructrequest();
	afx_msg void OnOperateConstructquery();
	afx_msg void OnOperatorSenddispacther();
	afx_msg void OnUpdateOperatorSenddispacther(CCmdUI* pCmdUI);
	afx_msg void OnOperatorSendopendispacther();
	afx_msg void OnUpdateOperatorSendopendispacther(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOperateConstructquery(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOperatorConstructrequest(CCmdUI* pCmdUI);
	afx_msg void OnViewShowwarnlog();
	afx_msg void OnViewNewmessage();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnOperatorSinstashow();
	afx_msg void OnUpdateOperatorSinstashow(CCmdUI* pCmdUI);
	afx_msg void OnOperatorMulstashow();
	afx_msg void OnUpdateOperatorMulstashow(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnUpdateConnection(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:

	//发送机器回执
	void SendConfirmFrame(DWORD dwOrder);

	//分析从列调送来的调度命令
	void AnalyseDispatchFrame(BYTE *pFrame);

	//分析从车站送来的施工请求帧
	void AnalyseAskFrame(BYTE *pFrame);

	//分析从车站传来的调度命令回执帧
	void AnalyseResponseFrame(LPBYTE pFrame);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__5687BE00_8D93_440B_8384_C56633F25E35__INCLUDED_)
