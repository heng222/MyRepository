/********************************************************
*                                                                                                            
* �� �� ���� ACDefine.h  
* ����ʱ�䣺 2015-05-01
* ��    �ߣ� 
* ���������� �������κ궨�� 
* ��  ע  ��  ��
*
********************************************************/ 

#ifndef AC_DEFINE_H_
#define AC_DEFINE_H_

/*ȫ��ZC���ID����ZC�����������*/
#define AC_SUM_MAX 2000U
#define LOCAL_AC_SUM_MAX 400U

/*������������*/
#define AC_MIAN_CI  0x55U                      /*������������CI*/
#define AC_DEPOT_CI  0xaaU                      /*�������ڳ�����CI*/

/*����߽������*/
#define CONDOMINIUM_AC_SELF_ZC  0x55U            /*������ĳ�����������ڣ�����������ZC*/
#define CONDOMINIUM_AC_NEXT_ZC  0xaaU			 /*������ĳ�����������ڣ�����������ZC*/

/*�������г����߼�����*/
#define SIZE_MAX_SECTIONNUM           20U                /*��������������߼���������*/
#define SIZE_MAX_TRAINOFAC            15U                /*���������������е�����г�����*/

/*�������η�������*/
#define AC_DIR_UP_STATUS                     0xaaU       /*����*/
#define AC_DIR_DOWN_STATUS                   0x55U       /*����*/
#define FORWORD_DIRCTION                     0x55U       /*�߼�������*/
#define NEGATIVE_DIRCTION                    0xaaU       /*�߼�������*/

/*�����������г����з�����Ϣ*/
#define AC_DIR_FARAWAY                       1U          /*���������з���ΪԶ��*/
#define AC_DIR_CLOSED                        2U          /*���������з���Ϊ�ӽ�*/
#define AC_DIR_DEFAULT                       3U          /*���������з���Ϊ�޷���*/

/*������������/δ��������*/
#define AC_LOCK_STATUS                       0x55U       /*����*/
#define AC_UNLOCK_STATUS                     0xaaU       /*δ����*/

/*��������ռ��/��������*/
#define AC_OCC_STATUS                        0x55U       /*ռ��*/
#define AC_FREE_STATUS                       0xaaU       /*����*/

/*����������ΰ���������������*/
#define AC_SWITCH_SUM_MAX                    4U          /*�������ΰ���������������*/

/*�������η�ͨ���г�ռ��/δ��ͨ���г�ռ������*/
#define AC_UT_OCC_STATUS                     0x55U       /*�����ͨ���г�ռ��״̬*/
#define AC_UT_FREE_STATUS                    0xaaU       /*����δ��ͨ���г�ռ��״̬*/

/*��������ARBռ��/δARBռ������*/
#define AC_ARB_OCC_STATUS                    0x55U       /*����ARBռ��״̬*/
#define AC_ARB_FREE_STATUS                   0xaaU       /*����δARBռ��״̬*/

#define LINK_BELONG_TO_AC_SUM_MAX            5U          /*link�������������������*/

/*�����ڼ������Ϊ�Ŀ�ʱ�����ڼ�����������*/
#define  MAX_ADJACENT_LOSE_AC                4U

/*������ɨ״̬*/
#define CLEAN_STATUS_DEFAULT                 0U         /*Ĭ��״̬*/
#define CLEAN_STATUS_HEAD_ENTRY			     1U	       /*��ͷ�������ɨ����*/
#define CLEAN_STATUS_ALL_ENTRY			     2U         /*��ͷ��β���������ɨ����*/
#define CLEAN_STATUS_HEAD_OUT				 3U         /*��ͷ�������ɨ����*/
#define CLEAN_STATUS_ALL_OUT				 4U         /*��β�������ɨ����*/

#endif 
