// NaviServerDoc.h : interface of the CNaviServerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NAVISERVERDOC_H__E389B16E_CDBC_4FA5_AD77_4DFA7B5F774D__INCLUDED_)
#define AFX_NAVISERVERDOC_H__E389B16E_CDBC_4FA5_AD77_4DFA7B5F774D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNaviServerDoc : public CDocument
{
protected: // create from serialization only
	CNaviServerDoc();
	DECLARE_DYNCREATE(CNaviServerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNaviServerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNaviServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNaviServerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVISERVERDOC_H__E389B16E_CDBC_4FA5_AD77_4DFA7B5F774D__INCLUDED_)
