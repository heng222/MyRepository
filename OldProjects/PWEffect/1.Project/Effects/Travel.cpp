// Travel.cpp : Implementation of CTravel
#include "stdafx.h"
#include "Travel.h"

/////////////////////////////////////////////////////////////////////////////
// CTravel


//
//  --------------- CTravel ----------------
//
HRESULT CTravel::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // default value of properties.
    m_iRate = -1;
    m_fAngle = 0.0f; // Right
    m_bCircular = FALSE;
    m_iSpacing = 0;
    
    //
    m_hdcCanvas = NULL;
    m_hbmpCanvas = NULL;
    m_hBrush = NULL;
    m_lMaxLen = 0;
    
    return S_OK;
}

HRESULT CTravel::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here
    
    // Initialize the control value.
    Initialize();

    //
    return S_OK;
}

HRESULT CTravel::OnStart()
{
    // 
    return S_OK;
}

HRESULT CTravel::OnTerminate()
{
    if (m_hdcCanvas)
    {
        ::DeleteDC(m_hdcCanvas);
        m_hdcCanvas = NULL;
    }

    if (m_hbmpCanvas)
    {
        ::DeleteObject(m_hbmpCanvas);
        m_hbmpCanvas = NULL;
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
HRESULT CTravel::OnImplEffect(IN DWORD* pInputBuf,
                              IN DWORD* pOutputBuf,
                              IN INT iWidth,
                              IN INT iHeight)
{
    BOOL bFlag = _thisx::UpdateControlValue();
    if (!bFlag)
    {
        return E_NOTIMPL;
    }    
    
    // Create a bitmap of input surface. 
    HBITMAP hInputBitmap = _basex::CreateSufaceBitmap(
        iWidth,iHeight,pInputBuf);
    
    // Select it to the DC.
    HDC hMemDC = _basex::GetMemDC();
    HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC,hInputBitmap);
    
    // Draw live image.
    _thisx::DrawLiveImage(hMemDC,m_hdcCanvas);
    
    // the DIB info we used to get title pixel-mapping.
    BITMAPINFO bmi;
    _basex::GetSurfaceBmpInfo(bmi);
    
    // get DIB's bits.
    LONG lLines = ::GetDIBits( m_hdcCanvas, m_hbmpCanvas, 0, iHeight, 
        (PVOID)pOutputBuf, 
        (BITMAPINFO *)&bmi, 
        DIB_RGB_COLORS);
    
    // 
    ::SelectObject(hMemDC,hOldBmp);
    ::DeleteObject(hInputBitmap);
    _basex::ReleaseMemDC();
    
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods
BOOL CTravel::Initialize()
{
    INT nWidth = _basex::Width();
    INT nHeight = _basex::Height();
    
    // Create DC
    if (m_hdcCanvas==NULL)
    {
        m_hdcCanvas = ::CreateCompatibleDC(NULL);
        RTN_FALSE_IF_BADPTR(m_hdcCanvas);
    }
    
    // Create Bitmap
    if (m_hbmpCanvas==NULL)
    {
        m_hbmpCanvas = ::CreateCompatibleBitmap(CAutoDeskDC(),
            nWidth, nHeight);
        RTN_FALSE_IF_BADPTR(m_hbmpCanvas);
        ::SelectObject(m_hdcCanvas,m_hbmpCanvas);
    }
    
    // Create brush
    if (m_hBrush==NULL)
    {
        m_hBrush = ::CreateSolidBrush(m_clrBackground);
    }
    
    
    // Initialize travel-rectangle.
    
    TMRect rectCanvas(0,0,
        _basex::Width(),_basex::Height());
    
    m_TravelRectOn.Initialize(rectCanvas,
        rectCanvas, m_fAngle, TRUE);
    
    m_TravelRectOff.Initialize(rectCanvas,
        rectCanvas, m_fAngle, FALSE);    
    
    m_lMaxLen = (DWORD)(_basex::GetDuration()*FRAMERATE*m_iRate);
    //m_lMaxLen = m_TravelRectOn.GetMaxTravelLen();
    
    return TRUE;
}

BOOL CTravel::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
    if (m_iRate<0)
    {
        m_TravelRectOn.TravelP(fProgress);
        m_TravelRectOff.TravelP(fProgress);
    }
    else
    {
        LONG lLiveLen = fProgress*m_lMaxLen;
        m_TravelRectOn.Travel(lLiveLen);
        m_TravelRectOff.Travel(lLiveLen);
        if (m_bCircular && m_iSpacing>0)
        {
            CTravelRect::TPosType iPosType = 
                m_TravelRectOn.GetPositionType(m_TravelRectOff);
            if (iPosType==CTravelRect::EBackward)
            {
                m_TravelRectOff.Travel(lLiveLen+m_iSpacing);
            }
            else
            {
                m_TravelRectOn.Travel(lLiveLen+m_iSpacing);
            }
        }
    }
    
    return TRUE;
}



void CTravel::DrawLiveImage(HDC hdcSource,
                            HDC hdcOutput)
{
    INT nWidth = _basex::Width();
    INT nHeight = _basex::Height();
    
    // Fill background to specified color
    RECT rExtent = {0,0, nWidth, nHeight };
    ::FillRect(hdcOutput,&rExtent,m_hBrush);
        
    // travel to draw
    RECT rDest,rSource;   
    CTravelRect* pTR = NULL;
    
    // Show region traveling on .
    pTR = &m_TravelRectOn;
    if (!pTR->HasTraveledOut())
    {
        pTR->GetIntersectRect(rDest);
        pTR->GetIntersectRectEx(rSource);
        ::BitBlt(hdcOutput, 
            rDest.left,
            rDest.top, 
            rDest.right-rDest.left,
            rDest.bottom-rDest.top, 
            hdcSource, 
            rSource.left, 
            rSource.top, 
            SRCCOPY);
    }
    
    // Show region traveling off.
    if (m_bCircular)
    {
        pTR = &m_TravelRectOff;
        if (!pTR->HasTraveledOut())
        {
            pTR->GetIntersectRect(rDest);
            pTR->GetIntersectRectEx(rSource);
            ::BitBlt(hdcOutput, 
                rDest.left,
                rDest.top, 
                rDest.right-rDest.left,
                rDest.bottom-rDest.top, 
                hdcSource, 
                rSource.left, 
                rSource.top, 
                SRCCOPY);
        }
    }    
}

//////////////////////////////////////////////////////////////////////////
// Properties


STDMETHODIMP CTravel::get_Rate(INT *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_iRate;
	return S_OK;
}

STDMETHODIMP CTravel::put_Rate(INT newVal)
{
	// TODO: Add your implementation code here
    m_iRate = newVal;
	return S_OK;
}

STDMETHODIMP CTravel::get_Angle(FLOAT *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_fAngle*180/PIRADIAN;
	return S_OK;
}

STDMETHODIMP CTravel::put_Angle(FLOAT newVal)
{
	// TODO: Add your implementation code here
    m_fAngle = newVal*PIRADIAN/180;
	return S_OK;
}

STDMETHODIMP CTravel::get_Circular(BOOL *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bCircular;
	return S_OK;
}

STDMETHODIMP CTravel::put_Circular(BOOL newVal)
{
	// TODO: Add your implementation code here
    m_bCircular = newVal;
	return S_OK;
}

STDMETHODIMP CTravel::get_Spacing(INT *pVal)
{
	// TODO: Add your implementation code here
    
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iSpacing;
	return S_OK;
}

STDMETHODIMP CTravel::put_Spacing(INT newVal)
{
	// TODO: Add your implementation code here
    if (newVal<0)
    {
        return E_INVALIDARG;
    }
    m_iSpacing = newVal;
	return S_OK;
}
