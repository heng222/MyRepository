/*************************************************
  文件名   ：SectionTypeData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SectionTypeData数据管理
			DmuCommonData组件的SectionTypeData功能可分解如下：
			1）	给SectionTypeDataStru结构体指针分配空间
			2）	获取SectionTypeData数据
			3）	获取SectionTypeData信息
			4）	获取指定IDSectionTypeDataStru的结构体下标
			5）	获取指定IDSectionTypeDataStru的结构体指针
			6）	获取指定IDSectionTypeDataStru的区域类型
			7）	获取指定IDSectionTypeDataStru的区域ID
			8）	获取指定IDSectionTypeDataStru的区域属性
			9）	获取指定设备类型和ID的区段属性

  备注    ：无。
 
*************************************************/

#include "SectionTypeData.h"
#include "../../../Common/Malloc.h"

static BnfSectionTypeStruct* SectionTypeDataStru = NULL;   /*定义SectionTypeData数据结构体*/
static UINT16_S LineNumSectionType = 0u;/*表行数*/


/*
* 功能描述： 给SectionTypeDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSectionTypeDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SectionTypeDataStru))
    {
        SectionTypeDataStru = (BnfSectionTypeStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSectionTypeStruct) * lineNum);
        LineNumSectionType = lineNum;
    }
}

/*
* 功能描述： 获取SectionTypeData数据
* 参数说明：
* 返回值  ： 
            BnfSectionTypeStruct*
*/
BnfSectionTypeStruct *GetSectionTypeData(void)
{
    return SectionTypeDataStru;
}


/*
* 功能描述： 获取SectionTypeData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSectionTypeStruct*
*/
BnfSectionTypeStruct *GetSectionTypeDataInfo(UINT16_S* lineNum)
{

    BnfSectionTypeStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSectionType;
        retVal = SectionTypeDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDSectionTypeDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSectionTypeDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumSectionType; i++)
    {
        if (indexId == SectionTypeDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSectionTypeDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSectionTypeStruct* GetIndexIdSectionTypeDataStru(const UINT16_S indexId)
{
    BnfSectionTypeStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSectionTypeDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSectionType)
    {
        retVal = &SectionTypeDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSectionTypeDataStru的区域类型
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 区域类型
*/ 
UINT16_S GetSectionTypeDataStrusectionType(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSectionTypeDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSectionType)
    {
        retVal = SectionTypeDataStru[bufIndex].sectionType;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSectionTypeDataStru的区域ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 区域ID
*/ 
UINT16_S GetSectionTypeDataStrusectionId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSectionTypeDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSectionType)
    {
        retVal = SectionTypeDataStru[bufIndex].sectionId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSectionTypeDataStru的区域属性
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 区域属性
*/ 
UINT8_S GetSectionTypeDataStrusectionProperty(const UINT16_S indexId)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSectionTypeDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSectionType)
    {
        retVal = SectionTypeDataStru[bufIndex].sectionProperty;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}


/*
** 功能描述： 获取指定设备类型和ID的区段属性
* 参数说明： const UINT16_S devType   设备类型,const UINT16_S devId   设备ID
* 返回值  :  0: 获取数据失败
*             >0: 区段属性
*/ 
UINT8_S GetSecPropertyAccordName(const UINT16_S devType,const UINT16_S devId)
{
    UINT8_S retVal = 0u;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; (i < LineNumSectionType)&&(devId > 0); i++)
    {
        if ((devType == SectionTypeDataStru[i].sectionType)&&(devId == SectionTypeDataStru[i].sectionId))
        {
            retVal = SectionTypeDataStru[i].sectionProperty;
            break;
        }
    }
    return retVal;
}

