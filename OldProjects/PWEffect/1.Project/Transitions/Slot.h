// Slot.h : Declaration of the CSlot

#ifndef __SLOT_H_
#define __SLOT_H_

#include "resource.h"       // main symbols
#include "DTOTransBase.h"
#include "TravelRect.h"

/////////////////////////////////////////////////////////////////////////////
// CSlot
class ATL_NO_VTABLE CSlot : 
	public CDTOTransBase,
	public CComCoClass<CSlot, &CLSID_Slot>,
	public IDispatchImpl<ISlot, &IID_ISlot, &LIBID_ISSPWEffectLib>
{
    typedef CDTOTransBase _basex;
    typedef CSlot _thisx;
    typedef ISlot _selfI;

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
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_SLOT)
        
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

    void  DrawSlot(IN HDC hInDC1,IN HDC hInDC2,IN HDC hOutDC,
        CTravelRect& aTravelRect);
    
    
    // Properties
private:
    
    // Bitmap
private:
    

    // Control values
private:

    INT  m_iLeftSlotLen;
    INT  m_iMidSlotLen;
    INT  m_iRightSlotLen;

    CTravelRect  m_trLeft;

    CTravelRect  m_trMid;

    CTravelRect  m_trRight;
	
};

#endif //__SLOT_H_
