/*************************************************
  文件名   ：ConResSpeedData.h
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： ConResSpeedData数据管理
			DmuCommonData组件的ConResSpeedData功能可分解如下：
			1）	给BnfConResSpeedStruct结构体指针分配空间
			2）	获取ConResSpeed数据
			3）	获取ConResSpeed信息
			4）	获取统一限速表中的限速值

  备注    ：无。
 
*************************************************/
#ifndef CONRESSPEED_DATA_H_
#define CONRESSPEED_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  CONRESSPEED_LINE_BYTE_NUM             3                                            /*一行数据字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*统一限速表数据结构体*/
typedef struct BnfConResSpeedStruct
{
    UINT8_S  index;                                        /*索引编号*/
    UINT16_S resSpeed;                                    /*限速值（cm/s）*/
}BnfConResSpeedStruct;

/*
* 功能描述： 给BnfConResSpeedStruct结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocConResSpeedDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取ConResSpeed数据
* 参数说明：
* 返回值  ： 
            BnfConResSpeedStruct*
*/
BnfConResSpeedStruct *GetConResSpeedData(void);

/*
* 功能描述： 获取ConResSpeed信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfConResSpeedStruct*
*/
BnfConResSpeedStruct *GetConResSpeedDataInfo(UINT16_S* lineNum);

/*
* 功能描述： 获取统一限速表中的限速值
* 参数说明：无
* 返回值  ：0xFFFF 无效
            其他:有效
*/
UINT16_S GetConResSpeedValue(void);

#ifdef __cplusplus
}
#endif

#endif
