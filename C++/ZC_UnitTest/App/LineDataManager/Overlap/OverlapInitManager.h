
/********************************************************                                                                                                           
�� �� ���� OverlapInitManager.h
��    �ߣ� ZC��
����ʱ�䣺 2015.04.18
������ �������γ�ʼ��  
��ע�� ��  
********************************************************/ 



#ifndef OVERLAP_INIT_MANAGER_H_
#define OVERLAP_INIT_MANAGER_H_


#include "OverlapDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
������:    InitOverlapInitializationData  
��������: ��ʼ�����ع���ı������γ�ʼ��Ϣ
����: ��   
���: ��
����ֵ: ��      
*************************************************/
void InitOverlapInitializationData(void);

/*************************************************
������:   InitOverlapLocalInfo   
��������: ��ʼ�����ع���ı���������Ϣ
����: ��   
���: ��
����ֵ: 0: ��ʼ��ʧ��
		>0: ��ʼ���ɹ�      
*************************************************/
UINT8_S InitOverlapLocalInfo(void);

#ifdef __cplusplus
}
#endif

#endif
