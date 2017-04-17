/*****************************************************************************
 * module stdafx.h
 *
 *  This file is used to build a precompiled header (PCH) file named MMSTFX.pch 
 *  Miscellaneous classes also are defined here.
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#if !defined(AFX_STDAFX_H_)
#define AFX_STDAFX_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "debugmacros.h"

#include <atlbase.h>

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <ddraw.h>

//DXTransform includes
#include <DXTmpl.h>

//Declare module instance defined in stdafx.cpp.
extern HINSTANCE g_hInst;

//Declare global variable to keep track if D3DX is initialized in this module.
extern bool g_fD3DXInitialized;
//
//#pragma comment(lib,"D:\\Program Files\\DMSDK6\\lib\\d3dx.lib")
//#pragma comment(lib,"D:\\Program Files\\DMSDK6\\lib\\DXTrans.lib")

/***********************************************************************
 *
 *  Declare smart class for automatic deleting of new'ed memory pointers
 *  when object goes out of scope.
 *
 ***********************************************************************/

//Ignore UDT boundary warning on WORD size data.
//Note: Do not use the arrow operator with WORD-sized data.
#pragma warning( push )
#pragma warning( disable : 4284 ) 

template<class TYPE>
class CSmartPtr
{
public:
	CSmartPtr(TYPE*	pc = NULL)
	{
		m_pc = pc;
	}

	~CSmartPtr(void)
	{
		if (m_pc !=	NULL)
			delete m_pc;
	}

	operator TYPE*() const
	{
		return (TYPE*)m_pc;
	}

	TYPE* operator ->(void)
	{
		return m_pc;
	}

	const TYPE*	operator ->(void) const
	{
		return m_pc;
	}

	TYPE& operator *(void)
	{
		return *m_pc;
	}

	const TYPE&	operator *(void) const
	{
		return *m_pc;
	}

	TYPE** operator&(void)
	{
		return &m_pc;
	};

	int	operator == (TYPE* pPtr) const
	{
		return (m_pc == pPtr);
	}

	int	operator != (TYPE* pPtr) const
	{
		return (m_pc != pPtr);
	}

	operator TYPE* &(void)
	{
	return m_pc;
	}

	TYPE* Detach()
	{
		TYPE* pPtr = m_pc;
		m_pc = NULL;
		return pPtr;
	}

	HRESULT Attach(TYPE* pPtr)
	{
		RTN_HR_IF_FALSE(!m_pc);
		m_pc = pPtr;
		return pPtr;
	}
	HRESULT Delete()
	{
		if(m_pc)
		{
			delete m_pc;
			m_pc = NULL;
		}
		return S_OK;
	}

	TYPE* operator = (TYPE* pPtr)
	{
		if(&pPtr != &m_pc)
		{
			Delete();
			m_pc = pPtr;
		}
		return pPtr;
	}

	TYPE* m_pc;

private:
	const CSmartPtr<TYPE>& operator = (const CSmartPtr<TYPE>& autoPtr);
	CSmartPtr(const CSmartPtr<TYPE>&);
};


#pragma warning( pop )

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H_)
