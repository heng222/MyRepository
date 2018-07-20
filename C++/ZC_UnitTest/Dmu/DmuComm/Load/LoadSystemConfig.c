/********************************************************
* 
* 文 件 名： LoadSystemConfig.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入SystemConfig数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadSystemConfig.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入SystemConfig数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadSystemConfigData(void)
{
    BnfSystemConfigStruct* BnfSystemConfigStru = NULL;/*SystemConfig信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_CONFIGDATA_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(SYSTEMCONFIG_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % SYSTEMCONFIG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SYSTEMCONFIG_LINE_BYTE_NUM);

                /*写入SYSTEMCONFIG信息结构体指针地址*/
                MallocSystemConfigDataStru(tempDataNum);
                BnfSystemConfigStru = GetSystemConfigData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfSystemConfigStru != NULL);i++)
                {
                    /*系统运行最高速度*/
                    BnfSystemConfigStru[i].maxLineLimitSpeed = *pTempData;    
                    pTempData += 1;

                    /*临时限速最高限速*/
                    BnfSystemConfigStru[i].maxTsrSpeed = *pTempData;    
                    pTempData += 1;

                    /*NTP校时时区差*/
                    BnfSystemConfigStru[i].mimeZoneDifference = *pTempData;    
                    pTempData += 1;

                    /*安全防护距离*/
                    BnfSystemConfigStru[i].safeBackDistance = ShortFromChar(pTempData);    
                    pTempData += 2;    

                    /*系统定义最大保护区段长度*/
                    BnfSystemConfigStru[i].maxOverlapLength = ShortFromChar(pTempData);    
                    pTempData += 2;    

                    /*seg逻辑方向上下行*/
                    BnfSystemConfigStru[i].segLogicDirUpAndDown = *pTempData;    
                    pTempData += 1;    

                    /*RM限速值*/
                    BnfSystemConfigStru[i].rmLimitSpeed = ShortFromChar(pTempData);    
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
