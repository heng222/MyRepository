/********************************************************
* 
* 文 件 名： LoadSwitch.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述：  载入Switch数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadSwitch.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入Switch数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadSwitchData(void)
{
    BnfSwitchStruct* BnfSwitchStru = NULL;/*Switch信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_SWITCH_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(SWITCH_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % SWITCH_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SWITCH_LINE_BYTE_NUM);

                /*写入SWITCH信息结构体指针地址*/
                MallocSwitchDataStru(tempDataNum);
                BnfSwitchStru = GetSwitchData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfSwitchStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfSwitchStru[i].switchId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*道岔名称*/
                    MemoryCpy(BnfSwitchStru[i].switchName,SWITCH_NAME_LEN,pTempData,SWITCH_NAME_LEN);
                    pTempData += SWITCH_NAME_LEN;

                    /*联动道岔编号*/     
                    BnfSwitchStru[i].switchOtherId = ShortFromChar(pTempData);          
                    pTempData += 2;  
                    /*方向*/
                    BnfSwitchStru[i].dir = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*定位SegID*/
                    BnfSwitchStru[i].locSegId = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*反位SegID*/
                    BnfSwitchStru[i].antiSegId = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*汇合SegID*/
                    BnfSwitchStru[i].joinSegId = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*道岔侧向静态限速*/
                    BnfSwitchStru[i].switchSideResSpeed = ShortFromChar(pTempData);           /*道岔侧向静态限速*/
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
