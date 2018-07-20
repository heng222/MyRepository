/*******************************************
�ļ���	��TsrParsePackAtsData.c
����	������
����ʱ�䣺2016-10
����	��ATS���ݽ�������ļ�
��ע	����
*******************************************/

#include "TsrParsePackAtsData.h"
#include "ParsePackInterfaceDefine.h"
#include "../TsrTransmitFlagAdmin/TsrTransmitStateDataManage.h"
#include "../TsrIO/TsrOutputDataProcess.h"
#include "../TsrQuery/QueryManage.h"
#include "../TsrSystem/TsrSystemDefine.h"
#include "../TsrSystem/TsrSysConfigData.h"
#include "../TsrSystem/TsrSysStatusData.h"
/*#include "../TsrMaintenance/MaintainManager.h"*/
/*#include "../TsrMaintenance/CheckDevFault.h"*/
/*#include "../TsrMaintenance/EventCode.h"*/
#include "../../../Common/MemSet.h"
#include "../../../Common/Convert.h"
#include "../../../Common/CRC32.h"
#include "../../../Common/CommonQueue.h"
#include "../../../Dmu/DmuComm/Data/LogicSectionData.h"
#include "../../../PlatformAdapter/AppItf/AdptAppCommonDef.h"
#include "../../../PlatformAdapter/AppItf/AdptAppFileInterface.h"
#include "../../../PlatformAdapter/AppItf/AdptAppServiceInterface.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../IOManager/IOInterfaceProcess/IOInterfaceProcess.h"
#include "../../IOManager/ParseIOData/ParsePackAtsData.h"

static Tsr_DataStru_FromAts g_RcvFromAtsData;/*ATS������������Ϣ�ṹ��*/
static Tsr_DataStru_ToATS g_ReplyToAtsData;/*�ظ�ATS��������Ϣ�ṹ��*/
static UINT8_S g_LastAtsCmdType = DEFAULT_ZERO;/*ATS���һ����������*/
static UINT16_S g_TimeBetweenFsAndSs = UINT16_MAX;/*�״ζ��μ�ʱʱ��*/
static UINT32_S g_AtsCmdCrc32 = DEFAULT_ZERO; /*���ڴ�ż���ATS�����CRC32*/
static Tsr_DataStru_Cell_Stru g_LastTsrCellData;/*�����״����û�ȡ������ʱ����*/
static UINT16_S g_AtsFirCmdRandomNo = DEFAULT_ZERO;/*ATS�״�����������*/

static void SetAtsCmdType(UINT16_S atsCmdType);
static UINT32_S GetAtsID(void);
static void SetAtsID(UINT32_S atsID);
static UINT32_S GetTargetID(void);
static void SetTargetID(UINT32_S targetID);
static UINT16_S GetCurRandomNo(void);
static void SetCurRandomNo(UINT16_S randomNo);
static UINT32_S GetAts_Crc32(void);
static void SetAts_Crc32(UINT32_S ats_Crc32);
static void SetTsrCellDataFromAts(Tsr_DataStru_Cell_Stru tsrCellData);
static void SetLastTsrCellData(const Tsr_DataStru_Cell_Stru* pLastTsrCellData);
static UINT16_S GetAtsFirCmdRandomNo(void);
static void SetAtsFirCmdRandomNo(UINT16_S randomNo);
static UINT32_S GetAtsCmdCrc32(void);
static UINT8_S GetLastAtsCmdType(void);
static UINT16_S GetReplyToAtsResCmdValue(void);
static void SetReplyToAtsResCmdValue(UINT8_S replyToAtsCmd);
static UINT16_S GetReplyToAtsAutoCmdValue(void);
static UINT8_S GetReplyToAtsReplyCode(void);
static void SetReplyToAtsReplyCode(UINT8_S replyCode);
static Tsr_DataStru_Set_Stru* GetReplyToAtsTsrMsgStru(void);
static UINT8_S CheckRcvFromAtsCmdType(void);
static UINT8_S CheckRcvFromAtsTsrSpeed(void);
static UINT8_S CheckRcvFromAtsTsrNum(void);
static UINT8_S TSR_CheckRandomNo(void);
static UINT8_S CheckRcvFromAtsTsrLogicCount(void);
static UINT8_S CheckRcvFromAtsTsrLogicIds(void);
static UINT8_S CheckRcvFromAtsCrc(void);
static UINT16_S PackReplyToAtsDataFrame(UINT8_S* dataBuf, UINT16_S MaxDataLen);
static UINT16_S PackResponseFrame(UINT8_S* dataBuf, UINT16_S MaxDataLen);
static UINT16_S PackTsrReportFrame(UINT8_S* dataBuf, UINT16_S MaxDataLen);

/*******************************************
������	��GetAtsCmdType
������������ȡATS���͹�������������
����	����
���	����
����ֵ	��ATS���͹�������������
*******************************************/
UINT16_S GetAtsCmdType(void)
{
	return g_RcvFromAtsData.AtsCmdType;
}

/*******************************************
������	��SetAtsCmdType
��������������ATS���͹�������������ֵ
����	��UINT16_S atsCmdType,ATS���͹�������������ֵ
���	����
����ֵ	����
*******************************************/
static void SetAtsCmdType(UINT16_S atsCmdType)
{
	g_RcvFromAtsData.AtsCmdType = atsCmdType;
}

/*******************************************
������	��GetAtsID
������������ȡATS���͹�����AtsID
����	����
���	����
����ֵ	��ATS���͹�����AtsID
*******************************************/
static UINT32_S GetAtsID(void)
{
	return g_RcvFromAtsData.AtsID;
}

/*******************************************
������	��SetAtsID
��������������ATS���͹�����AtsID
����	��UINT32_S atsID,ATS���͹�����AtsIDֵ
���	����
����ֵ	����
*******************************************/
static void SetAtsID(UINT32_S atsID)
{
	g_RcvFromAtsData.AtsID = atsID;
}

/*******************************************
������	��GetTargetID
������������ȡATS���͹�����TargetID
����	����
���	����
����ֵ	��ATS���͹�����TargetID
*******************************************/
static UINT32_S GetTargetID(void)
{
	return g_RcvFromAtsData.TargetID;
}

/*******************************************
������	��SetTargetID
��������������ATS���͹�����TargetID
����	��UINT32_S targetID,ATS���͹�����TargetIDֵ
���	����
����ֵ	����
*******************************************/
static void SetTargetID(UINT32_S targetID)
{
	g_RcvFromAtsData.TargetID = targetID;
}

/*******************************************
������	��GetCurRandomNo
������������ȡATS���͹����������
����	����
���	����
����ֵ	��ATS���͹����������
*******************************************/
static UINT16_S GetCurRandomNo(void)
{
	return g_RcvFromAtsData.RandomNo;
}

/*******************************************
������	��SetCurRandomNo
��������������ATS���͹����������
����	��UINT16_S randomNo,ATS���͹����������
���	����
����ֵ	����
*******************************************/
static void SetCurRandomNo(UINT16_S randomNo)
{
	g_RcvFromAtsData.RandomNo = randomNo;
}

/*******************************************
������	��GetAts_Crc32
������������ȡATS���͹�����Ats_Crc32
����	����
���	����
����ֵ	��ATS���͹�����Ats_Crc32
*******************************************/
static UINT32_S GetAts_Crc32(void)
{
	return g_RcvFromAtsData.Ats_Crc32;
}

/*******************************************
������	��SetAts_Crc32
��������������ATS���͹�����Ats_Crc32
����	��UINT32_S ats_Crc32,ATS���͹�����Ats_Crc32ֵ
���	����
����ֵ	����
*******************************************/
static void SetAts_Crc32(UINT32_S ats_Crc32)
{
	g_RcvFromAtsData.Ats_Crc32 = ats_Crc32;
}

/*******************************************
������	��GetTsrCellDataFromAts
������������ȡATS���͵���ʱ������Ϣ
����	����
���	����
����ֵ	��ATS���͵���ʱ������Ϣ
*******************************************/
Tsr_DataStru_Cell_Stru* GetTsrCellDataFromAts(void)
{
	return &g_RcvFromAtsData.TsrCellData;
}

/*******************************************
������	��SetTsrCellDataFromAts
��������������ATS���͹�������ʱ������Ϣ
����	��Tsr_DataStru_Cell_Stru tsrCellData,������ʱ������Ϣ
���	����
����ֵ	����
*******************************************/
static void SetTsrCellDataFromAts(Tsr_DataStru_Cell_Stru tsrCellData)
{
	Pri_SetTsrCell(&(g_RcvFromAtsData.TsrCellData), tsrCellData);
}

/*******************************************
������	��GetRcvFromAtsData
������������ȡATS������������Ϣ�ṹ��
����	����
���	����
����ֵ	��ATS������������Ϣ�ṹ��
*******************************************/
Tsr_DataStru_FromAts* GetRcvFromAtsData(void)
{
	return &g_RcvFromAtsData;
}

/*******************************************
������	��ClearRcvFromAtsData
�������������ATS������������Ϣ�ṹ��
����	����
���	����
����ֵ	����
*******************************************/
void ClearRcvFromAtsData()
{
	g_RcvFromAtsData.AtsCmdType = DEFAULT_ZERO;
	g_RcvFromAtsData.AtsID = DEFAULT_ZERO;
	g_RcvFromAtsData.Ats_Crc32 = DEFAULT_ZERO;
	g_RcvFromAtsData.TargetID = DEFAULT_ZERO;
	Pri_ClearTsrCell(&(g_RcvFromAtsData.TsrCellData));
}

