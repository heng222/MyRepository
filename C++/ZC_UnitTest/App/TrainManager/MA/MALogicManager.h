/********************************************************                                                                                                            
 *
 * 文 件 名： MALogicManager.h
 * 作    者： ZC组
 * 创建时间： 2015-04-18
 * 描述    ： 移动授权逻辑处理 
 * 备注    ： 无 
 *
********************************************************/
#ifndef MA_LOGIC_MANAGER_H_
#define MA_LOGIC_MANAGER_H_

#include "../../../Common/CommonTypes.h"
#include "MAStatusData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* 函数名称： ManageTrainMaInfo
* 功能描述： 列车的移动授权信息管理
* 输入参数： 无
* 输出参数： 无
* 返回值  ： 无
*/
void ManageTrainMaInfo(void);

/*
* 函数名称： JudgeTrainStateFailure
* 功能描述： 故障状态列车处理
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainStateFailure(const UINT16_S trainId);

/*
* 函数名称： JudgeHandOverTrain
* 功能描述： 移交状态下的移动授权计算
* 输入参数： const UINT16_S trainId,列车ID
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeHandOverTrain(const UINT16_S trainId);

/*
* 函数名称： CalculateTrainMa
* 功能描述： 列车的移动授权信息管理
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateTrainMa(const UINT16_S trainId);

/*
* 函数名称： JudgeTrainMaByRouteInfo
* 功能描述： 处理以进路为条件的列车的移动授权信息管理
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainMaByRouteInfo(const UINT16_S trainId);

/*
* 函数名称： JudgeRouteOfLockOverlap
* 功能描述： 判断进路是否具有锁闭（办理）的保护区段
* 输入参数： const UINT16_S routeId,列车Id
* 输出参数： 无
* 返回值  ： 0u:无overlap
*			 >0u:overlapId
*/
UINT16_S JudgeRouteOfLockOverlap(const UINT16_S routeId);

/*
* 函数名称： JudgeOverlapOfAcFree
* 功能描述： 判断保护区段关联的计轴区段是否空闲
* 输入参数： const UINT8_S overlapOfAcNum,保护区段包含的计轴数量
*            const UINT16_S overlapAcIdBuff[]，保护区段包含的计轴ID
* 输出参数： 无
* 返回值  ： RETURN_SUCCESS:空闲
*			 RETURN_ERROR:非空闲
*/
UINT8_S JudgeOverlapOfAcFree(const UINT8_S overlapOfAcNum,const UINT16_S overlapAcIdBuff[]);

/*
* 函数名称： CalulateOverlapLength
* 功能描述： 判断保护区段关联的计轴区段是否空闲
* 输入参数： const UINT8_S overlapOfAcNum,保护区段包含的计轴数量
*            const UINT16_S overlapAcIdBuff[]，保护区段包含的计轴ID
* 输出参数： UINT32_S *overlapLength,长度
* 返回值  ： RETURN_SUCCESS:计算成功
*			 RETURN_ERROR  :计算失败
*/
UINT8_S CalulateOverlapLength(const UINT8_S overlapOfAcNum,const UINT16_S overlapAcIdBuff[],UINT32_S *overlapLength);

/*
* 函数名称： JudgeTrainMaByOutwardAcInfo
* 功能描述： 以进路或者保护区段外方一个计轴区段信息为基准更新移动授权信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainMaByOutwardAcInfo(const UINT16_S trainId);

/*
* 函数名称： CalculateAcOrderHaveOtherTrain
* 功能描述： 判断从车头到MA终点计轴序列中是否包含其他列车/或者占用
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 0u:不含有其他列车/或者占用
*            1u:含有其他列车/或者占用
*            2u:其他情况已紧急
*/
UINT8_S CalculateAcOrderHaveOtherTrain(const UINT16_S trainId);

/*
* 函数名称： JudgeTrainMaByAcInfo
* 功能描述： 以计轴区段信息为基准更新移动授权信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainMaByAcInfo(const UINT16_S trainId);

/*
* 函数名称： JudgeCommUnCtTrainForMa
* 功能描述： 判断是否由于追踪非通信列车导致MA回撤影响其他计算
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeCommUnCtTrainForMa(const UINT16_S trainId);

/*
* 函数名称： JudgeTrainMaByAcOfFrontAcInfo
* 功能描述： 处理前方计轴区段内的列车对当前列车移动授权的影响
* 输入参数： const UINT8_S flagType,(类型信息:0x55,考虑前方计轴内列车信息;0xaa,不考虑前方计轴内列车信息)
*            const UINT16_S trainId,列车Id
*            const UINT16_S acId,当前计轴
*            const UINT16_S frontAcId,前方计轴区段    
* 输出参数： 无
* 返回值  ： RETURN_SUCCESS,处理成功
*            RETURN_ERROR  ,处理失败
*/
UINT8_S JudgeTrainMaByAcOfFrontAcInfo(const UINT8_S flagType,const UINT16_S trainId,const UINT16_S acId,const UINT16_S frontAcId);

