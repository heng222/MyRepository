/*******************************************
文件名	：TsrSysStatusData.c
作者	：董欣
创建时间：2016-10
描述    ：系统状态数据管理
备注    ：无
*******************************************/
#include "TsrSysStatusData.h"

UINT8_S g_ZcWorkState = DEFAULT_ZERO;

/*******************************************
函数名	: GetZcWorkState
功能描述：获取工作状态
输入	：无
输出	：无
返回值	：ZC工作状态
*******************************************/
UINT8_S GetZcWorkState(void)
{
	return g_ZcWorkState;
}

/*******************************************
函数名	: SetZcWorkState
功能描述：设置工作状态
输入	：无
输出	：无
返回值	：无
*******************************************/
void SetZcWorkState(UINT8_S workState)
{
	g_ZcWorkState = workState;
}