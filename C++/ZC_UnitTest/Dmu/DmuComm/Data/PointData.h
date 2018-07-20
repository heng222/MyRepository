/*************************************************
  文件名   ：PointData.h
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
#ifndef POINT_DATA_H_
#define POINT_DATA_H_

#include "../../../Common/CommonTypes.h"

#define POINT_MAX_NAME_LEN                  16                              /*名称长度*/
#define POINT_LINE_BYTE_NUM                 44                         /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*点表数据结构体*/
typedef struct BnfPointStruct
{
    UINT16_S  indexId;                                        /*索引编号*/
    UINT8_S  name[POINT_MAX_NAME_LEN];                        /*名称*/
    UINT8_S  startPathwayName[POINT_MAX_NAME_LEN];            /*起点轨道名称*/
    UINT32_S  location;                                          /*公里标(cm)*/  
    UINT16_S  pointType;                                        /*点类型*/
    UINT16_S  startJointMainLkId;                                /*起点正向相邻点ID*/
    UINT16_S  startJointSideLkId;                                /*起点侧向相邻点ID*/
    UINT16_S  tmnlJointMainLkId;                                /*终点正向相邻点ID*/
    UINT16_S  tmnlJointSideLkId;                                /*终点侧向相邻点ID*/
    UINT16_S  manageZCId;                                        /*所属ZC区域编号*/
    UINT16_S  manageATSId;                                    /*所属ATS区域编号*/
    UINT16_S  manageCIId;                                /*所属物理CI区域编号*/ 
}BnfPointStruct;

/*
* 功能描述： 给PointDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocPointDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取PointData数据
* 参数说明：
* 返回值  ： 
            BnfPointStruct*
*/
BnfPointStruct *GetPointData(void);

/*
* 功能描述： 获取PointData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfPointStruct*
*/
BnfPointStruct *GetPointDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDPointDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetPointDataStruIndex(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfPointStruct* GetIndexIdPointDataStru(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的名称
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetPointDataStruname(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的起点轨道名称
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 起点轨道名称
*/ 
UINT8_S* GetPointDataStrustartPathwayName(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的公里标(cm)
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 公里标(cm)
*/ 
UINT32_S GetPointDataStrulocation(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的点类型
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 点类型
*/ 
UINT16_S GetPointDataStrupointType(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的起点正向相邻点ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点正向相邻点ID
*/ 
UINT16_S GetPointDataStrustartJointMainLkId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的起点侧向相邻点ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点侧向相邻点ID
*/ 
UINT16_S GetPointDataStrustartJointSideLkId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的终点正向相邻点ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点正向相邻点ID
*/ 
UINT16_S GetPointDataStrutmnlJointMainLkId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的终点侧向相邻点ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点侧向相邻点ID
*/ 
UINT16_S GetPointDataStrutmnlJointSideLkId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的所属ZC区域编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属ZC区域编号
*/ 
UINT16_S GetPointDataStrumanageZCId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的所属ATS区域编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属ATS区域编号
*/ 
UINT16_S GetPointDataStrumanageATSId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDPointDataStru的所属物理CI区域编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属物理CI区域编号
*/ 
UINT16_S GetPointDataStrumanageCIId(const UINT16_S indexId);


#ifdef __cplusplus
}
#endif

#endif