/*******************************************
������	��SetLastTsrCellData
���������������״β����ĵ�����ʱ������Ϣ
����	���״β����ĵ�����ʱ������Ϣ
���	����
����ֵ	����
*******************************************/
static void SetLastTsrCellData(const Tsr_DataStru_Cell_Stru* pLastTsrCellData)
{
	UINT8_S ii = DEFAULT_ZERO;

	if(pLastTsrCellData != NULL)
	{
		g_LastTsrCellData.TsrSpeed = pLastTsrCellData->TsrSpeed;
		g_LastTsrCellData.LogicSecQuan = pLastTsrCellData->LogicSecQuan;

		if ( pLastTsrCellData->LogicSecQuan > LOGIC_MAX_NUM)
		{
			for (ii = DEFAULT_ZERO; ii < LOGIC_MAX_NUM; ii++)
			{
				g_LastTsrCellData.LogicSecId[ii] = pLastTsrCellData->LogicSecId[ii];
			}
		}
		else
		{
			for (ii = DEFAULT_ZERO; ii < pLastTsrCellData->LogicSecQuan; ii++)
			{
				g_LastTsrCellData.LogicSecId[ii] = pLastTsrCellData->LogicSecId[ii];
			}
		}
	}
}
/*******************************************
������	��GetLastTsrCellData
������������ȡ�״β����ĵ�����ʱ������Ϣ
����	����
���	����
����ֵ	���״β����ĵ�����ʱ������Ϣ
*******************************************/
Tsr_DataStru_Cell_Stru* GetLastTsrCellData(void)
{
	return &g_LastTsrCellData;
}
/*******************************************
������	��ClearLastTsrCellData
��������������״β����ĵ�����ʱ������Ϣ
����	����
���	����
����ֵ	����
*******************************************/
void ClearLastTsrCellData(void)
{
	Pri_ClearTsrCell(&g_LastTsrCellData);
}

/*******************************************
������	��GetAtsFirCmdRandomNo
������������ȡATS�״�����������
����	����
���	����
����ֵ	��ATS�״�����������
*******************************************/
static UINT16_S GetAtsFirCmdRandomNo(void)
{
	return g_AtsFirCmdRandomNo;
}

/*******************************************
������	��SetAtsFirCmdRandomNo
��������������ATS�״�����������
����	��UINT16_S randomNo,ATS�״�����������
���	����
����ֵ	����
*******************************************/
static void SetAtsFirCmdRandomNo(UINT16_S randomNo)
{
	g_AtsFirCmdRandomNo = randomNo;
}

/*******************************************
������	��GetAtsCmdCrc32
������������ȡg_AtsCmdCrc32
����	����
���	����
����ֵ	��AtsCmdCrc32�����CRC32
*******************************************/
static UINT32_S GetAtsCmdCrc32(void)
{
	return g_AtsCmdCrc32;
}

/*******************************************
������	��SetAtsCmdCrc32
��������������g_AtsCmdCrc32
����	��UINT32_S crc32
���	����
����ֵ	����
*******************************************/
void SetAtsCmdCrc32(UINT32_S crc32)
{
	g_AtsCmdCrc32 = crc32;
}

/*******************************************
������	��GetAtsSendTsrFsAndSsTime
������������ȡ�״ζ��μ�ʱʱ��
����	����
���	����
����ֵ	��g_TimeBetweenFsAndSs�״ζ��μ�ʱʱ��
*******************************************/
UINT16_S GetAtsSendTsrFsAndSsTime(void)
{
	return g_TimeBetweenFsAndSs;
}

/*******************************************
������	��AddAtsSendTsrFsAndSsTime
�����������ۼ��״ζ��μ�ʱʱ��
����	����
���	����
����ֵ	����
*******************************************/
void AddAtsSendTsrFsAndSsTime(void)
{
	g_TimeBetweenFsAndSs = g_TimeBetweenFsAndSs+ 1u;
}

/*******************************************
������	��SetAtsSendTsrFsAndSsTime
���������������״ζ��μ�ʱʱ��
����	��fsAndSsTime�״ζ��μ�ʱʱ��
���	����
����ֵ	����
*******************************************/
void SetAtsSendTsrFsAndSsTime(UINT16_S fsAndSsTime)
{
	g_TimeBetweenFsAndSs = fsAndSsTime;
}

/*******************************************
������	��SetLastAtsCmdType
��������������ATS���һ����������
����	��lastCmdTypeATS���һ����������
���	����
����ֵ	����
*******************************************/
void SetLastAtsCmdType(UINT8_S lastCmdType)
{
	g_LastAtsCmdType = lastCmdType;
}

/*******************************************
������	��GetLastAtsCmdType
������������ȡATS���һ����������
����	����
���	����
����ֵ	��LastAtsCmdTypeATS���һ����������
*******************************************/
static UINT8_S GetLastAtsCmdType(void)
{
	return g_LastAtsCmdType;
}

/*******************************************
������	��GetReplyToAtsResCmdValue
������������ȡ Ӧ��ظ�ATS��������Ϣֵ
          �������״��ϵ�ȷ�ϻظ�/�����ϵ�ȷ�ϻظ�/�״�����TSR�ظ�/��������TSR�ظ�/�״�ȡ��TSR�ظ�/����ȡ��TSR�ظ�/
����	����
���	����
����ֵ	���ظ�ATS��Ӧ��������Ϣֵ
*******************************************/
static UINT16_S GetReplyToAtsResCmdValue(void)
{
	return g_ReplyToAtsData.msgType_res;
}

/*******************************************
������	��SetReplyToAtsResCmdValue
�������������� Ӧ��ظ�ATS��������Ϣֵ
          �������״��ϵ�ȷ�ϻظ�/�����ϵ�ȷ�ϻظ�/�״�����TSR�ظ�/��������TSR�ظ�/�״�ȡ��TSR�ظ�/����ȡ��TSR�ظ�/
����	���ظ�ATS��������Ϣֵ
���	����
����ֵ	����
*******************************************/
static void SetReplyToAtsResCmdValue(UINT8_S replyToAtsCmd)
{
	g_ReplyToAtsData.msgType_res = replyToAtsCmd;
}

/*******************************************
������	��GetReplyToAtsAutoCmdValue
������������ȡ �����ظ�ATS��Ӧ��������Ϣֵ
          �����������㱨/�����㱨
����	����
���	����
����ֵ	���ظ�ATS��Ӧ��������Ϣֵ
*******************************************/
static UINT16_S GetReplyToAtsAutoCmdValue(void)
{
	return g_ReplyToAtsData.msgType_auto;
}

/*******************************************
������	��SetReplyToAtsAutoCmdValue
�������������� �����ظ�ATS��������Ϣֵ
          �����������㱨/�����㱨
����	���ظ�ATS��������Ϣֵ
���	����
����ֵ	����
*******************************************/
void SetReplyToAtsAutoCmdValue(UINT8_S replyToAtsCmd)
{
	g_ReplyToAtsData.msgType_auto = replyToAtsCmd;
}

/*******************************************
������	��GetReplyToAtsReplyCode
������������ȡ �ظ�ATS�Ļ�Ӧ��
����	����
���	����
����ֵ	���ظ�ATS�Ļ�Ӧ��
*******************************************/
static UINT8_S GetReplyToAtsReplyCode(void)
{
	return g_ReplyToAtsData.replyCode;
}
/*******************************************
������	��SetReplyToAtsReplyCode
�������������� �ظ�ATS�Ļ�Ӧ��
����	���ظ�ATS�Ļ�Ӧ��
���	����
����ֵ	����
*******************************************/
static void SetReplyToAtsReplyCode(UINT8_S replyCode)
{
	g_ReplyToAtsData.replyCode = replyCode;
}

/*******************************************
������	��WriteReplyToAtsData
����������д��ʱ������Ϣ�� ���͸�ZC�����ݽṹ
����	����
���	����
����ֵ	����
*******************************************/
void WriteReplyToAtsData(const Tsr_DataStru_Set_Stru* tsrDataStru)
{
	if(NULL != tsrDataStru)
		Pri_SetTsrSet(&g_ReplyToAtsData.TsrSetData, *tsrDataStru);
}

/*******************************************
������	��GetReplyToAtsTsrMsgStru
������������ȡ ��ATS���͵���ʱ������Ϣ
����	����
���	����
����ֵ	����ATS���͵���ʱ������Ϣ
*******************************************/
static Tsr_DataStru_Set_Stru* GetReplyToAtsTsrMsgStru(void)
{
	return &g_ReplyToAtsData.TsrSetData;
}

/*******************************************
������  : GetReplyToAtsDataStru
������������ATS���͵�������Ϣ�ṹ��
����    ����
���    ����
����ֵ	��g_ReplyToAtsData  ATS��������������Ϣ�ṹ��
*******************************************/
Tsr_DataStru_ToATS* GetReplyToAtsDataStru(void)
{
	return &g_ReplyToAtsData;
}

/*******************************************
������	��ClearReplyToAtsData
������������� ��ATS���͵�������Ϣ�ṹ��
����	����
���	����
����ֵ	����
*******************************************/
void ClearReplyToAtsData(void)
{
	UINT8_S iCyc = DEFAULT_ZERO;
	g_ReplyToAtsData.msgType_auto = DEFAULT_ZERO;
	g_ReplyToAtsData.msgType_res = DEFAULT_ZERO;
	g_ReplyToAtsData.replyCode = TSR_UNKNOWN;
	for (iCyc = DEFAULT_ZERO; iCyc < TSR_MAX_NUM; iCyc++)
	{
		g_ReplyToAtsData.TsrSetData.TsrQuan = DEFAULT_ZERO;
		Pri_ClearTsrCell(&g_ReplyToAtsData.TsrSetData.CellTsrData[iCyc]);
	}
}

