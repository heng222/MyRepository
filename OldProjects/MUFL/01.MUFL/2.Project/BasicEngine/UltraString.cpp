#include "StdAfx.h"
#include "UltraString.h"

//
// Trims leading spaces and control characters from a string
//
void CUltraString::TrimLeft(LPCTSTR  pszParam,
                            LPTSTR   pszResult)
{
    TCHAR szBuffer[MAX_PATH] = {0};
    if ( (TRUE != ::IsBadStringPtr(pszParam, MAX_PATH)) &&
        (_tcslen(pszParam) > 0) )
    {
        DWORD dwIndex = 0;
        while ( (dwIndex < _tcslen(pszParam)) && (pszParam[dwIndex] == ' ') )
            dwIndex++;
        if (dwIndex < _tcslen(pszParam))
            _tcscpy_s(szBuffer, MAX_PATH,&pszParam[dwIndex]);
    } // if
    _tcscpy_s(pszResult, MAX_PATH,szBuffer);
}

//
// Trims trailing spaces and control characters from a string
//
void CUltraString::TrimRight(LPCTSTR  pszParam,
                             LPTSTR   pszResult)
{
    TCHAR szBuffer[MAX_PATH] = {0};
    if ( (TRUE != ::IsBadStringPtr(pszParam, MAX_PATH)) &&
        (_tcslen(pszParam) > 0) )
    {
        int nIndex = _tcslen(pszParam) - 1;
        while ( (nIndex >= 0) && (pszParam[nIndex] == ' ') )
            nIndex--;
        if (nIndex >= 0)
        {
            _tcsncpy_s(szBuffer, MAX_PATH,pszParam,nIndex+1); 
        } // if
    } // if
    _tcscpy_s(pszResult, MAX_PATH,szBuffer);
}

//
// Trims leading and trailing spaces and control characters from a string
//
void CUltraString::Trim(  LPCTSTR  pszParam,
                        LPTSTR   pszResult     )
{
    TrimLeft(pszParam, pszResult);
    TrimRight(pszParam, pszResult);
}


//---------------------------------------------------------------------------
// UnicodeToAnsi
// 
// Translates Unicode to ANSI strings
//---------------------------------------------------------------------------
BOOL CUltraString::UnicodeToAnsi( LPCWSTR pszwUniString, 
                   LPSTR  pszAnsiBuff,
                   DWORD  dwAnsiBuffSize)
{
    int  iRet  = ::WideCharToMultiByte(
        CP_ACP,
        0,
        pszwUniString,
        -1,
        pszAnsiBuff,
        dwAnsiBuffSize,
        NULL,
        NULL);
    return (0 != iRet);
}


//---------------------------------------------------------------------------
// AnsiToUnicode
// 
// Translates ANSI strings to Unicode.
//---------------------------------------------------------------------------
BOOL CUltraString::AnsiToUnicode( LPCSTR  pszAnsiBuff,
                                  LPWSTR pszwUniString, 
                                  DWORD  dwUniBuffSize)
{
    int  iRet   =   ::MultiByteToWideChar(
        CP_ACP,
        0,
        pszAnsiBuff,
        -1,
        pszwUniString,
        dwUniBuffSize );

    return (0 != iRet);
}

//用于实现string和wstring的转换：
/*std::string ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	std::string result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}
std::wstring s2ws(const std::string& s)
{
setlocale(LC_ALL, "chs");
const char* _Source = s.c_str();
size_t _Dsize = s.size() + 1;
wchar_t *_Dest = new wchar_t[_Dsize];
wmemset(_Dest, 0, _Dsize);
mbstowcs(_Dest,_Source,_Dsize);
std::wstring result = _Dest;
delete []_Dest;
setlocale(LC_ALL, "C");
return result;
}

*/
