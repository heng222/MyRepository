#if !defined(AFX_INFPROMPTDLG_H__00173400_A6C2_4E0B_97A3_3F0B4FBCCB12__INCLUDED_)
#define AFX_INFPROMPTDLG_H__00173400_A6C2_4E0B_97A3_3F0B4FBCCB12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfPromptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfPromptDlg dialog

#include "NewMessage.h"
class CMainFrame;

class CInfPromptDlg : public CDialog
{
public:
	CNewMessage m_newMessage;
	
// Construction
public:
	void ShowNewMsg();

	CInfPromptDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInfPromptDlg)
	enum { IDD = IDD_INFORMATION_PROMPT };
	CComboBox	m_ctrlDetailedInf;
	CStatic	m_ctrlPromptInf;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfPromptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfPromptDlg)
	afx_msg void OnClose();
	afx_msg void OnButtonShowNewMsg();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMainFrame*		m_pMainFrame;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFPROMPTDLG_H__00173400_A6C2_4E0B_97A3_3F0B4FBCCB12__INCLUDED_)