/*******************************************
������	��CheckRcvFromAtsCmdType
�������������ATS��������������Ϣ
����	����
���	����
����ֵ	��0ʧ�ܣ�1�ɹ�
*******************************************/
static UINT8_S CheckRcvFromAtsCmdType(void)
{
	UINT8_S rtnValue =DEFAULT_ZERO;

	/*LogMsgString( 1,"GetRcvFromAtsCmdType %d\n",GetAtsCmdType());*/
	if (ATS_TO_ZC_TSR_FRT_SET == GetAtsCmdType())
	{
		if (DEFAULT_ZERO == GetLastAtsCmdType())
		{
			SetLastAtsCmdType(LAST_ATS_FR_SET_CMD);
			rtnValue = TSR_SUCCESS;
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_FIR_SET_CMD_INCORRECT);
			/*LogMsgString( 1,"CheckRcvFromAtsCmdType TSR_FS_SET error\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_FS_SET_CMD_ERROR,LOG_EVENT_ERROR,1u,GetLastAtsCmdType());*/
			rtnValue = TSR_ERROR;/*���������״���������*/
		}				
	}
	else if (ATS_TO_ZC_TSR_FRT_CANCEL == GetAtsCmdType())
	{
		if (DEFAULT_ZERO == GetLastAtsCmdType())
		{
			SetLastAtsCmdType(LAST_ATS_FR_CANCEL_CMD);
			rtnValue = TSR_SUCCESS;
		}
		else
		{
			/*LogMsgString(1,"CheckRcvFromAtsCmdType TSR_FS_CANCEL error\n");*/
			SetReplyToAtsReplyCode(TSR_FIR_CANCEL_CMD_INCORRECT);
			/*SetEventLogList(DMS_ATS_CHECK_FS_CANCEL_CMD_ERROR,LOG_EVENT_ERROR,1u,GetLastAtsCmdType());*/
			rtnValue = TSR_ERROR;/*���������״�ȡ������*/
		}				
	}
	else if (ATS_TO_ZC_TSR_FRT_CONFIRM== GetAtsCmdType())
	{
		if(ZC_WORK_POP==GetZcWorkState())
		{
			if (DEFAULT_ZERO == GetLastAtsCmdType())
			{
				SetLastAtsCmdType(LAST_ATS_FR_CONFIRM_CMD);
				rtnValue = TSR_SUCCESS;
			}
			else
			{	
				/*LogMsgString( 1,"CheckRcvFromAtsCmdType TSR_FS_CONFIRM error\n");		*/
				/*SetEventLogList(DMS_ATS_CHECK_FS_CONFIRM_CMD_55_ERROR,LOG_EVENT_ERROR,1u,GetLastAtsCmdType());*/
				SetReplyToAtsReplyCode(TSR_FIR_CONFIRM_CMD_INCORRECT);
				rtnValue = TSR_ERROR;/*���������״�ȷ������*/
			}	
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_FIR_CONFIRM_CMD_INCORRECT_YETCONFIRMED);/*ϵͳ״̬��תΪ�����������ַ������״��ϵ�ȷ������*/
			/*SetEventLogList(DMS_ATS_CHECK_FS_CONFIRM_CMD_AA_ERROR,LOG_EVENT_ERROR,1u,GetZcWorkState());*/
			rtnValue = TSR_ERROR;/*���������״�ȷ������*/
		}			
	}
	else if (ATS_TO_ZC_TSR_SEC_SET == GetAtsCmdType())
	{
		if (LAST_ATS_FR_SET_CMD == GetLastAtsCmdType())
		{
			if (GetAtsSendTsrFsAndSsTime() > GetPeriodsBetweenFsAndSs())/*�����ȴ�ʱ��*/
			{
				/*LogMsgString(1, "CheckRcvFromAtsCmdType over time error\n");*/
				SetReplyToAtsReplyCode(TSR_OUTOFSETTIME_BETWEEN_FIR_SEC_CMD);
				/*SetEventLogList(DMS_ATS_CHECK_SS_SET_CMD_OVERTIME_ERROR,LOG_EVENT_ERROR,1u,GetAtsSendTsrFsAndSsTime());*/
				rtnValue = TSR_ERROR;
			}
			else
			{
				SetLastAtsCmdType(LAST_ATS_SR_SET_CMD);
				rtnValue = TSR_SUCCESS;
			}
		}
		else
		{
	
			/*LogMsgString( 1,"CheckRcvFromAtsCmdType last cmd not TSR_FS_SET\n");*/
			SetReplyToAtsReplyCode(TSR_SEC_SET_CMD_INCORRECT);
			/*SetEventLogList(DMS_ATS_CHECK_SS_SET_CMD_ERROR,LOG_EVENT_ERROR,1u,GetLastAtsCmdType());*/
			rtnValue = TSR_ERROR;
		}
		
	}
	else if (ATS_TO_ZC_TSR_SEC_CANCEL == GetAtsCmdType())
	{
		if (LAST_ATS_FR_CANCEL_CMD == GetLastAtsCmdType())
		{
			if (GetAtsSendTsrFsAndSsTime() > GetPeriodsBetweenFsAndSs())/*�����ȴ�ʱ��*/
			{
				/*LogMsgString(1,"CheckRcvFromAtsCmdType over time error\n");*/
				SetReplyToAtsReplyCode(TSR_OUTOFSETTIME_BETWEEN_FIR_SEC_CMD);
				/*SetEventLogList(DMS_ATS_CHECK_SS_CANCEL_CMD_OVERTIME_ERROR,LOG_EVENT_ERROR,1u,GetAtsSendTsrFsAndSsTime());*/
				rtnValue = TSR_ERROR;
			}
			else
			{
				SetLastAtsCmdType(LAST_ATS_SR_CANSCEL_CMD);
				rtnValue = TSR_SUCCESS;
			}
		}
		else
		{
			/*LogMsgString(1,"CheckRcvFromAtsCmdType last cmd not TSR_FS_CANCEL\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_SS_CANCEL_CMD_ERROR,LOG_EVENT_ERROR,1u,GetLastAtsCmdType());*/
			SetReplyToAtsReplyCode(TSR_SEC_CANCEL_CMD_INCORRECT);
			rtnValue = TSR_ERROR;
		}
		
	}
	else if (ATS_TO_ZC_TSR_SEC_CONFIRM == GetAtsCmdType())
	{
		if (LAST_ATS_FR_CONFIRM_CMD == GetLastAtsCmdType())
		{
			if (GetAtsSendTsrFsAndSsTime() > GetPeriodsBetweenFsAndSs())/*�����ȴ�ʱ��*/
			{
				/*LogMsgString( 1,"CheckRcvFromAtsCmdType over time error\n");*/
				/*SetEventLogList(DMS_ATS_CHECK_SS_CONFIRM_CMD_OVERTIME_ERROR,LOG_EVENT_ERROR,1u,GetAtsSendTsrFsAndSsTime());*/
				SetReplyToAtsReplyCode(TSR_OUTOFSETTIME_BETWEEN_FIR_SEC_CMD);
				rtnValue = TSR_ERROR;
			}
			else
			{
				SetLastAtsCmdType(LAST_ATS_SR_CONFIRM_CMD);
				rtnValue = TSR_SUCCESS;
			}
		}
		else
		{
			/*LogMsgString(1, "CheckRcvFromAtsCmdType last cmd not TSR_FS_CONFIRM \n");*/
			/*SetEventLogList(DMS_ATS_CHECK_SS_CONFIRM_CMD_ERROR,LOG_EVENT_ERROR,1u,GetLastAtsCmdType());*/
			SetReplyToAtsReplyCode(TSR_SEC_CONFIRM_CMD_INCORRECT);
			rtnValue = TSR_ERROR;
		}
	}
	else
	{
		/*LogMsgString( 1,"CheckRcvFromAtsCmdType error\n");*/
		SetReplyToAtsReplyCode(TSR_ATS_FRMAE_TYPE_INCORRECT);
		/*SetEventLogList(DMS_ATS_CHECK_CMD_ERROR,LOG_EVENT_ERROR,1u,GetAtsCmdType());*/
		rtnValue = TSR_ERROR;
	}
	return rtnValue;
}

