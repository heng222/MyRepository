/************************************************************************
*
* 文件名   ：  RouteStatusData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  进路状态管理
* 备  注   ：  无
*
************************************************************************/
#ifndef ROUTE_STATUS_DATA_H_
#define ROUTE_STATUS_DATA_H_


#include "RouteDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*进路状态数据结构体*/
	typedef struct RouteDataStruct
	{
		UINT16_S RouteId;                     /*进路按钮ID*/
		UINT8_S RouteStatus;                  /*进路当前状态*/
        UINT8_S RouteStopReq;                 /* 进路停车保证请求 */
        UINT8_S RouteStopConfirm;             /* 进路停车保证确认*/
	} RouteDataStruct;


	/*
	* 功能描述： 获取进路数据
	* 参数说明： void    
	* 返回值  ： NULL: 获取数据失败
	*			 !NULL: 进路数据
	*/
	RouteDataStruct* GetRouteStatusData(void);

	/*
	* 功能描述： 获取进路当前状态
	* 参数说明： const routeId 进路ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 进路状态
	*/
	UINT8_S GetRouteStatus(const UINT16_S routeId);

	/*
	* 功能描述： 设置进路当前状态
	* 参数说明： const UINT16  routeId 进路ID; 
	*	         UINT8_S routeStatus 进路状态    
	* 返回值  ： 0;失败
	*            1;成功
	*/
	UINT8_S SetRouteStatus(const UINT16_S routeId,UINT8_S routeStatus);

    /*
	* 功能描述： 获取进路停车后保证请求
	* 参数说明： const UINT16_S routeId 进路ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 进路状态
	*/
	UINT8_S GetRouteStopReq(const UINT16_S routeId);

   /*
	* 功能描述： 设置进路停车后保证请求
	* 参数说明： const UINT16_S routeId 进路ID    
    *          const UINT8_S routeStopReq,进路停车保证请求
	* 返回值  ： 0: 失败
	*			1: 成功
	*/
	UINT8_S SetRouteStopReq(const UINT16_S routeId,const UINT8_S routeStopReq);	
	
    /*
	* 功能描述： 获取进路停车后保证确认
	* 参数说明： const UINT16_S routeId 进路ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 进路状态
	*/
	UINT8_S GetRouteStopConfirm(const UINT16_S routeId);

   /*
	* 功能描述： 设置进路停车后保证确认
	* 参数说明： const UINT16_S routeId 进路ID    
    *          const UINT8_S routeStopConfirm,进路停车保证确认
	* 返回值  ： 0: 失败
	*			1: 成功
	*/
	UINT8_S SetRouteStopConfirm(const UINT16_S routeId,const UINT8_S routeStopConfirm);	
	

#ifdef __cplusplus
}
#endif

#endif
