/************************************************************************
*
* 文件名   ：  RouteConfigData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  进路配置数据管理
* 备  注   ：  无
*
************************************************************************/
#include "RouteConfigData.h"

RouteConfigDataStruct gRouteConfigDataStruBuff[ROUTE_LOCAL_SUM_MAX];                  /*本地管理的进路配置信息*/
UINT16_S gRouteIdBuff[ROUTE_SUM_MAX] = {0U};                                          /*定义进路映射数组*/
UINT16_S gRouteCurSum = 0U;                                                          /*进路当前总数*/

/*
* 功能描述： 获取进路管理总数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 进路当前总数
*/
UINT16_S GetRouteSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gRouteCurSum >= ROUTE_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gRouteCurSum;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定数组下标对应的进路ID
* 参数说明： const UINT16 bufIndex, 数组下标    
* 返回值  ： 0: 获取数据失败
*			>0: 进路ID      
*/
UINT16_S GetRouteId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].RouteId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID进路索引号
* 参数说明： const UINT16 routeId,进路ID
* 返回值  ：  ROUTE_SUM_MAX;获取数据失败
*			  >=0U;查找索引成功
*/
UINT16_S GetRouteConfigBufIndex(const UINT16_S routeId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((routeId >= 1U)&&(routeId < ROUTE_SUM_MAX))
	{
		rtnValue = gRouteIdBuff[routeId];
	}
	else
	{
		rtnValue = ROUTE_SUM_MAX;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID站台进路所属联锁ID
* 参数说明： const UINT16 routeId,进路ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属联锁ID      
*/
UINT8_S GetRouteBelongCiId(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID进路所属ZC的ID
* 参数说明： const UINT16 psbId, 进路ID    
* 返回值  ： 0: 获取数据失败
*			>0: 所属ZcID      
*/
UINT8_S GetRouteBelongZcId(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID进路共管区域属性
* 参数说明： const UINT16 routeId, 进路ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT16_S GetRouteChangeAttribute(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID进路类型
* 参数说明： const UINT16 routeId, 进路ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetRouteType(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].RouteType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID进路区域类型
* 参数说明： const UINT16 routeId, 进路ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetRouteAreaType(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].RouteAreaType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定进路Id的防护信号机Id
* 参数说明： const UINT16 routeId, 进路ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT16_S GetRouteOfSingalId(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].RouteSingalId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID进路内保护区段数量
* 参数说明： const UINT16 routeId, 进路ID     
* 返回值  ： DEFAULT_UINT8_VALUE: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetRouteOfOverlapNum(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].OverlapNum;
	}
	else
	{
		rtnValue = DEFAULT_UINT8_VALUE;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID进路内保护区段Idbuff
* 参数说明： const UINT16 routeId, 进路ID   
*			 UINT8_S bufSize,输出数组大小，
*            UINT16_S overlapIdBuff[],输出数组
* 返回值  ： RETURN_ERROR: 获取数据失败
*			RETURN_SUCCESS: 获取成功      
*/
UINT8_S GetRoutOfOverlapIdBuff(const UINT16_S routeId,UINT8_S bufSize,UINT16_S overlapIdBuff[])
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;   
    UINT8_S routeOfOverlapNum = DEFAULT_UINT8_VALUE;  /* 进路包含保护区段数量 */

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if ((bufIndex < GetRouteSum())
		&& (bufSize >= ROUTE_OF_OVERLAP_SUM_MAX)
		&& (overlapIdBuff != NULL))
	{
        routeOfOverlapNum = GetRouteOfOverlapNum(routeId);

        if(DEFAULT_UINT8_VALUE == routeOfOverlapNum)
        {
            rtnValue = RETURN_ERROR;
        }
        else
        {
            for (cycle = 0U; cycle < routeOfOverlapNum; cycle++)
            {
                overlapIdBuff[cycle] = gRouteConfigDataStruBuff[bufIndex].OverlapIdBuff[cycle];
            }
            rtnValue = RETURN_SUCCESS;
        } 		
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
	
/*
* 功能描述： 获取指定ID进路内计轴区段数量
* 参数说明： const UINT16 routeId, 进路ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetRouteOfAcNum(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].AcNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定id进路内指定下标的计轴区段Id
* 参数说明： const UINT16 routeId, 进路ID   
*			 UINT8_S index,查询下标
*            UINT16_S *outAcId,输出计轴区段ID
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 获取成功      
*/
UINT8_S GetRoutOfAcIdFromIndex(const UINT16_S routeId,UINT8_S index,UINT16_S *outAcId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	if (NULL != outAcId)
	{
		bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/
		*outAcId = DEFAULT_ZERO;

		if ((bufIndex < GetRouteSum())
			&& (index < GetRouteOfAcNum(routeId)))
		{
			*outAcId = gRouteConfigDataStruBuff[bufIndex].AcIdBuff[index];
			rtnValue = RETURN_SUCCESS;
		}
		else
		{
			rtnValue = RETURN_ERROR;
		}
	}
	return rtnValue;
}

/*
* 功能描述： 获取指定ID进路内计轴区段buff
* 参数说明： const UINT16 routeId, 进路ID   
*			 UINT8_S bufSize,输出数组大小，
*            UINT16_S acIdBuff[],输出数组
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 RETURN_SUCCESS: 获取成功      
*/
UINT8_S GetRoutOfAcIdBuff(const UINT16_S routeId,UINT8_S bufSize,UINT16_S acIdBuff[])
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if ((bufIndex < GetRouteSum())
		&& (bufSize >= ROUTE_OF_AC_SUM_MAX)
		&& (acIdBuff != NULL))
	{
		for (cycle = 0U; cycle < GetRouteOfAcNum(routeId); cycle++)
		{
			acIdBuff[cycle] = gRouteConfigDataStruBuff[bufIndex].AcIdBuff[cycle];
		}
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID进路内障碍物数量
* 参数说明： const UINT16 routeId, 进路ID     
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT16_S GetRouteOfObsNum(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].ObsNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定ID进路内障碍物信息
* 参数说明： const UINT16 routeId, 进路ID   
*            const UINT8_S bufSize,数组大小
*            RouteObsStruct routeObsStruBuff[],输出数组
* 返回值  ： 0: 获取数据失败
*			>0: 获取成功      
*/
UINT8_S GetRoutepObsStruBuff(const UINT16_S routeId,const UINT8_S bufSize,RouteObsStruct routeObsStruBuff[])
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

	if ((bufIndex < GetRouteSum())
		&& (bufSize >= ROUTE_OF_OBS_SUM_MAX)
		&& (routeObsStruBuff != NULL))
	{
		for (cycle = 0U; cycle < GetRouteOfObsNum(routeId); cycle++)
		{
			routeObsStruBuff[cycle].ObsId = gRouteConfigDataStruBuff[bufIndex].RouteObsStruBuff[cycle].ObsId;
			routeObsStruBuff[cycle].ObsType = gRouteConfigDataStruBuff[bufIndex].RouteObsStruBuff[cycle].ObsType;
		}
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 获取指定进路最后一个计轴区段
* 参数说明： const UINT16 routeId, 进路ID   
*            UINT16_S *acId, 计轴区段ID（输出）
* 返回值  ： 0: 获取失败
*			 1: 获取成功
*/
UINT8_S GetRouteLastAcId(const UINT16_S routeId,UINT16_S *acId)
{
	UINT16_S bufIndex = 0U;     /*数组下标*/
	UINT8_S acNumOfRoute = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*获取数组下标*/

    if (NULL != acId)
    {
        if (bufIndex < GetRouteSum())
        {
            acNumOfRoute = gRouteConfigDataStruBuff[bufIndex].AcNum;

            if (ROUTE_OF_AC_SUM_MAX >= acNumOfRoute)
            {
                (*acId) = gRouteConfigDataStruBuff[bufIndex].AcIdBuff[acNumOfRoute - 1U];
                rtnValue = RETURN_SUCCESS;
            } 
            else
            {
                (*acId) = 0U;
                rtnValue = RETURN_ERROR;
            }
        }
        else
        {
            (*acId) = 0U;
            rtnValue = RETURN_ERROR;
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
	
	return rtnValue;
}
