// WrapAround.cpp : Implementation of CWrapAround
#include "stdafx.h"
#include "WrapAround.h"

/////////////////////////////////////////////////////////////////////////////
// CWrapAround


//
//  --------------- CWrapAround ----------------
//
HRESULT CWrapAround::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    m_hdcLive  = NULL;
    m_hbmpLive = NULL;
    m_hBrush = NULL;

    // 
    m_iRate = 5;
    m_iDirection = ED_LEFT;
    m_iSpacing = 0;
    
    return S_OK;
}

HRESULT CWrapAround::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here

    // Create DC
    ASSERT(m_hdcLive==NULL);
    m_hdcLive = ::CreateCompatibleDC(NULL);
    RTN_HR_IF_BADNEW(m_hdcLive);
    
    // Create Bitmap
    ASSERT(m_hbmpLive==NULL);
    m_hbmpLive = ::CreateCompatibleBitmap(CAutoDeskDC(),
        _basex::Width(),    _basex::Height());
    RTN_HR_IF_BADNEW(m_hbmpLive);
    
    // select bitmap to dc.
    ::SelectObject(m_hdcLive,m_hbmpLive);

    // Create bush
    if (m_hBrush==NULL)
    {
        m_hBrush = ::CreateSolidBrush(m_clrBackground);
    }

    // 
    ResetControlValue();

    //
    return S_OK;
}

// On start to play
HRESULT CWrapAround::OnStart()
{
    ResetControlValue();
    return S_OK;
}


// On duration changed.
HRESULT CWrapAround::OnDurationChanged(FLOAT fNewDur)
{
    ResetControlValue();
    return S_OK;
}


HRESULT CWrapAround::OnTerminate()
{
    if (m_hdcLive)
    {
        ::DeleteDC(m_hdcLive);
        m_hdcLive = NULL;
    }
    
    if (m_hbmpLive)
    {
        ::DeleteObject(m_hbmpLive);
        m_hbmpLive = NULL;
    }

    if (m_hBrush)
    {
        ::DeleteObject(m_hBrush);
        m_hBrush = NULL;
    }
   
    
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


// 
HRESULT CWrapAround::OnImplEffect(IN DWORD* pInputBuf,
                                 IN DWORD* pOutputBuf,
                                 IN INT iWidth,
                                 IN INT iHeight)
{   
    
    // update control value
    HRESULT hr = UpdateControlValue();
    if (hr==S_FALSE)
    {
        return E_NOTIMPL;
    }
    
    BOOL rc = S_OK;
    
    
    // Create a bitmap of input surface. 
    HBITMAP hInputBitmap = _basex::CreateSufaceBitmap(
        iWidth,iHeight,pInputBuf);   
    
    // Select it to the DC.
    HDC hMemDC = _basex::GetMemDC();
    HANDLE hOldBmp = ::SelectObject(hMemDC,hInputBitmap);
    if (hOldBmp==NULL)
    {
        rc = E_FAIL;
    }
    
    if ( SUCCEEDED(rc) )
    {
        // Draw live image
        DrawLiveBitmap(hMemDC,m_hdcLive);
        
        // the DIB info we used to get title pixel-mapping.
        BITMAPINFO bmi;
        _basex::GetSurfaceBmpInfo(bmi);
        
        // get DIB's bits.
        LONG lLines = ::GetDIBits( m_hdcLive, m_hbmpLive, 0, iHeight, 
            (PVOID)pOutputBuf, 
            (BITMAPINFO *)&bmi, 
            DIB_RGB_COLORS );
        
        if (lLines!=iHeight)
        {
            rc = E_FAIL;
        }
    }
    
    // 
    ::DeleteObject(hInputBitmap);
    _basex::ReleaseMemDC(); // must call release after use.
    
    
    //
	return rc;
}


//////////////////////////////////////////////////////////////////////////
// Private methods

HRESULT CWrapAround::ResetControlValue()
{
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();
    TMRect rExtent(0,0,nWidth,nHeight);
    DOUBLE fAngle = 0;

    if (m_iDirection==ED_LEFT)
    {
        fAngle = PIRADIAN;
    }
    else if (m_iDirection==ED_RIGHT)
    {
        fAngle = 0;
    }
    else if (m_iDirection==ED_UP)
    {
        fAngle = -PIRADIAN/2;
    }
    else if (m_iDirection==ED_DOWN)
    {
        fAngle = PIRADIAN/2;
    }
    else
    {
        ASSERT(0);
        return E_FAIL;
    }
    
    m_rectTravel.Initialize(rExtent,rExtent,fAngle,FALSE);

    // max travel length
    m_dwMaxTravelLen = (DWORD)(_basex::GetDuration()*FRAMERATE*m_iRate);

    // 
    return S_OK;
}

HRESULT CWrapAround::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
    DWORD dwTravelLen = (DWORD)(fProgress*m_dwMaxTravelLen);

    m_rectTravel.Travel(dwTravelLen);
    // 
    return S_OK;
}

