/************************************************************************
*
* 文件名   ：  SignalStatusData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  信号机状态管理
* 备  注   ：  无
*
************************************************************************/
#include "SignalStatusData.h"
#include "SignalConfigData.h"

SignalDataStruct gSignalDataStruBuff[SIGNAL_LOCAL_SUM_MAX];          /*本地管理的保护区段状态信息*/

/*
	* 功能描述： 获取信号机数据
	* 参数说明： void    
	* 返回值  ： NULL: 获取数据失败
	*			 !NULL: 信号机数据
	*/
SignalDataStruct* GetSignalStatusData(void)
{
	return gSignalDataStruBuff;
}

/*
* 功能描述： 获取信号机当前状态
* 参数说明： const UINT16  signalId 信号机ID    
* 返回值  ： 0: 获取数据失败
*			>0: 信号机状态
*/
UINT8_S GetSignalStatus(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalDataStruBuff[bufIndex].SignalStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置信号机当前状态
* 参数说明： const UINT16 signalId 信号机ID; 
*            UINT8_S signalStatus 信号机状态    
* 返回值  ： 0;失败
*            1;成功
*/
UINT8_S SetSignalStatus(const UINT16_S signalId,UINT8_S signalStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		if ((SIGNAL_STATE_PASS == signalStatus) || (SIGNAL_STATE_STOP == signalStatus))
		{
			gSignalDataStruBuff[bufIndex].SignalStatus = signalStatus;
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
* 功能描述： 获取信号机信号机亮灭状态
* 参数说明： const UINT16 signalId 信号机ID    
* 返回值  ： 0: 获取数据失败
*			>0: 信号机状态
*/
UINT8_S GetSignalLightOffStatus(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalDataStruBuff[bufIndex].LightOffStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置信号机信号机亮灭状态
* 参数说明： const UINT16 signalId 信号机ID; 
*	         UINT8_S  lightOffStatus 信号机状态    
* 返回值  ： 0;失败
*            1;成功
*/
UINT8_S SetSignalLightOffStatus(const UINT16_S signalId,UINT8_S lightOffStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		if ((SIGNAL_OFF_COMMAND == lightOffStatus) || (SIGNAL_LIGHT_COMMAND == lightOffStatus))
		{
			gSignalDataStruBuff[bufIndex].LightOffStatus = lightOffStatus;
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
* 功能描述： 获取信号机列车跨压信号机状态
* 参数说明： const UINT16 signalId 信号机ID    
* 返回值  ： 0: 获取数据失败
*			>0: 信号机状态
*/
UINT8_S GetSignalCrossStatus(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalDataStruBuff[bufIndex].CrossStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置信号机列车跨压信号机状态
* 参数说明： const UINT16 signalId 信号机ID; 
*	         UINT8_S  crossStatus 信号机状态    
* 返回值  ： 0;失败
*            1;成功
*/
UINT8_S SetSignalCrossStatus(const UINT16_S signalId,UINT8_S crossStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		if ((SIGNAL_TRAIN_ALREADY_CROSS == crossStatus) || (SIGNAL_TRAIN_NOT_CROSS == crossStatus))
		{
			gSignalDataStruBuff[bufIndex].CrossStatus = crossStatus;
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
