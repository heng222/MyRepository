// Snow.cpp : Implementation of CSnow
#include "stdafx.h"
#include <WinBase.h>

#include "Snow.h"
#include "TMPoint.h"

/////////////////////////////////////////////////////////////////////////////
// CSnow

 
//
//  --------------- CSnow ----------------
//
HRESULT CSnow::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());

    //
    m_clrSnow = RGB(255,255,255);
    m_iRate = 5; // 5 pixels per frame.
    m_fAmount = 0.1f;
    
    // 
    m_hDCSnow = ::CreateCompatibleDC(NULL);
    m_hBmpSnow = NULL;
    m_hPenSnow = NULL;

    m_ptSeparator.x = m_ptSeparator.y = 0;
    m_bRounding = FALSE;
    
    return S_OK;
}

HRESULT CSnow::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your codes after here.
    
    // Seed the random-number generator with GetTickCount so that
    // the numbers will be different every time we run.
    ::srand(::GetTickCount());

    // Initialize control value.
    m_ptSeparator.x = 0;
    m_ptSeparator.y = _thisx::GetSkyHeight();
    m_bRounding = FALSE;

    // create the pen to draw snow.
    RTN_HR_IF_FALSE(CreateSnowPen());

    //
    if (m_hBmpSnow==NULL)
    {
        INT nSkyWidth = _thisx::GetSkyWidth();
        INT nSkyHeight = _thisx::GetSkyHeight();
        m_hBmpSnow = _thisx::CreateSnowImg(m_hDCSnow,nSkyWidth,nSkyHeight);
    }

    //
    return S_OK;
}

HRESULT CSnow::OnStart()
{
    // Initialize control value.
    m_ptSeparator.x = 0;
    m_ptSeparator.y = _thisx::GetSkyHeight();
    m_bRounding = FALSE;

    //
    return S_OK;
}

