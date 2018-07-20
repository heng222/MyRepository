
/********************************************************                                                                                                           
 �� �� ���� OverlapStatusData.c
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015.04.18
 ������ ��������״̬  
 ��ע�� ��  
********************************************************/ 

#include "OverlapStatusData.h"
#include "OverlapConfigData.h"

OverlapDataStruct gOverlapDataStruBuff[OVERLAP_LOCAL_SUM_MAX];          /*���ع���ı�������״̬��Ϣ*/

/*************************************************
  ������:   GetOverlapStatusData   
  ��������: ��ȡ������������
  ����: void    
  ���: ��
  ����ֵ: NULL: ��ȡ����ʧ��
*			 !NULL: ������������
*************************************************/
OverlapDataStruct* GetOverlapStatusData(void)
{
	return gOverlapDataStruBuff;
}

/*************************************************
  ������:   GetOverlapStatus   
  ��������: ��ȡ�������ε�ǰ״̬
  ����: overlapId ��������ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ��������״̬
*************************************************/
UINT8_S GetOverlapStatus(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*��ȡ�����±�*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapDataStruBuff[bufIndex].OverlapStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:   SetOverlapStatus   
  ��������: ���ñ������ε�ǰ״̬
  ����: overlapId ��������ID; 
	         overlapStatus ��������״̬    
  ���: ��
  ����ֵ: ��
*************************************************/
UINT8_S SetOverlapStatus(const UINT16_S overlapId,UINT8_S overlapStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*��ȡ�����±�*/

	if (bufIndex < GetOverlapSum())
	{
		if ((OVERLAP_STATE_SET == overlapStatus) || (OVERLAP_STATE_UNSET == overlapStatus))
		{
			gOverlapDataStruBuff[bufIndex].OverlapStatus = overlapStatus;
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
