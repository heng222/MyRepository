

#ifndef __M_COORDINATES_TRANSFER_PROVIDER_345
#define __M_COORDINATES_TRANSFER_PROVIDER_345



#include "geometry.h"


/************************************************************************/
/*  
    Coordinates transforming interface
*/
/************************************************************************/
class __declspec(novtable) MCoorTransProvider
{

public:

    // Zoom scale
    virtual DWORD GetCurZoomScale() const;
    virtual DWORD GetMaxZoomScale() const;
    virtual DWORD GetMinZoomScale() const;

    // retrieve logic rectangle of the whole map
    virtual void GetLogicRect(TMRect& rectLogic) const;

    // retrieve rotating radians
    virtual float GetRotateRadians() const;

    // transferring functions between logic coordinates and device coordinates
    virtual void LpToDp(const TMPoint& aLp,CPoint& aDp) const; 
    virtual void DpToLp(const CPoint& aDp,TMPoint& aLp) const;
    virtual void LrToDr(const TMRect& aLRect,CRect& aDRect) const; 
    virtual void DrToLr(const CRect& aDRect,TMRect& aLRect) const;
    virtual DOUBLE DlToLl(DOUBLE dLenDevice) const;
    virtual DOUBLE LlToDl(DOUBLE dLenLogic) const;

};

//////////////////////////////////////////////////////////////////////////

#endif