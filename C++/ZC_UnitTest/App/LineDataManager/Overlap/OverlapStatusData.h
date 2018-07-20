
/********************************************************                                                                                                           
文 件 名： OverlapStatusData.h
作    者： ZC组
创建时间： 2015.04.18
描述： 保护区段状态  
备注： 无  
********************************************************/ 

#ifndef OVERLAP_STATUS_DATA_H_
#define OVERLAP_STATUS_DATA_H_


#include "OverlapDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/*保护区段状态数据结构体*/
typedef struct OverlapDataStruct
{
	UINT16_S OverlapId;                     /*保护区段按钮ID*/
	UINT8_S OverlapStatus;                  /*保护区段当前状态*/
} OverlapDataStruct;


/*************************************************
函数名:   GetOverlapStatusData   
功能描述: 获取保护区段数据
输入: void    
输出: 无
返回值: NULL: 获取数据失败
*			 !NULL: 保护区段数据
*************************************************/
OverlapDataStruct* GetOverlapStatusData(void);

/*************************************************
函数名:   GetOverlapStatus   
功能描述: 获取保护区段当前状态
输入: overlapId 保护区段ID    
输出: 无
返回值: 0: 获取数据失败
		>0: 保护区段状态
*************************************************/
UINT8_S GetOverlapStatus(const UINT16_S overlapId);

/*************************************************
函数名:   SetOverlapStatus   
功能描述: 设置保护区段当前状态
输入: overlapId 保护区段ID; 
	        overlapStatus 保护区段状态    
输出: 无
返回值: 无
*************************************************/
UINT8_S SetOverlapStatus(const UINT16_S overlapId,UINT8_S overlapStatus);

#ifdef __cplusplus
}
#endif

#endif
