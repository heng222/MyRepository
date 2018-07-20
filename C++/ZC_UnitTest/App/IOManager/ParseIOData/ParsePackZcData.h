/************************************************************************
*
* 文件名   ：  ParsePackZcData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  解析和组包相邻ZC数据管理
* 备  注	：  无
*
************************************************************************/

#ifndef PARSE_PACK_ZC_DATA_H_
#define PARSE_PACK_ZC_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ParsePackIODefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*ZC与相邻ZC动态数据结构体*/
	typedef struct ZcAndNzcIODataStruct
	{
		UINT8_S ZcId;                                        /*通信的Id*/
		UINT16_S ValueBuffLen;                                /*通信的Buf长度*/
		UINT8_S ValueBuff[ZC_NZC_COM_BYTE_SUM_MAX];           /*通信的Buf值*/
	}ZcAndNzcIODataStruct;

	/*
	* 功能描述： 获取相邻ZC输入Zc的最大数量
	* 参数说明： void
	* 返回值  ：  SINGLE_TYPE_COMM_TARGET_SUM_MAX: 失败
	*			>0: 数量            
	*/
	UINT8_S GetNZcToZcCurSum(void);

	/*
	* 功能描述：获取相邻ZC输入的数据数组下标对应的ZCID
	* 参数说明： const UINT8 nZcIdOfIndex
	* 返回值  ： 0: 失败
	*			 >0: 成功      
	*/
	UINT16_S GetNZcToZcBuffIndexOfNZcId(const UINT8_S nZcIdOfIndex);

	/*
	* 功能描述：获取相邻ZC输入的数据数组下标对应的数据长度
	* 参数说明： const UINT8 nZcIdOfIndex
	* 返回值  ： 0: 失败
	*			 >0: 成功      
	*/
	UINT16_S GetNZcToZcIdDataBufLen(const UINT8_S nZcIdOfIndex);

	/*
	* 功能描述： 获取NZc输入Zc的Id对应数据信息
	* 参数说明： const UINT8 nZcIdOfIndex
	* 返回值  ： NULL: 失败
	*			 !NULL: 成功      
	*/
	UINT8_S* GetNZcToZcBufDataOfIndex(const UINT8_S nZcIdOfIndex);

	/*
	* 功能描述： 解析NZC输入的单帧数据
	* 参数说明： const UINT8_S dataBuff[], 数据缓冲区
	*            const UINT16_S dataLength, 数据长度
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseNzcToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength);

    /*
    * 功能描述： 相邻ZC输入的单帧数据合法性检查
    * 参数说明： const UINT8_S dataBuff[], 数据缓冲区
    *            const UINT16_S dataLen, 数据长度
    * 返回值  ： 0: 合法性检查失败
    *			 1: 合法性检查成功      
    */
	UINT8_S NzcInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen);

	/*
	* 功能描述： 获取ZC输出给NZc的最大数量
	* 参数说明： void
	* 返回值  ： SINGLE_TYPE_COMM_TARGET_SUM_MAX: 失败
	*			>0: 数量      
	*/
	UINT8_S GetZcToNZcCurSum(void);

	/*
	* 功能描述：获取输出给相邻ZC数据数组下标对应的数据长度
	* 参数说明： const UINT8 nZcIdOfIndex
	* 返回值  ： 0: 失败
	*			 >0: 成功      
	*/
	UINT16_S GetZcToNZcIdDataBufLen(const UINT8_S nZcIdOfIndex);

	/*
	* 功能描述： 获取输出给相邻ZC数据数组下标对应的数据信息
	* 参数说明： const UINT8 nZcIdOfIndex
	* 返回值  ： NULL: 失败
	*			 !NULL: 成功         
	*/
	UINT8_S* GetZcToNZcBufDataOfIndex(const UINT8_S nZcIdOfIndex);

    /*
    * 功能描述： 组相邻ZC数据
    * 参数说明： const UINT8* dataBuf,数据缓存
    *            const UINT16_S dataLength,数据长度
    *            const UINT16_S destId, 目标ID   
    * 返回值  ： RETURN_ERROR:组数据失败
    *			 RETURN_SUCCESS:组数据成功      
    */
	UINT8_S PackZcToNzcFrameData(const UINT8_S* dataBuf,const UINT16_S dataLength,const UINT16_S destId);

	/*
	* 功能描述： 清空本周期所有相邻ZC输入信息
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearCycleNZcInputData(void);

	/*
	* 功能描述： 清空本周期所有相邻ZC输出信息
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearCycleNZcOutputData(void);

#ifdef __cplusplus
}
#endif
#endif
