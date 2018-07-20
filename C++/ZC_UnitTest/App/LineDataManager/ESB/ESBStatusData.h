/************************************************************************
*
* �ļ���   ��  ESBStatusData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����ͣ����ť״̬����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef ESB_STATUS_DATA_H_
#define ESB_STATUS_DATA_H_


#include "ESBDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*����ͣ����ť״̬���ݽṹ��*/
	typedef struct EsbDataStruct
	{
		UINT16_S EsbId;                     /*����ͣ����ť��ťID*/
		UINT8_S EsbStatus;                  /*����ͣ����ť��ǰ״̬*/
	} EsbDataStruct;


	/*
	* ���������� ��ȡ����ͣ����ť����
	* ����˵���� void    
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*			 !NULL: ����ͣ����ť����
	*/
	EsbDataStruct* GetEsbStatusData(void);

	/*
	* ���������� ��ȡ����ͣ����ť��ǰ״̬
	* ����˵���� esbId ����ͣ����ťID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ͣ����ť״̬
	*/
	UINT8_S GetEsbStatus(const UINT16_S esbId);

	/*
	* ���������� ���ý���ͣ����ť��ǰ״̬
	* ����˵���� esbId ����ͣ����ťID; 
	*	         esbStatus ����ͣ����ť״̬    
	* ����ֵ  �� 0;ʧ��
	*            1;�ɹ�
	*/
	UINT8_S SetEsbStatus(const UINT16_S esbId,UINT8_S esbStatus);

#ifdef __cplusplus
}
#endif

#endif
