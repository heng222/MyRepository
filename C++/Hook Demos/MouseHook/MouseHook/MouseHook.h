#ifndef _DEFINED_44E531B1_14D3_11d5_A025_006067718D04
#define _DEFINED_44E531B1_14D3_11d5_A025_006067718D04

#include "StdAfx.h"
#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
    
#ifdef _COMPILING_44E531B1_14D3_11d5_A025_006067718D04
    #define LIBSPEC __declspec(dllexport)
#else
    #define LIBSPEC __declspec(dllimport)
#endif 

    LIBSPEC BOOL SetMyHook(HWND hWnd);
    LIBSPEC BOOL ClearMyHook(HWND hWnd);

#ifdef __cplusplus
}
#endif // __cplusplus

#define UWM_MOUSEMOVE_MSG _T("UWM_MOUSEMOVE_MSG-44E531B1_14D3_11d5_A025_006067718D04")
#define UWM_CHAR_MSG      _T("{31C856F4-2D17-49dc-89DC-75232AE298E2}")

// These declarations are because the latest SDK isn't installed...
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(p) ((int)(short)LOWORD(p))
#define GET_Y_LPARAM(p) ((int)(short)HIWORD(p))
#endif

#endif // _DEFINED_44E531B1_14D3_11d5_A025_006067718D04

