/********************************************************
*                                                                                                            
* 文 件 名： CircQueueStruct.h
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 郭文章
* 功能描述： 环形队列结构体 
* 修改记录：   
*
********************************************************/
#ifndef CIRC_QUEUE_STRUCT_H_
#define CIRC_QUEUE_STRUCT_H_


#include "Copy.h"


#define DATA_PACKAGE_MAX              100u    /*数据包最大个数*/
#define DATA_LEN_MAX                  1400u   /*数据长度最大值*/



/*数据存储结构体*/
typedef struct
{
    UINT8_S DataBuf[DATA_LEN_MAX]; /*数据缓冲区*/
    UINT32_S DataLen; /*数据长度*/
} DataCellStruct;



/*数据环形队列结构体*/
typedef struct
{
    DataCellStruct DataCellStru[DATA_PACKAGE_MAX]; /*环形结构中节点数据*/
    UINT32_S HeadIndex; /*环形结构头指针*/
    UINT32_S TailIndex; /*环形结构尾指针*/
    UINT32_S DataPkgCount; /*环形结构中数据总数*/
} CirQueueStruct;



typedef CirQueueStruct QUEUESTRUCT;



#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 添加队列数据
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针
*              CHAR_S* pDataBuf, 数据缓冲区
*              int dataLen, 数据长度
* 返回值  ： 0: 成功
*              -1: 失败
*/
INT8_S AddQueueData(CirQueueStruct* pCirQueueStru, const UINT8_S* pDataBuf,const UINT32_S dataLen);

/*
* 功能描述： 获取队列数据包个数
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针   
* 返回值  ： -1: 失败
*              >=0: 数据包个数 
*/
UINT32_S GetQueuePkgCount(const CirQueueStruct* pCirQueueStru);

/*
* 功能描述： 获取队列数据包
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针
*              CHAR_S* pDataBuf, 数据缓冲区
*              int dataLen, 数据长度    
* 返回值  ： -1: 失败
*              >=0: 数据的字节长度
*/
UINT32_S GetQueuePkgData(CirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen);




#ifdef __cplusplus
}
#endif


#endif
