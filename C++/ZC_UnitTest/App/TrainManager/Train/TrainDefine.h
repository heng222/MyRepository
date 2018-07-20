/************************************************************************
 �ļ�����  TrainDefine.h
 ����  ��  ZC��
 ����ʱ�� ��  2015-07-01
 ���� ��  �г��궨��
 ��ע �� ��
************************************************************************/
#ifndef TRAIN_DEFINE_H_
#define TRAIN_DEFINE_H_

#define SIZE_MAX_ROUTENUM  3U			/*�г���ƥ���·����*/
#define SIZE_MAX_LINE_TRAIN 150U         /*���������ܵ��г�����*/
#define SIZE_MAX_CONTROLE_TRAIN 40U		/*��ZC���Ʒ�Χ������г�����*/

#define TRAIN_ERROR_MAX_NUM      500U    /*�г����ȷ�����*/

#define TRAIN_MIN_SPEED          14U     /*�����г���С���ٶ�*/

/*�г�����*/
#define TRAIN_MODE_CBTC                     1U                 /*��ZC�����г�*/
#define TRAIN_MODE_TO_RM0                   2U                 /*�ȴ�����ΪRM0���г�*/
#define TRAIN_MODE_RM                       3U                 /*���߻ָ��г�*/
#define TRAIN_MODE_RM0                      4U                 /*���߻ָ�RM0�г�*/
#define TRAIN_MODE_IN                       5U                 /*�����г�*/
#define TRAIN_MODE_OUT                      6U                 /*ע���г�*/

/*�г�״̬*/
#define TRAIN_STATE_MOVING                  1U                 /*��������״̬*/
#define TRAIN_STATE_HANDOVER                2U                 /*�ƽ�״̬*/
#define TRAIN_STATE_TAKEOVER                3U                 /*�ӹ�״̬*/
#define TRAIN_STATE_REVERSE                 4U                 /*�۷�״̬*/
#define TRAIN_STATE_CANCELLATION            5U                 /*ע��״̬*/
#define TRAIN_STATE_FAILURE                 6U                 /*����״̬*/

/*�г���ǰ����ģʽ*/
#define TRAIN_IN_MODE_RM                    1U                 /*RMģʽ*/
#define TRAIN_IN_MODE_CM                    2U                 /*ATPģʽ*/
#define TRAIN_IN_MODE_AM                    3U                 /*ATOģʽ*/
#define TRAIN_IN_MODE_EUM                   4U                 /*BYPASSģʽ*/
#define TRAIN_IN_MODE_RD                    5U                 /*RDģʽ*/

/*�г����м���*/
#define TRAIN_IN_LEVEL_CBTC                    3U                 /*CBTC���м���*/
#define TRAIN_IN_LEVEL_BLOC                    2U                 /*BLOC���м���*/
#define TRAIN_IN_LEVEL_IL                      1U                 /*IL���м���*/

/*�г�������Ϣ*/
#define TRAIN_IN_APPLY_MA                   1U                 /*����MA*/
#define TRAIN_IN_HANDOVERTOCANCEL           2U                 /*�л�ע������*/
#define TRAIN_IN_REVERSETOCANCEL            4U                 /*�۷�ע������*/
#define TRAIN_IN_TOEXITCBTC                 3U                 /*�˳�CBTC����*/
#define TRAIN_IN_CHANGED                    5U                 /*�г��������*/


/*�г������Ϣ*/
#define OUT_TRAIN_MOVING                    1U                 /*��������(����MA)*/
#define OUT_TRAIN_HANDOVERTOCANCEL          2U                 /*�л�ע��ȷ��*/
#define OUT_TRAIN_REVERSETOCANCEL           4U                 /*�۷�ע��ȷ��*/
#define OUT_TRAIN_TOEXITCBTC                3U                 /*�˳�CBTCȷ��*/
#define OUT_TRAIN_CHANGED                   5U                 /*�г��������ȷ��*/

/*��ZC�����л���Ϣ*/
#define NZC_TRAIN_DEFAULT                   0U                 /*��״̬*/
#define NZC_TRAIN_HANDOVER                  1U                 /*�ƽ�����*/
#define NZC_TRAIN_CONFIRMATION              2U                 /*�ƽ�����ȷ��*/
#define NZC_TRAIN_HADTOOKOVER               3U                 /*�ѽӹ�*/
#define NZC_TRAIN_MANAGENOHAND              4U                 /*�ƽ�δ�л�*/
#define NZC_TRAIN_MANAGENOTAKE              5U                 /*�ӹ�δ�л�*/

/*�г��������з���*/
#define TRAIN_UNSAFE_DIR_UP                 0x55U              /*�г��������з���-����*/
#define TRAIN_UNSAFE_DIR_DOWN               0xaaU              /*�г��������з���-����*/

#define SIZE_MAX_SECTION_OF_TRAIN            10U      /*�г�ռѹ������߼���������*/

#define SIZE_MAX_SWITCH_MUM_OF_SAFE_TRAIN   10U                /*�г���ȫλ�ü���ʱʹ�õĵ�������*/

#endif
