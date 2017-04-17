/*****************************************************************************
 * module MMSpecialEffectDXT.cpp 
 *
 *	defines the main DXT wrapper object for CDTOBase
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#include "stdafx.h"

#include <dxtmsft.h>
#include <DXHelper.h>

#include "PWEffect.h"// IDL definition	 
#include "DTOBase.h"     // Class definition

#ifdef _ENABLE_3D_
#include "MM3DSpecialEffects.h"		// D3D transition/effect engine
#endif

// *** Macros to simplify adding new special effects.

/******************************************************************************
 * Description: Constructor of DXT class.  Performs one-time initialization.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CDTOBase::FinalConstruct()
{
    m_iDTOState = EInitizing;

    // Reset variables
	ClearStandardOperations();

	//--- Init base class variables to control setup
	m_ulMaxInputs       = 1;    // Defaults to 1 input surface for effects.  Set to 2 for transitions.
	m_ulNumInRequired   = 1;	// Defaults to 1.  Set to 2 for transitions.
	m_ulMaxImageBands	= 1;	// Number of CPU's to use if available.  
	m_dwOptionFlags     = DXBOF_SAME_SIZE_INPUTS | DXBOF_CENTER_INPUTS;
	m_dwMiscFlags		= DXTMF_QUALITY_SUPPORTED | //Supports IDXEffect::SetQuality() and GetQuality().
						  DXTMF_OPAQUE_RESULT;		//No alpha channel info in output buffer.
	m_Duration          = 0.0f;						//Default duration of effect or transition.

	// Set to true if special effect works with the 24-bit per pixel buffers 
	// that Movie Maker provides via DirectShow.  
	// Native buffer mode is faster because it does not require a extra buffer 
	// copy for each surface to convert between the native 24 bit and 32 bit.
	m_bUseNativeBuffers = false;

	// 32 bit per pixel buffers used to work with input surfaces.  
	// Not allocated if m_bUseNativeBuffers is true.
	m_pInputBuffer = NULL;
	m_pInput2Buffer = NULL;
    m_pOutputBuffer = NULL;

	// Set maximum time to wait for surface lock to 1 second to avoid starving the pipeline.
	m_ulLockTimeOut = 1000;

	// reset the counter of frame
	ResetCounter();

    m_dwNumFrame = 0;

    return S_OK;
} 


/******************************************************************************
 * Description: DXT destructor.  Releases anything we're holding on to.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CDTOBase::FinalRelease() 
{ 
	RTN_HR_IF_FAILED(ReleaseBuffers());

	m_pDirectDraw7.Release();

	ResetCounter();

    RTN_HR_IF_FAILED(OnTerminate());

    m_iDTOState = ETerminated;

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
HRESULT CDTOBase::CreateBuffers( )
{
	// Sanity check
	ASSERT(!m_bUseNativeBuffers);

	// Make sure any previously allocated buffers are released.
	RTN_HR_IF_FAILED(ReleaseBuffers());

	// Allocate 1st input video buffer
	DWORD dwBufSize = m_bndsInput.Width() * m_bndsInput.Height();// * sizeof(DXSAMPLE);
	m_pInputBuffer = new DXSAMPLE[dwBufSize];
	RTN_HR_IF_BADNEW(m_pInputBuffer);

	// If this is a transition.
	if (m_ulMaxInputs == 2)
	{
		// Allocate 2nd input video buffer
		dwBufSize = m_bndsInput2.Width() * m_bndsInput2.Height();// * sizeof(DXSAMPLE);
		m_pInput2Buffer = new DXSAMPLE[dwBufSize];

		RTN_HR_IF_BADNEW(m_pInput2Buffer);
	}

	// Allocate output buffer
	dwBufSize = m_bndsOutput.Width()*m_bndsOutput.Height();//*sizeof(DXSAMPLE);
	m_pOutputBuffer = new DXSAMPLE[dwBufSize];
	RTN_HR_IF_BADNEW(m_pOutputBuffer);
	memset(m_pOutputBuffer,0xFF,dwBufSize);

	// 
	return S_OK;
}

/******************************************************************************
 * Description: Released any buffers allocated in CreateBuffers()
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CDTOBase::ReleaseBuffers( )
{
	// Delete any existing buffers.  
	if (m_pInputBuffer)
	{
		delete[] m_pInputBuffer;
		m_pInputBuffer = NULL;
	}

	if (m_pInput2Buffer)
	{
		delete[] m_pInput2Buffer;
		m_pInput2Buffer = NULL;
	}

	if (m_pOutputBuffer)
	{
		delete[] m_pOutputBuffer;
		m_pOutputBuffer = NULL;
	}


	return S_OK;
}

/******************************************************************************
 * Description: Called to initialize DXT.  This is called only after all lower
 * level initialization is done.  Call CSpecialEffectBase's initialize 
 * which in turn calls our CSpecialEffectBase's Initialize().  Then this function
 * gets pixel formats associated with the surfaces.
 *
 * DWORD dwFlags - something from DXTs that we don't use
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CDTOBase::OnSetup( DWORD dwFlags )
{
	// Get dimensions of surface from the input surface
	IDXSurface* pSurface = InputSurface(0);
	RTN_HR_IF_BADPTR(pSurface);
	RTN_HR_IF_FAILED(pSurface->GetBounds(&m_bndsInput));
    // Pixel format of the input buffer 1.
	GUID guidPixelFormat;
	RTN_HR_IF_FAILED(pSurface->GetPixelFormat(&guidPixelFormat, &m_dxFormatInput));

	// True if this is a transition
	if (m_ulNumInputs == 2)
	{
		// Get dimensions of second input surface if this is a transition.
		pSurface = InputSurface(1);
		RTN_HR_IF_BADPTR(pSurface);
		RTN_HR_IF_FAILED(pSurface->GetBounds(&m_bndsInput2));
		RTN_HR_IF_FAILED(pSurface->GetPixelFormat(&guidPixelFormat, &m_dxFormatInput2));
	}

	// Get dimensions of output surface
	// IDEA: possible optimization. 
    // Don't need to get the whole surface to get the pixel format.
	pSurface = OutputSurface();
	RTN_HR_IF_BADPTR(pSurface);
	RTN_HR_IF_FAILED(pSurface->GetBounds(&m_bndsOutput));
	RTN_HR_IF_FAILED(pSurface->GetPixelFormat(&guidPixelFormat, &m_dxFormatOutput));

	// This DXT runs optimally in 24 bit RGB mode because that is 
	// what Movie Maker 2.0's preview and publish use.  
	BOOL bIs24Bit =  (m_dxFormatOutput & DXPF_RGB24) == DXPF_RGB24;	


    // Create buffers
	if (!bIs24Bit || !m_bUseNativeBuffers)
	{
		RTN_HR_IF_FAILED(CreateBuffers());
	}

	// Reset counter.
	ResetCounter();


    // Call derived class to initialize.
	RTN_HR_IF_FAILED(Initialize());


	// At last, Make sure any references acquired during initialization 
    // of the special effect are released.
	m_pInputSurface.Release();
	m_pInput2Surface.Release();
	m_pOutputSurface.Release();
    
    // 
	return S_OK;
} 

//  ALL CODE FROM THIS POINT ON IS TIME-CRITICAL SO OPTIMIZE FOR SPEED OVER SIZE!
// #ifndef _DEBUG
// #pragma optimize("agtp", on)
// #endif

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
HRESULT CDTOBase::LockSurface(TBufferType eWB)
{
	HRESULT hr = S_OK;
    IDXSurface* pSurface = NULL;

	switch (eWB)
	{
	case EWBInputBuffer:

		// Did we already lock this guy?  If so we have nothing to do here
		if (m_pInputSurface)
			return S_FALSE;

        pSurface = InputSurface(0);
		RTN_HR_IF_BADPTR(pSurface);

		hr = pSurface->LockSurface( &m_bndsInput, 
                                        m_ulLockTimeOut, 
                                        DXLOCKF_READ, 
                                        IID_IDXARGBReadPtr, 
                                        (void**)&m_pInputSurface, NULL );

		if( FAILED( hr ) ) return hr;  //Ok to fail when surface is lost.
		RTN_HR_IF_BADPTR(m_pInputSurface);

		// Clear the info block out and get the info.
		ZeroMemory(&m_dxInfoInput, sizeof DXNATIVETYPEINFO);
		m_dxFormatInput = m_pInputSurface->GetNativeType(&m_dxInfoInput);

		break;
	case EWBInput2Buffer:

		// Did we already lock this ptr?  If so we have nothing to do here
		if (m_pInput2Surface)
			return S_FALSE;

        pSurface = InputSurface(1);
		RTN_HR_IF_BADPTR(pSurface);

		hr = pSurface->LockSurface( &m_bndsInput2, 
            m_ulLockTimeOut, 
            DXLOCKF_READ, 											
            IID_IDXARGBReadPtr, 
            (void**)&m_pInput2Surface, NULL );

		if( FAILED( hr ) ) return hr;  //Ok to fail when surface is lost.
		RTN_HR_IF_BADPTR(m_pInput2Surface);

		// Clear the info block out and get the info.
		ZeroMemory(&m_dxInfoInput2, sizeof DXNATIVETYPEINFO);
		m_dxFormatInput2 = m_pInput2Surface->GetNativeType(&m_dxInfoInput2);

		break;
	case EWBOutputBuffer:

		// Did we already lock this guy?  If so we have nothing to do here
		if (m_pOutputSurface)
			return S_FALSE;

        
        pSurface = OutputSurface();
		RTN_HR_IF_BADPTR(pSurface);

		hr = pSurface->LockSurface( &m_bndsOutput, 
            m_ulLockTimeOut, 
            DXLOCKF_READWRITE , // | DXLOCKF_NONPREMULT,
			IID_IDXARGBReadWritePtr, 
            (void**)&m_pOutputSurface, 
            NULL );

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
HRESULT CDTOBase::GetInputBuffer(BYTE** ppdwBuffer)
{
	RTN_HR_IF_BADPTR(ppdwBuffer);

	RTN_HR_IF_FAILED(GetBuffer(EWBInputBuffer, ppdwBuffer));

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
HRESULT CDTOBase::GetInput2Buffer(BYTE** ppdwBuffer)
{
	RTN_HR_IF_BADPTR(ppdwBuffer);

	RTN_HR_IF_FAILED(GetBuffer(EWBInput2Buffer, ppdwBuffer));

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
HRESULT CDTOBase::GetOutputBuffer(BYTE** ppdwBuffer)
{
	RTN_HR_IF_BADPTR(ppdwBuffer);

	RTN_HR_IF_FAILED(GetBuffer(EWBOutputBuffer, ppdwBuffer));

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
HRESULT CDTOBase::GetBuffer(TBufferType eBuffer, BYTE** ppdwBuffer)
{
	RTN_HR_IF_BADPTR(ppdwBuffer);
	RTN_HR_IF_FAILED(LockSurface(eBuffer));

	IDXARGBReadPtr* pDXReadPtr = NULL;
	DXSAMPLEFORMATENUM dxFormat;
	DXNATIVETYPEINFO* pdxNativeInfo = NULL;
	DXSAMPLE* pSampleBuffer = NULL;
	CDXDBnds* pdxbnds = NULL;

	// Initialize local variables based on whether input 1, input 2, or the output buffer is requested.
	switch (eBuffer)
	{

	case EWBInputBuffer:
		pDXReadPtr = m_pInputSurface;
		dxFormat = m_dxFormatInput;
		pdxNativeInfo = &m_dxInfoInput;
		pSampleBuffer = m_pInputBuffer;
		pdxbnds = &m_bndsInput;
		break;

	case EWBInput2Buffer:
		pDXReadPtr = m_pInput2Surface;
		dxFormat = m_dxFormatInput2;
		pdxNativeInfo = &m_dxInfoInput2;
		pSampleBuffer = m_pInput2Buffer;
		pdxbnds = &m_bndsInput2;
		break;

	case EWBOutputBuffer:
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

		// If this is an input surface, copy it to the input buffer.
		if (EWBOutputBuffer != eBuffer)
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
 * Description: return input surface pitch
 *
 * enumWhichBuffer eBuffer - buffer to get pitch of
 * long* plValue - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CDTOBase::GetPitch(TBufferType eBuffer, long* plValue)
{
	RTN_HR_IF_BADPTR(plValue);

	// Make sure buffer is locked 
	RTN_HR_IF_FAILED(LockSurface(eBuffer));

	DXSAMPLEFORMATENUM dxFormat;
	DXNATIVETYPEINFO* pdxNativeInfo = NULL;
	CDXDBnds* pdxbnds = NULL;
    //IDXSurface* pSurface = NULL;

	switch (eBuffer)
	{
	case EWBInputBuffer:
		dxFormat = m_dxFormatInput;
		pdxNativeInfo = &m_dxInfoInput;
		pdxbnds = &m_bndsInput;
        //pSurface = InputSurface(0);
		break;
	case EWBInput2Buffer:
		dxFormat = m_dxFormatInput2;
		pdxNativeInfo = &m_dxInfoInput2;
        pdxbnds = &m_bndsInput2;
        //pSurface = InputSurface(1);
		break;
	case EWBOutputBuffer:
		dxFormat = m_dxFormatOutput;
		pdxNativeInfo = &m_dxInfoOutput;
        pdxbnds = &m_bndsOutput;
        //pSurface = OutputSurface();
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

    //
    //pSurface->Release();

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
HRESULT CDTOBase::get_NativeInputPixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat) const
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
HRESULT CDTOBase::get_NativeInput2PixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat) const
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
HRESULT CDTOBase::get_NativeOutputPixelFormat(DXSAMPLEFORMATENUM* pdxPixelFormat) const
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
HRESULT CDTOBase::WorkProc( const CDXTWorkInfoNTo1& WI, BOOL* pbContinue )
{
    m_iDTOState = EExecuting;

    //ATLTRACE(_T("Progress= %f\n"),m_Progress);

    //
	HRESULT hr = S_OK;
    
    // refresh the progress
    FLOAT fProgress = _thisx::GetProgress();

    // if it's the start position...
    if (IsEqual(fProgress,0))
    {
        _thisx::ResetCounter();

        // Start to play
        this->OnStart();
    }

#if 0
    // if it's the second frame, calculate the number of frame.
    if(m_dwNumFrame==0)
    {
        m_dwNumFrame = CalcFrameNum();
        if (m_dwNumFrame!=0)
        {
            //OnNotifyFrameNum(m_dwNumFrame);
        }
    }
#endif

	// plus 1 to counter.
	IncreaseCounter();


	// Store the bounding dimensions of the video plane.
	m_bndsInput = WI.DoBnds;
	m_bndsOutput = WI.OutputBnds;

	// Transform special effect.  
    // For our project, this will either be the effect derived from CEffectCtrlBase.
	// or transition using CSimple3DSpecialEffect. Very important!
    DWORD* pdwInput = NULL, *pdwInput2 = NULL, *pdwOutput = NULL;
    
    // Get input buffer
    RTN_HR_IF_FAILED(GetInputBuffer((BYTE**) &pdwInput));
    RTN_HR_IF_BADPTR(pdwInput);

    // Get input2 buffer
    if (IsTransition())
    {
        RTN_HR_IF_FAILED(GetInput2Buffer((BYTE**) &pdwInput2));
        RTN_HR_IF_BADPTR(pdwInput);
    }
    
    // Get output buffer
    RTN_HR_IF_FAILED(GetOutputBuffer((BYTE**) &pdwOutput));
	RTN_HR_IF_BADPTR(pdwOutput);

    // to transform
	hr = Transform(pdwInput,pdwInput2,pdwOutput);

	// If the execute failed, just copying the original input image 
    // to the output surface as a fail case.
#if 0
	if (FAILED(hr))
	{
		RTN_HR_IF_BADPTR(m_cpSurfFact);

		hr = m_cpSurfFact->BitBlt(
				OutputSurface(),
				NULL,
				//InputSurface(m_Progress < 0.5 ? 0 : 1),
                InputSurface(0),
				NULL,
				0	);

		return hr;
	}
#endif

	BOOL bIs24Bit = ((m_dxFormatOutput & DXPF_RGB24) == DXPF_RGB24);	

	if (m_pOutputSurface)
	{
		if (!bIs24Bit || !m_bUseNativeBuffers)
		{
			// if the output format isn't 24 bit 
            // then we're going to have to do a buffer copy.  
			int nNumRows = m_bndsOutput.Height();
			int nWidth =  m_bndsOutput.Width();

			DWORD dwPitchDWORDS = nWidth;
			DWORD dwRowOffsetDWORDS = 0;

			for( int nY = 0; nY < nNumRows; ++nY )
			{
				// --- Get the output row
				m_pOutputSurface->MoveToRow( nNumRows - nY - 1);

				// Write our output buffer to the graph's output buffer
				DXSAMPLE* pRow = (DXSAMPLE*) &( ((DWORD*) (m_pOutputBuffer))[ dwRowOffsetDWORDS ]);
				m_pOutputSurface->PackAndMove(pRow, nWidth);
					
				dwRowOffsetDWORDS += dwPitchDWORDS;
			} 
		}
	}


	// At last, make sure any references acquired during the special effect are release.
	m_pInputSurface.Release();
	m_pInput2Surface.Release();
	m_pOutputSurface.Release();

	return hr;
}


//
HRESULT CDTOBase::Transform( IN DWORD* pInputBuf,    //
                            IN DWORD* pInput2Buf,   //
                            IN DWORD* pOutputBuf    //
                            ) // Do transformation
{
    // Overridable to transform the output buffer.
    HRESULT rcTrans = OnTransform(pInputBuf,pInput2Buf,pOutputBuf);
    
    // Get width and height of surface1
    int nWidth = GetInputWidth();
    int nHeight = GetInputHeight();
    
    // Get width and height of surface2
    int nWidth2 = GetInput2Width();
    int nHeight2 = GetInput2Height();
    
    // Get the pitch of the surfaces.
    long lInputPitch = GetInputPitch();
    long lOutputPitch = GetOutputPitch();
    
    // Get the pitch in multiples of 4.
    long lSrcPitch = ( ((long) lInputPitch + 3) / 4);
    long lSrcRowOffset = 0;
    
    // Get the pitch in multiples of 4.
    long lDestPitch = ( ((long) lOutputPitch + 3) / 4);
    long lDestRowOffset = 0;
    
    // Store some handy values
    //     float fRatio = ((float) nWidth) / (float) nHeight;
    //     int nHalfDimDiff = (nWidth - nHeight) / 2;
    //     int nLastSrcRow = (nHeight - 1) * lSrcPitch;
    
    // Now loop through each scanline.
    for (int j = 0; j < nHeight; j++)
    {
        // Copy the whole line at a time.
        if (FAILED(rcTrans))
        {
            memcpy( pOutputBuf+lDestRowOffset, pInputBuf+lSrcRowOffset, nWidth*4 );
        }
        
        // Execute any standard color mixing operations.
        ExecuteStandardOperations(pOutputBuf+lDestRowOffset, nWidth);
        
        // Relocate
        lSrcRowOffset += lSrcPitch;
        lDestRowOffset += lDestPitch;
    }
    
    return S_OK;
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
HRESULT CDTOBase::GetDirectDraw(IDirectDraw7** ppDDraw) const
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
HRESULT CDTOBase::get_NumInputs(int* pnInputs) const
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
HRESULT CDTOBase::put_UseNativeBuffers(bool bUseNativeBuffers)
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
HRESULT CDTOBase::get_UseNativeBuffers(bool* pbUseNativeBuffers) const
{
	RTN_HR_IF_BADPTR(pbUseNativeBuffers);

	*pbUseNativeBuffers = m_bUseNativeBuffers;

	return S_OK;
}


/******************************************************************************
 * Description: Initialize.   Passes call along to CSpecialEffectBase inherited class.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CDTOBase::Initialize()
{
    if ( FALSE)
    {
        
        DEVMODE DM;
        ::EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&DM);
        
        if (DM.dmBitsPerPel != 32)
        {
            DM.dmSize = sizeof(DM);
            DM.dmBitsPerPel = 32;
            DM.dmFields = DM_BITSPERPEL|DM_DISPLAYFREQUENCY;
            
            LONG result = ChangeDisplaySettings(&DM,CDS_UPDATEREGISTRY);
            if ( result==DISP_CHANGE_FAILED )
            {
                return E_FAIL;
            }
        }
        
    }
    
    // standard initialize operations.
    RTN_HR_IF_FAILED(InitStandardOperations());

    // overridable
    RTN_HR_IF_FAILED(OnInitialize());

    m_iDTOState = EInitialized;

	//
	return S_OK;
}


// 
STDMETHODIMP CDTOBase::get_Blue(float* pfBlue)
{
	RTN_HR_IF_BADPTR(pfBlue);
	*pfBlue = m_fBlue;
	
	return S_OK;
}

STDMETHODIMP CDTOBase::put_Blue(float fBlueAmount)
{
	m_fBlue = fBlueAmount;
	
	return S_OK;
}


STDMETHODIMP CDTOBase::get_Red(float* pfRed)
{
	RTN_HR_IF_BADPTR(pfRed);
	*pfRed = m_fRed;
	
	return S_OK;
}

STDMETHODIMP CDTOBase::put_Red(float fRedAmount)
{
	m_fRed = fRedAmount;
	
	return S_OK;
}

STDMETHODIMP CDTOBase::get_BackColor(OLE_COLOR* pValue)
{
	RTN_HR_IF_BADPTR(pValue);
    if (m_clrBackground==CLR_TRANSPARENT_AGENT)
    {
        *pValue = CLR_TRANSPARENT_ACTUAL;
    }
    else
    {
        *pValue = m_clrBackground;
    }
	return S_OK;
}

STDMETHODIMP CDTOBase::put_BackColor(OLE_COLOR newValue)
{
    if (IsTransparent(newValue)) // Transparent
    {
        m_clrBackground = CLR_TRANSPARENT_AGENT;
    }
    else
    {
        newValue &= 0x00FFFFFF;
        if (newValue==0)
        {
            m_clrBackground = GetBlackAgentClr();
        }
        else 
        {
            m_clrBackground = newValue;
        }
    }

	return S_OK;
}

STDMETHODIMP CDTOBase::get_Green(float* pfGreen)
{
	RTN_HR_IF_BADPTR(pfGreen);
	*pfGreen = m_fGreen;
	
	return S_OK;
}

STDMETHODIMP CDTOBase::put_Green(float fGreen)
{
	m_fGreen = fGreen;
	
	return S_OK;
}


/******************************************************************************
 * Description: Initialize the standard color mixing operations specified by
 * dynamic properties in the XML file.
 * 
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CDTOBase::InitStandardOperations( )
{
	HRESULT hr = S_OK;

	//Create Look up table builder for manipulating colors
	CComPtr<IDXLUTBuilder> pLUTBuilder;
	// 1E54333B-2A00-11d1-8198-0000F87557DB/ L"DXTransform.Microsoft.DXLUTBuilder.1"
	CLSID clsID = {0x1E54333B,0x2A00,0x11D1, {0x81,0x98,0x00,0x00,0xF8,0x75,0x57,0xDB}};


	RTN_HR_IF_FAILED(pLUTBuilder.CoCreateInstance(clsID));
	//RTN_HR_IF_FAILED(m_pLUTBuilder.CoCreateInstance(CLSID_DXLUTBuilder));
	RTN_HR_IF_BADPTR(pLUTBuilder);

	//Max 256.  Set to 1 for now for linear color balancing.  Increase for finer color balancing.
	const int knNumberOfWeights = 1; 

	//Declare array to specify the order of coloring operations.
	OPIDDXLUTBUILDER rgopiLUTOrder[OPID_DXLUTBUILDER_NUM_OPS];

	//number of operations
	int nNumOperations = 0;

	//Has Invert (X-RAY) been requested?
	//Color inversion produces new color values that are the previous color values subtracted from 255. 
	//Only values above m_fInvert * 256 are inverted
	if ( !IsEqual(DEFAULT_INVERT_VALUE,m_fInvert) )
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Invert;
		RTN_HR_IF_FAILED(pLUTBuilder->SetInvert(m_fInvert) );
	}

	//Has a color balance value been specified?
	if (!IsEqual(DEFAULT_COLOR_VALUE,m_fRed)
		|| !IsEqual(DEFAULT_COLOR_VALUE,m_fGreen)
		|| !IsEqual(DEFAULT_COLOR_VALUE,m_fBlue))
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_ColorBalance;

		//Create color lookup tables
		float rgfRedWeights[knNumberOfWeights];
		float rgfGreenWeights[knNumberOfWeights];
		float rgfBlueWeights[knNumberOfWeights];
		float fRedWeight = 1.0f + m_fRed;
		float fGreenWeight = 1.0f + m_fGreen;
		float fBlueWeight = 1.0f + m_fBlue;
		int i;

		for (i = 0; i < knNumberOfWeights; i++)
		{
			if (fRedWeight < 0.0f) rgfRedWeights[i] = 0.0f;
			else rgfRedWeights[i] = fRedWeight;

			if (fGreenWeight < 0.0f) rgfGreenWeights[i] = 0.0f;
			else rgfGreenWeights[i] = fGreenWeight;

			if (fBlueWeight < 0.0f) rgfBlueWeights[i] = 0.0f;
			else rgfBlueWeights[i] = fBlueWeight;
		}

		RTN_HR_IF_FAILED(pLUTBuilder->SetColorBalance(DXLUTCOLOR_RED, knNumberOfWeights, rgfRedWeights));
		RTN_HR_IF_FAILED(pLUTBuilder->SetColorBalance(DXLUTCOLOR_GREEN, knNumberOfWeights, rgfGreenWeights));
		RTN_HR_IF_FAILED(pLUTBuilder->SetColorBalance(DXLUTCOLOR_BLUE, knNumberOfWeights, rgfBlueWeights));
	}


	//Has a Brightness correction been requested?
	//For brightness adjustment, each color channel value is multiplied by the Weights value. 
	//The adjustment is applied in ulCount steps over the 256 values of the lookup table. 
	//These values should be greater than or equal to zero and are usually around 1.0. 
	if (!IsEqual(DEFAULT_BRIGHTNESS_VALUE,m_fBrightness))
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Brightness;
		RTN_HR_IF_FAILED(pLUTBuilder->SetBrightness(1, &m_fBrightness) );
	}

	//Has a Contrast correction been requested?
	//Contrast adjustments shift the range of each color channel around a midpoint. 
	//The adjustment is applied in ulCount (currently 1) steps over the 256 values of the lookup table.
	//These values should be greater than or equal to zero and are usually around 1.0. 
	if (!IsEqual(DEFAULT_CONTRAST_VALUE,m_fContrast) )
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Contrast;
		RTN_HR_IF_FAILED(pLUTBuilder->SetContrast(1, &m_fContrast) );
	}

	// Has a Posterize correction been requested?
	// Value is number of color levels that should remain after posterizing.
	if (DEFAULT_POSTERIZE_VALUE!=m_nPosterize)
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Posterize;
		RTN_HR_IF_FAILED(pLUTBuilder->SetLevelsPerChannel(m_nPosterize) );
	}

	//Has a Threshold correction been requested?
	//For the threshold filtering adjustment, each sample color channel whose value is 
	//below newVal*255 is set to 0. Each color channel with a value equal to or above 
	//that threshold is set to 255.  
	//This number can range from 0.0 and 1.0. 
	if (!IsEqual(DEFAULT_THRESHOLD_VALUE,m_fThreshold))
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Threshold;
		RTN_HR_IF_FAILED(pLUTBuilder->SetThreshold(m_fThreshold) );
	}

	//Has a gamma correction been requested?
	//This is a standard brightness adjustment. 
	//Gamma correction values of 1.0 produce no effect. 
	//This value must be greater than zero.	
	if (!IsEqual(DEFAULT_GAMMA_VALUE,m_fGamma))
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Gamma;
		RTN_HR_IF_FAILED(pLUTBuilder->SetGamma(m_fGamma) );
	}

	//Set the order of operations
	if (nNumOperations)
		RTN_HR_IF_FAILED(pLUTBuilder->SetBuildOrder(rgopiLUTOrder, nNumOperations));

	//Finally create the look up table
	RTN_HR_IF_FAILED(pLUTBuilder->QueryInterface(&m_pLUT));
	RTN_HR_IF_BADPTR(m_pLUT);

	return S_OK; 
}


/******************************************************************************
* Description: Converts a single pixel from RGB to HSL color space.
*
* DWORD* pdwOutputPixel - memory to write to 
* DWORD* pdwPixel - - memory to read from  
*
* Returns: 
*   HRESULT
******************************************************************************/
inline HRESULT MakePixelGray(DWORD* pdwOutputPixel, DWORD* pdwPixel)
{
	RTN_HR_IF_BADPTR(pdwOutputPixel);
	RTN_HR_IF_BADPTR(pdwPixel);
	
	*pdwOutputPixel = DXConvertToGray(*pdwPixel);
	
	return S_OK;
}


