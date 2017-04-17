/*****************************************************************************
 * module MMSpecialEffectDXT.h 
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
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#ifndef MMSpecialEffectDXT_H
#define MMSpecialEffectDXT_H

//Include DXTransform SDK
#include <DTBase.h>

//Include special effect base class object.
#include "MMSpecialEffect.h"

//Include resources
#include "resource.h"

//Simple enum describing which buffer we're talking about.
typedef enum _enumWhichBuffer
{
	enumWBInputBuffer = 0,	//1st input buffer for transitions or only input buffer for effects.
	enumWBInput2Buffer,		//2nd input buffer for transitions.  Not used for effects.
	enumWBOutputBuffer		//Output memery buffer

} enumWhichBuffer;

//The strings used to create an object from a string
const CComBSTR g_szSimple3DInternalName = L"Simple3D";
const CComBSTR g_szStandardInternalName = L"Standard";


/*****************************************************************************
 * class CMMSpecialEffectDXT -		class for DTX wrapper object
 *****************************************************************************/
class CMMSpecialEffectDXT : 
	public CDXBaseNTo1,
	public IDispatchImpl<IMMSampleTFX, &IID_IMMSampleTFX, &LIBID_MMFXLib>
{
private:
	typedef IDispatchImpl<IMMSampleTFX, &IID_IMMSampleTFX, &LIBID_MMFXLib> _dispatchBase;

public:

	//ATL Setup
	BEGIN_COM_MAP(CMMSpecialEffectDXT)
		COM_INTERFACE_ENTRY(IDXEffect)
		COM_INTERFACE_ENTRY(IMMSampleTFX)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY_CHAIN( CDXBaseNTo1 )
	END_COM_MAP()

protected:
	//Private Member Data

	//Storage for properties set by Movie Maker from values in the extension XML file 
	//which describes this effect or transition. 
	//Amount of blue to add as effect.  See declaration of put_Blue.
	float m_fBlueAmount;	

	//Amount of melting that will occur to video A.  
	//This for a Melt transition.  See definition of put_MeltIntensity.
	float m_fMeltIntensity; 
	
	//Buffers for unpacking/repacking to/from 32bit pixel format.  
	//For purformance reasons we would like to operate directly on the input and output buffers in 24-bit
	//but if 32-bit operations are desired we use this buffers to unpack the 24 bit to 32.
	//Only used if native pixel format != display depth AND NativeBufferMode is not set to true.
	DXSAMPLE* m_pInputBuffer, *m_pInput2Buffer, *m_pOutputBuffer;

	//Surface pointers.  Maintained during the lifetime of the WorkProc() method.
	CComPtr<IDXARGBReadPtr>	m_pInputSurface;
	CComPtr<IDXARGBReadPtr>	m_pInput2Surface;
	CComPtr<IDXARGBReadWritePtr> m_pOutputSurface;

	//Hold a Direct Draw object so we only have to create it once.
	CComPtr<IDirectDraw7> m_pDirectDraw7;

	//Storage for the bounding rectangles of all surfaces.
	CDXDBnds m_bndsInput, m_bndsInput2, m_bndsOutput;

	//Native buffer info and pixel format.  
	//Set during our the OnSetup() method.
	DXNATIVETYPEINFO m_dxInfoInput, m_dxInfoInput2, m_dxInfoOutput;
	DXSAMPLEFORMATENUM m_dxFormatInput, m_dxFormatInput2, m_dxFormatOutput;

	//If true, the input and output buffers will always be 32 bit.
	bool m_bUseNativeBuffers;

	//The special effect object.  Set in CreateSpecialEffectByName().
	CMMSpecialEffect* m_pSpecialEffect;

	//Private Methods

	//locks one of the input surfaces or the output surface for read/write.
	HRESULT LockSurface(enumWhichBuffer eWB);
	
	//Gets pointer to memory buffer.
	HRESULT GetBuffer(enumWhichBuffer eBuffer, BYTE** ppdwBuffer);
	HRESULT GetPitch(enumWhichBuffer eBuffer, long* plValue);

	//management methods for store buffers.
	HRESULT CreateBuffers( );
	HRESULT ReleaseBuffers( );

	//Handles creation of the special effect object.
	//Called from put_Property() when the property name is "InternalName".
	HRESULT CreateSpecialEffectByName(BSTR bstrInternalName);
	HRESULT Initialize();
	HRESULT Terminate();

  public:
	//Public Methods
	 
	CMMSpecialEffectDXT() { } 

	//Constructor and destructor
	virtual HRESULT FinalConstruct();
	virtual HRESULT FinalRelease();

	//DXT case class overrides 
	HRESULT WorkProc( const CDXTWorkInfoNTo1& WI, BOOL* pbContinue );
	HRESULT OnSetup( DWORD dwFlags );

	//IMMSampleTFX properties
	STDMETHOD(get_Blue)(float* pfBlue);
	STDMETHOD(put_Blue)(float fBlue);
	STDMETHOD(get_MeltIntensity)(float* pfMeltIntensity);
	STDMETHOD(put_MeltIntensity)(float fMeltIntensity);

	//Public methods for dealing with input and output surfaces.
	//Called from CMMSpecialEffectDXT's hosted special effect object to get 32bit buffer and buffer info.
	virtual HRESULT GetInputBuffer(BYTE** ppbBuffer);
	virtual HRESULT GetInput2Buffer(BYTE** ppbBuffer);
	virtual HRESULT GetOutputBuffer(BYTE** ppbBuffer);
	virtual HRESULT get_Width(int* pnValue);
	virtual HRESULT get_Height(int* pnValue);
	virtual HRESULT get_InputPitch(long* plValue);
	virtual HRESULT get_Input2Pitch(long* plValue);
	virtual HRESULT get_OutputPitch(long* plValue);
	virtual HRESULT get_NativeInputPixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat);
	virtual HRESULT get_NativeInput2PixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat);
	virtual HRESULT get_NativeOutputPixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat);
	virtual HRESULT GetDirectDraw(IDirectDraw7** ppDDraw);
	virtual HRESULT get_NumInputs(int* pnInputs);
	virtual HRESULT get_Quality(float* pfQuality) { return GetQuality(pfQuality); }
	virtual HRESULT get_UseNativeBuffers(bool* pbUseNativeBuffers);
	virtual HRESULT put_UseNativeBuffers(bool bUseNativeBuffers);
 
	//Implement IDXEffect properties: Progress, Duration.
	DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)
};


