/************************************************************************
*
* �ļ���   ��  DRInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����۷���ʼ������
* ��  ע   ��  ��
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

extern DRButtonConfigDataStruct gDRButtonConfigDataStruBuff[DR_BUTTON_LOCAL_SUM_MAX];     /*���������۷���ť�������ýṹ��*/
extern UINT16_S gDRButtonIdBuff[DR_BUTTON_SUM_MAX];                                      /*���������۷���ťIDӳ������*/
extern UINT16_S gDRButtonCurSum;                                                        /*���������۷���ť��ǰ����*/

extern DRLampConfigDataStruct gDRLampConfigDataStruBuff[DR_LAMP_LOCAL_SUM_MAX];           /*���������۷���ť�������ýṹ��*/
extern UINT16_S gDRLampIdBuff[DR_LAMP_SUM_MAX];                                          /*���������۷���ťIDӳ������*/
extern UINT16_S gDRLampCurSum;                                                          /*���������۷���ť��ǰ����*/

extern DRButtonDataStruct  gDRButtonDataStruBuff[DR_BUTTON_LOCAL_SUM_MAX];                /*���������۷���ť״̬���ݽṹ��*/
extern DRLampDataStruct gDRLampDataStruBuff[DR_LAMP_LOCAL_SUM_MAX];                       /*���������۷���ť״̬���ݽṹ��*/

/*
* ���������� ��ʼ�����ع���������۷���ť��ʼ��Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
*/
void InitDrButtonInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gDRButtonCurSum = 0U;

	/*��ʼ��ȫ�ֱ���*/
	for (cycle = DEFAULT_ZERO;cycle < DR_BUTTON_SUM_MAX;cycle++)
	{
		gDRButtonIdBuff[cycle] = DR_BUTTON_SUM_MAX;
	}

	/*�豸��ȫ̬����*/
	for (cycle = DEFAULT_ZERO;cycle < DR_BUTTON_LOCAL_SUM_MAX;cycle++)
	{
		gDRButtonDataStruBuff[cycle].DRButtonStatus = DR_BUTTON_STATE_UP;
		gDRLampDataStruBuff[cycle].DRLampCmd = DR_LAMP_DEFAULT_STATUS;
	}
}

/*
* ���������� ��ʼ�����ع���������۷��Ƴ�ʼ��Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
*/
void InitDrLampInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gDRLampCurSum = 0U;

	/*��ʼ��ȫ�ֱ���*/
	for (cycle = DEFAULT_ZERO;cycle < DR_LAMP_SUM_MAX;cycle++)
	{
		gDRLampIdBuff[cycle] = DR_LAMP_SUM_MAX;
	}
}


/*
* ���������� ��ʼ�����ع���������۷���ť��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitDrButtonLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineDrButtonMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ʼ������*/
	InitDrButtonInitializationData();

	lineDrButtonMaxId = GetLineDrButtonMaxId();

	if (DR_BUTTON_SUM_MAX >= lineDrButtonMaxId)
	{
		for (cycle = 1U; cycle <= lineDrButtonMaxId;cycle++)
		{
			/*�жϸ�Id��Ӧ�������۷���ť�Ƿ������л�����*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_DRB);

			/*�жϸ�Id��Ӧ�������۷���ť�Ƿ����ڱ�ZC*/
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

				/*����IDӳ������*/
				gDRButtonIdBuff[cycle] = addIndex;

				/*��д״̬��Ӧ��ID��Ϣ*/
				gDRButtonDataStruBuff[addIndex].DRButtonId = cycle;

				gDRButtonCurSum++;
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
* ���������� ��ʼ�����ع���������۷�����Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitDrLampLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineDrLampMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ʼ������*/
	InitDrLampInitializationData();

	lineDrLampMaxId = GetLineDrLampMaxId();

	if (DR_LAMP_SUM_MAX >= lineDrLampMaxId)
	{
		for (cycle = 1U; cycle <= lineDrLampMaxId;cycle++)
		{
			/*�жϸ�Id��Ӧ�������۷���ť�Ƿ������л�����*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_DRL);

			/*�жϸ�Id��Ӧ�������۷���ť�Ƿ����ڱ�ZC*/
			belongZcId = GetLineDrLampBelongZcId(cycle);

			if ((belongZcId != GetLocalZcId()) && (RETURN_ERROR == rtnOfChangeArea))
			{
				/*�����ڱ�ZC��Ͻ��Χ�����л������ڵ��ϰ���*/
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

				/*����IDӳ������*/
				gDRLampIdBuff[cycle] = addIndex;

				/*��д״̬��Ӧ��ID��Ϣ*/
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
