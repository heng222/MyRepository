/************************************************************************
*
* 文件名   ：  MaskInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  码位初始化管理
* 备  注   ：  无
*
************************************************************************/
#include "MaskConfigData.h"
#include "MaskInitManager.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Common/Convert.h"
#include "../../IOManager/CommTarget/CommTargetConfigData.h"
#include "../../../Dmu/DmuComm/Data/SwitchData.h"
#include "../../../Dmu/DmuComm/Data/SignData.h"
#include "../../../Dmu/DmuComm/Data/ShieldDoorData.h"
#include "../../../Dmu/DmuComm/Data/EmergStopButtonData.h"
#include "../../../Dmu/DmuComm/Data/AxleSectionData.h"
#include "../../../Dmu/DmuComm/Data/LogicSectionData.h"
#include "../../../Dmu/DmuComm/Data/RouteData.h"
#include "../../../Dmu/DmuComm/Data/ProtectZoneData.h"
#include "../../../Dmu/DmuComm/Data/ArData.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Malloc.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern ZcCiMaskConfigDataStruct gZcToCiMaskConfigDataStruBuff[COMM_CI_SUM_MAX];                        /*引用ZC-CI码位信息结构体*/
extern UINT16_S gZcToCiIdBuff[LINE_CI_SUM_MAX];                                                       /*引用ZC与Ci通信ID索引数组*/
extern UINT8_S  gZcToCiCurSum;                                                                       /*引用ZC输出CI的最大数量*/

extern ZcCiMaskConfigDataStruct gCiToZcMaskConfigDataStruBuff[COMM_CI_SUM_MAX];                        /*引用CI-ZC码位信息结构体*/
extern UINT16_S gCiToZiIdBuff[LINE_CI_SUM_MAX];                                                       /*引用CI输入的最大数量*/
extern UINT8_S  gCiToZcCurSum;                                                                       /*引用CI输如ZC的最大数量*/

extern UINT16_S gToCiConfigSignalCrossIdBuff[SINGLE_ZC_TO_CI_MASK_SUM_MAX];                         /*定义本ZC需要计算的信号机跨压*/
extern UINT16_S gSignalCrossNum;

extern UINT16_S gToCiConfigSignalLightOffIdBuff[SINGLE_ZC_TO_CI_MASK_SUM_MAX];                     /*定义本ZC需要计算的信号机亮灭*/
extern UINT16_S gSignalLightOffNum;

