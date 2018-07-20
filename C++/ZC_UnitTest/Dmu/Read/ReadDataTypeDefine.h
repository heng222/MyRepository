
/*************************************************
  �ļ���   ��ReadDataTypeDefine.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� �ļ�ϵͳ�ļ�����������Ͷ���
  ��ע    ���ޡ� 
*************************************************/


#ifndef    READ_DATA_TYPE_DEFINE_H
#define    READ_DATA_TYPE_DEFINE_H

#define BNF_TABLE_NUM              0xC0u                          /*�����*/
#define BNP_TABLE_SHEET_MAX_NUM    24u                            /*�������SHEET�ĸ���*/

/*��·���� �궨��*/
#define LINE_DATA_TYPE                             0x10u         /*��·����ID*/
#define LINE_POINT_ID                             1u            /*���*/
#define LINE_SEG_ID                              2u            /*Seg��ID*/
#define LINE_AXLE_SGMT_ID                        3u            /*�������α�ID*/
#define LINE_PHYSICAL_SGMT_ID                    4u            /*�������α�ID*/
#define LINE_LGC_SGMT_ID                         5u            /*�߼����α�*/
#define LINE_AXLE_ID                             6u            /*��������ID*/
#define LINE_SWITCH_ID                           7u            /*�����ID*/
#define LINE_SIGNAL_ID                           8u            /*�źŻ���ID*/
#define LINE_SHIELD_DOOR_ID                      9u            /*�����ű�ID*/
#define LINE_EMERG_STOP_BUTTON_ID               10u           /*����ͣ����ť��ID*/
#define LINE_TRAIN_STATION_ID                    11u              /*��վID*/
#define LINE_PLATFORM_ID                        12u           /*վ̨��ID*/
#define LINE_BALISE_ID                          13u           /*Ӧ������ID*/
#define LINE_GRADE_ID                           14u           /*�¶ȱ�ID*/
#define LINE_STATIC_RES_SPEED_ID                15u           /*��̬���ٱ�ID*/
#define LINE_ROUTE_ID                           16u           /*��·��ID*/
#define LINE_PROTECT_ZONE_ID                    17u           /*�������α�ID*/
#define LINE_BLOC_APPTCH_SECTION_ID             18u           /*��ʽ�ӽ����α�ID*/
#define LINE_CBTC_APPTCH_SECTION_ID             19u           /*CBTC�ӽ����α�ID*/
#define LINE_BLOC_TRG_ZONE_ID                   20u           /*��ʽ�������α�ID*/
#define LINE_CBTC_TRG_ZONE_ID                   21u           /*CBTC�������α�ID*/
#define LINE_SECTION_TYPE_ID                    22u              /*�������Ա�*/
#define LINE_CONRESSPEED_ID                        23u              /*ͳһ���ٲ�ѯ*/
#define LINE_CONGRADE_ID                        24u              /*ͳһ�¶Ȳ�ѯ*/


/*��Ӫ����*/
#define RUN_DATA_TYPE                            0x20u       /*��Ӫ���� ����*/
#define RUN_STOPSECTION_ID                        1u            /*ͣ�������ID*/
#define RUN_STOPPOINT_ID                        2u            /*ͣ�����ID*/
#define RUN_DEFAULT_ROUTE_ID                    3u            /*Ĭ���������б�ID*/
#define RUN_STA_RUN_LEVEL_ID                    4u            /*վ����Ӫ�����ID*/
#define RUN_AR_ID                                5u            /*�����۷���ID*/
#define RUN_EXIT_CBTC_SECTION_ID                6u            /*�˳�CBTC�����ID*/
#define RUN_TRAIN_CONTROL_LEVEL_ID                7u            /*��CBTC�����ID*/

