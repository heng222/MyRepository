#pragma once
//////////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "VATransformer.h"


// 
CONST  GpClr CLR_TRANSPARENT_AGENT = GpClr(255,10,10,10);
CONST  GpClr CLR_BLACK_AGENT = GpClr(255,1,1,1);

// text effect definition
typedef enum tagTextEffect
{
    ETE_NONE,
    ETE_SHADOW,     // Shadow
    ETE_OUTLINE,    // Outline

}TTextEffect;

// Text attribute
typedef struct _tagTextAttribute 
{

    TTextEffect m_iEffectType;

    // Common attribute ..
    LOGFONT		m_logFont;      // logic font
    BOOL        m_bRaster;      // raster font?
    UINT		m_uAlignment;   // alignment
    UINT        m_uVAlignment;  // line alignment
    INT 		m_iFirstIndent; // First indent
    INT         m_iLeadAmount;  // lead amount
    INT         m_iKernAmount;  // Kern amount
    GpClr	    m_clrText;      // text color
    GpClr	    m_clrBkg;       // background color
    GpClr       m_clrGrid;      // Grid Color

    // Effect Attributes ...
    BOOL        m_bShowGrid;
    
    // Only valid under ETE_SHADOW
    int         m_iCxShadow;
    int         m_iCyShadow;
    GpClr       m_clrShadow;

    // Only valid under ETE_OUTLINE
    INT         m_iWidthOutline;
    GpClr       m_clrOutline;

public:

    // Constructor
    _tagTextAttribute();

    // Color Operations.
public:

    VOID    SetBkgColor(const GpClr& clr);
    GpClr   GetBkgColor() const;
    
    VOID    SetTextColor(const GpClr& clr);
    GpClr   GetTextColor() const;

    VOID    SetShadowColor(const GpClr& clr);
    GpClr   GetShadowColor() const;
    
    VOID    SetOutlineColor(const GpClr& clr);
    GpClr   GetOutlineColor() const;

public:

    //
    BOOL    IsBkgTspt() const;
    BOOL    IsTextTspt() const;
    BOOL    IsShadowTspt() const;
    BOOL    IsOutlineTspt() const;

    GpClr   GetTsptAgentColor() const;

}TTextAttri,*PTTextAttri;

//////////////////////////////////////////////////////////////////////////
// 
class CTextLayer
{
public:

    CTextLayer(void);
    ~CTextLayer(void);

    // Attributes
private:

    HDC         m_hDC;
    HFONT       m_hFont;

    TTextAttri  m_TextAttri;

    SIZE        m_sizeText; // extent of text
    SIZE        m_sizeCanvas; // extent of canvas
    //SIZE        m_sizeDest; // extent of destination.

    CWStrArray  m_listLines;

    // Virtual methods
protected:


private:

    // Create font and select it to dc
    BOOL    CreateFontAndSelect();

    // calculate the entire text rectangle .
    BOOL    CalcTextLayoutRect( OUT RECT& rcTextLayout // the layout extent of a line.
                               ) const;

    // specific line layout rectangle
    void    CalcLineLayoutPos( IN INT iRowNo, //    Row No. (based zero)
                                IN const RECT& rcTextLayout,    // text layout.
                                OUT POINT& ptPos // the position
                               ) const;

    // calculate the intercharacter spacing 
    void    CalcInterCharacterSpacing( IN const wstring& strLine,   //
                                       OUT LPINT lpDx
                                       ) const;

	// Need bubble surround ?
	BOOL	NeedBubbleSurround() const;

    // Position grid
    void    CalcGridPos( OUT CPointArray& ptArray) const;

	// Draw Grid(GDI)
	void	DrawGrid(IN HDC hDC) const;
    void	DrawGridEx(IN HDC hDC) const;

    // Create a 32Bit bitmap.
    HBITMAP Create32Bitmap(IN HDC hDC,const SIZE& size);

// functions
public:

    void    Initialize(IN const TTextAttri& attri);

    void    SetSize( IN SIZE sizeText,  //
                     IN SIZE sizeCanvas
                    );

    SIZE    GetCanvasSize() const { return m_sizeCanvas; }

    void    AddLine(IN const wstring& strLine);

    void    GetFrameText(OUT wstring& strText);

    BOOL    Create(HBITMAP& hActual,HBITMAP& hVirtual);

// interface
public:

    //void    SetTextColor(GpClr clr) { m_TextAttri.m_clrText=clr; }
    //void    SetBkgColor(GpClr clr) { m_TextAttri.m_clrBkg=clr; }
    void    SetAlinment(UINT align) { m_TextAttri.m_uAlignment=align; }
    void    SetLineAline(UINT align) { m_TextAttri.m_uVAlignment=align; }

    BOOL    DrawTextLayer(IN HDC hdc, IN HBITMAP hBitmap);

    void    DrawString(IN HDC hdc,  // 
                       IN const GpClr& clrText, //
                       IN const POINT& ptPos,   // 
                       IN const TString& strText //
                       ) ;
    
    HBITMAP StretchBitmap( IN HDC hdcSrc,
                           IN SIZE sizeOrg,
                           IN SIZE sizeDest) const;


// Effects implementation
public:

    //
    TTextEffect GetEffectType() const { return m_TextAttri.m_iEffectType; }


    // Non-effect
    void    DrawRawText(IN HDC hdc) ;

    // Shadow effect
    //void    SetShadowColor(const GpClr& clr) { m_TextAttri.m_clrShadow=clr; }
    void    DrawShadow(
                IN HDC hDC  // 
                ) ;


    // Outline effect
    //void    SetOutlineColor(const GpClr& clr) { m_TextAttri.m_clrOutline=clr; }
    void    DrawOutline_GDIP(
                IN Gdiplus::Graphics &g, 
                IN const wstring &strText, 
                IN const Gdiplus::FontFamily *fontFamily, 
                IN INT style,
                IN Gdiplus::REAL emSize,
                IN const Gdiplus::StringFormat* strFormat
                ) const;
    void    DrawOutline(IN HDC hDC
                ) ;// Only for TrueType fonts

    void    DrawOutlineEx( // Using the self-defined arithmetic.
                    IN HDC hDC  // Device Context.
                ) ; // Available for all fonts

    void    DrawOutlineEx_Img(
                    IN HDC hDC,  // Device Context.
                    IN HBITMAP hBitmap
                    );

    // Bubble surround
    SIZE    GetBubbleSize(
                    IN HDC hdc,
                    IN const wstring& strText
                    ) const;
    void    DrawBubble(
                IN HDC hDC   // 
                ) ;
};
//////////////////////////////////////////////////////////////////////////
// 

typedef    vector<CTextLayer*>     CFrameImgList;