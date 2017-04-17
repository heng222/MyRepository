

#ifndef _DTO_EFFECTS_BASE_H_45902
#define _DTO_EFFECTS_BASE_H_45902

#include "DTOBase.h"

/*****************************************************************************
 * class 
 * 
 *****************************************************************************/
class ATL_NO_VTABLE CDTOEffectBase : public CDTOBase
{
	typedef CDTOBase _basex;
    typedef CDTOEffectBase _thisx;

public:
	
	// ATL Setup
// 	BEGIN_COM_MAP(CDTOClrAdjust)
// 		COM_INTERFACE_ENTRY(IColorAdjust)
//  		COM_INTERFACE_ENTRY2(IDispatch,IColorAdjust)
// 		COM_INTERFACE_ENTRY_CHAIN( CDTOBase )
// 	END_COM_MAP()

public: 
	
	// Implement IDXEffect properties: Progress, Duration, etc..
	//DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)

	// From IPWEffect
	DECLARE_IPWEFFECT_METHODS(_basex)


	// From CDTOBase
protected:

    virtual HRESULT FinalConstruct();
	
    virtual HRESULT OnInitialize();

    virtual HRESULT OnStart();
    
    virtual HRESULT OnTerminate();
    
    virtual HRESULT OnTransform(IN DWORD* pInputBuf,
                        IN DWORD* pInput2Buf,
                        IN DWORD* pOutputBuf);
    
    virtual BOOL IsTransition();

    // On duration changed.
    virtual HRESULT OnDurationChanged(FLOAT fNewDur);

    // New virtual methods
protected:

    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,       // The original input data (Bottom-up)
                                 IN DWORD* pOutputBuf,      // Output buffer (Top-down)
                                 IN INT iWidth,
                                 IN INT iHeight);

    // New public methods
public:

    // width / height of input/output surface.
    INT     Width() const;
    INT     Height() const;

    // Retrieve the input/output buffer size.
    LONG    GetBufferSize() const;    

    // 
    HDC     GetMemDC();
    void    ReleaseMemDC();

protected:


    // private members
private:
    
    // The memory DC and compatible bitmap.
    HDC		    m_hMemDC;
	HBITMAP		m_hMemBitmap;
    BOOL        m_bMemDcLock;
    
    // 
    LONG    m_lPitch;
};

//////////////////////////////////////////////////////////////////////////
#endif