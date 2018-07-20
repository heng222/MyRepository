/************************************************************************
*
* 文件名   ：  RouteLogicManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  进路逻辑处理管理
* 备  注   ：  无
*
************************************************************************/
#include "RouteLogicManager.h"
#include "RouteConfigData.h"
#include "RouteStatusData.h"

/*
* 功能描述： 处理通信故障Ci对应的单个进路信息
* 参数说明： const UINT16 routeId，进路ID    
* 返回值  ： void  
*/
void InitFailureSingleRoute(const UINT16_S routeId)
{
	SetRouteStatus(routeId,ROUTE_STATE_UNSET);
}

/*
* 功能描述： 处理通信故障Ci对应的进路信息
* 参数说明： const UINT16 ciId，通信故障的CIID    
* 返回值  ： void  
*/
void InitFailureCiRoute(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S routeId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetRouteSum();cycle++)
	{
		routeId = GetRouteId(cycle);

		if (ciId == GetRouteBelongCiId(routeId))
		{
			/*设置状态为安全态*/
			InitFailureSingleRoute(routeId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 处理通信故障NZc对应的进路信息
* 参数说明： const UINT16 nZcId，通信故障的nZcId    
* 返回值  ： void  
*/
void InitFailureNZcRoute(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S routeId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetRouteSum();cycle++)
	{
		routeId = GetRouteId(cycle);

		if ((nZcId == GetRouteBelongZcId(routeId))
			&& (FLAG_SET == GetRouteChangeAttribute(routeId)))
		{
			/*设置状态为安全态*/
			InitFailureSingleRoute(routeId);
		} 
		else
		{
            /*不处理*/
		}
	}
}
