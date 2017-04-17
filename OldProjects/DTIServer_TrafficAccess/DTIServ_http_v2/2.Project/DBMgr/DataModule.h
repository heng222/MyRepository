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
	���ڹ������ݿ��뱾������
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
        EDBET_DISCONNTED=10,    // û�����ӵ����ݿ�
        EDBET_NODATA,           // û��ȡ������
    };

private:

    //
    //CRITICAL_SECTION m_CriticalSection;

    // ��ͨ��Ϣ���ڵ����ݿ�
	CAdoConnection	m_OracleDB;


    // ԭʼ��ͨ��Ϣ����������ʾ
    CTfcInfMgr  m_TfcInfMgr;
    CTfcInfView m_wndTfcView;

    // ������Ľ�ͨ��Ϣ����������ʾ
    CTfcParsedMgr   m_TfcParsedMgr;
    CTfcParsedView  m_wndTfcParsed;


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

private:
    BOOL CDataModule::ConnectToDB();


public:

    void GetDBCnntPara(CString& strSource,CString& strUsername,CString& strPwd) const;

    // ����·��������������ݣ���Ϣ
    BOOL    UpdateLinkInfo(TLinkAttri& aLink);
    
    // ����·����ԭʼ���ݣ���Ϣ
    BOOL    UpdateRoadInfo(IMsgRawTrafInf& roadInfo);

    // ���½�ͨ����ʾ
    void    UpdateTfcViewInf(IMsgRawTrafInf& wsTrafInf);

#if 0
    // ��ȡ����ʵʱ·����Ϣ
    BOOL    RetrieveLinkInfo(CLinkList& aLinkList) const;
#endif

    // 
    //void    UpdateTfcEvents

    //// 
    //void    GetLinkList(CLinkList& listResult,const CPoint& start, const CPoint& dest,
    //            const CString& strLinkName);

};
