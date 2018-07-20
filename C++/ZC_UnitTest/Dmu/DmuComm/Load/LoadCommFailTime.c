/********************************************************
* 
* 文 件 名： LoadCommFailTime.c 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入CommFailTime数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadCommFailTime.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入CommFailTime数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadCommFailTimeData(void)
{
    BnfCommFailTimeStruct* BnfCommFailTimeStru = NULL;/*CommFailTime信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_COMMFAILTIME_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(COMMFAILTIME_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % COMMFAILTIME_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / COMMFAILTIME_LINE_BYTE_NUM);

                /*写入COMMFAILTIME信息结构体指针地址*/
                MallocCommFailTimeDataStru(tempDataNum);
                BnfCommFailTimeStru = GetCommFailTimeData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfCommFailTimeStru != NULL);i++)
                {
                    /*ATP至ZC通信故障时间*/
                    BnfCommFailTimeStru[i].atpToZcCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ZC至ATP通信故障时间*/
                    BnfCommFailTimeStru[i].zcToAtpCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;
                    

                    /*ATP至CI通信故障时间*/
                    BnfCommFailTimeStru[i].atpToCiCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*CI至ATP通信故障时间*/
                    BnfCommFailTimeStru[i].ciToAtpCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ATP至ATS通信故障时间*/
                    BnfCommFailTimeStru[i].atpToAtsCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ATS至ATP通信故障时间*/
                    BnfCommFailTimeStru[i].atsToAtpCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ZC至DMS通信故障时间*/
                    BnfCommFailTimeStru[i].zcToDmsCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*DMS至ZC通信故障时间*/
                    BnfCommFailTimeStru[i].dmsToZcCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ZC至CI通信故障时间*/
                    BnfCommFailTimeStru[i].zcToCiCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;
                    
                    /*CI至ZC通信故障时间*/
                    BnfCommFailTimeStru[i].ciToZcCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*DMS至ATS通信故障时间*/
                    BnfCommFailTimeStru[i].dmsToAtsCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ATS至DMS通信故障时间*/
                    BnfCommFailTimeStru[i].atsToDmsCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ZC至ATS通信故障时间*/
                    BnfCommFailTimeStru[i].zcToAtsCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ZC至ZC通信故障时间*/
                    BnfCommFailTimeStru[i].zcToZcCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*CI至CI通信故障时间*/
                    BnfCommFailTimeStru[i].ciToCiCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

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
