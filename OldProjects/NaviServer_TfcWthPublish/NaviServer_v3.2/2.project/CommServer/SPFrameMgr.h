
/*
* ============================================================================
*  Name     : protocol definition
*  Part of  : NaviInt
*  Created  : 19.11.2006 by ZhangHeng
*  Description:
*     
*  Version  :
*  Copyright: Copyright (c) 2007, China SpaceSat. Corp. Ltd.
* ============================================================================
*/

#pragma once

#include <BaseFpProvider.h>
#include "SPPrototocol.h"

//////////////////////////////////////////////////////////////////////////
class CSPFrameMgr :  public CBaseFpProvider
{
public:
    CSPFrameMgr(void);
    ~CSPFrameMgr(void);

// FROM MFrameParserProvider
public:

    virtual WORD GetMaxLenFrame() const;
    
    virtual void ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList);

    virtual void BuildPacket(TBaseProtocol* pProStructure,LPBYTE lpBuffer,int& iBufLen);

private:
    TBaseProtocol* ParsePacket();

    // 用于存放解析后的数据帧
    BYTE	m_byFrame[TSpFrame::EMaxLenFrame];

    // 数据帧的大小
    WORD    m_wFrameLen;

    // 协议体大小
    WORD	m_wBlockSize;

    // 是否已经接收到帧头
    BOOL	m_bHasRcvHead;
};