/*******************************************
������	��CheckRcvFromAtsTsrSpeed
�������������ATS����������ʱ�����ٶ���Ϣ
����	����
���	����
����ֵ	��0ʧ�ܣ�1�ɹ�
*******************************************/
static UINT8_S CheckRcvFromAtsTsrSpeed(void)
{
	Tsr_DataStru_Cell_Stru* tempSingleTsrDataStru = NULL;
	Tsr_DataStru_Cell_Stru* lastSingleTsrDataStru = NULL;
	UINT8_S speedValue = DEFAULT_ZERO;
	UINT8_S rtnValue =DEFAULT_ZERO;

	tempSingleTsrDataStru = GetTsrCellDataFromAts();
	lastSingleTsrDataStru = GetLastTsrCellData();

	if(ATS_TO_ZC_TSR_FRT_SET == GetAtsCmdType())	
	{
		if ((tempSingleTsrDataStru->TsrSpeed == DEFAULT_ZERO)||(tempSingleTsrDataStru->TsrSpeed > GetTsrMaxSpeed()))
		{
			SetReplyToAtsReplyCode(TSR_FIR_SET_TSRSPEEDVALUE_OVERFLOW);/*�ٶ���Ч*/
			/*LogMsgString(1, "CheckRcvFromAtsTsrSpeed Invalid\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_FS_SET_SPEED_ILLEGAL,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->TsrSpeed);*/
			rtnValue = TSR_ERROR;
		}
		else
		{
			speedValue = CheckSingleTSRSpeed(&tempSingleTsrDataStru->LogicSecId[0], tempSingleTsrDataStru->LogicSecQuan, tempSingleTsrDataStru->TsrSpeed);

			if(DEFAULT_ZERO == speedValue)
			{
				/*LogMsgString(1, "CheckRcvFromAtsTsrSpeed  beyond singleTsrSpeed\n");*/
				SetReplyToAtsReplyCode(TSR_UNKNOWN);/*�ٶ���Ч*/
				/*SetEventLogList(DMS_ATS_CHECK_FS_SET_SPEED_CHECK_ERROR,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->TsrSpeed);*/
				rtnValue = TSR_ERROR;
			}
			else if(1u == speedValue)
			{
				SetReplyToAtsReplyCode(TSR_OK);/*�ٶ���Ч*/
				rtnValue = TSR_SUCCESS;
			}
			else
			{
			
				/*LogMsgString(1, "CheckRcvFromAtsTsrSpeed some beyond singleTsrSpeed\n");*/
				SetReplyToAtsReplyCode(TSR_FIR_SET_TSRSPEEDVALUE_GREATERTHAN_STATICDEFAULTVALUE);/*���õ���ʱ������ֵ����ĳһ���߼����ε���·����������ֵ,�ٶ���Ч*/
				/*SetEventLogList(DMS_ATS_CHECK_FS_SET_SPEED_CHECK_LIMIT,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->TsrSpeed);*/
				rtnValue = TSR_ERROR;
			}						
		}
	}
	else if(ATS_TO_ZC_TSR_SEC_SET == GetAtsCmdType())
	{
		/*�������õ���ʱ�����ٶ�ֵ���״����õĲ�һ�£����ٶ���Ч*/
		if ((tempSingleTsrDataStru->TsrSpeed == DEFAULT_ZERO)||(tempSingleTsrDataStru->TsrSpeed > GetTsrMaxSpeed()) || (tempSingleTsrDataStru->TsrSpeed != lastSingleTsrDataStru->TsrSpeed))
		{
			/*LogMsgString(1, "CheckRcvFromAtsTsrSpeed Invalid\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_FS_SS_SET_SPEED_DIFFER,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->TsrSpeed);*/
			SetReplyToAtsReplyCode(TSR_SEC_SET_TSRSPEEDVALUE_DIFFERFROMFIR);/*�ٶ���Ч*/
			rtnValue = TSR_ERROR;
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_OK);/*�ٶ���Ч*/
			rtnValue = TSR_SUCCESS;
		}
	}
	else if (ATS_TO_ZC_TSR_FRT_CONFIRM== GetAtsCmdType())
	{
		if (tempSingleTsrDataStru->TsrSpeed != UINT8_MAX)
		{
			/*LogMsgString(1,"CheckRcvFromAtsTsrSpeed speed is not zero\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_FS_CONFIRM_SPEED_ILLEGAL,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->TsrSpeed);*/
			SetReplyToAtsReplyCode(TSR_UNKNOWN);
			rtnValue = TSR_ERROR;
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_OK);		
			rtnValue = TSR_SUCCESS;
		}
	}
	else if (ATS_TO_ZC_TSR_SEC_CONFIRM == GetAtsCmdType())
	{
		if (tempSingleTsrDataStru->TsrSpeed != UINT8_MAX)
		{
			/*LogMsgString(1, "CheckRcvFromAtsTsrSpeed speed is not zero\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_FS_SS_CONFIRM_SPEED_DIFFER,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->TsrSpeed);*/
			SetReplyToAtsReplyCode(TSR_UNKNOWN);
			rtnValue = TSR_ERROR;
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_OK);
			rtnValue = TSR_SUCCESS;
		}
	}
	else if ((ATS_TO_ZC_TSR_FRT_CANCEL == GetAtsCmdType()) || (ATS_TO_ZC_TSR_SEC_CANCEL == GetAtsCmdType()))
	{
		SetReplyToAtsReplyCode(TSR_OK);			
		rtnValue = TSR_SUCCESS;
	}
	else
	{
		/*LogMsgString(1,"CheckRcvFromAtsTsrSpeed error\n");*/
		SetReplyToAtsReplyCode(TSR_UNKNOWN);
		rtnValue = TSR_ERROR;
	}
	
	return rtnValue;
}


/*******************************************
������	��CheckRcvFromAtsTsrNum
�������������ATS����������ʱ������Ŀ
����	����
���	����
����ֵ	��0ʧ�ܣ�1�ɹ�
*******************************************/
static UINT8_S CheckRcvFromAtsTsrNum(void)
{
	UINT8_S result = DEFAULT_ZERO;
	Tsr_DataStru_Set_Stru* pTempTsrData = NULL;

	pTempTsrData = GetTsrDataAdmin();

	if (ATS_TO_ZC_TSR_FRT_SET == GetAtsCmdType())
	{
		if(pTempTsrData->TsrQuan>=TSR_MAX_NUM)
		{
			SetReplyToAtsReplyCode(TSR_TSRQUANTITY_OVERFLOW);/*TSR������Ч*/

			/*LogMsgString( 1,"CheckRcvFromAtsTsrNum beyond TSR_MAX_NUM\n");			*/
			/*SetEventLogList(DMS_ATS_CHECK_SET_TSR_NUM_OVERTOP,LOG_EVENT_ERROR,1u,pTempTsrData->TsrQuan);*/
			result = TSR_ERROR;
		}
		else
		{
			result = TSR_SUCCESS;
		}
	}
	else if (ATS_TO_ZC_TSR_FRT_CANCEL == GetAtsCmdType())
	{
		if((pTempTsrData->TsrQuan == DEFAULT_ZERO) ||(pTempTsrData->TsrQuan>TSR_MAX_NUM))
		{			
			SetReplyToAtsReplyCode(TSR_FIR_CANCEL_CMD_INCORRECT_ZCHASNOTSR);/*TSR������Ч*/

			/*LogMsgString( 1,"CheckRcvFromAtsTsrNum saveTsrNum is zero or beyond TSR_MAX_NUM\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_CANCEL_TSR_NUM_ERROR,LOG_EVENT_ERROR,1u,pTempTsrData->TsrQuan);*/
			result = TSR_ERROR;
		}
		else
		{
			result = TSR_SUCCESS;
		}
	}
	else
	{
		result = TSR_SUCCESS;
	}

	return result;

}

/*******************************************
������	��TSR_CheckRandomNo
�����������������������״������������Ƿ�һ��
����	����
���	����
����ֵ	��0ʧ�ܣ�1�ɹ�
*******************************************/
static UINT8_S TSR_CheckRandomNo(void)
{
	UINT8_S retv = TSR_SUCCESS;
	UINT16_S tmpAtsCmdType = DEFAULT_ZERO;
	UINT16_S tmpAtsFirCmdRandomNo = DEFAULT_ZERO;
	UINT16_S tmpCurRandomNo = DEFAULT_ZERO;
	tmpAtsCmdType = GetAtsCmdType();
	if((ATS_TO_ZC_TSR_SEC_SET == tmpAtsCmdType) || (ATS_TO_ZC_TSR_SEC_CANCEL == tmpAtsCmdType) 
		|| (ATS_TO_ZC_TSR_SEC_CONFIRM == tmpAtsCmdType))
	{
		tmpAtsFirCmdRandomNo = GetAtsFirCmdRandomNo();/*�״����������*/
		tmpCurRandomNo = GetCurRandomNo();/*�������������*/
		if(tmpCurRandomNo != tmpAtsFirCmdRandomNo)
		{
			retv = TSR_ERROR;
		}
		else
		{
			retv = TSR_SUCCESS;
		}
	}
	else
	{
		retv = TSR_SUCCESS;
	}
	return retv;
}

