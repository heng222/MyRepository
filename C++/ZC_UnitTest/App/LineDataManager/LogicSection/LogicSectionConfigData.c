/************************************************************************
*
* 文件名   ：  LogicSectionConfigData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  逻辑区段配置数据
* 备  注   ：  无
*
************************************************************************/
#include "LogicSectionConfigData.h"

LogicSectionConfigDataStruct gLogicSectionConfigDataStruBuff[LOGIC_SECTION_LOCAL_SUM_MAX];          /*本地管理的逻辑区段配置信息*/
UINT16_S gLogicSectionIdBuff[LOGIC_SECTION_SUM_MAX] = {0U};                                         /*定义逻辑区段映射数组*/
UINT16_S gLogicSectionCurSum = 0U;        /*逻辑区段当前总数*/

/*
* 功能描述： 获取逻辑区段管理总数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 逻辑区段当前总数
*/
UINT16_S GetLogicSectionSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gLogicSectionCurSum >= LOGIC_SECTION_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gLogicSectionCurSum;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定数组下标对应的逻辑区段ID
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： 0: 获取数据失败
*			>0: 逻辑区段ID      
*/
UINT16_S GetLogicSectionId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetLogicSectionSum())
	{
		rtnValue = gLogicSectionConfigDataStruBuff[bufIndex].LogicSectionId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID逻辑区段索引号
* 参数说明： const UINT16 logicSectionId,逻辑区段ID
* 返回值  ：  LOGIC_SECTION_SUM_MAX;获取数据失败
*			  >=0U;查找索引成功
*/
UINT16_S GetLogicSectionConfigBufIndex(const UINT16_S logicSectionId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((logicSectionId >= 1U) && (logicSectionId < LOGIC_SECTION_SUM_MAX))
	{
		rtnValue = gLogicSectionIdBuff[logicSectionId];
	}
	else
	{
		rtnValue = LOGIC_SECTION_SUM_MAX;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID站台逻辑区段所属联锁ID
* 参数说明： const UINT16 logicSectionId,逻辑区段ID   
* 返回值  ： 0: 获取数据失败
*			>0: 所属联锁ID      
*/
UINT8_S GetLogicSectionBelongCiId(const UINT16_S logicSectionId)
{
	UINT16_S bufIndex = 0U;          /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*获取数组下标*/
	bufIndex = GetLogicSectionConfigBufIndex(logicSectionId);  

	if (bufIndex < GetLogicSectionSum())
	{
		rtnValue = gLogicSectionConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID逻辑区段所属ZC的ID
* 参数说明： const UINT16 logicSectionId,逻辑区段ID   
* 返回值  ： 0: 获取数据失败
*			>0: 所属ZcID      
*/
UINT8_S GetLogicSectionBelongZcId(const UINT16_S logicSectionId)
{
	UINT16_S bufIndex = 0U;          /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*获取数组下标*/
	bufIndex = GetLogicSectionConfigBufIndex(logicSectionId);  

	if (bufIndex < GetLogicSectionSum())
	{
		rtnValue = gLogicSectionConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID逻辑区段所属计轴区段ID
* 参数说明： const UINT16 logicSectionId,逻辑区段ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT16_S GetLogicSectionBelongAcId(const UINT16_S logicSectionId)
{
	UINT16_S bufIndex = 0U;          /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	/*获取数组下标*/
	bufIndex = GetLogicSectionConfigBufIndex(logicSectionId);  

	if (bufIndex < GetLogicSectionSum())
	{
		rtnValue = gLogicSectionConfigDataStruBuff[bufIndex].BelongAcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
