// AuxApp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������

// CAuxAppApp:
// �йش����ʵ�֣������ AuxApp.cpp
//

class CAuxAppApp : public CWinApp
{
public:
	CAuxAppApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAuxAppApp theApp;
