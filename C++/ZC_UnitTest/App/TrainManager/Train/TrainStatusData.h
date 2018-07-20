/********************************************************                                                                                                            
 文 件 名： TrainStatusData.h   
 作    者： ZC组
 创建时间： 2015-07-01
 描述： 列车状态数据管理  
 备注： 无  
********************************************************/
#ifndef TRAIN_STATUS_DATA_H_
#define TRAIN_STATUS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "TrainDefine.h"
#include "../../SysDataManager/SysDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*列车位置数据结构*/
typedef struct STrainSafeLocStruct
{
	UINT16_S  TrainHeadLink;                         /* 列车车头安全位置区段号（Link）*/
	UINT32_S  TrainHeadOffset;                       /* 列车车头安全位置偏移位置（Offset）*/
	UINT16_S  TrainTailLink;                         /* 列车尾部安全位置区段号（Link）*/
	UINT32_S  TrainTailOffset;                       /* 列车尾部安全位置偏移位置（Offset）*/
}TrainSafeLocStruct;

/*列车状态数据结构体*/
typedef struct STrainInfoStruct
{
	UINT16_S  TrainID;                                       /*列车ID*/
	UINT16_S  TrainControlZC;                                /*列车当前受控ZCID*/
	UINT32_S  TrainCycle;                                    /*车载ATP输入信息时的本地时间（车载ATP当前周期号）*/
	UINT8_S   TrainType;                                     /*列车类型*/
	UINT8_S   SuspectHead;                                   /*前端可疑标志*/
	UINT8_S   SuspectTail;                                   /*后端可疑标志*/
	UINT16_S  TrainHeadAC;                                   /*列车安全车头所在计轴区段*/		
	UINT16_S  TrainTailAC;                                   /*列车安全车尾所在计轴区段*/
	UINT16_S  TrainUnsafeHeadAC;                             /*列车非安全车头所在计轴区段*/		
	UINT16_S  TrainUnsafeTailAC;                             /*列车非安全车尾所在计轴区段*/
	UINT16_S  TrainFrontSignal;                              /*列车前方需要防护的信号机*/
	UINT8_S   SignalProtection;                              /*列车闯过信号机防护标志*/
	UINT8_S   CommStatus;                                    /*标示该列车通信链路的状态*/
	UINT8_S   CommRedundancy;                                /*列车通信计时位*/
	UINT8_S   PrtclDelay;                                    /*列车通信协议延迟时间*/
	UINT8_S   TrainStatus;                                   /*标示内部管理列车的各种状态*/
	UINT8_S   TrainInType;                                   /*车载ATP输入的信息帧类型*/
	UINT8_S   TrainOutType;                                  /*给车载ATP输出的信息帧类型*/
	UINT8_S   HandoverInType;                                /*相邻ZC输入信息帧类型*/
	UINT8_S   HandoverOutType;                               /*向相邻ZC输出信息帧类型*/
	TrainSafeLocStruct  TrainSafeLocStru;                    /*列车安全位置结构体*/
	TrainSafeLocStruct  TrainUnSafeLocStru;                  /*列车非安全位置结构体*/
	UINT8_S  TrainUnsafeDirection;                           /*列车头部非安全位置对应的期望运行方向:0x55-逻辑正方向;0xaa-逻辑反方向*/
	UINT8_S  TrainRealDirection;                             /*列车头部非安全位置实际运行方向:0x55-逻辑正方向;0xaa-逻辑反方向*/
	UINT8_S  TrainMode;                                      /*列车驾驶模式信息*/
	UINT8_S  TrainLevel;                                     /*列车运行级别*/      
	UINT16_S TrainSpeed;                                     /*列车实际速度信息，单位cm/s*/
	UINT8_S  TrainStopArea;                                  /*列车停车区域停稳信息*/
	UINT8_S  TrainIntegrity;                                 /*列车完整性标示码*/
	UINT8_S  TrainEmergency;                                 /*列车紧急停车标示信息*/
	UINT16_S TrainError;                                     /*列车不确定误差*/
	UINT8_S MatchRouteNum;                                   /*列车匹配进路数量*/
	UINT16_S MatchedRouteIDBuff[SIZE_MAX_ROUTENUM];          /*列车当前已排进路ID*/
	UINT16_S ChangeLineId;                                   /*切换线路ID*/
	UINT8_S PreSectionNum;                                   /*上周期占压逻辑区段数量*/
	UINT16_S PreSectionIdBuff[SIZE_MAX_SECTION_OF_TRAIN];    /*上周期占压逻辑区段ID*/
}TrainInfoStruct;

