/******************************************************************************
 *File Name         :    Vcp_Service_Interface.h
 *Copyright         :    Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :    2012/03/11
 *Module Id      :  SD-SM_PAB-1010
 *Description    :    SM提供的有关PAB的BSP接口(本文件只实现ETH口绑定)
 *                  其它函数的实现都已库函数的形式提供
 *
 *+----------+---------------------------------------------------------------+
 *| Design   |    轨道交通信号系统通用安全计算机平台主机插件SM_PAB           |
 *|  File    |    软件详细设计说明书Vcp_Service_Interface组件_B.2            |
 *+----------+--------------+------------+-----------------------------------+
 *| Version  |    Author    |    Date    |            Description            |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0001 | YanGuang     | 2012/03/11 |  File Create                      |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0002 | YanGuang     | 2013/04/17 |(1)对函数指针类型的形参添加const   |
 *|          |              |            |   限定符                          |
 *|          |              |            |(2)修改TAG_CellMsg的说明           |
 *|          |              |            |(3)修改F_VCP_UsrDataRecv形参       |
 *|          |              |            |   修改F_VCP_UsrDataRecvMutual形参 |
 *|          |              |            |   修改F_VCP_DevInfSummary形参     |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0003 | YanGuang     | 2013/08/28 |(1)删除过渡状态                    |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0004 | YanGuang     | 2013/10/29 |增加接口函数:                      |
 *|          |              |            |(1)F_VCP_UsrIndicator              |
 *|          |              |            |(2)F_VCP_UsrInquiryParamVersion    |
 *|          |              |            |增加接口常量:                      |
 *|          |              |            |(1)c_UsrIndicatorA                 |
 *|          |              |            |(2)c_UsrIndicatorB                 |
 *|          |              |            |(3)c_UsrIndicatorOn                |
 *|          |              |            |(4)c_UsrIndicatorOff               |
 *|          |              |            |(5)c_InquiryLoc                    |
 *|          |              |            |(6)c_InquiryRem                    |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0005 | ZhuHui       | 2014/03/20 |(1)删除文件相关数据结构、函数      |
 *|          |              |            |(2)添加接口F_VCP_GetVcpId          |
 *|          |              |            |           F_VCP_GetHwVersion      |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0006 | ZhuHui       | 2014/08/20 |(1)在E_SysDevStatus中添加一种状态  |
 *|          |              |            |   e_SysDevTesting                 |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0007 | ZhuHui       | 2014/10/10 |(1)添加接口F_VCP_GetLocBspVersion  |
 *|          |              |            |(2)修改F_VCP_UsrDataSend           |
 *|          |              |            |   解决无法向平台外设发送数据情况  |
 *+----------+--------------+------------+-----------------------------------+
 *| C.B.0001 | ZhuHui       | 2015/08/20 |(1)Eth模式下通过新接口发送/接收    |
 *|          |              |            |   系间用户数据                    |
 *|          |              |            |   添加宏标识系间用户数据最大长度  |
 *+----------+--------------+------------+-----------------------------------+
 *
 ******************************************************************************/

/******************************************************************************
*    Multi-Include-Prevent Start Section
****************************************************************************/
#ifndef VCP_SERVICE_INTERFACE_H_
#define VCP_SERVICE_INTERFACE_H_
#define ZC_adpter_VERSION   "1.0.0.0"
#define ZC_CSP_VERSION      "1.2.0.0"/*ARTESYN使用的系统版本为1.2*/
#define MAX_CFG_FILE_NUMBER    8U


#define TRANSMIT_2OO2_STATE_GOOD                  0x01U      /*通信良好*/
#define TRANSMIT_2OO2_STATE_LINK                  0x02U      /*维持连接*/
#define TRANSMIT_2OO2_STATE_BAD                   0x03U      /*通信中断*/
#define COM_DEV_TYPE_SUM                          8U
#define COM_DEV_MAX                               1400
#define SRB_Master_Value                          0xC0			/*在SRB模式下主系标志C3 单机调试模式下为C0*/


