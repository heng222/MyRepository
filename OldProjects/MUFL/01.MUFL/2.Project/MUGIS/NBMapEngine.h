#pragma once

#include "MCoordinateTransfer.h"
#include "NBMapGrid.h"


//////////////////////////////////////////////////////////////////////////
// Attribute of engine.
struct TEgAttri 
{
    TMPoint     ptMapCenter;        // the Original center point of map. (changed always)
    CRect       rectDevice;         // the extent of device. ( changed rarely)
    DWORD       dwZoomScale;        // the current scale(use denominator) ( changed usually)
    DWORD       dwMaxScale;         // the max scale(use denominator) (changed usually)
    DWORD       dwMinScale;         // the min scale(use denominator) (changed usually)
    DOUBLE      fPhysicPerDevice;   // physic units(millimeter) per device unit(pixel)(never changed)
    DOUBLE      fPhysicPerLogic;    // physic units(millimeter) per logic unit(pixel) <changed usually>
    float       fUnitZoom;          // Unit of zoom ( changed it always)
    DOUBLE      fRoateRadians;      // Angles rotating clockwise.(based on Radians)

    // 
    TEgAttri();
    ~TEgAttri();

    TEgAttri& operator=(const TEgAttri& aOther);
};

//////////////////////////////////////////////////////////////////////////
// Class CNBMapEngine

class AFX_EXT_CLASS CNBMapEngine : public MCoorTransProvider,public MNBGridMgrObserver
{
public:

    CNBMapEngine(void);
    virtual ~CNBMapEngine(void)=0;

    // Initialize map engine.
    BOOL Initialize( TEgAttri& aAttri );

    // Close engine 
    void Close();

    // Event of map operation
    enum TMapEventType
    {
        EMO_NONE = 0,           // Not defined.

        EMO_MOVE_VECTOR = 10,   // Panning map along a vector. (wParam = TVector*)
        EMO_MAP_ZOOMIN,         // Zoom in map. ( Zoom in map by wParam=TMPoint* as center. )
        EMO_MAP_ZOOMOUT,        // Zoom out map. ( zoom out map by wParam=TMPoint* as center. ) 
        EMO_ROTATE_CENTER,      // Rotating by center of map.(wParam = float*)
        EMO_DEVICERECT_CHANGED, // the extent of device changed. (wParam=CRect*)

        EMO_EVENT_RESEVERED = 50,
    };
    virtual void MapOperation(int aEvent,WPARAM wParam=NULL,LPARAM lParam=NULL);

    // Retrieve the grid manager.
    const MGridManager*   GetGridMgr() const;

    // Retrieve the extent of map.
    TMRect  GetRectMapActived() const;

    // Get the center of the map
    TMPoint GetMapCenter() const;

    // From MCoorTransProvider
public:

    DWORD GetCurZoomScale() const;
    DWORD GetMaxZoomScale() const;
    DWORD GetMinZoomScale() const;
    void GetLogicRect(TMRect& rectLogic) const;
    float GetRotateRadians() const;
    void LpToDp(const TMPoint& aLp,CPoint& aDp) const;
    void DpToLp(const CPoint& aDp,TMPoint& aLp) const;
    void LrToDr(const TMRect& aLRect,CRect& aDRect) const; 
    void DrToLr(const CRect& aDRect,TMRect& aLRect) const;
    DOUBLE DlToLl(DOUBLE dLenDevice) const;
    DOUBLE LlToDl(DOUBLE dLenLogic) const;


    // From MNBGridMgrObserver
public:

    void OnBuildingGrid();
    void OnBuildGrid(PTNBMapGrid pGrid);
    void OnGridsBuilt();
    void OnDestroyGrid(PTNBMapGrid pGrid);


    // New virtual functions
protected:

    virtual BOOL OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid)=0;
    virtual void OnActivedRectChanged(const CGridList& listGrid);
    virtual void OnRotatingRadiansChanged(float aNewRotating);


protected:

    TLcType  TransferDeviceunitToLogicunit(int aTwipLen) const;

    void  LPtToDPt_Reserve(const TMPoint& aLp,CPoint& aDp) const;
    void  DPtToLPt_Reserve(const CPoint& aDp,TMPoint& aLp) const;


private:

    void  InitMapRect(TMPoint aMapCenter,LONG lWidthOfDevice,LONG lHeightOfDevice);
    void  AdjustTransferScale();
    void  RearrangeGridActived();

    void  OnActivedRectChanged_Reserved();

private:

    CGridList   m_listGridActived;

    CNBMapGridMgr   m_GridMgr;

    TEgAttri    m_lEgAttri;

    // transfer scale (logic coordinates to device coordinates)
    DOUBLE	m_fTranfScale;

    // logic rectangle activated.
    TMRect	m_rectLogicActived;

};
