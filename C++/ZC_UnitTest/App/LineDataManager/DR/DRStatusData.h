/************************************************************************
*
* �ļ���   ��  DRStatusData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����۷�״̬
* ��  ע   ��  ��
*
************************************************************************/
#ifndef DR_STATUS_DATA_H_
#define DR_STATUS_DATA_H_


#include "DRDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*DR��ť״̬���ݽṹ��*/
	typedef struct DRButtonDataStruct
	{
		UINT16_S DRButtonId;                /*�����۷���ťID*/
		UINT16_S TrainId;                   /*�����۷���ť��Ӧ�г�ID*/
		UINT8_S DRButtonStatus;             /*�����۷���ť��ǰ״̬*/
	} DRButtonDataStruct;

	/*DR��״̬���ݽṹ��*/
	typedef struct DRLampDataStruct
	{
		UINT16_S DRLampId;                /*�����۷���ťID*/
		UINT16_S TrainId;                 /*�����۷���ť��Ӧ�г�ID*/
		UINT8_S DRLampCmd;                /*�����۷��ƿ�������*/
	} DRLampDataStruct;


	/*
	* ���������� ��ȡ�����۷���ť����
	* ����˵���� void    
	* ����ֵ  �� �����۷���ť�ṹ�������׵�ַ
	*/
	DRButtonDataStruct* GetDRButtonStatusData(void);

	/*
	* ���������� ��ȡ�����۷�������
	* ����˵���� void    
	* ����ֵ  �� �����۷��ƽṹ�������׵�ַ
	*/
	DRLampDataStruct* GetDRLampData(void);

	/*
	* ���������� ��ȡ�����۷���ť�������г�ID
	* ����˵���� const UINT16 drButtonId,�����۷���ťID   
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �г�ID
	*/
	UINT16_S GetDRButtonOfTrainId(const UINT16_S drButtonId);

	/*
	* ���������� ���������۷���ť�������г�ID
	* ����˵���� const UINT16 drButtonId, �����۷���ťID
	*            UINT16_S trainId,�г�ID
	* ����ֵ  �� 0:��ȡ����ʧ��
	*            1����ȡ���ݳɹ�
	*/
	UINT8_S SetDRButtonOfTrainId(const UINT16_S drButtonId,UINT16_S trainId);

	/*
	* ���������� ��ȡ�����۷��ƹ����г�ID
	* ����˵���� const UINT16 drLampId,�����۷���ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �г�ID
	*/
	UINT16_S GetDRLampOfTrainId(const UINT16_S drLampId);

	/*
	* ���������� ���������۷��ƹ����г�ID
	* ����˵���� const UINT16 drLampId,�����۷���ID  
	*            UINT16_S trainId,�г�ID
	* ����ֵ  �� 0:��ȡ����ʧ��
	*            1����ȡ���ݳɹ�
	*/
	UINT8_S SetDRLampOfTrainId(const UINT16_S drLampId,UINT16_S trainId);

	/*
	* ���������� ��ȡ�����۷��ƿ�������
	* ����˵���� const UINT16 drLampId,�����۷���ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������
	*/
	UINT8_S GetDRLampCommand(const UINT16_S drLampId);

	/*
	* ���������� ���������۷��ƿ�������
	* ����˵���� const UINT16 drLampId,�����۷���ID  
	*            UINT8_S drLampCmd,�����۷�������   
	* ����ֵ  �� 0:��ȡ����ʧ��
	*            1����ȡ���ݳɹ�
	*/
	UINT8_S SetDRLampCommand(const UINT16_S drLampId,UINT8_S drLampCmd);

	/*
	* ���������� ��ȡ�����۷���ť��ǰ״̬
	* ����˵���� const UINT16 drButtonId,�����۷���ťID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������
	*/
	UINT8_S GetDRButtonStatus(const UINT16_S drButtonId);

	/*
	* ���������� ���������۷���ť��������
	* ����˵���� const UINT16 drButtonId,�����۷���ťID  
	*            UINT8_S drButtonStatus,�����۷���ť����   
	* ����ֵ  �� 0:��ȡ����ʧ��
	*            1����ȡ���ݳɹ�
	*/
	UINT8_S SetDRButtonStatus(const UINT16_S drButtonId,UINT8_S drButtonStatus);

#ifdef __cplusplus
}
#endif

#endif
