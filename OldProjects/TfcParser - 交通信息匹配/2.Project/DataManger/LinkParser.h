#pragma once

#include "TfcParsedMgr.h"

#include "RoadIDMgr.h"

//////////////////////////////////////////////////////////////////////////


class CLinkParser
{

public:

    CLinkParser(void);
    ~CLinkParser(void);

    BOOL    Open();
    void    Close();

    // 交通道路信息
    void    AttachRoadList(CTfcRoadList* pRoadList);

    // 瑞图的Link数据与引擎
    void    AttachLinkList(CLinkList* pLinkList);
    void    AttachLinkGridMgr(const MGridManager* pGridMgr);

    // 解析指定的一条道路
    void    ParseOneRoad(PTRawRoadTfcInf pRoad,CLinkList& linkList);

    // 解析所有道路
    BOOL    ParseRoads();

    // 查找指定道路的解析结果
    BOOL    LookUpLinks(CString strKey,CLinkList& linkList) const;

    // 保存解析结果至文本文件
    BOOL    SaveToTextFile(const CString& strFilePath) const;

    // 保存解析结果至二进制文件
    BOOL    SaveToBinFile(const CString& strFilePath) const;



private:

    // 解析结果
    CMapRoadToLinks m_mapRoadToLinks;

    // 清除解析结果
    void    ClearResult();


private:

    CRoadIDMgr    m_roadIDMgr;

    CTfcRoadList*   m_pRoadList;

    
    const MGridManager*   m_pLinkGridMgr;
    CLinkList*      m_pLinkList;

};
