/************************************************************************
*
* 文件名   ：  SignalInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  信号机初始化管理
* 备  注   ：  无
*
************************************************************************/
#include "SignalConfigData.h"
#include "SignalInitManager.h"
#include "SignalStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/SignData.h"
#include "../../DmuZc/Data/ZcSignInfoData.h"
#include "../Mask/MaskConfigData.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern SignalConfigDataStruct gSignalConfigDataStruBuff[SIGNAL_LOCAL_SUM_MAX];            /*引用本地管理的信号机配置信息*/
extern UINT16_S gSignalIdBuff[SIGNAL_SUM_MAX];                  /*引用信号机映射数组*/
extern UINT16_S gSignalCurSum;                                                      /*引用信号机当前总数*/
extern SignalDataStruct gSignalDataStruBuff[SIGNAL_LOCAL_SUM_MAX];                        /*引用本地管理的保护区段状态信息*/

/*
* 功能描述： 初始化本地管理的信号机初始信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitSignalInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gSignalCurSum = 0U;

	/*初始化全局变量*/
	for (cycle = DEFAULT_ZERO;cycle < SIGNAL_SUM_MAX;cycle++)
	{
		gSignalIdBuff[cycle] = SIGNAL_SUM_MAX;
	}

	/*状态安全侧处理*/
	for (cycle = DEFAULT_ZERO;cycle < SIGNAL_LOCAL_SUM_MAX;cycle++)
	{
		gSignalDataStruBuff[cycle].SignalStatus = SIGNAL_STATE_STOP;

		gSignalDataStruBuff[cycle].LightOffStatus = SIGNAL_LIGHT_COMMAND;

		gSignalDataStruBuff[cycle].CrossStatus = SIGNAL_TRAIN_ALREADY_CROSS;
	}
}

