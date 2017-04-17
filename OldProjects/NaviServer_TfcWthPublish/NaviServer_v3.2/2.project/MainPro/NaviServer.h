// NaviServer.h : main header file for the NAVISERVER application
//

#if !defined(AFX_NAVISERVER_H__9E0B1514_A816_467B_847F_E1052FCFE2BD__INCLUDED_)
#define AFX_NAVISERVER_H__9E0B1514_A816_467B_847F_E1052FCFE2BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols



///////////////////////////////////////////////////////////////////////////

#include "ModuleDispatch.h"

//////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// CNaviServerApp:
// See NaviServer.cpp for the implementation of this class
//

class CNaviServerApp : public CWinApp
{
public:

	CNaviServerApp();

	CView* GetView(CRuntimeClass *pViewClass);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNaviServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CNaviServerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

private:

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVISERVER_H__9E0B1514_A816_467B_847F_E1052FCFE2BD__INCLUDED_)
