/*************************************************
  文件名   ：StaRunLevelData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： StaRunLevelData数据管理
			DmuCommonData组件的StaRunLevelData功能可分解如下：
			1）	给StaRunLevelDataStru结构体指针分配空间
			2）	获取StaRunLevelData数据
			3）	获取StaRunLevelData信息
			4）	获取指定IDStaRunLevelDataStru的结构体下标
			5）	获取指定IDStaRunLevelDataStru的结构体指针
			6）	获取指定IDStaRunLevelDataStru的起点目的地编号
			7）	获取指定IDStaRunLevelDataStru的终点目的地编号
			8）	获取指定IDStaRunLevelDataStru的运行级别分级数目
			9）	获取指定IDStaRunLevelDataStru的
			10）	获取指定起点与终点的运行级别对应速度

  备注    ：无。
 
*************************************************/

#include "StaRunLevelData.h"
#include "../../../Common/Malloc.h"

static BnfStaRunLevelStruct* StaRunLevelDataStru = NULL;   /*定义StaRunLevelData数据结构体*/
static UINT16_S LineNumStaRunLevel = 0u;/*表行数*/


/*
* 功能描述： 给StaRunLevelDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocStaRunLevelDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == StaRunLevelDataStru))
    {
        StaRunLevelDataStru = (BnfStaRunLevelStruct*)MemoryMalloc((UINT32_S)sizeof(BnfStaRunLevelStruct) * lineNum);
        LineNumStaRunLevel = lineNum;
    }
}

/*
* 功能描述： 获取StaRunLevelData数据
* 参数说明：
* 返回值  ： 
            BnfStaRunLevelStruct*
*/
BnfStaRunLevelStruct *GetStaRunLevelData(void)
{
    return StaRunLevelDataStru;
}


/*
* 功能描述： 获取StaRunLevelData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfStaRunLevelStruct*
*/
BnfStaRunLevelStruct *GetStaRunLevelDataInfo(UINT16_S* lineNum)
{
    BnfStaRunLevelStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumStaRunLevel;
        retVal = StaRunLevelDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDStaRunLevelDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetStaRunLevelDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumStaRunLevel; i++)
    {
        if (indexId == StaRunLevelDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStaRunLevelDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfStaRunLevelStruct* GetIndexIdStaRunLevelDataStru(const UINT16_S indexId)
{
    BnfStaRunLevelStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStaRunLevelDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStaRunLevel)
    {
        retVal = &StaRunLevelDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStaRunLevelDataStru的起点目的地编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点目的地编号
*/ 
UINT16_S GetStaRunLevelDataStrustartDestId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStaRunLevelDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStaRunLevel)
    {
        retVal = StaRunLevelDataStru[bufIndex].startDestId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStaRunLevelDataStru的终点目的地编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点目的地编号
*/ 
UINT16_S GetStaRunLevelDataStruendDestId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStaRunLevelDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStaRunLevel)
    {
        retVal = StaRunLevelDataStru[bufIndex].endDestId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStaRunLevelDataStru的运行级别分级数目
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 运行级别分级数目
*/ 
UINT16_S GetStaRunLevelDataStrurunLevelNum(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStaRunLevelDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStaRunLevel)
    {
        retVal = StaRunLevelDataStru[bufIndex].runLevelNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStaRunLevelDataStru的
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 
*/ 
SngRunLevelStruct* GetStaRunLevelDataStrurunLevelStru(const UINT16_S indexId)
{
    SngRunLevelStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStaRunLevelDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStaRunLevel)
    {
        retVal = StaRunLevelDataStru[bufIndex].runLevelStru;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定起点与终点的运行级别对应速度
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0 查询失败
*            > 0 : 查询的速度 
*/ 
UINT16_S GetSpdForLevelByStartToEnd(UINT16_S startId,UINT16_S endId,UINT16_S level)
{
    UINT16_S tmpSpd = 0u;
    UINT32_S    tmpI = 0u;
    if ((startId == 0u)||(endId == 0u)||(level == 0u))
    {
        tmpI = 0xffffu;
    }
    for (tmpI = 0u; tmpI < LineNumStaRunLevel; tmpI++)
    {
        if ((StaRunLevelDataStru[tmpI].startDestId == startId)
            &&(StaRunLevelDataStru[tmpI].endDestId == endId))
        {
            if ((level <= StaRunLevelDataStru[tmpI].runLevelNum)&&(level > 0u))
            {
                tmpSpd = StaRunLevelDataStru[tmpI].runLevelStru[level-1u].levelSpeed;
                break;
            }
        }
    }
    return tmpSpd;
}
