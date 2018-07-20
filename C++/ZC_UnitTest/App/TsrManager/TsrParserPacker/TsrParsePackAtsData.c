/*******************************************
文件名	：TsrParsePackAtsData.c
作者	：董欣
创建时间：2016-10
描述	：ATS数据解析组包文件
备注	：无
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

static Tsr_DataStru_FromAts g_RcvFromAtsData;/*ATS发来的数据信息结构体*/
static Tsr_DataStru_ToATS g_ReplyToAtsData;/*回复ATS的数据信息结构体*/
static UINT8_S g_LastAtsCmdType = DEFAULT_ZERO;/*ATS最近一次命令类型*/
static UINT16_S g_TimeBetweenFsAndSs = UINT16_MAX;/*首次二次计时时间*/
static UINT32_S g_AtsCmdCrc32 = DEFAULT_ZERO; /*用于存放计算ATS命令的CRC32*/
static Tsr_DataStru_Cell_Stru g_LastTsrCellData;/*缓存首次设置或取消的临时限速*/
static UINT16_S g_AtsFirCmdRandomNo = DEFAULT_ZERO;/*ATS首次命令的随机码*/

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
函数名	：GetAtsCmdType
功能描述：获取ATS发送过来的命令类型
输入	：无
输出	：无
返回值	：ATS发送过来的命令类型
*******************************************/
UINT16_S GetAtsCmdType(void)
{
	return g_RcvFromAtsData.AtsCmdType;
}

/*******************************************
函数名	：SetAtsCmdType
功能描述：设置ATS发送过来的命令类型值
输入	：UINT16_S atsCmdType,ATS发送过来的命令类型值
输出	：无
返回值	：无
*******************************************/
static void SetAtsCmdType(UINT16_S atsCmdType)
{
	g_RcvFromAtsData.AtsCmdType = atsCmdType;
}

/*******************************************
函数名	：GetAtsID
功能描述：获取ATS发送过来的AtsID
输入	：无
输出	：无
返回值	：ATS发送过来的AtsID
*******************************************/
static UINT32_S GetAtsID(void)
{
	return g_RcvFromAtsData.AtsID;
}

/*******************************************
函数名	：SetAtsID
功能描述：设置ATS发送过来的AtsID
输入	：UINT32_S atsID,ATS发送过来的AtsID值
输出	：无
返回值	：无
*******************************************/
static void SetAtsID(UINT32_S atsID)
{
	g_RcvFromAtsData.AtsID = atsID;
}

/*******************************************
函数名	：GetTargetID
功能描述：获取ATS发送过来的TargetID
输入	：无
输出	：无
返回值	：ATS发送过来的TargetID
*******************************************/
static UINT32_S GetTargetID(void)
{
	return g_RcvFromAtsData.TargetID;
}

/*******************************************
函数名	：SetTargetID
功能描述：设置ATS发送过来的TargetID
输入	：UINT32_S targetID,ATS发送过来的TargetID值
输出	：无
返回值	：无
*******************************************/
static void SetTargetID(UINT32_S targetID)
{
	g_RcvFromAtsData.TargetID = targetID;
}

/*******************************************
函数名	：GetCurRandomNo
功能描述：获取ATS发送过来的随机数
输入	：无
输出	：无
返回值	：ATS发送过来的随机数
*******************************************/
static UINT16_S GetCurRandomNo(void)
{
	return g_RcvFromAtsData.RandomNo;
}

/*******************************************
函数名	：SetCurRandomNo
功能描述：设置ATS发送过来的随机数
输入	：UINT16_S randomNo,ATS发送过来的随机数
输出	：无
返回值	：无
*******************************************/
static void SetCurRandomNo(UINT16_S randomNo)
{
	g_RcvFromAtsData.RandomNo = randomNo;
}

/*******************************************
函数名	：GetAts_Crc32
功能描述：获取ATS发送过来的Ats_Crc32
输入	：无
输出	：无
返回值	：ATS发送过来的Ats_Crc32
*******************************************/
static UINT32_S GetAts_Crc32(void)
{
	return g_RcvFromAtsData.Ats_Crc32;
}

/*******************************************
函数名	：SetAts_Crc32
功能描述：设置ATS发送过来的Ats_Crc32
输入	：UINT32_S ats_Crc32,ATS发送过来的Ats_Crc32值
输出	：无
返回值	：无
*******************************************/
static void SetAts_Crc32(UINT32_S ats_Crc32)
{
	g_RcvFromAtsData.Ats_Crc32 = ats_Crc32;
}

