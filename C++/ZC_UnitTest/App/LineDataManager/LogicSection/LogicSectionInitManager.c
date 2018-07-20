/************************************************************************
*
* 文件名   ：  LogicSectionInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  逻辑区段初始化管理
* 备  注   ：  无
*
************************************************************************/
#include "LogicSectionConfigData.h"
#include "LogicSectionStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/LogicSectionData.h"
#include "LogicSectionInitManager.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern LogicSectionConfigDataStruct gLogicSectionConfigDataStruBuff[LOGIC_SECTION_LOCAL_SUM_MAX];          /*引用本地管理的逻辑区段配置信息*/
extern UINT16_S gLogicSectionIdBuff[LOGIC_SECTION_SUM_MAX];                                         /*引用定义逻辑区段映射数组*/
extern UINT16_S gLogicSectionCurSum;   
extern LogicSectionStruct gLogicSectionDataStruBuff[LOGIC_SECTION_LOCAL_SUM_MAX];                   /*引用定义本地管理的逻辑区段状态数据数组*/

/*
* 功能描述： 初始化本地管理的逻辑区段初始信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitLogicSectionInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gLogicSectionCurSum = 0U;

	/*初始化全局变量*/
	for (cycle = DEFAULT_ZERO;cycle < LOGIC_SECTION_SUM_MAX;cycle++)
	{
		gLogicSectionIdBuff[cycle] = LOGIC_SECTION_SUM_MAX;
	}

	/*状态安全侧处理*/
	for (cycle = DEFAULT_ZERO;cycle < LOGIC_SECTION_LOCAL_SUM_MAX;cycle++)
	{
		gLogicSectionDataStruBuff[cycle].LogicSectionOccStatus = LOGIC_SECTION_STATE_UT;
	}
}

/*
* 功能描述： 初始化本地管理的逻辑区段信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitLogicSectionLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineLogicSectionMaxId = DEFAULT_ZERO;
	UINT16_S belongAcId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;
    UINT16_S localZcId =DEFAULT_ZERO;

	/*初始化数量*/
	InitLogicSectionInitializationData();

	lineLogicSectionMaxId = GetLineLogicSectionMaxId();

	if (LOGIC_SECTION_SUM_MAX >= lineLogicSectionMaxId)
	{
		for (cycle = 1U; cycle <= lineLogicSectionMaxId;cycle++)
		{
			/*判断该Id是否属于本ZC*/
			belongAcId = GetLineLogicSectionBelongAcId(cycle);
			belongZcId = GetLineLogicSectionBelongZcId(cycle);

			if ((DEFAULT_ZERO != belongAcId) || (DEFAULT_ZERO != belongZcId))
			{
				/*判断该acId是否属于切换区域*/
				rtnOfChangeArea = GetAppointObsInChangeArea(belongAcId,OBS_TYPE_AC);
                localZcId = GetLocalZcId();

				if ((belongZcId == localZcId) || (RETURN_SUCCESS == rtnOfChangeArea))
				{
					if (addIndex < LOGIC_SECTION_LOCAL_SUM_MAX)
					{
						gLogicSectionConfigDataStruBuff[addIndex].LogicSectionId = cycle;
						gLogicSectionConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
						gLogicSectionConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLineLogicSectionBelongCiId(cycle));
						gLogicSectionConfigDataStruBuff[addIndex].BelongAcId = belongAcId;

						/*设置ID映射数组*/
						gLogicSectionIdBuff[cycle] = addIndex;

						/*填写状态对应的ID信息*/
						gLogicSectionDataStruBuff[addIndex].LogicSectionId = cycle;

						gLogicSectionCurSum++;
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
			else
			{			
				breakFlag = FLAG_SET;
				break;
			}
			
		}

		if (FLAG_SET == breakFlag)
		{           
            rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
    	}		
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}
	
	return rtnValue;
}
