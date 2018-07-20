/************************************************************************
*
* 文件名   ：  PSDStatusData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  屏蔽门状态管理
* 备  注   ：  无
*
************************************************************************/
#include "PSDStatusData.h"
#include "PSDConfigData.h"

PsdDataStruct gPsdDataStruBuff[PSD_LOCAL_SUM_MAX];             /*定义本地管理的屏蔽门状态数据数组*/

/*
* 功能描述： 获取屏蔽门数据
* 参数说明： void    
* 返回值  ： NULL: 获取数据失败
*			 !NULL: 屏蔽门数据
*/
PsdDataStruct* GetPsdStatusData(void)
{
	return gPsdDataStruBuff;
}

/*
* 功能描述： 获取屏蔽门当前状态
* 参数说明： psdId 屏蔽门ID    
* 返回值  ： 0: 获取数据失败
*			>0: 屏蔽门状态
*/
UINT8_S GetPsdStatus(const UINT16_S psdId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetPsdConfigBufIndex(psdId);  /*获取数组下标*/

	if (bufIndex < GetPsdSum())
	{
		rtnValue = gPsdDataStruBuff[bufIndex].PsdStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置屏蔽门当前状态
* 参数说明： psdId 屏蔽门ID; 
	            psdStatus 屏蔽门状态    
* 返回值  ： 无
*/
UINT8_S SetPsdStatus(const UINT16_S psdId,UINT8_S psdStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetPsdConfigBufIndex(psdId);  /*获取数组下标*/

	if (bufIndex < GetPsdSum())
	{
		if ((PSD_STATE_CLOSE == psdStatus) || (PSD_STATE_OPEN == psdStatus))
		{
			gPsdDataStruBuff[bufIndex].PsdStatus = psdStatus;
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
