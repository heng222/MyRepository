/********************************************************
* 
* 文 件 名： LoadBlocApptchSection.c 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入BlocApptchSection数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadBlocApptchSection.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入BlocApptchSection数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadBlocApptchSectionData(void)
{
    BnfBlocApptchSectionStruct* BnfBlocApptchSectionStru = NULL;/*BlocApptchSection信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_BLOC_APPTCH_SECTION_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(BLOCAPPTCHSECTION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % BLOCAPPTCHSECTION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / BLOCAPPTCHSECTION_LINE_BYTE_NUM);

                /*写入BLOCAPPTCHSECTION信息结构体指针地址*/
                MallocBlocApptchSectionDataStru(tempDataNum);
                BnfBlocApptchSectionStru = GetBlocApptchSectionData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfBlocApptchSectionStru != NULL);i++)
                {
                    BnfBlocApptchSectionStru[i].blocApptchSectionId = ShortFromChar(pTempData);                        /*索引编号*/
                    pTempData += 2;

                    BnfBlocApptchSectionStru[i].includeAxleSgmtNum = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    for (j = 0u;j < BLOCAPPTCHSECTION_AXLESGM_MAX_NUM; j++)
                    {
                        BnfBlocApptchSectionStru[i].includeAxleSgmtId[j] = ShortFromChar(pTempData);                    
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
