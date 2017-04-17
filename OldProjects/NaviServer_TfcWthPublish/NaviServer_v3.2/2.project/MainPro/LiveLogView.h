// NaviServerView.h : interface of the CNaviServerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NAVISERVERVIEW_H__F0829BB4_AFFA_4F01_B9C5_9C3B1650C423__INCLUDED_)
#define AFX_NAVISERVERVIEW_H__F0829BB4_AFFA_4F01_B9C5_9C3B1650C423__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxcmn.h"
#include "NaviServerDoc.h"
#include "SortListCtrl.h"
#include "NetLogDlg.h"
#include "InterfaceEx.h"

class CLiveLogView : public CFormView
{
protected: // create from serialization only
	CLiveLogView();
	DECLARE_DYNCREATE(CLiveLogView)

public:
	//{{AFX_DATA(CNaviServerView)
	enum{ IDD = IDD_NAVISERVER_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
    //enum {}; // 最小高度
	CNaviServerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNaviServerView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLiveLogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNaviServerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CSortListCtrl m_ctrlList;
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

private:
	CMenu	m_LogMenu;

public:
	afx_msg void OnLogMenuDelSel();
	afx_msg void OnLogClear();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);

public:
    void AddLiveLog(PIMsgAppLogs pNewLog);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

#ifndef _DEBUG  // debug version in NaviServerView.cpp
inline CNaviServerDoc* CLiveLogView::GetDocument()
   { return (CNaviServerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVISERVERVIEW_H__F0829BB4_AFFA_4F01_B9C5_9C3B1650C423__INCLUDED_)