/*ϵͳ����  �궨��*/
#define  SYSTEM_CONFIGDATA_TYPE                    0x30u        /*ϵͳ����*/
#define  SYSTEM_CONFIGDATA_ID                    1u            /*ϵͳ�������ñ�*/
#define  SYSTEM_TEMPLIMITSPEED_CONFIG_ID        2u            /*��ʱ�������ñ�*/
#define  SYSTEM_TRAINTYPE_CONFIG_ID                3u            /*�г�������������ID*/
#define  SYSTEM_TRAININFO_ID                    4u            /*�������ܲ���ID*/
#define  SYSTEM_RAILINFO_ID                        5u            /*��·����*/
#define  SYSTEM_ACCTABLE_ID                        6u            /*���ǣ�����ٶȷֶ�ȡֵ��*/
#define  SYSTEM_COMMFAILTIME_ID                 7u            /*ͨ�Ź���ʱ���*/
#define  SYSTEM_DEV_COMM_ID                        8u            /*�豸ͨ�Ź�ϵ��*/

/*�ֽ���*/
#define  DIVIDPOINT_TYPE                        0x40u        /*�ֽ�������*/
#define  DIVIDPOINT_LINRSWITCH_INFO_ID            1u            /*�л���·��ϢID*/

/*ZC���ݱ� �궨��*/
#define  ZC_DATA_TYPE                            0x60u
#define  ZC_SIGN_INFO_ID                        1u            /*�źŻ���ϢID*/

/*ZC��������*/
#define  ZC_CONFIG_TYPE                            0x61u        /*ZC������������*/
#define  ZC_CONFIG_DATA_ID                        1u            /*ZC��������ID*/
#define  ZC_TIME_CONFIG_DATA_ID                    2u            /*ZCУʱ���ñ�ID*/
#define  ZC_COMM_CONFIG_DATA_ID                    3u            /*ZCͨ�����ñ�ID*/
#define  ZC_SYSTEM_CONFIG_DATA_ID                4u            /*ZCϵͳ���ñ�ID*/

/*ZC_NZC�ӿ���λ����*/
#define ZC_NZC_INTERCODE_TYPE                   0xB4u           /*ZC_NZC�ӿ���λ��������*/    
#define ZC_NZC_SWITCHCODE_TYPE                   1u              /*ZC_NZC������λ*/    
#define ZC_NZC_SIGNCODE_TYPE                       2u              /*ZC_NZC�źŻ���λ*/    
#define ZC_NZC_PSDCODE_TYPE                       3u              /*ZC_NZC��������λ*/    
#define ZC_NZC_ESBCODE_TYPE                       4u              /*ZC_NZC����ͣ����ť��λ*/    
#define ZC_NZC_AXLESECCODE_TYPE                   5u              /*ZC_NZC����������λ*/    
#define ZC_NZC_ROUTECODE_TYPE                   6u              /*ZC_NZC��·��λ*/    
#define ZC_NZC_PROSECCODE_TYPE                   7u              /*ZC_NZC����������λ*/    
#define ZC_NZC_ARCODE_TYPE                       8u              /*ZC_NZC�����۷���λ*/    

/*CI_ZC�ӿ���λ����*/
#define ZC_CI_INTERCODE_TYPE                       0xB3u           /*CI_ZC�ӿ���λ��������*/    
#define ZC_CI_SWITCHCODE_TYPE                   1u              /*CI_ZC������λ*/    
#define ZC_CI_SIGNCODE_TYPE                       2u              /*CI_ZC�źŻ���λ*/    
#define ZC_CI_PSDCODE_TYPE                       3u              /*CI_ZC��������λ*/    
#define ZC_CI_ESBCODE_TYPE                       4u              /*CI_ZC����ͣ����ť��λ*/    
#define ZC_CI_AXLESECCODE_TYPE                   5u              /*CI_ZC����������λ*/
#define ZC_CI_LOGICSECTION_TYPE                    6u                /*CI_ZC�߼�������λ*/
#define ZC_CI_ROUTECODE_TYPE                       7u              /*CI_ZC��·��λ*/    
#define ZC_CI_PROSECCODE_TYPE                   8u              /*CI_ZC����������λ*/    
#define ZC_CI_ARCODE_TYPE                       9u              /*CI_ZC�����۷���λ*/    

/*DMS��������*/
#define  DMS_CONFIGDATA_TYPE                    0xC0u        /*DMS�������� ����*/
#define  DMS_CONFIGDATA_ID                        1u            /*DMS��������ID*/

