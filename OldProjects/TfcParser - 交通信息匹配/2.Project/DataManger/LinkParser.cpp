

#include "StdAfx.h"
#include ".\linkparser.h"
#include "GlobalMacro.h"
#include <XMLFile.h>

 //#define _TRACE_INFORMATION


//////////////////////////////////////////////////////////////////////////

#define         OFFSET_LONG         540
#define         OFFSET_LATI         106

//////////////////////////////////////////////////////////////////////////
// 临时XML文件名
#define             TEMPXMLFILENAME     _T("RawTfcInf.xml")

//////////////////////////////////////////////////////////////////////////

// 角度偏差
#define             EXTENT_ANGLE     (30*3.1415926/180)

// 距离偏差
#define             MIN_EXTENT   200    // Link与道路的最小偏差
#define             MAX_EXTENT   400    // 

//////////////////////////////////////////////////////////////////////////

CLinkParser::CLinkParser(void)
{
    m_pLinkList = NULL;
    m_pRoadList = NULL;
    m_pLinkGridMgr = NULL;
}

CLinkParser::~CLinkParser(void)
{
}

void CLinkParser::ClearResult()
{
    CString key;
    CLinkList* pLinkList;
    for( POSITION pos = m_mapRoadToLinks.GetStartPosition(); pos != NULL; )
    {
        m_mapRoadToLinks.GetNextAssoc( pos, key, pLinkList );
        pLinkList->RemoveAll();
        delete pLinkList;
    }
    m_mapRoadToLinks.RemoveAll();
}

void CLinkParser::Close()
{
    m_roadIDMgr.Clear();

    //
    ClearResult();
}

//////////////////////////////////////////////////////////////////////////


BOOL CLinkParser::Open()
{
    if (!m_roadIDMgr.ReadMapFile())
    {
        return FALSE;
    }

    return TRUE;
}

void CLinkParser::AttachRoadList(CTfcRoadList* pRoadList)
{
    m_pRoadList = pRoadList;
}


void CLinkParser::AttachLinkList(CLinkList* pLinkList)
{
    m_pLinkList = pLinkList;
}

void CLinkParser::AttachLinkGridMgr(const MGridManager* pGridMgr)
{
    m_pLinkGridMgr = pGridMgr;
}

//////////////////////////////////////////////////////////////////////////
//

