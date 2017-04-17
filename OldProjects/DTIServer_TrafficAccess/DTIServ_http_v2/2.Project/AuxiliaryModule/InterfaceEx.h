/*
* ============================================================================
*  Description: 内部消息结构定义
* ============================================================================
*/
#ifndef _INTERMOUDULE_COMM_ATTRI__
#define _INTERMOUDULE_COMM_ATTRI__
//////////////////////////////////////////////////////////////////////////

#include <NBaseModule.h>
#include <MCoordinateTransfer.h>
#include <Geometry.h>
#include <UserColors.h>

//////////////////////////////////////////////////////////////////////////

#define     ID_MODULE_WEBSERV   ID_MODULE_RESERVED+0x10     // WebService module
#define     ID_MODULE_HTTP      ID_MODULE_RESERVED+0x12     // Http Module

//////////////////////////////////////////////////////////////////////////
// Inherited message Interface

// Type of Inter module message
enum TIMCMsgType
{
    EDB_CONNECTION_STATE = ESYS_RESERVED+0x100,      // 数据库连接状态检测


    EMSG_RECV_RAWTFCINF,		// 收到新的交通信息
    EMSG_SHOW_TIPWND,           // 显示信息窗口
    EMSG_CLOSE_TIPWND,          // 关闭信息窗口


    EMSG_FLASH_TFCRAW,          // 刷新原始交通信息
    EMSG_CREATE_TFCRAWVIEW,     // 创建原始交通显示视图
    EMSG_CREATE_TFCPARASEVIEW,  // 创建解析后的交通信息显示视图

};
//////////////////////////////////////////////////////////////////////////
// Inherited message Interface

// 交通畅通级别
enum ETrafficLevel
{
    ETfc_NoInf = -1,// 无信息
    ETfc_free = 0,  // 畅通
    ETfc_slowly,    // 缓慢
    ETfc_jam,       // 拥堵
};

//** ------------------------------- 原始路况信息 -------------------------

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

    //
    TRawRoadTfcInf()
    {
        //
        ptCorStaPos.iX = ptCorStaPos.iY = -1;
        ptCorEndPos.iX = ptCorEndPos.iY = -1;
        iJamReason = 0;
    }

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
    void DrawRoad(CDC* pDC,MCoorTransProvider& ctProvider)
    {
        CPen newPen;
        CBrush brush;
        COLORREF lineClr;
        if (fSpeed>=40)
        {
            lineClr = CLR_DARKGREEN;
        }
        else if (fSpeed<40 && fSpeed>20)
        {
            lineClr = CLR_YELLOW;
        }
        else if (fSpeed<=20 && fSpeed>=0)
        {
            lineClr = CLR_RED;
        }
        else
        {
            lineClr = CLR_DEEPGRAY;
        }
        newPen.CreatePen(PS_SOLID,5,lineClr);
        brush.CreateSolidBrush(CLR_BKG_2);
        //brush.CreateHatchBrush(HS_CROSS,CLR_BKG_1);

        CPen* pOldPen = pDC->SelectObject(&newPen);
        CBrush* pOldBrush = pDC->SelectObject(&brush);


        //
        CPoint ptStart,ptEnd;
        ctProvider.LpToDp(ptStartPos,ptStart);
        ctProvider.LpToDp(ptEndPos,ptEnd);
        pDC->MoveTo(ptStart);
        pDC->LineTo(ptEnd);


        //
        pDC->SelectObject(pOldPen);
        pDC->SelectObject(pOldBrush);
    }

    //
    void DrawRoadName(CDC* pDC,MCoorTransProvider& aTransfer)
    {

        // 中心点
        CPoint pt;
        aTransfer.LpToDp(ptStartPos,pt);

        // 设置默认字体
        CFont  font;
        int iFontHeight;
        iFontHeight = 12;
        font.CreateFont(iFontHeight,0, 0, 0, FW_THIN, false, false, 0,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, "宋体");


        CFont* pOldFont = pDC->SelectObject(&font);
        pDC->SetTextColor(CLR_BLACK);
        pDC->SetBkMode(TRANSPARENT);

        CSize size = pDC->GetTextExtent(strStartName);
        pDC->TextOut(pt.x-size.cx/2,pt.y-10,strStartName);



        pDC->SelectObject(pOldFont);
    }

};
typedef TRawRoadTfcInf* PTRawRoadTfcInf;




//** -------------------------  Link属性定义  --------------------------------------

class TLinkAttri
{

public:

    CString         m_strLinkID;        // LinkID    
    DWORD           m_dwRoadID;         // 对应的交通检测路段ID
    TMPoint         m_StartPos;         // Link的起始点坐标（1/24S）
    TMPoint         m_EndPos;           // Link的终止点坐标（1/24S）
    CString         m_strLinkName;      // LinkName   
    int             m_iSpeed;           // 速度。单位：KM/H
    int             m_iJamLevel;        // 拥堵级别
    int             m_iJamReason;       // 拥堵原因
    COleDateTime    m_pubTime;          // 采集时间


    // 
    TMRect          m_rectExtent;       // 外接矩形
    CMPointArray    m_arrayPt;          // 形状点数组（1/24S）

public:

    // Constructor
    TLinkAttri()
    {
        m_iJamLevel = ETfc_free;
    }

