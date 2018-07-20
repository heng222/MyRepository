/*******************************************
�ļ���	��DmuStruct.h
����	������
����ʱ�䣺2016-10
����	��DSU��ѯ����
��ע	����
*******************************************/

#ifndef DMU_STRUCT_H_
#define DMU_STRUCT_H_

#include "../../../../Common/CommonTypes.h"
#include "../../TsrSystem/TsrSystemDefine.h"

#define  LOGIC_MAX_NUM                                  25u										/*һ�����������а���������߼���������*/
#define  TSR_MAX_NUM									20u										/* һ��ZC�����������ʱ������������*/

#ifdef __cplusplus
extern "C" {
#endif

/*������ʱ���ٽṹ��*/
typedef struct S_TSR_DATASTRU_CELL
{
	UINT8_S TsrSpeed;/*����ֵ*/
	UINT8_S LogicSecQuan;/*�߼�������*/
	UINT16_S LogicSecId[LOGIC_MAX_NUM];/*�߼�����ID*/
}Tsr_DataStru_Cell_Stru;

/*��·��ʱ���ٽṹ��*/
typedef struct S_TSR_DATASTRU_SET
{
	UINT8_S TsrQuan;
	Tsr_DataStru_Cell_Stru CellTsrData[TSR_MAX_NUM];
}Tsr_DataStru_Set_Stru;

#ifdef __cplusplus
}
#endif

#endif
