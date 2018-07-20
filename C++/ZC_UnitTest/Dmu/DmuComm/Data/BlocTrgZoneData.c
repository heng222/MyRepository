/*************************************************
  文件名   ：BlocTrgZoneData.c
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： BlocTrgZoneData数据管理
			DmuCommonData组件的BlocTrgZoneData功能可分解如下：
			1）	给BlocTrgZoneDataStru结构体指针分配空间
			2）	获取BlocTrgZoneData数据
			3）	获取BlocTrgZoneData信息
			4）	获取指定IDBlocTrgZoneDataStru的结构体下标
			5）	获取指定IDBlocTrgZoneDataStru的结构体指针
			6）	 获取指定IDBlocTrgZoneDataStru的包含的计轴区段数目
			7）	获取指定IDBlocTrgZoneDataStru的包含的计轴区段编号

  备注    ：无。
 
*************************************************/

#include "BlocTrgZoneData.h"
#include "../../../Common/Malloc.h"

static BnfBlocTrgZoneStruct* BlocTrgZoneDataStru = NULL;   /*定义BlocTrgZoneData数据结构体*/
static UINT16_S LineNumBlocTrgZone = 0u;/*表行数*/


/*
* 功能描述： 给BlocTrgZoneDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocBlocTrgZoneDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == BlocTrgZoneDataStru))
    {
        BlocTrgZoneDataStru = (BnfBlocTrgZoneStruct*)MemoryMalloc((UINT32_S)sizeof(BnfBlocTrgZoneStruct) * lineNum);
        LineNumBlocTrgZone = lineNum;
    }
}

/*
* 功能描述： 获取BlocTrgZoneData数据
* 参数说明：
* 返回值  ： 
BnfBlocTrgZoneStruct*
*/
BnfBlocTrgZoneStruct *GetBlocTrgZoneData(void)
{
    return BlocTrgZoneDataStru;
}


/*
* 功能描述： 获取BlocTrgZoneData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
BnfBlocTrgZoneStruct*
*/
BnfBlocTrgZoneStruct *GetBlocTrgZoneDataInfo(UINT16_S* lineNum)
{

    BnfBlocTrgZoneStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumBlocTrgZone;
        retVal =  BlocTrgZoneDataStru;

    }
    return retVal;
}
/*
** 功能描述： 获取指定IDBlocTrgZoneDataStru的结构体下标
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetBlocTrgZoneDataStruIndex(const UINT16_S blocApptchSectionId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumBlocTrgZone; i++)
    {
        if (blocApptchSectionId == BlocTrgZoneDataStru[i].blocApptchSectionId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDBlocTrgZoneDataStru的结构体指针
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfBlocTrgZoneStruct* GetIndexIdBlocTrgZoneDataStru(const UINT16_S blocApptchSectionId)
{
    BnfBlocTrgZoneStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetBlocTrgZoneDataStruIndex(blocApptchSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumBlocTrgZone)
    {
        retVal = &BlocTrgZoneDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDBlocTrgZoneDataStru的包含的计轴区段数目
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含的计轴区段数目
*/ 
UINT16_S GetBlocTrgZoneDataStruincludeAxleSgmtNum(const UINT16_S blocApptchSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetBlocTrgZoneDataStruIndex(blocApptchSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumBlocTrgZone)
    {
        retVal = BlocTrgZoneDataStru[bufIndex].includeAxleSgmtNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDBlocTrgZoneDataStru的包含的计轴区段编号
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 包含的计轴区段编号
*/ 
UINT16_S* GetBlTrgZoDataInAxleSegmId(const UINT16_S blocApptchSectionId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetBlocTrgZoneDataStruIndex(blocApptchSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumBlocTrgZone)
    {
        retVal = BlocTrgZoneDataStru[bufIndex].includeAxleSgmtId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

