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

    // �õ�����ĳߴ�
    virtual CSize   GetGridSize() const;

    // �õ���ͼ�ķ�Χ
    virtual TMRect  GetMapRect() const;

    // �õ����������������
    virtual int     GetNumOfRow() const;
    virtual int     GetNumOfCol() const;

    // ���ݵ�����õ����ڵ�����
    virtual const PTNBMapGrid  GetGridByPoint(TMPoint point) const;

    // ���ݵ�����õ�����������к����к�
    virtual BOOL    GetGridNoByPos(TMPoint point,int& iRowNo,int& iColNo) const;

    // ����������к����кŵõ������ID
    virtual TGridID   GetGridIDByNo(int iRowNo,int iColNo) const;

    // �����������кŵõ�����ķ�Χ
    virtual TMRect  GetRectByNo(int iRowNo,int iColNo) const;

    // �õ���ָ�������ཻ������
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



