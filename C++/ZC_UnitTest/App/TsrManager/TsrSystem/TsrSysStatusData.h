/*******************************************
文件名	：TsrSysStatusData.h
作者	：董欣
创建时间：2016-10
描述	：系统状态数据管理
备注	：无
*******************************************/

#ifndef TSR_SYS_STATUS_DATA_H_
#define TSR_SYS_STATUS_DATA_H_
#include "../../../Common/CommonTypes.h"
#include "TsrSystemDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
函数名	: GetZcWorkState
功能描述：获取工作状态
输入	：无
输出	：无
返回值	：ZC工作状态
*******************************************/
extern UINT8_S GetZcWorkState(void);

/*******************************************
函数名	: SetZcWorkState
功能描述：设置工作状态
输入	：无
输出	：无
返回值	：无
*******************************************/
extern void SetZcWorkState(UINT8_S workState);

#ifdef __cplusplus
}
#endif
#endif