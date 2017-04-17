// Flash.h : Declaration of the CFlash

#ifndef __FLASH_H_
#define __FLASH_H_

#include "resource.h"       // main symbols
#include "DTOEffectBase.h"

/////////////////////////////////////////////////////////////////////////////
// CFlash
class CFlash : 
	public CDTOEffectBase,
	public CComCoClass<CFlash, &CLSID_Flash>,
	public IDispatchImpl<IFlash, &IID_IFlash, &LIBID_ISSPWEffectLib>
{
    
    typedef CDTOEffectBase _basex;
    typedef CFlash _thisx;
    typedef IFlash _selfI;
    
public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
    // _selfI Interface
public:
    
    STDMETHOD(get_OffTime)(/*[out, retval]*/ DWORD *pVal);
    STDMETHOD(put_OffTime)(/*[in]*/ DWORD newVal);
    STDMETHOD(get_OnTime)(/*[out, retval]*/ DWORD *pVal);
    STDMETHOD(put_OnTime)(/*[in]*/ DWORD newVal);
    STDMETHOD(get_FlashStyle)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_FlashStyle)(/*[in]*/ INT newVal);
    STDMETHOD(get_TextColor)(/*[out, retval]*/ OLE_COLOR *pVal);
    STDMETHOD(put_TextColor)(/*[in]*/ OLE_COLOR newVal);
    STDMETHOD(get_WED)(/*[out, retval]*/ FLOAT *pVal);
	STDMETHOD(put_WED)(/*[in]*/ FLOAT newVal);
    
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_FLASH)
        
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
    virtual HRESULT OnDurationChanged(FLOAT fNewDur);
    virtual HRESULT OnTerminate();
    
    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,
        IN DWORD* pOutputBuf,
        IN INT iWidth,
        IN INT iHeight);

protected:

    void    OnFlashStateChanged();
    
    // Private utilities methods
private:

    // Get the flash-on color according to the specified pixel.
    void    Conver2FlashOn(IN const DXSAMPLE* pClrOrg,
                OUT DXSAMPLE* pClrDest) const;

    // Get the flash-off color according to the specified pixel.
    void    Convert2FlashOff(IN const DXSAMPLE* pClrOrg,
                OUT DXSAMPLE* pClrDest) const;

    // Determine should be flash on or flash off.
    BOOL        IsFlashOn(float fProgress) const;
    
    // Convert the source value to flash on/off color.
    void        ConvertData(const DXSAMPLE* pInput,
                   DXSAMPLE* pOutput,
                   INT iWidth, INT iHeight, 
                   BOOL bOnTime) const;
    
    // Properties
private:

    COLORREF    m_clrText;
    DWORD       m_dwOnTime;     // millisecond unit.
    DWORD       m_dwOffTime;    // millisecond
    TFlashStyle m_iFashStyle;   // blank, invert or random.
    FLOAT       m_fWEDistance;  // Threshold in tolerance
    
    // Members
private:

    DWORD    m_dwPeriod; // millisecond

    BOOL     m_bFlashFlag; // just a flag

    DXSAMPLE m_clrTextRdm; // a random text color(only valid when FlashStyle==ERandom)
    DXSAMPLE m_clrOtherRdm; // A random text color for elements 
                            // except background color and text color.
};

//////////////////////////////////////////////////////////////////////////
#endif //__FLASH_H_
