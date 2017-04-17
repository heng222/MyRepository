#pragma once

#include <Ado.h>

#include "CityMgr.h"
#include "TfcParsedMgr.h"
#include "DistrictMgr.h"
#include "DistrictRgnMgr.h"
#include "RoadIDMgr.h"

/************************************************************************/
/*
	    ���ڹ������ݿ��뱾������
    ���ܣ�
        1�����Ԥ���������ݣ����Ա���������֣������µ����ݿ⡣
        2������������·����Ϣ�Ĳ�ѯ����
*/
/************************************************************************/
class AFX_EXT_CLASS CDataModule : public CNBaseModule,public MAdoConnectionObserver
{

public:

	CDataModule(CImcDispatcher& aDispatcher);
	~CDataModule(void);

private:

    enum { EMID=ID_MODULE_DATABASE};

    enum TDBErrType
    {
        EDBET_SUCCESS = 0,
        EDBET_DISCONNTED=10,    // û�����ӵ����ݿ�
        EDBET_NODATA,           // û��ȡ������
    };

    //
    CRITICAL_SECTION m_CriticalSection;

    // Oracle���ݿ����Ӷ���
	CAdoConnection	m_OracleDB;

    //--------- [�����ѯ] ----------

    // ���������������
    CBJDistrictMgr m_DistMgr;

    // ȫ������Χ�������������ļ�mapcity.can��
    CDistrictRgnMgr m_cityRgnMgr;

    // ȫ����Ҫ�������ԣ������ļ�city.txt��
    CCityMgr    m_CityMgr;


    //---------  [��ͨ��ѯ] ----------

    // ��ͨ��Ϣ������
    CTfcParsedMgr  m_TfcInfMgr;

    // �н�ͨ�����Ϣ�ĵ�·ID������
    CRoadIDMgr    m_roadIDMgr;



    // From CNBaseModule
private:
    virtual BOOL OnInitModule();
    virtual BOOL OnStart();
    virtual BOOL OnActive();
    virtual void OnRecvIMCMessage(PTImcMsg aImcMsg);
    virtual BOOL OnRecvInterMessage(PTImcMsg aImcMsg);
    virtual void OnClose();

    // From MAdoConnectionObserver
private:
    virtual void OnExecuteFailure();

    // New private functions
private:
    void GetDBCnntPara(CString& strSource,CString& strUsername,CString& strPwd) const;
    BOOL ConnectToDB();

public:
	
    BOOL IsDBConnected() const;

public:

    //          [�����������ѯ]

    // ���ݾ�γ�ȵõ�����С�����������
    BOOL GetRegionIDByPosition(const TMPoint& ptPos,CString& strAreaID) const;

	// ��������ID��ʱ����õ�������С����������Ϣ
	BOOL GetDistrictWeather(const char& cFlag,const CString& strAreaID,TWeatherInf& weatherInf) const;

public:

    //          [ȫ�������ѯ]

    // ���������ѯ��Ӧ��������Ϣ
    BOOL GetCityWthInfByPos(const TMPoint& poiPos,CString& strCityName,CString& strWthInf) const;

	
public:

    //          [��ͨ��Ϣ��ѯ]

	// ����Link����ֹ�������Ʒ�����Ӧ�ĵ�һLink���������� ��������һLink����
	void GetSpecifiedLinkTfcInf(TLinkAttri& link);

    // ���ݵ�·�����������ѯ��Ӧ·�ε�·����Ϣ ��ͨ����·��������·����Ϣ��
    void GetRoadTfcInfByRoadName(CRoadTfcInfList& roadTfcList,const CString& strRoadName,TMPoint roadPos);

public:

    // ���������ѯ��������
    PTCityStruton GetCityByPos(DWORD dwLongi,DWORD dwLati) const;

};
