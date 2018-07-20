/************************************************************************
*
* �ļ���   ��  SwitchLogicManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����߼��������
* ��  ע   ��  ��
*
************************************************************************/
#include "SwitchLogicManager.h"
#include "SwitchConfigData.h"
#include "SwitchStatusData.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Convert.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataHandle.h"


/*
* ���������� ����ͨ�Ź���Ci��Ӧ�ĵ���������Ϣ
* ����˵���� const UINT16 switchId������ID    
* ����ֵ  �� void  
*/
void InitFailureSingleSwitch(const UINT16_S switchId)
{
	SetSwitchPosStatus(switchId,SWITCH_STATE_LOSE);
	SetSwitchLock(switchId,SWITCH_STATE_UNLOCK);
}

/*
* ���������� ����ͨ�Ź���Ci��Ӧ�ĵ�����Ϣ
* ����˵���� const UINT16 ciId;ͨ�Ź��ϵ�����ID   
* ����ֵ  �� void  
*/
void InitFailureCiSwitch(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S switchId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetSwitchSum();cycle++)
	{
		switchId = GetSwitchId(cycle);

		if (ciId == GetSwitchBelongCiId(switchId))
		{
			/*��Ci��Χ�ڴ����*/
			InitFailureSingleSwitch(switchId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� ����ͨ�Ź���NZc��Ӧ�ĵ�����Ϣ
* ����˵���� const UINT16 nZcId,����ZC    
* ����ֵ  �� void  
*/
void InitFailureNZcSwitch(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S switchId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetSwitchSum();cycle++)
	{
		switchId = GetSwitchId(cycle);

		if ((nZcId == GetSwitchBelongZcId(switchId))
			&& (FLAG_SET == GetSwitchChangeAttribute(switchId)))
		{
			/*��Ci��Χ�ڴ����*/
			InitFailureSingleSwitch(switchId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� ��֯����ѯ����DMU�ı��ص�����Ϣ
* ����˵���� void    
* ����ֵ  �� void  
*/
void SetDmuSwitchStatusInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S indexLength = DEFAULT_ZERO;
	UINT8_S switchStatusBuff[SWITCH_LOCAL_SUM_MAX*3U] = {DEFAULT_ZERO};
	UINT16_S switchId = DEFAULT_ZERO;

	/*��ʼ��*/
	MemorySet(switchStatusBuff,((UINT32_S)(sizeof(UINT8_S)*SWITCH_LOCAL_SUM_MAX*3U)),
                0U,((UINT32_S)(sizeof(UINT8_S)*SWITCH_LOCAL_SUM_MAX*3U)));

	/*��֯���ص���״̬��Ϣ*/
	for (cycle = DEFAULT_ZERO;cycle < GetSwitchSum();cycle++)
	{
		switchId = GetSwitchId(cycle);

		ShortToChar(switchId,&switchStatusBuff[indexLength]);
		indexLength = indexLength + 2U;

		switchStatusBuff[indexLength] = GetSwitchPosStatus(switchId);
		indexLength = indexLength + 1U;
	}

	UpdateSwitchStatus(switchStatusBuff,indexLength);
}
