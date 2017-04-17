// MaintainDoc.h : interface of the CMaintainDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINTAINDOC_H__89740C11_6548_4A90_9174_10D460EAFFC2__INCLUDED_)
#define AFX_MAINTAINDOC_H__89740C11_6548_4A90_9174_10D460EAFFC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMaintainDoc : public CDocument
{
protected: // create from serialization only
	CMaintainDoc();
	DECLARE_DYNCREATE(CMaintainDoc)

// Attributes
public:



// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaintainDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMaintainDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:

	//{{AFX_MSG(CMaintainDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINTAINDOC_H__89740C11_6548_4A90_9174_10D460EAFFC2__INCLUDED_)
