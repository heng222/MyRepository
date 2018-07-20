/*************************************************
  文件名   ：SegData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SegData数据管理
			DmuCommonData组件的SegData功能可分解如下：
			1）	给SegDataStru结构体指针分配空间
			2）	获取SEG表的行数
			3）	获取SegData数据
			4）	获取SegData信息
			5）	获取指定IDSegDataStru的结构体下标
			6）	获取指定IDSegDataStru的结构体指针
			7）	 获取指定IDSegDataStru的长度（cm)
			8）	获取指定IDSegDataStru的起点端点类型
			9）	获取指定IDSegDataStru的起点端点编号
			10）	获取指定IDSegDataStru的终点端点类型
			11）	获取指定IDSegDataStru的终点端点编号
			12）	获取指定IDSegDataStru的起点正向相邻SegID
			13）	获取指定IDSegDataStru的起点侧向相邻点SegID
			14）	获取指定IDSegDataStru的终点正向相邻点SegID
			15）	获取指定IDSegDataStru的终点侧向相邻点SegID
			16）	获取指定IDSegDataStru的所属ZC区域ID
			17）	获取指定IDSegDataStru的所属ATS区域ID
			18）	获取指定IDSegDataStru的所属CI区域ID
			19）	获取指定IDSegDataStru的终点端点编号和终点端点类型
			20）	获取指定IDSegDataStru的起点端点编号和起点端点类型
			21）	获取指定点指定位置的SEG信息
			22）	获取指定CIID获取ZCID
  备注    ：无。
 
*************************************************/


#include "SegData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"

static BnfSegStruct* SegDataStru = NULL;   /*定义SegData数据结构体*/
static UINT16_S LineNumSeg = 0u;/*表行数*/


/*
* 功能描述： 给SegDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSegDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SegDataStru))
    {
        SegDataStru = (BnfSegStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSegStruct) * lineNum);
        LineNumSeg = lineNum;
    }
    

}

/*获取SEG表的行数*/
UINT16_S GetSegIdNum(void)
{
    return LineNumSeg;
}

/*
* 功能描述： 获取SegData数据
* 参数说明：
* 返回值  ： 
            BnfSegStruct*
*/
BnfSegStruct *GetSegData(void)
{
    return SegDataStru;
}


/*
* 功能描述： 获取SegData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSegStruct*
*/
BnfSegStruct *GetSegDataInfo(UINT16_S* lineNum)
{
    BnfSegStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSeg;
        retVal = SegDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDSegDataStru的结构体下标
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSegDataStruIndex(const UINT16_S segId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumSeg; i++)
    {
        if (segId == SegDataStru[i].segId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的结构体指针
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSegStruct* GetIndexIdSegDataStru(const UINT16_S segId)
{
    BnfSegStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = &SegDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的长度（cm)
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 长度（cm)
*/ 
UINT32_S GetSegDataStrulength(const UINT16_S segId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].length;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的起点端点类型
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点端点类型
*/ 
UINT16_S GetSegDataStrustartPointType(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].startPointType;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的起点端点编号
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点端点编号
*/ 
UINT16_S GetSegDataStrustartPointId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].startPointId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的终点端点类型
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点端点类型
*/ 
UINT16_S GetSegDataStruendPointType(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].endPointType;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的终点端点编号
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点端点编号
*/ 
UINT16_S GetSegDataStruendPointId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].endPointId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的起点正向相邻SegID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点正向相邻SegID
*/ 
UINT16_S GetSegDataStrusegStartJointMainSegId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segStartJointMainSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的起点侧向相邻点SegID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点侧向相邻点SegID
*/ 
UINT16_S GetSegDataStrusegStartJointSideSegId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segStartJointSideSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的终点正向相邻点SegID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点正向相邻点SegID
*/ 
UINT16_S GetSegDataStrusegTmnlJointMainSegId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segTmnlJointMainSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的终点侧向相邻点SegID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点侧向相邻点SegID
*/ 
UINT16_S GetSegDataStrusegTmnlJointSideSegId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segTmnlJointSideSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的所属ZC区域ID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属ZC区域ID
*/ 
UINT16_S GetSegDataStrusegManageZCId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segManageZCId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的所属ATS区域ID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属ATS区域ID
*/ 
UINT16_S GetSegDataStrusegManageATSId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segManageATSId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的所属CI区域ID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属CI区域ID
*/ 
UINT16_S GetSegDataStrusegManageCIId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segManageCIId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的终点端点编号和终点端点类型
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点端点编号
*/ 
UINT16_S GetSegDataStruendPointInfo(const UINT16_S segId,UINT16_S* pointType)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/

    if(NULL != pointType)
    {
        bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
        if (bufIndex < LineNumSeg)
        {
            retVal = SegDataStru[bufIndex].endPointId;
            *pointType = SegDataStru[bufIndex].endPointType;
        }
        else
        {
            /*Do nothing currently !*/
        }
    }

    return retVal;
}

/*
** 功能描述： 获取指定IDSegDataStru的起点端点编号和起点端点类型
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点端点编号
*/ 
UINT16_S GetSegDataStrustartPointInfo(const UINT16_S segId,UINT16_S* pointType)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/

    if(NULL != pointType)
    {
        bufIndex = GetSegDataStruIndex(segId);/*获取结构体数组下标*/
        if (bufIndex < LineNumSeg)
        {
            retVal = SegDataStru[bufIndex].startPointId;
            *pointType = SegDataStru[bufIndex].startPointType;
        }
        else
        {
            /*Do nothing currently !*/
        }
    }

    return retVal;
}

/*
** 功能描述： 获取指定点指定位置的SEG信息
* 参数说明： const UINT16_S pointId;点编号
*             const UINT8_S startOrEnd  此点为起点或终点  1 起点 2 终点
*             BnfSegStruct* pSegStru SEG结构体信息指针
* 返回值  :  0: 获取数据失败
*            >0: 终点端点编号
*/ 
UINT8_S GetSegInfoBuffAccordPointId(UINT16_S pointId,const UINT8_S startOrEnd,BnfSegStruct* pSegStru)
{
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S index = 0u;/*结构体数据下标*/

    if ((startOrEnd != START_POINT)&&(startOrEnd != END_POINT)&&(pSegStru == NULL))
    {
/*Do nothing currently !*/
    }
    else
    {
        for (i = 0u;(i < LineNumSeg)&&(index < ONEPOINT_SAMEDIR_INCLUDE_SEG); i++)
        {
            if (START_POINT == startOrEnd)
            {
                if (pointId == SegDataStru[i].startPointId)
                {
                    pSegStru[index] = SegDataStru[i];
                    index=index+1;
                }
            }
            else
            {
                if (pointId == SegDataStru[i].endPointId)
                {
                    pSegStru[index] = SegDataStru[i];
                    index=index+1;
                }
            }
        }
    }
    
    return index;
}

/*
** 功能描述： 获取指定CIID获取ZCID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: ZCID
*/ 
UINT16_S ArrordCiIdGetZcId(const UINT16_S ciId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumSeg; i++)
    {
        if (ciId == SegDataStru[i].segManageCIId)
        {
            retVal = SegDataStru[i].segManageZCId;
            break;
        }
    }
    return retVal;
}
