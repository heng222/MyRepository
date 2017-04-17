// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once


#ifndef IN_OUT
#define IN_OUT
#endif

#include <Windows.h>
#include <assert.h>

// STL header and namespace
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#ifdef _UNICODE
typedef std::wstring        TString;
#else
typedef std::string         TString;
#endif
 
// self-defined collection classes
typedef vector<POINT>   CPointArray;
typedef vector<SIZE>    CSizeArray;
typedef vector<HBITMAP> CHBmpArray;
typedef list<wstring>   CWStrList;
typedef vector<wstring> CWStrArray;



// GDI+ header and Library.
#include <GdiPlus.h>
#pragma comment( lib, "gdiplus.lib" )
typedef Gdiplus::Color GpClr;

// CLR namespace
using namespace System;
using namespace System::Diagnostics;

// CLR_ASSERT 
#ifdef _DEBUG
    #define CLR_ASSERT(expression)  Debug::Assert(expression)
#else
    #define CLR_ASSERT(expression)
#endif

// CLR_TRACE
#ifdef _DEBUG
    #define CLR_TRACE(expression)  Console::Write(expression)
#else
    #define CLR_TRACE(expression)
#endif

