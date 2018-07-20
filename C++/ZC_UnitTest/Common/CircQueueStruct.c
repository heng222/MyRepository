/********************************************************
*                                                                                                            
* 文 件 名： CircQueueStruct.cpp
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 郭文章
* 功能描述： 环形队列结构体  
* 修改记录：   
*
********************************************************/ 
#include "CircQueueStruct.h"







/*
* 功能描述： 添加队列数据
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针
*              CHAR_S* pDataBuf, 数据缓冲区
*              int dataLen, 数据长度
* 返回值  ： 0: 成功
*              -1: 失败
*/
INT8_S AddQueueData(CirQueueStruct* pCirQueueStru,const UINT8_S* pDataBuf,const UINT32_S dataLen)
{
    INT8_S retVal = 0;
    
    if ((pCirQueueStru != NULL) && (pDataBuf != NULL) && (dataLen > 0) && (dataLen <= DATA_LEN_MAX) && (pCirQueueStru->DataPkgCount != DATA_PACKAGE_MAX))
    {
        if (DATA_PACKAGE_MAX == pCirQueueStru->TailIndex)
        {
            pCirQueueStru->TailIndex = 0;
        }

        MemoryCpy(pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DataBuf, DATA_LEN_MAX, pDataBuf, dataLen); /*添加新数据*/

        pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DataLen = dataLen; /*记录添加的数据长度*/

        /*添加数据后处理尾索引*/
        pCirQueueStru->TailIndex++; /*增加尾索引*/
        pCirQueueStru->DataPkgCount++; /*增加数据包个数*/

        retVal = 0;
    }
    else
    {
        retVal = 1;
    }

    return retVal;
}


/*
* 功能描述： 获取队列数据包个数
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针    
* 返回值  ： 数据包个数
*/
UINT32_S GetQueuePkgCount(const CirQueueStruct* pCirQueueStru)
{
    UINT32_S retVal = 0u;
    if (pCirQueueStru != NULL)
    {
        retVal = pCirQueueStru->DataPkgCount; /*数据包个数*/
    }
    
    return retVal;
}


/*
* 功能描述： 获取队列数据包
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针
*              CHAR_S* pDataBuf, 数据缓冲区
*              int dataLen, 数据长度    
* 返回值  ： -1: 失败
*              >=0: 数据的字节长度
*/
UINT32_S GetQueuePkgData(CirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen)
{
    UINT32_S realDataLen = 0u; /*记录实际数据长度*/
    UINT32_S retVal = 0u;

    
    if ((pCirQueueStru != NULL) && (pDataBuf != NULL) && (dataLen > 0))
    {
        if (pCirQueueStru->DataPkgCount > 0)
        { /*数据包个数大于0*/

            realDataLen = pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DataLen; /*记录实际数据长度*/

            if ((realDataLen > 0) && (dataLen >= realDataLen))
            { /*实际数据长度有效 && 获取数据缓冲区长度有效 && 数据包个数大于0*/

                MemoryCpy(pDataBuf, dataLen, pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DataBuf, realDataLen); /*COPY数据*/

                pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DataLen = 0; /*数据长度清0*/

                /*提取数据后处理头索引*/
                pCirQueueStru->HeadIndex++;

                if (DATA_PACKAGE_MAX == pCirQueueStru->HeadIndex)
                {
                    pCirQueueStru->HeadIndex = 0;
                }

                pCirQueueStru->DataPkgCount--; /*减少数据包个数*/

                retVal = realDataLen;
            }
            else
            {
                retVal = 0u;
            }
        }
        else
        {
            retVal = 0u;
        }
    }
    else
    {
        retVal = 0u;
    }
    return retVal;
}




