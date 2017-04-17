#include "StdAfx.h"
#include "StringUtility.h"

//
// Trims leading spaces and control characters from a string
//
void CStringUtility::TrimLeft(LPCTSTR  pszParam, LPTSTR   pszResult)
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
void CStringUtility::TrimRight(LPCTSTR  pszParam, LPTSTR   pszResult)
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
void CStringUtility::Trim(  LPCTSTR  pszParam, LPTSTR   pszResult     )
{
    TrimLeft(pszParam, pszResult);
    TrimRight(pszParam, pszResult);
}


//---------------------------------------------------------------------------
// UnicodeToAnsi
// 
// Translates Unicode to ANSI strings
//---------------------------------------------------------------------------
BOOL CStringUtility::UnicodeToAnsi( LPCWSTR pszwUniString, 
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
// UnicodeToAnsi
// 
// Translates Unicode to ANSI strings
//---------------------------------------------------------------------------
std::string CStringUtility::UnicodeToAnsi(const std::wstring& wString)
{
    if (wString.length() > 0)
    {
        int len = wString.length() * 2 + 1;
        LPSTR ansiBuf = new char[len];

        BOOL rc = CStringUtility::UnicodeToAnsi(wString.c_str(), ansiBuf, len);

        std::string ansiString;
        ansiString.append(ansiBuf);

        delete[] ansiBuf;

        return ansiString.c_str();
    }
    else
    {
        return "";
    }
}

//---------------------------------------------------------------------------
// AnsiToUnicode
// 
// Translates ANSI strings to Unicode.
//---------------------------------------------------------------------------
BOOL CStringUtility::AnsiToUnicode( LPCSTR  pszAnsiBuff,
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


std::wstring CStringUtility::AnsiToUnicode(const std::string&  ansiString)
{
    if (ansiString.length() > 0)
    {
        int len = ansiString.length() * 2 + 1;
        LPWSTR wBuf = new wchar_t[len];

        BOOL rc = CStringUtility::AnsiToUnicode(ansiString.c_str(), wBuf, len);

        std::wstring wString;
        wString.append(wBuf);

        delete[] wBuf;

        return wString.c_str();
    }
    else
    {
        return L"";
    }
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

// Format the specified string
std::wstring CStringUtility::Format(LPCWSTR lpszFormat, ...)
{
    va_list va;
    va_start(va, lpszFormat);

    //TCHAR buf1[BUFFER_SIZE] = {0};
    wchar_t buf2[BUFFER_SIZE] = {0};


    /*if (_sntprintf_s(buf1, BUFFER_SIZE, _T("%s"), 
        lpszFormat) < 0)
    {
        buf1[BUFFER_SIZE-1] = _T('\0');
    }*/

    // format the message as requested
    if (_vsnwprintf_s(buf2, BUFFER_SIZE, lpszFormat, va) < 0)
    {
        buf2[BUFFER_SIZE-1] = _T('\0');
    }

    va_end(va);

    return buf2;

}


// Format the specified string
std::string CStringUtility::Format(LPCSTR lpszFormat, ...)
{
    va_list va;
    va_start(va, lpszFormat);

    char buffer[BUFFER_SIZE] = {0};

    // format the message as requested
    if (_vsnprintf_s(buffer, BUFFER_SIZE, lpszFormat, va) < 0)
    {
        buffer[BUFFER_SIZE-1] = _T('\0');
    }

    va_end(va);

    return buffer;

}