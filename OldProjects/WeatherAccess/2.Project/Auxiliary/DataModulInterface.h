

#ifndef _DBINTERFACE_EXTENSE_837HFYR
#define _DBINTERFACE_EXTENSE_837HFYR
//////////////////////////////////////////////////////////////////////////

#include <MCoordinateTransfer.h>
#include <UserColors.h>
#include "InterfaceEx.h"

//////////////////////////////////////////////////////////////////////////

//** ���ݿ���
class IMsgDBCntTest : public TImcMsg
{
public:

    //
    enum TType
    {
        E_REQUEST,
        E_RESPONSE,
    };

    // Constructor && Destructor
    IMsgDBCntTest()
    {
        m_wMsgType = EDB_CONNECTION_STATE;
        SetSynchronous(FALSE);
    }    

private:
    TType iType;

public:
    BOOL bResult;   // [OUT]

public:

    PTImcMsg Duplicate() const
    {
        IMsgDBCntTest* pDump = new IMsgDBCntTest;
        pDump->operator =(*this);
        pDump->iType = iType;
        pDump->bResult = bResult;
        return pDump;
    }

    void SetType(TType aType)
    {
        iType = aType;
        if (aType==E_REQUEST)
        {
            SetSourceModule(ID_MODULE_USERIF);
            SetDestModule(ID_MODULE_DATABASE);
        }
        else
        {
            SetSourceModule(ID_MODULE_DATABASE);
            SetDestModule(ID_MODULE_USERIF);
        }
    }

};
typedef IMsgDBCntTest*      PIMsgDBCntTest;


//////////////////////////////////////////////////////////////////////////
//** ��ȡָ��������������������Ϣ
class IMsgRetriveWthInf : public TImcMsg
{
public:

    CString strDistrictID;
    CWthInfList& m_wthInf;
    BOOL bSuccess;

    // 
    IMsgRetriveWthInf(const CString& strID,CWthInfList& aList):m_wthInf(aList)
    {
        strDistrictID = strID;
        m_wMsgType = EMSG_RETRIVE_DISTWTHINF;
        SetDestModule(ID_MODULE_DATABASE);
        bSuccess = FALSE;
    }
};
typedef IMsgRetriveWthInf* PIMsgRetriveWthInf;


//////////////////////////////////////////////////////////////////////////

// * ��ȡ����������Ϣ
class IMsgRetriveCityWthInf : public TImcMsg
{
public:

    CString strCityName;
    CString strWthInf;

    IMsgRetriveCityWthInf()
    {
        m_wMsgType = EMSG_RETRIVE_CITYWTHINF;
        SetDestModule(ID_MODULE_DATABASE);
    }
};

typedef IMsgRetriveCityWthInf* PIMsgRetriveCityWthInf;

//////////////////////////////////////////////////////////////////////////
//** ��ȡȫ��������Ϣ
class IMsgRetrieveCityInf : public TImcMsg
{
public:

    CCityList*  m_cityInf;

    IMsgRetrieveCityInf()
    {
        m_wMsgType = EMSG_RETRIVE_CITYS;
        SetDestModule(ID_MODULE_DATABASE);
        //
        m_cityInf = NULL;
    }
};
typedef IMsgRetrieveCityInf* PIMsgRetrieveCityInf;



//////////////////////////////////////////////////////////////////////////
#endif