/*************************************************
  文件名   ：LineSwitchInfoData.c
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： LineSwitchInfoData数据管理
			DmuCommonData组件的LineSwitchInfoData功能可分解如下：
			1）	给LineSwitchInfoDataStru结构体指针分配空间
			2）	获取LineSwitchInfoData数据
			3）	获取LineSwitchInfoData信息
			4）	获取指定IDLineSwitchInfoDataStru的结构体下标
			5）	获取指定IDLineSwitchInfoDataStru的结构体指针
			6）	获取指定IDLineSwitchInfoDataStru的切换线路移交ZCID
			7）	获取指定IDLineSwitchInfoDataStru的切换线路接管ZCID
			8）	获取指定IDLineSwitchInfoDataStru的切换线路方向
			9）	获取指定IDLineSwitchInfoDataStru的切换线路起点所处seg编号
			10）	获取指定IDLineSwitchInfoDataStru的切换线路起点所处seg偏移
			11）	获取指定IDLineSwitchInfoDataStru的切换点所处seg编号
			12）	获取指定IDLineSwitchInfoDataStru的切换点所处seg偏移
			13）	获取指定IDLineSwitchInfoDataStru的切换线路终点所处seg编号
			14）	获取指定IDLineSwitchInfoDataStru的切换线路终点所处seg偏移
			15）	获取指定IDLineSwitchInfoDataStru的切换点相关进路编号
			16）	获取指定IDLineSwitchInfoDataStru的切换线路内包含的道岔数目
			17）	获取指定IDLineSwitchInfoDataStru的道岔信息结构体
			18）	获取切换线路数量和ID信息

  备注    ：无。
 
*************************************************/

#include "LineSwitchInfoData.h"
#include "../../../Common/Malloc.h"

static BnfLineSwitchInfoStruct* LineSwitchInfoDataStru = NULL;   /*定义LineSwitchInfoData数据结构体*/
static UINT16_S LineNumLineSwitchInfo = 0u;/*表行数*/


/*
* 功能描述： 给LineSwitchInfoDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocLineSwitchInfoDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == LineSwitchInfoDataStru))
    {
        LineSwitchInfoDataStru = (BnfLineSwitchInfoStruct*)MemoryMalloc((UINT32_S)sizeof(BnfLineSwitchInfoStruct) * lineNum);
        LineNumLineSwitchInfo = lineNum;
    }
}

/*
* 功能描述： 获取LineSwitchInfoData数据
* 参数说明：
* 返回值  ： 
            BnfLineSwitchInfoStruct*
*/
BnfLineSwitchInfoStruct *GetLineSwitchInfoData(void)
{
    return LineSwitchInfoDataStru;
}


/*
* 功能描述： 获取LineSwitchInfoData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfLineSwitchInfoStruct*
*/
BnfLineSwitchInfoStruct *GetLineSwitchInfoDataInfo(UINT16_S* lineNum)
{

    BnfLineSwitchInfoStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumLineSwitchInfo;
        retVal = LineSwitchInfoDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetLineSwitchInfoDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumLineSwitchInfo; i++)
    {
        if (indexId == LineSwitchInfoDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfLineSwitchInfoStruct* GetIndexIdLineSwitchInfoDataStru(const UINT16_S indexId)
{
    BnfLineSwitchInfoStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = &LineSwitchInfoDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路移交ZCID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路移交ZCID
*/ 
UINT16_S GetLineSwitchInfoDataStrulineSwitchTraZcId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].lineSwitchTraZcId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路接管ZCID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路接管ZCID
*/ 
UINT16_S GetLinSwInfDatliSwTakeOvZcId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].lineSwitchTakeOverZcId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路方向
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路方向
*/ 
UINT8_S GetLineSwInfoDatalineSwDir(const UINT16_S indexId)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].lineSwitchDir;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路起点所处seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路起点所处seg编号
*/ 
UINT16_S GetLineSwitchInfoDataStrustartLineSwitchInfoId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].startLineSwitchInfoId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路起点所处seg偏移
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路起点所处seg偏移
*/ 
UINT32_S GetLineSwitchInfoDataStrustartSegOffset(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].startSegOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换点所处seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换点所处seg编号
*/ 
UINT16_S GetLineSwitchInfoDataStruswitchPointSegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].switchPointSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换点所处seg偏移
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换点所处seg偏移
*/ 
UINT32_S GetLineSwInfoDataSwPointOff(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].switchPointOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路终点所处seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路终点所处seg编号
*/ 
UINT16_S GetLineSwitchInfoDataStruendLineSwitchInfoId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].endLineSwitchInfoId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路终点所处seg偏移
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路终点所处seg偏移
*/ 
UINT32_S GetLineSwitchInfoDataStrusegEndOffset(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].segEndOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换点相关进路编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换点相关进路编号
*/ 
UINT16_S GetLineSwitchInfoDataStrurelationRouteNum(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].relationRouteNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路内包含的道岔数目
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路内包含的道岔数目
*/ 
UINT16_S GetLineSwitchInfoDataStruincludeSwitchNum(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].includeSwitchNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的道岔信息结构体
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 道岔信息结构体
*/ 
BnfSngSwitchInfoStruct* GetLineSwInfDataSwInfStru(const UINT16_S indexId)
{
    BnfSngSwitchInfoStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].switchInfoStru;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取切换线路数量和ID信息
* 输入参数： const UINT16_S localZcId, 本地ZCid
*            UINT16_S changeLineIdBuf[]，切换线路ID数组（最大30条）
* 返回值  ： 0xff: 获取数据失败
*            0>: 数量
*/
UINT8_S GetLocalZcChangeLineNum(const UINT16_S localZcId, UINT16_S changeLineIdBuf[])
{
    UINT8_S retVal = 0xffu;/*函数返回值*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S index = 0u;/*数组偏移*/

    if(NULL != changeLineIdBuf)
    {
        for ( i = 0u; i < LineNumLineSwitchInfo; i++)
        {
            if ((localZcId == LineSwitchInfoDataStru[i].lineSwitchTraZcId)
                || (localZcId == LineSwitchInfoDataStru[i].lineSwitchTakeOverZcId))
            {
                changeLineIdBuf[index] = LineSwitchInfoDataStru[i].indexId;
                index=index+1;
            }
        }

        if(index != 0u)
        {
            retVal = index;
        }

    }

    return retVal;
}
