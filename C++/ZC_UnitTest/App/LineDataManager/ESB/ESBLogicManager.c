/************************************************************************
*
* �ļ���   ��  ESBLogicManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����ͣ����ť�߼�����
* ��  ע   ��  ��
*
************************************************************************/
#include "ESBConfigData.h"
#include "ESBLogicManager.h"
#include "ESBStatusData.h"

/*
* ���������� ������϶�Ӧ�ĵ���ESB��Ϣ
* ����˵���� const UINT16 esbId��ESBID    
* ����ֵ  �� void  
*/
void InitFailureSingleEsb(const UINT16_S esbId)
{
	SetEsbStatus(esbId,ESB_STATE_DOWN);
}

/*
* ���������� ����ͨ�Ź���Ci��Ӧ�Ľ���ͣ����ť��Ϣ
* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
* ����ֵ  �� void  
*/
void InitFailureCiEsb(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S esbId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetEsbSum();cycle++)
	{
		esbId = GetEsbId(cycle);

		if (ciId == GetEsbBelongCiId(esbId))
		{
			/*����״̬Ϊ��ȫ̬*/
			InitFailureSingleEsb(esbId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� ����ͨ�Ź���ZC��Ӧ�Ľ���ͣ����ť��Ϣ
* ����˵���� const UINT16 nZcId��ͨ�Ź��ϵ�nZcID    
* ����ֵ  �� void  
*/
void InitFailureNZcEsb(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S esbId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetEsbSum();cycle++)
	{
		esbId = GetEsbId(cycle);

		if ((nZcId == GetEsbBelongZcId(esbId))
			&& (FLAG_SET == GetEsbChangeAttribute(esbId)))
		{
			/*����״̬Ϊ��ȫ̬*/
			InitFailureSingleEsb(esbId);
		} 
		else
		{
            /*������*/
		}
	}
}
