#if !defined(AFX_CHILDMULFRAME_H__925A68E9_3A23_4B2F_AE99_D9282CAC255F__INCLUDED_)
#define AFX_CHILDMULFRAME_H__925A68E9_3A23_4B2F_AE99_D9282CAC255F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChildMulFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildMulFrame frame

class CChildMulFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildMulFrame)
protected:
	CChildMulFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildMulFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChildMulFrame();

	// Generated message map functions
	//{{AFX_MSG(CChildMulFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDMULFRAME_H__925A68E9_3A23_4B2F_AE99_D9282CAC255F__INCLUDED_)
