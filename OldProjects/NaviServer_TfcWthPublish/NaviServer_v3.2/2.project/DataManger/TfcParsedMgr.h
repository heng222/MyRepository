#pragma once

#include <NBMapEngine.h>
#include "InterfaceEx.h"
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

#define    SET_LINKLIST(pGrid,pLinkList)         (pGrid->m_wParam=(WPARAM)pLinkList)
#define    RETRIEVE_LINKLIST(pGrid)              ((CLinkList*)(pGrid->m_wParam))

//////////////////////////////////////////////////////////////////////////
class CTfcParsedMgr : public CNBMapEngine
{

public:

    CTfcParsedMgr(void);
    ~CTfcParsedMgr(void);

    // From CNBMapEngine
private:

    BOOL OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid);
    void OnActivedRectChanged(const CGridList& listGrid);
    void OnRotatingRadiansChanged(float aNewRotating);

    void OnBuildingGrid();
    void OnBuildGrid(PTNBMapGrid pGrid);
    void OnGridsBuilt();
    void OnDestroyGrid(PTNBMapGrid pGrid);


    // New functions
public:

    BOOL Open();

    void Close();

    BOOL ReadLink();


    // 查找与指定点最近的Link
    BOOL GetLinkByPoint(TMPoint point,CLinkList& aLinkList);

    // 查找与aRect相交的所有Link
    BOOL GetLinkByRect(TMRect aRect,CLinkList& aLinkList);

    // 更新路况信息 
    void UpdateLinkInf(CString strRoadID,int iSpeed);

   

private:

    // 保存所有Link
    CMapRoadToLinks   m_mapRoadIDtoLinks;

    TMRect m_rectMap;

};









