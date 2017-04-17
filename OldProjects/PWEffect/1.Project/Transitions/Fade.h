// Fade.h : Declaration of the CFade

#ifndef __FADE_H_
#define __FADE_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"

/////////////////////////////////////////////////////////////////////////////
// CFade
class ATL_NO_VTABLE CFade : 
    public CDTOTransBase,
	public CComCoClass<CFade, &CLSID_Fade>,
	public IDispatchImpl<IFade, &IID_IFade, &LIBID_ISSPWEffectLib>
{
    typedef CDTOTransBase _basex;
    typedef CFade _thisx;
    typedef IFade _selfI;
    
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
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_FADE)
        
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
    
    
    virtual HRESULT OnTransform(IN DWORD* pInputBuf,
        IN DWORD* pInput2Buf,
        IN DWORD* pOutputBuf);
//     virtual HRESULT DrawLiveBitmap(IN HDC hdcHide,
//         IN HDC hdcShow,
//         IN HDC hdcOutput);
    
    // Private utilities methods
private:    
    
    HRESULT  Initialize();    
    HRESULT  AdjustPixel(DWORD* pdwOutput, 
                const DWORD* pBufHide,
                const DWORD* pBufShow,
                FLOAT fRatio) const;
    
    
    // Properties
private:

    COLORREF     m_clrOriginal; // Original color for start.
    
    
    // Control values
private:    
    

};
//////////////////////////////////////////////////////////////////////////
#endif //__FADE_H_
