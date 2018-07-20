/*************************************************
  文件名   ：TrainTypeConfigData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： TrainTypeConfigData数据管理
			DmuCommonData组件的TrainTypeConfigData功能可分解如下：
			1）	给TrainTypeConfigDataStru结构体指针分配空间
			2）	获取TrainTypeConfigData数据
			3）	获取TrainTypeConfigData信息
			4）	获取指定IDTrainTypeConfigDataStru的结构体下标
			5）	获取指定IDTrainTypeConfigDataStru的结构体指针
			6）	获取指定IDTrainTypeConfigDataStru的列车类型

  备注    ：无。 
*************************************************/
#ifndef TRAINTYPECONFIG_DATA_H_
#define TRAINTYPECONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define TRAINTYPECONFIG_LINE_BYTE_NUM                    3u                  /*一行数据字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*列车车型配置表数据结构体*/
typedef struct BnfTrainTypeConfigStruct
{
    UINT16_S  trainDevName;            /*列车名称(TYPE+ID)*/        
    UINT8_S   trainType;                /*列车类型*/            
}BnfTrainTypeConfigStruct;

/*
* 功能描述： 给TrainTypeConfigDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocTrainTypeConfigDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取TrainTypeConfigData数据
* 参数说明：
* 返回值  ： 
            BnfTrainTypeConfigStruct*
*/
BnfTrainTypeConfigStruct *GetTrainTypeConfigData(void);

/*
* 功能描述： 获取TrainTypeConfigData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
*            BnfTrainTypeConfigStruct*
*/
BnfTrainTypeConfigStruct *GetTrainTypeConfigDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDTrainTypeConfigDataStru的结构体下标
* 参数说明： const UINT16_S trainDevName;列车名称(TYPE+ID)
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetTrainTypeConfigDataStruIndex(const UINT16_S trainDevName);

/*
** 功能描述： 获取指定IDTrainTypeConfigDataStru的结构体指针
* 参数说明： const UINT16_S trainDevName;列车名称(TYPE+ID)
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfTrainTypeConfigStruct* GetIndexIdTrainTypeConfigDataStru(const UINT16_S trainDevName);

/*
** 功能描述： 获取指定IDTrainTypeConfigDataStru的列车类型
* 参数说明： const UINT16_S trainDevName;列车名称(TYPE+ID)
* 返回值  :  0: 获取数据失败
*            >0: 列车类型
*/ 
UINT8_S GetTrainTypeConfigDataStrutrainType(const UINT16_S trainDevName);


#ifdef __cplusplus
}
#endif

#endif
