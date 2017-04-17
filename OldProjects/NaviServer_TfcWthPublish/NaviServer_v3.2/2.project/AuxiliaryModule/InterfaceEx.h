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
    EDB_CONNECTION_STATE = ESYS_RESERVED+0x100,      // ���ݿ�����״̬���

    ESCK_RECV_FRAME,                    // ��SOCKET�յ�ĳ��Э��֡
    ESCK_SEND_FRAME,                    // ͨ��SOCKET����Э��֡
    ESCK_SCK_STATE,                     // �õ�SCKģ���״̬
    ESCK_CLEAN_UP,                      // ��������
    ESCK_RETRIEVE_COMLOGS,              // �õ�ָ��ͨ�������־

    EMSG_START_SERVICE,                 // ������ͨ������Ϣ��������(wParam=BOOL bResult)
    EMSG_STOP_SERVICE,                  // ֹͣ����

    EMSG_CNNT_BALANCESERVER,            // ���ӵ����ط�����
    EMSG_TEST_BALANCESERVER,            // ��ѯ�븺�ط�����������״̬(wParam=0/1)


    EMSG_SHOW_TIPWND,                   // ��ʾ��Ϣ����
    EMSG_CLOSE_TIPWND,                  // �ر���Ϣ����
};

//////////////////////////////////////////////////////////////////////////
// Inherited message Interface

// ·����ͨ����
enum ETrafficLevel
{
    ETfc_NoInf = -1,// ����Ϣ
    ETfc_free = 0,  // ��ͨ
    ETfc_slowly,    // ����
    ETfc_jam,       // ӵ��
};

//** ------------------------------- ԭʼ·����Ϣ -------------------------

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


//** Link���Զ���

class TLinkAttri
{
public:

    CString         m_strLinkID;        // LinkID     
    DWORD           m_dwRoadID;         // ��Ӧ�Ľ�ͨ���·��ID
    TMPoint         m_StartPos;         // Link����ʼ�����꣨1/24S��
    TMPoint         m_EndPos;           // Link����ֹ�����꣨1/24S��
    CString         m_strLinkName;      // LinkName   
    int             m_iSpeed;           // �ٶȡ���λ��KM/H
    int             m_iJamLevel;        // ӵ�¼���
    int             m_iJamReason;       // ӵ��ԭ��
    COleDateTime    m_pubTime;          // �ɼ�ʱ��


    TMRect          m_rectExtent;       // ��Ӿ���
    CMPointArray    m_arrayPt;          // ��״�����飨1/24S��

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

    // ��״�����
    int GetNumofPt() const
    {
        return (int)m_arrayPt.GetCount();
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

    // Link��ĳ�߶ε���̾���
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
// ʡ����Ϣ
struct TCityStruton
{
    CString     m_strCityName;  // ��������
    CString     m_strCityID;    // ��������ṩ�̵ĳ��б���
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
#endif