// WPEngine.h : Declaration of the CFontBmpGen

#pragma once

#include "FontsMgr.h"
#include "ProwriteFont.h"
#include "TextLayer.h"
 
// adjust type
typedef enum _tagAdjustStyle
{
    EAdjustStyleInvalid = 0x00,

    EFrameAutosize_FontsizeFixed = 0x01,
    EFrameFixed_FontAutosize = 0x10,
    EFrameFixed_FontsizeFixed = 0x11,

}TAdjustStyle;


/////////////////////////////////////////////////////////////////////////////
// CWPEngine - Word process engine
class  CWPEngine
{
public:

	CWPEngine();

	~CWPEngine();

private:

    CFrameImgList   m_frmImgList;

public:


	// Attributes
private:

	HDC		m_hDC;

    INT     m_iAdjustStyle; // TAdjustStyle

	// Size of sign
	SIZE		m_sizeSign;
	// size of frame
	SIZE		m_sizeFrame;

	wstring		m_strText;

	HFONT		m_hFont;

    TTextAttri  m_textAttri;

    //BOOL        m_bTransparent;

    BOOL        m_bWordBreak;

    BOOL        m_bUsePWFont;   // Is the current font Prowrite font?

private:

    int         m_iMinHeight; // in pixel unit.


	// Private members
private:

    // retrieve the reference size.
    void    GetRefSize( OUT SIZE& sizeRef) const;

    // check the size
    BOOL    CheckRefSize() const;

	// create font and select it the current DC.
    BOOL	CreateSysFont();



    // Font Height Adjustment
private:


	// calculate the height of the font according to the size given.
    // False: can't find an appropriate height for current text 
    //        OR the text is empty. then use the minimum height.
    // TRUE: found an appropriate height.
	BOOL	CalculateFontHeight( IN const wstring& strText     // 
                                );

	// estimate the extent of the text. Return the number of row.
	void 	EstParagraphSize( IN const wstring& strText, // 
                         IN const SIZE& sizeMax, // extent
                         OUT SIZE& sizeText // 
                         ) const;


    // estimate the height of the font under the rectangle given.
    WORD    EstFontHeight( IN const SIZE& sizeExtent,   // 
                           IN const wstring& strText    // 
                           );

    // increase the font height according to the referenced size.
    WORD    IncrFontHeight( IN WORD wOrginHeight,   //
                            IN const SIZE& sizeRef, //
                            IN const wstring& strTextRef    //
                            );

    // decrease the font height according to the referenced size.
    WORD    DecrFontHeight( IN WORD wOrginHeight,   //
                            IN const SIZE& sizeRef, //
                            IN const wstring& strTextRef    //
                            );
    // adjust the height accurately.
    WORD    AdjustHeightAccurately( 
                              IN WORD wOrgHeight,
                              IN const SIZE& sizeExtent,
                              IN const wstring& strText
                              );

    // select an appropriate Prowrite fonts to use.
    BOOL    ChooseProwriteFont();

    // 
private:
    
    // fix the given text
    void    FixText(wstring& strText) const;

    // Clear the FrameImage list.
    void    ClearTextLayers();

    // Get the text that showing on the frames.
    void    GetImgText( IN CWStrList& strlistText );

    // Create an empty image.
    void    CreateEmptyLayer(
                IN CHBmpArray& arBmpActual, //
                IN CHBmpArray& arBmpVirtual, //
                IN CWStrList& strList //
                );
    
    // Create a FrameImage and push it back to the FrameImageList.
    CTextLayer*    CreateTextLayer();

	// format the text and return the dimensions of text using the current font .
	void 	FormatText( IN const wstring& strOrgText);

    BOOL    IsBreakChar(const wstring& strChar) const;

    // Get a word of current position
    BOOL    GetWord( IN const wstring& strText,
                     IN INT iIndex,
                     OUT wstring& strWord) const;

    //
    //INT     GetWordCurrentLen(const wstring& strWord,INT iIndex) const;

    // the current word need to return to next line?
    BOOL    NeedWordBreak(const wstring& strWord,INT iExtent) const;

    // to fix the size when adjust/estimate/calculate the size of font.
    // Attention: must be modified when you add a new text effect.
    void    AdjustRefSize( IN_OUT SIZE& sizeRef, //
                           IN BOOL bGrow=FALSE //
                        ) const;

private:

