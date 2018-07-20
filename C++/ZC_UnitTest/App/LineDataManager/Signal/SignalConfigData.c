/************************************************************************
*
* 文件名   ：  SignalConfigData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  信号机配置数据
* 备  注   ：  无
*
************************************************************************/
#include "SignalConfigData.h"

SignalConfigDataStruct gSignalConfigDataStruBuff[SIGNAL_LOCAL_SUM_MAX];            /*本地管理的信号机配置信息*/
UINT16_S gSignalIdBuff[SIGNAL_SUM_MAX] = {SIGNAL_LOCAL_SUM_MAX};                  /*定义信号机映射数组*/
UINT16_S gSignalCurSum = 0U;                                                      /*信号机当前总数*/

/*
* 功能描述： 获取信号机管理总数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 信号机当前总数
*/
UINT16_S GetSignalSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gSignalCurSum >= SIGNAL_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gSignalCurSum;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定数组下标对应的信号机ID
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： 0: 获取数据失败
*			>0: 信号机ID      
*/
UINT16_S GetSignalId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].SignalId;
	} 
	else
	{
		rtnValue = gSignalCurSum;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID信号机索引号
* 参数说明： const UINT16 signalId,信号机ID
* 返回值  ： SIGNAL_SUM_MAX ;获取数据失败
*			 >0U; 查找索引成功
*/
UINT16_S GetSignalConfigBufIndex(const UINT16_S signalId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((signalId >= 1U)&&(signalId < SIGNAL_SUM_MAX))
	{
		rtnValue = gSignalIdBuff[signalId];
	}
	else
	{
		rtnValue = SIGNAL_SUM_MAX;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID站台信号机所属联锁ID
* 参数说明： const UINT16 signalId,信号机ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属联锁ID      
*/
UINT8_S GetSignalBelongCiId(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID信号机所属ZC的ID
* 参数说明： const UINT16 signalId, 信号机ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属ZcID      
*/
UINT8_S GetSignalBelongZcId(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID信号机共管区域属性
* 参数说明： const UINT16 signalId, 信号机ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT16_S GetSignalChangeAttribute(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID信号机类型
* 参数说明： const UINT16 signalId, 信号机ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetSignalSignalType(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].SignalType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID信号机防护方向
* 参数说明： const UINT16 signalId, 信号机ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetSignalProtectDir(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].ProtectDir;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID信号机默认状态
* 参数说明： const UINT16 signalId, 信号机ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetSignalDefaultStatus(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].DefaultStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID信号机是否需要判断亮灭状态
* 参数说明： const UINT16 signalId, 信号机ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetSignalLightOffType(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].LightOffType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID信号机CBTC类型下的亮灭灯状态
* 参数说明： const UINT16 signalId, 信号机ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetSignalCbtcLightOffType(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].CbtcLightOffType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID信号机是否需要判断跨压状态
* 参数说明： const UINT16 signalId, 信号机ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetSignalCrossType(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].CrossType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID信号机是否需要判断闯过红灯信号机类型
* 参数说明： const UINT16 signalId, 信号机ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetSignalCrashType(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*获取数组下标*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].CrashType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
