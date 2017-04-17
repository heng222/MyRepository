
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
#include "afx.h"

#include <BaseFpProvider.h>
#include "MobilesProtocol_char.h"


//////////////////////////////////////////////////////////////////////////
class CMobileFrameMgrChar : public CBaseFpProvider
{
public:
	CMobileFrameMgrChar(void);
	virtual ~CMobileFrameMgrChar(void);

private:
	//用于存放解析后的数据帧
    BYTE	m_byFrame[TMobileFrame_Char::EMaxLenFrame];
	
	//数据帧的大小
	WORD    m_wFrameLen;

	//协议体大小
	WORD	m_wBlockSize;

	//是否已经接收到帧头
	BOOL	m_bHasRcvHead;

private:
	void Init(void);

    // 解析收到的数据帧
    TBaseProtocol* ParsePacket();

    // From CBaseFpProvider
public:

    virtual WORD GetMaxLenFrame() const;
	
    // 解析给定的数据
	virtual void ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList);
    
    // 打包数据
    virtual void BuildPacket(TBaseProtocol* pBasePro, LPBYTE lpBuffer,int& iBufLen);

};
