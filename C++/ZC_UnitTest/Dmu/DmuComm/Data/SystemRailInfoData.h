/*************************************************
  文件名   ：SystemRailInfoData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SystemRailInfoData数据管理
			DmuCommonData组件的SystemRailInfoData功能可分解如下：
			1）	给SystemRailInfoDataStru结构体指针分配空间
			2）	获取SystemRailInfoData数据
			3）	获取SystemRailInfoData信息
			4）	获取车头前方最差坡度计算范围。计算车头前方EBi对应的最差坡度时,在车头前方搜寻的长度范围,单位cm
			5）	获取车身最差坡度计算范围。计算车身处EBi对应的最差坡度时,
			6）	获取推荐速度与EBI的最小差值(km/h)

  备注    ：无。 
*************************************************/
#ifndef SYSTEMRAILINFO_DATA_H_
#define SYSTEMRAILINFO_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SYSTEMRAILINFO_LINE_BYTE_NUM                      7                        /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*线路参数表结构体定义*/
typedef struct BnfSystemRailInfoStruct
{
    UINT32_S disFrontToGetGrade;          /*车头前方最差坡度计算范围。计算车头前方EBi对应的最差坡度时,在车头前方搜寻的长度范围,单位cm*/
    UINT16_S disBetweenToGetGrade;        /*车身最差坡度计算范围。计算车身处EBi对应的最差坡度时, 在车头前方搜寻的长度范围,单位cm*/
    UINT8_S  minMarginFromEBI;            /*推荐速度与EBI的最小差值(km/h)*/
}BnfSystemRailInfoStruct;

/*
* 功能描述： 给SystemRailInfoDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSystemRailInfoDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取SystemRailInfoData数据
* 参数说明：
* 返回值  ： 
            BnfSystemRailInfoStruct*
*/
BnfSystemRailInfoStruct *GetSystemRailInfoData(void);

/*
* 功能描述： 获取SystemRailInfoData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSystemRailInfoStruct*
*/
BnfSystemRailInfoStruct *GetSystemRailInfoDataInfo(UINT16_S* lineNum);

/*
** 功能描述： 获取车头前方最差坡度计算范围。计算车头前方EBi对应的最差坡度时,在车头前方搜寻的长度范围,单位cm
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: 车头前方最差坡度计算范围。计算车头前方EBi对应的最差坡度时,在车头前方搜寻的长度范围,单位cm
*/ 
UINT32_S GetSystemRailDisFrontToGetGrade(void);

/*
** 功能描述： 获取车身最差坡度计算范围。计算车身处EBi对应的最差坡度时, 在车头前方搜寻的长度范围,单位cm
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*            <UINT16_NULL: 车身最差坡度计算范围。计算车身处EBi对应的最差坡度时, 在车头前方搜寻的长度范围,单位cm
*/ 
UINT16_S GetSystemRailDisBetweenToGetGrade(void);

/*
** 功能描述： 获取推荐速度与EBI的最小差值(km/h)
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*            <UINT8_NULL: 推荐速度与EBI的最小差值(km/h)
*/ 
UINT8_S GetSystemRailMinMarginFromEBI(void);
#ifdef __cplusplus
}
#endif

#endif
