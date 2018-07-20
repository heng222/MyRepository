/*******************************************
文件名	：TsrInterface.h
作者：董欣
创建时间：2016-10
描述：TSR接口
备注：无
*******************************************/

#ifndef TSR_INTERFACE_H_
#define TSR_INTERFACE_H_

#include "../../Common/CommonTypes.h"
#include "TsrSystem/TsrSystemDefine.h"
#include "TsrParserPacker/TsrParsePackInterface.h"
#include "TsrIO/TsrInputDataProcess.h"
#include "TsrIO/TsrOutputDataProcess.h"
#include "TsrInitialization/InitialProcess.h"
#include "TsrSystem/TsrSysStatusData.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************
函数名	：TsrInit
功能描述：Tsr初始化函数
输入	：无
输出	：无
返回值	：0:初始化失败；1：初始化成功。
*******************************************/
extern UINT8_S TsrInit(void);

/*******************************************
函数名	: TsrIFGetZcWorkState
功能描述：获取工作状态
输入	：无
输出	：无
返回值	：ZC工作状态
*******************************************/
extern UINT8_S TsrIFGetZcWorkState(void);

/*******************************************
函数名	: TsrIFSetZcWorkState
功能描述：设置工作状态
输入	：无
输出	：无
返回值	：无
*******************************************/
extern void TsrIFSetZcWorkState(UINT8_S workState);

/*******************************************
函数名	：ParseTsrCommandsFromAts
功能描述：解析ATS的输入数据
输入	：无
输出	：无
返回值	：retVal成功解析的数据包的数量
*******************************************/
extern UINT8_S ParseTsrCommandsFromAts(void);

/*******************************************
函数名	：ProcessTsrCommandsFromAts
功能描述：处理 ATS发来数据
输入	：无
输出	：无
返回值	：0:处理失败,1:处理成功
*******************************************/
extern UINT8_S ProcessTsrCommandsFromAts(void);

/*******************************************
函数名	：ProcessTsrCommandsToAts
功能描述：处理 回复到Ats数据
输入	：无
输出	：无
返回值	：0：失败；1：成功
*******************************************/
extern UINT8_S ProcessTsrCommandsToAts(void);

/*******************************************
函数名	：PackTsrCommandsToAts
功能描述：打包ATS输出数据
输入	：无
输出	：无
返回值	：无
*******************************************/

extern void PackTsrCommandsToAts(void);

#ifdef __cplusplus
}
#endif

#endif