/********************************************************
*                                                                                                            
* 文 件 名： AdptAppExtDevDataInterface.h   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 适配层对应用层通信接口结构处理的接口头文件 
* 备    注： 无 
*
********************************************************/ 

#ifndef ADPT_APP_ExtDev_DATA_INTERFACE_H_
#define ADPT_APP_ExtDev_DATA_INTERFACE_H_


#include "../../Common/Copy.h"
#include "../../Common/CommonTypes.h"


#define COM_WITHOUT_PRO       0u            /* 通信不需要通过协议 */
#define COM_WITH_RSSP         1u            /* 通信需要通过RSSP协议 */

#define RCV_ERROR          0xFFFFFFFFu   /* 应用获取数据但是数据为无效内容 */

typedef struct ComProCfg
{
    UINT8_S comSrcType;
    UINT8_S comDstType;
    UINT8_S protocolFlag;
}ComProCfgStruct;



#ifdef __cplusplus
extern "C" {
#endif

UINT8_S AdptAppExtDevSndData( UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId);

/*
* 功能描述： 获取队列数据
* 参数说明： 
*              char* pDataBuf, 数据缓冲区
*              int dataLen, 数据缓冲区长度
* 返回值  ： 1: 成功
*            0: 失败
*/
UINT32_S AdptAppExtDevRcvData(UINT8_S* pDataBuf, const UINT32_S dataLen, UINT8_S *pDevType, UINT8_S *pDevId);

/* 
* 功能描述：获取设备的通信状态记录标志
* 参数说明：
* 返回值  ：    1 有数据 0 无数据
*/
UINT8_S AdptAppGetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId);


#ifdef __cplusplus
}
#endif


#endif
