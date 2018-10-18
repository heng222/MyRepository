
/********************************************************                                                                                                           
�� �� ���� ChangeInitManager.h
��    �ߣ� ZC��
����ʱ�䣺 2015.04.18
������ �л������ʼ������  
��ע�� ��  
********************************************************/ 

#ifndef CHANGE_INIT_MANAGER_H_
#define CHANGE_INIT_MANAGER_H_

#include "../../../Common/CommonTypes.h"
#include "ChangeConfigData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
������:   InitChangeLineInitializationData   
��������: ��ʼ�����ع������л���·��ʼ��Ϣ
����: ��   
���: ��
����ֵ: ��     
*************************************************/
void InitChangeLineInitializationData(void);


/*************************************************
������:  InitChangeInfo    
��������: ��ʼ���л���������
����: void 
���: ��
����ֵ: 0: ��ʼ��ʧ��
			1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeInfo(void);

/*************************************************
������:   InitChangeLineInfo   
��������: ��ʼ���л���·����
����: void  
���: ��
����ֵ: 0: ��ʼ��ʧ��
			1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeLineInfo(void);

/*************************************************
������:   InitZcNZcMaskConfigCommTargetData   
��������: ��ʼ��ZC-NZC��λ������Ϣ����λ��Ϣ
����: ��   
���: ��
����ֵ: 0: ��ʼ��ʧ��
		>0: ��ʼ���ɹ�      
*************************************************/
UINT8_S InitZcNZcMaskConfigCommTargetData(void);

/*************************************************
������:    InitChangeAreaMaskInfo  
��������: ��ʼ���л�������λ����
����: void  
���: ��
����ֵ: 0: ��ʼ��ʧ��
*			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaMaskInfo(void);

/*************************************************
������:   InitChangeAreaOfSwitchMask   
��������: ��ʼ���л�������λ����(��������)
����: void  
���: ��
����ֵ: 0: ��ʼ��ʧ��
			1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfSwitchMask(void);

/*************************************************
������:  InitChangeAreaOfSignalMask    
��������: ��ʼ���л�������λ����(�źŻ�����)
����: void  
���: ��
����ֵ: 0: ��ʼ��ʧ��
*			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfSignalMask(void);

/*************************************************
������:   InitChangeAreaOfPsdMask   
��������: ��ʼ���л�������λ����(����������)
����: void  
���: ��
����ֵ: 0: ��ʼ��ʧ��
			1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfPsdMask(void);

/*************************************************
������:    InitChangeAreaOfEsbMask  
��������: ��ʼ���л�������λ����(����ͣ����ť����)
����: void  
���: ��
����ֵ: 0: ��ʼ��ʧ��
			1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfEsbMask(void);

/*************************************************
������:   InitChangeAreaOfAcMask   
��������: ��ʼ���л�������λ����(������������)
����: void  
���: ��
����ֵ: 0: ��ʼ��ʧ��
			1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfAcMask(void);

/*************************************************
������:   InitChangeAreaOfRouteMask   
��������: ��ʼ���л�������λ����(��·����)
����: void  
���: ��
����ֵ: 0: ��ʼ��ʧ��
			1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfRouteMask(void);

/*************************************************
������:   InitChangeAreaOfOverlapMask   
��������: ��ʼ���л�������λ����(������������)
����: void  
���: ��
����ֵ: 0: ��ʼ��ʧ��
			1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfOverlapMask(void);

/*************************************************
������:  InitChangeAreaOfDrMask    
��������: ��ʼ���л�������λ����(�����۷�����)
����: void  
���: ��
����ֵ: 0: ��ʼ��ʧ��
			1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfDrMask(void);

#ifdef __cplusplus
}
#endif

#endif