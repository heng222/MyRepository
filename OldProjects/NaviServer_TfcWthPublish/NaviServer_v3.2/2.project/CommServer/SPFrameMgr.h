
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

    // ���ڴ�Ž����������֡
    BYTE	m_byFrame[TSpFrame::EMaxLenFrame];

    // ����֡�Ĵ�С
    WORD    m_wFrameLen;

    // Э�����С
    WORD	m_wBlockSize;

    // �Ƿ��Ѿ����յ�֡ͷ
    BOOL	m_bHasRcvHead;
};
