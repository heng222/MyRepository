/*******************************************
文件名	：InitialProcess.h
作者：董欣
创建时间：2016-10
描述：数据初始化
备注：无
*******************************************/

#ifndef INITIAL_PROCESS_H_
#define INITIAL_PROCESS_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C"{
#endif

#define IN_CFG_LEN 1024u/*配置数据长度*/

/*******************************************
函数名	：InitialProcess
功能描述：初始化函数
输入	：无
输出	：无
返回值	：0:初始化失败；1：初始化成功。
*******************************************/
extern UINT8_S InitialProcess(void);

#ifdef __cplusplus
}
#endif
#endif