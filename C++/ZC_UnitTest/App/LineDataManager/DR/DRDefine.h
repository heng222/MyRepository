/************************************************************************
*
* �ļ���   ��  DRDefine.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����۷��궨��
* ��  ע   ��  ��
*
************************************************************************/
#ifndef DR_DEFINE_H_
#define DR_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*�����۷���ť�������ֵ*/
#define DR_BUTTON_SUM_MAX                  20U     /*���������۷���ť���ֵ*/

/*�����۷����������ֵ*/
#define DR_LAMP_SUM_MAX                    20U     /*���������۷������ֵ*/

/*���ع���������۷����������ֵ*/
#define DR_BUTTON_LOCAL_SUM_MAX            5U      /*���屾�ع���������۷���ť���ֵ*/

/*���ع���������۷����������ֵ*/
#define DR_LAMP_LOCAL_SUM_MAX              5U      /*���屾�ع���������۷������ֵ*/


/*�����۷���״̬*/
#define DR_LAMP_TWINKLE_STATUS             0x55U   /*�����۷�������״̬*/
#define DR_LAMP_STEADY_STATUS              0xaaU   /*�����۷����ȵ�״̬*/
#define DR_LAMP_DEFAULT_STATUS             0xffU   /*�����۷�����Ч״̬*/

/*�����۷���ť״̬*/
#define DR_BUTTON_STATE_DOWN               0x55U   /*�����۷���ť����*/
#define DR_BUTTON_STATE_UP                 0xaaU   /*�����۷���ťδ����*/


#endif
