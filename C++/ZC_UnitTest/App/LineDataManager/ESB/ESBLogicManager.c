/************************************************************************
*
* 文件名   ：  ESBLogicManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  紧急停车按钮逻辑处理
* 备  注   ：  无
*
************************************************************************/
#include "ESBConfigData.h"
#include "ESBLogicManager.h"
#include "ESBStatusData.h"

/*
* 功能描述： 处理故障对应的单个ESB信息
* 参数说明： const UINT16 esbId，ESBID    
* 返回值  ： void  
*/
void InitFailureSingleEsb(const UINT16_S esbId)
{
	SetEsbStatus(esbId,ESB_STATE_DOWN);
}

/*
* 功能描述： 处理通信故障Ci对应的紧急停车按钮信息
* 参数说明： const UINT16 ciId，通信故障的CIID    
* 返回值  ： void  
*/
void InitFailureCiEsb(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S esbId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetEsbSum();cycle++)
	{
		esbId = GetEsbId(cycle);

		if (ciId == GetEsbBelongCiId(esbId))
		{
			/*设置状态为安全态*/
			InitFailureSingleEsb(esbId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 处理通信故障ZC对应的紧急停车按钮信息
* 参数说明： const UINT16 nZcId，通信故障的nZcID    
* 返回值  ： void  
*/
void InitFailureNZcEsb(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S esbId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetEsbSum();cycle++)
	{
		esbId = GetEsbId(cycle);

		if ((nZcId == GetEsbBelongZcId(esbId))
			&& (FLAG_SET == GetEsbChangeAttribute(esbId)))
		{
			/*设置状态为安全态*/
			InitFailureSingleEsb(esbId);
		} 
		else
		{
            /*不处理*/
		}
	}
}
