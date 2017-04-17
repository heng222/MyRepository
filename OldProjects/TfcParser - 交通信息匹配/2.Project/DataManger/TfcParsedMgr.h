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

    
    CLinkList* GetLinkList() { return &m_linkList; };

    // ������ָ���������Link
    BOOL GetLinkByPoint(TMPoint point,CLinkList& aLinkList);

    // ������aRect�ཻ������Link
    BOOL GetLinkByRect(TMRect aRect,CLinkList& aLinkList);

    // ��ָ����Link�ƶ�����ͼ����
    void  MoveLinkToMapCenter(const TLinkAttri& aLink);

    //
    void ActiveLink(CLinkList& linkList);

    void DrawLink(CDC* pDC) const;
    void DrawRoadNode(CDC* pDC) const;
    void DrawNodeName(CDC* pDC) const;

    void SetRoadNode(CTfcRoadList* pRoadList) { m_pRoadList = pRoadList;};


private:

    CLinkList   m_linkList;

    TMRect m_rectMap;

    CLinkList m_linkActived;

    CTfcRoadList*    m_pRoadList;
};









