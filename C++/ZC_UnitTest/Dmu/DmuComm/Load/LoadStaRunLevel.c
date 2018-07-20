/********************************************************
* 
* 文 件 名： LoadStaRunLevel.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入StaRunLevel数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadStaRunLevel.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入StaRunLevel数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadStaRunLevelData(void)
{
    BnfStaRunLevelStruct* BnfStaRunLevelStru = NULL;/*StaRunLevel信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_STA_RUN_LEVEL_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(STARUNLEVEL_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % STARUNLEVEL_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / STARUNLEVEL_LINE_BYTE_NUM);

                /*写入STARUNLEVEL信息结构体指针地址*/
                MallocStaRunLevelDataStru(tempDataNum);
                BnfStaRunLevelStru = GetStaRunLevelData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfStaRunLevelStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfStaRunLevelStru[i].indexId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*起点目的地编号*/
                    BnfStaRunLevelStru[i].startDestId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*终点目的地编号*/
                    BnfStaRunLevelStru[i].endDestId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*运行级别分级数目*/
                    BnfStaRunLevelStru[i].runLevelNum = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    for (j = 0u; j < STARUNLEVEL_LEVEL_NUM; j++)
                    {
                        /*级别编号*/
                        BnfStaRunLevelStru[i].runLevelStru[j].levelId = ShortFromChar(pTempData);                        
                        pTempData += 2;

                        /*级别1对应时间*/
                        BnfStaRunLevelStru[i].runLevelStru[j].levelTime = ShortFromChar(pTempData);                        
                        pTempData += 2;

                        /*级别1对应速度*/
                        BnfStaRunLevelStru[i].runLevelStru[j].levelSpeed = ShortFromChar(pTempData);                        
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