HRESULT CWrapAround::DrawLiveBitmap(HDC hdcSrc,HDC hdcDest)
{

    // store some handy values
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();  
    if (m_hBrush==NULL)
    {
        return S_FALSE;
    }
    else
    {
        RECT rBkg = {0,0,nWidth,nHeight};
        ::FillRect(hdcDest,&rBkg,m_hBrush);
    }  
    
    
    // travel to draw
    RECT rLive,rExtent;
    m_rectTravel.GetExetent(rExtent);
    m_rectTravel.GetLiveRect(rLive);

    // the live(intersect) part
    ::BitBlt(hdcDest,rLive.left,rLive.top,nWidth,nHeight,
        hdcSrc,0,0,SRCCOPY);
    
    // another part.
    if (m_iDirection==ED_LEFT || m_iDirection==ED_RIGHT)
    {
        if (rLive.left<rExtent.left)
        {
            ::BitBlt(hdcDest,
                rLive.right+m_iSpacing, rLive.top,
                nWidth, nHeight,
                hdcSrc, 0, 0,
                SRCCOPY);
        }
        else
        {
            ::BitBlt(hdcDest,
                rLive.left - nWidth - m_iSpacing, rLive.top,
                nWidth, nHeight,
                hdcSrc, 0, 0,
                SRCCOPY);  
        }
    }
    else if (m_iDirection==ED_UP || m_iDirection==ED_DOWN)
    {
        if (rLive.top<rExtent.top)
        {            
            ::BitBlt(hdcDest, rLive.left, rLive.bottom+m_iSpacing,
                nWidth, nHeight,
                hdcSrc, 0, 0,
                SRCCOPY);
        }
        else
        {
            ::BitBlt(hdcDest, 0 , rLive.top-nHeight-m_iSpacing,
                nWidth, nHeight,
                hdcSrc, 0, 0,
                SRCCOPY);
        }
    }
    // 
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Properties



STDMETHODIMP CWrapAround::get_Rate(INT *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iRate;
	return S_OK;
}

STDMETHODIMP CWrapAround::put_Rate(INT newVal)
{
	// TODO: Add your implementation code here
    if (newVal<0)
    {
        return E_INVALIDARG;
    }
    m_iRate = newVal;
	return S_OK;
}

STDMETHODIMP CWrapAround::get_Direction(INT *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iDirection;

	return S_OK;
}

STDMETHODIMP CWrapAround::put_Direction(INT newVal)
{
	// TODO: Add your implementation code here
    m_iDirection = (TSingleDir)newVal;
	return S_OK;
}

STDMETHODIMP CWrapAround::get_Spacing(INT *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iSpacing;
	return S_OK;
}

STDMETHODIMP CWrapAround::put_Spacing(INT newVal)
{
	// TODO: Add your implementation code here
    if (newVal>=0)
    {
        m_iSpacing = newVal;
    }
    else
    {
        return E_INVALIDARG;
    }

	return S_OK;
}
