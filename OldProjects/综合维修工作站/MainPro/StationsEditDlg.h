#if !defined(AFX_STATIONSEDITDLG_H__094A21F8_B7B8_46F7_999A_9661C7600474__INCLUDED_)
#define AFX_STATIONSEDITDLG_H__094A21F8_B7B8_46F7_999A_9661C7600474__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StationsEditDlg.h : header file
//
class CMainFrame;
/////////////////////////////////////////////////////////////////////////////
// CStationsEditDlg dialog

class CStationsEditDlg : public CDialog
{
// Construction
public:
	CString GetStations();
	CStationsEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStationsEditDlg)
	enum { IDD = IDD_SHOWSTATION_DIALOG };
	CListBox	m_ctrlCurStation;
	CListBox	m_ctrlAllStation;
	CString	m_strAllStation;
	CString	m_strCurStation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStationsEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStationsEditDlg)
	afx_msg void OnSationAdd();
	afx_msg void OnStationDelete();
	afx_msg void OnStationAddall();
	afx_msg void OnStationDelall();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMainFrame* m_pMainFrame;
	//受令站名字列表
	CString m_strStations;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATIONSEDITDLG_H__094A21F8_B7B8_46F7_999A_9661C7600474__INCLUDED_)
