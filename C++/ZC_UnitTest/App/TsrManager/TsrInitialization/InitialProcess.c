/*******************************************
�ļ���	��InitialProcess.c
����	������
����ʱ�䣺2016-10
����	�����ݳ�ʼ��
��ע	����
*******************************************/

#include "InitialProcess.h"
#include "../TsrSystem/TsrSystemDefine.h"
#include "../TsrSystem/TsrSysConfigData.h"
#include "../TsrSystem/TsrSysStatusData.h"
#include "../TsrSystem/TsrSysConfigData.h"
#include "../TsrTransmitFlagAdmin/TsrTransmitStateDataManage.h"
#include "../TsrAdministrator/TsrDataAdmin.h"
#include "../TsrQuery/QueryManage.h"
/*#include "../TsrMain/MainApp.h"*/
#include "../TsrDmu/DataHandle/DmuDataHandle.h"
#include "../TsrDmu/DataHandle/DmuStruct.h"
/*#include "../TsrDataVersion/DataVersionDefine.h"*/
/*#include "../TsrDataVersion/DataVersionConfigData.h"*/
#include "../TsrParserPacker/TsrParsePackAtsData.h"
#include "../TsrParserPacker/ParsePackInterfaceDefine.h"
#include "../TsrIO/TsrOutputDataProcess.h" 	
/*#include "../TsrMaintenance/MaintainManager.h" */	
#include "../../SysDataManager/SysDefine.h" 
#include "../../DmuZc/Data/ZcCommConfigData.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/CommonTypes.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/Convert.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Dmu/DmuComm/Data/SystemDevCommData.h"
#include "../../../Dmu/DmuComm/Data/SystemConfigData.h"
#include "../../../Dmu/DmuComm/Data/TempLimitSpeedData.h"
#include "../../../Dmu/DmuComm/Data/SystemConfigData.h"
#include "../../../Dmu/DmuComm/Data/CommFailTimeData.h"
#include "../../../PlatformAdapter/AppItf/AdptAppFileInterface.h"
#include "../../../PlatformAdapter/AppItf/AdptAppServiceInterface.h"


static UINT8_S InitTsrRuntimeData(void);
static UINT8_S InitTsrParamConfigStru(void);
static void TsrGlobalDataInit(void);

/*******************************************
������	��InitialProcess
������������ʼ������
����	����
���	����
����ֵ	��0:��ʼ��ʧ�ܣ�1����ʼ���ɹ���
*******************************************/
UINT8_S InitialProcess(void)
{
	UINT8_S  rtnValue = TSR_SUCCESS;/*��������ֵ*/

	/*��ʼ��TSR��������������Ϣ*/
	if (TSR_SUCCESS == InitTsrParamConfigStru())
	{			
		/*��ʼ������ʱ������Ϣ*/
		if (TSR_SUCCESS == InitTsrRuntimeData())
		{
			rtnValue = TSR_SUCCESS;
							
		} 
		else
		{
			#ifdef SYS_TYPE_VXWORKS
			printf("InitTsrRuntimeData error\n");
			#endif
			rtnValue =  TSR_ERROR;
		}
	}
	else
	{
		#ifdef SYS_TYPE_VXWORKS
		printf("InitTsrParamConfigStru error\n");
		#endif
		rtnValue =  TSR_ERROR;
	}		
	
	return rtnValue;
}

/*******************************************
������	��InitTsrRuntimeData
������������ʼ�����б���
����	����
���	����
����ֵ	��0: ��ʼ��ʧ��,>0: ��ʼ���ɹ�
*******************************************/
static UINT8_S InitTsrRuntimeData(void)
{
	UINT8_S rtnValue =DEFAULT_ZERO;
	Tsr_DataStru_ToATS *replyToAtsDataStru = NULL;
	Tsr_DataStru_FromAts *rcvFromAtsDataStru = NULL;
	Tsr_DataStru_Cell_Stru *lastSingleTsrDataStru = NULL;

	/*��ʼ��ȫ�ֱ���*/
	TsrGlobalDataInit();

	/*��ʼ�����ݽṹ��*/
	rcvFromAtsDataStru = GetRcvFromAtsData();
	replyToAtsDataStru = GetReplyToAtsDataStru();
	lastSingleTsrDataStru = GetLastTsrCellData();

	if((NULL != replyToAtsDataStru)&&(NULL != rcvFromAtsDataStru)&&(NULL != lastSingleTsrDataStru))
	{
		ClearRcvFromAtsData();
		ClearReplyToAtsData();
		ClearLastTsrCellData();

		rtnValue = TSR_SUCCESS;
	}
	else
	{
		printf("InitTsrRuntimeData error\n");
		rtnValue =  TSR_ERROR;
	}

	return rtnValue;
}