/*******************************************
函数名	：GetTsrCellDataFromAts
功能描述：获取ATS发送的临时限速信息
输入	：无
输出	：无
返回值	：ATS发送的临时限速信息
*******************************************/
Tsr_DataStru_Cell_Stru* GetTsrCellDataFromAts(void)
{
	return &g_RcvFromAtsData.TsrCellData;
}

/*******************************************
函数名	：SetTsrCellDataFromAts
功能描述：设置ATS发送过来的临时限速信息
输入	：Tsr_DataStru_Cell_Stru tsrCellData,单个临时限速信息
输出	：无
返回值	：无
*******************************************/
static void SetTsrCellDataFromAts(Tsr_DataStru_Cell_Stru tsrCellData)
{
	Pri_SetTsrCell(&(g_RcvFromAtsData.TsrCellData), tsrCellData);
}

/*******************************************
函数名	：GetRcvFromAtsData
功能描述：获取ATS发来的数据信息结构体
输入	：无
输出	：无
返回值	：ATS发来的数据信息结构体
*******************************************/
Tsr_DataStru_FromAts* GetRcvFromAtsData(void)
{
	return &g_RcvFromAtsData;
}

/*******************************************
函数名	：ClearRcvFromAtsData
功能描述：清除ATS发来的数据信息结构体
输入	：无
输出	：无
返回值	：无
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
函数名	：SetLastTsrCellData
功能描述：设置首次操作的单个临时限速信息
输入	：首次操作的单个临时限速信息
输出	：无
返回值	：无
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
函数名	：GetLastTsrCellData
功能描述：获取首次操作的单个临时限速信息
输入	：无
输出	：无
返回值	：首次操作的单个临时限速信息
*******************************************/
Tsr_DataStru_Cell_Stru* GetLastTsrCellData(void)
{
	return &g_LastTsrCellData;
}
/*******************************************
函数名	：ClearLastTsrCellData
功能描述：清空首次操作的单个临时限速信息
输入	：无
输出	：无
返回值	：无
*******************************************/
void ClearLastTsrCellData(void)
{
	Pri_ClearTsrCell(&g_LastTsrCellData);
}

/*******************************************
函数名	：GetAtsFirCmdRandomNo
功能描述：获取ATS首次命令的随机码
输入	：无
输出	：无
返回值	：ATS首次命令的随机码
*******************************************/
static UINT16_S GetAtsFirCmdRandomNo(void)
{
	return g_AtsFirCmdRandomNo;
}

/*******************************************
函数名	：SetAtsFirCmdRandomNo
功能描述：设置ATS首次命令的随机码
输入	：UINT16_S randomNo,ATS首次命令的随机码
输出	：无
返回值	：无
*******************************************/
static void SetAtsFirCmdRandomNo(UINT16_S randomNo)
{
	g_AtsFirCmdRandomNo = randomNo;
}

/*******************************************
函数名	：GetAtsCmdCrc32
功能描述：获取g_AtsCmdCrc32
输入	：无
输出	：无
返回值	：AtsCmdCrc32命令的CRC32
*******************************************/
static UINT32_S GetAtsCmdCrc32(void)
{
	return g_AtsCmdCrc32;
}

/*******************************************
函数名	：SetAtsCmdCrc32
功能描述：设置g_AtsCmdCrc32
输入	：UINT32_S crc32
输出	：无
返回值	：无
*******************************************/
void SetAtsCmdCrc32(UINT32_S crc32)
{
	g_AtsCmdCrc32 = crc32;
}

/*******************************************
函数名	：GetAtsSendTsrFsAndSsTime
功能描述：获取首次二次计时时间
输入	：无
输出	：无
返回值	：g_TimeBetweenFsAndSs首次二次计时时间
*******************************************/
UINT16_S GetAtsSendTsrFsAndSsTime(void)
{
	return g_TimeBetweenFsAndSs;
}

/*******************************************
函数名	：AddAtsSendTsrFsAndSsTime
功能描述：累加首次二次计时时间
输入	：无
输出	：无
返回值	：无
*******************************************/
void AddAtsSendTsrFsAndSsTime(void)
{
	g_TimeBetweenFsAndSs = g_TimeBetweenFsAndSs+ 1u;
}

/*******************************************
函数名	：SetAtsSendTsrFsAndSsTime
功能描述：设置首次二次计时时间
输入	：fsAndSsTime首次二次计时时间
输出	：无
返回值	：无
*******************************************/
void SetAtsSendTsrFsAndSsTime(UINT16_S fsAndSsTime)
{
	g_TimeBetweenFsAndSs = fsAndSsTime;
}

