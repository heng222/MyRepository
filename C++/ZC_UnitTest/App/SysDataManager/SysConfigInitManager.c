/************************************************************************
*
* 文件名   ：  SysConfigInitManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  ZC系统配置的初始化管理
* 备  注   ：  无
*
************************************************************************/
#include "SysConfigInitManager.h"
#include "SysConfigData.h"
#include "SysDefine.h"
#include "../../Dmu/DmuComm/Data/SystemConfigData.h"
#include "../../Dmu/DmuComm/Data/TempLimitSpeedData.h"
#include "../../Dmu/DmuComm/Data/CommFailTimeData.h"
#include "../../Dmu/DmuComm/Data/TrainTypeConfigData.h"
#include "../../Dmu/DmuComm/Data/TrainInfoData.h"
#include "../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"
#include "../DmuZc/Data/ZcSystemConfigData.h"
#include "../DmuZc/Data/ZcCommConfigData.h"
#include "../DmuZc/Data/ZcTimeConfigData.h"
#include "../../PlatformAdapter/AppItf/AdptAppFileInterface.h"
#include "SysTimeData.h"
#include "math.h"

#ifdef SYS_TYPE_WINDOWS
#include "windows.h"
#endif

#ifdef PLATFORM_ARTESYN_FILEOPERATION
#include "../../cspadpt/Vcp_File_Interface.h"
#endif

extern ZcSubsystemConfigDataStruct gZcSubsystemConfigDataStru;     /*引用ZC子系统的配置数据信息结构*/
extern SystemConfigDataStruct gSystemConfigDataStru;               /*引用CBTC系统的配置数据信息结构*/
extern LocalZcConfigDataStruct gLocalZcConfigDataStru;             /*引用本地ZC配置数据结构信息*/

