/*******************************************
�ļ���	��TsrSysConfigData.h
����	������
����ʱ�䣺2016-10
����	��ϵͳ�������ݹ���
��ע	����
*******************************************/
#ifndef TSR_SYS_CONFIG_DATA_H_
#define TSR_SYS_CONFIG_DATA_H_
#include "../../../Common/CommonTypes.h"
#include "TsrSystemDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*TSR���ܲ�������*/
typedef struct S_TSR_PARAMETERS_CONFIG
{
	UINT16_S PeriodsBetweenFsAndSs;                     /*ATS������ʱ�����״�����ε�ʱ����*/
	UINT32_S PeriodsOnKeepingAliveWithAts;              /*ZC��ATSͨ�Ź���������*/
	UINT16_S PeriodsDuringAutoReplyTsrToAts;            /*������ATS�㱨TSR��������*/
	UINT8_S  TsrMaxSpeedAccordingly;                     /*�������ʱ��������ٶ�*/
}Tsr_Param_Config_Stru;

/*******************************************
������  : GetTsrMaxSpeed
������������ȡ �������ʱ��������ٶ�
����    ����
���    ����
����ֵ	����ʱ��������ٶ�
*******************************************/
extern UINT8_S GetTsrMaxSpeed(void);

/*******************************************
������  : GetPeriodsDuringAutoReplyTsrToAts
������������ȡ ������ATS�㱨TSR��������
����    ����
���    ����
����ֵ	����ATS���͵�����
*******************************************/
extern UINT16_S GetPeriodsDuringAutoReplyTsrToAts(void);

/*******************************************
������  : GetPeriodsBetweenFsAndSs
������������ȡ ATS������ʱ�����״�����ε�ʱ����
����    ����
���    ����
����ֵ	����ʱ�����״ζ��μ��ʱ��
*******************************************/
extern UINT16_S GetPeriodsBetweenFsAndSs(void);

/*******************************************
������  : GetPeriodsOnKeepingAliveWithAts
������������ȡ ZC��ATSͨ�Ź���������
����    ����
���    ����
����ֵ	��ZC��ATSͨ�Ź���������
*******************************************/
extern UINT32_S GetPeriodsOnKeepingAliveWithAts(void);

/*******************************************
������  : GetTsrParamConfig
������������ȡ TSR���ܲ������ñ���
����    ����
���    ����
����ֵ	��g_tsrParamConfig  TSR���ܲ�������
*******************************************/
extern Tsr_Param_Config_Stru* GetTsrParamConfig(void);

#ifdef __cplusplus
}
#endif
#endif