/*******************************************
������	��CheckRcvFromAtsTsrLogicCount
�������������ATS����������ʱ�����߼�����������Ϣ
����	����
���	����
����ֵ	��0ʧ�ܣ�1�ɹ�
*******************************************/
static UINT8_S CheckRcvFromAtsTsrLogicCount(void)
{
	Tsr_DataStru_Cell_Stru* tempSingleTsrDataStru = NULL;
	Tsr_DataStru_Cell_Stru* lastSingleTsrDataStru = NULL;
	UINT8_S rtnValue = DEFAULT_ZERO;

	tempSingleTsrDataStru = GetTsrCellDataFromAts();
	lastSingleTsrDataStru = GetLastTsrCellData();

	if (ATS_TO_ZC_TSR_FRT_SET == GetAtsCmdType())
	{
		if ((tempSingleTsrDataStru->LogicSecQuan == 0) || (tempSingleTsrDataStru->LogicSecQuan > LOGIC_MAX_NUM))
		{
			SetReplyToAtsReplyCode(TSR_FIR_SET_TSRLOGICSECTIONQUANTITY_OVERFLOW);
			/*LogMsgString( 1,"CheckRcvFromAtsTsrLogicCount LogicOfTsrNum is zero or beyond LOGIC_MAX_NUM\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_TSR_LOGIC_ERROR,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->LogicSecQuan);*/
			rtnValue = TSR_ERROR;
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_OK);
			rtnValue = TSR_SUCCESS;
		}
	}
	else if( ATS_TO_ZC_TSR_FRT_CANCEL == GetAtsCmdType())
	{
		if ((tempSingleTsrDataStru->LogicSecQuan == 0) || (tempSingleTsrDataStru->LogicSecQuan > LOGIC_MAX_NUM))
		{
			SetReplyToAtsReplyCode(TSR_FIR_CANCEL_TSRLOGICSECTIONQUANTITY_OVERFLOW);
			/*LogMsgString( 1,"CheckRcvFromAtsTsrLogicCount LogicOfTsrNum is zero or beyond LOGIC_MAX_NUM\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_TSR_LOGIC_ERROR,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->LogicSecQuan);*/
			rtnValue = TSR_ERROR;
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_OK);
			rtnValue = TSR_SUCCESS;
		}
	}
	else if (ATS_TO_ZC_TSR_SEC_SET == GetAtsCmdType())
	{
		if (tempSingleTsrDataStru->LogicSecQuan != lastSingleTsrDataStru->LogicSecQuan)
		{			
			SetReplyToAtsReplyCode(TSR_SEC_SET_TSRLOGICSECTIONQUANTITY_DIFFERFROMFIR);
			/*LogMsgString(1, "CheckRcvFromAtsTsrLogicCount LogicOfTsrNum unqual to lastLogicOfTsrNum\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_TSR_LOGIC_DIFFER,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->LogicSecQuan);*/
			rtnValue = TSR_ERROR;
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_OK);
			rtnValue = TSR_SUCCESS;
		}
	}
	else if(ATS_TO_ZC_TSR_SEC_CANCEL == GetAtsCmdType())
	{
		if (tempSingleTsrDataStru->LogicSecQuan != lastSingleTsrDataStru->LogicSecQuan)
		{		
			SetReplyToAtsReplyCode(TSR_SEC_CANCEL_TSRLOGICSECTIONQUANTITY_DIFFERFROMFIR);
			/*LogMsgString(1, "CheckRcvFromAtsTsrLogicCount LogicOfTsrNum unqual to lastLogicOfTsrNum\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_TSR_LOGIC_DIFFER,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->LogicSecQuan);*/
			rtnValue = TSR_ERROR;
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_OK);
			rtnValue = TSR_SUCCESS;
		}
	}
	else if((ATS_TO_ZC_TSR_FRT_CONFIRM == GetAtsCmdType()) ||
		(ATS_TO_ZC_TSR_SEC_CONFIRM == GetAtsCmdType()))
	{
		if (tempSingleTsrDataStru->LogicSecQuan != DEFAULT_ZERO)
		{
			/*LogMsgString(1, "CheckRcvFromAtsTsrLogicCount LogicOfTsrNum is not zero\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_CONFIRM_HAVA_LOGIC,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->LogicSecQuan);*/
			rtnValue = TSR_ERROR;
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_OK);
			rtnValue = TSR_SUCCESS;
		}
	}
	else
	{
	
		/*LogMsgString(1, "CheckRcvFromAtsTsrLogicCount error\n");*/
		SetReplyToAtsReplyCode(TSR_ATS_FRMAE_TYPE_INCORRECT);

		rtnValue = TSR_ERROR;
	}

	return rtnValue;
}

/*******************************************
������	��CheckRcvFromAtsTsrLogicIds
�������������ATS����������ʱ�����߼�����id
����	����
���	����
����ֵ	��0ʧ�ܣ�1�ɹ�
*******************************************/
static UINT8_S CheckRcvFromAtsTsrLogicIds(void)
{
	UINT8_S iCyc = DEFAULT_ZERO;
	UINT8_S iCyc_Inner = DEFAULT_ZERO;
	Tsr_DataStru_Cell_Stru* tempSingleTsrDataStru = NULL;
	Tsr_DataStru_Cell_Stru* lastSingleTsrDataStru = NULL;
	Tsr_DataStru_Set_Stru* tempTsrDataStru = NULL;
	UINT16_S tempLogicIds[MAX_SECTION_ID_NUM] = {DEFAULT_ZERO};
	UINT8_S tempTsrFindFlag = 0u;
	UINT8_S rtnValue = TSR_SUCCESS;/*��������ֵ*/
	UINT8_S checkTemp = DEFAULT_ZERO;

	tempSingleTsrDataStru = GetTsrCellDataFromAts();
	lastSingleTsrDataStru = GetLastTsrCellData();
	tempTsrDataStru = GetTsrDataAdmin();

	for (iCyc = DEFAULT_ZERO; iCyc < tempSingleTsrDataStru->LogicSecQuan; iCyc++)
	{
		if ((tempSingleTsrDataStru->LogicSecId[iCyc] < 1) || (tempSingleTsrDataStru->LogicSecId[iCyc] > GetLineLogicSectionMaxId()))
		{		
			/*SetEventLogList(DMS_ATS_CHECK_LOGICID_ERROR,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->LogicSecId[iCyc] );*/
			/*LogMsgString(1,"CheckRcvFromAtsTsrLogicIds Invalid\n");*/
			SetReplyToAtsReplyCode(TSR_UNKNOWN);/*�����߼�����ID��Ч�ĺ�*/
			rtnValue = TSR_ERROR;
		}
		else
		{
			/*do nothing*/
		}
	}
	if(rtnValue == TSR_SUCCESS)
	{
		if (ATS_TO_ZC_TSR_FRT_SET == GetAtsCmdType()) 
		{
			checkTemp = CheckSingleTsrLogicId(&tempSingleTsrDataStru->LogicSecId[0],tempSingleTsrDataStru->LogicSecQuan);
			if (DEFAULT_ZERO == checkTemp)
			{
				for (iCyc = DEFAULT_ZERO; iCyc < tempTsrDataStru->TsrQuan; iCyc++)/*��ע��·�߼�����ID*/
				{
					for (iCyc_Inner = DEFAULT_ZERO; iCyc_Inner < tempTsrDataStru->CellTsrData[iCyc].LogicSecQuan; iCyc_Inner++)
					{
						if (tempTsrDataStru->CellTsrData[iCyc].TsrSpeed != DEFAULT_ZERO)
						{
							tempLogicIds[tempTsrDataStru->CellTsrData[iCyc].LogicSecId[iCyc_Inner]] = 1u;
						}
					}
				}
				for (iCyc = DEFAULT_ZERO; iCyc < tempSingleTsrDataStru->LogicSecQuan; iCyc++)
				{
					if (1u == tempLogicIds[tempSingleTsrDataStru->LogicSecId[iCyc]])
					{
			
						/*LogMsgString(1,"CheckRcvFromAtsTsrLogicIds had speed in logicId!\n");*/
						/*SetEventLogList(TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGICSECTIONHASBEENSET,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->LogicSecId[iCyc]);*/
						SetReplyToAtsReplyCode(TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGICSECTIONHASBEENSET);
						rtnValue = TSR_ERROR;
						break;
					}
				}
			}
			else if(1u == checkTemp)/*������ ��Ӧ�� 40u����41u*/
			{
				SetReplyToAtsReplyCode(TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGSECATBOTHSWITCHPOSITON_A);/*�������Ӧ��*/
				rtnValue = TSR_ERROR;
			}
			else
			{
		
				/*LogMsgString(1, "CheckRcvFromAtsTsrLogicIds logic error\n");*/
				/*SetEventLogList(DMS_ATS_CHECK_FS_SET_TSR_FR_SECTION_COLLISION,LOG_EVENT_ERROR,1u,checkTemp);*/
				SetReplyToAtsReplyCode(TSR_UNKNOWN);/*�������Ӧ��*/
				rtnValue = TSR_ERROR;
			}		
		}
		else if(ATS_TO_ZC_TSR_FRT_CANCEL == GetAtsCmdType())
		{	
			checkTemp = CheckSingleTsrLogicId(&tempSingleTsrDataStru->LogicSecId[0],tempSingleTsrDataStru->LogicSecQuan);
			if (DEFAULT_ZERO == checkTemp)
			{
				for (iCyc = DEFAULT_ZERO; iCyc < tempTsrDataStru->TsrQuan; iCyc++)
				{
					tempTsrFindFlag = 1u;/*�Ƿ��ҵ�Ҫȡ������ʱ���ٱ�־��Ĭ��Ϊ1���ҵ���0Ϊû���ҵ�*/
					if (tempSingleTsrDataStru->LogicSecQuan == tempTsrDataStru->CellTsrData[iCyc].LogicSecQuan)
					{
						for (iCyc_Inner = DEFAULT_ZERO; iCyc_Inner < tempSingleTsrDataStru->LogicSecQuan; iCyc_Inner++)
						{
							if (tempSingleTsrDataStru->LogicSecId[iCyc_Inner] != tempTsrDataStru->CellTsrData[iCyc].LogicSecId[iCyc_Inner])
							{
								tempTsrFindFlag = DEFAULT_ZERO;
							}  
							else
							{
								/*������*/
							}
						}
					}
					else
					{
						tempTsrFindFlag = DEFAULT_ZERO;/*�߼����θ�������*/
					}
					if (1u == tempTsrFindFlag)
					{
						break;
					}
					else
					{
						/*����ѭ��*/
					}
				}

				if(0u == tempTsrFindFlag)
				{
					/*LogMsgString(1, "CheckRcvFromAtsTsrLogicIds not find\n");*/
					/*SetEventLogList(DMS_ATS_CHECK_TSR_FR_CANCEL_NONE,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->LogicSecId[iCyc]);*/
					SetReplyToAtsReplyCode(TSR_FIR_CANCEL_CMD_INCORRECT_ZCHASNOTSR);
					rtnValue = TSR_ERROR;
				
				}
			}
			else if(1u == checkTemp)/*������ ��Ӧ�� 40u����41u*/
			{
				SetReplyToAtsReplyCode(TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGSECATBOTHSWITCHPOSITON_A);/*�������Ӧ��*/
				rtnValue = TSR_ERROR;
			}
			else
			{
		
				/*LogMsgString(1, "CheckRcvFromAtsTsrLogicIds logic error\n");*/
				/*SetEventLogList(DMS_ATS_CHECK_FS_SET_CANCEL_FR_SECTION_COLLISION,LOG_EVENT_ERROR,1u,checkTemp);*/
				SetReplyToAtsReplyCode(TSR_UNKNOWN);/*�������Ӧ��*/
				rtnValue = TSR_ERROR;
			}	
	
		}
		else if ((ATS_TO_ZC_TSR_SEC_SET == GetAtsCmdType()) || (ATS_TO_ZC_TSR_SEC_CANCEL == GetAtsCmdType()))
		{
			for (iCyc = DEFAULT_ZERO; iCyc < tempSingleTsrDataStru->LogicSecQuan; iCyc++)
			{
				if (tempSingleTsrDataStru->LogicSecId[iCyc] != lastSingleTsrDataStru->LogicSecId[iCyc])
				{	
					/*LogMsgString(1, "CheckRcvFromAtsTsrLogicIds logicId not equal to lastlogicId\n");*/
					/*SetEventLogList(DMS_ATS_CHECK_FS_SS_LOGICID_DIFFER,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->LogicSecId[iCyc]);*/
					SetReplyToAtsReplyCode(TSR_SEC_CANCEL_TSRLOGICSECTIONID_DIFFERFROMFIR);		
					rtnValue = TSR_ERROR;
					break;
				}
				else
				{
				
					/*����*/
				}
			}
		}
		else
		{
	
		}
	}
	if(rtnValue == TSR_SUCCESS)
	{
		SetReplyToAtsReplyCode(TSR_OK);
	}
	return rtnValue;
}

