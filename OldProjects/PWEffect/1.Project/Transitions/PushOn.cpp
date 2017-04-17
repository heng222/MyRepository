// PushOn.cpp : Implementation of CPushOn
#include "stdafx.h"
#include "PushOn.h"

/////////////////////////////////////////////////////////////////////////////
// CPushOn


//
//  --------------- CPushOn ----------------
//
HRESULT CPushOn::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // Properties
    m_iDirection = ED_LEFT;
    m_bDisplayOn = TRUE;

    // control values
    m_hBrush = NULL;

    return S_OK;
}

HRESULT CPushOn::OnInitialize()
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
    if (m_hBrush==NULL)
    {
        m_hBrush = ::CreateSolidBrush(m_clrBackground);
    }

    //
    return S_OK;
}

HRESULT CPushOn::OnTerminate()
{
    ClearTravelRect();

    if (m_hBrush)
    {
        DeleteObject(m_hBrush);
        m_hBrush = NULL;
    }

    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods
HRESULT CPushOn::ClearTravelRect()
{
    // 
    INT nSize = m_arShowRgn.size();
    for (INT i=0; i<nSize; i++)
    {
        delete m_arShowRgn[i];
    }
    m_arShowRgn.resize(0);

    // 
    nSize = m_arHideRgn.size();
    for (i=0; i<nSize; i++)
    {
        delete m_arHideRgn[i];
    }
    m_arHideRgn.resize(0);

    //
    return S_OK;
}

HRESULT CPushOn::ResetControlValue()
{
    // 
    return S_OK;
}

HRESULT CPushOn::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
    CTravelRect* pTR = NULL;
        
    // Region 1
    INT iSize = m_arShowRgn.size();
    for (INT i=0; i<iSize; i++)
    {
        pTR = m_arShowRgn[i];
        pTR->TravelP(fProgress);
    }

    // Region 2
    iSize = m_arHideRgn.size();
    for (i=0; i<iSize; i++)
    {
        pTR = m_arHideRgn[i];
        pTR->TravelP(fProgress);
    }
    
    // 
    return S_OK;
}

HRESULT CPushOn::Initialize(TMRect rectExtent)
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
            // Region 1 to show 
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rectExtent,
                rectExtent,
                fAngles[0],
                TRUE);
            m_arShowRgn.push_back(pNewTravelRect);

            // Region 2 to hide
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rectExtent,
                rectExtent,
                fAngles[0],
                FALSE);
            m_arHideRgn.push_back(pNewTravelRect);
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
                TRUE);
            m_arShowRgn.push_back(pNewTravelRect);
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartLeft,
                rPartLeft,
                fAngles[0],
                FALSE);
            m_arHideRgn.push_back(pNewTravelRect);

            // Right Part
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartRight,
                rPartRight,
                fAngles[1],
                TRUE);
            m_arShowRgn.push_back(pNewTravelRect);
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartRight,
                rPartRight,
                fAngles[1],
                FALSE);
            m_arHideRgn.push_back(pNewTravelRect);

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
                TRUE);
            m_arShowRgn.push_back(pNewTravelRect);
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartTopLeft,
                rPartTopLeft,
                fAngles[0],
                FALSE);
            m_arHideRgn.push_back(pNewTravelRect);

          
            // TopRight Part 
            TMRect rPartTopRight = rectExtent;
            rPartTopRight.iTl.iX = rPartTopLeft.iBr.iX;
            rPartTopRight.iBr.iY = rPartTopLeft.iBr.iY;
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartTopRight,
                rPartTopRight,
                fAngles[1],
                TRUE);
            m_arShowRgn.push_back(pNewTravelRect);  
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartTopRight,
                rPartTopRight,
                fAngles[1],
                FALSE);
            m_arHideRgn.push_back(pNewTravelRect); 
            
            // Lower left
            TMRect rPartLowerLeft = rectExtent;
            rPartLowerLeft.iTl.iY = rectExtent.iBr.iY + rectExtent.Height()/2;
            rPartLowerLeft.iBr.iX = rectExtent.iBr.iX - rectExtent.Width()/2;            
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartLowerLeft,
                rPartLowerLeft,
                fAngles[2],
                TRUE);
            m_arShowRgn.push_back(pNewTravelRect);  
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartLowerLeft,
                rPartLowerLeft,
                fAngles[2],
                FALSE);
            m_arHideRgn.push_back(pNewTravelRect);  
        
            // Lower right
            TMRect rPartLowerRight = rectExtent;
            rPartLowerRight.iTl = rPartTopLeft.iBr;
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartLowerRight,
                rPartLowerRight,
                fAngles[3],
                TRUE);
            m_arShowRgn.push_back(pNewTravelRect);  
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rPartLowerRight,
                rPartLowerRight,
                fAngles[3],
                FALSE);
            m_arHideRgn.push_back(pNewTravelRect);  

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

VOID CPushOn::GetAngle(FLOAT* pAngle) const
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


HRESULT CPushOn::DrawLiveBitmap(IN HDC hdcHide,
                               IN HDC hdcShow,
                               IN HDC hdcOutput)
{
    // fill output buffer
    RECT rectBkg = {0,0,_basex::Width(),_basex::Height()};
    ::FillRect(hdcOutput,&rectBkg,m_hBrush);

    // travel to draw
    RECT rDest,rSource;   
    CTravelRect* pTR = NULL;
    
    // Show Rgn1
    INT iSize = m_arShowRgn.size();
    for (INT i=0; i<iSize; i++)
    {
        pTR = m_arShowRgn[i];
        if (!pTR->HasTraveledOut())
        {
            pTR->GetIntersectRect(rDest);
            pTR->GetIntersectRectEx(rSource);
            ::BitBlt(hdcOutput, 
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

    // Show Rgn2
    iSize = m_arHideRgn.size();
    for (i=0; i<iSize; i++)
    {
        pTR = m_arHideRgn[i];
        if (!pTR->HasTraveledOut())
        {
            pTR->GetIntersectRect(rDest);
            pTR->GetIntersectRectEx(rSource);
            ::BitBlt(hdcOutput, 
                rDest.left,
                rDest.top, 
                rDest.right-rDest.left,
                rDest.bottom-rDest.top, 
                hdcHide, 
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

STDMETHODIMP CPushOn::get_Direction(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iDirection;
	return S_OK;
}

STDMETHODIMP CPushOn::put_Direction(INT newVal)
{
    // TODO: Add your implementation code here
    if (newVal<0 || newVal>15)
    {
        return E_INVALIDARG;
    }
    
    m_iDirection = (TSingleDir)newVal;
    
	return S_OK;
}