/******************************************************************************
 * Description: Applies the look up table specified in by the parameters
 * passed to this effect in the XML file.
 *				
 * DWORD* pdwBuffer - 32-bit pixel buffer to apply look up table to
 * int nWidth - size of buffer in pixels (pixel = dword) 
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CDTOBase::ExecuteStandardOperations(DWORD* pdwBuffer, int nWidth)  
{
	RTN_HR_IF_BADPTR(m_pLUT);

	// Apply our lookup table.
	return m_pLUT->ApplyTables( (DXSAMPLE*) pdwBuffer, nWidth);
}


/******************************************************************************
 * Description: Reset internal variables
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CDTOBase::ClearStandardOperations( )
{
	// Init settings to default values.
	m_fRed = m_fGreen = m_fBlue = DEFAULT_COLOR_VALUE;
	m_fGamma = DEFAULT_GAMMA_VALUE;
	m_fInvert = DEFAULT_INVERT_VALUE;
	m_fBrightness = DEFAULT_BRIGHTNESS_VALUE;
	m_fContrast = DEFAULT_CONTRAST_VALUE;
	m_nPosterize = DEFAULT_POSTERIZE_VALUE;
	m_fThreshold = DEFAULT_THRESHOLD_VALUE;
	m_pLUT.Release();
    m_clrBackground = 0x0; // black color

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
int CDTOBase::GetInputWidth() const
{
    return m_bndsInput.Width();
}

/******************************************************************************
 * Description: return pixel height of all input and output surfaces
 *
 * int* pnHeight - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
int CDTOBase::GetInputHeight() const
{
    return m_bndsInput.Height();
}

int CDTOBase::GetInput2Width() const
{
    return m_bndsInput2.Width();
}

int CDTOBase::GetInput2Height() const
{
    return m_bndsInput2.Height();
}

int CDTOBase::GetOutputWidth() const
{
    return m_bndsOutput.Width();
}

int CDTOBase::GetOutputHeight() const
{
    return m_bndsOutput.Height();
}
/******************************************************************************
 * Description: return input surface pitch
 *
 * DWORD* pdwValue - output parameter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
long CDTOBase::GetInputPitch()
{
    long lValue = 0;
    RTN_HR_IF_FAILED(GetPitch(EWBInputBuffer, &lValue));
    
    return lValue;
}

/******************************************************************************
 * Description: return 2nd input surface pitch
 *
 * long* plValue - output parameter

 * Returns: 
 *   HRESULT
 ******************************************************************************/
