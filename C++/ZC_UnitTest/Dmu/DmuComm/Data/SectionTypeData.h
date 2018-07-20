/*************************************************
  文件名   ：SectionTypeData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SectionTypeData数据管理
			DmuCommonData组件的SectionTypeData功能可分解如下：
			1）	给SectionTypeDataStru结构体指针分配空间
			2）	获取SectionTypeData数据
			3）	获取SectionTypeData信息
			4）	获取指定IDSectionTypeDataStru的结构体下标
			5）	获取指定IDSectionTypeDataStru的结构体指针
			6）	获取指定IDSectionTypeDataStru的区域类型
			7）	获取指定IDSectionTypeDataStru的区域ID
			8）	获取指定IDSectionTypeDataStru的区域属性
			9）	获取指定设备类型和ID的区段属性

  备注    ：无。
 
*************************************************/

#ifndef SECTIONTYPE_DATA_H_
#define SECTIONTYPE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SECTIONTYPE_LINE_BYTE_NUM                 7         /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*区域属性表数据结构体*/
typedef struct BnfSectionTypeStruct
{
    UINT16_S  indexId;                               /*索引编号*/
    UINT16_S  sectionType;                           /*区域类型*/
    UINT16_S  sectionId;                               /*区域ID*/
    UINT8_S      sectionProperty;                    /*区域属性*/
}BnfSectionTypeStruct;

/*
* 功能描述： 给SectionTypeDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSectionTypeDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取SectionTypeData数据
* 参数说明：
* 返回值  ： 
            BnfSectionTypeStruct*
*/
BnfSectionTypeStruct *GetSectionTypeData(void);

/*
* 功能描述： 获取SectionTypeData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSectionTypeStruct*
*/
BnfSectionTypeStruct *GetSectionTypeDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDSectionTypeDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSectionTypeDataStruIndex(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDSectionTypeDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSectionTypeStruct* GetIndexIdSectionTypeDataStru(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDSectionTypeDataStru的区域类型
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 区域类型
*/ 
UINT16_S GetSectionTypeDataStrusectionType(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDSectionTypeDataStru的区域ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 区域ID
*/ 
UINT16_S GetSectionTypeDataStrusectionId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDSectionTypeDataStru的区域属性
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 区域属性
*/ 
UINT8_S GetSectionTypeDataStrusectionProperty(const UINT16_S indexId);

/*
** 功能描述： 获取指定设备类型和ID的区段属性
* 参数说明： const UINT16_S devType   设备类型,const UINT16_S devId   设备ID
* 返回值  :  0: 获取数据失败
*             >0: 区段属性
*/ 
UINT8_S GetSecPropertyAccordName(const UINT16_S devType,const UINT16_S devId);

#ifdef __cplusplus
}
#endif

#endif
