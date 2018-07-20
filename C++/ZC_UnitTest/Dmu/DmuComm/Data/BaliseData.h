/*************************************************
  文件名   ：BaliseData.h
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： BaliseData数据管理
			DmuCommonData组件的BaliseData功能可分解如下：
			1）	给BaliseDataStru结构体指针分配空间
			2）	获取BaliseData数据
			3）	获取BaliseData信息
			4）	获取指定IDBaliseDataStru的结构体下标
			5）	获取指定IDBaliseDataStru的结构体指针
			6）	获取指定IDBaliseDataStru的名称
			7）	获取指定IDBaliseDataStru的所处seg编号
			8）	获取指定IDBaliseDataStru的所处Seg偏移量（cm）


  备注    ：无。
 
*************************************************/
#ifndef BALISE_DATA_H_
#define BALISE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define BALISE_NAME_BYTE_LEN                 8                                /*名称长度*/
#define BALISE_RELATE_MAX_NUM                10                                /*应答器相邻应答器最大数量*/
#define BALISE_LINE_BYTE_NUM                20                               /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*应答器表数据结构体*/
typedef struct BnfBaliseStruct
{
    UINT16_S  indexId;                                            /*索引编号*/
    UINT32_S  baliseId;                                            /*应答器ID*/
    UINT8_S   name[BALISE_NAME_BYTE_LEN];                            /*名称*/
    UINT16_S  segId;                                               /*所处seg编号*/  
    UINT32_S  segOffset;                                            /*所处Seg偏移量（cm）*/  
}BnfBaliseStruct;

/*
* 功能描述： 给BaliseDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocBaliseDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取BaliseData数据
* 参数说明：
* 返回值  ： 
            BnfBaliseStruct*
*/
BnfBaliseStruct *GetBaliseData(void);

/*
* 功能描述： 获取BaliseData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfBaliseStruct*
*/
BnfBaliseStruct *GetBaliseDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDBaliseDataStru的结构体下标
* 参数说明： const UINT32_S baliseId;应答器ID
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetBaliseDataStruIndex(const UINT32_S baliseId);

/*
** 功能描述： 获取指定IDBaliseDataStru的结构体指针
* 参数说明： const UINT32_S baliseId;应答器ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfBaliseStruct* GetIndexIdBaliseDataStru(const UINT32_S baliseId);

/*
** 功能描述： 获取指定IDBaliseDataStru的名称
* 参数说明： const UINT32_S baliseId;应答器ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetBaliseDataStruname(const UINT32_S baliseId);

/*
** 功能描述： 获取指定IDBaliseDataStru的所处seg编号
* 参数说明： const UINT32_S baliseId;应答器ID
* 返回值  :  0: 获取数据失败
*            >0: 所处seg编号
*/ 
UINT16_S GetBaliseDataStrusegId(const UINT32_S baliseId);

/*
** 功能描述： 获取指定IDBaliseDataStru的所处Seg偏移量（cm）
* 参数说明： const UINT32_S baliseId;应答器ID
* 返回值  :  0: 获取数据失败
*            >0: 所处Seg偏移量（cm）
*/ 
UINT32_S GetBaliseDataStrusegOffset(const UINT32_S baliseId);




#ifdef __cplusplus
}
#endif

#endif
