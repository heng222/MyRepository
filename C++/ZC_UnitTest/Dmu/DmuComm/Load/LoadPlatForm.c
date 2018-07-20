/********************************************************
* 
* 文 件 名： LoadPlatForm.c 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入PlatForm数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadPlatForm.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入PlatForm数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadPlatFormData(void)
{
    BnfPlatFormStruct* BnfPlatFormStru = NULL;/*PlatForm信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_PLATFORM_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(PLATFORM_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % PLATFORM_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / PLATFORM_LINE_BYTE_NUM);

                /*写入PLATFORM信息结构体指针地址*/
                MallocPlatFormDataStru(tempDataNum);
                BnfPlatFormStru = GetPlatFormData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfPlatFormStru != NULL);i++)
                {
                    /*站台ID*/
                    BnfPlatFormStru[i].platFormId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*站台中心公里标*/
                    MemoryCpy(BnfPlatFormStru[i].platFormKillPost,PLATFORM_NAME_BYTE_LEN,pTempData,PLATFORM_NAME_BYTE_LEN);
                    pTempData += PLATFORM_NAME_BYTE_LEN;

                    /*站台关联seg编号*/
                    BnfPlatFormStru[i].segId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*逻辑方向上站台相对于停车区域的方向*/
                    BnfPlatFormStru[i].dir = *pTempData;    
                    pTempData++;
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