/*
* 功能描述： 初始化本地管理的码位信息中的基础信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitMaskValueData(void)
{
	UINT16_S cycleMask = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;

	gCiToZcCurSum = 0U;

	for (cycle = DEFAULT_ZERO;cycle < LINE_CI_SUM_MAX;cycle++)
	{
		gCiToZiIdBuff[cycle] = LINE_CI_SUM_MAX;
	}

	gZcToCiCurSum = 0U;

	for (cycle = DEFAULT_ZERO;cycle < LINE_CI_SUM_MAX;cycle++)
	{
		gZcToCiIdBuff[cycle] = LINE_CI_SUM_MAX;
	}

	for (cycle = DEFAULT_ZERO;cycle < COMM_CI_SUM_MAX;cycle++)
	{
		for (cycleMask = DEFAULT_ZERO;cycleMask < ZC_TO_CI_MASK_SUM_MAX;cycleMask++)
		{
			gZcToCiMaskConfigDataStruBuff[cycle].MaskIdBuff[cycleMask] = ZC_TO_CI_MASK_SUM_MAX;
			gCiToZcMaskConfigDataStruBuff[cycle].MaskIdBuff[cycleMask] = ZC_TO_CI_MASK_SUM_MAX;
		}
	}
}

/*
* 功能描述： 获取设备所属的联锁ID
* 参数说明： const UINT16 devId, 设备ID
*            const UINT8_S devType,设备类型
* 返回值  ： 0: 获取失败
*			>0: 所属CIID      
*/
UINT16_S GetLineDeviceBelongCiId(const UINT16_S devId,const UINT8_S devType)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	switch (devType)
	{
		case OBS_TYPE_POINT:
			rtnValue = GetLineSwitchBelongCiId(devId);
			break;

		case OBS_TYPE_SIGNAL:
			rtnValue = GetLineSignalBelongCiId(devId);
			break;

		case OBS_TYPE_PSD:
			rtnValue = GetLinePsdBelongCiId(devId);
			break;

		case OBS_TYPE_ESB:
			rtnValue = GetLineEsbBelongCiId(devId);
			break;

		case OBS_TYPE_AC:
			rtnValue = GetLineAcBelongCiId(devId);
			break;

		case OBS_TYPE_LS:
			rtnValue = GetLineAcBelongCiId(GetLineLogicSectionBelongAcId(devId));
			break;

		case OBS_TYPE_ROUTE:
			rtnValue = GetRouteDataStrumanageCI(devId);
			break;

		case OBS_TYPE_OVERLAP:
			rtnValue = GetLineOverlapBelongCiId(devId);
			break;

		case OBS_TYPE_DRB:
			rtnValue = GetLineDrButtonBelongCiId(devId);
			break;

		case OBS_TYPE_DRL:
			rtnValue = GetLineDrLampBelongCiId(devId);
			break;

		default:
			rtnValue = DEFAULT_ZERO;
			break;
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的码位信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcCiMaskLocalInfo(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*初始化码位信息*/
	InitMaskValueData();

	/*初始化通信对象信息*/
	rtnValue = InitZcCiMaskConfigCommTargetData();

	/*初始化道岔码位*/
	rtnValue &= InitZcCiMaskOfSwitchInfo();

	/*初始化信号机码位*/
	rtnValue &= InitZcCiMaskOfSignalInfo();

	/*初始化屏蔽门码位*/
	rtnValue &= InitZcCiMaskOfPsdInfo();

	/*初始化紧急停车按钮码位*/
	rtnValue &= InitZcCiMaskOfEsbInfo();

	/*初始化计轴区段码位*/
	rtnValue &= InitZcCiMaskOfAcInfo();

	/*初始化逻辑区段码位*/
	rtnValue &= InitZcCiMaskOfSectionInfo();

	/*初始化进路码位*/
	rtnValue &= InitZcCiMaskOfRouteInfo();

	/*初始化保护区段码位*/
	rtnValue &= InitZcCiMaskOfOverlapInfo();
	
	/*初始化无人折返码位*/
	rtnValue &= InitZcCiMaskOfDrInfo();

	return rtnValue;
}

/*
* 功能描述： 初始化码位配置信息中通讯对象
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			 1: 初始化成功      
*/
UINT8_S InitZcCiMaskConfigCommTargetData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;
	UINT16_S commTargetId = DEFAULT_ZERO;
	UINT8_S rtnValue = RETURN_SUCCESS;
	UINT8_S typeBuffIndex = DEFAULT_ZERO;
	UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};

	MemorySet(&commTargetIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)));
	typeBuffIndex = GetCommTargetTypeBuffIndex(INNER_DEVTYPE_CI);

	GetSingleCommTargetIdBuff(INNER_DEVTYPE_CI,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff);

	for (cycle = DEFAULT_ZERO;cycle < GetSingleCommTargetTypeSum(INNER_DEVTYPE_CI);cycle++)
	{
		commTargetId = commTargetIdBuff[cycle];

		if ((gZcToCiCurSum <= COMM_CI_SUM_MAX) 
			&& (gCiToZcCurSum <= COMM_CI_SUM_MAX)
			&& (LINE_CI_SUM_MAX > commTargetId))
		{
			gZcToCiMaskConfigDataStruBuff[gZcToCiCurSum].CommCiId = commTargetId;
			gZcToCiIdBuff[commTargetId] = gZcToCiCurSum;

			gCiToZcMaskConfigDataStruBuff[gCiToZcCurSum].CommCiId = commTargetId;
			gCiToZiIdBuff[commTargetId] = gCiToZcCurSum;

			gZcToCiCurSum++;
			gCiToZcCurSum++;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
			break;
		}
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的发送给CI系统的码位信息
* 参数说明： UINT16 maskId;码位ID
*            UINT8_S maskType;码位类型
*            UINT16_S devId;设备ID
*            UINT8_S devType;设备类型
*            UINT16_S relevanceMaskId;关联码位ID
* 返回值  ： 0: 初始化失败
*			 1: 初始化成功      
*/
UINT8_S InitSendToCiMaskInfo(UINT16_S maskId,UINT8_S maskType,UINT16_S devId,UINT8_S devType,UINT16_S relevanceMaskId)
{
	UINT8_S commTargetIndex = DEFAULT_ZERO;
	UINT16_S belongCiId = DEFAULT_ZERO;
	UINT16_S sendMaskBufIndex = ZC_TO_CI_MASK_SUM_MAX;
	UINT16_S maskCurSum = DEFAULT_ZERO;
	UINT8_S  deviceSum = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	belongCiId = GetLineDeviceBelongCiId(devId,devType);

	commTargetIndex =  GetSendCommTargetIndex(INNER_DEVTYPE_CI,belongCiId);

	if (COMM_CI_SUM_MAX > commTargetIndex)
	{
		if (DEFAULT_UINT16_VALUE != maskId)
		{
			/*判断该码位是否已在本地信息中*/
			sendMaskBufIndex = GetSendMaskBufIndex(maskId,INNER_DEVTYPE_CI,belongCiId);

			if (ZC_TO_CI_MASK_SUM_MAX == sendMaskBufIndex)
			{
				/*还未填写该码位信息*/
				/*码位数量*/
				maskCurSum = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskCurSum;

				if (maskCurSum <= ZC_TO_CI_MASK_SUM_MAX)
				{
					gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].MaskId = maskId;
					gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].MaskType = maskType;
					gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].DeviceType = devType;
					gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].RelevanceMaskId = relevanceMaskId;

					deviceSum = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].DeviceSum;
					if (deviceSum <= SINGLE_MASK_DEVICE_SUM_MAX)
					{
						gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].DeviceIdBuff[deviceSum] = devId;
						gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].DeviceSum++;
					} 
					else
					{
						rtnValue = RETURN_ERROR;
					}

					gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskIdBuff[maskId] = maskCurSum;
					gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskCurSum++;

					/*更新码位最大值*/
					if (maskId > gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskIdMax)
					{
						gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskIdMax = maskId;
					} 
					else
					{
                        /*不处理*/
					}

					rtnValue = RETURN_SUCCESS;
				} 
				else
				{
					rtnValue = RETURN_ERROR;
				}
			} 
			else
			{
				/*已填写该码位信息*/
				deviceSum = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[sendMaskBufIndex].DeviceSum;
				if (deviceSum <= SINGLE_MASK_DEVICE_SUM_MAX)
				{
					gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[sendMaskBufIndex].DeviceIdBuff[deviceSum] = devId;
					gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[sendMaskBufIndex].DeviceSum++;
				} 
				else
				{
					rtnValue = RETURN_ERROR;
				}
			}
		} 
		else
		{
			/*不填写该码位值*/
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的接受CI输入ZC系统的码位信息
* 参数说明： UINT16 maskId;码位ID
*            UINT8_S maskType;码位类型
*            UINT16_S devId;设备ID
*            UINT8_S devType;设备类型
*            UINT16_S relevanceMaskId;关联码位ID
* 返回值  ： 0: 初始化失败
*			 1: 初始化成功      
*/
UINT8_S InitReceiveToCiMaskInfo(UINT16_S maskId,UINT8_S maskType,UINT16_S devId,UINT8_S devType,UINT16_S relevanceMaskId)
{
	UINT8_S commTargetIndex = DEFAULT_ZERO;
	UINT16_S belongCiId = DEFAULT_ZERO;
	UINT16_S receiveMaskBufIndex = ZC_TO_CI_MASK_SUM_MAX;
	UINT16_S maskCurSum = DEFAULT_ZERO;
	UINT8_S  deviceSum = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	belongCiId = GetLineDeviceBelongCiId(devId,devType);

	commTargetIndex =  GetReceiveCommTargetIndex(INNER_DEVTYPE_CI,belongCiId);

	if (COMM_CI_SUM_MAX > commTargetIndex)
	{
		if (DEFAULT_UINT16_VALUE != maskId)
		{
			/*判断该码位是否已在本地信息中*/
			receiveMaskBufIndex = GetReceiveMaskBufIndex(maskId,INNER_DEVTYPE_CI,belongCiId);

			if (ZC_TO_CI_MASK_SUM_MAX == receiveMaskBufIndex)
			{
				/*还未填写该码位信息*/
				/*码位数量*/
				maskCurSum = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskCurSum;

				if (maskCurSum <= ZC_TO_CI_MASK_SUM_MAX)
				{
					gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].MaskId = maskId;
					gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].MaskType = maskType;
					gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].DeviceType = devType;
					gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].RelevanceMaskId = relevanceMaskId;

					deviceSum = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].DeviceSum;
					if (deviceSum <= SINGLE_MASK_DEVICE_SUM_MAX)
					{
						gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].DeviceIdBuff[deviceSum] = devId;
						gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[maskCurSum].DeviceSum++;
					} 
					else
					{
						rtnValue = RETURN_ERROR;
					}

					gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskIdBuff[maskId] = maskCurSum;
					gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskCurSum++;

					/*更新码位最大值*/
					if (maskId > gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskIdMax)
					{
						gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskIdMax = maskId;
					} 
					else
					{
                        /*不处理*/
					}

					rtnValue = RETURN_SUCCESS;
				} 
				else
				{
					rtnValue = RETURN_ERROR;
				}
			} 
			else
			{
				/*已填写该码位信息*/
				deviceSum = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[receiveMaskBufIndex].DeviceSum;
				if (deviceSum <= SINGLE_MASK_DEVICE_SUM_MAX)
				{
					gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[receiveMaskBufIndex].DeviceIdBuff[deviceSum] = devId;
					gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[receiveMaskBufIndex].DeviceSum++;
				} 
				else
				{
					rtnValue = RETURN_ERROR;
				}
			}
		} 
		else
		{
			/*该码位值无效,不填写*/
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的道岔码位信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcCiMaskOfSwitchInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*定义通用文件数据指针*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S switchId = DEFAULT_ZERO;
	UINT16_S switchFrontMaskId = DEFAULT_ZERO;
	UINT16_S switchSideMaskId = DEFAULT_ZERO;
	UINT16_S switchLockMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0; 

	/*读取文件中的道岔信息总和*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_SWITCHCODE_TYPE)),&maskDataLen,&indexId);
	
	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*分配内存大小*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_SWITCH_MASK_LEN)),maskDataLen,indexId,pMaskData);
		
		if (0 == tempRtnData)
		{
			/*查询成功*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_SWITCH_MASK_LEN)
			{
				/*道岔ID*/
				switchId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*道岔定位码位*/
				switchFrontMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*道岔反位码位*/
				switchSideMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitReceiveToCiMaskInfo(switchFrontMaskId,SWITCH_FRONT_MASK_TYPE,switchId,OBS_TYPE_POINT,switchSideMaskId);		
				rtnValue &= InitReceiveToCiMaskInfo(switchSideMaskId,SWITCH_SIDE_MASK_TYPE,switchId,OBS_TYPE_POINT,switchFrontMaskId);

				/*道岔锁闭码位*/
				switchLockMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitReceiveToCiMaskInfo(switchLockMaskId,SWITCH_LOCK_MASK_TYPE,switchId,OBS_TYPE_POINT,DEFAULT_ZERO);		
			}

			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		if (0 != tempRtnLen)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的信号机码位信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcCiMaskOfSignalInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*定义通用文件数据指针*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S signalId = DEFAULT_ZERO;
	UINT16_S signalStatusMaskId = DEFAULT_ZERO;
	UINT16_S signalCrossMaskId = DEFAULT_ZERO;
	UINT16_S signalLightOffMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*读取文件中的信号机信息总和*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_SIGNCODE_TYPE)),&maskDataLen,&indexId);
	
	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*分配内存大小*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_SIGNAL_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*查询成功*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_SIGNAL_MASK_LEN)
			{
				/*信号机ID*/
				signalId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*信号机状态码位*/
				signalStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitReceiveToCiMaskInfo(signalStatusMaskId,SIGNAL_STATUS_MASK_TYPE,signalId,OBS_TYPE_SIGNAL,DEFAULT_ZERO);

				/*信号机跨压码位*/
				signalCrossMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitSignalCrossInfo(signalId,signalCrossMaskId);

				rtnValue &= InitSendToCiMaskInfo(signalCrossMaskId,SIGNAL_CROSS_MASK_TYPE,signalId,OBS_TYPE_SIGNAL,DEFAULT_ZERO);

				/*信号机亮灭码位*/
				signalLightOffMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitSignalLightOffInfo(signalId,signalLightOffMaskId);

				rtnValue &= InitSendToCiMaskInfo(signalLightOffMaskId,SIGNAL_LIGHT_OFF_MASK_TYPE,signalId,OBS_TYPE_SIGNAL,DEFAULT_ZERO);		
			}

			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		if (0 != tempRtnLen)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的屏蔽门码位信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcCiMaskOfPsdInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*定义通用文件数据指针*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S psdId = DEFAULT_ZERO;
	UINT16_S psdStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*读取文件中的Psd信息总和*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_PSDCODE_TYPE)),&maskDataLen,&indexId);

	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*分配内存大小*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_PSD_MASK_LEN)),maskDataLen,indexId,pMaskData);

		/*查询成功*/
		if (0 == tempRtnData)
		{
			/*查询成功*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_PSD_MASK_LEN)
			{
				/*屏蔽门ID*/
				psdId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*屏蔽门状态码位*/
				psdStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitReceiveToCiMaskInfo(psdStatusMaskId,PSD_STATUS_MASK_TYPE,psdId,OBS_TYPE_PSD,DEFAULT_ZERO);		
			}

			rtnValue = RETURN_SUCCESS;
		}
		else
		{
			rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		if (0 != tempRtnLen)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的紧急停车按钮码位信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcCiMaskOfEsbInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*定义通用文件数据指针*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S esbId = DEFAULT_ZERO;
	UINT16_S esbStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*读取文件中的ESB信息总和*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_ESBCODE_TYPE)),&maskDataLen,&indexId);
	
	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*分配内存大小*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_ESB_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*查询成功*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_ESB_MASK_LEN)
			{
				/*紧急停车按钮ID*/
				esbId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*紧急停车按钮状态码位*/
				esbStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitReceiveToCiMaskInfo(esbStatusMaskId,ESB_STATUS_MASK_TYPE,esbId,OBS_TYPE_ESB,DEFAULT_ZERO);		
			}

			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		if (0 != tempRtnLen)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的计轴区段码位信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcCiMaskOfAcInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*定义通用文件数据指针*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S acId = DEFAULT_ZERO;
	UINT16_S acUpDirMaskId = DEFAULT_ZERO;
	UINT16_S acDownDirMaskId = DEFAULT_ZERO;
	UINT16_S acOccStatusMaskId = DEFAULT_ZERO;
	UINT16_S acLockStatusMaskId = DEFAULT_ZERO;
	UINT16_S acArbStatusMaskId = DEFAULT_ZERO;
	UINT16_S acStopStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*读取文件中的ac信息总和*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_AXLESECCODE_TYPE)),&maskDataLen,&indexId);
	
	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*分配内存大小*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_AC_SGMT_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*查询成功*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_AC_SGMT_MASK_LEN)
			{
				/*计轴区段ID*/
				acId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*计轴区段上行方向状态码位*/
				acUpDirMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*计轴区段下行方向状态码位*/
				acDownDirMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitReceiveToCiMaskInfo(acUpDirMaskId,AC_UP_DIR_MASK_TYPE,acId,OBS_TYPE_AC,acDownDirMaskId);	
				rtnValue &= InitReceiveToCiMaskInfo(acDownDirMaskId,AC_DOWN_DIR_MASK_TYPE,acId,OBS_TYPE_AC,acUpDirMaskId);	

				/*计轴区段占用状态码位*/
				acOccStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitReceiveToCiMaskInfo(acOccStatusMaskId,AC_OCC_STATUS_MASK_TYPE,acId,OBS_TYPE_AC,DEFAULT_ZERO);	

				/*计轴区段锁闭状态码位*/
				acLockStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitReceiveToCiMaskInfo(acLockStatusMaskId,AC_LOCK_STATUS_MASK_TYPE,acId,OBS_TYPE_AC,DEFAULT_ZERO);	

				/*计轴区段ARB状态码位*/
				acArbStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitSendToCiMaskInfo(acArbStatusMaskId,AC_ARB_STATUS_MASK_TYPE,acId,OBS_TYPE_AC,DEFAULT_ZERO);	

				/*计轴区段列车停稳状态码位*/
				acStopStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitSendToCiMaskInfo(acStopStatusMaskId,AC_STOP_STATUS_MASK_TYPE,acId,OBS_TYPE_AC,DEFAULT_ZERO);	
			}

			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		if (0 != tempRtnLen)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的逻辑区段码位信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcCiMaskOfSectionInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*定义通用文件数据指针*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S sectionlId = DEFAULT_ZERO;
	UINT16_S sectionCtOccStatusMaskId = DEFAULT_ZERO;
	UINT16_S sectionUtOccStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*读取文件中的逻辑区段信息总和*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_LOGICSECTION_TYPE)),&maskDataLen,&indexId);

	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*分配内存大小*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_SECTION_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*查询成功*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_SECTION_MASK_LEN)
			{
				/*逻辑区段ID*/
				sectionlId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*逻辑区段CT占用状态码位*/
				sectionCtOccStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*逻辑区段UT占用状态码位*/
				sectionUtOccStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitSendToCiMaskInfo(sectionCtOccStatusMaskId,SECTION_CT_OCC_MASK_TYPE,sectionlId,OBS_TYPE_LS,sectionUtOccStatusMaskId);
				rtnValue &= InitSendToCiMaskInfo(sectionUtOccStatusMaskId,SECTION_UT_OCC_MASK_TYPE,sectionlId,OBS_TYPE_LS,sectionCtOccStatusMaskId);

				/*逻辑区段临时限速码位*/
				/*sectionTsrStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitSendToCiMaskInfo(sectionTsrStatusMaskId,SECTION_TSR_MASK_TYPE,sectionlId,OBS_TYPE_LS,DEFAULT_ZERO);*/		
			}

			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		if (0 != tempRtnLen)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的进路码位信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcCiMaskOfRouteInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*定义通用文件数据指针*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S routeId = DEFAULT_ZERO;
	UINT16_S routeStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;
    UINT16_S stopReqMaskId = DEFAULT_ZERO;
    UINT16_S stopConfirmMaskId = DEFAULT_ZERO;

	/*读取文件中的进路信息总和*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_ROUTECODE_TYPE)),&maskDataLen,&indexId);
	
	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*分配内存大小*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_ROUTE_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*查询成功*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_ROUTE_MASK_LEN)
			{
				/*进路D*/
				routeId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*进路状态码位*/
				routeStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

                /* pbw,20171112 停车保证请求码位 */
                stopReqMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /* pbw,20171112 停车保证确认码位 */
                stopConfirmMaskId  = ShortFromChar(pMaskData);
                pMaskData += 2U;

                rtnValue = InitReceiveToCiMaskInfo(routeStatusMaskId,ROUTE_STATUS_MASK_TYPE,routeId,OBS_TYPE_ROUTE,DEFAULT_ZERO);	

                rtnValue = InitReceiveToCiMaskInfo(stopReqMaskId,ROUTE_STOP_REQUEST_MASK_TYPE,routeId,OBS_TYPE_ROUTE,DEFAULT_ZERO);	

                rtnValue = InitSendToCiMaskInfo(stopConfirmMaskId,ROUTE_STOP_CONFIRM_MASK_TYPE,routeId,OBS_TYPE_ROUTE,DEFAULT_ZERO);rtnValue = InitReceiveToCiMaskInfo(routeStatusMaskId,ROUTE_STATUS_MASK_TYPE,routeId,OBS_TYPE_ROUTE,DEFAULT_ZERO);		
			}

			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		if (0 != tempRtnLen)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的保护区段码位信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcCiMaskOfOverlapInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*定义通用文件数据指针*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S overlapId = DEFAULT_ZERO;
	UINT16_S overlapStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*读取文件中的保护区段信息总和*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_PROSECCODE_TYPE)),&maskDataLen,&indexId);

	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*分配内存大小*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_OVERLAP_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*查询成功*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_OVERLAP_MASK_LEN)
			{
				/*保护区段ID*/
				overlapId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*保护区段状态码位*/
				overlapStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitReceiveToCiMaskInfo(overlapStatusMaskId,OVERLAP_STATUS_MASK_TYPE,overlapId,OBS_TYPE_OVERLAP,DEFAULT_ZERO);		
			}

			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		if (0 != tempRtnLen)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地管理的无人折返码位信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcCiMaskOfDrInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*定义通用文件数据指针*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S drId = DEFAULT_ZERO;
	UINT16_S drLampTwinkleStatusMaskId = DEFAULT_ZERO;
	UINT16_S drLampSteadyStatusMaskId = DEFAULT_ZERO;
	UINT16_S drButtonStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*读取文件中的无人折返信息总和*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_ARCODE_TYPE)),&maskDataLen,&indexId);

	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*分配内存大小*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_DR_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*查询成功*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_DR_MASK_LEN)
			{
				/*无人折返按钮/灯ID*/
				drId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*无人折返灯闪灯码位*/
				drLampTwinkleStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitSendToCiMaskInfo(drLampTwinkleStatusMaskId,DR_LAMP_TWINKLE_STATUS_MASK_TYPE,drId,OBS_TYPE_DRL,DEFAULT_ZERO);

				/*无人折返灯稳灯码位*/
				drLampSteadyStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitSendToCiMaskInfo(drLampSteadyStatusMaskId,DR_LAMP_STEADY_STATUS_MASK_TYPE,drId,OBS_TYPE_DRL,DEFAULT_ZERO);

				/*无人折返按钮状态码位*/
				drButtonStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitReceiveToCiMaskInfo(drButtonStatusMaskId,DR_BUTTON_STATUS_MASK_TYPE,drId,OBS_TYPE_DRB,DEFAULT_ZERO);		
			}

			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		if (0 != tempRtnLen)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}

