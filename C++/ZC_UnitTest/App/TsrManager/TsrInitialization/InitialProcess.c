/*******************************************
文件名	：InitialProcess.c
作者	：董欣
创建时间：2016-10
描述	：数据初始化
备注	：无
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
函数名	：InitialProcess
功能描述：初始化函数
输入	：无
输出	：无
返回值	：0:初始化失败；1：初始化成功。
*******************************************/
UINT8_S InitialProcess(void)
{
	UINT8_S  rtnValue = TSR_SUCCESS;/*函数返回值*/

	/*初始化TSR参数配置数据信息*/
	if (TSR_SUCCESS == InitTsrParamConfigStru())
	{			
		/*初始化运行时数据信息*/
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
函数名	：InitTsrRuntimeData
功能描述：初始化运行变量
输入	：无
输出	：无
返回值	：0: 初始化失败,>0: 初始化成功
*******************************************/
static UINT8_S InitTsrRuntimeData(void)
{
	UINT8_S rtnValue =DEFAULT_ZERO;
	Tsr_DataStru_ToATS *replyToAtsDataStru = NULL;
	Tsr_DataStru_FromAts *rcvFromAtsDataStru = NULL;
	Tsr_DataStru_Cell_Stru *lastSingleTsrDataStru = NULL;

	/*初始化全局变量*/
	TsrGlobalDataInit();

	/*初始化数据结构体*/
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
函数名	：InitTsrParamConfigStru
功能描述：初始化TSR参数配置信息
输入	：无
输出	：无
返回值	：0: 初始化失败，>0: 初始化成功
*******************************************/
static UINT8_S InitTsrParamConfigStru(void)
{
	BnfSystemConfigStruct *bnfSysConfigStr = NULL;
	BnfCommFailTimeStruct *bnfCommFailTimeStru = NULL;
	BnfZcCommConfigStruct * pBnfZcCommConfigStru = NULL;
	Tsr_Param_Config_Stru* pTsrParamConfigStru = NULL;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bnfSysConfigStr = GetSystemConfigData();/*系统配置数据表*/
	bnfCommFailTimeStru = GetCommFailTimeData();/*通信故障超时时长结构体*/
	pBnfZcCommConfigStru = GetZcCommConfigData();/*ZC子系统配置表的第一项*/
	pTsrParamConfigStru = GetTsrParamConfig();/*TSR参数结构体*/

	if ((NULL != bnfSysConfigStr)
		&& (NULL != bnfCommFailTimeStru)
		  && (NULL != pBnfZcCommConfigStru)
		    && (NULL != pTsrParamConfigStru))/*安全防护*/
	{
		pTsrParamConfigStru->TsrMaxSpeedAccordingly = bnfSysConfigStr->maxTsrSpeed;
		pTsrParamConfigStru->PeriodsOnKeepingAliveWithAts = (UINT32_S)(bnfCommFailTimeStru->zcToAtsCommFailTime / ZC_RUN_CYCLE_TIME);
		/*正常汇报TSR的周期数与汇报列车位置周期数一致*/
		pTsrParamConfigStru->PeriodsDuringAutoReplyTsrToAts = (UINT16_S)((pBnfZcCommConfigStru->zcSendAtsDataCycle / ZC_RUN_CYCLE_TIME)*AUTOREPTSR_TIMESOVER_REPTRNPOS);
		/*首次/二次超时间隔与通信超时一致*/
		pTsrParamConfigStru->PeriodsBetweenFsAndSs = 120U/*临时封住(UINT16_S)pTsrParamConfigStru->PeriodsOnKeepingAliveWithAts*/;
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
函数名	：TsrGlobalDataInit
功能描述：初始化全局变量信息
输入	：无
输出	：无
返回值	：0: 初始化失败，>0: 初始化成功
*******************************************/
static void TsrGlobalDataInit(void)
{
	SetAtsSendTsrFsAndSsTime(UINT16_MAX); /* 首次二次计时时间 */
	SetLastAtsCmdType(LAST_ATS_SET_CMD_DEFAULT); /* ATS最近一次命令类型 */
	SetAutoReplyToAtsFlag(DEFAULT_ZERO); /*主动汇报TSR标志*/
	InitTsrDataAdmin();/*初始化临时限速管理变量*/
	SetZcWorkState(ZC_WORK_POP);/*初始化状态数据结构体*/
}