/*************************************************
  函数名:      GetTrainCurSum
  功能描述:    获取指定列车ID索引号
  输入:        无
  输出:        无
  返回值:      0U: 获取数据失败
               <SIZE_MAX_CONTROLE_TRAIN: 查找成功
*************************************************/
UINT8_S GetTrainCurSum(void);

/*************************************************
  函数名:      GetSingalTrainInfoOfIndex
  功能描述:    获取指定列车列车信息首地址
  输入:        const UINT16_S index, 数组下标
  输出:        无
  返回值:      Null: 获取数据失败
               >0: 单个列车信息首地址
*************************************************/
TrainInfoStruct* GetSingalTrainInfoOfIndex(const UINT16_S index);

/*
* 功能描述： 获取指定索引号的列车ID
* 参数说明： const UINT8_S index, 列车ID的下标
* 返回值  ： RETURN_ERROR: 获取数据失败
*			<SIZE_MAX_LINE_TRAIN: 查找成功
*/
UINT16_S GetTrainIdOfIndex(const UINT8_S index);

/*************************************************
  函数名:      GetTrainStatusBufIndex
  功能描述:    获取指定列车ID索引号
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               <SIZE_MAX_LINE_TRAIN: 查找成功
*************************************************/
UINT8_S GetTrainStatusBufIndex(const UINT16_S trainId);

/*************************************************
  函数名:      GetSingleTrainInfo
  功能描述:    获取指定列车ID列车信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        TrainInfoStruct *pSingleTrainInfo, 列车信息结构体
  返回值:      RETURN_ERROR:   获取数据失败
               RETURN_SUCCESS: 获取数据成功
*************************************************/
UINT8_S GetSingleTrainInfo(const UINT16_S trainId,TrainInfoStruct *pSingleTrainInfo);

/*************************************************
  函数名:      SetSingleTrainNextZcInputDataInfo
  功能描述:    设置相邻ZC输入的指定列车ID列车信息
  输入:        const UINT16_S trainId, 列车ID
               const TrainInfoStruct *pSingleTrainInfo, 列车信息结构体
  输出:        无
  返回值:      RETURN_ERROR:   设置数据失败
               RETURN_SUCCESS: 设置数据成功
*************************************************/
UINT8_S SetSingleTrainNextZcInputDataInfo(const UINT16_S trainId,const TrainInfoStruct *pSingleTrainInfo);

/*************************************************
  函数名:      SetSingleTrainInputDataInfo
  功能描述:    设置列车输入信息中指定列车ID列车信息
  输入:        const UINT16_S trainId, 列车ID
               const TrainInfoStruct *pSingleTrainInfo, 列车信息结构体
  输出:        无
  返回值:      RETURN_ERROR:   设置数据失败
               RETURN_SUCCESS: 设置数据成功
*************************************************/
UINT8_S SetSingleTrainInputDataInfo(const UINT16_S trainId,const TrainInfoStruct *pSingleTrainInfo);

