/************************************************************************
*
* �ļ���   ��  MainLogicManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  Ӧ�ú������߼�����
* ��  ע   ��  ��
*
************************************************************************/
#include "MainLogicManager.h"
#include "../IOManager/CommTarget/CommTargetLogicManager.h"
#include "../IOManager/ParseIOData/ParsePackProcessManager.h"
#include "../IOManager/IODataProcess/InputDataProcess.h"
#include "../SysDataManager/SysStatusData.h"
#include "../IOManager/IODataProcess/OutputDataProcess.h"
#include "../TrainManager/Train/TrainLogicManager.h"
#include "../TrainManager/MA/MALogicManager.h"
#include "../LineDataManager/AC/ACLogicManager.h"
#include "../LineDataManager/Signal/SignalLogicManager.h"
#include "../LineDataManager/Switch/SwitchLogicManager.h"
#include "../MaintainManager/MaintainManager.h"
#include "../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../LineDataManager/LogicSection/LogicSectionLogicManager.h"
#include "../TrainManager/Train/TrainStatusData.h"
#include "../MaintainManager/ZcMaintainManager.h"
#include "../LineDataManager/AC/ACConfigData.h"
#include "../SysDataManager/SysTimeData.h"
#include "../IOManager/ParseIOData/ParsePackNtpData.h"
#include "../LineDataManager/Change/ChangeConfigData.h"
#include "../LineDataManager/Tsr/TsrLogicManager.h"
#include "../TsrManager/TsrInterface.h"/*-bye-*/
#ifdef SYS_TYPE_VXWORKS
#include "../../PlatformAdapter/AppItf/AdptAppServiceInterface.h"
#endif
/*
* ���������� ZC��ϵͳӦ�ó�����ں���
* ����˵���� ��
* ����ֵ  �� 1:�߼�ִ������
*            0:�߼�ִ���쳣
*/
INT8_S ZcSystemAppMain(void)/*-bye-*/
{
	INT8_S rtnValue = 0;
	UINT8_S rtnZcRetValue = 0U;
    UINT32_S timeBuff[6] = {0u};


	/*ͨ��״̬ά��*/
	ManagerCommTargetCommCycle();

	/*����������Ϣ*/
    ParseInputData();
	
	/*����������Ϣ*/
	InputDataProcess();

	/*�����ѯ����������Ϣ*/
	SetDmuSwitchStatusInfo();

	/*�ж�ZCӦ���ϵ����Ƿ�ȡ��*/
	rtnZcRetValue = TsrIFGetZcWorkState();
	if (ZC_RESET_STATUS_FLAG_UNSET == rtnZcRetValue)
	{
		/*����ZCӦ�����߼�*/
        if(RETURN_SUCCESS == ZcAppMainLogicManager())
        {
			rtnValue = SIGNED_RETURN_SUCCESS;
        }
		
		/*�����Ϣ����*/
		OutputDataProcess();

		/*�����Ϣ��֯*/
		PackOutputData();
	} 
	else
	{
		/*����ZC���ATS������*/
        AtsOutputDataProcess();
		/*��֡�����ATS������*/
	    PackZcToAtsData();

		if (ZC_INIT_NTP_TIME_SUCC_FLAG_UNSET == GetNtpTimeSuccFlag())
		{
			/*�����NTP���ݴ���*/
			NtpOutputDataProcess();
			/*�����NTP������֯*/
			PackZcToNtpData();
		}     
		
		rtnValue = SIGNED_RETURN_SUCCESS;
	}
	
    /*��־��Ϣ*/
    PrintfZcMaintainInfo();

	/*ÿ������ڶ�ZC�ڲ�ʱ������2s*/
	AddLocalTime();

	/*�ۼ�ZC����*/
	AddZcCycle();
#ifdef SYS_TYPE_VXWORKS	
	Seconds2Calendar(GetLocalNtpTime(),timeBuff);
		
	LogPrintf(1U,"\n%d-%d-%d-%d-%d-%d\n",timeBuff[0],timeBuff[1],timeBuff[2],timeBuff[3],timeBuff[4],timeBuff[5]);
#endif 	
	return rtnValue;
}

/*
* ���������� ZC��ϵͳӦ�ó������߼�����
* ����˵���� ��
* ����ֵ  �� 1:�߼�ִ������
*            0:�߼�ִ���쳣
*/
UINT8_S ZcAppMainLogicManager(void)
{    
	UINT8_S rtnValue = DEFAULT_ZERO;
    /*
    UINT16_S trainSectionOfAcBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
    CheckLogicIdBetweenPoints(3U,232,10000,
        26,2600,85,trainSectionOfAcBuff);
   */
	/*�г�����ת��*/
	ManageTrainTypeTransform();

	/*�г���ȫλ�ü���*/
	CalculateTrainSafePos();

	/*�����г�λ��ռѹ����������Ϣ*/
	CalulateTrainLocToAcInfo();

	/*ͨ��״̬����*/
	ManageCommTargetCommStatus();

	/*ͨ�Ź��ϴ���*/
	ManageCommTargetCommFailure();

	/*�źŻ��������*/
	SignalControl();

	/*�г�������źŻ��ж�*/
	TrainCrashSignal();

	/*�г�����*/
	CalculateTrainOrderInAc();

	/*��ɨ����״̬����*/
	AcCleanStatusProcess();

	/*��������ARB����*/
	JudgeAxleARB();

	/*�������η�ͨ���г�ռ�ô���*/
	JudgeAxleUT();

	/*����ARB����תΪ��ͨ���г�ռ�ô���*/
	/* ConvertAlexArbToUt(); */

	/*�������η�ͨ���г�ռ�ô���*/
	/* ProcessAcUnCommTrainOccState(); */
    
	/*�г�ǰ��Σ��Դ����*/  
	ManageTrainDangerousSource();

	/*�г���·ƥ��*/
	CalculateCommTrainMatchingRoute();	

	/*�г��л�����ƥ��*/
	JudgeTrainChangeId();

	/*�г�״̬ת����Ϣ*/
	ManageTrainStatusTransform();

	/*�г����״̬��Ϣ*/
	ManageOutTrainType();

	/*�г�����ZC���״̬��Ϣ*/
	ManageNZcOutTrainType();

	/*�г��ƶ���Ȩ��Ϣ����*/
	ManageTrainMaInfo();

	/*��Ҫɾ���г���Ϣ������*/
	/* ManageDeleteTrainInfo(); */

    /*�źŻ�CBTC�����г���ѹ����*/
    TrainAcrossSingalManager();

	/*�߼�����ռ��״̬����*/
	UpdataLogicSectionManager();

	/*�г�ռѹ�߼�����У��*/
	rtnValue = JudgeTrainLogicContinuity();

    /*��Ҫɾ���г���Ϣ������*/
    ManageDeleteTrainInfo();

	return rtnValue;
}
