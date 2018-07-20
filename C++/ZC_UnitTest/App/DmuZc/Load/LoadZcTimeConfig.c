/*******************************************
 * 文件名	：  LoadZcTimeConfig.h
 * 作  者	：  ZC组
 * 创建时间	：  2015-5-25
 * 功能描述	：	载入ZcTimeConfig数据
 * 备  注	：  无	
*******************************************/
#include "LoadZcTimeConfig.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"


/*******************************************
* 功能描述： 载入ZcTimeConfig数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadZcTimeConfigData(void)
{
	INT8_S retVal = 0;/*函数返回值*/
	UINT8_S* pTempData = NULL;/*临时存储数据*/
	UINT8_S indexId = 0U;/*结构体下标*/
	UINT32_S tempDataLen = 0U;
	UINT16_S tempDataNum = 0U;/*数据表的行数*/
	UINT16_S i = 0U;/*循环使用*/
    BnfZcTimeConfigStruct* BnfZcTimeConfigStru = NULL;/*ZcTimeConfig信息结构体指针*/

	/*获取数据*/
	retVal = GetConfigDataLen(((UINT8_S)(ZC_CONFIG_TYPE)),((UINT8_S)(ZC_TIME_CONFIG_DATA_ID)),&tempDataLen,&indexId);

	if((0 == retVal)&&(((UINT16_S)tempDataLen) > 0U))
	{
		pTempData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(UINT32_S)(tempDataLen+50U));

        if (NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(((UINT16_S)(ZCTIMECONFIG_LINE_BYTE_NUM)),tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0U == (UINT16_S)(tempDataLen % ZCTIMECONFIG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / ZCTIMECONFIG_LINE_BYTE_NUM);

                /*写入ZCTIMECONFIG信息结构体指针地址*/
                MallocZcTimeConfigDataStru(tempDataNum);
                BnfZcTimeConfigStru = GetZcTimeConfigData();

                /*数据有效开始写入结构体*/
                if (BnfZcTimeConfigStru != NULL)
                {
                    for(i = 0U;i < tempDataNum;i++)
                    {
                        /*NTP校时误差时间(ms)*/	
                        BnfZcTimeConfigStru[i].errorTime = LongFromChar(pTempData);						
                        pTempData += 4U;

                        /*本系统与时钟服务器校时的时长（ms）*/
                        BnfZcTimeConfigStru[i].duration = LongFromChar(pTempData);						
                        pTempData += 4U;
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
