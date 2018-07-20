/************************************************************************
*
* 文件名   ：  SysConfigData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  获取ZC系统配置数据管理
* 备  注   ：  无
*
************************************************************************/
#include "SysConfigData.h"

ZcSubsystemConfigDataStruct gZcSubsystemConfigDataStru;     /*定义ZC子系统的配置数据信息结构*/
SystemConfigDataStruct gSystemConfigDataStru;               /*定义CBTC系统的配置数据信息结构*/
LocalZcConfigDataStruct gLocalZcConfigDataStru;             /*定义本地ZC配置数据结构信息*/

/*
* 功能描述： 获取本地ZC的id
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 本地ZCid      
*/
UINT16_S GetLocalZcId(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gLocalZcConfigDataStru.wZCID >= LINE_ZC_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gLocalZcConfigDataStru.wZCID;
	}

	return rtnValue;
}

/*
* 功能描述： 获取运营的信号机亮灭灯需要的长度
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 运营的信号机亮灭灯需要的长度      
*/
UINT32_S GetSignalLightLength(void)
{
	return gZcSubsystemConfigDataStru.SignalLightLength;
}

/*
* 功能描述： 获取线路最小可能车长
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 线路最小可能车长      
*/
UINT16_S GetLineMinTrainLength(void)
{
	return gZcSubsystemConfigDataStru.LineMinTrainLength;
}

/*
* 功能描述： 获取列车最大退行防护距离
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 列车最大退行防护距离      
*/
UINT16_S GetRetreatProtectDistance(void)
{
	return gZcSubsystemConfigDataStru.RetreatProtectDistance;
}

/*
* 功能描述： 获取区段冗余判断周期数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 区段冗余判断周期数     
*/
UINT16_S GetSectionRedundantCycle(void)
{
    UINT16_S rtnValue = 0U;

    rtnValue = (UINT16_S)gZcSubsystemConfigDataStru.SectionRedundantCycle;

	return rtnValue;
}

/*
* 功能描述： 获取NTP校时时区差
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: NTP校时时区差     
*/
UINT8_S GetNtpTimeZoneDiff(void)
{
	return gSystemConfigDataStru.NtpTimeZoneDiff;
}

/*
* 功能描述： 获取ZC向ATS汇报列车占用区段信息的周期数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: ZC向ATS汇报列车占用区段信息的周期数     
*/
UINT8_S GetZCToATSCycleCycle(void)
{
	return gZcSubsystemConfigDataStru.ZCToATSCycleCycle;
}

/*
* 功能描述： 获取列车CBTC折返周期数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 列车CBTC折返周期数    
*/
UINT8_S GetReverseCycle(void)
{
	return gZcSubsystemConfigDataStru.ReverseCycle;
}

/*
* 功能描述： 获取ZC是否需要宕机标志
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: ZC是否需要宕机标志    
*/
UINT8_S GetZCDowntimeFlag(void)
{
	return gZcSubsystemConfigDataStru.ZCDowntimeFlag;
}

/*
* 功能描述： 获取发送给CI的逻辑区段占用码位类型
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 发送给CI的逻辑区段占用码位类型    
*/
UINT8_S GetToCiSectionType(void)
{
	return gZcSubsystemConfigDataStru.ToCiSectionType;
}
/*
* 功能描述： 获取列车跨压信号机判断距离
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 列车跨压信号机判断距离   
*/
UINT16_S GetTrainAcrossSignalDis(void)
{
	return gZcSubsystemConfigDataStru.TrainAcrossSignalDis;
}

/*
* 功能描述： 获取NTP校时误差时间
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: NTP校时误差时间   
*/
UINT32_S GetNtpCheckDiffTime(void)
{
	return gZcSubsystemConfigDataStru.NtpCheckDiffTime;
}

/*
* 功能描述： 获取校时周期
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 校时周期   
*/
UINT16_S GetSendNtpApplyCycle(void)
{
	return gZcSubsystemConfigDataStru.SendNtpApplyCycle;
}

/*
* 功能描述： 获取系统最小保护区段长度
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 系统最小保护区段长度   
*/
UINT16_S GetLineMinOverlapLength(void)
{
	return gSystemConfigDataStru.LineMinOverlapLength;
}

/*
* 功能描述： 获取系线路最高限速
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 线路最高限速   
*/
UINT16_S GetLineMaxSpeed(void)
{
	return gSystemConfigDataStru.LineMaxSpeed;
}

/*
* 功能描述： 获取临时限速最高限速
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 临时限速最高限速   
*/
UINT16_S GetLineMaxTSRSpeed(void)
{
	return gSystemConfigDataStru.LineMaxTSRSpeed;
}

/*
* 功能描述： 获取安全防护距离
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 安全防护距离   
*/
UINT16_S GetLineMaBackDistance(void)
{
	return gSystemConfigDataStru.LineMaBackDistance;
}

