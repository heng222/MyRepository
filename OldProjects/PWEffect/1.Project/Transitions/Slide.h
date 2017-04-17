// Slide.h : Declaration of the CSlide

#ifndef __SLIDE_H_
#define __SLIDE_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CSlide
class ATL_NO_VTABLE CSlide : 
    public CDTOTransBase,
    public CComCoClass<CSlide, &CLSID_Slide>,
	public IDispatchImpl<ISlide, &IID_ISlide, &LIBID_ISSPWEffectLib>
{

public:

    typedef CDTOTransBase _basex;
    typedef CSlide _thisx;
    typedef ISlide _selfI;
    
public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
    // _selfI Interface
public:
    
    STDMETHOD(get_Direction)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Direction)(/*[in]*/ INT newVal);
    STDMETHOD(get_State)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_State)(/*[in]*/ BOOL newVal);
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_SLIDE)
        
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
        
    HRESULT  Initialize(TMRect rectExtent);
    
    HRESULT  ClearTravelRect();    
    
    VOID     GetAngle(FLOAT* pAngle) const;
    
    // Properties
private:
    
    TSingleDir  m_iDirection;
    
    // Control values
private:
    
    CTravelRectArray    m_arSlideRgn;
};

//////////////////////////////////////////////////////////////////////////
#endif //__SLIDE_H_
