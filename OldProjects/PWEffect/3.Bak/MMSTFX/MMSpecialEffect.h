/*****************************************************************************
 * module MMSpecialEffect.h 
 *
 *	Contains the class CMMSpecialEffect for performing simple image processing effects as color, 
 *	brightness, and constrast adjustments on an input video buffer.  The sample effect Blue Adjust 
 *	uses this class to adjust the amount of blue in the video.
 *	
 *	CMMSpecialEffect is a base class.  By overriding the Initialize(), Execute() and Terminate() 
 *	methods	entirly new effects and transitions may be created.
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/
#ifndef MMSpecialEffect_H
#define MMSpecialEffect_H

#include "MMSTFX.h"
#include "math.h" //fabs

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

//Convenience inline method to compare floating point values based on a tolerance.
#define FLOAT_TOLERANCE 0.0001

//String size of m_szInternalName
#define NAME_STR_LEN 64

inline bool IsEqual(float f1, float f2)
{
	return fabs(f1 - f2) < FLOAT_TOLERANCE;
}

//Forward definition of DXT object which is hosting this special effect object.
class CMMSpecialEffectDXT;

/*****************************************************************************
 * class CMMSpecialEffect -		SpecialEffects objects hosted by CMMSpecialEffect
 *****************************************************************************/
class CMMSpecialEffect 
{
private:

protected:
	//Back pointer to container class
	CMMSpecialEffectDXT* m_pDXT;

	//Name of as specified to the DXT's CreateSpecialEffectByName() property.
	//Will be "Standard" or "Simple3D" in this sample code.
	TCHAR m_szInternalName[NAME_STR_LEN];

	//Quality factor.  Acquired from DXT which is hosting this object.
	float m_fltQualityFactor;	

	//Standard operation variables for the "Standard" special effect.
	bool m_bDesaturate;

	//Color adjustment values.  
	float m_fRed;
	float m_fGreen;
	float m_fBlue;

	//Color operations that may be applied to image.
	float m_fInvert;
	float m_fGamma;
	float m_fBrightness;
	float m_fContrast;
	float m_fThreshold;
	int   m_nPosterize;

	CComPtr<IDXLookupTable> m_pLUT;	//Color adjustment object provided by DXTransform SDK.
										//Used to alter amount of red, green, blue, brightness, contrast, and brightness
										//and to apply posterize and threshold effects.

public:	

	CMMSpecialEffect(CMMSpecialEffectDXT* pDXT, LPCTSTR szInternalName);

	//Overloadable Methods
	virtual HRESULT Initialize();
	virtual HRESULT Terminate() { return E_NOTIMPL; }
	virtual HRESULT Execute();
	
	//Misc
	BOOL IsTransition();

	//Standard color mixer operations for basic effects.
	HRESULT ClearStandardOperations();
	HRESULT InitStandardOperations();
	HRESULT ExecuteStandardOperations(DWORD* pdwBuffer, int nWidth);

};

#endif