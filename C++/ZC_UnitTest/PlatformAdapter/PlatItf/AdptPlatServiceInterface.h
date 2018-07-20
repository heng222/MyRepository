/********************************************************
* 
* 文 件 名： AdptPlatServiceInterface.h
* 作    者： 董欣 
* 创建时间： 2016-09-01 
* 功能描述： 适配层提供给平台层的底层适配库函数的接口头文件  
* 备    注： 无 
* 
********************************************************/ 

#ifndef ADPTPLAT_SERVICE_INTERFACE_H_
#define ADPTPLAT_SERVICE_INTERFACE_H_

#include "AdptPlatBasicTypeDefinition.h"
#include "../../Common/CommonTypes.h"

#define MAX_REV_PIPE_NUM  15u
#define MAX_SND_PIPE_NUM  15u

/* 在平台通信设备配置表中平台外设备配置起始索引 */
#define VCP_DMS_START_INDEX  4u
#define VCP_ZC_START_INDEX  4u
#define VCP_ATP_START_INDEX  12u

/* 两系通信状态记录 */
#define EXT_DEV_COM_SUC  1u      /* 1有数据 */
#define EXT_DEV_COM_FAIL  0u      /* 0无数据 */

#define RSSP_PACK_ERROR_ID         0u  /* 错误的数据接收方类型或识别号 */
#define RSSP_PACK_ERROR_LEN        1u  /* 打包数据长度大于最大允许长度 */
#define RSSP_PACK_TSD_SSE_SSR      2u  /* 打包TSD和对时帧(SSR或SSE) */
#define RSSP_PACK_TSD              3u  /* 已打包TSD */

#define RSSP_PARSE_ERROR_ID         0u  /* 错误的数据接收方类型或识别号 */
#define RSSP_PARSE_ERROR_LEN        1u  /* 接收数据长度大于最大允许长度 */
#define RSSP_PARSE_SSE_SSR          2u  /* 接收对时帧(SSR或SSE) */
#define RSSP_PARSE_RSD              3u  /* 接收RSD */

#define RSSP_PACK_SSR_LEN    25u           /*SSR包长度*/
#define RSSP_PACK_SSE_LEN    20u           /*SSE包长度*/

#define MIC_R_DEV_NUM        200u      /* 过网关设备的总数目 */

#define HANDLE_OUT_NOT_MICR  0u         /* 处理输出数据不过网关 */
#define HANDLE_OUT_MICR_DEV  1u         /* 处理输出数据过网关为非NTP */
#define HANDLE_OUT_MICR_NTP  2u         /* 处理输出数据过网关为NTP */

/*定义设备配置详细信息*/
typedef struct AdptDevCfgDetail
{
    UINT16_S  devType;               
    UINT8_S   devId;
    UINT8_S   devSysId;
    UINT32_S   rcvPipeNum;      /*[4 byte] 设备接收管道数 */
    UINT32_S   sndPipeNum;      /*[4 byte] 设备发送管道数 */
    UINT32_S   sndPipeIndex;
}AdptDevCfgDetailStruct;

typedef struct AdptUsrBuff
{
  UINT8_S* ptrMsg  ;  /* 缓冲地址     */
  UINT32_S dataLen ;  /* 缓冲内容长度 */
  UINT32_S allocLen;  /* 缓冲分配长度 */
}AdptUsrBuffStruct;


/*定义设备配置详细信息*/
typedef struct AdptMicr
{
    UINT16_S  devType;
    UINT8_S   devId;
    UINT8_S   sysId;
    UINT8_S   comFlag;        /* 通信状态记录标志，1有数据0无数据 */
}AdptMicrDevStruct;


/*定义USR发送倒机数据信息注册函数*/
typedef void (*AdptTrackDataGet)(UINT8_S* inBuffAddr, UINT32_S inBuffLen, UINT32_S* outSendLen);

/*定义USR接收倒机数据信息注册函数*/
typedef void (*AdptTrackDataSet)(UINT8_S* inBuffAddr, UINT32_S inRecvLen);


