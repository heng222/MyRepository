/********************************************************
* 
* 文 件 名： LoadStopPoint.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入StopPoint数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadStopPoint.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入StopPoint数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadStopPointData(void)
{
    BnfStopPointStruct* BnfStopPointStru = NULL;/*StopPoint信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_STOPPOINT_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(STOPPOINT_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % STOPPOINT_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / STOPPOINT_LINE_BYTE_NUM);

                /*写入STOPPOINT信息结构体指针地址*/
                MallocStopPointDataStru(tempDataNum);
                BnfStopPointStru = GetStopPointData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfStopPointStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfStopPointStru[i].stopPointId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*停车点属性*/
                    BnfStopPointStru[i].attribute = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*停车点作用方向(16进制)*/
                    BnfStopPointStru[i].dir = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*停车点所处seg编号*/
                    BnfStopPointStru[i].segId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*停车点Seg偏移量*/
                    BnfStopPointStru[i].segOfst = LongFromChar(pTempData);                        
                    pTempData += 4;

                    /*停车点对应ATO作用窗范围*/
                    BnfStopPointStru[i].aTOParkArea = LongFromChar(pTempData);                        
                    pTempData += 4;
                    /*停车点对应ATP作用窗范围*/
                    BnfStopPointStru[i].aTPParkArea = LongFromChar(pTempData);                        
                    pTempData += 4;
                }
            }
            else
            {
                /*数据长度错误*/
                retVal = -1;
            }
        
        }
    }

    return retVal;
}
