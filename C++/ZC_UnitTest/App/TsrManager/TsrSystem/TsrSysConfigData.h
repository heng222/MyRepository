/*******************************************
文件名	：TsrSysConfigData.h
作者	：董欣
创建时间：2016-10
描述	：系统配置数据管理
备注	：无
*******************************************/
#ifndef TSR_SYS_CONFIG_DATA_H_
#define TSR_SYS_CONFIG_DATA_H_
#include "../../../Common/CommonTypes.h"
#include "TsrSystemDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*TSR功能参数配置*/
typedef struct S_TSR_PARAMETERS_CONFIG
{
	UINT16_S PeriodsBetweenFsAndSs;                     /*ATS设置临时限速首次与二次的时间间隔*/
	UINT32_S PeriodsOnKeepingAliveWithAts;              /*ZC与ATS通信故障周期数*/
	UINT16_S PeriodsDuringAutoReplyTsrToAts;            /*正常向ATS汇报TSR的周期数*/
	UINT8_S  TsrMaxSpeedAccordingly;                     /*允许的临时限速最大速度*/
}Tsr_Param_Config_Stru;

/*******************************************
函数名  : GetTsrMaxSpeed
功能描述：获取 允许的临时限速最大速度
输入    ：无
输出    ：无
返回值	：临时限速最大速度
*******************************************/
extern UINT8_S GetTsrMaxSpeed(void);

/*******************************************
函数名  : GetPeriodsDuringAutoReplyTsrToAts
功能描述：获取 正常向ATS汇报TSR的周期数
输入    ：无
输出    ：无
返回值	：向ATS发送的周期
*******************************************/
extern UINT16_S GetPeriodsDuringAutoReplyTsrToAts(void);

/*******************************************
函数名  : GetPeriodsBetweenFsAndSs
功能描述：获取 ATS设置临时限速首次与二次的时间间隔
输入    ：无
输出    ：无
返回值	：临时限速首次二次间隔时间
*******************************************/
extern UINT16_S GetPeriodsBetweenFsAndSs(void);

/*******************************************
函数名  : GetPeriodsOnKeepingAliveWithAts
功能描述：获取 ZC与ATS通信故障周期数
输入    ：无
输出    ：无
返回值	：ZC与ATS通信故障周期数
*******************************************/
extern UINT32_S GetPeriodsOnKeepingAliveWithAts(void);

/*******************************************
函数名  : GetTsrParamConfig
功能描述：获取 TSR功能参数配置变量
输入    ：无
输出    ：无
返回值	：g_tsrParamConfig  TSR功能参数配置
*******************************************/
extern Tsr_Param_Config_Stru* GetTsrParamConfig(void);

#ifdef __cplusplus
}
#endif
#endif