/*******************************************
������	��InitTsrParamConfigStru
������������ʼ��TSR����������Ϣ
����	����
���	����
����ֵ	��0: ��ʼ��ʧ�ܣ�>0: ��ʼ���ɹ�
*******************************************/
static UINT8_S InitTsrParamConfigStru(void)
{
	BnfSystemConfigStruct *bnfSysConfigStr = NULL;
	BnfCommFailTimeStruct *bnfCommFailTimeStru = NULL;
	BnfZcCommConfigStruct * pBnfZcCommConfigStru = NULL;
	Tsr_Param_Config_Stru* pTsrParamConfigStru = NULL;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bnfSysConfigStr = GetSystemConfigData();/*ϵͳ�������ݱ�*/
	bnfCommFailTimeStru = GetCommFailTimeData();/*ͨ�Ź��ϳ�ʱʱ���ṹ��*/
	pBnfZcCommConfigStru = GetZcCommConfigData();/*ZC��ϵͳ���ñ�ĵ�һ��*/
	pTsrParamConfigStru = GetTsrParamConfig();/*TSR�����ṹ��*/

	if ((NULL != bnfSysConfigStr)
		&& (NULL != bnfCommFailTimeStru)
		  && (NULL != pBnfZcCommConfigStru)
		    && (NULL != pTsrParamConfigStru))/*��ȫ����*/
	{
		pTsrParamConfigStru->TsrMaxSpeedAccordingly = bnfSysConfigStr->maxTsrSpeed;
		pTsrParamConfigStru->PeriodsOnKeepingAliveWithAts = (UINT32_S)(bnfCommFailTimeStru->zcToAtsCommFailTime / ZC_RUN_CYCLE_TIME);
		/*�����㱨TSR����������㱨�г�λ��������һ��*/
		pTsrParamConfigStru->PeriodsDuringAutoReplyTsrToAts = (UINT16_S)((pBnfZcCommConfigStru->zcSendAtsDataCycle / ZC_RUN_CYCLE_TIME)*AUTOREPTSR_TIMESOVER_REPTRNPOS);
		/*�״�/���γ�ʱ�����ͨ�ų�ʱһ��*/
		pTsrParamConfigStru->PeriodsBetweenFsAndSs = 120U/*��ʱ��ס(UINT16_S)pTsrParamConfigStru->PeriodsOnKeepingAliveWithAts*/;
		rtnValue = TSR_SUCCESS;
	}
	else
	{
		printf("InitTsrParamConfigStru error\n");
		rtnValue = TSR_ERROR;
	}	
	return rtnValue;
}

/*******************************************
������	��TsrGlobalDataInit
������������ʼ��ȫ�ֱ�����Ϣ
����	����
���	����
����ֵ	��0: ��ʼ��ʧ�ܣ�>0: ��ʼ���ɹ�
*******************************************/
static void TsrGlobalDataInit(void)
{
	SetAtsSendTsrFsAndSsTime(UINT16_MAX); /* �״ζ��μ�ʱʱ�� */
	SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT); /* ATS���һ���������� */
	SetAutoReplyToAtsFlag(DEFAULT_ZERO); /*�����㱨TSR��־*/
	InitTsrDataAdmin();/*��ʼ����ʱ���ٹ������*/
	SetZcWorkState(ZC_WORK_POP);/*��ʼ��״̬���ݽṹ��*/
}