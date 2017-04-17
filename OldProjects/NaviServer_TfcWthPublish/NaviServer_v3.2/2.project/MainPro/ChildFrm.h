// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__176C3234_F4E4_4135_B581_B3A10004522D__INCLUDED_)
#define AFX_CHILDFRM_H__176C3234_F4E4_4135_B581_B3A10004522D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

    enum TViewID
    {
        EVI_TREEVIEW,
        EVI_MAINVIEW,
        EVI_LIVLOGVIEW,
    };

    void ShowView(TViewID viewID);
    void HideView(TViewID viewID);

// Attributes
public:
    CSplitterWnd m_HSplitter;
    CSplitterWnd m_VSplitter;

// Operations
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);

private:
    void SetLayout();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__176C3234_F4E4_4135_B581_B3A10004522D__INCLUDED_)
