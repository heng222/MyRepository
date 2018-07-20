/*************************************************
  文件名   ：StopPointData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： StopPointData数据管理
			DmuCommonData组件的StopPointData功能可分解如下：
			1）	给StopPointDataStru结构体指针分配空间
			2）	获取StopPointData数据
			3）	获取StopPointData信息
			4）	获取指定IDStopPointDataStru的结构体下标
			5）	获取指定IDStopPointDataStru的结构体指针
			6）	获取指定IDStopPointDataStru的停车点属性
			7）	获取指定IDStopPointDataStru的停车点作用方向(16进制)
			8）	获取指定IDStopPointDataStru的停车点所处seg编号
			9）	获取指定IDStopPointDataStru的停车点Seg偏移量
			10）	获取指定IDStopPointDataStru的停车点对应ATO作用窗范围
			11）	获取指定IDStopPointDataStru的停车点对应ATP作用窗范围
			12）	获取指定偏移是否在ATP作用窗范围
			13）	获取指定偏移是否在ATO作用窗范围
   备注    ：无。
 
*************************************************/

#include "StopPointData.h"
#include "../../../Common/Malloc.h"

static BnfStopPointStruct* StopPointDataStru = NULL;   /*定义StopPointData数据结构体*/
static UINT16_S LineNumStopPoint = 0u;/*表行数*/


/*
* 功能描述： 给StopPointDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocStopPointDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == StopPointDataStru))
    {
        StopPointDataStru = (BnfStopPointStruct*)MemoryMalloc((UINT32_S)sizeof(BnfStopPointStruct) * lineNum);
        LineNumStopPoint = lineNum;
    }
}

/*
* 功能描述： 获取StopPointData数据
* 参数说明：
* 返回值  ： 
            BnfStopPointStruct*
*/
BnfStopPointStruct *GetStopPointData(void)
{
    return StopPointDataStru;
}


/*
* 功能描述： 获取StopPointData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfStopPointStruct*
*/
BnfStopPointStruct *GetStopPointDataInfo(UINT16_S* lineNum)
{

    BnfStopPointStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumStopPoint;
        retVal = StopPointDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDStopPointDataStru的结构体下标
* 参数说明： const UINT16_S stopPointId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetStopPointDataStruIndex(const UINT16_S stopPointId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumStopPoint; i++)
    {
        if (stopPointId == StopPointDataStru[i].stopPointId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopPointDataStru的结构体指针
* 参数说明： const UINT16_S stopPointId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfStopPointStruct* GetIndexIdStopPointDataStru(const UINT16_S stopPointId)
{
    BnfStopPointStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = &StopPointDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopPointDataStru的停车点属性
* 参数说明： const UINT16_S stopPointId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 停车点属性
*/ 
UINT16_S GetStopPointDataStruattribute(const UINT16_S stopPointId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].attribute;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopPointDataStru的停车点作用方向(16进制)
* 参数说明： const UINT16_S stopPointId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 停车点作用方向(16进制)
*/ 
UINT16_S GetStopPointDataStrudir(const UINT16_S stopPointId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].dir;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopPointDataStru的停车点所处seg编号
* 参数说明： const UINT16_S stopPointId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 停车点所处seg编号
*/ 
UINT16_S GetStopPointDataStrusegId(const UINT16_S stopPointId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].segId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopPointDataStru的停车点Seg偏移量
* 参数说明： const UINT16_S stopPointId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 停车点Seg偏移量
*/ 
UINT32_S GetStopPointDataStrusegOfst(const UINT16_S stopPointId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].segOfst;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopPointDataStru的停车点对应ATO作用窗范围
* 参数说明： const UINT16_S stopPointId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 停车点对应ATO作用窗范围
*/ 
UINT32_S GetStopPointDataStruaTOParkArea(const UINT16_S stopPointId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].aTOParkArea;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopPointDataStru的停车点对应ATP作用窗范围
* 参数说明： const UINT16_S stopPointId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 停车点对应ATP作用窗范围
*/ 
UINT32_S GetStopPointDataStruaTPParkArea(const UINT16_S stopPointId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopPointDataStruIndex(stopPointId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopPoint)
    {
        retVal = StopPointDataStru[bufIndex].aTPParkArea;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定偏移是否在ATP作用窗范围
* 参数说明： const UINT16_S stopPointId;索引编号
                         UINT32_S Off
* 返回值  :  0，不在ATP停车窗内
*                    1，在ATP停车窗内
*/ 
UINT8_S GetThisInAtpStopPointWindow(const UINT16_S stopPointId,UINT32_S Off)
{
    UINT8_S isIn = 0u;
    UINT32_S pointOff = GetStopPointDataStrusegOfst(stopPointId);
    UINT32_S windowLen = GetStopPointDataStruaTPParkArea(stopPointId);
    UINT32_S leftOff = pointOff -windowLen;
    UINT32_S rightOff = pointOff +windowLen;
    if ((Off>leftOff)&&(Off<rightOff))
    {
        isIn = 1u;
    }
    return isIn;
}

/*
** 功能描述： 获取指定偏移是否在ATO作用窗范围
* 参数说明： const UINT16_S stopPointId;索引编号
                         UINT32_S Off
* 返回值  :  0，不在ATP停车窗内
*                    1，在ATP停车窗内
*/ 
UINT8_S GetThisInAtoStopPointWindow(const UINT16_S stopPointId,UINT32_S Off)
{
    UINT8_S isIn = 0u;
    UINT32_S pointOff = GetStopPointDataStrusegOfst(stopPointId);
    UINT32_S windowLen = GetStopPointDataStruaTOParkArea(stopPointId);
    UINT32_S leftOff = pointOff -windowLen;
    UINT32_S rightOff = pointOff +windowLen;
    if ((Off>leftOff)&&(Off<rightOff))
    {
        isIn = 1u;
    }
    return isIn;
}
