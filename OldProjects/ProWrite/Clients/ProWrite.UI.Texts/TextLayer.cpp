#include "Stdafx.h"
#include "TextLayer.h"
#include "UltraString.h"
#include <complex>

#pragma warning (disable:4267)
//////////////////////////////////////////////////////////////////////////

//using namespace  Gdiplus;
using namespace System::Drawing;


#define    MIN_FONTHIEGHT   10


//////////////////////////////////////////////////////////////////////////
// TextAttribute

// Constructor
_tagTextAttribute::_tagTextAttribute()
{

    // LogFont
    memset(&(m_logFont), 0, sizeof(m_logFont));
    m_logFont.lfHeight = 12;
    m_logFont.lfWidth = 0;
    m_logFont.lfEscapement = 0;
    m_logFont.lfOrientation = 0;
    m_logFont.lfWeight = FW_NORMAL;
    m_logFont.lfItalic = FALSE;
    m_logFont.lfUnderline = FALSE;
    m_logFont.lfStrikeOut = 0;
    m_logFont.lfCharSet = DEFAULT_CHARSET;
    m_logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    m_logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS ;
    m_logFont.lfQuality = /*DEFAULT_QUALITY*/NONANTIALIASED_QUALITY;
    m_logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    wcscpy_s(m_logFont.lfFaceName,_T("Arial"));
    m_bRaster = FALSE;


    // 
    m_iEffectType = ETE_NONE;
    m_bShowGrid = FALSE;
    m_clrText.SetFromCOLORREF(RGB(255,255,255));
    m_clrBkg.SetFromCOLORREF(RGB(0,0,0));
    m_iCxShadow = 5;
    m_iCyShadow = -10;
    m_clrShadow.SetFromCOLORREF(RGB(128,128,128));
    m_iWidthOutline = 1;
    m_uAlignment = TA_CENTER;
    m_uVAlignment = DT_VCENTER;
    m_iFirstIndent = 0;
    m_iKernAmount = 0;
    m_iLeadAmount = 0;
}



VOID    _tagTextAttribute::SetBkgColor(const GpClr& clr)
{
    m_clrBkg = clr;
}
GpClr   _tagTextAttribute::GetBkgColor() const
{
    if (IsBkgTspt())
    {
        return CLR_TRANSPARENT_AGENT;
    }
    else
    {
        return m_clrBkg;
    }
}

VOID    _tagTextAttribute::SetTextColor(const GpClr& clr)
{
    m_clrText = clr;
}
GpClr   _tagTextAttribute::GetTextColor() const
{
    if (IsTextTspt())
    {
        return CLR_TRANSPARENT_AGENT;
    }
    else
    {
        return m_clrText;
    }

}

VOID    _tagTextAttribute::SetShadowColor(const GpClr& clr)
{
    m_clrShadow = clr;
}
GpClr   _tagTextAttribute::GetShadowColor() const
{
    if (IsShadowTspt())
    {
        return CLR_TRANSPARENT_AGENT;
    }
    else
    {
        return m_clrShadow;
    }
    
}

VOID    _tagTextAttribute::SetOutlineColor(const GpClr& clr)
{
    m_clrOutline = clr;
}
GpClr   _tagTextAttribute::GetOutlineColor() const
{
    if (IsOutlineTspt())
    {
        return CLR_TRANSPARENT_AGENT;
    }
    else
    {
        return m_clrOutline;
    }

}

BOOL _tagTextAttribute::IsBkgTspt() const
{
    return m_clrBkg.GetA() ==0;
}

BOOL   _tagTextAttribute::IsTextTspt() const
{
    return m_clrText.GetA() == 0;
}

BOOL    _tagTextAttribute::IsShadowTspt() const
{
    return m_clrShadow.GetA() == 0;
}

BOOL    _tagTextAttribute::IsOutlineTspt() const
{
    return m_clrOutline.GetA() == 0;
}

GpClr _tagTextAttribute::GetTsptAgentColor() const
{
    return CLR_TRANSPARENT_AGENT;
}



//////////////////////////////////////////////////////////////////////////
// CFrameImage
CTextLayer::CTextLayer(void):m_hFont(NULL)
{
    m_hDC = ::CreateCompatibleDC(NULL);
    ::SetMapMode(m_hDC,MM_TEXT);
    ::SetBkMode(m_hDC,TRANSPARENT);
}

CTextLayer::~CTextLayer(void)
{
    if (m_hFont)
    {
        ::DeleteObject(m_hFont);
        m_hFont = NULL;
    }

    if (m_hDC)
    {
        ::DeleteDC(m_hDC);
        m_hDC = NULL;
    }

}

