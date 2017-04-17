/*****************************************************************************
 * module MMSTFX.cpp 
 *
 *	Main module for DLL.  Defines ATL _Module object, object map entries for
 *  COM objects, and DLL entry points supplied by this DLL.
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#include "stdafx.h"
#include "DXTrans.h"
#include <dxtguid.c>
#include "resource.h"
#include "initguid.h"
#include "MMSTFX.h"
#include "MMSTFX_i.c"
#include "MMSpecialEffectDXT.h"
#include "d3dx.h"

CComModule _Module;

//Global flag to prevent D3DX from multi-initialization.
bool g_fD3DXInitialized = false;

//COM object map.  Defines mapping of COM CLSID's to C++ objects which this DLL can serve. 
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_MMSampleEffect, CMMSampleEffect)	   
	OBJECT_ENTRY(CLSID_MMSampleTransition, CMMSampleTransition)	 
END_OBJECT_MAP()

/*****************************************************************************
 * DLL Entry Point
 ****************************************************************************/
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_hInst = static_cast<HINSTANCE>(hInstance);
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		//Unitialized D3DX when DLL is unloaded.
		if (g_fD3DXInitialized)
		{
			D3DXUninitialize();
			g_fD3DXInitialized = false;
		}

		_Module.Term();
	}
	return TRUE;    // ok
}

/*****************************************************************************
 * Used to determine whether the DLL can be unloaded by OLE
 ****************************************************************************/
STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/*****************************************************************************
 * Returns a class factory to create an object of the requested type
 ****************************************************************************/
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{		
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/*****************************************************************************
 * DllRegisterServer - Adds entries to the system registry
 ****************************************************************************/
STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	RTN_HR_IF_FAILED(_Module.RegisterServer(TRUE));
	RTN_HR_IF_FAILED(CMMSampleEffect::UpdateRegistry(true));
	RTN_HR_IF_FAILED(CMMSampleTransition::UpdateRegistry(true));

	return S_OK;
}

/*****************************************************************************
 * DllUnregisterServer - Removes entries from the system registry
 ****************************************************************************/
STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	RTN_HR_IF_FAILED(CMMSampleTransition::UpdateRegistry(false));
	RTN_HR_IF_FAILED(CMMSampleTransition::UpdateRegistry(false));

	return S_OK;
}


