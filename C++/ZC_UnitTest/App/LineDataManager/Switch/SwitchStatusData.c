/************************************************************************
*
* 文件名   ：  SwitchStatusData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  道岔状态管理
* 备  注   ：  无
*
************************************************************************/
#include "SwitchStatusData.h"
#include "SwitchConfigData.h"

SwitchDataStruct gSwitchStatusDataStruBuff[SWITCH_LOCAL_SUM_MAX];          /*本地管理的道岔状态信息*/

/*
* 功能描述： 获取道岔数据
* 参数说明： void    
* 返回值  ： NULL: 获取数据失败
*			 !NULL: 道岔数据
*/
SwitchDataStruct* GetSwitchStatusData(void)
{
	return gSwitchStatusDataStruBuff;
}

/*
* 功能描述： 获取道岔当前状态
* 参数说明： const UINT16 switchId 道岔ID    
* 返回值  ： 3: 获取数据失败
*			不等于3: 道岔状态
*/
UINT8_S GetSwitchPosStatus(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*获取数组下标*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchStatusDataStruBuff[bufIndex].SwitchPosStatus;
	}
	else
	{
		rtnValue = SWITCH_STATE_LOSE;
	}

	return rtnValue;
}

/*
* 功能描述： 设置道岔当前状态
* 参数说明： const UINT16 switchId 道岔ID; 
*	         UINT8_S  SwitchPosStatus 道岔状态    
* 返回值  ： 0;失败
*            1;成功
*/
UINT8_S SetSwitchPosStatus(const UINT16_S switchId,UINT8_S switchPosStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*获取数组下标*/

	if (bufIndex < GetSwitchSum())
	{
		if ((SWITCH_STATE_MAIN == switchPosStatus) 
			|| (SWITCH_STATE_SIDE == switchPosStatus)
			|| (SWITCH_STATE_LOSE == switchPosStatus))
		{
			gSwitchStatusDataStruBuff[bufIndex].SwitchPosStatus = switchPosStatus;
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

/*
* 功能描述： 获取道岔锁闭状态
* 参数说明： const UINT16 switchId 道岔ID    
* 返回值  ： 0: 获取数据失败
*			>0: 道岔锁闭状态
*/
UINT8_S GetSwitchLock(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*获取数组下标*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchStatusDataStruBuff[bufIndex].SwitchLock;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置道岔锁闭状态
* 参数说明： const UINT16 switchId 道岔ID; 
*	         UINT8_S  lockStatus 道岔锁闭状态    
* 返回值  ： 0;失败
*            1;成功
*/
UINT8_S SetSwitchLock(const UINT16_S switchId,UINT8_S lockStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*获取数组下标*/

	if (bufIndex < GetSwitchSum())
	{
		if ((SWITCH_STATE_LOCK == lockStatus) || (SWITCH_STATE_UNLOCK == lockStatus))
		{
			gSwitchStatusDataStruBuff[bufIndex].SwitchLock = lockStatus;
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
