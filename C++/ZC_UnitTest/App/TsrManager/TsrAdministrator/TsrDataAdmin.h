/*******************************************
文件名	：TsrDataAdmin.h
作者	：董欣
创建时间：2016-10
描述	：临时限速管理
备注	：无
*******************************************/

#ifndef TSR_DATA_ADMIN_H_
#define TSR_DATA_ADMIN_H_

#include "../../../Common/CommonTypes.h"
#include "../TsrSystem/TsrSystemDefine.h"
#include "../TsrParserPacker/ParsePackInterfaceDefine.h"
#include "../TsrDmu/DataHandle/DmuStruct.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
函数名	：Pri_SetTsrCell
功能描述：对单个临时限速变量赋值的元函数
输入	：Tsr_DataStru_Cell_Stru *pLiftTsrCell,待设置单个临时限速变量  Tsr_DataStru_Cell_Stru wrightTsrCell，
输出	：无
返回值	：无
*******************************************/
extern void Pri_SetTsrCell(Tsr_DataStru_Cell_Stru *pLeftTsrCell,Tsr_DataStru_Cell_Stru wrightTsrCell);

/*******************************************
函数名	：Pri_SetTsrSet
功能描述：对临时限速集变量赋值的元函数
输入	：Tsr_DataStru_Set_Stru *pLeftTsrSet,待设置临时限速集变量  Tsr_DataStru_Set_Stru wrightTsrSet，
输出	：无
返回值	：无
*******************************************/
extern void Pri_SetTsrSet(Tsr_DataStru_Set_Stru *pLeftTsrSet,Tsr_DataStru_Set_Stru wrightTsrSet);

/*******************************************
函数名	：Pri_ClearTsrCell
功能描述：清除单个临时限速数据信息结构体元函数
输入	：无
输出	：无
返回值	：无
*******************************************/
extern void Pri_ClearTsrCell(Tsr_DataStru_Cell_Stru* pTsrCellData);


/*******************************************
函数名	：InitTsrDataAdmin
功能描述：初始化临时限速管理信息
输入	：无
输出	：无
返回值	：无
*******************************************/
extern void InitTsrDataAdmin(void);

/*******************************************
函数名	：GetTsrDataAdmin
功能描述：获取临时限速管理信息
输入	：无
输出	：无
返回值	：临时限速管理信息
*******************************************/
extern Tsr_DataStru_Set_Stru* GetTsrDataAdmin(void);

/*******************************************
函数名	：AddTsrDataAdmin
功能描述：添加设置的临时限速信息到临时限速管理信息
输入	：Tsr_DataStru_Cell_Stru* pTsrCellData,设置的临时限速信息
输出	：无
返回值	：无
*******************************************/
extern void AddTsrDataAdmin(const Tsr_DataStru_Cell_Stru* pTsrCellData);

/*******************************************
函数名	：DeleteTsrDataAdmin
功能描述：从临时限速管理信息中删除某个临时限速
输入	：pSingleTsrDataStru临时限速信息
输出	：无
返回值	：无
*******************************************/
extern void DeleteTsrDataAdmin(const Tsr_DataStru_Cell_Stru* pTsrCellData);


#ifdef __cplusplus
}
#endif

#endif