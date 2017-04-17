// PushOn.h : Declaration of the CPushOn

#ifndef __PUSHON_H_
#define __PUSHON_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CPushOn
class ATL_NO_VTABLE CPushOn : 
    public CDTOTransBase,
    public CComCoClass<CPushOn, &CLSID_PushOn>,
	public IDispatchImpl<IPushOn, &IID_IPushOn, &LIBID_ISSPWEffectLib>
{

public:
    
    typedef CDTOTransBase _basex;
    typedef CPushOn _thisx;
    typedef IPushOn _selfI;
    
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
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_PUSHON)

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

    HBRUSH  m_hBrush;
    
    CTravelRectArray    m_arShowRgn;
    CTravelRectArray    m_arHideRgn;
};

#endif //__PUSHON_H_
