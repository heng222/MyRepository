/*************************************************
  文件名   ：TempLimitSpeedData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： TempLimitSpeedData数据管理
			DmuCommonData组件的TempLimitSpeedData功能可分解如下：
			1）	给TempLimitSpeedDataStru结构体指针分配空间
			2）	获取TempLimitSpeedData数据
			3）	获取TempLimitSpeedData信息
			4）	获取指定IDTempLimitSpeedDataStru的一次设置的临时限速最大个数
			5）	获取指定IDTempLimitSpeedDataStru的一个临时限速报文中包含的最大逻辑区段数量
  备注    ：无。 
*************************************************/
#ifndef TEMPLIMITSPEED_DATA_H_
#define TEMPLIMITSPEED_DATA_H_

#include "../../../Common/CommonTypes.h"

#define TEMPLIMITSPEED_LINE_BYTE_NUM                    4                            /*一行数据字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*临时限速配置表数据结构体*/
typedef struct BnfTempLimitSpeedStruct
{
    UINT16_S  oneSetMaxNum;                       /*一次设置的临时限速最大个数*/
    UINT16_S  includeLgcSectionNum;               /*一个临时限速报文中包含的最大逻辑区段数量*/
}BnfTempLimitSpeedStruct;

/*
* 功能描述： 给TempLimitSpeedDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocTempLimitSpeedDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取TempLimitSpeedData数据
* 参数说明：
* 返回值  ： 
            BnfTempLimitSpeedStruct*
*/
BnfTempLimitSpeedStruct *GetTempLimitSpeedData(void);

/*
* 功能描述： 获取TempLimitSpeedData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfTempLimitSpeedStruct*
*/
BnfTempLimitSpeedStruct *GetTempLimitSpeedDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDTempLimitSpeedDataStru的一次设置的临时限速最大个数
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*            <UINT16_NULL: 一次设置的临时限速最大个数
*/ 
UINT16_S GetTempLimitSpeedDataStruoneSetMaxNum(void);

/*
** 功能描述： 获取指定IDTempLimitSpeedDataStru的一个临时限速报文中包含的最大逻辑区段数量
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*            <UINT16_NULL: 一个临时限速报文中包含的最大逻辑区段数量
*/ 
UINT16_S GetTempLimitSpeedDataStruincludeLgcSectionNum(void);


#ifdef __cplusplus
}
#endif

#endif
