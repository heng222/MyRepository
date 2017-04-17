
#include "stdafx.h"

#include <string.h>
#include <stdio.h>
#include "SysUtils.h"


//---------------------------------------------------------------------------
// IsToolHelpSupported
//
//
//---------------------------------------------------------------------------
BOOL CSysUtils::IsToolHelpSupported()
{

    BOOL    bResult(FALSE);
    HMODULE hModToolHelp;
    PROC    pfnCreateToolhelp32Snapshot;

    hModToolHelp = ::LoadLibrary( _T("KERNEL32.DLL") );
    if (NULL != hModToolHelp)
    {
        pfnCreateToolhelp32Snapshot = ::GetProcAddress( 
            hModToolHelp,
            ("CreateToolhelp32Snapshot"));
        bResult = (NULL != pfnCreateToolhelp32Snapshot);
        ::FreeLibrary(hModToolHelp);
    } // if

    return bResult;
}


//---------------------------------------------------------------------------
// IsPsapiSupported
//
//
//---------------------------------------------------------------------------
BOOL CSysUtils::IsPsapiSupported()
{
    BOOL bResult = FALSE;
    HMODULE hModPSAPI = NULL;

    hModPSAPI = ::LoadLibrary( _T("PSAPI.DLL" ));
    bResult = (NULL != hModPSAPI);
    if (NULL != hModPSAPI)
        ::FreeLibrary(hModPSAPI);

    return bResult;
}

//---------------------------------------------------------------------------
// IsWindows9x
//
//
//---------------------------------------------------------------------------
BOOL CSysUtils::IsWindows9x() 
{
    BOOL bResult = FALSE;
    OSVERSIONINFO vi = { sizeof(vi) };

    ::GetVersionEx(&vi);
    if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) 
        bResult = TRUE;

    return bResult;
}


//---------------------------------------------------------------------------
// IsWindowsNT4
//
// Inspect whether the OS is Windows NT4
//---------------------------------------------------------------------------
BOOL CSysUtils::IsWindowsNT4() 
{
    OSVERSIONINFO vi = { sizeof(vi) };

    ::GetVersionEx(&vi);

    return ( (vi.dwPlatformId == VER_PLATFORM_WIN32_NT) && 
        (vi.dwMajorVersion == 4) );
}

//---------------------------------------------------------------------------
// ModuleFromAddress
//
// Returns the HMODULE that contains the specified memory address
//---------------------------------------------------------------------------
HMODULE CSysUtils::ModuleFromAddress(PVOID pv) 
{
    MEMORY_BASIC_INFORMATION mbi;

    return ((::VirtualQuery(pv, &mbi, sizeof(mbi)) != 0) 
        ? (HMODULE) mbi.AllocationBase : NULL);
}

//---------------------------------------------------------------------------
// GetProcessHostFullName
//
// Return the path and the name of the current process
//---------------------------------------------------------------------------
BOOL CSysUtils::GetProcessHostFullName(LPTSTR pszFullFileName)
{
    DWORD dwResult = 0;
    ::ZeroMemory(pszFullFileName, MAX_PATH);
    if (TRUE != ::IsBadReadPtr((PBYTE)pszFullFileName, MAX_PATH))
        dwResult = ::GetModuleFileName(
        NULL,                   // handle to module
        pszFullFileName,        // file name of module
        MAX_PATH                // size of buffer
        );

    return (dwResult != 0);
}


//---------------------------------------------------------------------------
// GetProcessHostName
//
// Return the name of the current process
//---------------------------------------------------------------------------
BOOL CSysUtils::GetProcessHostName(LPTSTR pszFullFileName)
{
    BOOL  bResult;

    int   ch = '\\';

    bResult = GetProcessHostFullName(pszFullFileName);
    if (bResult)
    {        
        LPTSTR pdest;
        int   ch = '\\';

        // Search backward 
        pdest = _tcsrchr(pszFullFileName, ch);
        if( pdest != NULL )
        {
            _tcscpy_s(pszFullFileName,MAX_PATH, &pdest[1]);
        }

        bResult = TRUE;
    }

    return bResult;
}

