/********************************************************
*                                                                                                            
* 文 件 名： AdapterExtDevInOutManage.h   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 适配层处理头文件 
* 备    注： 无 
*
********************************************************/ 

#ifndef ADAPTER_EXTDEV_INOUT_MANAGE_H_
#define ADAPTER_EXTDEV_INOUT_MANAGE_H_


#include "../../Common/CommonTypes.h"


#define DEV_TOTAL_FRAME_NUM          100u    /* 数据包最大个数 */
#define DEV_TOTAL_FRAME_LEN          1300u   /*处理数据的总长度*/

/* 处理数据的总长度，由于接收数据有多包组成一包情况，所以扩大空间 */
#define DEV_TOTAL_RCV_FRAME_LEN          (DEV_TOTAL_FRAME_LEN*15u*2u)


/*数据存储结构体*/
typedef struct
{
    UINT8_S DataBuf[DEV_TOTAL_FRAME_LEN];  /*数据缓冲区*/
    UINT32_S DataLen;                     /*数据长度*/
    UINT8_S  DestDevType;                 /*目标设备类型*/
    UINT8_S  DestDevId;                   /*目标设备ID*/
    UINT8_S  scanFlag;                   /* 已经被扫描过的标志 */
} DevComDataCellStruct;



/*数据环形队列结构体*/
typedef struct
{
    DevComDataCellStruct DataCellStru[DEV_TOTAL_FRAME_NUM]; /*环形结构中节点数据*/
    UINT32_S HeadIndex;                                          /*环形结构头指针*/
    UINT32_S TailIndex;                                          /*环形结构尾指针*/
    UINT32_S DataPkgCount;                                       /*环形结构中数据总数*/
} DevComCirQueueStruct;



#ifdef __cplusplus
extern "C" {
#endif
/*
* 功能描述：初始化设备配置信息结构
* 参数说明： 无
* 返回值  ：    1,成功，0，失败
*/
UINT8_S AdapterExtDevCfgInfoInit(void);


/*
* 功能描述：读取设备配置信息
* 参数说明： 
* 返回值  ： 1:成功  0,失败
*/
UINT8_S AdapterGetDevCfgDetail(void);

/*
*功能描述: 平台外部输入数据管理
*参数：
*返回值: 无
*/
void  AdapterExtDevInDataManage(void);

/*
*功能描述: 平台外部输出数据管理
*参数：
*返回值: 
*/
void AdapterExtDevOutDataManage(void);

/*
* 功能描述： 添加发送队列数据
* 参数说明： 
*            pDataBuf, 数据缓冲区
*            dataLen, 数据长度
*            destDevType,设备类型
*            destDevId,设备ID
* 返回值  ： 1: 成功
*            0: 失败
*/
UINT8_S AdapterAddDevSndQueData(const UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId);

/*
* 功能描述： 按照设备类型和设备编号扫描接收队列中的一包数据
* 参数说明： pDataBuf, 数据缓冲区
*            dataLen, 数据长度
*            destDevType,设备类型
*            destDevId,设备ID
* 返回值  ： 0: 失败
*            >0: 数据的字节长度
*/
UINT32_S AdapterScanDevRcvQueData(UINT8_S* pDataBuf, UINT32_S dataLen, const UINT8_S destDevType, const UINT8_S destDevId);

/*
* 功能描述： 顺序获取接收队列的一个数据包
* 参数说明： 
*              char* pDataBuf, 数据缓冲区
*              int dataLen, 数据长度    
*            pDevType,设备类型
*            pDevId,设备ID
* 返回值  ： 0: 失败
*              >0: 数据的字节长度
*/
UINT32_S AdapterGetDevRcvQuePkgData(UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S* pDevType,UINT8_S* pDevId);


/* 
* 功能描述：获取设备的通信状态记录标志
* 参数说明：devIndex 设备的索引
* 返回值  ：    1 有数据 0 无数据
*/
UINT8_S AdapterGetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId);

/* 
* 功能描述：设置网关的数量
* 参数说明：micrNum 网关设备的数量
* 返回值  ：    无
*/
void AdapterSetMicrNum(const UINT8_S micrNum);

#ifdef __cplusplus
}
#endif
#endif

