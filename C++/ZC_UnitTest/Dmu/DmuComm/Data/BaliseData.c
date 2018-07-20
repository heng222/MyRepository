/*************************************************
  文件名   ：BaliseData.c
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： BaliseData数据管理
			DmuCommonData组件的BaliseData功能可分解如下：
			1）	给BaliseDataStru结构体指针分配空间
			2）	获取BaliseData数据
			3）	获取BaliseData信息
			4）	获取指定IDBaliseDataStru的结构体下标
			5）	获取指定IDBaliseDataStru的结构体指针
			6）	获取指定IDBaliseDataStru的名称
			7）	获取指定IDBaliseDataStru的所处seg编号
			8）	获取指定IDBaliseDataStru的所处Seg偏移量（cm）


  备注    ：无。
 
*************************************************/

#include "BaliseData.h"
#include "../../../Common/Malloc.h"

static BnfBaliseStruct* BaliseDataStru = NULL;   /*定义BaliseData数据结构体*/
static UINT16_S LineNumBalise = 0u;/*表行数*/


/*
* 功能描述： 给BaliseDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocBaliseDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == BaliseDataStru))
    {
        BaliseDataStru = (BnfBaliseStruct*)MemoryMalloc((UINT32_S)sizeof(BnfBaliseStruct) * lineNum);
        LineNumBalise = lineNum;
    }
}

/*
* 功能描述： 获取BaliseData数据
* 参数说明：
* 返回值  ： 
BnfBaliseStruct*
*/
BnfBaliseStruct *GetBaliseData(void)
{
    return BaliseDataStru;
}


/*
* 功能描述： 获取BaliseData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
BnfBaliseStruct*
*/
BnfBaliseStruct *GetBaliseDataInfo(UINT16_S* lineNum)
{

    BnfBaliseStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumBalise;
        retVal =  BaliseDataStru;

    }
    return retVal;
}
/*
** 功能描述： 获取指定IDBaliseDataStru的结构体下标
* 参数说明： const UINT32_S baliseId;应答器ID
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetBaliseDataStruIndex(const UINT32_S baliseId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumBalise; i++)
    {
        if (baliseId == BaliseDataStru[i].baliseId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDBaliseDataStru的结构体指针
* 参数说明： const UINT32_S baliseId;应答器ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfBaliseStruct* GetIndexIdBaliseDataStru(const UINT32_S baliseId)
{
    BnfBaliseStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetBaliseDataStruIndex(baliseId);/*获取结构体数组下标*/
    if (bufIndex < LineNumBalise)
    {
        retVal = &BaliseDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDBaliseDataStru的名称
* 参数说明： const UINT32_S baliseId;应答器ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetBaliseDataStruname(const UINT32_S baliseId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetBaliseDataStruIndex(baliseId);/*获取结构体数组下标*/
    if (bufIndex < LineNumBalise)
    {
        retVal = BaliseDataStru[bufIndex].name;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDBaliseDataStru的所处seg编号
* 参数说明： const UINT32_S baliseId;应答器ID
* 返回值  :  0: 获取数据失败
*            >0: 所处seg编号
*/ 
UINT16_S GetBaliseDataStrusegId(const UINT32_S baliseId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetBaliseDataStruIndex(baliseId);/*获取结构体数组下标*/
    if (bufIndex < LineNumBalise)
    {
        retVal = BaliseDataStru[bufIndex].segId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDBaliseDataStru的所处Seg偏移量（cm）
* 参数说明： const UINT32_S baliseId;应答器ID
* 返回值  :  0: 获取数据失败
*            >0: 所处Seg偏移量（cm）
*/ 
UINT32_S GetBaliseDataStrusegOffset(const UINT32_S baliseId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetBaliseDataStruIndex(baliseId);/*获取结构体数组下标*/
    if (bufIndex < LineNumBalise)
    {
        retVal = BaliseDataStru[bufIndex].segOffset;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}