/*****************************************************************************
 * class CMMSampleEffect -		class for DTX wrapper object
 * 294D0DE1-1B57-408d-A33F-FA708A5A28D6
 *****************************************************************************/
class CMMSampleEffect : 
	public CMMSpecialEffectDXT,
	public CComCoClass<CMMSampleEffect, &CLSID_MMSampleEffect>
{
	typedef CMMSpecialEffectDXT _dxtBase;
public:
	//Implement registration for DX Transform
	DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_MMSPECIALEFFECT1)

	DECLARE_POLY_AGGREGATABLE(CMMSampleEffect)

	virtual HRESULT FinalConstruct()
	{
		RTN_HR_IF_FAILED(_dxtBase::FinalConstruct());

		//This is the Blue Adjust effect, create the CMMSpecialEffect used to perform the effect.
		RTN_HR_IF_FAILED(CreateSpecialEffectByName(g_szStandardInternalName));

		return S_OK;
	}

};

/*****************************************************************************
 * class MMSampleTransition -		class for DTX wrapper object
 * 978DABA8-F330-4f09-BEC5-4D53C541BB4D
 *****************************************************************************/
class CMMSampleTransition : 
	public CMMSpecialEffectDXT,
	public CComCoClass<CMMSampleTransition, &CLSID_MMSampleTransition>
{
	typedef CMMSpecialEffectDXT _dxtBase;
public:
	//Implement registration for DX Transform
	DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_MMSPECIALEFFECT2)

	DECLARE_POLY_AGGREGATABLE(CMMSampleTransition)

	virtual HRESULT FinalConstruct()
	{
		RTN_HR_IF_FAILED(_dxtBase::FinalConstruct());
		m_ulMaxInputs       = 2;
		m_ulNumInRequired   = 2;

		//This is the Melt transition, create the CSimple3DSpecialEffect used to perform the 3D transition.
		RTN_HR_IF_FAILED(CreateSpecialEffectByName(g_szSimple3DInternalName));

		return S_OK;
	}
};

//////////////////////////////////////////////////////////////////////////
#endif 