void CLinkParser::ParseOneRoad(PTRawRoadTfcInf pRoad,CLinkList& linkList)
{
#ifdef _DEBUG
    if (pRoad->strRoadID.CompareNoCase("HI7017b")==0)
    {
        int a,b;
        a =2; 
        b =2;
    }
#endif

    // 定义Link映射表(LinkID到Link对象)，方便快速查找
    CTypedPtrMap<CMapStringToPtr,CString,PTLinkAttri> mapLink;

    // 

#ifdef _TRACE_INFORMATION
    TRACE("\n\n解析道路：%s(%s,%s).\n",pRoad->strRoadID,pRoad->strStartName,pRoad->strEndName);
#endif


    // 计算道路所在的网格
    CGridList gridList;
    m_pLinkGridMgr->GetGridByRect(TMRect(pRoad->ptCorStaPos,pRoad->ptCorEndPos),gridList);


    // 构建道路线段对象
    TSegmentVector segmentRoad(pRoad->ptCorStaPos,pRoad->ptCorEndPos);


    // 分析每个网格中的Link与道路是否匹配...

    POSITION gridPos = gridList.GetHeadPosition();
    while (gridPos)
    {
        PTNBMapGrid pGrid = gridList.GetNext(gridPos);

#ifdef _TRACE_INFORMATION
        TRACE("Grid %d(%d,%d)",pGrid->m_wGridID,pGrid->m_wRowID,pGrid->m_wColID);
        TRACE("对应的Link有：");
#endif

        // 取出网格中的Link链表
        CLinkList* pLinkList = RETRIEVE_LINKLIST(pGrid); 


        // 依次匹配、比较每个Link
        POSITION linkPos = pLinkList->GetHeadPosition();
        while (linkPos)
        {
            PTLinkAttri pLink = pLinkList->GetNext(linkPos);

            PTLinkAttri pLinkFound = NULL;
            CString strLinkID;
            strLinkID.Format("%d",pLink->m_dwLinkID);
            mapLink.Lookup(strLinkID,pLinkFound);

            // 如果此Link已经过解析，则继续解析下一条
            if (pLinkFound!=NULL)
            {
                continue;
            }


            /************************************************************************/
            /*                          解  析                                      */
            /* 1、比较夹角范围                                                      */
            /* 2、比较距离偏差                                                      */
            /************************************************************************/
            
#ifdef _DEBUG
            if (pLink->m_dwLinkID==2263)
            {
                int a,b;
                a =2; 
                b =2;
            }

#endif

            // 1、方向匹配……

            DOUBLE angle = segmentRoad.Angle(pLink->GetSegVector());

            
            // 道路与Link的夹角不大于EXTENT_ANGLE
            if ( angle>EXTENT_ANGLE )
            {
                if (pLink->m_iTrafficFlow==TLinkAttri::EBothDirection)
                {
                    if (PIRADIAN-angle>EXTENT_ANGLE)
                    {
                        continue;
                    }
                }
                else
                {
                    continue;
                }
            }


            // 2、距离匹配……

            DOUBLE fMinDistance = pLink->MinDistance(segmentRoad);
            //DOUBLE fMaxDistance = pLink->MaxDistance(segmentRoad);
            if ( fMinDistance > MIN_EXTENT)
            {
                continue;
            }


            // 3、投影匹配
            int iProjPos = pLink->ProjectionRelationship(segmentRoad);
            if ( iProjPos==TLinkAttri::E_PROJECT_NORELATION )
            {
                continue;
            }
            else if (iProjPos==TLinkAttri::E_LINKPROJ_PARTINSEG)
            {
                DOUBLE fStartToStart = pLink->DistanceToStart(segmentRoad.iStartPoint);
                DOUBLE fStartToEnd = pLink->DistanceToEnd(segmentRoad.iStartPoint);
                if (fStartToStart>fStartToEnd)
                {
                    continue;
                }  
                
                DOUBLE fEndToStart = pLink->DistanceToStart(segmentRoad.iEndPoint);
                DOUBLE fEndToEnd = pLink->DistanceToEnd(segmentRoad.iEndPoint);
                if (fEndToStart<fEndToEnd)
                {
                    continue;
                }

            }


            // 保存Link
            pLink->m_strRoadID = pRoad->strRoadID;
            mapLink.SetAt(strLinkID,pLink);


#ifdef _TRACE_INFORMATION
            TRACE("  %d,%s ",pLink->m_dwLinkID,pLink->m_strLinkName);
#endif


        }

#ifdef _TRACE_INFORMATION
        TRACE("\n");
#endif

    }

#ifdef _TRACE_INFORMATION
    TRACE("\n\n\n");
#endif

    //

    // Assignment
    POSITION pos;
    CString key;
    PTLinkAttri pLink;

    for( pos = mapLink.GetStartPosition(); pos != NULL; )
    {
        mapLink.GetNextAssoc( pos, key, pLink );
        linkList.AddTail(pLink);
    }
    mapLink.RemoveAll();

}


BOOL CLinkParser::ParseRoads()
{
    // 清除旧数据
    ClearResult();


    // 遍历道路进行解析
    POSITION pos = m_pRoadList->GetHeadPosition();
    while (pos)
    {
        PTRawRoadTfcInf pRoad = m_pRoadList->GetNext(pos);

        CLinkList* pLinkList = new CLinkList;

        ParseOneRoad(pRoad,*pLinkList);

        m_mapRoadToLinks.SetAt(pRoad->strRoadID,pLinkList);

    }


    return TRUE;
}


// 查找指定道路的解析结果
BOOL CLinkParser::LookUpLinks(CString strKey,CLinkList& linkList) const
{
    CLinkList* pLinkList = NULL;

    m_mapRoadToLinks.Lookup(strKey,pLinkList);


    if (pLinkList==NULL)
    {
        return FALSE;
    }

    POSITION pos = pLinkList->GetHeadPosition();
    while (pos)
    {
        linkList.AddTail(pLinkList->GetNext(pos));
    }

    return linkList.GetCount()>0;
}

