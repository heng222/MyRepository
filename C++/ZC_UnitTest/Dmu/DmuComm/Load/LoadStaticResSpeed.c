/********************************************************
* 
* 文 件 名： LoadStaticResSpeed.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入StaticResSpeed数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadStaticResSpeed.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入StaticResSpeed数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadStaticResSpeedData(void)
{
    BnfStaticResSpeedStruct* BnfStaticResSpeedStru = NULL;/*StaticResSpeed信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_STATIC_RES_SPEED_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(STATICRESSPEED_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % STATICRESSPEED_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / STATICRESSPEED_LINE_BYTE_NUM);

                /*写入STATICRESSPEED信息结构体指针地址*/
                MallocStaticResSpeedDataStru(tempDataNum);
                BnfStaticResSpeedStru = GetStaticResSpeedData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfStaticResSpeedStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfStaticResSpeedStru[i].staticResSpeedId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*该限速区域所处Seg编号*/
                    BnfStaticResSpeedStru[i].segId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*起点所处Seg偏移量(cm)*/
                    BnfStaticResSpeedStru[i].orgnSegOfst = LongFromChar(pTempData);                        
                    pTempData += 4;
                    /*终点所处Seg偏移量(cm)*/
                    BnfStaticResSpeedStru[i].tmnlSegOfst = LongFromChar(pTempData);                        
                    pTempData += 4;

                    /*关联道岔ID*/
                    BnfStaticResSpeedStru[i].relateSwitchId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*静态限速值*/
                    BnfStaticResSpeedStru[i].staticSpeed = ShortFromChar(pTempData);                        
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
