/************************************************************************
*
* 文件名   ：  ESBStatusData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  紧急停车按钮状态管理
* 备  注   ：  无
*
************************************************************************/
#include "ESBStatusData.h"
#include "ESBConfigData.h"

EsbDataStruct gEsbDataStruBuff[ESB_LOCAL_SUM_MAX];          /*本地管理的紧急停车按钮状态信息*/

/*
* 功能描述： 获取紧急停车按钮数据
* 参数说明： void    
* 返回值  ： NULL: 获取数据失败
*			 !NULL: 紧急停车按钮数据
*/
EsbDataStruct* GetEsbStatusData(void)
{
	return gEsbDataStruBuff;
}

/*
* 功能描述： 获取紧急停车按钮当前状态
* 参数说明： esbId 紧急停车按钮ID    
* 返回值  ： 0: 获取数据失败
*			>0: 紧急停车按钮状态
*/
UINT8_S GetEsbStatus(const UINT16_S esbId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetEsbConfigBufIndex(esbId);  /*获取数组下标*/

	if (bufIndex < GetEsbSum())
	{
		rtnValue = gEsbDataStruBuff[bufIndex].EsbStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置紧急停车按钮当前状态
* 参数说明： esbId 紧急停车按钮ID; 
*	         esbStatus 紧急停车按钮状态    
* 返回值  ： 0U;失败
*            1;成功
*/
UINT8_S SetEsbStatus(const UINT16_S esbId,UINT8_S esbStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetEsbConfigBufIndex(esbId);  /*获取数组下标*/

	if (bufIndex < GetEsbSum())
	{
		if ((ESB_STATE_DOWN == esbStatus) || (ESB_STATE_UP == esbStatus))
		{
			gEsbDataStruBuff[bufIndex].EsbStatus = esbStatus;
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
