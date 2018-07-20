/*************************************************
  文件名   ：BlocApptchSectionData.c
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： BaliseData数据管理
			DmuCommonData组件的BlocApptchSectionData功能可分解如下：
			1）	给BlocApptchSectionDataStru结构体指针分配空间
			2）	获取BlocApptchSectionData数据
			3）	获取BlocApptchSectionData信息
			4）	获取指定IDBlocApptchSectionDataStru的结构体下标
			5）	获取指定IDBlocApptchSectionDataStru的结构体指针
			6）	获取指定IDBlocApptchSectionDataStru的包含的计轴区段数目
			7）	获取指定IDBlocApptchSectionDataStru的包含的计轴区段编号
  备注    ：无。
 
*************************************************/

#include "BlocApptchSectionData.h"
#include "../../../Common/Malloc.h"

static BnfBlocApptchSectionStruct* BlocApptchSectionDataStru = NULL;   /*定义BlocApptchSectionData数据结构体*/
static UINT16_S LineNumBlocApptchSection = 0u;/*表行数*/


/*
* 功能描述： 给BlocApptchSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocBlocApptchSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == BlocApptchSectionDataStru))
    {
        BlocApptchSectionDataStru = (BnfBlocApptchSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfBlocApptchSectionStruct) * lineNum);
        LineNumBlocApptchSection = lineNum;
    }
}

/*
* 功能描述： 获取BlocApptchSectionData数据
* 参数说明：
* 返回值  ： 
BnfBlocApptchSectionStruct*
*/
BnfBlocApptchSectionStruct *GetBlocApptchSectionData(void)
{
    return BlocApptchSectionDataStru;
}


/*
* 功能描述： 获取BlocApptchSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
BnfBlocApptchSectionStruct*
*/
BnfBlocApptchSectionStruct *GetBlocApptchSectionDataInfo(UINT16_S* lineNum)
{
    BnfBlocApptchSectionStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumBlocApptchSection;
        retVal =  BlocApptchSectionDataStru;

    }
    return retVal;
}
/*
** 功能描述： 获取指定IDBlocApptchSectionDataStru的结构体下标
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetBlocApptchSectionDataStruIndex(const UINT16_S blocApptchSectionId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumBlocApptchSection; i++)
    {
        if (blocApptchSectionId == BlocApptchSectionDataStru[i].blocApptchSectionId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDBlocApptchSectionDataStru的结构体指针
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfBlocApptchSectionStruct* GetIndexIdBlocApptchSectionDataStru(const UINT16_S blocApptchSectionId)
{
    BnfBlocApptchSectionStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetBlocApptchSectionDataStruIndex(blocApptchSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumBlocApptchSection)
    {
        retVal = &BlocApptchSectionDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDBlocApptchSectionDataStru的包含的计轴区段数目
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含的计轴区段数目
*/ 
UINT16_S GetBlocApptchSectionDataStruincludeAxleSgmtNum(const UINT16_S blocApptchSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetBlocApptchSectionDataStruIndex(blocApptchSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumBlocApptchSection)
    {
        retVal = BlocApptchSectionDataStru[bufIndex].includeAxleSgmtNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDBlocApptchSectionDataStru的包含的计轴区段编号
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 包含的计轴区段编号
*/ 
UINT16_S* GetBlAppSectDataInAxSgmtId(const UINT16_S blocApptchSectionId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetBlocApptchSectionDataStruIndex(blocApptchSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumBlocApptchSection)
    {
        retVal = BlocApptchSectionDataStru[bufIndex].includeAxleSgmtId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

