#if !defined(AFX_CONSTRUCTREQUEST_H__A71EA311_7B72_4634_A583_0B2F68DE017D__INCLUDED_)
#define AFX_CONSTRUCTREQUEST_H__A71EA311_7B72_4634_A583_0B2F68DE017D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConstructRequest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConstructRequest dialog
#include "Maintain.h"
#include "SortListCtrl.h"
#include "ReadMendTemplate.h"

class CMainFrame;

//--------------------------------------
class CConstructRequest : public CDialog
{
// Construction
public:
	
	CConstructRequest(CWnd* pParent = NULL);   // standard constructor
	//~CConstructRequest() {KillTimer(1);}

// Dialog Data
	//{{AFX_DATA(CConstructRequest)
	enum { IDD = IDD_CONSTRUCT_REQUEST_DIALOG };
	CComboBox	m_ctrlStation;
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
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:

	CAdoConnection	m_adoLogConnect;
	CAdoRecordSet	m_adoLogSet;
	CMainFrame*		m_pMainFrame;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConstructRequest)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioRegister();
	afx_msg void OnNewregister();
	afx_msg void OnBDelete();
	afx_msg void OnBRequestCommand();
	afx_msg void OnSelchangeMendkind();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	void DisplayRecord();

	//施工种类与记录号
	BYTE m_byConKind,m_byOrder;

	
	//-------------------------------
private:

	//根据 m_byConKind,m_byOrder 更新对话框中的有关控件的可用状态
	void UpdateCtrlComponent();

	void InitRecContent();
	
	void UpdateListCtrl();
	
	void UpdateOrderEdit();
	
	BOOL AddNewData();

private:
	//存放施工模板的对象
	CReadMendTemplate m_MendTemplate;
	BOOL	m_bSaved;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSTRUCTREQUEST_H__A71EA311_7B72_4634_A583_0B2F68DE017D__INCLUDED_)