#ifdef WIN32
#pragma pack(1)
#define ADPTER_PACKED
#else
#define ADPTER_PACKED  __attribute__((__packed__))
#endif




/******************************************************************************
*    Debug switch Section
******************************************************************************/

/******************************************************************************
*    Include File Section 增加适配CSP平台部分
******************************************************************************/
/*
#include <vxworks.h>
#include <stdio.h>
#include <usrLib.h>
#include <arpa/inet.h>
*/

#include "fscVpd.h"
#include "fscRtd.h"
#include "fscCsDrv.h"
#include "fscLib.h"

#include "GL_Basic_Type_Definition.h"
#include "Vcp_Public_Definition.h"
#include "Vcp_Service_TestInterface.h"
#include "Vcp_File_Interface.h"
#include "..\GM_Utils\GM_MQ_Fixed.h"
#include "..\GM_Utils\GM_Memset.h"
#include "..\GM_Utils\GM_Memcpy.h"
#include "..\GM_Utils\GM_Ini_File.h"
#include "..\Common\CommonQueue.h"
#include "..\FSFB\GM_RSSP1_APP_Interface.h"
#include "..\FSFB\CFM\GM_RSSP1_CFM_Interface.h"
#include "..\FSFB\SFM\GM_RSSP1_SFM_Interface.h"
#include "..\INTERCOMM\GM_CFG_INTERCOMM.h"
#include "..\INTERCOMM\SYNC_INTERCOMM_Def.h"
#include "..\INTERCOMM\SYNC_INTERCOMM_Init.h"
#include "..\INTERCOMM\SYNC_INTERCOMM.h"
#include "..\INTERCOMM\GM_LOG_INTERCOMM.h"
/* CAN 通信
#include "..\INTERCOMM\CAN_INTERCOMM.h"
#include "..\fsiopkt\fsiopkt.h"
*/


/******************************************************************************
*    Global Macro Define Section
******************************************************************************/



/******************************************************************************
*    Global Struct    Define Section
******************************************************************************/
/*定义系统设备状态*/
/*C.A.0003  ZhuHui  2013/08/21  删除过渡状态*/
typedef  enum TAG_SysDevStatus
{
  e_SysDevNotExist= 1, /*设备不存在   */
  e_SysDevInit    = 2, /*设备初始化   */
  e_SysDevNormal  = 4, /*设备正常状态 */
  e_SysDevFault   = 5, /*设备故障状态 */
  e_SysDevTesting = 6  /*设备自检     */
}E_SysDevStatus;

/*定义用户数据接收状态*/
typedef enum TAG_UsrRxStatus
{
  e_UsrRxLcEmpty  = 1,  /* 无数据   */
  e_UsrRxLcAppNew = 2,  /* 新数据   */
  e_UsrRxLcAppOld = 3,  /* 旧数据   */
  e_UsrRxLcMsgErr = 4,  /* 数据错误 */ /* 单条数据超过配置最大长度 */
  e_UsrRecvCfgErr = 5,  /* 配置错误 */ /* 用户提供缓冲错误 */
  e_UsrRxErrDev   = 6   /* 错误设备 */
}E_UsrRxStatus;

typedef enum TAG_UsrTxStatus
{
  e_UsrTxSuccess   = 1,  /* 发送成功 */
  e_UsrTxErrDev    = 2,  /* 错误设备 */
  e_UsrTxErrData   = 3,  /* 错误数据 */ /* 空指针or数据超长 */
  e_UsrTxErrRepeat = 4,  /* 重复发送 */
  e_UsrTxErrStatus = 5   /* 错误状态 */ /* 不允许向非正常状态的Vcp设备发送数据 */
}E_UsrTxStatus;

