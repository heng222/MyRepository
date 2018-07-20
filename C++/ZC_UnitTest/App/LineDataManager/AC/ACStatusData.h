/********************************************************
*                                                                                                            
* 文 件 名： ACStatusData.h  
* 创建时间： 2015-05-01
* 作    者： 
* 功能描述： 计轴状态数据管理  
* 备  注  ：  无
*
********************************************************/ 
#ifndef AC_STATUS_DATA_H_
#define AC_STATUS_DATA_H_
#include "../../../Common/CommonTypes.h"
#include "ACDefine.h"

#ifdef __cplusplus
extern "C" 
{
#endif

	/*计轴区段配置数据结构体*/
	typedef struct AcStatusDataStruct
	{
		UINT16_S AcId;      		                                    /*计轴区段ID*/
		UINT8_S AcDirection;    	                                    /*计轴锁闭方向*/
		UINT8_S AcBelock;			                                    /*计轴锁闭*/
		UINT8_S AcStatusNow;                                          /*计轴占用空闲*/
		UINT8_S AcUtFlag;                                             /*计轴UT标志位*/
		UINT8_S AcUtRedundance;                                       /*UT冗余计数值*/
		UINT8_S AcArbFlag;                                            /*计轴UT标志位*/
		UINT8_S AcArbRedundance;                                      /*UT冗余计数值*/
		UINT16_S LastTrainEnterAc;                                    /*最后一辆进入计轴的列车ID*/
		UINT16_S CleanTrainId;                                        /*记录清扫列车ID*/
		UINT8_S TrainCleanFlag;                                       /*RM列车已清扫标志*/
		UINT8_S  TrainOfAcNum;                                        /*计轴区段内当前列车数量*/
		UINT16_S TrainSequenceBuff[SIZE_MAX_TRAINOFAC];	            /*列车序列数组*/
		UINT8_S LastTrainOfAcNum;                                     /*上周期计轴内列车数量*/
		UINT16_S LastTrainSequenceBuff[SIZE_MAX_TRAINOFAC];	        /*上周期计轴内列车序列数组*/
	} AcStatusDataStruct;

	/*
	* 功能描述： 获取指定ID计轴锁闭方向
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： RETURN_ERROR: 获取数据失败或者无方向
	*			 0x55: 锁闭方向与逻辑正方向相同
	*			 0xaa: 锁闭方向与逻辑正方向相反
	*/
	UINT8_S GetAcDirection(const UINT16_S acId);

	/*
	* 功能描述： 设置指定ID计轴锁闭方向
	* 参数说明： const UINT16 acId, 计轴ID  
	*            const UINT8_S acDirection
	* 返回值  ： RETURN_ERROR: 获取数据失败或者无方向
	*			 RETURN_SUCCESS: 成功
	*/
	UINT8_S SetAcDirection(const UINT16_S acId,const UINT8_S acDirection);

	/*
	* 功能描述： 获取指定ID计轴锁闭方向
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： RETURN_ERROR: 获取数据失败或者默认值
	*			 0x55: 锁闭
	*			 0xaa: 未锁闭
	*/
	UINT8_S GetAcBelock(const UINT16_S acId);

	/*
	* 功能描述： 设置指定ID计轴锁闭状态
	* 参数说明： const UINT16 acId, 计轴ID 
	*            const UINT8_S acBelock
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS: 成功
	*/
	UINT8_S SetAcBelock(const UINT16_S acId,const UINT8_S acBelock);

	/*
	* 功能描述： 获取指定ID计轴占用状态
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： RETURN_ERROR: 获取数据失败或者默认值
	*			 0x55: 占用
	*			 0xaa: 空闲
	*/
	UINT8_S GetAcStatusNow(const UINT16_S acId);

	/*
	* 功能描述： 设置指定ID计轴当前占用状态
	* 参数说明： const UINT16 acId, 计轴ID 
	*            const UINT8_S acStatus
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS: 成功
	*/
	UINT8_S SetAcStatusNow(const UINT16_S acId,const UINT8_S acStatus);

	/*
	* 功能描述： 获取指定ID计轴UT标志
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： 0: 获取数据失败
	*			 0x55: UT
	*			 0xaa: 非UT
	*/
	UINT8_S GetAcUtFlag(const UINT16_S acId);

	/*
	* 功能描述： 设置指定ID计轴UT标志
	* 参数说明： const UINT16 acId, 计轴ID 
	*            const UINT8_S acUtFlag
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS: 成功
	*/
	UINT8_S SetAcUtFlag(const UINT16_S acId,const UINT8_S acUtFlag);

	/*
	* 功能描述： 获取指定ID计轴ARB标志
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： 0: 获取数据失败
	*			 0x55: ARB
	*			 0xaa: 非ARB
	*/
	UINT8_S GetAcArbFlag(const UINT16_S acId);

	/*
	* 功能描述： 设置指定ID计轴ARB标志
	* 参数说明： const UINT16 acId, 计轴ID    
	*            const UINT8_S acArbFlag
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS: 成功
	*/
	UINT8_S SetAcArbFlag(const UINT16_S acId,const UINT8_S acArbFlag);

	/*
	* 功能描述： 获取指定ID计轴最后一辆进入过列车ID
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： 0: 获取数据失败
	*			 1: 获取数据成功
	*/
	UINT8_S GetAcLastTrain(const UINT16_S acId,UINT16_S *trainId);

	/*
	* 功能描述： 设置指定ID计轴最后一辆进入过列车ID
	* 参数说明： const UINT16 acId, 计轴ID   
	*            const UINT16_S acLastTrainId，最后一列车
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS: 成功
	*/
	UINT8_S SetAcLastTrain(const UINT16_S acId,const UINT16_S acLastTrainId);

	/*
	* 功能描述： 获取指定ID计轴UT冗余计时位
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： 0: 获取数据失败
	*			 >=0:冗余计时位
	*/
	UINT8_S GetAcUtRedundance(const UINT16_S acId);

	/*
	* 功能描述： 设置指定ID计轴UT冗余标志位
	* 参数说明： const UINT16 acId, 计轴ID  
	*            const UINT8_S acUtRedundance
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS: 成功
	*/
	UINT8_S SetAcUtRedundance(const UINT16_S acId,const UINT8_S acUtRedundance);

	/*
	* 功能描述： 获取指定ID计轴ARB冗余计时位
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： 0: 获取数据失败
	*			 >=0:冗余计时位
	*/
	UINT8_S GetAcArbRedundance(const UINT16_S acId);

	/*
	* 功能描述： 设置指定ID计轴ARB冗余标志位
	* 参数说明： const UINT16 acId, 计轴ID  
	*            const UINT8_S acArbRedundance
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS: 成功
	*/
	UINT8_S SetAcArbRedundance(const UINT16_S acId,const UINT8_S acArbRedundance);

	/*
	* 功能描述： 获取指定ID计轴列车数量
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： DEFAULT_UINT8_VALUE: 获取数据失败
	*			 >=0:列车数量
	*/
	UINT8_S GetAcTrainOfAcNum(const UINT16_S acId);

	/*
	* 功能描述： 设置指定ID计轴列车数量
	* 参数说明： const UINT16 acId, 计轴ID   
	*            const UINT8_S acTrainOfAcNum
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS: 成功
	*/
	UINT8_S SetAcTrainOfAcNum(const UINT16_S acId,const UINT8_S acTrainOfAcNum);

	/*
	* 功能描述： 获取指定ID计轴列车序列信息
	* 参数说明： const UINT16 acId, 计轴ID    
	*            const UINT8_S bufSzie,数组大小
	*            UINT16_S trainIdSequBuff[],输出数组
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS:成功
	*/
	UINT8_S GetAcTrainSequenceBuff(const UINT16_S acId,const UINT8_S bufSzie,UINT16_S trainIdSequBuff[]);

	/*
	* 功能描述： 设置指定ID计轴列车序列信息
	* 参数说明： const UINT16 acId,
	*            const UINT16_S trainIdSequBuff[],序列ID
	*            const UINT8_S trainNum,列车数量    
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS:成功
	*/
	UINT8_S SetAcTrainSequenceBuff(const UINT16_S acId,const UINT16_S trainIdSequBuff[],const UINT8_S trainNum);

	/*
	* 功能描述： 判断指定列车ID位于计轴列车序列的位置
	* 参数说明： const UINT16 acId 计轴Id
	*            const UINT16_S trainId，列车Id
	* 返回值  ： 0xff: 没有在该计轴列车序列中
	*			 0>=: 序列位置    
	*/
	UINT8_S GetTrainIdInTrainSequence(const UINT16_S acId,const UINT16_S trainId);

	/*
	* 功能描述： 查询指定计轴区段内的指定下标对应的列车Id
	* 参数说明： const UINT16 acId 计轴Id
	*            const UINT8_S index，索引下表
	*            UINT16_S *trainIdInAC，输出列车ID
    * 返回值  ： RETURN_ERROR: 查询失败
    *			 RETURN_SUCCESS: 查询成功    
	*/
	UINT8_S GetTrainIdInTrainSequenceOfIndex(const UINT16_S acId,const UINT8_S index,UINT16_S *trainIdInAC);

	/*
	* 功能描述： 获取上周期指定ID计轴列车数量
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： -1: 获取数据失败
	*			 >=0:列车数量
	*/
	UINT8_S GetLastTrainOfAcNum(const UINT16_S acId);

	/*
	* 功能描述： 设置上周期指定ID计轴列车数量
	* 参数说明： const UINT16 acId, 计轴ID  
	*            const UINT8_S acTrainOfAcNum
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS: 成功
	*/
	UINT8_S SetLastTrainOfAcNum(const UINT16_S acId,const UINT8_S acTrainOfAcNum);

	/*
	* 功能描述： 获取上周期指定ID计轴列车序列信息
	* 参数说明： const UINT16 acId, 计轴ID    
	*            const UINT8_S bufSzie,数组大小
	*            const UINT16_S trainIdSequBuff[],输出数组
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS:成功
	*/
	UINT8_S GetLastTrainSequenceBuf(const UINT16_S acId,const UINT8_S bufSzie,UINT16_S trainIdSequBuff[]);

	/*
	* 功能描述： 设置上周期指定ID计轴列车序列信息
	* 参数说明： const UINT16 acId,
	*            const UINT16_S trainIdSequBuff[],序列ID
	*            const UINT8_S trainNum,列车数量    
	* 返回值  ： RETURN_ERROR: 获取数据失败
	*			 RETURN_SUCCESS:成功
	*/
	UINT8_S SetLastTrainSequenceBuf(const UINT16_S acId,const UINT16_S trainIdSequBuff[],const UINT8_S trainNum);

	/*
	* 功能描述： 获取指定ID计轴列车已清扫标志
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： RETURN_UINT8_MAX_VALUE: 获取数据失败
	*			 FLAG_SET:已清扫
	*			 FLAG_UNSET:未清扫
	*/
	UINT8_S GetAcTrainCleanFlag(const UINT16_S acId);

	/*
	* 功能描述： 设置指定ID计轴列车已清扫标志
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： RETURN_SUCCESS: 设置成功
	*			 RETURN_ERROR:设置失败			 
	*/
	UINT8_S SetAcTrainCleanFlag(const UINT16_S acId,const UINT8_S cleanFlag);

	/*
	* 功能描述： 获取指定ID计轴已清扫列车ID
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： 0: 获取数据失败
	*			 >0:清扫列车ID
	*/
	UINT16_S GetAcCleanTrainId(const UINT16_S acId);

	/*
	* 功能描述： 设置指定ID计轴已清扫列车ID
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： RETURN_ERROR: 设置数据失败
	*			 RETURN_SUCCESS:设置成功
	*/
	UINT8_S SetAcCleanTrainId(const UINT16_S acId,const UINT16_S cleanTrainId);

	/*
	* 功能描述： 获取计轴区段内的第一列车
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： RETURN_UINT16_MAX_VALUE: 获取数据失败
	*			>0: 第一列列车ID
	*/
	UINT16_S GetFirstIdInTrainSequence(const UINT16_S acId);

	/*
	* 功能描述： 获取计轴区段内的最后一列车
	* 参数说明： const UINT16 acId, 计轴ID    
	* 返回值  ： RETURN_UINT16_MAX_VALUE: 获取数据失败
	*			>0: 最后一列列车ID
	*/
	UINT16_S GetLastIdInTrainSequence(const UINT16_S acId);
	
#ifdef __cplusplus
}
#endif

#endif
