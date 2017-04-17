/*
* ============================================================================
*  Name     : CNaviIntContainer from NaviIntContainer.h
*  Part of  : NaviInt
*  Created  : 19.11.2006 by ZhangHeng
*  Description:
*     Declares container control for application.
*  Version  :
*  Copyright: Copyright (c) 2007, China SpaceSat
* ============================================================================
*/

#ifndef _BUSINESS_FRAME_MGR_
#define _BUSINESS_FRAME_MGR_
//////////////////////////////////////////////////////////////////////////

#include "afx.h"

#include <BaseFpProvider.h>

#include "BusinessProtcl.h"


/************************************************************************/
/*  ���ֻ�ͨ��ʱ��Э�������                                            */
/*  ���ܣ�                                                              */
/*        1�����յ������ݽ��н������õ��涨��ʽ������֡                 */
/*		  2�����ݹ涨��Э�鹹������֡                                   */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
class CBusinessFrameMgr : public CBaseFpProvider
{
public:
    CBusinessFrameMgr(void);
    virtual ~CBusinessFrameMgr(void);

    // From CBaseFpProvider
public:

    virtual WORD GetMaxLenFrame() const;

    // ��������������
    virtual void ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList);


    // �������
    virtual void BuildPacket(TBaseProtocol* pBasePro, LPBYTE lpBuffer,int& iBufLen);

private:

    // �����յ�������֡
    TBaseProtocol* ParsePacket();

	/*! 
		Check DLE
	*/
	void CheckDLE(LPBYTE lpbyFrame,int& iLen);

	/*!
		Encapsulate frame ( XXX->1002XXX1003 )
	*/
	void EncapsFrame(LPBYTE lpbyDest,int& iLen);
	
	/*!
		Divest frame ( 1002XXX1003->XXX )
	*/
	void DivestFrame(LPBYTE& lpbyDest,int& iLen);

    void Init();

private:

    //���ڴ�Ž����������֡(�ѷ�ת��)
    BYTE	m_byFrame[TBusinessFrm::EMaxLenFrame];

	// ��ʶ�Ƿ������һ��DLE
	BOOL	m_bRecvNextDLE;

    // �Ƿ��Ѿ����յ�֡ͷ
    BOOL	m_bHasRcvHead;

    // ֡����Ч����
    int    m_iFrameLen;

};


//////////////////////////////////////////////////////////////////////////
// End of file
#endif