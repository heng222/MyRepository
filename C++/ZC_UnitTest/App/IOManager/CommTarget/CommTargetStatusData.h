/************************************************************************
*
* �ļ���   ��  CommTargetStatusData.h
* ����     ��  ZC��
* ����ʱ�� ��  2015.07.14
* �������� ��  ͨѶ����״̬
* ��  ע	��  ��
*
************************************************************************/

#ifndef COMM_TARGET_STATUS_DATA_H_
#define COMM_TARGET_STATUS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "CommTargetDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*ͨ�Ŷ���״̬���ݽṹ��*/
typedef struct SingleCommTargeStruct
{
	UINT16_S CommTargetId;                                    /*ͨ�Ŷ���ID*/	
	UINT8_S CommTargetStatus;                                /*ͨ��״̬*/
	UINT32_S CommTargetCycle;                                /*ͨ�������ۼ�λ*/
	UINT32_S CommTargetCycleNum;                             /*ͨ�Ŷ���������Ϣʱ�����ں�*/
} SingleCommTargeStruct;

/*ͨ�Ŷ���״̬���ݽṹ�壨����ͨ�Ŷ���*/
typedef struct CommTargetDataStruct
{
	UINT8_S CommTargetType;                                  /*ͨ�Ŷ�������*/
	UINT8_S CommTargetNum;                                   /*ͨ�Ŷ���ID����*/
	UINT8_S CommTargetIdBuff[COMM_TARGET_ID_MAX];            /*�豸ͨ��������*/
	SingleCommTargeStruct SingleCommTargeStru[SINGLE_TYPE_COMM_TARGET_SUM_MAX];          /*ͨ�������ۼ�λ*/
} CommTargetDataStruct;

/*
* ���������� ��ȡͨ�Ŷ�����Ϣ
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡͨ�Ŷ�����Ϣ
*/
CommTargetDataStruct* GetCommTargetStatusData(void);

/*
* ���������� ��ȡͨ�Ŷ���Id��Ӧ���±�
* ����˵���� const UINT8 commTargetType ����
			const UINT16_S commTargetId  ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����Id��Ӧ���±�
*/
UINT8_S GetOtherCommTargetIdBuffIndex(const UINT8_S commTargetType,const UINT16_S commTargetId);

/*
* ���������� ��ȡĳͨ�Ŷ���ͨ���ۼ���Ϣ
* ����˵���� const UINT8 commTargetType ͨ�Ŷ�������
*            const UINT16_S commTargetID ͨ�Ŷ���ID    
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*			>=0: ͨ���ۼ���Ϣ
*/
UINT16_S GetCommTargetCycle(const UINT8_S commTargetType,const UINT16_S commTargetId);

/*
* ���������� ����ĳͨ�Ŷ���ͨ���ۼ���Ϣ
* ����˵���� const UINT8 commTargetType ͨ�Ŷ�������
*			 const UINT16_S commTargetID ͨ�Ŷ���ID  
*			 const UINT16_S commTargetCycle ͨ�Ŷ����ۼ���Ϣ    
* ����ֵ  �� 0: ����ʧ��
*			 1: ���óɹ�
*/
UINT8_S SetCommTargetCycle(const UINT8_S commTargetType,const UINT16_S commTargetId, const UINT16_S commTargetCycle);

/*
* ���������� ��ȡĳͨ�Ŷ���״̬��Ϣ
* ����˵���� const UINT8 commTargetType ͨ�Ŷ�������
*			 const UINT16_S commTargetID ͨ�Ŷ���ID      
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>=0: ״̬��Ϣ
*/
UINT8_S GetCommTargetStatus(const UINT8_S commTargetType,const UINT16_S commTargetId);

/*
* ���������� ����ĳͨ�Ŷ���״̬��Ϣ
* ����˵���� const UINT8 commTargetType ͨ�Ŷ�������
*            const UINT16_S commTargetID ͨ�Ŷ���ID    
*            const UINT8_S commTargetStatus ͨ�Ŷ���״̬��Ϣ 
* ����ֵ  �� 0: ����ʧ��
*			 1: ���óɹ�
*/
UINT8_S SetCommTargetStatus(const UINT8_S commTargetType,const UINT16_S commTargetId, const UINT8_S commTargetStatus);

/*
* ���������� ��ȡĳͨ�Ŷ���ͨ�Ŷ���������Ϣʱ�����ں�
* ����˵���� const UINT8 commTargetType ͨ�Ŷ�������
*			 const UINT16_S commTargetID ͨ�Ŷ���ID     
* ����ֵ  ��  0: ��ȡ����ʧ��
*			>=0: ͨ�Ŷ���������Ϣʱ�����ں�
*/
UINT32_S GetCommTargetCycleNum(const UINT8_S commTargetType,const UINT16_S commTargetId);

/*
* ���������� ����ĳͨ�Ŷ���������Ϣ
* ����˵����const UINT8 commTargetType ͨ�Ŷ�������
*           const UINT16_S commTargetID ͨ�Ŷ���ID  
*           const UINT32_S commTargetCycleNum ͨ�Ŷ���������Ϣ    
* ����ֵ  �� 0: ����ʧ��
*			 1: ���óɹ�
*/
UINT8_S SetCommTargetCycleNum(const UINT8_S commTargetType,const UINT16_S commTargetId, const UINT32_S commTargetCycleNum);

/*
* ���������� ����ͨ�Ŷ���ͨ�Ź���״̬
* ����˵���� ��   
* ����ֵ  �� ��
*/
void ClearOneTrainCommCycleAndStatus(const UINT16_S trainId);
#ifdef __cplusplus
}
#endif

#endif
