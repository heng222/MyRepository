// BlackHole.cpp : Implementation of CBlackHole
#include "stdafx.h"
#include "PWEffect.h"
#include "BlackHole.h"


/////////////////////////////////////////////////////////////////////////////
// CBlackHole

#define     BLACKHOLE_ON_THREDHOLD     (0.85f)
#define     BLACKHOLE_OFF_THREDHOLD    (0.25f)

//
//  --------------- CBlackHole ----------------
//
HRESULT CBlackHole::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());

    // 
    m_ptStart.x = 0;
    m_ptStart.y = 0;


    return S_OK;
}

HRESULT CBlackHole::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());

    //
    return S_OK;
}


HRESULT CBlackHole::OnTerminate()
{    
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods

HRESULT CBlackHole::ResetControlValue()
{
    INT iHeight = _basex::Height();
    INT iWidth = _basex::Width();
    
    TMPoint mptStart(m_ptStart.x,m_ptStart.y);
    TMPoint mptEnd(iWidth/2,iHeight/2);
    
    if (!m_bDisplayOn)
    {
        m_vMove = TSegmentVector(mptEnd,mptStart);
        m_rLiveRect.SetNull();
    }
    else
    {
        m_vMove = TSegmentVector(mptStart,mptEnd);
        m_rLiveRect = TMRect(0,0,iWidth,iHeight);
    }

    // 
    return S_OK;
}

HRESULT CBlackHole::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();

    // live height and width    
    INT iLiveHeight;
    INT iLiveWidth;
    if (m_bDisplayOn) // black hole on
    {
        iLiveHeight = (INT)(_basex::Height() * fProgress);
        iLiveWidth  = (INT)(_basex::Width() * fProgress);
    }
    else // black hole off
    {        
        iLiveHeight = (INT)(_basex::Height() * (1-fProgress) );
        iLiveWidth  = (INT)(_basex::Width() * (1-fProgress));
    }

    // length of should be moved from start position
    INT iLenMove = (INT)(m_vMove.GetLength() * fProgress);

    // calculate the live position
    TMPoint ptLive;
    BOOL bFlag = m_vMove.GetRemotePoint(ptLive,iLenMove);
    if (!bFlag)
    {
        ptLive = m_vMove.iEndPoint;
    }

    // Built live rectangle
#if 0
    if (m_bDisplayOn)
    {
        if (fProgress<=BLACKHOLE_ON_THREDHOLD)
        {
            m_rLiveRect = TMRect(ptLive,iLiveWidth/2,iLiveHeight/2);
        }
        else
        {
            m_rLiveRect = TMRect(ptLive,iLiveWidth,iLiveHeight);
        }
    }
    else
    {
        if (fProgress<=BLACKHOLE_OFF_THREDHOLD)
        {
            m_rLiveRect = TMRect(ptLive,iLiveWidth,iLiveHeight);
        }
        else
        {
            m_rLiveRect = TMRect(ptLive,iLiveWidth/2,iLiveHeight/2);
        }
    }
#endif

    m_rLiveRect = TMRect(ptLive,iLiveWidth,iLiveHeight);

    // 
    return S_OK;
}

HRESULT  CBlackHole::DrawLiveBitmap(IN HDC hdcHide,
                                    IN HDC hdcShow,
                                    IN HDC hdcOutput)
{

    // store some handy values
    INT nWidth = _basex::Width();
    INT nHeight = _basex::Height();
    RECT rCanvas = {0,0,nWidth,nHeight};

    // 
    RECT rectLive = m_rLiveRect.ToRECT();
    INT iDestX = rectLive.left;
    INT iDestY = rectLive.top;
    INT iDestWidth = rectLive.right - rectLive.left;
    INT iDestHeight = rectLive.bottom - rectLive.top;

    // 
    ::SetStretchBltMode(hdcOutput,STRETCH_HALFTONE);
	::SetBrushOrgEx(hdcOutput,0,0,NULL);
    ::StretchBlt(hdcOutput,iDestX,iDestY,iDestWidth,iDestHeight,
                 hdcShow,0,0,nWidth,nHeight,SRCCOPY);

    //
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CBlackHole::get_StartX(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_ptStart.x;

	return S_OK;
}

STDMETHODIMP CBlackHole::put_StartX(INT newVal)
{
	// TODO: Add your implementation code here
    m_ptStart.x = newVal;

	return S_OK;
}

STDMETHODIMP CBlackHole::get_StartY(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_ptStart.y;

	return S_OK;
}

STDMETHODIMP CBlackHole::put_StartY(INT newVal)
{
	// TODO: Add your implementation code here
    m_ptStart.y = newVal;

	return S_OK;
}

STDMETHODIMP CBlackHole::get_State(BOOL *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bDisplayOn;
	return S_OK;
}

STDMETHODIMP CBlackHole::put_State(BOOL newVal)
{
	// TODO: Add your implementation code here    
    m_bDisplayOn = newVal;
	return S_OK;
}