    // 
    BOOL  CreateBitmap( OUT CHBmpArray& arBmpActual,OUT CHBmpArray& arrayBmp);

	// IFontBmpGen interface
public:

    BOOL    IsMinFontHeight() const;

    void    SetAdjustStyle(BOOL bFrameSizeFixed,BOOL bFontSizeFixed);
    TAdjustStyle    GetAdjustStyle() const { return (TAdjustStyle)m_iAdjustStyle; }

    // Text
    wstring GetText() const { return m_strText; }
	HRESULT SetText(LPCWSTR lpctText);
	
    // Sign size
    SIZE    GetSignSize() const { return m_sizeSign; }
    HRESULT SetSignSize(SIZE sizeSign );

    // Frame size.
    HRESULT SetFrameSize(int iWidth,int iHeight);
    SIZE   GetFrameSize() const { return m_sizeFrame; }

    // Font height
	void    SetFontPointHeight(int iFointHeight);
	int	    GetFontPointHeight() const;
    int     GetFontLogicHeight(BOOL bIncludeLeading=FALSE) const;
	HRESULT SetFontLogicHeight(INT ilogicHeight);

    // Font Style
	void  SetFontBold(BOOL bFlag);
    BOOL  GetFontBold() const;
	void  SetFontItalic(BOOL bFlag);
    BOOL  GetFontItalic() const;
	void  SetFontUnderLine(BOOL bFlag);
    BOOL  GetFontUnderLine() const;

    // Font[file] name
	HRESULT SetFontName(LPCWSTR lpctFaceName);
    wstring GetFontFaceName() const { return m_textAttri.m_logFont.lfFaceName; }
    wstring GetFontFileName() const;

    // text alignment
	HRESULT SetTextAlign( UINT uAlignment);
    UINT    GetTextAlign() const { return m_textAttri.m_uAlignment; }

    // line alignment
    void    SetLineAlign( UINT uVAlignment);
    UINT    GetLineAlign() const { return m_textAttri.m_uVAlignment; }

    // Text color
    VOID        SetTextColor(const GpClr& clrText);
    COLORREF    GetTextColor() const { return m_textAttri.m_clrText.ToCOLORREF(); }

    // Back color
	VOID     SetBkgColor(const GpClr& clrBkg);
    GpClr    GetBkgColor() const { return m_textAttri.m_clrBkg; }

    // First indent
	void	SetFirstIndent(IN INT iAmount);
	INT 	GetFirstIndent() const { return m_textAttri.m_iFirstIndent; }

    // Kern amount
    void    SetKernAmount(IN INT iAmount) ;
    UINT    GetKernAmount() { return m_textAttri.m_iKernAmount; }

    // Lead amount
    void    SetLeadAmount(IN INT iAmount);
    INT     GetLeadAmount() const { return m_textAttri.m_iLeadAmount; }

    // Grid
    void    SetGridFlag(IN BOOL bFlag) { m_textAttri.m_bShowGrid = bFlag; };
    BOOL    GetGridFlag() const { return m_textAttri.m_bShowGrid; }
    VOID    SetGridColor(const GpClr& clrGrid);
    GpClr   GetGridColor() { return m_textAttri.m_clrGrid; }

    // Transparent
    BOOL    IsTransparent() const { return m_textAttri.IsBkgTspt(); }
    GpClr   GetTsptAgentColor() const { return m_textAttri.GetTsptAgentColor(); }

    // Word break
    void    SetWordBreak(IN BOOL bEnable) { m_bWordBreak=bEnable; }
    BOOL    GetWordBreak() const { return m_bWordBreak; }

    // Create text layer.
	BOOL    GenerateBmp(IN CHBmpArray& arBmpActual,
                        IN CHBmpArray& arrayBmp,    //
                        IN CWStrList& strList  );

// Interface: text effect
public:

    
    // Set/Get effect type
    void        SetEffectType(IN TTextEffect type);
    TTextEffect GetEffectType() const;

    
    // enable shadow effect and set the attribute.
    void     SetShadowColor(IN const GpClr& clr);
    COLORREF GetShadowColor() const;
    void     SetShadowDropdown(IN SIZE size);
    BOOL     GetShadowDropdown(OUT SIZE& size) const;


    // enable outline effect and set its attribute.
    void     SetOutlineColor(IN const GpClr& clr);
    COLORREF GetOutlineColor() const;
    void     SetOutlineWidth(IN WORD wWidth);
    INT      GetOutlineWidth() const;

    

};