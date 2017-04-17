
/*****************************************************************************
 * module MM3DSpecialEffects.cpp 
 *
 *	implements basic classes for 3D special effects
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#define _USE_MATH_DEFINES
#include "stdafx.h"

#include "MM3DSpecialEffects.h"
#include "MMSpecialEffectDXT.h"
#include <math.h>

// *** ALL CODE IN THIS FILE IS TIME-CRITICAL SO OPTIMIZE FOR SPEED OVER SIZE! *** //
#ifndef _DEBUG
#pragma optimize("agtp", on)
#endif

//Handy Identity matrix.  Initialized in C3DSpecialEffect constructor.
D3DXMATRIX g_matIdentity;

/******************************************************************************
/* C3DSpecialEffect implementation 
/*****************************************************************************/

/******************************************************************************
 * Description: constructor
 *
 * CMMSpecialEffectDXT* pBase - back pointer to container.
 * LPCTSTR szInternalName - internal name of effect.  From mapping in FilterBase::CreateSpecialEffectByName().
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
CMM3DSpecialEffect::CMM3DSpecialEffect(CMMSpecialEffectDXT* pDXT, LPCTSTR szName) 
	: CMMSpecialEffect(pDXT, szName)
{
	//Clear variables
	m_pDD          = NULL;
	m_pD3DDevice   = NULL;
	m_fFirstTime	= true;
	m_bReady		= false;
	m_fDeviceHasAlphablending = false;
	m_bUseZBuffer = false;
	m_fltQualityFactor = 1.0f;
	
	//Set field of view
	m_fFov          = FIELD_OF_VIEW_ANGLE;

	//Clear indentity matrix
	D3DXMatrixIdentity(&g_matIdentity);

	//Clear structures
	ZeroMemory(&m_descD3DDevice, sizeof D3DDEVICEDESC7);
}

/******************************************************************************
 * Description: Initialize handler.  Gets Hue value from XML file.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::Initialize( )
{
	RTN_HR_IF_FAILED(_SEBaseClass::Initialize( ));

	//In case we're already been initalized, release everything.
	if (!m_fFirstTime)
	{
		RTN_HR_IF_FAILED(Terminate());
	}

	//Create precision frame timer
	m_pFrameTimer = new CFrameTimer();
	RTN_HR_IF_BADNEW(m_pFrameTimer);

	//Set timer for 30 frames per second for publish and 15 FPS for preview
	//TODO: For PAL use 12.5 FPS for preview and 25 for publish.
	(void)m_pFrameTimer->Start( (m_fltQualityFactor > 0.5) ? 30.0f : 15.0f);

	//Do our one time initialization
	m_fFirstTime = false;

	//Set various mathematical settings
	RTN_HR_IF_FAILED(ResetCameraVectors());

	//Create D3D, the scene, and the geometry buffers.
	RTN_HR_IF_FAILED(CreateContext());
	RTN_HR_IF_FAILED(CreateScene());
	RTN_HR_IF_FAILED(CreateSurfaces());

	//Get dimensions of video buffers in pixels
	int nWidth, nHeight;

	RTN_HR_IF_BADPTR(m_pDXT);
	RTN_HR_IF_FAILED(m_pDXT->get_Width(&nWidth));
	RTN_HR_IF_FAILED(m_pDXT->get_Height(&nHeight));

	//Create DDraw texture objects for the input video buffers.
	RTN_HR_IF_FAILED(CreateDXTextures(nWidth, nHeight));

	return S_OK; 
}

/******************************************************************************
 * Description: Terminate handler.  Called when we're being unloaded.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::Terminate()
{
	//Delete the frame timer if we have one
	m_pFrameTimer.Delete();

	//Release D3D objects
	m_pInput1Surface.Release();
	m_pInput2Surface.Release();

	RTN_HR_IF_FAILED(ReleaseSurfaces());
	RTN_HR_IF_FAILED(ReleaseScene());
	RTN_HR_IF_FAILED(ReleaseContext());

	//Reset the initialization flag since we're uninitialized now.
	m_fFirstTime = TRUE;

	return S_OK; 
}

/******************************************************************************
 * Description: Called by D3D once for each type of zbuffer format.
 *
 * DDPIXELFORMAT* pddpf - enumerated pixel format 
 * VOID* pddpfDesired - output parameter.  We fill this is if pddpf is the desired buffer format.
 * Returns: 
 *   HRESULT
 ******************************************************************************/
static HRESULT WINAPI EnumZBufferCallback(  DDPIXELFORMAT* pddpf,
											VOID* pddpfDesired )
{
	// We are only interested in z-buffers, so ignore any
	// other formats (e.g. DDPF_STENCILBUFFER) that get enumerated. An app
	// could also check the depth of the z-buffer (16-bit, etc,) and make a
	// choice based on that.
	if( pddpf->dwFlags == DDPF_ZBUFFER )
	{
		memcpy( pddpfDesired, pddpf, sizeof(DDPIXELFORMAT) );

		// Return with D3DENUMRET_CANCEL to end the search.
		return D3DENUMRET_CANCEL;
	}
 
	// Return with D3DENUMRET_OK to continue the search.
	return D3DENUMRET_OK;
}

