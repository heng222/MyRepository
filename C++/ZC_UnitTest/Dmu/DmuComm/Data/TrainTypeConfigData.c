/*************************************************
  文件名   ：TrainTypeConfigData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： TrainTypeConfigData数据管理
			DmuCommonData组件的TrainTypeConfigData功能可分解如下：
			1）	给TrainTypeConfigDataStru结构体指针分配空间
			2）	获取TrainTypeConfigData数据
			3）	获取TrainTypeConfigData信息
			4）	获取指定IDTrainTypeConfigDataStru的结构体下标
			5）	获取指定IDTrainTypeConfigDataStru的结构体指针
			6）	获取指定IDTrainTypeConfigDataStru的列车类型

  备注    ：无。 
*************************************************/

#include "TrainTypeConfigData.h"
#include "../../../Common/Malloc.h"

static BnfTrainTypeConfigStruct* TrainTypeConfigDataStru = NULL;   /*定义TrainTypeConfigData数据结构体*/
static UINT16_S LineNumTrainTypeConfig = 0u;/*表行数*/


/*
* 功能描述： 给TrainTypeConfigDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocTrainTypeConfigDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == TrainTypeConfigDataStru))
    {
        TrainTypeConfigDataStru = (BnfTrainTypeConfigStruct*)MemoryMalloc((UINT32_S)sizeof(BnfTrainTypeConfigStruct) * lineNum);
        LineNumTrainTypeConfig = lineNum;
    }
}

/*
* 功能描述： 获取TrainTypeConfigData数据
* 参数说明：
* 返回值  ： 
            BnfTrainTypeConfigStruct*
*/
BnfTrainTypeConfigStruct *GetTrainTypeConfigData(void)
{
    return TrainTypeConfigDataStru;
}


/*
* 功能描述： 获取TrainTypeConfigData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfTrainTypeConfigStruct*
*/
BnfTrainTypeConfigStruct *GetTrainTypeConfigDataInfo(UINT16_S* lineNum)
{

    BnfTrainTypeConfigStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumTrainTypeConfig;
        retVal = TrainTypeConfigDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDTrainTypeConfigDataStru的结构体下标
* 参数说明： const UINT16_S trainDevName;列车名称(TYPE+ID)
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetTrainTypeConfigDataStruIndex(const UINT16_S trainDevName)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumTrainTypeConfig; i++)
    {
        if (trainDevName == TrainTypeConfigDataStru[i].trainDevName)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDTrainTypeConfigDataStru的结构体指针
* 参数说明： const UINT16_S trainDevName;列车名称(TYPE+ID)
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfTrainTypeConfigStruct* GetIndexIdTrainTypeConfigDataStru(const UINT16_S trainDevName)
{
    BnfTrainTypeConfigStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetTrainTypeConfigDataStruIndex(trainDevName);/*获取结构体数组下标*/
    if (bufIndex < LineNumTrainTypeConfig)
    {
        retVal = &TrainTypeConfigDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDTrainTypeConfigDataStru的列车类型
* 参数说明： const UINT16_S trainDevName;列车名称(TYPE+ID)
* 返回值  :  0: 获取数据失败
*            >0: 列车类型
*/ 
UINT8_S GetTrainTypeConfigDataStrutrainType(const UINT16_S trainDevName)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetTrainTypeConfigDataStruIndex(trainDevName);/*获取结构体数组下标*/
    if (bufIndex < LineNumTrainTypeConfig)
    {
        retVal = TrainTypeConfigDataStru[bufIndex].trainType;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

