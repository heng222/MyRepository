
#include "NBaseModule.h"

#ifndef _DBINTERFACE_EXTENSE_837HFYR
#define _DBINTERFACE_EXTENSE_837HFYR
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
            { strTemp.Format(_T(",最低气温:%.0f"),fTempMax);}
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



//////////////////////////////////////////////////////////////////////////
// 省市信息
struct TCityStruton
{
    CString     m_strCityName;
    CString     m_strCityID;

    enum TCityAttri
    {
        ECA_COUNTRY,        // 
        ECA_CITYDIRECT,     // 直辖市
        ECA_DISTSPECIAL,    // 特别行政区
        ECA_PROVINCE,       // 省份
        ECA_CITYNORMAL,     // 普通城市
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