// create a new font and select it to DC.
BOOL CTextLayer::CreateFontAndSelect()
{
    // Delete the old font
    if (m_hFont)
    {
        ::DeleteObject(m_hFont);
    }

    // create a new font
    m_hFont = ::CreateFontIndirect(&m_TextAttri.m_logFont);

    // select it to current DC.
    if (m_hFont)
    {
        ::SelectObject(m_hDC,m_hFont);
    }

    return (m_hFont!=NULL);
}

// Initialize
void CTextLayer::Initialize(IN const TTextAttri& attri)
{
    m_TextAttri = attri;

    CreateFontAndSelect();
}

// add line
void CTextLayer::AddLine(IN const wstring& strLine)
{
    m_listLines.push_back(strLine);
}

// Set text size and canvas size.
void CTextLayer::SetSize( IN SIZE sizeText,
                           IN SIZE sizeCanvas
                          )
{
    CLR_ASSERT(sizeText.cx>=0 && sizeText.cy>=0);
    CLR_ASSERT(sizeCanvas.cx>=0 && sizeCanvas.cy>=0);

    m_sizeCanvas = sizeCanvas;
    m_sizeText = sizeText;

    if(sizeText.cx>sizeCanvas.cx)
    {
        m_sizeText.cx = sizeCanvas.cx;
    }

    if (sizeText.cy>sizeCanvas.cy)
    {
        m_sizeText.cy = sizeCanvas.cy;
    }

}


//////////////////////////////////////////////////////////////////////////

void CTextLayer::GetFrameText(wstring& strText)
{
    strText.empty();

    // 
    CWStrArray::iterator iCur = m_listLines.begin();
    CWStrArray::iterator iEnd = m_listLines.end();

    for (; iCur!=iEnd; iCur++)
    {
        strText += *iCur;

        if (iCur+1!=iEnd)
        {
            strText += _T(" "); // 行间加一空格
        }
    }
}

BOOL  CTextLayer::CalcTextLayoutRect( OUT RECT& rcTextLayout //
                                     ) const
{ 

    // the rectangle of CANVAS.
    int iCanvasWidth = m_sizeCanvas.cx;
    int iCanvasHeight = m_sizeCanvas.cy;
    RECT rectCanvas = {0,0,m_sizeCanvas.cx,m_sizeCanvas.cy};

    // 根据垂直对齐方式(m_uVAlignment)得到文本输出区域(Rectangle)
    POINT ptOrg;
    ptOrg.x = m_TextAttri.m_iFirstIndent;

    if (m_TextAttri.m_uVAlignment==DT_TOP)
    {
        ptOrg.y = 0;
    }
    else if (m_TextAttri.m_uVAlignment==DT_VCENTER)
    {
        int iDeta = iCanvasHeight - m_sizeText.cy;
        if (iDeta%2!=0)
        {
            iDeta ++;
        }
        ptOrg.y = iDeta/2 + rectCanvas.top;
    }
    else if (m_TextAttri.m_uVAlignment==DT_BOTTOM)
    {
        ptOrg.y = iCanvasHeight-m_sizeText.cy + rectCanvas.top;
    }
    else
    {
        CLR_ASSERT(FALSE);
        return FALSE;
    }

    // return value
    rcTextLayout.left = ptOrg.x;
    rcTextLayout.top = ptOrg.y;
    rcTextLayout.right = rectCanvas.right;
    rcTextLayout.bottom = rcTextLayout.top + m_sizeText.cy;

    return TRUE;
}

