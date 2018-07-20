/********************************************************                                                                                                            
 文 件 名： MaintainManager.h
 作    者： ZC组
 创建时间： 2015-04-18
 描述： 维护日志管理
 备注： 无  
********************************************************/

#ifndef MAINTAIN_MANAGER_H_
#define MAINTAIN_MANAGER_H_

#include "../../Common/CommonTypes.h"

/* 如果是Vxworks版，调用平台适配层的日志记录函数 */
#ifdef SYS_TYPE_VXWORKS
#include "../../cspadpt/Vcp_Device_Definition_Inf.h"
#include "../../cspadpt/Vcp_Service_Interface.h"
#include "../../cspadpt/Vcp_Service_TestInterface.h"
#include "../../PlatformAdapter/PlatformLog/AdapterLog.h"

#define LogPrintf   AdptAppLogPrintf      /* 适配层日志打印 */
#define LogPrintBuff AdptAppLogPrintBuff  /* 适配层日志打印数组*/
#endif

#define LOG_TYPE   1                    /* 记录log为1，不记录log为0 */
#define MAINTAIN_DATA_LEN_MAX 25000u    /* 日志数组的长度 */
#define UDP_OUT_FRAME_LEN_1 25000u      /* UDP数组的长度 */


#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
  函数名:      SetLogPrintfType
  功能描述:    设置打印log信息类型
  输入:        const UINT8_S logPrintfType 记录日志标识
  输出:        无
  返回值:      无
*************************************************/
void SetLogPrintfType(const UINT8_S logPrintfType);

/*************************************************
  函数名:      LogPrintf
  功能描述:    打印log信息
  输入:        UINT8_S chRunSystem, 标识
               const char * lpszFormat 指针
  输出:        无
  返回值:      0u 失败
               1u 成功
*************************************************/
#ifdef SYS_TYPE_WINDOWS
UINT8_S LogPrintf(UINT8_S chRunSystem, const char * lpszFormat, ...);
#endif

/*************************************************
  函数名:      LogPrintf_Windows
  功能描述:    打印Windows下log信息
  输入:        const char * szFileName, 文件名
               const char * lpszFormat, 指针
               const UINT32_S dwLength, 长度
  输出:        无
  返回值:      -1:  失败
               !=-1: 成功
*************************************************/
#ifdef SYS_TYPE_WINDOWS
INT32_S LogPrintf_Windows(const char * szFileName, const char * lpszFormat,const UINT32_S dwLength);
#endif

/*************************************************
  函数名:      LogPrintBuff
  功能描述:    将缓冲区数据转化为字符串
  输入:        const UINT8_S dataBuf[]， 数组首地址
               const UINT16_S bufLength,数组长度
               const UINT16_S dataLength 数据长度
  输出:        无
  返回值:      0U,失败
               1U,成功
*************************************************/
#ifdef SYS_TYPE_WINDOWS
UINT8_S LogPrintBuff(const UINT8_S dataBuf[],const UINT16_S bufLength,const UINT16_S dataLength);
#endif

/*************************************************
  函数名:      LogBufPeriodClear
  功能描述:    将缓冲区清空
  输入:        无
  输出:        无
  返回值:      0无
*************************************************/
void LogBufPeriodClear(void);

/*************************************************
  函数名:      GetgMaintainDataArr
  功能描述:    获取日志字节数组的首地址
  输入:        无
  输出:        无
  返回值:      数组首地址
*************************************************/
UINT8_S *GetgMaintainDataArr(void);

/*************************************************
  函数名:      GetgMaintainLen
  功能描述:    获取日志数组中字节的数量
  输入:        无
  输出:        无
  返回值:      字节长度
*************************************************/
UINT32_S *GetgMaintainLen(void);


#ifdef __cplusplus
}
#endif

#endif
