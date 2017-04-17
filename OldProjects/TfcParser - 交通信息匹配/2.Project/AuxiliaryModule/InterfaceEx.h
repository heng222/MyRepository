/*
* ============================================================================
*  Description: Internal message structure definition
* ============================================================================
*/
#ifndef _INTERMOUDULE_COMM_ATTRI__
#define _INTERMOUDULE_COMM_ATTRI__
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#include <NBaseModule.h>
#include "GlobalStrcton.h"
#include <AppLogMgr.h>
#include <CommonFunc.h>
#include <geometry.h>
#include <MCoordinateTransfer.h>
#include <UserColors.h>


//////////////////////////////////////////////////////////////////////////

//#define     ID_MODULE_WEBSERV   ID_MODULE_RESERVED+0x10     // WebService module
//#define     ID_MODULE_HTTP      ID_MODULE_RESERVED+0x12     // Http Module

//////////////////////////////////////////////////////////////////////////
// Inherited message Interface

// Type of Inter module message
enum TIMCMsgType
{
    EDB_CONNECTION_STATE = ESYS_RESERVED+0x100,      // 数据库连接状态检测


    EMSG_CREATE_TFCRAWVIEW,     // 创建原始交通显示视图
    EMSG_CREATE_TFCPARASEVIEW,  // 创建解析后的交通信息显示视图

    EMSG_PARSE_LOOKUP,      // 查找指定道路的解析结果

    EMSG_PARSE_START,       // 开始解析全部交通道路信息
    EMSG_PARSE_PAUSE,       // 暂停解析
    EMSG_PARSE_FINISHED,    // 解析完成
    EMSG_PARSE_STORAGE,     // 保存解析结果

};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Inherited message Interface

//** 原始路况信息

class TRawRoadTfcInf
{

public:

    CString     strRoadID;      // 原始道路编号
    DWORD       dwRoadID;       // 新道路编号

    CString     strRoadName;    // 道路名称
    CString     strStartName;   // 起点名称
    CString     strEndName;     // 终点名称
    float       fSpeed;         // 道路速度
    float       loadTime;       // 旅行时间
    COleDateTime  timePublish;  // 发布时间
    TMPoint     ptStartPos;     // 起点坐标(单位：1/24秒)
    TMPoint     ptCorStaPos;    // 起点坐标在瑞图数据中的对应点
    TMPoint     ptEndPos;       // 终点坐标
    TMPoint     ptCorEndPos;    // 终止坐标在瑞图数据中的对应点
    int         iJamReason;     // 拥堵原因
    TMRect      rectExtent;     // 外接矩形

    // Attribute for drawing

    // Constructor
    TRawRoadTfcInf()
    {
        //
        ptCorStaPos.iX = ptCorStaPos.iY = -1;
        ptCorEndPos.iX = ptCorEndPos.iY = -1;
        iJamReason = 0;

        //
    }

    // Functions
    void Copy(const TRawRoadTfcInf& other)
    {
        if (this!=&other)
        {
            strRoadID = other.strRoadID;    
            strRoadName = other.strRoadName;   
            strStartName = other.strStartName;   
            strEndName = other.strEndName;    
            fSpeed = other.fSpeed;
            loadTime = other.loadTime;
            timePublish = other.timePublish;     
            ptStartPos = other.ptStartPos;     
            ptCorStaPos = other.ptCorStaPos;
            ptEndPos = other.ptEndPos;      
            ptCorEndPos = other.ptCorEndPos;
            iJamReason = other.iJamReason;
        }
    }


    //

    void DrawNode(CDC* pDC,const MCoorTransProvider& ctProvider) const
    {
        CPoint ptStart;
        ctProvider.LpToDp(ptCorStaPos,ptStart);
        CRect rectStart( ptStart.x-4,ptStart.y+4,ptStart.x+4,ptStart.y-4);
        pDC->Ellipse(rectStart);
    }

