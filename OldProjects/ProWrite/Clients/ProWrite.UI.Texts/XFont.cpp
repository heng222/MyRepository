// XFont.cpp  Version 1.1
//
// Author:       Philip Patrick (GetFontProperties)
//
// Version 1.0   - Initial release of GetFontProperties()
//
// Modified by:  Hans Dietrich
//               hdietrich2@hotmail.com
//
// Version 1.1:  - Removed MFC dependency from GetFontProperties()
//               - Converted CFile file I/O to memory mapped file
//               - Added Unicode support
//               - Combined with my GetFontFile() routine
//
///////////////////////////////////////////////////////////////////////////////
#include <Stdafx.h>
#include <windows.h>
#include <crtdbg.h>
#include "XTrace.h"
#include "XFont.h"

///////////////////////////////////////////////////////////////////////////////
//
// If you do not want XTRACE output you can
// uncomment the following lines:
//
#undef  XTRACE
#define XTRACE 
//
///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable : 4127)		// conditional expression is constant

///////////////////////////////////////////////////////////////////////////////


// private routines
static LONG GetNextNameValue(HKEY key, LPCTSTR subkey, LPTSTR szName, LPTSTR szData);
static BOOL GetWinVer(LPTSTR lpszVersion, int nVersionSize, int *nVersion);
static BOOL MatchString(LPCTSTR lpctsToSearch,LPCTSTR lpctCharSet);


///////////////////////////////////////////////////////////////////////////////
// defines used by GetWinVer()
#define WUNKNOWNSTR	_T("unknown Windows version")

#define W95STR		_T("Windows 95")
#define W95SP1STR	_T("Windows 95 SP1")
#define W95OSR2STR	_T("Windows 95 OSR2")
#define W98STR		_T("Windows 98")
#define W98SP1STR	_T("Windows 98 SP1")
#define W98SESTR	_T("Windows 98 SE")
#define WMESTR		_T("Windows ME")

#define WNT351STR	_T("Windows NT 3.51")
#define WNT4STR		_T("Windows NT 4")
#define W2KSTR		_T("Windows 2000")
#define WXPSTR		_T("Windows XP")
#define WVISTASTR   _T("Windows Vista")

#define WCESTR		_T("Windows CE")


#define WUNKNOWN	0

#define W9XFIRST	1
#define W95			1
#define W95SP1		2
#define W95OSR2		3
#define W98			4
#define W98SP1		5
#define W98SE		6
#define WME			7
#define W9XLAST		99

#define WNTFIRST	101
#define WNT351		101
#define WNT4		102
#define W2K			103
#define WXP			104
#define WVISTA      105
#define WNTLAST		199

#define WCEFIRST	201
#define WCE			201
#define WCELAST		299


///////////////////////////////////////////////////////////////////////////////
//
// structs used by GetFontProperties()
//
typedef struct _tagFONT_PROPERTIES_ANSI
{
    char csName[1024];
    char csCopyright[1024];
    char csTrademark[1024];
    char csFamily[1024];
} FONT_PROPERTIES_ANSI;

typedef struct _tagTT_OFFSET_TABLE
{
    USHORT	uMajorVersion;
    USHORT	uMinorVersion;
    USHORT	uNumOfTables;
    USHORT	uSearchRange;
    USHORT	uEntrySelector;
    USHORT	uRangeShift;
} TT_OFFSET_TABLE;

typedef struct _tagTT_TABLE_DIRECTORY
{
    char	szTag[4];			//table name
    ULONG	uCheckSum;			//Check sum
    ULONG	uOffset;			//Offset from beginning of file
    ULONG	uLength;			//length of the table in bytes
} TT_TABLE_DIRECTORY;

typedef struct _tagTT_NAME_TABLE_HEADER
{
    USHORT	uFSelector;			//format selector. Always 0
    USHORT	uNRCount;			//Name Records count
    USHORT	uStorageOffset;		//Offset for strings storage, from start of the table
} TT_NAME_TABLE_HEADER;

typedef struct _tagTT_NAME_RECORD
{
    USHORT	uPlatformID;
    USHORT	uEncodingID;
    USHORT	uLanguageID;
    USHORT	uNameID;
    USHORT	uStringLength;
    USHORT	uStringOffset;	//from start of storage area
} TT_NAME_RECORD;

