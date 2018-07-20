/*************************************************
  文件名   ：GradeData.h
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
#ifndef GRADE_DATA_H_
#define GRADE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  GRADE_LINE_BYTE_NUM            34                        /*一行数据字节数*/
#define     GRADE_INCLUDE_LINK_NUM            10                        /*坡度中间SEG最大值*/

#ifdef __cplusplus
extern "C" {
#endif

/*坡度表*/
typedef struct BnfGradeStruct
{
    UINT16_S  gradeId;                                /*编号*/
    UINT16_S  orgnSegId;                                /*坡度起点所处Seg编号*/
    UINT32_S  orgnSegOfst;                            /*坡度起点所处Seg偏移量*/
    UINT16_S  tmnlSegId;                                /*坡度终点所处Seg编号*/
    UINT32_S  tmnlSegOfst;                            /*坡度终点所处Seg偏移量*/    
    UINT16_S    orgnRelatePointId;                        /*起点关联道岔编号*/
    UINT16_S  orgnJointMainGradeId;                    /*起点正线坡度编号*/
    UINT16_S  orgnJointSideGradeId;                    /*起点侧线坡度编号*/
    UINT16_S    tmnlRelatePointId;                        /*终点关联道岔编号*/
    UINT16_S  tmnlJointMainGradeId;                    /*终点正线坡度编号*/    
    UINT16_S  tmnlJointSideGradeId;                    /*终点侧线坡度编号*/
    UINT16_S  gradValue;                                /*坡度值*/
    UINT16_S  inclineDir;                                /*坡段相对于线路逻辑方向的倾斜方向*/
    UINT32_S  radius;                                    /*竖曲线半径*/

    /*动态计算*/
    UINT32_S  orgnSegIdLength;                        /*坡度起点所处Seg长度*/
    UINT32_S  tmnlSegIdLength;                        /*坡度终点所处Seg长度*/
    UINT8_S    includeSegNum;                            /*包含的SEGID个数*/
    UINT16_S    segIdBuff[GRADE_INCLUDE_LINK_NUM];        /*包含的SEGID*/
    UINT32_S    segIdLength[GRADE_INCLUDE_LINK_NUM];    /*包含SEG的长度*/
    UINT32_S gradeLength;                                /*坡度长度*/    
}BnfGradeStruct;

/*
* 功能描述： 给GradeDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocGradeDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取GradeData数据
* 参数说明：
* 返回值  ： 
            BnfGradeStruct*
*/
BnfGradeStruct *GetGradeData(void);

/*
* 功能描述：获取GradeData表行数
* 参数说明：无
* 返回值  ：UINT16
*/
UINT16_S GetGradeDataLineNum(void);

/*
* 功能描述： 获取GradeData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfGradeStruct*
*/
BnfGradeStruct *GetGradeDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDGradeDataStru的结构体下标
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetGradeDataStruIndex(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的结构体指针
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfGradeStruct* GetIndexIdGradeDataStru(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的坡度起点所处Seg编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡度起点所处Seg编号
*/ 
UINT16_S GetGradeDataStruorgnSegId(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的坡度起点所处Seg偏移量
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡度起点所处Seg偏移量
*/ 
UINT32_S GetGradeDataStruorgnSegOfst(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的坡度终点所处Seg编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡度终点所处Seg编号
*/ 
UINT16_S GetGradeDataStrutmnlSegId(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的坡度终点所处Seg偏移量
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡度终点所处Seg偏移量
*/ 
UINT32_S GetGradeDataStrutmnlSegOfst(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的起点正线坡度编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 起点正线坡度编号
*/ 
UINT16_S GetGradeDataStruorgnJointMainGradeId(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的起点侧线坡度编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 起点侧线坡度编号
*/ 
UINT16_S GetGradeDataStruorgnJointSideGradeId(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的终点正线坡度编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 终点正线坡度编号
*/ 
UINT16_S GetGradeDataStrutmnlJointMainGradeId(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的终点侧线坡度编号
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 终点侧线坡度编号
*/ 
UINT16_S GetGradeDataStrutmnlJointSideGradeId(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的坡度值
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡度值
*/ 
UINT16_S GetGradeDataStrugradValue(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的坡段相对于线路逻辑方向的倾斜方向
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 坡段相对于线路逻辑方向的倾斜方向
*/ 
UINT16_S GetGradeDataStruinclineDir(const UINT16_S gradeId);

/*
** 功能描述： 获取指定IDGradeDataStru的竖曲线半径
* 参数说明： const UINT16_S gradeId;编号
* 返回值  :  0: 获取数据失败
*            >0: 竖曲线半径
*/ 
UINT32_S GetGradeDataStruradius(const UINT16_S gradeId);


#ifdef __cplusplus
}
#endif

#endif
