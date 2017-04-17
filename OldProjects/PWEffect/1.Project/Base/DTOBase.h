/*****************************************************************************
 * module CDTOBase.h 
 *
 *	Contains two sample DXT's (DirectX Transforms) one effect CMMSampleEffect and
 *	one transition CMMSampleTransition, both built from a common base class CMMSpecialEffectDXT.
 *	
 *	CMMSpecialEffectDXT is a COM object which inherits from a base class CDXBaseNTo1 provided by
 *	the DXTransform SDK for creating video effects and transitions.  CMMSpecialEffectDXT handles
 *	communication and memory buffer manipulation between Movie Maker and the 
 *	class CMMSpecialEffect which implements the graphics portion the effect or transition.
 *	In this sample, CMMSpecialEffectDXT creates and stores a CMMSpecialEffect object when either
 *	the Blue or MeltIntensity properties are set through the Movie Maker via BlueAdjust.xml or Melt.xml.
 *	
 * Copyright (c) ISoftStone Corporation. All rights reserved.
 *****************************************************************************/

#ifndef _DIRECT_TRANSFOR_OBJECT_BASE_
#define _DIRECT_TRANSFOR_OBJECT_BASE_

//Include resources
#include "resource.h"
#include <math.h> //fabs

//Include DXTransform SDK
#include <DTBase.h>
#include "RandMgr.h"
#include "PWEffect.h"


// Simple enum describing which buffer we're talking about.
typedef enum _tagBufferType
{
	EWBInputBuffer = 0,	// 1st input buffer for transitions or only input buffer for effects.
	EWBInput2Buffer,	// 2nd input buffer for transitions.  Not used for effects.
	EWBOutputBuffer		// Output memery buffer

} TBufferType;

// Transparent color
#define CLR_TRANSPARENT_AGENT     0
#define CLR_TRANSPARENT_ACTUAL    0XFFFFFF

//Initial value of m_fGamma
#define DEFAULT_GAMMA_VALUE 1.0f

//Initial value of m_fCOLOR
#define DEFAULT_COLOR_VALUE 0.0f

//Initial value of m_fInvert
#define DEFAULT_INVERT_VALUE 1.0f

//Initial value of m_fBrightness 
#define DEFAULT_BRIGHTNESS_VALUE -1.0f

//Initial value of m_fConstrast 
#define DEFAULT_CONTRAST_VALUE -1.0f

//Initial value of m_nPosterize 
#define DEFAULT_POSTERIZE_VALUE 0

//Initial value of m_fThreshold 
#define DEFAULT_THRESHOLD_VALUE (-1.0f)

// Frame rate
#define     FRAMERATE       33.333

//Convenience inline method to compare floating point values based on a tolerance.
#define FLOAT_TOLERANCE 0.0001
inline bool IsEqual(float f1, float f2)
{
    return fabs(f1 - f2) < FLOAT_TOLERANCE;
}

class CAutoDeskDC
{
public:
    CAutoDeskDC()
    {
        m_hDeskDC = ::GetDC(NULL);
    }

    ~CAutoDeskDC()
    {
        ::ReleaseDC(NULL,m_hDeskDC);
    }

    operator HDC()
    {
        return m_hDeskDC;
    }

private:

    HDC m_hDeskDC;
};

/*****************************************************************************
 * class CDTOBase -		class for DTX wrapper object
 *****************************************************************************/
