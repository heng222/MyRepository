/************************************************************************
*
* �ļ���   ��  RouteInitManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��·��ʼ������
* ��  ע   ��  ��
*
************************************************************************/

#ifndef ROUTE_INIT_MANAGER_H_
#define ROUTE_INIT_MANAGER_H_


#include "RouteDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ��ʼ�����ع���Ľ�·��ʼ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��      
	*/
	void InitRouteInitializationData(void);

	/*
	* ���������� ��ʼ�����ع���Ľ�·��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitRouteLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
