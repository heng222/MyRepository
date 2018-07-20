/************************************************************************
*
* �ļ���   ��  SwitchStatusData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����״̬����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SWITCH_STATUS_DATA_H_
#define SWITCH_STATUS_DATA_H_


#include "SwitchDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*����״̬���ݽṹ��*/
	typedef struct SwitchDataStruct
	{
		UINT16_S SwitchId;                     /*����ťID*/
		UINT8_S SwitchPosStatus;               /*����ǰλ��״̬*/
		UINT8_S SwitchLock;                    /*��������״̬*/
	} SwitchDataStruct;


	/*
	* ���������� ��ȡ��������
	* ����˵���� void    
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*			 !NULL: ��������
	*/
	SwitchDataStruct* GetSwitchStatusData(void);

	/*
	* ���������� ��ȡ����ǰ״̬
	* ����˵���� const UINT16 switchId ����ID    
	* ����ֵ  �� 3: ��ȡ����ʧ��
	*			������3: ����״̬
	*/
	UINT8_S GetSwitchPosStatus(const UINT16_S switchId);

	/*
	* ���������� ���õ���ǰ״̬
	* ����˵���� const UINT16 switchId ����ID; 
	*	         UINT8_S  SwitchPosStatus ����״̬    
	* ����ֵ  �� 0;ʧ��
	*            1;�ɹ�
	*/
	UINT8_S SetSwitchPosStatus(const UINT16_S switchId,UINT8_S switchPosStatus);

	/*
	* ���������� ��ȡ��������״̬
	* ����˵���� const UINT16 switchId ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������״̬
	*/
	UINT8_S GetSwitchLock(const UINT16_S switchId);

	/*
	* ���������� ���õ�������״̬
	* ����˵���� const UINT16 switchId ����ID; 
	*	         UINT8_S  lockStatus ��������״̬    
	* ����ֵ  �� 0;ʧ��
	*            1;�ɹ�
	*/
	UINT8_S SetSwitchLock(const UINT16_S switchId,UINT8_S lockStatus);

#ifdef __cplusplus
}
#endif

#endif
