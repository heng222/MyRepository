/************************************************************************
*
* �ļ���   ��  SysConfigInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ZCϵͳ���õĳ�ʼ������
* ��  ע   ��  ��
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

extern ZcSubsystemConfigDataStruct gZcSubsystemConfigDataStru;     /*����ZC��ϵͳ������������Ϣ�ṹ*/
extern SystemConfigDataStruct gSystemConfigDataStru;               /*����CBTCϵͳ������������Ϣ�ṹ*/
extern LocalZcConfigDataStruct gLocalZcConfigDataStru;             /*���ñ���ZC�������ݽṹ��Ϣ*/

/*
* ���������� ��ʼ��ϵͳ������Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
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
		/*��ʼ��ϵͳ��������*/
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
* ���������� ��ʼ��ϵͳ������Ϣ���г���Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
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

	/*��ʼ���г�����*/
	pBnfTrainTypeConfigStru = GetTrainTypeConfigDataInfo(&trainTypeNum);

	if ((NULL != pBnfTrainTypeConfigStru)
		&& (DEFAULT_ZERO != trainTypeNum))
	{
		for (cycle = DEFAULT_ZERO;cycle < trainTypeNum;cycle++)
		{
			/*��ȡ�г�Id*/
			trainId = (UINT16_S)(pBnfTrainTypeConfigStru[cycle].trainDevName & ((UINT16_S)0x00ffU));

			if (LINE_MAX_TRAIN_ID > trainId)
			{
				gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].TrainID = trainId;
				gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].TrainType = pBnfTrainTypeConfigStru[cycle].trainType;
			
				/*���ݳ�����Ϣ��ȡ�г�������Ϣ*/
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

                        /* ����󳵳���ֵ */
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
			/*������*/
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ʼ��ZC��ϵͳ������Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
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

		/*��ȡNTP�������*/
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
* ���������� ��ʼ������ZCId������Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
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
	
	getZcId = GetPrivateProfileInt(L"����������Ϣ",L"����ID",0xFF,L"ini\\ZcLocalConfig.ini");
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
	/* ������ƽ̨ */
	CSPADPT_Get_SpeciConfig_Addr_Size(ENUM_CONFIG_DAT_TYPE_CIID, (UINT8*)(&l_Addr), &l_Size);
	
	l_Result = GM_Ini_File_Read_Int("CI_GLOBAL", "localCiId", &l_value, (char*)l_Addr);
	
	if ((GM_TRUE == l_Result) && (l_value > 0))
	{
		gLocalZcConfigDataStru.wZCID = (UINT16_S)(l_value);
		printf("ZcId:%d\n",gLocalZcConfigDataStru.wZCID);
	    rtnValue = RETURN_SUCCESS;
	}
	#else
	/*�򿪶������ļ�*/
	tempRetVal = AdptAppFileOpen(ZC_ID_CONFIG_DATA,0U,&pfile);

	/*�жϴ򿪶������ļ��Ƿ�ɹ�*/
	if (1U == tempRetVal)
	{
		retVal = AdptAppFileRead(pfile,ZC_ID_CONFIG_DATA,dataBuff,((UINT32_S)(sizeof(dataBuff))));
		if(0U != retVal)
		{
			/*��ȡ�ɹ�������ִ��*/
			gLocalZcConfigDataStru.wZCID = (UINT16_S)(((UINT16_S)dataBuff[0]) & ((UINT16_S)0x00ffU));
			printf("ZcId:%d\n",gLocalZcConfigDataStru.wZCID);
			rtnValue = RETURN_SUCCESS;
		}
		else
		{
			/*��¼�ļ���ȡʧ�ܵĴ���*/
			rtnValue = RETURN_ERROR;
		}
		AdptAppFileClose(pfile);
	}
	else
	{
		/*�򿪶������ļ�ʧ��*/
		rtnValue = RETURN_ERROR;
	}
	#endif
	#endif

	return rtnValue;
}

/*
* ���������� ��ʼ������Ntp������Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
*/
void InitLocalNtpConfigData(void)
{
	InitSysTimeData();
}
