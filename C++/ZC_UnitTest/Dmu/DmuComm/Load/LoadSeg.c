/********************************************************
* 
* 文 件 名： LoadSeg.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入Seg数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadSeg.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入Seg数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadSegData(void)
{
    BnfSegStruct* BnfSegStru = NULL;/*Seg信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_SEG_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(SEG_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % SEG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SEG_LINE_BYTE_NUM);

                /*写入SEG信息结构体指针地址*/
                MallocSegDataStru(tempDataNum);
                BnfSegStru = GetSegData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfSegStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfSegStru[i].segId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*长度（cm)*/
                    BnfSegStru[i].length = LongFromChar(pTempData);            
                    pTempData += 4;
                    /*起点端点类型*/
                    BnfSegStru[i].startPointType = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*起点端点编号*/
                    BnfSegStru[i].startPointId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*终点端点类型*/
                    BnfSegStru[i].endPointType = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*终点端点编号*/
                    BnfSegStru[i].endPointId = ShortFromChar(pTempData);        
                    pTempData += 2;

                    /*起点正向相邻SegID*/
                    BnfSegStru[i].segStartJointMainSegId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*起点侧向相邻点SegID*/
                    BnfSegStru[i].segStartJointSideSegId = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*终点正向相邻点SegID*/
                    BnfSegStru[i].segTmnlJointMainSegId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*终点侧向相邻点SegID*/
                    BnfSegStru[i].segTmnlJointSideSegId = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*所属ZC区域ID*/
                    BnfSegStru[i].segManageZCId = ShortFromChar(pTempData);                
                    pTempData += 2;
                    /*所属ATS区域ID*/
                    BnfSegStru[i].segManageATSId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*所属物理CI区域ID*/ 
                    BnfSegStru[i].segManageCIId = ShortFromChar(pTempData);        
                    pTempData += 2;

                    /*限速信息属性*/
                    BnfSegStru[i].segResSpeed = *pTempData;        
                    pTempData += 1;
                    /*坡度信息属性*/ 
                    BnfSegStru[i].grade = *pTempData;        
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
