/************************************************************************
*
* �ļ���   ��  SwitchStatusData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����״̬����
* ��  ע   ��  ��
*
************************************************************************/
#include "SwitchStatusData.h"
#include "SwitchConfigData.h"

SwitchDataStruct gSwitchStatusDataStruBuff[SWITCH_LOCAL_SUM_MAX];          /*���ع���ĵ���״̬��Ϣ*/

/*
* ���������� ��ȡ��������
* ����˵���� void    
* ����ֵ  �� NULL: ��ȡ����ʧ��
*			 !NULL: ��������
*/
SwitchDataStruct* GetSwitchStatusData(void)
{
	return gSwitchStatusDataStruBuff;
}

/*
* ���������� ��ȡ����ǰ״̬
* ����˵���� const UINT16 switchId ����ID    
* ����ֵ  �� 3: ��ȡ����ʧ��
*			������3: ����״̬
*/
UINT8_S GetSwitchPosStatus(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*��ȡ�����±�*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchStatusDataStruBuff[bufIndex].SwitchPosStatus;
	}
	else
	{
		rtnValue = SWITCH_STATE_LOSE;
	}

	return rtnValue;
}

/*
* ���������� ���õ���ǰ״̬
* ����˵���� const UINT16 switchId ����ID; 
*	         UINT8_S  SwitchPosStatus ����״̬    
* ����ֵ  �� 0;ʧ��
*            1;�ɹ�
*/
UINT8_S SetSwitchPosStatus(const UINT16_S switchId,UINT8_S switchPosStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*��ȡ�����±�*/

	if (bufIndex < GetSwitchSum())
	{
		if ((SWITCH_STATE_MAIN == switchPosStatus) 
			|| (SWITCH_STATE_SIDE == switchPosStatus)
			|| (SWITCH_STATE_LOSE == switchPosStatus))
		{
			gSwitchStatusDataStruBuff[bufIndex].SwitchPosStatus = switchPosStatus;
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
* ���������� ��ȡ��������״̬
* ����˵���� const UINT16 switchId ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������״̬
*/
UINT8_S GetSwitchLock(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*��ȡ�����±�*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchStatusDataStruBuff[bufIndex].SwitchLock;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ���õ�������״̬
* ����˵���� const UINT16 switchId ����ID; 
*	         UINT8_S  lockStatus ��������״̬    
* ����ֵ  �� 0;ʧ��
*            1;�ɹ�
*/
UINT8_S SetSwitchLock(const UINT16_S switchId,UINT8_S lockStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*��ȡ�����±�*/

	if (bufIndex < GetSwitchSum())
	{
		if ((SWITCH_STATE_LOCK == lockStatus) || (SWITCH_STATE_UNLOCK == lockStatus))
		{
			gSwitchStatusDataStruBuff[bufIndex].SwitchLock = lockStatus;
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
