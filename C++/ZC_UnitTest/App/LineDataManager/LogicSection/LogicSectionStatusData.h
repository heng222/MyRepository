/************************************************************************
*
* �ļ���   ��  LogicSectionStatusData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �߼�����״̬����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef LOGIC_SECTION_STATUS_DATA_H_
#define LOGIC_SECTION_STATUS_DATA_H_

#include "LogicSectionDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*�߼�����״̬���ݽṹ��*/
	typedef struct LogicSectionStruct
	{
		UINT16_S LogicSectionId;                     /*�߼�����ID*/
		UINT8_S LogicSectionOccStatus;               /*�߼����ε�ǰ״̬*/
	} LogicSectionStruct;


	/*
	* ���������� ��ȡ�߼���������
	* ����˵���� void    
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*			 !NULL: �߼���������
	*/
	LogicSectionStruct* GetLogicSectionStatusData(void);

	/*
	* ���������� ��ȡ�߼����ε�ǰ״̬
	* ����˵���� const UINT16 logicSectionId �߼�����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �߼�����״̬
	*/
	UINT8_S GetLogicSectionOccStatus(const UINT16_S logicSectionId);

	/*
	* ���������� �����߼����ε�ǰ״̬
	* ����˵���� const UINT16  logicSectionId �߼�����ID; 
	*	         UINT8_S logicSectionStatus �߼�����״̬    
	* ����ֵ  �� 0;ʧ��
	*            1;�ɹ�
	*/
	UINT8_S SetLogicSectionOccStatus(const UINT16_S logicSectionId,UINT8_S logicSectionStatus);

#ifdef __cplusplus
}
#endif

#endif
