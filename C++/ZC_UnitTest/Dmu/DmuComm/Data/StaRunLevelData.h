/*************************************************
  文件名   ：StaRunLevelData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： StaRunLevelData数据管理
			DmuCommonData组件的StaRunLevelData功能可分解如下：
			1）	给StaRunLevelDataStru结构体指针分配空间
			2）	获取StaRunLevelData数据
			3）	获取StaRunLevelData信息
			4）	获取指定IDStaRunLevelDataStru的结构体下标
			5）	获取指定IDStaRunLevelDataStru的结构体指针
			6）	获取指定IDStaRunLevelDataStru的起点目的地编号
			7）	获取指定IDStaRunLevelDataStru的终点目的地编号
			8）	获取指定IDStaRunLevelDataStru的运行级别分级数目
			9）	获取指定IDStaRunLevelDataStru的
			10）	获取指定起点与终点的运行级别对应速度

  备注    ：无。
 
*************************************************/
#ifndef STARUNLEVEL_DATA_H_
#define STARUNLEVEL_DATA_H_

#include "../../../Common/CommonTypes.h"

#define STARUNLEVEL_LEVEL_NUM                      5                                   /*运行级别个数*/              
#define STARUNLEVEL_LINE_BYTE_NUM                 38                                /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*每个运行级别信息*/
typedef struct _SngRunLevelStruct
{
    UINT16_S levelId;               /*级别编号*/
    UINT16_S levelTime;             /*级别对应时间*/
    UINT16_S levelSpeed;            /*级别对应速度*/
}SngRunLevelStruct;

/*站间运营级别表数据结构体*/
typedef struct BnfStaRunLevelStruct
{
    UINT16_S  indexId;                           /*索引编号*/
    UINT16_S  startDestId;                       /*起点目的地编号*/
    UINT16_S  endDestId;                           /*终点目的地编号*/
    UINT16_S  runLevelNum;                       /*运行级别分级数目*/
    SngRunLevelStruct runLevelStru[STARUNLEVEL_LEVEL_NUM];
}BnfStaRunLevelStruct;

/*
* 功能描述： 给StaRunLevelDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocStaRunLevelDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取StaRunLevelData数据
* 参数说明：
* 返回值  ： 
            BnfStaRunLevelStruct*
*/
BnfStaRunLevelStruct *GetStaRunLevelData(void);

/*
* 功能描述： 获取StaRunLevelData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfStaRunLevelStruct*
*/
BnfStaRunLevelStruct *GetStaRunLevelDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDStaRunLevelDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetStaRunLevelDataStruIndex(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDStaRunLevelDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfStaRunLevelStruct* GetIndexIdStaRunLevelDataStru(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDStaRunLevelDataStru的起点目的地编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点目的地编号
*/ 
UINT16_S GetStaRunLevelDataStrustartDestId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDStaRunLevelDataStru的终点目的地编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点目的地编号
*/ 
UINT16_S GetStaRunLevelDataStruendDestId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDStaRunLevelDataStru的运行级别分级数目
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 运行级别分级数目
*/ 
UINT16_S GetStaRunLevelDataStrurunLevelNum(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDStaRunLevelDataStru的
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 
*/ 
SngRunLevelStruct* GetStaRunLevelDataStrurunLevelStru(const UINT16_S indexId);

/*
** 功能描述： 获取指定起点与终点的运行级别对应速度
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0 查询失败
*            > 0 : 查询的速度 
*/ 
UINT16_S GetSpdForLevelByStartToEnd(UINT16_S startId,UINT16_S endId,UINT16_S level);

#ifdef __cplusplus
}
#endif

#endif
