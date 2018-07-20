
/********************************************************                                                                                                           
�� �� ���� OverlapLogicManager.h
��    �ߣ� ZC��
����ʱ�䣺 2015.04.18
������ ���������߼�����  
��ע�� ��  
********************************************************/ 

#ifndef OVERLAP_LOGIC_DATA_H_
#define OVERLAP_LOGIC_DATA_H_


#include "OverlapDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
������:    InitFailureSingleOverlap  
��������: ����ͨ�Ź���Ci��Ӧ�ĵ�������������Ϣ
����: const UINT16 overlapId����������ID    
���: ��
����ֵ: void  
*************************************************/
void InitFailureSingleOverlap(const UINT16_S overlapId);

/*************************************************
������:   InitFailureCiOverlap   
��������: ����ͨ�Ź���Ci��Ӧ�ı���������Ϣ
����: const UINT16 ciId��ͨ�Ź��ϵ�CIID    
���: ��
����ֵ: void  
*************************************************/
void InitFailureCiOverlap(const UINT16_S ciId);

/*************************************************
������:   InitFailureNZcOverlap   
��������: ����ͨ�Ź���nZc��Ӧ�ı���������Ϣ
����: const UINT16 nZcId��ͨ�Ź��ϵ�nZcID    
���: ��
����ֵ: void  
*************************************************/
void InitFailureNZcOverlap(const UINT16_S nZcId);

/*************************************************
������:    CalulateSwtichStateOfOverlapIsNeed  
��������: ���������overlap�Ƿ��������״̬�����պ�λ�ã�
����: const UINT16 overlpId����������ID   
���: ��
����ֵ: 0:����������
*            1:��������  
*************************************************/
UINT8_S CalulateSwtichStateOfOverlapIsNeed(const UINT16_S overlpId);

#ifdef __cplusplus
}
#endif

#endif
