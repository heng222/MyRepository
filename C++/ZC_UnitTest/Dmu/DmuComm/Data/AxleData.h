/*************************************************
  文件名   ：AxleData.h
  作者     ：董欣      
  创建时间 ：2016-8-10
  功能描述 ： AxleData数据管理
			DmuCommonData组件的AxleData功能可分解如下：
				1）	给AxleDataStru结构体指针分配空间
				2）	获取AxleData数据
				3）	获取AxleData信息
				4）	获取指定IDAxleDataStru的结构体下标
				5）	获取指定IDAxleDataStru的结构体指针
				6）	获取指定IDAxleDataStru的计轴器名称
				7）	获取指定IDAxleDataStru的计轴器所处Seg偏移量(cm)
  备注    ：无。
 
*************************************************/
#ifndef AXLE_DATA_H_
#define AXLE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  AXLE_NAME_BYTE_NUM       8                            /*名称的字节数*/
#define  AXLE_LINE_BYTE_NUM      14                            /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif


/*计轴器表*/
typedef struct BnfAxleStruct
{
    UINT16_S  axleId;                        /*编号*/
    UINT8_S  axleName[AXLE_NAME_BYTE_NUM];                    /*计轴器名称*/    
    UINT32_S axleSegOfst;                    /*计轴器所处Seg偏移量(cm)*/
}BnfAxleStruct;

/*
* 函数名称： MallocAxleDataStru
* 功能描述： 给AxleDataStru结构体指针分配空间
* 输入参数： UINT16_S lineNum 表的数据行数
* 输出参数： 无
* 返回值  ： void
*/
void MallocAxleDataStru(UINT16_S lineNum);

/*
* 函数名称： GetAxleData
* 功能描述： 获取AxleData数据
* 输入参数： 无
* 输出参数： 无
* 返回值  ： 
            BnfAxleStruct*
*/
BnfAxleStruct *GetAxleData(void);

/*
* 函数名称： GetAxleDataInfo
* 功能描述： 获取AxleData信息
* 输入参数： 无
* 输出参数： UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfAxleStruct*
*/
BnfAxleStruct *GetAxleDataInfo(UINT16_S* lineNum);

/*
* 函数名称： GetAxleDataStruIndex
* 功能描述： 获取指定IDAxleDataStru的结构体下标
* 输入参数： const UINT16_S axleId;编号
* 输出参数： 无
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetAxleDataStruIndex(const UINT16_S axleId);

/*
* 函数名称： GetIndexIdAxleDataStru
* 功能描述： 获取指定IDAxleDataStru的结构体指针
* 输入参数： const UINT16_S axleId;编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfAxleStruct* GetIndexIdAxleDataStru(const UINT16_S axleId);

/*
* 函数名称： GetAxleDataStruaxleName
* 功能描述： 获取指定IDAxleDataStru的计轴器名称
* 输入参数： const UINT16_S axleId;编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: 计轴器名称
*/ 
UINT8_S* GetAxleDataStruaxleName(const UINT16_S axleId);

/*
* 函数名称： GetAxleDataStruaxleSegOfst
* 功能描述： 获取指定IDAxleDataStru的计轴器所处Seg偏移量(cm)
* 输入参数： const UINT16_S axleId;编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 计轴器所处Seg偏移量(cm)
*/ 
UINT32_S GetAxleDataStruaxleSegOfst(const UINT16_S axleId);


#ifdef __cplusplus
}
#endif

#endif
