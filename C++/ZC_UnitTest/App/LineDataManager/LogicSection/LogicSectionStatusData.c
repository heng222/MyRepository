/************************************************************************
*
* �ļ���   ��  LogicSectionStatusData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �߼�����״̬����
* ��  ע   ��  ��
*
************************************************************************/
#include "LogicSectionConfigData.h"
#include "LogicSectionStatusData.h"

LogicSectionStruct gLogicSectionDataStruBuff[LOGIC_SECTION_LOCAL_SUM_MAX];             /*���屾�ع�����߼�����״̬��������*/

/*
* ���������� ��ȡ�߼���������
* ����˵���� void    
* ����ֵ  �� NULL: ��ȡ����ʧ��
*			 !NULL: �߼���������
*/
LogicSectionStruct* GetLogicSectionStatusData(void)
{
	return gLogicSectionDataStruBuff;
}

/*
* ���������� ��ȡ�߼����ε�ǰ״̬
* ����˵���� const UINT16 logicSectionId �߼�����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �߼�����״̬
*/
UINT8_S GetLogicSectionOccStatus(const UINT16_S logicSectionId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetLogicSectionConfigBufIndex(logicSectionId);  /*��ȡ�����±�*/

	if (bufIndex < GetLogicSectionSum())
	{
		rtnValue = gLogicSectionDataStruBuff[bufIndex].LogicSectionOccStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� �����߼����ε�ǰ״̬
* ����˵���� const UINT16  logicSectionId �߼�����ID; 
*	         UINT8_S logicSectionStatus �߼�����״̬    
* ����ֵ  �� 0;ʧ��
*            1;�ɹ�
*/
UINT8_S SetLogicSectionOccStatus(const UINT16_S logicSectionId,UINT8_S logicSectionStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetLogicSectionConfigBufIndex(logicSectionId);  /*��ȡ�����±�*/

	if (bufIndex < GetLogicSectionSum())
	{
		if ((LOGIC_SECTION_STATE_UT == logicSectionStatus)
			|| (LOGIC_SECTION_STATE_CT == logicSectionStatus)
			|| (LOGIC_SECTION_STATE_FREE == logicSectionStatus))
		{
			gLogicSectionDataStruBuff[bufIndex].LogicSectionOccStatus = logicSectionStatus;
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
