/*************************************************
  文件名   ：CbtcApptchSectionData.h
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： CbtcApptchSectionData数据管理
			DmuCommonData组件的CbtcApptchSectionData功能可分解如下：
			1）	给CbtcApptchSectionDataStru结构体指针分配空间
			2）	获取CbtcApptchSectionData数据
			3）	获取CbtcApptchSectionData信息
			4）	获取指定IDCbtcApptchSectionDataStru的结构体下标
			5）	获取指定IDCbtcApptchSectionDataStru的结构体指针
			6）	获取指定IDCbtcApptchSectionDataStru的包含的逻辑区段的数目
			7）	获取指定IDCbtcApptchSectionDataStru的包含的逻辑区段的编号


  备注    ：无。
 
*************************************************/
#ifndef CBTCAPPTCHSECTION_DATA_H_
#define CBTCAPPTCHSECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define CBTCAPPTCHSECTION_LGCZONE_MAX_NUM               10                                               /*包含逻辑区段的最大数目*/
#define CBTCAPPTCHSECTION_LINE_BYTE_NUM                 24                                                /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*Cbtc保护区段表数据结构体*/
typedef struct BnfCbtcApptchSectionStruct
{
    UINT16_S  cbtcApptchSectionId;                                            /*索引编号*/
    UINT16_S  includeLgcZoneNum;                                                /*包含的逻辑区段的数目*/
    UINT16_S  includeLgcZoneId[CBTCAPPTCHSECTION_LGCZONE_MAX_NUM];            /*包含的逻辑区段的编号*/
}BnfCbtcApptchSectionStruct;

/*
* 功能描述： 给CbtcApptchSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocCbtcApptchSectionDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取CbtcApptchSectionData数据
* 参数说明：
* 返回值  ： 
            BnfCbtcApptchSectionStruct*
*/
BnfCbtcApptchSectionStruct *GetCbtcApptchSectionData(void);

/*
* 功能描述： 获取CbtcApptchSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfCbtcApptchSectionStruct*
*/
BnfCbtcApptchSectionStruct *GetCbtcApptchSectionDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDCbtcApptchSectionDataStru的结构体下标
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetCbtcApptchSectionDataStruIndex(const UINT16_S cbtcApptchSectionId);

/*
** 功能描述： 获取指定IDCbtcApptchSectionDataStru的结构体指针
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfCbtcApptchSectionStruct* GetIndexIdCbtcApptchSectionDataStru(const UINT16_S cbtcApptchSectionId);

/*
** 功能描述： 获取指定IDCbtcApptchSectionDataStru的包含的逻辑区段的数目
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含的逻辑区段的数目
*/ 
UINT16_S GetCbtcApptchSectionDataStruincludeLgcZoneNum(const UINT16_S cbtcApptchSectionId);

/*
** 功能描述： 获取指定IDCbtcApptchSectionDataStru的包含的逻辑区段的编号
* 参数说明： const UINT16_S cbtcApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 包含的逻辑区段的编号
*/ 
UINT16_S* GetCbtcAppSectDataInLgcZoId(const UINT16_S cbtcApptchSectionId);


#ifdef __cplusplus
}
#endif

#endif
