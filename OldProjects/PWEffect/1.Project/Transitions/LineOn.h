// LineOn.h : Declaration of the CLineOn

#ifndef __LINEON_H_
#define __LINEON_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CLineOn/off
class ATL_NO_VTABLE CLineOn : 
	public CDTOTransBase,
	public CComCoClass<CLineOn, &CLSID_LineOn>,
	public IDispatchImpl<ILineOn, &IID_ILineOn, &LIBID_ISSPWEffectLib>
{
    typedef CDTOTransBase _basex;
    typedef CLineOn _thisx;
    typedef ILineOn _selfI;
    
public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
    // _selfI Interface
public:
    
    STDMETHOD(get_LineWidth)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_LineWidth)(/*[in]*/ INT newVal);
    STDMETHOD(get_LagSpacing)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_LagSpacing)(/*[in]*/ INT newVal);
    STDMETHOD(get_Direction)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Direction)(/*[in]*/ INT newVal);
    STDMETHOD(get_State)(/*[out, retval]*/ BOOL *pVal);
    STDMETHOD(put_State)(/*[in]*/ BOOL newVal);
    STDMETHOD(get_PullPoint)(/*[out, retval]*/ INT *pVal);
	STDMETHOD(put_PullPoint)(/*[in]*/ INT newVal);
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_LINEON)
        
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
    
    FLOAT    GetAngle() const;
    
    HRESULT  Initialize(TMRect rectExtent);
    
    HRESULT  ClearTravelRect();



    // Properties
private:
    
    TSingleDir  m_iDirection;
    INT         m_iPullPoint;
    INT         m_iLagSpacing;
    INT         m_iLineWidth;
    
    // Control values
private:
    
    INT                 m_iMaxTravelLen;
    CTravelRectArray    m_arLinePart1;
    CTravelRectArray    m_arLinePart2;
};

//////////////////////////////////////////////////////////////////////////
#endif //__LINEON_H_
