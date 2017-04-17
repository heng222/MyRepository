/*
* ============================================================================
*  Name     : microunion type define
*  Part of  : MuSys.dll
*  Created  : 19.11.2006 by MU.
*  Description: 
*     
*  Version  : 1.0.0.2
*  Copyright: Copyright (c) 2007, MU Corpor.
* ============================================================================
*/
#ifndef __MUTYPE_H_DEFINE_FILE_89YU23BHDY6
#define __MUTYPE_H_DEFINE_FILE_89YU23BHDY6
//////////////////////////////////////////////////////////////////////////

#include <list>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
#include <comutil.h>
#include <string>
#include <iostream>
#include <io.h> 
#include <stdlib.h>
#include <stdio.h>

// TString
#ifndef _TSTRING
#define _TSTRING
    #ifdef	_UNICODE
        typedef	std::wstring TString;	
    #else
        typedef std::string TString;
    #endif
#endif

typedef char NB_CHAR;
typedef unsigned char NB_UCHAR;
typedef unsigned char NB_BYTE;
typedef char* NB_LPSTR;

typedef short NB_SHORT;
typedef unsigned short NB_USHORT;
typedef unsigned short NB_WORD;

typedef unsigned int NB_UINT;
typedef int NB_INT;

typedef unsigned long NB_ULONG;
typedef long NB_BOOL;


#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//////////////////////////////////////////////////////////////////////////

// 
#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef IN_OUT
#define IN_OUT
#endif

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

#ifdef _BASIC_CLASS_PROJECT_
#define BSCEG_EXT_API __declspec(dllexport)
#else
#define BSCEG_EXT_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////

#ifndef _BASIC_CLASS_PROJECT_
#ifdef _DEBUG
#ifdef _UNICODE
#pragma comment( lib, "MuSysUD" )
#else
#pragma comment( lib, "MuSysD" )
#endif
#else
#ifdef _UNICODE
#pragma comment( lib, "MuSysU" )
#else
#pragma comment( lib, "MuSys" )
#endif
#endif
#endif


//////////////////////////////////////////////////////////////////////////
#endif