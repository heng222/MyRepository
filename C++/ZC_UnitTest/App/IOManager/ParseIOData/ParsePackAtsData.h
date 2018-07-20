/************************************************************************
*
* 文件名   ：  ParsePackAtsData.h
* 创建时间 ：  2014.04.14
* 作者     ：  ZC组
* 功能描述 ：  解析组包ATS数据管理
* 备  注   ：  无
*
************************************************************************/

#ifndef PARSE_PACK_ATS_DATA_H_
#define PARSE_PACK_ATS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ParsePackIODefine.h"

#ifdef __cplusplus
extern "C" {
#endif
	/*ZC与ATS动态数据结构体*/
	typedef struct ZcAndAtsIODataStruct
	{
		UINT8_S AtsId;                                       /*通信的AtsId*/
		UINT16_S ValueBuffLen;                                /*通信的Buf长度*/
		UINT8_S ValueBuff[ZC_ATS_COM_BYTE_SUM_MAX];           /*通信的Buf值*/
	}ZcAndAtsIODataStruct;

	/*
	* 功能描述：获取输出给ATS数据数组下标对应的数据长度
	* 参数说明： 无
	* 返回值  ： ZC给ATS的数据长度      
	*/
	UINT16_S GetZcToAtsIdDataBufLen(void);

	/*
	* 功能描述： 获取输出给Ats数据数组下标对应的数据信息
	* 参数说明： 无
	* 返回值  ： ZC给ATS的数组的首地址     
	*/
	UINT8_S* GetZcToAtsDataBuff(void);

	/*
	* 功能描述： 组ZC给ATS数据
	* 参数说明： const UINT8* dataBuf,数据数组   
	*            const UINT16_S dataLen,数据长度
	*            const UINT16_S commAtsId,通信的AtsId
	* 返回值  ： 0:组数据失败
	*			 1:组数据成功      
	*/
	UINT8_S PackZcToAtsFrameData(const UINT8_S* dataBuf,const UINT16_S dataLen);/*-bye- 删除了第三个参数*/

	/*
	* 功能描述： 清空本周期Ats输出信息
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearCycleAtsOutputData(void);

#ifdef __cplusplus
}
#endif

#endif

