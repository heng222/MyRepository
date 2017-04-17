// Bounce.cpp : Implementation of CBounce
#include "stdafx.h"
#include "PWEffect.h"
#include "Bounce.h"

/////////////////////////////////////////////////////////////////////////////
// CBounce


//
//  --------------- CBounce ----------------
//
HRESULT CBounce::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    m_bDisplayOn = TRUE;
    
    // 
    m_ptRef.x = m_ptRef.y = 0;

    // 
    return S_OK; 
}

HRESULT CBounce::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here
    
    //
    return S_OK;
}

HRESULT CBounce::OnTerminate()
{    
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}



//////////////////////////////////////////////////////////////////////////
// Private methods

HRESULT CBounce::ResetControlValue()
{
    // Get width and height of surfaces
    int nWidth = Width();
    int nHeight = Height();
    
    // 
    m_ptRef.x = 0;
    m_ptRef.y = nHeight;

    //
    m_wMaxLength = 2*nHeight;
    
    return S_OK;
}

HRESULT CBounce::UpdateControlValue()
{
    INT nHeight = _basex::Height();
    FLOAT fProgress = _basex::GetProgress();

    INT iLiveLen = INT(fProgress*m_wMaxLength);

    if ( iLiveLen <= nHeight )
    {
        m_ptRef.y = nHeight - iLiveLen;
    }
    else if ( iLiveLen <= (nHeight+0.5*nHeight) )
    {
        if (m_iLastLen<=nHeight)
        {
            m_ptRef.y = 0;
        }
        else
        {
            m_ptRef.y = iLiveLen - nHeight;
        }
    }
    else // iCurlen<=m_wMaxLength
    {
        m_ptRef.y = 0.5*nHeight - (iLiveLen - 1.5*nHeight);
    }

    m_iLastLen = iLiveLen;

    return S_OK;
}

HRESULT CBounce::DrawLiveBitmap(IN HDC hInDC1,IN HDC hdcShow,IN HDC hOutDC)
{
    // 
    INT iWidth = _basex::Width();
    INT iHeight = _basex::Height();
        
    // Input2
    ::BitBlt(hOutDC,0,0,iWidth, iHeight-m_ptRef.y,
        hdcShow, m_ptRef.x, m_ptRef.y,SRCCOPY);

    return S_OK;
}
    
//////////////////////////////////////////////////////////////////////////
// Properties


