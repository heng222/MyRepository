/************************************************************************
*
* 文件名   ：  SwitchConfigData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  道岔配置数据管理
* 备  注   ：  无
*
************************************************************************/
#include "SwitchConfigData.h"

SwitchConfigDataStruct gSwitchConfigDataStruBuff[SWITCH_LOCAL_SUM_MAX];             /*本地管理的道岔信息*/
UINT16_S gSwitchIdBuff[SWITCH_SUM_MAX] = {0U};                                      /*定义道岔映射数组*/
UINT16_S gSwitchCurSum = 0U;                                                       /*道岔当前总数*/

/*
* 功能描述： 获取道岔管理总数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 道岔当前总数
*/
UINT16_S GetSwitchSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gSwitchCurSum >= SWITCH_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gSwitchCurSum;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定数组下标对应的道岔ID
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： 0: 获取数据失败
*			>0: 道岔ID      
*/
UINT16_S GetSwitchId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchConfigDataStruBuff[bufIndex].SwitchId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID道岔索引号
* 参数说明： const UINT16 switchId,道岔ID
* 返回值  ： SWITCH_SUM_MAX; 获取数据失败
*			 >0U; 查找索引成功
*/
UINT16_S GetSwitchConfigBufIndex(const UINT16_S switchId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((switchId >= 1U)&&(switchId < SWITCH_SUM_MAX))
	{
		rtnValue = gSwitchIdBuff[switchId];
	}
	else
	{
		rtnValue = SWITCH_SUM_MAX;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID站台道岔所属联锁ID
* 参数说明： const UINT16 switchId,道岔ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属联锁ID      
*/
UINT8_S GetSwitchBelongCiId(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*获取数组下标*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID道岔所属ZC的ID
* 参数说明： const UINT16 switchId, 道岔ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属ZcID      
*/
UINT8_S GetSwitchBelongZcId(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*获取数组下标*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID道岔共管区域属性
* 参数说明： const UINT16 switchId, 道岔ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT16_S GetSwitchChangeAttribute(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*获取数组下标*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID道岔位置区域
* 参数说明： const UINT16 switchId, 道岔ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT16_S GetSwitchPosition(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*获取数组下标*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchConfigDataStruBuff[bufIndex].SwitchPosition;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
