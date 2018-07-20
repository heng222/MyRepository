/*************************************************
  文件名   ：StopSectionData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： StopSectionData数据管理
			DmuCommonData组件的StopSectionData功能可分解如下：
			1）	给StopSectionDataStru结构体指针分配空间
			2）	获取StopSectionData数据
			3）	获取StopSectionData信息
			4）	获取指定IDStopSectionDataStru的结构体下标
			5）	获取指定IDStopSectionDataStru的结构体指针
			6）	获取指定IDStopSectionDataStru的所属车站名称
			7）	获取指定dstCode的所属车站名称
			8）	获取指定IDStopSectionDataStru的目的地编号
			9）	获取指定IDStopSectionDataStru的停车区域seg编号
			10）	获取指定IDStopSectionDataStru的停车区域属性
			11）	获取指定IDStopSectionDataStru的站台最小停站时间
			12）	获取指定IDStopSectionDataStru的站台最大停站时间
			13）	获取指定IDStopSectionDataStru的站台默认停站时间
			14）	获取指定IDStopSectionDataStru的站台开门方式
			15）	获取指定IDStopSectionDataStru的站台开门时间间隔
			16）	获取指定IDStopSectionDataStru的站台关门方式
			17）	获取指定IDStopSectionDataStru的站台关门时间间隔
			18）	获取指定IDStopSectionDataStru的站台默认停稳时间
			19）	查询某个点是否属于转换轨
			20）	获取指定位置的停车区域属性
			21）	获取指定位置的停车区域ID
			22）	获取指定位置的停车区域信息
  备注    ：无。
 
*************************************************/

#include "StopSectionData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/Convert.h"
static BnfStopSectionStruct* StopSectionDataStru = NULL;   /*定义StopSectionData数据结构体*/
static UINT16_S LineNumStopSection = 0u;/*表行数*/


/*
* 功能描述： 给StopSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocStopSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == StopSectionDataStru))
    {
        StopSectionDataStru = (BnfStopSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfStopSectionStruct) * lineNum);
        LineNumStopSection = lineNum;
    }
}

/*
* 功能描述： 获取StopSectionData数据
* 参数说明：
* 返回值  ： 
BnfStopSectionStruct*
*/
BnfStopSectionStruct *GetStopSectionData(void)
{
    return StopSectionDataStru;
}


/*
* 功能描述： 获取StopSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
BnfStopSectionStruct*
*/
BnfStopSectionStruct *GetStopSectionDataInfo(UINT16_S* lineNum)
{

    BnfStopSectionStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumStopSection;
        retVal = StopSectionDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDStopSectionDataStru的结构体下标
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetStopSectionDataStruIndex(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumStopSection; i++)
    {
        if (stopSectionId == StopSectionDataStru[i].stopSectionId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的结构体指针
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfStopSectionStruct* GetIndexIdStopSectionDataStru(const UINT16_S stopSectionId)
{
    BnfStopSectionStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = &StopSectionDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的所属车站名称
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 所属车站名称
*/ 
UINT8_S* GetStopSectionDataStrustationName(const UINT16_S stopSectionId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].stationName;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定dstCode的所属车站名称
* 参数说明： const UINT16_S dstCode;
* 返回值  :  NULL: 获取数据失败
*            !NULL: 所属车站名称
*/ 
UINT8_S* GetStopSecNameByDstCode(const UINT16_S dstCode)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S i = 0u;
    UINT16_S destId = 0u;

    for(i = 0u;i < LineNumStopSection;i++)
    {
        destId = ShortFromChar(StopSectionDataStru[i].bDesId);
        if(dstCode == destId)
        {
            retVal = StopSectionDataStru[i].stationName;
            break;
        }
    }
    return retVal;
}


/*
** 功能描述： 获取指定IDStopSectionDataStru的目的地编号
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 目的地编号
*/ 
UINT8_S* GetStopSectionDataStrubDesId(const UINT16_S stopSectionId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].bDesId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的停车区域seg编号
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 停车区域seg编号
*/ 
UINT16_S GetStopSectionDataStrusegId(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].segId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的停车区域属性
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 停车区域属性
*/ 
UINT16_S GetStopSectionDataStrusttribute(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].sttribute;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台最小停站时间
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台最小停站时间
*/ 
UINT16_S GetStopSectionDataStruminParkTime(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].minParkTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台最大停站时间
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台最大停站时间
*/ 
UINT16_S GetStopSectionDataStrumaxParkTime(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].maxParkTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台默认停站时间
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台默认停站时间
*/ 
UINT16_S GetStopSectionDataStruparkTime(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].parkTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台开门方式
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台开门方式
*/ 
UINT16_S GetStopSectionDataStrudoorOpenMode(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].doorOpenMode;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台开门时间间隔
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台开门时间间隔
*/ 
UINT16_S GetStopSectionDataStrudoorOpenTime(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].doorOpenTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台关门方式
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台关门方式
*/ 
UINT16_S GetStopSectionDataStrudoorCloseMode(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].doorCloseMode;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台关门时间间隔
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台关门时间间隔
*/ 
UINT16_S GetStopSectDataDoorCTim(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].doorCloseTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台默认停稳时间
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台默认停稳时间
*/ 
UINT16_S GetStopSectionDataStruparkSteadyTime(const UINT16_S stopSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetStopSectionDataStruIndex(stopSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumStopSection)
    {
        retVal = StopSectionDataStru[bufIndex].parkSteadyTime;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 查询某个点是否属于转换轨
* 参数说明： 
* 返回值  ： 0: 查询失败
*            1: 属于
*             2: 不属于
*/
UINT8_S CheckPointBelongToZHG(UINT16_S wTrainHeadSeg)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumStopSection; i++)
    {
        if (wTrainHeadSeg == StopSectionDataStru[i].segId)
        {
            if (RUN_TRANSFORM_AREA == (StopSectionDataStru[i].sttribute &RUN_TRANSFORM_AREA))
            {
                retVal = 1u;        
            }
            else
            {
                retVal = 2u;
            }

            break;
        }
        else
        {
            retVal = 2u;
        }

    }

    return retVal;
}

/*
** 功能描述： 获取指定位置的停车区域属性
* 参数说明： const UINT16_S segId;SEGID
* 返回值  :   0: 此SEGID没有停车区域
*             >0: 停车区域属性
*/ 
UINT16_S GetCurSegOfStopSecType(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumStopSection; i++)
    {
        if (segId == StopSectionDataStru[i].segId)
        {
            retVal = StopSectionDataStru[i].sttribute;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定位置的停车区域ID
* 参数说明： const UINT16_S segId;SEGID
* 返回值  :   0: 此SEGID没有停车区域
*             >0: 停车区域ID
*/ 
UINT16_S GetCurSegOfStopSecId(const UINT16_S segId)
{
    UINT16_S retVal = 0x0u;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumStopSection; i++)
    {
        if (segId == StopSectionDataStru[i].segId)
        {
            retVal = StopSectionDataStru[i].stopSectionId;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定位置的停车区域信息
* 参数说明： const UINT16_S segId;SEGID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfStopSectionStruct* GetCurSegOfStopSecInfo(const UINT16_S segId)
{
    BnfStopSectionStruct* retVal = NULL;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumStopSection; i++)
    {
        if (segId == StopSectionDataStru[i].segId)
        {
            retVal = &StopSectionDataStru[i];
            break;
        }
    }
    return retVal;
}

