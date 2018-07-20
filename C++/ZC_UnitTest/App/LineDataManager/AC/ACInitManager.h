/************************************************************************
*
* �ļ���   ��  ACInitManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �������εĳ�ʼ��
* ��  ע   ��  ��
*
************************************************************************/

#ifndef AC_INIT_MANAGER_H_
#define AC_INIT_MANAGER_H_


#include "ACDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ��ʼ�����ع���ļ������γ�ʼ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��     
	*/
	void InitAcInitializationData(void);

	/*
	* ���������� ��ʼ�����ع���ļ���������Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitACLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
