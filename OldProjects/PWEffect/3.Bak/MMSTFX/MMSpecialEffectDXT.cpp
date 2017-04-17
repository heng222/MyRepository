/*****************************************************************************
 * module MMSpecialEffectDXT.cpp 
 *
 *	defines the main DXT wrapper object for CMMSpecialEffect
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#include "stdafx.h"

#include "MMSTFX.h"					//IDL
#include "MMSpecialEffectDXT.h"     //Class definition
#include "MM3DSpecialEffects.h"		//D3D transition/effect engine


/******************************************************************************
 * Description: Constructor of DXT class.  Performs one-time initialization.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::FinalConstruct()
{
	//--- Init base class variables to control setup
	m_ulMaxInputs       = 1;    //Defaults to 1 input surface for effects.  Set to 2 for transitions.
	m_ulNumInRequired   = 1;	//Defaults to 1.  Set to 2 for transitions.
	m_ulMaxImageBands	= 1;	//Number of CPU's to use if available.  
	m_dwOptionFlags     = DXBOF_SAME_SIZE_INPUTS | DXBOF_CENTER_INPUTS;
	m_dwMiscFlags		= DXTMF_QUALITY_SUPPORTED | //Supports IDXEffect::SetQuality() and GetQuality().
						  DXTMF_OPAQUE_RESULT;		//No alpha channel info in output buffer.
	m_Duration          = 2.0;						//Default duration of effect or transition.

	//Set to true if special effect works with the 24-bit per pixel buffers that Movie Maker provides via
	//DirectShow.  Native buffer mode is faster because it does not require a extra buffer copy for each surface
	//to convert between the native 24 bit and 32 bit.
	m_bUseNativeBuffers = false;

	//32 bit per pixel buffers used to work with input surfaces.  Not allocated if m_bUseNativeBuffers is true.
	m_pInputBuffer = NULL;
	m_pInput2Buffer = NULL;
	m_pOutputBuffer = NULL;

	//Set maximum time to wait for surface lock to 1 second to avoid starving the pipeline.
	m_ulLockTimeOut = 1000;

	m_pSpecialEffect = NULL;

	m_fBlueAmount = 0.0f;		//Amount of blue to add as effect.  See declaration of put_Blue.
	m_fMeltIntensity = 0.0f;	//Amount of melting that will occur for 3D transition.  See declaration of put_MeltIntensity.

    return S_OK;
} 


/******************************************************************************
 * Description: DXT destructor.  Releases anything we're holding on to.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::FinalRelease() 
{ 
	RTN_HR_IF_FAILED(ReleaseBuffers());
	m_pDirectDraw7.Release();

	RTN_HR_IF_FAILED(Terminate());

	return S_OK; 
}

/******************************************************************************
 * Description: Allocates buffers necessary to unpack and repack input and
 * output surfaces to 32bit ARGB.  Only needed when native pixel formats are 
 * not 32bit.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::CreateBuffers( )
{
	//Sanity
	ASSERT(!m_bUseNativeBuffers);

	//Make sure any previously allocated buffers are released.
	RTN_HR_IF_FAILED(ReleaseBuffers());

	//Allocate 1st input video buffer
	m_pInputBuffer = new DXSAMPLE[m_bndsInput.Width() * m_bndsInput.Height() * sizeof( DXSAMPLE )];
	RTN_HR_IF_BADNEW(m_pInputBuffer);

	//If this is a transition
	if (m_ulMaxInputs == 2)
	{
		//Allocate 2nd input video buffer
		m_pInput2Buffer = new DXSAMPLE[m_bndsInput2.Width() * m_bndsInput2.Height() * sizeof( DXSAMPLE )];
		RTN_HR_IF_BADNEW(m_pInput2Buffer);
	}

	//Allocate output buffer
	m_pOutputBuffer = new DXSAMPLE[m_bndsOutput.Width() * m_bndsOutput.Height() * sizeof( DXSAMPLE )];
	RTN_HR_IF_BADNEW(m_pOutputBuffer);

	return S_OK;
}

/******************************************************************************
 * Description: Released any buffers allocated in CreateBuffers()
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::ReleaseBuffers( )
{
	//Delete any existing buffers.  
	if (m_pInputBuffer)
	{
		delete [] m_pInputBuffer;
		m_pInputBuffer = NULL;
	}

	if (m_pInput2Buffer)
	{
		delete [] m_pInput2Buffer;
		m_pInput2Buffer = NULL;
	}

	if (m_pOutputBuffer)
	{
		delete [] m_pOutputBuffer;
		m_pOutputBuffer = NULL;
	}

	return S_OK;
}

/******************************************************************************
 * Description: Called to initialize DXT.  This is called only after all lower
 * level initialization is done.  Call CMMSpecialEffectDXT's initialize 
 * which in turn calls our CMMSpecialEffect's Initialize().  Then this function
 * gets pixel formats associated with the surfaces.
 *
 * DWORD dwFlags - something from DXTs that we don't use
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::OnSetup( DWORD dwFlags )
{
	//In case this gets called twice
	ReleaseBuffers();

	//Get dimensions of surface from the input surface
	IDXSurface* pSurface = InputSurface(0);
	RTN_HR_IF_BADPTR(pSurface);
	RTN_HR_IF_FAILED(pSurface->GetBounds(&m_bndsInput));

	GUID guidPixelFormat;
	RTN_HR_IF_FAILED(pSurface->GetPixelFormat(&guidPixelFormat, &m_dxFormatInput));

	//True if this is a transition
	if (m_ulNumInputs == 2)
	{
		//Get dimensions of second input surface if this is a transition.
		pSurface = InputSurface(1);
		RTN_HR_IF_BADPTR(pSurface);
		RTN_HR_IF_FAILED(pSurface->GetBounds(&m_bndsInput2));
		RTN_HR_IF_FAILED(pSurface->GetPixelFormat(&guidPixelFormat, &m_dxFormatInput2));
	}

	//Get dimensions of output surface
	//IDEA: possible optimization. Don't need to get the whole surface to get the pixel format.
	pSurface = OutputSurface();
	RTN_HR_IF_BADPTR(pSurface);
	RTN_HR_IF_FAILED(pSurface->GetBounds(&m_bndsOutput));
	RTN_HR_IF_FAILED(pSurface->GetPixelFormat(&guidPixelFormat, &m_dxFormatOutput));

	//This DXT runs optimally in 24 bit RGB mode because that is what Movie Maker 2.0's preview and publish use.  
	BOOL bIs24Bit =  (m_dxFormatOutput & DXPF_RGB24) == DXPF_RGB24;	

	//Call base class initialize which calls our CMMSpecialEffect's Initialize().
	RTN_HR_IF_FAILED(Initialize());

	if (!bIs24Bit || !m_bUseNativeBuffers)
	{
		RTN_HR_IF_FAILED(CreateBuffers());
	}

	//Make sure any references acquired during initalization of the special effect are released.
	m_pInputSurface.Release();
	m_pInput2Surface.Release();
	m_pOutputSurface.Release();

	return S_OK;
} 

//  ALL CODE FROM THIS POINT ON IS TIME-CRITICAL SO OPTIMIZE FOR SPEED OVER SIZE!
#ifndef _DEBUG
#pragma optimize("agtp", on)
#endif

/******************************************************************************
 * Description: locks one of the input surfaces or the output surface.
 * The surface is locked for the duration of the WorkProc().  Locking the surface
 * allows us to read from and write to it.  This method also gets and stores the
 * surface format.  If surface is already locked we return immediately.
 *
 * enumWhichBuffer eWB - which buffer to lock
 * 
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::LockSurface(enumWhichBuffer eWB)
{
	HRESULT hr = S_OK;

	switch (eWB)
	{
	case enumWBInputBuffer:

		//Did we already lock this guy?  If so we have nothing to do here
		if (m_pInputSurface)
			return S_FALSE;

		RTN_HR_IF_BADPTR(InputSurface( 0 ));
		hr = InputSurface( 0 )->LockSurface( &m_bndsInput, m_ulLockTimeOut, DXLOCKF_READ, 
											IID_IDXARGBReadPtr, (void**)&m_pInputSurface, NULL );
		if( FAILED( hr ) ) return hr;  //Ok to fail when surface is lost.
		RTN_HR_IF_BADPTR(m_pInputSurface);

		//Clear the info block out and get the info.
		ZeroMemory(&m_dxInfoInput, sizeof DXNATIVETYPEINFO);
		m_dxFormatInput = m_pInputSurface->GetNativeType(&m_dxInfoInput);

		break;
	case enumWBInput2Buffer:

		//Did we already lock this ptr?  If so we have nothing to do here
		if (m_pInput2Surface)
			return S_FALSE;

		RTN_HR_IF_BADPTR(InputSurface( 1 ));
		hr = InputSurface( 1 )->LockSurface( &m_bndsInput2, m_ulLockTimeOut, DXLOCKF_READ, 
											IID_IDXARGBReadPtr, (void**)&m_pInput2Surface, NULL );
		if( FAILED( hr ) ) return hr;  //Ok to fail when surface is lost.
		RTN_HR_IF_BADPTR(m_pInput2Surface);

		//Clear the info block out and get the info.
		ZeroMemory(&m_dxInfoInput2, sizeof DXNATIVETYPEINFO);
		m_dxFormatInput2 = m_pInput2Surface->GetNativeType(&m_dxInfoInput2);

		break;
	case enumWBOutputBuffer:

		//Did we already lock this guy?  If so we have nothing to do here
		if (m_pOutputSurface)
			return S_FALSE;

		RTN_HR_IF_BADPTR(OutputSurface( ));
		hr = OutputSurface(  )->LockSurface( &m_bndsOutput, m_ulLockTimeOut, DXLOCKF_READWRITE , // | DXLOCKF_NONPREMULT,
											IID_IDXARGBReadWritePtr, (void**)&m_pOutputSurface, NULL );
		if( FAILED( hr ) ) return hr;
		RTN_HR_IF_BADPTR(m_pOutputSurface);

		//Clear the info block out and get the info.
		ZeroMemory(&m_dxInfoOutput, sizeof DXNATIVETYPEINFO);
		m_dxFormatOutput = m_pOutputSurface->GetNativeType(&m_dxInfoOutput);

		break;

	default:
		RTN_HR_IF_FAILED(E_UNEXPECTED);
		break;

	}
	return S_OK;
}

/******************************************************************************
 * Description: return input buffer.  see comments in GetBuffer
 *
 * BYTE** ppdwBuffer - pointer to byte pointer to receive requested byte pointer pointer
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::GetInputBuffer(BYTE** ppdwBuffer)
{
	RTN_HR_IF_BADPTR(ppdwBuffer);

	RTN_HR_IF_FAILED(GetBuffer(enumWBInputBuffer, ppdwBuffer));

	RTN_HR_IF_BADPTR(*ppdwBuffer);

	return S_OK;
}

/******************************************************************************
 * Description: return 2nd input buffer.  see comments in GetInputBuffer.
 *
 * BYTE** ppdwBuffer - pointer to byte pointer to receive requested byte pointer pointer
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::GetInput2Buffer(BYTE** ppdwBuffer)
{
	RTN_HR_IF_BADPTR(ppdwBuffer);

	RTN_HR_IF_FAILED(GetBuffer(enumWBInput2Buffer, ppdwBuffer));

	RTN_HR_IF_BADPTR(*ppdwBuffer);

	return S_OK;
}

/******************************************************************************
 * Description: return output buffer.  see comments in GetInputBuffer
 *
 * BYTE** ppdwBuffer - pointer to byte pointer to receive requested byte pointer pointer
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::GetOutputBuffer(BYTE** ppdwBuffer)
{
	RTN_HR_IF_BADPTR(ppdwBuffer);

	RTN_HR_IF_FAILED(GetBuffer(enumWBOutputBuffer, ppdwBuffer));

	RTN_HR_IF_BADPTR(*ppdwBuffer);

	return S_OK;
}

/******************************************************************************
 * Description: return 1st video input buffer.  the input buffer is a byte pointer 
 * to raw pixel data.  the pixel format is always 32bit ARGB unless the
 * NativePixelFormat is set to true.
 *
 * enumWhichBuffer eWB - which buffer to get
 * BYTE*** ppdwBuffer - pointer to byte pointer pointer to receive requested byte pointer pointer
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::GetBuffer(enumWhichBuffer eBuffer, BYTE** ppdwBuffer)
{
	RTN_HR_IF_BADPTR(ppdwBuffer);
	RTN_HR_IF_FAILED(LockSurface(eBuffer));

	IDXARGBReadPtr* pDXReadPtr = NULL;
	DXSAMPLEFORMATENUM dxFormat;
	DXNATIVETYPEINFO* pdxNativeInfo = NULL;
	DXSAMPLE* pSampleBuffer = NULL;
	CDXDBnds* pdxbnds = NULL;

	//Initialize local variables based on whether input 1, input 2, or the output buffer is requested.
	switch (eBuffer)
	{
	case enumWBInputBuffer:
		pDXReadPtr = m_pInputSurface;
		dxFormat = m_dxFormatInput;
		pdxNativeInfo = &m_dxInfoInput;
		pSampleBuffer = m_pInputBuffer;
		pdxbnds = &m_bndsInput;
		break;
	case enumWBInput2Buffer:
		pDXReadPtr = m_pInput2Surface;
		dxFormat = m_dxFormatInput2;
		pdxNativeInfo = &m_dxInfoInput2;
		pSampleBuffer = m_pInput2Buffer;
		pdxbnds = &m_bndsInput2;
		break;
	case enumWBOutputBuffer:
		pDXReadPtr = m_pOutputSurface;
		dxFormat = m_dxFormatOutput;
		pdxNativeInfo = &m_dxInfoOutput;
		pSampleBuffer = m_pOutputBuffer;
		pdxbnds = &m_bndsOutput;
		break;
	default:
		RTN_HR_IF_FAILED(E_UNEXPECTED);
	}

	//Sanity check the internal state
	RTN_HR_IF_BADPTR(pDXReadPtr);

	//We can use the block of memory provided DXT as the memory buffer if the native pixel format is 24bit and
	//this is a request for an input buffer or an output buffer and an alternate format has not been selected.
	BOOL bIs24Bit = (dxFormat & DXPF_RGB24) == DXPF_RGB24;	

	if (bIs24Bit && m_bUseNativeBuffers)
	{
		*ppdwBuffer = pdxNativeInfo->pFirstByte;
	}
	else 
	{
		RTN_HR_IF_BADPTR(pSampleBuffer);
		*ppdwBuffer = (BYTE*) pSampleBuffer;

		//If this is an input surface, copy it to the input buffer.
		if (enumWBOutputBuffer != eBuffer)
		{
			int nNumRows = pdxbnds->Height();
			int nWidth =  pdxbnds->Width();
			for( int nY = 0; nY < nNumRows; ++nY )
			{
				pDXReadPtr->MoveToXY( 0, nNumRows - nY - 1);

				if (!pDXReadPtr->Unpack(pSampleBuffer + nY * nWidth, nWidth, false))
				{
					RTN_HR_IF_FAILED(E_UNEXPECTED);
				}
			}
		}
	}

	RTN_HR_IF_BADPTR(*ppdwBuffer);

	return S_OK;
}



/******************************************************************************
 * Description: return width of all input and output surfaces
 *
 * int* pnWidth - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::get_Width(int* pnWidth)
{
	RTN_HR_IF_BADPTR(pnWidth);
	ASSERT(m_bndsInput.Width() == m_bndsOutput.Width());
	*pnWidth = m_bndsOutput.Width();

	return S_OK;
}

/******************************************************************************
 * Description: return pixel height of all input and output surfaces
 *
 * int* pnHeight - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::get_Height(int* pnHeight)
{
	RTN_HR_IF_BADPTR(pnHeight);
	ASSERT(m_bndsInput.Height() == m_bndsOutput.Height());
	*pnHeight = m_bndsOutput.Height();

	return S_OK;
}

/******************************************************************************
 * Description: return input surface pitch
 *
 * enumWhichBuffer eBuffer - buffer to get pitch of
 * long* plValue - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::GetPitch(enumWhichBuffer eBuffer, long* plValue)
{
	RTN_HR_IF_BADPTR(plValue);

	//Make sure buffer is locked 
	RTN_HR_IF_FAILED(LockSurface(eBuffer));

	DXSAMPLEFORMATENUM dxFormat;
	DXNATIVETYPEINFO* pdxNativeInfo = NULL;
	CDXDBnds* pdxbnds = NULL;

	switch (eBuffer)
	{
	case enumWBInputBuffer:
		dxFormat = m_dxFormatInput;
		pdxNativeInfo = &m_dxInfoInput;
		pdxbnds = &m_bndsInput;
		break;
	case enumWBInput2Buffer:
		dxFormat = m_dxFormatInput2;
		pdxNativeInfo = &m_dxInfoInput2;
		pdxbnds = &m_bndsInput2;
		break;
	case enumWBOutputBuffer:
		dxFormat = m_dxFormatOutput;
		pdxNativeInfo = &m_dxInfoOutput;
		pdxbnds = &m_bndsOutput;
		break;
	default:
		RTN_HR_IF_FAILED(E_UNEXPECTED);
	}


	BOOL bIs24Bit = (dxFormat & DXPF_RGB24) == DXPF_RGB24 ;	// We need to check for equality as DXPF is not an exclusive enumeration

	//If the surface is 24 bit then we'll use the native format settings
	if (bIs24Bit && m_bUseNativeBuffers)
	{
		*plValue = pdxNativeInfo->lPitch ;
	}
	else
	{
		//Otherwise return the pitch of our internally allocated 32 bit buffer.
		*plValue = pdxbnds->Width() * 4;  //Always 32 bit to have room for conversion.
	}

	return S_OK;
}


/******************************************************************************
 * Description: return input surface pitch
 *
 * DWORD* pdwValue - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::get_InputPitch(long* plValue)
{
	RTN_HR_IF_FAILED(GetPitch(enumWBInputBuffer, plValue));

	return S_OK;
}

/******************************************************************************
 * Description: return 2nd input surface pitch
 *
 * long* plValue - output parameter

 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::get_Input2Pitch(long* plValue)
{
	RTN_HR_IF_FAILED(GetPitch(enumWBInput2Buffer, plValue));

	return S_OK;
}

/******************************************************************************
 * Description: return output surface pitch
 *
 * DWORD* pdwValue - output parameter
 *
 * long* plValue - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::get_OutputPitch(long* plValue)
{
	RTN_HR_IF_BADPTR(plValue);

	RTN_HR_IF_FAILED(GetPitch(enumWBOutputBuffer, plValue));

	return S_OK;
}

/******************************************************************************
 * Description: Returns the first input DX surface pixel format
 *
 * DXSAMPLEFORMATENUM* pdxPixelFormat - output parameter
 *
 * Returns: 
 *   HRESULT
 *****************************************************************************/
