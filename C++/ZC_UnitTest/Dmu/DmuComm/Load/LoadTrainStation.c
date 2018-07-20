/********************************************************
* 
* 文 件 名： LoadTrainStation.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入TrainStation数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadTrainStation.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入TrainStation数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadTrainStationData(void)
{
    BnfTrainStationStruct* BnfTrainStationStru = NULL;/*TrainStation信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_TRAIN_STATION_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(TRAINSTATION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % TRAINSTATION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / TRAINSTATION_LINE_BYTE_NUM);

                /*写入TRAINSTATION信息结构体指针地址*/
                MallocTrainStationDataStru(tempDataNum);
                BnfTrainStationStru = GetTrainStationData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfTrainStationStru != NULL);i++)
                {
                    /*车站ID*/
                    BnfTrainStationStru[i].stationId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*车站名称*/
                    MemoryCpy(BnfTrainStationStru[i].name,TRAINSTATION_NAME_BYTE_LEN,pTempData,TRAINSTATION_NAME_BYTE_LEN);
                    pTempData += TRAINSTATION_NAME_BYTE_LEN;
                    /*车站包含站台数目*/
                    BnfTrainStationStru[i].includeStationNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*站台编号*/
                    for(j =0u;j < TRAINSTATION_ID_MAX_NUM;j++)
                    {
                        BnfTrainStationStru[i].stationIdBuff[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;
                    }
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
