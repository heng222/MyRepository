/*******************************************
�ļ���	��TsrParsePackAtsData.h
����	������
����ʱ�䣺2016-10
����	��ATS���ݽ�������ļ�
��ע	����
*******************************************/

#ifndef TSR_PARSEPACK_ATS_DATA_H_
#define TSR_PARSEPACK_ATS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "../TsrAdministrator/TsrDataAdmin.h"
#include "../../../Common/CircQueueStruct.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APPLENPOS_IN_REPLYTOATS 10U/*����ZC����Ϣ֡�� Ӧ�ò����ݳ��Ⱦ�����ʼ�ֽڵ�ƫ����*/
#define MSGLENPOS_IN_REPLYTOATS 12U/*����ZC����Ϣ֡�� �����ܳ��Ⱦ�����ʼ�ֽڵ�ƫ����*/
#define LENGTH_FIELD_BYTES      2U/*�����ֶ���ռ�ֽ���*/

/*ATS���͸�ZC�Ķ�̬������Ϣ�ṹ��*/
typedef struct S_TSR_DATASTRU_FROMATS
{
	UINT32_S AtsID;/*ATS ID*/
	UINT32_S TargetID;/*Ŀ��ID*/
	UINT16_S AtsCmdType;/*ATS��������*/
	UINT16_S RandomNo;/*�����*/
	Tsr_DataStru_Cell_Stru TsrCellData;/*ATS���õĵ�����ʱ������Ϣ*/
	UINT32_S Ats_Crc32;/*ATS���͵�CRC��Ϣ*/
}Tsr_DataStru_FromAts;

/*ZC���͸�ATS��������Ϣ�ṹ��*/
typedef struct S_TSR_DATASTRU_TOATS
{
	UINT16_S msgType_res;/*Ӧ�������ͣ���ʼֵ0/����ֵ0x0072 0x0074 0x0091 0x0093 0x00A1 0x00A3/����ֵ�Ƿ�/*/
	UINT16_S msgType_auto;/*�����㱨�������ͣ���ʼֵ0/����ֵ0x0070 0x0080/����ֵ�Ƿ�/*/
	UINT8_S replyCode;/*��Ӧ��*/
	Tsr_DataStru_Set_Stru TsrSetData;/*�ظ�����ʱ������Ϣ*/
}Tsr_DataStru_ToATS;

/*******************************************
������	��GetAtsCmdType
������������ȡATS���͹�������������
����	����
���	����
����ֵ	��ATS���͹�������������
*******************************************/
extern UINT16_S GetAtsCmdType(void);

/*******************************************
������	��GetLastTsrCellData
������������ȡ�״β����ĵ�����ʱ������Ϣ
����	����
���	����
����ֵ	���״β����ĵ�����ʱ������Ϣ
*******************************************/
extern Tsr_DataStru_Cell_Stru* GetLastTsrCellData(void);

/*******************************************
������	��ClearLastTsrCellData
��������������״β����ĵ�����ʱ������Ϣ
����	����
���	����
����ֵ	����
*******************************************/
extern void ClearLastTsrCellData(void);

/*******************************************
������	��GetRcvFromAtsData
������������ȡATS������������Ϣ�ṹ��
����	����
���	����
����ֵ	��ATS������������Ϣ�ṹ��
*******************************************/
extern Tsr_DataStru_FromAts* GetRcvFromAtsData(void);

/*******************************************
������	��ClearRcvFromAtsData
�������������ATS������������Ϣ�ṹ��
����	����
���	����
����ֵ	����
*******************************************/
extern void ClearRcvFromAtsData();

/*******************************************
������	��SetAtsCmdCrc32
��������������g_AtsCmdCrc32
����	��UINT32_S crc32
���	����
����ֵ	����
*******************************************/
extern void SetAtsCmdCrc32(UINT32_S crc32);

