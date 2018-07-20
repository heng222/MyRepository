/*************************************************
  文件名   ：CbtcTrgZoneData.h
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： CbtcTrgZoneData数据管理
			DmuCommonData组件的CbtcTrgZoneData功能可分解如下：
			1）	给CbtcTrgZoneDataStru结构体指针分配空间
			2）	获取CbtcTrgZoneData数据
			3）	获取CbtcTrgZoneData信息
			4）	获取指定IDCbtcTrgZoneDataStru的结构体下标
			5）	获取指定IDCbtcTrgZoneDataStru的结构体指针
			6）	获取指定IDCbtcTrgZoneDataStru的包含的逻辑区段的数目
			7）	获取指定IDCbtcTrgZoneDataStru的包含的逻辑区段的编号
  备注    ：无。
 
*************************************************/
#ifndef CBTCTRGZONE_DATA_H_
#define CBTCTRGZONE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define CBTCTRGZONE_LGCZONE_MAX_NUM               16                                                   /*包含逻辑区段的最大数目*/
#define CBTCTRGZONE_LINE_BYTE_NUM                 36                                                /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*Cbtc触发区段表数据结构体*/
typedef struct BnfCbtcTrgZoneStruct
{
    UINT16_S  cbtcApptchSectionId;                                /*索引编号*/
    UINT16_S  includeLgcZoneNum;                                    /*包含的逻辑区段的数目*/
    UINT16_S  includeLgcZoneId[CBTCTRGZONE_LGCZONE_MAX_NUM];        /*包含的逻辑区段的编号*/
}BnfCbtcTrgZoneStruct;

/*
* 功能描述： 给CbtcTrgZoneDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocCbtcTrgZoneDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取CbtcTrgZoneData数据
* 参数说明：
* 返回值  ： 
            BnfCbtcTrgZoneStruct*
*/
BnfCbtcTrgZoneStruct *GetCbtcTrgZoneData(void);

/*
* 功能描述： 获取CbtcTrgZoneData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfCbtcTrgZoneStruct*
*/
BnfCbtcTrgZoneStruct *GetCbtcTrgZoneDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDCbtcTrgZoneDataStru的结构体下标
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetCbtcTrgZoneDataStruIndex(const UINT16_S cbtcApptchSectionId);

/*
** 功能描述： 获取指定IDCbtcTrgZoneDataStru的结构体指针
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfCbtcTrgZoneStruct* GetIndexIdCbtcTrgZoneDataStru(const UINT16_S cbtcApptchSectionId);

/*
** 功能描述： 获取指定IDCbtcTrgZoneDataStru的包含的逻辑区段的数目
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含的逻辑区段的数目
*/ 
UINT16_S GetCbtcTrgZoneDataStruincludeLgcZoneNum(const UINT16_S cbtcApptchSectionId);

/*
** 功能描述： 获取指定IDCbtcTrgZoneDataStru的包含的逻辑区段的编号
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 包含的逻辑区段的编号
*/ 
UINT16_S* GetCbtcTrgZoDataInLgcZoId(const UINT16_S cbtcApptchSectionId);


#ifdef __cplusplus
}
#endif

#endif
