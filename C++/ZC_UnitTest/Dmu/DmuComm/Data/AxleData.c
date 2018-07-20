/*************************************************
  文件名   ：AxleData.h
  作者     ：董欣      
  创建时间 ：2016-8-10
  功能描述 ： 载入AxleData数据管理
			DmuCommonData组件的AxleData功能可分解如下：
				1）	给AxleDataStru结构体指针分配空间
				2）	获取AxleData数据
				3）	获取AxleData信息
				4）	获取指定IDAxleDataStru的结构体下标
				5）	获取指定IDAxleDataStru的结构体指针
				6）	获取指定IDAxleDataStru的计轴器名称
				7）	获取指定IDAxleDataStru的计轴器所处Seg偏移量(cm)
  备注    ：无。
 
*************************************************/

#include "AxleData.h"
#include "../../../Common/Malloc.h"

static BnfAxleStruct* AxleDataStru = NULL;   /*定义AxleData数据结构体*/
static UINT16_S LineNumAxle = 0u;/*表行数*/


/*
* 函数名称： MallocAxleDataStru
* 功能描述： 给AxleDataStru结构体指针分配空间
* 输入参数： UINT16_S lineNum 表的数据行数
* 输出参数： 无
* 返回值  ： void
*/
void MallocAxleDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == AxleDataStru))
    {
        AxleDataStru = (BnfAxleStruct*)MemoryMalloc((UINT32_S)sizeof(BnfAxleStruct) * lineNum);
        LineNumAxle = lineNum;
    }
}

/*
* 函数名称： GetAxleData
* 功能描述： 获取AxleData数据
* 输入参数： 无
* 输出参数： 无
* 返回值  ： 
            BnfAxleStruct*
*/
BnfAxleStruct *GetAxleData(void)
{
    return AxleDataStru;
}


/*
* 函数名称： GetAxleDataInfo
* 功能描述： 获取AxleData信息
* 输入参数： 无
* 输出参数： UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfAxleStruct*
*/
BnfAxleStruct *GetAxleDataInfo(UINT16_S* lineNum)
{

    BnfAxleStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumAxle;
        retVal =  AxleDataStru;

    }
    return retVal;
}
/*
* 函数名称： GetAxleDataStruIndex
* 功能描述： 获取指定IDAxleDataStru的结构体下标
* 输入参数： const UINT16_S axleId;编号
* 输出参数： 无
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetAxleDataStruIndex(const UINT16_S axleId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumAxle; i++)
    {
        if (axleId == AxleDataStru[i].axleId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
* 函数名称： GetIndexIdAxleDataStru
* 功能描述： 获取指定IDAxleDataStru的结构体指针
* 输入参数： const UINT16_S axleId;编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfAxleStruct* GetIndexIdAxleDataStru(const UINT16_S axleId)
{
    BnfAxleStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetAxleDataStruIndex(axleId);/*获取结构体数组下标*/
    if (bufIndex < LineNumAxle)
    {
        retVal = &AxleDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 函数名称： GetAxleDataStruaxleName
* 功能描述： 获取指定IDAxleDataStru的计轴器名称
* 输入参数： const UINT16_S axleId;编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: 计轴器名称
*/ 
UINT8_S* GetAxleDataStruaxleName(const UINT16_S axleId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetAxleDataStruIndex(axleId);/*获取结构体数组下标*/
    if (bufIndex < LineNumAxle)
    {
        retVal = AxleDataStru[bufIndex].axleName;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 函数名称： GetAxleDataStruaxleSegOfst
* 功能描述： 获取指定IDAxleDataStru的计轴器所处Seg偏移量(cm)
* 输入参数： const UINT16_S axleId;编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 计轴器所处Seg偏移量(cm)
*/ 
UINT32_S GetAxleDataStruaxleSegOfst(const UINT16_S axleId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetAxleDataStruIndex(axleId);/*获取结构体数组下标*/
    if (bufIndex < LineNumAxle)
    {
        retVal = AxleDataStru[bufIndex].axleSegOfst;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

