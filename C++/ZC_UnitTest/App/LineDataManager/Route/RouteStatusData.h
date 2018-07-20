/************************************************************************
*
* �ļ���   ��  RouteStatusData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��·״̬����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef ROUTE_STATUS_DATA_H_
#define ROUTE_STATUS_DATA_H_


#include "RouteDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*��·״̬���ݽṹ��*/
	typedef struct RouteDataStruct
	{
		UINT16_S RouteId;                     /*��·��ťID*/
		UINT8_S RouteStatus;                  /*��·��ǰ״̬*/
        UINT8_S RouteStopReq;                 /* ��·ͣ����֤���� */
        UINT8_S RouteStopConfirm;             /* ��·ͣ����֤ȷ��*/
	} RouteDataStruct;


	/*
	* ���������� ��ȡ��·����
	* ����˵���� void    
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*			 !NULL: ��·����
	*/
	RouteDataStruct* GetRouteStatusData(void);

	/*
	* ���������� ��ȡ��·��ǰ״̬
	* ����˵���� const routeId ��·ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��·״̬
	*/
	UINT8_S GetRouteStatus(const UINT16_S routeId);

	/*
	* ���������� ���ý�·��ǰ״̬
	* ����˵���� const UINT16  routeId ��·ID; 
	*	         UINT8_S routeStatus ��·״̬    
	* ����ֵ  �� 0;ʧ��
	*            1;�ɹ�
	*/
	UINT8_S SetRouteStatus(const UINT16_S routeId,UINT8_S routeStatus);

    /*
	* ���������� ��ȡ��·ͣ����֤����
	* ����˵���� const UINT16_S routeId ��·ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��·״̬
	*/
	UINT8_S GetRouteStopReq(const UINT16_S routeId);

   /*
	* ���������� ���ý�·ͣ����֤����
	* ����˵���� const UINT16_S routeId ��·ID    
    *          const UINT8_S routeStopReq,��·ͣ����֤����
	* ����ֵ  �� 0: ʧ��
	*			1: �ɹ�
	*/
	UINT8_S SetRouteStopReq(const UINT16_S routeId,const UINT8_S routeStopReq);	
	
    /*
	* ���������� ��ȡ��·ͣ����֤ȷ��
	* ����˵���� const UINT16_S routeId ��·ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��·״̬
	*/
	UINT8_S GetRouteStopConfirm(const UINT16_S routeId);

   /*
	* ���������� ���ý�·ͣ����֤ȷ��
	* ����˵���� const UINT16_S routeId ��·ID    
    *          const UINT8_S routeStopConfirm,��·ͣ����֤ȷ��
	* ����ֵ  �� 0: ʧ��
	*			1: �ɹ�
	*/
	UINT8_S SetRouteStopConfirm(const UINT16_S routeId,const UINT8_S routeStopConfirm);	
	

#ifdef __cplusplus
}
#endif

#endif
