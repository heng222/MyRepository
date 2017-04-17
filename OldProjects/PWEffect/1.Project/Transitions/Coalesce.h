// Coalesce.h : Declaration of the CCoalesce

#ifndef __COALESCE_H_
#define __COALESCE_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TMPoint.h"

/////////////////////////////////////////////////////////////////////////////
// Entity grid definition
struct TEntity 
{
    TMRect  m_rExtent;
    BOOL    m_bFlag;

    TEntity()
    {
        m_bFlag = FALSE;
    }
};
typedef std::vector<TEntity*>   CEntityArray;

// CCoalesce class 
class ATL_NO_VTABLE CCoalesce : 
    public CDTOTransBase,
	public CComCoClass<CCoalesce, &CLSID_Coalesce>,
	public IDispatchImpl<ICoalesce, &IID_ICoalesce, &LIBID_ISSPWEffectLib>
{

public:
    
    typedef CDTOTransBase _basex;
    typedef CCoalesce _thisx;
    typedef ICoalesce _selfI;
    
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
    STDMETHOD(get_EntityWidth)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_EntityWidth)(/*[in]*/ INT newVal);
    STDMETHOD(get_EntityHeight)(/*[out, retval]*/ INT *pVal);
	STDMETHOD(put_EntityHeight)(/*[in]*/ INT newVal);
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_COALESCE)
        
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
    
    HRESULT  Initialize();
    VOID     ResetEntity();
    HRESULT  ClearEntity();
    
    // Properties
private:

    TMSize      m_sizeEntity;
    
    // Control values
private:
    
    INT     m_iHLines;  // The number of horizontal line.
    INT     m_iVLines;  // The number of vertical line
    CEntityArray    m_Entity;

    INT     m_iCurrentNum;  // The current number of entities to show in per row.
    
};

#endif //__COALESCE_H_
