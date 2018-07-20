/********************************************************
* 
* 文 件 名： LoadExitCbtcSection.c 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入ExitCbtcSection数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadExitCbtcSection.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入ExitCbtcSection数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadExitCbtcSectionData(void)
{
    BnfExitCbtcSectionStruct* BnfExitCbtcSectionStru = NULL;/*ExitCbtcSection信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_EXIT_CBTC_SECTION_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(EXITCBTCSECTION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % EXITCBTCSECTION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / EXITCBTCSECTION_LINE_BYTE_NUM);

                /*写入EXITCBTCSECTION信息结构体指针地址*/
                MallocExitCbtcSectionDataStru(tempDataNum);
                BnfExitCbtcSectionStru = GetExitCbtcSectionData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfExitCbtcSectionStru != NULL);i++)
                {
                    BnfExitCbtcSectionStru[i].indexId = ShortFromChar(pTempData);                        /*索引编号*/
                    pTempData += 2;

                    BnfExitCbtcSectionStru[i].dir = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    BnfExitCbtcSectionStru[i].attribute = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    BnfExitCbtcSectionStru[i].startOffset = LongFromChar(pTempData);                    
                    pTempData += 4;

                    BnfExitCbtcSectionStru[i].endOffSet = LongFromChar(pTempData);                    
                    pTempData += 4;

                    BnfExitCbtcSectionStru[i].segNum = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    for(j = 0u;j < EXITCBTCSECTION_SEG_MAX_NUM;j++)
                    {
                        BnfExitCbtcSectionStru[i].segInfoBuff[j] = ShortFromChar(pTempData);                    
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
