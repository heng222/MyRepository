/********************************************************
* 
* 文 件 名： LoadSystemRailInfo.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入SystemRailInfo数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadSystemRailInfo.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入SystemRailInfo数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadSystemRailInfoData(void)
{
    BnfSystemRailInfoStruct* BnfSystemRailInfoStru = NULL;/*SystemRailInfo信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_RAILINFO_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(SYSTEMRAILINFO_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % SYSTEMRAILINFO_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SYSTEMRAILINFO_LINE_BYTE_NUM);

                /*写入SYSTEMRAILINFO信息结构体指针地址*/
                MallocSystemRailInfoDataStru(tempDataNum);
                BnfSystemRailInfoStru = GetSystemRailInfoData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfSystemRailInfoStru != NULL);i++)
                {
                    /*车头前方最差坡度计算范围*/
                    BnfSystemRailInfoStru[i].disFrontToGetGrade = LongFromChar(pTempData);
                    pTempData += 4;
                    /*车身最差坡度计算范围*/
                    BnfSystemRailInfoStru[i].disBetweenToGetGrade = ShortFromChar(pTempData);
                    pTempData += 2;    
                    /*推荐速度与EBI的最小差值(km/h)*/
                    BnfSystemRailInfoStru[i].minMarginFromEBI = *pTempData;
                    pTempData += 1;    
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
