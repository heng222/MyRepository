/*****************************************************************************
 * module DebugMacros.h
 *
 *  Declares a series of macros for error handling.  Error handling macros incur
 *  very little overhead in Release builds.  
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#ifndef __DEBUGDLL_H__
#define __DEBUGDLL_H__
#pragma once
#pragma warning( disable : 4511 )  //copy constructor could not be generated


#define DEBUGDLL_API	WINAPI
#define DEBUGDLL_CLASS	

#define SHARED_CONST extern const _declspec(selectany)

/***************************************************************************
 *  DEFINES to get the most out of the Debug CRT library
 *
 **************************************************************************/

// Fix up any of the Debug defines
#if defined(_DEBUG) || defined(DEBUG)
	#ifndef _DEBUG
		#define _DEBUG
	#endif
	#ifndef DEBUG
		#define DEBUG
	#endif
#endif

#ifdef _DEBUG
	#define DEBUG_CODE(X) X
#else
	#define DEBUG_CODE(X)
#endif


#include <windows.h>
#include <crtdbg.h>
#include <Unknwn.h>



#ifdef _DEBUG

bool DEBUGDLL_API AssertMessage(LPCSTR lpszFile, int wLine, LPCWSTR lpcwszBody, LPCSTR szExpression,
								HINSTANCE hinstSrcModule, DWORD	 dwLastError, HRESULT hrReturn, bool fRtnHR);
bool DEBUGDLL_API AssertMessage(LPCSTR lpszFile, int wLine, LPCSTR lpcwszBody, LPCSTR szExpression,
								HINSTANCE hinstSrcModule, DWORD dwLastError, HRESULT hrReturn, bool fRtnHR);

#define DoAssertMessage(szBody, szExpression, dwLastError, hr, rRtnHR)\
	AssertMessage(__FILE__, __LINE__, szBody, szExpression, NULL, dwLastError, hr, rRtnHR)

