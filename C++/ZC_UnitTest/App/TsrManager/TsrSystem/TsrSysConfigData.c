/*******************************************
�ļ���	��TsrSysConfigData.c
����	������
����ʱ�䣺2016-10
����	��TSR�����������ݹ���
��ע	����
*******************************************/
#include "TsrSysConfigData.h"

static Tsr_Param_Config_Stru g_tsrParamConfigStru;

/*******************************************
������  : GetTsrMaxSpeed
������������ȡ �������ʱ��������ٶ�
����    ����
���    ����
����ֵ	����ʱ��������ٶ�
*******************************************/
UINT8_S GetTsrMaxSpeed(void)
{
	return g_tsrParamConfigStru.TsrMaxSpeedAccordingly;
}

/*******************************************
������  : GetPeriodsOnKeepingAliveWithAts
������������ȡ ZC��ATSͨ�Ź���������
����    ����
���    ����
����ֵ	����ATSͨ������
*******************************************/
UINT32_S GetPeriodsOnKeepingAliveWithAts(void)
{
	return (UINT8_S)g_tsrParamConfigStru.PeriodsOnKeepingAliveWithAts;
}

/*******************************************
������  : GetPeriodsDuringAutoReplyTsrToAts
������������ȡ ������ATS�㱨TSR��������
����    ����
���    ����
����ֵ	����ATS���͵�����
*******************************************/
UINT16_S GetPeriodsDuringAutoReplyTsrToAts(void)
{
	return g_tsrParamConfigStru.PeriodsDuringAutoReplyTsrToAts;
}

/*******************************************
������  : GetPeriodsBetweenFsAndSs
������������ȡ ATS������ʱ�����״�����ε�ʱ����
����    ����
���    ����
����ֵ	����ʱ�����״ζ��μ��ʱ��
*******************************************/
UINT16_S GetPeriodsBetweenFsAndSs(void)
{
	return (UINT16_S)g_tsrParamConfigStru.PeriodsBetweenFsAndSs;
}

/*******************************************
������  : GetTsrParamConfig
������������ȡ TSR���ܲ������ñ���
����    ����
���    ����
����ֵ	��g_tsrParamConfigStru  TSR���ܲ�������
*******************************************/
Tsr_Param_Config_Stru* GetTsrParamConfig(void)
{
	return &g_tsrParamConfigStru;
}