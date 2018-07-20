
/********************************************************                                                                                                           
 �� �� ���� OverlapConfigData.c   
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015.04.18
 ������ ����������������  
 ��ע�� ��  
********************************************************/ 


#include "OverlapConfigData.h"

OverlapConfigDataStruct gOverlapConfigDataStruBuff[OVERLAP_LOCAL_SUM_MAX];            /*���ع���ı�������������Ϣ*/
UINT16_S gOverlapIdBuff[OVERLAP_SUM_MAX] = {0U};                                      /*���屣������ӳ������*/
UINT16_S gOverlapCurSum = 0U;                                                        /*�������ε�ǰ����*/

/*************************************************
  ������:   GetOverlapSum   
  ��������: ��ȡ�������ι�������
  ����: void    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: �������ε�ǰ����
*************************************************/
UINT16_S GetOverlapSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gOverlapCurSum >= OVERLAP_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gOverlapCurSum;
	}

	return rtnValue;
}

/*************************************************
  ������:   GetOverlapId   
  ��������: ��ȡָ�������±��Ӧ�ı�������ID
  ����: const UINT16 bufIndex, �����±�  
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ��������ID      
*************************************************/
UINT16_S GetOverlapId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].OverlapId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:   GetOverlapConfigBufIndex   
  ��������: ��ȡָ��ID��������������
  ����: const UINT16 overlapId,��������ID
  ���: ��
  ����ֵ:  OVERLAP_SUM_MAX;��ȡ����ʧ��
			  >0;���������ɹ�
*************************************************/
UINT16_S GetOverlapConfigBufIndex(const UINT16_S overlapId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((overlapId >= 1U)&&(overlapId < OVERLAP_SUM_MAX))
	{
		rtnValue = gOverlapIdBuff[overlapId];
	}
	else
	{
		rtnValue = OVERLAP_SUM_MAX;
	}

	return rtnValue;
}

/*************************************************
  ������:   GetOverlapBelongCiId   
  ��������: ��ȡָ��IDվ̨����������������ID
  ����: const UINT16 overlapId,��������ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ��������ID      
*************************************************/
UINT8_S GetOverlapBelongCiId(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*��ȡ�����±�*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:   GetOverlapBelongZcId   
  ��������: ��ȡָ��ID������������ZC��ID
  ����: const UINT16 overlapId, ��������ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ����ZcID      
*************************************************/
UINT8_S GetOverlapBelongZcId(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*��ȡ�����±�*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:   GetOverlapChangeAttribute   
  ��������: ��ȡָ��ID�������ι�����������
  ����: const UINT16 overlapId, ��������ID   
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ��ȡ�ɹ�      
*************************************************/
UINT16_S GetOverlapChangeAttribute(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*��ȡ�����±�*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:    GetOverlapSwitchAttribute  
  ��������: ��ȡָ��ID�������ε�������
  ����: const UINT16 overlapId, ��������ID   
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ��ȡ�ɹ�      
*************************************************/
UINT16_S GetOverlapSwitchAttribute(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*��ȡ�����±�*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].SwitchAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:  GetOverlapContainAcNum    
  ��������: ��ȡָ��ID�������ΰ���������������
  ����: const UINT16 overlapId, ��������ID     
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ��ȡ����      
*************************************************/
UINT8_S GetOverlapContainAcNum(const UINT16_S overlapId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*��ȡ�����±�*/

	if (bufIndex < GetOverlapSum())
	{
		rtnValue = gOverlapConfigDataStruBuff[bufIndex].ContainAcNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*************************************************
  ������:   GetOverlapContainAcBuff   
  ��������: ��ȡָ��ID�������ΰ���������������
  ����: const UINT16 overlapId, ��������ID    
            const UINT8_S bufSzie, ��������С
            UINT16_S containAcIdBuff[]���������
  ���: UINT16_S containAcIdBuff[] �����ļ�����������
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ��ȡ������������      
*************************************************/
UINT8_S GetOverlapContainAcBuff(const UINT16_S overlapId,const UINT8_S bufSzie,UINT16_S containAcIdBuff[])
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S cycle = 0U;
	UINT8_S rtnValue = 0U;
    UINT16_S overlapSum = 0U;

	bufIndex = GetOverlapConfigBufIndex(overlapId);  /*��ȡ�����±�*/
    overlapSum = GetOverlapSum();

	if ((bufIndex < overlapSum)
		&& (OVERLAP_OF_AC_SUM_MAX <= bufSzie)
		&& (containAcIdBuff != NULL))
	{
		for (cycle = 0U;cycle < GetOverlapContainAcNum(overlapId);cycle++)
		{
			containAcIdBuff[cycle] = gOverlapConfigDataStruBuff[bufIndex].ContainAcBuff[cycle];
		}
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
