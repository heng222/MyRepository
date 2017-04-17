// SimpleTrans.h : Declaration of the CSimpleTrans

#ifndef __SIMPLETRANS_H_
#define __SIMPLETRANS_H_

#include "resource.h"       // main symbols

#include "DTOTransBase.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpleTrans class
// 
class CSimpleTrans : 
	public CDTOTransBase,
	public CComCoClass<CSimpleTrans, &CLSID_SimpleTrans>,
	public IDispatchImpl<ISimpleTrans, &IID_ISimpleTrans, &LIBID_ISSPWEffectLib>

{
        typedef  CDTOTransBase  _basex;
        typedef  CSimpleTrans   _thisx;
        typedef  ISimpleTrans   _selfI;

public: 
	
    // ATL Setup
    BEGIN_COM_MAP(CSimpleTrans)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
    
    
    // _selfI Interface
public:
    
    
public:
    
    // Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_SIMPLETRANS)
    
    DECLARE_POLY_AGGREGATABLE(_thisx)
    
    // Implement IDXEffect properties: Progress, Duration, etc..
    //DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)
    
    // Implement IPWEffect properties: Blue, Red, Green, etc..
    DECLARE_IPWEFFECT_METHODS(_basex)
    
    
    // From _basex
public:
    
    virtual HRESULT FinalConstruct();
    virtual HRESULT OnInitialize();
    virtual HRESULT OnTerminate();
    
    virtual HRESULT OnTransform(IN DWORD* pInputBuf,
        IN DWORD* pInput2Buf,
        IN DWORD* pOutputBuf);
    
    
    
    
    // Private methods
private:
    
    
    // Attributes
private:
    
    // members
private:
   

};



//////////////////////////////////////////////////////////////////////////
#endif //__SIMPLETRANS_H_
