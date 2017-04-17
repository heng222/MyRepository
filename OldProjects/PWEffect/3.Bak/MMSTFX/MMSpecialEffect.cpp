/*****************************************************************************
 * module MMSpecialEffect.cpp 
 *
 *	implements shared code
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/
#include "stdafx.h"

#include "MMSpecialEffect.h"
#include "MMSpecialEffectDXT.h"
#include "D3dx.h"
#include <dxtmsft.h>
#include <DXHelper.h>

/******************************************************************************
 * Description: constructor
 *
 * CMMSpecialEffectDXT* pDXT - back pointer to container.
 * LPCTSTR szInternalName - internal name of effect.  From mapping in FilterBase::CreateSpecialEffectByName().
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
CMMSpecialEffect::CMMSpecialEffect(CMMSpecialEffectDXT* pDXT, LPCTSTR szInternalName)
{
	RTN_VOID_IF_BADPTR(pDXT);

	//Must pass in name for special effect or it won't work correctly.
	RTN_VOID_IF_FALSE(szInternalName && lstrlen(szInternalName) );

	//Store name 
	_tcsncpy(m_szInternalName, szInternalName, NAME_STR_LEN);
	m_pDXT = pDXT;

	//Reset variables
	RTN_VOID_IF_FAILED(ClearStandardOperations());
}

/******************************************************************************
 * Description: Do one-time setup of special effect
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffect::Initialize( )
{
	//Sanity check
	RTN_HR_IF_BADPTR(m_pDXT);

	//Get the Quality factor from the DXT and store it in the special effect object.
	//Determine the quality.  Movie Maker sets this value to 1.0 during publish and <= 0.5 during preview.
	//TODO: Use the quality value to speed up operations during preview and create better quality
	//output during publish (when movie file is created).
	float fltQualityFactor = 0.0;
	RTN_HR_IF_FAILED(m_pDXT->get_Quality(&fltQualityFactor));

	RTN_HR_IF_FAILED(InitStandardOperations());

	return S_OK;
}

/******************************************************************************
 * Description: Reset internal variables
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffect::ClearStandardOperations( )
{
	//Init settings to default values.
	m_fRed = m_fGreen = m_fBlue = DEFAULT_COLOR_VALUE;
	m_bDesaturate = false;
	m_fGamma = DEFAULT_GAMMA_VALUE;
	m_fInvert = DEFAULT_INVERT_VALUE;
	m_fBrightness = DEFAULT_BRIGHTNESS_VALUE;
	m_fContrast = DEFAULT_CONTRAST_VALUE;
	m_nPosterize = DEFAULT_POSTERIZE_VALUE;
	m_fThreshold = DEFAULT_THRESHOLD_VALUE;
	m_pLUT.Release();

	return S_OK;
}


/******************************************************************************
 * Description: Initialize the standard color mixing operations specified by
 * dynamic properties in the XML file.
 * 
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffect::InitStandardOperations( )
{
	HRESULT hr = S_OK;

	//Reset internal variables
	RTN_HR_IF_FAILED(ClearStandardOperations());

	float fValue = 0.0f;

	//Get the Blue adjust property.  
	RTN_HR_IF_FAILED(m_pDXT->get_Blue(&fValue));
	if (!IsEqual(fValue, 0.0f)) //If value is non-zero then store as amount of blue to add.
	{
		m_fBlue = fValue;
	}

	//TODO: Add code here for getting values of new properties you add to the object and XML.

	//Create Look up table builder for manipulating colors
	CComPtr<IDXLUTBuilder> m_pLUTBuilder;
	RTN_HR_IF_FAILED(m_pLUTBuilder.CoCreateInstance(CLSID_DXLUTBuilder));
	RTN_HR_IF_BADPTR(m_pLUTBuilder);

	//Max 256.  Set to 1 for now for linear color balancing.  Increase for finer color balancing.
	const int knNumberOfWeights = 1; 

	//Declare array to specify the order of coloring operations.
	OPIDDXLUTBUILDER rgopiLUTOrder[OPID_DXLUTBUILDER_NUM_OPS];

	//number of operations
	int nNumOperations = 0;

	//Has Invert (X-RAY) been requested?
	//Color inversion produces new color values that are the previous color values subtracted from 255. 
	//Only values above m_fInvert * 256 are inverted
	if (DEFAULT_INVERT_VALUE != m_fInvert)
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Invert;
		RTN_HR_IF_FAILED(m_pLUTBuilder->SetInvert(m_fInvert) );
	}

	//Has a color balance value been specified?
	if (DEFAULT_COLOR_VALUE != m_fRed || DEFAULT_COLOR_VALUE != m_fGreen || DEFAULT_COLOR_VALUE != m_fBlue)
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_ColorBalance;

		//Create color lookup tables
		float rgfRedWeights[knNumberOfWeights], rgfGreenWeights[knNumberOfWeights], rgfBlueWeights[knNumberOfWeights];
		float fRedWeight = 1.0f + m_fRed, 
			fGreenWeight = 1.0f + m_fGreen, 
			fBlueWeight = 1.0f + m_fBlue;
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

		RTN_HR_IF_FAILED(m_pLUTBuilder->SetColorBalance(DXLUTCOLOR_RED, knNumberOfWeights, rgfRedWeights));
		RTN_HR_IF_FAILED(m_pLUTBuilder->SetColorBalance(DXLUTCOLOR_GREEN, knNumberOfWeights, rgfGreenWeights));
		RTN_HR_IF_FAILED(m_pLUTBuilder->SetColorBalance(DXLUTCOLOR_BLUE, knNumberOfWeights, rgfBlueWeights));
	}


	//Has a Brightness correction been requested?
	//For brightness adjustment, each color channel value is multiplied by the Weights value. 
	//The adjustment is applied in ulCount steps over the 256 values of the lookup table. 
	//These values should be greater than or equal to zero and are usually around 1.0. 
	if (DEFAULT_BRIGHTNESS_VALUE != m_fBrightness)
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Brightness;
		RTN_HR_IF_FAILED(m_pLUTBuilder->SetBrightness(1, &m_fBrightness) );
	}

	//Has a Contrast correction been requested?
	//Contrast adjustments shift the range of each color channel around a midpoint. 
	//The adjustment is applied in ulCount (currently 1) steps over the 256 values of the lookup table.
	//These values should be greater than or equal to zero and are usually around 1.0. 
	if (DEFAULT_CONTRAST_VALUE != m_fContrast)
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Contrast;
		RTN_HR_IF_FAILED(m_pLUTBuilder->SetContrast(1, &m_fContrast) );
	}

	//Has a Posterize correction been requested?
	//Value is number of color levels that should remain after posterizing.
	if (DEFAULT_POSTERIZE_VALUE != m_nPosterize)
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Posterize;
		RTN_HR_IF_FAILED(m_pLUTBuilder->SetLevelsPerChannel(m_nPosterize) );
	}

	//Has a Threshold correction been requested?
	//For the threshold filtering adjustment, each sample color channel whose value is 
	//below newVal*255 is set to 0. Each color channel with a value equal to or above 
	//that threshold is set to 255.  
	//This number can range from 0.0 and 1.0. 
	if (DEFAULT_THRESHOLD_VALUE != m_fThreshold)
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Threshold;
		RTN_HR_IF_FAILED(m_pLUTBuilder->SetThreshold(m_fThreshold) );
	}

	//Has a gamma correction been requested?
	//This is a standard brightness adjustment. 
	//Gamma correction values of 1.0 produce no effect. 
	//This value must be greater than zero.	
	if (DEFAULT_GAMMA_VALUE != m_fGamma)
	{
		rgopiLUTOrder[nNumOperations++] = OPID_DXLUTBUILDER_Gamma;
		RTN_HR_IF_FAILED(m_pLUTBuilder->SetGamma(m_fGamma) );
	}

	//Set the order of operations
	if (nNumOperations)
		RTN_HR_IF_FAILED(m_pLUTBuilder->SetBuildOrder(rgopiLUTOrder, nNumOperations));

	//Finally create the look up table
	RTN_HR_IF_FAILED(m_pLUTBuilder->QueryInterface(&m_pLUT));
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
 * Description: Default Execute() operation is to simply copy buffer.
 * and apply dynamic color adjustment properties specified in the XML file.
 * For 3D effects and transitions, this method is overridden by CMM3DSpecialEffect.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CMMSpecialEffect::Execute()  
{ 
	DWORD* pdwInput = NULL,
		  *pdwOutput = NULL;

	//Get input buffer
	RTN_HR_IF_BADPTR(m_pDXT);
	RTN_HR_IF_FAILED(m_pDXT->GetInputBuffer((BYTE**) &pdwInput));
	RTN_HR_IF_BADPTR(pdwInput);

	//Get output buffer
	RTN_HR_IF_FAILED(m_pDXT->GetOutputBuffer((BYTE**) &pdwOutput));
	RTN_HR_IF_BADPTR(pdwOutput);

	int nWidth = -1, nHeight = -1;

	//Get width and height of surfaces
	RTN_HR_IF_BADPTR(m_pDXT);
	RTN_HR_IF_FAILED(m_pDXT->get_Width(&nWidth));
	RTN_HR_IF_FAILED(m_pDXT->get_Height(&nHeight));

	//Get the pitch of the surfaces.
	long lInputPitch = -1, lOutputPitch = -1;
	RTN_HR_IF_FAILED(m_pDXT->get_InputPitch(&lInputPitch));
	RTN_HR_IF_FAILED(m_pDXT->get_OutputPitch(&lOutputPitch));

	//Get the pitch in multiples of 4.
	long lSrcPitchDWORDS = ( ((long) lInputPitch + 3) / 4);
	long lSrcRowOffsetDWORDS = 0;
	
	//Get the pitch in multiples of 4.
	long lDestPitchDWORDS = ( ((long) lOutputPitch + 3) / 4);
	long lDestRowOffsetDWORDS = 0;

	//Store some handy values
	float fRatio = ((float) nWidth) / (float) nHeight;
	int nHalfDimDiff = (nWidth - nHeight) / 2;

	int nLastSrcRow = (nHeight - 1) * lSrcPitchDWORDS;

	//Now loop through each scanline.
	for (int j = 0; j < nHeight; j++)
	{
		//If desaturating, copy each pixel one at a time from the input buffer to the output buffer.
		if (m_bDesaturate)
		{
			float fJOffset = 0;

			//Loop across each row (destiation row)
			for (int i = 0; i < nWidth; i++)
			{
				int nOffsetSrc = lSrcRowOffsetDWORDS + i;
				int nOffsetDest = lDestRowOffsetDWORDS + i;

				//Desaturate pixel and store in output buffer
				RTN_HR_IF_FAILED(MakePixelGray(pdwOutput + nOffsetDest, pdwInput + nOffsetSrc));
			}
		}
		else
		{
			//Copy the whole line at a time.
			memcpy(pdwOutput + lDestRowOffsetDWORDS, pdwInput + lSrcRowOffsetDWORDS, nWidth * 4);
		}

		//Execute any standard color mixing operations.
		RTN_HR_IF_FAILED(ExecuteStandardOperations((DWORD*) pdwOutput + lDestRowOffsetDWORDS, nWidth));

		lSrcRowOffsetDWORDS += lSrcPitchDWORDS;
		lDestRowOffsetDWORDS += lDestPitchDWORDS;
	}

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
HRESULT CMMSpecialEffect::ExecuteStandardOperations(DWORD* pdwBuffer, int nWidth)  
{
	RTN_HR_IF_BADPTR(m_pLUT);

	//Apply our lookup table.
	return m_pLUT->ApplyTables( (DXSAMPLE*) pdwBuffer, nWidth);
}

/******************************************************************************
 * Description: Returns true if number of inputs to filter is 2,
 *				otherwise returns false.
 *
 * Returns: 
 *   bool
 ******************************************************************************/
BOOL CMMSpecialEffect::IsTransition()
{
	RTN_FALSE_IF_BADPTR(m_pDXT);
	
	int nInputs = 0;

	RTN_FALSE_IF_FAILED(m_pDXT->get_NumInputs(&nInputs));

	return nInputs == 2;
}

