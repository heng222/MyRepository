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

#ifndef NAVIINTCFRAMEMGR_H
#define NAVIINTCFRAMEMGR_H
//////////////////////////////////////////////////////////////////////////

#include "afx.h"

#include <BaseFpProvider.h>
#include "MobilesProtocol_bin.h"


/************************************************************************/
/*  与手机通信时的协议解析器                                            */
/*  功能：                                                              */
/*        1、对收到的数据进行解析，得到规定格式的数据帧                 */
/*		  2、根据规定的协议构建数据帧                                   */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
class CMobileFrameMgrBin : public CBaseFpProvider
{
public:
    CMobileFrameMgrBin(void);
    virtual ~CMobileFrameMgrBin(void);

    // From CBaseFpProvider
public:

    virtual WORD GetMaxLenFrame() const;

    // 解析给定的数据
    virtual void ParseRawData(LPBYTE pByData, WORD wDataLen,CBaseProtocolList& aFrameList);


    // 打包数据
    virtual void BuildPacket(TBaseProtocol* pBasePro, LPBYTE lpBuffer,int& iBufLen);

private:

    // 解析收到的数据帧
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

    //用于存放解析后的数据帧(已反转义)
    BYTE	m_byFrame[TMobileFrameBin::EMaxLenFrame];

	// 标识是否接收下一个DLE
	BOOL	m_bRecvNextDLE;

    // 是否已经接收到帧头
    BOOL	m_bHasRcvHead;

    // 帧的有效长度
    int    m_iFrameLen;

};


//////////////////////////////////////////////////////////////////////////
// End of file
#endif