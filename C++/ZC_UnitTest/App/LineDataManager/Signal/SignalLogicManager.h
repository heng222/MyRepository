/************************************************************************
*
* 文件名   ：  SignalLogicManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  维护管理
* 备  注   ：  无
*
************************************************************************/
#ifndef SIGNAL_LOGIC_MANAGER_DATA_H_
#define SIGNAL_LOGIC_MANAGER_DATA_H_

#include "SignalDefine.h"
#include "../../../Common/CommonTypes.h"
#include "../../SysDataManager/SysConfigData.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*
	* 功能描述： 处理通信故障Ci对应的单个信号机信息
	* 参数说明： const UINT16 signalId，信号机ID    
	* 返回值  ： void  
	*/
	void InitFailureSingleSignal(const UINT16_S signalId);

	/*
	* 功能描述： 处理通信故障Ci对应的信号机信息
	* 参数说明： const UINT16 ciId，联锁ID    
	* 返回值  ： void  
	*/
	void InitFailureCiSignal(const UINT16_S ciId);

	/*
	* 功能描述： 处理通信故障NZc对应的信号机信息
	* 参数说明： const UINT16 nZCId    
	* 返回值  ： void  
	*/
	void InitFailureNZcSignal(const UINT16_S nZCId);

	/*
	* 功能描述： 信号机亮灭控制
	* 参数说明： void
	* 返回值  ： void     
	*/
	void SignalControl(void);

	/*
	* 功能描述： 信号机亮灭命令处理
	* 参数说明： UINT16 signalId,信号机Id
	* 返回值  ： void      
	*/
	void SignalLightAndOffDeal(UINT16_S signalId);

	/*
	* 功能描述： 计算信号机亮灭命令处理时的计轴区段序列
	* 参数说明： const UINT16 signalId,信号机Id
	*            UINT8_S *acNum,计轴区段数量
	*            UINT16_S acIdBuff[],计轴区段ID缓存
	* 返回值  ： 0: 计算失败
	*			 1: 计算成功      
	*/
	UINT8_S CalculateAcOfSignalLighten(const UINT16_S signalId,UINT8_S *acNum,UINT16_S acIdBuff[]);

	/*
	* 功能描述： 列车闯信号判断
	* 参数说明： 无
	* 返回值  ： 无     
	*/
	void TrainCrashSignal(void);

	/*
	* 功能描述： 处理列车跨压信号机状态
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void TrainAcrossSingalManager(void);

	/*
	* 功能描述： 单个列车跨压信号机状态处理
	* 参数说明： UINT16 signalId,信号机Id
	* 返回值  ： 0: 处理失败
	*			 1: 处理成功      
	*/
	UINT8_S JudgeTrainAcrossOfSingalSignal(const UINT16_S signalId);

	/*
	* 功能描述： 判断列车位置是否满足该信号机的待判跨压
	* 参数说明： UINT16 signalId,信号机Id
	*            const UINT8_S trainId,列车Id
	* 返回值  ： 0: 处理失败
	*			 1: 处理成功      
	*/
	UINT8_S JudgeTrainNeedSingalLoc(const UINT16_S signalId, const UINT16_S trainId);

#ifdef __cplusplus
}
#endif

#endif
