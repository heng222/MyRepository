/************************************************************************
*
* �ļ���   ��  SignalInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �źŻ���ʼ������
* ��  ע   ��  ��
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

extern SignalConfigDataStruct gSignalConfigDataStruBuff[SIGNAL_LOCAL_SUM_MAX];            /*���ñ��ع�����źŻ�������Ϣ*/
extern UINT16_S gSignalIdBuff[SIGNAL_SUM_MAX];                  /*�����źŻ�ӳ������*/
extern UINT16_S gSignalCurSum;                                                      /*�����źŻ���ǰ����*/
extern SignalDataStruct gSignalDataStruBuff[SIGNAL_LOCAL_SUM_MAX];                        /*���ñ��ع���ı�������״̬��Ϣ*/

/*
* ���������� ��ʼ�����ع�����źŻ���ʼ��Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
*/
void InitSignalInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gSignalCurSum = 0U;

	/*��ʼ��ȫ�ֱ���*/
	for (cycle = DEFAULT_ZERO;cycle < SIGNAL_SUM_MAX;cycle++)
	{
		gSignalIdBuff[cycle] = SIGNAL_SUM_MAX;
	}

	/*״̬��ȫ�ദ��*/
	for (cycle = DEFAULT_ZERO;cycle < SIGNAL_LOCAL_SUM_MAX;cycle++)
	{
		gSignalDataStruBuff[cycle].SignalStatus = SIGNAL_STATE_STOP;

		gSignalDataStruBuff[cycle].LightOffStatus = SIGNAL_LIGHT_COMMAND;

		gSignalDataStruBuff[cycle].CrossStatus = SIGNAL_TRAIN_ALREADY_CROSS;
	}
}

/*
* ���������� ��ʼ�����ع�����źŻ���Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
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

	/*��ʼ������*/
	InitSignalInitializationData();

	lineSignalMaxId = GetLineSignalMaxId();

	if (SIGNAL_SUM_MAX >= lineSignalMaxId)
	{
		for (cycle = 1U; cycle <= lineSignalMaxId;cycle++)
		{
			/*�жϸ�Id�Ƿ������л�����*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_SIGNAL);

			/*�жϸ�Id�Ƿ����ڱ�ZC*/
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

				/*���źŻ���CI��λ�е��źŻ�,��Ҫ��ѯĬ��״̬��CT���ӽ�ʱ��״̬*/			
				defualtStatus = (UINT8_S)(GetZcSignInfoDataStrulightFlag(cycle));

				switch (defualtStatus)
				{
					case 0x00U:
						/*Ĭ�ϳ�̬��Ҫ���*/
						gSignalConfigDataStruBuff[addIndex].DefaultStatus = (UINT8_S)SIGNAL_OFF_COMMAND;	

						/*CBTC�г��ӽ�Ĭ����Ҫ���*/
						gSignalConfigDataStruBuff[addIndex].CbtcLightOffType = (UINT8_S)SIGNAL_OFF_COMMAND;
						break;

					case 0x01U:
						/*Ĭ�ϳ�̬��Ҫ����*/
						gSignalConfigDataStruBuff[addIndex].DefaultStatus = (UINT8_S)SIGNAL_LIGHT_COMMAND;

						/*CBTC�г��ӽ�Ĭ����Ҫ���*/
						gSignalConfigDataStruBuff[addIndex].CbtcLightOffType = (UINT8_S)SIGNAL_OFF_COMMAND;
						break;

					case 0x02U:
						/*Ĭ�ϳ�̬��Ҫ���*/
						gSignalConfigDataStruBuff[addIndex].DefaultStatus = (UINT8_S)SIGNAL_OFF_COMMAND;

						/*CBTC�г��ӽ�Ĭ����Ҫ����*/
						gSignalConfigDataStruBuff[addIndex].CbtcLightOffType = (UINT8_S)SIGNAL_LIGHT_COMMAND;
						break;

					case 0x03U:
						/*Ĭ�ϳ�̬��Ҫ����*/
						gSignalConfigDataStruBuff[addIndex].DefaultStatus = (UINT8_S)SIGNAL_LIGHT_COMMAND;

						/*CBTC�г��ӽ�Ĭ����Ҫ����*/
						gSignalConfigDataStruBuff[addIndex].CbtcLightOffType = (UINT8_S)SIGNAL_LIGHT_COMMAND;
						break;

					default:
						/*Ĭ�ϳ�̬��Ҫ����*/
						gSignalConfigDataStruBuff[addIndex].DefaultStatus = (UINT8_S)SIGNAL_LIGHT_COMMAND;

						/*CBTC�г��ӽ�Ĭ����Ҫ����*/
						gSignalConfigDataStruBuff[addIndex].CbtcLightOffType = (UINT8_S)SIGNAL_LIGHT_COMMAND;
						break;
				}

				/*����IDӳ������*/
				gSignalIdBuff[cycle] = addIndex;

				/*��д״̬��Ӧ��ID��Ϣ*/
				gSignalDataStruBuff[addIndex].SignalId = cycle;

				gSignalCurSum++;
				addIndex++;
			} 
			else
			{
				/*�����ڱ�ZC��Ͻ��Χ�����л������ڵ��ϰ���*/
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
* ���������� ��ʼ�����ع�����źŻ��������Ϣ
* ����˵���� const UINT16 signalId���źŻ�ID   
* ����ֵ  �� 0: ʧ��
*			 0x55: ����
*            0xaa: ������
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
                /*������*/
			}
		}

		if (FLAG_SET != rtnValue)
		{
			rtnValue = FLAG_UNSET;
		} 
		else
		{
            /*������*/
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ʼ�����ع�����źŻ���ѹ��Ϣ
* ����˵���� const UINT16 signalId���źŻ�ID   
* ����ֵ  �� 0: ʧ��
*			 0x55: ����
*            0xaa: ������
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
                /*������*/
			}
		}

		if (FLAG_SET != rtnValue)
		{
			rtnValue = FLAG_UNSET;
		} 
		else
		{
            /*������*/
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
