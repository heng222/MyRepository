/*************************************************
  文件名   ：ExitCbtcSectionData.c
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： ExitCbtcSectionData数据管理
			DmuCommonData组件的ExitCbtcSectionData功能可分解如下：
			1）	给ExitCbtcSectionDataStru结构体指针分配空间
			2）	获取ExitCbtcSectionData数据
			3）	获取ExitCbtcSectionData信息
			4）	获取指定IDExitCbtcSectionDataStru的结构体下标
			5）	获取指定IDExitCbtcSectionDataStru的结构体指针
			6）	 获取指定IDExitCbtcSectionDataStru的退出CBTC区域时列车运行方向
			7）	获取指定IDExitCbtcSectionDataStru的退出CBTC区域属性
			8）	 获取指定IDExitCbtcSectionDataStru的起点所处seg编号
			9）	获取指定IDExitCbtcSectionDataStru的起点所处Seg偏移量
			10）	获取指定IDExitCbtcSectionDataStru的终点所处Seg偏移量
			11）	获取指定IDExitCbtcSectionDataStru的包含的Seg数目
			12）	获取指定IDExitCbtcSectionDataStru的SEG编号
			13）	查询某个点是否和退出CBTC区域终点重合
			14）	查询某个点是否属于CBTC区域

  备注    ：无。
 
*************************************************/

#include "ExitCbtcSectionData.h"
#include "../../../Common/Malloc.h"

static BnfExitCbtcSectionStruct* ExitCbtcSectionDataStru = NULL;   /*定义ExitCbtcSectionData数据结构体*/
static UINT16_S LineNumExitCbtcSection = 0u;/*表行数*/


/*
* 功能描述： 给ExitCbtcSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocExitCbtcSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ExitCbtcSectionDataStru))
    {
        ExitCbtcSectionDataStru = (BnfExitCbtcSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfExitCbtcSectionStruct) * lineNum);
        LineNumExitCbtcSection = lineNum;
    }
}

/*
* 功能描述： 获取ExitCbtcSectionData数据
* 参数说明：
* 返回值  ： 
            BnfExitCbtcSectionStruct*
*/
BnfExitCbtcSectionStruct *GetExitCbtcSectionData(void)
{
    return ExitCbtcSectionDataStru;
}


/*
* 功能描述： 获取ExitCbtcSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfExitCbtcSectionStruct*
*/
BnfExitCbtcSectionStruct *GetExitCbtcSectionDataInfo(UINT16_S* lineNum)
{
    BnfExitCbtcSectionStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumExitCbtcSection;
        retVal = ExitCbtcSectionDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetExitCbtcSectionDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumExitCbtcSection; i++)
    {
        if (indexId == ExitCbtcSectionDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfExitCbtcSectionStruct* GetIndexIdExitCbtcSectionDataStru(const UINT16_S indexId)
{
    BnfExitCbtcSectionStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = &ExitCbtcSectionDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的退出CBTC区域时列车运行方向
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 退出CBTC区域时列车运行方向
*/ 
UINT16_S GetExitCbtcSectionDataStrudir(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].dir;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的退出CBTC区域属性
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 退出CBTC区域属性
*/ 
UINT16_S GetExitCbtcSectionDataStruattribute(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].attribute;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的起点所处seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处seg编号
*/ 
UINT16_S GetExitCbtcSectionDataStrustartSegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].startSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的起点所处Seg偏移量
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处Seg偏移量
*/ 
UINT32_S GetExitCbtcSectDataStartOff(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].startOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的终点所处Seg偏移量
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点所处Seg偏移量
*/ 
UINT32_S GetExitCbtcSectionDataStruendOffSet(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].endOffSet;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的包含的Seg数目
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含的Seg数目
*/ 
UINT16_S GetExitCbtcSectionDataStrusegNum(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].segNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的SEG编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: SEG编号
*/ 
UINT16_S* GetExitCbtcSectionDataStrusegInfoBuff(const UINT16_S indexId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].segInfoBuff;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/* 功能描述： 查询某个点是否和退出CBTC区域终点重合
* 参数说明： 
* 返回值  ： 
*    1,重合
*    2,不重合
*/
UINT8_S CheckAtQuitCbtcIsFindPoint(const UINT16_S seg,const UINT32_S offset)
{
    UINT8_S retVal = 2u;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/
    UINT16_S j =0u;/*循环使用*/

    for ( i = 0u; i < LineNumExitCbtcSection; i++)
    {
        for (j = 0u; j < ExitCbtcSectionDataStru[i].segNum; j++)
        {
            if ((seg == ExitCbtcSectionDataStru[i].segInfoBuff[j])&&(offset == ExitCbtcSectionDataStru[i].endOffSet))
            {
                retVal = 1u;
                break;
            }
        }

    }
    return retVal;
}

/* 功能描述： 查询某个点是否属于CBTC区域
* 参数说明： 
* 返回值  ： 
*    0,不属于
*    1,属于
*/
UINT8_S ExitCbtcSecIncludePoint(UINT16_S segId,UINT32_S offset)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S i = 0u;    /*循环使用*/
    UINT16_S j = 0u;    /*循环使用*/
    UINT8_S flag = 0u;  /* 找到标志 ,初始化为未找到*/

    for ( i = 0u; i < LineNumExitCbtcSection; i++)
    {
        for (j = 0u; j < ExitCbtcSectionDataStru[i].segNum; j++)
        {
            if ((segId == ExitCbtcSectionDataStru[i].segInfoBuff[j]))
            {
                if (ExitCbtcSectionDataStru[i].startOffset < ExitCbtcSectionDataStru[i].endOffSet)
                {
                    /* 退出区域的起点小于终点 */
                    if ((offset>= ExitCbtcSectionDataStru[i].startOffset)&&(offset <= ExitCbtcSectionDataStru[i].endOffSet))
                    {
                        flag = 1u;
                    }
                } 
                else
                {
                    /* 退出区域的起点大于终点 */
                    if ((offset <= ExitCbtcSectionDataStru[i].startOffset)&&(offset >= ExitCbtcSectionDataStru[i].endOffSet))
                    {
                        flag = 1u;
                    }
                }
                
                if (1u == flag)
                {
                    break;
                }
                
            }
        }
        if (1u == flag)
        {
            break;
        }

    }

    if(1u == flag)
    {
        retVal = 1u;
    }
    return retVal;
}
