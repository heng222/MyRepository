#if !defined(AFX_MULTSTAVIEW_H__7DE6E042_E688_4BC9_AC72_D750EC9E8865__INCLUDED_)
#define AFX_MULTSTAVIEW_H__7DE6E042_E688_4BC9_AC72_D750EC9E8865__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultStaView.h : header file
//
#include "MaintainDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CMultStaView view

class CMultStaView : public CScrollView
{
protected:
	CMultStaView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMultStaView)

// Attributes
public:
	CMaintainDoc* GetDocument();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultStaView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMultStaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMultStaView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MaintainView.cpp
inline CMaintainDoc* CMultStaView::GetDocument()
   { return (CMaintainDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTSTAVIEW_H__7DE6E042_E688_4BC9_AC72_D750EC9E8865__INCLUDED_)
