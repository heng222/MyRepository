

#ifndef _DTO_TRANSITIONS_BASE_H_563OJIDE
#define _DTO_TRANSITIONS_BASE_H_563OJIDE

#include "DTOBase.h"

/*****************************************************************************
 * class 
 * 
 *****************************************************************************/
class CDTOTransBase : public CDTOBase

{
	typedef CDTOBase _basex;
    typedef CDTOTransBase _thisx;

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


	// From _basex
protected:
    
    virtual HRESULT FinalConstruct();

    virtual HRESULT OnInitialize();

    // On start to play
    virtual HRESULT OnStart();

    virtual HRESULT OnDurationChanged(FLOAT fNewDur);

    virtual HRESULT OnTerminate();
    
    virtual HRESULT OnTransform(IN DWORD* pInputBuf,
        IN DWORD* pInput2Buf,
        IN DWORD* pOutputBuf);
    
    virtual BOOL IsTransition();
	
    // New virtual methods
protected:

    
    virtual HRESULT ResetControlValue()=0;

    virtual HRESULT UpdateControlValue()=0;
    
    
    virtual HRESULT DrawLiveBitmap(IN HDC hdcHide,
                        IN HDC hdcShow,
                        IN HDC hdcOutput);
    

    // new public methods
public:
    
    INT     Width() const;
    INT     Height() const;

    
    HRESULT  GetBitmapInfo(BITMAPINFO& bmpInfo) const;

    // retrieve specified DC.
    HDC      RetrieveDC(TBufferType iType) const;

    // retrieve the corresponding output bitmap 
    HBITMAP  RetrieveOutputBitmap() const;
    
    //
protected:

    BOOL        m_bDisplayOn;   // TRUE=DisplayOn; FALSE=DisplayOff

    // Private members
private:

    HDC         m_hdcInput1;
    HDC         m_hdcInput2;

    HDC         m_hdcOutput;
    HBITMAP     m_hBmpOutput;

};

//////////////////////////////////////////////////////////////////////////
#endif