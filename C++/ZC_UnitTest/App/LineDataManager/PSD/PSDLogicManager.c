/************************************************************************
*
* �ļ���   ��  PSDLogicManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �������߼�����
* ��  ע   ��  ��
*
************************************************************************/
#include "PSDConfigData.h"
#include "PSDStatusData.h"
#include "PSDLogicManager.h"


/*
* ���������� ����ͨ�Ź���Ci��Ӧ�ĵ�����������Ϣ
* ����˵���� const UINT16 psdId��������ID    
* ����ֵ  �� void  
*/
void InitFailureSinglePsd(const UINT16_S psdId)
{
	SetPsdStatus(psdId,PSD_STATE_OPEN);
}

/*
* ���������� ����ͨ�Ź���Ci��Ӧ����������Ϣ
* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�������ID    
* ����ֵ  �� void  
*/
void InitFailureCiPsd(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S psdId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetPsdSum();cycle++)
	{
		psdId = GetPsdId(cycle);

		if (ciId == GetPsdBelongCiId(psdId))
		{
			/*����״̬Ϊ��ȫ̬*/
			InitFailureSinglePsd(psdId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� ����ͨ�Ź���Ci��Ӧ����������Ϣ
* ����˵���� const UINT16 nZcId��ͨ�Ź��ϵ�����ZcID    
* ����ֵ  �� void  
*/
void InitFailureNZcPsd(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S psdId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetPsdSum();cycle++)
	{
		psdId = GetPsdId(cycle);

		if ((nZcId == GetPsdBelongZcId(psdId))
			&& (FLAG_SET == GetPsdChangeAttribute(psdId)))
		{
			/*����״̬Ϊ��ȫ̬*/
			InitFailureSinglePsd(psdId);
		} 
		else
		{
            /*������*/
		}
	}
}
