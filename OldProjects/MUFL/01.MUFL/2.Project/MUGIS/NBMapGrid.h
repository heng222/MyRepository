#pragma once

#include "geometry.h"
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Map grid 

typedef   DWORD     TGridID;

struct TNBMapGrid
{
    TGridID     m_dwGridID;     // ID of grid

    WORD        m_wRowID;       // Row No.
    WORD        m_wColID;       // column no.
    TMRect      m_rectExtent;   // extent.

    WPARAM      m_wParam;
    LPARAM      m_lParam;

    // Constructor
    TNBMapGrid();
};

typedef TNBMapGrid* PTNBMapGrid;

typedef CTypedPtrList<CPtrList,PTNBMapGrid> CGridList;



//////////////////////////////////////////////////////////////////////////
// Grid manager interface

class __declspec(novtable) MGridManager
{

public:

    // 得到网格的尺寸
    virtual CSize   GetGridSize() const;

    // 得到地图的范围
    virtual TMRect  GetMapRect() const;

    // 得到网格的行数与列数
    virtual int     GetNumOfRow() const;
    virtual int     GetNumOfCol() const;

    // 根据点坐标得到所在的网格
    virtual const PTNBMapGrid  GetGridByPoint(TMPoint point) const;

    // 根据点坐标得到所在网格的行号与列号
    virtual BOOL    GetGridNoByPos(TMPoint point,int& iRowNo,int& iColNo) const;

    // 根据网格的行号与列号得到网格的ID
    virtual TGridID   GetGridIDByNo(int iRowNo,int iColNo) const;

    // 根据网格行列号得到网格的范围
    virtual TMRect  GetRectByNo(int iRowNo,int iColNo) const;

    // 得到与指定矩形相交的网格
    virtual void    GetGridByRect(TMRect rect,CGridList& gridList) const;

};



//////////////////////////////////////////////////////////////////////////
// Grid's Observer

class __declspec(novtable) MNBGridMgrObserver 
{

public:

    virtual void OnBuildingGrid();
    virtual void OnBuildGrid(PTNBMapGrid pGrid);
    virtual void OnGridsBuilt();
    virtual void OnDestroyGrid(PTNBMapGrid pGrid);

};



//////////////////////////////////////////////////////////////////////////
// Grid manager

class AFX_EXT_CLASS CNBMapGridMgr : public MGridManager
{

public:

    CNBMapGridMgr(MNBGridMgrObserver& observer);
    virtual ~CNBMapGridMgr();


public:

    BOOL    Initialize(TMRect mapRect,CSize sizeGrid);

    void    Close();


    // From MGridManager
public:

    TMRect      GetMapRect() const;
    CSize       GetGridSize() const;
    int         GetNumOfRow() const;
    int         GetNumOfCol() const;
    const       PTNBMapGrid  GetGridByPoint(TMPoint point) const;
    BOOL        GetGridNoByPos(TMPoint point,int& iRowNo,int& iColNo) const;
    TGridID     GetGridIDByNo(int iRowNo,int iColNo) const;
    TMRect      GetRectByNo(int iRowNo,int iColNo) const;
    void        GetGridByRect(TMRect rect,CGridList& gridList) const;


private:

    BOOL    BuildGrid();
    void    DestroyGrid();

private:

    MNBGridMgrObserver& m_Observer;

    TMRect  m_rectMap;      // Extent of map

    int    m_iUnitWidth;      // width unit of grid.
    int    m_iUnitHeight;     // height unit of grid.

    int    m_iNumRow;       // number of grids in horizontally
    int    m_iNumCol;       // number of grids in vertically


    CTypedPtrArray<CPtrArray,PTNBMapGrid> m_gridArray;
};


//////////////////////////////////////////////////////////////////////////
// End of File



