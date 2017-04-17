// Fade.cpp : Implementation of CFade
#include "stdafx.h"
#include "Fade.h"

/////////////////////////////////////////////////////////////////////////////
// CFade

//
//  --------------- CFade ----------------
//
HRESULT CFade::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    //
    m_bDisplayOn = TRUE;    
    m_clrOriginal = 0; // Black

    return S_OK;
}

HRESULT CFade::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here

            
    //
    return S_OK;
}

HRESULT CFade::OnTerminate()
{
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods

HRESULT CFade::ResetControlValue()
{
    // 
    return S_OK;
}

HRESULT CFade::UpdateControlValue()
{
    // 
    return S_OK;
}

HRESULT CFade::Initialize()
{
    //
    return S_OK;
}

HRESULT CFade::OnTransform(IN DWORD* pInput1Buf,
                           IN DWORD* pInput2Buf,
                           IN DWORD* pOutputBuf)
{    
    FLOAT fProgress = _basex::GetProgress();

    INT iWidth = Width();
    INT iHeight = Height();
  
    // Now loop through each scanline.
    for (int j = 0; j < iHeight; j++)
    {
        // Loop across each row (destination row)
        for (int i = 0; i < iWidth; i++)
        {            
            // Desaturate pixel and store in output buffer
            RTN_HR_IF_FAILED(
                AdjustPixel( pOutputBuf, pInput1Buf, pInput2Buf,fProgress));

            // Next pixel.
            pOutputBuf++;
            pInput1Buf++;
            pInput2Buf++;            
        }
    }

    //
    return S_OK;
}


HRESULT CFade::AdjustPixel(DWORD* pdwOutput, 
                           const DWORD* pBufHide,
                           const DWORD* pBufShow,
                           FLOAT fRatio) const
{
    RTN_HR_IF_BADPTR(pdwOutput);
    RTN_HR_IF_BADPTR(pBufHide);
    RTN_HR_IF_BADPTR(pBufShow);

    
    // Buffer to show
    BYTE rShow	= _basex::GetRed(*pBufShow);
    BYTE gShow	= _basex::GetGreen(*pBufShow);
    BYTE bShow	= _basex::GetBlue(*pBufShow);

    // Buffer to hide
    BYTE rHide	= _basex::GetRed(*pBufHide);
    BYTE gHide	= _basex::GetGreen(*pBufHide);
    BYTE bHide	= _basex::GetBlue(*pBufHide);
    
    // output 
    BYTE rDest, gDest, bDest;
    rDest = rShow * (fRatio) + rHide * (1.0 - fRatio);
    gDest = gShow * (fRatio) + gHide * (1.0 - fRatio);
    bDest = bShow * (fRatio) + bHide * (1.0 - fRatio);
    
    *pdwOutput = _basex::MakeDXSAMPLE(rDest,gDest,bDest);

    return S_OK;
}




//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CFade::get_State(BOOL *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bDisplayOn;
    return S_OK;
}

STDMETHODIMP CFade::put_State(BOOL newVal)
{
    // TODO: Add your implementation code here
    m_bDisplayOn = newVal;
    return S_OK;
}