/************************************************************************
*
* 文件名   ：  PSDLogicManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  屏蔽门逻辑处理
* 备  注   ：  无
*
************************************************************************/
#include "PSDConfigData.h"
#include "PSDStatusData.h"
#include "PSDLogicManager.h"


/*
* 功能描述： 处理通信故障Ci对应的单个屏蔽门信息
* 参数说明： const UINT16 psdId，屏蔽门ID    
* 返回值  ： void  
*/
void InitFailureSinglePsd(const UINT16_S psdId)
{
	SetPsdStatus(psdId,PSD_STATE_OPEN);
}

/*
* 功能描述： 处理通信故障Ci对应的屏蔽门信息
* 参数说明： const UINT16 ciId，通信故障的屏蔽门ID    
* 返回值  ： void  
*/
void InitFailureCiPsd(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S psdId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetPsdSum();cycle++)
	{
		psdId = GetPsdId(cycle);

		if (ciId == GetPsdBelongCiId(psdId))
		{
			/*设置状态为安全态*/
			InitFailureSinglePsd(psdId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 处理通信故障Ci对应的屏蔽门信息
* 参数说明： const UINT16 nZcId，通信故障的相邻ZcID    
* 返回值  ： void  
*/
void InitFailureNZcPsd(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S psdId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetPsdSum();cycle++)
	{
		psdId = GetPsdId(cycle);

		if ((nZcId == GetPsdBelongZcId(psdId))
			&& (FLAG_SET == GetPsdChangeAttribute(psdId)))
		{
			/*设置状态为安全态*/
			InitFailureSinglePsd(psdId);
		} 
		else
		{
            /*不处理*/
		}
	}
}
