/*************************************************
  文件名   ：GradeData.c
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： GradeData数据管理
			DmuCommonData组件的GradeData功能可分解如下：
			1）	给GradeDataStru结构体指针分配空间
			2）	获取GradeData数据
			3）	获取GradeData表行数
			4）	获取GradeData信息
			5）	获取指定IDGradeDataStru的结构体下标
			6）	获取指定IDGradeDataStru的结构体指针
			7）	获取指定IDGradeDataStru的坡度起点所处Seg编号
			8）	获取指定IDGradeDataStru的坡度起点所处Seg偏移量
			9）	获取指定IDGradeDataStru的坡度终点所处Seg编号
			10）	获取指定IDGradeDataStru的坡度终点所处Seg偏移量
			11）	获取指定IDGradeDataStru的起点正线坡度编号
			12）	获取指定IDGradeDataStru的起点侧线坡度编号
			13）	获取指定IDGradeDataStru的终点正线坡度编号
			14）	获取指定IDGradeDataStru的终点侧线坡度编号
			15）	获取指定IDGradeDataStru的坡度值
			16）	获取指定IDGradeDataStru的坡段相对于线路逻辑方向的倾斜方向
			17）	获取指定IDGradeDataStru的竖曲线半径
  备注    ：无。
 
*************************************************/

#include "GradeData.h"
#include "../../../Common/Malloc.h"

static BnfGradeStruct* GradeDataStru = NULL;   /*定义GradeData数据结构体*/
static UINT16_S LineNumGrade = 0u;/*表行数*/


/*
* 功能描述： 给GradeDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocGradeDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == GradeDataStru))
    {
        GradeDataStru = (BnfGradeStruct*)MemoryMalloc((UINT32_S)sizeof(BnfGradeStruct) * lineNum);
        LineNumGrade = lineNum;
    }
}

/*
* 功能描述： 获取GradeData数据
* 参数说明：
* 返回值  ： 
BnfGradeStruct*
*/
BnfGradeStruct *GetGradeData(void)
{
    return GradeDataStru;
}

/*
* 功能描述：获取GradeData表行数
* 参数说明：无
* 返回值  ：UINT16
*/
UINT16_S GetGradeDataLineNum(void)
{
    return LineNumGrade;
}


/*
* 功能描述： 获取GradeData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
BnfGradeStruct*
*/
BnfGradeStruct *GetGradeDataInfo(UINT16_S* lineNum)
{

    BnfGradeStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumGrade;
        retVal = GradeDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDGradeDataStru的结构体下标
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetGradeDataStruIndex(const UINT16_S gradeId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumGrade; i++)
    {
        if (gradeId == GradeDataStru[i].gradeId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的结构体指针
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfGradeStruct* GetIndexIdGradeDataStru(const UINT16_S gradeId)
{
    BnfGradeStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = &GradeDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的坡度起点所处Seg编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡度起点所处Seg编号
*/ 
UINT16_S GetGradeDataStruorgnSegId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].orgnSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的坡度起点所处Seg偏移量
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡度起点所处Seg偏移量
*/ 
UINT32_S GetGradeDataStruorgnSegOfst(const UINT16_S gradeId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].orgnSegOfst;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的坡度终点所处Seg编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡度终点所处Seg编号
*/ 
UINT16_S GetGradeDataStrutmnlSegId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].tmnlSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的坡度终点所处Seg偏移量
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡度终点所处Seg偏移量
*/ 
UINT32_S GetGradeDataStrutmnlSegOfst(const UINT16_S gradeId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].tmnlSegOfst;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的起点正线坡度编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 起点正线坡度编号
*/ 
UINT16_S GetGradeDataStruorgnJointMainGradeId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].orgnJointMainGradeId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的起点侧线坡度编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 起点侧线坡度编号
*/ 
UINT16_S GetGradeDataStruorgnJointSideGradeId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].orgnJointSideGradeId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的终点正线坡度编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 终点正线坡度编号
*/ 
UINT16_S GetGradeDataStrutmnlJointMainGradeId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].tmnlJointMainGradeId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的终点侧线坡度编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 终点侧线坡度编号
*/ 
UINT16_S GetGradeDataStrutmnlJointSideGradeId(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].tmnlJointSideGradeId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的坡度值
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡度值
*/ 
UINT16_S GetGradeDataStrugradValue(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].gradValue;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的坡段相对于线路逻辑方向的倾斜方向
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡段相对于线路逻辑方向的倾斜方向
*/ 
UINT16_S GetGradeDataStruinclineDir(const UINT16_S gradeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].inclineDir;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDGradeDataStru的竖曲线半径
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 竖曲线半径
*/ 
UINT32_S GetGradeDataStruradius(const UINT16_S gradeId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetGradeDataStruIndex(gradeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumGrade)
    {
        retVal = GradeDataStru[bufIndex].radius;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

