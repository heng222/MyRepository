/*************************************************
  文件名   ：ConGradeData.c
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： ConGradeData数据管理
			DmuCommonData组件的ConGradeData功能可分解如下：
			1）	给BnfConGradeStruct结构体指针分配空间
			2）	获取ConGrade数据
			3）	获取ConGrade信息
			4）	获取统一限速表中的坡度值
  备注    ：无。
 
*************************************************/

#include "ConGradeData.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/Copy.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfConGradeDataStruct* ConGradeDataStru = NULL;   /*定义ConGradeData数据结构体*/
static UINT16_S LineNumConGrade = 0u;/*表行数*/


/*
* 功能描述： 给BnfConGradeStruct结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocConGradeDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ConGradeDataStru))
    {
        ConGradeDataStru = (BnfConGradeDataStruct*)MemoryMalloc((UINT32_S)sizeof(BnfConGradeDataStruct) * lineNum);
        LineNumConGrade = lineNum;
    }
}

/*
* 功能描述： 获取ConGrade数据
* 参数说明：
* 返回值  ： 
            BnfConGradeStruct*
*/
BnfConGradeDataStruct *GetConGradeData(void)
{
    return ConGradeDataStru;
}


/*
* 功能描述： 获取ConGrade信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfConGradeStruct*
*/
BnfConGradeDataStruct *GetConGradeDataInfo(UINT16_S* lineNum)
{

    BnfConGradeDataStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumConGrade;
        retVal =  ConGradeDataStru;

    }
    return retVal;
}

/*
* 功能描述： 获取统一限速表中的坡度值
* 参数说明：无
* 返回值  ：0xFFFF 无效
            其他:有效
*/
UINT16_S GetConGradeValue(void)
{
    UINT16_S retVal = UINT16_NULL;
    if (NULL != ConGradeDataStru)
    {
        retVal = ConGradeDataStru[0].grade;
    }

    return retVal;
}
