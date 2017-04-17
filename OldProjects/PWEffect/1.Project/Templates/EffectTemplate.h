// PixelPlay.h : Declaration of the CNewEffect

#ifndef __PIXELPLAY_H_
#define __PIXELPLAY_H_

#include "resource.h"       // main symbols
#include "DTOEffectBase.h"

/////////////////////////////////////////////////////////////////////////////
// CNewEffect
class CNewEffect : 
	public CDTOEffectBase,
	public CComCoClass<CNewEffect, &CLSID_PixelPlay>,
	public IDispatchImpl<INewInterface, &IID_INewInterface, &LIBID_ISSPWEffectLib>
{
    typedef CDTOEffectBase _basex;
    typedef CNewEffect _thisx;
    typedef INewInterface _selfI;
    
public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
     // _selfI Interface
public:

    
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_NEWEFFECT)
        
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

    // On duration changed.
    virtual HRESULT OnDurationChanged(FLOAT fNewDur);

    virtual HRESULT OnTerminate();
    
    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,
        IN DWORD* pOutputBuf,
        IN INT iWidth,
        IN INT iHeight);
    
    // Private utilities methods
private:
    
    HRESULT  ResetControlValue();
    
    HRESULT  UpdateControlValue();
    
    
    // Properties
private:
    
    // Control values
private:
	
};

//////////////////////////////////////////////////////////////////////////
#endif //__PIXELPLAY_H_
