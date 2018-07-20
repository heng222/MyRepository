/*************************************************
  文件名   ：ConGradeData.h
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
#ifndef CONGRADE_DATA_H_
#define CONGRADE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  CONGRADE_LINE_BYTE_NUM             3                                            /*一行数据字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*统一限速表数据结构体*/
typedef struct BnfConGradeDataStruct
{
    UINT8_S  index;                                        /*索引编号*/
    UINT16_S grade;                                        /*坡度值*/
}BnfConGradeDataStruct;

/*
* 功能描述： 给BnfConGradeStruct结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocConGradeDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取ConGrade数据
* 参数说明：
* 返回值  ： 
            BnfConGradeStruct*
*/
BnfConGradeDataStruct *GetConGradeData(void);

/*
* 功能描述： 获取ConGrade信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfConGradeStruct*
*/
BnfConGradeDataStruct *GetConGradeDataInfo(UINT16_S* lineNum);

/*
* 功能描述： 获取统一限速表中的坡度值
* 参数说明：无
* 返回值  ：0xFFFF 无效
            其他:有效
*/
UINT16_S GetConGradeValue(void);

#ifdef __cplusplus
}
#endif

#endif
