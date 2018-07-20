/************************************************************************
*
* 文件名   ：  RouteLogicManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  进路逻辑处理管理
* 备  注   ：  无
*
************************************************************************/
#ifndef ROUTE_LOGIC_MANAGER_H_
#define ROUTE_LOGIC_MANAGER_H_


#include "RouteDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 处理通信故障Ci对应的单个进路信息
	* 参数说明： const UINT16 routeId，进路ID    
	* 返回值  ： void  
	*/
	void InitFailureSingleRoute(const UINT16_S routeId);

	/*
	* 功能描述： 处理通信故障Ci对应的进路信息
	* 参数说明： const UINT16 ciId，通信故障的CIID    
	* 返回值  ： void  
	*/
	void InitFailureCiRoute(const UINT16_S ciId);

	/*
	* 功能描述： 处理通信故障NZc对应的进路信息
	* 参数说明： const UINT16 nZcId，通信故障的nZcId    
	* 返回值  ： void  
	*/
	void InitFailureNZcRoute(const UINT16_S nZcId);

#ifdef __cplusplus
}
#endif

#endif
