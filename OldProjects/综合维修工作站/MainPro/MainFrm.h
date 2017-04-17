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

	//ָ����������д�Ի����ָ��
	CDdmlxdDlg*			m_pDdmlxdDlg;

	//������Ϣ��
	CWarnLogDlg*		m_pWarnLogDlg;
	CWarnNoteDlg*		m_pWarnNoteDlg;

	//��Ϣ��ʾ��
	CInfPromptDlg*		m_pInfPromptDlg;//����Ϊ��ģʽ�Ի���

	//-------------------------------------
	BYTE				BufferTmp[4096];
	CDoubleConnection	m_socketClient;
	CAdoConnection		m_adoLogConnect;
	CReceiveQueue		m_receiveQueue;
	
// Operations
public:
	
	BOOL	m_bSingleStaShow;//��ǰ���ĸ���ͼ��
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

	//���ӵ����ݿ��������Ӧ�÷�����
	BOOL ConnectToDBServer();
	BOOL ConnectToALServer();

	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	BOOL		m_bConnected;//�����Ƿ����ӵı��
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

	//���ͻ�����ִ
	void SendConfirmFrame(DWORD dwOrder);

	//�������е������ĵ�������
	void AnalyseDispatchFrame(BYTE *pFrame);

	//�����ӳ�վ������ʩ������֡
	void AnalyseAskFrame(BYTE *pFrame);

	//�����ӳ�վ�����ĵ��������ִ֡
	void AnalyseResponseFrame(LPBYTE pFrame);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__5687BE00_8D93_440B_8384_C56633F25E35__INCLUDED_)