// 根据效果(m_txtEffectType)、行对齐方式(m_uAlignment)以及
// 行号计算当前行(iRowNo)的输出点坐标(POINT)
void CTextLayer::CalcLineLayoutPos( IN INT iRowNo, //    Row No. (based zero)
                                     IN const RECT& rcTextLayout,    // text layout.
                                     OUT POINT& ptPos // the position
                                    ) const
{    
    CLR_ASSERT(iRowNo<(INT)m_listLines.size());

    //
    TCHAR cStrTrimed[MAX_PATH];
    CUltraString::Trim(m_listLines[iRowNo].c_str(),cStrTrimed);
    wstring strLine = cStrTrimed;
    INT iSize = strLine.size();

    // width of a line PLUS all of the intercharacter spacing.
    SIZE sizeLine;
    ::GetTextExtentPoint32(m_hDC,cStrTrimed,iSize,&sizeLine); 

    int iInterCharSpacing = 0;
    if (!strLine.empty())
    {
        iInterCharSpacing = (iSize-1) * m_TextAttri.m_iKernAmount;// intercharacter spacing
        sizeLine.cx += iInterCharSpacing;
    }


    TEXTMETRIC tm;
    ::GetTextMetrics(m_hDC,&tm);
    ptPos.y = rcTextLayout.top + tm.tmHeight*iRowNo;
    ptPos.y += iRowNo*m_TextAttri.m_iLeadAmount;

    // Text Alignment
    if (m_TextAttri.m_uAlignment==TA_LEFT)
    {
        ptPos.x = rcTextLayout.left;

        // Text effect
        if (m_TextAttri.m_iEffectType==ETE_SHADOW)
        {
            (m_TextAttri.m_iCxShadow>=0) ? 0 : ptPos.x+=abs(m_TextAttri.m_iCxShadow);
            (m_TextAttri.m_iCyShadow>=0) ? 0 : ptPos.y+=abs(m_TextAttri.m_iCyShadow);
        }
        else if (m_TextAttri.m_iEffectType==ETE_OUTLINE)
        {
            ptPos.x += m_TextAttri.m_iWidthOutline;
            ptPos.y += m_TextAttri.m_iWidthOutline;
        }

    }
    else if (m_TextAttri.m_uAlignment==TA_CENTER)
    {
        int iWidth = rcTextLayout.right - rcTextLayout.left;
        CLR_ASSERT(iWidth>=iInterCharSpacing);

        int iDeta = iWidth - sizeLine.cx;
        if (iDeta%2!=0)
        {
            iDeta ++;
        }
        ptPos.x = rcTextLayout.left + iDeta/2;

        // Text effect
        if (m_TextAttri.m_iEffectType==ETE_SHADOW)
        {
            ptPos.x -= m_TextAttri.m_iCxShadow/2;
            (m_TextAttri.m_iCyShadow>=0) ? 0 : (ptPos.y+=abs(m_TextAttri.m_iCyShadow));
        }
        else if (m_TextAttri.m_iEffectType==ETE_OUTLINE)
        {
            ptPos.y += m_TextAttri.m_iWidthOutline;
        }

    }
    else if (m_TextAttri.m_uAlignment==TA_RIGHT)
    {
        ptPos.x = rcTextLayout.right - sizeLine.cx;

        // Text effect
        if (m_TextAttri.m_iEffectType==ETE_SHADOW)
        {
            (m_TextAttri.m_iCxShadow>0) ?  0 : (ptPos.x-=m_TextAttri.m_iCxShadow);
            (m_TextAttri.m_iCyShadow>=0) ? 0 : (ptPos.y+=abs(m_TextAttri.m_iCyShadow));
        }
        else if (m_TextAttri.m_iEffectType==ETE_OUTLINE)
        {
            ptPos.x -= m_TextAttri.m_iWidthOutline;
            ptPos.y += m_TextAttri.m_iWidthOutline;
        }
    }
    else
    {
        CLR_ASSERT(FALSE);
    }

    // Adjust accurately ( should be optimized)
    if (m_TextAttri.m_logFont.lfItalic)
    {
        if (m_TextAttri.m_bRaster)
        {
            //ptPos.x = ptPos.x-(10-CVATransformer::GetRatio());
            ptPos.x -= 3;
        }
    }

}


// calculate the inter character spacing 
void CTextLayer::CalcInterCharacterSpacing( IN const wstring& strLine,   //
                                  OUT LPINT lpDx) const
{
    SIZE sizeChar;
    size_t iLen = strLine.size();
    for (size_t i=0; i<iLen; i++)
    {
        wstring strChar(&(strLine.at(i)),1);
        ::GetTextExtentPoint32(m_hDC,strChar.c_str(),1,&sizeChar);
        *(lpDx+i) = m_TextAttri.m_iKernAmount + sizeChar.cx;
    }

}


BOOL CTextLayer::NeedBubbleSurround() const
{
    if (m_TextAttri.m_iEffectType!=ETE_OUTLINE)
    {
        return FALSE;
    }
    
	SIZE sizeChar;
	wstring strChar = L"I";
	::GetTextExtentPoint32(m_hDC,strChar.c_str(),1,&sizeChar);

    //
    //ABC abc[2];
    //::GetCharABCWidthsI(m_hDC,L'I',1,NULL,abc);
    INT iCharWidth = sizeChar.cx;

    if (iCharWidth>5)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
	
}


void CTextLayer::CalcGridPos( OUT CPointArray& ptArray
                              ) const
{
    CLR_ASSERT(CVATransformer::GetRatio()>0);
    ptArray.resize(0); 

    // number of line
    int iNumRow = m_sizeCanvas.cy;

    // number of column
    int iNumCol = m_sizeCanvas.cx;

    // calculate column position.
    POINT pt1,pt2;
    pt1.y = 0;
    pt2.y = iNumRow * CVATransformer::GetRatio();
    for (int i=0; i<=iNumCol; i++)
    {
        pt1.x = i*CVATransformer::GetRatio();
        pt2.x = pt1.x;

        ptArray.push_back(pt1);
        ptArray.push_back(pt2);
    }

    // calculate line position.
    pt1.x = 0;
    pt2.x = iNumCol*CVATransformer::GetRatio();
    for (int j=0; j<=iNumRow; j++)
    {
        pt1.y = j*CVATransformer::GetRatio();

        pt2.y = pt1.y;

        ptArray.push_back(pt1);
        ptArray.push_back(pt2);
    }
}

