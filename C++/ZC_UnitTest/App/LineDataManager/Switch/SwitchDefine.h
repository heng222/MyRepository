/************************************************************************
*
* �ļ���   ��  SwitchDefine.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����궨��
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SWITCH_DEFINE_H_
#define SWITCH_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*�����������ֵ*/
#define SWITCH_SUM_MAX                            500U    /*����������ֵ*/

/*���ع���ĵ����������ֵ*/
#define SWITCH_LOCAL_SUM_MAX                      50U     /*���屾�ع���ĵ������ֵ*/

/*��������/δ����״̬*/
#define SWITCH_STATE_LOCK                         0x55U   /*��������*/
#define SWITCH_STATE_UNLOCK                       0xaaU   /*����δ����*/

/*����ռ��/����״̬*/
#define SWITCH_STATE_OCCUPY                       0x55U   /*����ռ��*/
#define SWITCH_STATE_FREE                         0xaaU   /*�������*/

/*����״̬(���������Ŀ�)*/
#define SWITCH_STATE_MAIN                         1U	     /*����λ״̬*/
#define SWITCH_STATE_SIDE                         2U		 /*����λ״̬*/
#define SWITCH_STATE_LOSE                         3U		 /*����ʧ��״̬*/

/*����λ������*/
#define SWITCH_POSITION_DEPOT                     0x55U   /*������/ͣ��������*/
#define SWITCH_POSITION_MAIN                      0xaaU   /*���ߵ���*/

/*�����������������������*/
#define SWITCH_BELONG_AC_SUM_MAX                  12U     /*�����������������������*/

#endif
