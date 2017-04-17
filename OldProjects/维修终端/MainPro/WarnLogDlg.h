#if !defined(AFX_WARNLOGDLG_H__4FA2C1E5_37F2_4DB0_B49F_1AB1B842831E__INCLUDED_)
#define AFX_WARNLOGDLG_H__4FA2C1E5_37F2_4DB0_B49F_1AB1B842831E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WarnLogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWarnLogDlg dialog
#include "SortListCtrl.h"

class CWarnLogDlg : public CDialog
{
// Construction
public:
	int nCode,nType;
	BOOL m_bActive;
	int m_nItem;
	void InitList();
	CImageList m_ImageList1,m_ImageList2;
	CWarnLogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWarnLogDlg)
	enum { IDD = IDD_WARNLOG_DIALOG };
	CComboBox	m_ctrlStation;
	CComboBox	m_ctrlDate;
	CSortListCtrl	m_ctrlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWarnLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWarnLogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeWarnlogdlgDate();
	afx_msg void OnDblclkWarnlogdlgList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeWarnlogdlgStation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNLOGDLG_H__4FA2C1E5_37F2_4DB0_B49F_1AB1B842831E__INCLUDED_)