void CTextLayer::DrawGrid(IN HDC hDC) const
{
    if (CVATransformer::GetRatio()<=1)
    {
        return ; // It's no need to draw grid.
    }

    // Create a new pen to draw grid.    
    HPEN hNewPen = ::CreatePen(PS_SOLID,1,RGB(130,130,130)/*m_TextAttri.m_clrGrid.ToCOLORREF()*/);
    HPEN hOldPen = (HPEN)::SelectObject(hDC,hNewPen);

    //
    CPointArray ptArray;
    CalcGridPos(ptArray);
    INT iSize = ptArray.size();
    CLR_ASSERT(iSize%2==0);
    if (iSize%2==0)
    {
        // Draw lines
        for (int i=0; i<iSize; i+=2)
        {
            POINT pt1 = ptArray[i];
            POINT pt2 = ptArray[i+1];
            ::MoveToEx(hDC,pt1.x,pt1.y,NULL);
            ::LineTo(hDC,pt2.x,pt2.y);
        }
    }

    // Release resource
    ::SelectObject(hDC,hOldPen);
    ::DeleteObject(hNewPen);
}

void CTextLayer::DrawGridEx(IN HDC hDC) const
{
    if (CVATransformer::GetRatio()<=1)
    {
        return ; // It's no need to draw grid.
    }
    
    Gdiplus::Graphics g(hDC);
    GpClr clrGrid(50,
        250-m_TextAttri.m_clrBkg.GetR(),
        250-m_TextAttri.m_clrBkg.GetG(),
        250-m_TextAttri.m_clrBkg.GetB());
    Gdiplus::Pen penGrid(clrGrid,1);

    //
    CPointArray ptArray;
    CalcGridPos(ptArray);
    int iSize = ptArray.size();
    CLR_ASSERT(iSize%2==0);

    // Draw lines
    for (int i=0; i<iSize; i+=2)
    {
        POINT pt1 = ptArray[i];
        POINT pt2 = ptArray[i+1];
        g.DrawLine(&penGrid,pt1.x,pt1.y,pt2.x,pt2.y);
    }
}

// stretch the bitmap. Return the destination bitmap.
HBITMAP CTextLayer::StretchBitmap(IN HDC hdcSrc,
                                  IN SIZE sizeOrg,
                                  IN SIZE sizeDest) const
{
    HBITMAP hBmpStretch = NULL;
    HDC hdcDest = NULL;
    HANDLE hOldBmp = NULL;

    try
    {
        // create a stretchable bitmap
        hBmpStretch = ::CreateCompatibleBitmap(hdcSrc,sizeDest.cx,sizeDest.cy);
        if (hBmpStretch!=NULL)
        {
            // create memory DC
            hdcDest = ::CreateCompatibleDC(hdcSrc);
            CLR_ASSERT(hdcDest!=NULL);
            hOldBmp = ::SelectObject(hdcDest,hBmpStretch);

            // to stretch the bitmap.
            //POINT ptBrush;
            //::GetBrushOrgEx(hdcDest,&ptBrush);
            ::SetStretchBltMode(hdcSrc,BLACKONWHITE);
            ::SetStretchBltMode(hdcDest,BLACKONWHITE);
            //::SetBrushOrgEx(hdcDest,ptBrush.x,ptBrush.y,NULL);
            BOOL bFlag = ::StretchBlt(hdcDest,0,0,sizeDest.cx,sizeDest.cy,
                hdcSrc,0,0,sizeOrg.cx,sizeOrg.cy,SRCCOPY);
            CLR_ASSERT(bFlag==TRUE);
            UNREFERENCED_PARAMETER(bFlag);
        }

    }
    catch(...)
    {
        throw std::exception(("CFrameImage::StretchBitmap() cathes an error!"));
    }
    finally
    {
        if (hdcDest!=NULL)
        {
            ::SelectObject(hdcDest,hOldBmp);
            ::DeleteDC(hdcDest);
        }
    }

    // Return the BITMAP.
    return hBmpStretch;
}

