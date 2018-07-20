/************************************************************************
*
* 文件名   ：  RouteInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  进路初始化管理
* 备  注   ：  无
*
************************************************************************/

#include "RouteConfigData.h"
#include "RouteInitManager.h"
#include "RouteStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/RouteData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern RouteConfigDataStruct gRouteConfigDataStruBuff[ROUTE_LOCAL_SUM_MAX];          /*引用本地管理的进路配置信息*/
extern UINT16_S gRouteIdBuff[ROUTE_SUM_MAX];                                        /*引用进路映射数组*/
extern UINT16_S gRouteCurSum;                                                      /*引用进路当前总数*/
extern RouteDataStruct gRouteStatusDataStruBuff[ROUTE_LOCAL_SUM_MAX];                /*引用本地管理的进路状态信息*/

/*
* 功能描述： 初始化本地管理的进路初始信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitRouteInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gRouteCurSum = DEFAULT_ZERO;

	/*初始化全局变量*/
	for (cycle = DEFAULT_ZERO;cycle < ROUTE_SUM_MAX;cycle++)
	{
		gRouteIdBuff[cycle] = ROUTE_SUM_MAX;
	}

	/*状态安全侧处理*/
	for (cycle = DEFAULT_ZERO;cycle < ROUTE_LOCAL_SUM_MAX;cycle++)
	{
		gRouteStatusDataStruBuff[cycle].RouteStatus = ROUTE_STATE_UNSET;
	}
}

/*
* 功能描述： 初始化本地管理的进路信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitRouteLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineRouteMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S acNumOfRoute = DEFAULT_ZERO;
	UINT8_S obsNumOfRoute = DEFAULT_ZERO;
	UINT16_S acIdBuff[ROUTE_OF_AC_SUM_MAX] = {DEFAULT_ZERO};
	UINT16_S obsIdBuff[ROUTE_OF_OBS_SUM_MAX * 2U] = {DEFAULT_ZERO};
	UINT8_S cycleOfAc = DEFAULT_ZERO;
	UINT8_S cycleOfObs = DEFAULT_ZERO;
	UINT8_S index = DEFAULT_ZERO;
	UINT8_S overlapNum = DEFAULT_ZERO;
	UINT8_S cycleOfOverlap = DEFAULT_ZERO;
	UINT16_S overlapIdBuff[ROUTE_OF_OVERLAP_SUM_MAX] = {DEFAULT_ZERO};
    UINT16_S localZcId = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;

	/*初始化数量*/
	MemorySet(&acIdBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)));
	MemorySet(&obsIdBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_OBS_SUM_MAX*2U)),
                 0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_OBS_SUM_MAX*2U)));
	MemorySet(&overlapIdBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_OVERLAP_SUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_OVERLAP_SUM_MAX)));

	InitRouteInitializationData();

	lineRouteMaxId = GetLineRouteMaxId();

	if (ROUTE_SUM_MAX >= lineRouteMaxId)
	{
		for (cycle = 1U; cycle <= lineRouteMaxId;cycle++)
		{
			/*判断该Id是否属于切换区域*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_ROUTE);

			/*判断该Id是否属于本ZC*/
			belongZcId = GetLineRouteBelongZcId(cycle);
            localZcId = GetLocalZcId();
                 
			if ((belongZcId == localZcId) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				if (addIndex < ROUTE_LOCAL_SUM_MAX)
				{
					gRouteConfigDataStruBuff[addIndex].RouteId = cycle;
					gRouteConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)belongZcId;
					gRouteConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)GetRouteDataStrumanageCI(cycle);
					gRouteConfigDataStruBuff[addIndex].RouteSingalId = (UINT8_S)(GetRouteDataStrustartSignalId(cycle));

					if (belongZcId == GetLocalZcId())
					{
						gRouteConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
					}
					else
					{
						gRouteConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
					}

					gRouteConfigDataStruBuff[addIndex].RouteType = (UINT8_S)GetRouteDataStrurouteType(cycle);
					gRouteConfigDataStruBuff[addIndex].RouteAreaType = GetLineRouteAreaType(cycle);

					/*获取进路包含的保护区段信息*/
					overlapNum = (UINT8_S)(GetLineRouteOfOverlapInfo(cycle, overlapIdBuff));

					if ((overlapNum > 0U) && (overlapNum <= ROUTE_OF_OVERLAP_SUM_MAX))
					{
						gRouteConfigDataStruBuff[addIndex].OverlapNum = overlapNum;

						for (cycleOfOverlap = DEFAULT_ZERO; cycleOfOverlap < overlapNum; cycleOfOverlap++)
						{
							gRouteConfigDataStruBuff[addIndex].OverlapIdBuff[cycleOfOverlap] = overlapIdBuff[cycleOfOverlap];
						}
					}
					else
					{
						/*不处理*/
					}

					/*获取进路关联的计轴区段信息*/
					acNumOfRoute = (UINT8_S)(GetLineRouteOfAcInfo(cycle, acIdBuff));

					if ((acNumOfRoute > 0U) && (acNumOfRoute <= ROUTE_OF_AC_SUM_MAX))
					{
						gRouteConfigDataStruBuff[addIndex].AcNum = acNumOfRoute;

						for (cycleOfAc = DEFAULT_ZERO; cycleOfAc < acNumOfRoute; cycleOfAc++)
						{
							gRouteConfigDataStruBuff[addIndex].AcIdBuff[cycleOfAc] = acIdBuff[cycleOfAc];
						}
					}
					else
					{
						/*不处理*/
					}

					/*获取进路关联的障碍物信息*/
					obsNumOfRoute = (UINT8_S)(GetLineRouteOfObsInfo(cycle, obsIdBuff));

					/*初始化*/
					index = DEFAULT_ZERO;

					if ((obsNumOfRoute > 0U) && (obsNumOfRoute <= ROUTE_OF_OBS_SUM_MAX))
					{
						gRouteConfigDataStruBuff[addIndex].ObsNum = obsNumOfRoute;

						for (cycleOfObs = DEFAULT_ZERO; cycleOfObs < obsNumOfRoute; cycleOfObs++)
						{
							gRouteConfigDataStruBuff[addIndex].RouteObsStruBuff[cycleOfObs].ObsId = obsIdBuff[index];
							index = index + 1U;

							gRouteConfigDataStruBuff[addIndex].RouteObsStruBuff[cycleOfObs].ObsType = (UINT8_S)obsIdBuff[index];
							index = index + 1U;
						}
					}
					else
					{
						/*不处理*/
					}

					/*设置ID映射数组*/
					gRouteIdBuff[cycle] = addIndex;

					/*填写状态对应的ID信息*/
					gRouteStatusDataStruBuff[addIndex].RouteId = cycle;

					gRouteCurSum++;
					addIndex++;
				}
				else
				{
					breakFlag = FLAG_SET;
					break;
				}
			} 
			else
			{
				/*不属于本ZC管辖范围或者切换区域内的障碍物*/
			}
		}

		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}
	
	if (FLAG_SET == breakFlag)
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
