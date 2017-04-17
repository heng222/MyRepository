#pragma once

#include "afx.h"
#include <afxtempl.h>
#include "NBMapEngine.h"
#include "UserColors.h"
#include "DataModulInterface.h"
#include "RoadIDMgr.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

#define    SET_ROADLIST(pGrid,pRoadList)         (pGrid->m_wParam=(WPARAM)pRoadList)
#define    RETRIEVE_ROADLIST(pGrid)              ((CTfcRoadList*)(pGrid->m_wParam))

//////////////////////////////////////////////////////////////////////////

class CTfcInfMgr : public CNBMapEngine
{
public:
    CTfcInfMgr(void);
    ~CTfcInfMgr(void);


    // From CNBMapEngine
private:

    BOOL OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid);

    void OnBuildingGrid();
    void OnBuildGrid(PTNBMapGrid pGrid);
    void OnGridsBuilt();
    void OnDestroyGrid(PTNBMapGrid pGrid);

public:

    BOOL  Open();
	
    CTfcRoadList* GetRoadList() { return &m_tfcRoadList; }

    void  SetActivedRoad(const CTfcRoadList& aRoadList);
    
    void  DrawTfcStream(CDC* pDC,BOOL bDrawName);

    BOOL  GetRoadByPoint(TMPoint point,CTfcRoadList& aRoadList);

    void  Close();


private:


    CRoadIDMgr    m_roadIDMgr;

    CTfcRoadList  m_tfcRoadList;

    CTfcRoadList  m_tfcRoadActived;

    TMRect  m_rectMap;

};
