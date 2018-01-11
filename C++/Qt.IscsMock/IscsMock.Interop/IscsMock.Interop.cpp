// 这是主 DLL 文件。

#include "stdafx.h"

#include "qwindowdefs_win.h"
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

void IscsMockClr::Initialize(IntPtr parent)
{
	WId id = (WId)parent.ToInt64();
	m_pIscsMock->Open(id);
}

IntPtr IscsMockClr::GetWindowsId()
{
	return IntPtr(m_pIscsMock->GetWindows());
}


void IscsMockClr::ShowWindow()
{
	m_pIscsMock->ShowWindow();
}