/******************************************************************************
 * Description: Called to create D3D objects.  Initializes basic rendering 
 * settings.  Sets m_bReady to true when done.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::CreateContext()
{
	HRESULT hr = S_OK;

	RTN_HR_IF_TRUE(m_bReady);

	//Get dimensions of video buffers in pixels
	int nWidth, nHeight;

	RTN_HR_IF_BADPTR(m_pDXT);
	RTN_HR_IF_FAILED(m_pDXT->get_Width(&nWidth));
	RTN_HR_IF_FAILED(m_pDXT->get_Height(&nHeight));

	//Get global direct draw 7 object
	RTN_HR_IF_FAILED(m_pDXT->GetDirectDraw(&m_pDD));
	RTN_HR_IF_BADPTR(m_pDD);

	//Get Direct 3D 7 object
	m_pD3D = m_pDD;
	RTN_HR_IF_BADPTR(m_pD3D);

	//Create rendering surface
	DDSURFACEDESC2 desc;

	//Initialize surface description for the new primary rendering surface we're about to create.
	ZeroMemory(&desc, sizeof DDSURFACEDESC2);
	desc.dwSize = sizeof DDSURFACEDESC2;
	desc.dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS;
	desc.dwWidth = nWidth;
	desc.dwHeight = nHeight;
	desc.ddsCaps.dwCaps =  DDSCAPS_3DDEVICE | DDSCAPS_SYSTEMMEMORY; 

	//Create the new rendering surface
	RTN_HR_IF_FAILED(m_pDD->CreateSurface(&desc, &m_pInitialRenderSurface, NULL)); 

	//Is ZBuffering enabled?  It hurts perf so only use it when necessary.  When the possibility exists for
	//twos triangles to insect zbuffering may be necessary to ensure proper drawing.
	if (m_bUseZBuffer)
	{
		//Create ZBuffer
		ZeroMemory(&desc, sizeof DDSURFACEDESC2);
		desc.dwSize = sizeof DDSURFACEDESC2;

		//Get a zbuffer pixel format
		RTN_HR_IF_FAILED(m_pD3D->EnumZBufferFormats( IID_IDirect3DRGBDevice, 
									EnumZBufferCallback, (VOID*)&desc.ddpfPixelFormat ));

		desc.dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_CAPS;
		desc.dwWidth = nWidth;
		desc.dwHeight = nHeight;
		desc.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_SYSTEMMEMORY; 
		
		//Create the new zbuffer surface
		RTN_HR_IF_FAILED(m_pDD->CreateSurface(&desc, &m_pZBuffer, NULL)); 
		RTN_HR_IF_BADPTR(m_pZBuffer);

		//Attach zbuffer to the new surface.
		//This initial rendering surface is needed for CreateDevice() to be successful.
		//The real rendering surface will be set before each RenderScene() call.
		RTN_HR_IF_FAILED(m_pInitialRenderSurface->AddAttachedSurface(m_pZBuffer));
	}

	//Create an RGB software D3D rendering device rendering device.
	RTN_HR_IF_FAILED(m_pD3D->CreateDevice( IID_IDirect3DRGBDevice,
											m_pInitialRenderSurface,
											&m_pD3DDevice));
	RTN_HR_IF_BADPTR(m_pD3DDevice);

	if (m_bUseZBuffer)
	{
		//Remove the zbuffer we attached to our rendering surface.
		//We'll add it to the rendering target during each frame.
		RTN_HR_IF_FAILED(m_pInitialRenderSurface->DeleteAttachedSurface(0, NULL)); 

		RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE , D3DZB_TRUE ));
	}

	//Initialize D3DX if we haven't already.  Only do once or bad things happen.
	if (!g_fD3DXInitialized)
	{
		// Initialize D3DX
		RTN_HR_IF_FAILED(D3DXInitialize());

		g_fD3DXInitialized = true;
	}

	//Get rendering device capabilities.
	ZeroMemory(&m_descD3DDevice, sizeof(D3DDEVICEDESC7));
	RTN_HR_IF_FAILED(m_pD3DDevice->GetCaps(&m_descD3DDevice));

	//Read device capabilities from device caps struct.  
	m_fDeviceHasAlphablending = (m_descD3DDevice.dpcTriCaps.dwSrcBlendCaps & D3DPBLENDCAPS_SRCALPHA) &&
								(m_descD3DDevice.dpcTriCaps.dwDestBlendCaps & D3DPBLENDCAPS_INVSRCALPHA) &&
								(m_descD3DDevice.dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAFLATBLEND);

	//Set camera project matrix and rendering settings
	RTN_HR_IF_FAILED(m_pD3DDevice->SetTransform(D3DTRANSFORMSTATE_PROJECTION, m_matProjection));

	//Set most basic (fast) lighting settings
	RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING, FALSE));

	//Use gouraud shading during publish and flat shading during preview.
	RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, ( m_fltQualityFactor > 0.5 ) ? D3DSHADE_GOURAUD : D3DSHADE_FLAT ));

	//Finally set flag to indicate that the 3D code has been initialized.
	m_bReady = TRUE;

	return S_OK;
}

/******************************************************************************
 * Description: Sets camera position, orientation, and velocities.  
 * Camera starts 4.8 units up the world's y-axis looking straight down.
 * CAMERA_POSITION_? values are defined in 3DSpecialEffects.h.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::ResetCameraVectors()
{
	//Set camera position to 4.8 on the Y axis an.
	m_vecPosition.x = CAMERA_POSITION_X;
	m_vecPosition.y = CAMERA_POSITION_Y;
	m_vecPosition.z = CAMERA_POSITION_Z;

	//Set the camera orientation 
	m_vecYPR.x = CAMERA_YAW;
	m_vecYPR.y = 0.0f;  
	m_vecYPR.z = 0.0f;

	//Clear the world transformation matrix, set to identity matrix.
	D3DXMatrixTranslation(&m_matPosition, 0.0f, 0.0f, 0.0f);

	//Set the camera's project matrix.
	D3DXMatrixPerspectiveFov(&m_matProjection, D3DXToRadian(m_fFov), CAMERA_ASPECT_RATIO, 0.1f, 100.0f);

	return S_OK;
}

/******************************************************************************
 * Description: Reclaims rendering device surface when surface is lost.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::RestoreContext()
{
	RTN_HR_IF_BADPTR(m_pDD);
	RTN_HR_IF_FAILED(m_pDD->RestoreAllSurfaces());

	//Call inherited class to restore surfaces
	RTN_HR_IF_FAILED(RestoreSurfaces());

	return S_OK;
}


/******************************************************************************
 * Description: Releases all DirectX and D3DX objects and clears m_bReady flag.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::ReleaseContext()
{
	m_bReady = FALSE;

	m_pRenderSurface.Release();
	m_pInitialRenderSurface.Release();
	m_pZBuffer.Release();
	m_pD3DDevice.Release();
	m_pD3D.Release();
	m_pDD.Release();

	return S_OK;
}

/******************************************************************************
 * Description: Loads a texture from a block of memory.  Pixel format assumed
 * to be 24bit RGB.
 *
 * BYTE* pbBuff - memory buffer containing pixel data
 * long  lPitch - surface pitch of pixel data in bytes (pitch can be <0)
 * RECT* pRect - area of pixels to copy
 * IDirectDrawSurface7* pDDS - texture surface to copy pixel data too.  Must already
 *							   been created.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::LoadTextureFromMemoryARGB(BYTE* pbBuff, long lPitch, RECT* pRect, IDirectDrawSurface7* pDDS)
{
	RTN_HR_IF_BADPTR(pbBuff);

	HRESULT hr = S_OK;

	RTN_HR_IF_BADPTR(m_pD3DDevice);
	RTN_HR_IF_BADPTR(pDDS);
	RTN_HR_IF_BADPTR(pRect);

	//If the pitch is negative, flip the sign and start at the other end of the buffer.
	if ( ((long)lPitch) < 0)
	{
		pbBuff = pbBuff + ( (pRect->bottom - 1) * lPitch);
		lPitch = abs(lPitch);
	}


	//Load the image onto the texture
	//For performance reasons, use point sampling during preview and linear sampling during publish.
	hr = D3DXLoadTextureFromMemory(	m_pD3DDevice, 
									pDDS, 
									D3DX_DEFAULT, 
									pbBuff,
									NULL, 
									D3DX_SF_R8G8B8,
									lPitch,
									pRect,
									(m_fltQualityFactor > 0.5) ?  D3DX_FT_LINEAR : D3DX_FT_POINT );

	RTN_HR_IF_FAILED(hr);

	return S_OK;
}


/******************************************************************************
 * Description: Creates 1 or 2 DirectDraw surfaces for use for the input video images.
 *
 * int nWidth - the pixel width of the textures
 * int nHeight - the pixel height of the textures
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::CreateDXTextures(int nWidth, int nHeight)
{
	HRESULT hr = S_OK;

	//Sanity check: make sure surfaces are NULL.
	//Shouldn't be called twice.
	ASSERT(NULL == m_pInput1Surface.p);
	m_pInput1Surface.Release();

	//Sanity check: make sure surfaces are NULL.
	ASSERT(NULL == m_pInput2Surface.p);
	m_pInput2Surface.Release();

	DWORD dwFlags = D3DX_TEXTURE_NOMIPMAP,
		  dwWidth  = nWidth,
		  dwHeight = nHeight, 
		  dwNumMipMaps = 0;
		  
	//Set the pixel format
	D3DX_SURFACEFORMAT dxSurfFormat = D3DX_SF_R8G8B8;  

	//Create the texture
	hr = D3DXCreateTexture( m_pD3DDevice, 
							&dwFlags, 
							&dwWidth, 
							&dwHeight, 
							&dxSurfFormat,
							NULL, 
							&m_pInput1Surface, 
							&dwNumMipMaps);
	RTN_HR_IF_FAILED(hr);

	//If this is a transition, then there is two input surfaces.  
	//Create the texture for the second input surface.
	if (IsTransition())
	{
		dwFlags = D3DX_TEXTURE_NOMIPMAP;
		dwWidth  = nWidth;
		dwHeight = nHeight; 
		dwNumMipMaps = 0;

		//Set the pixel format
		D3DX_SURFACEFORMAT dxSurfFormat = D3DX_SF_R8G8B8;  

		//Create the texture
		hr = D3DXCreateTexture( m_pD3DDevice, 
								&dwFlags, 
								&dwWidth, 
								&dwHeight, 
								&dxSurfFormat,
								NULL, 
								&m_pInput2Surface, 
								&dwNumMipMaps);
		RTN_HR_IF_FAILED(hr);
	}

	return S_OK;
}

/******************************************************************************
 * Description: Sets the rendering target of the D3D device to a 24-bit block of memory.
 * Used to render directly onto the output video buffer supplied by DirectShow.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::SetRenderTargetOnMemoryARGB(BYTE* pbBuffer, long lPitch, RECT* prcRect)
{
	RTN_HR_IF_BADPTR(pbBuffer);
	RTN_HR_IF_BADPTR(prcRect);

	HRESULT hr = S_OK;
	DDSURFACEDESC2 desc;

	//Initialize surface description for the new primary rendering surface we're about to create.
	ZeroMemory(&desc, sizeof DDSURFACEDESC2);
	desc.dwSize = sizeof DDSURFACEDESC2;
	desc.dwFlags = DDSD_HEIGHT | DDSD_LPSURFACE | DDSD_PITCH | DDSD_WIDTH | DDSD_CAPS | DDSD_PIXELFORMAT;
	desc.dwWidth = prcRect->right - prcRect->left;
	desc.dwHeight = prcRect->bottom - prcRect->top;
	desc.ddsCaps.dwCaps =  DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE | DDSCAPS_SYSTEMMEMORY; 

	desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
    desc.ddpfPixelFormat.dwFlags= DDPF_RGB;
    desc.ddpfPixelFormat.dwRGBBitCount = 3*8;	// RGB24
    desc.ddpfPixelFormat.dwRBitMask    = 0x00FF0000;
    desc.ddpfPixelFormat.dwGBitMask    = 0x0000FF00;
    desc.ddpfPixelFormat.dwBBitMask    = 0x000000FF;

	//If our pitch is negative we're flip the sign of the pitch and point
	//the surface pointer at the top instead of the bottom of the image.
	if ( ((long) lPitch) < 0)
	{
		desc.lPitch = abs((long) lPitch); 
		desc.lpSurface = pbBuffer - ( (prcRect->bottom - 1) * desc.lPitch);
	}
	else
	{
		desc.lPitch = lPitch; 
		desc.lpSurface = pbBuffer;
	}

	//Create the new rendering surface
	RTN_HR_IF_BADPTR(m_pDD);
	RTN_HR_IF_FAILED(m_pDD->CreateSurface(&desc, &m_pRenderSurface, NULL)); 

	if (m_bUseZBuffer)
	{
		//If we're using a zbuffer, attach zbuffer to the new surface.
		RTN_HR_IF_FAILED(m_pRenderSurface->AddAttachedSurface(m_pZBuffer));
	}

	//Finally set the new target render
	RTN_HR_IF_BADPTR(m_pD3DDevice);
	RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderTarget(m_pRenderSurface, 0));

	return S_OK;
}

/******************************************************************************
 * Description: Resets all state changes made in SetRenderTargetOnMemoryARGB().
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::RestoreRenderTarget()
{
	RTN_HR_IF_BADPTR(m_pInitialRenderSurface);
	RTN_HR_IF_BADPTR(m_pRenderSurface);

	//Put the old render target back
	RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderTarget(m_pInitialRenderSurface, 0));
	
	if (m_bUseZBuffer)
	{
		//Remove the zbuffer we attached to our rendering surface.
		RTN_HR_IF_FAILED(m_pRenderSurface->DeleteAttachedSurface(0, NULL)); 
	}

	//Release objects.
	m_pRenderSurface.Release();

	return S_OK;
}

/******************************************************************************
 * Description: Time sensitive render method called when CMM3DSpecialEffect()
 *				should render to the output buffer.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMM3DSpecialEffect::Execute()  
{ 
	HRESULT hr = S_OK;

	//Get the pixel width and height of the input/output buffers
	int nWidth = -1, nHeight = -1;
	float fProgress;

	RTN_HR_IF_BADPTR(m_pDXT);
	RTN_HR_IF_FAILED(m_pDXT->get_Width(&nWidth));
	RTN_HR_IF_FAILED(m_pDXT->get_Height(&nHeight));

	//Get the progress into the transition 0.0 - 1.0
	RTN_HR_IF_FAILED(m_pDXT->get_Progress(&fProgress));

	DWORD* pdwInput = NULL, *pdwInput2 = NULL, *pdwOutput = NULL;
	RECT rect; 

	SetRect(&rect, 0, 0, nWidth, nHeight);
	
	//Get the pitch of the surfaces.
	long lInputPitch = -1, lOutputPitch = -1;
	RTN_HR_IF_FAILED(m_pDXT->get_InputPitch(&lInputPitch));
	RTN_HR_IF_FAILED(m_pDXT->get_OutputPitch(&lOutputPitch));

	//Add 3 to make sure we round up correctly to get all bits
	long lPitchDWORDS = ( ((long) (lOutputPitch + 3) ) / 4);
	long lRowOffsetDWORDS = 0;
	
	//If it's negative, flip the sign and start at the other end of the buffer.
	if (lPitchDWORDS < 0)
	{
		lRowOffsetDWORDS = lPitchDWORDS * (nHeight - 1);
		lPitchDWORDS = -lPitchDWORDS;
	}

	//Get the first video input buffer
	RTN_HR_IF_FAILED(m_pDXT->GetInputBuffer((BYTE**) &pdwInput));
	RTN_HR_IF_BADPTR(pdwInput);

	//Copy the first video input buffer on a texture
	RTN_HR_IF_FAILED(LoadTextureFromMemoryARGB((BYTE*) pdwInput, lInputPitch, &rect, m_pInput1Surface));

	//If this is a transition, do the same thing for the second video input buffer as the first.
	if (IsTransition())
	{
		long lInput2Pitch = -1;
		RTN_HR_IF_FAILED(m_pDXT->get_Input2Pitch(&lInput2Pitch));

		//Get the 2nd video input buffer
		RTN_HR_IF_FAILED(m_pDXT->GetInput2Buffer((BYTE**) &pdwInput2));
		RTN_HR_IF_BADPTR(pdwInput2);

		//Copy the second video input buffer on a texture
		RTN_HR_IF_FAILED(LoadTextureFromMemoryARGB((BYTE*) pdwInput2, lInput2Pitch, &rect, m_pInput2Surface));
	}

	//Get the output video buffer
	RTN_HR_IF_FAILED(m_pDXT->GetOutputBuffer((BYTE**) &pdwOutput));
	RTN_HR_IF_BADPTR(pdwOutput);

	//Set the output video buffer as the rendering target
	RTN_HR_IF_FAILED(SetRenderTargetOnMemoryARGB((BYTE*) pdwOutput, lOutputPitch, &rect));

	//Begin rendering
	if(SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//Note that we don't need to clear the rendering target for transitions since we always render into the entire surface.

		int nClearFlags = D3DCLEAR_TARGET;
		
		if (m_bUseZBuffer)
			nClearFlags |= D3DCLEAR_ZBUFFER;

		RTN_HR_IF_FAILED(m_pD3DDevice->Clear( 0, NULL, nClearFlags, 0xff000000, 1.0f, 0L ));

		//Compute camera's transformation matrix as the composition or camera position and orientation.
		//First make a quaternion (4D vector) out of the rotation Yaw Pitch Roll vector
		D3DXQUATERNION qR;
		D3DXQuaternionRotationYawPitchRoll(&qR, m_vecYPR.y, m_vecYPR.x,  m_vecYPR.z);

		//Make the transition matrix out of the position vector and the quaternion of Yaw Pitch Roll.
		D3DXMatrixAffineTransformation(&m_matPosition, 1.0f, NULL, &qR, &m_vecPosition);

		//Find camera's view matrix as the inverse of the camera's transformation matrix.
		D3DXMatrixInverse(&m_matView, NULL, &m_matPosition);

		//Make sure the world transform starts out as a nothing.
		(void)m_pD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, g_matIdentity);

		//Set the camera's view matrix.
		//IDEA: Optimization.  None of the effects (so far) change camera the transformation, 
		//we dont' need to do this every frame.
		(void)m_pD3DDevice->SetTransform(D3DTRANSFORMSTATE_VIEW, m_matView);

		//Call the inheriting class to render the scene
		RTN_HR_IF_FAILED(RenderScene(fProgress));

		//Tell D3D we're done rendering scene
		RTN_HR_IF_FAILED(m_pD3DDevice->EndScene());
	}

	//Release everything we're done in SetRenderTarget...
	RTN_HR_IF_FAILED(RestoreRenderTarget());

	return S_OK; 
}

/******************************************************************************
/* CSimple3DSpecialEffect implementation - a basic 3D class for effects and 
 * transitions composed of one or two 3D video planes.
/*****************************************************************************/

