/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : Server.dll
*  Created  : 19.11.2006 by H.W.
*  Description:
*     
*  Version  : 1.0.0.2.3
*  Copyright: Copyright (c) 2007, H.W. Corpor.
* ============================================================================
*/

#ifndef _BASE_PROTOCOL_8UEI3IOAPD321925
#define _BASE_PROTOCOL_8UEI3IOAPD321925
//////////////////////////////////////////////////////////////////////////

#include <afxtempl.h>

class AFX_EXT_CLASS TBaseProtocol
{

public:

    // 
    TBaseProtocol();
    virtual ~TBaseProtocol()=0;  // virtual destructor is necessary

    void SetAutoDel(BOOL bFlag);
    void AutoDel();

    
    // 获得协议类型
    virtual int GetProType()=0;


    // 字符串化协议类型
    virtual CString GetProName()=0;

private:

    BOOL    m_bAutoDel;

};
typedef TBaseProtocol* PTBaseProtocol;
typedef CList<PTBaseProtocol,PTBaseProtocol> CBaseProtocolList;



//////////////////////////////////////////////////////////////////////////
#endif