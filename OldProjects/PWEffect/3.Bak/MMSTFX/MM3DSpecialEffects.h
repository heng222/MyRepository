
/*****************************************************************************
 * module MM3DSpecialEffect.h 
 *
 *	Defines the classes CMM3DSpecialEffect, CSimple3DSpecialEffect, and CVideoPlane.
 *	
 *	CMM3DSpecialEffect inherits from CMMSpecialEffect and implements basic Direct3D functionality
 *	to create texture objects from the input video buffer(s) and a rendering target surface 
 *	directly on the output video buffer.  It declares methods to simplify which may be overridden:
 *	CreateScene, ReleaseScene, RenderScene, CreateSurfaces, RestoreSurfaces, ReleaseSurfaces.  
 *	Note that this class does not render anything, it is inherited by CSimple3DSpecialEffect 
 *	for this purpose.
 *	
 *	CSimple3DSpecialEffect inherits from CMM3DSpecialEffect and performs rendering.  Creates one or 
 *	two 3D plane(s) depending on if this if an effect or transition.  The planes are aligned to 
 *	the XZ plane, are 2 wide by 2 units high, and sit directly in front of the virtual camera.  
 *	The Melt sample transition uses this class by sliding the first video plane down the screen 
 *	revealing the second video plane behind it.
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#ifndef THREEDSPECIALEFFECT_H
#define THREEDSPECIALEFFECT_H

#include "MMSpecialEffect.h"
#include "frametimer.h"

#include <d3d.h>
#include <d3dx.h>

//Width and height of video plane
#define VIDEO_PLANE_SIZE 4.0f


//Camera's field of view
#define FIELD_OF_VIEW_ANGLE 45.0f
#define CAMERA_ASPECT_RATIO (3.0f / 4.0f)

//Camera position and orientation
#define CAMERA_POSITION_X 0.01f  //Horizontal in relation to the video plane/origin
#define CAMERA_POSITION_Y 4.8284271f   //Distance = 2.0 * tan(180 - 90 - (FOV_ANGLE / (VIDEO_PLANE_SIZE / 2.0) )) 
#define CAMERA_POSITION_Z 0.01f	//Vertical in relation to the video plane/origin
#define CAMERA_YAW -1.570796326f		// -PI/2 = quarter turn 

//Vertex structure.  conforms to D3D's flexible vertex format 
//for describing vertex buffers.  Defines postion, color, and texture coords.

// Packing this struct because D3D requires it
#pragma pack(push, d3dpck)
#pragma pack(4)
typedef struct VIDEOPLANE_VERTEX
{
	D3DXVECTOR3 m_vecPos;
	D3DCOLOR    m_dwDiffuse;
	D3DXVECTOR2 m_vecTex;
} VIDEOPLANE_VERTEX;

//Internal vertex structure.  Used to keep extra data about the vertex outside the context of D3D's vertex buffer format.
class VIDEOPLANE_VERTEX_INTERNAL : public VIDEOPLANE_VERTEX
{
public:
	float m_fVelocityX;		//Velocity of vertex.  Used for Melt transition when progress is between 0.0 and 0.5.
	float m_fVelocityZ;		//Velocity of vertex.  Used for Melt transition when progress is between 0.0 and 0.5.
	int m_nX;				//X index of vertex in mesh.
	int m_nY;				//Y index of vertex in mesh.
} ;
#pragma pack(pop, d3dpck) // Reverting back to default


/*****************************************************************************
 * class CVideoPlane -		class for drawing an input video onto a single plane
 *							in 3D.  Plane is aligned to the XZ axis.
 *****************************************************************************/
class CVideoPlane
{
private:

	//Height and wwidth of the plane in 3D
	float m_fWidth; 
	float m_fHeight; 

	//Number of times to repeat the image.
	float m_fTile; 

	//Position of plane on the Y axis.
	float m_fYOffset;
	DWORD m_dwColor;

	//Image is inverted if this is set to true in the constructor
	bool m_fInputUpsidedown;