    void DrawRoad(CDC* pDC,const MCoorTransProvider& ctProvider) const
    {
        CPoint ptStart,ptEnd;
        ctProvider.LpToDp(ptCorStaPos,ptStart);
        ctProvider.LpToDp(ptCorEndPos,ptEnd);
        pDC->MoveTo(ptStart);
        pDC->LineTo(ptEnd);
    }

    //
    void DrawRoadName(CDC* pDC,const MCoorTransProvider& aTransfer) const
    {
        // 中心点
        CPoint pt;
        aTransfer.LpToDp(ptCorStaPos,pt);

        CSize size = pDC->GetTextExtent(strStartName);
        pDC->TextOut(pt.x-size.cx/2,pt.y-10,strStartName);
    }

    //
    // 道路的投影是否与在指定的线段上
    /*BOOL ProjectionInSeg( const TSegmentVector& aSegment) const
    {
        if (aSegment.ProjectionInSeg(ptCorStaPos))
        {
            return TRUE;
        }

        if (aSegment.ProjectionInSeg(ptCorEndPos))
        {
            return TRUE;
        }

        return FALSE;
    }*/

};
typedef TRawRoadTfcInf* PTRawRoadTfcInf;

typedef CTypedPtrList<CPtrList,PTRawRoadTfcInf> CTfcRoadList;

typedef CTypedPtrMap<CMapStringToPtr,CString,PTRawRoadTfcInf> CMapTfcRoad;


//** -------------------------  Link属性定义  --------------------------------------

class TLinkAttri
{

public:

    // 道路等级
    enum TLinkLevel
    {        
        EFreeWay		= 0,   // 高速路
        ERingRoad		= 1,   // 都市高速路 
        ENatinalHighway	= 2,   // 国道
        EDistrictWay	= 3,   // 省道
        ECityMainRoad   = 4,   // 城市主干道
        ECountryWay		= 5,   // 县道
        ECityViceRoad   = 6,   // 城市次干道
        ECityBranchRoad = 7,   // 城市支路
        EOtherRoad		= 8,   // 其它道路
        EVillageWay		= 9,   // 乡道
        ENonNavigation  = 10,  // 非导航道路
    };
    int     m_iLinkLevel;

    // 道路的交通流方向
    enum TTfcFlow
    {
        ENoInvestigation = -1,   // 未调查
        EBothDirection = 0,      // 双向均可通行
        EForward = 1,            // 正向可通行
        EBackward = 2,           // 反向可通行
        EClosed = 3,             // 双向均不可通行
    };
    int     m_iTrafficFlow;

public:
    
    DWORD           m_dwMapID;          // MapID
    DWORD           m_dwLinkID;         // LinkID    
    CString         m_strRoadID;        // 对应的道路ID(解析前的道路ID)
    CString         m_strLinkName;      // LinkName   

    TMRect          m_rectExtent;       // 外接矩形
    CMPointArray    m_arrayPt;          // 形状点数组（1/24S）


    // Attribute for drawing

public:

    // Constructor
    TLinkAttri()
    {
    }
    ~TLinkAttri()
    {
    }

    // New functions
    /*TLinkAttri& operator= (const TLinkAttri& other)
    {
        if (this != &other)
        {
            m_strLinkID = other.m_strLinkID;
            m_strRoadID = other.m_strRoadID;
            m_strLinkName = other.m_strLinkName;
            m_rectExtent = other.m_rectExtent;
        }
        return *this;
        }*/

    // 绘制
    void DrawLink(CDC* pDC,const MCoorTransProvider& aMtp)
    {

        CPoint ptShape;
        for (int i=0; i<m_arrayPt.GetCount(); i++)
        {
            aMtp.LpToDp(m_arrayPt.GetAt(i),ptShape);

            if (i==0)
            {
                pDC->MoveTo(ptShape);
            }
            else
            {
                pDC->LineTo(ptShape);
            }
        }       

    }

