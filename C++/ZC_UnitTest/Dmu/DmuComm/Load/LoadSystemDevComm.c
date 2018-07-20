/********************************************************
* 
* 文 件 名： LoadSystemDevComm.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入SystemDevComm数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadSystemDevComm.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入SystemDevComm数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadSystemDevCommData(void)
{
    BnfSystemDevCommStruct* BnfSystemDevCommStru = NULL;/*SystemDevComm信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S  j = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_DEV_COMM_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(SYSTEMDEVCOMM_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % SYSTEMDEVCOMM_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SYSTEMDEVCOMM_LINE_BYTE_NUM);

                /*写入SYSTEMDEVCOMM信息结构体指针地址*/
                MallocSystemDevCommDataStru(tempDataNum);
                BnfSystemDevCommStru = GetSystemDevCommData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfSystemDevCommStru != NULL);i++)
                {
                    
                    /*本设备编号(Device_Type+Device_ID)*/    
                    BnfSystemDevCommStru[i].devName = ShortFromChar(pTempData);
                    pTempData += 2;    

                    /*通信对象数量*/
                    BnfSystemDevCommStru[i].commObjectNum = ShortFromChar(pTempData);
                    pTempData += 2;    

                    /*通信对象编号(Device_Type+Device_ID)*/
                    for (j = 0u; j < SYSTEMDEVCOMM_COMMOBJECT_MAX_NUM; j++)
                    {
                        BnfSystemDevCommStru[i].commObjectIdBuff[j] = ShortFromChar(pTempData);
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