/*定义设备存在的细节*/
typedef struct TAG_DevDetail
{
  GM_UINT16 DevType; /*[2 byte] 设备类型           */
  UINT8  DevCab ; /*[1 byte] 设备的插箱编号     */
  UINT8  DevPos ; /*[1 byte] 设备的插件位置     */
  UINT8  AccCab ; /*[1 byte] 接入的插箱编号     */
  UINT8  AccPos ; /*[1 byte] 接入的插箱位置     */
  UINT8  AccSys ; /*[1 byte] 接入的系别         */
  UINT8  AppId  ; /*[1 byte] 指示设备的"应用ID" */
}T_DevDetail;

/* 定义设备附加信息 */
typedef struct TAG_DevExInfo
{
  UINT32 TxMsgLen; /*[4 byte] 设备发送长度   */
  UINT32 RxMsgLen; /*[4 byte] 设备接收长度   */
  UINT32 SendNum ; /*[4 byte] 设备发送管道数 */
  UINT32 RecvNum ; /*[4 byte] 设备接收管道数 */
}T_DevExInfo;

/*定义一个VCP设备的信息*/
typedef struct TAG_SysDevInf
{
  T_DevDetail    Detail; /*[8 byte]*/
  E_SysDevStatus Status; /*[4 byte]*/
}T_SysDevInf;

/*设备版本信息*/
typedef struct TAG_UsrDevVerInf
{
  /*生产Id长度*/
  #define c_VCP_ManIdLen (10UL)

  UINT32    SwProc               ; /*内核程序软件版本号*/
  UINT32    SwComm               ; /*通信程序软件版本号*/
  T_RealClk Date                 ; /*生产日期          */
  UINT32    HwVer                ; /*硬件版本号        */
  UINT8     ManId[c_VCP_ManIdLen]; /*生产编号          */
  UINT8     Reserve[2]           ; /*预留              */
}T_UsrDevVerInf;

/*定义设备配置详细信息*/
typedef struct TAG_DevCfgDetail
{
  /*最大设备名长度*/
  #define c_VCP_MaxDevNameLen (16UL)

  CHARACTER    DevName[c_VCP_MaxDevNameLen]; /* 设备名   */
  T_DevDetail  BasicInfo                   ; /* 基本信息 */
  T_DevExInfo  ExInfo                      ; /* 附加信息 */
}T_DevCfgDetail;

/*定义用户指示器*/
#define c_UsrIndicatorA (0xAAUL)
#define c_UsrIndicatorB (0xBBUL)

/*定义用户指示器动作*/
#define c_UsrIndicatorOff (0UL)
#define c_UsrIndicatorOn  (1UL)

/*查询本地主机配置文件标识*/
#define c_InquiryLoc (0UL)
/*查询另一系主机配置文件标识*/
#define c_InquiryRem (1UL)

/* 最大系间互换数据长度 */
#define c_VCP_MaxMutualDataLen4Eth (100UL * 1024UL)
#define c_VCP_MaxMutualDataLen4Flr (1200UL)

/******************************************************************************
*    CSP Variable Declare Section BIGEN
******************************************************************************/

typedef enum enum_extern_eth_comm_protocal_type
{
	ENUM_EXT_ETH_COMM_TYPE_INVALID = 0x00U,      /*无效类型*/
	ENUM_EXT_ETH_COMM_TYPE_RAW     = 0x55U,      /*裸协议*/
	ENUM_EXT_ETH_COMM_TYPE_RSSP1   = 0xAAU,      /*RSSP-1协议*/
	ENUM_EXT_ETH_COMM_TYPE_RSSP2   = 0xBBU       /*预留RSSP-2协议*/ 

}ENUM_TYPE_EXTERN_ETH_COMM_PROTOCAL;




