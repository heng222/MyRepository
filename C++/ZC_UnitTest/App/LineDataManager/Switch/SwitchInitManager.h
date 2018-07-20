/************************************************************************
*
* �ļ���   ��  SwitchInitManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SWITCH_INIT_MANAGER_H_
#define SWITCH_INIT_MANAGER_H_


#include "SwitchDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ��ʼ�����ع���ĵ����ʼ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��      
	*/
	void InitSwitchInitializationData(void);

	/*
	* ���������� ��ʼ�����ع���ĵ�����Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitSwitchLocalInfo(void);


#ifdef __cplusplus
}
#endif

#endif