// 
HBITMAP CTextLayer::Create32Bitmap(IN HDC hDC,const SIZE& size)
{
    // Build BITMAPINFO
    BITMAPINFO bmpInfo;
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biPlanes = 1; 
    bmpInfo.bmiHeader.biBitCount = 32; 
    bmpInfo.bmiHeader.biCompression = BI_RGB; 
    bmpInfo.bmiHeader.biSizeImage = 0; 
    bmpInfo.bmiHeader.biClrUsed = 0; 
    bmpInfo.bmiHeader.biWidth = size.cx;
    bmpInfo.bmiHeader.biHeight = size.cy;

    // Create a 32-bit bitmap.
    LPVOID lpBits = NULL;

    HBITMAP hBmp32 =::CreateDIBSection(hDC, // create a DIB, do not call CreateDIBitmap to create a DDB.
        &bmpInfo,
        DIB_RGB_COLORS,
        &lpBits,
        NULL,
        0);
#ifdef _DEBUG
    //HBITMAP hBmpTest = ::CreateDIBitmap(hDC, &(bmpInfo.bmiHeader), 0,NULL,&bmpInfo, DIB_RGB_COLORS);
    //BITMAP bitmap;
    //::GetObject(hBmpTest,sizeof(BITMAP),&bitmap);
    //DIBSECTION dibsection;
    //::GetObject(hBmpTest,sizeof(dibsection),&dibsection);
    ////
    //return hBmpTest;
#endif

    return hBmp32;
}

// 
BOOL CTextLayer::Create(HBITMAP& hBmpActual,HBITMAP& hBmpVirtual)
{
    BOOL bFlag = TRUE;
    HDC hDeskDC = ::GetDC(NULL);
    HBITMAP hOldBmp = NULL;

    // create bitmap and select it to the display context.
    hBmpActual = Create32Bitmap(hDeskDC,m_sizeCanvas);
    if (hBmpActual==NULL)
    {
        return FALSE;
    }
    hOldBmp = (HBITMAP)::SelectObject(m_hDC,hBmpActual);

    // fill background
    HBRUSH hBkgBrush = ::CreateSolidBrush(m_TextAttri.GetBkgColor().ToCOLORREF());    
    RECT rectCanvas = {0,0,m_sizeCanvas.cx,m_sizeCanvas.cy};
    ::FillRect(m_hDC,&rectCanvas,hBkgBrush);
    ::DeleteObject(hBkgBrush);


    // no text to draw?
    if ( m_listLines.size()!=0 )
    {
        DrawTextLayer(m_hDC,hBmpActual);
    }

    ::SelectObject(m_hDC,hOldBmp);

    // 
    hOldBmp = (HBITMAP)::SelectObject(m_hDC,hBmpActual);

    // stretch        
    SIZE sizeVirtual;
    CVATransformer::A2V(m_sizeCanvas,sizeVirtual);
    hBmpVirtual = StretchBitmap(m_hDC,m_sizeCanvas,sizeVirtual);

    if (hBmpVirtual==NULL)
    {
        bFlag = FALSE;
    }
    else
    {
        // draw grid
        if (m_TextAttri.m_bShowGrid)
        {
            ::SelectObject(m_hDC,hBmpVirtual);
            DrawGrid(m_hDC);
        }
    }

    ::SelectObject(m_hDC,hOldBmp);
    ::ReleaseDC(NULL,hDeskDC);
    
    //
    return bFlag;
}
BOOL CTextLayer::DrawTextLayer( IN HDC hdc, IN HBITMAP hBitmap)
{
    // ATTENTION: !!!DO NOT call. 当使用TA_CENTER与TA_RIGHT时，ExtTextOut的第三个参数无效
    //::SetTextAlign(m_hDC,m_TextAttri.m_uAlignment); 


    ::SetTextAlign(hdc,TA_LEFT); // Must be set to TA_LEFT.
    ::SetBkColor(hdc,m_TextAttri.GetBkgColor().ToCOLORREF());
    ::SetBkMode(hdc,TRANSPARENT);


    // switch
    if (m_TextAttri.m_iEffectType==ETE_NONE)
    {
        DrawRawText(hdc);
    }
    else if (m_TextAttri.m_iEffectType==ETE_SHADOW)
    {
        DrawShadow(hdc);
    }
    else if (m_TextAttri.m_iEffectType==ETE_OUTLINE)
    {

        DrawOutlineEx_Img(hdc,hBitmap);
        //DrawOutlineEx(hdc);

		/*
		if ( !NeedBubbleSurround())
	    {
		    DrawOutlineEx(hdc);
	    }
	    else
	    {
		    DrawBubble(hdc);
	    }
       */
		
    }
	else
	{
		CLR_ASSERT(ERROR);
	}

    return TRUE;
}

void CTextLayer::DrawString(IN HDC hdc,
                            IN const GpClr& clrText,
                            IN const POINT& ptPos,
                            IN const TString& strLine)
{
    // inter-character spacing
    LPINT lpDX = NULL;
    if (m_TextAttri.m_iKernAmount!=0)
    {
        lpDX = new INT[strLine.size()];
        CalcInterCharacterSpacing(strLine,lpDX);
    }

    // Set text color.
    ::SetTextColor(hdc,clrText.ToCOLORREF());

    // Text out
    BOOL bFlag = ::ExtTextOut(hdc,ptPos.x,ptPos.y,ETO_OPAQUE,
        NULL,strLine.c_str(),strLine.length(),lpDX);

    CLR_ASSERT(bFlag==TRUE);

    //
    delete[] lpDX;
}


