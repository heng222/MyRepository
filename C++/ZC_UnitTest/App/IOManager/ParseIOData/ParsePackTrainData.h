/************************************************************************
*
* 文件名   ：  ParsePackTrainData.h
* 创建时间 ：  2015.04.14
* 作者     ：  ZC组
* 功能描述 ：  解析组包列车数据管理
* 备  注	：  无
*
************************************************************************/

#ifndef PARSE_PACK_TRAIN_DATA_H_
#define PARSE_PACK_TRAIN_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ParsePackIODefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*ZC与车载ATP动态数据结构体*/
	typedef struct ZcAndTrainIODataStruct
	{
		UINT8_S TrainId;                                       /*通信的Id*/
		UINT16_S ValueBuffLen;                                  /*通信的Buf长度*/
		UINT8_S ValueBuff[ZC_TRAIN_COM_BYTE_SUM_MAX];           /*通信的Buf值*/
	}ZcAndTrainIODataStruct;

	/*
	* 功能描述： 获取车载ATP输入的最大数量
	* 参数说明： void
	* 返回值  ： SIZE_MAX_LINE_TRAIN+1: 失败
	*			>=0: 数量      
	*/
	UINT8_S GetTrainToZcCurSum(void);

	/*
	* 功能描述：获取车载ATP输入Zc的Id对应列车ID
	* 参数说明： const UINT8 trainIdOfIndex
	* 返回值  ： 0: 失败
	*			 >0: 成功      
	*/
	UINT16_S GetTrainToZcBuffIndexOfTrainId(const UINT8_S trainIdOfIndex);

	/*
	* 功能描述：获取车载ATP输入Zc的Id对应数据长度
	* 参数说明： const UINT8 ciIdOfIndex
	* 返回值  ： 0: 失败
	*			 >0: 成功      
	*/
	UINT16_S GetTrainToZcIdDataBufLen(const UINT8_S trainIdOfIndex);

	/*
	* 功能描述： 获取车载ATP输入Zc的Id对应数据信息
	* 参数说明： const UINT8 trainIdOfIndex
	* 返回值  ： NULL: 失败
	*			 !NULL: 成功       
	*/
	UINT8_S* GetTrainToZcBufDataOfIndex(const UINT8_S trainIdOfIndex);

	/*
	* 功能描述： 解析车载ATP输入的单帧数据
	* 参数说明： const UINT8_S dataBuff[], 数据缓冲区
	*            const UINT16_S dataLength, 数据长度
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseTrainToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength);

	/*
	* 功能描述： 校验车载ATP输入的数据正确性
	* 参数说明： const UINT8_S dataBuff[],数据数组   
	*            const UINT16_S dataLen,数据长度
	* 返回值  ： 0:合法性校验失败
	*			 1:合法性校验成功      
	*/
	UINT8_S TrainInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen);

	/*
	* 功能描述： 获取ZC输出车载Atp的最大数量
	* 参数说明： void
	* 返回值  ： SIZE_MAX_LINE_TRAIN+1,失败
	*			 1: 成功      
	*/
	UINT8_S GetToTrainCurSum(void);

	/*
	* 功能描述： 获取ZC输出车载ATP的Id对应数据长度
	* 参数说明： const UINT8 trainIdOfIndex
	* 返回值  ： 0: 失败
	*			 >0: 成功      
	*/
	UINT16_S GetToTrainIdDataBufLen(const UINT8_S trainIdOfIndex);

	/*
	* 功能描述： 获取ZC输出车载Atp的Id下标对应缓存区
	* 参数说明： const UINT8 trainIdOfIndex
	* 返回值  ： NULL: 失败
	*			 !NULL: 成功      
	*/
	UINT8_S* GetToTrainBufDataOfIndex(const UINT8_S trainIdOfIndex);

	/*
	* 功能描述： 组车载ATP数据
	* 参数说明： const UINT8* dataBuff,数据缓存
	*            const UINT16_S dataLength,数据长度
	*            const UINT16_S destId, 目标ID   
	* 返回值  ： 0:组数据失败
	*			 1:组数据成功      
	*/
	UINT8_S PackZcToTrainFrameData(const UINT8_S* dataBuff,const UINT16_S dataLength,const UINT16_S destId);

	/*
	* 功能描述： 清空本周期所有车载Atp输入信息
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearCycleTrainInputData(void);

	/*
	* 功能描述： 清空本周期所有输出给车载Atp信息
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void ClearCycleTrainOutputData(void);

#ifdef __cplusplus
}
#endif
#endif
