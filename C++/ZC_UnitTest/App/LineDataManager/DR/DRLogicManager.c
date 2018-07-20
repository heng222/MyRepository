/************************************************************************
*
* �ļ���   ��  DRLogicManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����۷��߼�����
* ��  ע   ��  ��
*
************************************************************************/
#include "DRLogicManager.h"
#include "DRStatusData.h"
#include "DRConfigData.h"

/*
* ���������� ������϶�Ӧ�ĵ��������۷���ť��Ϣ
* ����˵���� const UINT16 drButtonId�������۷���ťID    
* ����ֵ  �� void  
*/
void InitFailureSingleDrButton(const UINT16_S drButtonId)
{
	SetDRButtonStatus(drButtonId,DR_BUTTON_STATE_UP);
}

/*
* ���������� ����ͨ�Ź���Ci��Ӧ�������۷���ť��Ϣ
* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
* ����ֵ  �� void  
*/
void InitFailureCiDrButoon(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S drButtonId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO; cycle < GetDRButtonSum();cycle++)
	{
		drButtonId = GetDRButtonId(cycle);

		if (GetDRButtonBelongCiId(drButtonId) == ciId)
		{
			InitFailureSingleDrButton(drButtonId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� ����ͨ�Ź���ZC��Ӧ�������۷���ť��Ϣ
* ����˵���� const UINT16 nZcId��ͨ�Ź��ϵ�nZcID    
* ����ֵ  �� void  
*/
void InitFailureNZcDrButton(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S drButtonId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO; cycle < GetDRButtonSum();cycle++)
	{
		drButtonId = GetDRButtonId(cycle);

		if (GetDRButtonBelongZcId(drButtonId) == nZcId)
		{
			InitFailureSingleDrButton(drButtonId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� ������϶�Ӧ�ĵ��������۷�����Ϣ
* ����˵���� const UINT16 drLampId�������۷���ID    
* ����ֵ  �� void  
*/
void InitFailureSingleDrLamp(const UINT16_S drLampId)
{
	SetDRLampCommand(drLampId,DR_LAMP_DEFAULT_STATUS);
	SetDRLampOfTrainId(drLampId,DEFAULT_ZERO);
}

/*
* ���������� ����ͨ�Ź���Ci��Ӧ�������۷�����Ϣ
* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
* ����ֵ  �� void  
*/
void InitFailureCiDrLamp(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S drLampId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO; cycle < GetDRLampSum();cycle++)
	{
		drLampId = GetDRLampId(cycle);

		if (GetDRLampBelongCiId(drLampId) == ciId)
		{
			InitFailureSingleDrLamp(drLampId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� ����ͨ�Ź���ZC��Ӧ�������۷�����Ϣ
* ����˵���� const UINT16 nZcId��ͨ�Ź��ϵ�nZcID    
* ����ֵ  �� void  
*/
void InitFailureNZcDrLamp(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S drLampId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO; cycle < GetDRLampSum();cycle++)
	{
		drLampId = GetDRLampId(cycle);

		if (GetDRLampBelongZcId(drLampId) == nZcId)
		{
			InitFailureSingleDrLamp(drLampId);
		} 
		else
		{
            /*������*/
		}
	}
}
