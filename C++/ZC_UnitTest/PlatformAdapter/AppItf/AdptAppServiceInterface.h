/********************************************************
*                                                                                                            
* 文 件 名： AdptAppServiceInterface.h   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 适配层对应用层的接口头文件 
* 备    注： 无 
*
********************************************************/ 

#ifndef ADPT_APP_SERVICE_INTERFACE_H_
#define ADPT_APP_SERVICE_INTERFACE_H_


#include "../../Common/CommonTypes.h"
#include "../PlatItf/AdptPlatBasicTypeDefinition.h"
#include "../PlatItf/AdptPlatServiceInterface.h"


#define RSSP_CFG_MAX_LEN           10000u                /* RSSP协议配置文件最大长度 */
#define RSSP_CFG_NAME           "RSSR.bin"                /* RSSP协议配置文件名 */

#ifdef __cplusplus
extern "C" {
#endif
/*
* 功能描述：提供给应用设备通信初始化接口函数
* 参数说明： 
*                           输入，
*                           无
*                           输出，
*                           无
* 返回值  ：  无
*/
UINT8_S  AdptAppExtDevInit(void);



/*
* 功能描述：提供给应用发送给其他设备数据的发送接口函数
* 参数说明： 
*                           输入，
*                           无
*                           输出，
*                           无
* 返回值  ：  无
*/
void  AdptAppExtDevInDataManage(void);


/*
* 功能描述：提供给应用接收其他设备数据的接口函数
* 参数说明： 
*                           输入，
*                           无
*                           输出，
*                           无
* 返回值  ：  无
*/
void AdptAppExtDevOutDataManage(void);




/*
*功能描述: 数据输入接口
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

UINT8_S AdptAppUsrDataRecv(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  AdptUsrBuffStruct* ioUsrBuff);


/*
*功能描述: 数据输出接口
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

UINT8_S AdptAppUsrDataSend(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  const UINT8_S*  inData,
                                  const UINT32_S dataLen);


/*
* 功能描述：提供给应用通过平台前面板发送调试数据(通过网口)的接口
* 参数说明： 
*                           输入，
*                           const UINT8* const inData，发送缓冲区 
*                           const UINT32 inDataLen，发送数据长度
*                           输出，
*                           无
* 返回值  ： 1:有数据且发送成功 
*                          0:(发送失败 || 发送缓冲区地址为NULL || 发送长度为0)
*/


UINT8_S AdptAppUsrDataWatch(const UINT8_S* const inData,
                                    const UINT32_S inDataLen);


/*
* 功能描述：提供给应用两系同步时两系间数据接收接口函数
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
UINT8_S AdptAppUsrDataRecvMutual(AdptCellMsgStruct* const ioMsg);

/*
* 功能描述：提供给应用两系同步时两系间数据发送接口函数
* 参数说明：输入,
*                            const void* const inData，发送数据缓冲区
*                            const UINT32 inDataLen,发送数据长度
* 返回值      :  1,成功 ，0，失败
*/
UINT8_S AdptAppUsrDataSendMutual(const void* const inData, const UINT32_S inDataLen);


/*
* 功能描述：提供给应用驱使平台宕机的接口函数
* 参数说明：const UINT32 errNo ，需要记录的错误码
* 返回值      :  无
*/
void  AdptAppUsrHaltSystem(const UINT32_S errNo);



/*
* 功能描述：提供给应用获取平台相关设备状态的接口函数
* 参数说明： 
*                           输入，
*                           const UINT8 devType，设备类型; 
*                           const UINT8 devId，设备ID;
*                           const UINT8 sysId,设备ID
*                           输出，无
* 返回值  ： 设备状态
                            1,设备不存在
                   2,设备初始化
                   4,设备正常状态
                   5,设备故障状态 
                   6,设备自检
*/
UINT8_S AdptAppInquiryDevStatus(const UINT32_S devType,const UINT32_S devId,const UINT32_S sysId);



/*
* 功能描述：提供给 应用获取平台周期开始系统时钟的接口函数
* 参数说明： 
*                         输入，无
*                         输出，
*                                    UINT32 *sec，秒
*                                    UINT32 * msec, 毫秒
* 返回值  ： 无
*/

void AdptAppSystemClkGet(UINT32_S *sec, UINT32_S *msec);

/*
* 功能描述：提供给应用获取系统日历时间的接口函数
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
void  AdptAppCalendarClkGet(UINT32_S *year,UINT32_S * month,UINT32_S * day,UINT32_S *hour,UINT32_S *min,UINT32_S *sec);

/*
* 功能描述： 提供给应用设置系统日历时间接口函数
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
UINT8_S  AdptAppCalendarClkSet(UINT32_S year,UINT32_S month,UINT32_S day,UINT32_S hour,UINT32_S min,UINT32_S sec);

/*
* 功能描述：提供给 应用获取当前所处系别信息(0x01 ,I系;0x02,II系)接口函数
* 参数说明： 无
* 全局变量： 
* 返回值  ： 当前所处系别信息(0x01 ,I系;0x02,II系)
*/
UINT32_S AdptAppGetSystemId(void);
/*
* 功能描述：提供给 应用获取主系系别信息(0x01 ,I系;0x02,II系)接口函数
* 参数说明： 无
* 全局变量： 
* 返回值  ：  主系系别信息(0x01 ,I系;0x02,II系)
*/
UINT32_S AdptAppGetMasterId(void);




/*
* 功能描述：提供给应用导机注册接口函数
* 参数说明：const UINT32 inMaxLen, 注册最大倒机数据长度;
*                            const UINT32 inInterval,注册强制倒机周期间隔;
*                            AdptTrackDataGet inDataGet, 注册获取USR倒机数据函数
*                            AdptTrackDataSet inDataSe,t注册设置USR倒机数据函数
* 返回值      :    1,成功 0,失败
*/
UINT8_S AdptAppTrackRegister(const UINT32_S inMaxLen,
                               const UINT32_S inInterval,
                               AdptTrackDataGet inDataGet,
                               AdptTrackDataSet inDataSet);


/*
* 功能描述：提供给应用获取平台周期号的接口函数
* 参数说明：无
* 返回值      :    平台周期号
*/
UINT32_S AdptAppCycNum(void);

/*
* 功能描述：提供给应用设置系统名称的接口函数
* 参数说明：localName 系统名称  
* 返回值      :    
*/
void AdptAppSetLocalName(UINT16_S localName);

/*
* 功能描述：提供给应用获取系统名称的接口函数
* 参数说明：无
* 返回值      :    系统名称 
*/
UINT16_S AdptAppGetLocalName(void);


/*
* 功能描述：Rssp协议进行初始化 
* 参数说明：selfDevId本机设备名，inCfgLen配置数据长度，inCfgBuf配置数据缓冲区 
* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptAppRsspInit(const UINT16_S selfDevId);

/*
* 功能描述：Rssp协议更新周期时钟 
* 参数说明：无
* 返回值      :    无
*/
void AdptAppRsspUpdateClock(void);

/*
* 功能描述：Rssp协议获取同步数据
* 参数说明：buf同步数据缓冲区 
* 返回值      :    同步数据长度 
*/
UINT16_S AdptAppRsspGetSynData(UINT8_S *buf);

/*
* 功能描述：Rssp协议传输同步数据
* 参数说明：buf同步数据缓冲区 ,数据长度 
* 返回值      :    同步数据长度 
*/
void AdptAppRsspSetSynData(UINT8_S *buf, UINT16_S len);

/*
* 功能描述：将输入设备类型、设备识别号对应的链路置为关闭状态， 
*                            协议栈将拒绝对应设备传入数据。 
* 参数说明：dstDevId设备名
* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptAppRsspClose(const UINT16_S dstDevId);

/*
* 功能描述：查询各插件处理软件版本及通信软件版本
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
UINT8_S AdptAppPlugSwVersionGet(const UINT32_S  inDevType,
                                  const UINT32_S  inAppId,
                                  const UINT32_S  inAccSys,
                                  UINT32_S* const plugAppVer,
                                  UINT32_S* const plugCommVer);

/*
* 功能描述：提供给应用设置系统一端二端名的接口函数
* 用于区分车载ATP ATO设备一端二端，如果为地面设备不需要调用此函数
* 参数说明：TrainName 系统名称  
* 返回值      :    
*/
void AdptAppSetTrainName(UINT16_S TrainName);

/*
* 功能描述：提供给应用获取系统一端二端名的接口函数
* 参数说明：无
* 返回值      :    系统名称 
*/
UINT16_S AdptAppGetTrainName(void);

/*
* 功能描述：获取平台系统时钟的接口函数
*                 注意此数据获取为系统当前时间，仅供串口打印日志使用 
* 参数说明： 
*                         输入，无
*                         输出，
*                                    UINT32 *sec，秒
*                                    UINT32 * msec, 毫秒
* 返回值  ： 无
*/
void AdptAppTestSystemClkGet(UINT32_S *sec, UINT32_S *msec);

/*******************************************************************************
* 功能秒数：将秒数转换为日历时间    
* 输入参数：const UINT32_S Seconds(自1970年1月1日0时开始的秒数,已经默认转为本地时间)
* 输出参数：UINT8 *pCalenderBuff   时间数组:年月日时分秒
* 返回值：  1-成功;0-失败;
********************************************************************************/
UINT8_S Seconds2Calendar(UINT32_S seconds, UINT32_S *pCalenderBuff);

/*******************************************************************************
* 功能秒数：将日历时间转换为秒数 
* 输入参数：UINT8 *pCalenderBuff   时间数组:年月日时分秒 
* 输出参数：无 
* 返回值：  UINT32_S Seconds(自1970年1月1日0时开始的秒数) 
*           >0 成功;0失败; 
********************************************************************************/
UINT32_S CalendarToSeconds(UINT32_S *pCalenderBuff);


#ifdef __cplusplus
}
#endif


#endif
