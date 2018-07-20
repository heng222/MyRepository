/************************************************************************
*
* �ļ���   ��  DRConfigData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����۷���������
* ��  ע   ��  ��
*
************************************************************************/
#include "DRConfigData.h"


DRButtonConfigDataStruct gDRButtonConfigDataStruBuff[DR_BUTTON_LOCAL_SUM_MAX];     /*���������۷���ť�������ýṹ��*/
UINT16_S gDRButtonIdBuff[DR_BUTTON_SUM_MAX] = {DR_BUTTON_LOCAL_SUM_MAX};          /*���������۷���ťIDӳ������*/
UINT16_S gDRButtonCurSum = 0U;                                                    /*�����۷���ť��ǰ����*/

DRLampConfigDataStruct gDRLampConfigDataStruBuff[DR_LAMP_LOCAL_SUM_MAX];           /*���������۷���ť�������ýṹ��*/
UINT16_S gDRLampIdBuff[DR_LAMP_SUM_MAX] = {DR_LAMP_LOCAL_SUM_MAX};                /*���������۷���ťIDӳ������*/
UINT16_S gDRLampCurSum = 0U;                                                      /*�����۷���ť��ǰ����*/


/*
* ���������� ��ȡ�����۷���ť��������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �����۷���ť��ǰ����
*/
UINT16_S GetDRButtonSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gDRButtonCurSum >= DR_BUTTON_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	}
	else
	{
		rtnValue = gDRButtonCurSum;
	}

	return rtnValue;
}

/*
* ���������� ��ȡ�����۷��ƹ�������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �����۷��Ƶ�ǰ����
*/
UINT16_S GetDRLampSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gDRLampCurSum >= DR_LAMP_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	}
	else
	{
		rtnValue = gDRLampCurSum;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������±��Ӧ�������۷���ťID
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �����۷���ťID      
*/
UINT16_S GetDRButtonId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue =  gDRButtonConfigDataStruBuff[bufIndex].DRButtonId;
	}
	else
	{
		rtnValue =  RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������±��Ӧ�������۷�����ID
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �����۷���ID    
*/
UINT16_S GetDRLampId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetDRLampSum())
	{
		rtnValue = gDRLampConfigDataStruBuff[bufIndex].DRLampId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������۷���ťID������
* ����˵���� const UINT16 drButtonId, �����۷���ťID
* ����ֵ  �� DR_BUTTON_LOCAL_SUM_MAX: ��ȡ����ʧ��
*			<DR_BUTTON_LOCAL_SUM_MAX: ���ҳɹ�
*/
UINT16_S GetDRButtonConfigBufIndex(const UINT16_S drButtonId)
{
	UINT16_S rtnValue = DR_BUTTON_LOCAL_SUM_MAX;

	if ((drButtonId >= 1U) && (drButtonId < DR_BUTTON_SUM_MAX))
	{
		rtnValue = gDRButtonIdBuff[drButtonId];
	}
	else
	{
		rtnValue = DR_BUTTON_LOCAL_SUM_MAX;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������۷���ID������
* ����˵���� const UINT16 drLampId, �����۷���ID
* ����ֵ  �� DR_LAMP_LOCAL_SUM_MAX: ��ȡ����ʧ��
*			<DR_LAMP_LOCAL_SUM_MAX: ���ҳɹ�
*/
UINT16_S GetDRLampConfigBufIndex(const UINT16_S drLampId)
{
	UINT16_S rtnValue = DR_LAMP_LOCAL_SUM_MAX;

	if ((drLampId >= 1U) && (drLampId < DR_LAMP_SUM_MAX))
	{
		rtnValue = gDRLampIdBuff[drLampId];
	}
	else
	{
		rtnValue = DR_LAMP_LOCAL_SUM_MAX;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�����۷���ť��������ID
* ����˵���� const UINT16 drButtonId    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������ID      
*/
UINT8_S GetDRButtonBelongCiId(const UINT16_S drButtonId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue = gDRButtonConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�����۷�����������ID
* ����˵���� const UINT16 drLampId   
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������ID      
*/
UINT8_S GetDRLampBelongCiId(const UINT16_S drLampId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRLampSum())
	{
		rtnValue =  gDRLampConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue =  RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�����۷���ť����ZCID
* ����˵���� const UINT16 drButtonId    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ZC��ID      
*/
UINT8_S GetDRButtonBelongZcId(const UINT16_S drButtonId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue = gDRButtonConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�����۷�������ZCID
* ����˵���� const UINT16 drLampId   
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ZC��ID      
*/
UINT8_S GetDRLampBelongZcId(const UINT16_S drLampId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRLampSum())
	{
		rtnValue = gDRLampConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�����۷���ť������������
* ����˵���� const UINT16 doorId, ������ID    
* ����ֵ  �� 0: ������
*			 FLAG_SET: ����      
*/
UINT8_S GetDRButtonChangeAttribute(const UINT16_S drButtonId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRButtonConfigBufIndex(drButtonId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRButtonSum())
	{
		rtnValue = gDRButtonConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�����۷���ť������������
* ����˵���� const UINT16 doorId, ������ID    
* ����ֵ  �� 0: ������
*			 FLAG_SET: ����      
*/
UINT8_S GetDRLampChangeAttribute(const UINT16_S drLampId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetDRLampConfigBufIndex(drLampId);  /*��ȡ�����±�*/

	if (bufIndex < GetDRLampSum())
	{
		rtnValue = gDRLampConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