/******************************************************************************
 * Description: constructor
 *
 * CMMSpecialEffectDXT* pDXT - back pointer to container.
 * LPCTSTR szInternalName - internal name of effect.  From mapping in FilterBase::CreateSpecialEffectByName().
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
CSimple3DSpecialEffect::CSimple3DSpecialEffect(CMMSpecialEffectDXT* pDXT, LPCTSTR szInternalName) 
	: _baseClass(pDXT, szInternalName) 
{ 
	//Default to always drawing the 1st input video and drawing the second only if this is a transtion.
	m_bDisplayVideoPlane = true;
	m_bDisplayVideoPlane2 = IsTransition();

	//Default is only the front side of each video plane are drawn.
	m_bShowAFront = true;
	m_bShowABack = false;
    m_bShowBFront = true;
	m_bShowBBack = false;

	//Default to 32x32 video plane for this sample.
	m_nPlaneSubdivisions = 32;

	//Set to true to enabled alpha blending on the first video plane.  Note that the alpha component of each vertex
	//in the video plane must also be set.
	m_fAlphaBlendA = false;
}

/******************************************************************************
 * Description: Creates planar geometry objects for input videos
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CSimple3DSpecialEffect::CreateScene()
{
	//Color of video plane.
	D3DXCOLOR kcolorVideoPlane(1.0f, 1.0f, 1.0f, 1.0f);

	// Create VideoPlane
	if (m_bDisplayVideoPlane)
	{
		//Create the 1st video plane.
		RTN_HR_IF_BADNEW(m_spVideoPlane = new CVideoPlane(m_pD3D, m_pD3DDevice, false, false) );

		//Set it's size to be 4.0 x 4.0, no titling of the texture, white, and sitting at Y = 0.0.
		RTN_HR_IF_FAILED(m_spVideoPlane->Initialize(VIDEO_PLANE_SIZE / CAMERA_ASPECT_RATIO, 
													VIDEO_PLANE_SIZE , 
													1.0f, 
													kcolorVideoPlane, 
													0.0f, 
													m_bShowAFront, 
													m_bShowABack,
													m_nPlaneSubdivisions));
	}
		
	//If this is a transition then we'll create a second video plane for the second input surface.
	if (m_bDisplayVideoPlane2)
	{
		// Create the 2nd video plane for transitions
		RTN_HR_IF_BADNEW(m_spVideoPlane2 = new CVideoPlane(m_pD3D, m_pD3DDevice, false, m_bShowBBack && !m_bShowBFront ));

		//Set it's size to be 4.0 x 4.0, no titling of the texture, white, and sitting at Y = -0.01.
		RTN_HR_IF_FAILED(m_spVideoPlane2->Initialize(VIDEO_PLANE_SIZE / CAMERA_ASPECT_RATIO, 
													 VIDEO_PLANE_SIZE , 
													 1.0f, 
													 kcolorVideoPlane, 
													 (m_bUseZBuffer ? -0.005f : 0.0f), 
													 m_bShowBFront, 
													 m_bShowBBack,
													 m_nPlaneSubdivisions));
	}

	return S_OK;
}

/******************************************************************************
 * Description: Release the video plane geomtry
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CSimple3DSpecialEffect::ReleaseScene()
{
	//Release smart pointers for video planes
	m_spVideoPlane.Delete();
	m_spVideoPlane2.Delete();

	return S_OK;
}

/******************************************************************************
 * Description: Render the video plane(s).  Time sensitive!
 *
 * float fProgress - 0.0 to 1.0 value indicating progress into transition effect
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CSimple3DSpecialEffect::RenderScene(float fProgress)
{
	RTN_HR_IF_BADPTR(m_pD3DDevice);


	//Render the 2nd plane first since it must appear behind the 1st plane,
	//But only if the progress of the effect is greater than zero.
	if (m_bDisplayVideoPlane2 && fProgress > 0.0f)
	{
		RTN_HR_IF_BADPTR(m_spVideoPlane2);

		//Set the 2nd input video as the current texture
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTexture(0, m_pInput2Surface));

		//Draw the plane geometry
		RTN_HR_IF_FAILED(m_spVideoPlane2->Draw(fProgress));

		//Clear the current texture to free resources
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTexture(0, NULL));
	}

	//Draw the first video plane if the progress is less than 1.0
	if (m_bDisplayVideoPlane && (!IsTransition() || fProgress < 1.0f) )
	{
		RTN_HR_IF_BADPTR(m_spVideoPlane);

		//Turn on blending for fade/glow effects if needed and the device can do it..
		if (m_fAlphaBlendA && m_fDeviceHasAlphablending)
		{
			RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE));
			RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderState( D3DRENDERSTATE_SRCBLEND,   D3DBLEND_SRCALPHA));
			RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderState( D3DRENDERSTATE_DESTBLEND,  D3DBLEND_INVSRCALPHA ));
		}

		//Set the first input video as the current texture
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTexture(0, m_pInput1Surface));

		//Draw the plane geometry
		RTN_HR_IF_FAILED(m_spVideoPlane->Draw(fProgress));

		//Clear the current texture
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTexture(0, NULL));

		//Restore previous state
		if (m_fAlphaBlendA && m_fDeviceHasAlphablending)
		{
			RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE));
			RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderState( D3DRENDERSTATE_DESTBLEND,  D3DBLEND_ZERO  ));
			RTN_HR_IF_FAILED(m_pD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE));
		}
	}

	return S_OK;
}

/******************************************************************************
 * Description: Create video plane vertex buffers if enabled.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CSimple3DSpecialEffect::CreateSurfaces()
{
	if (m_bDisplayVideoPlane)
	{
		RTN_HR_IF_BADPTR(m_spVideoPlane);
		RTN_HR_IF_FAILED(m_spVideoPlane->CreateSurfaces());
	}

	if (m_bDisplayVideoPlane2)
	{
		RTN_HR_IF_BADPTR(m_spVideoPlane2);
		RTN_HR_IF_FAILED(m_spVideoPlane2->CreateSurfaces());
	}

	return S_OK;
}

/******************************************************************************
 * Description: Release video plane vertex memory
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CSimple3DSpecialEffect::RestoreSurfaces()
{
	if (m_bDisplayVideoPlane)
	{
		RTN_HR_IF_BADPTR(m_spVideoPlane);
		RTN_HR_IF_FAILED(m_spVideoPlane->RestoreSurfaces());
	}

	if (m_bDisplayVideoPlane2)
	{
		RTN_HR_IF_BADPTR(m_spVideoPlane2);
		RTN_HR_IF_FAILED(m_spVideoPlane2->RestoreSurfaces());
	}

	return S_OK;
}


/******************************************************************************
 * Description: Restores video plane vertex memory
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CSimple3DSpecialEffect::ReleaseSurfaces()
{
	if (m_spVideoPlane)
		RTN_HR_IF_FAILED(m_spVideoPlane->ReleaseSurfaces());

	if (m_spVideoPlane2)
		RTN_HR_IF_FAILED(m_spVideoPlane2->ReleaseSurfaces());

	return S_OK;
}


/******************************************************************************
 * Description: Initialize handler.  Reads settings from the properties and sets
 * up internal state.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CSimple3DSpecialEffect::Initialize( )
{
	HRESULT hr = S_OK;

	//This sample 3D device is set up to always render in 24 bit RGB.  
	//Check if the native buffer format is 24 bit and if so, render directly to the output
	//surface by setting the UseNativeBuffers property on the DXT.
	//Note that native buffers will always be 24 bit inside Movie Maker 2.0. 
	DXSAMPLEFORMATENUM dxFormat;
	RTN_HR_IF_BADPTR(m_pDXT);
	RTN_HR_IF_FAILED(m_pDXT->get_NativeOutputPixelFormat(&dxFormat));

	bool f24bit = (dxFormat & DXPF_RGB24) == DXPF_RGB24;	
	if (f24bit)
	{
		RTN_HR_IF_FAILED(m_pDXT->put_UseNativeBuffers(true));
	}

	//Call base class.  This will create scene, video planes, and read base class parameters.
	RTN_HR_IF_FAILED(_baseClass::Initialize());
	RTN_HR_IF_BADPTR(m_spVideoPlane); //Sanity check.  Surfaces should be created by now.

	//Get the MeltIntensity property.  
	float fValue = 0.0f;
	RTN_HR_IF_FAILED(m_pDXT->get_MeltIntensity(&fValue));
	if (!IsEqual(fValue, 0.0f))
	{
		RTN_HR_IF_FAILED(m_spVideoPlane->SetMeltIntensity(fValue));

		//Uncomment to use alpha blending!
		//RTN_HR_IF_FAILED(m_spVideoPlane->SetFadeStart(0.7f));
		//m_fAlphaBlendA = true;
	}
	
	//Enabled alpha blending on the device if we need it and if the device can handle it.
	if ( m_fAlphaBlendA && m_fDeviceHasAlphablending)
	{
		RTN_HR_IF_BADPTR(m_pD3DDevice);
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,  D3DTOP_MODULATE));
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE ));
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE ));

		RTN_HR_IF_FAILED(m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE ));
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE));
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE));
	}


	return S_OK;
}

/******************************************************************************
/* CVideoPlane implementation 
/*****************************************************************************/

