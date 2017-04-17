/*
* ============================================================================
*  Description: �ڲ���Ϣ�ṹ����
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
    EDB_CONNECTION_STATE = ESYS_RESERVED+0x100,      // ���ݿ�����״̬���
    EWEBS_NEW_WEATHERINF,		                      // �յ��µ�������Ϣ


    EMSG_RETRIVE_CITYS,                 // ��ȡȫ����������(���ƣ�ID��)��Ϣ
    EMSG_CREATE_RGNVIEW,                // ����Region��ͼ
    EMSG_RETRIVE_DISTWTHINF,            // ��ȡС��������Ϣ
    EMSG_RETRIVE_CITYWTHINF,            // ��ȡ������������Ϣ

};

//////////////////////////////////////////////////////////////////////////
// Inherited message Interface

/************************************************************************/
/* Message = EWEBS_NEW_WEATHERINF                                       */
/************************************************************************/
/*  ȫ������Ҫ����������Ϣ���ݸ�ʽ                                      */
class IMsgCityWthInf : public TImcMsg
{
public:
    CString         strCityCode;    // ���д���
    COleDateTime    publishTime;	// ��������
    CString         strCityName;    // ��������
    CString         strProvince;    // ��������ʡ��
    float           fTodMinTemper;  // ������������
    float           fTodMaxTemper;  // ������������
    CString         strTodWthDes;   // ����������ſ�
    CString         strTodWindDir;  // ����ķ���
    int             iTodMinWindPow; // �������С����
    int             iTodMaxWindPow; // �����������
    int             iTodHumidity;   // ����Ŀ���ʪ��
    CString         strCurWthDes;   // ʵ����������
    CString         strLifeIndex;   // ����ָ��

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
// ������Ϣ���ݸ�ʽ 
typedef struct _weather_information
{
    // ʱ��ָʾ��
    enum TPeriodCode
    {        
        EPer_TodayDaytime = '1',      // �������
        EPer_Tonight = '2',           // ����ҹ��
        EPer_TomorrowDayTime = '3',   // �������
        EPer_Tom_evening = 'd',       // ����ҹ��
        EPer_Fr6To9 = '4',	          // δ��6-9��
        EPer_Afternoon = '5',	      // ��������
        EPer_Fr9To12 = '6',	          // δ��9-12��
        EPer_Fr11To14 = '7',	      // δ��11-14��
        EPer_Fr14To17 = '8',	      // δ��14-17��
        EPer_Fr17To20 = '9',	      // δ��17-20��
        EPer_Fr20To23 = 'f',	      // δ��20-23��
    };

    // Members
    COleDateTime  publishTime;	    // ����ʱ��
    TPeriodCode   cPeriodFlag;	    // ʱ��ָʾ��
    CString		  strDistID;	    // ����ID
    CString       strDistName;      // ��������
    CString		  strWeatherDes;    // ����״��
    float		  fTempMax;		    // ����¶�
    float		  fTempMin;		    // ����¶�
    CString		  strWindDirec;	    // ����
    BYTE          byWindPowerMin;   // ��С����ǿ��
    BYTE          byWindPowerMax;   // ������ǿ��
    BYTE	      byHumidity;		// ���ʪ��

    // Constructor
    _weather_information()
    {        
    }

    // Functions
    _weather_information& operator=(const _weather_information& aOther)
    {
        if (this!=&aOther)
        {
            publishTime = aOther.publishTime;	    // ����ʱ��
            cPeriodFlag = aOther.cPeriodFlag;	    // ʱ��ָʾ��
            strDistID = aOther.strDistID;	    // ����ID
            strDistName = aOther.strDistName;      // ��������
            strWeatherDes = aOther.strWeatherDes;    // ����״��
            fTempMax = aOther.fTempMax;		    // ����¶�
            fTempMin = aOther.fTempMin;		    // ����¶�
            strWindDirec = aOther.strWindDirec;	    // ����
            byWindPowerMin = aOther.byWindPowerMin;   // ��С����ǿ��
            byWindPowerMax = aOther.byWindPowerMax;   // ������ǿ��
            byHumidity = aOther.byHumidity;		// ���ʪ��
        }
        return *this;
    }

    void GetWetherDescription(CString& strDes) const
    {
        CString strTemp;

        // 
        switch(cPeriodFlag)
        {
        case EPer_TodayDaytime:  { strDes = _T("�������"); }    break;
        case EPer_Tonight:       { strDes = _T("����ҹ��"); }   break;
        case EPer_TomorrowDayTime: { strDes = _T("�������");  }   break;
        case EPer_Tom_evening: { strDes = _T("����ҹ��"); }    break;
        case EPer_Fr6To9: { strDes = _T("δ��6-9��"); } break;
        case EPer_Afternoon: { strDes = _T("��������"); } break;
        case EPer_Fr9To12: { strDes = _T("δ��9-12��"); } break;
        case EPer_Fr11To14: { strDes = _T("δ��11-14��"); } break;
        case EPer_Fr14To17: { strDes = _T("δ��14-17��"); } break;
        case EPer_Fr17To20: { strDes = _T("δ��17-20��"); } break;
        case EPer_Fr20To23: { strDes = _T("δ��20-23��"); } break;
        default: { strDes = _T("δ֪ʱ��"); }
        }

        // the weather condition
        strDes += _T(",")+strWeatherDes;

        // temperature
        switch(cPeriodFlag)
        {
        case EPer_TodayDaytime: 
        case EPer_TomorrowDayTime:  
        case EPer_Afternoon: 
            { strTemp.Format(_T(",�������:%.0f"),fTempMax); }    
            break;

        case EPer_Tonight:
        case EPer_Tom_evening: 
        case EPer_Fr20To23:
            { strTemp.Format(_T(",�������:%.0f"),fTempMin);}
            break;

        default: 
            { strTemp.Format(_T(",�¶�:%.0f��%.0f"),fTempMin,fTempMax); }
        }
        strDes += strTemp;

        // the wind direction 
        strTemp.Format(_T(",����:%s"),strWindDirec);
        strDes += strTemp;

        // the wind power
        strTemp.Format(_T(",%d��%d��"),byWindPowerMin,byWindPowerMax);
        strDes += strTemp;

        // relative humidity
        strTemp.Format(_T(",ʪ��:%d%%"),byHumidity);
        strDes += strTemp;
    }

}TWeatherInf,*PTWeatherInf;
typedef CList<PTWeatherInf,PTWeatherInf> CWthInfList;






//////////////////////////////////////////////////////////////////////////
// ʡ����Ϣ
struct TCityStruton
{
    CString     m_strCityName;  // ��������
    CString     m_strCityID;    // �ṩ�̵ĳ��б���
    WORD        m_wIndex;       // �ѷ��ĳ��б��루��ӦMapCity.can�ļ��е�������

    enum TCityAttri
    {
        ECA_COUNTRY=0,        // ��
        ECA_CITYDIRECT=1,     // ֱϽ��
        ECA_DISTSPECIAL,      // �ر�������
        ECA_PROVINCE,         // ʡ��
        ECA_CITYNORMAL,       // ��ͨ����
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