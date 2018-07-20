/*************************************************
  文件名   ：PhysicalSectionData.h
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： PhysicalSectionData数据管理
			DmuCommonData组件的PhysicalSectionData功能可分解如下：
			1）	给LogicSectionDataStru结构体指针分配空间
			2）	获取LogicSectionData数据
			3）	获取LogicSectionData信息
			4）	获取指定IDLogicSectionDataStru的结构体下标
			5）	获取指定IDLogicSectionDataStru的结构体指针
			6）	获取指定IDLogicSectionDataStru的名称
			7）	获取指定IDLogicSectionDataStru的起点所处Seg编号
			8）	获取指定IDLogicSectionDataStru的起点所处Seg偏移量
			9）	获取指定IDLogicSectionDataStru的终点所处Seg编号
			10）	获取指定IDLogicSectionDataStru的终点所处Seg偏移量
			11）	获取线路逻辑区段最大ID
			12）	根据输入的SEGID获取逻辑区段的信息
			13）	获取逻辑区段所属ZC
			14）	获取逻辑区段所属CI
			15）	获取逻辑区段所属AC
			16）	查询此SEG前方的逻辑区段
			17）	查询此SEG后方的逻辑区段
			18）	获取逻辑区段ID相关联的逻辑区段ID
  备注    ：无。
 
*************************************************/
#ifndef PHYSICAL_SECTION_DATA_H_
#define PHYSICAL_SECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  PHYSICALSECTION_NAME_BYTE_NUM       16                                                                      /*名称的字节数*/
#define  PHYSICALSECTION_AXLEID_MAX_NUM       5                                                                    /*计轴最大编号*/
#define  PHYSICALSECTION_LINE_BYTE_NUM         30                                                                    /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*物理区段表*/
typedef struct BnfPhysicalSectionStruct
{
    UINT16_S  physicalStcId;                                                /*编号*/
    UINT8_S   name[PHYSICALSECTION_NAME_BYTE_NUM];                        /*名称*/
    UINT16_S  includeAxleScNum;                                            /*包含计轴区段数目*/
    UINT16_S  axleIdBuff[PHYSICALSECTION_AXLEID_MAX_NUM];                 /*计轴编号*/
}BnfPhysicalSectionStruct;

/*
* 功能描述： 给PhysicalSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocPhysicalSectionDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取PhysicalSectionData数据
* 参数说明：
* 返回值  ： 
            BnfPhysicalSectionStruct*
*/
BnfPhysicalSectionStruct *GetPhysicalSectionData(void);

/*
* 功能描述： 获取PhysicalSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfPhysicalSectionStruct*
*/
BnfPhysicalSectionStruct *GetPhysicalSectionDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDPhysicalSectionDataStru的结构体下标
* 参数说明： const UINT16_S physicalStcId;编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetPhysicalSectionDataStruIndex(const UINT16_S physicalStcId);

/*
** 功能描述： 获取指定IDPhysicalSectionDataStru的结构体指针
* 参数说明： const UINT16_S physicalStcId;编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfPhysicalSectionStruct* GetIndexIdPhysicalSectionDataStru(const UINT16_S physicalStcId);

/*
** 功能描述： 获取指定IDPhysicalSectionDataStru的名称
* 参数说明： const UINT16_S physicalStcId;编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetPhysicalSectionDataStruname(const UINT16_S physicalStcId);

/*
** 功能描述： 获取指定IDPhysicalSectionDataStru的包含计轴区段数目
* 参数说明： const UINT16_S physicalStcId;编号
* 返回值  :  0: 获取数据失败
*            >0: 包含计轴区段数目
*/ 
UINT16_S GetPhysicalSectionDataStruincludeAxleScNum(const UINT16_S physicalStcId);

/*
** 功能描述： 获取指定IDPhysicalSectionDataStru的计轴编号
* 参数说明： const UINT16_S physicalStcId;编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 计轴编号
*/ 
UINT16_S* GetPhysicalSectionDataStruaxleIdBuff(const UINT16_S physicalStcId);


#ifdef __cplusplus
}
#endif

#endif
