// GDI+Sample.h : GDI+Sample Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGDISampleApp:
// �йش����ʵ�֣������ GDI+Sample.cpp
//

class CGDISampleApp : public CWinApp
{
public:
	CGDISampleApp();


	ULONG_PTR m_gdiplusToken;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

extern CGDISampleApp theApp;