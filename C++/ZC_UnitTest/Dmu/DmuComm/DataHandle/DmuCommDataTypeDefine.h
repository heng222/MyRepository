/********************************************************
* 
* �� �� ���� DmuCommDataTypeDefine.h 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ������ѯ����ͷ�ļ� 
* ��    ע�� �� 
* 
********************************************************/ 

#ifndef DMU_COMM_DATATYPE_DEFINE_H_
#define DMU_COMM_DATATYPE_DEFINE_H_

#include "../../../Common/CommonTypes.h"

/*�����SEG�߼����� */
#define LINESEG_SAME_DIR                                0x55u                            /*��SEG�߼�������ͬ*/
#define LINESEG_CONVER_DIR                                0xAAu                            /*��SEG�߼������෴*/

#define SEG_LOGIC_DIR_DOWN                                0x55u                            /*����(link�߼�����Ϊ��·���з���)*/
#define SEG_LOGIC_DIR_UP                                0xAAu                            /*����(link�߼�����Ϊ��·���з���)*/

#define INCLINE_SAME_DIR                                0x55u                            /*�¶���SEG�߼�����������б��������*/
#define INCLINE_CONVER_DIR                                0xAAu                            /*�¶���SEG�߼�����������б��������*/

#define SWITCH_STATUS_SAME                                1u                                /*����λ*/
#define SWITCH_STATUS_CONTRA                            2u                                /*����λ*/
#define SWITCH_STATUS_LOSE                                3u                                /*�����Ŀ�*/

#define SIGNPRO_DIR_SAME                                0x55u                            /*�źŻ���������Ϊ����*/
#define SIGNPRO_DIR_CONTRA                                0xAAu                            /*�źŻ���������Ϊ����*/

#define OPENSIGNAL_PASS_CLOSE                            0x55u                            /*�ǿ����źŻ���־*/
#define OPENSIGNAL_PASS_OPEN                            0xAAu                            /*�����źŻ���־*/

#define PSD_STATUS_OPEN                                    0x55u                            /*������״̬Ϊ����*/
#define PSD_STATUS_CLOSE                                0xAAu                            /*������״̬Ϊ�ر�*/
#define ESP_STATUS_ACTIVITE                                0x55u                            /*վ̨����ͣ����ť����*/
#define ESP_STATUS_UNACTIVITE                            0xAAu                            /*վ̨����ͣ����ť�ͷ�*/

#define DEFAULT_ZERO                                       0u                            /*������ʼֵΪ0*/
#define DEFAULT_1_VALUE                                    1u                            /*������ʼֵΪ1*/
#define DEFAULT_2_VALUE                                    2u                            /*������ʼֵΪ2*/
#define UINT8_NULL                                        0xFFu                            /*һ���ֽڵ���Чֵ*/
#define UINT16_NULL                                   0xFFFFu                            /*�����ֽڵ���Чֵ*/
#define UINT32_NULL                               0xFFFFFFFFu                            /*�ĸ��ֽڵ���Чֵ*/

/*�����Ͷ���*/
#define POINTTYPE_SWITCH                                0x03u                            /*����*/
#define POINTTYPE_AXLE                                    0x02u                            /*����*/
#define START_POINT                                        0x01u                            /*���*/
#define END_POINT                                        0x02u                            /*�յ�*/

/*�ϰ������ͺ궨��*/
#define    LINEOBS_SIGNAL                                    0x01u                            /*�źŻ�*/
#define    LINEOBS_PSD                                        0x02u                            /*������*/
#define    LINEOBS_ESB                                        0x03u                            /*վ̨����ͣ����ť*/
#define    LINEOBS_SWITCH                                    0x04u                            /*����*/
#define    LINEOBS_PLATFORM                                0x05u                            /*վ̨����*/
#define    LINEOBS_ZCDVIDE                                    0x07u                            /*ZC�߽��*/
#define    LINEOBS_RES                                        0x08u                            /*��������*/
#define LINEOBS_TRAIN_TAIL                                0x09u                            /*ǰ���г���β*/
#define LINEOBS_TRAIN_HEAD                                0x0au                            /*ǰ���г���ͷ*/
#define LINEOBS_AXLESEC                                    0x0bu                            /*��������*/    
#define LINEOBS_UT                                        0x0cu                            /*�������Σ���ͨ�ų�ռ�õ�ʹ�ü�������ʼ�˵������*/    
#define LINEOBS_OVERLAP                                    0x0du                            /*Overlap*/    
#define LINEOBS_ARBUTTON                                0x0eu                            /*�����۷���ť*/    
#define LINEOBS_ARLIGHT                                    0x0fu                            /*�����۷���*/    
#define LINEOBS_ROUTE                                    0x10u                            /*��·*/    
#define LINEOBS_LS                                        0x11u                            /*�߼�����*/

