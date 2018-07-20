/************************************************************************
*
* 文件名   ：  DataVersionStatusData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  数据版本
* 备  注   ：  无
*
************************************************************************/
#ifndef DATA_VERSION_STATUS_DATA_H_
#define DATA_VERSION_STATUS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "DataVersionDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 获取ZC自己版本号信息
* 参数说明： const UINT8 bufSize,输出buf大小
*            UINT8_S mapVersionBuff[],电子地图版本号缓存数组    
* 返回值  ： 0: 获取数据失败
*			 1: 获取数据成功
*/
UINT8_S GetZcSelfDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[]);

/*
* 功能描述： 设置ZC自己版本号信息
* 参数说明： const UINT8 bufSize,输出buf大小
*            const UINT8_S mapVersionBuff[],电子地图版本号缓存数组    
* 返回值  ： 0: 设置数据失败
*			 1: 设置数据成功
*/
UINT8_S SetZcSelfDataVersionData(const UINT8_S bufSize,const UINT8_S mapVersionBuff[]);	

/*
* 功能描述： 清空ZC数据版本号信息
* 参数说明： 无   
* 返回值  ： 无
*/
void ClearZcSelfDataVersion(void);

	
#ifdef __cplusplus
}
#endif

#endif
