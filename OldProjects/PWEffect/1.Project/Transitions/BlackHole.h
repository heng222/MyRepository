// BlackHole.h : Declaration of the CBlackHole

#ifndef __BLACKHOLE_H_
#define __BLACKHOLE_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TMPoint.h"

/////////////////////////////////////////////////////////////////////////////
// CBlackHole
class CBlackHole : 
	public CDTOTransBase,
	public CComCoClass<CBlackHole, &CLSID_BlackHole>,
	public IDispatchImpl<IBlackHole, &IID_IBlackHole, &LIBID_ISSPWEffectLib>
{

    typedef CDTOTransBase _basex;
    typedef CBlackHole _thisx;
    typedef IBlackHole _selfI;

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
    STDMETHOD(get_StartY)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_StartY)(/*[in]*/ INT newVal);
    STDMETHOD(get_StartX)(/*[out, retval]*/ INT *pVal);
	STDMETHOD(put_StartX)(/*[in]*/ INT newVal);
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_BLACKHOLE)
    
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

    POINT   m_ptStart; // start position

    // Control values
private:
	
    TSegmentVector  m_vMove;     // 起始点与中心角形成的有向线段
    TMRect          m_rLiveRect; // live rectangle.
};

//////////////////////////////////////////////////////////////////////////
#endif //__BLACKHOLE_H_
