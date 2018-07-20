/********************************************************
* 
* 文 件 名： LoadStopSection.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入StopSection数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadStopSection.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入StopSection数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadStopSectionData(void)
{
    BnfStopSectionStruct* BnfStopSectionStru = NULL;/*StopSection信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_STOPSECTION_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(STOPSECTION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % STOPSECTION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / STOPSECTION_LINE_BYTE_NUM);

                /*写入STOPSECTION信息结构体指针地址*/
                MallocStopSectionDataStru(tempDataNum);
                BnfStopSectionStru = GetStopSectionData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfStopSectionStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfStopSectionStru[i].stopSectionId = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*所属车站名称*/
                    MemoryCpy(BnfStopSectionStru[i].stationName,STOPSECTION_STATION_NAME_LEN,pTempData,STOPSECTION_STATION_NAME_LEN);
                    pTempData +=STOPSECTION_STATION_NAME_LEN;
                    /*目的地编号*/
                    MemoryCpy(BnfStopSectionStru[i].bDesId,STOPSECTION_DEST_CODE_LEN,pTempData,STOPSECTION_DEST_CODE_LEN);
                    pTempData +=STOPSECTION_DEST_CODE_LEN;
                    /*停车区域seg编号*/
                    BnfStopSectionStru[i].segId = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*停车区域属性*/
                    BnfStopSectionStru[i].sttribute = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*站台最小停站时间*/
                    BnfStopSectionStru[i].minParkTime = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*站台最大停站时间*/
                    BnfStopSectionStru[i].maxParkTime = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*站台默认停站时间*/
                    BnfStopSectionStru[i].parkTime = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*站台开门方式*/
                    BnfStopSectionStru[i].doorOpenMode = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*站台开门时间间隔*/
                    BnfStopSectionStru[i].doorOpenTime = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*站台关门方式*/
                    BnfStopSectionStru[i].doorCloseMode = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*站台关门时间间隔*/
                    BnfStopSectionStru[i].doorCloseTime = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*站台默认停稳时间*/
                    BnfStopSectionStru[i].parkSteadyTime = ShortFromChar(pTempData);    
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
