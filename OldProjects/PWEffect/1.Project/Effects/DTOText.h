 // DTOText.h : Declaration of the CDTOText

#ifndef __DTOTEXT_H_
#define __DTOTEXT_H_

#include "DTOEffectBase.h"

//////////////////////////////////////////////////////////////////////////

// CDTOText
class  CDTOText : 
	public CDTOEffectBase,
	public CComCoClass<CDTOText, &CLSID_DTOText>,
	public IDispatchImpl<ITextEffect, &IID_ITextEffect, &LIBID_ISSPWEffectLib>
{

    typedef CDTOEffectBase  _basex;
    typedef CDTOText _thisx;
    typedef ITextEffect _selfI;

public: 
	
	// COM MAP
	BEGIN_COM_MAP(_thisx)
		COM_INTERFACE_ENTRY(_selfI)
		COM_INTERFACE_ENTRY2(IDispatch,_selfI)
		COM_INTERFACE_ENTRY_CHAIN( _basex )
	END_COM_MAP()
    
    // _selfI interface
public:
    
    STDMETHOD(get_TextColor)(OLE_COLOR *pVal);
    STDMETHOD(put_TextColor)(OLE_COLOR newVal);
    
    STDMETHOD(get_TitleType)(INT *pVal);
    STDMETHOD(put_TitleType)(INT newVal);
    
    STDMETHOD(get_Title)(BSTR* strTitle);
    STDMETHOD(put_Title)(BSTR pStrTitle);
    
    
    STDMETHOD(get_FontName)(BSTR *pVal);
    STDMETHOD(put_FontName)(BSTR newVal);
    STDMETHOD(get_FontHeight)(WORD *pVal);
	STDMETHOD(put_FontHeight)(WORD newVal);


public:
	
	// Implement registration for DX Transform
	DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_DTOTEXT)
		
	DECLARE_POLY_AGGREGATABLE(_thisx)

	// Implement IDXEffect properties: Progress, Duration, etc..
	//DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)

	// Implement IPWEffect properties: Blue, Red, Green, etc..
	DECLARE_IPWEFFECT_METHODS(_basex)
    
    
    // From CDTOEffectBase
public:
    
    virtual HRESULT FinalConstruct();
    
    virtual HRESULT OnInitialize();
    virtual HRESULT OnStart();

    virtual HRESULT OnTerminate();
    
    
    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,
                                 IN DWORD* pOutputBuf,
                                 IN INT iWidth,
                                 IN INT iHeight);
    
    // Private methods
private:
    
    HRESULT	 InitializeDC();
    HRESULT	 InitLogFont();
    HRESULT  CreateFontAndSelect();
    HRESULT  CalculateTitleSize();
    HRESULT  InitBounceParameter();
    HRESULT	 CalculateScrollStride(void);
    HRESULT  DrawTitle(IN HDC hDC);

    void	CalcStartPos();
    
    void	SetFontPointHeight(IN WORD wHeight);
    int	    GetFontPointHeight() const;
    
    void    SetFontLogicHeight(WORD wlogicHeight);
    int     GetFontLogicHeight(BOOL bIncludeLeading=FALSE) const;


    // Attributes
private:
    
    TTextType	m_iEType;
    CComBSTR	m_strTitle;
    COLORREF	m_clrText;
    LOGFONT		m_logFont;
    
    // Control data
private:
    
    HDC     m_hdcText;
    HFONT	m_hFont;
    POINT	m_ptStart;	       // Title的输出坐标
    SIZE	m_sizeTitle;
    
    INT     m_iScrollStride;   // Step
    INT     m_iBottomBorder;   // 下落边界
    INT     m_iBounceHeight;   // 弹起高度
    float   m_fBounceIndex;    // 弹跳系数
    BOOL    m_bBounceState;    // 弹跳状态(TRUE: 弹起，FALSE:下落)
};

//////////////////////////////////////////////////////////////////////////
#endif //__DTOTEXT_H_
