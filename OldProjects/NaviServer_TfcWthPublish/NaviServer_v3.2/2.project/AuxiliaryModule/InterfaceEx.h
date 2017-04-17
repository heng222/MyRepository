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
#include <InterComMsg.h>
#include <NBaseModule.h>
#include <CommonFunc.h>
#include <Geometry.h>
#include <UserColors.h>
#include <MCoordinateTransfer.h>


//////////////////////////////////////////////////////////////////////////

#define     ID_MODULE_WEBSERV   ID_MODULE_RESERVED+0x10     // WebService module
#define     ID_MODULE_HTTP      ID_MODULE_RESERVED+0x12     // Http Module

//////////////////////////////////////////////////////////////////////////
// Type of Inter module message
enum TIMCMsgType
{
    EDB_CONNECTION_STATE = ESYS_RESERVED+0x100,      // 数据库连接状态检测

    ESCK_RECV_FRAME,                    // 从SOCKET收到某种协议帧
    ESCK_SEND_FRAME,                    // 通过SOCKET发送协议帧
    ESCK_SCK_STATE,                     // 得到SCK模块的状态
    ESCK_CLEAN_UP,                      // 清理网络
    ESCK_RETRIEVE_COMLOGS,              // 得到指定通信域的日志

    EMSG_START_SERVICE,                 // 启动交通气象信息发布服务(wParam=BOOL bResult)
    EMSG_STOP_SERVICE,                  // 停止服务

    EMSG_CNNT_BALANCESERVER,            // 连接到负载分配器
    EMSG_TEST_BALANCESERVER,            // 查询与负载分配器的连接状态(wParam=0/1)


    EMSG_SHOW_TIPWND,                   // 显示信息窗口
    EMSG_CLOSE_TIPWND,                  // 关闭信息窗口
};

//////////////////////////////////////////////////////////////////////////
// Inherited message Interface

// 路况畅通级别
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
            dwRoadID = other.dwRoadID;
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

    int GetJamLevel() const
    {
        if (fSpeed>=40)
        {
            return  ETfc_free;
        }
        else if (fSpeed<40 && fSpeed>=20)
        {
            return ETfc_slowly;
        }
        else if (fSpeed>=0 && fSpeed<20)
        {
            return ETfc_jam;
        }
        else
        {
            return ETfc_NoInf;
        }
    }

};
typedef TRawRoadTfcInf* PTRawRoadTfcInf;
typedef CList<PTRawRoadTfcInf,PTRawRoadTfcInf> CRoadTfcInfList;


