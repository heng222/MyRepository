/************************************************************************
*
* 文件名   ：  RouteStatusData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  进路状态管理
* 备  注   ：  无
*
************************************************************************/
#include "RouteStatusData.h"
#include "RouteConfigData.h"

RouteDataStruct gRouteStatusDataStruBuff[ROUTE_LOCAL_SUM_MAX];          /*本地管理的保护区段状态信息*/

/*
* 功能描述： 获取进路数据
* 参数说明： void    
* 返回值  ： NULL: 获取数据失败
*			 !NULL: 进路数据
*/
RouteDataStruct* GetRouteStatusData(void)
{
	return gRouteStatusDataStruBuff;
}

/*
* 功能描述： 获取进路当前状态
* 参数说明： const routeId 进路ID    
* 返回值  ： 0: 获取数据失败
*			>0: 进路状态
*/
UINT8_S GetRouteStatus(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteStatusDataStruBuff[bufIndex].RouteStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 设置进路当前状态
* 参数说明： const UINT16  routeId 进路ID; 
*	         UINT8_S routeStatus 进路状态    
* 返回值  ： 0;失败
*            1;成功
*/
UINT8_S SetRouteStatus(const UINT16_S routeId,UINT8_S routeStatus)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		if ((ROUTE_STATE_SET == routeStatus) || (ROUTE_STATE_UNSET == routeStatus))
		{
			gRouteStatusDataStruBuff[bufIndex].RouteStatus = routeStatus;
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

/*
* 功能描述： 获取进路停车后保证请求
* 参数说明： const UINT16_S routeId 进路ID    
* 返回值  ： 0: 获取数据失败
*			>0: 进路状态
*/
UINT8_S GetRouteStopReq(const UINT16_S routeId)
{

    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

    if (bufIndex < GetRouteSum())
    {
        rtnValue = gRouteStatusDataStruBuff[bufIndex].RouteStopReq;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* 功能描述： 设置进路停车后保证请求
* 参数说明： const UINT16_S routeId 进路ID    
*          const UINT8_S routeStopReq,进路停车保证请求
* 返回值  ： 0: 失败
*			1: 成功
*/
UINT8_S SetRouteStopReq(const UINT16_S routeId,const UINT8_S routeStopReq)	
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

    if (bufIndex < GetRouteSum())
    {
        if ((ROUTE_STOP_REQ_SET == routeStopReq) || (ROUTE_STOP_REQ_UNSET == routeStopReq))
        {
            gRouteStatusDataStruBuff[bufIndex].RouteStopReq = routeStopReq;
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


/*
* 功能描述： 获取进路停车后保证确认
* 参数说明： const UINT16_S routeId 进路ID    
* 返回值  ： 0: 获取数据失败
*			>0: 进路状态
*/
UINT8_S GetRouteStopConfirm(const UINT16_S routeId)
{

    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

    if (bufIndex < GetRouteSum())
    {
        rtnValue = gRouteStatusDataStruBuff[bufIndex].RouteStopConfirm;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* 功能描述： 设置进路停车后保证确认
* 参数说明： const UINT16_S routeId 进路ID    
*          const UINT8_S routeStopConfirm,进路停车保证确认
* 返回值  ： 0: 失败
*			1: 成功
*/
UINT8_S SetRouteStopConfirm(const UINT16_S routeId,const UINT8_S routeStopConfirm)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

    if (bufIndex < GetRouteSum())
    {
        if ((ROUTE_STOP_CONFIRM_SET == routeStopConfirm) || (ROUTE_STOP_CONFIRM_UNSET == routeStopConfirm))
        {
            gRouteStatusDataStruBuff[bufIndex].RouteStopConfirm = routeStopConfirm;
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