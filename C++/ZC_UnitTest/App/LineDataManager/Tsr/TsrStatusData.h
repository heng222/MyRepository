/************************************************************************
*
* 文件名   ：  TsrStatusData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  临时限速状态管理
* 备  注   ：  无
*
************************************************************************/
#ifndef TSR_STATUS_DATA_H_
#define TSR_STATUS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "TsrDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*定义单个临时限速信息*/
	typedef struct SingleTsrDataStruct
	{
		UINT8_S  Speed;                                          /*临时限速数值(单位：km/h)*/
		UINT8_S  SectionNum;                                     /*临时限速区域包含逻辑区段数量*/
		UINT16_S  SectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX];      /*临时限速区域包含逻辑区段ID*/
	}SingleTsrDataStruct;


	/*临时限速结构体信息*/
	typedef struct TsrDataStruct
	{
		UINT16_S  BelongZcId;                                 /*临时限速所属ZC*/
		UINT8_S  TsrNum;                                      /*临时限速数量*/
		SingleTsrDataStruct  SingleTsrDataStru[SINGLE_ZC_TSR_SUM_MAX];    /*单个ZC范围内的临时限速数据结构*/
	}TsrDataStruct;
	
	/*
	* 功能描述： 获取本ZC管理范围内当前临时限速数量总数
	*	        （包含相邻ZC发送过来的切换区域内的临时限速）
	* 参数说明： void    
	* 返回值  ： TSR_BUFF_SUM_MAX: 获取数据失败
	*			>=0: 当前ZC数量总数
	*/
	UINT16_S GetTsrOfZcSum(void);

	/*
	* 功能描述： 获取指定数组下标对应的所属ZCID
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： 0: 获取数据失败
	*			>0: ZCID      
	*/
	UINT16_S GeTsrOfBelongZcId(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定数组下标对应的临时限速信息
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： NULL: 获取数据失败
	*			!NULL: 信息      
	*/
	TsrDataStruct* GeTsrDataStructOfIndex(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定ZCID临时限速下标
	* 参数说明： const UINT16 zcId,zcID
	* 返回值  ： TSR_BUFF_SUM_MAX; 获取数据失败
	*			 >0;查找索引成功
	*/
	UINT8_S GeZcIdOfTsrBufIndex(const UINT16_S zcId);

	/*
	* 功能描述： 获取指定ZCID临时限速数量
	* 参数说明： const UINT16 zcId,zcID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 数量信息     
	*/
	UINT8_S GetZcIdOfTsrNum(const UINT16_S zcId);

	/*
	* 功能描述： 设置指定ZC下标临时限速数量
	* 参数说明： const UINT8 tsrOfZcBufIndex,临时限速对应的ZC下标 
	*            const UINT8_S tsrNum,临时限速数量
	* 返回值  ： 0: 失败
	*			>0: 成功     
	*/
	UINT8_S SetZcIdOfTsrNum(const UINT8_S tsrOfZcBufIndex,const UINT8_S tsrNum);

	/*
	* 功能描述： 获取指定ZCID对应的某个下标下的临时限速对应的速度值
	* 参数说明： const UINT16 zcId, ZCID
	*	         const UINT16_S singleBufIndex buf下标   
	* 返回值  ： 0: 获取数据失败
	*			>0: 某条临时限速信息(以逻辑区段ID数组为返回值)      
	*/
	UINT8_S GetSingleTsrDataOfSpeed(const UINT16_S zcId,const UINT16_S singleBufIndex);

	/*
	* 功能描述： 设置指定ZCID对应的某个下标下的临时限速对应的速度值
	* 参数说明： const UINT8 tsrOfZcBufIndex,存储临时限速关联的ZCid对应下标
	*	         const UINT16_S singleBufIndex,单个ZC临时限速buf下标
	*            const UINT16_S speed,临时限速速度
	* 返回值  ： 0: 获取数据失败
	*			>0: 某条临时限速信息(以逻辑区段ID数组为返回值)      
	*/
	UINT8_S SetSingleTsrDataOfSpeed(const UINT8_S tsrOfZcBufIndex,const UINT16_S singleBufIndex, const UINT16_S speed);

	/*
	* 功能描述： 获取指定ZCID对应的某个下标下临时限速对应的逻辑区段数量
	* 参数说明： const UINT16 zcId, ZCID
	*	         const UINT16_S singleBufIndex buf下标   
	* 返回值  ： 0: 获取数据失败
	*			>0: 数量      
	*/
	UINT8_S GetSingleTsrDataOfSectionNum(const UINT16_S zcId,const UINT16_S singleBufIndex);

	/*
	* 功能描述： 获取指定ZCID对应的某个下标下的临时限速对应的逻辑区段buff
	* 参数说明： const UINT16 zcId, ZCID
	*			 const UINT16_S bufIndex buf下标   
	*			 const UINT8_S bufSize,数组大小
	*            UINT16_S sectionIdBuff[],输出数组
	* 返回值  ： 0: 获取数据失败
	*			 1: 获取成功      
	*/
	UINT8_S GetSingleTsrDataOfSectionBuff(const UINT16_S zcId,const UINT16_S singleBufIndex,const UINT8_S bufSize,UINT16_S sectionIdBuff[]);

	/*
	* 功能描述： 设置指定ZCID对应的某个下标下的临时限速的逻辑区段buff
	* 参数说明： const UINT8 tsrOfZcBufIndex,存储临时限速关联的ZCid对应下标
	*	         const UINT16_S singleBufIndex,单个ZC临时限速buf下标  
	*            const UINT8_S sectionNum,设置的临时限速数量
	*            const UINT16_S sectionIdBuff[],设置的临时限速对应的逻辑区段Id数组
	* 返回值  ： 0: 设置数据失败
	*			 1: 设置数据成功      
	*/
	UINT8_S SetSingleTsrDataOfSectionInfo(const UINT8_S tsrOfZcBufIndex,const UINT8_S singleBufIndex,const UINT8_S sectionNum,const UINT16_S sectionIdBuff[]);

	/*
	* 功能描述： 申请临时限速对应的ZC下标
	* 参数说明： const UINT16 zcId, zcId    
	* 返回值  ： 0: 设置失败
	*			>0: 设置成功      
	*/
	UINT8_S AplyTsrIndexOfZcId(const UINT16_S zcId);

#ifdef __cplusplus
}
#endif

#endif
