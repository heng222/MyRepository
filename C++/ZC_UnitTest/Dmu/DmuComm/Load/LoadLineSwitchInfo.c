/********************************************************
* 
* 文 件 名： LoadLineSwitchInfo.c 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入LineSwitchInfo数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadLineSwitchInfo.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入LineSwitchInfo数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadLineSwitchInfoData(void)
{
    BnfLineSwitchInfoStruct* BnfLineSwitchInfoStru = NULL;/*LineSwitchInfo信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(DIVIDPOINT_TYPE,DIVIDPOINT_LINRSWITCH_INFO_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(LINESWITCHINFO_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % LINESWITCHINFO_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / LINESWITCHINFO_LINE_BYTE_NUM);

                /*写入LINESWITCHINFO信息结构体指针地址*/
                MallocLineSwitchInfoDataStru(tempDataNum);
                BnfLineSwitchInfoStru = GetLineSwitchInfoData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfLineSwitchInfoStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfLineSwitchInfoStru[i].indexId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*切换线路移交ZCID*/
                    BnfLineSwitchInfoStru[i].lineSwitchTraZcId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*切换线路接管ZCID*/
                    BnfLineSwitchInfoStru[i].lineSwitchTakeOverZcId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*切换线路方向*/
                    BnfLineSwitchInfoStru[i].lineSwitchDir = *pTempData;
                    pTempData += 1;
                    /*切换线路起点所处seg编号*/
                    BnfLineSwitchInfoStru[i].startLineSwitchInfoId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*切换线路起点所处seg偏移*/
                    BnfLineSwitchInfoStru[i].startSegOffset = LongFromChar(pTempData);
                    pTempData += 4;
                    /*切换点所处seg编号*/
                    BnfLineSwitchInfoStru[i].switchPointSegId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*切换点所处seg偏移*/
                    BnfLineSwitchInfoStru[i].switchPointOffset = LongFromChar(pTempData);
                    pTempData += 4;
                    /*切换线路终点所处seg编号*/
                    BnfLineSwitchInfoStru[i].endLineSwitchInfoId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*切换线路终点所处seg偏移*/
                    BnfLineSwitchInfoStru[i].segEndOffset = LongFromChar(pTempData);
                    pTempData += 4;
                    /*切换点相关进路编号*/  
                    BnfLineSwitchInfoStru[i].relationRouteNum = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*切换线路内包含的道岔数目*/ 
                    BnfLineSwitchInfoStru[i].includeSwitchNum = ShortFromChar(pTempData);
                    pTempData += 2;
                    for(j = 0u;j < LINESWITCHINFO_SWITCH_NUM;j++)
                    {
                        /*道岔编号*/
                        BnfLineSwitchInfoStru[i].switchInfoStru[j].switchId = ShortFromChar(pTempData);
                        pTempData += 2;
                        /*道岔状态*/
                        BnfLineSwitchInfoStru[i].switchInfoStru[j].switchStatus = ShortFromChar(pTempData);
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