    // New functions
    TLinkAttri& operator= (const TLinkAttri& other)
    {
        if (this != &other)
        {
            m_strLinkID = other.m_strLinkID;
            m_dwRoadID = other.m_dwRoadID;
            m_StartPos = other.m_StartPos;
            m_EndPos = other.m_EndPos;
            m_strLinkName = other.m_strLinkName;
            m_iSpeed = other.m_iSpeed;
            m_iJamLevel = other.m_iJamLevel;
            m_iJamReason = other.m_iJamReason;
            m_pubTime = other.m_pubTime;

            m_rectExtent = other.m_rectExtent;
            int iCount = (int)other.m_arrayPt.GetCount();
            m_arrayPt.SetSize(iCount);
            for (int i=0; i<iCount; i++)
            {
                m_arrayPt.SetAt(i,other.m_arrayPt[i]);
            }
        }
        return *this;
    }

    void SetSpeed(int iNewSpeed)
    {
        m_iSpeed = iNewSpeed;

        if (m_iSpeed>=40)
        {
            m_iJamLevel = ETfc_free;
        }
        else if (m_iSpeed<40 && m_iSpeed>=20)
        {
            m_iJamLevel = ETfc_slowly;
        }
        else if (m_iSpeed>=0 && m_iSpeed<20)
        {
            m_iJamLevel = ETfc_jam;
        }
        else
        {
            m_iJamLevel = ETfc_NoInf;
        }
    }

    void DrawLink(CDC* pDC,const MCoorTransProvider& aMtp) const
    {
        CPen newPen;
        CBrush brush;
        COLORREF lineClr;
        if (m_iJamLevel==ETfc_free)
        {
            lineClr = CLR_DARKGREEN;
        }
        else if (ETfc_slowly==m_iJamLevel)
        {
            lineClr = CLR_YELLOW;
        }
        else if (ETfc_jam==m_iJamLevel)
        {
            lineClr = CLR_RED;
        }
        else
        {
            lineClr = CLR_DEEPGRAY;
        }
        newPen.CreatePen(PS_SOLID,3,lineClr);
        brush.CreateSolidBrush(CLR_BKG_2);
        //brush.CreateHatchBrush(HS_CROSS,CLR_BKG_1);

        CPen* pOldPen = pDC->SelectObject(&newPen);
        CBrush* pOldBrush = pDC->SelectObject(&brush);


        //
        /*CPoint ptStart,ptEnd;
        aMtp.LpToDp(m_StartPos,ptStart);
        aMtp.LpToDp(m_EndPos,ptEnd);
        pDC->MoveTo(ptStart);
        pDC->LineTo(ptEnd);*/

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


        //
        pDC->SelectObject(pOldPen);
        pDC->SelectObject(pOldBrush);
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

    // 
    void DeleteBySpeed(int iDelSpeed)
    {
        PTLinkAttri pElement;
        POSITION pos = GetHeadPosition();
        POSITION posOld;
        while (pos)
        {
            posOld = pos;
            pElement = GetNext(pos);
            if (iDelSpeed == pElement->m_iSpeed)
            {
                RemoveAt(posOld);
                delete pElement;
                pElement = NULL;
            }
        }
    }
};

typedef CTypedPtrMap<CMapStringToPtr,CString,CLinkList*> CMapRoadToLinks;


//* 交通事件属性定义

class TTfcEventAttri
{

public:

    enum TState
    {
        ENormal,
        EActive,
    };
    int m_iState;

    enum TEventType
    {
        EET_Unkown = 0,
        EET_Accident = 1,   // 1.事故
        EET_Jam = 2,        // 2.拥堵
        EET_Query = 3,      // 3.咨询
        EET_Reflect =4,     // 4.反映
        EET_Other = 5,      // 5.其它
    };

    CString     m_strEventID;   // 事件ID
    COleDateTime m_timeAlarm;   // 报警时间
    int         m_iEventType;   // 事件类型

    int         m_iHandledState;  // 处理状态
    int         m_iValid;         // 是否有效
    CString     m_strPhoneNo;     // 电话
    TMPoint     m_ptPhonePos;     // 电话定位，精确到1/24秒
    TMPoint     m_ptAddrPos;      // 案发地点位置，精确到1/24秒
    CString     m_strCaseAddr;    // 案发地点
    CString     m_strContent;     // 报警内容

public:

    TTfcEventAttri()
    {
        m_iState = ENormal;
        m_iEventType = EET_Unkown;
    }
    ~TTfcEventAttri()
    {

    }

    // 
    void  SetActive(BOOL bEable = TRUE)
    {
        if (bEable)
        {
            m_iState = EActive;
        }
        else
        {
            m_iState = ENormal;
        }
    }

    BOOL  IsActive() const
    {
        return m_iState==EActive;
    }

    //
    CRect GetDeviceRect(MCoorTransProvider& aCtp) const
    {
        CRect rect;
        CPoint ptPos;
        aCtp.LpToDp(m_ptPhonePos,ptPos);
        if ( IsActive() )
        {
            rect = CRect(ptPos,CSize(8,8));
        }
        else
        {
            rect = CRect(ptPos,CSize(6,6));
        }
        return rect;
    }

    //
    void  DrawSelf(CDC* pDC,MCoorTransProvider& aCtp)
    {
        // Draw Event
        CPoint ptPos;
        if (m_ptPhonePos.iX!=0)
        {
            aCtp.LpToDp(m_ptPhonePos,ptPos);
            pDC->Ellipse(GetDeviceRect(aCtp));
        }
    }


};
typedef TTfcEventAttri* PTTfcEventAttri;
typedef CTypedPtrList<CPtrList,PTTfcEventAttri>  CTfcEventList;




//////////////////////////////////////////////////////////////////////////
#endif