/*******************************************
函数名	：SetLastAtsCmdType
功能描述：设置ATS最近一次命令类型
输入	：lastCmdTypeATS最近一次命令类型
输出	：无
返回值	：无
*******************************************/
void SetLastAtsCmdType(UINT8_S lastCmdType)
{
	g_LastAtsCmdType = lastCmdType;
}

/*******************************************
函数名	：GetLastAtsCmdType
功能描述：获取ATS最近一次命令类型
输入	：无
输出	：无
返回值	：LastAtsCmdTypeATS最近一次命令类型
*******************************************/
static UINT8_S GetLastAtsCmdType(void)
{
	return g_LastAtsCmdType;
}

/*******************************************
函数名	：GetReplyToAtsResCmdValue
功能描述：获取 应答回复ATS的命令信息值
          包括：首次上电确认回复/二次上电确认回复/首次设置TSR回复/二次设置TSR回复/首次取消TSR回复/二次取消TSR回复/
输入	：无
输出	：无
返回值	：回复ATS的应答命令信息值
*******************************************/
static UINT16_S GetReplyToAtsResCmdValue(void)
{
	return g_ReplyToAtsData.msgType_res;
}

/*******************************************
函数名	：SetReplyToAtsResCmdValue
功能描述：设置 应答回复ATS的命令信息值
          包括：首次上电确认回复/二次上电确认回复/首次设置TSR回复/二次设置TSR回复/首次取消TSR回复/二次取消TSR回复/
输入	：回复ATS的命令信息值
输出	：无
返回值	：无
*******************************************/
static void SetReplyToAtsResCmdValue(UINT8_S replyToAtsCmd)
{
	g_ReplyToAtsData.msgType_res = replyToAtsCmd;
}

/*******************************************
函数名	：GetReplyToAtsAutoCmdValue
功能描述：获取 主动回复ATS的应答命令信息值
          包括：重启汇报/正常汇报
输入	：无
输出	：无
返回值	：回复ATS的应答命令信息值
*******************************************/
static UINT16_S GetReplyToAtsAutoCmdValue(void)
{
	return g_ReplyToAtsData.msgType_auto;
}

/*******************************************
函数名	：SetReplyToAtsAutoCmdValue
功能描述：设置 主动回复ATS的命令信息值
          包括：重启汇报/正常汇报
输入	：回复ATS的命令信息值
输出	：无
返回值	：无
*******************************************/
void SetReplyToAtsAutoCmdValue(UINT8_S replyToAtsCmd)
{
	g_ReplyToAtsData.msgType_auto = replyToAtsCmd;
}

/*******************************************
函数名	：GetReplyToAtsReplyCode
功能描述：获取 回复ATS的回应码
输入	：无
输出	：无
返回值	：回复ATS的回应码
*******************************************/
static UINT8_S GetReplyToAtsReplyCode(void)
{
	return g_ReplyToAtsData.replyCode;
}
/*******************************************
函数名	：SetReplyToAtsReplyCode
功能描述：设置 回复ATS的回应码
输入	：回复ATS的回应码
输出	：无
返回值	：无
*******************************************/
static void SetReplyToAtsReplyCode(UINT8_S replyCode)
{
	g_ReplyToAtsData.replyCode = replyCode;
}

/*******************************************
函数名	：WriteReplyToAtsData
功能描述：写临时限速信息到 发送给ZC的数据结构
输入	：无
输出	：无
返回值	：无
*******************************************/
void WriteReplyToAtsData(const Tsr_DataStru_Set_Stru* tsrDataStru)
{
	if(NULL != tsrDataStru)
		Pri_SetTsrSet(&g_ReplyToAtsData.TsrSetData, *tsrDataStru);
}

/*******************************************
函数名	：GetReplyToAtsTsrMsgStru
功能描述：获取 向ATS发送的临时限速信息
输入	：无
输出	：无
返回值	：向ATS发送的临时限速信息
*******************************************/
static Tsr_DataStru_Set_Stru* GetReplyToAtsTsrMsgStru(void)
{
	return &g_ReplyToAtsData.TsrSetData;
}

/*******************************************
函数名  : GetReplyToAtsDataStru
功能描述：向ATS发送的数据信息结构体
输入    ：无
输出    ：无
返回值	：g_ReplyToAtsData  ATS发送来的数据信息结构体
*******************************************/
Tsr_DataStru_ToATS* GetReplyToAtsDataStru(void)
{
	return &g_ReplyToAtsData;
}

