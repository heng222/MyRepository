/************************************************************************
*
* 文件名   ：  ACInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  计轴区段的初始化
* 备  注   ：  无
*
************************************************************************/

#include "ACInitManager.h"
#include "ACConfigData.h"
#include "ACStatusData.h"
#include "../Change/ChangeConfigData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../../Dmu/DmuComm/Data/AxleSectionData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Common/MemSet.h"

extern AcConfigDataStruct gAcConfigDataStruBuff[LOCAL_AC_SUM_MAX];    /*引用本ZC计轴数据配置结构体*/
extern UINT16_S gLocalAcIndexBuff[AC_SUM_MAX];		                 /*引用本ZC计轴下标数组*/
extern UINT16_S gAcCurSum;								     	     /*引用本ZC计轴当前总数*/
extern AcStatusDataStruct gAcStatusDataStruBuff[LOCAL_AC_SUM_MAX];    /*引用本ZC计轴数据状态结构体*/

/*
* 功能描述： 初始化本地管理的计轴区段初始信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitAcInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gAcCurSum = 0U;

	/*初始化全局变量*/
	for (cycle = DEFAULT_ZERO;cycle < AC_SUM_MAX;cycle++)
	{
		gLocalAcIndexBuff[cycle] = AC_SUM_MAX;
	}

	/*状态安全态处理*/
	for (cycle = DEFAULT_ZERO;cycle < LOCAL_AC_SUM_MAX;cycle++)
	{
		gAcStatusDataStruBuff[cycle].AcUtFlag = AC_UT_OCC_STATUS;

		gAcStatusDataStruBuff[cycle].AcBelock = AC_UNLOCK_STATUS;

		gAcStatusDataStruBuff[cycle].AcStatusNow = AC_OCC_STATUS;
	}
}

/*
* 功能描述： 初始化本地管理的计轴区段信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitACLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineAcMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S  switchNum = DEFAULT_ZERO;      
	UINT16_S switchInfoBuff[AC_SWITCH_SUM_MAX * 2U] = {0U};
	UINT8_S  logicSectionNum = DEFAULT_ZERO;                            
	UINT16_S logicSectionIdBuff[SIZE_MAX_SECTIONNUM] = {0U};
	UINT8_S cycleSwitch = DEFAULT_ZERO;
	UINT8_S cycleLogicSection = DEFAULT_ZERO;
	UINT8_S indexOfSwtich = DEFAULT_ZERO;
	UINT8_S errorFlag = DEFAULT_ZERO;

	/*初始化*/
	InitAcInitializationData();
	MemorySet(&switchInfoBuff[0],((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX)),
              0U,((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX)));
	MemorySet(&logicSectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTIONNUM)),
              0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTIONNUM)));

	lineAcMaxId = GetLineAcMaxId();

	if (AC_SUM_MAX >= lineAcMaxId)
	{
		for (cycle = 1U; cycle <= lineAcMaxId;cycle++)
		{
			/*判断该Id是否属于切换区域*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_AC);

			/*判断该Id是否属于本ZC*/
			belongZcId = GetLineAcBelongZcId(cycle);

			if ((belongZcId == GetLocalZcId()) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gAcConfigDataStruBuff[addIndex].AcId = cycle;
				gAcConfigDataStruBuff[addIndex].BelongZcId = belongZcId;
				gAcConfigDataStruBuff[addIndex].BelongCiId = GetLineAcBelongCiId(cycle);

				if (belongZcId == GetLocalZcId())
				{
					gAcConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gAcConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				/*获取计轴区段属性*/
				gAcConfigDataStruBuff[addIndex].AcType = GetLineAcType(cycle);

				/*初始化查询信息*/
				MemorySet(switchInfoBuff,((UINT32_S)(sizeof(UINT16_S)*AC_SWITCH_SUM_MAX*2U)),
                          0U,((UINT32_S)(sizeof(UINT16_S)*AC_SWITCH_SUM_MAX*2U)));
				indexOfSwtich = DEFAULT_ZERO;

				if (RETURN_SUCCESS == GetLineAcIncludeSwitchInfo(cycle,&switchNum,switchInfoBuff))
				{
					gAcConfigDataStruBuff[addIndex].SwitchNum = switchNum;			

					for (cycleSwitch = DEFAULT_ZERO;cycleSwitch < switchNum;cycleSwitch++)
					{
						gAcConfigDataStruBuff[addIndex].SwitchInAcStru[cycleSwitch].SwitchId = switchInfoBuff[indexOfSwtich];
                        indexOfSwtich = indexOfSwtich + 1U;

						gAcConfigDataStruBuff[addIndex].SwitchInAcStru[cycleSwitch].SwitchPostion = (UINT8_S)switchInfoBuff[indexOfSwtich];
                        indexOfSwtich = indexOfSwtich + 1U;
					}
				} 
				else
				{
					errorFlag = FLAG_SET;
					break;
				}

				/*初始化查询信息*/
				MemorySet(logicSectionIdBuff,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_SECTIONNUM)),
                          0U,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_SECTIONNUM)));
				logicSectionNum = DEFAULT_ZERO;

				if (RETURN_SUCCESS == GetLineAcIncludeLogicSectionInfo(cycle,&logicSectionNum,logicSectionIdBuff))
				{
					gAcConfigDataStruBuff[addIndex].LogicSectionNum = logicSectionNum;

					for (cycleLogicSection = DEFAULT_ZERO;cycleLogicSection < logicSectionNum;cycleLogicSection++)
					{
						gAcConfigDataStruBuff[addIndex].LogicSectionIdBuff[cycleLogicSection] = logicSectionIdBuff[cycleLogicSection];
					}
				} 
				else
				{
					errorFlag = FLAG_SET;
					break;
				}

				/*设置ID映射数组*/
				gLocalAcIndexBuff[cycle] = addIndex;

				/*填写状态对应的ID信息*/
				gAcStatusDataStruBuff[addIndex].AcId = cycle;

				gAcCurSum++;
				addIndex++;
			} 
			else
			{
				/*不属于本ZC管辖范围或者切换区域内的障碍物*/
			}
		}

		if (FLAG_SET == errorFlag)
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
