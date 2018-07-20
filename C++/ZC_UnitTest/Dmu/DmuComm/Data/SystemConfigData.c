/*************************************************
  文件名   ：SystemConfigData.c
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

#include "SystemConfigData.h"
#include "../../../Common/Malloc.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfSystemConfigStruct* BnfSystemConfigDataStru = NULL;   /*定义SystemConfigData数据结构体*/
static UINT16_S LineNumSystemConfig = 0u;/*表行数*/


/*
* 功能描述： 给SystemConfigDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSystemConfigDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == BnfSystemConfigDataStru))
    {
        BnfSystemConfigDataStru = (BnfSystemConfigStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSystemConfigStruct) * lineNum);
        LineNumSystemConfig = lineNum;
    }
}

/*
* 功能描述： 获取SystemConfigData数据
* 参数说明：
* 返回值  ： 
            BnfSystemConfigStruct*
*/
BnfSystemConfigStruct *GetSystemConfigData(void)
{
    return BnfSystemConfigDataStru;
}


/*
* 功能描述： 获取SystemConfigData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSystemConfigStruct*
*/
BnfSystemConfigStruct *GetSystemConfigDataInfo(UINT16_S* lineNum)
{

    BnfSystemConfigStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSystemConfig;
        retVal = BnfSystemConfigDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDSystemConfigDataStru的系统运行最高速度(km/h)
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*            <UINT8_NULL: 系统运行最高速度(km/h)
*/ 
UINT8_S GetSystemConfigDataStrumaxLineLimitSpeed(void)
{
    UINT8_S retVal = UINT8_NULL;/*函数返回值*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].maxLineLimitSpeed;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}


/*
** 功能描述： 获取临时限速最高限速(km/h)
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*            <UINT8_NULL: 临时限速最高限速(km/h)
*/ 
UINT8_S GetSystemMaxTsrSpeed(void)
{
    UINT8_S retVal = UINT8_NULL;/*函数返回值*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].maxTsrSpeed;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取NTP校时时区差.格林威治时间与本地时间的时区差，单位：时区，应用使用时应乘以3600转换为秒。
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*            <UINT8_NULL: NTP校时时区差.格林威治时间与本地时间的时区差，单位：时区，应用使用时应乘以3600转换为秒。
*/ 
UINT8_S GetSystemNtpMimeZoneDifference(void)
{
    UINT8_S retVal = UINT8_NULL;/*函数返回值*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].mimeZoneDifference;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取安全防护距离.考虑到最不利情况情况下（最大潜在退行距离和线路最大坡度等）移动授权考虑的安全防护距离
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*            <UINT16_NULL: 安全防护距离.考虑到最不利情况情况下（最大潜在退行距离和线路最大坡度等）移动授权考虑的安全防护距离
*/ 
UINT16_S GetSystemSafeBackDistance(void)
{
    UINT16_S retVal = UINT16_NULL;/*函数返回值*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].safeBackDistance;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取系统定义最大保护区段长度（cm）
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*            <UINT16_NULL: 系统定义最大保护区段长度（cm）
*/ 
UINT16_S GetSystemMaxOverlapLength(void)
{
    UINT16_S retVal = UINT16_NULL;/*函数返回值*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].maxOverlapLength;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取seg逻辑方向上下行
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*            <UINT8_NULL: seg逻辑方向上下行
*/ 
UINT8_S GetSystemSegLogicDirUpAndDown(void)
{
    UINT8_S retVal = UINT8_NULL;/*函数返回值*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].segLogicDirUpAndDown;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取RM限速值
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*            <UINT16_NULL: RM限速值
*/ 
UINT16_S GetSystemRmLimitSpeed(void)
{
    UINT16_S retVal = UINT16_NULL;/*函数返回值*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].rmLimitSpeed;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

