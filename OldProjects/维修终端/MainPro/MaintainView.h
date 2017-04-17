// MaintainView.h : interface of the CMaintainView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINTAINVIEW_H__21574762_E20A_4439_9561_8F40E3520112__INCLUDED_)
#define AFX_MAINTAINVIEW_H__21574762_E20A_4439_9561_8F40E3520112__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MaintainDoc.h"

class CMaintainView : public CScrollView
{
protected: // create from serialization only
	CMaintainView();
	DECLARE_DYNCREATE(CMaintainView)

// Attributes
public:
	CMaintainDoc* GetDocument();
		
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaintainView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:


	
	virtual ~CMaintainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	

private:

   
// Generated message map functions
protected:
	//{{AFX_MSG(CMaintainView)
	afx_msg void OnOperateConstructquery();
	afx_msg void OnOperatorConstructrequest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MaintainView.cpp
inline CMaintainDoc* CMaintainView::GetDocument()
   { return (CMaintainDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINTAINVIEW_H__21574762_E20A_4439_9561_8F40E3520112__INCLUDED_)
