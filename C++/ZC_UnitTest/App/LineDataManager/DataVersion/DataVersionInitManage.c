/************************************************************************
*
* 文件名   ：  DataVersionInitManage.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  数据版本初始化管理
* 备  注   ：  无
*
************************************************************************/
#include "DataVersionConfigData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Common/Convert.h"
#include "DataVersionInitManage.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"
#include "DataVersionDefine.h"

extern DataVersionStruct gLocalDataVersionStru;                 /*定义本地数据的版本号信息*/

/*
* 功能描述： 初始化本地数据版本信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			 1: 初始化成功
*/
UINT8_S InitLocalDataVersion(void)
{
	UINT16_S initErrorFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/* ZC自己使用的数据版本信息 */
	if (RETURN_SUCCESS == InitLocalZcSelfDataVersion())
	{
        /*不处理*/	
	} 
	else
	{
		initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
	}

    /* ZC和ATP对比的数据版本 */
    if (RETURN_SUCCESS == InitZcAtpDataVersion())
    {
        /* 不处理 */
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_3);
    }

	if (DEFAULT_ZERO == initErrorFlag)
	{
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	LogPrintf(1U,"InitLocalDV Err %d\n",initErrorFlag);
	return rtnValue;
}

/*
* 功能描述： 初始化本地数据版本信息(ZC自己数据版本)
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			 1: 初始化成功
*/
UINT8_S InitLocalZcSelfDataVersion(void)
{
	UINT8_S versionBuff[SINGLE_VERSION_LEN_MAX] = {DEFAULT_ZERO};
	INT8_S tempRtn = 1;
	UINT32_S dataVerison = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;

	MemorySet(&versionBuff[0],((UINT32_S)(SIZE_UINT8 * SINGLE_VERSION_LEN_MAX)),
                0U,((UINT32_S)(SIZE_UINT8 * SINGLE_VERSION_LEN_MAX)));

	/*获取ZC自己使用的数据版本信息*/
	tempRtn = DmuGetDataFileVersion(&dataVerison);

	if (0 == tempRtn)
	{
		LongToChar(dataVerison,versionBuff);

		for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
		{
			gLocalDataVersionStru.SelfDataVersion[cycle] = versionBuff[cycle];
		}

		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地数据版本信息(ZC和ATP数据版本)
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			 1: 初始化成功
*/
UINT8_S InitZcAtpDataVersion(void)
{
    UINT8_S versionBuff[SINGLE_VERSION_LEN_MAX] = {DEFAULT_ZERO};
    INT8_S tempRtn = 1;
    UINT32_S dataVerison = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;

    MemorySet(&versionBuff[0],((UINT32_S)(SIZE_UINT8 * SINGLE_VERSION_LEN_MAX)),
        0U,((UINT32_S)(SIZE_UINT8 * SINGLE_VERSION_LEN_MAX)));

    /*获取ZC和ATP对比的数据版本信息*/
    tempRtn = DmuGetIntSysCmpDataFileVer(((UINT8_S)(INTERSYSVERCMP_IDX_ATPZC)),&dataVerison);

    if (0 == tempRtn)
    {
        LongToChar(dataVerison,versionBuff);

        for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
        {
            gLocalDataVersionStru.ZcATPDataVersion[cycle] = versionBuff[cycle];
        }

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}