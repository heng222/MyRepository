/************************************************************************
*
* 文件名   ：  ESBInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  紧急停车按钮初始化管理
* 备  注   ：  无
*
************************************************************************/
#include "ESBConfigData.h"
#include "ESBInitManager.h"
#include "ESBStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/EmergStopButtonData.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern EsbConfigDataStruct gEsbConfigDataStruBuff[ESB_LOCAL_SUM_MAX];          /*引用本地管理的紧急停车按钮配置信息*/
extern UINT16_S gEsbIdBuff[ESB_SUM_MAX];                                      /*引用紧急停车按钮映射数组*/
extern UINT16_S gEsbCurSum;                                                  /*引用紧急停车按钮当前总数*/
extern EsbDataStruct gEsbDataStruBuff[ESB_LOCAL_SUM_MAX];                      /*引用本地管理的紧急停车按钮状态信息*/

/*
* 功能描述： 初始化本地管理的紧急停车按钮初始信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitEsbInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gEsbCurSum = 0U;

	/*初始化全局变量*/
	for (cycle = DEFAULT_ZERO;cycle < ESB_SUM_MAX;cycle++)
	{
		gEsbIdBuff[cycle] = ESB_SUM_MAX;
	}

	/*状态安全侧处理*/
	for (cycle = DEFAULT_ZERO;cycle < ESB_LOCAL_SUM_MAX;cycle++)
	{
		gEsbDataStruBuff[cycle].EsbStatus = ESB_STATE_DOWN;
	}
}

/*
* 功能描述： 初始化本地管理的紧急停车按钮信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			 1: 初始化成功      
*/
UINT8_S InitESBLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineEsbMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*初始化数量*/
	InitEsbInitializationData();

	lineEsbMaxId = GetLineEsbMaxId();

	if (ESB_SUM_MAX >= lineEsbMaxId)
	{
		for (cycle = 1U; cycle <= lineEsbMaxId;cycle++)
		{
			/*判断该Id是否属于切换区域*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_ESB);

			/*判断该Id是否属于本ZC*/
			belongZcId = GetLineEsbBelongZcId(cycle);

			if ((belongZcId == GetLocalZcId()) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gEsbConfigDataStruBuff[addIndex].EsbId = cycle;
				gEsbConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gEsbConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLineEsbBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gEsbConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gEsbConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				/*设置ID映射数组*/
				gEsbIdBuff[cycle] = addIndex;

				/*填写状态对应的ID信息*/
				gEsbDataStruBuff[addIndex].EsbId = cycle;

				gEsbCurSum++;
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
