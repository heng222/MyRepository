/************************************************************************
*
* �ļ���   ��  PSDInitManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����ų�ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef PSD_INIT_MANAGER_H_
#define PSD_INIT_MANAGER_H_


#include "PSDDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ��ʼ�����ع���������ų�ʼ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��      
	*/
	void InitPsdInitializationData(void);

	/*
	* ���������� ��ʼ�����ع������������Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitPSDLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