/*************************************************
  函数名:      GetTrainControlZc
  功能描述:    获取指定列车受控ZC
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               <RETURN_UINT8_MAX_VALUE: 获取数据成功
*************************************************/
UINT16_S GetTrainControlZc(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainControlZc
  功能描述:    设置指定列车受控ZC
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S zcId, ZC的编号
  输出:        无
  返回值:      RETURN_ERROR:   设置数据失败
               RETURN_SUCCESS: 设置数据成功
*************************************************/
UINT8_S SetTrainControlZc(const UINT16_S trainId,const UINT16_S zcId);

/*************************************************
  函数名:      GetTrainCycle
  功能描述:    获取指定列车周期号
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取数据失败
               >0:             获取数据成功
*************************************************/
UINT32_S GetTrainCycle(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainCycle
  功能描述:    设置指定列车周期号
  输入:        const UINT16_S trainId, 列车ID
               const UINT32_S trainCycle， 列车周期号
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainCycle(const UINT16_S trainId,const UINT32_S trainCycle);

/*************************************************
  函数名:      GetTrainType
  功能描述:    获取指定列车类型
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT8_S GetTrainType(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainType
  功能描述:    设置指定列车类型
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainType, 列车类型
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainType(const UINT16_S trainId,const UINT8_S trainType);

/*************************************************
  函数名:      GetTrainSuspectHead
  功能描述:    获取指定列车前端可疑标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT8_S GetTrainSuspectHead(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainSuspectHead
  功能描述:    设置指定列车前端可疑标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S suspectHead, 列车前端可疑标志
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainSuspectHead(const UINT16_S trainId,const UINT8_S suspectHead);

/*************************************************
  函数名:      GetTrainSuspectTail
  功能描述:    获取指定列车后端可疑标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT8_S GetTrainSuspectTail(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainSuspectTail
  功能描述:    设置指定列车后端可疑标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S suspectTail, 列车后端可疑标志
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainSuspectTail(const UINT16_S trainId,const UINT8_S suspectTail);

/*************************************************
  函数名:      GetTrainTrainHeadAC
  功能描述:    获取指定列车车头所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取数据失败
               >0:             设置成功
*************************************************/
UINT16_S GetTrainTrainHeadAC(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainTrainHeadAC
  功能描述:    设置指定列车车头所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainHeadAC, 车头所在的计轴区段
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainTrainHeadAC(const UINT16_S trainId,const UINT16_S trainHeadAC);

/*************************************************
  函数名:      GetTrainTrainTailAC
  功能描述:    获取指定列车车尾所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT16_S GetTrainTrainTailAC(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainTrainTailAC
  功能描述:    设置指定列车车尾所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainTailAC, 列车车尾所在计轴
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainTrainTailAC(const UINT16_S trainId,const UINT16_S trainTailAC);

/*************************************************
  函数名:      GetTrainUnsafeTrainHeadAC
  功能描述:    获取指定列车非安全车头所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT16_S GetTrainUnsafeTrainHeadAC(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainUnsafeTrainHeadAC
  功能描述:    设置指定列车非安全车头所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainUnsafeHeadAC, 列车非安全车头所在计轴区段
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainUnsafeTrainHeadAC(const UINT16_S trainId,const UINT16_S trainUnsafeHeadAC);

/*************************************************
  函数名:      GetTrainUnsafeTrainTailAC
  功能描述:    获取指定列车非安全车尾所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               RETURN_SUCCESS: 获取成功
*************************************************/
UINT16_S GetTrainUnsafeTrainTailAC(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainUnsafeTrainTailAC
  功能描述:    获取指定列车非安全车尾所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainUnsafeTailAC, 列车非安全车尾所在计轴区段
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainUnsafeTrainTailAC(const UINT16_S trainId,const UINT16_S trainUnsafeTailAC);

/*************************************************
  函数名:      GetTrainFrontSignal
  功能描述:    获取指定列车前方需要防护信号机
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT16_S GetTrainFrontSignal(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainFrontSignal
  功能描述:    设置指定列车前方需要防护信号机
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainFrontSignal, 列车前方信号机
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainFrontSignal(const UINT16_S trainId,const UINT16_S trainFrontSignal);

/*************************************************
  函数名:      GetTrainSignalProtection
  功能描述:    获取指定列车闯信号标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT8_S GetTrainSignalProtection(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainSignalProtection
  功能描述:    设置指定列车闯信号标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S signalProtection, 列车闯信号机防护标志
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainSignalProtection(const UINT16_S trainId,const UINT8_S signalProtection);

/*************************************************
  函数名:      GetTrainCommStatus
  功能描述:    获取指定列车通信链路状态
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:    获取失败
               >0:              获取成功
*************************************************/
UINT8_S GetTrainCommStatus(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainCommStatus
  功能描述:    设置指定列车通信链路状态
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S commStatus, 列车通信链路状态
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainCommStatus(const UINT16_S trainId,const UINT8_S commStatus);

/*************************************************
  函数名:      GetTrainCommRedundancy
  功能描述:    获取指定列车通信计时位
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:    获取失败
               >0:              获取成功
*************************************************/
UINT8_S GetTrainCommRedundancy(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainCommRedundancy
  功能描述:    设置指定列车通信计时位
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S commRedundancy, 列车通信计时位
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainCommRedundancy(const UINT16_S trainId,const UINT8_S commRedundancy);

/*************************************************
  函数名:      GetTrainPrtclDelay
  功能描述:    获取指定列车通信协议延迟时间
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:    获取失败
               >0:              获取成功
*************************************************/
UINT8_S GetTrainPrtclDelay(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainPrtclDelay
  功能描述:    设置指定列车通信协议延迟时间
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S prtclDelay, 列车通信协议延迟时间
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainPrtclDelay(const UINT16_S trainId,const UINT8_S prtclDelay);

/*************************************************
  函数名:      GetTrainStatus
  功能描述:    获取指定列车状态
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainStatus(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainPrtclDelay
  功能描述:    设置指定列车状态
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainStatus, 列车列车状态
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainStatus(const UINT16_S trainId,const UINT8_S trainStatus);

/*************************************************
  函数名:      GetTrainInType
  功能描述:    获取指定列车输入类型
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainInType(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainInType
  功能描述:    设置指定列车输入类型
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainInType, 列车输入类型
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainInType(const UINT16_S trainId,const UINT8_S trainInType);

/*************************************************
  函数名:      GetTrainOutType
  功能描述:    获取指定列车输出类型
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainOutType(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainOutType
  功能描述:    设置指定列车输出类型
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainOutType, 列车输出类型
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainOutType(const UINT16_S trainId,const UINT8_S trainOutType);

/*************************************************
  函数名:      GetTrainHandoverInType
  功能描述:    获取指定相邻ZC输入类型
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainHandoverInType(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainHandoverInType
  功能描述:    设置指定列车相邻ZC输入类型
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S handoverInType, 列车相邻ZC输入类型
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainHandoverInType(const UINT16_S trainId,const UINT8_S handoverInType);

/*************************************************
  函数名:      GetTrainHandoverOutType
  功能描述:    获取指定相邻ZC输出类型
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainHandoverOutType(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainHandoverOutType
  功能描述:    设置指定列车相邻ZC输出类型
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S handoverOutType, 列车相邻ZC输出类型
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainHandoverOutType(const UINT16_S trainId,const UINT8_S handoverOutType);

/*************************************************
  函数名:      GetTrainUnsafeDirection
  功能描述:    获取指定列车期望运行方向
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainUnsafeDirection(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainUnsafeDirection
  功能描述:    设置指定列车期望运行方向
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainUnsafeDirection, 列车期望运行方向
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainUnsafeDirection(const UINT16_S trainId,const UINT8_S trainUnsafeDirection);

/*************************************************
  函数名:      GetTrainRealDirection
  功能描述:    获取指定列车实际运行方向
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainRealDirection(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainRealDirection
  功能描述:    设置指定列车实际运行方向
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainRealDirection, 列车实际运行方向
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainRealDirection(const UINT16_S trainId,const UINT8_S trainRealDirection);

/*************************************************
  函数名:      GetTrainMode
  功能描述:    获取指定列车模式
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainMode(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainMode
  功能描述:    设置指定列车模式
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainMode, 列车列车模式
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainMode(const UINT16_S trainId,const UINT8_S trainMode);

/*************************************************
  函数名:      GetTrainLevel
  功能描述:    获取指定列车级别
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainLevel(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainMode
  功能描述:    设置指定列车级别
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainLevel, 列车列车级别
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainLevel(const UINT16_S trainId,const UINT8_S trainLevel);

/*************************************************
  函数名:      GetTrainSpeed
  功能描述:    获取指定列车速度
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT16_S GetTrainSpeed(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainSpeed
  功能描述:    设置指定列车速度
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainSpeed, 列车速度
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainSpeed(const UINT16_S trainId,const UINT16_S trainSpeed);

/*************************************************
  函数名:      GetTrainStopArea
  功能描述:    获取指定列车停稳标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainStopArea(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainStopArea
  功能描述:    设置指定列车停稳标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainStopArea, 列车停稳标志
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainStopArea(const UINT16_S trainId,const UINT8_S trainStopArea);

/*************************************************
  函数名:      GetTrainEmergency
  功能描述:    获取指定列车完整性标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainIntegrity(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainIntegrity
  功能描述:    设置指定列车完整性标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainIntegrity, 列车完整性标志
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainIntegrity(const UINT16_S trainId,const UINT8_S trainIntegrity);

/*************************************************
  函数名:      GetTrainEmergency
  功能描述:    获取指定列车紧急停车标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainEmergency(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainEmergency
  功能描述:    设置指定列车紧急停车标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainEmergency, 列车紧急停车标志
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainEmergency(const UINT16_S trainId,const UINT8_S trainEmergency);

/*************************************************
  函数名:      GetMatchRouteNum
  功能描述:    获取指定列车已匹配进路数量
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      >=0,数量
*************************************************/
UINT8_S GetMatchRouteNum(const UINT16_S trainId);

/*************************************************
  函数名:      GetTrainMatchedRouteIdBuff
  功能描述:    获取指定列车已匹配进路信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        UINT16_S routeIdBuff[], 匹配的进路的编号
  返回值:      RETURN_ERROR:    获取数据失败
               RETURN_SUCCESS:  获取数据成功
*************************************************/
UINT8_S GetTrainMatchedRouteIdBuff(const UINT16_S trainId,UINT16_S routeIdBuff[]);

/*************************************************
  函数名:      GetTrainMatchedLastRouteId
  功能描述:    获取指定列车已匹配的最后一条进路信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        UINT16_S *pLastRouteId, 最后一条进路Id
  返回值:      RETURN_ERROR:    获取数据失败
               RETURN_SUCCESS:  获取数据成功
*************************************************/
UINT8_S GetTrainMatchedLastRouteId(const UINT16_S trainId,UINT16_S *pLastRouteId);

/*************************************************
  函数名:      SetTrainMatchedRouteIdBuf
  功能描述:    设置指定列车已匹配进路信息
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S routeIdBuff[] 进路ID数组
               const UINT8_S routeNum 进路数量
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainMatchedRouteIdBuf(const UINT16_S trainId,const UINT16_S routeIdBuff[],const UINT8_S routeNum);

/*************************************************
  函数名:      GetTrainSafeLoc
  功能描述:    获取指定列车切换线路ID
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:    获取数据失败
               >0:              获取数据成功
*************************************************/
UINT16_S GetTrainChangeLineId(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainChangeLineId
  功能描述:    设置指定列车切换线路ID
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S changeLineId, 列车切换线路ID
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainChangeLineId(const UINT16_S trainId,const UINT16_S changeLineId);

/*************************************************
  函数名:      GetTrainSafeLoc
  功能描述:    获取指定列车安全位置信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        TrainSafeLocStruct *pTrainSafeLocStru, 列车位置信息结构体
  返回值:      RETURN_ERROR:    获取数据失败
               RETURN_SUCCESS:  获取数据成功
*************************************************/
UINT8_S GetTrainSafeLoc(const UINT16_S trainId,TrainSafeLocStruct *pTrainSafeLocStru);

/*************************************************
  函数名:      SetTrainSafeLoc
  功能描述:    设置指定列车安全位置信息
  输入:        const UINT16_S trainId, 列车ID
               TrainSafeLocStruct *pTrainSafeLocStru, 列车位置结构体
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainSafeLoc(const UINT16_S trainId,const TrainSafeLocStruct *pTrainSafeLocStru);

/*************************************************
  函数名:      SetTrainSafeHeadLoc
  功能描述:    设置指定列车安全车头位置信息
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainSafeHeadLink, 安全车头link
               const UINT32_S trainSafeHeadOffset, 安全车头offset
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainSafeHeadLoc(const UINT16_S trainId,const UINT16_S trainSafeHeadLink,const UINT32_S trainSafeHeadOffset);

/*************************************************
  函数名:      SetTrainSafeTailLoc
  功能描述:    设置指定列车安全车尾位置信息
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainSafeTailLink, 安全车尾link
               const UINT32_S trainSafeTailOffset, 安全车尾offset
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainSafeTailLoc(const UINT16_S trainId,const UINT16_S trainSafeTailLink,const UINT32_S trainSafeTailOffset);

/*************************************************
  函数名:      GetTrainUnSafeLoc
  功能描述:    获取指定列车非安全位置信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        TrainSafeLocStruct *pTrainUnSafeLocStru, 列车位置信息结构体
  返回值:      RETURN_ERROR:    获取数据失败
               RETURN_SUCCESS:  获取数据成功
*************************************************/
UINT8_S GetTrainUnSafeLoc(const UINT16_S trainId,TrainSafeLocStruct *pTrainUnSafeLocStru);

/*************************************************
  函数名:      SetTrainUnSafeLoc
  功能描述:    设置指定列车非安全位置信息
  输入:        const UINT16_S trainId, 列车ID
               const TrainSafeLocStruct trainUnSafeLocStru, 位置信息结构体
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainUnSafeLoc(const UINT16_S trainId,const TrainSafeLocStruct trainUnSafeLocStru);

/*************************************************
  函数名:      GetTrainError
  功能描述:    获取指定列车ID不确定误差
  输入:        const UINT16_S trainId, 列车ID
  输出:        UINT16_S sectionIdBuff[], 逻辑区段ID数组
  返回值:      TRAIN_ERROR_MAX_NUM:      获取数据失败
               >0:    获取数据成功
*************************************************/
UINT16_S GetTrainError(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainError
  功能描述:    设置指定列车ID不确定误差
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainError, 不确定误差
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainError(const UINT16_S trainId, const UINT16_S trainError);

/*************************************************
  函数名:      AllotTrainIndex
  功能描述:    分配确定列车分配的缓存下标
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      SIZE_MAX_CONTROLE_TRAIN: 分配下标失败
               (0,SIZE_MAX_CONTROLE_TRAIN): 分配下标成功
*************************************************/
UINT8_S AllotTrainIndex(const UINT16_S trainId);

/*************************************************
  函数名:      GetTrainPreSectionId
  功能描述:    获取指定列车上周期逻辑区段ID
  输入:        const UINT16_S trainId, 列车ID
  输出:        UINT16_S sectionIdBuff[], 逻辑区段ID数组
  返回值:      RETURN_ERROR:      获取数据失败
               RETURN_SUCCESS:    获取数据成功
*************************************************/
UINT8_S GetTrainPreSectionId(const UINT16_S trainId,UINT16_S sectionIdBuff[]);

/*************************************************
  函数名:      GetTrainPreSectionNum
  功能描述:    获取指定列车上周期逻辑区段数量
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE:      获取数据失败
               [0,RETURN_UINT8_MAX_VALUE):  获取数据成功
*************************************************/
UINT8_S GetTrainPreSectionNum(const UINT16_S trainId);

/*************************************************
  函数名:      SetTrainPreSectionId
  功能描述:    设置指定列车上周期逻辑区段信息
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S sectionIdBuff[], 逻辑区段ID数组
               const UINT8_S sectionNum, 逻辑区段的数量
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainPreSectionId(const UINT16_S trainId,const UINT16_S sectionIdBuff[],const UINT8_S sectionNum);

/*************************************************
  函数名:      DeleteSingleTrainInfo
  功能描述:    删除单个列车信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      无
*************************************************/
void DeleteSingleTrainInfo(const UINT16_S trainId);

#ifdef __cplusplus
}
#endif

#endif
