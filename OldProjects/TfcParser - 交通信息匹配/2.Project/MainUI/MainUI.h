// MainUI.h : MainUI Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������

#include "DlgAppStart.h"
#include "ModuleDispatch.h"


// CMainUIApp:
// �йش����ʵ�֣������ MainUI.cpp
//

class CMainUIApp : public CWinApp
{
public:
	CMainUIApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
    virtual int ExitInstance();
    CView* GetView(CRuntimeClass *pViewClass);
};

extern CMainUIApp theApp;
