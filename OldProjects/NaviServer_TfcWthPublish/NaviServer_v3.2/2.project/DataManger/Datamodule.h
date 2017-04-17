#pragma once

#include <Ado.h>

#include "CityMgr.h"
#include "TfcParsedMgr.h"
#include "DistrictMgr.h"
#include "DistrictRgnMgr.h"
#include "RoadIDMgr.h"

/************************************************************************/
/*
	    用于管理数据库与本地数据
    功能：
        1、检测预报气象数据（来自北京市气象局）并更新到数据库。
        2、气象数据与路况信息的查询处理。
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
        EDBET_DISCONNTED=10,    // 没有连接到数据库
        EDBET_NODATA,           // 没有取得数据
    };

    //
    CRITICAL_SECTION m_CriticalSection;

    // Oracle数据库连接对象
	CAdoConnection	m_OracleDB;

    //--------- [气象查询] ----------

    // 北京市区域管理器
    CBJDistrictMgr m_DistMgr;

    // 全国区域范围管理器（依赖文件mapcity.can）
    CDistrictRgnMgr m_cityRgnMgr;

    // 全国主要城市属性（依赖文件city.txt）
    CCityMgr    m_CityMgr;


    //---------  [交通查询] ----------

    // 交通信息管理器
    CTfcParsedMgr  m_TfcInfMgr;

    // 有交通监测信息的道路ID管理器
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

    //          [北京市气象查询]

    // 根据经纬度得到北京小区的区域编码
    BOOL GetRegionIDByPosition(const TMPoint& ptPos,CString& strAreaID) const;

	// 根据区域ID与时段码得到北京市小区的气象信息
	BOOL GetDistrictWeather(const char& cFlag,const CString& strAreaID,TWeatherInf& weatherInf) const;

public:

    //          [全国气象查询]

    // 根据坐标查询相应的气象信息
    BOOL GetCityWthInfByPos(const TMPoint& poiPos,CString& strCityName,CString& strWthInf) const;

	
public:

    //          [交通信息查询]

	// 根据Link的起止点与名称返回相应的单一Link的所有属性 （解析单一Link请求）
	void GetSpecifiedLinkTfcInf(TLinkAttri& link);

    // 根据道路名称与坐标查询相应路段的路况信息 《通过道路名称请求路况信息》
    void GetRoadTfcInfByRoadName(CRoadTfcInfList& roadTfcList,const CString& strRoadName,TMPoint roadPos);

public:

    // 根据坐标查询城市属性
    PTCityStruton GetCityByPos(DWORD dwLongi,DWORD dwLati) const;

};
