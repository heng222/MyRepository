/************************************************************************
*
* �ļ���   ��  LogicSectionConfigData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �߼�������������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef LOGIC_SECTION_CONFIG_DATA_H_
#define LOGIC_SECTION_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "LogicSectionDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*���������ݽṹ��*/
	typedef struct LogicSectionConfigDataStruct
	{
		UINT16_S LogicSectionId;            /*�߼�����ID*/
		UINT8_S BelongCiId;                 /*��������ID*/
		UINT8_S BelongZcId;                 /*����ZCID*/
		UINT16_S BelongAcId;                /*������������Id*/
	} LogicSectionConfigDataStruct;

	/*
	* ���������� ��ȡ�߼����ι�������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �߼����ε�ǰ����
	*/
	UINT16_S GetLogicSectionSum(void);

	/*
	* ���������� ��ȡָ�������±��Ӧ���߼�����ID
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �߼�����ID      
	*/
	UINT16_S GetLogicSectionId(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ��ID�߼�����������
	* ����˵���� const UINT16 logicSectionId,�߼�����ID
	* ����ֵ  ��  LOGIC_SECTION_SUM_MAX;��ȡ����ʧ��
	*			  >=0;���������ɹ�
	*/
	UINT16_S GetLogicSectionConfigBufIndex(const UINT16_S logicSectionId);

	/*
	* ���������� ��ȡָ��IDվ̨�߼�������������ID
	* ����˵���� const UINT16 logicSectionId,�߼�����ID   
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������ID      
	*/
	UINT8_S GetLogicSectionBelongCiId(const UINT16_S logicSectionId);

	/*
	* ���������� ��ȡָ��ID�߼���������ZC��ID
	* ����˵���� const UINT16 logicSectionId,�߼�����ID   
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ZcID      
	*/
	UINT8_S GetLogicSectionBelongZcId(const UINT16_S logicSectionId);

	/*
	* ���������� ��ȡָ��ID�߼�����������������ID
	* ����˵���� const UINT16 logicSectionId,�߼�����ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT16_S GetLogicSectionBelongAcId(const UINT16_S logicSectionId);

#ifdef __cplusplus
}
#endif

#endif