/*
* 功能描述： 初始化信号机跨压信息
* 参数说明： const UINT16 signalId,信号机ID 
*            const UINT16_S maskId,码位值
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitSignalCrossInfo(const UINT16_S signalId,const UINT16_S maskId)
{
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	belongZcId = GetLineSignalBelongZcId(signalId);

	/*判断信号机所属ZC是否为本ZC*/
	if (DEFAULT_ZERO != belongZcId)
	{
		if (belongZcId == GetLocalZcId())
		{
			if ((DEFAULT_UINT16_VALUE != maskId)
				&& (gSignalCrossNum < SINGLE_ZC_TO_CI_MASK_SUM_MAX))
			{
				gToCiConfigSignalCrossIdBuff[gSignalCrossNum] = signalId;
				gSignalCrossNum++;
			} 
			else
			{
                /*不处理*/
			}
		}
		else
		{
            /*不处理*/
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
* 功能描述： 初始化信号机亮灭信息
* 参数说明： const UINT16 signalId,信号机ID 
*            const UINT16_S maskId,码位值
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitSignalLightOffInfo(const UINT16_S signalId,const UINT16_S maskId)
{
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	belongZcId = GetLineSignalBelongZcId(signalId);

	/*判断信号机所属ZC是否为本ZC*/
	if (DEFAULT_ZERO != belongZcId)
	{
		if (belongZcId == GetLocalZcId())
		{
			if ((DEFAULT_UINT16_VALUE != maskId)
				&& (gSignalLightOffNum < SINGLE_ZC_TO_CI_MASK_SUM_MAX))
			{
				gToCiConfigSignalLightOffIdBuff[gSignalLightOffNum] = signalId;
				gSignalLightOffNum++;
			} 
			else
			{
                /*不处理*/
			}
		}
		else
		{
            /*不处理*/
		}

		rtnValue = RETURN_SUCCESS; 
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
