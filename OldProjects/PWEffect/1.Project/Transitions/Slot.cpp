// Slot.cpp : Implementation of CSlot
#include "stdafx.h"
#include "Slot.h"

/////////////////////////////////////////////////////////////////////////////
// CSlot

//
//  --------------- CSlot ----------------
//
HRESULT CSlot::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    //
    m_bDisplayOn = TRUE;
    
    return S_OK;
}

HRESULT CSlot::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here
    
    //
    return S_OK;
}


HRESULT CSlot::OnTerminate()
{
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Private methods


HRESULT CSlot::ResetControlValue()
{
    INT nWidth = _basex::Width();
    INT nHeight = _basex::Height();
    
    // the max len
    m_iLeftSlotLen  = (INT)(nHeight * 3);
    m_iMidSlotLen   = (INT)(nHeight * 5);
    m_iRightSlotLen = (INT)(nHeight * 7);

    // left slot
    TMRect rLeftOrg = TMRect(0,0,nWidth/3,nHeight);
    m_trLeft.Initialize(rLeftOrg,rLeftOrg,(FLOAT)(PIRADIAN/2),TRUE);

    // middle slot    
    TMRect rMidOrg = TMRect(rLeftOrg.Right(),0,rLeftOrg.Right()+nWidth/3,nHeight);
    m_trMid.Initialize(rMidOrg,rMidOrg,(FLOAT)(PIRADIAN/2),TRUE);
   
    // right slot
    TMRect rRightOrg = TMRect(rMidOrg.Right(),0,nWidth,nHeight);    
    m_trRight.Initialize(rRightOrg,rRightOrg,(FLOAT)(PIRADIAN/2),TRUE);

    // 
    return S_OK;
}

HRESULT CSlot::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
    if(IsEqual(fProgress,1.0f))
    {
        return S_FALSE;
    }

    INT iLeftTravelLen = (INT)(fProgress*m_iLeftSlotLen);
    INT iMidTravelLen = (INT)(fProgress*m_iMidSlotLen);
    INT iRightTravelLen = (INT)(fProgress*m_iRightSlotLen);

    m_trLeft.Travel(iLeftTravelLen);
    m_trMid.Travel(iMidTravelLen);
    m_trRight.Travel(iRightTravelLen);

    if (m_iLeftSlotLen-iLeftTravelLen<m_trLeft.Height())
    {
        m_trLeft.SetLiveToExetent();
    }

    if (m_iMidSlotLen-iMidTravelLen<m_trMid.Height())
    {
        m_trMid.SetLiveToExetent();
    }


    // 
    return S_OK;
}

HRESULT CSlot::DrawLiveBitmap(IN HDC hInDC1,
                              IN HDC hInDC2,
                              IN HDC hOutDC)
{
    // Left slot
    DrawSlot(hInDC1,hInDC2,hOutDC,m_trLeft);
    
    // middle
    DrawSlot(hInDC1,hInDC2,hOutDC,m_trMid);
    
    // right slot  
    DrawSlot(hInDC1,hInDC2,hOutDC,m_trRight);
    
    return S_OK;
}

void CSlot::DrawSlot(IN HDC hInDC1,IN HDC hInDC2,IN HDC hOutDC,
        CTravelRect& aTravelRect)
{
    INT nHeight = _basex::Height();
    
    // travel to draw
    RECT rLive,rIntersect,rExtent,rOrig;
    INT iISWidth, iISHeight;

    // intersect slot   
    aTravelRect.GetOrigRect(rOrig);
    aTravelRect.GetExetent(rExtent);
    aTravelRect.GetLiveRect(rLive);
    aTravelRect.GetIntersectRect(rIntersect);
    
    iISWidth  = rIntersect.right - rIntersect.left;
    iISHeight = rIntersect.bottom - rIntersect.top; 
    
    ::BitBlt(hOutDC,
        rLive.left,
        rLive.top,
        aTravelRect.Width(),
        aTravelRect.Height(),
        hInDC2,
        rOrig.left,
        rOrig.top,
        SRCCOPY);
    
    // another part.
    if (rLive.top<rExtent.top)
    {
        ::BitBlt(hOutDC, rExtent.left, rExtent.top + iISHeight,
            aTravelRect.Width(), nHeight - iISHeight,            
            hInDC1, rExtent.left, rExtent.top,
            SRCCOPY);
    }
    else
    {
        ::BitBlt(hOutDC, rExtent.left, rExtent.top,
            aTravelRect.Width(), nHeight - iISHeight,            
            hInDC1,   rExtent.left, rExtent.top + iISHeight,
            SRCCOPY);
    }
    
    
}
//////////////////////////////////////////////////////////////////////////
// Properties



