/************************************************************************
*
* 文件名   ：  DRLogicManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  无人折返逻辑处理
* 备  注   ：  无
*
************************************************************************/
#include "DRLogicManager.h"
#include "DRStatusData.h"
#include "DRConfigData.h"

/*
* 功能描述： 处理故障对应的单个无人折返按钮信息
* 参数说明： const UINT16 drButtonId，无人折返按钮ID    
* 返回值  ： void  
*/
void InitFailureSingleDrButton(const UINT16_S drButtonId)
{
	SetDRButtonStatus(drButtonId,DR_BUTTON_STATE_UP);
}

/*
* 功能描述： 处理通信故障Ci对应的无人折返按钮信息
* 参数说明： const UINT16 ciId，通信故障的CIID    
* 返回值  ： void  
*/
void InitFailureCiDrButoon(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S drButtonId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO; cycle < GetDRButtonSum();cycle++)
	{
		drButtonId = GetDRButtonId(cycle);

		if (GetDRButtonBelongCiId(drButtonId) == ciId)
		{
			InitFailureSingleDrButton(drButtonId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 处理通信故障ZC对应的无人折返按钮信息
* 参数说明： const UINT16 nZcId，通信故障的nZcID    
* 返回值  ： void  
*/
void InitFailureNZcDrButton(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S drButtonId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO; cycle < GetDRButtonSum();cycle++)
	{
		drButtonId = GetDRButtonId(cycle);

		if (GetDRButtonBelongZcId(drButtonId) == nZcId)
		{
			InitFailureSingleDrButton(drButtonId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 处理故障对应的单个无人折返灯信息
* 参数说明： const UINT16 drLampId，无人折返灯ID    
* 返回值  ： void  
*/
void InitFailureSingleDrLamp(const UINT16_S drLampId)
{
	SetDRLampCommand(drLampId,DR_LAMP_DEFAULT_STATUS);
	SetDRLampOfTrainId(drLampId,DEFAULT_ZERO);
}

/*
* 功能描述： 处理通信故障Ci对应的无人折返灯信息
* 参数说明： const UINT16 ciId，通信故障的CIID    
* 返回值  ： void  
*/
void InitFailureCiDrLamp(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S drLampId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO; cycle < GetDRLampSum();cycle++)
	{
		drLampId = GetDRLampId(cycle);

		if (GetDRLampBelongCiId(drLampId) == ciId)
		{
			InitFailureSingleDrLamp(drLampId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 处理通信故障ZC对应的无人折返灯信息
* 参数说明： const UINT16 nZcId，通信故障的nZcID    
* 返回值  ： void  
*/
void InitFailureNZcDrLamp(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S drLampId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO; cycle < GetDRLampSum();cycle++)
	{
		drLampId = GetDRLampId(cycle);

		if (GetDRLampBelongZcId(drLampId) == nZcId)
		{
			InitFailureSingleDrLamp(drLampId);
		} 
		else
		{
            /*不处理*/
		}
	}
}
