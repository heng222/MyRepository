/*******************************************
 * 文件名	：  LoadZcCommConfig.h
 * 作  者	：  ZC组
 * 创建时间	：  2015-5-25
 * 功能描述	：	载入ZcCommConfig数据
 * 备  注	：  无
*******************************************/
#include "LoadZcCommConfig.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"

/*******************************************
* 函数名	：
* 功能描述： 载入ZcCommConfig数据
* 参数说明： void
* 返回值  ： 0:成功
			-2 数据长度错误
*			-1 函数指针为空
			1接口防护错误
			2传入的数据类型和表单编号错误
*
*
*/
INT8_S LoadZcCommConfigData(void)
{
	INT8_S retVal = 0;/*函数返回值*/
	UINT8_S* pTempData = NULL;/*临时存储数据*/
	UINT8_S indexId = 0U;/*结构体下标*/
	UINT32_S tempDataLen = 0U;
	UINT16_S tempDataNum = 0U;/*数据表的行数*/
	UINT16_S i = 0U;/*循环使用*/
    BnfZcCommConfigStruct* BnfZcCommConfigStru = NULL;/*ZcCommConfig信息结构体指针*/

	/*获取数据*/
	retVal = GetConfigDataLen(((UINT8_S)(ZC_CONFIG_TYPE)),((UINT8_S)(ZC_COMM_CONFIG_DATA_ID)),&tempDataLen,&indexId);

	if((0 == retVal)&&(((UINT16_S)tempDataLen) > 0U))
	{
		pTempData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(UINT32_S)(tempDataLen+50U));

        if (NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(((UINT16_S)(ZCCOMMCONFIG_LINE_BYTE_NUM)),tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0U == (UINT16_S)(tempDataLen % ZCCOMMCONFIG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / ZCCOMMCONFIG_LINE_BYTE_NUM);

                /*写入ZCCOMMCONFIG信息结构体指针地址*/
                MallocZcCommConfigDataStru(tempDataNum);
                BnfZcCommConfigStru = GetZcCommConfigData();

                /*数据有效开始写入结构体*/
                for(i = 0U;(i < tempDataNum)&&(BnfZcCommConfigStru != NULL);i++)
                {
                    /*ZC向ATS发送数据周期时间(ms)*/
                    BnfZcCommConfigStru[i].zcSendAtsDataCycle = LongFromChar(pTempData);						
                    pTempData += 4U;
                }
            }
            else
            {
                /*数据长度错误*/
                retVal = -2;
            }
        } 
        else
        {
            retVal = -1;
        }	
	}
    else
    {
        retVal = 2;
    }

	return retVal;
}
