/********************************************************
* 
* 文 件 名： LoadAr.c 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入Ar数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadAr.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入Ar数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadArData(void)
{
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/
    BnfArStruct* bnfArStru = NULL;/*Ar信息结构体指针*/
    

    /*获取数据*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_AR_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S) * (tempDataLen+50u));

        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(AR_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % AR_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / AR_LINE_BYTE_NUM);

                /*写入AR信息结构体指针地址*/
                MallocArDataStru(tempDataNum);
                bnfArStru = GetArData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(bnfArStru != NULL);i++)
                {
                    /*索引编号*/
                    bnfArStru[i].arId = ShortFromChar(pTempData);                        
                    pTempData += 2; 
                    /*无人折返出发站台编号*/
                    bnfArStru[i].startPlartformId = ShortFromChar(pTempData);                        
                    pTempData += 2; 
                    /*无人折返进入点对应停车点编号*/
                    bnfArStru[i].arInStopPointId = ShortFromChar(pTempData);                        
                    pTempData += 2; 
                    /*无人折返换端点对应停车点编号*/
                    bnfArStru[i].revertPointId = ShortFromChar(pTempData);                        
                    pTempData += 2; 
                    /*无人折返退出站台编号*/
                    bnfArStru[i].endPlartformId = ShortFromChar(pTempData);                        
                    pTempData += 2; 
                    /*无人折返退出点对应停车点编号*/
                    bnfArStru[i].aROutStopPointId = ShortFromChar(pTempData);                        
                    pTempData += 2;     
                    /*无人折返灯ID*/
                    bnfArStru[i].aRLampID = ShortFromChar(pTempData);                        
                    pTempData += 2;     
                    /*无人折返按钮ID*/
                    bnfArStru[i].aRButtonId = ShortFromChar(pTempData);                        
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
