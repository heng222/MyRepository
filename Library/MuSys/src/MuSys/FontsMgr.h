#pragma once

#include "Stdafx.h"
#include "MuType.h"

//////////////////////////////////////////////////////////////////////////


//
class CFontInfo 
{
public:

	TString		m_strFontName;

    // Font type
	BOOL		m_bRaster;
    BOOL        m_bTrueType;
    BOOL        m_bDeviceType;

    // 0 = REGULAR
    // 1 = REGULAR | BOLD
    // 3 = REGULAR | BOLD | ITALICS
    // 7 = REGULAR | BOLD | ITALICS | BOLDITALICS
    //WORD        m_wStyle;

    // available height list(in Pixel)
    std::list<int>   m_listHeight;

public:

    //
    CFontInfo()
    {
        m_bRaster = FALSE;
        m_bTrueType = FALSE;
        m_bDeviceType = FALSE;
    }
	//
	int operator<(const CFontInfo &other)
	{
        INT iRC =  _tcsicmp(m_strFontName.c_str(),other.m_strFontName.c_str());
        return (iRC<0);
	}
};

// enumerate all the fonts under the current system.
extern "C" AFX_EXT_API 
void EnumFontInfo(std::vector<CFontInfo>& fontInfor,const TString& strFontName);

//////////////////////////////////////////////////////////////////////////



