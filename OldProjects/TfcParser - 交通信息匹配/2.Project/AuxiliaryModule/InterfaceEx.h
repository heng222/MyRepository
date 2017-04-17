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
    EDB_CONNECTION_STATE = ESYS_RESERVED+0x100,      // ���ݿ�����״̬���


    EMSG_CREATE_TFCRAWVIEW,     // ����ԭʼ��ͨ��ʾ��ͼ
    EMSG_CREATE_TFCPARASEVIEW,  // ����������Ľ�ͨ��Ϣ��ʾ��ͼ

    EMSG_PARSE_LOOKUP,      // ����ָ����·�Ľ������

    EMSG_PARSE_START,       // ��ʼ����ȫ����ͨ��·��Ϣ
    EMSG_PARSE_PAUSE,       // ��ͣ����
    EMSG_PARSE_FINISHED,    // �������
    EMSG_PARSE_STORAGE,     // ����������

};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Inherited message Interface

//** ԭʼ·����Ϣ

class TRawRoadTfcInf
{

public:

    CString     strRoadID;      // ԭʼ��·���
    DWORD       dwRoadID;       // �µ�·���

    CString     strRoadName;    // ��·����
    CString     strStartName;   // �������
    CString     strEndName;     // �յ�����
    float       fSpeed;         // ��·�ٶ�
    float       loadTime;       // ����ʱ��
    COleDateTime  timePublish;  // ����ʱ��
    TMPoint     ptStartPos;     // �������(��λ��1/24��)
    TMPoint     ptCorStaPos;    // �����������ͼ�����еĶ�Ӧ��
    TMPoint     ptEndPos;       // �յ�����
    TMPoint     ptCorEndPos;    // ��ֹ��������ͼ�����еĶ�Ӧ��
    int         iJamReason;     // ӵ��ԭ��
    TMRect      rectExtent;     // ��Ӿ���

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
        // ���ĵ�
        CPoint pt;
        aTransfer.LpToDp(ptCorStaPos,pt);

        CSize size = pDC->GetTextExtent(strStartName);
        pDC->TextOut(pt.x-size.cx/2,pt.y-10,strStartName);
    }

    //
    // ��·��ͶӰ�Ƿ�����ָ�����߶���
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


//** -------------------------  Link���Զ���  --------------------------------------

class TLinkAttri
{

public:

    // ��·�ȼ�
    enum TLinkLevel
    {        
        EFreeWay		= 0,   // ����·
        ERingRoad		= 1,   // ���и���· 
        ENatinalHighway	= 2,   // ����
        EDistrictWay	= 3,   // ʡ��
        ECityMainRoad   = 4,   // �������ɵ�
        ECountryWay		= 5,   // �ص�
        ECityViceRoad   = 6,   // ���дθɵ�
        ECityBranchRoad = 7,   // ����֧·
        EOtherRoad		= 8,   // ������·
        EVillageWay		= 9,   // ���
        ENonNavigation  = 10,  // �ǵ�����·
    };
    int     m_iLinkLevel;

    // ��·�Ľ�ͨ������
    enum TTfcFlow
    {
        ENoInvestigation = -1,   // δ����
        EBothDirection = 0,      // ˫�����ͨ��
        EForward = 1,            // �����ͨ��
        EBackward = 2,           // �����ͨ��
        EClosed = 3,             // ˫�������ͨ��
    };
    int     m_iTrafficFlow;

public:
    
    DWORD           m_dwMapID;          // MapID
    DWORD           m_dwLinkID;         // LinkID    
    CString         m_strRoadID;        // ��Ӧ�ĵ�·ID(����ǰ�ĵ�·ID)
    CString         m_strLinkName;      // LinkName   

    TMRect          m_rectExtent;       // ��Ӿ���
    CMPointArray    m_arrayPt;          // ��״�����飨1/24S��


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

    // ����
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

    // ��״�����
    int GetNumofPt() const
    {
        return (int)m_arrayPt.GetCount();
    }

    // ĳ�㵽Link���ľ���
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

    // ĳ�㵽Link�յ�ľ���
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


    // Link�ĳ���
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

    // ����Link��Ӧ���߶�
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
        Link��ָ���߶ε�λ�ù�ϵ
        1��Link��ȫ��ͶӰ���߶���
        2���߶ε�ȫ��ͶӰ��Link��
        3��Link�Ĳ���ͶӰ���߶���(�߶εĲ���ͶӰ��Link��)
        4��Link���߶���ͶӰ��ϵ
    */
    enum TLPPType
    {
        E_LINKPROJ_ALLINSEG = 1,    // Link��ȫ��ͶӰ���߶���
        E_SEGMENT_ALLINLINK,        // �߶ε�ȫ��ͶӰ��Link��
        E_LINKPROJ_PARTINSEG,       // Link�Ĳ���ͶӰ���߶���(�߶εĲ���ͶӰ��Link��)
        E_PROJECT_NORELATION,       // Link���߶���ͶӰ��ϵ
    };
    int ProjectionRelationship( const TSegmentVector& aSegment) const
    {
        BOOL bFlagPre = FALSE;
        BOOL bFlagCur = FALSE;

        int iNumFlag = 0; // Link����״���ͶӰ���߶��ϵĸ���

        // Link��ͶӰ��ָ�����߶εĹ�ϵ
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
            // ָ�����߶�ͶӰ��Link�Ĺ�ϵ
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

    // ĳ�㵽Link����С����
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

    // Link��ĳ�߶ε�������
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

    // Link��ĳ�߶ε���̾���
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

    // Link��ָ���������Ƿ��ཻ
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