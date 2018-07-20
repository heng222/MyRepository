/*******************************************
文件名	：TsrOutputDataProcess.c
作者	：董欣
创建时间：2016-10
描述	：输出处理程序
备注	：无
*******************************************/

#include "TsrOutputDataProcess.h"
#include "../TsrTransmitFlagAdmin/TsrTransmitStateDataManage.h"
#include "../TsrParserPacker/TsrParsePackAtsData.h"
#include "../TsrParserPacker/ParsePackInterfaceDefine.h"
#include "../TsrSystem/TsrSysStatusData.h"
#include "../TsrSystem/TsrSysConfigData.h"
/*#include "../TsrMaintenance/MaintainManager.h" */
#include "../../../Common/MemSet.h"
#include "../../SysDataManager/SysStatusData.h"

static UINT8_S g_AutoReplyToAtsFlag = DEFAULT_ZERO;/*主动向ATS汇报标志:0本周期不汇报，1本周期汇报*/

/*******************************************
函数名	：GetAutoReplyToAtsFlag
功能描述：获取主动向ATS汇报标志
输入	：无
输出	：无
返回值	：0本周期不汇报，1本周期汇报
*******************************************/
UINT8_S GetAutoReplyToAtsFlag(void)
{
	return g_AutoReplyToAtsFlag;
}

/*******************************************
函数名	：SetAutoReplyToAtsFlag
功能描述：设置主动向ATS汇报标志
输入	：UINT8_S replayTime,0本周期不汇报，1本周期汇报
输出	：无
返回值	：无
*******************************************/
void SetAutoReplyToAtsFlag(UINT8_S replayTime)
{
	g_AutoReplyToAtsFlag = replayTime;
}

/*******************************************
函数名	：ProcessReplyToAtsData
功能描述：处理回复到Ats数据
输入	：无
输出	：无
返回值	：0：失败；1：成功
*******************************************/
UINT8_S ProcessReplyToAtsData()
{
	UINT32_S zcCycle = DEFAULT_ZERO;
	UINT16_S replyToAtsCycle = DEFAULT_ZERO;
	Tsr_DataStru_Set_Stru* pTmpTsrSetData = NULL;

	zcCycle = GetZcCycle();
	pTmpTsrSetData = GetTsrDataAdmin();

	if (ZC_WORK_POP == GetZcWorkState())/*上电*/
	{
		SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_RESET_REPORT);
		WriteReplyToAtsData(pTmpTsrSetData);/*将临时限速管理信息填写到向ATS发送临时限速结构体中*/
		SetAutoReplyToAtsFlag(AUTO_REPLYTO_ATS);/*初始上电状态需要立即回复ATS信息,发送重启后汇报TSR*/
	}
	else if (ZC_WORK_NORMAL == GetZcWorkState())
	{
		replyToAtsCycle = GetPeriodsDuringAutoReplyTsrToAts(); 

		if ((DEFAULT_ZERO != replyToAtsCycle)
			        &&(DEFAULT_ZERO == (zcCycle % replyToAtsCycle))
					         &&(DEFAULT_ZERO != zcCycle))/*回复周期到*/
		{
			SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_NORMAL_REPORT);
			WriteReplyToAtsData(pTmpTsrSetData);/*设置临时限速信息*/
			SetAutoReplyToAtsFlag(AUTO_REPLYTO_ATS);/*回复周期到需要立即回复ATS信息，发送正常汇报TSR*/
			SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_NORMAL_REPORT);
		}
		else
		{
			/*不处理*/
		}

	}
	else
	{
		/*不处理*/
	}

	return TSR_SUCCESS;
}



