/*******************************************
文件名	：TsrTransmitStateDataManage.h
作者	：董欣
创建时间：2016-10
描述	：通信状态数据管理头文件
备注	：无
*******************************************/
#ifndef TSR_TRANSMIT_STATE_DATA_MANAGE_H_
#define TSR_TRANSMIT_STATE_DATA_MANAGE_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************
函数名	：GetResReplyToAtsFlag
功能描述：获取 向ATS发送应答信息标志
输入	：无
输出	：无
返回值	：0: 获取数据失败
		  0xaau:收到ATS命令标志 0x55u:未收到ATS命令标志
*******************************************/
extern UINT8_S GetResReplyToAtsFlag();

/*******************************************
函数名	：SetResReplyToAtsFlag
功能描述：设置 向ATS发送应答信息标志
输入	：UINT8_S resReplyToAtsFlag, 应答信息标志
输出	：无
返回值	：无
*******************************************/
extern void SetResReplyToAtsFlag(UINT8_S resReplyToAtsFlag);

#ifdef __cplusplus
}
#endif 

#endif