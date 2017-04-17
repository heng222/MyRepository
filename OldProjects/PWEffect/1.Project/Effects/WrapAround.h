// WrapAround.h : Declaration of the CWrapAround

#ifndef __WRAPAROUND_H_
#define __WRAPAROUND_H_

#include "resource.h"       // main symbols
#include "DTOEffectBase.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CWrapAround
class ATL_NO_VTABLE CWrapAround : 
	public CDTOEffectBase,
	public CComCoClass<CWrapAround, &CLSID_WrapAround>,
	public IDispatchImpl<IWrapAround, &IID_IWrapAround, &LIBID_ISSPWEffectLib>
{

    typedef CDTOEffectBase _basex;
    typedef CWrapAround _thisx;
    typedef IWrapAround _selfI;

public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
        // _selfI Interface
public:

    STDMETHOD(get_Rate)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Rate)(/*[in]*/ INT newVal);
    STDMETHOD(get_Direction)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Direction)(/*[in]*/ INT newVal);
    STDMETHOD(get_Spacing)(/*[out, retval]*/ INT *pVal);
	STDMETHOD(put_Spacing)(/*[in]*/ INT newVal);
    
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_WRAPAROUND)
    
    DECLARE_POLY_AGGREGATABLE(_thisx)
    
    //Implement IDXEffect properties: Progress, Duration, etc..
    //DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)
    
    // From IPWEffect
    DECLARE_IPWEFFECT_METHODS(_basex)
    
    // From _basex
public:
    
    virtual HRESULT FinalConstruct();
    
    virtual HRESULT OnInitialize();
    
    virtual HRESULT OnStart();
    
    // On duration changed.
    virtual HRESULT OnDurationChanged(FLOAT fNewDur);
    
    virtual HRESULT OnTerminate();
    
    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,
        IN DWORD* pOutputBuf,
        IN INT iWidth,
        IN INT iHeight);
    
    // Private utilities methods
private:
    
    HRESULT  ResetControlValue();
    
    HRESULT  UpdateControlValue();
    
    HRESULT  DrawLiveBitmap(HDC hdcSrc,HDC hdcDest);
    
    // Properties
private:

    TSingleDir m_iDirection;  // movement direction
    INT        m_iRate;       // Movement rate.
    INT        m_iSpacing;    // Spacing


    // Control values
private:

    HDC     m_hdcLive;
    HBITMAP m_hbmpLive;
    HBRUSH  m_hBrush;
	
    DWORD       m_dwMaxTravelLen;
    CTravelRect m_rectTravel;
};

#endif //__WRAPAROUND_H_
