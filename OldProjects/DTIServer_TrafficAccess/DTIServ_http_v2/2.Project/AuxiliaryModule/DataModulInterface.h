

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



// ���յ�ԭʼ��ͨ��Ϣ������ͨ��˾�ṩ��

class IMsgRawTrafInf : public TImcMsg
{
public:

    TRawRoadTfcInf      m_tfcRawRoadInf;

public:

    //
    IMsgRawTrafInf()
    {
        SetSourceModule(ID_MODULE_HTTP);
        SetDestModule(ID_MODULE_DATABASE);
        m_wMsgType = EMSG_RECV_RAWTFCINF;
    }

    // 
    void Copy(const IMsgRawTrafInf& other)
    {
        if (this!=&other)
        {
            m_tfcRawRoadInf.Copy(other.m_tfcRawRoadInf);
            TImcMsg::Copy(other);
        }
    }
};
typedef IMsgRawTrafInf* PIMsgRawTrafInf;


//////////////////////////////////////////////////////////////////////////


//** ������ͨ��Ϣ��ͼ
class IMsgCreateTfcView : public TImcMsg
{
public:
    CWnd* pRefWnd;

    //
    IMsgCreateTfcView()
    {
        m_wMsgType = EMSG_CREATE_TFCRAWVIEW;
        SetSourceModule(ID_MODULE_USERIF);
        SetDestModule(ID_MODULE_DATABASE);

        pRefWnd = NULL;
    }
};
typedef IMsgCreateTfcView* PIMsgCreateTfcView;





//////////////////////////////////////////////////////////////////////////
#endif