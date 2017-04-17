

#ifndef _COMMON_DEFINATION_
#define _COMMON_DEFINATION_

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <list>
#include <algorithm>
#include <math.h>
#include <comutil.h>
#include <vector>
#include <map>
using namespace std;

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


// TString definition
#ifdef _UNICODE
typedef std::wstring    TString;
#else
typedef std::string    TString;
#endif

// 


//////////////////////////////////////////////////////////////////////////
#endif