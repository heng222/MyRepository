/*******************************************
文件名	：DmuStruct.h
作者	：董欣
创建时间：2016-10
描述	：DSU查询函数
备注	：无
*******************************************/

#ifndef DMU_STRUCT_H_
#define DMU_STRUCT_H_

#include "../../../../Common/CommonTypes.h"
#include "../../TsrSystem/TsrSystemDefine.h"

#define  LOGIC_MAX_NUM                                  25u										/*一个限速区段中包含的最大逻辑区段数量*/
#define  TSR_MAX_NUM									20u										/* 一个ZC包含的最大临时限速区段数量*/

#ifdef __cplusplus
extern "C" {
#endif

/*单个临时限速结构体*/
typedef struct S_TSR_DATASTRU_CELL
{
	UINT8_S TsrSpeed;/*限速值*/
	UINT8_S LogicSecQuan;/*逻辑区段数*/
	UINT16_S LogicSecId[LOGIC_MAX_NUM];/*逻辑区段ID*/
}Tsr_DataStru_Cell_Stru;

/*线路临时限速结构体*/
typedef struct S_TSR_DATASTRU_SET
{
	UINT8_S TsrQuan;
	Tsr_DataStru_Cell_Stru CellTsrData[TSR_MAX_NUM];
}Tsr_DataStru_Set_Stru;

#ifdef __cplusplus
}
#endif

#endif
