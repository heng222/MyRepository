/************************************************************************
*
* 文件名   ：  LogicSectionLogicManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  逻辑区段逻辑处理
* 备  注   ：  无
*
************************************************************************/
#ifndef LOGIC_SECTION_LOGIC_MANAGER_H_
#define LOGIC_SECTION_LOGIC_MANAGER_H_

#include "../../SysDataManager/SysDefine.h"
#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 处理故障对应的单个逻辑区段信息
	* 参数说明： const UINT16 logicSectionId，逻辑区段ID    
	* 返回值  ： void  
	*/
	void InitFailureSingleLogicSetion(const UINT16_S logicSectionId);

	/*
	* 功能描述： 处理通信故障Ci对应的逻辑区段信息
	* 参数说明： const UINT16 ciId，通信故障的CIID    
	* 返回值  ： void  
	*/
	void InitFailureCiLogicSection(const UINT16_S ciId);

	/*
	* 功能描述： 逻辑区段更新占用状态
	* 参数说明： void    
	* 返回值  ： void
	*/
	void UpdataLogicSectionManager(void);

	/*
	* 功能描述： 更新单个计轴区段逻辑区段占用状态
	* 参数说明： const UINT16 acId;计轴区段编号    
	* 返回值  ： void
	*/
	void UpdateSingalAcLogicSection(const UINT16_S acId);

	/*
	* 功能描述： 初始化单个计轴内逻辑区段状态为UT
	* 参数说明： const UINT16 acId;计轴区段编号    
	* 返回值  ： void
	*/
	void InitLogicStatusOfSingleAc(const UINT16_S acId);

	/*
	* 功能描述： 更新单个计轴内单单个列车占压逻辑区段
	* 参数说明： const UINT16 acId;计轴区段编号 
	*            const UINT16_S trainId;列车ID
	* 返回值  ： void
	*/
	void UpdateLogicStatusOfSingleTrain(const UINT16_S acId,const UINT16_S trainId);

	/*
	* 功能描述： 更新单个计轴内单列车占压逻辑区段
	* 参数说明： const UINT16 acId;计轴区段编号   
	* 返回值  ： void
	*/
	void UpdateLogicStatusOfTrain(const UINT16_S acId);

	/*
	* 功能描述： 更新单个计轴内两列车或者列车与计轴端点之间逻辑区段状态
	* 参数说明： const UINT16 acId 待判断计轴ID    
	* 返回值  ： void
	*/
	void UpdateLogicStatusBetweenTrains(const UINT16_S acId);

	/*
	* 功能描述： 更新2辆列车之间的逻辑区段状态
	* 参数说明： const UINT16 trainId1;前车ID
	*            const UINT16_S trainId2;后车ID
	* 返回值  ： void
	*/
	void UpdateLogicStatusBetweenTwoTrains(const UINT16_S trainId1,const UINT16_S trainId2);

	/*
	* 功能描述： 更新单个计轴内第一辆车前方逻辑区段状态
	* 参数说明： const UINT16 acId;计轴区段编号
	*            const UINT16_S trainId;列车ID
	* 返回值  ： void
	*/
	void UpdateLogicStatusBeforeFirstTrain(const UINT16_S acId,const UINT16_S trainId);

	/*
	* 功能描述： 更新单个计轴内最后一辆车后方逻辑区段状态
	* 参数说明： const UINT16 acId;计轴区段编号
	*            const UINT16_S trainId;列车ID
	* 返回值  ： void
	*/
	void UpdateLogicStatusRearLastTrain(const UINT16_S acId,const UINT16_S trainId);

	/*
	* 功能描述： 判断两列通信车之间的逻辑区段状态
	* 参数说明： const UINT16 trainId1;前车ID
	*            const UINT16_S trainId2;后车ID  
	* 返回值  ： 0x55 紫光带
	*			 0xaa 空闲			 
	*			 0    失败
	*/
	UINT8_S JudgeLogicStatusBetweenTwoTrains(const UINT16_S trainId1,const UINT16_S trainId2);

	/*
	* 功能描述： 在本函数内，对比本周期列车占压的逻辑区段和缓存的上周期占压的逻辑区段，
	判断是否有重合部分
	* 参数说明： const UINT16 preSectionId[]  上周期占压逻辑区段
	*			 cosnt UINT16_S oldSectionId[]   本周期周期占压逻辑区段
	*			 UINT8_S preSectionNum      上周期占压逻辑区段数量
	*			 UINT8_S oldSectionNum       本周期占压逻辑区段数量
	* 返回值  ： RETURN_SUCCESS 重合
	*			 RETURN_ERROR 无重合			 
	*/
	/*逻辑区段重合性判断函数*/
	UINT8_S JudgeLogicSectionSuperPosition(const UINT16_S preSectionId[],const UINT16_S oldSectionId[],
		UINT8_S preSectionNum,UINT8_S oldSectionNum);

	/*
	* 功能描述： 列车占压逻辑区段连续性检查，当检测到不连续后，控制本ZC宕机
	* 参数说明： 无
	* 返回值  ： 0:连续性校验失败
	*            1:连续性校验成功
	*/
	UINT8_S JudgeTrainLogicContinuity(void);

#ifdef __cplusplus
}
#endif

#endif
