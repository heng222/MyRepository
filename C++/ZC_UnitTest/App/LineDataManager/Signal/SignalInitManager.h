/************************************************************************
*
* �ļ���   ��  SignalInitManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �źŻ���ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SIGNAL_INIT_MANAGER_H_
#define SIGNAL_INIT_MANAGER_H_


#include "SignalDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ��ʼ�����ع�����źŻ���ʼ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��      
	*/
	void InitSignalInitializationData(void);

	/*
	* ���������� ��ʼ�����ع�����źŻ���Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitSignalLocalInfo(void);

	/*
	* ���������� ��ʼ�����ع�����źŻ��������Ϣ
	* ����˵���� const UINT16 signalId���źŻ�ID   
	* ����ֵ  �� 0: ʧ��
	*			 0x55: ����
	*            0xaa: ������
	*/
	UINT8_S InitSignalLightOffType(const UINT16_S signalId);

	/*
	* ���������� ��ʼ�����ع�����źŻ���ѹ��Ϣ
	* ����˵���� const UINT16 signalId���źŻ�ID   
	* ����ֵ  �� 0: ʧ��
	*			 0x55: ����
	*            0xaa: ������
	*/
	UINT8_S InitSignalCorssType(const UINT16_S signalId);

#ifdef __cplusplus
}
#endif

#endif