/*与当前CI设备通信的设备通信状态结构体*/
typedef struct  CommunicationDevStatus
{
	UINT8 DeviceIdCiLocal;					/*本联锁ID*/
	UINT8 DeviceTypeOther;					/*对方设备类型*/
	UINT8 ComDevSum;						    /*此类型设备总数*/
	UINT8 ComDevIdBuf[COM_DEV_MAX];			/*此类型设备*/
	UINT8 ComDevIdComStatusBuf[COM_DEV_MAX];	/*此类型设备通信状态*/
}ADPTER_PACKED CommunicationDevStatusStruct;


typedef struct
{
	GM_UINT16  Index;                      /*索引号:16*/
	GM_UINT16  Des_Source_ID;           /*目的地址:16*/
	UINT8   SFM_State;                  /*SFM状态: 4*/
	UINT8   Des_MS_State;            /*远端设备主备信息: 4*/
	UINT8   Udp_Chn_Num;             /*UDP通道数目: 4*/
	UINT8   Udp_Chn_State;           /*UDP通道状态: 8*/
}ADPTER_PACKED  APP_RSSPI_COMM_STATE;


/******************************************************************************
*    CSP Variable Declare Section END
******************************************************************************/





/******************************************************************************
*    Global Variable Declare Section
******************************************************************************/


/******************************************************************************
*    Global Prototype Declare Section
******************************************************************************/
/******************************************************************************
 *Name    : F_VCP_UsrDataWatch
 *Function: 提供给用户每个周期进行调试数据监测的接口
 *          (如果本次调用时的本周期的累计实时数据长度已经超出1400字节则本函数
 *           不会对此次数据进行发送,并返回e_FALSE)
 *Para    : @inData    : 为消息数据首地址
 *          @inDataLen : 为消息数据长度(以字节为单位)
 *Return  : 输出成功则返回e_TRUE, 否则返回e_FALSE
 *Note    :
******************************************************************************/
E_SysBool F_VCP_UsrDataWatch(const UINT8* const inData,
                             const UINT32       inDataLen);


/******************************************************************************
 *Name    : F_VCP_UsrDataRecv
 *Function: 若用户提供完整的设备指示(即提供inDevType、inAppId 、inDevSys)则可获
 *          得指定设备的数据，否则(即提供inDevType、inAppId)可获得主系设备的数据。
 *          用户获取数据成功后，同周期内再次获取相同设备的数据，
 *          函数则会返回数据重复标识(e_RxLcAppOld).
 *Para    : @inDevType : 输入设备的逻辑类型
 *          @inAppId   : 输入设备的应用ID
 *          @inDevSys  : 输入设备的所在系别
 *          @ioMsg     : 输入/输出数据的缓冲,其结构如下:
 *                      typedef  struct TAG_CellMsg
 *                      {
 *                        UINT8*  ptrMsg ; [>Out: 存储区首地址               <]
 *                        UINT32  dataLen; [>I/O: 存储区长度/存储区中数据长度<]
 *                      } T_CellMsg;
 *Return  : 返回 E_UsrRxStatus, 指示获取数据的状态
 *           . e_UsrRxLcEmpty  = 1, 逻辑通道数据为空
 *           . e_UsrRxLcAppNew = 2, 逻辑通道(用户)消息为新
 *           . e_UsrRxLcAppOld = 3, 逻辑通道(用户)消息为旧
 *           . e_UsrRxLcMsgErr = 4, 逻辑通道的消息错误
 *           . e_UsrRecvCfgErr = 5  用户提供的接收配置信息错误
 *Note    :
 ******************************************************************************/
E_UsrRxStatus F_VCP_UsrDataRecv(const UINT32 inDevType,
                                const UINT32 inAppId,
                                const UINT32 inDevSys,
                                T_CellMsg*   ioMsg);

/******************************************************************************
 *Name    : F_VCP_UsrDataRecvEx
 *Function: 获得指定设备的数据 增强型
 *Para    : @inDevType: 输入设备的逻辑类型
 *          @inAppId  : 输入设备的应用ID
 *          @inDevSys : 输入设备的所在系别
 *          @inPipeId : 输入管道号
 *          @ioUsrBuff: 输入/输出数据的缓冲
 *Return  : 返回 E_UsrRxStatus, 指示获取数据的状态
 *Note    :
 ******************************************************************************/
