// Wipe.h : Declaration of the CWipe

#ifndef __WIPE_H_
#define __WIPE_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CWipe
class ATL_NO_VTABLE CWipe : 
    public CDTOTransBase,
    public CComCoClass<CWipe, &CLSID_Wipe>,
	public IDispatchImpl<IWipe, &IID_IWipe, &LIBID_ISSPWEffectLib>
{

public:
    
    typedef CDTOTransBase _basex;
    typedef CWipe _thisx;
    typedef IWipe _selfI;
    
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
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_WIPE)
        
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
    
    VOID     GetAngle(FLOAT* pAngle) const;
    
    HRESULT  Initialize(TMRect rectExtent);
    
    HRESULT  ClearTravelRect();
    
    
    
    // Properties
private:
    
    TSingleDir  m_iDirection;
    
    // Control values
private:
    
    CTravelRectArray    m_arWipeRgn;
};

#endif //__WIPE_H_
