/********************************************************
* 
* 文 件 名： LoadPhysicalSection.c 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入PhysicalSection数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadPhysicalSection.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入PhysicalSection数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadPhysicalSectionData(void)
{
    BnfPhysicalSectionStruct* BnfPhysicalSectionStru = NULL;/*PhysicalSection信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*道岔名称写入循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_PHYSICAL_SGMT_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(PHYSICALSECTION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % PHYSICALSECTION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / PHYSICALSECTION_LINE_BYTE_NUM);

                /*写入PHYSICALSECTION信息结构体指针地址*/
                MallocPhysicalSectionDataStru(tempDataNum);
                BnfPhysicalSectionStru = GetPhysicalSectionData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfPhysicalSectionStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfPhysicalSectionStru[i].physicalStcId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*名称*/
                    MemoryCpy(BnfPhysicalSectionStru[i].name,PHYSICALSECTION_NAME_BYTE_NUM,pTempData,PHYSICALSECTION_NAME_BYTE_NUM);
                    pTempData += PHYSICALSECTION_NAME_BYTE_NUM;

                    /*包含计轴区段数目*/     
                    BnfPhysicalSectionStru[i].includeAxleScNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*计轴编号*/
                    for(j = 0u;j < PHYSICALSECTION_AXLEID_MAX_NUM;j++)
                    {
                        BnfPhysicalSectionStru[i].axleIdBuff[j] = ShortFromChar(pTempData);                        
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
