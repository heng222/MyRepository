/*******************************************
�ļ���	��TsrDataAdmin.h
����	������
����ʱ�䣺2016-10
����	����ʱ���ٹ���
��ע	����
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
������	��Pri_SetTsrCell
�����������Ե�����ʱ���ٱ�����ֵ��Ԫ����
����	��Tsr_DataStru_Cell_Stru *pLiftTsrCell,�����õ�����ʱ���ٱ���  Tsr_DataStru_Cell_Stru wrightTsrCell��
���	����
����ֵ	����
*******************************************/
extern void Pri_SetTsrCell(Tsr_DataStru_Cell_Stru *pLeftTsrCell,Tsr_DataStru_Cell_Stru wrightTsrCell);

/*******************************************
������	��Pri_SetTsrSet
��������������ʱ���ټ�������ֵ��Ԫ����
����	��Tsr_DataStru_Set_Stru *pLeftTsrSet,��������ʱ���ټ�����  Tsr_DataStru_Set_Stru wrightTsrSet��
���	����
����ֵ	����
*******************************************/
extern void Pri_SetTsrSet(Tsr_DataStru_Set_Stru *pLeftTsrSet,Tsr_DataStru_Set_Stru wrightTsrSet);

/*******************************************
������	��Pri_ClearTsrCell
�������������������ʱ����������Ϣ�ṹ��Ԫ����
����	����
���	����
����ֵ	����
*******************************************/
extern void Pri_ClearTsrCell(Tsr_DataStru_Cell_Stru* pTsrCellData);


/*******************************************
������	��InitTsrDataAdmin
������������ʼ����ʱ���ٹ�����Ϣ
����	����
���	����
����ֵ	����
*******************************************/
extern void InitTsrDataAdmin(void);

/*******************************************
������	��GetTsrDataAdmin
������������ȡ��ʱ���ٹ�����Ϣ
����	����
���	����
����ֵ	����ʱ���ٹ�����Ϣ
*******************************************/
extern Tsr_DataStru_Set_Stru* GetTsrDataAdmin(void);

/*******************************************
������	��AddTsrDataAdmin
����������������õ���ʱ������Ϣ����ʱ���ٹ�����Ϣ
����	��Tsr_DataStru_Cell_Stru* pTsrCellData,���õ���ʱ������Ϣ
���	����
����ֵ	����
*******************************************/
extern void AddTsrDataAdmin(const Tsr_DataStru_Cell_Stru* pTsrCellData);

/*******************************************
������	��DeleteTsrDataAdmin
��������������ʱ���ٹ�����Ϣ��ɾ��ĳ����ʱ����
����	��pSingleTsrDataStru��ʱ������Ϣ
���	����
����ֵ	����
*******************************************/
extern void DeleteTsrDataAdmin(const Tsr_DataStru_Cell_Stru* pTsrCellData);


#ifdef __cplusplus
}
#endif

#endif