// 保存结果至文本文件
BOOL CLinkParser::SaveToTextFile(const CString& strFilePath) const
{
    // 生成道路到Link的映射文件

    CStdioFile stdFile;
    if (!stdFile.Open(strFilePath,CFile::modeReadWrite|CFile::modeCreate|CFile::shareDenyNone))
    {
        return FALSE;
    }

    //

    CString strLine;

    strLine.Format(_T("Num= %d\n\n"),m_mapRoadToLinks.GetCount());
    stdFile.WriteString(strLine);


    // 
    CString key;
    CLinkList* pLinkList = NULL;
    for( POSITION pos = m_mapRoadToLinks.GetStartPosition(); pos != NULL; )
    {
        m_mapRoadToLinks.GetNextAssoc( pos, key, pLinkList );

        PTRoadIDMap pRoadIDMap = NULL;
        m_roadIDMgr.Lookup(key,pRoadIDMap);
        ASSERT(pRoadIDMap!=NULL);
        strLine.Format(_T("Road= %s,%d,%d\n"),key,pRoadIDMap->dwRoadID,pLinkList->GetCount());

        //strLine.Format(_T("Road= %s,%d\n"),key,pLinkList->GetCount());
        //
        stdFile.WriteString(strLine);

        // 保存Road对应的每一条Link
        POSITION linkPos = pLinkList->GetHeadPosition();
        while (linkPos)
        {
            PTLinkAttri pLink = pLinkList->GetNext(linkPos);
            strLine.Format(_T("%d-%d,%s,"),pLink->m_dwMapID,pLink->m_dwLinkID,pLink->m_strLinkName);
            stdFile.WriteString(strLine);

            // 保存Link的所有形状点
            int iCount = (int)(pLink->m_arrayPt.GetCount());
            strLine.Format(_T("%d,"),iCount);
            stdFile.WriteString(strLine);
            for (int k=0; k<iCount; k++)
            {
                strLine.Format(_T("%d,%d,"),pLink->m_arrayPt.GetAt(k).iX,pLink->m_arrayPt.GetAt(k).iY);
                stdFile.WriteString(strLine);
            }
            stdFile.WriteString("\n");

        }
        stdFile.WriteString("\n");

    }

    stdFile.Close();

    return TRUE;
}


// 保存解析结果至二进制文件
BOOL CLinkParser::SaveToBinFile(const CString& strFilePath) const
{
    // 生成道路到Link的映射文件

    CFile binFile;
    if (!binFile.Open(strFilePath,CFile::modeReadWrite|CFile::modeCreate|CFile::shareDenyWrite))
    {
        return FALSE;
    }

    // 监控路段的个数
    DWORD dwRoadCount = (DWORD)m_mapRoadToLinks.GetCount();
    binFile.Write(&dwRoadCount,sizeof(dwRoadCount));
    

    // 
    CString strRoadID;
    CLinkList* pLinkList = NULL;
    for( POSITION pos = m_mapRoadToLinks.GetStartPosition(); pos != NULL; )
    {
        m_mapRoadToLinks.GetNextAssoc( pos, strRoadID, pLinkList );

        // 监控路段的ID
        PTRoadIDMap pRoadIDMap = NULL;
        m_roadIDMgr.Lookup(strRoadID,pRoadIDMap);
        ASSERT(pRoadIDMap!=NULL);
        binFile.Write(&(pRoadIDMap->dwRoadID),sizeof(pRoadIDMap->dwRoadID));

        // 对应的Link个数
        WORD wLinkCount = (WORD)pLinkList->GetCount();
        binFile.Write(&wLinkCount,sizeof(wLinkCount));
        

        // 保存Road对应的每一条Link
        POSITION linkPos = pLinkList->GetHeadPosition();
        while (linkPos)
        {
            PTLinkAttri pLink = pLinkList->GetNext(linkPos);
            binFile.Write(&(pLink->m_dwMapID),sizeof(pLink->m_dwLinkID));
            binFile.Write(&(pLink->m_dwLinkID),sizeof(pLink->m_dwMapID));
        }

    }
    binFile.Close();

    return TRUE;
}





