#pragma once


#include "stdafx.h"
#include <NBaseModule.h>
#include <Ado.h>
#include "TfcInfView.h"
#include "TfcParsedView.h"
#include "RoadIDMgr.h"


//////////////////////////////////////////////////////////////////////////


/************************************************************************/
/*
	用于管理数据库与本地数据
*/
/************************************************************************/
class AFX_EXT_CLASS CDataModule : public CNBaseModule
{
public:
	CDataModule(CImcDispatcher& aDispatcher);
	~CDataModule(void);


    enum TDBErrType
    {
        EDBET_SUCCESS = 0,
        EDBET_DISCONNTED=10,    // 没有连接到数据库
        EDBET_NODATA,           // 没有取得数据
    };

private:

    //
    //CRITICAL_SECTION m_CriticalSection;

    // 交通信息所在的数据库
	CAdoConnection	m_OracleDB;


    // 原始交通信息管理器及显示
    CTfcInfMgr  m_TfcInfMgr;
    CTfcInfView m_wndTfcView;

    // 解析后的交通信息管理器及显示
    CTfcParsedMgr   m_TfcParsedMgr;
    CTfcParsedView  m_wndTfcParsed;


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

private:
    BOOL CDataModule::ConnectToDB();


public:

    void GetDBCnntPara(CString& strSource,CString& strUsername,CString& strPwd) const;

    // 更新路况（解析后的数据）信息
    BOOL    UpdateLinkInfo(TLinkAttri& aLink);
    
    // 更新路况（原始数据）信息
    BOOL    UpdateRoadInfo(IMsgRawTrafInf& roadInfo);

    // 更新交通流显示
    void    UpdateTfcViewInf(IMsgRawTrafInf& wsTrafInf);

#if 0
    // 获取所有实时路况信息
    BOOL    RetrieveLinkInfo(CLinkList& aLinkList) const;
#endif

    // 
    //void    UpdateTfcEvents

    //// 
    //void    GetLinkList(CLinkList& listResult,const CPoint& start, const CPoint& dest,
    //            const CString& strLinkName);

};
