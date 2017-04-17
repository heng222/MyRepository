#pragma once


#include "Stdafx.h"


using namespace System::Xml; 
using namespace System::IO;

//////////////////////////////////////////////////////////////////////////
// struct of font
enum TPWFontStyle
{
    EPWF_REGULAR     = 0x0000,  // Regular Prowrite font
    EPWF_BOLD        = 0x0001,  // Bold
    EPWF_ITALICS     = 0x0002,  // Italics
    EPWF_BOLDITALICS = 0x0004,  // BoldItalics
	EPWF_STRIKEOUT	 = 0x0008,	// Strikeout
};

// struct of font
struct TPWFont 
{
    wstring         m_strFileName;
    wstring         m_strFontName;
    INT             m_iHeight;
    TPWFontStyle    m_iFontStyle;
    BOOL            m_bAutoFont;

    //
    TPWFont()
    {
        m_iHeight = 0;
        m_iFontStyle = EPWF_REGULAR;
        m_bAutoFont = TRUE;
    }


    // < operation overridden
    BOOL operator<(const TPWFont &other)
    {
        if (m_iHeight<other.m_iHeight)
        {
            return TRUE;
        }
        else if (m_iHeight>other.m_iHeight)
        {
            return FALSE;
        }
        else
        {
            if (m_iFontStyle!=EPWF_BOLD&&other.m_iFontStyle==EPWF_BOLD)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
    }

    // Can be used when auto-size enable?
    BOOL   IsAutoFont() const
    {
        //return (m_iFontStyle!=EPWF_ITALICS);
        return m_bAutoFont;
    }
};
typedef  TPWFont*               PTPWFont;
typedef  std::vector<TPWFont>   CPWFontArray;

// Prowrite font manager
class CProwriteFont
{

private:

    CProwriteFont(void);
    ~CProwriteFont(void);

public:

    // Initialize and release
    static BOOL  Initialize(String^ strFileName);
    static void  Release();


public:

    // Determine the given font is ProwriteFont.
    static  BOOL    IsProwriteFont(const wstring& strFontName);

    // Retrieve the minimum height.
    static  INT     GetMinHeight();

    // Retrieve all height value
    static void     GetAllHeight(std::vector<INT>& arHeight);

    // Display Name operation
    static  void    SetShowName(const wstring& strName);
    static  wstring GetShowName();
    static  BOOL    IsShowName(const wstring& strName);

    // Get the logic font
    static  BOOL    GetLogicFont( LOGFONT& logFont,
                              INT iHeight,
                              TPWFontStyle iStyle);
	// Get the Prowrite font
	static  PTPWFont    GetPWFont(const wstring& strFontName);

    // Get file name according to FontName
    static  wstring GetFileName(const wstring& strFontName); 

    // Get Style
    // Return the specific font's style 
    // 0 = EPWF_REGULAR
    // 1 = EPWF_REGULAR | EPWF_BOLD
    // 3 = EPWF_REGULAR | EPWF_BOLD | EPWF_ITALICS
    // 7 = EPWF_REGULAR | EPWF_BOLD | EPWF_ITALICS | EPWF_BOLDITALICS
    static  WORD     GetStyle(INT iHeight);

    // Travel the Prowrite fonts.
    static  BOOL     GetFirstFont(LOGFONT& logFont,BOOL bAutoFont=TRUE);
    static  BOOL     GetNextFont(LOGFONT& logFont,BOOL bAutoFont=TRUE);

    // for parse ProwriteFont configure file.
private:

    // add a prowrite font to collection.
    static void      AddFont(const wstring& strFontName,INT iHeight,TPWFontStyle iStyle);
    static  BOOL     ParseFont(XmlNode^ xmlNode);
    static  BOOL     GetLOGFONT(INT iIndex,LOGFONT& logFont);
    static  VOID     NextAutoFontPos();
    static  BOOL     IsAutoFont(INT iIndex);

private:

    static  BOOL              m_bInit;       // Has been initialized?
    
    static  CPWFontArray      m_PWFonts;     // Prowrite font collection
    static  wstring           m_strShowName; // "Prowrite Sign Font"

    // the current position
    static  LONG              m_iPosition;
    static  CRITICAL_SECTION* m_pCriticalSection;    // to protect m_iPosition.
};

//////////////////////////////////////////////////////////////////////////
// End of file
