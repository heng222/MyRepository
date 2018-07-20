/************************************************************************
*
* 文件名   ：  SwitchInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  道岔初始化管理
* 备  注   ：  无
*
************************************************************************/
#include "SwitchConfigData.h"
#include "SwitchInitManager.h"
#include "SwitchStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/SwitchData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern SwitchConfigDataStruct gSwitchConfigDataStruBuff[SWITCH_LOCAL_SUM_MAX];             /*引用本地管理的道岔信息*/
extern UINT16_S gSwitchIdBuff[SWITCH_SUM_MAX];                                      /*引用道岔映射数组*/
extern UINT16_S gSwitchCurSum;                                                       /*引用道岔当前总数*/
extern SwitchDataStruct gSwitchStatusDataStruBuff[SWITCH_LOCAL_SUM_MAX];                         /*引用本地管理的道岔状态信息*/

/*
* 功能描述： 初始化本地管理的道岔初始信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitSwitchInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gSwitchCurSum = 0U;

	/*初始化全局变量*/
	for (cycle = DEFAULT_ZERO;cycle < SWITCH_SUM_MAX;cycle++)
	{
		gSwitchIdBuff[cycle] = SWITCH_SUM_MAX;
	}

	/*状态安全侧处理*/
	for (cycle = DEFAULT_ZERO;cycle < SWITCH_LOCAL_SUM_MAX;cycle++)
	{
		gSwitchStatusDataStruBuff[cycle].SwitchLock = SWITCH_STATE_UNLOCK;

		gSwitchStatusDataStruBuff[cycle].SwitchPosStatus = SWITCH_STATE_LOSE;
	}
}

/*
* 功能描述： 初始化本地管理的道岔信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitSwitchLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineSwitchMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*初始化数量*/
	InitSwitchInitializationData();

	lineSwitchMaxId = GetLineSwitchMaxId();

	if (SWITCH_SUM_MAX >= lineSwitchMaxId)
	{
		for (cycle = 1U; cycle <= lineSwitchMaxId;cycle++)
		{
			/*判断该Id是否属于切换区域*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_POINT);

			/*判断该Id是否属于本ZC*/
			belongZcId = GetLineSwitchBelongZcId(cycle);

			if ((belongZcId == GetLocalZcId()) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gSwitchConfigDataStruBuff[addIndex].SwitchId = cycle;
				gSwitchConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gSwitchConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLineSwitchBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gSwitchConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gSwitchConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}
				gSwitchConfigDataStruBuff[addIndex].SwitchPosition = GetLineSwitchPosition(cycle);


				/*设置ID映射数组*/
				gSwitchIdBuff[cycle] = addIndex;

				/*填写状态对应的ID信息*/
				gSwitchStatusDataStruBuff[addIndex].SwitchId = cycle;

				gSwitchCurSum++;
				addIndex++;
				
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
	
	return rtnValue;
}
