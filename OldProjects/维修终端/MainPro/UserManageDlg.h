#if !defined(AFX_USERMANAGEDLG_H__E59C951E_096C_4408_A367_C7D2F1321B9E__INCLUDED_)
#define AFX_USERMANAGEDLG_H__E59C951E_096C_4408_A367_C7D2F1321B9E__INCLUDED_

#include "OperatorInf.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserManageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserManageDlg dialog
class COperatorInf;
class CUserManageDlg : public CDialog
{
// Construction
public:
	void ClearUserInfo();
	//检查输入的用户信息是否有效
	BOOL IsValidUserInfo(int iFlag = 1);
	CUserManageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserManageDlg)
	enum { IDD = IDD_USERMANAGE_DIALOG };
	CComboBox	m_ctrlUserKind;
	CComboBox	m_ctrlName;
	CString	m_strName;
	CString	m_strPassword;
	CString	m_strPWConfirm;
	int		m_iUserKind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserManageDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserManageDlg)
	afx_msg void OnUsermanageAdd();
	afx_msg void OnUsermanageDel();
	virtual BOOL OnInitDialog();
	afx_msg void OnUsermanageModiPas();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//存放操作员信息
	COperatorInf m_cOperatorInf;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERMANAGEDLG_H__E59C951E_096C_4408_A367_C7D2F1321B9E__INCLUDED_)