#define ASSERT_BASE(EXP, SZ)\
	do\
	{\
		DWORD __dwLastErrorBeforeF = GetLastError();\
		SetLastError(NEG_ONE);\
		if(!(EXP))\
		{\
			DWORD __dwNewLastError = GetLastError();\
			if(DoAssertMessage(SZ, #EXP, __dwNewLastError==NEG_ONE ? 0 : __dwNewLastError, 0, false))\
			{\
				_CrtDbgBreak();\
			}\
			if(__dwNewLastError == NEG_ONE)\
			{\
				SetLastError(__dwLastErrorBeforeF);\
			}\
		}\
	}while(0)

#define ASSERT_BASE_HR(HR, SZ)\
	do\
	{\
		DWORD __dwLastErrorBeforeF = GetLastError();\
		SetLastError(NEG_ONE);\
		HRESULT __hrTemp = HR;\
		if(FAILED(__hrTemp))\
		{\
			DWORD __dwNewLastError = GetLastError();\
			if(DoAssertMessage(SZ, #HR, __dwNewLastError==NEG_ONE ? 0 : __dwNewLastError, __hrTemp, false))\
			{\
				_CrtDbgBreak();\
			}\
			if(__dwNewLastError == NEG_ONE)\
			{\
				SetLastError(__dwLastErrorBeforeF);\
			}\
		}\
	}while(0)

#define ASSERT(f)			ASSERT_BASE(f, (LPCTSTR)NULL)
#define ASSERTSZ(f, sz)		ASSERT_BASE(f, sz)		
#define ASSERT_OK(f)		ASSERT_BASE_HR(f, (LPCTSTR)NULL)
#define ASSERTSZ_OK(f, sz)	ASSERT_BASE_HR(f, sz)

#define VERIFY			ASSERT
#define VERIFYSZ		ASSERTSZ
#define VERIFY_OK		ASSERT_OK
#define VERIFYSZ_OK		ASSERTSZ_OK

#else	//_DEBUG

#define ASSERT(f)
#define ASSERTSZ(f, sz)
#define ASSERT_OK(f)
#define ASSERTSZ_OK(f, sz)

#define VERIFY(f)			do{bool fDummy = !(f);fDummy;}while(0)
#define VERIFYSZ(f, sz)		do{bool fDummy = !(f);fDummy;}while(0)
#define VERIFY_OK(f)		do{bool fDummy = !(SUCCEEDED(f));fDummy;}while(0)
#define VERIFYSZ_OK(f, sz)	do{bool fDummy = !(SUCCEEDED(f));fDummy;}while(0)

#define DoAssertMessage(szBody, szExpression, dwLastError, hr, rtnhr) false
#define IGNORE_ASSERT(X)

#endif	//_DEBUG

#ifdef _ASSERTE
#undef _ASSERTE
#define _ASSERTE ASSERT
#endif
 
/***************************************************************************
 *  RTN_XXX_IF_XXX.  Macros to return, continue, or goto when an 
 *  error condition occurs.
 *
 ***************************************************************************/

#define NEG_ONE 0xffffffff
#define INITDIALOG_ERROR -1
#define ShowEndDialogError()\
{\
    ASSERTSZ(false, _T("Error Create Dialog.  Dialog Will Close"));\
}

#define MACRO_BASE_CORE(TYPE, EXP, FUNC, DO_FUNC, HR) \
	do\
	{\
		DEBUG_CODE(DWORD __dwLastErrorBeforeF = GetLastError();)\
		TYPE tempVal = (EXP);\
		if(FUNC(tempVal))\
		{\
			DEBUG_CODE(DWORD __dwNewLastError = GetLastError();)\
			if(DoAssertMessage((LPSTR)NULL, #EXP, __dwNewLastError==NEG_ONE ? 0 : __dwNewLastError, HR, true))\
			{\
				_CrtDbgBreak();\
			}\
			DEBUG_CODE(if(__dwNewLastError == NEG_ONE)\
			{\
				SetLastError(__dwLastErrorBeforeF);\
			}\
			else\
			{\
				SetLastError(__dwNewLastError);\
			})\
			DO_FUNC;\
		}\
	}while(0)

// This one cant be used safly with If statments but continue can't be used inside a do while
#define CONTINUE_BASE_CORE(TYPE, EXP, FUNC, DO_FUNC, HR) \
	{\
		DEBUG_CODE(DWORD __dwLastErrorBeforeF = GetLastError();)\
		TYPE tempVal = (EXP);\
		if(FUNC(tempVal))\
		{\
			DEBUG_CODE(DWORD __dwNewLastError = GetLastError();)\
			if(DoAssertMessage((LPSTR)NULL, #EXP, __dwNewLastError==NEG_ONE ? 0 : __dwNewLastError, HR, true))\
			{\
				_CrtDbgBreak();\
			}\
			DEBUG_CODE(if(__dwNewLastError == NEG_ONE)\
			{\
				SetLastError(__dwLastErrorBeforeF);\
			}\
			else\
			{\
				SetLastError(__dwNewLastError);\
			})\
			DO_FUNC;\
		}\
	}


#define MACRO_BASE_HR(EXP, DO_FUNC) MACRO_BASE_CORE(HRESULT, EXP, FAILED, DO_FUNC, tempVal)
#define MACRO_BASE(TYPE, EXP, FUNC, DO_FUNC) MACRO_BASE_CORE(TYPE, EXP, FUNC, DO_FUNC, S_OK)
#define END_DIALOG_RETURN ShowEndDialogError(); EndDialog(IDABORT); return INITDIALOG_ERROR

#define RTN_BASE(TYPE, EXP, FUNC, RETVAL)	MACRO_BASE(TYPE, EXP, FUNC, return(RETVAL))
#define EXIT_BASE(TYPE, EXP, FUNC)			MACRO_BASE(TYPE, EXP, FUNC, goto Exit)
#define CONTINUE_BASE(TYPE, EXP, FUNC)		CONTINUE_BASE_CORE(TYPE, EXP, FUNC, continue, S_OK)
#define VOID_BASE(TYPE, EXP, FUNC)			MACRO_BASE(TYPE, EXP, FUNC, return)

#define RTN_CUSTOM_IF_FAILED(HR, RETVAL)	MACRO_BASE_HR((HR),	return RETVAL)
#define RTN_CUSTOM_IF_BADPTR(PTR, RETVAL)	RTN_BASE(const void*,	(PTR), NULL==,	RETVAL)
#define RTN_CUSTOM_IF_FALSE(EXP, RETVAL)	RTN_BASE(BOOL,			(EXP), !,		RETVAL)
#define RTN_CUSTOM_IF_NEGONE(EXP, RETVAL)	RTN_BASE(DWORD,			(EXP), NEG_ONE==,RETVAL)
#define RTN_CUSTOM_IF_BADWINDOW(WND, RETVAL)	RTN_CUSTOM_IF_FALSE(::IsWindow(WND), RETVAL)
#define RTN_CUSTOM_IF_TRUE(EXP, RETVAL)		RTN_CUSTOM_IF_FALSE(!(EXP), RETVAL)
#define RTN_CUSTOM_IF_NOTSOK(EXP, RETVAL)	RTN_BASE(HRESULT,		(EXP), S_OK!=,RETVAL)

#define RTN_HR_IF_FAILED(HR)	RTN_CUSTOM_IF_FAILED(HR, tempVal)
#define RTN_HR_IF_BADPTR(PTR)	RTN_CUSTOM_IF_BADPTR(PTR, E_POINTER)
#define RTN_HR_IF_BADNEW(PTR)	RTN_CUSTOM_IF_BADPTR(PTR, E_OUTOFMEMORY)
#define RTN_HR_IF_FALSE(EXP)	RTN_CUSTOM_IF_FALSE(EXP, E_FAIL)
#define RTN_HR_IF_BADWINDOW(W)	RTN_CUSTOM_IF_BADWINDOW(W, E_FAIL)
#define RTN_HR_IF_NEGONE(EXP)	RTN_CUSTOM_IF_NEGONE(EXP, E_FAIL)
#define RTN_HR_IF_TRUE(EXP)		RTN_CUSTOM_IF_TRUE(EXP, E_FAIL)
#define RTN_HR_IF_NOTSOK(EXP)	RTN_CUSTOM_IF_NOTSOK(EXP, E_FAIL)

#define RTN_UNEXPECTED_IF_BADPTR(PTR)	RTN_CUSTOM_IF_BADPTR(PTR, E_UNEXPECTED)
#define RTN_UNEXPECTED_IF_TRUE(EXP)		RTN_CUSTOM_IF_TRUE(EXP, E_UNEXPECTED)
#define RTN_UNEXPECTED_IF_FALSE(EXP)	RTN_CUSTOM_IF_FALSE(EXP, E_UNEXPECTED)
#define RTN_INVALIDARG_IF_BADPTR(PTR)	RTN_CUSTOM_IF_BADPTR(PTR, E_INVALIDARG)
#define RTN_INVALIDARG_IF_TRUE(EXP)		RTN_CUSTOM_IF_TRUE(EXP, E_INVALIDARG)
#define RTN_INVALIDARG_IF_FALSE(EXP)	RTN_CUSTOM_IF_FALSE(EXP, E_INVALIDARG)
#define RTN_POINTER_IF_BADPTR(PTR)		RTN_CUSTOM_IF_BADPTR(PTR, E_POINTER)
#define RTN_FAIL_IF_BADPTR(PTR)			RTN_CUSTOM_IF_BADPTR(PTR, E_FAIL)
#define RTN_OUTOFMEMORY_IF_FALSE(EXP)	RTN_CUSTOM_IF_FALSE(EXP, E_OUTOFMEMORY)

#define RTN_FALSE_IF_FAILED(HR)		RTN_CUSTOM_IF_FAILED(HR, false)
#define RTN_FALSE_IF_BADPTR(PTR)	RTN_CUSTOM_IF_BADPTR(PTR, false)
#define RTN_FALSE_IF_BADNEW(PTR)	RTN_CUSTOM_IF_BADPTR(PTR, false)
#define RTN_FALSE_IF_FALSE(EXP)		RTN_CUSTOM_IF_FALSE(EXP, false)
#define RTN_FALSE_IF_BADWINDOW(W)	RTN_CUSTOM_IF_BADWINDOW(W, false)
#define RTN_FALSE_IF_NEGONE(EXP)	RTN_CUSTOM_IF_NEGONE(EXP, false)
#define RTN_FALSE_IF_TRUE(EXP)		RTN_CUSTOM_IF_TRUE(EXP, false)

#define RTN_TRUE_IF_FAILED(HR)		RTN_CUSTOM_IF_FAILED(HR, true)

#define RTN_VOID_IF_FAILED(HR)		MACRO_BASE_HR((HR),	return)
#define RTN_VOID_IF_BADPTR(PTR)		VOID_BASE(const void*,	(PTR),	NULL==)
#define RTN_VOID_IF_FALSE(EXP)		VOID_BASE(BOOL,			(EXP),	!)
#define RTN_VOID_IF_BADNEW(PTR)		VOID_BASE(const void*,	(PTR),	NULL==)
#define RTN_VOID_IF_NEGONE(EXP)		VOID_BASE(BOOL,			(EXP),	NEG_ONE!=)
#define RTN_VOID_IF_TRUE(EXP)		RTN_VOID_IF_FALSE(!(EXP))
#define RTN_VOID_IF_BADWINDOW(WND)	RTN_VOID_IF_FALSE(::IsWindow(WND));

#define CONTINUE_IF_FAILED(HR)		CONTINUE_BASE_CORE(HRESULT, (HR), FAILED, continue, tempVal)
#define CONTINUE_IF_BADPTR(PTR)		CONTINUE_BASE(const void*,	(PTR),	NULL==)
#define CONTINUE_IF_FALSE(EXP)		CONTINUE_BASE(BOOL,			(EXP),	!)
#define CONTINUE_IF_NEGONE(EXP)		CONTINUE_BASE(BOOL,			(EXP),	NEG_ONE==)
#define CONTINUE_IF_BADNEW(PTR)		CONTINUE_BASE(const void*,	(PTR),	NULL==)
#define CONTINUE_IF_TRUE(EXP)		CONTINUE_IF_FALSE(!(EXP))
#define CONTINUE_IF_BADWINDOW(WND)	CONTINUE_IF_FALSE(::IsWindow(WND));

#define GOTO_EXIT_IF_FAILED(HR)		MACRO_BASE_HR((HR),	goto Exit;)
#define GOTO_EXIT_IF_BADPTR(PTR)	EXIT_BASE(const void*,	(PTR),	NULL==)
#define GOTO_EXIT_IF_FALSE(EXP)		EXIT_BASE(BOOL,			(EXP),	!)
#define GOTO_EXIT_IF_NEGONE(EXP)	EXIT_BASE(BOOL,			(EXP),	NEG_ONE==)
#define GOTO_EXIT_IF_BADNEW(PTR)	EXIT_BASE(const void*,	(PTR),	NULL==)
#define GOTO_EXIT_IF_TRUE(EXP)		GOTO_EXIT_IF_FALSE(!(EXP))
#define GOTO_EXIT_IF_BADWINDOW(WND)	GOTO_EXIT_IF_FALSE(::IsWindow(WND))





#endif //__DEBUGDLL_H__
