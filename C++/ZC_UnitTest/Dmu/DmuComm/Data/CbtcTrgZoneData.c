/*************************************************
  文件名   ：CbtcTrgZoneData.c
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： CbtcTrgZoneData数据管理
			DmuCommonData组件的CbtcTrgZoneData功能可分解如下：
			1）	给CbtcTrgZoneDataStru结构体指针分配空间
			2）	获取CbtcTrgZoneData数据
			3）	获取CbtcTrgZoneData信息
			4）	获取指定IDCbtcTrgZoneDataStru的结构体下标
			5）	获取指定IDCbtcTrgZoneDataStru的结构体指针
			6）	获取指定IDCbtcTrgZoneDataStru的包含的逻辑区段的数目
			7）	获取指定IDCbtcTrgZoneDataStru的包含的逻辑区段的编号
  备注    ：无。
 
*************************************************/

#include "CbtcTrgZoneData.h"
#include "../../../Common/Malloc.h"

static BnfCbtcTrgZoneStruct* CbtcTrgZoneDataStru = NULL;   /*定义CbtcTrgZoneData数据结构体*/
static UINT16_S LineNumCbtcTrgZone = 0u;/*表行数*/


/*
* 功能描述： 给CbtcTrgZoneDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocCbtcTrgZoneDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == CbtcTrgZoneDataStru))
    {
        CbtcTrgZoneDataStru = (BnfCbtcTrgZoneStruct*)MemoryMalloc((UINT32_S)sizeof(BnfCbtcTrgZoneStruct) * lineNum);
        LineNumCbtcTrgZone = lineNum;
    }
}

/*
* 功能描述： 获取CbtcTrgZoneData数据
* 参数说明：
* 返回值  ： 
            BnfCbtcTrgZoneStruct*
*/
BnfCbtcTrgZoneStruct *GetCbtcTrgZoneData(void)
{
    return CbtcTrgZoneDataStru;
}


/*
* 功能描述： 获取CbtcTrgZoneData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfCbtcTrgZoneStruct*
*/
BnfCbtcTrgZoneStruct *GetCbtcTrgZoneDataInfo(UINT16_S* lineNum)
{

    BnfCbtcTrgZoneStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumCbtcTrgZone;
        retVal =  CbtcTrgZoneDataStru;

    }
    return retVal;
}
/*
** 功能描述： 获取指定IDCbtcTrgZoneDataStru的结构体下标
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetCbtcTrgZoneDataStruIndex(const UINT16_S cbtcApptchSectionId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumCbtcTrgZone; i++)
    {
        if (cbtcApptchSectionId == CbtcTrgZoneDataStru[i].cbtcApptchSectionId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCbtcTrgZoneDataStru的结构体指针
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfCbtcTrgZoneStruct* GetIndexIdCbtcTrgZoneDataStru(const UINT16_S cbtcApptchSectionId)
{
    BnfCbtcTrgZoneStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetCbtcTrgZoneDataStruIndex(cbtcApptchSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumCbtcTrgZone)
    {
        retVal = &CbtcTrgZoneDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCbtcTrgZoneDataStru的包含的逻辑区段的数目
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含的逻辑区段的数目
*/ 
UINT16_S GetCbtcTrgZoneDataStruincludeLgcZoneNum(const UINT16_S cbtcApptchSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetCbtcTrgZoneDataStruIndex(cbtcApptchSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumCbtcTrgZone)
    {
        retVal = CbtcTrgZoneDataStru[bufIndex].includeLgcZoneNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCbtcTrgZoneDataStru的包含的逻辑区段的编号
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 包含的逻辑区段的编号
*/ 
UINT16_S* GetCbtcTrgZoDataInLgcZoId(const UINT16_S cbtcApptchSectionId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetCbtcTrgZoneDataStruIndex(cbtcApptchSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumCbtcTrgZone)
    {
        retVal = CbtcTrgZoneDataStru[bufIndex].includeLgcZoneId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

