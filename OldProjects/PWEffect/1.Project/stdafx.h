/*****************************************************************************
 * module stdafx.h
 *
 *  This file is used to build a precompiled header (PCH) file named PWEffect.pch 
 *  Miscellaneous classes also are defined here.
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#if !defined(AFX_STDAFX_H_)
#define AFX_STDAFX_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if _USE_MFC
    #define STRICT
    #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0400
    #define _ATL_APARTMENT_THREADED

    #include <afxwin.h>
    #include <afxdisp.h>
    #endif
#endif


#include "debugmacros.h"
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <ddraw.h>

// DXTransform includes
#include <DXTmpl.h>

//Declare module instance defined in stdafx.cpp.
extern HINSTANCE g_hInst;

//Declare global variable to keep track if D3DX is initialized in this module.
extern bool g_fD3DXInitialized;
// 



// regsvr32 /s $(TargetPath)
//#define _ENABLE_GDIPLUS_

#ifdef _ENABLE_GDIPLUS_
    // Add GDI+ Header
    #include <GdiPlus.h>

    #pragma comment( lib, ".\\GDIPlus\\Lib\\gdiplus.lib" )

    using namespace Gdiplus;
#endif


	
	
// STL header and namespace
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <ocidl.h>	// Added by ClassView

using namespace std;
// self-defined collection classes
typedef vector<POINT>   CPointArray;
typedef vector<SIZE>    CSizeArray;
typedef vector<RECT>    CRectArray;
typedef vector<HBITMAP> CHBmpArray;
typedef list<wstring>   CWStrList;
typedef vector<wstring> CWStrArray;


//////////////////////////////////////////////////////////////////////////


//#include <Icm.h>

#include "SmartPtr.h"

/***********************************************************************
 *
 *  Declare smart class for automatic deleting of new'ed memory pointers
 *  when object goes out of scope.
 *
 ***********************************************************************/

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H_)
