#if !defined(AFX_CONSTRUCTQUERY_H__D684FE9F_99B2_409B_B600_6AD11BF270E6__INCLUDED_)
#define AFX_CONSTRUCTQUERY_H__D684FE9F_99B2_409B_B600_6AD11BF270E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConstructQuery.h : header file
//
#include "SortListCtrl.h"
#include "ReadMendTemplate.h"
#include "Maintain.h"

class CMainFrame;

/////////////////////////////////////////////////////////////////////////////
// CConstructQuery dialog

class CConstructQuery : public CDialog
{
// Construction
public:
	CConstructQuery(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConstructQuery)
	enum { IDD = IDD_CONSTRUCT_QUERY_DIALOG };
	CStatic	m_ctrlSMendKind;
	CStatic	m_ctrlSConsumeTime;
	CEdit	m_ctrlConsumeTime;
	CEdit	m_ctrlMendKind;
	CComboBox	m_ctrlAskStation;
	CSortListCtrl	m_ctrlList;
	CDateTimeCtrl	m_ctrlRDateTime;
	CComboBox	m_ctrlRWatcher;
	CComboBox	m_ctrlRAsker;
	COleDateTime	m_oleRDateTime;
	BOOL	m_bCheck1;
	BOOL	m_bCheck2;
	BOOL	m_bCheck3;
	CString	m_strComAsker;
	CString	m_strComWatcher;
	BOOL	m_bCheck4;
	CString	m_strAskStation;
	int		m_iKindReg;
	int		m_iKindCom;
	CString	m_strAsker;
	CString	m_strAskTime;
	CString	m_strChecker;
	CString	m_strCheckTime;
	CString	m_strComContent;
	CString	m_strComOrder;
	CString	m_strComTitle;
	int		m_iConsumeTime;
	CString	m_strCopyFor;
	CString	m_strDispatcher;
	CString	m_strOrgReceive;
	CString	m_strOrgSend;
	CString	m_strRegContent;
	CString	m_strRegTitle;
	CString	m_strSendTime;
	CString	m_strStations;
	CString	m_strWatcher;
	CString	m_strMendKind;
	CString	m_strStation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstructQuery)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Attributes
public:
	CAdoConnection	m_adoLogConnect;
	CAdoRecordSet	m_adoLogSet;
	CMainFrame*		m_pMainFrame;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConstructQuery)
	virtual BOOL OnInitDialog();
	afx_msg void OnBQuery();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBClear();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnBSave();
	afx_msg void OnCheck4();
	afx_msg void OnRadioReg();
	afx_msg void OnRadioCcomand();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateComboBox();
	void UpdateListCtrl( CString strSQL );
	void ShowDetailedInf();
	CReadMendTemplate m_MendTemplate;
	//-------------------------------
public:
    afx_msg void OnDtnDatetimechangeCondatetime(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTRUCTQUERY_H__D684FE9F_99B2_409B_B600_6AD11BF270E6__INCLUDED_)
