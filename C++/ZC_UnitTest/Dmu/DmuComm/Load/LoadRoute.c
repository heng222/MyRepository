/********************************************************
* 
* 文 件 名： LoadRoute.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入Route数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadRoute.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入Route数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadRouteData(void)
{
    BnfRouteStruct* BnfRouteStru = NULL;/*Route信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_ROUTE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(ROUTE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % ROUTE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / ROUTE_LINE_BYTE_NUM);

                /*写入ROUTE信息结构体指针地址*/
                MallocRouteDataStru(tempDataNum);
                BnfRouteStru = GetRouteData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfRouteStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfRouteStru[i].routeId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*进路名称*/
                    MemoryCpy(BnfRouteStru[i].routeName,ROUTE_NAME_BYTE_LEN,pTempData,ROUTE_NAME_BYTE_LEN);
                    pTempData += ROUTE_NAME_BYTE_LEN;
                    /*进路性质*/
                    BnfRouteStru[i].routeType = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*起始信号机编号*/
                    BnfRouteStru[i].startSignalId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*终止信号机编号*/
                    BnfRouteStru[i].endSignalId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*包含计轴区段数目*/
                    BnfRouteStru[i].includeAxleSecNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*保护区段编号*/
                    for(j = 0u;j < ROUTE_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].AxleSec[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;  
                    }
                    /*保护区段数目*/
                    BnfRouteStru[i].protectSecNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*保护区段编号*/
                    for(j = 0u;j < ROUTE_PROTECT_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].protectSecId[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;  
                    }

                    /*点式接近区段数目*/    
                    BnfRouteStru[i].blogAccessSegNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*点式接近区段编号*/
                    for(j = 0u;j < ROTRE_ACCESS_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].blogAccessSegId[j] = ShortFromChar(pTempData);                        
                        pTempData += 2; 
                    }
                    /*CBTC接近区段数目*/
                    BnfRouteStru[i].cbtcAccessSegNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*CBTC接近区段编号*/
                    for(j = 0u;j < ROTRE_ACCESS_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].cbtcAccessSegId[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;  
                    }

                    /*点式触发区段数量*/
                    BnfRouteStru[i].blocTrgAreaNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*点式触发区段ID*/
                    for(j = 0u;j < ROUTE_TRG_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].blocTrgAreaId[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;   
                    }

                    /*CBTC触发区段数量*/
                    BnfRouteStru[i].cbtcTrgAreaNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*CBTC触发区段ID*/
                    for(j = 0u;j < ROUTE_TRG_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].cbtcTrgAreaId[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;  
                    }
                    /*所属CI区域编号*/
                    BnfRouteStru[i].manageCI = ShortFromChar(pTempData);                        
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