class ATL_NO_VTABLE CDTOBase : 
	public CDXBaseNTo1,
	public IDispatchImpl<IPWEffect, &IID_IPWEffect, &LIBID_ISSPWEffectLib>
{
        typedef CDXBaseNTo1 _basex;
        typedef CDTOBase _thisx;

public:

	// ATL Setup
	BEGIN_COM_MAP(CDTOBase)
 		COM_INTERFACE_ENTRY(IPWEffect)
 		COM_INTERFACE_ENTRY(IDXEffect)
 		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_CHAIN( CDXBaseNTo1 )
    END_COM_MAP()


     // Interface
public:
    
    // IDXEffect interface override
    STDMETHODIMP get_Capabilities(long *pVal);
    STDMETHODIMP get_Progress(float *pVal);
    STDMETHODIMP put_Progress(float newVal);
    STDMETHODIMP get_StepResolution(float *pVal);
    STDMETHODIMP get_Duration(float *pVal);
    STDMETHODIMP put_Duration(float newVal);
        
    // IPWEffect Interface
    STDMETHOD(get_Blue)(float* pfBlue);
    STDMETHOD(put_Blue)(float fBlue);
    STDMETHOD(get_Green)(float* pfGreen);
    STDMETHOD(put_Green)(float pfGreen);
    STDMETHOD(get_Red)(float* pfRed);
    STDMETHOD(put_Red)(float pfRed);
    STDMETHOD(get_BackColor)(OLE_COLOR* pValue);
	STDMETHOD(put_BackColor)(OLE_COLOR newValue);
    

    // From CDXBaseNTo1
public:
    
    virtual HRESULT WorkProc( const CDXTWorkInfoNTo1& WI, BOOL* pbContinue );
	virtual HRESULT OnSetup( DWORD dwFlags );


	// New virtual Methods
public:

    //virtual ~CDTOBase()=0 {}; 
    
    // Constructor and destructor
    virtual HRESULT FinalConstruct();
    virtual HRESULT FinalRelease();

    // Called after OnSetup. At this time, the properties
    // of DTO have already initialized.
    virtual HRESULT OnInitialize() = 0;

    // On start to play. (usually we initialize control value here.)
    virtual HRESULT OnStart() = 0;

    // On Notify the number of frame
    //virtual HRESULT OnNotifyFrameNum(DWORD dwNumFrame) = 0;

    // Called after FinalRelease.
	virtual HRESULT OnTerminate() = 0;

    // Called on WorkProc.
    virtual HRESULT OnTransform(IN DWORD* pInputBuf,
                                IN DWORD* pInput2Buf,
                                IN DWORD* pOutputBuf) = 0;

    // Is the DTO a transition object?
    virtual BOOL IsTransition() = 0;

    // On duration changed.
    virtual HRESULT  OnDurationChanged(FLOAT fNewDur);
    
    // New public methods
public:

	// Public methods for dealing with input and output surfaces.
	// Called from CMMSpecialEffectDXT's hosted special effect object to get 32bit buffer and buffer info.
    HRESULT GetInputBuffer(BYTE** ppbBuffer);
    int     GetInputWidth() const;
    int     GetInputHeight() const;
    long    GetInputPitch();
	
    HRESULT GetInput2Buffer(BYTE** ppbBuffer);
    int     GetInput2Width() const;
    int     GetInput2Height() const;
    long    GetInput2Pitch();


    HRESULT GetOutputBuffer(BYTE** ppbBuffer);
    int     GetOutputWidth() const;
    int     GetOutputHeight() const;
    long    GetOutputPitch();

	HRESULT get_NativeInputPixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat) const;
	HRESULT get_NativeInput2PixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat) const;
	HRESULT get_NativeOutputPixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat) const;
	HRESULT GetDirectDraw(IDirectDraw7** ppDDraw) const;
	HRESULT get_NumInputs(int* pnInputs) const;
	HRESULT get_Quality(float* pfQuality) { return GetQuality(pfQuality); }
	HRESULT get_UseNativeBuffers(bool* pbUseNativeBuffers) const;
	HRESULT put_UseNativeBuffers(bool bUseNativeBuffers);
    

    // Duration
    FLOAT  GetDuration() const { return m_Duration; }

    // Progress
    FLOAT  GetProgress() const { return m_Progress; }

    // frame rate
    FLOAT  GetFrameRate() const { return 68.966f; }
	
	// Private Methods
private:

    // Initialization when DTO's properties have initialized.
    HRESULT  Initialize();

    // To transform
    HRESULT  Transform(IN DWORD* pInputBuf,   
                       IN DWORD* pInput2Buf,   
                       IN DWORD* pOutputBuf);


    // Standard color mixer operations for basic effects.
    HRESULT  InitStandardOperations();
    HRESULT  ExecuteStandardOperations(DWORD* pdwBuffer, int nWidth);
    HRESULT  ClearStandardOperations();

	// locks one of the input surfaces or the output surface for read/write.
	HRESULT  LockSurface(TBufferType eWB);
	
	// Gets pointer to memory buffer.
	HRESULT  GetBuffer(TBufferType eBuffer, BYTE** ppdwBuffer);
	HRESULT  GetPitch(TBufferType eBuffer, long* plValue);
	
	// management methods for store buffers.
	HRESULT  CreateBuffers( );
	HRESULT  ReleaseBuffers( );
	
protected:

	// frame counter
	LONG	GetCounter() const;
	void	ResetCounter();
	void	IncreaseCounter();

    // DTO color methods
    DXSAMPLE  MakeDXSAMPLE(BYTE byR,BYTE byG,BYTE byB) const;
    DXSAMPLE  MakeDXSAMPLE(COLORREF clrRef) const;
    BYTE	  GetRed(DWORD dwValue) const;
    BYTE	  GetGreen(DWORD dwValue) const;
    BYTE	  GetBlue(DWORD dwValue) const;
    COLORREF  DX2COLORREF(DXSAMPLE clrDX) const;
    DXSAMPLE  COLORREF2DX(COLORREF clrRef) const;
    
    // The weighted Euclidean Distance between two colors.
    DOUBLE    WEDistanceOfColors(COLORREF in_color1, 
                        COLORREF in_color2) CONST;
    // 
    BOOL    IsUseNativeBuf() const;

    // Retrieve a black agent
    COLORREF GetBlackAgentClr() const;

    // Is transparent color
    BOOL    IsTransparent(COLORREF clr) const;
    
    // bitmap information of surface.
    HRESULT GetSurfaceBmpInfo(BITMAPINFO& bmpInfo) const;

    // 
    WORD    GetBitCount() const;
    
    // Create a DDB.
    HBITMAP  CreateBitmap(DWORD* pData,INT iWidth,
                INT iHeight,BOOL bBottomUp=TRUE) const;

    // Copy Bitmap's bits
    void    CopyBitmapBits(DXSAMPLE* pDest,DXSAMPLE* pSource,
                INT iWidth, INT iHeight) const;

    // Invert bitmap's bits.
    void    InvertBitmapBits(const DWORD* pInput,
                DWORD* pOutput,
                INT iWidth,     INT iHeight) const;

    HBITMAP CreateSufaceBitmap(INT iWidth, 
                INT iHeight,
                CONST VOID *lpbInit            // initialization data
                ) const;

    // Private methods