//** Link属性定义

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

    // 形状点个数
    int GetNumofPt() const
    {
        return (int)m_arrayPt.GetCount();
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
    DOUBLE MaxDistance( const TSegmentVector& mVector) const
    {
        DOUBLE fMaxDis = 0;
        int iCount = (int)m_arrayPt.GetCount();

        for (int i=0; i<iCount; i++)
        {
            TMPoint pt = m_arrayPt.GetAt(i);
            DOUBLE fDistance = mVector.Distance(pt);
            if (fDistance>fMaxDis || i==0)
            {
                fMaxDis = fDistance; 
            }
        }

        return fMaxDis;
    }

    // Link到某线段的最短距离
    DOUBLE MinDistance( const TSegmentVector& mVector ) const
    {
        DOUBLE fMinDis = 0;
        int iCount = (int)m_arrayPt.GetCount();

        for (int i=0; i<iCount; i++)
        {
            TMPoint pt = m_arrayPt.GetAt(i);
            DOUBLE fDistance = mVector.Distance(pt);
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


//////////////////////////////////////////////////////////////////////////
// 省市信息
struct TCityStruton
{
    CString     m_strCityName;  // 城市名称
    CString     m_strCityID;    // 气象服务提供商的城市编码
    WORD        m_wIndex;       // 已方的城市编码（对应MapCity.can文件中的索引）

    enum TCityAttri
    {
        ECA_COUNTRY=0,        // 国
        ECA_CITYDIRECT=1,     // 直辖市
        ECA_DISTSPECIAL,      // 特别行政区
        ECA_PROVINCE,         // 省份
        ECA_CITYNORMAL,       // 普通城市
    }m_iCityAttri;

    CList<TCityStruton*,TCityStruton*>    m_subItemList;

    // Constructor and destructor
    TCityStruton()
    {

    }
    ~TCityStruton()
    {
        ClearList();
    }

    void ClearList()
    {
        while (m_subItemList.GetHeadPosition())
        {
            delete m_subItemList.RemoveHead();
        }
    }
};
typedef TCityStruton* PTCityStruton;
typedef CList<PTCityStruton,PTCityStruton> CCityList;



//////////////////////////////////////////////////////////////////////////

/************************************************************************/
// 天气信息数据格式 
typedef struct _weather_information
{
    // 时段指示码
    enum TPeriodCode
    {        
        EPer_TodayDaytime = '1',      // 今天白天
        EPer_Tonight = '2',           // 今天夜间
        EPer_TomorrowDayTime = '3',   // 明天白天
        EPer_Tom_evening = 'd',       // 明天夜间
        EPer_Fr6To9 = '4',	          // 未来6-9点
        EPer_Afternoon = '5',	      // 今天下午
        EPer_Fr9To12 = '6',	          // 未来9-12点
        EPer_Fr11To14 = '7',	      // 未来11-14点
        EPer_Fr14To17 = '8',	      // 未来14-17点
        EPer_Fr17To20 = '9',	      // 未来17-20点
        EPer_Fr20To23 = 'f',	      // 未来20-23点
    };

    // Members
    COleDateTime  publishTime;	    // 发布时间
    TPeriodCode   cPeriodFlag;	    // 时段指示码
    CString		  strDistID;	    // 区域ID
    CString       strDistName;      // 区域名称
    CString		  strWeatherDes;    // 天气状况
    float		  fTempMax;		    // 最高温度
    float		  fTempMin;		    // 最低温度
    CString		  strWindDirec;	    // 风向
    BYTE          byWindPowerMin;   // 最小风力强度
    BYTE          byWindPowerMax;   // 最大风力强度
    BYTE	      byHumidity;		// 相对湿度

    // Constructor
    _weather_information()
    {        
    }

    // Functions
    _weather_information& operator=(const _weather_information& aOther)
    {
        if (this!=&aOther)
        {
            publishTime = aOther.publishTime;	    // 发布时间
            cPeriodFlag = aOther.cPeriodFlag;	    // 时段指示码
            strDistID = aOther.strDistID;	    // 区域ID
            strDistName = aOther.strDistName;      // 区域名称
            strWeatherDes = aOther.strWeatherDes;    // 天气状况
            fTempMax = aOther.fTempMax;		    // 最高温度
            fTempMin = aOther.fTempMin;		    // 最低温度
            strWindDirec = aOther.strWindDirec;	    // 风向
            byWindPowerMin = aOther.byWindPowerMin;   // 最小风力强度
            byWindPowerMax = aOther.byWindPowerMax;   // 最大风力强度
            byHumidity = aOther.byHumidity;		// 相对湿度
        }
        return *this;
    }

    void GetWetherDescription(CString& strDes) const
    {
        CString strTemp;

        // 
        switch(cPeriodFlag)
        {
        case EPer_TodayDaytime:  { strDes = _T("今天白天"); }    break;
        case EPer_Tonight:       { strDes = _T("今天夜间"); }   break;
        case EPer_TomorrowDayTime: { strDes = _T("明天白天");  }   break;
        case EPer_Tom_evening: { strDes = _T("明天夜间"); }    break;
        case EPer_Fr6To9: { strDes = _T("未来6-9点"); } break;
        case EPer_Afternoon: { strDes = _T("今天下午"); } break;
        case EPer_Fr9To12: { strDes = _T("未来9-12点"); } break;
        case EPer_Fr11To14: { strDes = _T("未来11-14点"); } break;
        case EPer_Fr14To17: { strDes = _T("未来14-17点"); } break;
        case EPer_Fr17To20: { strDes = _T("未来17-20点"); } break;
        case EPer_Fr20To23: { strDes = _T("未来20-23点"); } break;
        default: { strDes = _T("未知时段"); }
        }

        // the weather condition
        strDes += _T(",")+strWeatherDes;

        // temperature
        switch(cPeriodFlag)
        {
        case EPer_TodayDaytime: 
        case EPer_TomorrowDayTime:  
        case EPer_Afternoon: 
            { strTemp.Format(_T(",最高气温:%.0f"),fTempMax); }    
            break;

        case EPer_Tonight:
        case EPer_Tom_evening: 
        case EPer_Fr20To23:
            { strTemp.Format(_T(",最低气温:%.0f"),fTempMin);}
            break;

        default: 
            { strTemp.Format(_T(",温度:%.0f～%.0f"),fTempMin,fTempMax); }
        }
        strDes += strTemp;

        // the wind direction 
        strTemp.Format(_T(",风向:%s"),strWindDirec);
        strDes += strTemp;

        // the wind power
        strTemp.Format(_T(",%d～%d级"),byWindPowerMin,byWindPowerMax);
        strDes += strTemp;

        // relative humidity
        strTemp.Format(_T(",湿度:%d%%"),byHumidity);
        strDes += strTemp;
    }

}TWeatherInf,*PTWeatherInf;
typedef CList<PTWeatherInf,PTWeatherInf> CWthInfList;







//////////////////////////////////////////////////////////////////////////
#endif