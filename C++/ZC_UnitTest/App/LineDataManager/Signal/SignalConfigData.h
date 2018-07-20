/************************************************************************
*
* �ļ���   ��  SignalConfigData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �źŻ���������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SIGNAL_CONFIG_DATA_H_
#define SIGNAL_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "SignalDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*�źŻ��������ݽṹ��*/
	typedef struct SignalConfigDataStruct
	{
		UINT16_S SignalId;                      /*�źŻ�ID*/
		UINT8_S BelongCiId;                     /*��������ID*/
		UINT8_S BelongZcId;                     /*����ZCID*/
		UINT8_S ChangeAttribute;                /*������������(��־�Ƿ�����ĳ����������)*/
		UINT8_S SignalType;                     /*�źŻ�����*/
		UINT8_S ProtectDir;                     /*�źŻ���������*/
		UINT8_S DefaultStatus;                  /*�źŻ�Ĭ��״̬*/
		UINT8_S LightOffType;                   /*�źŻ��Ƿ���Ҫ�ж����������*/
		UINT8_S CbtcLightOffType;               /*CBTC�����г���Ӧ�źŻ�����������*/
		UINT8_S CrossType;                      /*�źŻ��Ƿ���Ҫ�жϿ�ѹ״̬����*/
		UINT8_S CrashType;                      /*�źŻ��Ƿ���Ҫ�жϴ����źŻ�״̬����*/
	} SignalConfigDataStruct;

	/*
	* ���������� ��ȡ�źŻ���������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �źŻ���ǰ����
	*/
	UINT16_S GetSignalSum(void);

	/*
	* ���������� ��ȡָ�������±��Ӧ���źŻ�ID
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �źŻ�ID      
	*/
	UINT16_S GetSignalId(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ��ID�źŻ�������
	* ����˵���� const UINT16 signalId,�źŻ�ID
	* ����ֵ  �� SIGNAL_SUM_MAX ;��ȡ����ʧ��
	*			 >0; ���������ɹ�
	*/
	UINT16_S GetSignalConfigBufIndex(const UINT16_S signalId);

	/*
	* ���������� ��ȡָ��IDվ̨�źŻ���������ID
	* ����˵���� const UINT16 signalId,�źŻ�ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������ID      
	*/
	UINT8_S GetSignalBelongCiId(const UINT16_S signalId);

	/*
	* ���������� ��ȡָ��ID�źŻ�����ZC��ID
	* ����˵���� const UINT16 signalId, �źŻ�ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ZcID      
	*/
	UINT8_S GetSignalBelongZcId(const UINT16_S signalId);

	/*
	* ���������� ��ȡָ��ID�źŻ�������������
	* ����˵���� const UINT16 signalId, �źŻ�ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT16_S GetSignalChangeAttribute(const UINT16_S signalId);

	/*
	* ���������� ��ȡָ��ID�źŻ�����
	* ����˵���� const UINT16 signalId, �źŻ�ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetSignalSignalType(const UINT16_S signalId);

	/*
	* ���������� ��ȡָ��ID�źŻ���������
	* ����˵���� const UINT16 signalId, �źŻ�ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetSignalProtectDir(const UINT16_S signalId);

	/*
	* ���������� ��ȡָ��ID�źŻ�Ĭ��״̬
	* ����˵���� const UINT16 signalId, �źŻ�ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetSignalDefaultStatus(const UINT16_S signalId);

	/*
	* ���������� ��ȡָ��ID�źŻ��Ƿ���Ҫ�ж�����״̬
	* ����˵���� const UINT16 signalId, �źŻ�ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetSignalLightOffType(const UINT16_S signalId);

	/*
	* ���������� ��ȡָ��ID�źŻ�CBTC�����µ������״̬
	* ����˵���� const UINT16 signalId, �źŻ�ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetSignalCbtcLightOffType(const UINT16_S signalId);

	/*
	* ���������� ��ȡָ��ID�źŻ��Ƿ���Ҫ�жϿ�ѹ״̬
	* ����˵���� const UINT16 signalId, �źŻ�ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetSignalCrossType(const UINT16_S signalId);

	/*
	* ���������� ��ȡָ��ID�źŻ��Ƿ���Ҫ�жϴ�������źŻ�����
	* ����˵���� const UINT16 signalId, �źŻ�ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT8_S GetSignalCrashType(const UINT16_S signalId);

#ifdef __cplusplus
}
#endif

#endif
