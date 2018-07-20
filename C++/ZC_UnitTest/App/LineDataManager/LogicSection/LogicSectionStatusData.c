/************************************************************************
*
* 文件名   ：  LogicSectionStatusData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  逻辑区段状态管理
* 备  注   ：  无
*
************************************************************************/
#include "LogicSectionConfigData.h"
#include "LogicSectionStatusData.h"

LogicSectionStruct gLogicSectionDataStruBuff[LOGIC_SECTION_LOCAL_SUM_MAX];             /*定义本地管理的逻辑区段状态数据数组*/

/*
* 功能描述： 获取逻辑区段数据
* 参数说明： void    
* 返回值  ： NULL: 获取数据失败
*			 !NULL: 逻辑区段数据
*/
LogicSectionStruct* GetLogicSectionStatusData(void)
{
	return gLogicSectionDataStruBuff;
}

/*
* 功能描述： 获取逻辑区段当前状态
* 参数说明： const UINT16 logicSectionId 逻辑区段ID    
* 返回值  ： 0: 获取数据失败
*			>0: 逻辑区段状态
*/
UINT8_S GetLogicSectionOccStatus(const UINT16_S logicSectionId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetLogicSectionConfigBufIndex(logicSectionId);  /*获取数组下标*/

	if (bufIndex < GetLogicSectionSum())
	{
		rtnValue = gLogicSectionDataStruBuff[bufIndex].LogicSectionOccStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置逻辑区段当前状态
* 参数说明： const UINT16  logicSectionId 逻辑区段ID; 
*	         UINT8_S logicSectionStatus 逻辑区段状态    
* 返回值  ： 0;失败
*            1;成功
*/
UINT8_S SetLogicSectionOccStatus(const UINT16_S logicSectionId,UINT8_S logicSectionStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetLogicSectionConfigBufIndex(logicSectionId);  /*获取数组下标*/

	if (bufIndex < GetLogicSectionSum())
	{
		if ((LOGIC_SECTION_STATE_UT == logicSectionStatus)
			|| (LOGIC_SECTION_STATE_CT == logicSectionStatus)
			|| (LOGIC_SECTION_STATE_FREE == logicSectionStatus))
		{
			gLogicSectionDataStruBuff[bufIndex].LogicSectionOccStatus = logicSectionStatus;
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
