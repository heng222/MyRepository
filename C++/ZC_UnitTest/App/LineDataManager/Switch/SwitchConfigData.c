/************************************************************************
*
* �ļ���   ��  SwitchConfigData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����������ݹ���
* ��  ע   ��  ��
*
************************************************************************/
#include "SwitchConfigData.h"

SwitchConfigDataStruct gSwitchConfigDataStruBuff[SWITCH_LOCAL_SUM_MAX];             /*���ع���ĵ�����Ϣ*/
UINT16_S gSwitchIdBuff[SWITCH_SUM_MAX] = {0U};                                      /*�������ӳ������*/
UINT16_S gSwitchCurSum = 0U;                                                       /*����ǰ����*/

/*
* ���������� ��ȡ�����������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ǰ����
*/
UINT16_S GetSwitchSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gSwitchCurSum >= SWITCH_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gSwitchCurSum;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������±��Ӧ�ĵ���ID
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ID      
*/
UINT16_S GetSwitchId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchConfigDataStruBuff[bufIndex].SwitchId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID����������
* ����˵���� const UINT16 switchId,����ID
* ����ֵ  �� SWITCH_SUM_MAX; ��ȡ����ʧ��
*			 >0U; ���������ɹ�
*/
UINT16_S GetSwitchConfigBufIndex(const UINT16_S switchId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((switchId >= 1U)&&(switchId < SWITCH_SUM_MAX))
	{
		rtnValue = gSwitchIdBuff[switchId];
	}
	else
	{
		rtnValue = SWITCH_SUM_MAX;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��IDվ̨������������ID
* ����˵���� const UINT16 switchId,����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������ID      
*/
UINT8_S GetSwitchBelongCiId(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*��ȡ�����±�*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��������ZC��ID
* ����˵���� const UINT16 switchId, ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ZcID      
*/
UINT8_S GetSwitchBelongZcId(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*��ȡ�����±�*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��������������
* ����˵���� const UINT16 switchId, ����ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT16_S GetSwitchChangeAttribute(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*��ȡ�����±�*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID����λ������
* ����˵���� const UINT16 switchId, ����ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT16_S GetSwitchPosition(const UINT16_S switchId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSwitchConfigBufIndex(switchId);  /*��ȡ�����±�*/

	if (bufIndex < GetSwitchSum())
	{
		rtnValue = gSwitchConfigDataStruBuff[bufIndex].SwitchPosition;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
