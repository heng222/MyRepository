/************************************************************************
*
* 文件名   ：  MaskConfigData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  码位配置数据
* 备  注   ：  无
*
************************************************************************/
#ifndef MASK_CONFIG_DATA_H_
#define MASK_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "MaskDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*码位信息数据结构体*/
	typedef struct MaskConfigDataStruct
	{
		UINT16_S MaskId;                                   /*码位ID*/
		UINT8_S MaskType;                                  /*码位类型*/
		UINT8_S DeviceType;                                /*码位对应的设备类型*/
		UINT8_S DeviceSum;                                 /*码位对应的设备数量*/
		UINT16_S DeviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX];  /*码位对应的设备IdBuff*/
		UINT16_S RelevanceMaskId;                          /*码位关联的码位id*/
	} MaskConfigDataStruct;

	typedef struct ZcCiMaskConfigDataStruct
	{
		UINT16_S CommCiId;                   /*通讯联锁ID*/
		UINT16_S MaskCurSum;                 /*目前码位总数*/
		UINT16_S MaskIdMax;                  /*码位ID的最大值*/
		UINT16_S MaskIdBuff[ZC_TO_CI_MASK_SUM_MAX];                                /*码位ID的数组*/
		MaskConfigDataStruct MaskConfigDataStru[SINGLE_ZC_TO_CI_MASK_SUM_MAX];  /*码位信息数据结构体数组*/
	}ZcCiMaskConfigDataStruct;

	/*
	* 功能描述： 获取输出设备总个数
	* 参数说明： const UINT8 destSystemType 目标系统类型  
	* 返回值  ： 0: 获取数据失败
	*			>0: 设备当前总数
	*/
	UINT8_S GetSendCommTargetNum(const UINT8_S destSystemType);

	/*
	* 功能描述： 获取某个设备对应的总数
	* 参数说明： const UINT8 destSystemType 目标系统类型  
	*			 const UINT16_S destSystemId 目标ID
	* 返回值  ： 0: 获取数据失败
	*			>0: 码位信息当前总数
	*/
	UINT8_S GetSendCommTargetIndex(const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* 功能描述： 获取码位信息管理总数
	* 参数说明： const UINT8 destSystemType 目标系统类型
	*			 const UINT16_S destSystemId 目标系统Id
	* 返回值  ： 0: 获取数据失败
	*			>0: 码位信息当前总数
	*/
	UINT16_S GetSendToOtherMaskSum(const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* 功能描述： 获取码位ID最大值
	* 参数说明： const UINT8 destSystemType 目标系统类型 
	*			 const UINT16_S destSystemId 目标系统Id
	* 返回值  ： 0: 获取数据失败
	*			>0: 码位ID最大值
	*/
	UINT16_S GetSendToOtherMaskIdMax(const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* 功能描述： 获取指定ZC接收指定系统码位总数
	* 参数说明： const UINT8 sourceSystemType, 源系统类型
	*			 const UINT16_S sourceSystemId 源系统ID
	* 返回值  ： 0: 获取数据失败
	*			>0: 码位总数      
	*/
	UINT16_S GetReceiveToZcMaskSum(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* 功能描述： 获取码位ID最大值
	* 参数说明： const UINT8 sourceSystemType, 源系统类型   
	*			 const UINT16_S sourceSystemId 源系统ID
	* 返回值  ： 0: 获取数据失败
	*			>0: 码位ID最大值
	*/
	UINT16_S GetReceiveToZcMaskIdMax(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* 功能描述： 获取发送给其他子系统指定数组下标对应的码位下标
	* 参数说明： const UINT16 bufIndex, 数组下标
	*			 const UINT8_S destSystemType, 目标系统类型
	*			 const UINT16_S destSystemId, 目标系统ID
	* 返回值  ： 0: 获取数据失败
	*			>0: 码位下标     
	*/
	UINT16_S GetSendMaskId(const UINT16_S bufIndex,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* 功能描述： 获取指定ID码位索引号
	* 参数说明： const UINT16 maskId,码位ID
	*			 const UINT8_S destSystemType, 目标系统类型
	*		     const UINT16_S destSystemId 目标系统Id
	* 返回值  ： ZC_TO_CI_MASK_SUM_MAX; 获取数据失败
	*			 >=0;查找索引成功
	*/
	UINT16_S GetSendMaskBufIndex(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* 功能描述： 获取指定ID码位的码位类型
	* 参数说明： const UINT16 maskId,码位ID
	*			 const UINT8_S destSystemType, 目标系统类型
	*			 const UINT16_S destSystemId 目标系统Id
	* 返回值  ： 0 : 获取数据失败
	*			 >0; 码位类型信息
	*/
	UINT8_S GetSendMaskType(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* 功能描述： 获取指定ID码位的设备类型
	* 参数说明： const UINT16 maskId,码位ID
	*			 const UINT8_S destSystemType, 目标系统类型
	*			 const UINT16_S destSystemId 目标系统Id
	* 返回值  ： 0: 获取数据失败
	*			 >0 设备类型信息
	*/
	UINT8_S GetSendDeviceType(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* 功能描述： 获取指定ID码位的设备数量
	* 参数说明： const UINT16 maskId,码位ID
	*				const UINT8_S destSystemType, 目标系统类型
	*				const UINT16_S destSystemId 目标系统Id
	* 返回值  ： 0: 获取数据失败
	*			 >0 设备数量
	*/
	UINT8_S GetSendDeviceSum(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* 功能描述： 获取指定ID码位的设备ID数组
	* 参数说明： const UINT16 maskId,码位ID
	*		     const UINT8_S destSystemType, 目标系统类型
	*			 const UINT16_S destSystemId 目标系统Id
	*			 const UINT8_S bufSize,数组大小
	*			 UINT16_S deviceIdBuff[],输出数组
	* 返回值  ： 0: 获取数据失败
	*			 1: 成功
	*/
	UINT8_S GetSendDeviceIdBuff(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId,const UINT8_S bufSize,UINT16_S deviceIdBuff[]);

	/*
	* 功能描述： 获取指定ID码位的关联码位Id
	* 参数说明： const UINT16 maskId,码位ID
	*			 const UINT8_S destSystemType, 目标系统类型
	*			 const UINT16_S destSystemId 目标系统Id
	* 返回值  ： 0: 获取数据失败
	*			 >0 关联码位ID
	*/
	UINT16_S GetSendRelevanceMaskId(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId);

	/*
	* 功能描述： 获取输入设备总个数
	* 参数说明： const UINT8 sourceSystemId 源系统类型  
	* 返回值  ： 0: 获取数据失败
	*			>0: 设备当前总数
	*/
	UINT8_S GetReceiveCommTargetNum(const UINT8_S sourceSystemId);

	/*
	* 功能描述： 获取接受某个设备的下标
	* 参数说明： const UINT8 sourceSystemType 源系统类型  
	*			 const UINT16_S sourceSystemId 源目标ID
	* 返回值  ： COMM_CI_SUM_MAX: 获取数据失败
	*			>0: 通讯对象的下标
	*/
	UINT8_S GetReceiveCommTargetIndex(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* 功能描述： 获取指定接受数组下标对应的码位下标
	* 参数说明： const UINT16 bufIndex, 数组下标
	*			 const UINT8_S sourceSystemType, 源系统类型
	*			 const UINT16_S sourceSystemId 源系统ID
	* 返回值  ： 0: 获取数据失败
	*			>0: 码位ID     
	*/
	UINT16_S GetReceiveMaskId(const UINT16_S bufIndex,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* 功能描述： 获取指定ID码位索引号
	* 参数说明： const UINT16 maskId,码位ID
	*			 const UINT8_S sourceSystemType, 源系统类型
	*			 const UINT16_S sourceSystemId 源系统ID
	* 返回值  ： CI_TO_ZC_MASK_SUM_MAX: 获取数据失败
	*			 >0 查找索引成功
	*/
	UINT16_S GetReceiveMaskBufIndex(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* 功能描述： 获取指定ID码位的码位类型
	* 参数说明： const UINT16 maskId,码位ID
	*			const UINT8_S sourceSystemType, 源系统类型
	*			const UINT16_S sourceSystemId 源系统ID
	* 返回值  ： 0: 获取数据失败
	*			 >0 码位类型信息
	*/
	UINT8_S GetReceiveMaskType(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* 功能描述： 获取指定ID码位的设备类型
	* 参数说明： const UINT16 maskId,码位ID
	*			 const UINT8_S sourceSystemType, 源系统类型
	*			 const UINT16_S sourceSystemId 源系统ID
	* 返回值  ： 0: 获取数据失败
	*			 >0:设备类型信息
	*/
	UINT8_S GetReceiveDeviceType(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* 功能描述： 获取指定ID码位的设备数量
	* 参数说明： const UINT16 maskId,码位ID
	*			 const UINT8_S sourceSystemType, 源系统类型
	*			 const UINT16_S sourceSystemId 源系统ID
	* 返回值  ： 0: 获取数据失败
	*			 >0 设备数量
	*/
	UINT8_S GetReceiveDeviceSum(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);

	/*
	* 功能描述： 获取指定ID码位的设备ID数组
	* 参数说明： const UINT16 maskId,码位ID
	*			 const UINT8_S sourceSystemType, 源系统类型
	*			 const UINT16_S sourceSystemId 源系统ID
	*			 const UINT8_S bufSize,数组大小
	*			 UINT16_S deviceIdBuff[],输出数组
	* 返回值  ： 0: 获取数据失败
	*			 1: 获取数据成功
	*/
	UINT8_S GetReceiveDeviceIdBuff(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId,const UINT8_S bufSize,UINT16_S deviceIdBuff[]);

	/*
	* 功能描述： 获取指定ID码位的关联码位Id
	* 参数说明： const UINT16 maskId,码位ID
	*			 const UINT8_S sourceSystemType, 源系统类型
	*			 const UINT16_S sourceSystemId 源系统ID
	* 返回值  ： 0: 获取数据失败
	*			 >0 关联码位ID
	*/
	UINT16_S GetReceiveRelevanceMaskId(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId);
	
	/*
	* 功能描述： 获取本ZC关联的信号机跨压命令信号机数
	* 参数说明： 无
	* 返回值  ： 0: 获取数据失败
	*			>0: 数量
	*/
	UINT16_S GetMaskOfSignalCorssNum(void);

	/*
	* 功能描述： 获取本ZC关联的信号机跨压命令信号机Id信息
	* 参数说明： const UINT16 buffSize,buff大小
	*            UINT16_S signalIdBuff[],信号机IdBuff
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取数据成功
	*/
	UINT8_S GetMaskOfSignalCorssIdBuff(const UINT16_S buffSize,UINT16_S signalIdBuff[]);

	/*
	* 功能描述： 获取本ZC关联的信号机亮灭命令信号机数
	* 参数说明： 无
	* 返回值  ： 0: 获取数据失败
	*			>0: 数量
	*/
	UINT16_S GetMaskOfSignalLightOffNum(void);

	/*
	* 功能描述： 获取本ZC关联的信号机亮灭命令信号机Id信息
	* 参数说明： const UINT16 buffSize,buff大小
	*            UINT16_S signalIdBuff[],信号机IdBuff
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取数据成功
	*/
	UINT8_S GetMaskOfSignalLightOffIdBuff(const UINT16_S buffSize,UINT16_S signalIdBuff[]);

#ifdef __cplusplus
}
#endif

#endif
