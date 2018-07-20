/************************************************************************
*
* �ļ���   ��  DRStatusData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����۷�״̬
* ��  ע   ��  ��
*
************************************************************************/
#include "DRStatusData.h"
#include "DRConfigData.h"

/*Local���ݶ���*/
DRButtonDataStruct  gDRButtonDataStruBuff[DR_BUTTON_LOCAL_SUM_MAX];                /*���������۷���ť״̬���ݽṹ��*/
DRLampDataStruct gDRLampDataStruBuff[DR_LAMP_LOCAL_SUM_MAX];                       /*���������۷���״̬���ݽṹ��*/


/*
* ���������� ��ȡ�����۷���ť����
* ����˵���� void    
* ����ֵ  �� �����۷���ť�ṹ�������׵�ַ
*/
DRButtonDataStruct* GetDRButtonStatusData(void)
{
	return gDRButtonDataStruBuff;
}

/*
* ���������� ��ȡ�����۷�������
* ����˵���� void    
* ����ֵ  �������۷��ƽṹ�������׵�ַ
*/
DRLampDataStruct* GetDRLampData(void)
{
	return gDRLampDataStruBuff;
}

/*
* ���������� ��ȡ�����۷���ť�������г�ID
* ����˵���� const UINT16 drButtonId,�����۷���ťID   
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �г�ID
*/
UINT16_S GetDRButtonOfTrainId(const UINT16_S drButtonId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue = gDRButtonDataStruBuff[bufIndex].TrainId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ���������۷���ť�������г�ID
* ����˵���� const UINT16 drButtonId, �����۷���ťID
*            UINT16_S trainId,�г�ID
* ����ֵ  �� 0:��ȡ����ʧ��
*            1����ȡ���ݳɹ�
*/
UINT8_S SetDRButtonOfTrainId(const UINT16_S drButtonId,UINT16_S trainId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRButtonSum())
	{
		gDRButtonDataStruBuff[bufIndex].TrainId = trainId;

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡ�����۷��ƹ����г�ID
* ����˵���� const UINT16 drLampId,�����۷���ID   
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �г�ID
*/
UINT16_S GetDRLampOfTrainId(const UINT16_S drLampId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRLampSum())
	{
		rtnValue = gDRLampDataStruBuff[bufIndex].TrainId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ���������۷��ƹ����г�ID
* ����˵���� const UINT16 drLampId,�����۷���ID  
*            UINT16_S trainId,�г�ID
* ����ֵ  �� 0:��ȡ����ʧ��
*            1����ȡ���ݳɹ�
*/
UINT8_S SetDRLampOfTrainId(const UINT16_S drLampId,UINT16_S trainId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRLampSum())
	{
		gDRLampDataStruBuff[bufIndex].TrainId = trainId;

		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡ�����۷��ƿ�������
* ����˵���� const UINT16 drLampId,�����۷���ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������
*/
UINT8_S GetDRLampCommand(const UINT16_S drLampId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRLampSum())
	{
		rtnValue = gDRLampDataStruBuff[bufIndex].DRLampCmd;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ���������۷��ƿ�������
* ����˵���� const UINT16 drLampId,�����۷���ID  
*            UINT8_S drLampCmd,�����۷�������   
* ����ֵ  �� 0:��ȡ����ʧ��
*            1����ȡ���ݳɹ�
*/
UINT8_S SetDRLampCommand(const UINT16_S drLampId,UINT8_S drLampCmd)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRLampSum())
	{
		if ((DR_LAMP_STEADY_STATUS == drLampCmd) || (DR_LAMP_TWINKLE_STATUS == drLampCmd))
		{
			gDRLampDataStruBuff[bufIndex].DRLampCmd = drLampCmd;

			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡ�����۷���ť��ǰ״̬
* ����˵���� const UINT16 drButtonId,�����۷���ťID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������
*/
UINT8_S GetDRButtonStatus(const UINT16_S drButtonId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue = gDRButtonDataStruBuff[bufIndex].DRButtonStatus;
	}
	else
	{
		rtnValue = DEFAULT_ZERO;
	}

	return rtnValue;
}

/*
* ���������� ���������۷���ť��������
* ����˵���� const UINT16 drButtonId,�����۷���ťID  
*            UINT8_S drButtonStatus,�����۷���ť����   
* ����ֵ  �� 0:��ȡ����ʧ��
*            1����ȡ���ݳɹ�
*/
UINT8_S SetDRButtonStatus(const UINT16_S drButtonId,UINT8_S drButtonStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRButtonSum())
	{
		if ((DR_BUTTON_STATE_DOWN == drButtonStatus) || (DR_BUTTON_STATE_UP == drButtonStatus))
		{
			gDRButtonDataStruBuff[bufIndex].DRButtonStatus = drButtonStatus;

			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
