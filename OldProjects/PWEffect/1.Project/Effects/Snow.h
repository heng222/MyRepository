// Snow.h : Declaration of the CSnow

#ifndef __SNOW_H_
#define __SNOW_H_

#include "resource.h"       // main symbols
#include "DTOEffectBase.h"
#include "TMPoint.h"

/////////////////////////////////////////////////////////////////////////////
// CSnow
class CSnow : 
	public CDTOEffectBase,
	public CComCoClass<CSnow, &CLSID_Snow>,
	public IDispatchImpl<ISnow, &IID_ISnow, &LIBID_ISSPWEffectLib>
{

    typedef CDTOEffectBase _basex;
    typedef CSnow _thisx;
    typedef ISnow _selfI;

public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
    // _selfI Interface
public:

    STDMETHOD(get_Amount)(/*[out, retval]*/ FLOAT *pVal);
    STDMETHOD(put_Amount)(/*[in]*/ FLOAT newVal);
    STDMETHOD(get_Rate)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Rate)(/*[in]*/ INT newVal);
    STDMETHOD(get_Color)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_Color)(/*[in]*/ OLE_COLOR newVal);
    
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_SNOW)
        
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
    virtual HRESULT OnTerminate();
    
    
    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,
        IN DWORD* pOutputBuf,
        IN INT iWidth,
        IN INT iHeight);
    
    // Private utilities methods
private:
    
    COLORREF    GetSkyColor() const;

    INT         GetSkyWidth() const;
    INT         GetSkyHeight() const;

    INT         GetFlakeArea() const;
    INT         GetFlakeWidth() const;



    void        RandPosition(IN const POINT& ptOrg, 
                        IN  INT iRadius,
                        OUT TMPoint& ptRand) const;
    BOOL        CreateSnowPen();

    void        DrawSnow(IN HDC hDC,IN POINT pt) const;

    HBITMAP     CreateSnowImg(HDC hDC,INT nWidth,INT nHeight) const;
    
    void        ImplementSnowing(IN HDC hInputDC);

    void        UpdateSeparatorPos();
    
    // Properties
private:

    COLORREF    m_clrSnow;
    INT         m_iRate;
    FLOAT       m_fAmount;

    // Members
private:
    
    HDC         m_hDCSnow;
    HBITMAP     m_hBmpSnow;
    HPEN        m_hPenSnow;
    
    BOOL        m_bRounding; // has already returned?
    POINT       m_ptSeparator;
    
};

//////////////////////////////////////////////////////////////////////////
#endif //__SNOW_H_
