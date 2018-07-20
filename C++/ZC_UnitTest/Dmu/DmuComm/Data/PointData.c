/*************************************************
  文件名   ：PointData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： PointData数据管理
			DmuCommonData组件的PointData功能可分解如下：
			1）	给PointDataStru结构体指针分配空间
			2）	获取PointData数据
			3）	获取PointData信息
			4）	获取指定IDPointDataStru的结构体下标
			5）	获取指定IDPointDataStru的结构体指针
			6）	获取指定IDPointDataStru的名称
			7）	获取指定IDPointDataStru的起点轨道名称
			8）	获取指定IDPointDataStru的公里标(cm)
			9）	获取指定IDPointDataStru的点类型
			10）	获取指定IDPointDataStru的起点正向相邻点ID
			11）	获取指定IDPointDataStru的起点侧向相邻点ID
			12）	获取指定IDPointDataStru的终点正向相邻点ID
			13）	获取指定IDPointDataStru的终点侧向相邻点ID
			14）	获取指定IDPointDataStru的所属ZC区域编号
			15）	获取指定IDPointDataStru的所属ATS区域编号
			16）	获取指定IDPointDataStru的所属物理CI区域编号
  备注    ：无。
 
*************************************************/

#include "PointData.h"
#include "../../../Common/Malloc.h"

static BnfPointStruct* PointDataStru = NULL;   /*定义PointData数据结构体*/
static UINT16_S LineNumPoint = 0u;/*表行数*/


/*
* 功能描述： 给PointDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocPointDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == PointDataStru))
    {
        PointDataStru = (BnfPointStruct*)MemoryMalloc((UINT32_S)sizeof(BnfPointStruct) * lineNum);
        LineNumPoint = lineNum;
    }
}

/*
* 功能描述： 获取PointData数据
* 参数说明：
* 返回值  ： 
            BnfPointStruct*
*/
BnfPointStruct *GetPointData(void)
{
    return PointDataStru;
}


/*
* 功能描述： 获取PointData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfPointStruct*
*/
BnfPointStruct *GetPointDataInfo(UINT16_S* lineNum)
{

    BnfPointStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumPoint;
        retVal = PointDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDPointDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetPointDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumPoint; i++)
    {
        if (indexId == PointDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfPointStruct* GetIndexIdPointDataStru(const UINT16_S indexId)
{
    BnfPointStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = &PointDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的名称
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetPointDataStruname(const UINT16_S indexId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的起点轨道名称
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 起点轨道名称
*/ 
UINT8_S* GetPointDataStrustartPathwayName(const UINT16_S indexId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].startPathwayName;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的公里标(cm)
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 公里标(cm)
*/ 
UINT32_S GetPointDataStrulocation(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].location;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的点类型
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 点类型
*/ 
UINT16_S GetPointDataStrupointType(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].pointType;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的起点正向相邻点ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点正向相邻点ID
*/ 
UINT16_S GetPointDataStrustartJointMainLkId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].startJointMainLkId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的起点侧向相邻点ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点侧向相邻点ID
*/ 
UINT16_S GetPointDataStrustartJointSideLkId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].startJointSideLkId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的终点正向相邻点ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点正向相邻点ID
*/ 
UINT16_S GetPointDataStrutmnlJointMainLkId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].tmnlJointMainLkId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的终点侧向相邻点ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点侧向相邻点ID
*/ 
UINT16_S GetPointDataStrutmnlJointSideLkId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].tmnlJointSideLkId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的所属ZC区域编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属ZC区域编号
*/ 
UINT16_S GetPointDataStrumanageZCId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].manageZCId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的所属ATS区域编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属ATS区域编号
*/ 
UINT16_S GetPointDataStrumanageATSId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].manageATSId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPointDataStru的所属物理CI区域编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属物理CI区域编号
*/ 
UINT16_S GetPointDataStrumanageCIId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPointDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPoint)
    {
        retVal = PointDataStru[bufIndex].manageCIId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