/*
* 函数名称： JudgeTrainMaByAcOfSameAcInfo
* 功能描述： 处理同计轴区段内的列车对当前列车移动授权的影响
* 输入参数： const UINT16_S trainId,列车Id
*            const UINT16_S acId，列车占压计轴区段
*            const UINT8_S frontTrainIndex，前方列车计轴序列下标
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainMaByAcOfSameAcInfo(const UINT16_S trainId,const UINT16_S acId,const UINT8_S frontTrainIndex);

/*
* 函数名称： CalculateTrainMaByFrontTrainTail
* 功能描述： 计算前方列车车尾引起的移动授权更新
* 输入参数： const UINT16_S trainId,列车Id
*            const UINT16_S frontTrainId,前方列车ID
*            const UINT16_S acId,待处理计轴Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateTrainMaByFrontTrainTail(const UINT16_S trainId,const UINT16_S frontTrainId,const UINT16_S acId);

/*
* 函数名称： CalculateTrainMaByFrontTrainHead
* 功能描述： 计算前方列车车头引起的移动授权更新
* 输入参数： const UINT16_S trainId,列车Id
*            const UINT16_S frontTrainId,前方列车ID
*            const UINT16_S acId,待处理计轴Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateTrainMaByFrontTrainHead(const UINT16_S trainId,const UINT16_S frontTrainId,const UINT16_S acId);

/*
* 函数名称： JudgeTrainMaByStationInfo
* 功能描述： 处理以站台为条件的列车的移动授权信息管理
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainMaByStationInfo(const UINT16_S trainId);

/*
* 函数名称： CalculateObsInfoBelongToMaArea
* 功能描述： 计算移动授权范围内的障碍物信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateObsInfoBelongToMaArea(const UINT16_S trainId);

/*
* 函数名称： CalculateTsrInfoBelongToMaArea
* 功能描述： 计算移动授权范围内的临时限速信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateTsrInfoBelongToMaArea(const UINT16_S trainId);

/*
* 函数名称： JudgeReverseStateMaInfo
* 功能描述： 处理折返状态下的移动授权信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeReverseStateMaInfo(const UINT16_S trainId);

/*
* 函数名称： CalculaReverseStateMaInfo
* 功能描述： 计算折返位置的移动授权信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculaReverseStateMaInfo(const UINT16_S trainId);

/*
* 函数名称： JudgeCancellationStateMaInfo
* 功能描述： 处理注销状态下的移动授权信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeCancellationStateMaInfo(const UINT16_S trainId);

/*
* 函数名称： CalculatAdjustMaEndInfo
* 功能描述： 计算是否需要调整移动授权终点并调整移动授权终点
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculatAdjustMaEndInfo(const UINT16_S trainId);

/*
* 函数名称： CalculateMaEndAttribute
* 功能描述： 计算移动授权终点属性信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateMaEndAttribute(const UINT16_S trainId);

/*
* 函数名称： MixObsOfMa
* 功能描述： 混合移动授权信息中的障碍物信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： ObsOfMAStruct mixObsBuff[],输出障碍物信息
* 返回值  ： RETURN_UINT8_MAX_VALUE:失败
*            [0,RETURN_UINT8_MAX_VALUE):障碍物数量
*/
UINT8_S MixObsOfMa(const UINT16_S trainId,ObsOfMAStruct mixObsBuff[]);

/*
* 函数名称： MixTsrOfMa
* 功能描述： 混合移动授权信息中的临时限速信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： TsrOfMAStruct mixTsrBuff[],输出混合后的临时限速
* 返回值  ： RETURN_UINT8_MAX_VALUE:失败
*            [0,RETURN_UINT8_MAX_VALUE):临时限速数量
*/
UINT8_S MixTsrOfMa(const UINT16_S trainId,TsrOfMAStruct mixTsrBuff[]);

/*
* 函数名称： SingleTrainHandMixMA
* 功能描述： 单辆列车混合移动授权（切换列车）
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void SingleTrainHandMixMA(const UINT16_S trainId);
	
/*
* 函数名称： CalPointIsOnOverlap
* 功能描述： 计算1点是否位于保护区段上
* 输入参数： const UINT16_S segId, seg编号
*          const UINT32_S offset,seg偏移量
*          const UINT8_S dir,方向
* 输出参数： UINT16_S *OutOverlapId,保护区段编号
* 返回值  ： 0:失败
*          1：位于保护区段内部(不包括端点)
*          2: 位于沿运行方向保护区段起点
*          3: 位于沿运行方向保护区段终点
*/
UINT8_S CalPointIsOnOverlap(const UINT16_S segId,const UINT32_S offset,const UINT8_S dir,UINT16_S *OutOverlapId);
#ifdef __cplusplus
}
#endif

#endif
