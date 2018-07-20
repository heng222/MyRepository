/************************************************************************
*
* �ļ���   ��  MaskInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��λ��ʼ������
* ��  ע   ��  ��
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

extern ZcCiMaskConfigDataStruct gZcToCiMaskConfigDataStruBuff[COMM_CI_SUM_MAX];                        /*����ZC-CI��λ��Ϣ�ṹ��*/
extern UINT16_S gZcToCiIdBuff[LINE_CI_SUM_MAX];                                                       /*����ZC��Ciͨ��ID��������*/
extern UINT8_S  gZcToCiCurSum;                                                                       /*����ZC���CI���������*/

extern ZcCiMaskConfigDataStruct gCiToZcMaskConfigDataStruBuff[COMM_CI_SUM_MAX];                        /*����CI-ZC��λ��Ϣ�ṹ��*/
extern UINT16_S gCiToZiIdBuff[LINE_CI_SUM_MAX];                                                       /*����CI������������*/
extern UINT8_S  gCiToZcCurSum;                                                                       /*����CI����ZC���������*/

extern UINT16_S gToCiConfigSignalCrossIdBuff[SINGLE_ZC_TO_CI_MASK_SUM_MAX];                         /*���屾ZC��Ҫ������źŻ���ѹ*/
extern UINT16_S gSignalCrossNum;

extern UINT16_S gToCiConfigSignalLightOffIdBuff[SINGLE_ZC_TO_CI_MASK_SUM_MAX];                     /*���屾ZC��Ҫ������źŻ�����*/
extern UINT16_S gSignalLightOffNum;

/*
* ���������� ��ʼ�����ع������λ��Ϣ�еĻ�����Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
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
* ���������� ��ȡ�豸����������ID
* ����˵���� const UINT16 devId, �豸ID
*            const UINT8_S devType,�豸����
* ����ֵ  �� 0: ��ȡʧ��
*			>0: ����CIID      
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
* ���������� ��ʼ�����ع������λ��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitZcCiMaskLocalInfo(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ʼ����λ��Ϣ*/
	InitMaskValueData();

	/*��ʼ��ͨ�Ŷ�����Ϣ*/
	rtnValue = InitZcCiMaskConfigCommTargetData();

	/*��ʼ��������λ*/
	rtnValue &= InitZcCiMaskOfSwitchInfo();

	/*��ʼ���źŻ���λ*/
	rtnValue &= InitZcCiMaskOfSignalInfo();

	/*��ʼ����������λ*/
	rtnValue &= InitZcCiMaskOfPsdInfo();

	/*��ʼ������ͣ����ť��λ*/
	rtnValue &= InitZcCiMaskOfEsbInfo();

	/*��ʼ������������λ*/
	rtnValue &= InitZcCiMaskOfAcInfo();

	/*��ʼ���߼�������λ*/
	rtnValue &= InitZcCiMaskOfSectionInfo();

	/*��ʼ����·��λ*/
	rtnValue &= InitZcCiMaskOfRouteInfo();

	/*��ʼ������������λ*/
	rtnValue &= InitZcCiMaskOfOverlapInfo();
	
	/*��ʼ�������۷���λ*/
	rtnValue &= InitZcCiMaskOfDrInfo();

	return rtnValue;
}

