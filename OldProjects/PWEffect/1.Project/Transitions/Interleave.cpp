// Interleave.cpp : Implementation of CInterleave
#include "stdafx.h"
#include "Interleave.h"

/////////////////////////////////////////////////////////////////////////////
// CInterleave



//
//  --------------- CInterleave ----------------
//
HRESULT CInterleave::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // 
    m_bDisplayOn = TRUE;   // Display on?
    m_iDirection = ELeft_Right;
    m_bVertical  = TRUE;   // vertical lines?
    m_iThickness = 1;      // lines thickness

    //
    return S_OK;
}

HRESULT CInterleave::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here
    
    //
    Initialize();

    //
    ResetControlValue();

    //
    return S_OK;
}

HRESULT CInterleave::OnTerminate()
{
    // clear travel rectangle
    ClearTravelRect();

    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Private methods
HRESULT CInterleave::GenerateSlot(TMRect rectExtent,CTravelRectArray& arTR) const
{
    INT nWidth  = rectExtent.Width();
    INT nHeight = rectExtent.Height();

    INT iTotalLen = m_bVertical ? nWidth : nHeight;
    
    INT nNumber = iTotalLen/m_iThickness;
    if (iTotalLen%m_iThickness!=0)
    {
        nNumber ++;
    }

    // build seed rect
    TMRect rSeed;
    if (m_bVertical)
    {
        rSeed = TMRect(rectExtent.Left(), rectExtent.Top(),
            rectExtent.Left()+m_iThickness,rectExtent.Bottom());
    } 
    else
    {
        rSeed = TMRect(rectExtent.Left(), rectExtent.Top(),
            rectExtent.Right(),rectExtent.Top()-m_iThickness);
    }
    
    // build travel rectangle.
    CTravelRect* pNewTravelRect = NULL;
    for (INT i=0; i<nNumber; i++)
    {
        TMRect rOriginal = rSeed;
        if (m_bVertical)
        {
            rOriginal.MoveRight(m_iThickness*i);
        }
        else
        {
            rOriginal.MoveBottom(m_iThickness*i);
        }
        
        // create a new TravelRect.
        pNewTravelRect = new CTravelRect;
        pNewTravelRect->Initialize(rOriginal,
            rectExtent,
            GetAngle(i%2),
            m_bDisplayOn);
        
        // save
        arTR.push_back(pNewTravelRect);
    }

    //
    return S_OK;
}

HRESULT CInterleave::Initialize()
{    

    // output width and height
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();

    // extent
    ClearTravelRect();

    // extent
    if (m_iDirection!=EIn_Out)
    {
        TMRect rectExtent(0,0,nWidth,nHeight);        
        _thisx::GenerateSlot(rectExtent,m_arTravelRect);
    }
    else
    {
        TMRect rLeftPart(0,0,nWidth/2,nHeight);
        TMRect rRightPart(rLeftPart.Right(),0,Width(),Height());
        _thisx::GenerateSlot(rLeftPart,m_arTravelRect);
        _thisx::GenerateSlot(rRightPart,m_arTravelRect);
    }

    // 
    return S_OK;
}

FLOAT CInterleave::GetAngle(BOOL bFlag) const
{	
    if (m_iDirection==ETop_Bottom)
    {
        return (bFlag ? PIRADIAN/2 : -PIRADIAN/2);
    }
    else if (m_iDirection==ELeft_Right)
    {
        return (bFlag ? 0 : PIRADIAN);
    }
    else if (m_iDirection==EIn_Out)
    {
        return (bFlag ? 0 : PIRADIAN);
    }
    else if (m_iDirection==ETopLeft_BottomRight)
    {
        FLOAT fAngle;
        fAngle = atan2f(_basex::Height(),_basex::Width());
        if (bFlag)
        {
            fAngle += (FLOAT)(PIRADIAN);
        }
        return fAngle;
    }
    else if (m_iDirection==EBottomLeft_TopRight)
    {
        FLOAT fAngle;
        fAngle = -atan2f(_basex::Height(),_basex::Width());
        if (bFlag)
        {
            fAngle += (FLOAT)(PIRADIAN);
        }
        return fAngle;
    }
    else if (m_iDirection==ETopCorners)
    {
        FLOAT fAngle;
        fAngle = atan2f(_basex::Height(),_basex::Width());
        if (bFlag)
        {
            return -fAngle;
        }
        else
        {
            return PIRADIAN + fAngle;
        }
    }
    else if (m_iDirection==EBottomCorners)
    {
        FLOAT fAngle;
        fAngle = atan2f(_basex::Height(),_basex::Width());
        if (bFlag)
        {
            return fAngle;
        }
        else
        {
            return PIRADIAN - fAngle;
        }
    }
    else
    {
        ASSERT(ERROR);
    }
    
    return 0;
}

HRESULT CInterleave::ClearTravelRect()
{
    INT nSize = m_arTravelRect.size();
    for (INT i=0; i<nSize; i++)
    {
        delete m_arTravelRect[i];
    }
    m_arTravelRect.resize(0);
    
    //
    return S_OK;
}

HRESULT CInterleave::ResetControlValue()
{
    // 
    return S_OK;
}

HRESULT CInterleave::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
    //
    INT iSize = m_arTravelRect.size();

    for (INT i=0; i<iSize; i++)
    {
        CTravelRect* pTR = m_arTravelRect[i];
        INT iLen= pTR->GetMaxTravelLen()/2 * fProgress;
        pTR->Travel(iLen);
    }

    // 
    return S_OK;
}


