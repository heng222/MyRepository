// Interleave.h : Declaration of the CInterleave

#ifndef __INTERLEAVE_H_
#define __INTERLEAVE_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CInterleave
class ATL_NO_VTABLE CInterleave : 
	public CDTOTransBase,
	public CComCoClass<CInterleave, &CLSID_Interleave>,
	public IDispatchImpl<IInterleave, &IID_IInterleave, &LIBID_ISSPWEffectLib>
{

    typedef CDTOTransBase _basex;
    typedef CInterleave _thisx;
    typedef IInterleave _selfI;

public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
    // _selfI Interface
public:

    STDMETHOD(get_Thickness)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Thickness)(/*[in]*/ INT newVal);
    STDMETHOD(get_Lines)(/*[out, retval]*/ BOOL *pVal);
    STDMETHOD(put_Lines)(/*[in]*/ BOOL newVal);
    STDMETHOD(get_State)(/*[out, retval]*/ BOOL *pVal);
    STDMETHOD(put_State)(/*[in]*/ BOOL newVal);   
    STDMETHOD(get_Direction)(/*[out, retval]*/ INT *pVal);
	STDMETHOD(put_Direction)(/*[in]*/ INT newVal);
    
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_INTERLEAVE)
    
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

    FLOAT    GetAngle(BOOL bFlag) const;
    
    HRESULT  Initialize();

    HRESULT  GenerateSlot(TMRect rectExtent,CTravelRectArray& arTR) const;

    HRESULT  ClearTravelRect();
    
    // Properties
private:
    
    TILDir  m_iDirection;   // direction to move
    BOOL    m_bVertical;    // TRUE=vertical lines; FALSE=horizontal lines
    INT     m_iThickness;   // lines thickness

    // Control values
private:
	
    CTravelRectArray    m_arTravelRect;

};

//////////////////////////////////////////////////////////////////////////
#endif //__INTERLEAVE_H_
