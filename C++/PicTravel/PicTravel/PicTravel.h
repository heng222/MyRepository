// PicTravel.h : PicTravel Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPicTravelApp:
// �йش����ʵ�֣������ PicTravel.cpp
//

class CPicTravelApp : public CWinApp
{
public:
	CPicTravelApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPicTravelApp theApp;