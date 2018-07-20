/*************************************************
  文件名   ：TrainControlLevelData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： TrainControlLevelData数据管理
			DmuCommonData组件的TrainControlLevelData功能可分解如下：
			1）	给TrainControlLevelDataStru结构体指针分配空间
			2）	获取TrainControlLevelData数据
			3）	获取TrainControlLevelData信息
			4）	获取指定IDTrainControlLevelDataStru的结构体下标
			5）	获取指定IDTrainControlLevelDataStru的结构体指针
			6）	获取指定IDTrainControlLevelDataStru的起点所处seg编号
			7）	获取指定IDTrainControlLevelDataStru的起点所处Seg偏移量
			8）	获取指定IDTrainControlLevelDataStru的终点所处seg编号
			9）	获取指定IDTrainControlLevelDataStru的终点所处Seg偏移量
			10）	获取指定IDTrainControlLevelDataStru的非CBTC区域列车运行方向

  备注    ：无。 
*************************************************/
#ifndef TRAINCONTROLLEVEL_DATA_H_
#define TRAINCONTROLLEVEL_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  TRAINCONTROLLEVEL_LINE_BYTE_NUM                 16                              /*一行数据字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*非CBTC区域表数据结构体*/
typedef struct BnfTrainControlLevelStruct
{
    UINT16_S  indexId;                               /*索引编号*/
    UINT16_S  startSegId;                               /*起点所处seg编号*/
    UINT32_S  startOffset;                        /*起点所处Seg偏移量*/
    UINT16_S  endSegId;                               /*终点所处seg编号*/
    UINT32_S  endOffset;                               /*终点所处Seg偏移量*/
    UINT16_S  dir;                                   /*非CBTC区域列车运行方向*/
}BnfTrainControlLevelStruct;

/*
* 功能描述： 给TrainControlLevelDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocTrainControlLevelDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取TrainControlLevelData数据
* 参数说明：
* 返回值  ： 
            BnfTrainControlLevelStruct*
*/
BnfTrainControlLevelStruct *GetTrainControlLevelData(void);

/*
* 功能描述： 获取TrainControlLevelData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfTrainControlLevelStruct*
*/
BnfTrainControlLevelStruct *GetTrainControlLevelDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDTrainControlLevelDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetTrainControlLevelDataStruIndex(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDTrainControlLevelDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfTrainControlLevelStruct* GetIndexIdTrainControlLevelDataStru(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDTrainControlLevelDataStru的起点所处seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处seg编号
*/ 
UINT16_S GetTrainControlLevelDataStrustartSegId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDTrainControlLevelDataStru的起点所处Seg偏移量
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处Seg偏移量
*/ 
UINT32_S GetTrContrLevDataStartOff(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDTrainControlLevelDataStru的终点所处seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点所处seg编号
*/ 
UINT16_S GetTrainControlLevelDataStruendSegId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDTrainControlLevelDataStru的终点所处Seg偏移量
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点所处Seg偏移量
*/ 
UINT32_S GetTrContrLevDataOff(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDTrainControlLevelDataStru的非CBTC区域列车运行方向
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 非CBTC区域列车运行方向
*/ 
UINT16_S GetTrainControlLevelDataStrudir(const UINT16_S indexId);


#ifdef __cplusplus
}
#endif

#endif
