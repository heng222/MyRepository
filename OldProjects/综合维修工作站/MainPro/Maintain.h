// Maintain.h : main header file for the MAINTAIN application
//

#if !defined(AFX_MAINTAIN_H__C36A8E0D_57A5_4D06_BB25_15D862669ECF__INCLUDED_)
#define AFX_MAINTAIN_H__C36A8E0D_57A5_4D06_BB25_15D862669ECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include <MMSYSTEM.H>

//typedef unsigned char BYTE;
/////////////////////////////////////////////////////////////////////////////
// CMaintainApp:
// See Maintain.cpp for the implementation of this class
//

class CMaintainApp : public CWinApp
{
public:
	CZCTMag		m_ZCTMag;

	//
	CMultiDocTemplate*  m_pSingleStaDocTemplate;
	CMultiDocTemplate*  m_pMultiStatDocTemplate;

	
	//系统工作路径
	CString m_strExePath;

	//系统连接数据库的服务名,用户名,口令
	CString m_strDBDataSource,m_strDBUserID,m_strDBPassword;
	
	//
	BOOL m_bMove;
	//---------------------------------------------------------------------------

public:
	CView* GetView(CRuntimeClass* pViewClass );
	
	CMaintainApp();
	
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaintainApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
	//{{AFX_MSG(CMaintainApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsOneInstance();
	BOOL initStatus();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINTAIN_H__C36A8E0D_57A5_4D06_BB25_15D862669ECF__INCLUDED_)
