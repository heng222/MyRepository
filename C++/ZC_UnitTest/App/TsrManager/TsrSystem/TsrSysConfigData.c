/*******************************************
文件名	：TsrSysConfigData.c
作者	：董欣
创建时间：2016-10
描述	：TSR参数配置数据管理
备注	：无
*******************************************/
#include "TsrSysConfigData.h"

static Tsr_Param_Config_Stru g_tsrParamConfigStru;

/*******************************************
函数名  : GetTsrMaxSpeed
功能描述：获取 允许的临时限速最大速度
输入    ：无
输出    ：无
返回值	：临时限速最大速度
*******************************************/
UINT8_S GetTsrMaxSpeed(void)
{
	return g_tsrParamConfigStru.TsrMaxSpeedAccordingly;
}

/*******************************************
函数名  : GetPeriodsOnKeepingAliveWithAts
功能描述：获取 ZC与ATS通信故障周期数
输入    ：无
输出    ：无
返回值	：与ATS通信周期
*******************************************/
UINT32_S GetPeriodsOnKeepingAliveWithAts(void)
{
	return (UINT8_S)g_tsrParamConfigStru.PeriodsOnKeepingAliveWithAts;
}

/*******************************************
函数名  : GetPeriodsDuringAutoReplyTsrToAts
功能描述：获取 正常向ATS汇报TSR的周期数
输入    ：无
输出    ：无
返回值	：向ATS发送的周期
*******************************************/
UINT16_S GetPeriodsDuringAutoReplyTsrToAts(void)
{
	return g_tsrParamConfigStru.PeriodsDuringAutoReplyTsrToAts;
}

/*******************************************
函数名  : GetPeriodsBetweenFsAndSs
功能描述：获取 ATS设置临时限速首次与二次的时间间隔
输入    ：无
输出    ：无
返回值	：临时限速首次二次间隔时间
*******************************************/
UINT16_S GetPeriodsBetweenFsAndSs(void)
{
	return (UINT16_S)g_tsrParamConfigStru.PeriodsBetweenFsAndSs;
}

/*******************************************
函数名  : GetTsrParamConfig
功能描述：获取 TSR功能参数配置变量
输入    ：无
输出    ：无
返回值	：g_tsrParamConfigStru  TSR功能参数配置
*******************************************/
Tsr_Param_Config_Stru* GetTsrParamConfig(void)
{
	return &g_tsrParamConfigStru;
}