

#ifndef _CDTOCOLORADJUSTEFFECT_H_43OJI
#define _CDTOCOLORADJUSTEFFECT_H_43OJI

#include "DTOEffectBase.h"

//
typedef enum _tagAdjustType
{
    ENoChange,		// No change
    EGray,			// Gray
    ERed,			// Red
    EGreen,         // Green
    EBlue,          // Blue
    EWhite,         // white
    EAmber,			// Amber
    EBlueGreen,     // BLUE - GREEN
    ERedGreen,      // RED - GREEN
}TAdjustType;

/*****************************************************************************
 * class CDTOClrAdjust -		class for DTX wrapper object
 * {94CB0B89-3EC4-465f-83DD-BE327C134BE5}
 *****************************************************************************/
class CDTOClrAdjust : 
	public CDTOEffectBase,
	public CComCoClass<CDTOClrAdjust, &CLSID_ClrAdjustEffect>,
	public IDispatchImpl<IColorAdjust, &IID_IColorAdjust, &LIBID_ISSPWEffectLib>

{ 
	typedef CDTOEffectBase _basex;
    typedef CDTOClrAdjust _thisx;
    typedef IColorAdjust _selfI;

public:
	 
	// ATL Setup
	BEGIN_COM_MAP(_thisx)
		COM_INTERFACE_ENTRY(_selfI)
 		COM_INTERFACE_ENTRY2(IDispatch,_selfI)
		COM_INTERFACE_ENTRY_CHAIN( _basex )
	END_COM_MAP()

	// _selfI Interface
public:
	
	STDMETHOD(get_AdjustType)(BSTR* strType);
    STDMETHOD(put_AdjustType)(BSTR pStrType);
    STDMETHOD(get_SunglassColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_SunglassColor)(/*[in]*/ OLE_COLOR newVal);

public: 

	//Implement registration for DX Transform
	DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_COLORADJUST)

	DECLARE_POLY_AGGREGATABLE(_thisx)
	
	//Implement IDXEffect properties: Progress, Duration, etc..
	//DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)

	// From IPWEffect
	DECLARE_IPWEFFECT_METHODS(_basex)
    
    
    // From CDTOEffectBase
public:
    
    virtual HRESULT FinalConstruct();
    
    virtual HRESULT OnInitialize();
    virtual HRESULT OnTerminate();
  
    
    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,
                                 IN DWORD* pOutputBuf,
                                 IN INT iWidth,
                                 IN INT iHeight);

    // Private utilities methods
private:
    
	HRESULT AdjustPixel(DWORD* pdwOutputPixel, const DWORD* pdwPixel);

    // Properties
private:
    
	TAdjustType m_iAdjustType;
    COLORREF    m_clrSunglass;
};

//////////////////////////////////////////////////////////////////////////
#endif