/*******************************************
函数名	：ClearReplyToAtsData
功能描述：清空 向ATS发送的数据信息结构体
输入	：无
输出	：无
返回值	：无
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
函数名	：CheckRcvFromAtsCmdType
功能描述：检查ATS发送来的命令信息
输入	：无
输出	：无
返回值	：0失败，1成功
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
			rtnValue = TSR_ERROR;/*错误发送了首次设置命令*/
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
			rtnValue = TSR_ERROR;/*错误发送了首次取消命令*/
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
				rtnValue = TSR_ERROR;/*错误发送了首次确认命令*/
			}	
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_FIR_CONFIRM_CMD_INCORRECT_YETCONFIRMED);/*系统状态已转为正常工作后又发送了首次上电确认命令*/
			/*SetEventLogList(DMS_ATS_CHECK_FS_CONFIRM_CMD_AA_ERROR,LOG_EVENT_ERROR,1u,GetZcWorkState());*/
			rtnValue = TSR_ERROR;/*错误发送了首次确认命令*/
		}			
	}
	else if (ATS_TO_ZC_TSR_SEC_SET == GetAtsCmdType())
	{
		if (LAST_ATS_FR_SET_CMD == GetLastAtsCmdType())
		{
			if (GetAtsSendTsrFsAndSsTime() > GetPeriodsBetweenFsAndSs())/*超出等待时间*/
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
			if (GetAtsSendTsrFsAndSsTime() > GetPeriodsBetweenFsAndSs())/*超出等待时间*/
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
			if (GetAtsSendTsrFsAndSsTime() > GetPeriodsBetweenFsAndSs())/*超出等待时间*/
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
函数名	：CheckRcvFromAtsTsrSpeed
功能描述：检查ATS发送来的临时限速速度信息
输入	：无
输出	：无
返回值	：0失败，1成功
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
			SetReplyToAtsReplyCode(TSR_FIR_SET_TSRSPEEDVALUE_OVERFLOW);/*速度无效*/
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
				SetReplyToAtsReplyCode(TSR_UNKNOWN);/*速度无效*/
				/*SetEventLogList(DMS_ATS_CHECK_FS_SET_SPEED_CHECK_ERROR,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->TsrSpeed);*/
				rtnValue = TSR_ERROR;
			}
			else if(1u == speedValue)
			{
				SetReplyToAtsReplyCode(TSR_OK);/*速度有效*/
				rtnValue = TSR_SUCCESS;
			}
			else
			{
			
				/*LogMsgString(1, "CheckRcvFromAtsTsrSpeed some beyond singleTsrSpeed\n");*/
				SetReplyToAtsReplyCode(TSR_FIR_SET_TSRSPEEDVALUE_GREATERTHAN_STATICDEFAULTVALUE);/*设置的临时限速数值高于某一个逻辑区段的线路设计最高限速值,速度无效*/
				/*SetEventLogList(DMS_ATS_CHECK_FS_SET_SPEED_CHECK_LIMIT,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->TsrSpeed);*/
				rtnValue = TSR_ERROR;
			}						
		}
	}
	else if(ATS_TO_ZC_TSR_SEC_SET == GetAtsCmdType())
	{
		/*二次设置的临时限速速度值与首次设置的不一致，即速度无效*/
		if ((tempSingleTsrDataStru->TsrSpeed == DEFAULT_ZERO)||(tempSingleTsrDataStru->TsrSpeed > GetTsrMaxSpeed()) || (tempSingleTsrDataStru->TsrSpeed != lastSingleTsrDataStru->TsrSpeed))
		{
			/*LogMsgString(1, "CheckRcvFromAtsTsrSpeed Invalid\n");*/
			/*SetEventLogList(DMS_ATS_CHECK_FS_SS_SET_SPEED_DIFFER,LOG_EVENT_ERROR,1u,tempSingleTsrDataStru->TsrSpeed);*/
			SetReplyToAtsReplyCode(TSR_SEC_SET_TSRSPEEDVALUE_DIFFERFROMFIR);/*速度无效*/
			rtnValue = TSR_ERROR;
		}
		else
		{
			SetReplyToAtsReplyCode(TSR_OK);/*速度有效*/
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
函数名	：CheckRcvFromAtsTsrNum
功能描述：检查ATS发送来的临时限速数目
输入	：无
输出	：无
返回值	：0失败，1成功
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
			SetReplyToAtsReplyCode(TSR_TSRQUANTITY_OVERFLOW);/*TSR数量无效*/

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
			SetReplyToAtsReplyCode(TSR_FIR_CANCEL_CMD_INCORRECT_ZCHASNOTSR);/*TSR数量无效*/

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
函数名	：TSR_CheckRandomNo
功能描述：检查二次命令与首次命令的随机码是否一致
输入	：无
输出	：无
返回值	：0失败，1成功
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
		tmpAtsFirCmdRandomNo = GetAtsFirCmdRandomNo();/*首次命令随机码*/
		tmpCurRandomNo = GetCurRandomNo();/*二次命令随机码*/
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
函数名	：CheckRcvFromAtsTsrLogicCount
功能描述：检查ATS发送来的临时限速逻辑区段数量信息
输入	：无
输出	：无
返回值	：0失败，1成功
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
函数名	：CheckRcvFromAtsTsrLogicIds
功能描述：检查ATS发送来的临时限速逻辑区段id
输入	：无
输出	：无
返回值	：0失败，1成功
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
	UINT8_S rtnValue = TSR_SUCCESS;/*函数返回值*/
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
			SetReplyToAtsReplyCode(TSR_UNKNOWN);/*增加逻辑区段ID无效的宏*/
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
				for (iCyc = DEFAULT_ZERO; iCyc < tempTsrDataStru->TsrQuan; iCyc++)/*标注线路逻辑区段ID*/
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
			else if(1u == checkTemp)/*待区分 回应码 40u或是41u*/
			{
				SetReplyToAtsReplyCode(TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGSECATBOTHSWITCHPOSITON_A);/*待补充回应码*/
				rtnValue = TSR_ERROR;
			}
			else
			{
		
				/*LogMsgString(1, "CheckRcvFromAtsTsrLogicIds logic error\n");*/
				/*SetEventLogList(DMS_ATS_CHECK_FS_SET_TSR_FR_SECTION_COLLISION,LOG_EVENT_ERROR,1u,checkTemp);*/
				SetReplyToAtsReplyCode(TSR_UNKNOWN);/*待补充回应码*/
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
					tempTsrFindFlag = 1u;/*是否找到要取消的临时限速标志，默认为1，找到，0为没有找到*/
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
								/*不处理*/
							}
						}
					}
					else
					{
						tempTsrFindFlag = DEFAULT_ZERO;/*逻辑区段个数不等*/
					}
					if (1u == tempTsrFindFlag)
					{
						break;
					}
					else
					{
						/*继续循环*/
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
			else if(1u == checkTemp)/*待区分 回应码 40u或是41u*/
			{
				SetReplyToAtsReplyCode(TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGSECATBOTHSWITCHPOSITON_A);/*待补充回应码*/
				rtnValue = TSR_ERROR;
			}
			else
			{
		
				/*LogMsgString(1, "CheckRcvFromAtsTsrLogicIds logic error\n");*/
				/*SetEventLogList(DMS_ATS_CHECK_FS_SET_CANCEL_FR_SECTION_COLLISION,LOG_EVENT_ERROR,1u,checkTemp);*/
				SetReplyToAtsReplyCode(TSR_UNKNOWN);/*待补充回应码*/
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
				
					/*继续*/
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
函数名	：CheckRcvFromAtsCrc
功能描述：校验ATS发送来的CRC校验信息
输入	：无
输出	：无
返回值	：0失败，1成功
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
		/*不处理*/
		rtnValue = TSR_SUCCESS;
	}
	return rtnValue;
}




