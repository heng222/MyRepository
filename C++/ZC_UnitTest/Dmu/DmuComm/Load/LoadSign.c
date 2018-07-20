/********************************************************
* 
* 文 件 名： LoadSign.c  
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入Sign数据 
* 备    注： 无 
* 
********************************************************/ 

#include "LoadSign.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入Sign数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadSignData(void)
{
    BnfSignStruct* BnfSignStru = NULL;/*Sign信息结构体指针*/
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S* pTempData = NULL;/*临时存储数据*/
    UINT8_S indexId = 0u;/*结构体下标*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*数据表的行数*/
    UINT16_S i = 0u;/*循环使用*/

    /*获取数据*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_SIGNAL_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(SIGN_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0u == (tempDataLen % SIGN_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SIGN_LINE_BYTE_NUM);

                /*写入SIGN信息结构体指针地址*/
                MallocSignDataStru(tempDataNum);
                BnfSignStru = GetSignData();

                /*数据有效开始写入结构体*/
                for(i = 0u;(i < tempDataNum)&&(BnfSignStru != NULL);i++)
                {
                    /*索引编号*/
                    BnfSignStru[i].signId = ShortFromChar(pTempData);                        
                    pTempData += 2;
        
                    /*信号机名称*/
                    MemoryCpy(BnfSignStru[i].signName,SIGN_NAME_LEN,pTempData,SIGN_NAME_LEN);
                    pTempData += SIGN_NAME_LEN;

                    /*类型*/
                    BnfSignStru[i].signType = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*属性*/
                    BnfSignStru[i].signProperty = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*所处seg编号*/     
                    BnfSignStru[i].signProtectSegId = ShortFromChar(pTempData);          
                    pTempData += 2;  
                    
                    /*所处Seg偏移量（cm）*/
                    BnfSignStru[i].signProtectSegOffset = LongFromChar(pTempData); 
                    pTempData += 4;
                    /*防护方向*/
                    BnfSignStru[i].protectiveDir =  *pTempData;          
                    pTempData += 1;  
                    /*灯列信息*/
                    BnfSignStru[i].lightInfo = LongFromChar(pTempData); 
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
