/************************************************************************
*
* �ļ���   ��  PSDConfigData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��������������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef PSD_CONFIG_DATA_H_
#define PSD_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "PSDDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*���������ݽṹ��*/
	typedef struct PsdConfigDataStruct
	{
		UINT16_S PsdId;                     /*������ID*/
		UINT8_S BelongCiId;                 /*��������ID*/
		UINT8_S BelongZcId;                 /*����ZCID*/
		UINT8_S ChangeAttribute;       /*������������(��־�Ƿ�����ĳ����������)*/
	} PsdConfigDataStruct;

	/*
	* ���������� ��ȡ�����Ź�������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �����ŵ�ǰ����
	*/
	UINT16_S GetPsdSum(void);

	/*
	* ���������� ��ȡָ�������±��Ӧ��������ID
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ������ID      
	*/
	UINT16_S GetPsdId(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ��ID������������
	* ����˵���� const UINT16 psbId,������ID
	* ����ֵ  �� PSD_LOCAL_SUM_MAX; ��ȡ����ʧ��
	*			  >=0;���������ɹ�
	*/
	UINT16_S GetPsdConfigBufIndex(const UINT16_S psdId);

	/*
	* ���������� ��ȡָ��IDվ̨��������������ID
	* ����˵���� const UINT16 psdId,������ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������ID      
	*/
	UINT8_S GetPsdBelongCiId(const UINT16_S psdId);

	/*
	* ���������� ��ȡָ��ID��������������ID
	* ����˵���� const UINT16 psdId, ������ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ZcID      
	*/
	UINT8_S GetPsdBelongZcId(const UINT16_S psdId);

	/*
	* ���������� ��ȡָ��ID�����Ź�����������
	* ����˵���� const UINT16 psdId, ������ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT16_S GetPsdChangeAttribute(const UINT16_S psdId);

#ifdef __cplusplus
}
#endif

#endif