    // 形状点个数
    int GetNumofPt() const
    {
        return (int)m_arrayPt.GetCount();
    }

    // 某点到Link起点的距离
    DOUBLE DistanceToStart(TMPoint aPoint) const
    {
        if (m_arrayPt.GetCount()>0)
        {
            return aPoint.Distance(m_arrayPt.GetAt(0));
        }
        else
        {
            return 0;
        }
    }

    // 某点到Link终点的距离
    DOUBLE DistanceToEnd(TMPoint aPoint) const
    {
        int iCount = (int)m_arrayPt.GetCount();
        if (iCount>1)
        {
            return aPoint.Distance(m_arrayPt.GetAt(iCount-1));
        }
        else
        {
            return 0;
        }
    }


    // Link的长度
    DOUBLE GetLength() const
    {
        DOUBLE fDistance = 0;
        int iCount = (int)m_arrayPt.GetCount();
        if (iCount<2)
        {
            return 0;            
        }

        for (int i=0; i<iCount-1; i++)
        {
            TMPoint pt1 = m_arrayPt.GetAt(i);
            TMPoint pt2 = m_arrayPt.GetAt(i+1);
            fDistance += pt1.Distance(pt2);
        }

        return fDistance;
    }

    // 构建Link相应的线段
    TSegmentVector GetSegVector() const
    {
        int iCount = (int)m_arrayPt.GetCount();
        if (iCount>=2)
        {

            TMPoint pt1 = m_arrayPt.GetAt(0);
            TMPoint pt2 = m_arrayPt.GetAt(iCount-1);

            TSegmentVector ver;
            if (m_iTrafficFlow==EForward)
            {
                ver = TSegmentVector(pt1,pt2);
            }
            else if (m_iTrafficFlow==EBackward)
            {
                ver = TSegmentVector(pt2,pt1);
            }
            else
            {
                ver = TSegmentVector(pt1,pt2);
            }
            return ver;
        }
        else
        {
            return TSegmentVector(TMPoint(0,0),TMPoint(0,0));
        }
    }
    
    /**
        Link与指定线段的位置关系
        1、Link的全部投影在线段上
        2、线段的全部投影在Link上
        3、Link的部分投影在线段上(线段的部分投影在Link上)
        4、Link与线段无投影关系
    */
    enum TLPPType
    {
        E_LINKPROJ_ALLINSEG = 1,    // Link的全部投影在线段上
        E_SEGMENT_ALLINLINK,        // 线段的全部投影在Link上
        E_LINKPROJ_PARTINSEG,       // Link的部分投影在线段上(线段的部分投影在Link上)
        E_PROJECT_NORELATION,       // Link与线段无投影关系
    };
    int ProjectionRelationship( const TSegmentVector& aSegment) const
    {
        BOOL bFlagPre = FALSE;
        BOOL bFlagCur = FALSE;

        int iNumFlag = 0; // Link的形状点的投影在线段上的个数

        // Link的投影与指定的线段的关系
        int iCount = (int)m_arrayPt.GetCount();
        for (int i=0; i<iCount; i++)
        {
            TMPoint pt = m_arrayPt.GetAt(i);

            if(aSegment.ProjectionPosition(pt)==TSegmentVector::EPP_INSEGMENT)
            {
                iNumFlag++;
            }
        }

        // 
        if (iNumFlag==0)
        {
            int iNum = 0;
            // 指定的线段投影与Link的关系
            TSegmentVector segSelf = GetSegVector();

            if (segSelf.ProjectionPosition(aSegment.iStartPoint)==TSegmentVector::EPP_INSEGMENT)
            {
                iNum++;
            }

            if (segSelf.ProjectionPosition(aSegment.iEndPoint)==TSegmentVector::EPP_INSEGMENT)
            {
                iNum++;
            }

            if (iNum==0)
            {
                return E_PROJECT_NORELATION;
            }
            else if(iNum==2)
            {
                return E_SEGMENT_ALLINLINK;
            }
            else
            {
                return E_LINKPROJ_PARTINSEG;
            }
        }
        else if(iNumFlag==iCount)
        {
            return E_LINKPROJ_ALLINSEG;
        }
        else
        {
            return E_LINKPROJ_PARTINSEG;
        }


  


    }

   
//    DOUBLE GetAzimuth() const
//    {
//        int iCount = (int)m_arrayPt.GetCount();
//        if (iCount>=2)
//        {
//#ifdef _DEBUG
//
//            TMPoint pt1 = m_arrayPt.GetAt(0);
//            TMPoint pt2 = m_arrayPt.GetAt(iCount-1);
//#endif
//            TSegmentVector ver(m_arrayPt.GetAt(0),m_arrayPt.GetAt(iCount-1));
//            return ver.GetAzimuth();
//        }
//        else
//        {
//            return 0;
//        }
//    }

