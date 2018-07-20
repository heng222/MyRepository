/************************************************************************
*
* �ļ���   ��  SignalStatusData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �źŻ�״̬����
* ��  ע   ��  ��
*
************************************************************************/
#include "SignalStatusData.h"
#include "SignalConfigData.h"

SignalDataStruct gSignalDataStruBuff[SIGNAL_LOCAL_SUM_MAX];          /*���ع���ı�������״̬��Ϣ*/

/*
	* ���������� ��ȡ�źŻ�����
	* ����˵���� void    
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*			 !NULL: �źŻ�����
	*/
SignalDataStruct* GetSignalStatusData(void)
{
	return gSignalDataStruBuff;
}

/*
* ���������� ��ȡ�źŻ���ǰ״̬
* ����˵���� const UINT16  signalId �źŻ�ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �źŻ�״̬
*/
UINT8_S GetSignalStatus(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalDataStruBuff[bufIndex].SignalStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� �����źŻ���ǰ״̬
* ����˵���� const UINT16 signalId �źŻ�ID; 
*            UINT8_S signalStatus �źŻ�״̬    
* ����ֵ  �� 0;ʧ��
*            1;�ɹ�
*/
UINT8_S SetSignalStatus(const UINT16_S signalId,UINT8_S signalStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		if ((SIGNAL_STATE_PASS == signalStatus) || (SIGNAL_STATE_STOP == signalStatus))
		{
			gSignalDataStruBuff[bufIndex].SignalStatus = signalStatus;
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
* ���������� ��ȡ�źŻ��źŻ�����״̬
* ����˵���� const UINT16 signalId �źŻ�ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �źŻ�״̬
*/
UINT8_S GetSignalLightOffStatus(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalDataStruBuff[bufIndex].LightOffStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� �����źŻ��źŻ�����״̬
* ����˵���� const UINT16 signalId �źŻ�ID; 
*	         UINT8_S  lightOffStatus �źŻ�״̬    
* ����ֵ  �� 0;ʧ��
*            1;�ɹ�
*/
UINT8_S SetSignalLightOffStatus(const UINT16_S signalId,UINT8_S lightOffStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		if ((SIGNAL_OFF_COMMAND == lightOffStatus) || (SIGNAL_LIGHT_COMMAND == lightOffStatus))
		{
			gSignalDataStruBuff[bufIndex].LightOffStatus = lightOffStatus;
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
* ���������� ��ȡ�źŻ��г���ѹ�źŻ�״̬
* ����˵���� const UINT16 signalId �źŻ�ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �źŻ�״̬
*/
UINT8_S GetSignalCrossStatus(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalDataStruBuff[bufIndex].CrossStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� �����źŻ��г���ѹ�źŻ�״̬
* ����˵���� const UINT16 signalId �źŻ�ID; 
*	         UINT8_S  crossStatus �źŻ�״̬    
* ����ֵ  �� 0;ʧ��
*            1;�ɹ�
*/
UINT8_S SetSignalCrossStatus(const UINT16_S signalId,UINT8_S crossStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		if ((SIGNAL_TRAIN_ALREADY_CROSS == crossStatus) || (SIGNAL_TRAIN_NOT_CROSS == crossStatus))
		{
			gSignalDataStruBuff[bufIndex].CrossStatus = crossStatus;
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
