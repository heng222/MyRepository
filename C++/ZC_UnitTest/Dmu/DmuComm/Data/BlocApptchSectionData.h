/*************************************************
  文件名   ：BlocApptchSectionData.h
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： BaliseData数据管理
			DmuCommonData组件的BlocApptchSectionData功能可分解如下：
			1）	给BlocApptchSectionDataStru结构体指针分配空间
			2）	获取BlocApptchSectionData数据
			3）	获取BlocApptchSectionData信息
			4）	获取指定IDBlocApptchSectionDataStru的结构体下标
			5）	获取指定IDBlocApptchSectionDataStru的结构体指针
			6）	获取指定IDBlocApptchSectionDataStru的包含的计轴区段数目
			7）	获取指定IDBlocApptchSectionDataStru的包含的计轴区段编号
  备注    ：无。
 
*************************************************/
#ifndef BLOCAPPTCHSECTION_DATA_H_
#define BLOCAPPTCHSECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define BLOCAPPTCHSECTION_AXLESGM_MAX_NUM               10                                                   /*包含计轴区段的最大数目*/
#define BLOCAPPTCHSECTION_LINE_BYTE_NUM                 24                                                    /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*点式保护区段表数据结构体*/
typedef struct BnfBlocApptchSectionStruct
{
    UINT16_S  blocApptchSectionId;                                            /*索引编号*/
    UINT16_S  includeAxleSgmtNum;                                                /*包含的计轴区段数目*/
    UINT16_S  includeAxleSgmtId[BLOCAPPTCHSECTION_AXLESGM_MAX_NUM];                /*包含的计轴区段编号*/
}BnfBlocApptchSectionStruct;

/*
* 功能描述： 给BlocApptchSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocBlocApptchSectionDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取BlocApptchSectionData数据
* 参数说明：
* 返回值  ： 
            BnfBlocApptchSectionStruct*
*/
BnfBlocApptchSectionStruct *GetBlocApptchSectionData(void);

/*
* 功能描述： 获取BlocApptchSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfBlocApptchSectionStruct*
*/
BnfBlocApptchSectionStruct *GetBlocApptchSectionDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDBlocApptchSectionDataStru的结构体下标
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetBlocApptchSectionDataStruIndex(const UINT16_S blocApptchSectionId);

/*
** 功能描述： 获取指定IDBlocApptchSectionDataStru的结构体指针
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfBlocApptchSectionStruct* GetIndexIdBlocApptchSectionDataStru(const UINT16_S blocApptchSectionId);

/*
** 功能描述： 获取指定IDBlocApptchSectionDataStru的包含的计轴区段数目
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含的计轴区段数目
*/ 
UINT16_S GetBlocApptchSectionDataStruincludeAxleSgmtNum(const UINT16_S blocApptchSectionId);

/*
** 功能描述： 获取指定IDBlocApptchSectionDataStru的包含的计轴区段编号
* 参数说明： const UINT16_S blocApptchSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 包含的计轴区段编号
*/ 
UINT16_S* GetBlAppSectDataInAxSgmtId(const UINT16_S blocApptchSectionId);


#ifdef __cplusplus
}
#endif

#endif