/*
* ���������� ��ʼ����λ������Ϣ��ͨѶ����
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			 1: ��ʼ���ɹ�      
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
* ���������� ��ʼ�����ع���ķ��͸�CIϵͳ����λ��Ϣ
* ����˵���� UINT16 maskId;��λID
*            UINT8_S maskType;��λ����
*            UINT16_S devId;�豸ID
*            UINT8_S devType;�豸����
*            UINT16_S relevanceMaskId;������λID
* ����ֵ  �� 0: ��ʼ��ʧ��
*			 1: ��ʼ���ɹ�      
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
			/*�жϸ���λ�Ƿ����ڱ�����Ϣ��*/
			sendMaskBufIndex = GetSendMaskBufIndex(maskId,INNER_DEVTYPE_CI,belongCiId);

			if (ZC_TO_CI_MASK_SUM_MAX == sendMaskBufIndex)
			{
				/*��δ��д����λ��Ϣ*/
				/*��λ����*/
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

					/*������λ���ֵ*/
					if (maskId > gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskIdMax)
					{
						gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskIdMax = maskId;
					} 
					else
					{
                        /*������*/
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
				/*����д����λ��Ϣ*/
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
			/*����д����λֵ*/
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ʼ�����ع���Ľ���CI����ZCϵͳ����λ��Ϣ
* ����˵���� UINT16 maskId;��λID
*            UINT8_S maskType;��λ����
*            UINT16_S devId;�豸ID
*            UINT8_S devType;�豸����
*            UINT16_S relevanceMaskId;������λID
* ����ֵ  �� 0: ��ʼ��ʧ��
*			 1: ��ʼ���ɹ�      
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
			/*�жϸ���λ�Ƿ����ڱ�����Ϣ��*/
			receiveMaskBufIndex = GetReceiveMaskBufIndex(maskId,INNER_DEVTYPE_CI,belongCiId);

			if (ZC_TO_CI_MASK_SUM_MAX == receiveMaskBufIndex)
			{
				/*��δ��д����λ��Ϣ*/
				/*��λ����*/
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

					/*������λ���ֵ*/
					if (maskId > gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskIdMax)
					{
						gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskIdMax = maskId;
					} 
					else
					{
                        /*������*/
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
				/*����д����λ��Ϣ*/
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
			/*����λֵ��Ч,����д*/
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ʼ�����ع���ĵ�����λ��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitZcCiMaskOfSwitchInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*����ͨ���ļ�����ָ��*/
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

	/*��ȡ�ļ��еĵ�����Ϣ�ܺ�*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_SWITCHCODE_TYPE)),&maskDataLen,&indexId);
	
	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*�����ڴ��С*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_SWITCH_MASK_LEN)),maskDataLen,indexId,pMaskData);
		
		if (0 == tempRtnData)
		{
			/*��ѯ�ɹ�*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_SWITCH_MASK_LEN)
			{
				/*����ID*/
				switchId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*����λ��λ*/
				switchFrontMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*����λ��λ*/
				switchSideMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitReceiveToCiMaskInfo(switchFrontMaskId,SWITCH_FRONT_MASK_TYPE,switchId,OBS_TYPE_POINT,switchSideMaskId);		
				rtnValue &= InitReceiveToCiMaskInfo(switchSideMaskId,SWITCH_SIDE_MASK_TYPE,switchId,OBS_TYPE_POINT,switchFrontMaskId);

				/*����������λ*/
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
* ���������� ��ʼ�����ع�����źŻ���λ��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitZcCiMaskOfSignalInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*����ͨ���ļ�����ָ��*/
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

	/*��ȡ�ļ��е��źŻ���Ϣ�ܺ�*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_SIGNCODE_TYPE)),&maskDataLen,&indexId);
	
	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*�����ڴ��С*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_SIGNAL_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*��ѯ�ɹ�*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_SIGNAL_MASK_LEN)
			{
				/*�źŻ�ID*/
				signalId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*�źŻ�״̬��λ*/
				signalStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitReceiveToCiMaskInfo(signalStatusMaskId,SIGNAL_STATUS_MASK_TYPE,signalId,OBS_TYPE_SIGNAL,DEFAULT_ZERO);

				/*�źŻ���ѹ��λ*/
				signalCrossMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitSignalCrossInfo(signalId,signalCrossMaskId);

				rtnValue &= InitSendToCiMaskInfo(signalCrossMaskId,SIGNAL_CROSS_MASK_TYPE,signalId,OBS_TYPE_SIGNAL,DEFAULT_ZERO);

				/*�źŻ�������λ*/
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
* ���������� ��ʼ�����ع������������λ��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitZcCiMaskOfPsdInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*����ͨ���ļ�����ָ��*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S psdId = DEFAULT_ZERO;
	UINT16_S psdStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*��ȡ�ļ��е�Psd��Ϣ�ܺ�*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_PSDCODE_TYPE)),&maskDataLen,&indexId);

	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*�����ڴ��С*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_PSD_MASK_LEN)),maskDataLen,indexId,pMaskData);

		/*��ѯ�ɹ�*/
		if (0 == tempRtnData)
		{
			/*��ѯ�ɹ�*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_PSD_MASK_LEN)
			{
				/*������ID*/
				psdId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*������״̬��λ*/
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
* ���������� ��ʼ�����ع���Ľ���ͣ����ť��λ��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitZcCiMaskOfEsbInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*����ͨ���ļ�����ָ��*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S esbId = DEFAULT_ZERO;
	UINT16_S esbStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*��ȡ�ļ��е�ESB��Ϣ�ܺ�*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_ESBCODE_TYPE)),&maskDataLen,&indexId);
	
	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*�����ڴ��С*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_ESB_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*��ѯ�ɹ�*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_ESB_MASK_LEN)
			{
				/*����ͣ����ťID*/
				esbId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*����ͣ����ť״̬��λ*/
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
* ���������� ��ʼ�����ع���ļ���������λ��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitZcCiMaskOfAcInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*����ͨ���ļ�����ָ��*/
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

	/*��ȡ�ļ��е�ac��Ϣ�ܺ�*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_AXLESECCODE_TYPE)),&maskDataLen,&indexId);
	
	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*�����ڴ��С*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_AC_SGMT_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*��ѯ�ɹ�*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_AC_SGMT_MASK_LEN)
			{
				/*��������ID*/
				acId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*�����������з���״̬��λ*/
				acUpDirMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*�����������з���״̬��λ*/
				acDownDirMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitReceiveToCiMaskInfo(acUpDirMaskId,AC_UP_DIR_MASK_TYPE,acId,OBS_TYPE_AC,acDownDirMaskId);	
				rtnValue &= InitReceiveToCiMaskInfo(acDownDirMaskId,AC_DOWN_DIR_MASK_TYPE,acId,OBS_TYPE_AC,acUpDirMaskId);	

				/*��������ռ��״̬��λ*/
				acOccStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitReceiveToCiMaskInfo(acOccStatusMaskId,AC_OCC_STATUS_MASK_TYPE,acId,OBS_TYPE_AC,DEFAULT_ZERO);	

				/*������������״̬��λ*/
				acLockStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitReceiveToCiMaskInfo(acLockStatusMaskId,AC_LOCK_STATUS_MASK_TYPE,acId,OBS_TYPE_AC,DEFAULT_ZERO);	

				/*��������ARB״̬��λ*/
				acArbStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitSendToCiMaskInfo(acArbStatusMaskId,AC_ARB_STATUS_MASK_TYPE,acId,OBS_TYPE_AC,DEFAULT_ZERO);	

				/*���������г�ͣ��״̬��λ*/
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
* ���������� ��ʼ�����ع�����߼�������λ��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitZcCiMaskOfSectionInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*����ͨ���ļ�����ָ��*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S sectionlId = DEFAULT_ZERO;
	UINT16_S sectionCtOccStatusMaskId = DEFAULT_ZERO;
	UINT16_S sectionUtOccStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*��ȡ�ļ��е��߼�������Ϣ�ܺ�*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_LOGICSECTION_TYPE)),&maskDataLen,&indexId);

	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*�����ڴ��С*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_SECTION_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*��ѯ�ɹ�*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_SECTION_MASK_LEN)
			{
				/*�߼�����ID*/
				sectionlId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*�߼�����CTռ��״̬��λ*/
				sectionCtOccStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*�߼�����UTռ��״̬��λ*/
				sectionUtOccStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitSendToCiMaskInfo(sectionCtOccStatusMaskId,SECTION_CT_OCC_MASK_TYPE,sectionlId,OBS_TYPE_LS,sectionUtOccStatusMaskId);
				rtnValue &= InitSendToCiMaskInfo(sectionUtOccStatusMaskId,SECTION_UT_OCC_MASK_TYPE,sectionlId,OBS_TYPE_LS,sectionCtOccStatusMaskId);

				/*�߼�������ʱ������λ*/
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
* ���������� ��ʼ�����ع���Ľ�·��λ��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitZcCiMaskOfRouteInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*����ͨ���ļ�����ָ��*/
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

	/*��ȡ�ļ��еĽ�·��Ϣ�ܺ�*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_ROUTECODE_TYPE)),&maskDataLen,&indexId);
	
	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*�����ڴ��С*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_ROUTE_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*��ѯ�ɹ�*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_ROUTE_MASK_LEN)
			{
				/*��·D*/
				routeId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*��·״̬��λ*/
				routeStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

                /* pbw,20171112 ͣ����֤������λ */
                stopReqMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /* pbw,20171112 ͣ����֤ȷ����λ */
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
* ���������� ��ʼ�����ع���ı���������λ��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitZcCiMaskOfOverlapInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*����ͨ���ļ�����ָ��*/
	UINT32_S maskDataLen = DEFAULT_ZERO;
	UINT16_S cycleMaskData = DEFAULT_ZERO;
	UINT16_S overlapId = DEFAULT_ZERO;
	UINT16_S overlapStatusMaskId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S indexId = DEFAULT_ZERO;
	INT8_S tempRtnLen = 0;
	INT8_S tempRtnData = 0;

	/*��ȡ�ļ��еı���������Ϣ�ܺ�*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_PROSECCODE_TYPE)),&maskDataLen,&indexId);

	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*�����ڴ��С*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_OVERLAP_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*��ѯ�ɹ�*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_OVERLAP_MASK_LEN)
			{
				/*��������ID*/
				overlapId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*��������״̬��λ*/
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
* ���������� ��ʼ�����ع���������۷���λ��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitZcCiMaskOfDrInfo(void)
{
	UINT8_S *pMaskData = NULL;                                  /*����ͨ���ļ�����ָ��*/
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

	/*��ȡ�ļ��е������۷���Ϣ�ܺ�*/
	tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_CI_INTERCODE_TYPE)),((UINT8_S)(ZC_CI_ARCODE_TYPE)),&maskDataLen,&indexId);

	if ((0 == tempRtnLen)
		&& (0U < maskDataLen))
	{
		/*�����ڴ��С*/
		pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
		tempRtnData = GetConfigData(((UINT16_S)(CI_ZC_DR_MASK_LEN)),maskDataLen,indexId,pMaskData);

		if (0 == tempRtnData)
		{
			/*��ѯ�ɹ�*/
			for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += CI_ZC_DR_MASK_LEN)
			{
				/*�����۷���ť/��ID*/
				drId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				/*�����۷���������λ*/
				drLampTwinkleStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue = InitSendToCiMaskInfo(drLampTwinkleStatusMaskId,DR_LAMP_TWINKLE_STATUS_MASK_TYPE,drId,OBS_TYPE_DRL,DEFAULT_ZERO);

				/*�����۷����ȵ���λ*/
				drLampSteadyStatusMaskId = ShortFromChar(pMaskData);
				pMaskData += 2U;

				rtnValue &= InitSendToCiMaskInfo(drLampSteadyStatusMaskId,DR_LAMP_STEADY_STATUS_MASK_TYPE,drId,OBS_TYPE_DRL,DEFAULT_ZERO);

				/*�����۷���ť״̬��λ*/
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
* ���������� ��ʼ���źŻ���ѹ��Ϣ
* ����˵���� const UINT16 signalId,�źŻ�ID 
*            const UINT16_S maskId,��λֵ
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitSignalCrossInfo(const UINT16_S signalId,const UINT16_S maskId)
{
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	belongZcId = GetLineSignalBelongZcId(signalId);

	/*�ж��źŻ�����ZC�Ƿ�Ϊ��ZC*/
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
                /*������*/
			}
		}
		else
		{
            /*������*/
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
* ���������� ��ʼ���źŻ�������Ϣ
* ����˵���� const UINT16 signalId,�źŻ�ID 
*            const UINT16_S maskId,��λֵ
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitSignalLightOffInfo(const UINT16_S signalId,const UINT16_S maskId)
{
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	belongZcId = GetLineSignalBelongZcId(signalId);

	/*�ж��źŻ�����ZC�Ƿ�Ϊ��ZC*/
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
                /*������*/
			}
		}
		else
		{
            /*������*/
		}

		rtnValue = RETURN_SUCCESS; 
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
