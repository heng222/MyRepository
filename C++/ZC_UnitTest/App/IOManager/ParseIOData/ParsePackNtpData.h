/************************************************************************
*
* 文件名   ：  ParsePackNtpData.h
* 创建时间 ：  2014.04.14
* 作者     ：  ZC组
* 功能描述 ：  解析组包Ntp数据管理
* 备  注	：  无
*
************************************************************************/

#ifndef PARSE_PACK_NTP_DATA_H_
#define PARSE_PACK_NTP_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ParsePackIODefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*ZC与Ntp动态数据结构体*/
	typedef struct ZcAndNtpIODataStruct
	{
		UINT8_S NtpId;                                       /*通信的NtpId*/
		UINT16_S ValueBuffLen;                                /*通信的Buf长度*/
		UINT8_S ValueBuff[ZC_NTP_COM_BYTE_SUM_MAX];           /*通信的Buf值*/
	}ZcAndNtpIODataStruct;

	/*
	* 功能描述： 获取Ntp输入给ZC的数据长度
	* 参数说明： 无
	* 返回值  ： 0: 获取失败
	*			 >0: 数据长度      
	*/
	UINT16_S GetNtpToZcDataLen(void);

	/*
	* 功能描述： 获取Ntp输入给ZC的数据信息
	* 参数说明： 无
	* 返回值  ：  NULL: 获取失败
	*			 !NULL: 获取成功       
	*/
	UINT8_S* GetNtpToZcDataBuff(void);

	/*
	* 功能描述： 获取ZC输出给Ntp的数据长度
	* 参数说明： 无
	* 返回值  ： 0: 数据解析失败
	*			 >0: 数据长度      
	*/
	UINT16_S GetZcToNtpDataLen(void);

	/*
	* 功能描述： 获取ZC输出给Ntp的数据信息
	* 参数说明： 无
	* 返回值  ： NULL: 获取失败
	*			 !NULL: 获取成功       
	*/
	UINT8_S* GetZcToNtpDataBuff(void);

	/*
	* 功能描述： 解析Ntp输入的单帧数据
	* 参数说明： const UINT8_S dataBuff[], 数据缓冲区
	*            const UINT16_S dataLength, 数据长度
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseNtpToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength);

    /*
    * 功能描述： 组Ntp帧数据
    * 参数说明： UINT8* dataBuff,数据数组   
    *            const UINT16_S dataLen,数据长度
    *            const UINT16_S commNtpId,通信的NtpId(预留)
    * 返回值  ： 0:组数据失败
    *			 1:组数据成功      
    */
	UINT8_S PackZcToNtpFrameData(const UINT8_S* dataBuff,const UINT16_S dataLen,const UINT16_S commNtpId);

	/*
	* 功能描述： 清空本周期所有输入的Ntp输入信息
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearCycleNtpInputData(void);

	/*
	* 功能描述： 清空本周期所有输出给Ntp输入信息
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearCycleNtpOutputData(void);

#ifdef __cplusplus
}
#endif
#endif
