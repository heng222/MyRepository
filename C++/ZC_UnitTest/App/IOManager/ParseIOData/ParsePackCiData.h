/************************************************************************
*
* 文件名   ：  ParsePackCiData.h
* 创建时间 ：  2015.08.14
* 作者     ：  ZC组
* 功能描述 ：  解析和打包联锁数据
* 备  注	：  无
*
************************************************************************/

#ifndef PARSE_PACK_CI_DATA_H_
#define PARSE_PACK_CI_DATA_H_

#include "../../LineDataManager/Mask/MaskDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*ZC与CI动态数据结构体*/
	typedef struct ZcAndCiIODataStruct
	{
		UINT8_S CiId;                                        /*通信的CiId*/
		UINT16_S MaskValueBuffLen;                            /*码位值Buf长度*/
		UINT8_S MaskValueBuff[ZC_TO_CI_MASK_SUM_MAX];         /*码位的最大值*/
	}ZcAndCiIODataStruct;

	/*
	* 功能描述： 解析CI输入的单帧数据
	* 参数说明： const UINT8 dataBuff[], 数据缓冲区
	*            const UINT16_S dataLength, 数据长度	
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseCiToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength);

    /*
    * 功能描述： 校验CI输入的数据正确性
    * 参数说明： const UINT8_S dataBuff[],数据数组   
    *            const UINT16_S dataLen,数据长度
    * 返回值  ： 0:合法性校验失败
    *			 1:合法性校验成功      
    */
    UINT8_S CiInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen);

	/*
	* 功能描述： 获取Ci输入Zc的最大数量
	* 参数说明： void
	* 返回值  ： 0: 失败
	*			 >0: 数量         
	*/
	UINT8_S GetCiToZcCurSum(void);

    /*
    * 功能描述：获取Ci输入Zc的Id对应CIid
    * 参数说明： const UINT8 ciIdOfIndex
    * 返回值  ： COMM_CI_SUM_MAX: 失败
    *			 >=0U: 成功      
    */
	UINT16_S GetCiToZcBuffIndexOfCiId(const UINT8_S ciIdOfIndex);

	/*
	* 功能描述：获取Ci输入Zc的Id对应数据长度
	* 参数说明： const UINT8 ciIdOfIndex
	* 返回值  ： 0: 失败
	*			 >0: 成功      
	*/
	UINT16_S GetCiToZcIdDataBuffLen(const UINT8_S ciIdOfIndex);

	/*
	* 功能描述： 获取Ci输入Zc的Id对应下标
	* 参数说明： const UINT8 ciIdOfIndex
	* 返回值  ：  NULL: 失败
	*			 非NULL: 成功     
	*/
	UINT8_S* GetCiToZcDataBuffByIndex(const UINT8_S ciIdOfIndex);

	/*
	* 功能描述： 组包输出给Ci的单帧数据
	* 参数说明：  const UINT8_S dataBuff[], 数据缓冲区
	*             UINT16_S dataLength, 数据长度
	*             UINT16_S destId, 目标CI设备ID
	* 返回值  ： 0: 数据打包失败
	*			 1: 数据打包成功      
	*/
	UINT8_S PackZcToCiFrameData(const UINT8_S dataBuff[], UINT16_S dataLength,UINT16_S destId);

	/*
	* 功能描述： 获取ZC输出CI的最大数量
	* 参数说明： void
	* 返回值  ： 0: 失败
	*			 >0: 成功      
	*/
	UINT8_S GetToCiCurSum(void);

	/*
	* 功能描述： 获取ZC输出CI的Id对应数据长度
	* 参数说明： const UINT8 ciIdOfIndex
	* 返回值  ： 0: 失败
	*			 >0: 成功      
	*/
	UINT16_S GetToCiIdDataBuffLen(const UINT8_S ciIdOfIndex);

	/*
	* 功能描述： 获取ZC输出CI的Id下标对应缓存区
	* 参数说明： const UINT8 ciIdOfIndex
	* 返回值  ：  NULL: 失败
	*			 非NULL: 成功     
	*/
	UINT8_S* GetToCiDataBuffByIndex(const UINT8_S ciIdOfIndex);

	/*
	* 功能描述： 清空本周期所有输入的CI输入信息
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearCycleCiInputData(void);

	/*
	* 功能描述： 清空本周期所有输出给CI输入信息
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearCycleCiOutputData(void);

#ifdef __cplusplus
}
#endif

#endif
