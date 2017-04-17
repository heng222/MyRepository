/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : Server.dll
*  Created  : 19.11.2006 by H.R.
*  Description: 
*     
*  Version  : 1.0.0.2.3
*  Copyright: Copyright (c) 2007, H.W. Corpor.
* ============================================================================
*/
#ifndef __NBASE_TYPE_DEFINE_FILE_
#define __NBASE_TYPE_DEFINE_FILE_
//////////////////////////////////////////////////////////////////////////

#include <string>

//#ifndef _TSTRING
//#define _TSTRING
#ifdef	_UNICODE
typedef	std::wstring TString;	
#else
typedef std::string TString;
#endif
//#endif

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

//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
#endif