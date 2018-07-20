/********************************************************
* 
* 文 件 名： LoadPoint.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入Point数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadPoint.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入Point数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadPointData(void)
{
    BnfPointStruct* BnfPointStru = NULL;/*Point信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_POINT_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(POINT_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % POINT_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / POINT_LINE_BYTE_NUM);

                /*写入POINT信息结构体指针地址*/
                MallocPointDataStru(tempDataNum);
                BnfPointStru = GetPointData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfPointStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfPointStru[i].indexId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*名称*/
                    MemoryCpy(BnfPointStru[i].name,POINT_MAX_NAME_LEN,pTempData,POINT_MAX_NAME_LEN);
                    pTempData += POINT_MAX_NAME_LEN;
                    /*起点轨道名称*/
                    MemoryCpy(BnfPointStru[i].startPathwayName,POINT_MAX_NAME_LEN,pTempData,POINT_MAX_NAME_LEN);
                    pTempData += POINT_MAX_NAME_LEN;
                    /*公里标(cm)*/
                    BnfPointStru[i].location = LongFromChar(pTempData);                
                    pTempData += 4;
                    /*点类型*/  
                    BnfPointStru[i].pointType = ShortFromChar(pTempData);            
                    pTempData += 2;

                    /*起点正向相邻点ID*/
                    BnfPointStru[i].startJointMainLkId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*起点侧向相邻点ID*/
                    BnfPointStru[i].startJointSideLkId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*终点正向相邻点ID*/
                    BnfPointStru[i].tmnlJointMainLkId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*终点侧向相邻点ID*/
                    BnfPointStru[i].tmnlJointSideLkId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*所属ZC区域编号*/
                    BnfPointStru[i].manageZCId = ShortFromChar(pTempData);                
                    pTempData += 2;
                    /*所属ATS区域编号*/
                    BnfPointStru[i].manageATSId = ShortFromChar(pTempData);                
                    pTempData += 2;
                    /*所属物理CI区域编号*/ 
                    BnfPointStru[i].manageCIId = ShortFromChar(pTempData);        
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
