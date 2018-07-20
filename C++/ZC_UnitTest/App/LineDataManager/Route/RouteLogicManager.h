/************************************************************************
*
* �ļ���   ��  RouteLogicManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��·�߼��������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef ROUTE_LOGIC_MANAGER_H_
#define ROUTE_LOGIC_MANAGER_H_


#include "RouteDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ�ĵ�����·��Ϣ
	* ����˵���� const UINT16 routeId����·ID    
	* ����ֵ  �� void  
	*/
	void InitFailureSingleRoute(const UINT16_S routeId);

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ�Ľ�·��Ϣ
	* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
	* ����ֵ  �� void  
	*/
	void InitFailureCiRoute(const UINT16_S ciId);

	/*
	* ���������� ����ͨ�Ź���NZc��Ӧ�Ľ�·��Ϣ
	* ����˵���� const UINT16 nZcId��ͨ�Ź��ϵ�nZcId    
	* ����ֵ  �� void  
	*/
	void InitFailureNZcRoute(const UINT16_S nZcId);

#ifdef __cplusplus
}
#endif

#endif
