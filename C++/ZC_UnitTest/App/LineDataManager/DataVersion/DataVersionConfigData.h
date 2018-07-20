/************************************************************************
*
* 文件名   ：  DataVersionConfigData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  数据版本配置数据
* 备  注   ：  无
*
************************************************************************/
#ifndef DATA_VERSION_CONFIG_DATA_H_
#define DATA_VERSION_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "DataVersionDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*定义单个数据版本*/
typedef struct DataVersionStruct
{
	UINT8_S  SelfDataVersion[SINGLE_VERSION_LEN_MAX];      /* ZC自己用的数据版本信息 */
    UINT8_S  ZcATPDataVersion[SINGLE_VERSION_LEN_MAX];     /* ZC和ATP数据版本信息 */
}DataVersionStruct;

/*
* 功能描述： 获取ZC自己数据版本号信息
* 参数说明： const UINT8 bufSize,输出buf大小
*            UINT8_S mapVersionBuff[],电子地图版本号缓存数组    
* 返回值  ： 0: 获取数据失败
*			1: 获取数据成功
*/
UINT8_S GetSelfDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[]);

/*
* 功能描述： 获取ZC和ATP对比的数据版本号信息
* 参数说明： const UINT8 bufSize,输出buf大小
*            UINT8_S mapVersionBuff[],电子地图版本号缓存数组    
* 返回值  ： 0: 获取数据失败
*			1: 获取数据成功
*/
UINT8_S GetZcAtpDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[]);

#ifdef __cplusplus
}
#endif

#endif
