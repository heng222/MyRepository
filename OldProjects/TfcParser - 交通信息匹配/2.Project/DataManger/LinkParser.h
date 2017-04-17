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

    // ��ͨ��·��Ϣ
    void    AttachRoadList(CTfcRoadList* pRoadList);

    // ��ͼ��Link����������
    void    AttachLinkList(CLinkList* pLinkList);
    void    AttachLinkGridMgr(const MGridManager* pGridMgr);

    // ����ָ����һ����·
    void    ParseOneRoad(PTRawRoadTfcInf pRoad,CLinkList& linkList);

    // �������е�·
    BOOL    ParseRoads();

    // ����ָ����·�Ľ������
    BOOL    LookUpLinks(CString strKey,CLinkList& linkList) const;

    // �������������ı��ļ�
    BOOL    SaveToTextFile(const CString& strFilePath) const;

    // �������������������ļ�
    BOOL    SaveToBinFile(const CString& strFilePath) const;



private:

    // �������
    CMapRoadToLinks m_mapRoadToLinks;

    // ����������
    void    ClearResult();


private:

    CRoadIDMgr    m_roadIDMgr;

    CTfcRoadList*   m_pRoadList;

    
    const MGridManager*   m_pLinkGridMgr;
    CLinkList*      m_pLinkList;

};
