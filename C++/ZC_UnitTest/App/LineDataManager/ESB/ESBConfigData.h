/************************************************************************
*
* �ļ���   ��  ESBConfigData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����ͣ����ť��������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef ESB_CONFIG_DATA_H_
#define ESB_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ESBDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*����ͣ����ť�������ݽṹ��*/
	typedef struct EsbConfigDataStruct
	{
		UINT16_S EsbId;                     /*����ͣ����ťID*/
		UINT8_S BelongCiId;                 /*��������ID*/
		UINT8_S BelongZcId;                 /*����ZCID*/
		UINT8_S ChangeAttribute;       /*������������(��־�Ƿ�����ĳ����������)*/
	} EsbConfigDataStruct;

	/*
	* ���������� ��ȡ����ͣ����ť��������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ͣ����ť��ǰ����
	*/
	UINT16_S GetEsbSum(void);

	/*
	* ���������� ��ȡָ�������±��Ӧ�Ľ���ͣ����ťID
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ͣ����ťID      
	*/
	UINT16_S GetEsbId(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ��ID����ͣ����ť������
	* ����˵���� const UINT16 esbId,����ͣ����ťID
	* ����ֵ  �� ESB_LOCAL_SUM_MAX: ��ȡ����ʧ��
	*			<ESB_LOCAL_SUM_MAX: ���ҳɹ�
	*/
	UINT16_S GetEsbConfigBufIndex(const UINT16_S esbId);

	/*
	* ���������� ��ȡָ��IDվ̨����ͣ����ť��������ID
	* ����˵���� const UINT16 esbId,����ͣ����ťID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������ID      
	*/
	UINT8_S GetEsbBelongCiId(const UINT16_S esbId);

	/*
	* ���������� ��ȡָ��ID����ͣ����ť��������ID
	* ����˵���� const UINT16 esbId, ����ͣ����ťID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ZcID      
	*/
	UINT8_S GetEsbBelongZcId(const UINT16_S esbId);

	/*
	* ���������� ��ȡָ��ID����ͣ����ť������������
	* ����˵���� const UINT16 esbId, ����ͣ����ťID     
	* ����ֵ  �� 0: ������
	*			 FLAG_SET: ����      
	*/
	UINT8_S GetEsbChangeAttribute(const UINT16_S esbId);

#ifdef __cplusplus
}
#endif

#endif
