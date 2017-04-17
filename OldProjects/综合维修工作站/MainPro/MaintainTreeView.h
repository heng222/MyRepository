#if !defined(AFX_MAINTAINTREEVIEW_H__02588B32_6B9A_4938_98EE_048845C1DA89__INCLUDED_)
#define AFX_MAINTAINTREEVIEW_H__02588B32_6B9A_4938_98EE_048845C1DA89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaintainTreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaintainTreeView view

class CMaintainTreeView : public CTreeView
{
protected:
	CMaintainTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMaintainTreeView)

// Attributes
public:
	CImageList m_ImageList;
// Operations
public:
	HTREEITEM GetItemByName(HWND hWnd, HTREEITEM hItem,LPCTSTR szItemName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaintainTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMaintainTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMaintainTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINTAINTREEVIEW_H__02588B32_6B9A_4938_98EE_048845C1DA89__INCLUDED_)
