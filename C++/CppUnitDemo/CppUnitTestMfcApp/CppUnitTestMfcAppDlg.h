// CppUnitTestMfcAppDlg.h : header file
//

#if !defined(AFX_CPPUNITTESTMFCAPPDLG_H__7ECBE2F2_3E19_48F9_AB30_F127D47C56B2__INCLUDED_)
#define AFX_CPPUNITTESTMFCAPPDLG_H__7ECBE2F2_3E19_48F9_AB30_F127D47C56B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCppUnitTestMfcAppDlg dialog

class CCppUnitTestMfcAppDlg : public CDialog
{
// Construction
public:
	CCppUnitTestMfcAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCppUnitTestMfcAppDlg)
	enum { IDD = IDD_CPPUNITTESTMFCAPP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCppUnitTestMfcAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCppUnitTestMfcAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPUNITTESTMFCAPPDLG_H__7ECBE2F2_3E19_48F9_AB30_F127D47C56B2__INCLUDED_)
