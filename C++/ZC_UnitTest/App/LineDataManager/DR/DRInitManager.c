/************************************************************************
*
* 文件名   ：  DRInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  无人折返初始化管理
* 备  注   ：  无
*
************************************************************************/
#include "DRConfigData.h"
#include "DRInitManager.h"
#include "DRStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Dmu/DmuComm/Data/ArData.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern DRButtonConfigDataStruct gDRButtonConfigDataStruBuff[DR_BUTTON_LOCAL_SUM_MAX];     /*引用无人折返按钮数据配置结构体*/
extern UINT16_S gDRButtonIdBuff[DR_BUTTON_SUM_MAX];                                      /*引用无人折返按钮ID映射数组*/
extern UINT16_S gDRButtonCurSum;                                                        /*引用无人折返按钮当前总数*/

extern DRLampConfigDataStruct gDRLampConfigDataStruBuff[DR_LAMP_LOCAL_SUM_MAX];           /*引用无人折返按钮数据配置结构体*/
extern UINT16_S gDRLampIdBuff[DR_LAMP_SUM_MAX];                                          /*引用无人折返按钮ID映射数组*/
extern UINT16_S gDRLampCurSum;                                                          /*引用无人折返按钮当前总数*/

extern DRButtonDataStruct  gDRButtonDataStruBuff[DR_BUTTON_LOCAL_SUM_MAX];                /*引用无人折返按钮状态数据结构体*/
extern DRLampDataStruct gDRLampDataStruBuff[DR_LAMP_LOCAL_SUM_MAX];                       /*引用无人折返按钮状态数据结构体*/

/*
* 功能描述： 初始化本地管理的无人折返按钮初始信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitDrButtonInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gDRButtonCurSum = 0U;

	/*初始化全局变量*/
	for (cycle = DEFAULT_ZERO;cycle < DR_BUTTON_SUM_MAX;cycle++)
	{
		gDRButtonIdBuff[cycle] = DR_BUTTON_SUM_MAX;
	}

	/*设备安全态处理*/
	for (cycle = DEFAULT_ZERO;cycle < DR_BUTTON_LOCAL_SUM_MAX;cycle++)
	{
		gDRButtonDataStruBuff[cycle].DRButtonStatus = DR_BUTTON_STATE_UP;
		gDRLampDataStruBuff[cycle].DRLampCmd = DR_LAMP_DEFAULT_STATUS;
	}
}

/*
* 功能描述： 初始化本地管理的无人折返灯初始信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitDrLampInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gDRLampCurSum = 0U;

	/*初始化全局变量*/
	for (cycle = DEFAULT_ZERO;cycle < DR_LAMP_SUM_MAX;cycle++)
	{
		gDRLampIdBuff[cycle] = DR_LAMP_SUM_MAX;
	}
}


/*
* 功能描述： 初始化本地管理的无人折返按钮信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitDrButtonLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineDrButtonMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*初始化数量*/
	InitDrButtonInitializationData();

	lineDrButtonMaxId = GetLineDrButtonMaxId();

	if (DR_BUTTON_SUM_MAX >= lineDrButtonMaxId)
	{
		for (cycle = 1U; cycle <= lineDrButtonMaxId;cycle++)
		{
			/*判断该Id对应的无人折返按钮是否属于切换区域*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_DRB);

			/*判断该Id对应的无人折返按钮是否属于本ZC*/
			belongZcId = GetLineDrButtonBelongZcId(cycle);

			if ((belongZcId == GetLocalZcId()) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gDRButtonConfigDataStruBuff[addIndex].DRButtonId = cycle;
				gDRButtonConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gDRButtonConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLineDrButtonBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gDRButtonConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gDRButtonConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				/*设置ID映射数组*/
				gDRButtonIdBuff[cycle] = addIndex;

				/*填写状态对应的ID信息*/
				gDRButtonDataStruBuff[addIndex].DRButtonId = cycle;

				gDRButtonCurSum++;
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

/*
* 功能描述： 初始化本地管理的无人折返灯信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitDrLampLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineDrLampMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*初始化数量*/
	InitDrLampInitializationData();

	lineDrLampMaxId = GetLineDrLampMaxId();

	if (DR_LAMP_SUM_MAX >= lineDrLampMaxId)
	{
		for (cycle = 1U; cycle <= lineDrLampMaxId;cycle++)
		{
			/*判断该Id对应的无人折返按钮是否属于切换区域*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_DRL);

			/*判断该Id对应的无人折返按钮是否属于本ZC*/
			belongZcId = GetLineDrLampBelongZcId(cycle);

			if ((belongZcId != GetLocalZcId()) && (RETURN_ERROR == rtnOfChangeArea))
			{
				/*不属于本ZC管辖范围或者切换区域内的障碍物*/
			} 
			else
			{
				gDRLampConfigDataStruBuff[addIndex].DRLampId = cycle;
				gDRLampConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gDRLampConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLineDrLampBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gDRLampConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gDRLampConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				/*设置ID映射数组*/
				gDRLampIdBuff[cycle] = addIndex;

				/*填写状态对应的ID信息*/
				gDRLampDataStruBuff[addIndex].DRLampId = cycle;

				gDRLampCurSum++;
				addIndex++;
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
