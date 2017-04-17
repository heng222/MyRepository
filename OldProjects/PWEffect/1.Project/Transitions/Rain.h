// Rain.h : Declaration of the CRain

#ifndef __RAIN_H_
#define __RAIN_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TMPoint.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CRain ( RainOn Transition )
class CRain : 
	public CDTOTransBase,
	public CComCoClass<CRain, &CLSID_Rain>,
	public IDispatchImpl<IRain, &IID_IRain, &LIBID_ISSPWEffectLib>
{

    typedef CDTOTransBase _basex;
    typedef CRain _thisx;
    typedef IRain _selfI;

public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
    // _selfI Interface
public:
    
    STDMETHOD(get_Color)(/*[out, retval]*/ OLE_COLOR *pVal);
    STDMETHOD(put_Color)(/*[in]*/ OLE_COLOR newVal);
    STDMETHOD(get_Amount)(/*[out, retval]*/ FLOAT *pVal);
    STDMETHOD(put_Amount)(/*[in]*/ FLOAT newVal);
    STDMETHOD(get_Angle)(/*[out, retval]*/ FLOAT *pVal);
	STDMETHOD(put_Angle)(/*[in]*/ FLOAT newVal);
    
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_RAIN)
        
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
    
    COLORREF    GetSkyColor() const;

    INT         GetDripArea() const;
    INT         GetDripHeight() const;

    INT         GetSkyWidth() const;
    INT         GetSkyHeight() const;
    
    
    void        CaclRainEndPos(IN const POINT& ptOrg, 
                        IN  INT iRadius,
                        OUT TMPoint& ptRand) const;

    BOOL        CreateRainPen();
    
    void        DrawDrip(IN HDC hDC,IN POINT pt) const;
    
    HBITMAP     CreateStaticRainImage(HDC hDC,INT nWidth,INT nHeight) const;
    
     
    

    // Properties
private:

    COLORREF    m_clrRain;      // Rain color
    FLOAT       m_fAmount;      // amount [0,1]
    FLOAT       m_fAngle;       // angle with X-coordinates
    
    // Members
private:

    HDC         m_hDCRain;
    HBITMAP     m_hBmpRain;
    HPEN        m_hPenRain;   
        
    DWORD       m_dwMaxTravelLen;
    CTravelRect m_rectTravel;
    BOOL        m_bWraped; // wrap to draw rain?
    BOOL        m_bShowInput2;  // show input2 buffer?
};
    
//////////////////////////////////////////////////////////////////////////
#endif //__PIXELPLAY_H_