HRESULT CSnow::OnTerminate()
{
    if (m_hDCSnow!=NULL)
    {
        ::DeleteDC(m_hDCSnow);
        m_hDCSnow = NULL;
    }

    if (m_hBmpSnow!=NULL)
    {
        ::DeleteObject(m_hBmpSnow);
        m_hBmpSnow = NULL;
    }

    if (m_hPenSnow)
    {
        ::DeleteObject(m_hPenSnow);
        m_hPenSnow = NULL;
    }
    
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


// 
HRESULT CSnow::OnImplEffect(IN DWORD* pInputBuf,
                                 IN DWORD* pOutputBuf,
                                 IN INT iWidth,
                                 IN INT iHeight)
{
    
    if (m_clrSnow==0) // Transparent
    {
        return E_NOTIMPL;
    }

    // Create a bitmap of input surface.    
    HBITMAP hInputBitmap = _basex::CreateSufaceBitmap(
        iWidth,iHeight,pInputBuf);
    
    // Select it to the DC.
    HDC hMemDC = _basex::GetMemDC();
    HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC,hInputBitmap);
    
    // Draw Title
    ImplementSnowing(hMemDC);

    //
    // the DIB info we used to get title pixel-mapping.
    BITMAPINFO bmi;
    _basex::GetSurfaceBmpInfo(bmi);
    
    //
    
    // get DIB's bits.
    LONG lLines = ::GetDIBits( CAutoDeskDC(), hInputBitmap, 0, iHeight, 
        (PVOID)pOutputBuf, 
        (BITMAPINFO *)&bmi, 
        DIB_RGB_COLORS);
    
    // 
    ::SelectObject(hMemDC,hOldBmp);
    ::DeleteObject(hInputBitmap);
    _basex::ReleaseMemDC();
    
    //
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods

void CSnow::ImplementSnowing(HDC hdcDest)
{
    ASSERT(m_hDCSnow!=NULL);
    ASSERT(m_hBmpSnow!=NULL);

    
    INT nSkyWidth = _thisx::GetSkyWidth();
    INT nSkyHeight = _thisx::GetSkyHeight();

    COLORREF clrTransparent = _thisx::GetSkyColor();

    INT iUpperHeight = nSkyHeight - m_ptSeparator.y;
    
    // upper image    
    if (iUpperHeight<=_basex::Height())
    {
        ::TransparentBlt(hdcDest,// Dest
            0,0,
            _basex::Width(), iUpperHeight, 
            
            m_hDCSnow, // Source
            m_ptSeparator.x, m_ptSeparator.y,
            nSkyWidth, iUpperHeight,
            clrTransparent );
    }
    else
    {
        ::TransparentBlt(hdcDest,// Dest
            0,0,
            _basex::Width(), _basex::Height(), 
            
            m_hDCSnow, // Source
            m_ptSeparator.x, m_ptSeparator.y,
            nSkyWidth, _basex::Height(),
            clrTransparent );
    }
    
    
    // lower image
    if (m_bRounding)
    {
        INT iLowerHeight = _basex::Height() - iUpperHeight;

        if ( iLowerHeight>0 )
        {
            ::TransparentBlt( hdcDest,
                0, iUpperHeight,
                _basex::Width(),iLowerHeight, // Dest 
                
                m_hDCSnow, // Source
                0,0,
                nSkyWidth, iLowerHeight,
            clrTransparent );
        }
    }

    // update the position .
    UpdateSeparatorPos();
}

void CSnow::UpdateSeparatorPos()
{
    INT iNewY = m_ptSeparator.y - m_iRate;

    // 
    if (iNewY>=0)
    {
        m_ptSeparator.y = iNewY;
    }
    else
    {
        m_ptSeparator.y = _thisx::GetSkyHeight() - abs(iNewY);
        m_bRounding = TRUE;
    }
    
}


COLORREF CSnow::GetSkyColor() const
{
    return ( ~m_clrSnow );
}


INT CSnow::GetSkyWidth() const
{
    // Must >= _basex::Width()
    return _basex::Width();
}

INT CSnow::GetSkyHeight() const
{
    // must >= _basex::Height() !!!
    return _basex::Height()*5;
}

INT CSnow::GetFlakeWidth() const
{
    if (m_fAmount>0.66)
    {
        return 8;
    }
    else if (m_fAmount>0.33)
    {
        return 6;
    }
    else
    {
        return 4;
    }

}

INT CSnow::GetFlakeArea() const
{
    INT iWidth = GetFlakeWidth();
    return iWidth*iWidth;
}

BOOL CSnow::CreateSnowPen()
{
    if (m_hPenSnow)
    {
        ::DeleteObject(m_hPenSnow);
    }

    // 
    if (m_fAmount>0.66)
    {
        m_hPenSnow = ::CreatePen(PS_SOLID,1,m_clrSnow);
    }
    else if (m_fAmount>0.33)
    {
        m_hPenSnow = ::CreatePen(PS_SOLID,1,m_clrSnow);
    }
    else
    {
        m_hPenSnow = ::CreatePen(PS_SOLID,1,m_clrSnow);
    }

    return m_hPenSnow!=NULL;
}


void CSnow::RandPosition(IN const POINT& ptOrg,
                         IN  INT iRadius,
                         OUT TMPoint& ptRand ) const
{
    DOUBLE fRadian = ( 2 * PIRADIAN * ::rand() ) / RAND_MAX;// =((360*::rand()) / RAND_MAX) * PIRADIAN / 180;

    ptRand.iX = ptOrg.x + iRadius;
    ptRand.iY = ptOrg.y;
    ptRand.Rotate(TMPoint(ptOrg.x,ptOrg.y),fRadian);
}

void CSnow::DrawSnow(IN HDC hDC,IN POINT pt) const
{

    INT iSnowWidth = GetFlakeWidth()/2;

    TMPoint pt1;

    // 
    _thisx::RandPosition(pt,iSnowWidth,pt1);
    
    // draw
    INT iNumFlake = GetFlakeWidth();
    DOUBLE fRadian = 2*PIRADIAN/iNumFlake; //360.0/iNumFlake*PIRADIAN/180;
    for (INT i=0; i<iNumFlake; i++)
    {
        ::MoveToEx(hDC,pt.x,pt.y,NULL);
        ::LineTo(hDC,pt1.iX,pt1.iY);

        //
        pt1.Rotate(TMPoint(pt.x,pt.y),fRadian);
    }

}

HBITMAP CSnow::CreateSnowImg(HDC hDC,INT nWidth,INT nHeight) const
{

    // create a bitmap and select it to a DC 
    // which has already been created to draw snow.
    HBITMAP hBmpSnow = ::CreateCompatibleBitmap(CAutoDeskDC(),nWidth,nHeight);
    ::SelectObject(hDC,hBmpSnow);

    // initialize DC
    COLORREF clrBkg = _thisx::GetSkyColor();
    HBRUSH hBkgBrush = ::CreateSolidBrush(clrBkg);
    ::SelectObject(hDC,hBkgBrush);
    //::SetBkMode(hDC,TRANSPARENT);
    RECT rctBkg = {0,0,nWidth,nHeight}; 
    ::FillRect(hDC,&rctBkg,hBkgBrush);
    HANDLE hOldPen = ::SelectObject(hDC,m_hPenSnow);


    // draw
    CPointArray ptArray;
    DWORD dwNumRequest = DWORD(m_fAmount*nWidth*nHeight);
    dwNumRequest /= _thisx::GetFlakeArea();
    RECT rExtent = {0,0,nWidth,nHeight};
    CRandMgr::GenerateRandPos(ptArray,dwNumRequest,rExtent);
    INT iSize = ptArray.size();
    for(INT k=0; k<iSize; k++)
    {
        _thisx::DrawSnow(hDC,ptArray[k]);
    }

    //
    ::SelectObject(hDC,hOldPen);
    ::DeleteObject(hBkgBrush);

    //
    return hBmpSnow;

}

//////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CSnow::get_Color(OLE_COLOR *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
	*pVal = m_clrSnow;

	return S_OK;
}

STDMETHODIMP CSnow::put_Color(OLE_COLOR newVal)
{
	// TODO: Add your implementation code here
    if (_basex::IsTransparent(newVal))
    {
        m_clrSnow = 0;
    }
    else
    {
        m_clrSnow = (newVal&0x00FFFFFF);
        if (m_clrSnow==0)
        {
            m_clrSnow = _basex::GetBlackAgentClr();
        }
    }
	return S_OK;
}

STDMETHODIMP CSnow::get_Rate(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iRate;
	return S_OK;
}

STDMETHODIMP CSnow::put_Rate(INT newVal)
{
	// TODO: Add your implementation code here
    m_iRate = newVal;
	return S_OK;
}

STDMETHODIMP CSnow::get_Amount(FLOAT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_fAmount;

	return S_OK;
}

STDMETHODIMP CSnow::put_Amount(FLOAT newVal)
{
	// TODO: Add your implementation code here
    m_fAmount = newVal;
	return S_OK;
}
