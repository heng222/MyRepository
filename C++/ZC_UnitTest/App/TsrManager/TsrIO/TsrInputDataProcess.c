/*******************************************
�ļ���	��TsrInputDataProcess.c
����	������
����ʱ�䣺2016-10
����	�����봦�����
��ע	����
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
������	��UpdateTsrOperatingObject
�������������� ���ع������ʱ����������Ϣ ����
����	����
���	����
����ֵ	��0:����ʧ��,1:����ɹ�
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
	/*������ʱ�����±�*/
    flag = AplyTsrIndexOfZcId(localZcId);

    if ((DEFAULT_ZERO != localZcId) &&(flag > DEFAULT_ZERO))
    {
		tempTsrDataStru = GetTsrDataAdmin();/*��ȡTSR������ʱ���ٹ���������������ݸ��µ� gTsrDataStruBuff[indexOfTsrBuff]����*/
        indexOfTsrBuff = GeZcIdOfTsrBufIndex(localZcId);/*��ȡ��ZC��gTsrDataStruBuff�����е��±�*/

        if ((TSR_BUFF_SUM_MAX != indexOfTsrBuff) && (tempTsrDataStru != NULL))
        {
			tmpTsrQuan = tempTsrDataStru->TsrQuan;

            if (TSR_MAX_NUM >= tmpTsrQuan)
            {
                /*�������Ϣ*/
                DeleteSingleZcTsrInfo(localZcId);

                for (iCyc = DEFAULT_ZERO;iCyc < tmpTsrQuan;iCyc++)
                {
					tmpTsrSpeed = tempTsrDataStru->CellTsrData[iCyc].TsrSpeed;
                    /*д����ʱ���ٵ��ٶ�ֵ*/
                    rtnValue = SetSingleTsrDataOfSpeed(indexOfTsrBuff,(UINT16_S)iCyc,(UINT16_S)tmpTsrSpeed);

					tmpLogsecQuan = tempTsrDataStru->CellTsrData[iCyc].LogicSecQuan;

                    /*���õ�����ʱ�����߼�������Ϣ*/
                    rtnValue *= SetSingleTsrDataOfSectionInfo(indexOfTsrBuff,iCyc,tmpLogsecQuan,tempTsrDataStru->CellTsrData[iCyc].LogicSecId);

                    if (RETURN_ERROR == rtnValue)
                    {
                        rtnValue = RETURN_ERROR;
                        break;
                    } 
                    else
                    {
                        /*������*/
                    }
                }

                /*������ʱ��������*/
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
������	��ProcessRcvFromAtsData
��������������ATS��������
����	����
���	����
����ֵ	��0:����ʧ��,1:����ɹ�
*******************************************/
UINT8_S ProcessRcvFromAtsData(void)
{
	UINT8_S returnValue = TSR_ERROR;
	Tsr_DataStru_Cell_Stru* tempSingleTsrDataStru = NULL;
	UINT32_S crc = DEFAULT_ZERO;

	tempSingleTsrDataStru = GetTsrCellDataFromAts();


	/*�жϵȴ�Ats�����Ƿ�ʱ*/
	if (GetAtsSendTsrFsAndSsTime() != UINT16_MAX)
	{
		AddAtsSendTsrFsAndSsTime();/*�ۼӶ��εȴ�ʱ��*/

/*		LogMsgString( 1,"WaitAtsSecondCmdTime  %d\n", GetAtsSendTsrFsAndSsTime());*/

		if (GetAtsSendTsrFsAndSsTime() > GetPeriodsBetweenFsAndSs())/*��ʱ*/
		{
/*			LogMsgString( 1,"wait second over  %d\n", GetAtsSendTsrFsAndSsTime());*/

			SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT);/*����ϴ����õ�ATS��������*/

			SetAtsSendTsrFsAndSsTime(UINT16_MAX);/*���ó�ʱʱ��Ϊ����ֵ*/

			ClearLastTsrCellData();
		}
	}

	/*�жϱ������Ƿ���ATS����Ҫ����*/
    if (RES_REPLYTO_ATS == GetResReplyToAtsFlag())
	{
		crc =  CalcCrc();
		SetAtsCmdCrc32(crc);

		/*����������Ϣ�Ϸ��Լ��*/
		if (TSR_ERROR == CheckAtsInputData())
		{
			/*�����д������ATS�������ݽṹ��*/
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

					SetAtsSendTsrFsAndSsTime(1u);/*�ȴ���������ʱ�俪ʼ��ʱ*/
/*					LogMsgString( 1,"WaitAtsSecondCmdTime  %d\n", GetAtsSendTsrFsAndSsTime());*/
/*					SetEventLogList(DMS_ATS_TIME_START,LOG_EVENT_INFORMATION,1u,GetAtsSendTsrFsAndSsTime());*/
					break;

				case ATS_TO_ZC_TSR_FRT_CANCEL:

					SetAtsSendTsrFsAndSsTime(1u);/*�ȴ���������ʱ�俪ʼ��ʱ*/
/*					LogMsgString( 1,"WaitAtsSecondCmdTime  %d\n", GetAtsSendTsrFsAndSsTime());*/
/*					SetEventLogList(DMS_ATS_TIME_START,LOG_EVENT_INFORMATION,1u,GetAtsSendTsrFsAndSsTime());*/
					break;

				case ATS_TO_ZC_TSR_FRT_CONFIRM:

					SetAtsSendTsrFsAndSsTime(1u);/*�ȴ���������ʱ�俪ʼ��ʱ*/
/*					LogMsgString( 1,"WaitAtsSecondCmdTime  %d\n", GetAtsSendTsrFsAndSsTime());*/
/*					SetEventLogList(DMS_ATS_TIME_START,LOG_EVENT_INFORMATION,1u,GetAtsSendTsrFsAndSsTime());*/
					break;

				case ATS_TO_ZC_TSR_SEC_SET:

					SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT);/*����ϴ����õ�ATS��������*/
					SetAtsSendTsrFsAndSsTime(UINT16_MAX);/*�����������ʱ�俪ʼ��ʱ*/
					ClearLastTsrCellData();

					if (ZC_WORK_NORMAL == GetZcWorkState())
					{
					    AddTsrDataAdmin(GetTsrCellDataFromAts());/*�����ʱ������Ϣ*/
					    SetAutoReplyToAtsFlag(AUTO_REPLYTO_ATS);/*������ʱ���ٳɹ���Ҫ�����ظ�ATS��Ϣ�����������㱨TSR*/
						SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_NORMAL_REPORT);

						if (TSR_SUCCESS == UpdateTsrOperatingObject())
						{
							/*Do nothing currently !*/
						} 
						else
						{/*����������ʧ�ܣ���ɾ�����������е���ʱ���٣��ɶ��˶�ƽ̨��֤����ATP��������������ȫ����*/
							DeleteSingleZcTsrInfo(GetLocalZcId());
						}
					}
					break;

				case ATS_TO_ZC_TSR_SEC_CANCEL:

					SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT);/*����ϴ����õ�ATS��������*/
					SetAtsSendTsrFsAndSsTime(UINT16_MAX);/*�����������ʱ�俪ʼ��ʱ*/
					ClearLastTsrCellData();

					if (ZC_WORK_NORMAL == GetZcWorkState())
					{
					    DeleteTsrDataAdmin(GetTsrCellDataFromAts());/*ɾ����ʱ������Ϣ*/
					    SetAutoReplyToAtsFlag(AUTO_REPLYTO_ATS);/*ȡ����ʱ���ٳɹ���Ҫ�����ظ�ATS��Ϣ�����������㱨TSR*/
						SetReplyToAtsAutoCmdValue(ZC_TO_ATS_TSR_NORMAL_REPORT);

						if (TSR_SUCCESS == UpdateTsrOperatingObject())
						{
							/*Do nothing currently !*/
						} 
						else
						{/*����������ʧ�ܣ���ɾ�����������е���ʱ���٣��ɶ��˶�ƽ̨��֤����ATP��������������ȫ����*/
							DeleteSingleZcTsrInfo(GetLocalZcId());
						}
					}
					break;

				case ATS_TO_ZC_TSR_SEC_CONFIRM:

					SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT);/*����ϴ����õ�ATS��������*/
					SetAtsSendTsrFsAndSsTime(UINT16_MAX);/*�����������ʱ�俪ʼ��ʱ*/
					SetZcWorkState(ZC_WORK_NORMAL);/*��������*/

					SetAutoReplyToAtsFlag(AUTO_REPLYTO_ATS);/*�ϵ�ȷ�ϳɹ���Ҫ�����ظ�ATS��Ϣ�����������㱨TSR*/
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
		/*û�����ݣ�������*/
	}

/*	LogMsgString(1,"ZcWorkState:%x\n",GetZcWorkState());*/
	
	return returnValue;
}