//---------------------------------------------------------------------------
// GetProcessHostPath
//
// Return the path of the current process
//---------------------------------------------------------------------------
BOOL CSysUtils::GetProcessHostPath(LPTSTR pszPath)
{
    BOOL  bResult;

    int   ch = '\\';

    bResult = GetProcessHostFullName(pszPath);
    if (bResult)
    {        
        LPTSTR pdest;
        int   ch = '\\';

        // Search backward 
        pdest = _tcsrchr(pszPath, ch);
        if( pdest != NULL )
        {
            pdest[1] = 0;
            //_tcscpy_s(pszPath,MAX_PATH, &pdest[1]);
        }

        bResult = TRUE;
    }

    return bResult;
}

//---------------------------------------------------------------------------
// ReplaceFileName
//
//---------------------------------------------------------------------------
BOOL CSysUtils::ReplaceFileName(LPTSTR pszOldFileName,
                            LPTSTR pszBaseNewFileName,
                            LPTSTR pszNewFileName
                            )
{
    BOOL  bResult = FALSE;
    LPTSTR pdest;
    int   ch = '\\';

    if ( 
        (TRUE != ::IsBadReadPtr(pszOldFileName, _tcslen(pszOldFileName) + 1))  &&
        (TRUE != ::IsBadReadPtr(pszBaseNewFileName, _tcslen(pszBaseNewFileName) + 1))
        )
    {
        if (TRUE != ::IsBadReadPtr(pszNewFileName, MAX_PATH))
        {
            ::ZeroMemory(pszNewFileName, sizeof(MAX_PATH));
            _tcscpy_s(pszNewFileName, MAX_PATH,pszOldFileName);

            // Search backward and replaces the dll name with the hook one
            pdest = _tcsrchr(pszNewFileName, ch);
            if( pdest != NULL )
                _tcscpy_s(&pdest[1], MAX_PATH,pszBaseNewFileName);
            else
                _tcscpy_s(pszNewFileName, MAX_PATH,pszBaseNewFileName);

            bResult = TRUE;
        }
    }

    return bResult;
}

//---------------------------------------------------------------------------
// ReplaceFileName
//
//---------------------------------------------------------------------------
BOOL CSysUtils::ReplaceFileName( HINSTANCE hOldFile,
                            LPTSTR     pszBaseNewFileName,
                            LPTSTR     pszNewFileName
                            )
{
    BOOL  bResult = FALSE;
    TCHAR  szFileName[MAX_PATH];

    if (TRUE != ::IsBadReadPtr(pszBaseNewFileName, _tcslen(pszBaseNewFileName) + 1))
    {
        if (TRUE != ::IsBadReadPtr(pszNewFileName, MAX_PATH))
        {
            ::ZeroMemory(pszNewFileName, sizeof(MAX_PATH));
            if (NULL != hOldFile)
            {
                if (0 != ::GetModuleFileName(hOldFile, szFileName, MAX_PATH))
                    bResult = 
                    ReplaceFileName(
                    szFileName, 
                    pszBaseNewFileName, 
                    pszNewFileName);
            } 
        }
    }

    return bResult;
}


// Enum all processes in current OS.
INT CSysUtils::GetProcessInfo( std::vector<PROCESSENTRY32>& peArray,
                   LPCTSTR lpctName/*=NULL*/)
{
    // Get the list of processes in the system
    // !! Do not call the CloseHandle function to close the snapshot 
    // call. That generates a memory leak.
    HANDLE hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return -1;
    }

    //
    try
    {
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(pe);

        BOOL bOk = ::Process32First(hSnapshot,&pe);
        for (; bOk; bOk=::Process32Next(hSnapshot,&pe))
        {
            if (lpctName==NULL || _tcsicmp(pe.szExeFile,lpctName)==0)
            {
                peArray.push_back(pe);
            }
        }
    }
    catch (...)
    {
        return -1;
    }

    return (INT)(peArray.size());
}

