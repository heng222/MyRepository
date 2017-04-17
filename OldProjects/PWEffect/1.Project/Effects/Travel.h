// Travel.h : Declaration of the CTravel

#ifndef __TRAVEL_H_
#define __TRAVEL_H_

#include "resource.h"       // main symbols
#include "DTOEffectBase.h"
#include "TMPoint.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CTravel
class CTravel : 
	public CDTOEffectBase,
	public CComCoClass<CTravel, &CLSID_Travel>,
	public IDispatchImpl<ITravel, &IID_ITravel, &LIBID_ISSPWEffectLib>
{
    typedef CDTOEffectBase _basex;
    typedef CTravel _thisx;
    typedef ITravel _selfI;

public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
    // _selfI Interface
public:
    
    STDMETHOD(get_Angle)(/*[out, retval]*/ FLOAT *pVal);
    STDMETHOD(put_Angle)(/*[in]*/ FLOAT newVal);
    STDMETHOD(get_Rate)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Rate)(/*[in]*/ INT newVal);
	STDMETHOD(get_Circular)(/*[out, retval]*/ BOOL *pVal);
    STDMETHOD(put_Circular)(/*[in]*/ BOOL newVal);
    STDMETHOD(get_Spacing)(/*[out, retval]*/ INT *pVal);
	STDMETHOD(put_Spacing)(/*[in]*/ INT newVal);
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_TRAVEL)
        
    DECLARE_POLY_AGGREGATABLE(_thisx)
    
    //Implement IDXEffect properties: Progress, Duration, etc..
    //DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)
    
    // From IPWEffect
    DECLARE_IPWEFFECT_METHODS(_basex)
        
        
    // From _basex
public:

    virtual HRESULT FinalConstruct();
    virtual HRESULT OnStart();
    virtual HRESULT OnInitialize();
    virtual HRESULT OnTerminate();
    
    
    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,
        IN DWORD* pOutputBuf,
        IN INT iWidth,
        IN INT iHeight);
    
    // Private utilities methods
private:

    BOOL    Initialize();
    

    BOOL    UpdateControlValue();

    void    DrawLiveImage(HDC hdcSource,HDC hdcDest);
    
    // Properties
private:
    
    INT     m_iRate;    // 
    FLOAT   m_fAngle;   // 与正X轴的顺时针夹角 (radian)
    BOOL    m_bCircular;    // Enable Circular?
    INT     m_iSpacing; // Spacing. Only valid when m_bCircular is set to TRUE.(like WrapAround)

    // Members
private:

    // DC and bitmap for drawing live image.
    HDC        m_hdcCanvas;
    HBITMAP    m_hbmpCanvas;
    HBRUSH     m_hBrush;

    CTravelRect m_TravelRectOn;
    CTravelRect m_TravelRectOff;
    LONG        m_lMaxLen;
};

//////////////////////////////////////////////////////////////////////////
#endif //__TRAVEL_H_
