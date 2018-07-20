/*************************************************
  文件名   ：PhysicalSectionData.c
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： PhysicalSectionData数据管理
			DmuCommonData组件的PhysicalSectionData功能可分解如下：
			1）	给LogicSectionDataStru结构体指针分配空间
			2）	获取LogicSectionData数据
			3）	获取LogicSectionData信息
			4）	获取指定IDLogicSectionDataStru的结构体下标
			5）	获取指定IDLogicSectionDataStru的结构体指针
			6）	获取指定IDLogicSectionDataStru的名称
			7）	获取指定IDLogicSectionDataStru的起点所处Seg编号
			8）	获取指定IDLogicSectionDataStru的起点所处Seg偏移量
			9）	获取指定IDLogicSectionDataStru的终点所处Seg编号
			10）	获取指定IDLogicSectionDataStru的终点所处Seg偏移量
			11）	获取线路逻辑区段最大ID
			12）	根据输入的SEGID获取逻辑区段的信息
			13）	获取逻辑区段所属ZC
			14）	获取逻辑区段所属CI
			15）	获取逻辑区段所属AC
			16）	查询此SEG前方的逻辑区段
			17）	查询此SEG后方的逻辑区段
			18）	获取逻辑区段ID相关联的逻辑区段ID
  备注    ：无。
 
*************************************************/

#include "PhysicalSectionData.h"
#include "../../../Common/Malloc.h"

static BnfPhysicalSectionStruct* PhysicalSectionDataStru = NULL;   /*定义PhysicalSectionData数据结构体*/
static UINT16_S LineNumPhysicalSection = 0u;/*表行数*/


/*
* 功能描述： 给PhysicalSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocPhysicalSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == PhysicalSectionDataStru))
    {
        PhysicalSectionDataStru = (BnfPhysicalSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfPhysicalSectionStruct) * lineNum);
        LineNumPhysicalSection = lineNum;
    }
}

/*
* 功能描述： 获取PhysicalSectionData数据
* 参数说明：
* 返回值  ： 
            BnfPhysicalSectionStruct*
*/
BnfPhysicalSectionStruct *GetPhysicalSectionData(void)
{
    return PhysicalSectionDataStru;
}


/*
* 功能描述： 获取PhysicalSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfPhysicalSectionStruct*
*/
BnfPhysicalSectionStruct *GetPhysicalSectionDataInfo(UINT16_S* lineNum)
{
    BnfPhysicalSectionStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumPhysicalSection;
        retVal = PhysicalSectionDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDPhysicalSectionDataStru的结构体下标
* 参数说明： const UINT16_S physicalStcId;编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetPhysicalSectionDataStruIndex(const UINT16_S physicalStcId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumPhysicalSection; i++)
    {
        if (physicalStcId == PhysicalSectionDataStru[i].physicalStcId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPhysicalSectionDataStru的结构体指针
* 参数说明： const UINT16_S physicalStcId;编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfPhysicalSectionStruct* GetIndexIdPhysicalSectionDataStru(const UINT16_S physicalStcId)
{
    BnfPhysicalSectionStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPhysicalSectionDataStruIndex(physicalStcId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPhysicalSection)
    {
        retVal = &PhysicalSectionDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPhysicalSectionDataStru的名称
* 参数说明： const UINT16_S physicalStcId;编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetPhysicalSectionDataStruname(const UINT16_S physicalStcId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPhysicalSectionDataStruIndex(physicalStcId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPhysicalSection)
    {
        retVal = PhysicalSectionDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPhysicalSectionDataStru的包含计轴区段数目
* 参数说明： const UINT16_S physicalStcId;编号
* 返回值  :  0: 获取数据失败
*            >0: 包含计轴区段数目
*/ 
UINT16_S GetPhysicalSectionDataStruincludeAxleScNum(const UINT16_S physicalStcId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPhysicalSectionDataStruIndex(physicalStcId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPhysicalSection)
    {
        retVal = PhysicalSectionDataStru[bufIndex].includeAxleScNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPhysicalSectionDataStru的计轴编号
* 参数说明： const UINT16_S physicalStcId;编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 计轴编号
*/ 
UINT16_S* GetPhysicalSectionDataStruaxleIdBuff(const UINT16_S physicalStcId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPhysicalSectionDataStruIndex(physicalStcId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPhysicalSection)
    {
        retVal = PhysicalSectionDataStru[bufIndex].axleIdBuff;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

