/************************************************************************
*
* �ļ���   ��  SignalDefine.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �źŻ��궨��
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SIGNAL_DEFINE_H_
#define SIGNAL_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*���źŻ��������ֵ*/
#define SIGNAL_SUM_MAX                        500U    /*�����źŻ����ֵ*/

/*���ع�����źŻ��������ֵ*/
#define SIGNAL_LOCAL_SUM_MAX                  (100U+120U)     /*���屾�ع�����źŻ����ֵ*/

/*�źŻ��ĵ�ǰ״̬*/
#define SIGNAL_STATE_PASS                     0x55U   /*�źŻ�ͨ���ź�*/
#define SIGNAL_STATE_STOP                     0xaaU   /*�źŻ�ֹͣ�ź�*/

/*�źŻ������������״̬*/
#define SIGNAL_LIGHT_COMMAND                  0x55U   /*�źŻ���������*/
#define SIGNAL_OFF_COMMAND                    0xaaU   /*�źŻ��������*/

/*�źŻ����г���ѹ״̬*/
#define SIGNAL_TRAIN_ALREADY_CROSS            0x55U   /*�źŻ��г��ѿ�ѹ״̬*/
#define SIGNAL_TRAIN_NOT_CROSS                0xaaU   /*�źŻ��г�δ��ѹ״̬*/

/*�ж��źŻ������������������������*/
#define SIGNAL_LIGHT_OFF_AC_NUM_MAX           10U     /*�����ļ��������������*/

#endif
