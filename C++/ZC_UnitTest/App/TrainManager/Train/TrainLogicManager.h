/********************************************************                                                                                                            
 文 件 名： TrainStatusData.h   
 作    者： ZC组
 创建时间： 2015-07-05
 描述： 列车逻辑处理 
 备注： 无  
********************************************************/
#ifndef TRAIN_LOGIC_MANAGER_H_
#define TRAIN_LOGIC_MANAGER_H_

#include "../../../Common/CommonTypes.h"
#include "TrainDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
  函数名:      SetTrainToModeToRM0
  功能描述:    列车降级处理
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      无
*************************************************/
void SetTrainToModeToRM0(const UINT16_S trainId);

/*************************************************
  函数名:      TrainDirChangeForCheck
  功能描述:    转换列车方向用于反向查询
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      转换值 
*************************************************/
UINT8_S TrainDirChangeForCheck(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeTrainNeedCalculate
  功能描述:    判断列车是否需要进行相应的计算
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      1U:需要
               0U:不需要
*************************************************/
UINT8_S JudgeTrainNeedCalculate(const UINT16_S trainId);

/*************************************************
  函数名:      CalculateTrainSafePos
  功能描述:    计算列车安全位置
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void CalculateTrainSafePos(void);

/*************************************************
  函数名:      CalculateTrainHeadSafePos
  功能描述:    计算列车安全车头位置
  输入:        const UINT16_S trainId,列车ID
  输出:        无
  返回值:      无
*************************************************/
void CalculateTrainHeadSafePos(const UINT16_S trainId);

/*************************************************
  函数名:      CalculateTrainTailSafePos
  功能描述:    计算列车安全车尾位置
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      无
*************************************************/
void CalculateTrainTailSafePos(const UINT16_S trainId);

/*************************************************
  函数名:      CalculateTrainHeadDistance
  功能描述:    计算列车安全车头位置需要的距离
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      距离值
*************************************************/
UINT32_S CalculateTrainHeadDistance(const UINT16_S trainId);

/*************************************************
  函数名:      CalculateTrainTailDistance
  功能描述:    计算列车安全车尾位置需要的距离
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      距离值
*************************************************/
UINT32_S CalculateTrainTailDistance(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeSwitchBelongAcOccStatus
  功能描述:    计算列车安全车尾位置需要的距离
  输入:        cosnt UINT16_S swtichId 道岔ID
  输出:        无
  返回值:      0u:占用
               1u:未占用
*************************************************/
UINT8_S JudgeSwitchBelongAcOccStatus(const UINT16_S swtichId);

/*************************************************
  函数名:      CalculateTrainSafeLocAcOfSwitch
  功能描述:    计算列车安全位置基于需要的距离的计轴内道岔或者尽头线情况
  输入:        const UINT8_S flag,标志信息(1u:车头；2u:车尾)
               const UINT32_S distance,距离值
               const UINT8_S dir,方向
  输出:        UINT16_S errorSwitchOrAcId[SIZE_MAX_SWITCH_MUM_OF_SAFE_TRAIN],不满足拓扑关系道岔编号
               UINT8_S * pSwitchOrAcNum,不满足拓扑关系道岔的数量
               UINT16_S *endAcOfLine,尽头线计轴区段编号
  返回值:      0x03u：位置计算成功
               0x02u：位置计算失败（原因道岔位置错误,errorSwitchOrAcId为不满足拓扑关系道岔编号;pSwitchOrAcNum为不满足拓扑关系道岔的数量）
               0x01u：位置计算失败（原因线路尽头,endAcOfLine,尽头线计轴区段编号）
               0x00u：位置计算失败（其他原因）
*************************************************/
UINT8_S CalculateTrainSafeLocAcOfSwitch(const UINT8_S flag,const UINT16_S trainId,const UINT32_S distance,const UINT8_S dir,UINT16_S errorSwitchOrAcId[SIZE_MAX_SWITCH_MUM_OF_SAFE_TRAIN],UINT8_S * pSwitchOrAcNum,UINT16_S *endAcOfLine);

/*************************************************
  函数名:      ManageTrainDangerousSource
  功能描述:    处理列车前方和后方危险源信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageTrainDangerousSource(void);

/*************************************************
  函数名:      ManageAddTrainHeadSuspect
  功能描述:    管理列车前方危险源信息（是否由于危险源而添加前方危险区域标记）
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      无
*************************************************/
void ManageAddTrainHeadSuspect(const UINT16_S trainId);

/*************************************************
  函数名:      ManageAddTrainTailSuspect
  功能描述:    管理列车后方危险源信息（是否由于危险源而添加后方危险区域标记）
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      无
*************************************************/
void ManageAddTrainTailSuspect(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeTrainHeadSuspect
  功能描述:    判断是否可以去除列车前方危险源信息
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      1u：处理成功（前方无危险源）
               0u：处理失败（前方存在危险源）
*************************************************/
UINT8_S JudgeTrainHeadSuspect(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeTrainTailSuspect
  功能描述:    判断是否可以去除列车后方危险源信息
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      1u：处理成功（后方无危险源）
               0u：处理失败（后方存在危险源）
*************************************************/
UINT8_S JudgeTrainTailSuspect(const UINT16_S trainId);

/*************************************************
  函数名:      CalulateTrainLocToAcInfo
  功能描述:    计算列车占压的安全和非安全计轴区段
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void CalulateTrainLocToAcInfo(void);

/*************************************************
  函数名:      CalculateCommTrainMatchingRoute
  功能描述:    计算通信列车是否能匹配上可用的进路信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void CalculateCommTrainMatchingRoute(void);

/*************************************************
  函数名:      CalculateCommTrainMatchingRoute
  功能描述:    计算通信列车是否能匹配上可用的进路信息
  输入:        const UINT16_S trainId,待匹配列车ID
  输出:        UINT8_S matchRouteIndex,匹配进路的下标
               UINT16_S mathRouteIdBuff[],匹配进路的ID数组
  返回值:      0u:匹配失败
               1u:匹配成功
*************************************************/
UINT8_S MatchTrainSingleRoute(const UINT16_S trainId,UINT8_S matchRouteIndex,UINT16_S matchRouteIdBuff[]);

/*************************************************
  函数名:      MatchTrainHeadFrontAcInRoute
  功能描述:    计算通信列车是否能匹配上可用的进路信息
  输入:        const UINT16_S trainHeadAcId,列车车头计轴区段ID
               const UINT16_S trainId,待匹配列车Id
  输出:        UINT16_S *pMatchRouteId,匹配进路信息
  返回值:      0u:匹配失败
               1u:匹配成功
*************************************************/
UINT8_S MatchTrainHeadFrontAcInRoute(const UINT16_S trainHeadAcId,const UINT16_S trainId,UINT16_S *pMatchRouteId);

/*************************************************
  函数名:      CalculateSignalLocBetweenTrainLoc
  功能描述:    计算信号机的位置是否位于列车车头车尾之间
  输入:        const UINT16_S trainId,列车ID
               const UINT16_S signalId,信号机ID
  输出:        无
  返回值:      0u:比较失败
               1u:位于列车车头车尾位置之间
               2u:不位于列车车头车尾位置之间
*************************************************/
UINT8_S CalculateSignalLocBetweenTrainLoc(const UINT16_S trainId,const UINT16_S signalId);

/*************************************************
  函数名:      CalulateAcIdBelongUseableRoute
  功能描述:    计算通信列车是否能匹配上可用的进路信息
  输入:        const UINT16_S acId,计轴区段ID
               const UINT8_S dir,匹配进路方向
  输出:        UINT16_S *pMathRouteId,输出可匹配进路 
  返回值:      0u:计轴不属于办理进路
               1u:计轴属于办理进路但进路不可被匹配
               2u:计轴属于办理进路且进路可被匹配
*************************************************/
UINT8_S CalulateAcIdBelongUseableRoute(const UINT16_S acId,const UINT8_S dir,UINT16_S *pMathRouteId);

/*************************************************
  函数名:      CalulateRouteMathToTrain
  功能描述:    计算指定列车ID是否能匹配指定进路
  输入:        const UINT16_S routeId,进路ID
               const UINT16_S trainId,列车ID
  输出:        无
  返回值:      0u:匹配失败
               1u:匹配成功
*************************************************/
UINT8_S CalulateRouteMathToTrain(const UINT16_S routeId,const UINT16_S trainId);

/*************************************************
  函数名:      CalculateBeCloseRouteMatch
  功能描述:    计算指定列车ID是否能按进路接近匹配原则匹配指定进路
  输入:        const UINT16_S routeId,进路ID
  输出:        UINT16_S *pMathRouteId,可以匹配的进路ID
  返回值:      0u:匹配失败
               1u:匹配成功
*************************************************/
UINT8_S CalculateBeCloseRouteMatch(const UINT16_S trainId,UINT16_S *pMatchRouteId);

/*************************************************
  函数名:      CalculateRouteAcLockStatusIntegrality
  功能描述:    计算指定进路内计轴区段的锁闭完整性
  输入:        const UINT16_S routeId,进路ID
  输出:        无
  返回值:      0u:未完整锁闭
               1u:完整锁闭
*************************************************/
UINT8_S CalculateRouteAcLockStatusIntegrality(const UINT16_S routeId);

/*************************************************
  函数名:      ManageTrainTypeTransform
  功能描述:    管理列车类型转换
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageTrainTypeTransform(void);

/*************************************************
  函数名:      ManageTrainStatusTransform
  功能描述:    管理列车状态转换信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageTrainStatusTransform(void);

/*************************************************
  函数名:      ManageOutTrainType
  功能描述:    管理列车输出状态信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageOutTrainType(void);

/*************************************************
  函数名:      ManageNZcOutTrainType
  功能描述:    管理列车相邻ZC输出状态信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageNZcOutTrainType(void);

/*************************************************
  函数名:      JudegeNZcDefaultStatusTransform
  功能描述:    处理相邻ZC输入状态为无状态或者跨压切换点的下的相邻ZC输出转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudegeNZcDefaultStatusTransform(const UINT16_S trainId);

/*************************************************
  函数名:      JudegeNZcHandStatusTransform
  功能描述:    处理相邻ZC输入状态为移交申请状态的下的相邻ZC输出转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudegeNZcHandStatusTransform(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeNZcConfirmationStatusTransform
  功能描述:    处理相邻ZC输入状态为移交申请确认状态的下的相邻ZC输出转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeNZcConfirmationStatusTransform(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeNZcManagenohandStatusTransform
  功能描述:    处理相邻ZC输入状态为移交未切换状态的下的相邻ZC输出转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeNZcManagenohandStatusTransform(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeTrainDefaultStatusTransform
  功能描述:    处理默认状态的转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainDefaultStatusTransform(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeTrainStateMovingTransform
  功能描述:    处理STATE_MOVING状态列车状态的转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainStateMovingTransform(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeTrainHandOverTransform
  功能描述:    处理STATE_HANDOVER状态列车状态的转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainHandOverTransform(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeTrainTakeOverTransform
  功能描述:    处理STATE_TAKEOVER状态列车状态的转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainTakeOverTransform(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeTrainReverseTransform
  功能描述:    处理STATE_REVERSE状态列车状态的转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainReverseTransform(const UINT16_S trainId);

/*************************************************
  函数名:      CheckTrainLocSwitchLockState
  功能描述:    检查车身范围内的道岔锁闭状态
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      0u：锁闭异常
               1u：锁闭正常
*************************************************/
UINT8_S CheckTrainLocSwitchLockState(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeTrainLocalInChangeLine
  功能描述:    检查列车是否位于本ZC切换线路的移交ZC范围内
  输入:        const UINT16_S trainId,列车Id
  输出:        UINT16_S *pOutChangeLineId,输出的切换线路ID
  返回值:      0u：不属于
               1u：属于
*************************************************/
UINT8_S JudgeTrainLocalInChangeLine(const UINT16_S trainId,UINT16_S *pOutChangeLineId);

/*************************************************
  函数名:      JudgeTrainInfoOfCiCommFailure
  功能描述:    处于由于CI通信故障导致的列车信息变化
  输入:        const UINT16_S ciId,联锁ID
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainInfoOfCiCommFailure(const UINT16_S ciId);

/*************************************************
  函数名:      JudgeTrainInfoOfNZcCommFailure
  功能描述:    处于由于相邻Zc通信故障导致的列车信息变化
  输入:        const UINT16_S nZcId,相邻ZcId
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainInfoOfNZcCommFailure(const UINT16_S nZcId);

/*************************************************
  函数名:      CalculateTrainInChangeLineId
  功能描述:    计算列车是否位于某个切换线路
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void CalculateTrainInChangeLineId(void);

/*************************************************
  函数名:      JudgeSignalTrainChangeLineId
  功能描述:    计算列车是否位于某个切换线路
  输入:        const UINT16_S trainId,列车ID
  输出:        无
  返回值:      0u:不位于切换线路内
               >0u:位于切换区域内
*************************************************/
UINT16_S JudgeSignalTrainChangeLineId(const UINT16_S trainId);

/*************************************************
  函数名:      CalculateChangeLineSwtichPosInNeed
  功能描述:    计算切换线路的道岔是否在需要的位置
  输入:        const UINT16_S changeLineId,切换线路ID
  输出:        无
  返回值:      0u:不满足
               1u:满足
*************************************************/
UINT8_S CalculateChangeLineSwtichPosInNeed(const UINT16_S changeLineId);

/*************************************************
  函数名:      JudgeTrainChangeId
  功能描述:    设置所有列车的切换线路ID
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainChangeId(void);

/*************************************************
  函数名:      JudgeSingleTrainChangeId
  功能描述:    查找单个列车能匹配上的切换线路的ID
  输入:        const UINT16_S trainId,列车ID
  输出:        无
  返回值:      >0u:切换区域ID
               0u:不在切换区域
               0xffu:失败
*************************************************/
UINT8_S JudgeSingleTrainChangeId(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeRelationBetweenAcSqu
  功能描述:    判断两个计轴序列之间的关系：如果序列1完全包含在序列2中，返回成功；否则，返回失败
  输入:        const UINT8 acNum1,计轴序列1数量
  			   const UINT16_S acSqu1[CHANGE_AREA_AC_MAX]，计轴序列1ID
  			   const UINT8_S acNum1,计轴序列2数量
     		   const UINT16_S acSqu1[CHANGE_AREA_AC_MAX]，计轴序列2ID
  输出:        无
  返回值:      1u:包含
               0u:不包含
*************************************************/
UINT8_S JudgeRelationBetweenAcSqu(const UINT8_S acNum1,const UINT16_S acSqu1[],const UINT8_S acNum2,const UINT16_S acSqu2[]);

/*************************************************
  函数名:      JudgeSwitchStatusInChangeLine
  功能描述:    查找计轴序列内包含的道岔序列状态与切换区域状态的一致性
  输入:        const UINT16_S switchSquBuff[CHANGE_LINE_SWITCH_MAX],输入道岔序列
  			   const UINT8_S switchNum，输入道岔数量
  输出:        无
  返回值:      >0u:符合的切换区域ID
               0u: 失败
*************************************************/
UINT8_S JudgeSwitchStatusInChangeLine(const UINT16_S switchSquBuff[],const UINT8_S switchNum);

/*************************************************
  函数名:      JudgeSwitchIdInAcSqu
  功能描述:    查找计轴序列内包含的道岔序列
  输入:        const UINT16_S acSquBuff[CHANGE_AREA_AC_MAX], 计轴区段数组
  			   const UINT8_S acNum, 计轴区段数量
  输出:        UINT16_S switchSquBuff[CHANGE_LINE_SWITCH_MAX]，输出道岔序列
               UINT8_S *pSwitchNum，输出道岔数量
  返回值:      RETURN_SUCCESS:成功
               RETURN_ERROR: 失败
*************************************************/
UINT8_S JudgeSwitchIdInAcSqu(const UINT16_S acSquBuff[],const UINT8_S acNum,UINT16_S switchSquBuff[],UINT8_S *pSwitchNum);

/*************************************************
  函数名:      JudgetrainStartIdInChange
  功能描述:    查找列车位于共管区域的起始计轴
  输入:        const UINT16_S trainId,列车ID
  输出:        无
  返回值:      起始计轴区段ID
*************************************************/
UINT16_S JudgetrainStartIdInChange(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeTrainLocInChangeLine
  功能描述:    判断列车位于切换区域的位置
  输入:        const UINT16_S trainId,列车ID
  输出:        无
  返回值:      0u 失败
               1u 车头车尾均位于切换区域内
               2u 车头位于切换区域内，车尾均位于切换区域外
               3u 车头位于切换区域外，车尾均位于切换区域内
               4u 列车位于切换区域外
*************************************************/
UINT8_S JudgeTrainLocInChangeLine(const UINT16_S trainId);

/*************************************************
  函数名:      JudgeAcSquToChangeEnd
  功能描述:    获取指定计轴到切换区域终端的计轴序列
  输入:        const UINT16_S acId  起始计轴ID
               const UINT8_S direction 方向
  输出:        UINT8_S *pOutAcNum 返回计轴数量
               UINT16_S acSquBuff[CHANGE_AREA_AC_MAX] 返回计轴序列
  返回值:      RETURN_ERROR 失败
               RETURN_SUCCESS 成功
*************************************************/
UINT8_S JudgeAcSquToChangeEnd(const UINT16_S acId,const UINT8_S direction,UINT8_S *pOutAcNum,UINT16_S acSquBuff[]);

/*************************************************
  函数名:      ManageDeleteTrainInfo
  功能描述:    管理需要删除列车信息函数（对需要删除的列车进行删除）
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageDeleteTrainInfo(void);

#ifdef __cplusplus
}
#endif

#endif
