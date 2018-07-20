/************************************************************************
*
* �ļ���   ��  SignalStatusData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �źŻ�״̬����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SIGNAL_STATUS_DATA_H_
#define SIGNAL_STATUS_DATA_H_


#include "SignalDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*�źŻ�״̬���ݽṹ��*/
	typedef struct SignalDataStruct
	{
		UINT16_S SignalId;                      /*�źŻ�ID*/
		UINT8_S SignalStatus;                   /*�źŻ���ǰ״̬*/ 
		UINT8_S LightOffStatus;                 /*�źŻ�����״̬*/                
		UINT8_S CrossStatus;                    /*�г�����źŻ�״̬*/
	} SignalDataStruct;


	/*
	* ���������� ��ȡ�źŻ�����
	* ����˵���� void    
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*			 !NULL: �źŻ�����
	*/
	SignalDataStruct* GetSignalStatusData(void);

	/*
	* ���������� ��ȡ�źŻ���ǰ״̬
	* ����˵���� const UINT16  signalId �źŻ�ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �źŻ�״̬
	*/
	UINT8_S GetSignalStatus(const UINT16_S signalId);

	/*
	* ���������� �����źŻ���ǰ״̬
	* ����˵���� const UINT16 signalId �źŻ�ID; 
	*            UINT8_S signalStatus �źŻ�״̬    
	* ����ֵ  �� 0;ʧ��
	*            1;�ɹ�
	*/
	UINT8_S SetSignalStatus(const UINT16_S signalId,UINT8_S signalStatus);

	/*
	* ���������� ��ȡ�źŻ��źŻ�����״̬
	* ����˵���� const UINT16 signalId �źŻ�ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �źŻ�״̬
	*/
	UINT8_S GetSignalLightOffStatus(const UINT16_S signalId);

	/*
	* ���������� �����źŻ��źŻ�����״̬
	* ����˵���� const UINT16 signalId �źŻ�ID; 
	*	         UINT8_S  lightOffStatus �źŻ�״̬    
	* ����ֵ  �� 0;ʧ��
	*            1;�ɹ�
	*/
	UINT8_S SetSignalLightOffStatus(const UINT16_S signalId,UINT8_S lightOffStatus);

	/*
	* ���������� ��ȡ�źŻ��г���ѹ�źŻ�״̬
	* ����˵���� const UINT16 signalId �źŻ�ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �źŻ�״̬
	*/
	UINT8_S GetSignalCrossStatus(const UINT16_S signalId);

	/*
	* ���������� �����źŻ��г���ѹ�źŻ�״̬
	* ����˵���� const UINT16 signalId �źŻ�ID; 
	*	         UINT8_S  crossStatus �źŻ�״̬    
	* ����ֵ  �� 0;ʧ��
	*            1;�ɹ�
	*/
	UINT8_S SetSignalCrossStatus(const UINT16_S signalId,UINT8_S crossStatus);

#ifdef __cplusplus
}
#endif

#endif
