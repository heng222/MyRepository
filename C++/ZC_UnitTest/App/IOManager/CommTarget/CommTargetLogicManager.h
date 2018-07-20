/************************************************************************
*
* �ļ���   ��  CommTargetLogicManager.h
* ����     ��  ZC��
* ����ʱ�� ��  2015.07.14
* �������� ��  ͨѶ�����߼�����
* ��  ע   ��  ��
*
************************************************************************/

#ifndef COMM_TARGET_MANAGER_DATA_H_
#define COMM_TARGET_MANAGER_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "CommTargetDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* ��������:  ManagerCommTargetCommCycle
* ���������� ����ͨ�Ŷ���ͨ�����ڹ���
* ��������� void    
* ��������� ��
* ����ֵ  �� ��
*/
void ManagerCommTargetCommCycle(void);

/*
* �������ƣ� JudgeSingleCommTypeCommCyle
* ���������� ����ͨ�Ŷ��󣨳��г��⣩ͨ�����ڹ���
* ��������� const UINT8 commTargetType��ͨ�Ŷ�������  
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeSingleCommTypeCommCyle(const UINT8_S commTargetType);

/*
* �������ƣ� JudgeCommTrainCommCyle
* ���������� ����ͨ���г�ͨ�����ڹ���
* ��������� void    
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeCommTrainCommCyle(void);

/*
* �������ƣ� ManageCommTargetCommStatus
* ���������� ͨ�Ŷ���ͨ��״̬����
* ��������� void    
* ��������� ��
* ����ֵ  �� ��
*/
void ManageCommTargetCommStatus(void);

/*
* �������ƣ� JudgeSingleCommTypeCommStatus
* ���������� ����ͨ�Ŷ��󣨳��г��⣩ͨ��״̬����
* ��������� const UINT8 commTargetType��ͨ�Ŷ�������  
*            const UINT16_S maxCommFaultCycle����ͨ����������ͨ�Ź�������
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeSingleCommTypeCommStatus(const UINT8_S commTargetType,const UINT16_S maxCommFaultCycle);

/*
* �������ƣ� JudgeNtpCommStatus
* ���������� ����NTPͨ��״̬����
* ��������� ��
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeNtpCommStatus(void);

/*
* �������ƣ� JudgeCommTrainCommStatus
* ���������� ����ͨ���г�ͨ��״̬����
* ��������� const UINT16 maxCommFaultCycle����ͨ����������ͨ�Ź�������   
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeCommTrainCommStatus(const UINT16_S maxCommFaultCycle);

/*
* �������ƣ� ManageCommTargetCommFailure
* ���������� ����ͨ�Ŷ���ͨ�Ź���״̬
* ��������� ��   
* ��������� ��
* ����ֵ  �� ��
*/
void ManageCommTargetCommFailure(void);

/*
* �������ƣ� JudgeSingleCommTypeCommFailure
* ���������� �жϵ���ͨ�Ŷ���ͨ�Ź���״̬
* ��������� const UINT8 commTargetType,ͨѶ��������   
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeSingleCommTypeCommFailure(const UINT8_S commTargetType);

/*
* �������ƣ� ProcessCiCommFailure
* ���������� �жϵ���CIͨ�Ŷ���ͨ�Ź���״̬
* ��������� const UINT16 commCiId,ͨѶCI��ID   
* ��������� ��
* ����ֵ  �� ��
*/
void ProcessCiCommFailure(const UINT16_S commCiId);

/*
* �������ƣ� ProcessZcCommFailure
* ���������� �жϵ���ZCͨ�Ŷ���ͨ�Ź���״̬
* ��������� const UINT16 commZcId,ͨѶZC��ID   
* ��������� ��
* ����ֵ  �� ��
*/
void ProcessZcCommFailure(const UINT16_S commZcId);

/*
* �������ƣ� JudgeTrainCommFailure
* ���������� �ж��г�ͨ�Ź���״̬
* ��������� ��   
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeTrainCommFailure(void);

/*
* �������ƣ� ProcessTrainCommFailure
* ���������� �жϵ����г�ͨ�Ź���״̬
* ��������� const UINT16 commTrainId,ͨѶ�г�ID   
* ��������� ��
* ����ֵ  �� ��
*/
void ProcessTrainCommFailure(const UINT16_S commTrainId);

/*
* �������ƣ� FindFrontTrainOfTrainCommFailure
* ���������� ���ҹ����г�ǰ���г�����ͷ���ڼ���ͳ�ͷ���ڼ���ǰ�����ᣩ
* ��������� const UINT16 trainId,�г���ID 
*            const UINT16_S acId,��ͷ���ڼ�������
* ��������� ��
* ����ֵ  �� 0:δ�鵽�г�
*           >0:�г�Id
*/
UINT16_S FindFrontTrainOfTrainCommFailure(const UINT16_S trainId,const UINT16_S acId);

/*
* �������ƣ� FindRearTrainOfTrainCommFailure
* ���������� ���ҹ����г����г�����ͷ���ڼ���ͳ�ͷ���ڼ���ǰ�����ᣩ
* ��������� const UINT16 trainId,�г���ID 
*            const UINT16_S acId,��β���ڼ�������
* ��������� ��
* ����ֵ  �� 0 :δ�鵽�г�
*            >0:�г�Id
*/
UINT16_S FindRearTrainOfTrainCommFailure(const UINT16_S trainId,const UINT16_S acId);
	
#ifdef __cplusplus
}
#endif

#endif