E_UsrRxStatus F_VCP_UsrDataRecvEx(const UINT32 inDevType,
                                  const UINT32 inAppId,
                                  const UINT32 inDevSys,
                                  const UINT32 inPipeId,
                                  T_UsrBuff*   ioUsrBuff);


/******************************************************************************
 *Name    : F_VCP_UsrDataRecvMutual
 *Function: 本系用户接收他系用户发送的数据
 *Para    :  @ioMsg : 输入/输出数据的缓冲,其结构如下:
 *                    typedef  struct TAG_CellMsg
 *                    {
 *                      UINT8*  ptrMsg ; [>Out: 存储区首地址               <]
 *                      UINT32  dataLen; [>I/O: 存储区长度/存储区中数据长度<]
 *                    } T_CellMsg;
 *Return  : 返回 E_UsrRxStatus, 指示获取数据的状态
 *           . e_UsrRxLcEmpty  = 1, 逻辑通道数据为空
 *           . e_UsrRxLcAppNew = 2, 逻辑通道(用户)消息为新
 *           . e_UsrRxLcAppOld = 3, 逻辑通道(用户)消息为旧
 *           . e_UsrRxLcMsgErr = 4, 逻辑通道的消息错误
 *           . e_UsrRecvCfgErr = 5  用户提供的接收配置信息错误
 *Note    :
******************************************************************************/
E_UsrRxStatus F_VCP_UsrDataRecvMutual(T_CellMsg* const ioMsg);


/******************************************************************************
 *Name    : F_VCP_UsrDataSend
 *Function: 向指定设备发送数据
 *Para    : @inDevType: 输入设备的逻辑类型
 *          @inAppId  : 输入设备的应用ID
 *          @inDevSys : 输入设备的所在系别
 *          @inData   : 输入用户提供用于存数据的缓冲
 *          @inDataLen: 输入用户提供待输出数据的长度
 *Return  : 发送成功=>返回e_TRUE, 否则返回e_TRUE
 *Note    : 不允许向同一设备重复发送
******************************************************************************/
E_SysBool F_VCP_UsrDataSend(const UINT32 inDevType,
                            const UINT32 inAppId,
                            const UINT32 inDevSys,
                            const void*  inData,
                            const UINT32 inDataLen);




/******************************************************************************
 *Name    : F_VCP_UsrDataSendEx
 *Function: 向指定设备发送数据 增强型
 *Para    : @inDevType: 输入设备的逻辑类型
 *          @inAppId  : 输入设备的应用ID
 *          @inDevSys : 输入设备的所在系别
 *          @inPipeId : 输入指定的管道号[0-14], 非多管道设备填0
 *          @inData   : 输入用户提供用于存数据的缓冲
 *          @inDataLen: 输入用户提供待输出数据的长度
 *Return  : 发送状态
 *Note    : 不允许向同一设备重复发送
 ******************************************************************************/
E_UsrTxStatus F_VCP_UsrDataSendEx(const UINT32 inDevType,
                                  const UINT32 inAppId,
                                  const UINT32 inDevSys,
                                  const UINT32 ProtocolType,
                                  const void*  inData,
                                  const UINT32 inDataLen);



/******************************************************************************
 *Name    : F_VCP_UsrDataSendMutual
 *Function: 本机用户向他机用户发送数据的接口
 *Para    : @inData    : 输入数据
 *          @inDataLen : 输入数据的长度
 *Return  : 成功则返回e_TRUE, 否则返回e_TRUE。
 *Note    : 一个周期内重复调用，只发送最后一次数据
******************************************************************************/
E_SysBool F_VCP_UsrDataSendMutual(const void* const inData,
                                  const UINT32      inDataLen);