/*
* 功能描述： 初始化系统配置信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitSystemConfigData(void)
{
	UINT8_S rtnValue = 0U;
	BnfSystemConfigStruct *pBnfSysConfigStru = NULL;
	BnfTempLimitSpeedStruct *pBnfTempLimitSpeedStru = NULL;
	BnfCommFailTimeStruct *pBnfCommFailTimeStru = NULL;

	pBnfSysConfigStru = GetSystemConfigData();
	pBnfTempLimitSpeedStru = GetTempLimitSpeedData();
	pBnfCommFailTimeStru = GetCommFailTimeData();

	if ((NULL != pBnfSysConfigStru)
		&& (NULL != pBnfTempLimitSpeedStru)
		&& (NULL != pBnfCommFailTimeStru))
	{
		/*初始化系统配置数据*/
		gSystemConfigDataStru.LineMaBackDistance = pBnfSysConfigStru->safeBackDistance;
		gSystemConfigDataStru.LineMinOverlapLength = pBnfSysConfigStru->maxOverlapLength;
		gSystemConfigDataStru.LineMaxSpeed = (UINT16_S)((((UINT16_S)(pBnfSysConfigStru->maxLineLimitSpeed))*1000U) / 36U);
		gSystemConfigDataStru.LineMaxTSRSpeed = pBnfSysConfigStru->maxTsrSpeed;
		gSystemConfigDataStru.LinkLogicDirUpAndDown =  pBnfSysConfigStru->segLogicDirUpAndDown;

		gSystemConfigDataStru.ATSCommCycle = (UINT8_S)(pBnfCommFailTimeStru->zcToAtsCommFailTime/ZC_RUN_CYCLE_TIME);
		gSystemConfigDataStru.CICommCycle = (UINT8_S)(pBnfCommFailTimeStru->zcToCiCommFailTime/ZC_RUN_CYCLE_TIME);
		gSystemConfigDataStru.NZcCommCycle = (UINT8_S)(pBnfCommFailTimeStru->zcToZcCommFailTime/ZC_RUN_CYCLE_TIME);
		gSystemConfigDataStru.TrainAtpCommCycle = (UINT8_S)(pBnfCommFailTimeStru->zcToAtpCommFailTime/ZC_RUN_CYCLE_TIME);
		gSystemConfigDataStru.NtpTimeZoneDiff = pBnfSysConfigStru->mimeZoneDifference;

		if (RETURN_SUCCESS == InitTrainConfigInfo())
		{
			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 初始化系统配置信息中列车信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitTrainConfigInfo(void)
{
	UINT16_S trainTypeNum = DEFAULT_ZERO;
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S trainId = DEFAULT_ZERO;
	BnfTrainTypeConfigStruct *pBnfTrainTypeConfigStru = NULL;
	BnfTrainInfoStruct *pBnfTrainInfoStru = NULL;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;
    UINT16_S configMaxTrainLen = DEFAULT_ZERO;

	/*初始化列车参数*/
	pBnfTrainTypeConfigStru = GetTrainTypeConfigDataInfo(&trainTypeNum);

	if ((NULL != pBnfTrainTypeConfigStru)
		&& (DEFAULT_ZERO != trainTypeNum))
	{
		for (cycle = DEFAULT_ZERO;cycle < trainTypeNum;cycle++)
		{
			/*获取列车Id*/
			trainId = (UINT16_S)(pBnfTrainTypeConfigStru[cycle].trainDevName & ((UINT16_S)0x00ffU));

			if (LINE_MAX_TRAIN_ID > trainId)
			{
				gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].TrainID = trainId;
				gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].TrainType = pBnfTrainTypeConfigStru[cycle].trainType;
			
				/*根据车型信息获取列车参数信息*/
				pBnfTrainInfoStru = GetIndexIdTrainInfoDataStru((UINT8_S)(gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].TrainType));

				if (NULL != pBnfTrainInfoStru)
				{
					gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].TrainLength = pBnfTrainInfoStru->trainLength;
					gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].MaxLineDeclGradient = (UINT16_S)(((UINT16_S)(abs(pBnfTrainInfoStru->lineMaxGrade)))/10U);
					gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].MaxTrainTractionAcc = pBnfTrainInfoStru->trainMaxTracAcc 
						                                             + gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].MaxLineDeclGradient;
                    
                    if(configMaxTrainLen < pBnfTrainInfoStru->trainLength)               
                    {
                        configMaxTrainLen = pBnfTrainInfoStru->trainLength;

                        /* 给最大车长赋值 */
                        SetLineMaxTrainLength(configMaxTrainLen);
                    }
				} 
				else
				{
					rtnValue = RETURN_ERROR;
					breakFlag = FLAG_SET;
					break;
				}
			} 
			else
			{
				rtnValue = RETURN_ERROR;
				breakFlag = FLAG_SET;
				break;
			}
		}

		if (FLAG_SET != breakFlag)
		{
			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			/*不处理*/
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 初始化ZC子系统配置信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitZcSubSystemConfigData(void)
{
	BnfZcSystemConfigStruct *pBnfZcSystemConfigStru = NULL;
	BnfZcCommConfigStruct * pBnfZcCommConfigStru = NULL;
	UINT8_S rtnValue = DEFAULT_ZERO;

	pBnfZcSystemConfigStru = GetZcSystemConfigData();
	pBnfZcCommConfigStru = GetZcCommConfigData();

	if ((NULL != pBnfZcSystemConfigStru)
		&& (NULL != pBnfZcCommConfigStru))
	{
 
		gZcSubsystemConfigDataStru.LineMinTrainLength = pBnfZcSystemConfigStru->lineMinTrainLength;
		gZcSubsystemConfigDataStru.RetreatProtectDistance = pBnfZcSystemConfigStru->trainMaxRecedeDis;
		gZcSubsystemConfigDataStru.SignalLightLength = pBnfZcSystemConfigStru->sectionLength;
		gZcSubsystemConfigDataStru.ReverseCycle = (UINT8_S)(pBnfZcSystemConfigStru->trainCbtcBackTime / ZC_RUN_CYCLE_TIME);
		gZcSubsystemConfigDataStru.SectionRedundantCycle = (UINT8_S)(pBnfZcSystemConfigStru->redunJudgmentTime / ZC_RUN_CYCLE_TIME);
		gZcSubsystemConfigDataStru.ToCiSectionType = pBnfZcSystemConfigStru->freeCodeNumSwitch;
		gZcSubsystemConfigDataStru.TrainAcrossSignalDis = pBnfZcSystemConfigStru->signPressureDis;
		gZcSubsystemConfigDataStru.ZcTraceRmTrainType = pBnfZcSystemConfigStru->zcTrackRmTrainType;

		gZcSubsystemConfigDataStru.ZCToATSCycleCycle = (UINT8_S)(pBnfZcCommConfigStru->zcSendAtsDataCycle / ZC_RUN_CYCLE_TIME);

		/*读取NTP相关内容*/
		gZcSubsystemConfigDataStru.SendNtpApplyCycle = (UINT16_S)(GetZcTimeSystemDuration() / ZC_RUN_CYCLE_TIME);
		gZcSubsystemConfigDataStru.NtpCheckDiffTime = GetZcTimeNtprrorTime() / 1000U;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* 功能描述： 初始化本地ZCId配置信息
* 参数说明： 无   
* 返回值  ： 0: 初始化失败
*			>0: 初始化成功      
*/
UINT8_S InitLocalZcIdConfigData(void)
{
	UINT16_S getZcId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;    
	UINT32_S tempRetVal = 0U;    	
    UINT8_S dataBuff[20] ={DEFAULT_ZERO};
	UINT32_S retVal = DEFAULT_ZERO;
	FILEType pfile = NULL; 
	
#ifdef PLATFORM_ARTESYN_FILEOPERATION
	GM_BOOL l_Result = GM_FALSE;
	UINT32 l_Size = 0U;	
	UINT32 l_Addr = 0U;		
    INT32 l_value = -1;	
#endif

	#ifdef SYS_TYPE_WINDOWS
	
	getZcId = GetPrivateProfileInt(L"主机配置信息",L"本地ID",0xFF,L"ini\\ZcLocalConfig.ini");
	if ((0xFFU != getZcId)
		&& (0U != getZcId))
	{
		gLocalZcConfigDataStru.wZCID = getZcId;
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}
	#endif
	
	#ifdef SYS_TYPE_VXWORKS
	
	#ifdef PLATFORM_ARTESYN_FILEOPERATION
	/* 雅特生平台 */
	CSPADPT_Get_SpeciConfig_Addr_Size(ENUM_CONFIG_DAT_TYPE_CIID, (UINT8*)(&l_Addr), &l_Size);
	
	l_Result = GM_Ini_File_Read_Int("CI_GLOBAL", "localCiId", &l_value, (char*)l_Addr);
	
	if ((GM_TRUE == l_Result) && (l_value > 0))
	{
		gLocalZcConfigDataStru.wZCID = (UINT16_S)(l_value);
		printf("ZcId:%d\n",gLocalZcConfigDataStru.wZCID);
	    rtnValue = RETURN_SUCCESS;
	}
	#else
	/*打开二进制文件*/
	tempRetVal = AdptAppFileOpen(ZC_ID_CONFIG_DATA,0U,&pfile);

	/*判断打开二进制文件是否成功*/
	if (1U == tempRetVal)
	{
		retVal = AdptAppFileRead(pfile,ZC_ID_CONFIG_DATA,dataBuff,((UINT32_S)(sizeof(dataBuff))));
		if(0U != retVal)
		{
			/*读取成功，继续执行*/
			gLocalZcConfigDataStru.wZCID = (UINT16_S)(((UINT16_S)dataBuff[0]) & ((UINT16_S)0x00ffU));
			printf("ZcId:%d\n",gLocalZcConfigDataStru.wZCID);
			rtnValue = RETURN_SUCCESS;
		}
		else
		{
			/*记录文件读取失败的错误*/
			rtnValue = RETURN_ERROR;
		}
		AdptAppFileClose(pfile);
	}
	else
	{
		/*打开二进制文件失败*/
		rtnValue = RETURN_ERROR;
	}
	#endif
	#endif

	return rtnValue;
}

/*
* 功能描述： 初始化本地Ntp配置信息
* 参数说明： 无   
* 返回值  ： 无      
*/
void InitLocalNtpConfigData(void)
{
	InitSysTimeData();
}