/*ͣ���������Զ���*/
#define RUN_STATION_AREA                                0x01u                            /*վ̨����*/
#define    RUN_REVERT_AREA                                    0x02u                            /*�۷�����*/
#define    RUN_TRANSFORM_AREA                                0x04u                            /*ת��������*/

/*ͣ�������ſ��Ų�����ʽ*/
#define RUN_DOOR_NO_OPEN                                0u                                /*���Ҿ�����*/
#define RUN_DOOR_LEFT_OPEN                                1u                                /*���ŷ�������*/
#define RUN_DOOR_RIGHT_OPEN                                2u                                /*���ŷ�������*/
#define RUN_DOOR_LEFT_RIGHT_OPEN                        3u                                /*���ŷ��������ź�����*/
#define RUN_DOOR_RIGHT_LEFT_OPEN                        4u                                /*���ŷ������Һ�������*/
#define RUN_DOOR_BOTH_OPEN                                5u                                /*����ͬʱ��������*/

/*ͣ�������Ź��Ų�����ʽ*/
#define RUN_DOOR_NO_CLOSE                                0u                                /*���Ҿ�����*/
#define RUN_DOOR_LEFT_CLOSE                                1u                                /*���ŷ�������*/
#define RUN_DOOR_RIGHT_CLOSE                            2u                                /*���ŷ�������*/
#define RUN_DOOR_LEFT_RIGHT_CLOSE                        3u                                /*���ŷ��������ź�����*/
#define RUN_DOOR_RIGHT_LEFT_CLOSE                        4u                                /*���ŷ������Һ�������*/
#define RUN_DOOR_BOTH_CLOSE                                5u                                /*����ͬʱ��������*/

/*ͣ�������Զ���*/
#define RUN_OPERAT_STOP_POINT                            0x01u                            /*վ̨��Ӫͣ����*/
#define RUN_EXITROUTE_STOP_POINT                        0x02u                            /*�˳�ͣ���㣨CBTC��������CBTC����)*/
#define RUN_REVERT_STOP_POINT                            0x04u                            /*�۷�ͣ����*/ 
#define RUN_SIGNAL_STOP_POINT                            0x08u                            /*վ���źŻ�ͣ����(���۷�)*/  /*ͨ��ͣ����*/
#define RUN_REVERTEND_STOP_POINT                        0x10u                            /*�۷���ͣ����*/
#define RUN_SWITCH_STOP_POINT                            0x20u                            /*ת����(Сվ̨)ͣ���㣨��CBTC������CBTC����*/

/*��·����*/
#define  LINE_TRAIN_ROUTE                                0x01u                            /*�г���·*/
#define  LINE_REVERSE_ROUTE                                0x02u                            /*�۷���·*/
#define  LINE_IN_SGMT_ROUTE                                0x04u                            /*�ضν�·*/
#define  LINE_OUT_SGMT_ROUTE                            0x08u                            /*���ν�·*/
#define  LINE_IN_DEPOT_ROUTE                            0x10u                             /*�ؿ��·*/
#define  LINE_OUT_DEPOT_ROUTE                            0x20u                            /*�����·*/
#define  LINE_EXIT_CBTC_ROUTE                            0x40u                            /*CBTC�����˳���·*/
#define  LINE_EXIT_BLOC_ROUTE                            0x80u                            /*��ʽ�����˳���·*/

/*�˳�CBTC��������*/
#define LINE_ITC_EXIT_SEC                                0x01u                            /*��ʽ�˳�����*/
#define LINE_CBTC_EXIT_SEC                                0x02u                            /*CBTC�˳�����*/
#define LINE_IN_SGMT_SEC                                0x04u                            /*�ض���������*/
#define LINE_IN_DEPOT_SEC                                0x08u                            /*�ؿ���������*/