/*ATO��������  �궨��*/
#define  ATO_CONFIGDATA_TYPE                    0x07u        /*ATO�������� ����*/
#define  ATO_CONFIGDATA_ID                        1u            /*ATO���ò�����ID*/
#define  ATO_DOOR_CONFIGDATA_ID                    2u            /*ATO����������ID*/
#define  ATO_TMS_CONFIGDATA_ID                    3u            /*ATOTMS���ò�����ID*/
#define  ATO_BRIDGE_CONFIGDATA_ID                4u            /*ATO��ʻ̨��������ID*/
/*ATO����  �궨��*/
#define  ATO_DATA_TYPE                            0x80u        /*ATO���� ����*/
#define  ATO_TRACTIONSAMPLE_ID                    1u            /*����ǣ������������߱�ID*/
#define  ATO_BREAKSAMPLE_ID                        2u            /*�����ƶ�����������߱�ID*/ 
#define  ATO_ESPECIALTRIPNUM_ID                    3u            /*���⳵�κŶ�ID*/
#define  ATO_SPEED_CONFIGDATA_ID                4u            /*ATO�ٶȲ�����ID*/
#define  ATO_DFTSQC_ID                            5u            /*Ĭ�����б�*/

/*ATP��������  �궨��*/
#define  ATP_CONFIGDATA_TYPE                    0x71u        /*ATP�������� ����*/
#define  ATP_TRAIN_CONFIGDATA_ID                1u            /*ATP�����������ñ�ID*/
#define  ATP_RM_CONFIGDATA_ID                    2u            /*ATPRM���ñ�ID*/
#define  ATP_SIGN_CONFIGDATA_ID                    3u            /*ATPATP�źŻ����ñ�ID*/
#define  ATP_BACKRUN_CONFIGDATA_ID                4u            /*ATP�������ñ�ID*/
#define  ATP_BALISE_CONFIGDATA_ID                5u            /*ATPӦ�������ñ�ID*/
#define  ATP_LOOP_CONFIGDATA_ID                    6u            /*ATP�������ñ�ID*/
#define  ATP_WHEEL_CONFIGDATA_ID                7u            /*ATP�־����ñ�ID*/
#define  ATP_SELFPOWER_CONFIGDATA_ID            8u            /*ATP�Թض����ñ�ID*/
#define  ATP_ZEROSPEED_CONFIGDATA_ID            9u            /*ATP�������ñ�ID*/
#define  ATP_EB_CONFIGDATA_ID                    10u            /*ATPEB���ñ�ID*/
#define  ATP_ATO_CONFIGDATA_ID                    11u            /*ATPATO���ñ�ID*/
#define  ATP_MEASPEED_CONFIGDATA_ID                12u            /*ATP�������ñ�ID*/
#define  ATP_MODE_CONFIGDATA_ID                    13u            /*ATP��ʻģʽ���ñ�ID*/
#define  ATP_NET_CONFIGDATA_ID                    14u            /*ATP�������ñ�ID*/
#define  ATP_NMS_CONFIGDATA_ID                    15u            /*ATPNMS���ñ�ID*/
#define  ATP_NTP_CONFIGDATA_ID                    16u            /*ATPNTP���ñ�ID*/
#define  ATP_DOOR_CONFIGDATA_ID                 17u         /* ATP�������ñ�ID */

/*ATP����  �궨��*/
#define  ATP_DATA_TYPE                            0x70u        /*ATP���� ����*/
#define  ATP_SINGOPEN_INFO_ID                    1u             /*ATP�źŻ���ID*/
#define  ATP_BTRSPD_ID                            2u             /*ATPӦ������*/
#define  ATP_VRBTRSPD_VERSION_ID                3u             /*�ɱ�Ӧ�����汾ID*/

/*����ID�궨�����*/

/*ϵͳ�������ļ��Ƚ��漰�İ汾������*/
#define INTERSYSVERCMP_IDX_ATPZC                1u           /*ATP-ZC��ıȽ����ݰ汾������*/
#define INTERSYSVERCMP_IDX_ATPATO               2u           /*ATP-ATO��ıȽ����ݰ汾������*/
#define INTERSYSVERCMP_IDX_ZCDMS                3u           /*ZC-DMS��ıȽ����ݰ汾������*/

#endif
