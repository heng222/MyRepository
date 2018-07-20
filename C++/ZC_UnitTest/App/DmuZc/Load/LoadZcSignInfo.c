/*******************************************
 * 文件名	：  LoadZcSignInfo.h
 * 作  者	：  ZC组
 * 创建时间	：  2015-5-25
 * 功能描述	：	载入ZcSignInfo数据
 * 备  注	：  无
*******************************************/
#include "LoadZcSignInfo.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"


/*******************************************
* 功能描述： 载入ZcSignInfo数据
* 参数说明： void
* 返回值  ： void
*/
INT8_S LoadZcSignInfoData(void)
{
	INT8_S retVal = 0;/*函数返回值*/
	UINT8_S* pTempData = NULL;/*临时存储数据*/
	UINT8_S indexId = 0U;/*结构体下标*/
	UINT32_S tempDataLen = 0U;
	UINT16_S tempDataNum = 0U;/*数据表的行数*/
	UINT16_S i = 0U;/*循环使用*/
    BnfZcSignInfoStruct* BnfZcSignInfoStru = NULL;/*ZcSignInfo信息结构体指针*/

	/*获取数据*/
	retVal = GetConfigDataLen(((UINT8_S)(ZC_DATA_TYPE)),((UINT8_S)(ZC_SIGN_INFO_ID)),&tempDataLen,&indexId);

	if((0 == retVal) && (((UINT16_S)tempDataLen) > 0U))
	{
		pTempData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(UINT32_S)(tempDataLen+50U));

        if (NULL != pTempData)
        {
            /*获取数据*/
            retVal = GetConfigData(((UINT16_S)(ZCSIGNINFO_LINE_BYTE_NUM)),tempDataLen,indexId,pTempData);

            /*解析数据*/
            /*判断数据长度是否为整数倍*/
            if((0 == retVal)&&(0U == (UINT16_S)(tempDataLen % ZCSIGNINFO_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / ZCSIGNINFO_LINE_BYTE_NUM);

                /*写入ZCSIGNINFO信息结构体指针地址*/
                MallocZcSignInfoDataStru(tempDataNum);
                BnfZcSignInfoStru = GetZcSignInfoData();

                /*数据有效开始写入结构体*/
                for(i = 0U;(i < tempDataNum)&&(BnfZcSignInfoStru != NULL);i++)
                {
                    /*信号机ID*/
                    BnfZcSignInfoStru[i].signId = ShortFromChar(pTempData);						
                    pTempData += 2U;

                    /*闯信号标志*/
                    BnfZcSignInfoStru[i].throughSignFlag = ShortFromChar(pTempData);
                    pTempData += 2U;

                    /*亮灭标志*/
                    BnfZcSignInfoStru[i].lightFlag = ShortFromChar(pTempData);
                    pTempData += 2U;
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
