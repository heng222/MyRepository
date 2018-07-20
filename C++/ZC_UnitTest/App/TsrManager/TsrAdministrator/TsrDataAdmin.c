/*******************************************
文件名	：TsrDataAdmin.c
作者	：董欣
创建时间：2016-10
描述	：临时限速管理
备注	：无
*******************************************/

#include "TsrDataAdmin.h"
#include "../TsrQuery/QueryManage.h"
#include "../TsrSystem/TsrSysConfigData.h"
#include "../TsrSystem/TsrSystemDefine.h"
#include "../TsrParserPacker/TsrParsePackAtsData.h"
#include "../TsrTransmitFlagAdmin/TsrTransmitStateDataManage.h"
#include "../TsrDmu/DataHandle/DmuDataHandle.h"
#include "../TsrDmu/DataHandle/DmuStruct.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemCmp.h"

static Tsr_DataStru_Set_Stru g_tsrDataAdmin;/*Tsr功能模块临时限速管理变量*/

static void LookupTsrDataAdmin(const Tsr_DataStru_Cell_Stru* pTsrCellData, UINT8_S *posInTsrDataAdmin);
static void Pri_InitTsrCell(Tsr_DataStru_Cell_Stru *pTsrCell);
static void Pri_InitTsrSet(Tsr_DataStru_Set_Stru *pTsrSet);

/*******************************************
函数名	：Pri_InitTsrCell
功能描述：初始化TsrCell变量
输入	：Tsr_DataStru_Cell_Stru *pTsrCell,单个临时限速信息
输出	：无
返回值	：无
*******************************************/
static void Pri_InitTsrCell(Tsr_DataStru_Cell_Stru *pTsrCell)
{
	UINT8_S iCyc = DEFAULT_ZERO;
	(*pTsrCell).TsrSpeed = DEFAULT_ZERO;
	(*pTsrCell).LogicSecQuan = DEFAULT_ZERO;
	for (iCyc = DEFAULT_ZERO; iCyc < LOGIC_MAX_NUM; iCyc++)
	{
		(*pTsrCell).LogicSecId[iCyc] = 0u;
	}
}

/*******************************************
函数名	：Pri_InitTsrSet
功能描述：初始化TsrSet变量
输入	：Tsr_DataStru_Set_Stru *pTsrSet,临时限速集
输出	：无
返回值	：无
*******************************************/
static void Pri_InitTsrSet(Tsr_DataStru_Set_Stru *pTsrSet)
{
	UINT8_S iCyc = DEFAULT_ZERO;
	pTsrSet->TsrQuan = DEFAULT_ZERO;
	for (iCyc = DEFAULT_ZERO; iCyc < TSR_MAX_NUM; iCyc++)
	{
		Pri_InitTsrCell(&pTsrSet->CellTsrData[iCyc]);
	}
}

/*******************************************
函数名	：Pri_SetTsrCell
功能描述：对单个临时限速变量赋值的元函数
输入	：Tsr_DataStru_Cell_Stru *pLiftTsrCell,待设置单个临时限速变量  Tsr_DataStru_Cell_Stru wrightTsrCell，
输出	：无
返回值	：无
*******************************************/
void Pri_SetTsrCell(Tsr_DataStru_Cell_Stru *pLeftTsrCell,Tsr_DataStru_Cell_Stru wrightTsrCell)
{
	UINT8_S iCyc = DEFAULT_ZERO;
	(*pLeftTsrCell).TsrSpeed = wrightTsrCell.TsrSpeed;
	(*pLeftTsrCell).LogicSecQuan = wrightTsrCell.LogicSecQuan;
	for (iCyc = DEFAULT_ZERO; iCyc < wrightTsrCell.LogicSecQuan; iCyc++)
	{
		(*pLeftTsrCell).LogicSecId[iCyc] = wrightTsrCell.LogicSecId[iCyc];
	}
}

