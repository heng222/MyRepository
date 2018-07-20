/*******************************************
 * 文件名	：  LoadZcSystemConfig.h
 * 版权说明	：  北京三模科技有限公司
 * 版本号	：  1.0  
 * 创建时间	：  2015-5-25
 * 功能描述	：	载入ZcSystemConfig数据
 * 使用注意	：  
 * 修改记录	：	
*******************************************/
#include "LoadZcSystemConfig.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* 功能描述： 载入ZcSystemConfig数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadZcSystemConfigData(void)
{
	INT8_S retVal = 0;/*函数返回值*/
	UINT8_S* pTempData = NULL;/*临时存储数据*/
	UINT8_S indexId = 0U;/*结构体下标*/
	UINT32_S tempDataLen = 0U;
	UINT16_S tempDataNum = 0U;/*数据表的行数*/
	UINT16_S i = 0U;/*循环使用*/
    BnfZcSystemConfigStruct* BnfZcSystemConfigStru = NULL;/*ZcSystemConfig信息结构体指针*/

	/*获取数据*/
	retVal = GetConfigDataLen(((UINT8_S)(ZC_CONFIG_TYPE)),((UINT8_S)(ZC_SYSTEM_CONFIG_DATA_ID)),&tempDataLen,&indexId);

	if((0 == retVal)&&(((UINT16_S)tempDataLen) > 0U))
	{
		pTempData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(UINT32_S)(tempDataLen+50U));

        if (NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(((UINT16_S)(ZCSYSTEMCONFIG_LINE_BYTE_NUM)),tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0U == (UINT16_S)(tempDataLen % ZCSYSTEMCONFIG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / ZCSYSTEMCONFIG_LINE_BYTE_NUM);

                /*写入ZCSYSTEMCONFIG信息结构体指针地址*/
                MallocZcSystemConfigDataStru(tempDataNum);
                BnfZcSystemConfigStru = GetZcSystemConfigData();

                /*数据有效开始写入结构体*/
                for(i = 0U;(i < tempDataNum)&&(BnfZcSystemConfigStru != NULL);i++)
                {
                    /*列车最大退行距离（ms）*/
                    BnfZcSystemConfigStru[i].trainMaxRecedeDis = ShortFromChar(pTempData);						
                    pTempData += 2U;

                    /*线路最小可能车长(cm)*/
                    BnfZcSystemConfigStru[i].lineMinTrainLength = ShortFromChar(pTempData);						
                    pTempData += 2U;

                    /*运营要求的点灯区段长度(cm)*/
                    BnfZcSystemConfigStru[i].sectionLength = LongFromChar(pTempData);						
                    pTempData += 4U;

                    /*前端筛选计轴区段数量*/
                    BnfZcSystemConfigStru[i].axleSectionNum = ShortFromChar(pTempData);						
                    pTempData += 2U;

                    /*计轴区段非通信车占用冗余判断时间（ms）*/
                    BnfZcSystemConfigStru[i].redunJudgmentTime = LongFromChar(pTempData);						
                    pTempData += 4U;

                    /*ZC-CI逻辑区段占用空闲码位个数开关*/
                    BnfZcSystemConfigStru[i].freeCodeNumSwitch = *pTempData;						
                    pTempData += 1U;

                    /*列车CBTC折返时间（ms）*/
                    BnfZcSystemConfigStru[i].trainCbtcBackTime = LongFromChar(pTempData);						
                    pTempData += 4U;

                    /*判断信号机跨压距离(cm)*/
                    BnfZcSystemConfigStru[i].signPressureDis = ShortFromChar(pTempData);						
                    pTempData += 2U;

                    /*追踪不带后方检查标记RM列车方式*/
                    BnfZcSystemConfigStru[i].zcTrackRmTrainType = *pTempData;						
                    pTempData += 1U;
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