HRESULT CInterleave::DrawLiveBitmap(IN HDC hInDC1,
                                    IN HDC hdcShow,
                                    IN HDC hOutDC)
{
    // store some handy values
    INT nWidth = _basex::Width();
    INT nHeight = _basex::Height();
    
    
    // travel to draw
    RECT rOrig,rIntersect,rLive;
    RECT rExtent;
    INT iSize = m_arTravelRect.size();
    for (INT i=0; i<iSize; i++)
    {
        CTravelRect* pTR = m_arTravelRect[i];
        if (!pTR->HasTraveledOut())
        {
            pTR->GetExetent(rExtent);
            pTR->GetOrigRect(rOrig);
            pTR->GetLiveRect(rLive);
            pTR->GetIntersectRect(rIntersect);
            
            INT iISWidth  = rIntersect.right  - rIntersect.left;
            INT iISHeight = rIntersect.bottom - rIntersect.top; 
            if (m_iDirection==EIn_Out)
            {
                if (rLive.left<rExtent.left)
                {
                    ::BitBlt(hOutDC,   rIntersect.left,
                        rIntersect.top, iISWidth,
                        iISHeight, hdcShow,
                        rOrig.left+(pTR->Width()-iISWidth),
                        rOrig.top,
                        SRCCOPY);
                }
                else
                {
                    ::BitBlt(hOutDC, rIntersect.left, rIntersect.top,
                        iISWidth,iISHeight,hdcShow,rOrig.left,rOrig.top, SRCCOPY);
                }
            }
            else
            {
                ::BitBlt(hOutDC, rLive.left,rLive.top, pTR->Width(),
                    pTR->Height(), hdcShow, rOrig.left, rOrig.top, SRCCOPY);

            }
        }
    }
    
    // 
    return S_OK;
}
//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CInterleave::get_State(BOOL *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bDisplayOn;

	return S_OK;
}

STDMETHODIMP CInterleave::put_State(BOOL newVal)
{
	// TODO: Add your implementation code here
    m_bDisplayOn = newVal;
	return S_OK;
}

STDMETHODIMP CInterleave::get_Lines(BOOL *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bVertical;

	return S_OK;
}

STDMETHODIMP CInterleave::put_Lines(BOOL newVal)
{
	// TODO: Add your implementation code here
    m_bVertical = newVal;
	return S_OK;
}

STDMETHODIMP CInterleave::get_Thickness(INT *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iThickness;
	return S_OK;
}

STDMETHODIMP CInterleave::put_Thickness(INT newVal)
{
	// TODO: Add your implementation code here
    m_iThickness = newVal;
	return S_OK;
}


STDMETHODIMP CInterleave::get_Direction(INT *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = (INT)m_iDirection;
	return S_OK;
}

STDMETHODIMP CInterleave::put_Direction(INT newVal)
{
	// TODO: Add your implementation code here
    if (newVal>=ETop_Bottom && newVal<=EBottomCorners)
    {
        m_iDirection = (TILDir)newVal;
    }
    else
    {
        return E_INVALIDARG;
    }

	return S_OK;
}
