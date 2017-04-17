// Slide.cpp : Implementation of CSlide
#include "stdafx.h"
#include "Slide.h"

/////////////////////////////////////////////////////////////////////////////
// CSlide

#define         _BUG_CHECK_
//
//  --------------- CSlide ----------------
//
HRESULT CSlide::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    //
    m_iDirection = ED_LEFT;
    m_bDisplayOn = TRUE;
    

    return S_OK;
}

HRESULT CSlide::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here
    
    // output width and height
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();

    // clear travel rectangles
    ClearTravelRect();
    
    // generate slots
    TMRect rectExtent(0,0,nWidth,nHeight);        
    _thisx::Initialize(rectExtent);
    
    //

    //
    return S_OK;
}

HRESULT CSlide::OnTerminate()
{
    ClearTravelRect();

    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods
HRESULT CSlide::ClearTravelRect()
{
    // 
    INT nSize = m_arSlideRgn.size();
    for (INT i=0; i<nSize; i++)
    {
        delete m_arSlideRgn[i];
    }
    m_arSlideRgn.resize(0);

    //
    return S_OK;
}

HRESULT CSlide::ResetControlValue()
{
    // 
    return S_OK;
}

HRESULT CSlide::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
        
    // 
    CTravelRect* pTR = NULL;
    INT iSize = m_arSlideRgn.size();
    for (INT i=0; i<iSize; i++)
    {
        pTR = m_arSlideRgn[i];
        pTR->TravelP(fProgress);
    }
    
    // 
    return S_OK;
}

HRESULT CSlide::Initialize(TMRect rectExtent)
{
    INT nWidth = _basex::GetOutputWidth();
    INT nHeight = _basex::GetOutputHeight();
    FLOAT fAngles[4] = {0};
    GetAngle(fAngles);

    CTravelRect* pNewTravelRect = NULL;

    switch (m_iDirection)
    {
    case ED_LEFT:  // 0
    case ED_RIGHT: // 1
    case ED_UP:    // 2
    case ED_DOWN:  // 3
    case ED_UPPERLEFT:  // 6
    case ED_UPPERRIGHT: // 7
    case ED_LOWERLEFT:  // 8
    case ED_LOWERRIGHT: // 9
        {
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rectExtent,
                rectExtent,
                fAngles[0],
                m_bDisplayOn);
            
            // save
            m_arSlideRgn.push_back(pNewTravelRect);
        }
        break;     

    case ED_IN:  // 4
    case ED_OUT: // 5
    case ED_UPPERCENTER: // 10
    case ED_LOWERCENTER: // 11
    case ED_UPPERCORNERS: // 12
    case ED_LOWERCORNERS: // 13
        {
            TMRect rPartLeft = rectExtent;        
            rPartLeft.iBr.iX = rectExtent.iBr.iX - rectExtent.Width()/2;
            TMRect rPartRight = rectExtent;
            rPartRight.iTl.iX = rPartLeft.iBr.iX;

            // Left Part 
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartLeft,
                rPartLeft,
                fAngles[0],
                m_bDisplayOn);
            m_arSlideRgn.push_back(pNewTravelRect);

            // Right Part 
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartRight,
                rPartRight,
                fAngles[1],
                m_bDisplayOn);
            m_arSlideRgn.push_back(pNewTravelRect);
        }
        break;          
        
        
    case ED_CENTER: // 14
    case ED_ALLCORNERS: // 15
        {
            // TopLeft Part 
            TMRect rPartTopLeft = rectExtent;        
            rPartTopLeft.iBr.iX = rectExtent.iBr.iX - rectExtent.Width()/2;
            rPartTopLeft.iBr.iY = rectExtent.iBr.iY + rectExtent.Height()/2;
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartTopLeft,
                rPartTopLeft,
                fAngles[0],
                m_bDisplayOn);
            m_arSlideRgn.push_back(pNewTravelRect);

          
            // TopRight Part 
            TMRect rPartTopRight = rectExtent;
            rPartTopRight.iTl.iX = rPartTopLeft.iBr.iX;
            rPartTopRight.iBr.iY = rPartTopLeft.iBr.iY;
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartTopRight,
                rPartTopRight,
                fAngles[1],
                m_bDisplayOn);
            m_arSlideRgn.push_back(pNewTravelRect);  
            
            // Lower left
            TMRect rPartLowerLeft = rectExtent;
            rPartLowerLeft.iTl.iY = rectExtent.iBr.iY + rectExtent.Height()/2;
            rPartLowerLeft.iBr.iX = rectExtent.iBr.iX - rectExtent.Width()/2;
            
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartLowerLeft,
                rPartLowerLeft,
                fAngles[2],
                m_bDisplayOn);
            m_arSlideRgn.push_back(pNewTravelRect);  
        
            // Lower right
            TMRect rPartLowerRight = rectExtent;
            rPartLowerRight.iTl = rPartTopLeft.iBr;

            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartLowerRight,
                rPartLowerRight,
                fAngles[3],
                m_bDisplayOn);
            m_arSlideRgn.push_back(pNewTravelRect);  

        }
        break;
        
    default:
        {
            return E_FAIL;
        }
    }

    //
    return S_OK;
}

