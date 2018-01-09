// 这是主 DLL 文件。

#include "stdafx.h"

#include "IscsMock.Interop.h"

using namespace IscsMockInterop;

IscsMockClr::IscsMockClr() 
{
	m_pIscsMock = new IscsMock();
}
IscsMockClr::~IscsMockClr() 
{
	IscsMockClr::!IscsMockClr();
}
IscsMockClr::!IscsMockClr() 
{
	/*if (m_pIscsMock != nullptr)
	{
	delete m_pIscsMock;
	m_pIscsMock = nullptr;
	}*/
}

void IscsMockClr::Initialize()
{
}

long IscsMockClr::GetWindowsId()
{
	return m_pIscsMock->GetWindows();
}


void IscsMockClr::ShowQtWindow(long parent)
{
	m_pIscsMock->ShowWindow(parent);
}