#include "StdAfx.h"
#include ".\nbmapgrid.h"



//////////////////////////////////////////////////////////////////////////
// TNBMapGrid
TNBMapGrid::TNBMapGrid()
{
    m_wParam = NULL;
    m_lParam = NULL;
}



//////////////////////////////////////////////////////////////////////////

CNBMapGridMgr::CNBMapGridMgr(MNBGridMgrObserver& observer):
    m_Observer(observer)
{
    m_iUnitWidth = 100;
    m_iUnitHeight = 100;
    m_iNumRow = 0;
    m_iNumCol = 0;
}

CNBMapGridMgr::~CNBMapGridMgr()
{
    
}

void CNBMapGridMgr::Close()
{
    DestroyGrid();
}

void CNBMapGridMgr::DestroyGrid()
{
    INT_PTR iCount = m_gridArray.GetCount();

    for (INT_PTR i=0; i<iCount; i++)
    {
        PTNBMapGrid pGrid = m_gridArray.GetAt(i);
        m_Observer.OnDestroyGrid(pGrid);

        m_gridArray.SetAt(i,NULL);
        delete pGrid;
    }

    m_gridArray.SetSize(0);
}

//////////////////////////////////////////////////////////////////////////

BOOL CNBMapGridMgr::Initialize(TMRect mapRect,CSize sizeGrid)
{
    m_rectMap = mapRect;

    m_iUnitWidth = sizeGrid.cx;

    m_iUnitHeight = sizeGrid.cy;

    if (m_iUnitHeight<=0 || m_iUnitWidth<=0 )
    {
        return FALSE;
    }

    if ( !BuildGrid() )
    {
        return FALSE;
    }
    

    return TRUE;
}

BOOL CNBMapGridMgr::BuildGrid()
{
    ASSERT(m_iUnitHeight>0);
    ASSERT(m_iUnitWidth>0);

    TLcType lXmin = m_rectMap.iTl.iX;
    TLcType lXmax = m_rectMap.iBr.iX;

    if (lXmax<=lXmin)
    {
        return FALSE;
    }


    TLcType lYmin = m_rectMap.iBr.iY;
    TLcType lYmax = m_rectMap.iTl.iY;
    if (lYmin>=lYmax)
    {
        return FALSE;
    }

    // 确定行数
    LONG deltaY = LONG(lYmax-lYmin);
    if ((lYmax-lYmin)>deltaY)
    {
        deltaY++;
    }
    m_iNumRow = deltaY/m_iUnitHeight;
    if (deltaY%m_iUnitWidth>0)
    {
        m_iNumRow++;
    }

    // 确定列数
    LONG deltaX = LONG(lXmax-lXmin);
    if ((lYmax-lYmin)>deltaX)
    {
        deltaX++;
    }
    m_iNumCol = deltaX/m_iUnitWidth;
    if (deltaX%m_iUnitHeight>0)
    {
        m_iNumCol++;
    }

    // 分配内存
    m_gridArray.SetSize(m_iNumRow*m_iNumCol);
    

    // On building grid...
    m_Observer.OnBuildingGrid();


    // 依次构建每个网格
    for (int i=0; i<m_iNumRow; i++)
    {
        for (int j=0; j<m_iNumCol; j++)
        {
            PTNBMapGrid pGrid = new TNBMapGrid;

            pGrid->m_wRowID = WORD(i);
            pGrid->m_wColID = WORD(j);
            pGrid->m_dwGridID = GetGridIDByNo(i,j);
            pGrid->m_rectExtent.iTl.iX = j * m_iUnitWidth + lXmin;
            pGrid->m_rectExtent.iTl.iY = (i+1) * m_iUnitHeight + lYmin;
            pGrid->m_rectExtent.iBr.iX = pGrid->m_rectExtent.iTl.iX + m_iUnitWidth;
            pGrid->m_rectExtent.iBr.iY = pGrid->m_rectExtent.iTl.iY - m_iUnitHeight;

            m_gridArray.SetAt(pGrid->m_dwGridID,pGrid);


            // On building grid.
            m_Observer.OnBuildGrid(pGrid);
        }
    }

    // the grids have been built.
    m_Observer.OnGridsBuilt();


    return TRUE;
}


