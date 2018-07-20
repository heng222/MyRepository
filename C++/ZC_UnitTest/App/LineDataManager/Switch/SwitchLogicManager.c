/************************************************************************
*
* 文件名   ：  SwitchLogicManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  道岔逻辑处理管理
* 备  注   ：  无
*
************************************************************************/
#include "SwitchLogicManager.h"
#include "SwitchConfigData.h"
#include "SwitchStatusData.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Convert.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataHandle.h"


/*
* 功能描述： 处理通信故障Ci对应的单个道岔信息
* 参数说明： const UINT16 switchId，道岔ID    
* 返回值  ： void  
*/
void InitFailureSingleSwitch(const UINT16_S switchId)
{
	SetSwitchPosStatus(switchId,SWITCH_STATE_LOSE);
	SetSwitchLock(switchId,SWITCH_STATE_UNLOCK);
}

/*
* 功能描述： 处理通信故障Ci对应的道岔信息
* 参数说明： const UINT16 ciId;通信故障的联锁ID   
* 返回值  ： void  
*/
void InitFailureCiSwitch(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S switchId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetSwitchSum();cycle++)
	{
		switchId = GetSwitchId(cycle);

		if (ciId == GetSwitchBelongCiId(switchId))
		{
			/*本Ci范围内大道岔*/
			InitFailureSingleSwitch(switchId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 处理通信故障NZc对应的道岔信息
* 参数说明： const UINT16 nZcId,相邻ZC    
* 返回值  ： void  
*/
void InitFailureNZcSwitch(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S switchId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetSwitchSum();cycle++)
	{
		switchId = GetSwitchId(cycle);

		if ((nZcId == GetSwitchBelongZcId(switchId))
			&& (FLAG_SET == GetSwitchChangeAttribute(switchId)))
		{
			/*本Ci范围内大道岔*/
			InitFailureSingleSwitch(switchId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 组织给查询函数DMU的本地道岔信息
* 参数说明： void    
* 返回值  ： void  
*/
void SetDmuSwitchStatusInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S indexLength = DEFAULT_ZERO;
	UINT8_S switchStatusBuff[SWITCH_LOCAL_SUM_MAX*3U] = {DEFAULT_ZERO};
	UINT16_S switchId = DEFAULT_ZERO;

	/*初始化*/
	MemorySet(switchStatusBuff,((UINT32_S)(sizeof(UINT8_S)*SWITCH_LOCAL_SUM_MAX*3U)),
                0U,((UINT32_S)(sizeof(UINT8_S)*SWITCH_LOCAL_SUM_MAX*3U)));

	/*组织本地道岔状态信息*/
	for (cycle = DEFAULT_ZERO;cycle < GetSwitchSum();cycle++)
	{
		switchId = GetSwitchId(cycle);

		ShortToChar(switchId,&switchStatusBuff[indexLength]);
		indexLength = indexLength + 2U;

		switchStatusBuff[indexLength] = GetSwitchPosStatus(switchId);
		indexLength = indexLength + 1U;
	}

	UpdateSwitchStatus(switchStatusBuff,indexLength);
}
