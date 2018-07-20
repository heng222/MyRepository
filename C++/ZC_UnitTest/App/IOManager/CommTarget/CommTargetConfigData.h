/************************************************************************
*
* �ļ���   ��  CommTargetConfigData.h
* ��  ��   ��  ZC��
* ����ʱ�� ��  2015.07.14
* �������� ��  ͨѶĿ������
* ��  ע   ��  ��
*
************************************************************************/

#ifndef COMM_TARGET_CONFIG_DATA_H_
#define COMM_TARGET_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "CommTargetDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


/*ͨ�Ŷ����������ݽṹ��*/
typedef struct CommTargetConfigDataStruct
{
	UINT8_S CommTargetType;                                          /*ͨ�Ŷ����豸ʶ���*/
	UINT8_S CommTargetNum;                                           /*��ͨ�Ŷ����ͨ���豸����*/
	UINT16_S CommTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX];       /*ͨ�Ŷ���ID����*/
	UINT8_S CommProtocolType;                                        /*ͨ��Э������*/
} CommTargetConfigDataStruct;

/*
* �������ƣ� GetCommTargetTypeBuffIndex
* ���������� ��ȡͨ�����ʹ洢�±�
* ��������� const UINT8 commTargetType ͨ���豸����    
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ǰ����
*/
UINT8_S GetCommTargetTypeBuffIndex(const UINT8_S commTargetType);

/*
* �������ƣ� GetCommTargetTypeSum
* ���������� ��ȡͨ�����;�����
* ��������� void    
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ǰ����
*/
UINT8_S GetCommTargetTypeSum(void);

/*
* �������ƣ�GetSingleCommTargetTypeSum
* ���������� ��ȡĳ��ͨ���豸����
* ��������� const UINT8 commTargetType ͨ���豸���� 
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ǰ����
*/
UINT8_S GetSingleCommTargetTypeSum(const UINT8_S commTargetType);

/*
* �������ƣ� GetSingleCommTargetIdBuff
* ���������� ��ȡĳ���豸��ͨ��ID����
* ��������� const UINT8 commTargetType ͨ���豸����   
*            const UINT8_S bufSize �����С
* ��������� UINT16_S commTargetIdBuff[] �������
* ����ֵ  �� 0u: ��ȡ����ʧ��
*			 1u: ��ȡ���ݳɹ�
*/
UINT8_S GetSingleCommTargetIdBuff(const UINT8_S commTargetType,const UINT8_S bufSize,UINT16_S commTargetIdBuff[]);

/*
* �������ƣ� GetSingleCommProtocolType
* ���������� ��ȡĳ��ͨ�Ŷ���ʹ�õ�Э������
* ��������� const UINT8 commTargetType ͨ���豸����    
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ǰ����
*/
UINT8_S GetSingleCommProtocolType(const UINT8_S commTargetType);

/*
* �������ƣ� GetCommTargetIdInConfigData
* ���������� ��ȡͨ�Ŷ���Id�Ƿ����ڱ�ZCͨ�ŷ�Χ
* ��������� const UINT8 commTargetType, ͨѶĿ�������    
*            const UINT16_S commTargetId,ͨѶĿ��ı��
* ��������� ��
* ����ֵ  �� 0u: ������
*			 1u: ����      
*/
UINT8_S GetCommTargetIdInConfigData(const UINT8_S commTargetType, const UINT16_S commTargetId);

#ifdef __cplusplus
}
#endif

#endif
