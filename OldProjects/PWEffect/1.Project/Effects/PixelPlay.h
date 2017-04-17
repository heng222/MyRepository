// PixelPlay.h : Declaration of the CPixelPlay

#ifndef __PIXELPLAY_H_
#define __PIXELPLAY_H_

#include "resource.h"       // main symbols
#include "DTOEffectBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPixelPlay
class CPixelPlay : 
	public CDTOEffectBase,
	public CComCoClass<CPixelPlay, &CLSID_PixelPlay>,
	public IDispatchImpl<IPixelPlay, &IID_IPixelPlay, &LIBID_ISSPWEffectLib>
{
    typedef CDTOEffectBase _basex;
    typedef CPixelPlay _thisx;
    typedef IPixelPlay _selfI;
    
public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
     // _selfI Interface
public:
	
	STDMETHOD(get_R2ARatio)(/*[out, retval]*/ INT *pVal);
	STDMETHOD(put_R2ARatio)(/*[in]*/ INT newVal);
	STDMETHOD(get_A2VRatio)(/*[out, retval]*/ INT *pVal);
	STDMETHOD(put_A2VRatio)(/*[in]*/ INT newVal);
    
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_PIXELPLAY)
        
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
    
    
    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,
        IN DWORD* pOutputBuf,
        IN INT iWidth,
        IN INT iHeight);
    
    // Private utilities methods
private:
    
	FLOAT	 GetTransRatio() const;
	HRESULT  Pixelate(DWORD* pInput,DWORD* pOutput);
    DXSAMPLE CalcAvgColor(DXSAMPLE* pIn,INT iWidth,INT iHeight) const;
    void     SetColor(DXSAMPLE* pIn,INT iWidth,INT iHeight,DXSAMPLE clrNew) const;
    
    // Private members
private:
    
	INT		m_iR2ARatio;
	INT		m_iA2VRatio;
	
};

//////////////////////////////////////////////////////////////////////////
#endif //__PIXELPLAY_H_
