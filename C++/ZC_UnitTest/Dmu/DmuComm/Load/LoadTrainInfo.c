/********************************************************
* 
* 文 件 名： LoadTrainInfo.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入TrainInfo数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadTrainInfo.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入TrainInfo数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadTrainInfoData(void)
{
    BnfTrainInfoStruct* BnfTrainInfoStru = NULL;/*TrainInfo信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_TRAININFO_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(TRAININFO_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % TRAININFO_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / TRAININFO_LINE_BYTE_NUM);

                /*写入TRAININFO信息结构体指针地址*/
                MallocTrainInfoDataStru(tempDataNum);
                BnfTrainInfoStru = GetTrainInfoData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfTrainInfoStru != NULL);i++)
                {
                    /*列车车型*/
                    BnfTrainInfoStru[i].trainType = *pTempData;    
                    pTempData += 1;

                    /*列车长度*/
                    BnfTrainInfoStru[i].trainLength = ShortFromChar(pTempData);    
                    pTempData += 2;    

                    /*列车最大牵引加速度*/
                    BnfTrainInfoStru[i].trainMaxTracAcc = *pTempData;    
                    pTempData += 1;    

                    /*线路最大下坡坡度（线路夹角的正切值)*/
                    BnfTrainInfoStru[i].lineMaxGrade = ShortFromChar(pTempData);    
                    pTempData += 2;    

                    /*列车旋转质量系数*/
                    BnfTrainInfoStru[i].trainRotateRate = *pTempData;
                    pTempData += 1;

                    /*最不利情况下紧急制动减速度*/
                    BnfTrainInfoStru[i].trainWorstEbAcc = *pTempData;
                    pTempData += 1;

                    /*紧急制动建立等效时间。即滑行时间,单位:ms*/
                    BnfTrainInfoStru[i].timeEbBrakeBuild = ShortFromChar(pTempData);
                    pTempData += 2;

                     /*牵引切除延时。施加紧急制动时考虑的牵引切除延时,单位:ms*/
                    BnfTrainInfoStru[i].timeTracCut = ShortFromChar(pTempData);
                    pTempData += 2;

                    /*线路速度上限*/
                    BnfTrainInfoStru[i].maxLineLimitSpeed = *pTempData;
                    pTempData += 1;    
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
