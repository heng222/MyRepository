// LineOn.cpp : Implementation of CLineOn
#include "stdafx.h"
#include "LineOn.h"

/////////////////////////////////////////////////////////////////////////////
// CLineOn


//
//  --------------- CLineOn ----------------
//
HRESULT CLineOn::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    //
    m_iDirection = ED_LEFT;
    m_bDisplayOn = TRUE;
    m_iLagSpacing = 1;
    m_iLineWidth = 1;
    m_iPullPoint = 1;
    

    return S_OK;
}

HRESULT CLineOn::OnInitialize()
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

HRESULT CLineOn::OnTerminate()
{
    ClearTravelRect();

    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods
HRESULT CLineOn::ClearTravelRect()
{
    // Part1
    INT nSize = m_arLinePart1.size();
    for (INT i=0; i<nSize; i++)
    {
        delete m_arLinePart1[i];
    }
    m_arLinePart1.resize(0);
    
    // Part2
    nSize = m_arLinePart2.size();
    for (INT j=0; j<nSize; j++)
    {
        delete m_arLinePart2[j];
    }
    m_arLinePart2.resize(0);

    //
    return S_OK;
}

HRESULT CLineOn::ResetControlValue()
{
    // 
    return S_OK;
}

HRESULT CLineOn::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
    
    // live length
    INT iLiveLen = m_iMaxTravelLen * fProgress;
    INT iTempLen;
    
    // Part1
    INT iSize = m_arLinePart1.size();
    for (INT i=0; i<iSize; i++)
    {
        CTravelRect* pTR = m_arLinePart1[i];
        iTempLen = iLiveLen - (i*m_iLagSpacing);

        if (iTempLen>0)
        {
            INT iExetent = pTR->GetMaxTravelLen()/2;
            if ( iTempLen<=iExetent )
            {
                pTR->Travel(iTempLen);
            }
            else
            {
                pTR->Travel(iExetent);
            }
        }
    }
    
    // PART 2
    iSize = m_arLinePart2.size();
    for (INT j=0; j<iSize; j++)
    {
        CTravelRect* pTR = m_arLinePart2[j];
        iTempLen = iLiveLen - (j*m_iLagSpacing);
        if (iTempLen>0)
        {
            INT iExetent = pTR->GetMaxTravelLen()/2;
            if ( iTempLen<=iExetent )
            {
                pTR->Travel(iTempLen);
            }
            else
            {
                pTR->Travel(iExetent);
            }
        }
    }    

    // 
    return S_OK;
}

HRESULT CLineOn::Initialize(TMRect rectExtent)
{
    INT nWidth  = rectExtent.Width();
    INT nHeight = rectExtent.Height();
    BOOL bVertical = (m_iDirection==ED_UP||m_iDirection==ED_DOWN);
    
    INT iTotalLen = bVertical ? nWidth : nHeight;
    
    INT nNumber = iTotalLen/m_iLineWidth;
    if (iTotalLen%m_iLineWidth!=0)
    {
        nNumber ++;
    }
    
    // build seed rect
    TMRect rSeed;
    if (bVertical)
    {
        rSeed = TMRect(m_iPullPoint, rectExtent.Top(),
            m_iPullPoint+m_iLineWidth,rectExtent.Bottom());
    } 
    else
    {
        rSeed = TMRect(rectExtent.Left(), m_iPullPoint,
            rectExtent.Right(),m_iPullPoint-m_iLineWidth);
    }
    
    // build Part1 rectangle.
    CTravelRect* pNewTravelRect = NULL;
    for (INT i=0; i<nNumber; i++)
    {
        TMRect rectPart1 = rSeed;
        TMRect rectPart2 = rSeed;
        if (bVertical)
        {
            rectPart1.MoveLeft(i*m_iLineWidth);
            rectPart2.MoveRight(i*m_iLineWidth);
        }
        else
        {
            rectPart1.MoveBottom(i*m_iLineWidth);
            rectPart2.MoveTop(i*m_iLineWidth);
        }
        
        // Is part1 invalid?
        if (rectExtent.IsIntersects(rectPart1))
        {
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rectPart1,
                rectExtent,
                GetAngle(),
                m_bDisplayOn);
            
            // save
            m_arLinePart1.push_back(pNewTravelRect);
        }

        // intersects?
        if (rectExtent.IsIntersects(rectPart2))
        {
            pNewTravelRect = new CTravelRect;
            pNewTravelRect->Initialize(rectPart2,
                rectExtent,
                GetAngle(),
                m_bDisplayOn);
            
            // save
            m_arLinePart2.push_back(pNewTravelRect);
        }
    }

    // determine the max travel length
    INT iMaxSize = max(m_arLinePart1.size(),m_arLinePart2.size());
    m_iMaxTravelLen = (iMaxSize-1)*m_iLagSpacing;
    if (bVertical)
    {
        m_iMaxTravelLen += nHeight;
    }
    else
    {
        m_iMaxTravelLen += nWidth;
    }

    
    //
    return S_OK;
}


