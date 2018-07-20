/************************************************************************
*
* �ļ���   ��  CommTargetInitManager.h
* ����     ��  ZC��
* ����ʱ�� ��  2015.07.14
* �������� ��  ͨѶĿ���ʼ��
* ��  ע   ��  ��
*
************************************************************************/

#ifndef COMM_TARGET_INIT_MANAGER_H_
#define COMM_TARGET_INIT_MANAGER_H_

#include "../../../Common/CommonTypes.h"
#include "CommTargetDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* �������ƣ� InitCommTargetInfo
* ���������� ��ʼ��ͨ�Ŷ����ϵ
* ��������� void    
* ��������� ��
* ����ֵ  �� 0u: ��ʼ��ʧ��
*			 1u: ��ʼ���ɹ�
*/
UINT8_S InitCommTargetInfo(void);

/*
* �������ƣ� InitOtherCommTargetInfo
* ���������� ��ʼ������ͨ�Ŷ��󣨷��г�����ͨ�Ź�ϵ
* ��������� void   
* ��������� ��
* ����ֵ  �� 0u: ��ʼ��ʧ��
*			 1u: ��ʼ���ɹ�
*/
UINT8_S InitOtherCommTargetInfo(void);

/*
* �������ƣ� InitTrainCommTargetInfo
* ���������� ��ʼ���г�ͨ�Ŷ����ͨ�Ź�ϵ
* ��������� void    
* ��������� ��
* ����ֵ  �� ��
*/
void InitTrainCommTargetInfo(void);
	
#ifdef __cplusplus
}
#endif

#endif