// Get the information of threads in the specified process.
INT CSysUtils::GetThreadInfo( std::vector<THREADENTRY32>& teArray,
                         DWORD th32ProcessID )
{
    // Get the list of threads in the system
    // !! Do not call the CloseHandle function to close the snapshot 
    // call. That generates a memory leak.
    HANDLE hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,th32ProcessID);

    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return -1;
    }

    // Determine the current process ID.
    if (th32ProcessID==0)
    {
        th32ProcessID = ::GetCurrentProcessId();
    }

    // 
    try
    {
        THREADENTRY32 te;
        te.dwSize = sizeof(te);

        BOOL bOk = ::Thread32First(hSnapshot,&te);
        for (; bOk; bOk=::Thread32Next(hSnapshot,&te))
        {
            if (te.th32OwnerProcessID == th32ProcessID)
            {
                teArray.push_back(te);
            }
        }
    }
    catch (...)
    {
        return -1;
    }

    return (INT)(teArray.size());

}




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Hook Example
#pragma data_seg(".MYHOOKS")
HWND        g_hWndServer = NULL;
HHOOK       g_hHook = NULL;
UINT        UWM_HOOK_GETMSG = 0;
#pragma data_seg()
#pragma comment(linker, "/section:.MYHOOKS,rws")

// Variables

static LRESULT CALLBACK Msghook(UINT nCode, WPARAM wParam, LPARAM lParam);

// 
BOOL CSysUtils::LanuchHook(HWND hWnd,LPCTSTR lpctHostProcess)
{
	std::vector<PROCESSENTRY32> peArray;
	CSysUtils::GetProcessInfo(peArray, lpctHostProcess);
 
	std::vector<THREADENTRY32> teArray;
	if (peArray.size()>0)
	{
		CSysUtils::GetThreadInfo(teArray,peArray[0].th32ProcessID);

        
        HINSTANCE hMod = ModuleFromAddress(Msghook);
        if (g_hHook==NULL && g_hWndServer==NULL)
        {
            g_hWndServer = hWnd;
            UWM_HOOK_GETMSG = ::RegisterWindowMessage(UWM_CHAR_MSG);
            g_hHook = ::SetWindowsHookEx(WH_GETMESSAGE,
                        (HOOKPROC)Msghook,
                        hMod,
                        teArray[0].th32ThreadID);
        }
	}


	return (g_hHook!=NULL);
}

BOOL CSysUtils::UnHook()
{
    BOOL unhooked = FALSE;
    if (g_hHook!=NULL)
    {
        unhooked = UnhookWindowsHookEx(g_hHook);
        g_hWndServer = NULL;
        g_hHook = NULL;
    }
    
    return unhooked;
} 

static LRESULT CALLBACK Msghook(UINT nCode, WPARAM wParam, LPARAM lParam)
{
	/*static CString strMsg;	
    if (((DWORD)lParam & 0x40000000) &&(HC_ACTION==nCode))
    {		
        if ( (wParam==VK_SPACE)||
            (wParam==VK_RETURN)||
            (wParam>=0x2f ) &&(wParam<=0x100) ) 
        {

            if (wParam==VK_RETURN)
            {
                strMsg += _T("\n");
            }
            else
            {
                BYTE ks[256];
                GetKeyboardState(ks);

                WORD w;
                UINT scan = 0;
                ToAscii(wParam,scan,ks,&w,0);

                strMsg += CString(TCHAR(w));
            }
            ::MessageBox(NULL,strMsg,_T(""),MB_ICONINFORMATION);
        }

    }

    LRESULT RetVal = CallNextHookEx( g_hHook, nCode, wParam, lParam );	

    return  RetVal;*/
    if(nCode < 0)
    { 
        CallNextHookEx(g_hHook, nCode, wParam, lParam);
        return 0;
    }

    LPMSG msg = (LPMSG)lParam;
    if(msg->message == WM_MOUSEMOVE || msg->message == WM_NCMOUSEMOVE)
    {
        //PostMessage(g_hWndServer, UWM_MOUSEMOVE, 0, 0);
    }
    else if (msg->message==WM_CHAR)
    {
        PostMessage(g_hWndServer, UWM_HOOK_GETMSG, msg->wParam, msg->lParam);
    }

    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

