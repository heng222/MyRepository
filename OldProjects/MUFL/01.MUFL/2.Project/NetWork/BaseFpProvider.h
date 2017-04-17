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
        描述：得到协议流的最大长度
    */
    virtual WORD GetMaxLenFrame() const = 0;
    

    /**
        描述：解析给定的数据
        参数：
        [in] pByData: 需要解析的数据
        [in] wDatalen: 数据的长度
        [in] pInterface: 接口观察器
    */
    virtual void ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList) = 0;



    /**
        描述：打包数据
        参数：
        [in] pProStructure: 需要打包的协议结构体
        [in] lpBuffer: 
        [in/out] iBufLen: 数据的长度
    */
    virtual void BuildPacket(TBaseProtocol* pProStructure,LPBYTE lpBuffer,int& iBufLen) = 0;

};