	//Image is mirrored if this is set to true in the constructor
	bool m_fInputRightLeft;

	//Number of vertices and indexes to vertices in the plane.
	UINT m_uIndices;
	UINT m_uVertices;

	//Pointer to array of indices to vertices that describe the plane
	CSmartPtr<WORD> m_srgwIndices;

	//Pointer to D3D managed memory for vertices
	CComPtr<IDirect3DVertexBuffer7> m_pvbVertices;

	//D3D object and device description information
	CComPtr<IDirect3D7> m_pD3D;
	CComPtr<IDirect3DDevice7> m_pD3DDevice;

	//The current local transformation matrix computed in the Draw() method.
	D3DXMATRIX m_matrixLocal;

	//Must be set to true for local transformations to be applied to the video plane!  This flag is used
	//as an optimization so that each transformation component doesn't need to be checked each frame.
	BOOL m_bLocalTransform;

	//Plane's transformation components.
	D3DXVECTOR3 m_vecTranslation;
	D3DXVECTOR3 m_vecRotation;
	D3DXVECTOR3 m_vecScale;
	D3DXVECTOR3 m_vecInitialScale;
	D3DXVECTOR3 m_vecCenter;

	//True for Melt transition.  Causes vertices to move according to velocities set in SetMeltIntensity().
	float m_fMeltIntensity;

	//Copy of vertex array for internal use.  Extends video buffer supplied to D3D to allow extra 
	//information to be held about each vertex.
	CSmartPtr<VIDEOPLANE_VERTEX_INTERNAL> m_pVertexTime0;

	//Number of rows and columns of polygons in the video plane
	int m_nPlaneSubdivisions;

	//Time to start fading video plane using alpha blending
	float m_fFadeStartProgress;

public:

	//Constructor
	CVideoPlane(LPDIRECT3D7 pD3D, LPDIRECT3DDEVICE7 pD3DDevice, bool fInputUpsidedown, bool fInputRightLeft);
	~CVideoPlane();

	//Resource management
	HRESULT Initialize(float fWidth, float fHeight, float fTile, DWORD dwColor, float fYOffset, bool bFrontPolys, bool bBackPolys, int nPlaneSubdivisions);
	HRESULT CreateSurfaces();
	HRESULT RestoreSurfaces();
	HRESULT ReleaseSurfaces();

	//Drawing
	HRESULT Draw(float fProgress);

	//Set animation for duration of transition.
	HRESULT SetFadeStart(float fFadeStartProgress);
	HRESULT SetFinalScale(float fX, float fY, float fZ);
	HRESULT SetMeltIntensity(float fMeltIntensity);
};


/*****************************************************************************
 * class CMM3DSpecialEffect - base class for D3D effects and transitions
 * 
 *****************************************************************************/
class CMM3DSpecialEffect : public CMMSpecialEffect  
{
protected:
	typedef CMMSpecialEffect _SEBaseClass;

	//Precision timer object
	CSmartPtr<CFrameTimer> m_pFrameTimer;

	//D3DX, direct 3d, and direct draw objects for using D3D.
	CComPtr<IDirectDraw7>	m_pDD;
	CComQIPtr<IDirect3D7, &IID_IDirect3D7>	m_pD3D;

	//D3D rendering device
	CComPtr<IDirect3DDevice7> m_pD3DDevice;
	D3DDEVICEDESC7    m_descD3DDevice;
	
	//Device capability flags
	BOOL m_fDeviceHasAlphablending;

	//The rendering targets and zbuffer.  
	//Rendering surface will be locked to the DXT's output buffer.
	CComPtr<IDirectDrawSurface7> m_pRenderSurface, m_pInitialRenderSurface;

	//zbuffer for depth checking
	bool m_bUseZBuffer;
	CComPtr<IDirectDrawSurface7> m_pZBuffer;

	//Camera's projection matrix
	D3DXMATRIX m_matProjection;

	//Cameras position and rotation as matrix
	D3DXMATRIX m_matView;

