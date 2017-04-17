// MultiWipe.h : Declaration of the CMultiWipe

#ifndef __MULTIWIPE_H_
#define __MULTIWIPE_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiWipe
class ATL_NO_VTABLE CMultiWipe : 
    public CDTOTransBase,
    public CComCoClass<CMultiWipe, &CLSID_MultiWipe>,
	public IDispatchImpl<IMultiWipe, &IID_IMultiWipe, &LIBID_ISSPWEffectLib>
{
public:
    
    typedef CDTOTransBase _basex;
    typedef CMultiWipe _thisx;
    typedef IMultiWipe _selfI;
    
public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
        // _selfI Interface
public:
    
    STDMETHOD(get_State)(/*[out, retval]*/ BOOL *pVal);
    STDMETHOD(put_State)(/*[in]*/ BOOL newVal);
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_MULTIWIPE)
        
    DECLARE_POLY_AGGREGATABLE(_thisx)
    
    //Implement IDXEffect properties: Progress, Duration, etc..
    //DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)
    
    // From IPWEffect
    DECLARE_IPWEFFECT_METHODS(_basex)
        
        
        // From _basex
public:
	STDMETHOD(get_VWNum)(/*[out, retval]*/ INT *pVal);
	STDMETHOD(put_VWNum)(/*[in]*/ INT newVal);
	STDMETHOD(get_HWNum)(/*[out, retval]*/ INT *pVal);
	STDMETHOD(put_HWNum)(/*[in]*/ INT newVal);
    
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
    
    
    // Properties
private:

    INT     m_iHWNum;
    INT     m_iVWNum;
    
    // Control values
private:
    
    INT     m_iGridWidth;
    INT     m_iGridHeight;
    CMRectVector    m_arMultiWipe;
};

#endif //__MULTIWIPE_H_
