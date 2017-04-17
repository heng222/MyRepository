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
#pragma once

#include "BaseProtocol.h"

//////////////////////////////////////////////////////////////////////////
// Frame parser provider
class AFX_EXT_CLASS CBaseFpProvider
{
public:

    CBaseFpProvider();
    virtual ~CBaseFpProvider();

// Pure virtual functions
public:

    /**
        �������õ�Э��������󳤶�
    */
    virtual WORD GetMaxLenFrame() const = 0;
    

    /**
        ��������������������
        ������
        [in] pByData: ��Ҫ����������
        [in] wDatalen: ���ݵĳ���
        [in] pInterface: �ӿڹ۲���
    */
    virtual void ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList) = 0;



    /**
        �������������
        ������
        [in] pProStructure: ��Ҫ�����Э��ṹ��
        [in] lpBuffer: 
        [in/out] iBufLen: ���ݵĳ���
    */
    virtual void BuildPacket(TBaseProtocol* pProStructure,LPBYTE lpBuffer,int& iBufLen) = 0;

};


