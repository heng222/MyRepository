//---------------------------------------------------------------------------
//
// SysUtils.h
//
// SUBSYSTEM:   
//				
// MODULE:      
//				
// DESCRIPTION: Common utilities. 
//              Provides interface and implementation of some frequently
//              used functions
// 
//             
// AUTHOR:		Ivo Ivanov (ivopi@hotmail.com)
// DATE:		2001 December v1.00
//
//---------------------------------------------------------------------------
#ifndef _SYSUTILS_H_3A92167D
#define _SYSUTILS_H_3A92167D


#include "stdafx.h"
#include <TlHelp32.h>
#include <vector>

//
#define UWM_CHAR_MSG      _T("{31C856F4-49dc-2D17-89DC-AE298E275232}")

class AFX_EXT_CLASS CSysUtils
{
private:

	CSysUtils();
	~CSysUtils();

	// Operation System
public:

	//---------------------------------------------------------------------------
	// IsWindows9x
	//
	//
	//---------------------------------------------------------------------------
	static BOOL IsWindows9x();

	//---------------------------------------------------------------------------
	// IsWindowsNT4
	//
	// Inspect whether the OS is Windows NT4
	//---------------------------------------------------------------------------
	static BOOL IsWindowsNT4() ;


	//---------------------------------------------------------------------------
	// IsToolHelpSupported
	//
	//
	//---------------------------------------------------------------------------
	static BOOL IsToolHelpSupported();


	//---------------------------------------------------------------------------
	// IsPsapiSupported
	//
	//
	//---------------------------------------------------------------------------
	static BOOL IsPsapiSupported();

	// Process and Thread
public:

	// Get the information of processes specified by lpctProcessName.
	// if lpctProcessName is null, return all processes in the system.
	static INT GetProcessInfo( std::vector<PROCESSENTRY32>& peArray,
		LPCTSTR lpctName=NULL);

	// Get the information of threads in the specified process.
	// th32ProcessID parameter can be zero to indicate the current process. 
	static INT GetThreadInfo( std::vector<THREADENTRY32>& teArray,
		DWORD th32ProcessID );


	// Process path and name
public:

	//---------------------------------------------------------------------------
	// GetProcessHostFullName
	//
	// Return the path and the name of the current process
	//---------------------------------------------------------------------------
	static BOOL GetProcessHostFullName(LPTSTR pszFullFileName);


	//---------------------------------------------------------------------------
	// GetProcessHostName
	//
	// Return the name of the current process
	//---------------------------------------------------------------------------
	static BOOL GetProcessHostName(LPTSTR pszFullFileName);

	//---------------------------------------------------------------------------
	// GetProcessHostPath
	//
	// Return the path of the current process
	//---------------------------------------------------------------------------
	static BOOL GetProcessHostPath(LPTSTR pszPath);

public:

	//---------------------------------------------------------------------------
	// ModuleFromAddress
	//
	// Returns the HMODULE that contains the specified memory address
	//---------------------------------------------------------------------------
	static HMODULE ModuleFromAddress(PVOID pv) ;

	//---------------------------------------------------------------------------
	// ReplaceFileName
	//
	//---------------------------------------------------------------------------
	static BOOL ReplaceFileName(
		LPTSTR pszOldFileName,
		LPTSTR pszBaseNewFileName,
		LPTSTR pszNewFileName
		);

	//---------------------------------------------------------------------------
	// ReplaceFileName
	//
	//---------------------------------------------------------------------------
	static BOOL ReplaceFileName(
		HINSTANCE hOldFile,
		LPTSTR    pszBaseNewFileName,
		LPTSTR    pszNewFileName
		);

public:

	static BOOL LanuchHook(HWND hWnd,LPCTSTR lpctHostProcess);
    static BOOL UnHook();
};

//--------------------- End of the file -------------------------------------
#endif //_SYSUTILS_H_