//////////////////////////////////////////////////////////////////////////
// to draw raw text .
void CTextLayer::DrawRawText(IN HDC hdc) 
{
    // get the text layout extent.
    RECT rcTextLayout;
    CalcTextLayoutRect(rcTextLayout);

    //
    wstring strLine;
    int iNumLine = m_listLines.size();
    for ( int i=0; i<iNumLine; i++)
    {
        strLine = m_listLines[i];

        // position
        POINT ptPos;
        CalcLineLayoutPos(i,rcTextLayout,ptPos);        

        //
        DrawString(hdc,m_TextAttri.GetTextColor(),ptPos,strLine);
    }
}

// shadow effect
void CTextLayer::DrawShadow(IN HDC hDC)
{
    // get the text layout extent.
    RECT rcTextLayout;
    CalcTextLayoutRect(rcTextLayout);

    //
    wstring strLine;
    int iNumLine = m_listLines.size();

    // Draw Shadow
    for ( int i=0; i<iNumLine; i++)
    {
        strLine = m_listLines[i];

        // position
        POINT ptText;
        CalcLineLayoutPos(i,rcTextLayout,ptText);

        // draw shadow
        POINT ptShadow;
        ptShadow.x = ptText.x + m_TextAttri.m_iCxShadow;
        ptShadow.y = ptText.y + m_TextAttri.m_iCyShadow;
        DrawString(hDC,m_TextAttri.GetShadowColor(),ptShadow,strLine);
    }

    // Draw raw text.
    DrawRawText(hDC);
/*
    // Draw Text
    for ( int i=0; i<iNumLine; i++)
    {
        strLine = m_listLines[i];

        // position
        POINT ptText;
        CalcLineLayoutPos(i,rcTextLayout,ptText);

        // draw text
        DrawString(hDC,m_TextAttri.GetTextColor(),ptText,strLine);
    }
*/

}

// outline effect
/************************************************************************/
/* use GDI+                                                             */
/************************************************************************/
void CTextLayer::DrawOutline_GDIP(IN Gdiplus::Graphics &g, 
                                    IN const wstring &strText, 
                                    IN const Gdiplus::FontFamily *fontFamily, 
                                    IN INT style,
                                    IN Gdiplus::REAL emSize,
                                    IN const Gdiplus::StringFormat* strFormat) const
{
    g.Clear(m_TextAttri.GetBkgColor());

    // create a path 
    Gdiplus::GraphicsPath path;

    // Add a string
    path.AddString( strText.c_str(),strText.length(),
        fontFamily,style,emSize,
        Gdiplus::Point(0,0), strFormat);

    // Select the pen
    Gdiplus::Pen penOutline(m_TextAttri.GetOutlineColor(),(Gdiplus::REAL)m_TextAttri.m_iWidthOutline); 

    //Fill it 
    g.FillPath( &Gdiplus::SolidBrush(m_TextAttri.GetTextColor()),&path); 

    //outline it 
    g.DrawPath(&penOutline,&path);
    

}

/************************************************************************/
/* use GDI's PATH method(invalid when using raster font)                  */
/************************************************************************/
void CTextLayer::DrawOutline( IN HDC hDC) 
{
    HPEN hOldPen = NULL;
    HBRUSH hOldBrush = NULL;
    HBRUSH hBrush = NULL;
    HPEN hPenStroke = NULL;
    wstring strLine;

    // Set text color
    ::SetTextColor(hDC,m_TextAttri.GetTextColor().ToCOLORREF());

    // The pen, to draw path.
    hPenStroke = ::CreatePen(PS_SOLID,
        m_TextAttri.m_iWidthOutline,
        m_TextAttri.GetOutlineColor().ToCOLORREF());

    if (NULL!=hPenStroke)
    {
        hOldPen = (HPEN)::SelectObject(hDC,hPenStroke);        
    }
    else
    {
        goto EXIT_LABEL;
    }

    // The pen, to draw text
    hBrush = ::CreateSolidBrush(m_TextAttri.GetTextColor().ToCOLORREF());
    if (NULL!=hBrush)
    {
        hOldBrush = (HBRUSH)::SelectObject(hDC,hBrush);
    }
    else
    {
        goto EXIT_LABEL;
    }

    // get the text layout extent.
    RECT rcTextLayout;
    CalcTextLayoutRect(rcTextLayout);

    // draw
    int iNumLine = m_listLines.size();
    for ( int i=0; i<iNumLine; i++)
    {
        strLine = m_listLines[i];

        // position
        POINT ptPos;
        CalcLineLayoutPos(i,rcTextLayout,ptPos);

        // use a path to record how the text was drawn
        ::BeginPath(hDC);
        ::ExtTextOut(hDC,ptPos.x,ptPos.y,ETO_OPAQUE,NULL,strLine.c_str(),strLine.length(),NULL);
        ::EndPath(hDC);

        //::WidenPath(hDC);
        // Draw Text
        ::ExtTextOut(hDC,ptPos.x,ptPos.y,ETO_OPAQUE,NULL,strLine.c_str(),strLine.length(),NULL);

        // fill path
        //::SetPolyFillMode(hDC,WINDING);
        ::StrokePath(hDC);
    }

EXIT_LABEL:

    // Put back the old object.
    if (NULL!=hPenStroke)
    {
        ::SelectObject(hDC,hOldPen);
        ::DeleteObject(hPenStroke);
    }
    if (NULL!=hBrush)
    {
        ::SelectObject(hDC,hOldBrush);
        ::DeleteObject(hBrush);
    }
}

