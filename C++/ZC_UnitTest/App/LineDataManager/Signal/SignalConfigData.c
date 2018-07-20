/************************************************************************
*
* �ļ���   ��  SignalConfigData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �źŻ���������
* ��  ע   ��  ��
*
************************************************************************/
#include "SignalConfigData.h"

SignalConfigDataStruct gSignalConfigDataStruBuff[SIGNAL_LOCAL_SUM_MAX];            /*���ع�����źŻ�������Ϣ*/
UINT16_S gSignalIdBuff[SIGNAL_SUM_MAX] = {SIGNAL_LOCAL_SUM_MAX};                  /*�����źŻ�ӳ������*/
UINT16_S gSignalCurSum = 0U;                                                      /*�źŻ���ǰ����*/

/*
* ���������� ��ȡ�źŻ���������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �źŻ���ǰ����
*/
UINT16_S GetSignalSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gSignalCurSum >= SIGNAL_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gSignalCurSum;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������±��Ӧ���źŻ�ID
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �źŻ�ID      
*/
UINT16_S GetSignalId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].SignalId;
	} 
	else
	{
		rtnValue = gSignalCurSum;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�źŻ�������
* ����˵���� const UINT16 signalId,�źŻ�ID
* ����ֵ  �� SIGNAL_SUM_MAX ;��ȡ����ʧ��
*			 >0U; ���������ɹ�
*/
UINT16_S GetSignalConfigBufIndex(const UINT16_S signalId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((signalId >= 1U)&&(signalId < SIGNAL_SUM_MAX))
	{
		rtnValue = gSignalIdBuff[signalId];
	}
	else
	{
		rtnValue = SIGNAL_SUM_MAX;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��IDվ̨�źŻ���������ID
* ����˵���� const UINT16 signalId,�źŻ�ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������ID      
*/
UINT8_S GetSignalBelongCiId(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�źŻ�����ZC��ID
* ����˵���� const UINT16 signalId, �źŻ�ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ZcID      
*/
UINT8_S GetSignalBelongZcId(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�źŻ�������������
* ����˵���� const UINT16 signalId, �źŻ�ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT16_S GetSignalChangeAttribute(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�źŻ�����
* ����˵���� const UINT16 signalId, �źŻ�ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetSignalSignalType(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].SignalType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�źŻ���������
* ����˵���� const UINT16 signalId, �źŻ�ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetSignalProtectDir(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].ProtectDir;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�źŻ�Ĭ��״̬
* ����˵���� const UINT16 signalId, �źŻ�ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetSignalDefaultStatus(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].DefaultStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�źŻ��Ƿ���Ҫ�ж�����״̬
* ����˵���� const UINT16 signalId, �źŻ�ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetSignalLightOffType(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].LightOffType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�źŻ�CBTC�����µ������״̬
* ����˵���� const UINT16 signalId, �źŻ�ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetSignalCbtcLightOffType(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].CbtcLightOffType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�źŻ��Ƿ���Ҫ�жϿ�ѹ״̬
* ����˵���� const UINT16 signalId, �źŻ�ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetSignalCrossType(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].CrossType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�źŻ��Ƿ���Ҫ�жϴ�������źŻ�����
* ����˵���� const UINT16 signalId, �źŻ�ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetSignalCrashType(const UINT16_S signalId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetSignalConfigBufIndex(signalId);  /*��ȡ�����±�*/

	if (bufIndex < GetSignalSum())
	{
		rtnValue = gSignalConfigDataStruBuff[bufIndex].CrashType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
