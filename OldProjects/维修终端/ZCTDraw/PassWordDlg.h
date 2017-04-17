#if !defined(AFX_PASSDLG_H__5F875919_1FB1_4CDE_93FB_A01A3C06F245__INCLUDED_)
#define AFX_PASSDLG_H__5F875919_1FB1_4CDE_93FB_A01A3C06F245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PassDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CPassWordDlg dialog

class AFX_EXT_CLASS CPassWordDlg : public CDialog
{
// Construction
public:
	void OnButton(CString);
	CPassWordDlg(CString str,CString strCaption = "",CWnd* pParent = NULL);   // standard constructor
	~CPassWordDlg();
	

// Dialog Data
	//{{AFX_DATA(CPassWordDlg)
	enum { IDD = IDD_OPERPASSWORD_DLG };
	CString	m_strTrainNumber;
	//}}AFX_DATA



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassWordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPassWordDlg)
	afx_msg void OnButton0();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButtondel();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CString m_strSysKeyCode;

	CString m_strTitle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSDLG_H__5F875919_1FB1_4CDE_93FB_A01A3C06F245__INCLUDED_)