/************************************************************************/
/*  use GDI,valid under all font.                                       */
/************************************************************************/
void CTextLayer::DrawOutlineEx( IN HDC hDC ) 
{
    // background mode
    ::SetBkMode(hDC,TRANSPARENT);

    // Get the old text color
    COLORREF clrOld = ::GetTextColor(hDC);


    // get the text layout extent.
    RECT rcTextLayout;
    CalcTextLayoutRect(rcTextLayout);

    //
    wstring strLine;
    INT iNumLine = INT(m_listLines.size());
    for ( int k=0; k<iNumLine; k++)
    {
        strLine = m_listLines[k];

        // position
        POINT ptPos;
        CalcLineLayoutPos(k,rcTextLayout,ptPos);

        // Draw Outline ....
        
        POINT ptOutline;

#if 0
        // left move
        ptOutline = ptPos;
        for (int i=0; i<m_TextAttri.m_iWidthOutline; i++)
        {
            ptOutline.x -= 1;
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptOutline,strLine);
        }

        // right move
        ptOutline = ptPos;
        for (int i=0; i<m_TextAttri.m_iWidthOutline; i++)
        {
            ptOutline.x += 1;
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptOutline,strLine);
        }
#endif

        // top move
        ptOutline = ptPos;
        for (int i=1; i<=m_TextAttri.m_iWidthOutline; i++)
        {
            // Change the Y-position
            ptOutline.y -= 1;

            // draw text
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptOutline,strLine);

            // draw top-left region
            ptOutline.x = ptPos.x;
            for (int j=0; j<m_TextAttri.m_iWidthOutline; j++)
            {
                ptOutline.x -= 1;
                DrawString(hDC,m_TextAttri.GetOutlineColor(),ptOutline,strLine);
            }

            // draw top-right region
            ptOutline.x = ptPos.x;
            for (int j=0; j<m_TextAttri.m_iWidthOutline; j++)
            {
                ptOutline.x += 1;
                DrawString(hDC,m_TextAttri.GetOutlineColor(),ptOutline,strLine);
            }

        }

        // bottom move
        ptOutline = ptPos;
        for (int i=1; i<=m_TextAttri.m_iWidthOutline; i++)
        {
            // Change the Y-position
            ptOutline.y += 1;

            // Draw text
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptOutline,strLine);

            // bottom-left
            ptOutline.x = ptPos.x;
            for (int j=0; j<m_TextAttri.m_iWidthOutline; j++)
            {
                ptOutline.x -= 1;
                DrawString(hDC,m_TextAttri.GetOutlineColor(),ptOutline,strLine);
            }

            // bottom-right
            ptOutline.x = ptPos.x;
            for (int j=0; j<m_TextAttri.m_iWidthOutline; j++)
            {
                ptOutline.x += 1;
                DrawString(hDC,m_TextAttri.GetOutlineColor(),ptOutline,strLine);
            }
        }
        

        // Draw actual text ....
        //DrawString(hDC,m_TextAttri.GetTextColor(),ptPos,strLine);
    }


    // Draw raw text.
    DrawRawText(hDC);


    // Put back the old object.
    ::SetTextColor(hDC,clrOld);
}

