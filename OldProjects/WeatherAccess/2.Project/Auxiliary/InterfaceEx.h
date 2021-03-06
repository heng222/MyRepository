/*
* ============================================================================
*  Description: 内部消息结构定义
* ============================================================================
*/
#ifndef _INTERMOUDULE_COMM_ATTRI__
#define _INTERMOUDULE_COMM_ATTRI__
//////////////////////////////////////////////////////////////////////////

#include <NBaseModule.h>
#include <InterComMsg.h>
#include <AppLogMgr.h>

//////////////////////////////////////////////////////////////////////////
#define     ID_MODULE_WEBSERV   ID_MODULE_RESERVED+0x10
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Type of Inter module message
enum TIMCMsgType
{
    EDB_CONNECTION_STATE = ESYS_RESERVED+0x100,      // 数据库连接状态检测
    EWEBS_NEW_WEATHERINF,		                      // 收到新的气象信息


    EMSG_RETRIVE_CITYS,                 // 获取全国城市属性(名称，ID等)信息
    EMSG_CREATE_RGNVIEW,                // 创建Region视图
    EMSG_RETRIVE_DISTWTHINF,            // 获取小区气象信息
    EMSG_RETRIVE_CITYWTHINF,            // 获取城市气象入信息

};

//////////////////////////////////////////////////////////////////////////
// Inherited message Interface

/************************************************************************/
/* Message = EWEBS_NEW_WEATHERINF                                       */
/************************************************************************/
/*  全国各主要城市天气信息数据格式                                      */
class IMsgCityWthInf : public TImcMsg
{
public:
    CString         strCityCode;    // 城市代码
    COleDateTime    publishTime;	// 更新日期
    CString         strCityName;    // 城市名称
    CString         strProvince;    // 城市所在省份
    float           fTodMinTemper;  // 当天的最低气温
    float           fTodMaxTemper;  // 当天的最高气温
    CString         strTodWthDes;   // 当天的天气概况
    CString         strTodWindDir;  // 当天的风向
    int             iTodMinWindPow; // 当天的最小风力
    int             iTodMaxWindPow; // 当天的最大风力
    int             iTodHumidity;   // 当天的空气湿度
    CString         strCurWthDes;   // 实况天气描述
    CString         strLifeIndex;   // 生活指数

    // Constructor && Destructor
    IMsgCityWthInf()
    {
        // Parent init.
        SetSourceModule(ID_MODULE_WEBSERV);
        SetDestModule(ID_MODULE_DATABASE);
        m_wMsgType = EWEBS_NEW_WEATHERINF;

        // Self init.
        iTodHumidity = 0;
    }
};
typedef IMsgCityWthInf* PIMsgCityWthInf;


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
// 省市信息
struct TCityStruton
{
    CString     m_strCityName;  // 城市名称
    CString     m_strCityID;    // 提供商的城市编码
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
#endif