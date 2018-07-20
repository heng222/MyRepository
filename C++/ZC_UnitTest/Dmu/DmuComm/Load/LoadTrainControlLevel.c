/********************************************************
* 
* 文 件 名： LoadTrainControlLevel.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入TrainControlLevel数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadTrainControlLevel.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入TrainControlLevel数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadTrainControlLevelData(void)
{
    BnfTrainControlLevelStruct* BnfTrainControlLevelStru = NULL;/*TrainControlLevel信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_TRAIN_CONTROL_LEVEL_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(TRAINCONTROLLEVEL_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % TRAINCONTROLLEVEL_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / TRAINCONTROLLEVEL_LINE_BYTE_NUM);

                /*写入TRAINCONTROLLEVEL信息结构体指针地址*/
                MallocTrainControlLevelDataStru(tempDataNum);
                BnfTrainControlLevelStru = GetTrainControlLevelData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfTrainControlLevelStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfTrainControlLevelStru[i].indexId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*起点所处seg编号*/
                    BnfTrainControlLevelStru[i].startSegId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*起点所处Seg偏移量*/
                    BnfTrainControlLevelStru[i].startOffset = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*终点所处seg编号*/
                    BnfTrainControlLevelStru[i].endSegId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*终点所处Seg偏移量*/
                    BnfTrainControlLevelStru[i].endOffset = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*非CBTC区域列车运行方向*/
                    BnfTrainControlLevelStru[i].dir = ShortFromChar(pTempData);    
                    pTempData += 2;

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
