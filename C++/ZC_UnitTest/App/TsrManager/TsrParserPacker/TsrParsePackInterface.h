/*******************************************
文件名	：TsrParsePackInterface.h
作者	：董欣
创建时间：2016-10
描述	：解析组包
备注	：无
*******************************************/
#ifndef TSR_PARSEPACK_INTERFACE_H
#define TSR_PARSEPACK_INTERFACE_H

#include "../../../Common/CommonTypes.h"
#include "../TsrSystem/TsrSystemDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ATS_FRAME_OFFSET 0
#define ZC_FRAME_OFFSET 0
#define NTP_FRAME_OFFSET 0
/*******************************************
函数名	：Tsr_ParseIncomingDatas
功能描述：解析外部通信设备的输入数据
输入	：无
输出	：无
返回值	：retVal成功解析的数据包的数量
*******************************************/
extern UINT8_S Tsr_ParseIncomingDatas(void);

/*******************************************
函数名	：Tsr_PackOutletDatas
功能描述：打包ATS输出数据
输入	：无
输出	：无
返回值	：无
*******************************************/

extern void Tsr_PackOutletDatas(void);

#ifdef __cplusplus
}
#endif


#endif

