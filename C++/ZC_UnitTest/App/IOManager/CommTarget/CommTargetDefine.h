/************************************************************************
*
* �ļ���   ��  CommTargetDefine.h
* ��  ��   ��  ZC��
* ����ʱ�� ��  2015.07.14
* �������� ��  ͨѶĿ�궨�� 
* ��  ע   ��  ��
*
************************************************************************/
#ifndef COMM_TARGET_DEFINE_H_
#define COMM_TARGET_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*zc�����豸����ͨ�Ŷ����������ֵ(���г���������̶��豸)*/
#define SINGLE_TYPE_COMM_TARGET_SUM_MAX                 6U                           /*ͨ�Ŷ����������ֵ*/

/*�豸����ͨ�Ŷ����������ֵ������ͨ�Ŷ���*/
#define COMM_TARGET_ID_MAX                              (LINE_CI_SUM_MAX)             /*ͨ�Ŷ����������ֵ������ͨ�Ŷ���*/

/*�豸����ͨ�Ŷ����������ֵ��ͨ���г���*/
#define COMM_TRAIN_ID_MAX                               (LINE_MAX_TRAIN_ID)           /*ͨ�Ŷ����������ֵ��ͨ���г���*/

/*����ZCͨ�ŵ�����豸������������ȥ�г���������̶��豸��*/
#define COMM_TYPE_SUM_MAX                               6U                           /*ZCͨ�ŵ�����豸��������*/  


/*ͨ��״̬����*/
#define COMM_STATUS_NORMAL                              ((UINT8_S)(0xaaU))                        /*ͨ��״̬����*/
#define COMM_STATUS_ABNORMAL                            ((UINT8_S)(0x55U))                        /*ͨ��״̬�쳣*/

#endif
