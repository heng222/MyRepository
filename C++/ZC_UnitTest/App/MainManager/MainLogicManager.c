/************************************************************************
*
* 文件名   ：  MainLogicManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  应用函数主逻辑处理
* 备  注   ：  无
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
* 功能描述： ZC子系统应用程序入口函数
* 参数说明： 无
* 返回值  ： 1:逻辑执行正常
*            0:逻辑执行异常
*/
INT8_S ZcSystemAppMain(void)/*-bye-*/
{
	INT8_S rtnValue = 0;
	UINT8_S rtnZcRetValue = 0U;
    UINT32_S timeBuff[6] = {0u};


	/*通信状态维护*/
	ManagerCommTargetCommCycle();

	/*解析输入信息*/
    ParseInputData();
	
	/*处理输入信息*/
	InputDataProcess();

	/*输入查询函数道岔信息*/
	SetDmuSwitchStatusInfo();

	/*判断ZC应用上电标记是否取消*/
	rtnZcRetValue = TsrIFGetZcWorkState();
	if (ZC_RESET_STATUS_FLAG_UNSET == rtnZcRetValue)
	{
		/*处理ZC应用主逻辑*/
        if(RETURN_SUCCESS == ZcAppMainLogicManager())
        {
			rtnValue = SIGNED_RETURN_SUCCESS;
        }
		
		/*输出信息处理*/
		OutputDataProcess();

		/*输出信息组织*/
		PackOutputData();
	} 
	else
	{
		/*处理ZC输出ATS的数据*/
        AtsOutputDataProcess();
		/*组帧输出给ATS的数据*/
	    PackZcToAtsData();

		if (ZC_INIT_NTP_TIME_SUCC_FLAG_UNSET == GetNtpTimeSuccFlag())
		{
			/*输出给NTP数据处理*/
			NtpOutputDataProcess();
			/*输出给NTP数据组织*/
			PackZcToNtpData();
		}     
		
		rtnValue = SIGNED_RETURN_SUCCESS;
	}
	
    /*日志信息*/
    PrintfZcMaintainInfo();

	/*每五个周期对ZC内部时间增加2s*/
	AddLocalTime();

	/*累加ZC周期*/
	AddZcCycle();
#ifdef SYS_TYPE_VXWORKS	
	Seconds2Calendar(GetLocalNtpTime(),timeBuff);
		
	LogPrintf(1U,"\n%d-%d-%d-%d-%d-%d\n",timeBuff[0],timeBuff[1],timeBuff[2],timeBuff[3],timeBuff[4],timeBuff[5]);
#endif 	
	return rtnValue;
}

/*
* 功能描述： ZC子系统应用程序主逻辑管理
* 参数说明： 无
* 返回值  ： 1:逻辑执行正常
*            0:逻辑执行异常
*/
UINT8_S ZcAppMainLogicManager(void)
{    
	UINT8_S rtnValue = DEFAULT_ZERO;
    /*
    UINT16_S trainSectionOfAcBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
    CheckLogicIdBetweenPoints(3U,232,10000,
        26,2600,85,trainSectionOfAcBuff);
   */
	/*列车类型转换*/
	ManageTrainTypeTransform();

	/*列车安全位置计算*/
	CalculateTrainSafePos();

	/*计算列车位置占压计轴区段信息*/
	CalulateTrainLocToAcInfo();

	/*通信状态处理*/
	ManageCommTargetCommStatus();

	/*通信故障处理*/
	ManageCommTargetCommFailure();

	/*信号机亮灭控制*/
	SignalControl();

	/*列车闯红灯信号机判断*/
	TrainCrashSignal();

	/*列车排序*/
	CalculateTrainOrderInAc();

	/*清扫计轴状态处理*/
	AcCleanStatusProcess();

	/*计轴区段ARB处理*/
	JudgeAxleARB();

	/*计轴区段非通信列车占用处理*/
	JudgeAxleUT();

	/*处理ARB计轴转为非通信列车占用处理*/
	/* ConvertAlexArbToUt(); */

	/*计轴区段非通信列车占用处理*/
	/* ProcessAcUnCommTrainOccState(); */
    
	/*列车前后方危险源处理*/  
	ManageTrainDangerousSource();

	/*列车进路匹配*/
	CalculateCommTrainMatchingRoute();	

	/*列车切换区域匹配*/
	JudgeTrainChangeId();

	/*列车状态转换信息*/
	ManageTrainStatusTransform();

	/*列车输出状态信息*/
	ManageOutTrainType();

	/*列车相邻ZC输出状态信息*/
	ManageNZcOutTrainType();

	/*列车移动授权信息管理*/
	ManageTrainMaInfo();

	/*需要删除列车信息处理函数*/
	/* ManageDeleteTrainInfo(); */

    /*信号机CBTC级别列车跨压管理*/
    TrainAcrossSingalManager();

	/*逻辑区段占用状态更新*/
	UpdataLogicSectionManager();

	/*列车占压逻辑区段校核*/
	rtnValue = JudgeTrainLogicContinuity();

    /*需要删除列车信息处理函数*/
    ManageDeleteTrainInfo();

	return rtnValue;
}