/*******************************************
������	��CheckRcvFromAtsCrc
����������У��ATS��������CRCУ����Ϣ
����	����
���	����
����ֵ	��0ʧ�ܣ�1�ɹ�
*******************************************/
static UINT8_S CheckRcvFromAtsCrc(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT32_S temp_Crc = DEFAULT_ZERO;

	if ((ATS_TO_ZC_TSR_SEC_SET == GetAtsCmdType()) ||
		(ATS_TO_ZC_TSR_SEC_CANCEL == GetAtsCmdType()) ||
		(ATS_TO_ZC_TSR_SEC_CONFIRM == GetAtsCmdType()))
	{
		temp_Crc = CalcCrc();
		if (temp_Crc == GetAts_Crc32())
		{
			SetReplyToAtsReplyCode(TSR_OK);
			rtnValue = TSR_SUCCESS;
		}
		else
		{
		
			/*LogMsgString(1,"CheckRcvFromAtsCrc  crc  not equal\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_SS_CRC32_ERROR,LOG_EVENT_ERROR,1u,temp_Crc);*/
			SetReplyToAtsReplyCode(TSR_CRC32_CHECK_ERROR);
			rtnValue = TSR_ERROR;
		}				
	}
	else
	{
		/*������*/
		rtnValue = TSR_SUCCESS;
	}
	return rtnValue;
}




/*******************************************
������	��CheckAtsInputData
�������������ATS�������ݵĺϷ���
����	����
���	����
����ֵ	��0ʧ�ܣ�1�ɹ�
*******************************************/
UINT8_S CheckAtsInputData(void)
{
	UINT8_S rtnVlue = DEFAULT_ZERO;/*��������ֵ*/

	if (TSR_SUCCESS == TSR_CheckRandomNo())/*�������������������״������Ƿ�һ��*/
	{
		if (TSR_SUCCESS == CheckRcvFromAtsCmdType())/*���ATS��������������Ϣ�Ƿ���ȷ*/
		{
			if (TSR_SUCCESS == CheckRcvFromAtsTsrNum()) /*���ATS����������ʱ������Ŀ�Ƿ���ȷ*/
			{
				if (TSR_SUCCESS == CheckRcvFromAtsTsrLogicCount()) /*���ATS����������ʱ�����߼���ID��Ŀ�Ƿ���ȷ*/
				{
					if (TSR_SUCCESS == CheckRcvFromAtsTsrLogicIds()) /*���ATS����������ʱ�����߼���ID�Ƿ���ȷ*/
					{
						if (TSR_SUCCESS == CheckRcvFromAtsTsrSpeed())/*���ATS����������ʱ�����ٶ��Ƿ���ȷ*/
						{
							if (TSR_SUCCESS == CheckRcvFromAtsCrc()) /*���ATS��������������ϢCRC�Ƿ���ȷ*/
							{
								rtnVlue = TSR_SUCCESS;
							}
							else
							{
								rtnVlue = TSR_ERROR;
							}
						}
						else
						{
							rtnVlue = TSR_ERROR;
						}
					}
					else
					{
						rtnVlue = TSR_ERROR;
					}
				}
				else
				{
					rtnVlue = TSR_ERROR;
				}
			}
			else
			{
				rtnVlue = TSR_ERROR;
			}
		}
		else
		{
			rtnVlue = TSR_ERROR;
		}
	}
	else
	{
		rtnVlue = TSR_ERROR;
	}
	return rtnVlue;
}




/*******************************************
������	��ParseRcvFromAtsDataFrame
��������������ATS������������֡
����	��const UINT8_S* dataBuf, ���ݻ�����
		  const UINT16_S dataLength, ���ݳ���
���	����
����ֵ	��0: ���ݽ���ʧ��
		  1: ���ݽ����ɹ�
*******************************************/
UINT8_S ParseRcvFromAtsDataFrame(const UINT8_S* dataBuf, const UINT16_S dataLength)
{
	UINT8_S Retv = TSR_SUCCESS;
	UINT16_S iPos = DEFAULT_ZERO;/*������ƫ��ָ��*/
	UINT16_S iCyc = DEFAULT_ZERO;/*ѭ�����Ʊ���*/
	UINT16_S interftype = DEFAULT_ZERO;
	UINT32_S srcID = DEFAULT_ZERO;
	UINT32_S dstID = DEFAULT_ZERO;
	UINT16_S appAllDataLen = DEFAULT_ZERO;         /*Ӧ�ò������ܳ���*/
	UINT16_S appDataLen = DEFAULT_ZERO;            /*Ӧ�ò㱨���ܳ���*/
	UINT16_S appDataType = DEFAULT_ZERO;           /*Ӧ�ò㱨������*/
	UINT16_S reserve = DEFAULT_ZERO;              /*Ԥ��*/
	UINT16_S randomNum = DEFAULT_ZERO;              /*�����*/
	Tsr_DataStru_Cell_Stru tmpTsrCellData;
	UINT32_S tmpAts_Crc32 = DEFAULT_ZERO;
	Tsr_DataStru_Cell_Stru* pTmpTsrCellDataFromAts = NULL;

	Pri_ClearTsrCell(&tmpTsrCellData);
	if ((dataBuf != NULL) && (dataLength > DEFAULT_ZERO))
	{
		interftype = ShortFromChar(&dataBuf[iPos]);
		iPos += 2u;
		if (0x1010u != interftype)/*��Ϣ���ݺϷ��Լ���*/
		{
			Retv = TSR_ERROR;
		}
		else
		{/*do nothing*/}

		srcID = LongFromChar(&dataBuf[iPos]);
		iPos += 4u;
		if(0x00000301u != srcID)
		{
			Retv = TSR_ERROR;
		}
		else
		{/*do nothing*/}

		dstID = LongFromChar(&dataBuf[iPos]);
		iPos += 4u;
		if(0x00001E01u > dstID || 0x00001EFFu < dstID)
		{
			Retv = TSR_ERROR;
		}
		else
		{/*do nothing*/}

		if(TSR_SUCCESS == Retv)
		{
			SetAtsID(srcID);/*���ͷ���ʶ*/
			SetTargetID(dstID);/*���շ���ʶ*/
			appAllDataLen = ShortFromChar(&dataBuf[iPos]);/*Ӧ�ò����ݳ���*/
			iPos += 2u;
	        appDataLen = ShortFromChar(&dataBuf[iPos]);/*�����ܳ���*/
			iPos += 2u;
	        appDataType = ShortFromChar(&dataBuf[iPos]);/*��������*/
			iPos += 2u;
	        reserve = ShortFromChar(&dataBuf[iPos]);/*Ԥ��*/
			iPos += 2u;

			SetAtsCmdType(ShortFromChar(&dataBuf[iPos]));/*��������*/
			iPos += 2u;
			randomNum = ShortFromChar(&dataBuf[iPos]);/*�����*/
			iPos += 2u;
			SetCurRandomNo(randomNum);

			appDataType = GetAtsCmdType();
			pTmpTsrCellDataFromAts = GetTsrCellDataFromAts();
			if ( ATS_TO_ZC_TSR_FRT_SET == appDataType)
			{
				tmpTsrCellData.TsrSpeed = dataBuf[iPos];/*����ֵ*/
				iPos++;
				tmpTsrCellData.LogicSecQuan = dataBuf[iPos];/*�߼����θ���*/
				iPos++;
				if (tmpTsrCellData.LogicSecQuan > LOGIC_MAX_NUM)
				{
					for (iCyc = DEFAULT_ZERO; iCyc < LOGIC_MAX_NUM; iCyc++)
					{
						tmpTsrCellData.LogicSecId[iCyc] = ShortFromChar(&dataBuf[iPos]);
						iPos += 2u;
					}
				}
				else
				{
					for (iCyc = DEFAULT_ZERO; iCyc < tmpTsrCellData.LogicSecQuan; iCyc++)
					{
						tmpTsrCellData.LogicSecId[iCyc] = ShortFromChar(&dataBuf[iPos]);
						iPos += 2u;
					}
				}
				SetTsrCellDataFromAts(tmpTsrCellData);/*�߼����μ���*/

				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_FRT_SET_REPLY);
				SetLastTsrCellData(pTmpTsrCellDataFromAts);
				SetAtsFirCmdRandomNo(randomNum);/*�״������¼�������*/
			}
			else if(ATS_TO_ZC_TSR_FRT_CANCEL == appDataType)
			{
				tmpTsrCellData.TsrSpeed = DEFAULT_ZERO;/*����ȡ����������ֵ��0*/
				
				tmpTsrCellData.LogicSecQuan = dataBuf[iPos];/*�߼����θ���*/
				iPos++;
				if (tmpTsrCellData.LogicSecQuan > LOGIC_MAX_NUM)
				{
					for (iCyc = DEFAULT_ZERO; iCyc < LOGIC_MAX_NUM; iCyc++)
					{
						tmpTsrCellData.LogicSecId[iCyc] = ShortFromChar(&dataBuf[iPos]);
						iPos += 2u;
					}
				}
				else
				{
					for (iCyc = DEFAULT_ZERO; iCyc < tmpTsrCellData.LogicSecQuan; iCyc++)
					{
						tmpTsrCellData.LogicSecId[iCyc] = ShortFromChar(&dataBuf[iPos]);
						iPos += 2u;
					}
				}
				SetTsrCellDataFromAts(tmpTsrCellData);/*�߼����μ���*/

				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_FRT_CANCEL_REPLY);
				SetLastTsrCellData(pTmpTsrCellDataFromAts);
				SetAtsFirCmdRandomNo(randomNum);/*�״������¼�������*/
			}
			else if(ATS_TO_ZC_TSR_FRT_CONFIRM == appDataType)
			{
				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_FRT_CONFIRM_REPLY);
				SetAtsFirCmdRandomNo(randomNum);/*�״������¼�������*/
			}
			else if (ATS_TO_ZC_TSR_SEC_SET == appDataType)
			{
				tmpTsrCellData.TsrSpeed = dataBuf[iPos];/*����ֵ*/
				iPos++;
				tmpTsrCellData.LogicSecQuan = dataBuf[iPos];/*�߼����θ���*/
				iPos++;
				if (tmpTsrCellData.LogicSecQuan > LOGIC_MAX_NUM)
				{
					for (iCyc = DEFAULT_ZERO; iCyc < LOGIC_MAX_NUM; iCyc++)
					{
						tmpTsrCellData.LogicSecId[iCyc] = ShortFromChar(&dataBuf[iPos]);
						iPos += 2u;
					}
				}
				else
				{
					for (iCyc = DEFAULT_ZERO; iCyc < tmpTsrCellData.LogicSecQuan; iCyc++)
					{
						tmpTsrCellData.LogicSecId[iCyc] = ShortFromChar(&dataBuf[iPos]);
						iPos += 2u;
					}
				}
				SetTsrCellDataFromAts(tmpTsrCellData);/*�߼����μ���*/

				tmpAts_Crc32 = LongFromChar(&dataBuf[iPos]);/*CRC32У��ֵ*/
				iPos += 4u;
				SetAts_Crc32(tmpAts_Crc32);	

				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_SEC_SET_REPLY);
			}
			else if(ATS_TO_ZC_TSR_SEC_CANCEL == appDataType)
			{
				tmpTsrCellData.TsrSpeed = DEFAULT_ZERO;/*����ȡ����������ֵ��0*/
				
				tmpTsrCellData.LogicSecQuan = dataBuf[iPos];/*�߼����θ���*/
				iPos++;
				if (tmpTsrCellData.LogicSecQuan > LOGIC_MAX_NUM)
				{
					for (iCyc = DEFAULT_ZERO; iCyc < LOGIC_MAX_NUM; iCyc++)
					{
						tmpTsrCellData.LogicSecId[iCyc] = ShortFromChar(&dataBuf[iPos]);
						iPos += 2u;
					}
				}
				else
				{
					for (iCyc = DEFAULT_ZERO; iCyc < tmpTsrCellData.LogicSecQuan; iCyc++)
					{
						tmpTsrCellData.LogicSecId[iCyc] = ShortFromChar(&dataBuf[iPos]);
						iPos += 2u;
					}
				}
				SetTsrCellDataFromAts(tmpTsrCellData);/*�߼����μ���*/

				tmpAts_Crc32 = LongFromChar(&dataBuf[iPos]);/*CRC32У��ֵ*/
				iPos += 4u;
				SetAts_Crc32(tmpAts_Crc32);	

				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_SEC_CANCEL_REPLY);
			}
			else if(ATS_TO_ZC_TSR_SEC_CONFIRM == appDataType)
			{
				tmpAts_Crc32 = LongFromChar(&dataBuf[iPos]);/*CRC32У��ֵ*/
				iPos += 4u;
				SetAts_Crc32(tmpAts_Crc32);	

				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_SEC_CONFIRM_REPLY);
			}
			else
			{
				/*do nothing*/
			}

			/*�жϽ��������ݵĳ��Ⱥ�ʵ�ʳ����Ƿ�һ��*/
			if(iPos == dataLength)
			{
				SetResReplyToAtsFlag(RES_REPLYTO_ATS);/*�����յ�ATS�����־*/
				Retv = TSR_SUCCESS;
			}
			else
			{
				ClearRcvFromAtsData();
				Retv = TSR_ERROR;
			}
		}
		else
		{/*do nothing*/}
	}
	else
	{
		Retv = TSR_ERROR;
	}

	return Retv;
}