/*******************************************
函数名	：CheckAtsInputData
功能描述：检查ATS输入数据的合法性
输入	：无
输出	：无
返回值	：0失败，1成功
*******************************************/
UINT8_S CheckAtsInputData(void)
{
	UINT8_S rtnVlue = DEFAULT_ZERO;/*函数返回值*/

	if (TSR_SUCCESS == TSR_CheckRandomNo())/*检查二次命令的随机码与首次命令是否一致*/
	{
		if (TSR_SUCCESS == CheckRcvFromAtsCmdType())/*检查ATS发送来的命令信息是否正确*/
		{
			if (TSR_SUCCESS == CheckRcvFromAtsTsrNum()) /*检查ATS发送来的临时限速数目是否正确*/
			{
				if (TSR_SUCCESS == CheckRcvFromAtsTsrLogicCount()) /*检查ATS发送来的临时限速逻辑段ID数目是否正确*/
				{
					if (TSR_SUCCESS == CheckRcvFromAtsTsrLogicIds()) /*检查ATS发送来的临时限速逻辑段ID是否正确*/
					{
						if (TSR_SUCCESS == CheckRcvFromAtsTsrSpeed())/*检查ATS发送来的临时限速速度是否正确*/
						{
							if (TSR_SUCCESS == CheckRcvFromAtsCrc()) /*检查ATS发送来的命令信息CRC是否正确*/
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
函数名	：ParseRcvFromAtsDataFrame
功能描述：解析ATS发送来的数据帧
输入	：const UINT8_S* dataBuf, 数据缓冲区
		  const UINT16_S dataLength, 数据长度
输出	：无
返回值	：0: 数据解析失败
		  1: 数据解析成功
*******************************************/
UINT8_S ParseRcvFromAtsDataFrame(const UINT8_S* dataBuf, const UINT16_S dataLength)
{
	UINT8_S Retv = TSR_SUCCESS;
	UINT16_S iPos = DEFAULT_ZERO;/*缓冲区偏移指针*/
	UINT16_S iCyc = DEFAULT_ZERO;/*循环控制变量*/
	UINT16_S interftype = DEFAULT_ZERO;
	UINT32_S srcID = DEFAULT_ZERO;
	UINT32_S dstID = DEFAULT_ZERO;
	UINT16_S appAllDataLen = DEFAULT_ZERO;         /*应用层数据总长度*/
	UINT16_S appDataLen = DEFAULT_ZERO;            /*应用层报文总长度*/
	UINT16_S appDataType = DEFAULT_ZERO;           /*应用层报文类型*/
	UINT16_S reserve = DEFAULT_ZERO;              /*预留*/
	UINT16_S randomNum = DEFAULT_ZERO;              /*随机数*/
	Tsr_DataStru_Cell_Stru tmpTsrCellData;
	UINT32_S tmpAts_Crc32 = DEFAULT_ZERO;
	Tsr_DataStru_Cell_Stru* pTmpTsrCellDataFromAts = NULL;

	Pri_ClearTsrCell(&tmpTsrCellData);
	if ((dataBuf != NULL) && (dataLength > DEFAULT_ZERO))
	{
		interftype = ShortFromChar(&dataBuf[iPos]);
		iPos += 2u;
		if (0x1010u != interftype)/*信息内容合法性检查等*/
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
			SetAtsID(srcID);/*发送方标识*/
			SetTargetID(dstID);/*接收方标识*/
			appAllDataLen = ShortFromChar(&dataBuf[iPos]);/*应用层数据长度*/
			iPos += 2u;
	        appDataLen = ShortFromChar(&dataBuf[iPos]);/*报文总长度*/
			iPos += 2u;
	        appDataType = ShortFromChar(&dataBuf[iPos]);/*报文类型*/
			iPos += 2u;
	        reserve = ShortFromChar(&dataBuf[iPos]);/*预留*/
			iPos += 2u;

			SetAtsCmdType(ShortFromChar(&dataBuf[iPos]));/*报文类型*/
			iPos += 2u;
			randomNum = ShortFromChar(&dataBuf[iPos]);/*随机数*/
			iPos += 2u;
			SetCurRandomNo(randomNum);

			appDataType = GetAtsCmdType();
			pTmpTsrCellDataFromAts = GetTsrCellDataFromAts();
			if ( ATS_TO_ZC_TSR_FRT_SET == appDataType)
			{
				tmpTsrCellData.TsrSpeed = dataBuf[iPos];/*限速值*/
				iPos++;
				tmpTsrCellData.LogicSecQuan = dataBuf[iPos];/*逻辑区段个数*/
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
				SetTsrCellDataFromAts(tmpTsrCellData);/*逻辑区段集合*/

				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_FRT_SET_REPLY);
				SetLastTsrCellData(pTmpTsrCellDataFromAts);
				SetAtsFirCmdRandomNo(randomNum);/*首次命令记录下随机码*/
			}
			else if(ATS_TO_ZC_TSR_FRT_CANCEL == appDataType)
			{
				tmpTsrCellData.TsrSpeed = DEFAULT_ZERO;/*对于取消限速限速值置0*/
				
				tmpTsrCellData.LogicSecQuan = dataBuf[iPos];/*逻辑区段个数*/
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
				SetTsrCellDataFromAts(tmpTsrCellData);/*逻辑区段集合*/

				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_FRT_CANCEL_REPLY);
				SetLastTsrCellData(pTmpTsrCellDataFromAts);
				SetAtsFirCmdRandomNo(randomNum);/*首次命令记录下随机码*/
			}
			else if(ATS_TO_ZC_TSR_FRT_CONFIRM == appDataType)
			{
				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_FRT_CONFIRM_REPLY);
				SetAtsFirCmdRandomNo(randomNum);/*首次命令记录下随机码*/
			}
			else if (ATS_TO_ZC_TSR_SEC_SET == appDataType)
			{
				tmpTsrCellData.TsrSpeed = dataBuf[iPos];/*限速值*/
				iPos++;
				tmpTsrCellData.LogicSecQuan = dataBuf[iPos];/*逻辑区段个数*/
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
				SetTsrCellDataFromAts(tmpTsrCellData);/*逻辑区段集合*/

				tmpAts_Crc32 = LongFromChar(&dataBuf[iPos]);/*CRC32校验值*/
				iPos += 4u;
				SetAts_Crc32(tmpAts_Crc32);	

				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_SEC_SET_REPLY);
			}
			else if(ATS_TO_ZC_TSR_SEC_CANCEL == appDataType)
			{
				tmpTsrCellData.TsrSpeed = DEFAULT_ZERO;/*对于取消限速限速值置0*/
				
				tmpTsrCellData.LogicSecQuan = dataBuf[iPos];/*逻辑区段个数*/
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
				SetTsrCellDataFromAts(tmpTsrCellData);/*逻辑区段集合*/

				tmpAts_Crc32 = LongFromChar(&dataBuf[iPos]);/*CRC32校验值*/
				iPos += 4u;
				SetAts_Crc32(tmpAts_Crc32);	

				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_SEC_CANCEL_REPLY);
			}
			else if(ATS_TO_ZC_TSR_SEC_CONFIRM == appDataType)
			{
				tmpAts_Crc32 = LongFromChar(&dataBuf[iPos]);/*CRC32校验值*/
				iPos += 4u;
				SetAts_Crc32(tmpAts_Crc32);	

				SetReplyToAtsResCmdValue(ZC_TO_ATS_TSR_SEC_CONFIRM_REPLY);
			}
			else
			{
				/*do nothing*/
			}

			/*判断解析出数据的长度和实际长度是否一致*/
			if(iPos == dataLength)
			{
				SetResReplyToAtsFlag(RES_REPLYTO_ATS);/*更新收到ATS命令标志*/
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
函数名	：PackReplyToAtsData
功能描述：组包ATS数据
输入	：无
输出	：无
返回值	：0：失败；1：成功
*******************************************/
UINT8_S PackReplyToAtsData(void)
{
	UINT8_S tempDataBuf[DATA_LEN_MAX] = {DEFAULT_ZERO};
	UINT16_S dataLen = DEFAULT_ZERO;
	UINT8_S retVal = DEFAULT_ZERO;
	CirQueueStruct* pZcToAtsQueueStru = NULL;            /*接收数据队列*/

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
函数名	：PackResponseFrame
功能描述：组包 应答包数据帧
输入	：const UINT8_S* dataBuf, 数据缓冲区
		  const UINT16_S MaxDataLen, 数据缓冲区字节总长度
输出	：无
返回值	：>0 数据包实际长度
          0  失败
*******************************************/
static UINT16_S PackResponseFrame(UINT8_S* dataBuf, UINT16_S MaxDataLen)
{
	UINT16_S rtnValue = DEFAULT_ZERO;
	UINT16_S iPos = DEFAULT_ZERO;
	UINT16_S msgType = DEFAULT_ZERO;
	UINT16_S reserve = DEFAULT_ZERO;
	UINT8_S replyCode = DEFAULT_ZERO;
	UINT32_S tempCrc = DEFAULT_ZERO;

	iPos += 2u;/*跳过报文总长度2字节，后面填写*/

	msgType = GetReplyToAtsResCmdValue();
	ShortToChar(msgType, &dataBuf[iPos]);
	iPos += 2u;
			
	ShortToChar(reserve, &dataBuf[iPos]);
	iPos += 2u;

	msgType = GetReplyToAtsResCmdValue();
	ShortToChar(msgType, &dataBuf[iPos]);
	iPos += 2u;

	replyCode = GetReplyToAtsReplyCode();
	dataBuf[iPos] = replyCode;/*回应码*/
	iPos++;

	tempCrc = GetAtsCmdCrc32();
	LongToChar(tempCrc,&dataBuf[iPos]);
	iPos += 4u;

	ShortToChar((iPos-LENGTH_FIELD_BYTES),&dataBuf[DEFAULT_ZERO]);/*填写报文总长度*/

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
函数名	：PackTsrReportFrame
功能描述：组包 汇报TSR数据帧
输入	：const UINT8_S* dataBuf, 数据缓冲区
		  const UINT16_S MaxDataLen, 数据缓冲区字节总长度
输出	：无
返回值	：>0 数据包实际长度
          0  失败
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

	iPos += 2u;/*跳过报文总长度2字节，后面填写*/
			
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
		/*其他，不处理*/
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
函数名	：PackReplyToAtsDataFrame
功能描述：组包 发送给ATS的数据帧
输入	：const UINT8_S* dataBuf, 数据缓冲区
		  const UINT16_S MaxDataLen, 数据缓冲区字节总长度
输出	：无
返回值	：0: 数据组包失败
		  1: 数据组包成功
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
		dataBuf[iPos] = 0x10;/*接口信息类型*/
		iPos++;

		srcID = zcType + tmpZcId;
		LongToChar(srcID,&dataBuf[iPos]);/*发送方ID*/
		iPos += 4u;

		LongToChar(targetID,&dataBuf[iPos]);/* 接收方ID */
		iPos += 4u;

		iPos += 2u;/*跳过应用层数据长度2字节，后面填写*/

		if(RES_REPLYTO_ATS == GetResReplyToAtsFlag())
		{
			/*本周期 ATS有命令信息*/
			dataResLen = PackResponseFrame(temResBuf,DATA_LEN_MAX);
			MemoryCpy(&dataBuf[iPos],DATA_LEN_MAX,temResBuf,dataResLen);
			iPos += dataResLen;
		}
		else
		{
			/*无回复*/
			/*do nothing*/
		}

		if(AUTO_REPLYTO_ATS == GetAutoReplyToAtsFlag())
		{
			/*本周期 需要主动汇报TSR*/
			dataAutoRepTsrLen = PackTsrReportFrame(temAutoRepTsrBuf,DATA_LEN_MAX);
			MemoryCpy(&dataBuf[iPos],DATA_LEN_MAX,temAutoRepTsrBuf,dataAutoRepTsrLen);
			iPos += dataAutoRepTsrLen;
		}
		else
		{
			/*无回复*/
			/*do nothing*/
		}

		pTemAutoRepTrainposBuf = GetZcToAtsDataBuff();
		dataAutoRepTrainposLen = GetZcToAtsIdDataBufLen();
		tmpZcResetFlag = GetZcWorkState();
		/*ZC初始上电情况下不向ATS汇报列车位置*/
		if((ZC_RESET_STATUS_FLAG_UNSET == tmpZcResetFlag) && (dataAutoRepTrainposLen > DEFAULT_ZERO))
		{
			/*本周期 需要汇报列车位置*/
			MemoryCpy(&dataBuf[iPos],DATA_LEN_MAX,pTemAutoRepTrainposBuf,dataAutoRepTrainposLen);
			iPos += dataAutoRepTrainposLen;
		}
		else
		{
			/*无回复*/
			/*do nothing*/
		}

		appLen = iPos-APPLENPOS_IN_REPLYTOATS-LENGTH_FIELD_BYTES;
	    ShortToChar(appLen,&dataBuf[APPLENPOS_IN_REPLYTOATS] );/*填写应用层数据长度*/

		if (RES_REPLYTO_ATS == GetResReplyToAtsFlag())
		{
			/*清除ATS发送数据结构体*/
			ClearRcvFromAtsData();
			SetResReplyToAtsFlag(ANTI_RES_REPLYTO_ATS);/*清除应答标志*/
		}
		if (AUTO_REPLYTO_ATS == GetAutoReplyToAtsFlag())/*是否需要主动汇报*/
		{
			SetAutoReplyToAtsFlag(DEFAULT_ZERO);/*清除主动回复标志*/
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
函数名	：CalcCrc
功能描述：计算ATS发送过来命令的CRC值
输入	：无
输出	：无
返回值	：计算的CRC值
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
	if(ATS_TO_ZC_TSR_FRT_SET==tmpAtsCmdType || ATS_TO_ZC_TSR_SEC_SET==tmpAtsCmdType)/*首次设置 或 二次设置*/
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
	else if(ATS_TO_ZC_TSR_FRT_CANCEL==tmpAtsCmdType || ATS_TO_ZC_TSR_SEC_CANCEL==tmpAtsCmdType)/*首次取消 或 二次取消*/
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