BOOL CNBMapGridMgr::GetGridNoByPos(TMPoint point,int& iRowNo,int& iColNo) const
{
    TLcType lXmin = m_rectMap.iTl.iX;
    TLcType lYmin = m_rectMap.iBr.iY;

    LONG lDeltaY = LONG(point.iY-lYmin);
    iRowNo = lDeltaY / m_iUnitHeight;

    // 
    LONG lDeltaX = LONG(point.iX-lXmin);
    iColNo = lDeltaX / m_iUnitWidth;

    if (iColNo<0 || iColNo>=m_iNumCol )
    {
        return FALSE;
    }

    if (iRowNo<0 || iRowNo>=m_iNumRow)
    {
        return FALSE;
    }

    return TRUE;
}

TGridID CNBMapGridMgr::GetGridIDByNo(int iRowNo,int iColNo) const
{
    TGridID wGridID = (iRowNo*m_iNumCol+iColNo); // 行号×列数＋列号

    return wGridID;
}

TMRect CNBMapGridMgr::GetRectByNo(int iRowNo,int iColNo) const
{
    TGridID dwGridID = GetGridIDByNo(iRowNo,iColNo);

    INT_PTR iNum = m_gridArray.GetUpperBound();

    if (iNum<0 || DWORD(iNum)<dwGridID)
    {
        return TMRect(0,0,0,0);
    }

    return m_gridArray.GetAt(dwGridID)->m_rectExtent;
}

const PTNBMapGrid CNBMapGridMgr::GetGridByPoint(TMPoint point) const
{
    int iRowNo, iColNo ;

    if ( !GetGridNoByPos(point,iRowNo,iColNo))
    {
        return NULL;
    }    

    TGridID dwGridID = GetGridIDByNo(iRowNo,iColNo);

    INT_PTR iNum = m_gridArray.GetUpperBound();

    if (iNum<0 || DWORD(iNum)<dwGridID)
    {
        return NULL;
    }


    return m_gridArray.GetAt(dwGridID);
}

void CNBMapGridMgr::GetGridByRect(TMRect rect,CGridList& gridList) const
{
    if (m_gridArray.GetCount()==0)
    {
        return;
    }

    // 是否相交
    if (!m_rectMap.IsIntersects(rect))
    {
        return;
    }

    // 计算当前地图范围与指定矩形的相交结果
    TMRect rectInters = m_rectMap.Intersersects(rect);

    // 
    TLcType lXmin = rectInters.iTl.iX;
    TLcType lXmax = rectInters.iBr.iX;

    TLcType lYmin = rectInters.iBr.iY;
    TLcType lYmax = rectInters.iTl.iY;

    // 起止行号
    int iRowMin,iRowMax;

    // 起止列号
    int iColMin ,iColMax ;

    GetGridNoByPos(TMPoint(lXmin,lYmin),iRowMin,iColMin);
    GetGridNoByPos(TMPoint(lXmax,lYmax),iRowMax,iColMax);


    for (int i=iRowMin; i<=iRowMax; i++)
    {
        for (int j=iColMin; j<=iColMax; j++)
        {
            TGridID wGridID = GetGridIDByNo(i,j);
            PTNBMapGrid pGrid = m_gridArray.GetAt(wGridID);
            gridList.AddTail(pGrid);
        }
    }


}

//////////////////////////////////////////////////////////////////////////
// Interface

TMRect CNBMapGridMgr::GetMapRect() const
{
    return m_rectMap;
}

CSize CNBMapGridMgr::GetGridSize() const
{
    return CSize(m_iUnitWidth,m_iUnitHeight);
}

int CNBMapGridMgr::GetNumOfRow() const
{
    return m_iNumRow;
}

int CNBMapGridMgr::GetNumOfCol() const
{
    return m_iNumCol;
}