/******************************************************************************
 *Name    : F_VCP_UsrHaltSystem
 *Function: 当用户程序判断出现重大故障需要停止应用处理时调用此接口函数。
 *          本函数将存储故障代码(以便用户进行维护)并从5周期后终止执行用户应用处
 *          理程序。
 *Para    : @inErrCode: 输入故障代码
 *Return  : void
 *Note    :
 *C.A.0002  YanGuang  2013/04/17  修改原设计
 *                                将“从下周期开始终止执行用户应用处理程序”
 *                                改为 “立即终止执行用户应用处理程序”
******************************************************************************/
void F_VCP_UsrHaltSystem(const UINT32 inErrCode);


/******************************************************************************
 *Name    : F_VCP_DevInfSummary
 *Function: 用户可查询所有VCP设备的当前状态
 *Para    : @outDevInfArray: 输出所有VCP设备状态的数组，状态定义如下
 *           . e_SysDevNotExist =1, 设备不存在
 *           . e_SysDevInit     =2, 设备初始化
 *           . e_SysDevTran     =3, 设备过渡状态
 *           . e_SysDevNormal   =4, 设备正常状态
 *           . e_SysDevFault    =5  设备故障状态
 *          @ioDevInfTotal : 输入用户提供数组的容量
 *                           输出所有VCP设备的总数(用于指示第一个形参的数组长度)

 *Return  : void
 *Note    :
 *C.A.0002  YanGuang  2013/04/17  将形参名outDevInfTotal改为ioDevInfTotal
******************************************************************************/
void  F_VCP_DevInfSummary(T_SysDevInf* const outDevInfArray,
                          UINT32* const      ioDevInfTotal);



/******************************************************************************
 *Name    : F_VCP_InquiryDevStatus
 *Function: 提供给用户根据外设的VCP设备指定信息获取VCP设备的当前状态的接口
 *Para    : @inDevType: 输入设备的逻辑类型
 *          @inAppId  : 输入设备的应用编号
 *          @inClique : 输入设备所在系别标识
 *Return  : 返回指定设备的详细信息(包括设备描述及 状态 E_SysDevStatus):
 *          . e_SysDevNotExist = 1, 设备不存在
 *          . e_SysDevInit     = 2, 设备初始化
 *          . e_SysDevNormal   = 4, 设备正常状态
 *          . e_SysDevFault    = 5  设备故障状态
 *Note    :
******************************************************************************/
T_SysDevInf F_VCP_InquiryDevStatus(const UINT32 inDevType,
                                   const UINT32 inAppId,
                                   const UINT32 inClique);


/******************************************************************************
 *Name    : F_VCP_InquirySwVersion
 *Function: 提供给用户查询各插件处理软件版本及通信软件版本的接口
 *Para    : @inDevType      : 输入设备的逻辑类型
 *          @inAppId        : 输入设备的应用编号
 *          @inAccSys       : 输入设备所在系别标识
 *          @outProcVersion : 输出处理软件版本
 *          @outCommVersion : 输出通讯软件版本
 *
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
 *
 *Return  : 如果查询正确则返回e_TRUE, 否则e_FALSE
 *Note    :
******************************************************************************/
E_SysBool  F_VCP_InquirySwVersion(const UINT32  inDevType,
                                  const UINT32  inAppId,
                                  const UINT32  inAccSys,
                                  UINT32* const outProcVersion,
                                  UINT32* const outCommVersion);


/******************************************************************************
 *Name    : F_VCP_SystemClkGet
 *Function: 提供给用户获取系统时钟的接口
 *Para    : @outSysClk: 输出当前系统时间(其格式如下:)
 *          typedef  struct TAG_SysClk
 *          {
 *            UINT32 Sec ; [>[4 Byte] 秒数  <]
 *            UINT32 uSec; [>[4 Byte] 微秒数<]
 *          }T_SysClk;
 *Return  : void
 *Note    :
******************************************************************************/
void  F_VCP_SystemClkGet(T_SysClk* const outSysClk);


