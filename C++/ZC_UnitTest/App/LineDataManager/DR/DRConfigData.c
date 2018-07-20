/************************************************************************
*
* 文件名   ：  DRConfigData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  无人折返配置数据
* 备  注   ：  无
*
************************************************************************/
#include "DRConfigData.h"


DRButtonConfigDataStruct gDRButtonConfigDataStruBuff[DR_BUTTON_LOCAL_SUM_MAX];     /*定义无人折返按钮数据配置结构体*/
UINT16_S gDRButtonIdBuff[DR_BUTTON_SUM_MAX] = {DR_BUTTON_LOCAL_SUM_MAX};          /*定义无人折返按钮ID映射数组*/
UINT16_S gDRButtonCurSum = 0U;                                                    /*无人折返按钮当前总数*/

DRLampConfigDataStruct gDRLampConfigDataStruBuff[DR_LAMP_LOCAL_SUM_MAX];           /*定义无人折返按钮数据配置结构体*/
UINT16_S gDRLampIdBuff[DR_LAMP_SUM_MAX] = {DR_LAMP_LOCAL_SUM_MAX};                /*定义无人折返按钮ID映射数组*/
UINT16_S gDRLampCurSum = 0U;                                                      /*无人折返按钮当前总数*/


/*
* 功能描述： 获取无人折返按钮管理总数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 无人折返按钮当前总数
*/
UINT16_S GetDRButtonSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gDRButtonCurSum >= DR_BUTTON_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	}
	else
	{
		rtnValue = gDRButtonCurSum;
	}

	return rtnValue;
}

/*
* 功能描述： 获取无人折返灯管理总数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 无人折返灯当前总数
*/
UINT16_S GetDRLampSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gDRLampCurSum >= DR_LAMP_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	}
	else
	{
		rtnValue = gDRLampCurSum;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定数组下标对应的无人折返按钮ID
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： 0: 获取数据失败
*			>0: 无人折返按钮ID      
*/
UINT16_S GetDRButtonId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue =  gDRButtonConfigDataStruBuff[bufIndex].DRButtonId;
	}
	else
	{
		rtnValue =  RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定数组下标对应的无人折返按灯ID
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： 0: 获取数据失败
*			>0: 无人折返灯ID    
*/
UINT16_S GetDRLampId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetDRLampSum())
	{
		rtnValue = gDRLampConfigDataStruBuff[bufIndex].DRLampId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定无人折返按钮ID索引号
* 参数说明： const UINT16 drButtonId, 无人折返按钮ID
* 返回值  ： DR_BUTTON_LOCAL_SUM_MAX: 获取数据失败
*			<DR_BUTTON_LOCAL_SUM_MAX: 查找成功
*/
UINT16_S GetDRButtonConfigBufIndex(const UINT16_S drButtonId)
{
	UINT16_S rtnValue = DR_BUTTON_LOCAL_SUM_MAX;

	if ((drButtonId >= 1U) && (drButtonId < DR_BUTTON_SUM_MAX))
	{
		rtnValue = gDRButtonIdBuff[drButtonId];
	}
	else
	{
		rtnValue = DR_BUTTON_LOCAL_SUM_MAX;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定无人折返灯ID索引号
* 参数说明： const UINT16 drLampId, 无人折返灯ID
* 返回值  ： DR_LAMP_LOCAL_SUM_MAX: 获取数据失败
*			<DR_LAMP_LOCAL_SUM_MAX: 查找成功
*/
UINT16_S GetDRLampConfigBufIndex(const UINT16_S drLampId)
{
	UINT16_S rtnValue = DR_LAMP_LOCAL_SUM_MAX;

	if ((drLampId >= 1U) && (drLampId < DR_LAMP_SUM_MAX))
	{
		rtnValue = gDRLampIdBuff[drLampId];
	}
	else
	{
		rtnValue = DR_LAMP_LOCAL_SUM_MAX;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID无人折返按钮所属联锁ID
* 参数说明： const UINT16 drButtonId    
* 返回值  ： 0: 获取数据失败
*			>0: 所属联锁ID      
*/
UINT8_S GetDRButtonBelongCiId(const UINT16_S drButtonId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*获取数组下标*/

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue = gDRButtonConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID无人折返灯所属联锁ID
* 参数说明： const UINT16 drLampId   
* 返回值  ： 0: 获取数据失败
*			>0: 所属联锁ID      
*/
UINT8_S GetDRLampBelongCiId(const UINT16_S drLampId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*获取数组下标*/

	if (bufIndex < GetDRLampSum())
	{
		rtnValue =  gDRLampConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue =  RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID无人折返按钮所属ZCID
* 参数说明： const UINT16 drButtonId    
* 返回值  ： 0: 获取数据失败
*			>0: 所属ZC的ID      
*/
UINT8_S GetDRButtonBelongZcId(const UINT16_S drButtonId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*获取数组下标*/

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue = gDRButtonConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID无人折返灯所属ZCID
* 参数说明： const UINT16 drLampId   
* 返回值  ： 0: 获取数据失败
*			>0: 所属ZC的ID      
*/
UINT8_S GetDRLampBelongZcId(const UINT16_S drLampId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*获取数组下标*/

	if (bufIndex < GetDRLampSum())
	{
		rtnValue = gDRLampConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID无人折返按钮共管区域属性
* 参数说明： const UINT16 doorId, 屏蔽门ID    
* 返回值  ： 0: 不属于
*			 FLAG_SET: 属于      
*/
UINT8_S GetDRButtonChangeAttribute(const UINT16_S drButtonId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*获取数组下标*/

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue = gDRButtonConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID无人折返按钮共管区域属性
* 参数说明： const UINT16 doorId, 屏蔽门ID    
* 返回值  ： 0: 不属于
*			 FLAG_SET: 属于      
*/
UINT8_S GetDRLampChangeAttribute(const UINT16_S drLampId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*获取数组下标*/

	if (bufIndex < GetDRLampSum())
	{
		rtnValue = gDRLampConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
