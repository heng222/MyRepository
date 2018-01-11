// IscsMock.Interop.h

#pragma once
#include <vcclr.h>

#include "..\IscsMock\iscsmock.h"

using namespace System;

namespace IscsMockInterop {

	public ref class IscsMockClr
	{
	public:
		IscsMockClr() ;
		~IscsMockClr();

	protected:

		!IscsMockClr();

	private:
		IscsMock* m_pIscsMock;

	public:

		void Initialize(IntPtr parent);

		IntPtr GetWindowsId();

		void ShowWindow();
	};
}
