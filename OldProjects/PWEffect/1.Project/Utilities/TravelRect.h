// SmartRect.h: interface for the CSmartRect class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_SMARTRECT_H__2008134125
#define AFX_SMARTRECT_H__2008134125
//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "TMPoint.h"

//////////////////////////////////////////////////////////////////////////
// CSmartRect
class CTravelRect
{
public:

    // travel type
    enum TTravelType
    {
        ETravelOff = 0,  // travel off
        ETravelOn,       // travel on
    };

    // Position Type
    enum TPosType
    {
        EInvalid,
        EForward,
        EBackward,
    };

    // Constructor    
    CTravelRect();

public:


    operator  RECT() const;

    void      Initialize( IN TMRect rOriginal,                    
                    IN TMRect rExetent,
                    IN FLOAT fAngle, // In Degree
                    IN BOOL bTravelOn);

    VOID      Travel(IN LONG dwLen);
    VOID      TravelP(IN FLOAT fProgress);

    void      GetExetent(TMRect& rExtent) const;
    void      GetExetent(RECT& rExtent) const;

    void      GetOrigRect(RECT& rOrig) const;

    void      GetLiveRect(TMRect& rLive) const;
    void      GetLiveRect(RECT& rLive) const;

    // 得到LiveRect与OrgRect的相交区域（以OrgRect为参照区）
    void      GetIntersectRect(RECT& rIntersection) const;
    // 得到LiveRect与OrgRect的相交区域（以LiveRect为参照区）
    void      GetIntersectRectEx(RECT& rIntersection) const;

    BOOL      HasTraveledOut() const;
    
    INT       GetMaxTravelLen() const;
    INT       Width() const;
    INT       Height() const;

    void      SetLiveToExetent();

    // 判断两TravelRect的位置信息
    // 注：只有移动方向相同的TravelRect可以比较。
    TPosType  GetPositionType(const CTravelRect& aOther) const;
    

private:
    
    void      OnInitialize();

    BOOL      OnTraveling(LONG& lNewLen,
                    TMRect& rectOrg);

    TVector   BuildVector(INT iLen) const;

private:

    TTravelType m_iTravelType; // travel type

    INT         m_iMaxTravelLen; // Max travel length

    TMRect      m_rOriginal;  // original
    
    TMRect      m_rExtent; // extent
    
    TMRect      m_rStart;  // start
    

    // Live
    INT         m_iExtraLen; // attached travel length when TravelType=TraveOff
    TMRect      m_rectLive;  // live position.
    
    // angle with positive X-Coordinate
    FLOAT       m_fAngle;   

};

typedef std::vector<CTravelRect*> CTravelRectArray;
//////////////////////////////////////////////////////////////////////////
//
#endif