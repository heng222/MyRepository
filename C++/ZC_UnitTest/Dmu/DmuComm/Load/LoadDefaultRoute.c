/********************************************************
* 
* 文 件 名： LoadDefaultRoute.c 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入DefaultRoute数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadDefaultRoute.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入DefaultRoute数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadDefaultRouteData(void)
{
    BnfDefaultRouteStruct* BnfDefaultRouteStru = NULL;/*DefaultRoute信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_DEFAULT_ROUTE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(DEFAULTROUTE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % DEFAULTROUTE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / DEFAULTROUTE_LINE_BYTE_NUM);

                /*写入DEFAULTROUTE信息结构体指针地址*/
                MallocDefaultRouteDataStru(tempDataNum);
                BnfDefaultRouteStru = GetDefaultRouteData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfDefaultRouteStru != NULL);i++)
                {
                    BnfDefaultRouteStru[i].indexId = ShortFromChar(pTempData);                        /*索引编号*/
                    pTempData += 2;

                    BnfDefaultRouteStru[i].segId = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    BnfDefaultRouteStru[i].dir = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    BnfDefaultRouteStru[i].arriveStaId = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    BnfDefaultRouteStru[i].aimStaId = ShortFromChar(pTempData);                    
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
