// MouseHook.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#define _COMPILING_44E531B1_14D3_11d5_A025_006067718D04
#include "MouseHook.h"

#pragma data_seg(".JOE")
HWND   g_hWndServer     = NULL;
HHOOK  g_hHook          = NULL;
UINT   UWM_MOUSEMOVE    = 0;
UINT   UWM_CHAR         = 0;
#pragma data_seg()
#pragma comment(linker, "/section:.JOE,rws")


HINSTANCE g_hInst;

static LRESULT CALLBACK Msghook(UINT nCode, WPARAM wParam, LPARAM lParam);

BOOL APIENTRY DllMain( HINSTANCE hInstance, 
                       DWORD  Reason, 
                       LPVOID Reserved)
{
    switch(Reason)
    { 
    case DLL_PROCESS_ATTACH:
        g_hInst = hInstance;
        UWM_MOUSEMOVE = RegisterWindowMessage(UWM_MOUSEMOVE_MSG);
        UWM_CHAR = ::RegisterWindowMessage(UWM_CHAR_MSG);

        return TRUE;
        
    case DLL_PROCESS_DETACH:
        if(g_hWndServer != NULL)
            ClearMyHook(g_hWndServer);
        return TRUE;
    } 
    return TRUE;
}

/****************************************************************************
*                                 setMyHook
* Inputs:
*       HWND hWnd: Window to notify
* Result: BOOL
*       TRUE if successful
*	FALSE if error
* Effect: 
*       Sets the hook
****************************************************************************/

BOOL SetMyHook(HWND hWnd)
{
    if(g_hWndServer != NULL)
        return FALSE; // already hooked!

    g_hHook = SetWindowsHookEx(WH_GETMESSAGE,
                    (HOOKPROC)Msghook,
                    g_hInst,
                    0);

    if(g_hHook != NULL)
    { 
        g_hWndServer = hWnd;
        return TRUE;
    } 
    return FALSE; // failed to set hook
} 

  /****************************************************************************
  *                                 clearMyHook
  * Inputs:
  *       HWND hWnd: Window hook
  * Result: BOOL
  *       TRUE if successful
  *	FALSE if error
  * Effect: 
  *       Removes the hook that has been set
****************************************************************************/

BOOL ClearMyHook(HWND hWnd)
{
    if(hWnd != g_hWndServer || hWnd == NULL)
        return FALSE;
    BOOL unhooked = UnhookWindowsHookEx(g_hHook);
    if(unhooked)
        g_hWndServer = NULL; 
    return unhooked;
} 

  /****************************************************************************
  *                                   Msghook
  * Inputs:
  *       int nCode: Code value
  *	WPARAM wParam:
  *	LPARAM lParam:
  * Result: LRESULT
  *       Either 0 or the result of CallNextHookEx
  * Effect: 
  *       Hook processing function. If the message is a mouse-move message,
  *	posts the coordinates to the parent window
****************************************************************************/

static LRESULT CALLBACK Msghook(UINT nCode, WPARAM wParam, LPARAM lParam)
{
    if(nCode < 0)
    { 
        CallNextHookEx(g_hHook, nCode, wParam, lParam);
        return 0;
    }

    LPMSG msg = (LPMSG)lParam;
    if(msg->message == WM_MOUSEMOVE || msg->message == WM_NCMOUSEMOVE)
    {
        PostMessage(g_hWndServer, UWM_MOUSEMOVE, 0, 0);
    }
    else if (msg->message==WM_CHAR)
    {
        PostMessage(g_hWndServer, UWM_CHAR, msg->wParam, msg->lParam);
    }

    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
} 
 