// Rain.cpp : Implementation of CRain
#include "stdafx.h"
#include "Rain.h"
#include "ocidl.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CRain

//
//  --------------- CRain ----------------
//
HRESULT CRain::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());

    // base class
    m_bDisplayOn = TRUE;
    
    // self variables
    m_clrRain = RGB(192,192,192);
    m_fAmount = 0.3f;
    m_fAngle = 90;
    
    // 
    m_hDCRain = ::CreateCompatibleDC(NULL);
    m_hBmpRain = NULL;
    m_hPenRain = NULL;
    m_bWraped = FALSE;
    m_bShowInput2 = FALSE;
    
    
    return S_OK;
}

HRESULT CRain::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here

    // Seed the random-number generator with GetTickCount so that
    // the numbers will be different every time we run.
    ::srand(::GetTickCount());
    
    
    
    // create the pen to draw snow.
    RTN_HR_IF_FALSE(CreateRainPen());
    
    //
    if (m_hBmpRain==NULL)
    {
        INT nSkyWidth = _thisx::GetSkyWidth();
        INT nSkyHeight = _thisx::GetSkyHeight();
        m_hBmpRain = _thisx::CreateStaticRainImage(m_hDCRain,nSkyWidth,nSkyHeight);
    }

    // Initialize control value.
    ResetControlValue();

    //
    return S_OK;
}

HRESULT CRain::OnTerminate()
{
    if (m_hDCRain!=NULL)
    {
        ::DeleteDC(m_hDCRain);
        m_hDCRain = NULL;
    }
    
    if (m_hBmpRain!=NULL)
    {
        ::DeleteObject(m_hBmpRain);
        m_hBmpRain = NULL;
    }
    
    if (m_hPenRain)
    {
        ::DeleteObject(m_hPenRain);
        m_hPenRain = NULL;
    }

    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Private methods

HRESULT CRain::ResetControlValue()
{
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();
    TMRect rExtent(0,0,nWidth,nHeight);
    DOUBLE fAngle = PIRADIAN/2;
    
    m_rectTravel.Initialize(rExtent,rExtent,fAngle,TRUE);
    
    // max travel length
    m_dwMaxTravelLen = (DWORD)(_basex::GetDuration()*nHeight);
    
    // 
    return S_OK;
}

HRESULT CRain::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
    DWORD dwLiveLen = (DWORD)(fProgress*m_dwMaxTravelLen);
    DWORD dwRemainLen = m_dwMaxTravelLen-dwLiveLen;

    if ( dwRemainLen<=_basex::Height() )
    {
        m_bShowInput2 = TRUE;
        m_rectTravel.Travel(dwRemainLen);
    }
    else
    {
        m_bShowInput2 = FALSE;
        m_rectTravel.Travel(dwLiveLen);
    }

    
    if(dwLiveLen>_basex::Height())
    {
        m_bWraped = TRUE;
    }
    
    // 
    return S_OK;
}

HRESULT CRain::DrawLiveBitmap(IN HDC hdcIn1,IN HDC hdcShow,IN HDC hdcOut)
{
    COLORREF clrTransparent = _thisx::GetSkyColor();

    // store some handy values
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();   
    
    
    // travel to draw
    RECT rLive,rIntersect,rExtent;
    m_rectTravel.GetExetent(rExtent);
    m_rectTravel.GetLiveRect(rLive);
    m_rectTravel.GetIntersectRect(rIntersect);
    
    INT iISWidth  = rIntersect.right - rIntersect.left;
    INT iISHeight = rIntersect.bottom - rIntersect.top; 

    if (!m_bShowInput2)
    {
        // Input1 -> Output
        ::BitBlt(hdcOut,0,0,nWidth,nHeight,
            hdcIn1,0,0,SRCCOPY);
        
        // Draw Rain to output interface
        ::TransparentBlt(hdcOut,rLive.left,rLive.top,nWidth,nHeight,
            m_hDCRain,0,0,nWidth,nHeight,clrTransparent);

        
        if (m_bWraped)
        {
            // another part.
            if (rLive.top<rExtent.top)
            {
                ::TransparentBlt(hdcOut, rExtent.left, rExtent.top + iISHeight,
                    nWidth,
                    nHeight - iISHeight,

                    m_hDCRain, 0, 0,
                    nWidth,  nHeight - iISHeight,
                    clrTransparent);
            }
            else
            {
                ::TransparentBlt(hdcOut, 0 , 0,
                    nWidth, nHeight - iISHeight,

                    m_hDCRain,   0, iISHeight,
                    nWidth,  nHeight - iISHeight,
                    clrTransparent);
            }
        }
    }
    else
    {
        // Rain  -> Input1
        ::TransparentBlt(hdcIn1,0,0,nWidth,nHeight,
            m_hDCRain,0,0,nWidth,nHeight,clrTransparent);

        // Intersects part
        ::BitBlt(hdcOut,rLive.left,rLive.top,nWidth,nHeight,
            hdcIn1,0,0,SRCCOPY);

        // Merge input2 to output
        ::BitBlt(hdcOut, rExtent.left, rExtent.top + iISHeight,
            nWidth,
            nHeight - iISHeight,
            
            hdcShow, 0, 0,
            SRCCOPY);
    }
    
    
    return S_OK;
}
COLORREF CRain::GetSkyColor() const
{
    return ( ~m_clrRain );
}