/*******************************************
函数名	：Pri_SetTsrSet
功能描述：对临时限速集变量赋值的元函数
输入	：Tsr_DataStru_Set_Stru *pLeftTsrSet,待设置临时限速集变量  Tsr_DataStru_Set_Stru wrightTsrSet，
输出	：无
返回值	：无
*******************************************/
void Pri_SetTsrSet(Tsr_DataStru_Set_Stru *pLeftTsrSet,Tsr_DataStru_Set_Stru wrightTsrSet)
{
	UINT8_S iCyc_Outer = DEFAULT_ZERO;
	UINT8_S iCyc_Inner = DEFAULT_ZERO;
	if(pLeftTsrSet !=NULL)
	{
		pLeftTsrSet->TsrQuan = wrightTsrSet.TsrQuan;

		for (iCyc_Outer = DEFAULT_ZERO; iCyc_Outer < pLeftTsrSet->TsrQuan; iCyc_Outer++)
		{
			pLeftTsrSet->CellTsrData[iCyc_Outer].TsrSpeed = wrightTsrSet.CellTsrData[iCyc_Outer].TsrSpeed;
			pLeftTsrSet->CellTsrData[iCyc_Outer].LogicSecQuan = wrightTsrSet.CellTsrData[iCyc_Outer].LogicSecQuan;
			for (iCyc_Inner = DEFAULT_ZERO; iCyc_Inner < pLeftTsrSet->CellTsrData[iCyc_Outer].LogicSecQuan; iCyc_Inner++)
			{
				pLeftTsrSet->CellTsrData[iCyc_Outer].LogicSecId[iCyc_Inner] = wrightTsrSet.CellTsrData[iCyc_Outer].LogicSecId[iCyc_Inner];
			}
		}
	}
}

/*******************************************
函数名	：Pri_ClearTsrCell
功能描述：清除单个临时限速数据信息结构体元函数
输入	：无
输出	：无
返回值	：无
*******************************************/
void Pri_ClearTsrCell(Tsr_DataStru_Cell_Stru* pTsrCellData)
{
	UINT8_S iCyc = DEFAULT_ZERO;
	pTsrCellData->TsrSpeed = UINT8_MAX;
	pTsrCellData->LogicSecQuan = DEFAULT_ZERO;
	
	for (iCyc = DEFAULT_ZERO; iCyc < LOGIC_MAX_NUM; iCyc++)
	{
		pTsrCellData->LogicSecId[iCyc] = DEFAULT_ZERO;
	}	
}


/*******************************************
函数名	：InitTsrDataAdmin
功能描述：初始化临时限速管理信息
输入	：无
输出	：无
返回值	：无
*******************************************/
void InitTsrDataAdmin(void)
{
	Tsr_DataStru_Set_Stru *pTmpTsrDataSet = GetTsrDataAdmin();
	Pri_InitTsrSet(pTmpTsrDataSet);
}

/*******************************************
函数名	：GetTsrDataAdmin
功能描述：获取临时限速管理信息
输入	：无
输出	：无
返回值	：临时限速管理信息
*******************************************/
Tsr_DataStru_Set_Stru* GetTsrDataAdmin(void)
{
	return &g_tsrDataAdmin;
}

/*******************************************
函数名	：AddTsrDataAdmin
功能描述：添加设置的临时限速信息到临时限速管理信息
输入	：Tsr_DataStru_Cell_Stru* pTsrCellData,设置的临时限速信息
输出	：无
返回值	：无
*******************************************/
void AddTsrDataAdmin(const Tsr_DataStru_Cell_Stru* pTsrCellData)
{
	Tsr_DataStru_Set_Stru* pTempTsrData = NULL;

	if(pTsrCellData != NULL)
	{
		pTempTsrData = GetTsrDataAdmin();

/*		LogMsgString(1,"AddTsrDataAdmin TsrQuan %d, TsrSpeed %d, LogicSecQuan %d : \n",pTempTsrData->TsrQuan + 1, pTsrCellData->TsrSpeed, pTsrCellData->LogicSecQuan);*/

		if(TSR_MAX_NUM > pTempTsrData->TsrQuan)
		{
			Pri_SetTsrCell(&pTempTsrData->CellTsrData[pTempTsrData->TsrQuan], *pTsrCellData);
			pTempTsrData->TsrQuan++;
		}
	}
}