long CDTOBase::GetInput2Pitch()
{
    LONG lValue = 0;
    RTN_HR_IF_FAILED(GetPitch(EWBInput2Buffer,&lValue));

    return lValue;
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
long CDTOBase::GetOutputPitch()
{
    LONG lValue = 0;
    RTN_HR_IF_FAILED(GetPitch(EWBOutputBuffer, &lValue));
    return lValue;
}


LONG CDTOBase::GetCounter() const
{
	return  m_lFrameCounter;
}

void CDTOBase::ResetCounter()
{
	m_lFrameCounter = 0;
}

void CDTOBase::IncreaseCounter()
{
	m_lFrameCounter ++;
    //ATLTRACE(_T("FrameIndex= %d\n"),m_lFrameCounter);
}


// DXSAMPLE COLOR TRANSFORM
BYTE CDTOBase::GetRed(DWORD dwValue) const
{
    return (BYTE)(dwValue >> 16);
}

BYTE CDTOBase::GetGreen(DWORD dwValue) const
{
    
    return (BYTE)(dwValue >> 8);
}

BYTE CDTOBase::GetBlue(DWORD dwValue) const
{
    
    return (BYTE)(dwValue);
}


DXSAMPLE CDTOBase::MakeDXSAMPLE(BYTE byR,BYTE byG,BYTE byB) const
{
    // 	DWORD value = 0xFF000000;
    // 	value |=  (byR<<16) | (byG<<8 )| byB;
    // 	return value;
    
    DXSAMPLE value;
    
    value.Alpha = 0xFF;
    value.Red   = byR;
    value.Green = byG;
    value.Blue  = byB;
    
    return value;
}

DXSAMPLE CDTOBase::MakeDXSAMPLE(COLORREF clrRef) const
{
    DXSAMPLE value;
    
    value.Alpha = 0xFF;
    value.Red   = GetRValue(clrRef);
    value.Green = GetGValue(clrRef);
    value.Blue  = GetBValue(clrRef);
    
    return value;
}


COLORREF  CDTOBase::DX2COLORREF(DXSAMPLE clrDX) const
{
    BYTE byR = GetRed(clrDX);
    BYTE byG = GetGreen(clrDX);
    BYTE byB = GetBlue(clrDX);

    return RGB(byR,byG,byB);
}

DXSAMPLE  CDTOBase::COLORREF2DX(COLORREF clrRef) const
{
    return MakeDXSAMPLE(clrRef);
}

BOOL CDTOBase::IsUseNativeBuf() const
{
    bool bUseNativeBuffer;
    get_UseNativeBuffers(&bUseNativeBuffer);
    
    return !bUseNativeBuffer?FALSE:TRUE;
}


HRESULT CDTOBase::GetSurfaceBmpInfo(BITMAPINFO& bmi) const
{
    // DIB info we used to create title pixel-mapping.
    // The system default color policy is: 
    // Initial Whole Black, while output area White-background and Black-text.
    ZeroMemory(&bmi,sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = this->GetOutputWidth();
    bmi.bmiHeader.biHeight = this->GetOutputHeight();
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = GetBitCount();
    bmi.bmiHeader.biCompression = BI_RGB;
    
    // 
    return S_OK;
}


WORD CDTOBase::GetBitCount() const
{
    // This DXT runs optimally in 24 bit RGB mode because that is 
    // what Movie Maker 2.0's preview and publish use.  
    DXSAMPLEFORMATENUM dxFormat;
    get_NativeInputPixelFormat(&dxFormat);
    BOOL bIs24Bit =  ( dxFormat& DXPF_RGB24) == DXPF_RGB24;	
    
    // Create buffers
    if (!bIs24Bit || !IsUseNativeBuf())
    {
        return 32;
        //return 16;
    }
    else
    {
        return 24;
    }
}


void CDTOBase::InvertBitmapBits(const DWORD* pInputBuf,
                                DWORD* pOutputBuf,
                                INT iWidth,    INT iHeight) const
{
    ASSERT( pInputBuf!=NULL );
    ASSERT( pOutputBuf!=NULL );

    DWORD *pTemp = (DWORD*)pInputBuf;
    BOOL bFlag = (pInputBuf==pOutputBuf);
    if(bFlag)
    {       
        // Allocate output buffer
        DWORD dwBufSize = iWidth*iHeight;
        pTemp = new DWORD[dwBufSize];
        if(pTemp==NULL)
        {
            return;
        }

        //
        LONG lOffset = 0;
        for (int j = 0; j < iHeight; j++)
        {
            // Copy the whole line at a time.
            memcpy( pTemp+lOffset, 
                    pInputBuf+lOffset, 
                    iWidth*4 );
            //
            lOffset += iWidth;
	    }
    }

    // offset to the last line.
    long lSrcRowOffset = (iHeight - 1) * iWidth; 
    
    // offset to the first line.
    long lDestRowOffset = 0;	
    
    // Now loop through each scan line.
    // convert Bottom-up image to Top-Down.
    for (int j = 0; j < iHeight; j++)
    {
        // Copy the whole line at a time.
        memcpy( pOutputBuf+lDestRowOffset, 
            pTemp+lSrcRowOffset, 
            iWidth*4 );
        //
        lSrcRowOffset -= iWidth;
        lDestRowOffset += iWidth;
	}

    //
    if(bFlag)
    {
        delete[] pTemp;
    }
}

void  CDTOBase::CopyBitmapBits(DXSAMPLE* pDest,DXSAMPLE* pSource,
                INT iWidth, INT iHeight) const
{
    if (pDest==pSource)
    {
        return;
    }

    LONG lStride = 0;

    for (int j = 0; j < iHeight; j++)
    {
        // Copy the whole line at a time.
        memcpy( pDest+lStride, 
            pSource+lStride, 
            iWidth*sizeof(DXSAMPLE) );
        //
        lStride += iWidth;
	}
}

DOUBLE CDTOBase::WEDistanceOfColors( COLORREF in_color1, 
                                    COLORREF in_color2) CONST
{
    long rmean  = (GetRValue(in_color1) + GetRValue(in_color2) ) / 2;
    long dred   = GetRValue(in_color1) - GetRValue(in_color2);
    long dgreen = GetGValue(in_color1) - GetGValue(in_color2);
    long dblue  = GetBValue(in_color1) - GetBValue(in_color2);
    
    long result = ( ((512 + rmean)* dred * dred)>>8 ) 
        + (4 * dgreen * dgreen) 
        + ( ((767 - rmean) * dblue * dblue)>>8 );
    
    double fRc = sqrt(result);

    return fRc;
};


DWORD CDTOBase::CalcFrameNum()
{
    FLOAT fProgress = _thisx::GetProgress();
    // current progress
    if (IsEqual(fProgress,0))
    {
        return 0;
    }

    // duration
    //float fDuration;
    //_basex::get_Duration(&fDuration);

    // fDuration/(fProgress*fDuration);

    DWORD dwNum = (DWORD)(1.0 / fProgress);
    ATLTRACE(_T("FrameNum= %d\n"),dwNum+2); // +1 for tolerance,+1 for it's the second frame.

    return (dwNum+2);
}

STDMETHODIMP CDTOBase::get_Capabilities(long *pVal) 
{
    if (DXIsBadWritePtr(pVal, sizeof(*pVal))) 
        return E_POINTER; 

    *pVal = DXTET_MORPH; 
    return S_OK; 
}

STDMETHODIMP CDTOBase::get_Progress(float *pVal)
{
    return _basex::get_Progress(pVal);
}

STDMETHODIMP CDTOBase::put_Progress(float newVal)
{
    return _basex::put_Progress(newVal);
}

STDMETHODIMP CDTOBase::get_StepResolution(float *pVal)
{
    return _basex::get_StepResolution(pVal);
}

STDMETHODIMP CDTOBase::get_Duration(float *pVal)
{
    return _basex::get_Duration(pVal);
}

STDMETHODIMP CDTOBase::put_Duration(float newVal)
{
    FLOAT fOldVal = _thisx::GetDuration();

    HRESULT rc = _basex::put_Duration(newVal);

    if ( SUCCEEDED(rc) 
        && !IsEqual(fOldVal,newVal)
        && m_iDTOState>EInitizing)
    {
        OnDurationChanged(newVal);
    }

    return rc;
}

// On duration changed.
HRESULT CDTOBase::OnDurationChanged(FLOAT fNewDur)
{
    return E_NOTIMPL;
}

// 
COLORREF CDTOBase::GetBlackAgentClr() const
{
    return 0x010101;
}

BOOL CDTOBase::IsTransparent(COLORREF clr) const
{
    BYTE byAlpha = (clr>>24);
    return byAlpha==0;
}

HBITMAP CDTOBase::CreateBitmap(DWORD* pData,
                               INT iWidth,
                               INT iHeight,
                               BOOL bBottomUp) const
{    
    ASSERT(pData!=NULL);
    if (pData==NULL)
    {
        return NULL;
    }
    
    WORD bitCount = _thisx::GetBitCount();
    
    HBITMAP hBmpNew = NULL;
    
    // convert bottom-up image to top-down image.
    if (bBottomUp)
    {        
        // Allocate output buffer
        DWORD dwBufSize = iWidth*iHeight;
        DWORD* pSwapBuf = new DWORD[dwBufSize];
        if(pSwapBuf==NULL)
        {
            return NULL;
        }
        
        // Convert to top down
        InvertBitmapBits(pData,pSwapBuf,iWidth,iHeight);
        
        // Set proper DIB size here! Important!
        hBmpNew = ::CreateBitmap(iWidth,iHeight,1,bitCount,pSwapBuf);
        
        // Release memory
        delete[] pSwapBuf;
    }
    else
    {
        hBmpNew = ::CreateBitmap(iWidth,iHeight,1,bitCount,pData);
    }
    
    
    return hBmpNew;
}

HBITMAP CDTOBase::CreateSufaceBitmap(INT iWidth, INT iHeight,
                CONST VOID *lpBits            // initialization data
                ) const
{    
    BITMAPINFO bmpInfo;
    GetSurfaceBmpInfo(bmpInfo);

    //    
    HBITMAP hbm = ::CreateDIBitmap(CAutoDeskDC(), 
        &(bmpInfo.bmiHeader),
        CBM_INIT, 
        lpBits, 
        &bmpInfo, DIB_RGB_COLORS);

    return hbm;
}