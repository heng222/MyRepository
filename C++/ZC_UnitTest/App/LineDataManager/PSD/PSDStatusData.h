/************************************************************************
*
* �ļ���   ��  PSDStatusData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ������״̬����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef PSD_STATUS_DATA_H_
#define PSD_STATUS_DATA_H_


#include "PSDDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*������״̬���ݽṹ��*/
	typedef struct PsdDataStruct
	{
		UINT16_S PsdId;                     /*�����Ű�ťID*/
		UINT8_S PsdStatus;                  /*�����ŵ�ǰ״̬*/
	} PsdDataStruct;


	/*
	* ���������� ��ȡ����������
	* ����˵���� void    
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*			 !NULL: ����������
	*/
	PsdDataStruct* GetPsdStatusData(void);

	/*
	* ���������� ��ȡ�����ŵ�ǰ״̬
	* ����˵���� psdId ������ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ������״̬
	*/
	UINT8_S GetPsdStatus(const UINT16_S psdId);

	/*
	* ���������� ���������ŵ�ǰ״̬
	* ����˵���� psdId ������ID; 
	             psdStatus ������״̬    
	* ����ֵ  �� ��
	*/
	UINT8_S SetPsdStatus(const UINT16_S psdId,UINT8_S psdStatus);

#ifdef __cplusplus
}
#endif

#endif