VOID CSlide::GetAngle(FLOAT* pAngle) const
{	    
    INT nWidth = _basex::GetOutputWidth();
    INT nHeight = _basex::GetOutputHeight();
    
    if (m_iDirection==ED_LEFT)
    {
        pAngle[0] = FLOAT(PIRADIAN);
    }
    else if (m_iDirection==ED_RIGHT)
    {
        pAngle[0] = 0;
    }
    else if (m_iDirection==ED_UP)
    {
        pAngle[0] = FLOAT(-PIRADIAN/2);
    }
    else if (m_iDirection==ED_DOWN)
    {
        pAngle[0] = FLOAT(PIRADIAN/2);
    }
    else if (m_iDirection==ED_IN)
    {
        pAngle[0] = 0;
        pAngle[1] = FLOAT(PIRADIAN);
    }
    else if (m_iDirection==ED_OUT)
    {
        pAngle[0] = FLOAT(PIRADIAN);
        pAngle[1] = 0;
    }
    else if (m_iDirection==ED_UPPERLEFT)
    {
        pAngle[0] = (FLOAT)atan2(-nHeight,-nWidth);
    }
    else if (m_iDirection==ED_UPPERRIGHT)
    {
        pAngle[0] = (FLOAT)atan2(-nHeight,nWidth);
    }
    else if (m_iDirection==ED_LOWERLEFT)
    {
        pAngle[0] = (FLOAT)atan2(nHeight,-nWidth);
    }
    else if (m_iDirection==ED_LOWERRIGHT)
    {
        pAngle[0] = (FLOAT)atan2(nHeight,nWidth);
    }
    else if (m_iDirection==ED_UPPERCENTER)
    {        
        pAngle[0] = (FLOAT)atan2(-nHeight,nWidth/2);
        pAngle[1] = (FLOAT)atan2(-nHeight,-nWidth/2);
    }
    else if (m_iDirection==ED_LOWERCENTER)
    {        
        pAngle[0] = (FLOAT)atan2(nHeight,nWidth/2);
        pAngle[1] = (FLOAT)atan2(nHeight,-nWidth/2);
    }
    else if (m_iDirection==ED_UPPERCORNERS)
    {
        pAngle[0] = (FLOAT)atan2(-nHeight,-nWidth/2);
        pAngle[1] = (FLOAT)atan2(-nHeight,nWidth/2);
    }
    else if (m_iDirection==ED_LOWERCORNERS)
    {
        pAngle[0] = (FLOAT)atan2(nHeight,-nWidth/2);
        pAngle[1] = (FLOAT)atan2(nHeight,nWidth/2);
    }
    else if (m_iDirection==ED_CENTER)
    {
        
        pAngle[0] = (FLOAT)atan2(-nHeight,nWidth);
        pAngle[1] = (FLOAT)atan2(-nHeight,-nWidth);
        pAngle[2] = (FLOAT)atan2(nHeight,nWidth);
        pAngle[3] = (FLOAT)atan2(nHeight,-nWidth);
    }
    else if (m_iDirection==ED_ALLCORNERS)
    {
        pAngle[0] = (FLOAT)atan2(nHeight,-nWidth);
        pAngle[1] = (FLOAT)atan2(nHeight,nWidth);
        pAngle[2] = (FLOAT)atan2(-nHeight,-nWidth);
        pAngle[3] = (FLOAT)atan2(-nHeight,nWidth);
    }
}


HRESULT CSlide::DrawLiveBitmap(IN HDC hInDC1,
                               IN HDC hdcShow,
                               IN HDC hOutDC)
{
    // travel to draw
    RECT rDest,rSource;    
    INT iSize = m_arSlideRgn.size();
    for (INT i=0; i<iSize; i++)
    {
        CTravelRect* pTR = m_arSlideRgn[i];
        if (!pTR->HasTraveledOut())
        {
            pTR->GetIntersectRect(rDest);
            pTR->GetIntersectRectEx(rSource);
            ::BitBlt(hOutDC, 
                rDest.left,
                rDest.top, 
                rDest.right-rDest.left,
                rDest.bottom-rDest.top, 
                hdcShow, 
                rSource.left, 
                rSource.top, 
                SRCCOPY);
        }
    }
    
    // 
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CSlide::get_State(BOOL *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bDisplayOn;
	return S_OK;
}

STDMETHODIMP CSlide::put_State(BOOL newVal)
{
    // TODO: Add your implementation code here
    m_bDisplayOn = newVal;
	return S_OK;
}

STDMETHODIMP CSlide::get_Direction(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iDirection;
	return S_OK;
}

STDMETHODIMP CSlide::put_Direction(INT newVal)
{
    // TODO: Add your implementation code here
    if (newVal<0 || newVal>15)
    {
        return E_INVALIDARG;
    }
    
    m_iDirection = (TSingleDir)newVal;
    
	return S_OK;
}