/*******************************************
������	��PackReplyToAtsData
�������������ATS����
����	����
���	����
����ֵ	��0��ʧ�ܣ�1���ɹ�
*******************************************/
UINT8_S PackReplyToAtsData(void)
{
	UINT8_S tempDataBuf[DATA_LEN_MAX] = {DEFAULT_ZERO};
	UINT16_S dataLen = DEFAULT_ZERO;
	UINT8_S retVal = DEFAULT_ZERO;
	CirQueueStruct* pZcToAtsQueueStru = NULL;            /*�������ݶ���*/

	dataLen = PackReplyToAtsDataFrame(tempDataBuf, DATA_LEN_MAX);
	
	if (dataLen > MSGLENPOS_IN_REPLYTOATS)
	{
		/*LogBuff("ZcToAtsData:",tempDataBuf,dataLen);*/
		/*SetSendLogData(APP_TYPE_ATS,localAtsId[0],tempDataBuf,dataLen );*/
		pZcToAtsQueueStru = GetZcToAtsDataQueueStru();
		if (SIGNED_DEFAULT_ZERO == AddQueueData(pZcToAtsQueueStru, tempDataBuf, dataLen))
		{
            retVal = TSR_SUCCESS;
		} 
		else
		{
            retVal = TSR_ERROR;
        }
	}
	else
	{
		retVal = TSR_ERROR;
	}
	return retVal;
}

/*******************************************
������	��PackResponseFrame
������������� Ӧ�������֡
����	��const UINT8_S* dataBuf, ���ݻ�����
		  const UINT16_S MaxDataLen, ���ݻ������ֽ��ܳ���
���	����
����ֵ	��>0 ���ݰ�ʵ�ʳ���
          0  ʧ��
*******************************************/
static UINT16_S PackResponseFrame(UINT8_S* dataBuf, UINT16_S MaxDataLen)
{
	UINT16_S rtnValue = DEFAULT_ZERO;
	UINT16_S iPos = DEFAULT_ZERO;
	UINT16_S msgType = DEFAULT_ZERO;
	UINT16_S reserve = DEFAULT_ZERO;
	UINT8_S replyCode = DEFAULT_ZERO;
	UINT32_S tempCrc = DEFAULT_ZERO;

	iPos += 2u;/*���������ܳ���2�ֽڣ�������д*/

	msgType = GetReplyToAtsResCmdValue();
	ShortToChar(msgType, &dataBuf[iPos]);
	iPos += 2u;
			
	ShortToChar(reserve, &dataBuf[iPos]);
	iPos += 2u;

	msgType = GetReplyToAtsResCmdValue();
	ShortToChar(msgType, &dataBuf[iPos]);
	iPos += 2u;

	replyCode = GetReplyToAtsReplyCode();
	dataBuf[iPos] = replyCode;/*��Ӧ��*/
	iPos++;

	tempCrc = GetAtsCmdCrc32();
	LongToChar(tempCrc,&dataBuf[iPos]);
	iPos += 4u;

	ShortToChar((iPos-LENGTH_FIELD_BYTES),&dataBuf[DEFAULT_ZERO]);/*��д�����ܳ���*/

	if( iPos < MaxDataLen)
	{
		rtnValue = iPos;
	}
	else
	{
		rtnValue =  TSR_ERROR;
	}

	return rtnValue;
}
/*******************************************
������	��PackTsrReportFrame
������������� �㱨TSR����֡
����	��const UINT8_S* dataBuf, ���ݻ�����
		  const UINT16_S MaxDataLen, ���ݻ������ֽ��ܳ���
���	����
����ֵ	��>0 ���ݰ�ʵ�ʳ���
          0  ʧ��
*******************************************/
static UINT16_S PackTsrReportFrame(UINT8_S* dataBuf, UINT16_S MaxDataLen)
{
	UINT16_S rtnValue = DEFAULT_ZERO;
	UINT16_S iPos = DEFAULT_ZERO;
	UINT16_S iCyc_Outer = DEFAULT_ZERO;
	UINT16_S iCyc_Inner = DEFAULT_ZERO;
	UINT16_S msgType = DEFAULT_ZERO;
	UINT16_S reserve = DEFAULT_ZERO;
	Tsr_DataStru_Set_Stru* tempTsrDataStru = NULL;

	tempTsrDataStru = GetTsrDataAdmin();

	iPos += 2u;/*���������ܳ���2�ֽڣ�������д*/
			
	msgType = GetReplyToAtsAutoCmdValue();
	ShortToChar(msgType, &dataBuf[iPos]);
	iPos += 2u;

	ShortToChar(reserve, &dataBuf[iPos]);
	iPos += 2u;

	if(ZC_TO_ATS_TSR_RESET_REPORT == msgType)
	{
		msgType = GetReplyToAtsAutoCmdValue();
		ShortToChar(msgType, &dataBuf[iPos]);
		iPos += 2u;
	}
	else if(ZC_TO_ATS_TSR_NORMAL_REPORT == msgType)
	{
		msgType = GetReplyToAtsAutoCmdValue();
		ShortToChar(msgType, &dataBuf[iPos]);
		iPos += 2u;

		dataBuf[iPos] = tempTsrDataStru->TsrQuan;
		iPos++;

		for (iCyc_Outer = DEFAULT_ZERO; iCyc_Outer < tempTsrDataStru->TsrQuan; iCyc_Outer++)
		{
			dataBuf[iPos++] = tempTsrDataStru->CellTsrData[iCyc_Outer].TsrSpeed;
			dataBuf[iPos++] = tempTsrDataStru->CellTsrData[iCyc_Outer].LogicSecQuan;

			for (iCyc_Inner = DEFAULT_ZERO; iCyc_Inner < tempTsrDataStru->CellTsrData[iCyc_Outer].LogicSecQuan; iCyc_Inner++)
			{
				ShortToChar(tempTsrDataStru->CellTsrData[iCyc_Outer].LogicSecId[iCyc_Inner],&dataBuf[iPos]);
				iPos += 2u;
			}
		}
	}
	else
	{
		/*������������*/
	}

	ShortToChar((iPos-LENGTH_FIELD_BYTES),&dataBuf[DEFAULT_ZERO]);

	if( iPos < MaxDataLen)
	{
		rtnValue = iPos;
	}
	else
	{
		rtnValue =  TSR_ERROR;
	}

	return rtnValue;
}

