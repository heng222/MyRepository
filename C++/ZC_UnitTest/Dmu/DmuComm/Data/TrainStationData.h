/*************************************************
  文件名   ：TrainStationData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： TrainStationData数据管理
			DmuCommonData组件的TrainStationData功能可分解如下：
			1）	给TrainStationDataStru结构体指针分配空间
			2）	获取TrainStationData数据
			3）	获取TrainStationData信息
			4）	获取指定IDTrainStationDataStru的结构体下标
			5）	获取指定IDTrainStationDataStru的结构体指针
			6）	获取指定IDTrainStationDataStru的车站名称
			7）	获取指定IDTrainStationDataStru的车站包含站台数目
			8）	获取指定IDTrainStationDataStru的站台编号
  备注    ：无。 
*************************************************/
#ifndef TRAINSTATION_DATA_H_
#define TRAINSTATION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define TRAINSTATION_NAME_BYTE_LEN                 16                                                            /*名称长度*/
#define TRAINSTATION_ID_MAX_NUM                     6                                                            /*最大站台编号*/
#define TRAINSTATION_LINE_BYTE_NUM                 32                                                       /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*车站表数据结构体*/
typedef struct BnfTrainStationStruct
{
    UINT16_S  stationId;                                /*车站ID*/
    UINT8_S   name[TRAINSTATION_NAME_BYTE_LEN];        /*车站名称*/
    UINT16_S  includeStationNum;                        /*车站包含站台数目*/
    UINT16_S  stationIdBuff[TRAINSTATION_ID_MAX_NUM];      /*站台编号*/
}BnfTrainStationStruct;

/*
* 功能描述： 给TrainStationDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocTrainStationDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取TrainStationData数据
* 参数说明：
* 返回值  ： 
            BnfTrainStationStruct*
*/
BnfTrainStationStruct *GetTrainStationData(void);

/*
* 功能描述： 获取TrainStationData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfTrainStationStruct*
*/
BnfTrainStationStruct *GetTrainStationDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDTrainStationDataStru的结构体下标
* 参数说明： const UINT16_S stationId;车站ID
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetTrainStationDataStruIndex(const UINT16_S stationId);

/*
** 功能描述： 获取指定IDTrainStationDataStru的结构体指针
* 参数说明： const UINT16_S stationId;车站ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfTrainStationStruct* GetIndexIdTrainStationDataStru(const UINT16_S stationId);

/*
** 功能描述： 获取指定IDTrainStationDataStru的车站名称
* 参数说明： const UINT16_S stationId;车站ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 车站名称
*/ 
UINT8_S* GetTrainStationDataStruname(const UINT16_S stationId);

/*
** 功能描述： 获取指定IDTrainStationDataStru的车站包含站台数目
* 参数说明： const UINT16_S stationId;车站ID
* 返回值  :  0: 获取数据失败
*            >0: 车站包含站台数目
*/ 
UINT16_S GetTrainStationDataStruincludeStationNum(const UINT16_S stationId);

/*
** 功能描述： 获取指定IDTrainStationDataStru的站台编号
* 参数说明： const UINT16_S stationId;车站ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 站台编号
*/ 
UINT16_S* GetTrainStationDataStrustationIdBuff(const UINT16_S stationId);


#ifdef __cplusplus
}
#endif

#endif