/******************************************************************************
 *Name    : F_VCP_CalendarClkGet
 *Function: 提供给用户获取日历时钟的接口
 *Para    : @outClk: 输出日历时钟(其格式如下:)
 *          typedef  struct TAG_CalendarClk
 *          {
 *            UINT32 Year    ;  [>[4 Byte] 年份  <]
 *            UINT32 Mon     ;  [>[4 Byte] 月份  <]
 *            UINT32 Day     ;  [>[4 Byte] 日期  <]
 *            UINT32 Hour    ;  [>[4 Byte] 小时  <]
 *            UINT32 Min     ;  [>[4 Byte] 分钟  <]
 *            UINT32 Sec     ;  [>[4 Byte] 秒数  <]
 *            UINT32 MiSec   ;  [>[4 Byte] 毫秒数<]
 *            UINT32 WeekDay ;  [>[4 Byte] 星期几<]
 *          }T_CalendarClk;
 *Return  : void
 *Note    :
 *****************************************************************************/
E_SysBool  F_VCP_CalendarClkGet(T_CalendarClk* const outClk);


/******************************************************************************
 *Name    : F_VCP_CalendarClkSet
 *Function: 在提供给用户设置日历时钟的接口(注：字段WeekDay用户可以不填写)
 *Para    : @inClk: 输入日历时钟(其格式如下:)
 *          typedef  struct TAG_CalendarClk
 *          {
 *            UINT32 Year    ;  [>[4 Byte] 年份  <]
 *            UINT32 Mon     ;  [>[4 Byte] 月份  <]
 *            UINT32 Day     ;  [>[4 Byte] 日期  <]
 *            UINT32 Hour    ;  [>[4 Byte] 小时  <]
 *            UINT32 Min     ;  [>[4 Byte] 分钟  <]
 *            UINT32 Sec     ;  [>[4 Byte] 秒数  <]
 *            UINT32 MiSec   ;  [>[4 Byte] 毫秒数<]
 *            UINT32 WeekDay ;  [>[4 Byte] 星期几<]
 *          }T_CalendarClk;
 *Return  : 设置成功返回e_TRUE,否则返回e_FALSE
 *Note    : 2周期后生效
******************************************************************************/
E_SysBool  F_VCP_CalendarClkSet(const T_CalendarClk* const inClk);


/******************************************************************************
 *Name    : F_VCP_GetSystemId
 *Function: 提供给用户获取系别信息的接口
 *Para    : @outSysId: 输出系别信息
 *           . 0x01：I系;
 *           . 0x02：II系;
 *Return  : void
 *Note    :
******************************************************************************/
void  F_VCP_GetSystemId(UINT32* const outSysId);


/******************************************************************************
 *Name    : F_VCP_GetMasterId
 *Function: 提供给用户获取主备系别信息的接口
 *Para    : @outSysId: 输出系别信息
 *           . 0x01：I系;
 *           . 0x02：II系;
 *Return  : void
 *Note    :
******************************************************************************/
void  F_VCP_GetMasterId(UINT32* const outSysId);


/******************************************************************************
 *Name    : F_VCP_GetHwVersion
 *Function: 提供给用户获取硬件版本号的接口
 *Para    : @outHwVersion : 输出硬件版本号 要求outHwVersion是个CHAR数组长度为8
 *Return  : void
 *Note    :
******************************************************************************/
void F_VCP_GetHwVersion(CHAR* const outHwVersion);


/******************************************************************************
 *Name    : F_VCP_GetVcpId
 *Function: 提供给用户获取平台Id的接口
 *Para    : @outVcpId : 输出VcpId
 *Return  : void
 *Note    :
******************************************************************************/
void F_VCP_GetVcpId(UINT32* const outVcpId);