/******************************************************************************
 * Description: constructor
 *
 * LPDIRECT3D7 pD3D - pointer to the module's direct3D object
 * LPDIRECT3DDEVICE7 pD3DDevice - pointer to module's D3D rendering device
 * bool fInputUpsidedown - set to true if image should be flipped on the Y axis
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
CVideoPlane::CVideoPlane(LPDIRECT3D7 pD3D, LPDIRECT3DDEVICE7 pD3DDevice, bool fInputUpsidedown, bool fInputRightLeft)
{
	RTN_VOID_IF_BADPTR(pD3D);
	RTN_VOID_IF_BADPTR(pD3DDevice);

	m_uIndices  = 0;
	m_uVertices = 0;
	m_fYOffset = 0.0f;

	m_fInputUpsidedown = fInputUpsidedown;
	m_fInputRightLeft = fInputRightLeft;

	m_pvbVertices = NULL;

	m_pD3D = pD3D;
	m_pD3DDevice = pD3DDevice;

	ZeroMemory(&m_matrixLocal, sizeof D3DXMATRIX);

	m_bLocalTransform = false;
	m_vecTranslation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vecRotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vecScale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_vecCenter = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pVertexTime0.Delete();

	//True if the MeltIntensity property is set.  Used for the Melt transition.
	m_fMeltIntensity = 0.0f;

	//Default number of rectanges used to make up a video plane.
	m_nPlaneSubdivisions = 1;

	//Initialize to the highest value possible.
	m_fFadeStartProgress = FLT_MAX;
}


/******************************************************************************
 * Description: Nothing to do as member objects are smart ptr's or CCOMPtr's
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
CVideoPlane::~CVideoPlane()
{
}

/******************************************************************************
 * Description: Creates vertex and index information and stores information.
 *
 * float fWidth - width of plane to create in 3D world coordinates.
 * float fHeight - height of plane to create in 3D world coordinates.
 * float fTile - number of times to repeat video image on plane in each direction.
 * DWORD dwColor - color of plane.  White makes the most sense here.
 * float fYOffset - Coordinate of plane's position on the Y axis in world coordinates.
 * bool bFrontPolys - generate front-facing polygons.  Most useful.
 * bool bBackPolys - generate back facing polyons.  Useful if camera is behind the plane.
 * int nPlaneSubdivisions - number of polygonal subdivisions in row or colum.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CVideoPlane::Initialize(float fWidth, float fHeight, float fTile, DWORD dwColor, float fYOffset, bool bFrontPolys, bool bBackPolys, int nPlaneSubdivisions)
{
	HRESULT hr = S_OK;

	RTN_HR_IF_FALSE(bFrontPolys || bBackPolys);

	D3DXMatrixTranslation(&m_matrixLocal, 0.0f, 0.0f, 0.0f);

	// Calculate number of vertices and indices
	m_nPlaneSubdivisions = nPlaneSubdivisions;

	m_uVertices = (nPlaneSubdivisions + 1) * (nPlaneSubdivisions + 1);
	m_uIndices  = (nPlaneSubdivisions * nPlaneSubdivisions) * 6;

	//Back facing polygons
	if (bFrontPolys && bBackPolys)
		m_uIndices  = m_uIndices * 2;

	// Create indices
	m_srgwIndices = new WORD[m_uIndices];
	RTN_HR_IF_BADNEW(m_srgwIndices);

	// Fill in polygonal indicies to each vertex in the vertex array
	WORD *pwIndex = m_srgwIndices;

	for(UINT uZ = 0; uZ < (UINT) nPlaneSubdivisions; uZ++)
	{
		for(UINT uX = 0; uX < (UINT) nPlaneSubdivisions; uX++)
		{
			UINT uVertex = uX + uZ * (nPlaneSubdivisions + 1);

			//Make rectangles composed of two triangles each (6 verticies)
			if (bFrontPolys)
			{
				pwIndex[0] = uVertex + 0;
				pwIndex[1] = uVertex + 1;
				pwIndex[2] = uVertex + (nPlaneSubdivisions + 1);
				pwIndex[3] = uVertex + (nPlaneSubdivisions + 1);
				pwIndex[4] = uVertex + 1;
				pwIndex[5] = uVertex + (nPlaneSubdivisions + 2);

				pwIndex += 6;
			}

			//Make rear facing polygons
			if (bBackPolys)
			{
				pwIndex[0] = uVertex + (nPlaneSubdivisions + 1);
				pwIndex[1] = uVertex + 1;
				pwIndex[2] = uVertex + 0;
				pwIndex[3] = uVertex + (nPlaneSubdivisions + 2);
				pwIndex[4] = uVertex + 1;
				pwIndex[5] = uVertex + (nPlaneSubdivisions + 1);

				pwIndex += 6;
			}

			uVertex++;
		}
	}

	// Save all the other data
	m_fWidth = fWidth; 
	m_fHeight = fHeight; 
	m_fTile = fTile; 
	m_dwColor = dwColor;
	m_fYOffset = fYOffset;

	return S_OK;
}

/******************************************************************************
 * Description: Allocate a vertex buffer using D3D's flexible vertex format (fvf).
 * 
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CVideoPlane::CreateSurfaces()
{
	//If we haven't already created the vertex buffer do so.
	ASSERT(!m_pvbVertices);
	if(!m_pvbVertices)
	{
		//An array of FVF vertex structures.
		VIDEOPLANE_VERTEX *pVertices;

		//Vertex buffer description structure
		D3DVERTEXBUFFERDESC vbdesc;
		ZeroMemory(&vbdesc, sizeof D3DVERTEXBUFFERDESC);

		vbdesc.dwSize = sizeof(vbdesc);
		vbdesc.dwCaps = D3DVBCAPS_SYSTEMMEMORY;
		vbdesc.dwFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0);
		vbdesc.dwNumVertices = m_uVertices;

		//allocate memory for verticies
		RTN_HR_IF_BADPTR(m_pD3D);
		RTN_HR_IF_FAILED(m_pD3D->CreateVertexBuffer(&vbdesc, &m_pvbVertices, 0));
		RTN_HR_IF_BADPTR(m_pvbVertices);

		//Create initial state vertex array
		m_pVertexTime0 = new VIDEOPLANE_VERTEX_INTERNAL[m_uVertices];
		RTN_HR_IF_BADPTR(m_pVertexTime0);

		//Lock vertex memory so we can write to it
		//TODO: If HW acceleration is implemented, check HR for surface lost.
		RTN_HR_IF_FAILED(m_pvbVertices->Lock(DDLOCK_WAIT | DDLOCK_WRITEONLY, (void **) &pVertices, NULL));
		RTN_HR_IF_BADPTR(pVertices);

		// Fill in vertices
		UINT uDivs = m_nPlaneSubdivisions;
		UINT uX, uZ;

		RTN_HR_IF_FALSE(uDivs != 0);

		//Calculate the width and height increment for the loop the builds the plane.  
		//This is the size each rectangular polygon in the plane.
		float fXInc = m_fWidth  / (float) uDivs;
		float fZInc = m_fHeight / (float) uDivs;

		//Calculate the texture mapping coordinate increment.
		float fSInc = m_fTile / (float) uDivs;
		float fTInc = m_fTile / (float) uDivs;

		//Get backwards/negative if the image is coming in upsidedown
		if (m_fInputRightLeft)
			fSInc = -fSInc;

		//Get backwards/negative if the image is coming in upsidedown
		if (m_fInputUpsidedown)
			fTInc = -fTInc;

		//Initialize the column position and texture coordinates
		float fZ = m_fHeight * -0.5f;
		float fT = 0.0f;

		DWORD nCurrentVertex = 0;
		float fPlaneDivsTimes2 = m_nPlaneSubdivisions * 2.0f;

		//Loop on each column
		for(uZ = 0; uZ <= uDivs; uZ++)
		{
			//Initialize the row position and texture coordinates
			float fX = m_fWidth  * -0.5f;
			float fS = 0.0f;

			//Loop on each row
			for(uX = 0; uX <= uDivs; uX++)
			{
				VIDEOPLANE_VERTEX *pVertex;

				//Set position, color, and texture coords for each vertex in the plane
				pVertex = &pVertices[uX + uZ * (uDivs + 1)];
				pVertex->m_vecPos = D3DXVECTOR3(fX, m_fYOffset, fZ);
				pVertex->m_dwDiffuse = m_dwColor;
				pVertex->m_vecTex = D3DXVECTOR2(fS, fT);

				//Store a copy in our internal "Time Zero" vertex array.
				memcpy(&m_pVertexTime0[nCurrentVertex], pVertex, sizeof VIDEOPLANE_VERTEX);

				//Store X and Y grid position of vertex
				m_pVertexTime0[nCurrentVertex].m_nX = uX;
				m_pVertexTime0[nCurrentVertex].m_nY = uZ;

				//Initialize to FLT_MAX so velocity progress never starts by default
				m_pVertexTime0[nCurrentVertex].m_fVelocityX = 0.0;
				m_pVertexTime0[nCurrentVertex].m_fVelocityZ = 0.0;

				fX += fXInc;
				fS += fSInc;

				nCurrentVertex++;
			}

			fZ += fZInc;
			fT += fTInc;
		}

		//Tell D3D we're done writing to the vertex memory.
		RTN_HR_IF_FAILED(m_pvbVertices->Unlock());
	}

	return S_OK;
}


/******************************************************************************
 * Description: release and restore vertex buffer
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CVideoPlane::RestoreSurfaces()
{
	RTN_HR_IF_FAILED(ReleaseSurfaces());
	RTN_HR_IF_FAILED(CreateSurfaces());

	return S_OK;
}

/******************************************************************************
 * Description: release vertex buffer
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CVideoPlane::ReleaseSurfaces()
{
	m_pvbVertices.Release();

	return S_OK;
}



/******************************************************************************
 * Description: Renders the video plane.  Assumes BeginScene() has been called
 * on the device.
 *
 * float fProgress - time of rendering, ranges between 0.0 and 1.0.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CVideoPlane::Draw(float fProgress)
{
	RTN_HR_IF_BADPTR(m_pD3DDevice);

	//Is there an animated transformation on the video plane?
	if (m_bLocalTransform)
	{
		//Scale the translation and rotation vectors by the progress (time) into the effect.
		D3DXVECTOR3 vecTranslation, vecRotation, vecScale;
		D3DXVec3Scale(&vecTranslation, &m_vecTranslation, fProgress);
		D3DXVec3Scale(&vecRotation, &m_vecRotation, fProgress);

		//Has a final scaling vector been set?  D3DXVec3LengthSq returns the sum of the x, y, and z components
		//of a vector.  The default value of m_vecScale and m_vecInitialScale is the unit vector 1,1,1.
		if (!IsEqual(D3DXVec3LengthSq(&m_vecScale), 3.0f) || !IsEqual(D3DXVec3LengthSq(&m_vecInitialScale), 3.0f))
		{
			//Linear interpolate between the start scale and the final scale using the progress values.
			vecScale.x = m_vecScale.x * fProgress;
			vecScale.z = m_vecScale.z * fProgress;
		}
		else //No scaling
			vecScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		//Calculate the transformation matrix for the plane.
		D3DXQUATERNION qRotation;
		D3DXQuaternionRotationYawPitchRoll(&qRotation, vecRotation.y, vecRotation.x,  vecRotation.z);

		D3DXMatrixTransformation (	&m_matrixLocal,
									NULL, //Scaling center
									NULL, //scaling rotation
									&vecScale, //scaling
									&m_vecCenter, //rotation center
									&qRotation, //rotation
									&vecTranslation);

		// Apply planes's local transformation matrix to the device
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, m_matrixLocal ));
	}
	else
	{
		// Apply a generic indentity matrix
		RTN_HR_IF_FAILED(m_pD3DDevice->SetTransform(D3DTRANSFORMSTATE_WORLD, g_matIdentity ));
	}

	//Is vertex melt desired specified or fade specified?  If so, edit the vertex positions and alpha components.
	if (!IsEqual(m_fMeltIntensity, 0.0) || !IsEqual(m_fFadeStartProgress, FLT_MAX))
	{
		VIDEOPLANE_VERTEX* pVertices = NULL; 
		DWORD dwSize = 0;

		//Lock the vertex memory for writing
		RTN_HR_IF_BADPTR(m_pvbVertices);
		RTN_HR_IF_FAILED(m_pvbVertices->Lock(DDLOCK_WAIT | DDLOCK_WRITEONLY, 
											(void **) &pVertices, 
											&dwSize));
		RTN_HR_IF_BADPTR(pVertices);

		//Get number of vertices in buffer
		DWORD dwNumVertices = dwSize / sizeof VIDEOPLANE_VERTEX;

		//Default alpha value
		DWORD dwAlphaValue = 0xFF000000;
		
		//Time to start fading?  If so, compute the current alpha value of the vertex.
		if (fProgress > m_fFadeStartProgress)
		{
			float fAlphaProgress;

			//Compute alpha value avoid division by zero.
			if (!IsEqual(m_fFadeStartProgress, 1.0f))
				fAlphaProgress = (fProgress - m_fFadeStartProgress) * (1.0f / (1.0f - m_fFadeStartProgress));
			else
				fAlphaProgress = 0.0f;

			//Compute value 0 to 255 and move to the DWORD high byte.
			dwAlphaValue = ( (DWORD) ( (1.0f - fAlphaProgress) * 255) ) << 24;
		}

		//Z axis velocity of vertices when progress is 0.5 to 1.0. 
		const float kfVelocity2Z = -9.0;

		//Loop through the vertices adjusting postion and alpha value.
		for (DWORD i = 0; i < dwNumVertices; i++)
		{
			//For the first half the transition move the vertices according to their velocity.
			if (fProgress < 0.5)
			{
				//Add velocity contribution to position.  
				pVertices[i].m_vecPos.x = m_pVertexTime0[i].m_vecPos.x + (m_pVertexTime0[i].m_fVelocityX * fProgress) ;
				pVertices[i].m_vecPos.z = m_pVertexTime0[i].m_vecPos.z + (m_pVertexTime0[i].m_fVelocityZ * fProgress) ;
			}
			else //For the second half move them down the screen.
			{
				//Add velocity contribution to position.  
				pVertices[i].m_vecPos.x = m_pVertexTime0[i].m_vecPos.x + 
						(m_pVertexTime0[i].m_fVelocityX * fProgress) ;

				pVertices[i].m_vecPos.z = m_pVertexTime0[i].m_vecPos.z + 
						(m_pVertexTime0[i].m_fVelocityZ * fProgress) +
						(kfVelocity2Z * (fProgress - 0.5f) ) ;
			}

			//Apply alpha value to each vertex.
			pVertices[i].m_dwDiffuse = (pVertices[i].m_dwDiffuse & 0x00FFFFFF) | dwAlphaValue;
		}
		
		//Tell D3D we're done writing to the vertex buffer now.
		RTN_HR_IF_FAILED(m_pvbVertices->Unlock());
	}

	//Draw the plane
	RTN_HR_IF_FAILED(m_pD3DDevice->DrawIndexedPrimitiveVB(D3DPT_TRIANGLELIST, m_pvbVertices, 0, m_uVertices, m_srgwIndices, m_uIndices, 0));

	return S_OK;
}



/******************************************************************************
 * Description: set ending scale
 *
 * float fX - input final x scale
 * float fY - input final y scale
 * float fZ - input final z scale
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CVideoPlane::SetFinalScale(float fX, float fY, float fZ)
{
	//Use local transform when rendering
	m_bLocalTransform = true;

	m_vecScale.x = fX;
	m_vecScale.y = fY;
	m_vecScale.z = fZ;

	return S_OK;
}


/******************************************************************************
 * Description: Makes the video plane melt over the duration of the effect or
 * transition.  Called during initialization.
 *
 * float fMeltIntensity - intensity of melt.  higher number means more entropy.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CVideoPlane::SetMeltIntensity(float fMeltIntensity)
{
	//Set flag to turn melt on if intensity is not zero.
	m_fMeltIntensity = fMeltIntensity;

	//Now we will determine the progress (time 0..1.0) at which each vertex
	//will begin to melt.  

	VIDEOPLANE_VERTEX* pVertices = NULL; 
	DWORD dwSize = 0;

	//Lock the vertex memory for writing
	RTN_HR_IF_FAILED(m_pvbVertices->Lock(DDLOCK_WAIT | DDLOCK_READONLY, 
										(void **) &pVertices, 
										&dwSize));
	RTN_HR_IF_BADPTR(pVertices);

	//Get number of vertices in buffer
	DWORD dwNumVertices = dwSize / sizeof VIDEOPLANE_VERTEX;

	//Determine velocity of first pixel.  All velocities with be calculated as a small random value
	//continuing from this value.
	double fLastRandomZ = (rand() / (double)RAND_MAX) / 2.0;

	//Loop through the vertices, setting random melting velocities.
	//The random velocities (m_fVelocityX and m_fVelocityZ) will be used when progress is 0.0 to 0.5.
	//Note that a second constant velocity kfVelocity2Z is applied only after progress is than 0.5 to 1.0.  
	for (DWORD i = 0; i < dwNumVertices; i++)
	{
		//Compute random value for X axis velocity -0.25 to -.25.0.
		double fRandomX = ((rand() / (double)RAND_MAX) - 0.5) / 2.0;

		//Compute random value to add to Z axis velocity -0.0625 to 0.0625.
		double fRandomZ = fLastRandomZ - ((rand() / (double)RAND_MAX) -0.5) / 8.0;

		//Keep Z velocities going down the screen.
		if (fRandomZ < 0.0f) 
			fRandomZ = 0.0625f;
		
		//Accumulate new z velocity
		fLastRandomZ = fRandomZ;

		//For the first velocities which occur while progress is between 0.0 and 0.5, make values -0.5 to 0.5
		//This will make the vertices turn liquidy.
		m_pVertexTime0[i].m_fVelocityX = (float) fRandomX * m_fMeltIntensity;
		m_pVertexTime0[i].m_fVelocityZ = (float) -fRandomZ * m_fMeltIntensity;
	}

	//Release vertex buffer
	RTN_HR_IF_FAILED(m_pvbVertices->Unlock());

	return S_OK;
}

/******************************************************************************
 * Description: 
 *
 * float fFadeStartProgress - progress time to start fading at.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CVideoPlane::SetFadeStart(float fFadeStartProgress)
{
	m_fFadeStartProgress = fFadeStartProgress;

	return S_OK;
}
