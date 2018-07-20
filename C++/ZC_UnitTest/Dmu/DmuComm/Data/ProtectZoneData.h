/*************************************************
  文件名   ：ProtectZoneData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： ProtectZoneData数据管理
			DmuCommonData组件的ProtectZoneData功能可分解如下：
			1）	给ProtectZoneDataStru结构体指针分配空间
			2）	获取ProtectZoneData数据
			3）	获取ProtectZoneData信息
			4）	获取指定IDProtectZoneDataStru的结构体下标
			5）	获取指定IDProtectZoneDataStru的结构体指针
			6）	获取指定IDProtectZoneDataStru的包含的计轴区段数目
			7）	获取指定IDProtectZoneDataStru的包含的计轴区段编号
			8）	获取线路保护区段最大ID
			9）	获取保护区段包含的计轴区段信息
			10）	获取线路保护区段所属ZC
			11）	获取线路保护区段最大ID
  备注    ：无。
 
*************************************************/
#ifndef PROTECTZONE_DATA_H_
#define PROTECTZONE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define PROTECTZONE_AXLESGM_MAX_NUM               4                                            /*包含计轴区段的最大数目*/
#define PROTECTZONE_LINE_BYTE_NUM                 12                                        /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*保护区段表数据结构体*/
typedef struct BnfProtectZoneStruct
{
    UINT16_S  protectZoneId;                                                /*索引编号*/
    UINT16_S  includeAxleSgmtNum;                                            /*包含的计轴区段数目*/
    UINT16_S  includeAxleSgmtId[PROTECTZONE_AXLESGM_MAX_NUM];                /*包含的计轴区段编号*/

    /*动态计算字段*/
    UINT16_S  manageZCId;                                                    /*所属ZC区域ID*/
    UINT16_S  manageCIId;                                                    /*所属CI区域ID*/ 
}BnfProtectZoneStruct;

/*
* 功能描述： 给ProtectZoneDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocProtectZoneDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取ProtectZoneData数据
* 参数说明：
* 返回值  ： 
            BnfProtectZoneStruct*
*/
BnfProtectZoneStruct *GetProtectZoneData(void);

/*
* 功能描述： 获取ProtectZoneData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfProtectZoneStruct*
*/
BnfProtectZoneStruct *GetProtectZoneDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDProtectZoneDataStru的结构体下标
* 参数说明： const UINT16_S protectZoneId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetProtectZoneDataStruIndex(const UINT16_S protectZoneId);

/*
** 功能描述： 获取指定IDProtectZoneDataStru的结构体指针
* 参数说明： const UINT16_S protectZoneId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfProtectZoneStruct* GetIndexIdProtectZoneDataStru(const UINT16_S protectZoneId);

/*
** 功能描述： 获取指定IDProtectZoneDataStru的包含的计轴区段数目
* 参数说明： const UINT16_S protectZoneId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含的计轴区段数目
*/ 
UINT16_S GetProtectZoneDataStruincludeAxleSgmtNum(const UINT16_S protectZoneId);

/*
** 功能描述： 获取指定IDProtectZoneDataStru的包含的计轴区段编号
* 参数说明： const UINT16_S protectZoneId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 包含的计轴区段编号
*/ 
UINT16_S* GetProtZoDataInAxleSgmtId(const UINT16_S protectZoneId);

/*
* 功能描述： 获取线路保护区段最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0: 线路保护区段最大ID
*/
UINT16_S GetLineOverlapMaxId(void);

/*
* 功能描述： 获取保护区段包含的计轴区段信息
* 参数说明： const UINT16_S protectZoneId,保护区段ID
*            UINT16_S* pAcIdBuf，计轴区段ID数组
* 返回值  ： 0xffff: 获取数据失败
*            >0:计轴区段数量
*/
UINT16_S GetLineOverlapOfAcInfo(const UINT16_S protectZoneId,UINT16_S* pAcIdBuf);

/*
* 功能描述： 获取线路保护区段所属ZC
* 参数说明： const UINT16_S overlapId,保护区段ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCId
*/
UINT16_S GetLineOverlapBelongZcId(const UINT16_S overlapId);

/*
* 功能描述： 获取线路保护区段最大ID
所属CI
* 参数说明： const UINT16_S overlapId,保护区段ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ciId
*/
UINT16_S GetLineOverlapBelongCiId(const UINT16_S overlapId);

#ifdef __cplusplus
}
#endif

#endif
