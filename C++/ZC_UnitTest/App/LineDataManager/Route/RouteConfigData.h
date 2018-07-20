/************************************************************************
*
* �ļ���   ��  RouteConfigData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��·�������ݹ���
* ��  ע   ��  ��
*
************************************************************************/
#ifndef ROUTE_CONFIG_DATA_H_
#define ROUTE_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "RouteDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct RouteObsStruct
	{
		UINT16_S ObsId;                                /*��·���ϰ���Id*/
		UINT8_S ObsType;                               /*��·���ϰ�������*/
	} RouteObsStruct;

	/*��·���ݽṹ��*/
	typedef struct RouteConfigDataStruct
	{
		UINT16_S RouteId;                                      /*��·ID*/
		UINT8_S BelongCiId;                                    /*��������ID*/
		UINT8_S BelongZcId;                                    /*����ZCID*/
		UINT8_S ChangeAttribute;                               /*������������(��־�Ƿ�����ĳ����������)*/
		UINT8_S RouteType;                                     /*��·����*/
		UINT8_S RouteAreaType;                                 /*��·��������*/
		UINT8_S RouteSingalId;                                 /*��·��Ӧ���źŻ�Id*/  
		UINT8_S OverlapNum;                                    /*��·�����ı�����������*/
		UINT16_S OverlapIdBuff[ROUTE_OF_OVERLAP_SUM_MAX];      /*��·�����ı�����������*/
		UINT8_S  AcNum;                                        /*��·��Χ�ڼ�����������*/
		UINT16_S AcIdBuff[ROUTE_OF_AC_SUM_MAX];                /*��·��Χ�ڼ�������Id����*/
		UINT8_S  ObsNum;                                       /*��·��Χ���ϰ�������*/
		RouteObsStruct RouteObsStruBuff[ROUTE_OF_OBS_SUM_MAX];      /*��·��Χ���ϰ���ṹ��*/
	} RouteConfigDataStruct;

	/*
	* ���������� ��ȡ��·��������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��·��ǰ����
	*/
	UINT16_S GetRouteSum(void);

	/*
	* ���������� ��ȡָ�������±��Ӧ�Ľ�·ID
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��·ID      
	*/
	UINT16_S GetRouteId(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ��ID��·������
	* ����˵���� const UINT16 routeId,��·ID
	* ����ֵ  ��  ROUTE_SUM_MAX;��ȡ����ʧ��
	*			  >=0;���������ɹ�
	*/
	UINT16_S GetRouteConfigBufIndex(const UINT16_S routeId);

	/*
	* ���������� ��ȡָ��IDվ̨��·��������ID
	* ����˵���� const UINT16 routeId,��·ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������ID      
	*/
	UINT8_S GetRouteBelongCiId(const UINT16_S routeId);

	/*
	* ���������� ��ȡָ��ID��·����ZC��ID
	* ����˵���� const UINT16 routeId, ��·ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ZcID      
	*/
	UINT8_S GetRouteBelongZcId(const UINT16_S routeId);

	/*
	* ���������� ��ȡָ��ID��·������������
	* ����˵���� const UINT16 routeId, ��·ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT16_S GetRouteChangeAttribute(const UINT16_S routeId);

	/*
	* ���������� ��ȡָ��ID��·����
	* ����˵���� const UINT16 routeId, ��·ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetRouteType(const UINT16_S routeId);

	/*
	* ���������� ��ȡָ��ID��·��������
	* ����˵���� const UINT16 routeId, ��·ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetRouteAreaType(const UINT16_S routeId);

	/*
	* ���������� ��ȡָ����·Id�ķ����źŻ�Id
	* ����˵���� const UINT16 routeId, ��·ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT16_S GetRouteOfSingalId(const UINT16_S routeId);
	
	/*
	* ���������� ��ȡָ��ID��·�ڱ�����������
	* ����˵���� const UINT16 routeId, ��·ID     
	* ����ֵ  �� DEFAULT_UINT8_VALUE: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetRouteOfOverlapNum(const UINT16_S routeId);

	/*
	* ���������� ��ȡָ��ID��·�ڱ�������Idbuff
	* ����˵���� const UINT16 routeId, ��·ID   
	*			 UINT8_S bufSize,��������С��
	*            UINT16_S overlapIdBuff[],�������
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetRoutOfOverlapIdBuff(const UINT16_S routeId,UINT8_S bufSize,UINT16_S overlapIdBuff[]);

	/*
	* ���������� ��ȡָ��ID��·�ڼ�����������
	* ����˵���� const UINT16 routeId, ��·ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetRouteOfAcNum(const UINT16_S routeId);

	/*
	* ���������� ��ȡָ��id��·��ָ���±�ļ�������Id
	* ����˵���� const UINT16 routeId, ��·ID   
	*			 UINT8_S index,��ѯ�±�
	*            UINT16_S *outAcId,�����������ID
    * ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
    *			 RETURN_SUCCESS: ��ȡ�ɹ�      
	*/
	UINT8_S GetRoutOfAcIdFromIndex(const UINT16_S routeId,UINT8_S index,UINT16_S *outAcId);

	/*
	* ���������� ��ȡָ��ID��·�ڼ�������buff
	* ����˵���� const UINT16 routeId, ��·ID   
	*			 UINT8_S bufSize,��������С��
	*            UINT16_S acIdBuff[],�������
    * ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
    *			 RETURN_SUCCESS: ��ȡ�ɹ�        
	*/
	UINT8_S GetRoutOfAcIdBuff(const UINT16_S routeId,UINT8_S bufSize,UINT16_S acIdBuff[]);

	/*
	* ���������� ��ȡָ��ID��·���ϰ�������
	* ����˵���� const UINT16 routeId, ��·ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT16_S GetRouteOfObsNum(const UINT16_S routeId);

	/*
	* ���������� ��ȡָ��ID��·���ϰ�����Ϣ
	* ����˵���� const UINT16 routeId, ��·ID   
	*            const UINT8_S bufSize,�����С
	*            RoutepObsStru uct routepObsStru uBuff[],�������
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetRoutepObsStruBuff(const UINT16_S routeId,const UINT8_S bufSize,RouteObsStruct routeObsStruBuff[]);

	/*
	* ���������� ��ȡָ����·���һ����������
	* ����˵���� const UINT16 routeId, ��·ID   
	*            UINT16_S *acId, ��������ID�������
	* ����ֵ  �� 0: ��ȡʧ��
	*			 1: ��ȡ�ɹ�
	*/
	UINT8_S GetRouteLastAcId(const UINT16_S routeId,UINT16_S *acId);

#ifdef __cplusplus
}
#endif

#endif
