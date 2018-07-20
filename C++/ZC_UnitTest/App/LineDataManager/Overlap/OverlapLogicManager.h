
/********************************************************                                                                                                           
文 件 名： OverlapLogicManager.h
作    者： ZC组
创建时间： 2015.04.18
描述： 保护区段逻辑处理  
备注： 无  
********************************************************/ 

#ifndef OVERLAP_LOGIC_DATA_H_
#define OVERLAP_LOGIC_DATA_H_


#include "OverlapDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
函数名:    InitFailureSingleOverlap  
功能描述: 处理通信故障Ci对应的单个保护区段信息
输入: const UINT16 overlapId，保护区段ID    
输出: 无
返回值: void  
*************************************************/
void InitFailureSingleOverlap(const UINT16_S overlapId);

/*************************************************
函数名:   InitFailureCiOverlap   
功能描述: 处理通信故障Ci对应的保护区段信息
输入: const UINT16 ciId，通信故障的CIID    
输出: 无
返回值: void  
*************************************************/
void InitFailureCiOverlap(const UINT16_S ciId);

/*************************************************
函数名:   InitFailureNZcOverlap   
功能描述: 处理通信故障nZc对应的保护区段信息
输入: const UINT16 nZcId，通信故障的nZcID    
输出: 无
返回值: void  
*************************************************/
void InitFailureNZcOverlap(const UINT16_S nZcId);

/*************************************************
函数名:    CalulateSwtichStateOfOverlapIsNeed  
功能描述: 计算输入的overlap是否满足道岔状态（锁闭和位置）
输入: const UINT16 overlpId，保护区段ID   
输出: 无
返回值: 0:不满足条件
*            1:满足条件  
*************************************************/
UINT8_S CalulateSwtichStateOfOverlapIsNeed(const UINT16_S overlpId);

#ifdef __cplusplus
}
#endif

#endif
