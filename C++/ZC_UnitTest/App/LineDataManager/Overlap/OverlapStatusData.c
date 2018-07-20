
/********************************************************                                                                                                           
 文 件 名： OverlapStatusData.c
 作    者： ZC组
 创建时间： 2015.04.18
 描述： 保护区段状态  
 备注： 无  
********************************************************/ 

#include "OverlapStatusData.h"
#include "OverlapConfigData.h"

OverlapDataStruct gOverlapDataStruBuff[OVERLAP_LOCAL_SUM_MAX];          /*本地管理的保护区段状态信息*/

/*************************************************
  函数名:   GetOverlapStatusData   
  功能描述: 获取保护区段数据
  输入: void    
  输出: 无
  返回值: NULL: 获取数据失败
*			 !NULL: 保护区段数据
*************************************************/
OverlapDataStruct* GetOverlapStatusData(void)
{
	return gOverlapDataStruBuff;
}

/*************************************************
  函数名:   GetOverlapStatus   
  功能描述: 获取保护区段当前状态
  输入: overlapId 保护区段ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 保护区段状态
*************************************************/
UINT8_S GetOverlapStatus(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*获取数组下标*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapDataStruBuff[bufIndex].OverlapStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  函数名:   SetOverlapStatus   
  功能描述: 设置保护区段当前状态
  输入: overlapId 保护区段ID; 
	         overlapStatus 保护区段状态    
  输出: 无
  返回值: 无
*************************************************/
UINT8_S SetOverlapStatus(const UINT16_S overlapId,UINT8_S overlapStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*获取数组下标*/

	if (bufIndex < GetOverlapSum())
	{
		if ((OVERLAP_STATE_SET == overlapStatus) || (OVERLAP_STATE_UNSET == overlapStatus))
		{
			gOverlapDataStruBuff[bufIndex].OverlapStatus = overlapStatus;
			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
