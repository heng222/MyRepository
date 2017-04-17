#if !defined(AFX_APPSTARTDLG_H__E9780858_9646_4F8D_B5CF_51AB1F57B61D__INCLUDED_)
#define AFX_APPSTARTDLG_H__E9780858_9646_4F8D_B5CF_51AB1F57B61D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppStartDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppStartDlg dialog

class CAppStartDlg : public CDialog
{
// Construction
public:
	void SetInformation(const CString& strInf);
	CAppStartDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAppStartDlg)
	enum { IDD = IDD_DIALOG_LOGPRO };
	CStatic	m_ctrlInfor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppStartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAppStartDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPSTARTDLG_H__E9780858_9646_4F8D_B5CF_51AB1F57B61D__INCLUDED_)
