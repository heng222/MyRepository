// Filter.h : Declaration of the CFilter

#ifndef __FILTER_H_Declaration
#define __FILTER_H_Declaration

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TMPoint.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CFilter
class ATL_NO_VTABLE CFilter : 
	public CDTOTransBase,
	public CComCoClass<CFilter, &CLSID_Filter>,
	public IDispatchImpl<IFilter, &IID_IFilter, &LIBID_ISSPWEffectLib>
{

    typedef CDTOTransBase _basex;
    typedef CFilter _thisx;
    typedef IFilter _selfI;

public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
    // _selfI Interface
public:

    STDMETHOD(get_Spacing)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Spacing)(/*[in]*/ INT newVal);
    STDMETHOD(get_Thickness)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Thickness)(/*[in]*/ INT newVal);
    STDMETHOD(get_State)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_State)(/*[in]*/ BOOL newVal);

    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_FILTER)
    
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

    HRESULT  InitFilter();
        
    // Properties
private:

    INT     m_iThickness;     // Thickness
    INT     m_iSpacing;    // Spacing 
    
    // Control values
private:
    
    CTravelRectArray    m_Sticks;
};

//////////////////////////////////////////////////////////////////////////
#endif //__FILTER_H_
