#include "stdafx.h"
#include "FontsMgr.h"


//////////////////////////////////////////////////////////////////////////

BOOL AllowFontAsLimited(CFontInfo& fontInfo);

// does the fontlist include strFontName?
BOOL  IsExist(vector<CFontInfo>& fontList, const wstring& strFontName);


int CALLBACK S_EnumSysFontProc(const LOGFONT *lpelfe,	const TEXTMETRIC *lpntme,  
							   DWORD FontType,	LPARAM lParam);

int CALLBACK S_EnumSpecifiedFontProc(const LOGFONT *lpelfe,     // logical-font data
									 const TEXTMETRIC *lpntme,  // physical-font data
									 DWORD FontType,            // type of font
									 LPARAM lParam);            // application-defined data

int CALLBACK S_EnumFontFamProcRaster(const LOGFONT *lpelf,		// logical-font data
									 const TEXTMETRIC *lpntm,	// physical-font data
									 DWORD FontType,			// type of font
									 LPARAM lParam);			// application-defined data

//////////////////////////////////////////////////////////////////////////
/*
Values Meaning 
lfCharSet = DEFAULT_CHARSET && lfFaceName = '\0' Enumerates all fonts in all character sets. 
lfCharSet = DEFAULT_CHARSET && lfFaceName = a specific font Enumerates all character sets and styles in a specific font. 
lfCharSet =a specific character set && lfFaceName = '\0' Enumerates all styles of all fonts in the specific character set. 
lfCharSet =a specific character set && lfFaceName = a specific font Enumerates all styles of a font in a specific character set. 

*/
void EnumFontInfo(vector<CFontInfo>& fontInfor,const wstring& strFontName)
{
    HDC hdc = ::GetDC(NULL);

    // build 
	LOGFONT stLogFont;
    ZeroMemory(&stLogFont, sizeof(stLogFont));
    stLogFont.lfCharSet = DEFAULT_CHARSET; //
    size_t iFontSize = strFontName.size();
    if (iFontSize>0 && iFontSize<=LF_FACESIZE)
    {
        wcscpy_s(stLogFont.lfFaceName,strFontName.c_str());
    }

    // clear result
	fontInfor.resize(0);

    // 
    ::EnumFontFamiliesEx(hdc, &stLogFont, S_EnumSysFontProc, (LPARAM)(&fontInfor), 0);

    // sort
	sort(fontInfor.begin(), fontInfor.end());

	// Travel the list
	for(vector<CFontInfo>::iterator iCurFont = fontInfor.begin(); iCurFont != fontInfor.end(); ++iCurFont)
	{
        if(iCurFont->m_bRaster)
        {
            ::EnumFontFamilies( hdc, 
                strFontName.c_str(), 
                S_EnumFontFamProcRaster, 
                (LPARAM)&(iCurFont->m_listHeight) );

            iCurFont->m_listHeight.sort();
        }
        else
        {
            // Microsoft suggested numbers are 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72
            iCurFont->m_listHeight.push_back(7);
            iCurFont->m_listHeight.push_back(8);
            iCurFont->m_listHeight.push_back(10);
            iCurFont->m_listHeight.push_back(12);
            iCurFont->m_listHeight.push_back(14);
            iCurFont->m_listHeight.push_back(16);
            iCurFont->m_listHeight.push_back(18);
            iCurFont->m_listHeight.push_back(22);
            iCurFont->m_listHeight.push_back(24);
            iCurFont->m_listHeight.push_back(28);
            iCurFont->m_listHeight.push_back(36);
            iCurFont->m_listHeight.push_back(48);
            iCurFont->m_listHeight.push_back(60);
            iCurFont->m_listHeight.push_back(72);
            iCurFont->m_listHeight.push_back(108);
            iCurFont->m_listHeight.push_back(144);
            iCurFont->m_listHeight.push_back(220);
            iCurFont->m_listHeight.push_back(440);
        }

	}

    //
    ::ReleaseDC(NULL,hdc);

}

int CALLBACK S_EnumSysFontProc(const LOGFONT *lpelfe,     // logical-font data
							const TEXTMETRIC *lpntme,  // physical-font data
							DWORD FontType,            // type of font
							LPARAM lParam)             // application-defined data
{
	vector<CFontInfo> *pFontList = (vector<CFontInfo> *)lParam;

	//LPENUMLOGFONTEX pEnumLogFont = (ENUMLOGFONTEX *)lpelfe;
    //wstring strFontName = bTrueType ? pEnumLogFont->elfFullName : lpelfe->lfFaceName;

	BOOL bTrueType = (FontType & TRUETYPE_FONTTYPE);
	BOOL bRaster   = (FontType & RASTER_FONTTYPE);
    BOOL bDevice   = (FontType & DEVICE_FONTTYPE);


    // 
    CFontInfo stNewFontInfo;
    stNewFontInfo.m_strFontName = lpelfe->lfFaceName;
    stNewFontInfo.m_bRaster = bRaster;
    stNewFontInfo.m_bTrueType = bTrueType;
    stNewFontInfo.m_bDeviceType = bDevice;

    if ( !IsExist(*pFontList,stNewFontInfo.m_strFontName) && 
         lpelfe->lfFaceName[0]!='@')
    {
        pFontList->push_back(stNewFontInfo);
    }

	return 1;
}

