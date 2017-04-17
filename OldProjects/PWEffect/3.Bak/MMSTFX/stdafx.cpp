/*****************************************************************************
 * module stdafx.cpp
 *
 *  These files are used to build a precompiled types file named StdAfx.obj.  
 *  Miscellaneous debugging methods also are defined here.
 *
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#include "stdafx.h"
#include "assert.h"

//Include standard DXT base class CDXBaseNTo1.  Note this class defines it's own NEW allocator.
//Push the current new macro and restore it after dtbase.cpp is compiled.
//Note: is OK if this generates warning 4601: 'new' is not currently defined as a macro.

#pragma warning( push )
#pragma warning( disable : 4601 ) 

#pragma push_macro("new")
#undef new
#include <dtbase.cpp>
#pragma pop_macro("new")

#pragma warning( pop )

//Store a global handle to this module's instance.
HINSTANCE g_hInst;

//Define AssertMessage function used by RTN_ macros declared in DebugMacros.h.
#ifdef DEBUG
bool __stdcall AssertMessage(LPCSTR lpszFile, int wLine, LPCWSTR lpcwszBody, LPCSTR szExpression,
								HINSTANCE hinstSrcModule, DWORD dwLastError, HRESULT hrReturn, bool fRtnHR)
{
	AtlTrace(L"ASSERT!  File: %s, Line: %d, Expression: %s\n", lpszFile, wLine, szExpression);
	assert(false);
	return true;
}
bool __stdcall AssertMessage(LPCSTR lpszFile, int wLine, LPCSTR lpcwszBody, LPCSTR szExpression,
								HINSTANCE hinstSrcModule, DWORD dwLastError, HRESULT hrReturn, bool fRtnHR)
{
	AtlTrace(L"ASSERT!  File: %s, Line: %d, Expression: %s\n", lpszFile, wLine, szExpression);
	assert(false);
	return true;
}
#endif
