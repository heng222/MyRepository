/*******************************************
�ļ���	��TsrDataAdmin.c
����	������
����ʱ�䣺2016-10
����	����ʱ���ٹ���
��ע	����
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

static Tsr_DataStru_Set_Stru g_tsrDataAdmin;/*Tsr����ģ����ʱ���ٹ������*/

static void LookupTsrDataAdmin(const Tsr_DataStru_Cell_Stru* pTsrCellData, UINT8_S *posInTsrDataAdmin);
static void Pri_InitTsrCell(Tsr_DataStru_Cell_Stru *pTsrCell);
static void Pri_InitTsrSet(Tsr_DataStru_Set_Stru *pTsrSet);

/*******************************************
������	��Pri_InitTsrCell
������������ʼ��TsrCell����
����	��Tsr_DataStru_Cell_Stru *pTsrCell,������ʱ������Ϣ
���	����
����ֵ	����
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
������	��Pri_InitTsrSet
������������ʼ��TsrSet����
����	��Tsr_DataStru_Set_Stru *pTsrSet,��ʱ���ټ�
���	����
����ֵ	����
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
������	��Pri_SetTsrCell
�����������Ե�����ʱ���ٱ�����ֵ��Ԫ����
����	��Tsr_DataStru_Cell_Stru *pLiftTsrCell,�����õ�����ʱ���ٱ���  Tsr_DataStru_Cell_Stru wrightTsrCell��
���	����
����ֵ	����
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
������	��Pri_SetTsrSet
��������������ʱ���ټ�������ֵ��Ԫ����
����	��Tsr_DataStru_Set_Stru *pLeftTsrSet,��������ʱ���ټ�����  Tsr_DataStru_Set_Stru wrightTsrSet��
���	����
����ֵ	����
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
������	��Pri_ClearTsrCell
�������������������ʱ����������Ϣ�ṹ��Ԫ����
����	����
���	����
����ֵ	����
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
������	��InitTsrDataAdmin
������������ʼ����ʱ���ٹ�����Ϣ
����	����
���	����
����ֵ	����
*******************************************/
void InitTsrDataAdmin(void)
{
	Tsr_DataStru_Set_Stru *pTmpTsrDataSet = GetTsrDataAdmin();
	Pri_InitTsrSet(pTmpTsrDataSet);
}

/*******************************************
������	��GetTsrDataAdmin
������������ȡ��ʱ���ٹ�����Ϣ
����	����
���	����
����ֵ	����ʱ���ٹ�����Ϣ
*******************************************/
Tsr_DataStru_Set_Stru* GetTsrDataAdmin(void)
{
	return &g_tsrDataAdmin;
}

/*******************************************
������	��AddTsrDataAdmin
����������������õ���ʱ������Ϣ����ʱ���ٹ�����Ϣ
����	��Tsr_DataStru_Cell_Stru* pTsrCellData,���õ���ʱ������Ϣ
���	����
����ֵ	����
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
������	��LookupTsrDataAdmin
��������������ĳ����ʱ��������ʱ���ٹ�����Ϣ�е�λ��
����	��Tsr_DataStru_Cell_Stru* pTsrCellData,Ҫ���ҵ���ʱ����
���	��UINT8_S *posInTsrDataAdmin,Ҫ���ҵ���ʱ��������ʱ���ټ��е�λ�ã�δ���ҵ�����0xFFu
����ֵ	����
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
		if (pTsrCellData->LogicSecQuan == pTempTsrData->CellTsrData[iCyc_Outer].LogicSecQuan)/* ���ж������Ƿ�һ�� */
		{
			flagValid = DEFAULT_ZERO;

			for (iCyc_Inner = DEFAULT_ZERO; iCyc_Inner < pTsrCellData->LogicSecQuan; iCyc_Inner++)/* ���ж�ÿ���߼�����ID�Ƿ�һ�� */
			{
				if (pTsrCellData->LogicSecId[iCyc_Inner] == pTempTsrData->CellTsrData[iCyc_Outer].LogicSecId[iCyc_Inner])
				{
					/*��������*/
				}
				else
				{
					flagValid = 1u;
					break;
				}
			}

			if (DEFAULT_ZERO == flagValid)
			{
				*posInTsrDataAdmin = iCyc_Outer;/*Ԥɾ������ʱ�����������е�λ��*/
				break;
			}
		}
		else
		{
			/*��������*/
		}
	}
}


/*******************************************
������	��DeleteTsrDataAdmin
��������������ʱ���ٹ�����Ϣ��ɾ��ĳ����ʱ����
����	��pSingleTsrDataStru��ʱ������Ϣ
���	����
����ֵ	����
*******************************************/
void DeleteTsrDataAdmin(const Tsr_DataStru_Cell_Stru* pTsrCellData)
{
	UINT8_S iCyc = DEFAULT_ZERO;
	UINT8_S index_Pos = UINT8_MAX;
	Tsr_DataStru_Set_Stru* pTempTsrData = NULL;
	
	if(pTsrCellData != NULL)
	{
		pTempTsrData = GetTsrDataAdmin();
		LookupTsrDataAdmin(pTsrCellData, &index_Pos);/*����Ҫɾ����ʱ�������������е��±�ֵ*/

		if (UINT8_MAX != index_Pos)
		{
			/*�ҵ�Ҫɾ��������Ԫ��*/
			for (iCyc = DEFAULT_ZERO; iCyc < pTempTsrData->TsrQuan - 1u; iCyc++)
			{
				if (iCyc >= index_Pos)
				{
					/*��һ��Ԫ�ظ���ǰһ��Ԫ��ǰ���Ƚ�ǰһ��Ԫ����0*/
					Pri_ClearTsrCell(&pTempTsrData->CellTsrData[iCyc]);

					/*���ҵ����Ǹ�Ԫ���𣬺����Ԫ�ظ���ǰһ��Ԫ��*/
					Pri_SetTsrCell(&pTempTsrData->CellTsrData[iCyc],pTempTsrData->CellTsrData[iCyc+1]);
				}
			}

			/*�����һ��Ԫ����0*/
			Pri_ClearTsrCell(&pTempTsrData->CellTsrData[iCyc]);

			/*������һԪ��ɾ���������ܵĸ�����ȥ1*/
			pTempTsrData->TsrQuan -= 1u;

		}
		else
		{
			/*������*/
		}
	}
}