/************************************************************************
*
* 文件名   ：  MaskInitManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  码位初始化管理
* 备  注   ：  无
*
************************************************************************/
#ifndef MASK_INIT_MANAGER_H_
#define MASK_INIT_MANAGER_H_


#include "MaskDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 初始化本地管理的码位信息中的基础信息
	* 参数说明： 无   
	* 返回值  ： 无      
	*/
	void InitMaskValueData(void);

	/*
	* 功能描述： 获取设备所属的联锁ID
	* 参数说明： const UINT16 devId, 设备ID
	*            const UINT8_S devType,设备类型
	* 返回值  ： 0: 获取失败
	*			>0: 所属CIID      
	*/
	UINT16_S GetLineDeviceBelongCiId(const UINT16_S devId,const UINT8_S devType);

	/*
	* 功能描述： 初始化本地管理的码位信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcCiMaskLocalInfo(void);

	/*
	* 功能描述： 初始化码位配置信息中通讯对象
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			 1: 初始化成功      
	*/
	UINT8_S InitZcCiMaskConfigCommTargetData(void);

	/*
	* 功能描述： 初始化本地管理的发送给CI系统的码位信息
	* 参数说明： UINT16 maskId;码位ID
	*            UINT8_S maskType;码位类型
	*            UINT16_S devId;设备ID
	*            UINT8_S devType;设备类型
	*            UINT16_S relevanceMaskId;关联码位ID
	* 返回值  ： 0: 初始化失败
	*			 1: 初始化成功      
	*/
	UINT8_S InitSendToCiMaskInfo(UINT16_S maskId,UINT8_S maskType,UINT16_S devId,UINT8_S devType,UINT16_S relevanceMaskId);

	/*
	* 功能描述： 初始化本地管理的接受CI输入ZC系统的码位信息
	* 参数说明： UINT16 maskId;码位ID
	*            UINT8_S maskType;码位类型
	*            UINT16_S devId;设备ID
	*            UINT8_S devType;设备类型
	*            UINT16_S relevanceMaskId;关联码位ID
	* 返回值  ： 0: 初始化失败
	*			 1: 初始化成功      
	*/
	UINT8_S InitReceiveToCiMaskInfo(UINT16_S maskId,UINT8_S maskType,UINT16_S devId,UINT8_S devType,UINT16_S relevanceMaskId);

	/*
	* 功能描述： 初始化本地管理的道岔码位信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcCiMaskOfSwitchInfo(void);

	/*
	* 功能描述： 初始化本地管理的信号机码位信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcCiMaskOfSignalInfo(void);

	/*
	* 功能描述： 初始化本地管理的屏蔽门码位信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcCiMaskOfPsdInfo(void);

	/*
	* 功能描述： 初始化本地管理的紧急停车按钮码位信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcCiMaskOfEsbInfo(void);

	/*
	* 功能描述： 初始化本地管理的计轴区段码位信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcCiMaskOfAcInfo(void);

	/*
	* 功能描述： 初始化本地管理的逻辑区段码位信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcCiMaskOfSectionInfo(void);

	/*
	* 功能描述： 初始化本地管理的进路码位信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcCiMaskOfRouteInfo(void);

	/*
	* 功能描述： 初始化本地管理的保护区段码位信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcCiMaskOfOverlapInfo(void);

	/*
	* 功能描述： 初始化本地管理的无人折返码位信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitZcCiMaskOfDrInfo(void);

	/*
	* 功能描述： 初始化信号机跨压信息
	* 参数说明： const UINT16 signalId,信号机ID 
	*            const UINT16_S maskId,码位值
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitSignalCrossInfo(const UINT16_S signalId,const UINT16_S maskId);

	/*
	* 功能描述： 初始化信号机亮灭信息
	* 参数说明： const UINT16 signalId,信号机ID 
	*            const UINT16_S maskId,码位值
	* 返回值  ： 0: 初始化失败
	*			>0: 初始化成功      
	*/
	UINT8_S InitSignalLightOffInfo(const UINT16_S signalId,const UINT16_S maskId);

#ifdef __cplusplus
}
#endif

#endif
