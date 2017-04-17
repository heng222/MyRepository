// Radar.h : Declaration of the CRadar

#ifndef __RADAR_H_
#define __RADAR_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TMPoint.h"

/////////////////////////////////////////////////////////////////////////////
// CRadar
class ATL_NO_VTABLE CRadar : 
    public CDTOTransBase,
	public CComCoClass<CRadar, &CLSID_Radar>,
	public IDispatchImpl<IRadar, &IID_IRadar, &LIBID_ISSPWEffectLib>
{

public:
    
    typedef CDTOTransBase _basex;
    typedef CRadar _thisx;
    typedef IRadar _selfI;
    
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
    STDMETHOD(get_Direction)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Direction)(/*[in]*/ INT newVal);
    STDMETHOD(get_PointerWidth)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_PointerWidth)(/*[in]*/ INT newVal);
    STDMETHOD(get_PointerColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_PointerColor)(/*[in]*/ OLE_COLOR newVal);
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_RADAR)
    
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
    
    // Properties
private:
    
    TRoundDir  m_iDirection;
    COLORREF   m_clrPointer;
    INT        m_iPointerWidth;
    
    // Control values
private:

    TSegmentVector  m_sgPtOriginal; // 雷达针的初始位置
    TSegmentVector  m_sgPointer;    // 雷达针
    
    HPEN            m_hPen;
    
    CMPointVector   m_arVertexes;      // Rgn的各顶点

    CMSegmentArray  m_arEdges;      // 可能相交的边

    HRGN            m_hrgnArea;     // the area to show

    TMPoint         m_ptCross;
};

#endif //__RADAR_H_
