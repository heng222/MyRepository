
/********************************************************                                                                                                           
文 件 名： OverlapInitManager.h
作    者： ZC组
创建时间： 2015.04.18
描述： 保护区段初始化  
备注： 无  
********************************************************/ 



#ifndef OVERLAP_INIT_MANAGER_H_
#define OVERLAP_INIT_MANAGER_H_


#include "OverlapDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
函数名:    InitOverlapInitializationData  
功能描述: 初始化本地管理的保护区段初始信息
输入: 无   
输出: 无
返回值: 无      
*************************************************/
void InitOverlapInitializationData(void);

/*************************************************
函数名:   InitOverlapLocalInfo   
功能描述: 初始化本地管理的保护区段信息
输入: 无   
输出: 无
返回值: 0: 初始化失败
		>0: 初始化成功      
*************************************************/
UINT8_S InitOverlapLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
