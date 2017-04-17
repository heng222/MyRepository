
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
	//���ڴ�Ž����������֡
    BYTE	m_byFrame[TMobileFrame_Char::EMaxLenFrame];
	
	//����֡�Ĵ�С
	WORD    m_wFrameLen;

	//Э�����С
	WORD	m_wBlockSize;

	//�Ƿ��Ѿ����յ�֡ͷ
	BOOL	m_bHasRcvHead;

private:
	void Init(void);

    // �����յ�������֡
    TBaseProtocol* ParsePacket();

    // From CBaseFpProvider
public:

    virtual WORD GetMaxLenFrame() const;
	
    // ��������������
	virtual void ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList);
    
    // �������
    virtual void BuildPacket(TBaseProtocol* pBasePro, LPBYTE lpBuffer,int& iBufLen);

};