HRESULT CLineOn::DrawLiveBitmap(IN HDC hInDC1,
                                IN HDC hdcShow,
                                IN HDC hOutDC)
{
    // store some handy values
    INT nWidth = _basex::Width();
    INT nHeight = _basex::Height();

    
    // travel to draw
    RECT rOrig,rLive;
    INT iSize = m_arLinePart1.size();
    for (INT i=0; i<iSize; i++)
    {
        CTravelRect* pTR = m_arLinePart1[i];
        if (!pTR->HasTraveledOut())
        {
            pTR->GetOrigRect(rOrig);
            pTR->GetLiveRect(rLive);
            ::BitBlt(hOutDC, rLive.left,rLive.top, pTR->Width(),
                pTR->Height(), hdcShow, rOrig.left, rOrig.top, SRCCOPY);
                
        }
    }

    // Part2
    iSize = m_arLinePart2.size();
    for (i=0; i<iSize; i++)
    {
        CTravelRect* pTR = m_arLinePart2[i];
        if (!pTR->HasTraveledOut())
        {
            pTR->GetOrigRect(rOrig);
            pTR->GetLiveRect(rLive);
            ::BitBlt(hOutDC, rLive.left,rLive.top, pTR->Width(),
                pTR->Height(), hdcShow, rOrig.left, rOrig.top, SRCCOPY);
        }
    }
    
    // 
    return S_OK;
}

FLOAT CLineOn::GetAngle() const
{	
    if (m_iDirection==ED_LEFT)
    {
        return FLOAT(PIRADIAN);
    }
    else if (m_iDirection==ED_RIGHT)
    {
        return 0;
    }
    else if (m_iDirection==ED_UP)
    {
        return FLOAT(-PIRADIAN/2);
    }
    else if (m_iDirection==ED_DOWN)
    {
        return FLOAT(PIRADIAN/2);
    }
    else
    {
        ASSERT(ERROR);
    }
    
    return 0;
}
//////////////////////////////////////////////////////////////////////////
// Properties


STDMETHODIMP CLineOn::get_State(BOOL *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bDisplayOn;
	return S_OK;
}

STDMETHODIMP CLineOn::put_State(BOOL newVal)
{
	// TODO: Add your implementation code here
    m_bDisplayOn = newVal;
	return S_OK;
}

STDMETHODIMP CLineOn::get_Direction(INT *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iDirection;
	return S_OK;
}

STDMETHODIMP CLineOn::put_Direction(INT newVal)
{
	// TODO: Add your implementation code here
    if (newVal<0 || newVal>3)
    {
        return E_INVALIDARG;
    }

    m_iDirection = (TSingleDir)newVal;

	return S_OK;
}

STDMETHODIMP CLineOn::get_LagSpacing(INT *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iLagSpacing;
	return S_OK;
}

STDMETHODIMP CLineOn::put_LagSpacing(INT newVal)
{
	// TODO: Add your implementation code here
    m_iLagSpacing = newVal;
	return S_OK;
}

STDMETHODIMP CLineOn::get_LineWidth(INT *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iLineWidth;
	return S_OK;
}

STDMETHODIMP CLineOn::put_LineWidth(INT newVal)
{
	// TODO: Add your implementation code here
    m_iLineWidth = newVal;
	return S_OK;
}

STDMETHODIMP CLineOn::get_PullPoint(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iPullPoint;
	return S_OK;
}

STDMETHODIMP CLineOn::put_PullPoint(INT newVal)
{
	// TODO: Add your implementation code here
    m_iPullPoint = newVal;
	return S_OK;
}
