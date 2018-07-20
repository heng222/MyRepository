/********************************************************
*                                                                                                            
* �� �� ���� AdptAppCommonDef.h   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� �ӿڶ���ͷ�ļ� 
* ��    ע�� �� 
*
********************************************************/ 

#ifndef ADPT_APP_COMMON_DEF_H
#define ADPT_APP_COMMON_DEF_H

#include "../../Common/CommonTypes.h"

#define UDP_OUT_FRAME_LEN           1400u                /*UDP���һ֡������󳤶�*/

/*�豸״̬��غ궨��*/
#define DEV_STATE_EXIST_NO         1u                   /*�豸������*/
#define DEV_STATE_INIT             2u                   /*�豸��ʼ��*/
#define DEV_STATE_NORMAL           4u                   /*�豸����״̬ */
#define DEV_STATE_FAULT            5u                   /*�豸����״̬ */
#define DEV_STATE_SELFCHECK        6u                   /*�豸�Լ�*/

/*����-ͨ���豸����*/
#define MIC_R_NUM        3u                       /* ��ͨ�豸������Ŀ */
#define DEVTYPE_MIC_R    0x0bu                    /* ��ͨ�豸�������� */ 
#define DEVTYPE_MIC_NTP  0x0cu                    /* NTP�豸�������� */ 

#define DEVTYPE_CI       0x3cu                    /*CI�������ͺ����*/    
#define DEVTYPE_ZC       0x1eu                    /*����ZC���ݺ����*/    
#define DEVTYPE_ATS      0x03u                    /*ATS���ݺ����*/
#define DEVTYPE_VOBC     0x14u                    /*VOBC�����*/
#define DEVTYPE_NTP      0x33u                    /*NTP�����*/

#define DEVTYPE_SIM      0x1au                    /*��������*/
#define DEVTYPE_NMS      0x34u                    /*NMS�����*/
#define DEVTYPE_DMS      0x2bu                    /* DMS���ݺ���� */  
#define DEVTYPE_TESTPC   0x11u                    /*��������λ�������*/

/*������-ͨ���豸����(���Ͳ���)*/
#define DEVTYPE_ATP      0x13u                    /*ATP�����1d*/
#define DEVTYPE_ATO      0x08u                    /*ATO�����1c*/
#define DEVTYPE_DMI      0x07u                    /*DMI�����2a*/
#define DEVTYPE_RADA     0x0Au                    /*�״�����2c*/
#define DEVTYPE_BTM      0x09u                    /*BTM�����2d*/
#define DEVTYPE_UNUSED   0xffu                    /*���õĺ����*/

#define DEVTYPE_MAINTAIN 0x1bu                    /* ������־�豸���� */
#define DEVTYPE_RECORD   0x1cu                    /* ��¼���豸���� */
#define DEVTYPE_TEST     0x0fu                    /* Ϊ����BTM���������豸���� */ 




#define  FUNC_TURE                  0x55u               /*�ɹ�*/
#define  FUNC_FALSE                 0xAAu               /*ʧ��*/
#define  FUNC_WAIT                  0xFFu               /*�ȴ�*/





/*������غ궨��*/

#define SWITCH_COL_INVALID          0xAAu               /*�ɼ�������Ч*/
#define SWITCH_COL_VALID            0x55u               /*�ɼ�������Ч*/

#define SWITCH_DRV_INVALID          0xAAu               /*����������Ч*/
#define SWITCH_DRV_VALID            0x55u               /*����������Ч*/


/*�ٶ���غ궨��*/
#define TRAIN_DIR_FORWARD           0x55u               /*���з���:ǰ��*/
#define TRAIN_DIR_BACK              0xAAu               /*���з���:����*/
#define TRAIN_DIR_NO                0x00u               /*���з���:δ֪(δ��ȡ��)*/
#define TRAIN_DIR_INVALID           0xFFu               /*���з���:��Ч(��ȡ�����򣬵����򲻺Ϸ�)*/

#define ACC_DIR_FRONT               0x55u               /*������ٶ�(���ٶ�)*/
#define ACC_DIR_BACK                0xAAu               /*������ٶ�(���ٶ�)*/


#define WHEEL_STATUS_NORMAL         0x55u               /*��ת״̬����*/
#define WHEEL_STATUS_SPIN           0x11u               /*��ת״̬��ת*/
#define WHEEL_STATUS_ROLLER         0x22u               /*��ת״̬�ֻ�*/
#define WHEEL_STATUS_UNKOWN         0xAAu               /*��ת״̬δ֪*/


#define TRAIN_SPEED_INVLID          0xFFFFu             /*�ٶ���Чֵ*/
#define ACC_INVLID                  0xFFFFu             /*���ٶ���Чֵ*/
#define SPACE_INVLID                FLOAT32_MAX         /*������Чֵ*/
#define SENSOR_SPACE_INVLID         0xFFFFFFFFu         /*�ٶȴ������ۼƾ�����Чֵ*/


