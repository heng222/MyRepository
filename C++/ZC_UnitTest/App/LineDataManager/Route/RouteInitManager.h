/************************************************************************
*
* 文件名   ：  RouteInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  进路初始化管理
* 备  注   ：  无
*
************************************************************************/

#ifndef ROUTE_INIT_MANAGER_H_
#define ROUTE_INIT_MANAGER_H_


#include "RouteDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化本地管理的进路初始信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitRouteInitializationData(void);

	/*
	* 功能描述： 初始化本地管理的进路信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitRouteLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
