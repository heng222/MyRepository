/************************************************************************
*
* �ļ���   ��  LogicSectionConfigData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �߼�������������
* ��  ע   ��  ��
*
************************************************************************/
#include "LogicSectionConfigData.h"

LogicSectionConfigDataStruct gLogicSectionConfigDataStruBuff[LOGIC_SECTION_LOCAL_SUM_MAX];          /*���ع�����߼�����������Ϣ*/
UINT16_S gLogicSectionIdBuff[LOGIC_SECTION_SUM_MAX] = {0U};                                         /*�����߼�����ӳ������*/
UINT16_S gLogicSectionCurSum = 0U;        /*�߼����ε�ǰ����*/

/*
* ���������� ��ȡ�߼����ι�������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �߼����ε�ǰ����
*/
UINT16_S GetLogicSectionSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gLogicSectionCurSum >= LOGIC_SECTION_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gLogicSectionCurSum;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������±��Ӧ���߼�����ID
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �߼�����ID      
*/
UINT16_S GetLogicSectionId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetLogicSectionSum())
	{
		rtnValue = gLogicSectionConfigDataStruBuff[bufIndex].LogicSectionId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�߼�����������
* ����˵���� const UINT16 logicSectionId,�߼�����ID
* ����ֵ  ��  LOGIC_SECTION_SUM_MAX;��ȡ����ʧ��
*			  >=0U;���������ɹ�
*/
UINT16_S GetLogicSectionConfigBufIndex(const UINT16_S logicSectionId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((logicSectionId >= 1U) && (logicSectionId < LOGIC_SECTION_SUM_MAX))
	{
		rtnValue = gLogicSectionIdBuff[logicSectionId];
	}
	else
	{
		rtnValue = LOGIC_SECTION_SUM_MAX;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��IDվ̨�߼�������������ID
* ����˵���� const UINT16 logicSectionId,�߼�����ID   
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������ID      
*/
UINT8_S GetLogicSectionBelongCiId(const UINT16_S logicSectionId)
{
	UINT16_S bufIndex = 0U;          /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ȡ�����±�*/
	bufIndex = GetLogicSectionConfigBufIndex(logicSectionId);  

	if (bufIndex < GetLogicSectionSum())
	{
		rtnValue = gLogicSectionConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�߼���������ZC��ID
* ����˵���� const UINT16 logicSectionId,�߼�����ID   
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ZcID      
*/
UINT8_S GetLogicSectionBelongZcId(const UINT16_S logicSectionId)
{
	UINT16_S bufIndex = 0U;          /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ȡ�����±�*/
	bufIndex = GetLogicSectionConfigBufIndex(logicSectionId);  

	if (bufIndex < GetLogicSectionSum())
	{
		rtnValue = gLogicSectionConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�߼�����������������ID
* ����˵���� const UINT16 logicSectionId,�߼�����ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT16_S GetLogicSectionBelongAcId(const UINT16_S logicSectionId)
{
	UINT16_S bufIndex = 0U;          /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	/*��ȡ�����±�*/
	bufIndex = GetLogicSectionConfigBufIndex(logicSectionId);  

	if (bufIndex < GetLogicSectionSum())
	{
		rtnValue = gLogicSectionConfigDataStruBuff[bufIndex].BelongAcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
