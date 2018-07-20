/************************************************************************
*
* �ļ���   ��  LogicSectionInitManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �߼����γ�ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef LOGIC_SECTION_INIT_MANAGER_H_
#define LOGIC_SECTION_INIT_MANAGER_H_


#include "LogicSectionDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ��ʼ�����ع�����߼����γ�ʼ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��      
	*/
	void InitLogicSectionInitializationData(void);

	/*
	* ���������� ��ʼ�����ع�����߼�������Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			>0: ��ʼ���ɹ�      
	*/
	UINT8_S InitLogicSectionLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
