/************************************************************************
*
* 文件名   ：  DataVersionConfigData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  数据版本配置数据
* 备  注   ：  无
*
************************************************************************/

#include "DataVersionConfigData.h"

DataVersionStruct gLocalDataVersionStru;                 /*定义本地数据的版本号信息*/

/*
* 功能描述： 获取ZC自己数据版本号信息
* 参数说明： const UINT8 bufSize,输出buf大小
*            UINT8_S mapVersionBuff[],电子地图版本号缓存数组    
* 返回值  ： 0: 获取数据失败
*			1: 获取数据成功
*/
UINT8_S GetSelfDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[])
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;

	if ((SINGLE_VERSION_LEN_MAX <= bufSize)
		&& (NULL != mapVersionBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
		{
			mapVersionBuff[cycle] = gLocalDataVersionStru.SelfDataVersion[cycle];
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
* 功能描述： 获取ZC和ATP对比的数据版本号信息
* 参数说明： const UINT8 bufSize,输出buf大小
*            UINT8_S mapVersionBuff[],电子地图版本号缓存数组    
* 返回值  ： 0: 获取数据失败
*			1: 获取数据成功
*/
UINT8_S GetZcAtpDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;

    if ((SINGLE_VERSION_LEN_MAX <= bufSize)
        && (NULL != mapVersionBuff))
    {
        for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
        {
            mapVersionBuff[cycle] = gLocalDataVersionStru.ZcATPDataVersion[cycle];
        }

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}