/*Ӧ��������*/
#define BALI_WHEELCALI                                     0x0001u                            /*У��Ӧ����*/
#define BALI_FIXED                                        0x0002u                            /*�̶�Ӧ����*/
#define BALI_VARIABLE_DATA                                0x0004u                            /*�ɱ�����Ӧ����*/
#define BALI_INFILLED                                     0x0008u                            /*���Ӧ����*/
#define BALI_ATO                                        0x0020u                            /*ATOӦ����*/
#define BALI_LOCCALI                                     0x0040u                            /*λ��У��Ӧ����*/
#define BALI_NORMAL                                        0x0080u                            /*��ͨӦ����*/
#define BALI_LOOP                                        0x0010u                            /*����*/

/*��·������Ϣ����*/
#define SEG_INCLUDE_LIMITSPEED_MAX_NUM                  5u                               /*һ��SEG��������ʱ���ٵĸ���*/
#define MAX_ACOFSWITCH_NUM                                12u                                /*���������������ε�����*/
#define BOTHSEG_INCLUDE_MAX_SEG                            100u                                /*����SEGID֮�������SEGID����*/
#define TWO_POINT_AC_NUM_MAX                            20u                                /*����SEGID֮������ļ������θ���*/
#define TWO_POINT_SWITCH_NUM_MAX                        30u                                /*����SEGID֮������ĵ������*/
#define TWO_POINT_LOGICSEC_NUM_MAX                        50u                                /*����֮������߼����ε�������*/
#define TWO_POINT_STATION_NUM_MAX                        30u                                /*����SEGID֮�������վ̨����*/
#define TWO_POINT_PSD_NUM_MAX                            10u                                /*����SEGID֮������������Ÿ���*/
#define TWO_POINT_ESB_NUM_MAX                            10u                                /*����SEGID֮������Ľ���ͣ����ť����*/
#define AXLESEC_ADJACENT_MAX_NUM                        3u                                /*�����������ڼ������ε��������*/
#define SNGZC_INCLUDE_SWITCH_NUM                        400u                                /*����ZC�ڰ����ĵ�������*/
#define ONEPOINT_SAMEDIR_INCLUDE_SEG                    2u                                /*һ��������ͬһ���������SEG���ֵ*/
#define BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG            20u                                /*����״̬δ֪ʱ,����SEGID֮�������SEGID����*/
#define ROUTE_INCLUDE_PLATFORM_MAX_NUM                    3u                                /*һ����·���������վ̨����*/
#define STACK_PUSH_SEG_MAX_NUM                            100u                                /*ѹ��ջ��SEG����*/


#define MA_OBST_MAX_NUM                                    30u                                /*MA������ϰ�������*/
#define MA_TLS_MAX_NUM                                    20u                                /*MA�е������ʱ��������*/
#define MA_SWITCH_MAX_NUM                                20u                                /*MA������������*/

/*�豸���Ͷ���*/
#define DEV_ZC_TYPE                                        0x1eu                            /*ZC�豸����*/
#define DEV_ATS_TYPE                                    0x03u                            /*ATS�豸����*/
#define DEV_CI_TYPE                                        0x3Cu                            /*CI�豸����*/


/*MA�յ�����*/
#define MA_CBTC_END_TYPE                                   0x01u                            /*MA�յ�����ΪCBTC�յ�*/
#define MA_REVERSE_END_TYPE                              0x02u                            /*MA�յ��۷���·*/
#define MA_OTHER_END_TYPE                               0x03u                            /*��·�ϵ������ϰ���(ATP���������������)*/

/*CI��������*/
#define CI_MAIN_LINE_TYPE                               0x01u                            /*������������*/                      
#define CI_TRAIN_DEPOT_TYPE                             0x02u                            /*������/ͣ������������*/

/*ZC��������*/
#define ZC_MAIN_LINE_TYPE                               0x01u                            /*�����������������*/
#define ZC_TRAIN_DEPOT_TYPE                             0x02u                            /*������/ͣ�����������������*/

#endif
