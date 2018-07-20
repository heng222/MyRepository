/*************************************************
  文件名   ：TrainStationData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： TrainStationData数据管理
			DmuCommonData组件的TrainStationData功能可分解如下：
			1）	给TrainStationDataStru结构体指针分配空间
			2）	获取TrainStationData数据
			3）	获取TrainStationData信息
			4）	获取指定IDTrainStationDataStru的结构体下标
			5）	获取指定IDTrainStationDataStru的结构体指针
			6）	获取指定IDTrainStationDataStru的车站名称
			7）	获取指定IDTrainStationDataStru的车站包含站台数目
			8）	获取指定IDTrainStationDataStru的站台编号
  备注    ：无。 
*************************************************/

#include "TrainStationData.h"
#include "../../../Common/Malloc.h"

static BnfTrainStationStruct* TrainStationDataStru = NULL;   /*定义TrainStationData数据结构体*/
static UINT16_S LineNumTrainStation = 0u;/*表行数*/


/*
* 功能描述： 给TrainStationDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocTrainStationDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == TrainStationDataStru))
    {
        TrainStationDataStru = (BnfTrainStationStruct*)MemoryMalloc((UINT32_S)sizeof(BnfTrainStationStruct) * lineNum);
        LineNumTrainStation = lineNum;
    }
}

/*
* 功能描述： 获取TrainStationData数据
* 参数说明：
* 返回值  ： 
            BnfTrainStationStruct*
*/
BnfTrainStationStruct *GetTrainStationData(void)
{
    return TrainStationDataStru;
}


/*
* 功能描述： 获取TrainStationData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfTrainStationStruct*
*/
BnfTrainStationStruct *GetTrainStationDataInfo(UINT16_S* lineNum)
{

    BnfTrainStationStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumTrainStation;
        retVal = TrainStationDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDTrainStationDataStru的结构体下标
* 参数说明： const UINT16_S stationId;车站ID
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetTrainStationDataStruIndex(const UINT16_S stationId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumTrainStation; i++)
    {
        if (stationId == TrainStationDataStru[i].stationId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDTrainStationDataStru的结构体指针
* 参数说明： const UINT16_S stationId;车站ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfTrainStationStruct* GetIndexIdTrainStationDataStru(const UINT16_S stationId)
{
    BnfTrainStationStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetTrainStationDataStruIndex(stationId);/*获取结构体数组下标*/
    if (bufIndex < LineNumTrainStation)
    {
        retVal = &TrainStationDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDTrainStationDataStru的车站名称
* 参数说明： const UINT16_S stationId;车站ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 车站名称
*/ 
UINT8_S* GetTrainStationDataStruname(const UINT16_S stationId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetTrainStationDataStruIndex(stationId);/*获取结构体数组下标*/
    if (bufIndex < LineNumTrainStation)
    {
        retVal = TrainStationDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDTrainStationDataStru的车站包含站台数目
* 参数说明： const UINT16_S stationId;车站ID
* 返回值  :  0: 获取数据失败
*            >0: 车站包含站台数目
*/ 
UINT16_S GetTrainStationDataStruincludeStationNum(const UINT16_S stationId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetTrainStationDataStruIndex(stationId);/*获取结构体数组下标*/
    if (bufIndex < LineNumTrainStation)
    {
        retVal = TrainStationDataStru[bufIndex].includeStationNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDTrainStationDataStru的站台编号
* 参数说明： const UINT16_S stationId;车站ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 站台编号
*/ 
UINT16_S* GetTrainStationDataStrustationIdBuff(const UINT16_S stationId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetTrainStationDataStruIndex(stationId);/*获取结构体数组下标*/
    if (bufIndex < LineNumTrainStation)
    {
        retVal = TrainStationDataStru[bufIndex].stationIdBuff;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

