
/********************************************************                                                                                                           
 文 件 名： OverlapInitManager.c 
 作    者： ZC组
 创建时间： 2015.04.18
 描述： 保护区段初始化  
 备注： 无  
********************************************************/ 

#include "OverlapConfigData.h"
#include "OverlapInitManager.h"
#include "OverlapStatusData.h"
#include "../Change/ChangeConfigData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../../Dmu/DmuComm/Data/ProtectZoneData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern OverlapConfigDataStruct gOverlapConfigDataStruBuff[OVERLAP_LOCAL_SUM_MAX];            /*引用本地管理的保护区段配置信息*/
extern UINT16_S gOverlapIdBuff[OVERLAP_SUM_MAX];                                            /*引用保护区段映射数组*/
extern UINT16_S gOverlapCurSum;                                                            /*引用保护区段当前总数*/

extern OverlapDataStruct gOverlapDataStruBuff[OVERLAP_LOCAL_SUM_MAX];                        /*引用本地管理的保护区段状态信息*/

/*************************************************
  函数名:    InitOverlapInitializationData  
  功能描述: 初始化本地管理的保护区段初始信息
  输入: 无   
  输出: 无
  返回值: 无      
*************************************************/
void InitOverlapInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gOverlapCurSum = 0U;

	/*初始化全局变量*/
	for (cycle = DEFAULT_ZERO;cycle < OVERLAP_SUM_MAX;cycle++)
	{
		gOverlapIdBuff[cycle] = OVERLAP_SUM_MAX;
	}

	/*状态安全侧处理*/
	for (cycle = DEFAULT_ZERO;cycle < OVERLAP_LOCAL_SUM_MAX;cycle++)
	{
		gOverlapDataStruBuff[cycle].OverlapStatus = OVERLAP_STATE_UNSET;
	}
}

/*************************************************
  函数名:   InitOverlapLocalInfo   
  功能描述: 初始化本地管理的保护区段信息
  输入: 无   
  输出: 无
  返回值: 0: 初始化失败
			>0: 初始化成功      
*************************************************/
UINT8_S InitOverlapLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineOverlapMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT16_S  acNumOfOverlap = DEFAULT_ZERO;
	UINT16_S acInfoOfOvaerlapBuff[OVERLAP_OF_AC_SUM_MAX] = {DEFAULT_ZERO};
	UINT16_S cycleOfAc = DEFAULT_ZERO;
	UINT16_S  overlapOfSwitchNum = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;

	MemorySet(&acInfoOfOvaerlapBuff[0],((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)));

	/*初始化数量*/
	InitOverlapInitializationData();

	lineOverlapMaxId = GetLineOverlapMaxId();

	if (OVERLAP_SUM_MAX >= lineOverlapMaxId)
	{
		for (cycle = 1U; cycle <= lineOverlapMaxId;cycle++)
		{
			/*判断该Id是否属于切换区域*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_OVERLAP);

			/*判断该Id是否属于本ZC*/
			belongZcId = GetLineOverlapBelongZcId(cycle);
            localZcId = GetLocalZcId();

			if ((belongZcId == localZcId) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gOverlapConfigDataStruBuff[addIndex].OverlapId = cycle;
				gOverlapConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gOverlapConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLineOverlapBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gOverlapConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gOverlapConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				/*获取保护区段关联的计轴区段信息*/
				acNumOfOverlap = GetLineOverlapOfAcInfo(cycle,acInfoOfOvaerlapBuff);

				if ((acNumOfOverlap > 0U) && (acNumOfOverlap <= OVERLAP_OF_AC_SUM_MAX))
				{
					gOverlapConfigDataStruBuff[addIndex].ContainAcNum = (UINT8_S)(acNumOfOverlap);

					for (cycleOfAc = DEFAULT_ZERO;cycleOfAc < acNumOfOverlap;cycleOfAc++)
					{
						gOverlapConfigDataStruBuff[addIndex].ContainAcBuff[cycleOfAc] = acInfoOfOvaerlapBuff[cycleOfAc];
					}
				} 
				else
				{
                    /*不处理*/
				}

				/*判断保护区段是否有道岔*/
				overlapOfSwitchNum = GetLineOverlapOfSwitchNum(cycle);

				if ((DEFAULT_ZERO < overlapOfSwitchNum)
					&& (DEFAULT_0XFF > overlapOfSwitchNum))
				{
					gOverlapConfigDataStruBuff[addIndex].SwitchAttribute = FLAG_SET;
				} 
				else
				{
                    /*不处理*/
				}

				/*设置ID映射数组*/
				gOverlapIdBuff[cycle] = addIndex;

				/*填写状态对应的ID信息*/
				gOverlapDataStruBuff[addIndex].OverlapId = cycle;

				gOverlapCurSum++;
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
