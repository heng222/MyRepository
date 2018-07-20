/*************************************************
  文件名   ：SystemConfigData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SystemConfigData数据管理
			DmuCommonData组件的SystemConfigData功能可分解如下：
			1）	给SystemConfigDataStru结构体指针分配空间
			2）	获取SystemConfigData数据
			3）	获取SystemConfigData信息
			4）	获取指定IDSystemConfigDataStru的系统运行最高速度(km/h)
			5）	获取临时限速最高限速(km/h)
			6）	获取NTP校时时区差.格林威治时间与本地时间的时区差，单位
			7）	获取安全防护距离.考虑到最不利情况情况下（最大潜在退行距离和线路最大坡度等）移动授权考虑的安全防护距离
			8）	获取系统定义最大保护区段长度（cm）
			9）	获取seg逻辑方向上下行
			10）	获取RM限速值
  备注    ：无。 
*************************************************/
#ifndef SYSTEMCONFIG_DATA_H_
#define SYSTEMCONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SYSTEMCONFIG_LINE_BYTE_NUM                        (10-2)                           /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*系统配置数据表数据结构体*/
typedef struct BnfSystemConfigStruct
{
    UINT8_S   maxLineLimitSpeed;            /*系统运行最高速度(km/h)*/        
    UINT8_S    maxTsrSpeed;                /*临时限速最高限速(km/h)*/        
    UINT8_S    mimeZoneDifference;            /*NTP校时时区差.格林威治时间与本地时间的时区差，单位：时区，应用使用时应乘以3600转换为秒。*/        
    UINT16_S    safeBackDistance;            /*安全防护距离.考虑到最不利情况情况下（最大潜在退行距离和线路最大坡度等）移动授权考虑的安全防护距离*/        
    UINT16_S  maxOverlapLength;            /*系统定义最大保护区段长度（cm）*/
    UINT8_S    segLogicDirUpAndDown;        /*seg逻辑方向上下行*/    
    UINT16_S    rmLimitSpeed;                /*RM限速值*/        
}BnfSystemConfigStruct;

/*
* 功能描述： 给SystemConfigDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSystemConfigDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取SystemConfigData数据
* 参数说明：
* 返回值  ： 
            BnfSystemConfigStruct*
*/
BnfSystemConfigStruct *GetSystemConfigData(void);

/*
* 功能描述： 获取SystemConfigData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSystemConfigStruct*
*/
BnfSystemConfigStruct *GetSystemConfigDataInfo(UINT16_S* lineNum);

/*
** 功能描述： 获取指定IDSystemConfigDataStru的系统运行最高速度(km/h)
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*            <UINT8_NULL: 系统运行最高速度(km/h)
*/ 
UINT8_S GetSystemConfigDataStrumaxLineLimitSpeed(void);

/*
** 功能描述： 获取临时限速最高限速(km/h)
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*            <UINT8_NULL: 临时限速最高限速(km/h)
*/ 
UINT8_S GetSystemMaxTsrSpeed(void);

/*
** 功能描述： 获取NTP校时时区差.格林威治时间与本地时间的时区差，单位：时区，应用使用时应乘以3600转换为秒。
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*            <UINT8_NULL: NTP校时时区差.格林威治时间与本地时间的时区差，单位：时区，应用使用时应乘以3600转换为秒。
*/ 
UINT8_S GetSystemNtpMimeZoneDifference(void);

/*
** 功能描述： 获取安全防护距离.考虑到最不利情况情况下（最大潜在退行距离和线路最大坡度等）移动授权考虑的安全防护距离
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*            <UINT16_NULL: 安全防护距离.考虑到最不利情况情况下（最大潜在退行距离和线路最大坡度等）移动授权考虑的安全防护距离
*/ 
UINT16_S GetSystemSafeBackDistance(void);

/*
** 功能描述： 获取系统定义最大保护区段长度（cm）
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*            <UINT16_NULL: 系统定义最大保护区段长度（cm）
*/ 
UINT16_S GetSystemMaxOverlapLength(void);

/*
** 功能描述： 获取seg逻辑方向上下行
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*            <UINT8_NULL: seg逻辑方向上下行
*/ 
UINT8_S GetSystemSegLogicDirUpAndDown(void);

/*
** 功能描述： 获取RM限速值
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*            <UINT16_NULL: RM限速值
*/ 
UINT16_S GetSystemRmLimitSpeed(void);


#ifdef __cplusplus
}
#endif

#endif
