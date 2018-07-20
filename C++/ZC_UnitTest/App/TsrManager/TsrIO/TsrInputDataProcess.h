/*******************************************
文件名	：TsrInputDataProcess.h
作者	：董欣
创建时间：2016-10
描述	：输入处理程序
备注	：无
*******************************************/

#ifndef TSR_INPUT_DATA_PROCESS_H_
#define TSR_INPUT_DATA_PROCESS_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
函数名	：ProcessRcvFromAtsData
功能描述：处理ATS发来数据
输入	：无
输出	：无
返回值	：0:处理失败,1:处理成功
*******************************************/
extern UINT8_S ProcessRcvFromAtsData(void);

#ifdef __cplusplus
}
#endif

#endif