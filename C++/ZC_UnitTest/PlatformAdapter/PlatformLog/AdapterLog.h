/********************************************************
*                                                                                                            
* 文 件 名： AdapterLog.h   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 适配层提供给平台层的日志记录接口头文件 
* 备    注： 无 
*
********************************************************/ 

#ifndef ADAPTER_LOG_H_
#define ADAPTER_LOG_H_

#include "../../Common/CommonTypes.h"
#include "../../Common/CRC16.h"
#include "../AdptHandle/AdapterExtDevInOutManage.h"
#include "../PlatItf/AdptPlatServiceInterface.h"

#define MAX_LOG_LEN (DEV_TOTAL_FRAME_LEN*MAX_SND_PIPE_NUM)

#define LOG_RECORD_TYPE 0xFFu      /* log record 数据类型 */
#define LOG_RECORD_HEAD_LEN 30u    /* log record 头长度(包括尾部CRC16) */
#define LOG_RECORD_VER 1u          /* log record 版本号 */


#ifdef __cplusplus
extern "C" {
#endif



/*
* 功能描述： 打印log信息
* 参数说明： 无
* 返回值  ： -1:  失败
*            !=-1: 成功
*/
UINT8_S AdptAppLogPrintf(UINT8_S chRunSystem, const CHAR_S * lpszFormat, ...);

/*
* 功能描述： 将缓冲区数据转化为字符串
* 参数说明：UINT8 *dataBuf，输出字符串(输入输出) 
            const UINT16 dataLength,需要转化的长度
            const UINT16 useLen,可用空间
*函数返回值：0,转化错误  1，转化正常  2,空间不足
*/
UINT8_S AdptAppLogPrintBuff(const UINT8_S dataBuf[],const UINT16_S bufLength, const UINT16_S dataLength );

/*
* 功能描述： 周期清空日志缓冲区
* 参数说明： 无
* 返回值  ： void
*/
void AdptAppLogBufPeriodClear(void);


/*
* 功能描述： 打包发送维护信息，调试用 
* 参数说明： UINT8_S destDevType,const UINT8_S destDevId
* 返回值  ： void
*/
void AdptAppLogDataPack(const UINT8_S destDevType,const UINT8_S destDevId);

/*
* 功能描述： 打包发送维护信息，记录仪用 
* 参数说明： UINT8_S destDevType,const UINT8_S destDevId, const UINT8_S* logBuff, const UINT32_S logLen 
* 返回值  ： void
*/
void AdptAppLogRecordPack(const UINT8_S destDevType,const UINT8_S destDevId, const UINT8_S* logBuff, const UINT32_S logLen);


#ifdef __cplusplus
}
#endif

#endif
