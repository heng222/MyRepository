/************************************************************************
*
* 文件名   ：  CommTargetLogicManager.h
* 作者     ：  ZC组
* 创建时间 ：  2015.07.14
* 功能描述 ：  通讯对象逻辑处理
* 备  注   ：  无
*
************************************************************************/

#ifndef COMM_TARGET_MANAGER_DATA_H_
#define COMM_TARGET_MANAGER_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "CommTargetDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 函数名称:  ManagerCommTargetCommCycle
* 功能描述： 管理通信对象通信周期管理
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 无
*/
void ManagerCommTargetCommCycle(void);

/*
* 函数名称： JudgeSingleCommTypeCommCyle
* 功能描述： 处理通信对象（除列车外）通信周期管理
* 输入参数： const UINT8 commTargetType，通信对象类型  
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeSingleCommTypeCommCyle(const UINT8_S commTargetType);

/*
* 函数名称： JudgeCommTrainCommCyle
* 功能描述： 处理通信列车通信周期管理
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeCommTrainCommCyle(void);

/*
* 函数名称： ManageCommTargetCommStatus
* 功能描述： 通信对象通信状态管理
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 无
*/
void ManageCommTargetCommStatus(void);

/*
* 函数名称： JudgeSingleCommTypeCommStatus
* 功能描述： 处理通信对象（除列车外）通信状态管理
* 输入参数： const UINT8 commTargetType，通信对象类型  
*            const UINT16_S maxCommFaultCycle，该通信类型最大的通信故障周期
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeSingleCommTypeCommStatus(const UINT8_S commTargetType,const UINT16_S maxCommFaultCycle);

/*
* 函数名称： JudgeNtpCommStatus
* 功能描述： 处理NTP通信状态管理
* 输入参数： 无
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeNtpCommStatus(void);

/*
* 函数名称： JudgeCommTrainCommStatus
* 功能描述： 处理通信列车通信状态管理
* 输入参数： const UINT16 maxCommFaultCycle，该通信类型最大的通信故障周期   
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeCommTrainCommStatus(const UINT16_S maxCommFaultCycle);

/*
* 函数名称： ManageCommTargetCommFailure
* 功能描述： 处理通信对象通信故障状态
* 输入参数： 无   
* 输出参数： 无
* 返回值  ： 无
*/
void ManageCommTargetCommFailure(void);

/*
* 函数名称： JudgeSingleCommTypeCommFailure
* 功能描述： 判断单个通信对象通信故障状态
* 输入参数： const UINT8 commTargetType,通讯对象类型   
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeSingleCommTypeCommFailure(const UINT8_S commTargetType);

/*
* 函数名称： ProcessCiCommFailure
* 功能描述： 判断单个CI通信对象通信故障状态
* 输入参数： const UINT16 commCiId,通讯CI的ID   
* 输出参数： 无
* 返回值  ： 无
*/
void ProcessCiCommFailure(const UINT16_S commCiId);

/*
* 函数名称： ProcessZcCommFailure
* 功能描述： 判断单个ZC通信对象通信故障状态
* 输入参数： const UINT16 commZcId,通讯ZC的ID   
* 输出参数： 无
* 返回值  ： 无
*/
void ProcessZcCommFailure(const UINT16_S commZcId);

/*
* 函数名称： JudgeTrainCommFailure
* 功能描述： 判断列车通信故障状态
* 输入参数： 无   
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainCommFailure(void);

/*
* 函数名称： ProcessTrainCommFailure
* 功能描述： 判断单个列车通信故障状态
* 输入参数： const UINT16 commTrainId,通讯列车ID   
* 输出参数： 无
* 返回值  ： 无
*/
void ProcessTrainCommFailure(const UINT16_S commTrainId);

/*
* 函数名称： FindFrontTrainOfTrainCommFailure
* 功能描述： 查找故障列车前方列车（车头所在计轴和车头所在计轴前方计轴）
* 输入参数： const UINT16 trainId,列车的ID 
*            const UINT16_S acId,车头所在计轴区段
* 输出参数： 无
* 返回值  ： 0:未查到列车
*           >0:列车Id
*/
UINT16_S FindFrontTrainOfTrainCommFailure(const UINT16_S trainId,const UINT16_S acId);

/*
* 函数名称： FindRearTrainOfTrainCommFailure
* 功能描述： 查找故障列车后方列车（车头所在计轴和车头所在计轴前方计轴）
* 输入参数： const UINT16 trainId,列车的ID 
*            const UINT16_S acId,车尾所在计轴区段
* 输出参数： 无
* 返回值  ： 0 :未查到列车
*            >0:列车Id
*/
UINT16_S FindRearTrainOfTrainCommFailure(const UINT16_S trainId,const UINT16_S acId);
	
#ifdef __cplusplus
}
#endif

#endif
