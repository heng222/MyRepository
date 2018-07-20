/************************************************************************
*
* 文件名   ：  PSDInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  屏蔽门初始化管理
* 备  注   ：  无
*
************************************************************************/
#include "PSDConfigData.h"
#include "PSDInitManager.h"
#include "PSDStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/ShieldDoorData.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern PsdConfigDataStruct gPsdConfigDataStruBuff[PSD_LOCAL_SUM_MAX];          /*引用本地管理的屏蔽门配置信息*/
extern UINT16_S gPsdIdBuff[PSD_SUM_MAX];                                      /*引用屏蔽门映射数组*/
extern UINT16_S gPsdCurSum;                                                  /*引用屏蔽门当前总数*/
extern PsdDataStruct gPsdDataStruBuff[PSD_LOCAL_SUM_MAX];                      /*引用本地管理的屏蔽门状态信息*/

/*
* 功能描述： 初始化本地管理的屏蔽门初始信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitPsdInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gPsdCurSum = 0U;

	/*初始化全局变量*/
	for (cycle = DEFAULT_ZERO;cycle < PSD_SUM_MAX;cycle++)
	{
		gPsdIdBuff[cycle] = PSD_SUM_MAX;
	}

	/*状态安全侧处理*/
	for (cycle = DEFAULT_ZERO;cycle < PSD_LOCAL_SUM_MAX;cycle++)
	{
		gPsdDataStruBuff[cycle].PsdStatus = PSD_STATE_OPEN;
	}
}

/*
* 功能描述： 初始化本地管理的屏蔽门信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitPSDLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S linePsdMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;

	/*初始化数量*/
	InitPsdInitializationData();

	linePsdMaxId = GetLinePsdMaxId();

	if (PSD_SUM_MAX >= linePsdMaxId)
	{
		for (cycle = 1U; cycle <= linePsdMaxId;cycle++)
		{
			/*判断该Id是否属于切换区域*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_PSD);

			/*判断该Id是否属于本ZC*/
			belongZcId = GetLinePsdBelongZcId(cycle);
            localZcId = GetLocalZcId();

			if ((belongZcId == localZcId ) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gPsdConfigDataStruBuff[addIndex].PsdId = cycle;
				gPsdConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gPsdConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLinePsdBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gPsdConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gPsdConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				/*设置ID映射数组*/
				gPsdIdBuff[cycle] = addIndex;

				/*填写状态对应的ID信息*/
				gPsdDataStruBuff[addIndex].PsdId = cycle;

				gPsdCurSum++;
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