#define INFOR_FLAG_VALID            0x55u               /*��Ϣ��Ч*/
#define INFOR_FLAG_INVALID          0xAAu               /*��Ϣ��Ч*/



/*�Ƿ���Ҫ����SFI����*/
#define ODO_PARA_UPDATE_YES            1u                /* ��Ҫ���²���*/
#define ODO_PARA_UPDATE_NO             0u                /* ������²���*/

/*�Ƿ���ҪУ������*/
#define ODO_CALIB_YES            1u                /* ��ҪУ������*/
#define ODO_CALIB_NO             0u                /* ����У������*/

/*************************************************�������������*******************************************/
/*ATPӦ��ʹ�õ����п������������:�����ƶ�,����ʹ��,����ʹ��,ǣ���ж�,ARָʾ�����,ATOʹ�����,AR�̵������,��7��*/


/*��ȫ���:7*/
#define ATP_EB_OUTPUT                      ((UINT32_S)0x00000001u)    /*�����ƶ�*/
#define ATP_QYQD_OUTPUT                    ((UINT32_S)0x00000010u)    /*ǣ���ж�*/
#define ATP_LEFTDOOR_EN_OUTPUT             ((UINT32_S)0x00000004u)    /*����ʹ��*/
#define ATP_RIGHTDOOR_EN_OUTPUT            ((UINT32_S)0x00000008u)    /*����ʹ��*/
#define ATP_ATO_ENABLE1_OUTPUT             ((UINT32_S)0x00000040u)    /*ATOʹ�����1*/
#define ATP_ATO_ENABLE2_OUTPUT             ((UINT32_S)0x00000100u)    /*ATOʹ�����2*/
#define ATP_ZERO_SPEEDSIG_OUTPUT           ((UINT32_S)0x00000200u)    /*�����ź�*/

/*�ǰ�ȫ���:2*/
#define ATP_AR_LAMP_OUTPUT                 ((UINT32_S)0x00000020u)    /*ARָʾ�����*/
#define ATP_AR_RELAY_OUTPUT                ((UINT32_S)0x00000080u)    /*AR�̵����������*/


/********************************************end of �������������******************************************/



/*******************************************���뿪��������  START*******************************************/




/*ATP��ȫ����:8��*/
#define ATP_KEY_OPEN_INPUT              ((UINT32_S)0x00001000u)   /*˾��Կ������,����ʻ�Ҽ���*/
#define ATP_TRAIN_INTEG_INPUT           ((UINT32_S)0x00002000u)   /*�г�����*/
#define ATP_DOOR_CLOSED_INPUT           ((UINT32_S)0x00004000u)   /*���Źر�������*/
#define ATP_QYQD_VALID_INPUT            ((UINT32_S)0x00008000u)   /*ǣ�����ж�*/
#define ATP_EB_VALID_INPUT              ((UINT32_S)0x00010000u)   /*�г���ʵʩ�����ƶ�*/
#define ATP_BCZD_VALID_INPUT            ((UINT32_S)0x00020000u)   /*��ʵʩ�����ƶ�*/
#define ATP_SB_RIGHT_INPUT              ((UINT32_S)0x00040000u)   /*ǣ���ƶ��ֱ�����λ�ҷ����ֱ�����ǰλ*/
#define ATP_ASSURE_INPUT                ((UINT32_S)0x00080000u)   /*ȷ�ϰ�ť����*/

/*ATP�ǰ�ȫ����:10��*/
#define ATP_EUM_SWITCH_INPUT            ((UINT32_S)0x00000100u)   /*EUM���ؼ���*/
#define ATP_ATO_START_INPUT             ((UINT32_S)0x00000001u)   /*ATO����1��ť�Ѱ���*/
#define ATP_ATO_START2_INPUT            ((UINT32_S)0x01000000u)   /*ATO����2��ť�Ѱ���*/
#define ATP_MODE_UP_INPUT               ((UINT32_S)0x00000002u)   /*ģʽ��ѡ��*/
#define ATP_MODE_DOWN_INPUT             ((UINT32_S)0x00000004u)   /*ģʽ��ѡ��*/
#define ATP_AR_INPUT                    ((UINT32_S)0x00000008u)   /*AR��ť����*/
#define ATP_RIGHT_DOOR_OPEN_INPUT       ((UINT32_S)0x00000040u)   /*���ſ��Ű�ť����*/
#define ATP_RIGHT_DOOR_CLOSE_INPUT      ((UINT32_S)0x00000080u)   /*���Ź��Ű�ť����*/
#define ATP_LEFT_DOOR_OPEN_INPUT        ((UINT32_S)0x00000200u)   /*���ſ��Ű�ť����*/
#define ATP_LEFT_DOOR_CLOSE_INPUT       ((UINT32_S)0x00000400u)   /*���Ź��Ű�ť����*/





/********************************************���뿪�������� end*****************************************/


#endif
