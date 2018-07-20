/************************************************************************
*
* 文件名   ：  CommTargetStatusData.h
* 作者     ：  ZC组
* 创建时间 ：  2015.07.14
* 功能描述 ：  通讯对象状态
* 备  注	：  无
*
************************************************************************/

#ifndef COMM_TARGET_STATUS_DATA_H_
#define COMM_TARGET_STATUS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "CommTargetDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*通信对象状态数据结构体*/
typedef struct SingleCommTargeStruct
{
	UINT16_S CommTargetId;                                    /*通信对象ID*/	
	UINT8_S CommTargetStatus;                                /*通信状态*/
	UINT32_S CommTargetCycle;                                /*通信周期累加位*/
	UINT32_S CommTargetCycleNum;                             /*通信对象输入信息时的周期号*/
} SingleCommTargeStruct;

/*通信对象状态数据结构体（其他通信对象）*/
typedef struct CommTargetDataStruct
{
	UINT8_S CommTargetType;                                  /*通信对象类型*/
	UINT8_S CommTargetNum;                                   /*通信对象ID数量*/
	UINT8_S CommTargetIdBuff[COMM_TARGET_ID_MAX];            /*设备通信索引表*/
	SingleCommTargeStruct SingleCommTargeStru[SINGLE_TYPE_COMM_TARGET_SUM_MAX];          /*通信周期累加位*/
} CommTargetDataStruct;

/*
* 功能描述： 获取通信对象信息
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 获取通信对象信息
*/
CommTargetDataStruct* GetCommTargetStatusData(void);

/*
* 功能描述： 获取通信对象Id对应的下标
* 参数说明： const UINT8 commTargetType 类型
			const UINT16_S commTargetId  ID
* 返回值  ： 0: 获取数据失败
*			>0: 对象Id对应的下标
*/
UINT8_S GetOtherCommTargetIdBuffIndex(const UINT8_S commTargetType,const UINT16_S commTargetId);

/*
* 功能描述： 获取某通信对象通信累加信息
* 参数说明： const UINT8 commTargetType 通信对象类型
*            const UINT16_S commTargetID 通信对象ID    
* 返回值  ： 0xffff: 获取数据失败
*			>=0: 通信累加信息
*/
UINT16_S GetCommTargetCycle(const UINT8_S commTargetType,const UINT16_S commTargetId);

/*
* 功能描述： 设置某通信对象通信累加信息
* 参数说明： const UINT8 commTargetType 通信对象类型
*			 const UINT16_S commTargetID 通信对象ID  
*			 const UINT16_S commTargetCycle 通信对象累加信息    
* 返回值  ： 0: 设置失败
*			 1: 设置成功
*/
UINT8_S SetCommTargetCycle(const UINT8_S commTargetType,const UINT16_S commTargetId, const UINT16_S commTargetCycle);

/*
* 功能描述： 获取某通信对象状态信息
* 参数说明： const UINT8 commTargetType 通信对象类型
*			 const UINT16_S commTargetID 通信对象ID      
* 返回值  ： 0: 获取数据失败
*			>=0: 状态信息
*/
UINT8_S GetCommTargetStatus(const UINT8_S commTargetType,const UINT16_S commTargetId);

/*
* 功能描述： 设置某通信对象状态信息
* 参数说明： const UINT8 commTargetType 通信对象类型
*            const UINT16_S commTargetID 通信对象ID    
*            const UINT8_S commTargetStatus 通信对象状态信息 
* 返回值  ： 0: 设置失败
*			 1: 设置成功
*/
UINT8_S SetCommTargetStatus(const UINT8_S commTargetType,const UINT16_S commTargetId, const UINT8_S commTargetStatus);

/*
* 功能描述： 获取某通信对象通信对象输入信息时的周期号
* 参数说明： const UINT8 commTargetType 通信对象类型
*			 const UINT16_S commTargetID 通信对象ID     
* 返回值  ：  0: 获取数据失败
*			>=0: 通信对象输入信息时的周期号
*/
UINT32_S GetCommTargetCycleNum(const UINT8_S commTargetType,const UINT16_S commTargetId);

/*
* 功能描述： 设置某通信对象周期信息
* 参数说明：const UINT8 commTargetType 通信对象类型
*           const UINT16_S commTargetID 通信对象ID  
*           const UINT32_S commTargetCycleNum 通信对象周期信息    
* 返回值  ： 0: 设置失败
*			 1: 设置成功
*/
UINT8_S SetCommTargetCycleNum(const UINT8_S commTargetType,const UINT16_S commTargetId, const UINT32_S commTargetCycleNum);

/*
* 功能描述： 处理通信对象通信故障状态
* 参数说明： 无   
* 返回值  ： 无
*/
void ClearOneTrainCommCycleAndStatus(const UINT16_S trainId);
#ifdef __cplusplus
}
#endif

#endif
