
#ifndef _ULTRA_STRING_OPERATION_
#define _ULTRA_STRING_OPERATION_
//////////////////////////////////////////////////////////////////////////
#include "MuType.h"

// ×Ö·û´®²Ù×÷¾²Ì¬Àà
class AFX_EXT_CLASS CStringUtility
{
private:

    CStringUtility(void);
    ~CStringUtility(void);

    enum    { BUFFER_SIZE = 4096 };

public:

    //
    // Trims leading spaces and control characters from a string
    //
    static void TrimLeft(LPCTSTR pszParam, LPTSTR pszResult);

    //
    // Trims trailing spaces and control characters from a string
    //
    static  void TrimRight(LPCTSTR pszParam, LPTSTR pszResult);

    //
    // Trims leading and trailing spaces and control characters from a string
    //
    static void Trim(LPCTSTR pszParam, LPTSTR pszResult);

    //---------------------------------------------------------------------------
    // UnicodeToAnsi
    // 
    // Translates Unicode to ANSI strings
    //---------------------------------------------------------------------------
    static BOOL UnicodeToAnsi(LPCWSTR pszwUniString, 
                    LPSTR  pszAnsiBuff,
                    DWORD  dwAnsiBuffSize);

    //---------------------------------------------------------------------------
    // UnicodeToAnsi
    // 
    // Translates Unicode to ANSI strings
    //---------------------------------------------------------------------------
    static std::string UnicodeToAnsi(const std::wstring& wString);

    //---------------------------------------------------------------------------
    // AnsiToUnicode
    // 
    // Translates ANSI strings to Unicode.
    //---------------------------------------------------------------------------
    static BOOL AnsiToUnicode( LPCSTR  pszAnsiBuff,
                    LPWSTR pszwUniString, 
                    DWORD  dwUniBuffSize);

    //---------------------------------------------------------------------------
    // AnsiToUnicode
    // 
    // Translates ANSI strings to Unicode.
    //---------------------------------------------------------------------------
    static std::wstring AnsiToUnicode(const std::string&  pszAnsiBuff);

    // Format the specified string
    static std::wstring Format(LPCWSTR lpszFormat, ...);

    // Format the specified string
    static std::string Format(LPCSTR lpszFormat, ...);
};


//////////////////////////////////////////////////////////////////////////
#endif