/*
* 功能描述： 初始化本地管理的信号机信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitSignalLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineSignalMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S defualtStatus = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;

	/*初始化数量*/
	InitSignalInitializationData();

	lineSignalMaxId = GetLineSignalMaxId();

	if (SIGNAL_SUM_MAX >= lineSignalMaxId)
	{
		for (cycle = 1U; cycle <= lineSignalMaxId;cycle++)
		{
			/*判断该Id是否属于切换区域*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_SIGNAL);

			/*判断该Id是否属于本ZC*/
			belongZcId = GetLineSignalBelongZcId(cycle);
			localZcId = GetLocalZcId();

			if ((belongZcId == localZcId) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gSignalConfigDataStruBuff[addIndex].SignalId = cycle;
				gSignalConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gSignalConfigDataStruBuff[addIndex].BelongCiId =(UINT8_S)(GetLineSignalBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gSignalConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gSignalConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				gSignalConfigDataStruBuff[addIndex].SignalType = (UINT8_S)(GetSignDataStrusignProperty(cycle));
				gSignalConfigDataStruBuff[addIndex].ProtectDir = GetSignDataStruprotectiveDir(cycle);		
				gSignalConfigDataStruBuff[addIndex].CrashType = (UINT8_S)(GetZcSignInfoDataStruthroughSignFlag(cycle));

				gSignalConfigDataStruBuff[addIndex].LightOffType = InitSignalLightOffType(cycle);
				gSignalConfigDataStruBuff[addIndex].CrossType = InitSignalCorssType(cycle);

				/*该信号机是CI码位中的信号机,需要查询默认状态和CT车接近时的状态*/			
				defualtStatus = (UINT8_S)(GetZcSignInfoDataStrulightFlag(cycle));

				switch (defualtStatus)
				{
					case 0x00U:
						/*默认常态需要灭灯*/
						gSignalConfigDataStruBuff[addIndex].DefaultStatus = (UINT8_S)SIGNAL_OFF_COMMAND;	

						/*CBTC列车接近默认需要灭灯*/
						gSignalConfigDataStruBuff[addIndex].CbtcLightOffType = (UINT8_S)SIGNAL_OFF_COMMAND;
						break;

					case 0x01U:
						/*默认常态需要亮灯*/
						gSignalConfigDataStruBuff[addIndex].DefaultStatus = (UINT8_S)SIGNAL_LIGHT_COMMAND;

						/*CBTC列车接近默认需要灭灯*/
						gSignalConfigDataStruBuff[addIndex].CbtcLightOffType = (UINT8_S)SIGNAL_OFF_COMMAND;
						break;

					case 0x02U:
						/*默认常态需要灭灯*/
						gSignalConfigDataStruBuff[addIndex].DefaultStatus = (UINT8_S)SIGNAL_OFF_COMMAND;

						/*CBTC列车接近默认需要亮灯*/
						gSignalConfigDataStruBuff[addIndex].CbtcLightOffType = (UINT8_S)SIGNAL_LIGHT_COMMAND;
						break;

					case 0x03U:
						/*默认常态需要亮灯*/
						gSignalConfigDataStruBuff[addIndex].DefaultStatus = (UINT8_S)SIGNAL_LIGHT_COMMAND;

						/*CBTC列车接近默认需要亮灯*/
						gSignalConfigDataStruBuff[addIndex].CbtcLightOffType = (UINT8_S)SIGNAL_LIGHT_COMMAND;
						break;

					default:
						/*默认常态需要亮灯*/
						gSignalConfigDataStruBuff[addIndex].DefaultStatus = (UINT8_S)SIGNAL_LIGHT_COMMAND;

						/*CBTC列车接近默认需要亮灯*/
						gSignalConfigDataStruBuff[addIndex].CbtcLightOffType = (UINT8_S)SIGNAL_LIGHT_COMMAND;
						break;
				}

				/*设置ID映射数组*/
				gSignalIdBuff[cycle] = addIndex;

				/*填写状态对应的ID信息*/
				gSignalDataStruBuff[addIndex].SignalId = cycle;

				gSignalCurSum++;
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
* 功能描述： 初始化本地管理的信号机亮灭灯信息
* 参数说明： const UINT16 signalId，信号机ID   
* 返回值  ： 0: 失败
*			 0x55: 属于
*            0xaa: 不属于
*/
UINT8_S InitSignalLightOffType(const UINT16_S signalId)
{
	UINT16_S signalLightOffNum = DEFAULT_ZERO;
	UINT16_S signalLightOffIdBuff[SINGLE_ZC_TO_CI_MASK_SUM_MAX] = {DEFAULT_ZERO};
	UINT16_S cycle = DEFAULT_ZERO;
	UINT8_S tempRtn = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	MemorySet(&signalLightOffIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_ZC_TO_CI_MASK_SUM_MAX)),
                0U,((UINT32_S)(SIZE_UINT16 * SINGLE_ZC_TO_CI_MASK_SUM_MAX)));

	signalLightOffNum = GetMaskOfSignalLightOffNum();
	tempRtn = GetMaskOfSignalLightOffIdBuff(((UINT16_S)(SINGLE_ZC_TO_CI_MASK_SUM_MAX)),signalLightOffIdBuff);

	if ((DEFAULT_ZERO != signalLightOffNum)
		&& (RETURN_SUCCESS == tempRtn))
	{
		for (cycle = 0U;cycle < signalLightOffNum;cycle++)
		{
			if (signalLightOffIdBuff[cycle] == signalId)
			{
				rtnValue = FLAG_SET;
				break;
			} 
			else
			{
                /*不处理*/
			}
		}

		if (FLAG_SET != rtnValue)
		{
			rtnValue = FLAG_UNSET;
		} 
		else
		{
            /*不处理*/
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的信号机跨压信息
* 参数说明： const UINT16 signalId，信号机ID   
* 返回值  ： 0: 失败
*			 0x55: 属于
*            0xaa: 不属于
*/
UINT8_S InitSignalCorssType(const UINT16_S signalId)
{
	UINT16_S signalCorssNum = DEFAULT_ZERO;
	UINT16_S signalCrossIdBuff[SINGLE_ZC_TO_CI_MASK_SUM_MAX] = {DEFAULT_ZERO};
	UINT16_S cycle = DEFAULT_ZERO;
	UINT8_S tempRtn = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	MemorySet(&signalCrossIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_ZC_TO_CI_MASK_SUM_MAX)),
                0U,((UINT32_S)(SIZE_UINT16 * SINGLE_ZC_TO_CI_MASK_SUM_MAX)));

	signalCorssNum = GetMaskOfSignalCorssNum();
	tempRtn = GetMaskOfSignalCorssIdBuff(((UINT16_S)(SINGLE_ZC_TO_CI_MASK_SUM_MAX)),signalCrossIdBuff);

	if ((DEFAULT_ZERO != signalCorssNum)
		&& (RETURN_SUCCESS == tempRtn))
	{
		for (cycle = 0U;cycle < signalCorssNum;cycle++)
		{
			if (signalCrossIdBuff[cycle] == signalId)
			{
				rtnValue = FLAG_SET;
				break;
			} 
			else
			{
                /*不处理*/
			}
		}

		if (FLAG_SET != rtnValue)
		{
			rtnValue = FLAG_UNSET;
		} 
		else
		{
            /*不处理*/
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