#ifdef __cplusplus
extern "C" {
#endif

/* 发送前对于数据进行某些特殊的处理，如ATP有发送过网关的设备要打包的要求 */
UINT8_S AdptPlatOutDataHandle(UINT32_S inDevType, UINT32_S inAppId, const UINT8_S *inData, UINT32_S inLen, UINT8_S outData[], UINT32_S *pOutLen);


/*
* 功能描述：读取设备配置信息
* 参数说明： 
* 返回值  ： 1:成功  0,失败
*/
UINT8_S AdptPlatGetDevCfgDetail(const UINT32_S inListLen, AdptDevCfgDetailStruct outDevCfgDetailList[], UINT32_S* outDevNum);



/*
*功能描述: 获取UDP通信设备总数
* 参数：
*            输入:
*            inDevType : 输入设备的逻辑类型
*            inAppId   : 输入设备的应用ID
*            inDevSys  : 输入设备的所在系别
*            inPipeId: 输入所用通道号
*            ioUsrBuff: ioUsrBuff ->ptrMsg,接收缓冲区地址
*                           ioUsrBuff ->allocLen,接收缓冲可用空间
*            输出:
*            ioUsrBuff: ioUsrBuff ->ptrMsg,接收缓冲区地址
*                         ioUsrBuff ->dataLen,接收到的数据长度
*返回值: 1，成功；0，失败
*/

UINT8_S AdptPlatUsrDataRecv(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  const UINT32_S inPipeId,
                                  AdptUsrBuffStruct* ioUsrBuff);



/*
*功能描述: 获取UDP通信设备总数
* 参数：
*            输入:
*            inDevType : 输入设备的逻辑类型
*            inAppId   : 输入设备的应用ID
*            inDevSys  : 输入设备的所在系别
*            inPipeId: 输入所用通道号
*            inData:输入发送缓冲区地址
*            dataLen:输入发送数据长度
*            输出:
*            无
*返回值: 1，成功；0，失败
*/

UINT8_S AdptPlatUsrDataSend(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  const UINT32_S inPipeId,
                                  const UINT8_S * inData,
                                  const UINT32_S dataLen);




/*
* 功能描述：通过平台前面板发送调试数据(通过网口)
* 参数说明： 
*                           输入，const UINT8* const inData，发送缓冲区 const UINT32 inDataLen，发送数据长度
*                           输出，无
* 返回值  ： 1:有数据且发送成功  0,(发送失败 || 发送缓冲区地址为NULL || 发送长度为0)
*/

UINT8_S AdptPlatUsrDataWatch(const UINT8_S* const inData,
                                    const UINT32_S inDataLen);



/*
* 功能描述：两系同步时两系间数据接收接口函数
* 参数说明：输入:
*                            AdptCellMsgStruct* const ioMsg
*                            ioMsg.ptrMsg,接收数据缓冲器
*                            ioMsg.dataLen ,接收缓冲区可用空间
*                            输出 :
*                            AdptCellMsgStruct* const ioMsg
*                            ioMsg.ptrMsg,接收数据存放缓冲器
*                            ioMsg.dataLen ,接收数据长度
*
* 返回值      :  1,成功 ，0，失败
*/
UINT8_S AdptPlatUsrDataRecvMutual(AdptCellMsgStruct* const ioMsg);



/*
* 功能描述：两系同步时两系间数据发送接口函数
* 参数说明：输入,
*                            const void* const inData，发送数据缓冲区
*                            const UINT32 inDataLen,发送数据长度
* 返回值      :  1,成功 ，0，失败
*/

UINT8_S AdptPlatUsrDataSendMutual(const void* const inData, const UINT32_S inDataLen);




/*
* 功能描述：驱使平台宕机的接口函数
* 参数说明：const UINT32 errNo ，需要记录的错误码
* 返回值      :  无
*/
void AdptPlatUsrHaltSystem(const UINT32_S inErrCode);




/*
* 功能描述：获取设备状态
* 参数说明： 
*                           输入，const UINT8 devType，设备类型; const UINT8 devId，设备ID;const UINT8 sysId,设备ID
*                           输出，无
* 返回值  ： 设备状态

*/

UINT8_S AdptPlatInquiryDevStatus(const UINT32_S devType,const UINT32_S devId,const UINT32_S sysId);



/*
* 功能描述：获取平台周期开始系统时钟的接口函数
* 参数说明： 
*                         输入，无
*                         输出，
*                         UINT32 *sec，秒
*                         UINT32 * msec, 毫秒
* 返回值  ： 无
*/
void AdptPlatSystemClkGet(UINT32_S *sec, UINT32_S *msec);



/*
* 功能描述：获取系统日历时间的接口函数
* 参数说明： 
*                           输入，无
*                           输出，
*                                UINT32 *year，年
*                                UINT32 * month, 月
*                                UINT32 * day,     日
*                                UINT32 *hour,     时
*                                UINT32 *min,      分
*                                UINT32 *sec,      秒
*                                (无效值:0xFFFF)
* 返回值  ： 无
*/
void  AdptPlatCalendarClkGet(UINT32_S *year, UINT32_S * month, UINT32_S * day, UINT32_S *hour, UINT32_S *min, UINT32_S *sec);


/*
* 功能描述： 设置系统日历时间接口函数
* 参数说明： 
*                           输入，
*                                UINT32 year，年
*                                UINT32 month, 月
*                                UINT32 day,     日
*                                UINT32 hour,     时
*                                UINT32 min,      分
*                                UINT32 sec,      秒
*                           输出，无
* 返回值  ： 1，成功  0，失败
*/

UINT8_S AdptPlatCalendarClkSet(UINT32_S year, UINT32_S month, UINT32_S day, UINT32_S hour, UINT32_S min, UINT32_S sec);


/*
* 功能描述：获取当前所处系别信息(0x01 ,I系;0x02,II系)接口函数
* 参数说明： 无
* 全局变量： 
* 返回值  ： 当前所处系别信息(0x01 ,I系;0x02,II系)
*/

UINT32_S AdptPlatGetSystemId(void);

/*
* 功能描述：获取主系系别信息(0x01 ,I系;0x02,II系)接口函数
* 参数说明： 无
* 全局变量： 
* 返回值  ：  主系系别信息(0x01 ,I系;0x02,II系)
*/
UINT32_S AdptPlatGetMasterId(void);

/*
* 功能描述：提供给应用导机注册接口函数
* 参数说明：const UINT32 inMaxLen, 注册最大倒机数据长度;
*                            const UINT32 inInterval,注册强制倒机周期间隔;
*                            AdptTrackDataGet inDataGet, 注册获取USR倒机数据函数
*                            AdptTrackDataSet inDataSe,t注册设置USR倒机数据函数
* 返回值      :    1,成功 0,失败
*/
UINT8_S AdptPlatTrackRegister(const UINT32_S inMaxLen, const UINT32_S inInterval,
                   AdptTrackDataGet inDataGet, AdptTrackDataSet inDataSet);


/*
* 功能描述：获取平台周期号的接口函数
* 参数说明：无
* 返回值      :    平台周期号
*/
UINT32_S AdptPlatCycNum(void);

/*
* 功能描述：Rssp协议进行初始化 
* 参数说明：selfDevId本机设备名，inCfgLen配置数据长度，inCfgBuf配置数据缓冲区 
* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptPlatRsspInit(const UINT16_S selfDevId, const UINT16_S inCfgLen, UINT8_S *inCfgBuf);

/*
* 功能描述：Rssp协议更新周期时钟 
* 参数说明：无
* 返回值      :    无
*/
void AdptPlatRsspUpdateClock(void);

/*
* 功能描述：Rssp协议获取同步数据
* 参数说明：buf同步数据缓冲区 
* 返回值      :    同步数据长度 
*/
UINT16_S AdptPlatRsspGetSynData(UINT8_S *buf);

/*
* 功能描述：Rssp协议传输同步数据
* 参数说明：buf同步数据缓冲区 ,数据长度 
* 返回值      :    同步数据长度 
*/
void AdptPlatRsspSetSynData(UINT8_S *buf, UINT16_S len);


/*
* 功能描述：Rssp协议打包函数 
* 参数说明：inDstDevId设备名，inLen输入长度，inBuf输入数据，
*                     outTsdLen应用数据长度，outTsdBuf应用数据，outSsLen对时帧长度，outSsBuf对时帧数据
* 返回值      :    0类型错误，1 长度错误，2未打包TSD，3已打包TSD 
*/
UINT8_S AdptPlatRsspPackData(const UINT16_S inDstDevId, const UINT16_S inLen, UINT8_S *inBuf,
        UINT16_S *outTsdLen, UINT8_S *outTsdBuf,UINT16_S *outSseLen, UINT8_S *outSseBuf,UINT16_S *outSsrLen, UINT8_S *outSsrBuf);

/*
* 功能描述：Rssp协议解包函数  
* 参数说明：inDstDevId设备名，inLen输入长度，inBuf输入数据，
*                     outLen应用数据长度，outBuf应用数据 
* 返回值      :    0类型错误，1 长度错误，2 SSE or SSR，3 RSD 
*/
UINT8_S AdptPlatRsspParseData(const UINT16_S inDstDevId, const UINT16_S inLen, UINT8_S *inBuf,
        UINT16_S *outLen, UINT8_S *outBuf);

/*
* 功能描述：Rssp协议获取链路信息 
* 参数说明：inDstDevId设备名，timeDiff 时间差 
* 返回值      :    0关闭，1正常 
*/
UINT8_S AdptPlatRsspGetChaStat(const UINT16_S inDstDevId, UINT16_S *timeDiff);

/*
* 功能描述：将输入设备类型、设备识别号对应的链路置为打开状态， 
*                            协议栈将允许对应设备传入数据。 
* 参数说明：dstDevId设备名
* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptPlatRsspOpen(const UINT16_S dstDevId);

/*
* 功能描述：将输入设备类型、设备识别号对应的链路置为关闭状态， 
*                            协议栈将拒绝对应设备传入数据。 
* 参数说明：dstDevId设备名
* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptPlatRsspClose(const UINT16_S dstDevId);

/*
* 功能描述：提供给应用查询各插件处理软件版本及通信软件版本
* 参数说明：
*Para    : inDevType      : 输入设备的逻辑类型
*            inAppId        : 输入设备的应用编号
*            inAccSys       : 输入设备所在系别标识
*            plugAppVer : 输出处理软件版本
*            plugCommVer : 输出通讯软件版本

*          |  版本标识  |  版本类型  |  补充编号  |  版本编号  |
*          |-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|
*          版本标识：'V'
*          版本类型：'A' - 'Z'
*          版本编号：1 - 15
*          补充编号：正式版本：0
*                    测试版本：'a' - 'z'
*
*          显示示例：
*          0x56 -> 'V'
*          0x43 -> 'C'
*          0x61 -> 'a'
*          0x56430001UL -> V.C.0001   正式版
*          0x56436101UL -> V.C.0001a  测试版


* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptPlatPlugSwVersionGet(const UINT32_S  inDevType,
                                  const UINT32_S  inAppId,
                                  const UINT32_S  inAccSys,
                                  UINT32_S* const plugAppVer,
                                  UINT32_S* const plugCommVer);


/*
* 功能描述：获取平台周期开始系统时钟的接口函数
*          注意此数据获取为系统当前时间，仅供串口打印日志使用 
* 参数说明： 
*                         输入，无
*                         输出，
*                         UINT32 *sec，秒
*                         UINT32 * msec, 毫秒
* 返回值  ： 无
*/
void AdptPlatTestSystemClkGet(UINT32_S *sec, UINT32_S *msec);

#ifdef __cplusplus
}
#endif

#endif



