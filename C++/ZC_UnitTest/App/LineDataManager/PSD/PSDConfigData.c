/************************************************************************
*
* 文件名   ：  PSDConfigData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  屏蔽门配置数据
* 备  注   ：  无
*
************************************************************************/
#include "PSDConfigData.h"

PsdConfigDataStruct gPsdConfigDataStruBuff[PSD_LOCAL_SUM_MAX];          /*本地管理的屏蔽门配置信息*/
UINT16_S gPsdIdBuff[PSD_SUM_MAX] = {PSD_LOCAL_SUM_MAX};                                /*定义屏蔽门映射数组*/
UINT16_S gPsdCurSum = 0U;                                              /*屏蔽门当前总数*/
                                                
/*
* 功能描述： 获取屏蔽门管理总数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 屏蔽门当前总数
*/
UINT16_S GetPsdSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gPsdCurSum >= PSD_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gPsdCurSum;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定数组下标对应的屏蔽门ID
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： 0: 获取数据失败
*			>0: 屏蔽门ID      
*/
UINT16_S GetPsdId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetPsdSum())
	{
		rtnValue = gPsdConfigDataStruBuff[bufIndex].PsdId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID屏蔽门索引号
* 参数说明： const UINT16 psbId,屏蔽门ID
* 返回值  ： PSD_LOCAL_SUM_MAX; 获取数据失败
*			  >=0U;查找索引成功
*/
UINT16_S GetPsdConfigBufIndex(const UINT16_S psdId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((psdId >= 1U) && (psdId < PSD_SUM_MAX))
	{
		rtnValue = gPsdIdBuff[psdId];
	}
	else
	{
		rtnValue = PSD_LOCAL_SUM_MAX;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID站台屏蔽门所属联锁ID
* 参数说明： const UINT16 psbId,屏蔽门ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属联锁ID      
*/
UINT8_S GetPsdBelongCiId(const UINT16_S psdId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetPsdConfigBufIndex(psdId);  /*获取数组下标*/

	if (bufIndex < GetPsdSum())
	{
		rtnValue = gPsdConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID屏蔽门所属ZcID
* 参数说明： const UINT16 psbId, 屏蔽门ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属ZcID      
*/
UINT8_S GetPsdBelongZcId(const UINT16_S psdId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetPsdConfigBufIndex(psdId);  /*获取数组下标*/

	if (bufIndex < GetPsdSum())
	{
		rtnValue = gPsdConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID屏蔽门共管区域属性
* 参数说明： const UINT16 psbId, 屏蔽门ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT16_S GetPsdChangeAttribute(const UINT16_S psdId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetPsdConfigBufIndex(psdId);  /*获取数组下标*/

	if (bufIndex < GetPsdSum())
	{
		rtnValue = gPsdConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
