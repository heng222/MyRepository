// Bounce.h : Declaration of the CBounce

#ifndef __BOUNCE_H_
#define __BOUNCE_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"

/////////////////////////////////////////////////////////////////////////////
// CBounce
class CBounce : 
	public CDTOTransBase,
	public CComCoClass<CBounce, &CLSID_Bounce>,
	public IDispatchImpl<IBounce, &IID_IBounce, &LIBID_ISSPWEffectLib>
{
    typedef CDTOTransBase _basex;
    typedef CBounce _thisx;
    typedef IBounce _selfI;
    
public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
        // _selfI Interface
public:
    
    
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_BOUNCE)
        
    DECLARE_POLY_AGGREGATABLE(_thisx)
    
    //Implement IDXEffect properties: Progress, Duration, etc..
    //DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)
    
    // From IPWEffect
    DECLARE_IPWEFFECT_METHODS(_basex)
    
        
        // From _basex
public:
    
    virtual HRESULT FinalConstruct();
    
    virtual HRESULT OnInitialize();

    virtual HRESULT OnTerminate();

    virtual HRESULT ResetControlValue();
    virtual HRESULT UpdateControlValue();

    virtual HRESULT DrawLiveBitmap(IN HDC hdcHide,
        IN HDC hdcShow,
        IN HDC hdcOutput);

    
    // Private utilities methods
private:

    
    
    
    // Properties
private:
    

    // Control value
private:
        
    POINT	m_ptRef;	       // a reference point
    WORD    m_wMaxLength;
    INT     m_iLastLen;
    
};
    
//////////////////////////////////////////////////////////////////////////
#endif //__PIXELPLAY_H_
