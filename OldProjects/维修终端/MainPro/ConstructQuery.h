#if !defined(AFX_CONSTRUCTQUERY_H__D684FE9F_99B2_409B_B600_6AD11BF270E6__INCLUDED_)
#define AFX_CONSTRUCTQUERY_H__D684FE9F_99B2_409B_B600_6AD11BF270E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConstructQuery.h : header file
//
#include "SortListCtrl.h"
#include "ReadRecord.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CConstructQuery dialog

class CMainFrame;
class CConstructQuery : public CDialog
{
// Construction
public:
	CConstructQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConstructQuery)
	enum { IDD = IDD_CONSTRUCT_QUERY_DIALOG };
	CSortListCtrl	m_ctrlList;
	CDateTimeCtrl	m_ctrlRDateTime;
	COleDateTime	m_oleRDateTime;
	CString	m_strAsker;
	CString	m_strAskStation;
	CString	m_strAskTime;
	CString	m_strChecker;
	CString	m_strCheckTime;
	CString	m_strComContent;
	CString	m_strComTitle;
	CString	m_strComOrder;
	CString	m_strCopyFor;
	CString	m_strDispatcher;
	CString	m_strMendKind;
	CString	m_strOrgReceive;
	CString	m_strOrgSend;
	int		m_iComKind;
	int		m_iRegKind;
	CString	m_strRegContent;
	CString	m_strRegTitle;
	CString	m_strSendTime;
	CString	m_strStations;
	CString	m_strWatcher;
	CString	m_strConsumeTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstructQuery)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
// Attributes
public:
	void UpdateListCtrl();

// Implementation
protected:
	void ShowDetailedInf();

	// Generated message map functions
	//{{AFX_MSG(CConstructQuery)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBClear();
	afx_msg void OnCloseupCondatetime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioReg();
	afx_msg void OnRadioCCom();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	CMainFrame*		m_pMainFrame;

	//---------------------------------
	//存放一天中的所有记录
	CReadRecord Records;

private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTRUCTQUERY_H__D684FE9F_99B2_409B_B600_6AD11BF270E6__INCLUDED_)
