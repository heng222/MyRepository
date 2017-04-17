// PixelPlay.cpp : Implementation of CPixelPlay
#include "stdafx.h"
#include "PixelPlay.h"

/////////////////////////////////////////////////////////////////////////////
// CPixelPlay


//
//  --------------- CPixelPlay ----------------
//
HRESULT CPixelPlay::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // 
	m_iA2VRatio = 10;
	m_iR2ARatio = 1;
    
    return S_OK;
}

HRESULT CPixelPlay::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here
    
    //
    return S_OK;
}

HRESULT CPixelPlay::OnTerminate()
{

    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


// 
HRESULT CPixelPlay::OnImplEffect(IN DWORD* pInputBuf,
                                 IN DWORD* pOutputBuf,
                                 IN INT iWidth,
                                 IN INT iHeight)
{
	FLOAT fTransRatio = _thisx::GetTransRatio();
	if (fTransRatio<=1)
	{
		return E_NOTIMPL;
	}	
	
	// Pixelate
    Pixelate(pInputBuf,pOutputBuf);

	
    //
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Private methods
FLOAT CPixelPlay::GetTransRatio() const
{
	ASSERT(m_iR2ARatio!=0 && m_iA2VRatio!=0);

	FLOAT value = 1.0;

#if 0
	// 
	if (m_iR2ARatio>1)
	{
		value *= m_iR2ARatio;
	}
	else
	{
		value /= abs(m_iR2ARatio);
	}
#endif

	// 
	if (m_iA2VRatio>1)
	{
		value *= m_iA2VRatio;
	}
	else
	{
		value /= abs(m_iA2VRatio);
	}

	return value;
}

HRESULT  CPixelPlay::Pixelate(DWORD* pInput,DWORD* pOutput)
{
    // variable
    DXSAMPLE clrAvg;
    LONG lOffset;

    //
    INT iRatio = abs(m_iA2VRatio);

	INT iDestHeight = _basex::Height()/iRatio;
	INT	iDestWidth = _basex::Width()/iRatio;
    
    // pixelate the largest block region.
	for (INT i=0; i<iDestHeight; i++)
	{
        for (INT j=0; j<iDestWidth; j++)
        {
            lOffset = i*iRatio*_basex::Width() + j*iRatio;

            clrAvg = CalcAvgColor((DXSAMPLE*)(pInput+lOffset),
                iRatio,iRatio);

            SetColor((DXSAMPLE*)(pOutput+lOffset),
                iRatio,iRatio,clrAvg);
        }
	}

    // remaining pixels
    INT iRemainHeight = _basex::Height() - iDestHeight*iRatio;
    INT iRemainWidth = _basex::Width() - iDestWidth*iRatio;

    // Pixelate the remaining top band.
    if (iRemainHeight>0)
    {
        for (INT m=0; m<iDestWidth; m++)
        {
            lOffset = iDestHeight*iRatio*_basex::Width() + m*iRatio;

            clrAvg = CalcAvgColor((DXSAMPLE*)(pInput+lOffset),
                        iRatio,
                        iRemainHeight);
            
            SetColor((DXSAMPLE*)(pOutput+lOffset),
                iRatio,iRemainHeight,clrAvg);
        }

        if (iRemainWidth>0)
        {
            lOffset = iDestHeight*iRatio*_basex::Width();
            lOffset += iDestWidth*iRatio;

            clrAvg = CalcAvgColor((DXSAMPLE*)(pInput+lOffset),
                iRemainWidth,
                iRemainHeight);
            
            SetColor((DXSAMPLE*)(pOutput+lOffset),
                iRemainWidth,iRemainHeight,clrAvg);
        }
    }

    // Pixelate the remaining right band.
    if (iRemainWidth>0)
    {
        for (INT k=0; k<iDestHeight; k++)
        {
            lOffset = iRatio*iDestWidth + k*iRatio*_basex::Width();

            clrAvg = CalcAvgColor((DXSAMPLE*)(pInput+lOffset),
                iRemainWidth,
                iRatio);
            
            SetColor((DXSAMPLE*)(pOutput+lOffset),
                iRemainWidth,iRatio,clrAvg);

        }
    }

	return S_OK;
}

DXSAMPLE CPixelPlay::CalcAvgColor(DXSAMPLE* pIn,INT iWidth,INT iHeight) const
{
    ASSERT(iWidth<=_basex::Width());
    ASSERT(iHeight<=_basex::Height());

    // 
    DWORD dwR = 0;
    DWORD dwG = 0;
    DWORD dwB = 0;

    for (INT i=0; i<iHeight; i++)
    {
        for (INT j=0; j<iWidth; j++)
        {
            DWORD dwColor = *(pIn+j);
            dwR += _basex::GetRed(dwColor);
            dwG += _basex::GetGreen(dwColor);
            dwB += _basex::GetBlue(dwColor);
        }

        pIn += _basex::Width();
    }

    // average
    dwR /= iHeight*iWidth;
    dwG /= iHeight*iWidth;
    dwB /= iHeight*iWidth;

    return _basex::MakeDXSAMPLE((BYTE)dwR,(BYTE)dwG,(BYTE)dwB);
}

void CPixelPlay::SetColor(DXSAMPLE* pIn,INT iWidth,INT iHeight,DXSAMPLE clrNew) const
{
    ASSERT(iWidth<=_basex::Width());
    ASSERT(iHeight<=_basex::Height());
    
    // 
    for (INT i=0; i<iHeight; i++)
    {
        for (INT j=0; j<iWidth; j++)
        {
            *(pIn+j) = clrNew;
        }
        
        pIn += _basex::Width();
    }

}

//////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CPixelPlay::get_A2VRatio(INT *pVal)
{
	// TODO: Add your implementation code here
	RTN_HR_IF_BADPTR(pVal);
	*pVal = m_iA2VRatio;

	return S_OK;
}

STDMETHODIMP CPixelPlay::put_A2VRatio(INT newVal)
{
	// TODO: Add your implementation code here
	if (newVal==0)
	{
		return E_FAIL;
	}

	m_iA2VRatio = newVal;

	return S_OK;
}


STDMETHODIMP CPixelPlay::get_R2ARatio(INT *pVal)
{
	// TODO: Add your implementation code here
	RTN_HR_IF_BADPTR(pVal);
	*pVal = m_iR2ARatio;

	return S_OK;
}

STDMETHODIMP CPixelPlay::put_R2ARatio(INT newVal)
{
	// TODO: Add your implementation code here
	if (newVal==0)
	{
		return E_FAIL;
	}

	m_iR2ARatio = newVal;

	return S_OK;
}
