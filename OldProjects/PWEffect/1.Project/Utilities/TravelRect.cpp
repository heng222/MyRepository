
#include "stdafx.h"
#include "TravelRect.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////
// Constructor
CTravelRect::CTravelRect()
{
    m_iMaxTravelLen = -1;
    m_rStart.SetNull();
}

//////////////////////////////////////////////////////////////////////////

 
CTravelRect::operator RECT() const
{
    return m_rectLive.ToRECT();
}

TVector CTravelRect::BuildVector(INT iLen) const
{
    TMPoint ptEnd(iLen,0);
    FLOAT fRadian = m_fAngle;
    ptEnd.Rotate(TMPoint(0,0),fRadian,FALSE);
    
    TVector vTravel;
    vTravel.m_lHx = ptEnd.iX;
    vTravel.m_lVy = ptEnd.iY;
    return vTravel;
}

void CTravelRect::Initialize(IN TMRect rOriginal,
                             IN TMRect rExetent,
                             IN FLOAT fAngle,
                             IN BOOL m_bTravelOn)
{
    m_rOriginal = rOriginal;
    m_rExtent = rExetent;
    m_fAngle = fAngle;
    m_iTravelType = m_bTravelOn?ETravelOn:ETravelOff;
    
    OnInitialize();
}

void CTravelRect::OnInitialize()
{    
    TVector vTempTravel;
    
    // calculate vector
    TMRect rTemp = m_rExtent;
    for(INT iNum = 1; m_rExtent.IsIntersects(rTemp); iNum++ )
    {
        vTempTravel = -BuildVector(iNum);
        
        // move along vector
        rTemp = m_rExtent;
        rTemp.MoveAlongVector(vTempTravel);  
    }

    
    // Max travel length.
    m_iMaxTravelLen = vTempTravel.GetLength()*2;
    

    // determine start rectangle
    m_rStart = m_rOriginal;
    m_rStart.MoveAlongVector(vTempTravel);

    if (m_iTravelType==ETravelOn)
    {
        m_iExtraLen = 0;
    }
    else
    {
        m_iExtraLen = vTempTravel.GetLength();
    }


    // determine live Rectangle
    if (m_iTravelType==ETravelOff)
    {
        m_rectLive = m_rOriginal;
    }
    else
    {
        m_rectLive = m_rStart;
    }   
}

// 
void CTravelRect::Travel(IN LONG lLen)
{    
    // 
    BOOL bFlag = OnTraveling(lLen,m_rectLive);

    //
    if (!bFlag)
    {
        
        TVector vTravel = BuildVector(lLen);
        
        // move
        m_rectLive.MoveAlongVector(vTravel);
    }
}

VOID CTravelRect::TravelP(IN FLOAT fProgress)
{
    LONG lLiveLen = LONG(GetMaxTravelLen()/2 * fProgress);
    Travel(lLiveLen);
}

BOOL CTravelRect::OnTraveling(LONG& lNewLen,
                              TMRect& rectOrg)
{    
    
    rectOrg = m_rStart;
    
    if (m_iTravelType==ETravelOff)
    {
        lNewLen += m_iExtraLen;
    }
    
    // 
    TVector vTravel = BuildVector(lNewLen);
    
    
    // move
    rectOrg.MoveAlongVector(vTravel);
    
    // 
#if 0
    BOOL bFlag; // Flag to indicate should be reset to the start position.
    bFlag =  (vTravel.m_lHx>0 && rectOrg.Left()>m_rExtent.Right() );
    bFlag |= (vTravel.m_lHx<0 && rectOrg.Right()<m_rExtent.Left());
    bFlag |= (vTravel.m_lVy>0 && rectOrg.Bottom()>m_rExtent.Top());
    bFlag |= (vTravel.m_lVy<0 && rectOrg.Top()<m_rExtent.Bottom());
    if (bFlag && !m_rExtent.IsIntersects(rectOrg))
#else
    if(lNewLen>m_iMaxTravelLen)
#endif
    {   
        rectOrg = m_rStart;
        lNewLen = lNewLen % m_iMaxTravelLen;
       
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void CTravelRect::GetIntersectRect(RECT& rIntersection) const
{    
    rIntersection = m_rExtent.Intersersects(m_rectLive).ToRECT();
}

void CTravelRect::GetIntersectRectEx(RECT& rectSct) const
{
    //
    TVector vTemp(m_rectLive.iTl,m_rOriginal.iTl);
    
    //
    TMRect rIntSct = m_rExtent.Intersersects(m_rectLive);
    rIntSct.MoveAlongVector(vTemp);
    rectSct = rIntSct.ToRECT();
}

BOOL CTravelRect::HasTraveledOut() const
{
    return !m_rExtent.IsIntersects(m_rectLive);
}

void CTravelRect::GetExetent(TMRect& rExtent) const
{
    rExtent = m_rExtent;
}

void CTravelRect::GetExetent(RECT& rExtent) const
{
    rExtent = m_rExtent.ToRECT();
}

void CTravelRect::GetOrigRect(RECT& rOrig) const
{
    rOrig = m_rOriginal.ToRECT();
}

void CTravelRect::GetLiveRect(TMRect& rLive) const
{
    rLive = m_rectLive;
}

void CTravelRect::GetLiveRect(RECT& rLive) const
{ 
    rLive = m_rectLive.ToRECT();
}


INT CTravelRect::Width() const
{
    return m_rectLive.Width();
}

INT CTravelRect::Height() const
{
    return m_rectLive.Height();
}

INT CTravelRect::GetMaxTravelLen() const
{
    return m_iMaxTravelLen;
}

void CTravelRect::SetLiveToExetent()
{
    m_rectLive = m_rExtent;
}

CTravelRect::TPosType CTravelRect::GetPositionType(const CTravelRect& aOther) const
{
    if (fabs(m_fAngle - aOther.m_fAngle) > 0.00001)
    {
        return EInvalid;
    }

    // Build a vector from current Rect to aOther Rect.
    TVector vCurrent(m_rectLive.Center(),aOther.m_rectLive.Center());

    // Build movement vector .
    TVector vMovement = BuildVector(m_rExtent.Width());

    // The angle between two vectors.
    if (vCurrent.Angle(vMovement)<=PIRADIAN/6)
    {
        return EBackward;
    }
    else
    {
        return EForward;
    }
}