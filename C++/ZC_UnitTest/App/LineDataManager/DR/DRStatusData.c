/************************************************************************
*
* 文件名   ：  DRStatusData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  无人折返状态
* 备  注   ：  无
*
************************************************************************/
#include "DRStatusData.h"
#include "DRConfigData.h"

/*Local数据定义*/
DRButtonDataStruct  gDRButtonDataStruBuff[DR_BUTTON_LOCAL_SUM_MAX];                /*定义无人折返按钮状态数据结构体*/
DRLampDataStruct gDRLampDataStruBuff[DR_LAMP_LOCAL_SUM_MAX];                       /*定义无人折返灯状态数据结构体*/


/*
* 功能描述： 获取无人折返按钮数据
* 参数说明： void    
* 返回值  ： 无人折返按钮结构体数组首地址
*/
DRButtonDataStruct* GetDRButtonStatusData(void)
{
	return gDRButtonDataStruBuff;
}

/*
* 功能描述： 获取无人折返灯数据
* 参数说明： void    
* 返回值  ：无人折返灯结构体数组首地址
*/
DRLampDataStruct* GetDRLampData(void)
{
	return gDRLampDataStruBuff;
}

/*
* 功能描述： 获取无人折返按钮关联的列车ID
* 参数说明： const UINT16 drButtonId,无人折返按钮ID   
* 返回值  ： 0: 获取数据失败
*			>0: 列车ID
*/
UINT16_S GetDRButtonOfTrainId(const UINT16_S drButtonId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*获取数组下标*/

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue = gDRButtonDataStruBuff[bufIndex].TrainId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置无人折返按钮关联的列车ID
* 参数说明： const UINT16 drButtonId, 无人折返按钮ID
*            UINT16_S trainId,列车ID
* 返回值  ： 0:获取数据失败
*            1：获取数据成功
*/
UINT8_S SetDRButtonOfTrainId(const UINT16_S drButtonId,UINT16_S trainId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*获取数组下标*/

	if (bufIndex < GetDRButtonSum())
	{
		gDRButtonDataStruBuff[bufIndex].TrainId = trainId;

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取无人折返灯关联列车ID
* 参数说明： const UINT16 drLampId,无人折返灯ID   
* 返回值  ： 0: 获取数据失败
*			>0: 列车ID
*/
UINT16_S GetDRLampOfTrainId(const UINT16_S drLampId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*获取数组下标*/

	if (bufIndex < GetDRLampSum())
	{
		rtnValue = gDRLampDataStruBuff[bufIndex].TrainId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置无人折返灯关联列车ID
* 参数说明： const UINT16 drLampId,无人折返灯ID  
*            UINT16_S trainId,列车ID
* 返回值  ： 0:获取数据失败
*            1：获取数据成功
*/
UINT8_S SetDRLampOfTrainId(const UINT16_S drLampId,UINT16_S trainId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*获取数组下标*/

	if (bufIndex < GetDRLampSum())
	{
		gDRLampDataStruBuff[bufIndex].TrainId = trainId;

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取无人折返灯控制命令
* 参数说明： const UINT16 drLampId,无人折返灯ID    
* 返回值  ： 0: 获取数据失败
*			>0: 控制命令
*/
UINT8_S GetDRLampCommand(const UINT16_S drLampId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*获取数组下标*/

	if (bufIndex < GetDRLampSum())
	{
		rtnValue = gDRLampDataStruBuff[bufIndex].DRLampCmd;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置无人折返灯控制命令
* 参数说明： const UINT16 drLampId,无人折返灯ID  
*            UINT8_S drLampCmd,无人折返灯命令   
* 返回值  ： 0:获取数据失败
*            1：获取数据成功
*/
UINT8_S SetDRLampCommand(const UINT16_S drLampId,UINT8_S drLampCmd)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*获取数组下标*/

	if (bufIndex < GetDRLampSum())
	{
		if ((DR_LAMP_STEADY_STATUS == drLampCmd) || (DR_LAMP_TWINKLE_STATUS == drLampCmd))
		{
			gDRLampDataStruBuff[bufIndex].DRLampCmd = drLampCmd;

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
* 功能描述： 获取无人折返按钮当前状态
* 参数说明： const UINT16 drButtonId,无人折返按钮ID    
* 返回值  ： 0: 获取数据失败
*			>0: 控制命令
*/
UINT8_S GetDRButtonStatus(const UINT16_S drButtonId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*获取数组下标*/

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue = gDRButtonDataStruBuff[bufIndex].DRButtonStatus;
	}
	else
	{
		rtnValue = DEFAULT_ZERO;
	}

	return rtnValue;
}

/*
* 功能描述： 设置无人折返按钮控制命令
* 参数说明： const UINT16 drButtonId,无人折返按钮ID  
*            UINT8_S drButtonStatus,无人折返按钮命令   
* 返回值  ： 0:获取数据失败
*            1：获取数据成功
*/
UINT8_S SetDRButtonStatus(const UINT16_S drButtonId,UINT8_S drButtonStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*获取数组下标*/

	if (bufIndex < GetDRButtonSum())
	{
		if ((DR_BUTTON_STATE_DOWN == drButtonStatus) || (DR_BUTTON_STATE_UP == drButtonStatus))
		{
			gDRButtonDataStruBuff[bufIndex].DRButtonStatus = drButtonStatus;

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
