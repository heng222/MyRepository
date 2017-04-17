/*****************************************************************************
 * module PWEffect.cpp 
 *
 *	Main module for DLL.  Defines ATL _Module object, object map entries for
 *  COM objects, and DLL entry points supplied by this DLL.
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#include "stdafx.h"
#include <DXTrans.h>
#include <dxtguid.c>
#include <initguid.h>
#include "resource.h"

#include "PWEffect.h"
#include "PWEffect_i.c"


#ifdef _ENABLE_3D_
#include "d3dx.h"
#endif

#include "DTOClrAdjust.h"
#include "DTOText.h"
#include "Bijou.h"
#include "PixelPlay.h"
#include "Snow.h"
#include "Flash.h"
#include "Sparkle.h"
#include "Rain.h"
#include "Travel.h"
#include "Bounce.h"
#include "BlackHole.h"
#include "Slot.h"
#include "Filter.h"
#include "Interleave.h"
#include "WrapAround.h"
#include "LineOn.h"
#include "Slide.h"
#include "Wipe.h"
#include "MultiWipe.h"
#include "PushOn.h"
#include "Radar.h"
#include "Venetian.h"
#include "Fade.h"
#include "Coalesce.h"


// Com module
CComModule _Module;

//Global flag to prevent D3DX from multi-initialization.
bool g_fD3DXInitialized = false;

// for GDI+
#ifdef _ENABLE_GDIPLUS_
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
#endif

//COM object map.  Defines mapping of COM CLSID's to C++ objects which this DLL can serve. 
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ClrAdjustEffect, CDTOClrAdjust)
	OBJECT_ENTRY(CLSID_DTOText, CDTOText)
	OBJECT_ENTRY(CLSID_Bijou, CBijou)
	OBJECT_ENTRY(CLSID_PixelPlay, CPixelPlay)
    OBJECT_ENTRY(CLSID_Snow, CSnow)
    OBJECT_ENTRY(CLSID_Sparkle, CSparkle)
	OBJECT_ENTRY(CLSID_Flash, CFlash)
	OBJECT_ENTRY(CLSID_Rain, CRain)
	OBJECT_ENTRY(CLSID_Travel, CTravel)
	OBJECT_ENTRY(CLSID_Bounce, CBounce)
	OBJECT_ENTRY(CLSID_BlackHole, CBlackHole)
	OBJECT_ENTRY(CLSID_Slot, CSlot)
	OBJECT_ENTRY(CLSID_Filter, CFilter)
	OBJECT_ENTRY(CLSID_Interleave, CInterleave)
	OBJECT_ENTRY(CLSID_WrapAround, CWrapAround)
	OBJECT_ENTRY(CLSID_LineOn, CLineOn)
	OBJECT_ENTRY(CLSID_Slide, CSlide)
	OBJECT_ENTRY(CLSID_Wipe, CWipe)
	OBJECT_ENTRY(CLSID_MultiWipe, CMultiWipe)
	OBJECT_ENTRY(CLSID_PushOn, CPushOn)
	OBJECT_ENTRY(CLSID_Radar, CRadar)
	OBJECT_ENTRY(CLSID_Venetian, CVenetian)
	OBJECT_ENTRY(CLSID_Fade, CFade)
	OBJECT_ENTRY(CLSID_Coalesce, CCoalesce)
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

#ifdef _ENABLE_GDIPLUS_
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
#endif

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
        //Unitialized D3DX when DLL is unloaded.
#ifdef _ENABLE_3D_
		if (g_fD3DXInitialized)
		{
			D3DXUninitialize();
			g_fD3DXInitialized = false;
		}
#endif

#ifdef _ENABLE_GDIPLUS_
        GdiplusShutdown(gdiplusToken);
#endif
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

	//RTN_HR_IF_FAILED(CDTOClrAdjust::UpdateRegistry(TRUE));
	
 
	return S_OK;
}

/*****************************************************************************
 * DllUnregisterServer - Removes entries from the system registry
 ****************************************************************************/
STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();

	//RTN_HR_IF_FAILED(CDTOClrAdjust::UpdateRegistry(FALSE));
	

	return S_OK;
}


