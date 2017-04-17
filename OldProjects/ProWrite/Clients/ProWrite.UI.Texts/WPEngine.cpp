// WPEngine.cpp : Implementation of WPEngine
#include "stdafx.h"
#include <math.h>
#include "WPEngine.h"
#include "XTrace.h"
#include "XFont.h"

using namespace System::Drawing;
#pragma warning (disable:4267)

//#define _TRACE_INFO

/////////////////////////////////////////////////////////////////////////////
// Constructor && Destructor

CWPEngine::CWPEngine():    
	m_hFont(NULL),m_bWordBreak(TRUE),
    m_bUsePWFont(FALSE)
{
    m_hDC = ::CreateCompatibleDC(NULL);
    //SIZE size = {1000,1000};
    //m_hDC = Create32Bitmap(size);
    ::SetMapMode(m_hDC,MM_TEXT);
    ::SetBkMode(m_hDC,TRANSPARENT);

	//
    m_iAdjustStyle = EFrameFixed_FontAutosize;

	// Default text
	m_strText = _T("Please set the text.");	

    // 
	CreateSysFont();

	//
	m_sizeSign.cx = 1000;
	m_sizeSign.cy = 1000;

	m_sizeFrame = m_sizeSign;

}

CWPEngine::~CWPEngine()
{
    // first
    ClearTextLayers();

    // second
	if (m_hDC)
	{
		::DeleteDC(m_hDC);
        m_hDC = NULL;
    }

    if (m_hFont)
    {
        ::DeleteObject(m_hFont);
        m_hFont = NULL;
    }
}

//////////////////////////////////////////////////////////////////////////
// public members functions


void CWPEngine::SetAdjustStyle(BOOL bFrameSizeFixed,BOOL bFontSizeFixed)
{
    if (!bFrameSizeFixed&&bFontSizeFixed)
    {
        m_iAdjustStyle = EFrameAutosize_FontsizeFixed;
    }
    else if (bFrameSizeFixed&&!bFontSizeFixed)
    {
        m_iAdjustStyle = EFrameFixed_FontAutosize;
    }
    else if(bFrameSizeFixed&&bFontSizeFixed)
    {
        m_iAdjustStyle = EFrameFixed_FontsizeFixed;
    }
    else
    {
        // do nothing!
        CLR_ASSERT(ERROR);
    }

}

HRESULT CWPEngine::SetText(LPCWSTR lpctText)
{
    m_strText = lpctText;
    FixText(m_strText);
    return S_OK;
}

HRESULT CWPEngine::SetSignSize(SIZE sizeSign)
{
    CLR_ASSERT(sizeSign.cx>0 && sizeSign.cy>0);

//     if ((LONG)sizeSign.cx*(LONG)sizeSign.cy>MAXSIZE_LAYER)
//     {
//         sizeSign.cx = 1;
//         sizeSign.cy = 1;
//     }

    m_sizeSign.cx = sizeSign.cx;
    m_sizeSign.cy = sizeSign.cy;
    return S_OK;
}

void CWPEngine::SetKernAmount(IN int iAmount) 
{
    m_textAttri.m_iKernAmount = iAmount;
}


void CWPEngine::SetFirstIndent(IN INT iAmount) 
{ 
    m_textAttri.m_iLeadAmount = iAmount; 
}

void CWPEngine::SetLeadAmount(IN INT iAmount)
{
    m_textAttri.m_iLeadAmount = iAmount;
}


// invalid for ISEFonts
HRESULT CWPEngine::SetFontLogicHeight(INT ilogicHeight)
{
    // here, that is logic unit, we needn't transform.
    m_textAttri.m_logFont.lfHeight = ilogicHeight;

    CreateSysFont(); 

    return S_OK;
}


int CWPEngine::GetFontLogicHeight(BOOL bAllHeight) const
{
    int iHeight = 0;

    if (m_textAttri.m_logFont.lfHeight!=0)
    {
        TEXTMETRIC tm;
        ::GetTextMetrics(m_hDC,&tm);
        //BOOL bTrueType = tm.tmPitchAndFamily & TMPF_TRUETYPE;
        if (bAllHeight /*&& !m_bUsePWFont*/)
        {
            iHeight = tm.tmHeight;
        }
        else
        {
            iHeight = tm.tmAscent;
        }
    }

    return iHeight;
}

// invalid for ISEFonts
void CWPEngine::SetFontBold(BOOL bFlag)
{
    if (bFlag)
    {
        m_textAttri.m_logFont.lfWeight = FW_BOLD;
    }
    else
    {
        m_textAttri.m_logFont.lfWeight = FW_NORMAL;
    }

    CreateSysFont();
}