void CTextLayer::DrawOutlineEx_Img(
                          IN HDC hDC,  // Device Context.
                          IN HBITMAP hBitmap  )
{

    INT in_pixels = m_TextAttri.m_iWidthOutline;
    DWORD searchkey = m_TextAttri.m_clrText.GetValue() & 0xFFFFFF;
    DWORD dest = m_TextAttri.m_clrOutline.GetValue()   & 0xFFFFFF;
    
    //
    DrawRawText(hDC);

    // 
    if ( in_pixels < 0)
    {
        return;
    }

    // BITMAP information
    BITMAP bmp;
    ::GetObject(hBitmap,sizeof(bmp),&bmp);

    // Pointer to Bitmap data
    DWORD* pImgBits = (DWORD*)bmp.bmBits;

    // Everything allocated correctly for the copy.  Perform the outline
    for (int i = 0; i < bmp.bmHeight; i++)
    {
        for (int j = 0; j < bmp.bmWidth; j++)
        {
            if ( *pImgBits == searchkey)
            {
                //got a hit now search around it
                //Sub box variables
                int xleft, ytop, xright, ybottom;

                //Find the sub box size around the pixel
                if ((j - in_pixels) < 0)
                    xleft = -in_pixels + (j -in_pixels);
                else 
                    xleft = in_pixels; 

                if ((j + in_pixels) > bmp.bmWidth)
                    xright = bmp.bmWidth - (in_pixels + j);
                else
                    xright  = in_pixels;

                if ((i - in_pixels) < 0)
                    ytop = -in_pixels + (i -in_pixels);
                else 
                    ytop = in_pixels; 

                if ((i + in_pixels) > bmp.bmHeight)
                    ybottom = bmp.bmHeight - (in_pixels + i);
                else
                    ybottom  = in_pixels;

                // Sub box set and bounded to within the original image size
                DWORD* pStartData = (DWORD*)bmp.bmBits;

                for (int x = i - xleft; (x<=i+xright) && x<bmp.bmHeight; x++)
                {
                    for (int y = j - ytop; (y <=j+ybottom) && y<bmp.bmWidth; y++)
                    {
                        INT iIndex = (bmp.bmWidth * x) + y;

                        // set all pixels around the found pixel and
                        // not set any that are part of the search key
                        if ( pStartData[iIndex] != searchkey )
                        {
                            pStartData[iIndex] = dest;
                        }
                    }
                }
            }

            pImgBits ++;
        }
    }


}

// Bubble effect
SIZE CTextLayer::GetBubbleSize( IN HDC hdc,
                                  IN const wstring& strText
                                  ) const
{
    SIZE size = {0,0};
    if (!strText.empty())
    {
        ::GetTextExtentPoint32(hdc,strText.c_str(),strText.length(),&size);

        size_t iWidth = size.cx/strText.length();

        size.cx = iWidth/4+1;
        size.cy = size.cy/10;
    }
    return size;
}

void CTextLayer::DrawBubble( IN HDC hDC) 
{

    // background mode
    ::SetBkMode(hDC,TRANSPARENT);

    // Get the old text color
    COLORREF clrOld = ::GetTextColor(hDC);


    // get the text layout extent.
    RECT rcTextLayout;
    CalcTextLayoutRect(rcTextLayout);

    //
    wstring strLine;
    INT iNumLine = INT(m_listLines.size());
    for ( int m=0; m<iNumLine; m++)
    {
        strLine = m_listLines[m];

        // position
        POINT ptPos;
        CalcLineLayoutPos(m,rcTextLayout,ptPos);

        //
        SIZE sizeBubble = GetBubbleSize(hDC,strLine);

        // movement
        int i = 0;

        // left
        POINT ptBubble = ptPos;
        for (i=0; i<sizeBubble.cx; i++)
        {
            ptBubble.x -= 1;
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptBubble,strLine);
        }

        // right
        ptBubble = ptPos;
        for (i=0; i<sizeBubble.cx; i++)
        {
            ptBubble.x += 1;
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptBubble,strLine);
        }

        // top
        ptBubble = ptPos;
        for (i=0; i<sizeBubble.cy; i++)
        {
            ptBubble.y -= 1;
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptBubble,strLine);
        }

        // bottom
        ptBubble = ptPos;
        for (i=0; i<sizeBubble.cy; i++)
        {
            ptBubble.y += 1;
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptBubble,strLine);
        }

        // top-left
        int iWidth = (sizeBubble.cx+sizeBubble.cy)/2;
        ptBubble = ptPos;
        for (i=0; i<iWidth; i++)
        {
            ptBubble.x -= 1;
            ptBubble.y -= 1;
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptBubble,strLine);
        }

        // top-right
        ptBubble = ptPos;
        for (i=0; i<iWidth; i++)
        {
            ptBubble.x += 1;
            ptBubble.y -= 1;
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptBubble,strLine);
        }

        // bottom-left
        ptBubble = ptPos;
        for (i=0; i<iWidth; i++)
        {
            ptBubble.x -= 1;
            ptBubble.y += 1;
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptBubble,strLine);
        }

        // bottom-right
        ptBubble = ptPos;
        for (i=0; i<iWidth; i++)
        {
            ptBubble.x += 1;
            ptBubble.y += 1;
            DrawString(hDC,m_TextAttri.GetOutlineColor(),ptBubble,strLine);
        }

        // text color
        DrawString(hDC,m_TextAttri.GetTextColor(),ptPos,strLine);
    }


    // Put back the old object.
    ::SetTextColor(hDC,clrOld);

//////////////////////////////////////////////////////////////////////////

}