private:

    DWORD    m_dwNumFrame;
    DWORD    CalcFrameNum();



    // Member Data
private:

    // DTO state
    enum TState
    {
        EInitizing,
        EInitialized,
        EExecuting,
        ETerminated,
    } m_iDTOState;
    
    // Buffers for unpacking/repacking to/from 32bit pixel format.  
    // For performance reasons we would like to operate directly on the input and output buffers in 24-bit
    // but if 32-bit operations are desired we use this buffers to unpack the 24 bit to 32.
    // Only used if native pixel format != display depth AND NativeBufferMode is not set to true.
    DXSAMPLE* m_pInputBuffer, *m_pInput2Buffer, *m_pOutputBuffer;
    
    // Surface pointers.  Maintained during the lifetime of the WorkProc() method.
    CComPtr<IDXARGBReadPtr>	m_pInputSurface;
    CComPtr<IDXARGBReadPtr>	m_pInput2Surface;
    CComPtr<IDXARGBReadWritePtr> m_pOutputSurface;
    
    // Hold a Direct Draw object so we only have to create it once.
    CComPtr<IDirectDraw7> m_pDirectDraw7;
    
    // Storage for the bounding rectangles of all surfaces.
    CDXDBnds m_bndsInput, m_bndsInput2, m_bndsOutput;
    
    // Native buffer info and pixel format.  
    // Set during our the OnSetup() method.
    DXNATIVETYPEINFO m_dxInfoInput, m_dxInfoInput2, m_dxInfoOutput;
    DXSAMPLEFORMATENUM m_dxFormatInput, m_dxFormatInput2, m_dxFormatOutput;
    
    // If true, the input and output buffers will always be 32 bit.
    bool m_bUseNativeBuffers;

	// frame counter.
	LONG	m_lFrameCounter;


protected:
    
    // Quality factor.  Acquired from DXT which is hosting this object.
    // float m_fltQualityFactor;	
    
    // Color adjustment values.  
    float  m_fRed;
    float  m_fGreen;
    float  m_fBlue;
    COLORREF  m_clrBackground;  
    
    // Color operations that may be applied to image.
    float m_fInvert;
    float m_fGamma;
    float m_fBrightness;
    float m_fContrast;
    float m_fThreshold;
    int   m_nPosterize;
    
    // Color adjustment object provided by DXTransform SDK.
    // Used to alter amount of red, green, blue, contrast, brightness
    // and to apply posterize and threshold effects.
    CComPtr<IDXLookupTable> m_pLUT;	
    
};


// IPWEffect Macro implemention
// Declare IPWEffect properties: Blue, Red, Green, etc..
#define DECLARE_IPWEFFECT_METHODS(base_class) \
    STDMETHODIMP get_Capabilities(long *pVal) { return base_class::get_Capabilities(pVal);} \
    STDMETHODIMP get_Progress(float *pVal) { return base_class::get_Progress(pVal); } \
    STDMETHODIMP put_Progress(float newVal) { return base_class::put_Progress(newVal); } \
    STDMETHODIMP get_StepResolution(float *pVal) { return base_class::get_StepResolution(pVal);} \
    STDMETHODIMP get_Duration(float *pVal) { return base_class::get_Duration(pVal);  } \
    STDMETHODIMP put_Duration(float newVal) { return base_class::put_Duration(newVal); } \
    STDMETHOD(get_Blue)(float* pfBlue) { return base_class::get_Blue(pfBlue); } \
    STDMETHOD(put_Blue)(float fBlue) { return base_class::put_Blue(fBlue); } \
    STDMETHOD(get_Green)(float* pfGreen) { return base_class::get_Green(pfGreen); } \
    STDMETHOD(put_Green)(float fGreen) { return base_class::put_Green(fGreen); } \
    STDMETHOD(get_Red)(float* pfRed) { return base_class::get_Red(pfRed); } \
    STDMETHOD(put_Red)(float fRed) {return base_class::put_Red(fRed); } \
    STDMETHOD(get_BackColor)(OLE_COLOR* pValue) {return base_class::get_BackColor(pValue);} \
    STDMETHOD(put_BackColor)(OLE_COLOR newValue) {return base_class::put_BackColor(newValue);} \
 


//////////////////////////////////////////////////////////////////////////

// Retrieve the reference effect control marco definition
// #define DECLARE_REF_EFFECTCTRL(effect_ctrl_name) \
//     effect_ctrl_name* GetRefEffectCtrl() \
// 	{ \
// 		return (effect_ctrl_name*)RetrieveEffectCtrl(); \
// 	}
// 
// // 
// #define REF_CTRL() GetRefEffectCtrl()

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#endif	