/************************************************************************
*
* 文件名   ：  CommTargetConfigData.h
* 作  者   ：  ZC组
* 创建时间 ：  2015.07.14
* 功能描述 ：  通讯目标配置
* 备  注   ：  无
*
************************************************************************/

#ifndef COMM_TARGET_CONFIG_DATA_H_
#define COMM_TARGET_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "CommTargetDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


/*通信对象配置数据结构体*/
typedef struct CommTargetConfigDataStruct
{
	UINT8_S CommTargetType;                                          /*通信对象设备识别符*/
	UINT8_S CommTargetNum;                                           /*该通信对象的通信设备数量*/
	UINT16_S CommTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX];       /*通信对象ID数组*/
	UINT8_S CommProtocolType;                                        /*通信协议类型*/
} CommTargetConfigDataStruct;

/*
* 函数名称： GetCommTargetTypeBuffIndex
* 功能描述： 获取通信类型存储下表
* 输入参数： const UINT8 commTargetType 通信设备类型    
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*			>0: 当前总数
*/
UINT8_S GetCommTargetTypeBuffIndex(const UINT8_S commTargetType);

/*
* 函数名称： GetCommTargetTypeSum
* 功能描述： 获取通信类型就总数
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*			>0: 当前总数
*/
UINT8_S GetCommTargetTypeSum(void);

/*
* 函数名称：GetSingleCommTargetTypeSum
* 功能描述： 获取某类通信设备总数
* 输入参数： const UINT8 commTargetType 通信设备类型 
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*			>0: 当前总数
*/
UINT8_S GetSingleCommTargetTypeSum(const UINT8_S commTargetType);

/*
* 函数名称： GetSingleCommTargetIdBuff
* 功能描述： 获取某类设备的通信ID数组
* 输入参数： const UINT8 commTargetType 通信设备类型   
*            const UINT8_S bufSize 数组大小
* 输出参数： UINT16_S commTargetIdBuff[] 输出数组
* 返回值  ： 0u: 获取数据失败
*			 1u: 获取数据成功
*/
UINT8_S GetSingleCommTargetIdBuff(const UINT8_S commTargetType,const UINT8_S bufSize,UINT16_S commTargetIdBuff[]);

/*
* 函数名称： GetSingleCommProtocolType
* 功能描述： 获取某类通信对象使用的协议类型
* 输入参数： const UINT8 commTargetType 通信设备类型    
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*			>0: 当前总数
*/
UINT8_S GetSingleCommProtocolType(const UINT8_S commTargetType);

/*
* 函数名称： GetCommTargetIdInConfigData
* 功能描述： 获取通信对象Id是否属于本ZC通信范围
* 输入参数： const UINT8 commTargetType, 通讯目标的类型    
*            const UINT16_S commTargetId,通讯目标的编号
* 输出参数： 无
* 返回值  ： 0u: 不属于
*			 1u: 属于      
*/
UINT8_S GetCommTargetIdInConfigData(const UINT8_S commTargetType, const UINT16_S commTargetId);

#ifdef __cplusplus
}
#endif

#endif