BOOL CWPEngine::GetFontBold() const
{
	if(m_bUsePWFont)
	{
		PTPWFont pFont = CProwriteFont::GetPWFont(m_textAttri.m_logFont.lfFaceName);
		if (pFont)
		{
			return (pFont->m_iFontStyle==EPWF_BOLD) || (pFont->m_iFontStyle==EPWF_BOLDITALICS);
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return m_textAttri.m_logFont.lfWeight == FW_BOLD;
	}
}

void CWPEngine::SetFontItalic(BOOL bFlag)
{
    m_textAttri.m_logFont.lfItalic = bFlag;
    CreateSysFont();    
}

BOOL CWPEngine::GetFontItalic() const
{
	if(m_bUsePWFont)
	{
		PTPWFont pFont = CProwriteFont::GetPWFont(m_textAttri.m_logFont.lfFaceName);
		if (pFont)
		{
			return (pFont->m_iFontStyle==EPWF_ITALICS) || (pFont->m_iFontStyle==EPWF_BOLDITALICS);
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return m_textAttri.m_logFont.lfItalic;
	}

}

void CWPEngine::SetFontUnderLine(BOOL bFlag)
{
    m_textAttri.m_logFont.lfUnderline = bFlag;
    CreateSysFont();
}

BOOL CWPEngine::GetFontUnderLine() const
{
	if(m_bUsePWFont)
	{
		PTPWFont pFont = CProwriteFont::GetPWFont(m_textAttri.m_logFont.lfFaceName);
		if (pFont)
		{
			return (pFont->m_iFontStyle==EPWF_STRIKEOUT);
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return m_textAttri.m_logFont.lfUnderline;
	}
}

HRESULT CWPEngine::SetFontName(LPCWSTR lpcFaceName)
{

    HRESULT rc = S_OK;

    m_bUsePWFont = CProwriteFont::IsShowName(lpcFaceName);

    if (!m_bUsePWFont)
    {
        if(wcslen(lpcFaceName)>sizeof(m_textAttri.m_logFont.lfFaceName)-1)
        {
            rc = ERROR_INVALID_DATA;
        }
        else
        {
            wcscpy_s(m_textAttri.m_logFont.lfFaceName,lpcFaceName);
            CreateSysFont();
        }

        // Determine the minimum height.

        vector<CFontInfo> fontInfor;
        EnumFontInfo(fontInfor,lpcFaceName);

        CLR_ASSERT(fontInfor.size()>0);
        if(fontInfor.size()>0)
        {
            list<int>::iterator begin = fontInfor[0].m_listHeight.begin();
            m_iMinHeight = *begin;
            m_textAttri.m_bRaster = fontInfor[0].m_bRaster;
        }
        fontInfor.clear();
    }
    else
    {
        // Determine the minimum height.
        m_iMinHeight = CProwriteFont::GetMinHeight();
        m_textAttri.m_bRaster = TRUE;
    }

    return rc;
}

wstring CWPEngine::GetFontFileName() const
{
    if (m_bUsePWFont)
    {
        return CProwriteFont::GetFileName(m_textAttri.m_logFont.lfFaceName);
    }
    else
    {
        wstring strSearch = m_textAttri.m_logFont.lfFaceName;
        BOOL bFondCircle = FALSE;

        if (m_textAttri.m_logFont.lfItalic && m_textAttri.m_logFont.lfWeight==FW_BOLD)
        {
            strSearch += _T(" Bold Italic");
            bFondCircle = TRUE;
        }
        else if (!m_textAttri.m_logFont.lfItalic && m_textAttri.m_logFont.lfWeight==FW_BOLD)
        {
            strSearch += _T(" Bold");
            bFondCircle = TRUE;
        }
        else if (m_textAttri.m_logFont.lfItalic && m_textAttri.m_logFont.lfWeight!=FW_BOLD)
        {
            strSearch += _T(" Italic");
            bFondCircle = TRUE;
        }
        else
        {
            // do nothing
        }

        TCHAR szDisplayName[MAX_PATH], szFontFile[MAX_PATH];

        BOOL bFlag = GetFontFile( strSearch.c_str(), szDisplayName, MAX_PATH, szFontFile, MAX_PATH);

        if (bFlag)
        {
            return szFontFile;
        }
        else
        {
            if (bFondCircle)
            {
                bFlag = GetFontFile( m_textAttri.m_logFont.lfFaceName, 
                                szDisplayName, MAX_PATH, szFontFile, MAX_PATH );

                if (bFlag)
                {
                    return szFontFile;
                }
            }
        }

        return _T("Unknown");
    }
    
}

HRESULT CWPEngine::SetFrameSize(int iWidth,int iHeight)
{
    CLR_ASSERT(iWidth>0&&iHeight>0);

    if (iHeight<=0) {
        iHeight = 1;
    }

    if (iWidth<=0) {
        iWidth = 1;
    }

//     if ((LONG)iWidth*(LONG)iHeight>MAXSIZE_LAYER)
//     {
//         iHeight = 1;
//         iWidth = 1;
//     }

    m_sizeFrame.cx = iWidth;
    m_sizeFrame.cy = iHeight;
    return S_OK;
}

HRESULT CWPEngine::SetTextAlign(UINT uAlignment)
{
    m_textAttri.m_uAlignment = uAlignment;
    return S_OK;
}

void CWPEngine::SetLineAlign(UINT uVAlignment)
{
    m_textAttri.m_uVAlignment = uVAlignment;

}

VOID CWPEngine::SetTextColor(const GpClr& clrText)
{
    m_textAttri.m_clrText = clrText;
}

VOID CWPEngine::SetBkgColor(const GpClr& clrBkg)
{
    m_textAttri.m_clrBkg = clrBkg;
}

VOID CWPEngine::SetGridColor(const GpClr& clrGrid)
{
    m_textAttri.m_clrGrid = clrGrid;
}
//////////////////////////////////////////////////////////////////////////
// Interface: text effects

void CWPEngine::SetEffectType(TTextEffect type)
{
    m_textAttri.m_iEffectType = type;
}

TTextEffect CWPEngine::GetEffectType() const
{
    return m_textAttri.m_iEffectType; 
}



void CWPEngine::SetShadowColor(IN const GpClr& clr)
{
    m_textAttri.m_clrShadow = clr;
}

void CWPEngine::SetShadowDropdown(IN SIZE size)
{
    m_textAttri.m_iCxShadow = size.cx;
    m_textAttri.m_iCyShadow = size.cy;
}

COLORREF CWPEngine::GetShadowColor() const
{
    return m_textAttri.m_clrShadow.ToCOLORREF();
}

BOOL CWPEngine::GetShadowDropdown(OUT SIZE& size) const
{
    size.cx = m_textAttri.m_iCxShadow;
    size.cy = m_textAttri.m_iCyShadow;
    return TRUE;
}


void CWPEngine::SetOutlineColor(const GpClr& clr)
{
    m_textAttri.m_clrOutline = clr;

}
void CWPEngine::SetOutlineWidth(IN WORD wWidth)
{
    m_textAttri.m_iWidthOutline = wWidth;
}

COLORREF CWPEngine::GetOutlineColor() const
{
    return m_textAttri.m_clrOutline.ToCOLORREF();
}

INT  CWPEngine::GetOutlineWidth() const
{
    return m_textAttri.m_iWidthOutline;
}


//////////////////////////////////////////////////////////////////////////
// Private members

void  CWPEngine::FixText(wstring& strText) const
{
    wstring strTemp = strText;
    strText.resize(0);

    size_t iLen = strTemp.size();
    for (size_t i=0; i<iLen; i++)
    {
        // <31 for Control character
        // 0x0A = Line Feed
        // 0x0D = carriage return
        if (strTemp[i]>31 || strTemp[i]==0x0A)
        {
            strText.push_back(strTemp[i]);
        }
    }
}

void CWPEngine::ClearTextLayers()
{
    CTextLayer* pImage;
    for (CFrameImgList::iterator iCur = m_frmImgList.begin(); iCur!=m_frmImgList.end(); iCur++)
    {
        pImage = *iCur;
        delete pImage;
    }
    m_frmImgList.resize(0);
}

// create a new font and select it to DC.
BOOL CWPEngine::CreateSysFont()
{
    // Delete the old font
    if (m_hFont)
    {
        ::DeleteObject(m_hFont);
        m_hFont = NULL;
    }

    // create a new font

    m_hFont = ::CreateFontIndirect(&m_textAttri.m_logFont);

    // select it to current DC.

    if (m_hFont)
    {
        ::SelectObject(m_hDC,m_hFont);
    }


    return (m_hFont!=NULL);

}

BOOL  CWPEngine::ChooseProwriteFont()
{
    if(!m_bUsePWFont)
    {
        return FALSE;
    }

    if ( EFrameFixed_FontsizeFixed==m_iAdjustStyle||
         EFrameAutosize_FontsizeFixed==m_iAdjustStyle)
    {
        TPWFontStyle iStyle = EPWF_REGULAR;
        if ( m_textAttri.m_logFont.lfWeight==FW_BOLD &&
            m_textAttri.m_logFont.lfItalic)
        {
            iStyle = EPWF_BOLDITALICS;
        }
        else if ( m_textAttri.m_logFont.lfWeight==FW_BOLD &&
            !m_textAttri.m_logFont.lfItalic)
        {
            iStyle = EPWF_BOLD;
        } 
        else if( m_textAttri.m_logFont.lfWeight!=FW_BOLD &&
            m_textAttri.m_logFont.lfItalic)
        {
            iStyle = EPWF_ITALICS;
        }

        // search an appropriate  prowrite font
        wstring strFontName;
        BOOL bFlag = CProwriteFont::GetLogicFont(m_textAttri.m_logFont,
                        m_textAttri.m_logFont.lfHeight, iStyle);
        if (bFlag)
        {
            // Create font
            CreateSysFont();
        }
        else
        {
            return FALSE;
        }
    }
    else if(EFrameFixed_FontAutosize==m_iAdjustStyle)
    {
        SIZE   sizeActual;
        GetRefSize(sizeActual);
        BOOL bFlag = CProwriteFont::GetFirstFont(m_textAttri.m_logFont);
        while (bFlag)
        {
            // Create font
            CreateSysFont();

            // Is the current font appropriate ?
            if(AdjustHeightAccurately(0,sizeActual,m_strText))
            {
                return TRUE;
            }

            //
            bFlag = CProwriteFont::GetNextFont(m_textAttri.m_logFont);
        }
        if (!bFlag)
        {
            //return FALSE;
        }
    }
    else
    {
        return FALSE;
    }

    return TRUE;

}

// get the reference size.
void  CWPEngine::GetRefSize( OUT SIZE& sizeRef) const
{
    if (EFrameAutosize_FontsizeFixed==m_iAdjustStyle)
    {
        sizeRef.cx = m_sizeSign.cx*2;
        sizeRef.cy = m_sizeSign.cy*2;

    } 
    else if( EFrameFixed_FontsizeFixed==m_iAdjustStyle ||
             EFrameFixed_FontAutosize==m_iAdjustStyle )
    {
        sizeRef = m_sizeFrame;
    }
    else
    {
        CLR_ASSERT(ERROR);
        sizeRef.cx = sizeRef.cy = 0;
    }

}

// check size to determine if it's too small?
BOOL CWPEngine::CheckRefSize() const
{
    // retrieve the reference size.
    SIZE   sizeActual;
    GetRefSize(sizeActual);

    // adjust the size
    SIZE sizeRef = sizeActual;
	AdjustRefSize(sizeRef,FALSE);

    if ( EFrameFixed_FontsizeFixed==m_iAdjustStyle )
    {
        return TRUE;
    }
    else if (EFrameFixed_FontAutosize==m_iAdjustStyle)
    {
        if(m_iMinHeight>sizeRef.cy || m_iMinHeight>sizeRef.cx)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    else if( EFrameAutosize_FontsizeFixed==m_iAdjustStyle )
    {
        TEXTMETRIC tm;
        ::GetTextMetrics(m_hDC,&tm);
        if( tm.tmHeight>sizeRef.cy || tm.tmHeight>sizeRef.cx )
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    else
    {
        CLR_ASSERT(FALSE);
        return FALSE;
    }

}

//
void CWPEngine::AdjustRefSize(IN_OUT SIZE& sizeRef,
                                IN BOOL bDirection/*=FALSE*/) const
{

	bDirection ? (sizeRef.cx+=m_textAttri.m_iLeadAmount) : (sizeRef.cx-=m_textAttri.m_iLeadAmount);

    TTextEffect effType = m_textAttri.m_iEffectType;

    if (effType==ETE_NONE)
    {
        // do nothing
    }
    else if (effType==ETE_SHADOW)
    {
        int iValueX = abs(m_textAttri.m_iCxShadow);
        int iValueY = abs(m_textAttri.m_iCyShadow);

        bDirection ? (sizeRef.cx+=iValueX):(sizeRef.cx-=iValueX);
        bDirection ? (sizeRef.cy+=iValueY):(sizeRef.cy-=iValueY);
    }
    else if (effType==ETE_OUTLINE)
    {
        int iHValue = 2*abs(m_textAttri.m_iWidthOutline); // top + bottom
        int iVValue = 2*abs(m_textAttri.m_iWidthOutline); // left + right

        bDirection ? (sizeRef.cx+=iHValue) :(sizeRef.cx-=iHValue);
        bDirection ? (sizeRef.cy+=iVValue) :(sizeRef.cy-=iVValue);
    }
    else
    {
        CLR_ASSERT(FALSE); // unexpected effect type.
    }

}

// invalid when use ISEFonts
void CWPEngine::EstParagraphSize(IN const wstring& strText,
                             IN const SIZE& sizeMax,
                             OUT SIZE& sizeText) const
{
    sizeText.cx = 0;
    sizeText.cy = 0;
    CLR_ASSERT(strText.length()>0);

    int iMaxWidth = sizeMax.cx;

	size_t iTxtLengh = strText.length();

	// 
	::GetTextExtentPoint32(m_hDC,strText.c_str(),(INT)(strText.length()),&sizeText);

	// average width
	float fCharWidth = float(sizeText.cx)/(float)iTxtLengh;
    if (fCharWidth-(int)fCharWidth>0)
    {
        fCharWidth = (float)((int)fCharWidth+1);
    }
    if (fCharWidth==0)
    {
        fCharWidth = 1;
    }

	// max number per line
	int iNumCharPerRow = int(iMaxWidth/fCharWidth);
	if (iNumCharPerRow==0)
	{
		sizeText.cx = 0;
		sizeText.cy = 0;
		return;
	}

	// number of row
	size_t iNumRow = iTxtLengh/iNumCharPerRow; 

	if (iTxtLengh%iNumCharPerRow>0)
	{
		iNumRow ++;
	}

	if (iNumRow>1)
	{
		sizeText.cx = iMaxWidth;
		sizeText.cy *= iNumRow;
	}

}

// invalid when use ISEFonts
// estimate the height of the font under the rectangle given.
WORD CWPEngine::EstFontHeight(IN const SIZE& sizeExtent,
                                IN const wstring& strText)
{
    CLR_ASSERT(strText.length()>0);

    //
    if (sizeExtent.cx<0 || sizeExtent.cy<0)
    {
        return 0;
    }

    // number of characters
    INT iNumChar = INT(strText.length());

    // the height of one character
    WORD wHeightEachChar = 0;
    if (sizeExtent.cy<iNumChar)
    {
        wHeightEachChar = 1;
    }
    else
    {
        wHeightEachChar = WORD(sizeExtent.cy/iNumChar);
    }

    //  estimate the height approximately
    SetFontLogicHeight(wHeightEachChar);

    // 
    SIZE sizeText;
    ::GetTextExtentPoint32(m_hDC,strText.c_str(),strText.length(),&sizeText);


    // width of the characters[total/num]
    int iWidthEachChar = sizeText.cx/iNumChar;
    if (iWidthEachChar==0)
    {
        iWidthEachChar = 1;
    }
    int lTimeWidth = (sizeExtent.cx)/(iWidthEachChar);
    wHeightEachChar = (WORD)(wHeightEachChar*sqrt((float)lTimeWidth)); 
    if (wHeightEachChar%2!=0) // adjust to even
    {
        wHeightEachChar ++;
    }

    return wHeightEachChar;
}

// invalid when use ISEFonts
// increase the font height according to the referenced size.
WORD  CWPEngine::IncrFontHeight(IN WORD wOrginHeight,
                                  IN const SIZE& sizeRef,
                                  IN const wstring& strTextRef)
{
    SIZE sizeText;

    do 
    {
        SetFontLogicHeight(wOrginHeight);

        EstParagraphSize(strTextRef,sizeRef,sizeText);

        if ( sizeText.cx ==0 || sizeText.cy==0)
        {
            break;
        }
        else if( (sizeRef.cx*sizeRef.cy>sizeText.cx*sizeText.cy) 
                  && ((sizeText.cx<sizeRef.cx) || (sizeText.cy<sizeRef.cy)) )
        {
            wOrginHeight += 2;
        }
        else{
            break;
        }

    } while(TRUE);

    return wOrginHeight;
}

// invalid when use ISEFonts
// decrease the font height according to the referenced size.
WORD   CWPEngine::DecrFontHeight(IN WORD wOrginHeight,
                                   IN const SIZE& sizeRef,
                                   IN const wstring& strTextRef
                                   )
{
    SIZE sizeText;

    do 
    {
        SetFontLogicHeight(wOrginHeight);	

        EstParagraphSize(strTextRef,sizeRef,sizeText);

        if ( (sizeText.cx>sizeRef.cx) || (sizeText.cy>sizeRef.cy))
        {
            wOrginHeight -= 2;
            //
            if(wOrginHeight<=0){
                wOrginHeight = 0;
                break;
            }
        }
        else{
            break;
        }


    }while(TRUE);

    return wOrginHeight;
}

// invalid when use ISEFonts
// adjust accurately
WORD CWPEngine::AdjustHeightAccurately( IN WORD wOrgHeight,
                                    IN const SIZE& sizeExtent,
                                    IN const wstring& strText)
{

    // Adjust
    SIZE sizeMax = sizeExtent;
    AdjustRefSize(sizeMax,FALSE);

    // check if the extent valid.
    TEXTMETRIC tm;
    ::GetTextMetrics(m_hDC,&tm);

    if (!m_bUsePWFont)
    {
        CLR_ASSERT(wOrgHeight>0);

        // use the given height
        SetFontLogicHeight(wOrgHeight);
        while(tm.tmHeight>sizeMax.cy || tm.tmHeight>sizeMax.cx)
        {
            wOrgHeight --;
            if (wOrgHeight<=0)
            {
                return 0;
            }
            else 
            {
                SetFontLogicHeight(wOrgHeight);
                ::GetTextMetrics(m_hDC,&tm);
            }
        }
    }
    else
    {
        if(tm.tmHeight>sizeMax.cy || tm.tmHeight>sizeMax.cx)
        {
            return 0;
        }
    }


    // 
    int iNumRow = 1; 
    int iTempWidth = 0;
    SIZE sizeAlpha;
    wstring strCurWord  = _T("");

    for (UINT iIndex=0; iIndex<strText.length(); iIndex++)
    {
        wstring strChar(&(strText.at(iIndex)),1);
        ::GetTextExtentPoint32(m_hDC,strChar.c_str(),1,&sizeAlpha);

        BOOL bWordBreak = FALSE;
        if (m_bWordBreak)
        {
            wstring strTempWord;
            BOOL bIsWord = this->GetWord(strText,iIndex,strTempWord);
            if ( bIsWord && strTempWord.compare(strCurWord.c_str())!=0 )
            {
                strCurWord = strTempWord;
                bWordBreak = NeedWordBreak(strCurWord,sizeMax.cx-iTempWidth);
            }
        }

        // A new line?
        BOOL bBreakChar = IsBreakChar(strChar);
        if ( bBreakChar
            || (iTempWidth+sizeAlpha.cx)>sizeMax.cx 
            || bWordBreak)
        {
            strCurWord = _T("");

            INT iTotalLineAmount = (iNumRow)*m_textAttri.m_iLeadAmount;
            INT iTotalCharHeight = (iNumRow+1)*sizeAlpha.cy;
            
            // greater than sizemax.cy ?
            if ( (iTotalLineAmount+iTotalCharHeight)>=sizeMax.cy ) 
            {
                wOrgHeight --;

                if (wOrgHeight>0) 
                {
                    if (m_bUsePWFont)
                    {
                        return 0;
                    }
                    else
                    {
                        wOrgHeight = AdjustHeightAccurately(wOrgHeight,sizeExtent,strText);
                    }
                }
                break;
            }
            else 
            {
                iNumRow ++;
            }


            //
            if (bBreakChar)  {
                iTempWidth = 0;
            }
            else { // current width = char's width + intercharacter spacing
                iTempWidth = sizeAlpha.cx + m_textAttri.m_iKernAmount; 
            }
        }
        else {
            iTempWidth += sizeAlpha.cx;
            iTempWidth += m_textAttri.m_iKernAmount;
        }
    }
    
    if (m_bUsePWFont)
    {
        return 1;
    }
    else
    {
        return wOrgHeight;
    }
    
}

// invalid when use ISEFonts
BOOL CWPEngine::CalculateFontHeight(  //  calculate an appropriate height for the text given
                                      IN const wstring& strText // the text specified.
                                      )
{
    CLR_ASSERT(m_iAdjustStyle==EFrameFixed_FontAutosize);

    if (strText.length()==0)
    {
        return FALSE;
    }

    // determine the reference size.
    SIZE   sizeActual;
    GetRefSize(sizeActual);

    //
    SIZE sizeRef = sizeActual;

    AdjustRefSize(sizeRef,FALSE);

	WORD wHeightEachChar = EstFontHeight(sizeRef,strText);
    if (wHeightEachChar==0) // too many character
    {
        goto EXIT_LABEL;
    }
    
    // Increase font height
    wHeightEachChar = IncrFontHeight(wHeightEachChar,sizeRef,strText);
	

    // Decrease font height
    wHeightEachChar = DecrFontHeight(wHeightEachChar,sizeRef,strText);
    if (wHeightEachChar!=0) // too many character
    {
        wHeightEachChar = AdjustHeightAccurately(wHeightEachChar,sizeActual,strText);
    }

    
EXIT_LABEL:
    // 
    if (wHeightEachChar!=0)
    {
        SetFontLogicHeight(wHeightEachChar); // use the current height
    }
    else
    {
        SetFontLogicHeight(m_iMinHeight); // use the minimum height.
    }

	return (wHeightEachChar!=0);
}


void CWPEngine::FormatText( IN const wstring& strText ) 
{
    if (strText.empty())
    {
        return;
    }

    // determine the reference size.
    SIZE   sizeRef;
    GetRefSize(sizeRef);

    // Adjust
    SIZE sizeMax = sizeRef;
    AdjustRefSize(sizeMax,FALSE);

    //
    SIZE    sizePara    = {0,0}; // size of paragraph
    INT     iNumRow     = 1; 
    INT     iTempLen    = 0;    // just a temp length
    wstring strLine     = _T("");
    wstring strCurWord  = _T("");

    size_t iLenText = strText.length();
    CTextLayer* pImage = CreateTextLayer();

    for ( size_t iIndex=0; iIndex<iLenText; iIndex++ )
    {
        SIZE sizeChar;
        wstring strChar(1,strText.at(iIndex));
        ::GetTextExtentPoint32(m_hDC,strChar.c_str(),1,&sizeChar);
        
        BOOL bWordBreak = FALSE;
        if (m_bWordBreak)
        {
            wstring strTempWord;
            BOOL bIsWord = this->GetWord(strText,iIndex,strTempWord);

            if ( bIsWord && strTempWord.compare(strCurWord.c_str())!=0 )
            {
                strCurWord = strTempWord;
                bWordBreak = NeedWordBreak(strCurWord,sizeMax.cx-iTempLen);
            }
        }

        // create a new line( return to next line )?
        BOOL bBreakChar = IsBreakChar(strChar);
        if ( bBreakChar
            || (iTempLen+sizeChar.cx)>sizeMax.cx 
            || bWordBreak)
        {
            if ( !(strLine.empty() && iIndex==0))
            {
                pImage->AddLine(strLine);
                iNumRow ++;
            }

            //
            if ( bBreakChar ) 
            {
                iTempLen = 0;
                strLine.clear();
            }
            else 
            {
                strLine = strChar;

                // current width = char's width + intercharacter spacing
                iTempLen = sizeChar.cx + m_textAttri.m_iKernAmount; 
            }

        }
        else {
            iTempLen += sizeChar.cx;
            iTempLen += m_textAttri.m_iKernAmount; // plus the intercharacter spacing
            strLine.append(strChar);
        }
    }

    CLR_ASSERT(iNumRow>=0); // at least , there is one line!

    // calculate the size of text given.
    ::GetTextExtentPoint32(m_hDC,strLine.c_str(),strLine.length(),&sizePara);
    

    //
    if (iNumRow>1)
    {
        sizePara.cx = sizeMax.cx;
        sizePara.cy = (sizePara.cy*iNumRow) + (iNumRow-1)*m_textAttri.m_iLeadAmount;
    }
    else 
    { 
        // adjust the cx of the size.
        if (m_iAdjustStyle!=EFrameAutosize_FontsizeFixed)
        {
            sizePara.cx = sizeMax.cx;
        }
    }

    //
    AdjustRefSize(sizePara,TRUE);
    pImage->AddLine(strLine);
    if (m_iAdjustStyle!=EFrameAutosize_FontsizeFixed)
    {
        pImage->SetSize(sizePara,sizeRef);
    }
    else
    {
        pImage->SetSize(sizePara,sizePara);
    }

}


BOOL CWPEngine::IsBreakChar(const wstring& strChar) const
{
    if ( strChar==_T("\n")/* || strChar==_T("\r") */)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL CWPEngine::GetWord(const wstring& strText,INT iIndex,
                          OUT wstring& strWord) const
{
    INT iLen = INT(strText.size());
    if (iIndex>=iLen || iIndex<0)
    {
        return FALSE;
    }

    // 
    if ( !::_istalpha(strText[iIndex]) )
    {
        return FALSE;
    }

    //
    INT iBegin = 0,iEnd = 0;

    // forward look up
    for (iBegin=iIndex; iBegin>=0; iBegin--) 
    {
        if ( !::_istalpha(strText[iBegin]) )
        {
            break;
        }
    }

    // backward look up.
    for (iEnd=iIndex; iEnd<iLen; iEnd++) 
    {
        if ( !::_istalpha(strText[iEnd]))
        {
            break;
        }
    }

    // Get the word
    for (INT i=iBegin+1; i<iEnd; i++)
    {
        strWord.push_back(strText[i]);
    }

    // 
    return TRUE;
}

#if 0
INT WPEngine::GetWordCurrentLen(const wstring& strWord,INT iIndex) const
{
    INT iLen = strWord.size();
    if (iIndex<0 || iIndex>=iLen)
    {
        return 0;
    }

    INT iCurLen = 0;

    // forward look up
    for (INT iBegin=iIndex; iBegin>=0; iBegin--) 
    {
        SIZE sizeTemp;
        wstring strChar(&(strWord.at(iBegin)),1);
        ::GetTextExtentPoint32(m_hDC,strChar.c_str(),1,&sizeTemp);
        iCurLen += sizeTemp.cx;
    }

    return iLen;
}
#endif

BOOL  CWPEngine::NeedWordBreak(const wstring& strWord,INT iExtent) const
{
    // determine the reference size.
    SIZE   sizeRef;
    GetRefSize(sizeRef);
    AdjustRefSize(sizeRef,FALSE);

    //
    SIZE sizeWord;
    ::GetTextExtentPoint32(m_hDC,
        strWord.c_str(),
        strWord.size(),
        &sizeWord);

    return (sizeWord.cx>iExtent);

}

void CWPEngine::GetImgText( IN CWStrList& strlistText )
{
    CTextLayer* pImage;
    wstring strText;
    for (CFrameImgList::iterator iCur = m_frmImgList.begin(); iCur!=m_frmImgList.end(); iCur++)
    {
        pImage = *iCur;
        pImage->GetFrameText(strText);
        strlistText.push_back(strText);
    }
}

// Create an empty image.
void CWPEngine::CreateEmptyLayer( 
                        IN CHBmpArray& arBmpActual, //
                        IN CHBmpArray& arBmpVirtual, //
                        IN CWStrList& strList //
                        )
{

    // determine the reference size.
    SIZE   sizeActual;
    GetRefSize(sizeActual);

    //
    CTextLayer* pImg = CreateTextLayer();
    pImg->SetSize(sizeActual,sizeActual);

    HBITMAP hBmpA=NULL,hBmpV=NULL;
    BOOL bFlag = pImg->Create(hBmpA,hBmpV);
    strList.push_back(m_strText);
    arBmpActual.push_back(hBmpA);
    arBmpVirtual.push_back(hBmpV);
}

//
CTextLayer* CWPEngine::CreateTextLayer(  // Create Frame Image
                                      )
{
    CTextLayer* pNewImage = new CTextLayer;

    CLR_ASSERT(pNewImage!=NULL); // Out of memory?

    if (pNewImage!=NULL)
    {
        pNewImage->Initialize(m_textAttri);
        m_frmImgList.push_back(pNewImage);
    }
    return pNewImage;
}

// 
BOOL CWPEngine::CreateBitmap( OUT CHBmpArray& arBmpActual, 
                              OUT CHBmpArray& arBmpVirtual ) 
{
    CTextLayer* pImage = NULL;
    BOOL bFlag;
    HBITMAP hBmpA = NULL;
    HBITMAP hBmpV = NULL;

    //CFrameImgList::iterator iCurImg = m_frmImgList.begin();
    for (size_t i=0; i<m_frmImgList.size(); i++)
    {
        pImage = m_frmImgList[i];
        bFlag = pImage->Create(hBmpA,hBmpV);
        if (hBmpA==NULL || hBmpV==NULL)
        {
            return FALSE;
        }
        else
        {
            arBmpActual.push_back(hBmpA);
            arBmpVirtual.push_back(hBmpV);
        }
    }

    return TRUE;
}

BOOL CWPEngine::GenerateBmp(  // Generate one or several corresponding bitmaps
                              IN CHBmpArray& arBmpActual, //
                              IN CHBmpArray& arBmpVirtual, //
                              IN CWStrList& strList //
                              )
{
    // do some sanity check
    CLR_ASSERT(m_iAdjustStyle!=EAdjustStyleInvalid);

    if ( m_sizeFrame.cx<=0 || 
         m_sizeFrame.cy<=0 || 
         m_iAdjustStyle==EAdjustStyleInvalid)
    {
        return FALSE;
    }

    if (m_textAttri.m_iEffectType<0 || m_textAttri.m_iEffectType>2)
    {
        return FALSE;
    }

    // Clear
    ClearTextLayers();

    BOOL bFlag = !m_strText.empty();

    // check the reference size.
    if (!bFlag)
    {
        goto EXIT_LABEL;
    }


    // Select an appropriate font to use.
    if (m_bUsePWFont)
    {
        bFlag = ChooseProwriteFont();
    }
    else
    {
        if (EFrameFixed_FontAutosize==m_iAdjustStyle)
        {
            //bFlag = CalculateFontHeight(m_strText);
            CalculateFontHeight(m_strText);
        }
    }

    if (!bFlag)
    {
        goto EXIT_LABEL;
    }

    // Format text
    FormatText(m_strText);

    // Make all Textlayers create images.
    bFlag = CreateBitmap(arBmpActual,arBmpVirtual);
    if (bFlag)
    {
        // return the text showing on the each frameImage object.
        GetImgText(strList);
    }

EXIT_LABEL:

    if (!bFlag)
    {
        CreateEmptyLayer(arBmpActual,arBmpVirtual,strList);
    }

    // Clear
    ClearTextLayers();

    return TRUE;

}