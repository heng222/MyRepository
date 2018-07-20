/************************************************************************
*
* �ļ���   ��  DRInitManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����۷���ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef DR_INIT_MANAGER_H_
#define DR_INIT_MANAGER_H_


#include "DRDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ��ʼ�����ع���������۷���ť��ʼ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��      
	*/
	void InitDrButtonInitializationData(void);

	/*
	* ���������� ��ʼ�����ع���������۷��Ƴ�ʼ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��      
	*/
	void InitDrLampInitializationData(void);

	/*
	* ���������� ��ʼ�����ع���������۷���ť��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitDrButtonLocalInfo(void);

	/*
	* ���������� ��ʼ�����ع���������۷�����Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitDrLampLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