	//The root transform of the 3D scene
	D3DXMATRIX m_matPosition;

	//Camera position, orientation, and field of view.
	D3DXVECTOR3 m_vecPosition;
	D3DXVECTOR3 m_vecYPR;
	float m_fFov;

	//First time flag is true on first execute call.
	bool m_fFirstTime;

	//Ready flag indicates D3D device is created and ready for rendering.
	bool m_bReady;

	//Flags to indicate for which side of video plane to create polygons.
	bool m_bShowAFront, m_bShowABack,
		m_bShowBFront, m_bShowBBack;

	//ddraw surfaces to wrap the input video buffers.
	CComPtr<IDirectDrawSurface7> m_pInput1Surface, m_pInput2Surface;

	//Reset camera position to starting position.
	HRESULT ResetCameraVectors();

	//Creates the D3DX, D3D, and ddraw objects.  
	HRESULT CreateContext();

	//Resource management
	HRESULT RestoreContext();
	HRESULT ReleaseContext();

	//Create texture(s) from input video buffer(s).
	HRESULT CreateDXTextures(int nWidth, int nHeight);

	//Attach an input video buffer to a DDraw surface for use as a texture
	HRESULT LoadTextureFromMemoryARGB(BYTE* pBuff, long lPitch, RECT* pRect, IDirectDrawSurface7* pDDS);

	//Set and restore the camera's render target on the output buffer memory.
	HRESULT SetRenderTargetOnMemoryARGB(BYTE* pbBuffer, long lPitch, RECT* prcRect);
	HRESULT RestoreRenderTarget();

public:

		//Constructor.  Just pass call along to base class.
	CMM3DSpecialEffect(CMMSpecialEffectDXT* pDXT, LPCTSTR szName);

	// * Overloaded CMMSpecialEffect methods.
	// Inheriting classes should make sure to call these.
	virtual HRESULT Initialize( );
	virtual HRESULT Terminate();
	virtual HRESULT Execute();

	//Methods for inherting classing to overload to simplify rendering and resource management.
	//Pure virtual functions must be overridden in the class when inherits this class.
	virtual HRESULT CreateScene() = 0;
	virtual HRESULT ReleaseScene() = 0;
	virtual HRESULT RenderScene(float fProgress) = 0; 

	//Optional overridable methods to manage D3D memory for vertices.
	virtual HRESULT CreateSurfaces() { return E_NOTIMPL; } 
	virtual HRESULT RestoreSurfaces() { return E_NOTIMPL; } 
	virtual HRESULT ReleaseSurfaces()  { return E_NOTIMPL; } 

};

/*****************************************************************************
 * class CSimple3DSpecialEffect  -  class for manipulating input videos as one
 *									or two flat plans.
 *****************************************************************************/
class CSimple3DSpecialEffect : public CMM3DSpecialEffect 
{
protected:
	typedef CMM3DSpecialEffect _baseClass;
	
	//Input video planes
	CSmartPtr<CVideoPlane> m_spVideoPlane;
	CSmartPtr<CVideoPlane> m_spVideoPlane2;

	//Flags whether video planes should be rendered.
	BOOL m_bDisplayVideoPlane, m_bDisplayVideoPlane2;

	//If set to true, alpha blending will be enabled on the device before these are rendered.
	BOOL m_fAlphaBlendA;

	//Number of rows and columns of polygons in the video plane
	int m_nPlaneSubdivisions;

public:

	//Constructor
	CSimple3DSpecialEffect (CMMSpecialEffectDXT* pDXT, LPCTSTR szName) ;

	//Overrides from base classes
	virtual HRESULT Initialize();
	virtual HRESULT CreateScene();
	virtual HRESULT ReleaseScene();
	virtual HRESULT RenderScene(float fProgress);
	virtual HRESULT CreateSurfaces();
	virtual HRESULT RestoreSurfaces();
	virtual HRESULT ReleaseSurfaces();
};

#endif