int CALLBACK S_EnumFontFamProcRaster(const LOGFONT *lpelf,		// logical-font data
                                     const TEXTMETRIC *lpntm,	// physical-font data
                                     DWORD FontType,			// type of font
                                     LPARAM lParam)				// application-defined data
{
    //HDC hdc = ::GetDC(NULL);
    list<int> *panFontSizes = (list<int> *)lParam;

    // Unit: point °õ
    //int nLogPixelsY = ::GetDeviceCaps(hdc, LOGPIXELSY);
    //int nLogCharHeight = lpelf->lfHeight - lpntm->tmInternalLeading;
    //int nPointHeight = (nLogCharHeight * 72 + (nLogPixelsY>>1) ) / nLogPixelsY;

    
    // unit: pixel
    if (std::find(panFontSizes->begin(),panFontSizes->end(),lpelf->lfHeight)==panFontSizes->end())
    {
        panFontSizes->push_back(lpelf->lfHeight);
    }

    //
    //::ReleaseDC(NULL,hdc);
    return 1;
}

BOOL  IsExist(vector<CFontInfo>& fontList, const wstring& strFontName)
{
    size_t iSize = fontList.size();
    for (size_t i=0; i<iSize; i++)
    {        
        if (fontList[i].m_strFontName.compare(strFontName)==0)
        {
            return TRUE;
        }
    }

    return FALSE;
}



#if 0

//////////////////////////////////////////////////////////////////////////
// 
void EnumFontHeight(const wstring& strFontName,list<int>& heightList )
{
	
    HDC hdc = ::GetDC(NULL);

	//
	LOGFONT stLogFont;
	ZeroMemory(&stLogFont, sizeof(stLogFont));
	stLogFont.lfCharSet = ANSI_CHARSET;
	wcscpy_s(stLogFont.lfFaceName,strFontName.c_str());

	
	// if the font given is a raster font?
	CFontInfo fontSpecified;
    ::EnumFontFamiliesEx(hdc, &stLogFont, S_EnumSpecifiedFontProc, (LPARAM)(&fontSpecified), 0);

	//
	if(fontSpecified.m_bRaster)
	{
        ::EnumFontFamilies( hdc, 
			    strFontName.c_str(), 
			    S_EnumFontFamProcRaster, 
			    (LPARAM)&heightList
            );

		heightList.sort();
	}
	else
	{
		// Microsoft suggested numbers are 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72
		heightList.push_back(3);
		heightList.push_back(4);
		heightList.push_back(5);
		heightList.push_back(6);
		heightList.push_back(7);
		heightList.push_back(8);
		heightList.push_back(9);
		heightList.push_back(10);
		heightList.push_back(11);
		heightList.push_back(12);
		heightList.push_back(14);
		heightList.push_back(16);
		heightList.push_back(18);
		heightList.push_back(20);
		heightList.push_back(22);
		heightList.push_back(24);
		heightList.push_back(26);
		heightList.push_back(28);
		heightList.push_back(36);
		heightList.push_back(48);
		heightList.push_back(72);
		heightList.push_back(108);
		heightList.push_back(144);
	}
    ::ReleaseDC(NULL,hdc);
}

int CALLBACK S_EnumSpecifiedFontProc(const LOGFONT *lpelfe,     // logical-font data
							   const TEXTMETRIC *lpntme,  // physical-font data
							   DWORD FontType,            // type of font
							   LPARAM lParam)             // application-defined data
{
	CFontInfo* pFontInfor = (CFontInfo*)lParam;
	ENUMLOGFONTEX *pEnumLogFont = (ENUMLOGFONTEX *)lpelfe;

	BOOL bTrueType = FontType & TRUETYPE_FONTTYPE;

	/*wstring elfScript1(_T("Î÷·½"));
	wstring elfScript2(_T("Western"));
	if ( elfScript1.compare(pEnumLogFont->elfScript)==0 ||
		 elfScript2.compare(pEnumLogFont->elfScript)==0 )*/

    wstring strFontName = bTrueType ? pEnumLogFont->elfFullName : lpelfe->lfFaceName;
    pFontInfor->m_strFontName = strFontName;
    pFontInfor->m_bRaster = FontType&RASTER_FONTTYPE;

	return 1;
}

// in point
BYTE GetFontMinHeight(const wstring& strFontName)
{
    list<int> fontSize;
    EnumFontHeight(strFontName,fontSize);
    if (fontSize.size()>0)
    {
        list<int>::iterator iCurFont = fontSize.begin();
        return (BYTE)(*iCurFont);
    }
    else
    {
        return 0;
    }
}


// 
int  PointToLogicUnit(int iPointValue,const wstring& strFontName)
{
    if (iPointValue<=0)
    {
        return 0;
    }

    HDC hdc = ::GetDC(NULL);


    LOGFONT stLogFont;
    ZeroMemory(&stLogFont, sizeof(stLogFont));
    stLogFont.lfCharSet = DEFAULT_CHARSET;
    wcscpy_s(stLogFont.lfFaceName,strFontName.c_str());
    stLogFont.lfHeight = -(LONG)(iPointValue * ::GetDeviceCaps(hdc,LOGPIXELSY)/72.0);
    
    HFONT hNewFont = ::CreateFontIndirect(&stLogFont);
    ::SelectObject(hdc,hNewFont);

    TEXTMETRIC tm;
    ::GetTextMetrics(hdc,&tm);
    int iLogicValue = tm.tmHeight;


    //
    ::DeleteObject(hNewFont);

    return iLogicValue;
}
#endif