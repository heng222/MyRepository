/************************************************************************
*
* 文件名   ：  DataVersionStatusData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  维护管理
* 备  注   ：  无
*
************************************************************************/
#include "DataVersionConfigData.h"

DataVersionStruct gInputDataVersionStru;                 /*定义输入的数据版本号信息*/

/*
* 功能描述： 获取ZC自己版本号信息
* 参数说明： const UINT8 bufSize,输出buf大小
*            UINT8_S mapVersionBuff[],电子地图版本号缓存数组    
* 返回值  ： 0: 获取数据失败
*			 1: 获取数据成功
*/
UINT8_S GetZcSelfDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[])
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;

	if ((SINGLE_VERSION_LEN_MAX <= bufSize)
		&& (NULL != mapVersionBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
		{
			mapVersionBuff[cycle] = gInputDataVersionStru.SelfDataVersion[cycle];
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
* 功能描述： 设置ZC自己版本号信息
* 参数说明： const UINT8 bufSize,输出buf大小
*            const UINT8_S mapVersionBuff[],电子地图版本号缓存数组    
* 返回值  ： 0: 设置数据失败
*			 1: 设置数据成功
*/
UINT8_S SetZcSelfDataVersionData(const UINT8_S bufSize,const UINT8_S mapVersionBuff[])
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;

	if ((SINGLE_VERSION_LEN_MAX == bufSize)
		&& (NULL != mapVersionBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
		{
			gInputDataVersionStru.SelfDataVersion[cycle] = mapVersionBuff[cycle];
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
* 功能描述： 清空ZC数据版本号信息
* 参数说明： 无   
* 返回值  ： 无
*/
void ClearZcSelfDataVersion(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
	{
		gInputDataVersionStru.SelfDataVersion[cycle] = DEFAULT_ZERO;
	}
}
