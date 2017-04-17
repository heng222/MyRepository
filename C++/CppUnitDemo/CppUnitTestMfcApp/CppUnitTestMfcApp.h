// CppUnitTestMfcApp.h : main header file for the CPPUNITTESTMFCAPP application
//

#if !defined(AFX_CPPUNITTESTMFCAPP_H__2EC7A683_03D1_4F57_BEA0_B645ED5968E4__INCLUDED_)
#define AFX_CPPUNITTESTMFCAPP_H__2EC7A683_03D1_4F57_BEA0_B645ED5968E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCppUnitTestMfcAppApp:
// See CppUnitTestMfcApp.cpp for the implementation of this class
//

class CCppUnitTestMfcAppApp : public CWinApp
{
public:
	CCppUnitTestMfcAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCppUnitTestMfcAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCppUnitTestMfcAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPUNITTESTMFCAPP_H__2EC7A683_03D1_4F57_BEA0_B645ED5968E4__INCLUDED_)
