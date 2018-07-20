/************************************************************************
*
* �ļ���   ��  ESBConfigData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����ͣ����ť��������
* ��  ע   ��  ��
*
************************************************************************/
#include "ESBConfigData.h"


EsbConfigDataStruct gEsbConfigDataStruBuff[ESB_LOCAL_SUM_MAX];          /*���ع���Ľ���ͣ����ť������Ϣ*/
UINT16_S gEsbIdBuff[ESB_SUM_MAX] = {0U};                                /*�������ͣ����ťӳ������*/
UINT16_S gEsbCurSum = 0U;                                              /*����ͣ����ť��ǰ����*/


/*
* ���������� ��ȡ����ͣ����ť��������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ͣ����ť��ǰ����
*/
UINT16_S GetEsbSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gEsbCurSum >= ESB_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gEsbCurSum;
	}	

	return rtnValue;
}

/*
* ���������� ��ȡָ�������±��Ӧ�Ľ���ͣ����ťID
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ͣ����ťID      
*/
UINT16_S GetEsbId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetEsbSum())
	{
		rtnValue = gEsbConfigDataStruBuff[bufIndex].EsbId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID����ͣ����ť������
* ����˵���� const UINT16 esbId,����ͣ����ťID
* ����ֵ  �� ESB_LOCAL_SUM_MAX: ��ȡ����ʧ��
*			<ESB_LOCAL_SUM_MAX: ���ҳɹ�
*/
UINT16_S GetEsbConfigBufIndex(const UINT16_S esbId)
{
	UINT16_S rtnValue = ESB_LOCAL_SUM_MAX;

	if ((esbId >= 1U)&&(esbId < ESB_SUM_MAX))
	{
		rtnValue = gEsbIdBuff[esbId];
	}
	else
	{
		rtnValue = ESB_LOCAL_SUM_MAX;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��IDվ̨����ͣ����ť��������ID
* ����˵���� const UINT16 esbId,����ͣ����ťID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������ID      
*/
UINT8_S GetEsbBelongCiId(const UINT16_S esbId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetEsbConfigBufIndex(esbId);  /*��ȡ�����±�*/

	if (bufIndex < GetEsbSum())
	{
		rtnValue = gEsbConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID����ͣ����ť����ZCID
* ����˵���� const UINT16 esbId, ����ͣ����ťID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����zcID      
*/
UINT8_S GetEsbBelongZcId(const UINT16_S esbId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetEsbConfigBufIndex(esbId);  /*��ȡ�����±�*/

	if (bufIndex < GetEsbSum())
	{
		rtnValue = gEsbConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID����ͣ����ť������������
* ����˵���� const UINT16 esbId, ����ͣ����ťID     
* ����ֵ  �� 0: ������
*			 FLAG_SET: ����       
*/
UINT8_S GetEsbChangeAttribute(const UINT16_S esbId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetEsbConfigBufIndex(esbId);  /*��ȡ�����±�*/

	if (bufIndex < GetEsbSum())
	{
		rtnValue = gEsbConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
