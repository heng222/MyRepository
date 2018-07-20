/*******************************************
文件名	：TsrInputDataProcess.c
作者	：董欣
创建时间：2016-10
描述	：输入处理程序
备注	：无
*******************************************/

#include "TsrInputDataProcess.h"
#include "../TsrTransmitFlagAdmin/TsrTransmitStateDataManage.h"
#include "../TsrParserPacker/TsrParsePackAtsData.h"
#include "../TsrParserPacker/ParsePackInterfaceDefine.h"
#include "TsrOutputDataProcess.h"
#include "../TsrQuery/QueryManage.h"
#include "../TsrDmu/DataHandle/DmuDataHandle.h"
#include "../TsrDmu/DataHandle/DmuStruct.h"
#include "../../../Dmu/DmuComm/Data/SystemConfigData.h"
#include "../TsrSystem/TsrSysConfigData.h"
#include "../TsrSystem/TsrSysStatusData.h"
#include "../TsrSystem/TsrSystemDefine.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Convert.h"
#include "../../LineDataManager/Tsr/TsrLogicManager.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../LineDataManager/Tsr/TsrStatusData.h"
/*#include "../TsrMaintenance/MaintainManager.h"*/
/*#include "../TsrMaintenance/EventCode.h"/

static UINT8_S UpdateTsrOperatingObject();
/*******************************************
函数名	：UpdateTsrOperatingObject
功能描述：更新 本地管理的临时限速配置信息 变量
输入	：无
输出	：无
返回值	：0:处理失败,1:处理成功
*******************************************/
static UINT8_S UpdateTsrOperatingObject()
{
	UINT8_S rtnValue = TSR_ERROR;
	UINT8_S flag = DEFAULT_ZERO;
	UINT16_S localZcId = DEFAULT_ZERO;
	Tsr_DataStru_Set_Stru* tempTsrDataStru = NULL;
	UINT8_S indexOfTsrBuff = DEFAULT_ZERO;
	UINT8_S tmpTsrQuan = DEFAULT_ZERO;
	UINT8_S tmpLogsecQuan = DEFAULT_ZERO;
	UINT8_S iCyc = DEFAULT_ZERO;
	UINT8_S tmpTsrSpeed = DEFAULT_ZERO;

	localZcId = GetLocalZcId();
	/*申请临时限速下标*/
    flag = AplyTsrIndexOfZcId(localZcId);

    if ((DEFAULT_ZERO != localZcId) &&(flag > DEFAULT_ZERO))
    {
		tempTsrDataStru = GetTsrDataAdmin();/*获取TSR功能临时限速管理变量，将其内容更新到 gTsrDataStruBuff[indexOfTsrBuff]变量*/
        indexOfTsrBuff = GeZcIdOfTsrBufIndex(localZcId);/*获取本ZC在gTsrDataStruBuff变量中的下标*/

        if ((TSR_BUFF_SUM_MAX != indexOfTsrBuff) && (tempTsrDataStru != NULL))
        {
			tmpTsrQuan = tempTsrDataStru->TsrQuan;

            if (TSR_MAX_NUM >= tmpTsrQuan)
            {
                /*先清除信息*/
                DeleteSingleZcTsrInfo(localZcId);

                for (iCyc = DEFAULT_ZERO;iCyc < tmpTsrQuan;iCyc++)
                {
					tmpTsrSpeed = tempTsrDataStru->CellTsrData[iCyc].TsrSpeed;
                    /*写入临时限速的速度值*/
                    rtnValue = SetSingleTsrDataOfSpeed(indexOfTsrBuff,(UINT16_S)iCyc,(UINT16_S)tmpTsrSpeed);

					tmpLogsecQuan = tempTsrDataStru->CellTsrData[iCyc].LogicSecQuan;

                    /*设置单个临时限速逻辑区段信息*/
                    rtnValue *= SetSingleTsrDataOfSectionInfo(indexOfTsrBuff,iCyc,tmpLogsecQuan,tempTsrDataStru->CellTsrData[iCyc].LogicSecId);

                    if (RETURN_ERROR == rtnValue)
                    {
                        rtnValue = RETURN_ERROR;
                        break;
                    } 
                    else
                    {
                        /*不处理*/
                    }
                }

                /*设置临时限速数量*/
                SetZcIdOfTsrNum(indexOfTsrBuff,tmpTsrQuan);

				rtnValue = TSR_SUCCESS;
            } 
            else
            {
				rtnValue = TSR_ERROR;
            } 
        } 
        else
        {
            rtnValue = TSR_ERROR;
        }
    } 
    else
    {
        rtnValue = TSR_ERROR;
    }

	return rtnValue;
}
/*******************************************
函数名	：ProcessRcvFromAtsData
功能描述：处理ATS发来数据
输入	：无
输出	：无
返回值	：0:处理失败,1:处理成功
*******************************************/
UINT8_S ProcessRcvFromAtsData(void)
{
	UINT8_S returnValue = TSR_ERROR;
	Tsr_DataStru_Cell_Stru* tempSingleTsrDataStru = NULL;
	UINT32_S crc = DEFAULT_ZERO;

	tempSingleTsrDataStru = GetTsrCellDataFromAts();


	/*判断等待Ats请求是否超时*/
	if (GetAtsSendTsrFsAndSsTime() != UINT16_MAX)
	{
		AddAtsSendTsrFsAndSsTime();/*累加二次等待时间*/

/*		LogMsgString( 1,"WaitAtsSecondCmdTime  %d\n", GetAtsSendTsrFsAndSsTime());*/

		if (GetAtsSendTsrFsAndSsTime() > GetPeriodsBetweenFsAndSs())/*超时*/
		{
/*			LogMsgString( 1,"wait second over  %d\n", GetAtsSendTsrFsAndSsTime());*/

			SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT);/*清除上次设置的ATS发送命令*/

			SetAtsSendTsrFsAndSsTime(UINT16_MAX);/*设置超时时间为保留值*/

			ClearLastTsrCellData();
		}
	}

	/*判断本周期是否有ATS命令要处理*/
    if (RES_REPLYTO_ATS == GetResReplyToAtsFlag())
	{
		crc =  CalcCrc();
		SetAtsCmdCrc32(crc);

		/*进行输入信息合法性检查*/
		if (TSR_ERROR == CheckAtsInputData())
		{
			/*数据有错误，清除ATS发送数据结构体*/
			SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT);
			ClearRcvFromAtsData();
			ClearLastTsrCellData();
			SetAtsSendTsrFsAndSsTime(UINT16_MAX);
/*			LogMsgString( 1,"CheckAtsInputData error\n");*/
/*			SetEventLogList(DMS_ATS_CHECK_DATA_ERROR,LOG_EVENT_ERROR,1u,0u);*/
			returnValue = TSR_ERROR;
		}
		else
		{
/*			SetEventLogList(DMS_ATS_CHECK_OK,LOG_EVENT_INFORMATION,1u,0u);*/
/*			LogMsgString(1,"CheckAtsInputData ok\n");*/

			switch (GetAtsCmdType())
			{
				case ATS_TO_ZC_TSR_FRT_SET:

					SetAtsSendTsrFsAndSsTime(1u);/*等待二次设置时间开始计时*/
/*					LogMsgString( 1,"WaitAtsSecondCmdTime  %d\n", GetAtsSendTsrFsAndSsTime());*/
/*					SetEventLogList(DMS_ATS_TIME_START,LOG_EVENT_INFORMATION,1u,GetAtsSendTsrFsAndSsTime());*/
					break;

				case ATS_TO_ZC_TSR_FRT_CANCEL:

					SetAtsSendTsrFsAndSsTime(1u);/*等待二次设置时间开始计时*/
/*					LogMsgString( 1,"WaitAtsSecondCmdTime  %d\n", GetAtsSendTsrFsAndSsTime());*/
/*					SetEventLogList(DMS_ATS_TIME_START,LOG_EVENT_INFORMATION,1u,GetAtsSendTsrFsAndSsTime());*/
					break;

				case ATS_TO_ZC_TSR_FRT_CONFIRM:

					SetAtsSendTsrFsAndSsTime(1u);/*等待二次设置时间开始计时*/
/*					LogMsgString( 1,"WaitAtsSecondCmdTime  %d\n", GetAtsSendTsrFsAndSsTime());*/
/*					SetEventLogList(DMS_ATS_TIME_START,LOG_EVENT_INFORMATION,1u,GetAtsSendTsrFsAndSsTime());*/
					break;

				case ATS_TO_ZC_TSR_SEC_SET:

					SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT);/*清除上次设置的ATS发送命令*/
					SetAtsSendTsrFsAndSsTime(UINT16_MAX);/*清除二次设置时间开始计时*/
					ClearLastTsrCellData();

					if (ZC_WORK_NORMAL == GetZcWorkState())
					{
					    AddTsrDataAdmin(GetTsrCellDataFromAts());/*添加临时限速信息*/
					    SetAutoReplyToAtsFlag(AUTO_REPLYTO_ATS);/*设置临时限速成功需要立即回复ATS信息，发送正常汇报TSR*/
						SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_NORMAL_REPORT);

						if (TSR_SUCCESS == UpdateTsrOperatingObject())
						{
							/*Do nothing currently !*/
						} 
						else
						{/*若发生更新失败，则删除变量中所有的临时限速，由二乘二平台保证不向ATP输出，不会产生安全问题*/
							DeleteSingleZcTsrInfo(GetLocalZcId());
						}
					}
					break;

				case ATS_TO_ZC_TSR_SEC_CANCEL:

					SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT);/*清除上次设置的ATS发送命令*/
					SetAtsSendTsrFsAndSsTime(UINT16_MAX);/*清除二次设置时间开始计时*/
					ClearLastTsrCellData();

					if (ZC_WORK_NORMAL == GetZcWorkState())
					{
					    DeleteTsrDataAdmin(GetTsrCellDataFromAts());/*删除临时限速信息*/
					    SetAutoReplyToAtsFlag(AUTO_REPLYTO_ATS);/*取消临时限速成功需要立即回复ATS信息，发送正常汇报TSR*/
						SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_NORMAL_REPORT);

						if (TSR_SUCCESS == UpdateTsrOperatingObject())
						{
							/*Do nothing currently !*/
						} 
						else
						{/*若发生更新失败，则删除变量中所有的临时限速，由二乘二平台保证不向ATP输出，不会产生安全问题*/
							DeleteSingleZcTsrInfo(GetLocalZcId());
						}
					}
					break;

				case ATS_TO_ZC_TSR_SEC_CONFIRM:

					SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT);/*清除上次设置的ATS发送命令*/
					SetAtsSendTsrFsAndSsTime(UINT16_MAX);/*清除二次设置时间开始计时*/
					SetZcWorkState(ZC_WORK_NORMAL);/*正常工作*/

					SetAutoReplyToAtsFlag(AUTO_REPLYTO_ATS);/*上电确认成功需要立即回复ATS信息，发送正常汇报TSR*/
					SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_NORMAL_REPORT);
					break;
				default:
						
					break;
			}
			
			returnValue = TSR_SUCCESS;
		}		 		
	}
	else
	{
		/*没有数据，不处理*/
	}

/*	LogMsgString(1,"ZcWorkState:%x\n",GetZcWorkState());*/
	
	return returnValue;
}