/*******************************************
������	��GetAtsSendTsrFsAndSsTime
������������ȡ�״ζ��μ�ʱʱ��
����	����
���	����
����ֵ	��AtsSendTsrFsAndSsTime�״ζ��μ�ʱʱ��
*******************************************/
extern UINT16_S GetAtsSendTsrFsAndSsTime(void);

/*******************************************
������	��AddAtsSendTsrFsAndSsTime
�����������ۼ��״ζ��μ�ʱʱ��
����	����
���	����
����ֵ	����
*******************************************/
extern void AddAtsSendTsrFsAndSsTime(void);

/*******************************************
������	��SetAtsSendTsrFsAndSsTime
���������������״ζ��μ�ʱʱ��
����	��fsAndSsTime�״ζ��μ�ʱʱ��
���	����
����ֵ	����
*******************************************/
extern void SetAtsSendTsrFsAndSsTime(UINT16_S fsAndSsTime);

/*******************************************
������	��GetTsrCellDataFromAts
������������ȡATS���͵���ʱ������Ϣ
����	����
���	����
����ֵ	��ATS���͵���ʱ������Ϣ
*******************************************/
extern Tsr_DataStru_Cell_Stru* GetTsrCellDataFromAts(void);

/*******************************************
������	��SetLastAtsCmdType
��������������ATS���һ����������
����	��lastCmdTypeATS���һ����������
���	����
����ֵ	����
*******************************************/
extern void SetLastAtsCmdType(UINT8_S lastCmdType);

/*******************************************
������	��SetReplyToAtsAutoCmdValue
�������������� �����ظ�ATS��������Ϣֵ
          �����������㱨/�����㱨
����	���ظ�ATS��������Ϣֵ
���	����
����ֵ	����
*******************************************/
extern void SetReplyToAtsAutoCmdValue(UINT8_S replyToAtsCmd);

/*******************************************
������	��WriteReplyToAtsData
����������д��ʱ������Ϣ�� ���͸�ZC�����ݽṹ
����	����
���	����
����ֵ	����
*******************************************/
extern void WriteReplyToAtsData(const Tsr_DataStru_Set_Stru* tsrDataStru);

/*******************************************
������	��ClearReplyToAtsData
������������� ��ATS���͵�������Ϣ�ṹ��
����	����
���	����
����ֵ	����
*******************************************/
extern void ClearReplyToAtsData(void);

/*******************************************
������	��CheckAtsInputData
�������������ATS�������ݵĺϷ���
����	����
���	����
����ֵ	��0ʧ�ܣ�1�ɹ�
*******************************************/
extern UINT8_S CheckAtsInputData(void);


/*******************************************
������	��ParseRcvFromAtsDataFrame
��������������ATS������������֡
����	��const UINT8_S* dataBuf, ���ݻ�����
		  const UINT16_S dataLength, ���ݳ���
���	����
����ֵ	��0: ���ݽ���ʧ��
		  1: ���ݽ����ɹ�
*******************************************/
extern UINT8_S ParseRcvFromAtsDataFrame(const UINT8_S* dataBuf, const UINT16_S dataLength);

/*******************************************
������	��PackReplyToAtsData
�������������ATS����
����	����
���	����
����ֵ	��0��ʧ�ܣ�1���ɹ�
*******************************************/
extern UINT8_S PackReplyToAtsData(void);

/*******************************************
������	��CalcCrc
��������������ATS���͹��������CRCֵ
����	����
���	����
����ֵ	�������CRCֵ
*******************************************/
extern UINT32_S CalcCrc(void);


/*******************************************
������  : GetReplyToAtsDataStru
������������ȡ����ATS������Ϣ�ṹ��
����    ����
���    ����
����ֵ	��replyToAtsData  ����ATS������Ϣ�ṹ��
*******************************************/
extern Tsr_DataStru_ToATS* GetReplyToAtsDataStru(void);

#ifdef __cplusplus
}
#endif
#endif