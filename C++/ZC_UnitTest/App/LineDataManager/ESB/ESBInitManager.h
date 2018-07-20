/************************************************************************
*
* �ļ���   ��  ESBInitManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����ͣ����ť��ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef ESB_INIT_MANAGER_H_
#define ESB_INIT_MANAGER_H_


#include "ESBDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ��ʼ�����ع���Ľ���ͣ����ť��ʼ��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��      
	*/
	void InitEsbInitializationData(void);

	/*
	* ���������� ��ʼ�����ع���Ľ���ͣ����ť��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			 1: ��ʼ���ɹ�      
	*/
	UINT8_S InitESBLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