/*******************************************
函数名	：LookupTsrDataAdmin
功能描述：查找某个临时限速在临时限速管理信息中的位置
输入	：Tsr_DataStru_Cell_Stru* pTsrCellData,要查找的临时限速
输出	：UINT8_S *posInTsrDataAdmin,要查找的临时限速在临时限速集中的位置，未查找到返回0xFFu
返回值	：无
*******************************************/
static void LookupTsrDataAdmin(const Tsr_DataStru_Cell_Stru* pTsrCellData, UINT8_S *posInTsrDataAdmin)
{
	UINT8_S iCyc_Outer = DEFAULT_ZERO;
	UINT8_S iCyc_Inner = DEFAULT_ZERO;
	UINT8_S flagValid = DEFAULT_ZERO;
	Tsr_DataStru_Set_Stru* pTempTsrData = NULL;

	pTempTsrData = GetTsrDataAdmin();

	for (iCyc_Outer = DEFAULT_ZERO; iCyc_Outer < pTempTsrData->TsrQuan; iCyc_Outer++)
	{
		if (pTsrCellData->LogicSecQuan == pTempTsrData->CellTsrData[iCyc_Outer].LogicSecQuan)/* 先判断数量是否一致 */
		{
			flagValid = DEFAULT_ZERO;

			for (iCyc_Inner = DEFAULT_ZERO; iCyc_Inner < pTsrCellData->LogicSecQuan; iCyc_Inner++)/* 再判断每个逻辑区段ID是否都一致 */
			{
				if (pTsrCellData->LogicSecId[iCyc_Inner] == pTempTsrData->CellTsrData[iCyc_Outer].LogicSecId[iCyc_Inner])
				{
					/*继续遍历*/
				}
				else
				{
					flagValid = 1u;
					break;
				}
			}

			if (DEFAULT_ZERO == flagValid)
			{
				*posInTsrDataAdmin = iCyc_Outer;/*预删除的临时限速在数组中的位置*/
				break;
			}
		}
		else
		{
			/*继续遍历*/
		}
	}
}


/*******************************************
函数名	：DeleteTsrDataAdmin
功能描述：从临时限速管理信息中删除某个临时限速
输入	：pSingleTsrDataStru临时限速信息
输出	：无
返回值	：无
*******************************************/
void DeleteTsrDataAdmin(const Tsr_DataStru_Cell_Stru* pTsrCellData)
{
	UINT8_S iCyc = DEFAULT_ZERO;
	UINT8_S index_Pos = UINT8_MAX;
	Tsr_DataStru_Set_Stru* pTempTsrData = NULL;
	
	if(pTsrCellData != NULL)
	{
		pTempTsrData = GetTsrDataAdmin();
		LookupTsrDataAdmin(pTsrCellData, &index_Pos);/*查找要删的临时限速所在数组中的下标值*/

		if (UINT8_MAX != index_Pos)
		{
			/*找到要删除的数组元素*/
			for (iCyc = DEFAULT_ZERO; iCyc < pTempTsrData->TsrQuan - 1u; iCyc++)
			{
				if (iCyc >= index_Pos)
				{
					/*后一个元素覆盖前一个元素前，先将前一个元素清0*/
					Pri_ClearTsrCell(&pTempTsrData->CellTsrData[iCyc]);

					/*从找到的那个元素起，后面的元素覆盖前一个元素*/
					Pri_SetTsrCell(&pTempTsrData->CellTsrData[iCyc],pTempTsrData->CellTsrData[iCyc+1]);
				}
			}

			/*将最后一个元素清0*/
			Pri_ClearTsrCell(&pTempTsrData->CellTsrData[iCyc]);

			/*将其中一元素删除后，数组总的个数减去1*/
			pTempTsrData->TsrQuan -= 1u;

		}
		else
		{
			/*不处理*/
		}
	}
}