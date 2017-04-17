#if !defined(AFX_SHOWCOMMAND_H__5AAD8D1F_E723_4654_B3EB_C27AC8F32C2D__INCLUDED_)
#define AFX_SHOWCOMMAND_H__5AAD8D1F_E723_4654_B3EB_C27AC8F32C2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowCommand.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowCommand dialog

class CShowCommand : public CDialog
{
private:
	//文件名
	CString m_strPathName;
	//对应的记录号
	BYTE m_byOrder;
	//命令种类
	BYTE m_byKind;

	BOOL		m_bSignFor;	//是否已进行了人工签收
// Construction
public:
	CShowCommand(BYTE byKind = 0, BYTE byOrder = 0, CString strPathName = "", 
		CWnd* pParent = NULL); // standard constructor

// Dialog Data
	//{{AFX_DATA(CShowCommand)
	enum { IDD = IDD_SHOWDISCOMMAND };
	CButton	m_ctrlSignFor;
	CString	m_strContent;
	CString	m_strDispatcher;
	CString	m_strOrder;
	CString	m_strStations;
	CString	m_strSendTime;
	CString	m_strChecker;
	CString	m_strCheckTime;
	CString	m_strCopyFor;
	CString	m_strOrgReceive;
	CString	m_strOrgSend;
	CString	m_strTitle;
	CString	m_strReciver;
	CString	m_strRecBurName;
	CString	m_strRecSubBurName;
	CString	m_strSendBurName;
	CString	m_strSendDispName;
	CString	m_strSendSubBurName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowCommand)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowCommand)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSignFor();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWCOMMAND_H__5AAD8D1F_E723_4654_B3EB_C27AC8F32C2D__INCLUDED_)