#define SWAPWORD(x)		MAKEWORD(HIBYTE(x), LOBYTE(x))
#define SWAPLONG(x)		MAKELONG(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))


///////////////////////////////////////////////////////////////////////////////
//
// GetFontFile()
//
// Purpose:     Find the name of font file from the font name
//
// Parameters:  lpszFontName     - name of font
//              lpszDisplayName  - pointer to buffer where font display name
//                                 will be copied
//              nDisplayNameSize - size of display name buffer in TCHARs
//              lpszFontFile     - pointer to buffer where font file name
//                                 will be copied
//              nFontFileSize    - size of font file buffer in TCHARs
//
// Returns:     BOOL - TRUE = success
//
// Notes:       This is *not* a foolproof method for finding the name of a
//              font file. If a font has been installed in a normal manner,
//              and if it is in the Windows "Font" directory, then this method
//              will probably work. It will probably work for most screen
//              fonts and TrueType fonts. However, this method might not work
//              for fonts that are created or installed dynamically, or that
//              are specific to a particular device, or that are not installed
//              into the font directory.
//
BOOL GetFontFile(LPCTSTR lpszFontName,
                 LPTSTR lpszDisplayName,
                 int nDisplayNameSize,
                 LPTSTR lpszFontFile,
                 int nFontFileSize)
{
    _ASSERTE(lpszFontName && lpszFontName[0] != 0);
    if (!lpszFontName || lpszFontName[0] == 0)
        return FALSE;

    if (lpszDisplayName!=NULL)
    {
        lpszDisplayName[0] = _T('\0');
    }
    if (lpszFontFile!=NULL)
    {
        lpszFontFile[0] = _T('\0');
    }

    TCHAR szName[2 * MAX_PATH];
    TCHAR szData[2 * MAX_PATH];

    int nVersion;
    TCHAR szVersion[100];
    GetWinVer(szVersion, sizeof(szVersion)/sizeof(TCHAR)-1, &nVersion);

    XTRACE(_T("szVersion=%s\n"), szVersion);

    TCHAR szFontPath[1000];

    if ((nVersion >= WNTFIRST) && (nVersion <= WNTLAST))
        _tcscpy_s(szFontPath, _T("Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts"));
    else
        _tcscpy_s(szFontPath, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Fonts"));

    BOOL bResult = FALSE;

    while (GetNextNameValue(HKEY_LOCAL_MACHINE, szFontPath, szName, szData) == ERROR_SUCCESS)
    {
        if ( MatchString(lpszFontName,szName))
        {
            XTRACE(_T("found font\n"));

            if (lpszDisplayName!=NULL)
            {
                _tcsncpy_s(lpszDisplayName, nDisplayNameSize,szName, nDisplayNameSize-1);
            }

            if (lpszFontFile!=NULL)
            {
                LPTSTR cp = _tcsrchr((LPTSTR)szData, _T('\\'));
                if (cp)  
                {
                    cp++; 
                    _tcsncpy_s(lpszFontFile, nFontFileSize, cp, nFontFileSize-1);
                }
                else
                {
                    _tcsncpy_s(lpszFontFile, nFontFileSize, szData, nFontFileSize-1);
                }
            }

            bResult = TRUE;
            break;
        }

        szFontPath[0] = _T('\0');	// this will get next value, same key
    }

    GetNextNameValue(HKEY_LOCAL_MACHINE, NULL, NULL, NULL);	// close the registry key

    return bResult;
}


///////////////////////////////////////////////////////////////////////////////
//
// GetFontProperties()
//
// Purpose:     Get font name from font file
//
// Parameters:  lpszFilePath - file path of font file
//              lpFontPropsX - pointer to font properties struct
//
// Returns:     BOOL - TRUE = success
//
BOOL GetFontProperties(LPCTSTR lpszFilePath, FONT_PROPERTIES * lpFontPropsX)
{
    FONT_PROPERTIES_ANSI fp;
    FONT_PROPERTIES_ANSI * lpFontProps = &fp;

    memset(lpFontProps, 0, sizeof(FONT_PROPERTIES_ANSI));

    HANDLE hFile = INVALID_HANDLE_VALUE;
    hFile = ::CreateFile(lpszFilePath,
        GENERIC_READ,// | GENERIC_WRITE,
        0,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        XTRACE(_T("ERROR:  failed to open '%s'\n"), lpszFilePath);
        XTRACE(_T("ERROR: %s failed\n"), _T("CreateFile"));
        return FALSE;
    }

    // get the file size
    DWORD dwFileSize = ::GetFileSize(hFile, NULL);

    if (dwFileSize == INVALID_FILE_SIZE)
    {
        XTRACE(_T("ERROR: %s failed\n"), _T("GetFileSize"));
        ::CloseHandle(hFile);
        return FALSE;
    }

    XTRACE(_T("dwFileSize = %d\n"), dwFileSize);

    // Create a file mapping object that is the current size of the file
    HANDLE hMappedFile = NULL;
    hMappedFile = ::CreateFileMapping(hFile,
        NULL,
        PAGE_READONLY, //PAGE_READWRITE,
        0,
        dwFileSize,
        NULL);

    if (hMappedFile == NULL)
    {
        XTRACE(_T("ERROR: %s failed\n"), _T("CreateFileMapping"));
        ::CloseHandle(hFile);
        return FALSE;
    }

    LPBYTE lpMapAddress = (LPBYTE) ::MapViewOfFile(hMappedFile,		// handle to file-mapping object
        FILE_MAP_READ,//FILE_MAP_WRITE,			// access mode
        0,						// high-order DWORD of offset
        0,						// low-order DWORD of offset
        0);						// number of bytes to map

    if (lpMapAddress == NULL)
    {
        XTRACE(_T("ERROR: %s failed\n"), _T("MapViewOfFile"));
        ::CloseHandle(hMappedFile);
        ::CloseHandle(hFile);
        return FALSE;
    }

    BOOL bRetVal = FALSE;
    int index = 0;

    TT_OFFSET_TABLE ttOffsetTable;
    memcpy(&ttOffsetTable, &lpMapAddress[index], sizeof(TT_OFFSET_TABLE));
    index += sizeof(TT_OFFSET_TABLE);

    ttOffsetTable.uNumOfTables = SWAPWORD(ttOffsetTable.uNumOfTables);
    ttOffsetTable.uMajorVersion = SWAPWORD(ttOffsetTable.uMajorVersion);
    ttOffsetTable.uMinorVersion = SWAPWORD(ttOffsetTable.uMinorVersion);

    // check is this is a true type font and the version is 1.0
    if (ttOffsetTable.uMajorVersion != 1 || ttOffsetTable.uMinorVersion != 0)
    {
        XTRACE(_T("Not TrueType font!\n"));
        ::CloseHandle(hMappedFile);
        ::CloseHandle(hFile);
        return bRetVal;
    }

    TT_TABLE_DIRECTORY tblDir;
    memset(&tblDir, 0, sizeof(TT_TABLE_DIRECTORY));
    BOOL bFound = FALSE;
    char szTemp[4096];
    memset(szTemp, 0, sizeof(szTemp));

    for (int i = 0; i< ttOffsetTable.uNumOfTables; i++)
    {
        //f.Read(&tblDir, sizeof(TT_TABLE_DIRECTORY));
        memcpy(&tblDir, &lpMapAddress[index], sizeof(TT_TABLE_DIRECTORY));
        index += sizeof(TT_TABLE_DIRECTORY);

        strncpy_s(szTemp, tblDir.szTag, 4);
        if (_stricmp(szTemp, "name") == 0)
        {
            bFound = TRUE;
            tblDir.uLength = SWAPLONG(tblDir.uLength);
            tblDir.uOffset = SWAPLONG(tblDir.uOffset);
            break;
        }
        else if (szTemp[0] == 0)
        {
            break;
        }
    }

    if (bFound)
    {
        index = tblDir.uOffset;

        TT_NAME_TABLE_HEADER ttNTHeader;
        memcpy(&ttNTHeader, &lpMapAddress[index], sizeof(TT_NAME_TABLE_HEADER));
        index += sizeof(TT_NAME_TABLE_HEADER);

        ttNTHeader.uNRCount = SWAPWORD(ttNTHeader.uNRCount);
        ttNTHeader.uStorageOffset = SWAPWORD(ttNTHeader.uStorageOffset);
        TT_NAME_RECORD ttRecord;
        bFound = FALSE;

        for (int i = 0;
            i < ttNTHeader.uNRCount &&
            (lpFontProps->csCopyright[0] == 0 ||
            lpFontProps->csName[0] == 0      ||
            lpFontProps->csTrademark[0] == 0 ||
            lpFontProps->csFamily[0] == 0);
        i++)
        {
            memcpy(&ttRecord, &lpMapAddress[index], sizeof(TT_NAME_RECORD));
            index += sizeof(TT_NAME_RECORD);

            ttRecord.uNameID = SWAPWORD(ttRecord.uNameID);
            ttRecord.uStringLength = SWAPWORD(ttRecord.uStringLength);
            ttRecord.uStringOffset = SWAPWORD(ttRecord.uStringOffset);

            if (ttRecord.uNameID == 1 || ttRecord.uNameID == 0 || ttRecord.uNameID == 7)
            {
                int nPos = index; //f.GetPosition();

                index = tblDir.uOffset + ttRecord.uStringOffset + ttNTHeader.uStorageOffset;

                memset(szTemp, 0, sizeof(szTemp));

                memcpy(szTemp, &lpMapAddress[index], ttRecord.uStringLength);
                index += ttRecord.uStringLength;

                if (szTemp[0] != 0)
                {
                    _ASSERTE(strlen(szTemp) < sizeof(lpFontProps->csName));

                    switch (ttRecord.uNameID)
                    {
                    case 0:
                        if (lpFontProps->csCopyright[0] == 0)
                            strncpy_s(lpFontProps->csCopyright, sizeof(lpFontProps->csCopyright)-1,
                            szTemp,sizeof(lpFontProps->csCopyright)-1);
                        break;

                    case 1:
                        if (lpFontProps->csFamily[0] == 0)
                            strncpy_s(lpFontProps->csFamily, sizeof(lpFontProps->csFamily)-1,szTemp,
                            sizeof(lpFontProps->csFamily)-1);
                        bRetVal = TRUE;
                        break;

                    case 4:
                        if (lpFontProps->csName[0] == 0)
                            strncpy_s(lpFontProps->csName, sizeof(lpFontProps->csName)-1,szTemp,
                            sizeof(lpFontProps->csName)-1);
                        break;

                    case 7:
                        if (lpFontProps->csTrademark[0] == 0)
                            strncpy_s(lpFontProps->csTrademark, sizeof(lpFontProps->csTrademark)-1,szTemp,
                            sizeof(lpFontProps->csTrademark)-1);
                        break;

                    default:
                        break;
                    }
                }
                index = nPos;
            }
        }
    }

    ::UnmapViewOfFile(lpMapAddress);
    ::CloseHandle(hMappedFile);
    ::CloseHandle(hFile);

    if (lpFontProps->csName[0] == 0)
        strcpy_s(lpFontProps->csName, lpFontProps->csFamily);

    memset(lpFontPropsX, 0, sizeof(FONT_PROPERTIES));

#ifdef _UNICODE
    ::MultiByteToWideChar(CP_ACP, 0, lpFontProps->csName, -1, lpFontPropsX->csName,
        sizeof(lpFontPropsX->csName)/sizeof(TCHAR)-1);
    ::MultiByteToWideChar(CP_ACP, 0, lpFontProps->csCopyright, -1, lpFontPropsX->csCopyright,
        sizeof(lpFontPropsX->csCopyright)/sizeof(TCHAR)-1);
    ::MultiByteToWideChar(CP_ACP, 0, lpFontProps->csTrademark, -1, lpFontPropsX->csTrademark,
        sizeof(lpFontPropsX->csTrademark)/sizeof(TCHAR)-1);
    ::MultiByteToWideChar(CP_ACP, 0, lpFontProps->csFamily, -1, lpFontPropsX->csFamily,
        sizeof(lpFontPropsX->csFamily)/sizeof(TCHAR)-1);
#else
    strcpy_s(lpFontPropsX->csName, lpFontProps->csName);
    strcpy_s(lpFontPropsX->csCopyright, lpFontProps->csCopyright);
    strcpy_s(lpFontPropsX->csTrademark, lpFontProps->csTrademark);
    strcpy_s(lpFontPropsX->csFamily, lpFontProps->csFamily);
#endif

    return bRetVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// MatchString(LPCTSTR lpctsToSearch,LPCTSTR lpctCharSet)
//
// Purpose:     Á½×Ö·û´®ÊÇ·ñÆ¥Åä
//
// Parameters:  lpctsToSearch - Ö¸¶¨µÄ´ýÆ¥Åä×Ö·û´®
//              lpctCharSet   - ´Ó×¢²á±íÖÐÕÒµÄ×Ö·û´®
//
//
static BOOL MatchString(LPCTSTR lpctsToSearch,LPCTSTR lpctCharSet)
{    
    TCHAR strDest[MAX_PATH] = {0};
    _tcscpy_s(strDest,lpctCharSet);

#ifdef _COMPARE_ALL_
    // finds the first occurrence of '('.
    TCHAR* cp = _tcschr(strDest,'(');
    if (cp!=NULL)
    {
        cp--; // blank character
        *cp = 0;
    }
#endif

    // 
    if (_tcschr(lpctCharSet,'&')!=NULL)
    {
        if (_tcsstr(strDest,lpctsToSearch)!=NULL)
        {
            return TRUE;
        }
    }    
#ifdef _COMPARE_ALL_
    else if (_tcsicmp(lpctsToSearch, strDest)==0)
#else
    else if (_tcsnicmp(lpctsToSearch, strDest, _tcslen(lpctsToSearch))==0)
#endif
    {
        return TRUE;
    }

    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetNextNameValue()
//
// Purpose:     Get first/next name/value pair from registry
//
// Parameters:  key       - handle to open key, or predefined key
//              pszSubkey - subkey name
//              pszName   - pointer to buffer that receives the value string
//              pszData   - pointer to buffer that receives the data string
//
// Returns:     LONG - return code from registry function; ERROR_SUCCESS = success
//
// Notes:       If pszSubkey, pszName, and pszData are all NULL, then the open
//              handle will be closed.
//
//              The first time GetNextNameValue is called, pszSubkey should be
//              specified.  On subsequent calls, pszSubkey should be NULL or
//              an empty string.
//
static LONG GetNextNameValue(HKEY key, LPCTSTR pszSubkey, LPTSTR pszName, LPTSTR pszData)
{
    static HKEY hkey = NULL;	// registry handle, kept open between calls
    static DWORD dwIndex = 0;	// count of values returned
    LONG retval;

    // if all parameters are NULL then close key
    if (pszSubkey == NULL && pszName == NULL && pszData == NULL)
    {
        XTRACE(_T("closing key\n"));
        if (hkey)
            RegCloseKey(hkey);
        hkey = NULL;
        return ERROR_SUCCESS;
    }

    // if subkey is specified then open key (first time)
    if (pszSubkey && pszSubkey[0] != 0)
    {
        retval = RegOpenKeyEx(key, pszSubkey, 0, KEY_ALL_ACCESS, &hkey);
        if (retval != ERROR_SUCCESS)
        {
            XTRACE(_T("ERROR: RegOpenKeyEx failed\n"));
            return retval;
        }
        else
        {
            XTRACE(_T("RegOpenKeyEx ok\n"));
        }
        dwIndex = 0;
    }
    else
    {
        dwIndex++;
    }

    _ASSERTE(pszName != NULL && pszData != NULL);

    *pszName = 0;
    *pszData = 0;

    TCHAR szValueName[MAX_PATH];
    DWORD dwValueNameSize = sizeof(szValueName)-1;
    BYTE szValueData[MAX_PATH];
    DWORD dwValueDataSize = sizeof(szValueData)-1;
    DWORD dwType = 0;

    retval = RegEnumValue(hkey, dwIndex, szValueName, &dwValueNameSize, NULL,
        &dwType, szValueData, &dwValueDataSize);
    if (retval == ERROR_SUCCESS)
    {
        XTRACE(_T("szValueName=<%s>  szValueData=<%s>\n"), szValueName, szValueData);
        lstrcpy(pszName, (LPTSTR)szValueName);
        lstrcpy(pszData, (LPTSTR)szValueData);
    }
    else
    {
        XTRACE(_T("RegEnumKey failed\n"));
    }

    return retval;
}


// from winbase.h
#ifndef VER_PLATFORM_WIN32s
#define VER_PLATFORM_WIN32s             0
#endif
#ifndef VER_PLATFORM_WIN32_WINDOWS
#define VER_PLATFORM_WIN32_WINDOWS      1
#endif
#ifndef VER_PLATFORM_WIN32_NT
#define VER_PLATFORM_WIN32_NT           2
#endif
#ifndef VER_PLATFORM_WIN32_CE
#define VER_PLATFORM_WIN32_CE           3
#endif


/*
This table has been assembled from Usenet postings, personal
observations, and reading other people's code.  Please feel
free to add to it or correct it.


dwPlatFormID  dwMajorVersion  dwMinorVersion  dwBuildNumber
95             1              4               0             950
95 SP1         1              4               0        >950 && <=1080
95 OSR2        1              4             <10           >1080
98             1              4              10            1998
98 SP1         1              4              10       >1998 && <2183
98 SE          1              4              10          >=2183
ME             1              4              90            3000

NT 3.51        2              3              51
NT 4           2              4               0            1381
2000           2              5               0            2195
XP             2              5               1            2600

CE             3

*/

///////////////////////////////////////////////////////////////////////////////
//
// GetWinVer()
//
// Purpose:     Get Windows version info
//
// Parameters:  lpszVersion  - pointer to buffer that receives the version
//                             string
//              nVersionSize - size of the version buffer in TCHARs
//              pnVersion    - pointer to int that receives the version code
//
// Returns:     BOOL - TRUE = success
//
///////////////////////////////////////////////////////////////////////////////
// GetWinVer
static BOOL GetWinVer(LPTSTR lpszVersion, int nVersionSize, int *pnVersion)
{
    _tcsncpy_s(lpszVersion, nVersionSize,WUNKNOWNSTR, nVersionSize-1);
    *pnVersion = WUNKNOWN;

    TCHAR *cp = NULL;

    OSVERSIONINFO osinfo;
    osinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (!GetVersionEx(&osinfo))
        return FALSE;

    DWORD dwPlatformId   = osinfo.dwPlatformId;
    DWORD dwMinorVersion = osinfo.dwMinorVersion;
    DWORD dwMajorVersion = osinfo.dwMajorVersion;
    DWORD dwBuildNumber  = osinfo.dwBuildNumber & 0xFFFF;	// Win 95 needs this
    XTRACE(_T("%d:  %d.%d.%d\n"), dwPlatformId, dwMajorVersion, dwMinorVersion, dwBuildNumber);

    if ((dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) && (dwMajorVersion == 4))
    {
        if ((dwMinorVersion < 10) && (dwBuildNumber == 950))
        {
            cp = W95STR;
            *pnVersion = W95;
        }
        else if ((dwMinorVersion < 10) &&
            ((dwBuildNumber > 950) && (dwBuildNumber <= 1080)))
        {
            cp = W95SP1STR;
            *pnVersion = W95SP1;
        }
        else if ((dwMinorVersion < 10) && (dwBuildNumber > 1080))
        {
            cp = W95OSR2STR;
            *pnVersion = W95OSR2;
        }
        else if ((dwMinorVersion == 10) && (dwBuildNumber == 1998))
        {
            cp = W98STR;
            *pnVersion = W98;
        }
        else if ((dwMinorVersion == 10) &&
            ((dwBuildNumber > 1998) && (dwBuildNumber < 2183)))
        {
            cp = W98SP1STR;
            *pnVersion = W98SP1;
        }
        else if ((dwMinorVersion == 10) && (dwBuildNumber >= 2183))
        {
            cp = W98SESTR;
            *pnVersion = W98SE;
        }
        else if (dwMinorVersion == 90)
        {
            cp = WMESTR;
            *pnVersion = WME;
        }
    }
    else if (dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        if ((dwMajorVersion == 3) && (dwMinorVersion == 51))
        {
            cp = WNT351STR;
            *pnVersion = WNT351;
        }
        else if ((dwMajorVersion == 4) && (dwMinorVersion == 0))
        {
            cp = WNT4STR;
            *pnVersion = WNT4;
        }
        else if ((dwMajorVersion == 5) && (dwMinorVersion == 0))
        {
            cp = W2KSTR;
            *pnVersion = W2K;
        }
        else if ((dwMajorVersion == 5) && (dwMinorVersion == 1))
        {
            cp = WXPSTR;
            *pnVersion = WXP;
        }
        else if (dwMinorVersion == 6)
        {
            cp = WVISTASTR;
            *pnVersion = WVISTA;
        }
    }
    else if (dwPlatformId == VER_PLATFORM_WIN32_CE)
    {
        cp = WCESTR;
        *pnVersion = WCE;
    }

    if(cp!=NULL)
    {
        _tcsncpy_s(lpszVersion, nVersionSize,cp, nVersionSize-1);
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

