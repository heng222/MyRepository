/********************************************************                                                                                                           
 �� �� ���� OverlapLogicManager.c
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015.04.18
 ������ ���������߼�����  
 ��ע�� ��  
********************************************************/ 

#include "OverlapConfigData.h"
#include "OverlapLogicManager.h"
#include "OverlapStatusData.h"
#include "../AC/ACLogicManager.h"
#include "../../../Common/MemSet.h"

/*************************************************
  ������:    InitFailureSingleOverlap  
  ��������: ����ͨ�Ź���Ci��Ӧ�ĵ�������������Ϣ
  ����: const UINT16 overlapId����������ID    
  ���: ��
  ����ֵ: void  
*************************************************/
void InitFailureSingleOverlap(const UINT16_S overlapId)
{
	SetOverlapStatus(overlapId,OVERLAP_STATE_UNSET);
}

/*************************************************
  ������:   InitFailureCiOverlap   
  ��������: ����ͨ�Ź���Ci��Ӧ�ı���������Ϣ
  ����: const UINT16 ciId��ͨ�Ź��ϵ�CIID    
  ���: ��
  ����ֵ: void  
*************************************************/
void InitFailureCiOverlap(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S overlapId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetOverlapSum();cycle++)
	{
		overlapId = GetOverlapId(cycle);

		if (ciId == GetOverlapBelongCiId(overlapId))
		{
			/*����״̬Ϊ��ȫ̬*/
			InitFailureSingleOverlap(overlapId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*************************************************
  ������:   InitFailureNZcOverlap   
  ��������: ����ͨ�Ź���nZc��Ӧ�ı���������Ϣ
  ����: const UINT16 nZcId��ͨ�Ź��ϵ�nZcID    
  ���: ��
  ����ֵ: void  
*************************************************/
void InitFailureNZcOverlap(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S overlapId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetOverlapSum();cycle++)
	{
		overlapId = GetOverlapId(cycle);

		if ((nZcId == GetOverlapBelongZcId(overlapId))
			&& (FLAG_SET == GetOverlapChangeAttribute(overlapId)))
		{
			/*����״̬Ϊ��ȫ̬*/
			InitFailureSingleOverlap(overlapId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*************************************************
  ������:    CalulateSwtichStateOfOverlapIsNeed  
  ��������: ���������overlap�Ƿ��������״̬�����պ�λ�ã�
  ����: const UINT16 overlpId����������ID   
  ���: ��
  ����ֵ: 0:����������
*            1:��������  
*************************************************/
UINT8_S CalulateSwtichStateOfOverlapIsNeed(const UINT16_S overlpId)
{
	UINT8_S overlapContainAcNum = DEFAULT_ZERO;                   
	UINT16_S overlapContainAcBuff[OVERLAP_OF_AC_SUM_MAX] = {0U};
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S getFlag = RETURN_ERROR;
	
	MemorySet(&overlapContainAcBuff[0],((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)));

	if (FLAG_SET == GetOverlapSwitchAttribute(overlpId))
	{
		overlapContainAcNum = GetOverlapContainAcNum(overlpId);
        getFlag = GetOverlapContainAcBuff(overlpId,OVERLAP_OF_AC_SUM_MAX,overlapContainAcBuff);
		
		if ((overlapContainAcNum > 0U)
			&& (RETURN_SUCCESS == getFlag))
		{
			for (cycle = DEFAULT_ZERO;cycle < overlapContainAcNum;cycle++)
			{
				/*��ȡ�������ε�����Ϣ*/
				if (RETURN_SUCCESS == CalulateSwtichStateOfAcIsNeed(overlapContainAcBuff[cycle]))
				{
                    /*������*/
				} 
				else
				{
					breakFlag = FLAG_SET;
					break;
				}
			} 

			if (FLAG_SET == breakFlag)
			{
				rtnValue = RETURN_ERROR;
			}
			else
			{
				rtnValue = RETURN_SUCCESS;
			}
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}
