/*************************************************
  文件名   ：SystemAccTableData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SystemAccTableData数据管理
			DmuCommonData组件的SystemAccTableData功能可分解如下：
			1）	给SystemAccTableDataStru结构体指针分配空间
			2）	获取SystemAccTableData数据
			3）	获取SystemAccTableData信息
			4）	获取指定IDSystemAccTableDataStru的结构体下标
			5）	获取指定IDSystemAccTableDataStru的结构体指针
			6）	获取指定IDSystemAccTableDataStru的分段速度下限。根据车辆提供的牵引特性曲线分段得出，单位km/h
			7）	获取指定IDSystemAccTableDataStru的分段速度上限。根据车辆提供的牵引特性曲线分段得出，单位km/h
			8）	获取指定IDSystemAccTableDataStru的分段加速度值。根据车辆提供的牵引特性曲线分段得出，单位cm/s2
			9）	获取牵引加速度

  备注    ：无。
 
*************************************************/
#ifndef SYSTEMACCTABLE_DATA_H_
#define SYSTEMACCTABLE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  SYSTEMACCTABLE_LINE_BYTE_NUM                 4                            /*一行数据字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*列车最大牵引加速度分段取值表数据结构体*/
typedef struct BnfSystemAccTableStruct
{
    UINT8_S  trainType;            /*列车车型*/    
    UINT8_S  lowerLimitSpeed;        /*分段速度下限。根据车辆提供的牵引特性曲线分段得出，单位km/h*/
    UINT8_S  upperLimitSpeed;        /*分段速度上限。根据车辆提供的牵引特性曲线分段得出，单位km/h*/
    UINT8_S  accValue;            /*分段加速度值。根据车辆提供的牵引特性曲线分段得出，单位cm/s2*/    
}BnfSystemAccTableStruct;

/*
* 功能描述： 给SystemAccTableDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSystemAccTableDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取SystemAccTableData数据
* 参数说明：
* 返回值  ： 
            BnfSystemAccTableStruct*
*/
BnfSystemAccTableStruct *GetSystemAccTableData(void);

/*
* 功能描述： 获取SystemAccTableData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSystemAccTableStruct*
*/
BnfSystemAccTableStruct *GetSystemAccTableDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDSystemAccTableDataStru的结构体下标
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSystemAccTableDataStruIndex(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDSystemAccTableDataStru的结构体指针
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSystemAccTableStruct* GetIndexIdSystemAccTableDataStru(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDSystemAccTableDataStru的分段速度下限。根据车辆提供的牵引特性曲线分段得出，单位km/h
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 分段速度下限。根据车辆提供的牵引特性曲线分段得出，单位km/h
*/ 
UINT8_S GetSystemAccTableDataStrulowerLimitSpeed(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDSystemAccTableDataStru的分段速度上限。根据车辆提供的牵引特性曲线分段得出，单位km/h
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 分段速度上限。根据车辆提供的牵引特性曲线分段得出，单位km/h
*/ 
UINT8_S GetSystemAccTableDataStruupperLimitSpeed(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDSystemAccTableDataStru的分段加速度值。根据车辆提供的牵引特性曲线分段得出，单位cm/s2
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 分段加速度值。根据车辆提供的牵引特性曲线分段得出，单位cm/s2
*/ 
UINT8_S GetSystemAccTableDataStruaccValue(const UINT8_S trainType);

/*
** 功能描述： 获取牵引加速度
* 参数说明： const UINT8_S trainType;列车车型
*             const UINT16_S trainSpeed 列车当前速度
* 返回值  :  加速度
*/ 
UINT8_S GetTracAcc(const UINT16_S trainSpeed,const UINT8_S trainType);


#ifdef __cplusplus
}
#endif

#endif
