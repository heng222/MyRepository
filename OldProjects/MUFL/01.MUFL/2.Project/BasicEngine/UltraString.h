
#ifndef _ULTRA_STRING_OPERATION_
#define _ULTRA_STRING_OPERATION_
//////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CUltraString
{
private:

    CUltraString(void);
    ~CUltraString(void);

public:

    //
    // Trims leading spaces and control characters from a string
    //
    static void TrimLeft( LPCTSTR pszParam,
                          LPTSTR  pszResult);

    //
    // Trims trailing spaces and control characters from a string
    //
    static  void TrimRight( LPCTSTR  pszParam,
                            LPTSTR   pszResult);

    //
    // Trims leading and trailing spaces and control characters from a string
    //
    static void Trim(  LPCTSTR  pszParam,
                        LPTSTR   pszResult    );

    //---------------------------------------------------------------------------
    // UnicodeToAnsi
    // 
    // Translates Unicode to ANSI strings
    //---------------------------------------------------------------------------
    static BOOL UnicodeToAnsi( LPCWSTR pszwUniString, 
                    LPSTR  pszAnsiBuff,
                    DWORD  dwAnsiBuffSize);

    //---------------------------------------------------------------------------
    // AnsiToUnicode
    // 
    // Translates ANSI strings to Unicode.
    //---------------------------------------------------------------------------
    static BOOL AnsiToUnicode( LPCSTR  pszAnsiBuff,
                    LPWSTR pszwUniString, 
                    DWORD  dwUniBuffSize);
};


//////////////////////////////////////////////////////////////////////////
#endif