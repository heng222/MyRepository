#if !defined(AFX_WARNNOTEDLG_H__4178DB94_EFAC_4594_9403_95C65ADD076A__INCLUDED_)
#define AFX_WARNNOTEDLG_H__4178DB94_EFAC_4594_9403_95C65ADD076A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WarnNoteDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWarnNoteDlg dialog

class CWarnNoteDlg : public CDialog
{
// Construction
public:
	void TransactAlarmInfo(BYTE* ,int);
	void RefreshAll(DWORD,CTime);
	CWarnNoteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWarnNoteDlg)
	enum { IDD = IDD_WARNNOTE_DIALOG };
	CString	m_strContent;
	CString	m_strDate;
	CString	m_strNum;
	CString	m_strSource;
	CString	m_strStation;
	CString	m_strTime;
	CString	m_strLevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWarnNoteDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWarnNoteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnWarnnotedlgPrev();
	afx_msg void OnWarnnotedlgNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNNOTEDLG_H__4178DB94_EFAC_4594_9403_95C65ADD076A__INCLUDED_)
