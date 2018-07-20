/*******************************************
文件名	：TsrOutputDataProcess.h
作者	：董欣
创建时间：2016-10
描述	：输出处理程序
备注	：无
*******************************************/

#ifndef TSR_OUTPUT_DATA_PROCESS_H_
#define TSR_OUTPUT_DATA_PROCESS_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
函数名	：ProcessReplyToAtsData
功能描述：处理 回复到Ats数据
输入	：无
输出	：无
返回值	：0：失败；1：成功
*******************************************/
extern UINT8_S ProcessReplyToAtsData(void);

/*******************************************
函数名	：GetAutoReplyToAtsFlag
功能描述：获取主动向ATS汇报标志
输入	：无
输出	：无
返回值	：0本周期不汇报，1本周期汇报
*******************************************/
extern UINT8_S GetAutoReplyToAtsFlag(void);

/*******************************************
函数名	：SetAutoReplyToAtsFlag
功能描述：设置主动向ATS汇报标志
输入	：UINT8_S replayTime,0本周期不汇报，1本周期汇报
输出	：无
返回值	：无
*******************************************/
extern void SetAutoReplyToAtsFlag(UINT8_S replayTime);

#ifdef __cplusplus
}
#endif

#endif