    // 某点到Link的最小距离
    DOUBLE MinDistance(TMPoint point) const
    { 
        DOUBLE fMinDis = 0;
        int iCount = (int)m_arrayPt.GetCount();

        for (int i=0; i<iCount-1; i++)
        {
            TMPoint pt1 = m_arrayPt.GetAt(i);
            TMPoint pt2 = m_arrayPt.GetAt(i+1);
            TSegmentVector seg(pt1,pt2);

            DOUBLE fDistance = seg.Distance(point);

            if (fDistance<fMinDis || i==0)
            {
                fMinDis = fDistance; 
                if (fMinDis<=1E-6)
                {
                    break;
                }
            }
        }

        return fMinDis;

    }

    // Link到某线段的最大距离
    DOUBLE MaxDistance( const TSegmentVector& aSegment) const
    {
        DOUBLE fMaxDis = 0;
        int iCount = (int)m_arrayPt.GetCount();

        for (int i=0; i<iCount; i++)
        {
            TMPoint pt = m_arrayPt.GetAt(i);
            DOUBLE fDistance = aSegment.Distance(pt);
            if (fDistance>fMaxDis || i==0)
            {
                fMaxDis = fDistance; 
            }
        }

        return fMaxDis;
    }

    // Link到某线段的最短距离
    DOUBLE MinDistance( const TSegmentVector& aSegment ) const
    {
        DOUBLE fMinDis = 0;
        int iCount = (int)m_arrayPt.GetCount();

        for (int i=0; i<iCount; i++)
        {
            TMPoint pt = m_arrayPt.GetAt(i);
            DOUBLE fDistance = aSegment.Distance(pt);
            if (fDistance<fMinDis || i==0)
            {
                fMinDis = fDistance; 
                if (fMinDis<=1E-6)
                {
                    break;
                }
            }
        }

        return fMinDis;
    }

    // Link与指定的区域是否相交
    BOOL IsIntersects(TMRect aRect) const
    {
        int iCount = (int)m_arrayPt.GetCount();

        for (int i=0; i<iCount-1; i++)
        {
            TMPoint pt1 = m_arrayPt.GetAt(i);
            TMPoint pt2 = m_arrayPt.GetAt(i+1);
            TSegmentVector seg(pt1,pt2);

            BOOL bFlag = aRect.IsIntersects(seg);

            if (bFlag)
            {
                return TRUE;                
            }
        }
        
        return FALSE;
    }
};  
typedef TLinkAttri* PTLinkAttri;

class CLinkList : public CTypedPtrList<CPtrList,TLinkAttri*>
{
public:

    CLinkList()
    {
    }

    ~CLinkList()
    {
        //ClearList();
    }

    // 
    void ClearList()
    {
        while (GetHeadPosition())
        {
            PTLinkAttri pElment = RemoveHead();
            delete pElment;
        }
    }
};

typedef CTypedPtrMap<CMapStringToPtr,CString,CLinkList*> CMapRoadToLinks;





//////////////////////////////////////////////////////////////////////////
#endif