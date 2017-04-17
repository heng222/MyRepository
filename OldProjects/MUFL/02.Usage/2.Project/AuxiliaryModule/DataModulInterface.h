

#ifndef _DBINTERFACE_EXTENSE_837HFYR
#define _DBINTERFACE_EXTENSE_837HFYR
//////////////////////////////////////////////////////////////////////////

#include "InterfaceEx.h"

//////////////////////////////////////////////////////////////////////////

//** Êý¾Ý¿â¼ì²â
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
#endif