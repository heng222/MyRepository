/*************************************************
  文件名   ：SystemRailInfoData.c
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

#include "SystemRailInfoData.h"
#include "../../../Common/Malloc.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfSystemRailInfoStruct* SystemRailInfoDataStru = NULL;   /*定义SystemRailInfoData数据结构体*/
static UINT16_S LineNumSystemRailInfo = 0u;/*表行数*/


/*
* 功能描述： 给SystemRailInfoDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSystemRailInfoDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SystemRailInfoDataStru))
    {
        SystemRailInfoDataStru = (BnfSystemRailInfoStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSystemRailInfoStruct) * lineNum);
        LineNumSystemRailInfo = lineNum;
    }
}

/*
* 功能描述： 获取SystemRailInfoData数据
* 参数说明：
* 返回值  ： 
            BnfSystemRailInfoStruct*
*/
BnfSystemRailInfoStruct *GetSystemRailInfoData(void)
{
    return SystemRailInfoDataStru;
}


/*
* 功能描述： 获取SystemRailInfoData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSystemRailInfoStruct*
*/
BnfSystemRailInfoStruct *GetSystemRailInfoDataInfo(UINT16_S* lineNum)
{

    BnfSystemRailInfoStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSystemRailInfo;
        retVal = SystemRailInfoDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取车头前方最差坡度计算范围。计算车头前方EBi对应的最差坡度时,在车头前方搜寻的长度范围,单位cm
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: 车头前方最差坡度计算范围。计算车头前方EBi对应的最差坡度时,在车头前方搜寻的长度范围,单位cm
*/ 
UINT32_S GetSystemRailDisFrontToGetGrade(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != SystemRailInfoDataStru)
    {
        retVal = SystemRailInfoDataStru[0].disFrontToGetGrade;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取车身最差坡度计算范围。计算车身处EBi对应的最差坡度时, 在车头前方搜寻的长度范围,单位cm
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*            <UINT16_NULL: 车身最差坡度计算范围。计算车身处EBi对应的最差坡度时, 在车头前方搜寻的长度范围,单位cm
*/ 
UINT16_S GetSystemRailDisBetweenToGetGrade(void)
{
    UINT16_S retVal = UINT16_NULL;/*函数返回值*/
    if (NULL != SystemRailInfoDataStru)
    {
        retVal = SystemRailInfoDataStru[0].disBetweenToGetGrade;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取推荐速度与EBI的最小差值(km/h)
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*            <UINT8_NULL: 推荐速度与EBI的最小差值(km/h)
*/ 
UINT8_S GetSystemRailMinMarginFromEBI(void)
{
    UINT8_S retVal = UINT8_NULL;/*函数返回值*/
    if (NULL != SystemRailInfoDataStru)
    {
        retVal = SystemRailInfoDataStru[0].minMarginFromEBI;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