INT CRain::GetSkyWidth() const
{
    // Must >= _basex::Width()
    return _basex::Width();
}

INT CRain::GetSkyHeight() const
{
    // must >= _basex::Height() !!!
    return _basex::Height();
}


INT CRain::GetDripHeight() const
{
    if (m_fAmount>=0.66)
    {
        return 6;
    }
    else if (m_fAmount>=0.33)
    {
        return 5;
    }
    else
    {
        return 4;
    }

}

INT CRain::GetDripArea() const
{
    INT iLen = GetDripHeight();
    return iLen*2;
}

BOOL CRain::CreateRainPen()
{
    if (m_hPenRain)
    {
        ::DeleteObject(m_hPenRain);
    }

    // 
    if (m_fAmount>0.66)
    {
        m_hPenRain = ::CreatePen(PS_SOLID,1,m_clrRain);
    }
    else if (m_fAmount>0.33)
    {
        m_hPenRain = ::CreatePen(PS_DASH,1,m_clrRain);
    }
    else
    {
        m_hPenRain = ::CreatePen(PS_DASH,1,m_clrRain);
    }

    return m_hPenRain!=NULL;
}


void CRain::CaclRainEndPos(IN const POINT& ptOrg,
                         IN  INT iRadius,
                         OUT TMPoint& ptRand ) const
{
    ptRand.iX = ptOrg.x + iRadius;
    ptRand.iY = ptOrg.y;

    // random rotate
    //INT iAngle = 0;
    //CRandMgr::InitRandSeed();
    //CRandMgr::CreateRandomNum(iAngle,45,45,1);

    DOUBLE fRadian = (-m_fAngle)*PIRADIAN/180;

    ptRand.Rotate(TMPoint(ptOrg.x,ptOrg.y),fRadian);
}

void CRain::DrawDrip(IN HDC hDC,IN POINT ptStart) const
{
    HANDLE hOldPen = ::SelectObject(hDC,m_hPenRain);

    INT iRainLen = GetDripHeight();

    TMPoint ptEnd;

    // 
    _thisx::CaclRainEndPos(ptStart,iRainLen,ptEnd);
    
    // 
    ::MoveToEx(hDC,ptStart.x,ptStart.y,NULL);
    ::LineTo(hDC,ptEnd.iX,ptEnd.iY);

    // 
    ::SelectObject(hDC,hOldPen);
}

HBITMAP CRain::CreateStaticRainImage(HDC hDC,INT nWidth,INT nHeight) const
{

    // create a bitmap and select it to a DC 
    // which has already been created to draw snow.
    HBITMAP hBmpSnow = ::CreateCompatibleBitmap(CAutoDeskDC(),nWidth,nHeight);
    ::SelectObject(hDC,hBmpSnow);

    // initialize DC
    COLORREF clrBkg = _thisx::GetSkyColor();
    HBRUSH hBkgBrush = ::CreateSolidBrush(clrBkg);
    ::SelectObject(hDC,hBkgBrush);
    //::SetBkMode(m_hDCRain,TRANSPARENT);
    RECT rctBkg = {0,0,nWidth,nHeight}; 
    ::FillRect(hDC,&rctBkg,hBkgBrush);

    // draw
    CPointArray ptArray;
    DWORD dwNumRequest = DWORD(m_fAmount*nWidth*nHeight);
    dwNumRequest /= _thisx::GetDripArea();
    RECT rExtent = {0,0,nWidth,nHeight};
    CRandMgr::GenerateRandPos(ptArray,dwNumRequest,rExtent);
    INT iSize = ptArray.size();
    for(INT k=0; k<iSize; k++)
    {
        _thisx::DrawDrip(m_hDCRain,ptArray[k]);
    }

    //
    ::DeleteObject(hBkgBrush);

    //
    return hBmpSnow;

}

//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CRain::get_Amount(FLOAT *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_fAmount;
	return S_OK;
}

STDMETHODIMP CRain::put_Amount(FLOAT newVal)
{
	// TODO: Add your implementation code here
    if (newVal>1 || newVal<0)
    {
        return E_FAIL;
    }

    m_fAmount = newVal;

    // 
	return S_OK;
}

STDMETHODIMP CRain::get_Color(OLE_COLOR *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_clrRain;
	return S_OK;
}

STDMETHODIMP CRain::put_Color(OLE_COLOR newVal)
{
    // TODO: Add your implementation code here    
    if (_basex::IsTransparent(newVal))
    {
        m_clrRain = 0;
    }
    else
    {
        m_clrRain = (newVal&0x00FFFFFF);
        
        if (m_clrRain==0)
        {
            m_clrRain = _basex::GetBlackAgentClr();
        }
    }

	return S_OK;
}

STDMETHODIMP CRain::get_Angle(FLOAT *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_fAngle;
	return S_OK;
}

STDMETHODIMP CRain::put_Angle(FLOAT newVal)
{
	// TODO: Add your implementation code here
    m_fAngle = newVal;
	return S_OK;
}