/*
* 功能描述： 获取与车载ATP通信故障周期数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 与车载ATP通信故障周期数   
*/
UINT8_S GetTrainAtpCommCycle(void)
{
	return gSystemConfigDataStru.TrainAtpCommCycle;
}

/*
* 功能描述： 获取与相邻ZC通信故障周期数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 与相邻ZC通信故障周期数  
*/
UINT8_S GetNZcCommCycle(void)
{
	return gSystemConfigDataStru.NZcCommCycle;
}

/*
* 功能描述： 获取与CI通信故障周期数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 与CI通信故障周期数   
*/
UINT8_S GetCICommCycle(void)
{
	return gSystemConfigDataStru.CICommCycle;
}

/*
* 功能描述： 获取与ATS通信故障周期数
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 与ATS通信故障周期数   
*/
UINT8_S GetATSCommCycle(void)
{
	return gSystemConfigDataStru.ATSCommCycle;
}

/*
* 功能描述： 获取ZC内部逻辑方向与CI上下行方向之间的关系
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: ZC内部逻辑方向与CI上下行方向之间的关系   
*/
UINT8_S GetLinkLogicDirUpAndDown(void)
{
	return gSystemConfigDataStru.LinkLogicDirUpAndDown;
}

/*
* 功能描述： 获取指定ZcId对应的列车类型
* 参数说明： const UINT16 trainId 列车Id    
* 返回值  ： 0: 获取数据失败
*			>0: 列车类型   
*/
UINT16_S GetLineTrainType(const UINT16_S trainId)
{
	UINT16_S rtnvalue = DEFAULT_ZERO;

	if ((trainId >= 1U)&&(trainId < LINE_MAX_TRAIN_ID))
	{
		rtnvalue = gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].TrainType;
	}
	else
	{
		rtnvalue = RETURN_ERROR;
	}

	return rtnvalue;
}

/*
* 功能描述： 获取指定ZcId对应的列车车长
* 参数说明： const UINT16 trainId 列车Id    
* 返回值  ： 0: 获取数据失败
*			>0: 列车车长   
*/
UINT16_S GetTrainLength(const UINT16_S trainId)
{
	UINT16_S rtnvalue = DEFAULT_ZERO;

	if ((trainId >= 1U)&&(trainId < LINE_MAX_TRAIN_ID))
	{
		rtnvalue = gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].TrainLength;
	}
	else
	{
		rtnvalue = RETURN_ERROR;
	}

	return rtnvalue;
}

/*
* 功能描述： 获取指定ZcId对应的列车线路最大下坡坡度
* 参数说明： const UINT16 trainId 列车Id    
* 返回值  ： 0: 获取数据失败
*			>0: 列车线路最大下坡坡度   
*/
UINT16_S GetMaxLineDeclGradient(const UINT16_S trainId)
{
	UINT16_S rtnvalue = DEFAULT_ZERO;

	if ((trainId >= 1U)&&(trainId < LINE_MAX_TRAIN_ID))
	{
		rtnvalue = gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].MaxLineDeclGradient;
	}
	else
	{
		rtnvalue = RETURN_ERROR;
	}

	return rtnvalue;
}

/*
* 功能描述： 获取指定ZcId对应的列车最大牵引加速度
* 参数说明： const UINT16 trainId 列车Id    
* 返回值  ： 0: 获取数据失败
*			>0: 列车最大牵引加速度  
*/
UINT16_S GetMaxTrainTractionAcc(const UINT16_S trainId)
{
	UINT16_S rtnvalue = DEFAULT_ZERO;

	if ((trainId >= 1U)&&(trainId < LINE_MAX_TRAIN_ID))
	{
		rtnvalue = gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].MaxTrainTractionAcc;
	}
	else
	{
		rtnvalue = RETURN_ERROR;
	}

	return rtnvalue;
}

/*
* 功能描述： 追踪不带后方检查标记RM列车方式
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*			<UINT8_NULL: 追踪不带后方检查标记RM列车方式
*/ 
UINT8_S GetZcTraceRmTrainType(void)
{
	return gZcSubsystemConfigDataStru.ZcTraceRmTrainType;
}

/*
* 功能描述： 获取线路上最大车长
* 参数说明:  无
* 返回值  :  >0 线路列车最大长度
*/ 
UINT16_S GetLineMaxTrainLength(void)
{
    return gZcSubsystemConfigDataStru.LineMaxTrainLength;
}

/*
* 功能描述： 设置线路上最大车长
* 参数说明:  const UINT16_S trainMaxLen  线路列车最大长度
* 返回值  :  无
*/ 
void SetLineMaxTrainLength(const UINT16_S trainMaxLen)
{
    if ((DEFAULT_ZERO != trainMaxLen)
        && (UINT16_MAX != trainMaxLen))
    {
        gZcSubsystemConfigDataStru.LineMaxTrainLength = trainMaxLen;
    }  
}
