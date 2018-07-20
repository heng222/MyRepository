
/********************************************************                                                                                                           
�� �� ���� OverlapStatusData.h
��    �ߣ� ZC��
����ʱ�䣺 2015.04.18
������ ��������״̬  
��ע�� ��  
********************************************************/ 

#ifndef OVERLAP_STATUS_DATA_H_
#define OVERLAP_STATUS_DATA_H_


#include "OverlapDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/*��������״̬���ݽṹ��*/
typedef struct OverlapDataStruct
{
	UINT16_S OverlapId;                     /*�������ΰ�ťID*/
	UINT8_S OverlapStatus;                  /*�������ε�ǰ״̬*/
} OverlapDataStruct;


/*************************************************
������:   GetOverlapStatusData   
��������: ��ȡ������������
����: void    
���: ��
����ֵ: NULL: ��ȡ����ʧ��
*			 !NULL: ������������
*************************************************/
OverlapDataStruct* GetOverlapStatusData(void);

/*************************************************
������:   GetOverlapStatus   
��������: ��ȡ�������ε�ǰ״̬
����: overlapId ��������ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: ��������״̬
*************************************************/
UINT8_S GetOverlapStatus(const UINT16_S overlapId);

/*************************************************
������:   SetOverlapStatus   
��������: ���ñ������ε�ǰ״̬
����: overlapId ��������ID; 
	        overlapStatus ��������״̬    
���: ��
����ֵ: ��
*************************************************/
UINT8_S SetOverlapStatus(const UINT16_S overlapId,UINT8_S overlapStatus);

#ifdef __cplusplus
}
#endif

#endif
