#if !defined(AFX_CONSTRUCTREQUEST_H__A71EA311_7B72_4634_A583_0B2F68DE017D__INCLUDED_)
#define AFX_CONSTRUCTREQUEST_H__A71EA311_7B72_4634_A583_0B2F68DE017D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConstructRequest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConstructRequest dialog
#include "SortListCtrl.h"
#include "ReadRecord.h"
#include "ReadMendTemplate.h"

class CMainFrame;

class CConstructRequest : public CDialog
{
// Construction
public:
	
	CConstructRequest(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConstructRequest)
	enum { IDD = IDD_CONSTRUCT_REQUEST_DIALOG };
	CComboBox	m_ctrlMendKind;
	CEdit	m_ctrlOrder;
	CSortListCtrl	m_ctrlList;
	CDateTimeCtrl	m_ctrlDateTime;
	CString	m_strEdit1;
	CString	m_strEdit3;
	int		m_iKind;
	CString	m_strEdit7;
	CString	m_strContent;
	CString	m_strEdit2;
	CString	m_strAsker;
	CString	m_strWatcher;
	CString	m_strOrder;
	CString	m_strMendKind;
	CString	m_strStation;
	CTime	m_timeDateTime;
	int		m_iConsumeTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConstructRequest)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

private:
	void AddNewData();
	void GetFrame(LPBYTE byFrame,WORD& nFrameLen);
	void UpdateOrderEdit();
	void UpdateListCtrl();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConstructRequest)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioRegister();
	afx_msg void OnBDelete();
	afx_msg void OnBRequestCommand();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeMendkind();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	CMainFrame*		m_pMainFrame;

	//存放一天中的所有记录
	CReadRecord Records;

	CReadMendTemplate	m_MendTemplate;
	//---------------------------------

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTRUCTREQUEST_H__A71EA311_7B72_4634_A583_0B2F68DE017D__INCLUDED_)