/******************************************************************************
 *Name    : F_VCP_UsrIndicator
 *Function: 提供给用户控制指示器的接口
 *Para    : @inIndicatorNo : 输入用户指示器号
 *          @inAction      : 输入动作
 *Return  : 如果输入参数正确返回e_TRUE，否则返回e_FALSE
 *Note    :
******************************************************************************/
E_SysBool F_VCP_UsrIndicator(const UINT32 inIndicatorNo,
                             const UINT32 inAction);


/******************************************************************************
 *Name    : F_VCP_UsrInquiryParamVersion
 *Function: 提供给用户查询配置文件的接口
 *Para    : @inTarget        : 输入查询目标
 *          @outParamVersion : 输出配置文件版本
 *          @outParamCrc     : 输出配置文件Crc
 *          @inParamCrcLen   : 输入用户提供的存放配置文件Crc内存长度
 *Return  : 如果查询正确返回e_TRUE，否则返回e_FALSE
 *Note    :
 ******************************************************************************/
E_SysBool F_VCP_UsrInquiryParamVersion(const UINT32 inTarget,
                                       UINT32*      outParamVersion,
                                       UINT8        outParamCrc[],
                                       const UINT32 inParamCrcLen);


/******************************************************************************
 *Name    : F_VCP_GetDevVerInf
 *Function: 用户根据外设的VCP设备指定信息获取VCP设备的版本信息
 *Para    : @inDevType    : 输入设备的逻辑类型
 *          @inAppId      : 输入设备的应用编号
 *          @inDevSys     : 输入设备所在系别标识
 *          @outDevVerInf : 输出设备版本信息
 *Return  : 获取到设备的版本信息，返回e_TRUE，否则返回e_FALSE
 *Note    :
******************************************************************************/
E_SysBool F_VCP_GetDevVerInf(const UINT32     inDevType,
                             const UINT32     inAppId,
                             const UINT32     inDevSys,
                             T_UsrDevVerInf*  outDevVerInf);


/******************************************************************************
 *Name    : F_VCP_GetLocBspVersion
 *Function: 提供给用户获取Bsp版本号的接口
 *Para    : @outBspVersion : 输出Bsp版本号
 *Return  : void
 *Note    :
******************************************************************************/
void F_VCP_GetLocBspVersion(UINT32* const outBspVersion);


/******************************************************************************
 *Name    : F_VCP_GetDevCfgDetail
 *Function: 获取详细设备配置
 *Para    : @inListLen           : 输入设备列表长度
 *          @outDevCfgDetailList : 输出设备列表
 *          @outDevNum           : 输出设备列表中设备数
 *Return  : 配置设备总数量
 *Note    : 如果设备列表长度不足, 只会输出inListLen个设备配置
 *          返回值可能大于outDevNum
 ******************************************************************************/
UINT32 F_VCP_GetDevCfgDetail(const UINT32   inListLen,
                             T_DevCfgDetail outDevCfgDetailList[],
                             UINT32*        outDevNum);



/***************************************began***************************************
 *适配CSP平台的部分所需的头文件。
  Modified by Suomingyu 
  添加所需的头文件，数据结构，以及其他函数声明	
 ***********************************************************************************/
GM_BOOL  CSPADPT_App_Initialization(void);

GM_BOOL  CSPADPT_App_Main(void);

UINT32* CSPADPT_Get_Main_Cycle_Ptr(void);

QueueStruct* CSPADPT_Get_Cbtc_Send_Que_Ptr();

QueueStruct* CSPADPT_Get_Cbtc_Rcv_Que_Ptr();

QueueStruct* CSPADPT_Get_APP_LOG_Ptr();

ENUM_TYPE_EXTERN_ETH_COMM_PROTOCAL CSPADPT_Get_External_Comm_Protocal_Type(void);

UINT8 CSPADPT_Get_OppoMachine_State(void);

UINT8 CSPADPT_Get_Local_Machine_Id(void);

GM_BOOL  CSPADPT_Log_Record_Pack(UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length);

#endif