/*******************************************
������	��PackReplyToAtsDataFrame
������������� ���͸�ATS������֡
����	��const UINT8_S* dataBuf, ���ݻ�����
		  const UINT16_S MaxDataLen, ���ݻ������ֽ��ܳ���
���	����
����ֵ	��0: �������ʧ��
		  1: ��������ɹ�
*******************************************/
static UINT16_S PackReplyToAtsDataFrame(UINT8_S* dataBuf, UINT16_S MaxDataLen)
{
	UINT16_S rtnValue = DEFAULT_ZERO;
	UINT16_S iPos = DEFAULT_ZERO;
	UINT32_S zcType = 0x00001E00u;
	UINT32_S srcID = DEFAULT_ZERO;
	UINT32_S targetID = 0x00000301u;
	UINT16_S appLen = DEFAULT_ZERO;
	UINT8_S tmpZcId = DEFAULT_ZERO;
	UINT8_S temResBuf[DATA_LEN_MAX] = {DEFAULT_ZERO};
	UINT16_S dataResLen = DEFAULT_ZERO;
	UINT8_S temAutoRepTsrBuf[DATA_LEN_MAX] = {DEFAULT_ZERO};
	UINT16_S dataAutoRepTsrLen = DEFAULT_ZERO;
	UINT8_S *pTemAutoRepTrainposBuf = NULL;
	UINT16_S dataAutoRepTrainposLen = DEFAULT_ZERO;
	UINT8_S tmpZcResetFlag = DEFAULT_ZERO;

	if (dataBuf != NULL)
	{
		tmpZcId = (UINT8_S)GetLocalZcId();
		
		dataBuf[iPos] = 0x10;
		iPos++;
		dataBuf[iPos] = 0x10;/*�ӿ���Ϣ����*/
		iPos++;

		srcID = zcType + tmpZcId;
		LongToChar(srcID,&dataBuf[iPos]);/*���ͷ�ID*/
		iPos += 4u;

		LongToChar(targetID,&dataBuf[iPos]);/* ���շ�ID */
		iPos += 4u;

		iPos += 2u;/*����Ӧ�ò����ݳ���2�ֽڣ�������д*/

		if(RES_REPLYTO_ATS == GetResReplyToAtsFlag())
		{
			/*������ ATS��������Ϣ*/
			dataResLen = PackResponseFrame(temResBuf,DATA_LEN_MAX);
			MemoryCpy(&dataBuf[iPos],DATA_LEN_MAX,temResBuf,dataResLen);
			iPos += dataResLen;
		}
		else
		{
			/*�޻ظ�*/
			/*do nothing*/
		}

		if(AUTO_REPLYTO_ATS == GetAutoReplyToAtsFlag())
		{
			/*������ ��Ҫ�����㱨TSR*/
			dataAutoRepTsrLen = PackTsrReportFrame(temAutoRepTsrBuf,DATA_LEN_MAX);
			MemoryCpy(&dataBuf[iPos],DATA_LEN_MAX,temAutoRepTsrBuf,dataAutoRepTsrLen);
			iPos += dataAutoRepTsrLen;
		}
		else
		{
			/*�޻ظ�*/
			/*do nothing*/
		}

		pTemAutoRepTrainposBuf = GetZcToAtsDataBuff();
		dataAutoRepTrainposLen = GetZcToAtsIdDataBufLen();
		tmpZcResetFlag = GetZcWorkState();
		/*ZC��ʼ�ϵ�����²���ATS�㱨�г�λ��*/
		if((ZC_RESET_STATUS_FLAG_UNSET == tmpZcResetFlag) && (dataAutoRepTrainposLen > DEFAULT_ZERO))
		{
			/*������ ��Ҫ�㱨�г�λ��*/
			MemoryCpy(&dataBuf[iPos],DATA_LEN_MAX,pTemAutoRepTrainposBuf,dataAutoRepTrainposLen);
			iPos += dataAutoRepTrainposLen;
		}
		else
		{
			/*�޻ظ�*/
			/*do nothing*/
		}

		appLen = iPos-APPLENPOS_IN_REPLYTOATS-LENGTH_FIELD_BYTES;
	    ShortToChar(appLen,&dataBuf[APPLENPOS_IN_REPLYTOATS] );/*��дӦ�ò����ݳ���*/

		if (RES_REPLYTO_ATS == GetResReplyToAtsFlag())
		{
			/*���ATS�������ݽṹ��*/
			ClearRcvFromAtsData();
			SetResReplyToAtsFlag(ANTI_RES_REPLYTO_ATS);/*���Ӧ���־*/
		}
		if (AUTO_REPLYTO_ATS == GetAutoReplyToAtsFlag())/*�Ƿ���Ҫ�����㱨*/
		{
			SetAutoReplyToAtsFlag(DEFAULT_ZERO);/*��������ظ���־*/
		}

		if( iPos < MaxDataLen)
		{
			rtnValue = iPos;
		}
		else
		{
			rtnValue =  TSR_ERROR;
		}
	}
	else
	{
		/*LogMsgString(1,"PackReplyToAtsDataFrame error\n");*/
		rtnValue = TSR_ERROR;
	}

	return rtnValue;
}

/*******************************************
������	��CalcCrc
��������������ATS���͹��������CRCֵ
����	����
���	����
����ֵ	�������CRCֵ
*******************************************/
UINT32_S CalcCrc(void)
{
	UINT8_S tempCrc[DATA_LEN_MAX] = {DEFAULT_ZERO};
	UINT16_S tempCrcLength = DEFAULT_ZERO;
	Tsr_DataStru_Cell_Stru* atsToZcTsrDataStru = NULL;
	UINT8_S ii = DEFAULT_ZERO;
	UINT32_S returnCrc = DEFAULT_ZERO;
	UINT16_S tmpAtsCmdType = DEFAULT_ZERO;
	UINT16_S tmpCurRandomNo = DEFAULT_ZERO;

	MemorySet(&tempCrc[0],DATA_LEN_MAX, DEFAULT_ZERO, DATA_LEN_MAX);
	tempCrcLength = DEFAULT_ZERO;

	atsToZcTsrDataStru = GetTsrCellDataFromAts();

	tmpAtsCmdType = GetAtsCmdType();
	ShortToChar(tmpAtsCmdType,&tempCrc[tempCrcLength]);
    tempCrcLength += 2;
	tmpCurRandomNo = GetCurRandomNo();
	ShortToChar(tmpCurRandomNo,&tempCrc[tempCrcLength]);
    tempCrcLength += 2u;
	if(ATS_TO_ZC_TSR_FRT_SET==tmpAtsCmdType || ATS_TO_ZC_TSR_SEC_SET==tmpAtsCmdType)/*�״����� �� ��������*/
	{
		tempCrc[tempCrcLength] = atsToZcTsrDataStru->TsrSpeed;
		tempCrcLength++;
		tempCrc[tempCrcLength] = atsToZcTsrDataStru->LogicSecQuan;
		tempCrcLength++;
		for (ii = DEFAULT_ZERO; ii < atsToZcTsrDataStru->LogicSecQuan; ii++)
		{
			ShortToChar(atsToZcTsrDataStru->LogicSecId[ii],&tempCrc[tempCrcLength]);
			tempCrcLength = tempCrcLength + 2u;
		}
	}
	else if(ATS_TO_ZC_TSR_FRT_CANCEL==tmpAtsCmdType || ATS_TO_ZC_TSR_SEC_CANCEL==tmpAtsCmdType)/*�״�ȡ�� �� ����ȡ��*/
	{
		tempCrc[tempCrcLength] = atsToZcTsrDataStru->LogicSecQuan;
		tempCrcLength++;
		for (ii = DEFAULT_ZERO; ii < atsToZcTsrDataStru->LogicSecQuan; ii++)
		{
			ShortToChar(atsToZcTsrDataStru->LogicSecId[ii],&tempCrc[tempCrcLength]);
			tempCrcLength = tempCrcLength + 2u;
		}
	}
	else
	{
		/*do nothing*/
	}

	returnCrc = Crc32(tempCrc,tempCrcLength);

	return returnCrc;
}