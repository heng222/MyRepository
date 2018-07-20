/********************************************************
* 
* 文 件 名： LoadBlocTrgZone.c 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入BlocTrgZone数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadBlocTrgZone.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入BlocTrgZone数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadBlocTrgZoneData(void)
{
    BnfBlocTrgZoneStruct* BnfBlocTrgZoneStru = NULL;/*BlocTrgZone信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_BLOC_TRG_ZONE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));

        /*获取数据*/
        retVal = GetConfigData(BLOCTRGZONE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

        if(NULL != pTempData)
        {
            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % BLOCTRGZONE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / BLOCTRGZONE_LINE_BYTE_NUM);

                /*写入BLOCTRGZONE信息结构体指针地址*/
                MallocBlocTrgZoneDataStru(tempDataNum);
                BnfBlocTrgZoneStru = GetBlocTrgZoneData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfBlocTrgZoneStru != NULL);i++)
                {
                    BnfBlocTrgZoneStru[i].blocApptchSectionId = ShortFromChar(pTempData);                        /*索引编号*/
                    pTempData += 2;

                    BnfBlocTrgZoneStru[i].includeAxleSgmtNum = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    for (j = 0u;j < BLOCTRGZONE_AXLESGM_MAX_NUM; j++)
                    {
                        BnfBlocTrgZoneStru[i].includeAxleSgmtId[j] = ShortFromChar(pTempData);                    
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
