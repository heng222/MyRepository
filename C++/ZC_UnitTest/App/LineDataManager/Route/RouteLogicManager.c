/************************************************************************
*
* �ļ���   ��  RouteLogicManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��·�߼��������
* ��  ע   ��  ��
*
************************************************************************/
#include "RouteLogicManager.h"
#include "RouteConfigData.h"
#include "RouteStatusData.h"

/*
* ���������� ����ͨ�Ź���Ci��Ӧ�ĵ�����·��Ϣ
* ����˵���� const UINT16 routeId����·ID    
* ����ֵ  �� void  
*/
void InitFailureSingleRoute(const UINT16_S routeId)
{
	SetRouteStatus(routeId,ROUTE_STATE_UNSET);
}

/*
* ���������� ����ͨ�Ź���Ci��Ӧ�Ľ�·��Ϣ
* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
* ����ֵ  �� void  
*/
void InitFailureCiRoute(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S routeId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetRouteSum();cycle++)
	{
		routeId = GetRouteId(cycle);

		if (ciId == GetRouteBelongCiId(routeId))
		{
			/*����״̬Ϊ��ȫ̬*/
			InitFailureSingleRoute(routeId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� ����ͨ�Ź���NZc��Ӧ�Ľ�·��Ϣ
* ����˵���� const UINT16 nZcId��ͨ�Ź��ϵ�nZcId    
* ����ֵ  �� void  
*/
void InitFailureNZcRoute(const UINT16_S nZcId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S routeId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetRouteSum();cycle++)
	{
		routeId = GetRouteId(cycle);

		if ((nZcId == GetRouteBelongZcId(routeId))
			&& (FLAG_SET == GetRouteChangeAttribute(routeId)))
		{
			/*����״̬Ϊ��ȫ̬*/
			InitFailureSingleRoute(routeId);
		} 
		else
		{
            /*������*/
		}
	}
}