HRESULT CMMSpecialEffectDXT::get_NativeInputPixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat)
{
	RTN_HR_IF_BADPTR( pdxPixelFormat ) ;
	*pdxPixelFormat = m_dxFormatInput ;
	return S_OK ;
}

/******************************************************************************
 * Description: Returns the second input DX surface pixel format
 *
 * DXSAMPLEFORMATENUM* pdxPixelFormat - output parameter
 *
 * Returns: 
 *	 HRESULT
 *****************************************************************************/
HRESULT CMMSpecialEffectDXT::get_NativeInput2PixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat)
{
	RTN_HR_IF_BADPTR( pdxPixelFormat ) ;
	*pdxPixelFormat = m_dxFormatInput2 ;
	return S_OK ;
}

/******************************************************************************
 * Description: Returns the output DX surface pixel format
 *
 * DXSAMPLEFORMATENUM* pdxPixelFormat - output parameter
 *
 * Returns: 
 *	 HRESULT
 *****************************************************************************/
HRESULT CMMSpecialEffectDXT::get_NativeOutputPixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat)
{
	RTN_HR_IF_BADPTR( pdxPixelFormat ) ;
	*pdxPixelFormat = m_dxFormatOutput ;
	return S_OK ;
}


/******************************************************************************
 * Description: Time sensitive call when DXT should render to output buffer.
 *
 * const CDXTWorkInfoNTo1& WI - information for this cycle of execution
 * BOOL* pbContinue -  will be set to true if we should abort
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::WorkProc( const CDXTWorkInfoNTo1& WI, BOOL* pbContinue )
{
	RTN_HR_IF_BADPTR(m_pSpecialEffect);

	HRESULT hr = S_OK;

	//Store the bounding dimensions of the video plane.
	m_bndsInput = WI.DoBnds;
	m_bndsOutput = WI.OutputBnds;

	//Execute special effect.  For our sample, this will either be the blue adjust effect using the CMMSpecialEffect
	//or the melt transition using CSimple3DSpecialEffect
	hr = m_pSpecialEffect->Execute();

	//If the execute failed, just copying the original input image to the output surface as a fail case.
	if (FAILED(hr))
	{
		RTN_HR_IF_BADPTR(m_cpSurfFact);
		return m_cpSurfFact->BitBlt(OutputSurface(),NULL,InputSurface(m_Progress < 0.5 ? 0 : 1),NULL,0);
	}

	BOOL bIs24Bit = (m_dxFormatOutput & DXPF_RGB24) == DXPF_RGB24;	

	if (m_pOutputSurface)
	{
		if (!bIs24Bit || !m_bUseNativeBuffers)
		{
			//if the output format isn't 24 bit then we're going to have to do a buffer copy.  
			int nNumRows = m_bndsOutput.Height();
			int nWidth =  m_bndsOutput.Width();

			DWORD dwPitchDWORDS = nWidth;
			DWORD dwRowOffsetDWORDS = 0;

			for( int nY = 0; nY < nNumRows; ++nY )
			{
				//--- Get the output row
				m_pOutputSurface->MoveToRow( nNumRows - nY - 1);

				//Write our output buffer to the graph's output buffer
				DXSAMPLE* pRow = (DXSAMPLE*) &( ((DWORD*) (m_pOutputBuffer))[ dwRowOffsetDWORDS ]);
				m_pOutputSurface->PackAndMove(pRow, nWidth);
					
				dwRowOffsetDWORDS += dwPitchDWORDS;
			} 
		}
	}


	//Make sure any references acquired during the special effect are release.
	m_pInputSurface.Release();
	m_pInput2Surface.Release();
	m_pOutputSurface.Release();

	return hr;
}

/******************************************************************************
 * Description: Returns a pointer to direct draw.  Maintains DirectDraw 7 object
 * so it's only created once per DXT life cycle.
 *
 * IDirectDraw7** ppDDraw - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::GetDirectDraw(IDirectDraw7** ppDDraw)
{
	RTN_HR_IF_BADPTR(ppDDraw);
	
	if (!m_pDirectDraw7)
	{
		RTN_HR_IF_FAILED(DirectDrawCreateEx(NULL, (LPVOID*) &m_pDirectDraw7, IID_IDirectDraw7, NULL));
		RTN_HR_IF_BADPTR(m_pDirectDraw7);

		//Set normal cooperative level for offscreen rendering and ensure the DirectX preserves the 
		//floating point registers between calls to prevent collision with DirectShow.
		RTN_HR_IF_FAILED(m_pDirectDraw7->SetCooperativeLevel(NULL, DDSCL_NORMAL | DDSCL_FPUPRESERVE));
	}

	*ppDDraw = m_pDirectDraw7;
	(*ppDDraw)->AddRef();

	return S_OK;
}


/******************************************************************************
 * Description: get the number of inputs to the DXT.  
 *				1 - effects and titlings, 2 - transitions
 *
 * int* pnInputs - output parameters
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::get_NumInputs(int* pnInputs)
{
	RTN_HR_IF_BADPTR(pnInputs);

	*pnInputs = (int) m_ulMaxInputs;

	return S_OK;
}


/******************************************************************************
 * Description: set to true to access buffers directly in 24-bit mode rather than 
 * unpacking them into 32-bit buffers.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::put_UseNativeBuffers(bool bUseNativeBuffers)
{
	m_bUseNativeBuffers = bUseNativeBuffers;

	return S_OK;
}

/******************************************************************************
 * Description: returns true of operating in 24 bit mode.
 *
 * bool* pbUseNativeBuffers - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::get_UseNativeBuffers(bool* pbUseNativeBuffers)
{
	RTN_HR_IF_BADPTR(pbUseNativeBuffers);

	*pbUseNativeBuffers = m_bUseNativeBuffers;

	return S_OK;
}


/******************************************************************************
 * Description: Initialize.   Passes call along to CMMSpecialEffect inherited class.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::Initialize()
{
	//Has CreateSpecialEffectByName() been called to create the m_pSpecialEffect object?
	if (!m_pSpecialEffect)
	{
		//This must be the Blue Adjust effect because the Melt transition 
		//calls CreateSpecialEffectByName() in it's FinalConstruct() method.  

		//For blue adjust create the "Standard" object.  It copies input video buffer A 
		//to the output buffer.
		RTN_HR_IF_FAILED(CreateSpecialEffectByName(g_szStandardInternalName));
	}

	//Initialize the special effect CMMSpecialEffect or CMM3DSpecialEffect
	RTN_HR_IF_BADPTR(m_pSpecialEffect);
	RTN_HR_IF_FAILED(m_pSpecialEffect->Initialize());

	return S_OK;
}

/******************************************************************************
 * Description: Terminate.  Passes call along to CMMSpecialEffect inherited class
 * and then deletes the class.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::Terminate()
{
	if (m_pSpecialEffect)
	{
		HRESULT hr = S_OK;
		hr = m_pSpecialEffect->Terminate();		//Call special effect's terminate handler.
		if (FAILED(hr) && E_NOTIMPL != hr)
		{
			ASSERT(0);
		}

		delete m_pSpecialEffect;
		m_pSpecialEffect = NULL;
	}

	return S_OK;
}

// *** Macros to simplify adding new special effects.
#define DECLARE_SPECIAL_EFFECT(SE_NAME, SE_CLASS)		\
	else if (lstrcmp(bstrInternalName, SE_NAME) == 0)	\
	{													\
		m_pSpecialEffect = new SE_CLASS(this, bstrInternalName); \
		if (!m_pSpecialEffect)							\
			return E_OUTOFMEMORY;						\
	}											

//Start with a single if statement because DECLARE_SPECIAL_EFFECT always starts with else.
#define BEGIN_SPECIAL_EFFECT_MAP()	\
	if (0)	{ }						\

//The default will be just the standard special effect.
#define END_SPECIAL_EFFECT_MAP()	\
	else \
	{													\
		m_pSpecialEffect = new CMMSpecialEffect(this, bstrInternalName); \
		if (!m_pSpecialEffect)							\
			return E_OUTOFMEMORY;						\
	}											


/******************************************************************************
 * Description: Allocates a new class (which inherits from CMMSpecialEffect)
 * Developers creating new special effects must add code here associate their
 * class with an InternalName.  Called from CMMSampleEffect's or 
 * CMMSampleTransition's FinalConstruct() method.
 *
 * BSTR bstrInternalName - name of effect to create.  see map below.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffectDXT::CreateSpecialEffectByName(BSTR bstrInternalName)
{
	//Do we already have an special effect object?  
	//If so then no need to execute this code to create it again.
	if (m_pSpecialEffect)
	{
		ASSERT(0);
		return S_FALSE;
	}

	//Macros implement a series of IF states to create new special effects and are defined
	//at the top of this file.  To add a new special effect, copy a DECLARE_ line below and
	//change the values of the name and our new class to create.  Note that your new class 
	//must inherit from CMMSpecialEffect
	BEGIN_SPECIAL_EFFECT_MAP()
		DECLARE_SPECIAL_EFFECT(g_szStandardInternalName, CMMSpecialEffect)
		DECLARE_SPECIAL_EFFECT(g_szSimple3DInternalName, CSimple3DSpecialEffect)
		// *** Add code here to create special effect *** //
	END_SPECIAL_EFFECT_MAP()

	return S_OK;
}

/******************************************************************************
 * Description: IMMSampleTFX Blue property.  Set by Movie Maker from the Blue parameter 
 * value in the XML file in AddOnTFX used to describe the effects and transitions.  
 *
 * float* pfBlue - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
STDMETHODIMP CMMSpecialEffectDXT::get_Blue(float* pfBlue)
{
	RTN_HR_IF_BADPTR(pfBlue);
	*pfBlue = m_fBlueAmount;

	return S_OK;
}

/******************************************************************************
 * Description: IMMSampleTFX Blue property.  Set in the XML file used to describe
 * the effects and transitions.  
 *
 * float fBlueAmount - amount of blue to add to the image.  < 0 is less, 0 > is more.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
STDMETHODIMP CMMSpecialEffectDXT::put_Blue(float fBlueAmount)
{
	m_fBlueAmount = fBlueAmount;

	return S_OK;
}

/******************************************************************************
 * Description: IMMSampleTFX MeltIntensity property.  Set by Movie Maker from the MeltIntensity 
 * value in the XML file in AddOnTFX used to describe the effects and transitions.  
 *
 * float* pfMeltIntensity - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
STDMETHODIMP CMMSpecialEffectDXT::get_MeltIntensity(float* pfMeltIntensity)
{
	RTN_HR_IF_BADPTR(pfMeltIntensity);
	*pfMeltIntensity = m_fMeltIntensity;

	return S_OK;
}

/******************************************************************************
 * Description: IMMSampleTFX MeltIntensity property.  Set in the XML file used to describe
 * the effects and transitions.  
 *
 * float fMeltIntensity - amount of melting to occurr in Melt transition
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
STDMETHODIMP CMMSpecialEffectDXT::put_MeltIntensity(float fMeltIntensity)
{
	m_fMeltIntensity = fMeltIntensity;

	return S_OK;
}

