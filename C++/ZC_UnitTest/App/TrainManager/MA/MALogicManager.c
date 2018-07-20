/********************************************************                                                                                                            
*
* 文 件 名： MALogicManager.c
* 作    者： ZC组
* 创建时间： 2015-04-18
* 描述    ： 移动授权逻辑处理 
* 备注    ： 无 
*
********************************************************/
#include "MALogicManager.h"
#include "MAStatusData.h"
#include "MADefine.h"
#include "../Train/TrainStatusData.h"
#include "../Train/TrainDefine.h"
#include "../Train/TrainLogicManager.h"
#include "../../LineDataManager/Overlap/OverlapConfigData.h"
#include "../../LineDataManager/Overlap/OverlapStatusData.h"
#include "../../LineDataManager/Route/RouteConfigData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../LineDataManager/AC/ACConfigData.h"
#include "../../LineDataManager/AC/ACStatusData.h"
#include "../../LineDataManager/AC/ACLogicManager.h"
#include "../../LineDataManager/ESB/ESBConfigData.h"
#include "../../LineDataManager/Switch/SwitchConfigData.h"
#include "../../LineDataManager/PSD/PSDConfigData.h"
#include "../../LineDataManager/Tsr/TsrStatusData.h"
#include "../../LineDataManager/Signal/SignalConfigData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../LineDataManager/Switch/SwitchStatusData.h"
#include "../../LineDataManager/PSD/PSDStatusData.h"
#include "../../LineDataManager/ESB/ESBStatusData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../LineDataManager/Overlap/OverlapLogicManager.h"
#include "../../../Common/MemSet.h"

/*
* 函数名称： ManageTrainMaInfo
* 功能描述： 列车的移动授权信息管理
* 输入参数： 无
* 输出参数： 无
* 返回值  ： 无
*/
void ManageTrainMaInfo(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT8_S trainStatus = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);
        trainStatus = GetTrainStatus(trainId);

        /*LogPrintf(1U,"60::%d;%d;%d\n",trainId,trainType,trainStatus);*/ 
        if ((TRAIN_MODE_OUT != trainType)
            && (TRAIN_MODE_TO_RM0 != trainType)
            && (DEFAULT_ZERO != trainType))
        {
            switch (trainStatus)
            {
            case TRAIN_STATE_MOVING:
            case TRAIN_STATE_TAKEOVER:
                /*计算移动授权*/
                CalculateTrainMa(trainId);

                break;
            case TRAIN_STATE_HANDOVER:
                /*移交状态移动授权计算*/
                JudgeHandOverTrain(trainId);

                break;
            case TRAIN_STATE_REVERSE:
                /*计算折返状态下的移动授权*/
                JudgeReverseStateMaInfo(trainId);

                break;
            case TRAIN_STATE_CANCELLATION:
                /*计算注销状态移动授权*/
                JudgeCancellationStateMaInfo(trainId);

                break;
            case TRAIN_STATE_FAILURE:
                /*计算故障状态移动授权*/
                JudgeTrainStateFailure(trainId);
                break;	
            default:
                /*当列车有类型无状态时,清空移动授权信息*/
                ClearSingleTrainMaInfo(trainId);
                break;
            }
        } 
        else
        {
            switch (trainType)
            {
            case TRAIN_MODE_TO_RM0:
                if (TRAIN_STATE_FAILURE == trainStatus)
                {
                    /*计算故障状态移动授权*/
                    JudgeTrainStateFailure(trainId);
                } 
                else
                {
                    /*维持空MA信息*/
                }
                break;
            case TRAIN_MODE_OUT:

                if (TRAIN_STATE_CANCELLATION == trainStatus)
                {
                    /*计算注销状态移动授权*/
                    JudgeCancellationStateMaInfo(trainId);
                } 
                else
                {
                    /*计算故障状态移动授权*/
                    JudgeTrainStateFailure(trainId);
                }
                break;
            default:
                /*清除MA信息*/
                DeleteSingleTrainMaInfo(trainId);
                break;
            }
        }
    }	
}

/*
* 函数名称： JudgeTrainStateFailure
* 功能描述： 故障状态列车处理
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainStateFailure(const UINT16_S trainId)
{
    /*故障状态下先清除列车移动授权信息*/
    ClearSingleTrainMaInfo(trainId);

    /*设置MA类型为空MA*/
    SetMaType(trainId,ABNORMAL_MA_TYPE);

    LogPrintf(1U,"24.001 TrainId=%d,State Failure!\n",trainId);
}

/*
* 函数名称： JudgeHandOverTrain
* 功能描述： 移交状态下的移动授权计算
* 输入参数： const UINT16_S trainId,列车ID
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeHandOverTrain(const UINT16_S trainId)
{
    UINT8_S trainHandOverInType = DEFAULT_ZERO;

    /*先计算本ZC的移动授权*/
    CalculateTrainMa(trainId);

    trainHandOverInType = GetTrainHandoverInType(trainId);

    /*判断是否具有相邻ZC的移动授权信息*/
    if ((NZC_TRAIN_CONFIRMATION == trainHandOverInType)
        || (NZC_TRAIN_HADTOOKOVER == trainHandOverInType))
    {
        if (LINE_MAX_TRAIN_ID != GetNextZcMaStatusBufIndex(trainId))
        {
            /*混合移动授权*/
            SingleTrainHandMixMA(trainId);
            LogPrintf(1U,"32.001 TrainId=%d,Mix Ma!",trainId);
        } 
        else
        {
            LogPrintf(1U,"32.002 TrainId=%d,Not Mix Ma!",trainId);
        }
    } 
    else
    {
        /*不处理*/
    }
}


/*
* 函数名称： CalculateTrainMa
* 功能描述： 列车的移动授权信息管理
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateTrainMa(const UINT16_S trainId)
{
    TrainSafeLocStruct trainSafeLocStru;

    /*清除MA信息*/
    ClearSingleTrainMaInfo(trainId);

    /*申请MA数组位置*/
    SetMaStatusTrainId(trainId);
    SetMaType(trainId,NORMAL_MA_TYPE);

    /*以进路和进路的保护区段为基准计算移动授权终点信息*/
    JudgeTrainMaByRouteInfo(trainId);

    /* LogPrintf(1U,"13.01A %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    /*以进路外方计轴区段为基准更新移动授权信息*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {      
        JudgeTrainMaByOutwardAcInfo(trainId);     
    }
    else
    {
        /*不处理*/
    }

    /* LogPrintf(1U,"13.01B %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    /*以当前MA区域范围内计轴区段信息为基准更新移动授权终点信息*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {
        JudgeTrainMaByAcInfo(trainId);
    }
    else
    {
        /*不处理*/
    }

    /* LogPrintf(1U,"13.01C %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */ 
    /*以站台为基准更新移动授权终点信息*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {
        JudgeTrainMaByStationInfo(trainId);
    }
    else
    {
        /*不处理*/
    }

    /* LogPrintf(1U,"13.01D %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    /*设置移动授权起点信息*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {
        if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
        {
            SetMaHeadLink(trainId,trainSafeLocStru.TrainTailLink);
            SetMaHeadOffset(trainId,trainSafeLocStru.TrainTailOffset);
            SetMaHeadDir(trainId,GetTrainUnsafeDirection(trainId));
            SetMaTailDir(trainId,GetTrainUnsafeDirection(trainId));
        } 
        else
        {
            SetMaTailLink(trainId,DEFAULT_ZERO);
            SetMaTailOffset(trainId,DEFAULT_ZERO);
            SetMaTailDir(trainId,DEFAULT_ZERO);
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-B9\n",trainId);
        }
    }

    /* LogPrintf(1U,"13.01E %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {
        /*填写Ma终点类型*/
        CalculateMaEndAttribute(trainId);

        /*计算移动授权是否需要调整*/
        CalculatAdjustMaEndInfo(trainId);
    } 
    else
    {
        /*不处理*/
    }

    /* LogPrintf(1U,"13.01F %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    /*计算移动授权范围内的障碍物信息*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {
        CalculateObsInfoBelongToMaArea(trainId);
    }
    else
    {
        /*不处理*/
    }

    /* LogPrintf(1U,"13.01G %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    /*计算移动授权范围内的临时限速信息*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {
        CalculateTsrInfoBelongToMaArea(trainId);
    }
    else
    {
        /*不处理*/
    }

    /* LogPrintf(1U,"13.01H %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
}

/*
* 函数名称： JudgeTrainMaByRouteInfo
* 功能描述： 处理以进路为条件的列车的移动授权信息管理
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainMaByRouteInfo(const UINT16_S trainId)
{
    UINT16_S lastRouteId = DEFAULT_ZERO;
    UINT16_S matchOverlapId = DEFAULT_ZERO;
    UINT32_S overlapLength = DEFAULT_ZERO;
    UINT16_S lastAcIdOfRoute = DEFAULT_ZERO;
    UINT16_S acOfLinkId = DEFAULT_ZERO;
    UINT32_S acOfLinkOffset = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S maEndLink = DEFAULT_ZERO;
    UINT32_S maEndOffset = DEFAULT_ZERO;
    UINT16_S errorSwitchId = DEFAULT_ZERO;
    UINT8_S overlapOfAcNum = DEFAULT_ZERO;
    UINT16_S overlapAcIdBuff[OVERLAP_OF_AC_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S checkFlag = RETURN_ERROR;
    UINT32_S lineMinOverlapLength = DEFAULT_ZERO;
    UINT8_S rtnGetLastRoute = RETURN_ERROR;

    MemorySet(&overlapAcIdBuff[0],((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)));

    /*获取进路最后一条进路*/
    rtnGetLastRoute = GetTrainMatchedLastRouteId(trainId,&lastRouteId);

    if ((DEFAULT_ZERO != lastRouteId) && (RETURN_SUCCESS == rtnGetLastRoute))
    {
        /*获取进路基本信息*/
        if (RETURN_SUCCESS == GetRoutOfAcIdFromIndex(lastRouteId,(GetRouteOfAcNum(lastRouteId) - 1U),&lastAcIdOfRoute))
        {
            trainDir = GetTrainUnsafeDirection(trainId);

            if (RETURN_SUCCESS == CheckAcTerminalPosition(lastAcIdOfRoute,((UINT16_S)trainDir),&acOfLinkId,&acOfLinkOffset))
            {
                /*获取进路对应的保护区段*/
                matchOverlapId = JudgeRouteOfLockOverlap(lastRouteId);

                if (DEFAULT_ZERO != matchOverlapId)
                {
                    /*获取保护区段信息*/
                    overlapOfAcNum = GetOverlapContainAcNum(matchOverlapId);

                    if (RETURN_SUCCESS == GetOverlapContainAcBuff(matchOverlapId,OVERLAP_OF_AC_SUM_MAX,overlapAcIdBuff))
                    {
                        /*判断该保护区段是否空闲*/
                        if (RETURN_SUCCESS == JudgeOverlapOfAcFree(overlapOfAcNum,overlapAcIdBuff))
                        {
                            /*查询保护区段长度*/
                            if (RETURN_SUCCESS == CalulateOverlapLength(overlapOfAcNum,overlapAcIdBuff,&overlapLength))
                            {
                                /*获取进路最后一个计轴区段终点位置*/
                                lineMinOverlapLength = (UINT32_S)GetLineMinOverlapLength();
                                checkFlag = CheckNextPointOnDistance(acOfLinkId,acOfLinkOffset,trainDir,lineMinOverlapLength,&maEndLink,&maEndOffset,&errorSwitchId);

                                if ((overlapLength > lineMinOverlapLength) && (3U == checkFlag))
                                {
                                    /*将MA终点设置为最小的保护区段长度位置*/
                                    SetMaTailLink(trainId,maEndLink);
                                    SetMaTailOffset(trainId,maEndOffset);
                                } 
                                else
                                {
                                    /*将MA终点设置在保护区段终点*/
                                    acOfLinkId = DEFAULT_ZERO;
                                    acOfLinkOffset = DEFAULT_ZERO;

                                    if (RETURN_SUCCESS == CheckAcTerminalPosition(overlapAcIdBuff[overlapOfAcNum - 1U],((UINT16_S)trainDir),&acOfLinkId,&acOfLinkOffset))
                                    {
                                        SetMaTailLink(trainId,acOfLinkId);
                                        SetMaTailOffset(trainId,acOfLinkOffset);
                                    } 
                                    else
                                    {
                                        SetTrainToModeToRM0(trainId);
                                        LogPrintf(1u,"%d-S11\n",trainId);
                                    }
                                }
                            } 
                            else
                            {
                                /*将MA终点设置在进路终端终点*/
                                SetMaTailLink(trainId,acOfLinkId);
                                SetMaTailOffset(trainId,acOfLinkOffset);
                            }
                        } 
                        else
                        {
                            /*将MA终点设置在进路终端终点*/
                            SetMaTailLink(trainId,acOfLinkId);
                            SetMaTailOffset(trainId,acOfLinkOffset);
                        }
                    } 
                    else
                    {
                        /*将MA终点设置在进路终端终点*/
                        SetMaTailLink(trainId,acOfLinkId);
                        SetMaTailOffset(trainId,acOfLinkOffset);
                    }
                } 
                else
                {
                    /*将MA终点设置在进路终端终点*/
                    SetMaTailLink(trainId,acOfLinkId);
                    SetMaTailOffset(trainId,acOfLinkOffset);
                }
            } 
            else
            {
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-S12\n",trainId);
            }
        }       
    } 
    else
    {
        if (GetTrainControlZc(trainId) == GetLocalZcId())
        {
            /*受控ZC为本ZC,紧急制动*/
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-S13\n",trainId);
        } 
        else
        {
            /*不为本ZC控制,设置Ma类型为无MA*/
            SetMaType(trainId,NO_MA_TYPE);
        }
    }
}

/*
* 函数名称： JudgeRouteOfLockOverlap
* 功能描述： 判断进路是否具有锁闭（办理）的保护区段
* 输入参数： const UINT16_S routeId,列车Id
* 输出参数： 无
* 返回值  ： 0u:无overlap
*			 >0u:overlapId
*/
UINT16_S JudgeRouteOfLockOverlap(const UINT16_S routeId)
{
    UINT8_S routeOverlapNum = DEFAULT_ZERO;
    UINT16_S routeOverlapIdBuff[ROUTE_OF_OVERLAP_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S cycleOverlp = DEFAULT_ZERO;
    UINT16_S rtnValue = DEFAULT_ZERO;
    UINT8_S switchAttribute = DEFAULT_ZERO;
    UINT8_S overlapStatus = DEFAULT_ZERO;
    UINT8_S needFlag = RETURN_ERROR;

    MemorySet(&routeOverlapIdBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_OVERLAP_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_OVERLAP_SUM_MAX)));

    /*判断该进路是否具有保护区段*/
    routeOverlapNum = GetRouteOfOverlapNum(routeId);

    if (routeOverlapNum > DEFAULT_ZERO)
    {
        GetRoutOfOverlapIdBuff(routeId,ROUTE_OF_OVERLAP_SUM_MAX,routeOverlapIdBuff);

        for (cycleOverlp = DEFAULT_ZERO;cycleOverlp < routeOverlapNum;cycleOverlp++)
        {
            /*判断保护区段是否包含道岔*/
            switchAttribute = (UINT8_S)(GetOverlapSwitchAttribute(routeOverlapIdBuff[cycleOverlp]));

            if (FLAG_SET == switchAttribute)
            {
                /*获取保护区段*/
                overlapStatus = GetOverlapStatus(routeOverlapIdBuff[cycleOverlp]);
                needFlag = CalulateSwtichStateOfOverlapIsNeed(routeOverlapIdBuff[cycleOverlp]);

                if ((OVERLAP_STATE_SET == overlapStatus)
                    && (RETURN_SUCCESS == needFlag))
                {
                    rtnValue = routeOverlapIdBuff[cycleOverlp];
                    break;
                } 
                else
                {
                    /*不处理*/
                }
            } 
            else
            {
                rtnValue = routeOverlapIdBuff[cycleOverlp];
                break;
            }
        }
    } 
    else
    {
        /*不处理*/
    }

    return rtnValue;
}

/*
* 函数名称： JudgeOverlapOfAcFree
* 功能描述： 判断保护区段关联的计轴区段是否空闲
* 输入参数： const UINT8_S overlapOfAcNum,保护区段包含的计轴数量
*            const UINT16_S overlapAcIdBuff[]，保护区段包含的计轴ID
* 输出参数： 无
* 返回值  ： RETURN_SUCCESS:空闲
*			 RETURN_ERROR:非空闲
*/
UINT8_S JudgeOverlapOfAcFree(const UINT8_S overlapOfAcNum,const UINT16_S overlapAcIdBuff[])
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;

    if (NULL != overlapAcIdBuff)
    {
        for (cycle = DEFAULT_ZERO;cycle < overlapOfAcNum;cycle++)
        {
            if (AC_FREE_STATUS == GetAcStatusNow(overlapAcIdBuff[cycle]))
            {
                /*不处理*/
            } 
            else
            {
                rtnValue = RETURN_ERROR;
                breakFlag = FLAG_SET;
                break;
            }
        }

        if (FLAG_SET != breakFlag)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* 函数名称： CalulateOverlapLength
* 功能描述： 判断保护区段关联的计轴区段是否空闲
* 输入参数： const UINT8_S overlapOfAcNum,保护区段包含的计轴数量
*            const UINT16_S overlapAcIdBuff[]，保护区段包含的计轴ID
* 输出参数： UINT32_S *overlapLength,长度
* 返回值  ： RETURN_SUCCESS:计算成功
*			 RETURN_ERROR  :计算失败
*/
UINT8_S CalulateOverlapLength(const UINT8_S overlapOfAcNum,const UINT16_S overlapAcIdBuff[],UINT32_S *overlapLength)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT32_S acLength = DEFAULT_ZERO;

    if ((NULL != overlapAcIdBuff) && (NULL != overlapLength))
    {
        for (cycle = DEFAULT_ZERO;cycle < overlapOfAcNum;cycle++)
        {
            if (GetLineAcLength(overlapAcIdBuff[cycle],&acLength))
            {
                (*overlapLength) += acLength;
            } 
            else
            {
                rtnValue = RETURN_ERROR;
                break;
            }
        }

        if (overlapOfAcNum == cycle)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* 函数名称： JudgeTrainMaByOutwardAcInfo
* 功能描述： 以进路或者保护区段外方一个计轴区段信息为基准更新移动授权信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainMaByOutwardAcInfo(const UINT16_S trainId)
{
    UINT16_S maEndAcId = DEFAULT_ZERO;
    UINT16_S frontAcId = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S checkLinkId = DEFAULT_ZERO;
    UINT8_S rtnCheckLink = 0U;

    if (0U == CalculateAcOrderHaveOtherTrain(trainId))
    {
        /*获取移动授权终点所属计轴区段*/
        trainDir = GetTrainUnsafeDirection(trainId);
        rtnCheckLink = CalculatePointOfInsideLink(trainDir,GetMaTailLink(trainId),GetMaTailOffset(trainId),&checkLinkId);

        if (1U == rtnCheckLink)
        {
            maEndAcId = CheckPositionBelongAc(checkLinkId);	

            if (DEFAULT_ZERO != maEndAcId)
            {
                /*查询当前计轴前方计轴区段*/
                if (RETURN_SUCCESS == CheckFrontACStatus(maEndAcId,trainDir,&frontAcId))
                {
                    if (AC_FREE_STATUS == GetAcStatusNow(frontAcId))
                    {
                        /*不处理*/
                    } 
                    else
                    {
                        /*根据前方计轴信息处理移动授权*/
                        JudgeTrainMaByAcOfFrontAcInfo(FLAG_UNSET,trainId,maEndAcId,frontAcId);
                    }
                } 
                else
                {
                    /*查询前方计轴失败,不处理*/
                }
            } 
            else
            {
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B10\n",trainId);
            }
        } 
        else
        {
            /* 查询MA终点内方的Link失败,不处理 */
        }            
    } 
    else
    {
        /*包含其他列车或者其他情况,不处理*/
    }
}

/*
* 函数名称： CalculateAcOrderHaveOtherTrain
* 功能描述： 判断从车头到MA终点计轴序列中是否包含其他列车/或者占用
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 0u:不含有其他列车/或者占用
*            1u:含有其他列车/或者占用
*            2u:其他情况已紧急
*/
UINT8_S CalculateAcOrderHaveOtherTrain(const UINT16_S trainId)
{
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S acNum = DEFAULT_ZERO;
    UINT16_S acIdBuff[ZC_TWO_POINT_AC_NUM_MAX] = {DEFAULT_ZERO};
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S trainIdInAcIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S acTrainNum = DEFAULT_ZERO;
    UINT16_S checkLinkId = DEFAULT_ZERO;
    UINT8_S rtnLoc = RETURN_ERROR;
    UINT8_S rtnCheckLink = 0U;

    MemorySet(&acIdBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)));

    rtnLoc = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);
    trainDir = GetTrainUnsafeDirection(trainId);
    rtnCheckLink = CalculatePointOfInsideLink(trainDir,GetMaTailLink(trainId),GetMaTailOffset(trainId),&checkLinkId);

    if ((RETURN_SUCCESS == rtnLoc) && (1U == rtnCheckLink))
    {            
        /*查询以非安全车头位置至MA终点位置的计轴区段序列*/
        if (RETURN_SUCCESS == CheckAcOrderBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,checkLinkId,trainDir,&acNum,acIdBuff))
        {          
            /*通过计轴的信息，更新移动授权信息*/
            for (cycle = DEFAULT_ZERO;cycle < acNum;cycle++)
            {
                trainIdInAcIndex = GetTrainIdInTrainSequence(acIdBuff[cycle],trainId);

                if (DEFAULT_ZERO == cycle)
                {
                    if (DEFAULT_UINT8_VALUE == trainIdInAcIndex)
                    {
                        if (GetAcBelongZcId(acIdBuff[cycle]) == GetLocalZcId())
                        {
                            /*第一个计轴内无列车序列,不存在该情况,导向安全侧*/
                            SetTrainToModeToRM0(trainId);
                            rtnValue = 2U;
                            LogPrintf(1u,"%d-B11\n",trainId);
                        } 
                        else
                        {
                            /*相邻ZC的计轴区段,不处理*/
                        }

                    }
                    else
                    {
                        if (DEFAULT_ZERO == trainIdInAcIndex)
                        {
                            /*第一列车,继续遍历*/
                        } 
                        else
                        {
                            /*不是第一列车,说明包含其他列车*/
                            rtnValue = 1U;
                            break;
                        }
                    }
                } 
                else
                {
                    acTrainNum = GetAcTrainOfAcNum(acIdBuff[cycle]);

                    if (DEFAULT_ZERO == acTrainNum)
                    {
                        if (AC_UT_OCC_STATUS == GetAcUtFlag(acIdBuff[cycle]))
                        {
                            /*包含非通信列车占用计轴区段,直接返回包含占用*/
                            rtnValue = 1U;
                            break;
                        } 
                        else
                        {
                            /*遍历其他*/
                        }
                    } 
                    else
                    {
                        if ((DEFAULT_UINT8_VALUE != acTrainNum))
                        {
                            if (DEFAULT_UINT8_VALUE == trainIdInAcIndex)
                            {
                                /*本计轴不包含该列车,说明包含其他列车*/
                                rtnValue = 1U;
                                break;
                            }
                            else
                            {
                                if (DEFAULT_ZERO == trainIdInAcIndex)
                                {
                                    /*第一列车,继续遍历*/
                                } 
                                else
                                {
                                    /*不是第一列车,说明包含其他列车*/
                                    rtnValue = 1U;
                                    break;
                                }
                            }
                        } 
                        else
                        {
                            /*继续遍历*/
                        }
                    }
                }
            }
        }
        else
        {
            SetTrainToModeToRM0(trainId);
            rtnValue = 2U;
            LogPrintf(1u,"%d-B12\n",trainId);
        }
    } 
    else
    {
        /* 不处理 */
    }

    return rtnValue;
}

/*
* 函数名称： JudgeTrainMaByAcInfo
* 功能描述： 以计轴区段信息为基准更新移动授权信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainMaByAcInfo(const UINT16_S trainId)
{
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S acNum = DEFAULT_ZERO;
    UINT16_S acIdBuff[ZC_TWO_POINT_AC_NUM_MAX] = {DEFAULT_ZERO};
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S trainIdInAcIndex = DEFAULT_ZERO;
    UINT16_S checkLinkId = DEFAULT_ZERO;
    UINT8_S rtnLoc = RETURN_ERROR;
    UINT8_S rtnCalLink = 0U;

    MemorySet(&acIdBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)));

    rtnLoc = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);
    trainDir = GetTrainUnsafeDirection(trainId);

    rtnCalLink = CalculatePointOfInsideLink(trainDir,GetMaTailLink(trainId),GetMaTailOffset(trainId),&checkLinkId);

    if ((RETURN_SUCCESS == rtnLoc) && (1U == rtnCalLink))
    {
        /*查询以非安全车头位置至MA终点位置的计轴区段序列*/
        if (RETURN_SUCCESS == CheckAcOrderBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,checkLinkId,trainDir,&acNum,acIdBuff))
        {
            /*通过计轴的信息，更新移动授权信息*/
            for (cycle = DEFAULT_ZERO;cycle < acNum;cycle++)
            {
                trainIdInAcIndex = GetTrainIdInTrainSequence(acIdBuff[cycle],trainId);

                if (DEFAULT_UINT8_VALUE == trainIdInAcIndex)
                {
                    if (DEFAULT_ZERO != cycle)
                    {
                        /*该列车不位于该计轴区段内*/
                        if (RETURN_ERROR == JudgeTrainMaByAcOfFrontAcInfo(FLAG_SET,trainId,acIdBuff[cycle-1U],acIdBuff[cycle]))
                        {
                            /*继续下一个计轴区段*/
                        } 
                        else
                        {
                            break;
                        }
                    } 
                    else
                    {
                        if (GetAcBelongZcId(acIdBuff[cycle]) == GetLocalZcId())
                        {
                            /*第一个计轴内无列车序列,不存在该情况,导向安全侧*/
                            SetTrainToModeToRM0(trainId);
                            LogPrintf(1u,"%d-S14\n",trainId);
                        } 
                        else
                        {
                            /*相邻ZC计轴不处理*/
                        }

                    }
                } 
                else
                {
                    /*该列车不位于该计轴区段内*/
                    /*判断列车是否位于该计轴内第一列车车*/
                    if (DEFAULT_ZERO == trainIdInAcIndex)
                    {
                        /*继续查询下一个计轴区段*/
                    } 
                    else
                    {
                        /*获取该计轴区段前方列车信息*/
                        JudgeTrainMaByAcOfSameAcInfo(trainId,acIdBuff[cycle],(trainIdInAcIndex - 1U));
                        break;
                    }
                }
            }
        } 
        else
        {
            JudgeCommUnCtTrainForMa(trainId);	
        }
    } 
    else
    {
        /* 获取位置和查找MA终点所在Link任意1个失败 */
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-S15\n",trainId);
    }
}

/*
* 函数名称： JudgeCommUnCtTrainForMa
* 功能描述： 判断是否由于追踪非通信列车导致MA回撤影响其他计算
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeCommUnCtTrainForMa(const UINT16_S trainId)
{
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S rtnTemp = DEFAULT_ZERO;
    UINT8_S rtnLoc = RETURN_ERROR;

    rtnLoc = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);
    trainDir = GetTrainUnsafeDirection(trainId);

    if (MA_OBS_TYPE_COMM_UNCT_TRAIN != GetMaEndObsType(trainId))
    {
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B13\n",trainId);
    } 
    else
    {
        if (RETURN_SUCCESS == rtnLoc)
        {
            /*检查移动授权是否位于非安全车头后方*/
            rtnTemp = CheckLocRelationBetweenTwoPoints(GetMaTailLink(trainId),GetMaTailOffset(trainId),
                trainUnSafeLocStru.TrainHeadLink,trainUnSafeLocStru.TrainHeadOffset,trainDir);

            if ((2U == rtnTemp) || (3U == rtnTemp))
            {
                /*前方为非安全车头位置,不处理*/
            } 
            else
            {
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B14\n",trainId);
            }
        }      
    }
}

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
UINT8_S JudgeTrainMaByAcOfFrontAcInfo(const UINT8_S flagType,const UINT16_S trainId,const UINT16_S acId,const UINT16_S frontAcId)
{
    UINT16_S rearAcId = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainSafeHeadAc = DEFAULT_ZERO;
    UINT16_S acTopLink = DEFAULT_ZERO;
    UINT32_S acTopOffset = DEFAULT_ZERO;
    UINT16_S frontTrainId = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S trainDirInAc = DEFAULT_ZERO;
    UINT8_S trainIndexInAc = DEFAULT_ZERO;
    UINT8_S trainSumOnAc = DEFAULT_ZERO;   /*pbw,前方计轴区段中列车数目*/
    UINT16_S backLink = DEFAULT_ZERO;
    UINT32_S backOffset = DEFAULT_ZERO;
    UINT16_S errorSwitchId = DEFAULT_ZERO;
    UINT8_S checkRtn = DEFAULT_ZERO;
    UINT16_S frontAcTopLink = DEFAULT_ZERO;
    UINT32_S frontAcTopOffset = DEFAULT_ZERO;

    trainDir = GetTrainUnsafeDirection(trainId);
    trainSafeHeadAc = GetTrainTrainHeadAC(trainId);
    trainSumOnAc =  GetAcTrainOfAcNum(frontAcId);
#if 1  
    /*
    if ((AC_UT_OCC_STATUS == GetAcUtFlag(frontAcId))
    && (DEFAULT_ZERO == trainSumOnAc))*/
    /* pbw,2017.7.14,联锁分界点在信号机处，断相邻联锁通信，在分界点相邻计轴车不降级,
    因前方计轴区段UT占用且有车 */
    if ((AC_UT_OCC_STATUS == GetAcUtFlag(frontAcId)))
    {
        /* 计轴非通信列车占用，查询后方计轴区段 */
        if ((RETURN_SUCCESS == CheckRearACStatus(frontAcId,trainDir,&rearAcId))
            && (DEFAULT_ZERO != trainSafeHeadAc))
        {
            /*判断后方计轴是否是列车安全车头占压计轴*/
            if (rearAcId == trainSafeHeadAc)
            {
                /*列车需要紧急制动*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-S1\n",trainId);
            } 
            else
            {
                /*将移动授权放到后方计轴的始端位置*/
                if (RETURN_SUCCESS == CheckAcTopPosition(rearAcId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
                {
                    SetMaTailLink(trainId,acTopLink);
                    SetMaTailOffset(trainId,acTopOffset);
                } 
                else
                {
                    SetTrainToModeToRM0(trainId);
                    LogPrintf(1u,"%d-S2\n",trainId);
                }
            }
        } 
        else
        {
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-S3\n",trainId);
        }

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        /*if(AC_OCC_STATUS == GetAcStatusNow(frontAcId))
        {*/
            if(DEFAULT_ZERO == trainSumOnAc)
            {
                /* 无车 */
                if(DEFAULT_ZERO < GetAcUtRedundance(frontAcId))
                {
                    /* pbw,2017.7.19 占用无车，在判UT占用之前冗余时期,MA终点为该计轴区段始端 */
                    if (RETURN_SUCCESS == CheckAcTopPosition(frontAcId,((UINT16_S)trainDir),&frontAcTopLink,&frontAcTopOffset))
                    {
                        SetMaTailLink(trainId,frontAcTopLink);
                        SetMaTailOffset(trainId,frontAcTopOffset);
                    } 
                    else
                    {
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-S2333\n",trainId);
                    }

                    rtnValue = RETURN_SUCCESS;
                }       
            }
            else
            {
                /* 前方计轴区段有车(区段占用、区段空闲2种情况) */
                trainDirInAc = CalculateTrainDirInOtherAc(FLAG_SET,acId,frontAcId,trainDir);

                if ((DEFAULT_ZERO == trainDirInAc)
                    || (AC_DIR_DEFAULT == trainDirInAc))
                {
                    /*有列车序列而无方向或者计算失败，导向安全侧*/
                    SetTrainToModeToRM0(trainId);
                    LogPrintf(1u,"%d-S4\n",trainId);
                } 
                else
                {
                    if (AC_DIR_FARAWAY == trainDirInAc)
                    {
                        trainIndexInAc = GetAcTrainOfAcNum(frontAcId)-1U;
                    } 
                    else
                    {
                        trainIndexInAc = 0U;
                    }

                    if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(frontAcId,trainIndexInAc,&frontTrainId))
                    {
                        /*查询后方计轴区段*/
                        if ((RETURN_SUCCESS == CheckRearACStatus(frontAcId,trainDir,&rearAcId))
                            && (DEFAULT_ZERO != trainSafeHeadAc))
                        {
                            /*判断后方计轴是否是列车安全车头占压计轴且是否带有后端危险区域*/
                            if (AC_DIR_FARAWAY == trainDirInAc)
                            {
                                if (FLAG_SET == GetTrainSuspectTail(frontTrainId))
                                {
                                    if (rearAcId == trainSafeHeadAc)
                                    {
                                        /*列车需要紧急制动*/
                                        SetTrainToModeToRM0(trainId);
                                        LogPrintf(1u,"%d-S5\n",trainId);
                                    } 
                                    else
                                    {
                                        /*将移动授权放到后方计轴的始端位置*/
                                        if (RETURN_SUCCESS == CheckAcTopPosition(rearAcId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
                                        {
                                            SetMaTailLink(trainId,acTopLink);
                                            SetMaTailOffset(trainId,acTopOffset);
                                        } 
                                        else
                                        {
                                            SetTrainToModeToRM0(trainId);
                                            LogPrintf(1u,"%d-S6\n",trainId);
                                        }
                                    }
                                } 
                                else
                                {
                                    if (FLAG_SET == flagType)
                                    {
                                        /*处理前方列车引起的移动授权更新*/
                                        CalculateTrainMaByFrontTrainTail(trainId,frontTrainId,frontAcId);
                                    } 
                                    else
                                    {
                                        /*不处理*/
                                    }
                                }
                            } 
                            else
                            {
                                if (FLAG_SET == GetTrainSuspectHead(trainId))
                                {
                                    if (rearAcId == trainSafeHeadAc)
                                    {
                                        /*列车需要紧急制动*/
                                        SetTrainToModeToRM0(trainId);
                                        LogPrintf(1u,"%d-S7\n",trainId);
                                    } 
                                    else
                                    {
                                        /*将移动授权放到后方计轴的始端位置*/
                                        if (RETURN_SUCCESS == CheckAcTopPosition(rearAcId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
                                        {
                                            SetMaTailLink(trainId,acTopLink);
                                            SetMaTailOffset(trainId,acTopOffset);
                                        } 
                                        else
                                        {
                                            SetTrainToModeToRM0(trainId);
                                            LogPrintf(1u,"%d-S8\n",trainId);
                                        }
                                    }
                                } 
                                else
                                {
                                    if (FLAG_SET == flagType)
                                    {
                                        /*处理前方列车引起的移动授权更新*/
                                        CalculateTrainMaByFrontTrainHead(trainId,frontTrainId,frontAcId);
                                    } 
                                    else
                                    {
                                        /* pbw 2017.7.17 */
                                        if (RETURN_SUCCESS == CheckAcTopPosition(rearAcId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
                                        {
                                            /*进路外方的计轴区段内的列车无前端可疑标记,回撤移动授权*/
                                            checkRtn = CheckNextPointOnDistance(acTopLink,acTopOffset,TrainDirChangeForCheck(trainId),((UINT32_S)GetLineMaBackDistance()),&backLink,&backOffset,&errorSwitchId);

                                            if (0x03U == checkRtn)
                                            {
                                                SetMaTailLink(trainId,backLink);
                                                SetMaTailOffset(trainId,backOffset);
                                            }
                                            else
                                            {
                                                SetTrainToModeToRM0(trainId);
                                                LogPrintf(1u,"%d-B73\n",trainId);
                                            }
                                        } 
                                        else
                                        {
                                            SetTrainToModeToRM0(trainId);
                                            LogPrintf(1u,"%d-B7333\n",trainId);
                                        }                                          
                                    }
                                }
                            }
                        }
                        else
                        {
                            /*列车需要紧急制动*/
                            SetTrainToModeToRM0(trainId);
                            LogPrintf(1u,"%d-S9\n",trainId);
                        }
                    }
                    else
                    {
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-S10\n",trainId);
                    }
                }

                rtnValue = RETURN_SUCCESS;
            }
        /*}
        
        else
        {*/
            /* 空闲,直接返回失败 
            rtnValue = RETURN_ERROR;
        }*/
    }	


#else
    if ((AC_UT_OCC_STATUS == GetAcUtFlag(frontAcId))
        && (DEFAULT_ZERO == trainSumOnAc))
        /*
        if ((AC_UT_OCC_STATUS == GetAcUtFlag(frontAcId)))*/
    {
        /*计轴非通信列车占用，查询后方计轴区段*/
        if ((RETURN_SUCCESS == CheckRearACStatus(frontAcId,trainDir,&rearAcId))
            && (DEFAULT_ZERO != trainSafeHeadAc))
        {
            /*判断后方计轴是否是列车安全车头占压计轴*/
            if (rearAcId == trainSafeHeadAc)
            {
                /*列车需要紧急制动*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-S1\n",trainId);
            } 
            else
            {
                /*将移动授权放到后方计轴的始端位置*/
                if (RETURN_SUCCESS == CheckAcTopPosition(rearAcId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
                {
                    SetMaTailLink(trainId,acTopLink);
                    SetMaTailOffset(trainId,acTopOffset);
                } 
                else
                {
                    SetTrainToModeToRM0(trainId);
                    LogPrintf(1u,"%d-S2\n",trainId);
                }
            }
        } 
        else
        {
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-S3\n",trainId);
        }

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        /*处理前方列车引起的移动授权改变*/
        /*获取前方计轴内最后一列车*/
        if((DEFAULT_UINT8_VALUE == trainSumOnAc) || (DEFAULT_ZERO == trainSumOnAc))
        {
            /*无车*/
            /*pbw 增加获取失败的分支*/
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            trainDirInAc = CalculateTrainDirInOtherAc(FLAG_SET,acId,frontAcId,trainDir);

            if ((DEFAULT_ZERO == trainDirInAc)
                || (AC_DIR_DEFAULT == trainDirInAc))
            {
                /*有列车序列而无方向或者计算失败，导向安全侧*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-S4\n",trainId);
            } 
            else
            {
                if (AC_DIR_FARAWAY == trainDirInAc)
                {
                    trainIndexInAc = GetAcTrainOfAcNum(frontAcId)-1U;
                } 
                else
                {
                    trainIndexInAc = 0U;
                }

                if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(frontAcId,trainIndexInAc,&frontTrainId))
                {
                    /*查询后方计轴区段*/
                    if ((RETURN_SUCCESS == CheckRearACStatus(frontAcId,trainDir,&rearAcId))
                        && (DEFAULT_ZERO != trainSafeHeadAc))
                    {
                        /*判断后方计轴是否是列车安全车头占压计轴且是否带有后端危险区域*/
                        if (AC_DIR_FARAWAY == trainDirInAc)
                        {
                            if (FLAG_SET == GetTrainSuspectTail(frontTrainId))
                            {
                                if (rearAcId == trainSafeHeadAc)
                                {
                                    /*列车需要紧急制动*/
                                    SetTrainToModeToRM0(trainId);
                                    LogPrintf(1u,"%d-S5\n",trainId);
                                } 
                                else
                                {
                                    /*将移动授权放到后方计轴的始端位置*/
                                    if (RETURN_SUCCESS == CheckAcTopPosition(rearAcId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
                                    {
                                        SetMaTailLink(trainId,acTopLink);
                                        SetMaTailOffset(trainId,acTopOffset);
                                    } 
                                    else
                                    {
                                        SetTrainToModeToRM0(trainId);
                                        LogPrintf(1u,"%d-S6\n",trainId);
                                    }
                                }
                            } 
                            else
                            {
                                if (FLAG_SET == flagType)
                                {
                                    /*处理前方列车引起的移动授权更新*/
                                    CalculateTrainMaByFrontTrainTail(trainId,frontTrainId,frontAcId);
                                } 
                                else
                                {
                                    /*不处理*/
                                }
                            }
                        } 
                        else
                        {
                            if (FLAG_SET == GetTrainSuspectHead(trainId))
                            {
                                if (rearAcId == trainSafeHeadAc)
                                {
                                    /*列车需要紧急制动*/
                                    SetTrainToModeToRM0(trainId);
                                    LogPrintf(1u,"%d-S7\n",trainId);
                                } 
                                else
                                {
                                    /*将移动授权放到后方计轴的始端位置*/
                                    if (RETURN_SUCCESS == CheckAcTopPosition(rearAcId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
                                    {
                                        SetMaTailLink(trainId,acTopLink);
                                        SetMaTailOffset(trainId,acTopOffset);
                                    } 
                                    else
                                    {
                                        SetTrainToModeToRM0(trainId);
                                        LogPrintf(1u,"%d-S8\n",trainId);
                                    }
                                }
                            } 
                            else
                            {
                                if (FLAG_SET == flagType)
                                {
                                    /*处理前方列车引起的移动授权更新*/
                                    CalculateTrainMaByFrontTrainHead(trainId,frontTrainId,frontAcId);
                                } 
                                else
                                {
                                    /* pbw 2017.7.17 */
                                    if (RETURN_SUCCESS == CheckAcTopPosition(rearAcId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
                                    {
                                        /*进路外方的计轴区段内的列车无前端可疑标记,回撤移动授权*/
                                        checkRtn = CheckNextPointOnDistance(acTopLink,acTopOffset,TrainDirChangeForCheck(trainId),((UINT32_S)GetLineMaBackDistance()),&backLink,&backOffset,&errorSwitchId);

                                        if (0x03U == checkRtn)
                                        {
                                            SetMaTailLink(trainId,backLink);
                                            SetMaTailOffset(trainId,backOffset);
                                        }
                                        else
                                        {
                                            SetTrainToModeToRM0(trainId);
                                            LogPrintf(1u,"%d-B73\n",trainId);
                                        }
                                    } 
                                    else
                                    {
                                        SetTrainToModeToRM0(trainId);
                                        LogPrintf(1u,"%d-B7333\n",trainId);
                                    }                                          
                                }
                            }
                        }
                    }
                    else
                    {
                        /*列车需要紧急制动*/
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-S9\n",trainId);
                    }
                }
                else
                {
                    SetTrainToModeToRM0(trainId);
                    LogPrintf(1u,"%d-S10\n",trainId);
                }
            }

            rtnValue = RETURN_SUCCESS;
        }	
    }
#endif
    return rtnValue;
}

/*
* 函数名称： JudgeTrainMaByAcOfSameAcInfo
* 功能描述： 处理同计轴区段内的列车对当前列车移动授权的影响
* 输入参数： const UINT16_S trainId,列车Id
*            const UINT16_S acId，列车占压计轴区段
*            const UINT8_S frontTrainIndex，前方列车计轴序列下标
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainMaByAcOfSameAcInfo(const UINT16_S trainId,const UINT16_S acId,const UINT8_S frontTrainIndex)
{
    UINT16_S frontTrainId = DEFAULT_ZERO;

    if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(acId,frontTrainIndex,&frontTrainId))
    {
        if (FLAG_SET == GetTrainSuspectTail(frontTrainId))
        {
            /*前方列车带后端可疑,后方列车需要直接紧急制动*/
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-B15\n",trainId);
        } 
        else
        {
            /*处理前方列车引起的移动授权改变*/
            CalculateTrainMaByFrontTrainTail(trainId,frontTrainId,acId);
        }
    }
    else
    {
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B16\n",trainId);
    }
}

/*
* 函数名称： CalculateTrainMaByFrontTrainTail
* 功能描述： 计算前方列车车尾引起的移动授权更新
* 输入参数： const UINT16_S trainId,列车Id
*            const UINT16_S frontTrainId,前方列车ID
*            const UINT16_S acId,待处理计轴Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateTrainMaByFrontTrainTail(const UINT16_S trainId,const UINT16_S frontTrainId,const UINT16_S acId)
{
    UINT8_S trainType = DEFAULT_ZERO;
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S acTopLink = DEFAULT_ZERO;
    UINT32_S acTopOffset = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S checkDir = DEFAULT_ZERO;
    UINT16_S backLink = DEFAULT_ZERO;
    UINT32_S backOffset = DEFAULT_ZERO;
    UINT16_S errorSwitchId = DEFAULT_ZERO;
    UINT8_S checkRtn = DEFAULT_ZERO;
    UINT8_S traceRmTrainType = DEFAULT_ZERO;

    trainType = GetTrainType(frontTrainId);

    /*判断前方列车的状态*/
    switch (trainType)
    {
    case TRAIN_MODE_CBTC:
    case TRAIN_MODE_TO_RM0:
        /*设置列车移动授权为前方列车车尾*/
        if (RETURN_SUCCESS == GetTrainSafeLoc(frontTrainId,&trainSafeLocStru))
        {
            SetMaTailLink(trainId,trainSafeLocStru.TrainTailLink);
            SetMaTailOffset(trainId,trainSafeLocStru.TrainTailOffset);
        } 
        else
        {
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-B17\n",trainId);
        }

        break;
    case TRAIN_MODE_RM:
    case TRAIN_MODE_RM0:

        traceRmTrainType = GetZcTraceRmTrainType();
        if (TRACE_RM_TRAIN_TYPE_BACK == traceRmTrainType)
        {
            /*将移动授权设置在当前计轴始端退行防护距离的位置*/
            /*查询后方计轴*/
            trainDir = GetTrainUnsafeDirection(trainId);

            if (RETURN_SUCCESS == CheckAcTopPosition(acId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
            {
                checkDir = TrainDirChangeForCheck(trainId);

                checkRtn = CheckNextPointOnDistance(acTopLink,acTopOffset,checkDir,((UINT32_S)GetLineMaBackDistance()),&backLink,&backOffset,&errorSwitchId);

                if (0x03U == checkRtn)
                {
                    SetMaTailLink(trainId,backLink);
                    SetMaTailOffset(trainId,backOffset);
                    SetMaEndObsType(trainId,MA_OBS_TYPE_COMM_UNCT_TRAIN);
                } 
                else if ((0x02U == checkRtn) || (0x01U == checkRtn))
                {
                    SetMaTailLink(trainId,acTopLink);
                    SetMaTailOffset(trainId,acTopOffset);
                    SetMaEndObsType(trainId,MA_OBS_TYPE_COMM_UNCT_TRAIN);
                } 
                else
                {
                    SetTrainToModeToRM0(trainId);
                    LogPrintf(1u,"%d-B18\n",trainId);
                }
            } 
            else
            {
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B19\n",trainId);
            }
        } 
        else
        {
            if (TRACE_RM_TRAIN_TYPE_TAIL == traceRmTrainType)
            {
                /*设置列车移动授权为前方列车车尾*/
                if (RETURN_SUCCESS == GetTrainSafeLoc(frontTrainId,&trainSafeLocStru))
                {
                    SetMaTailLink(trainId,trainSafeLocStru.TrainTailLink);
                    SetMaTailOffset(trainId,trainSafeLocStru.TrainTailOffset);
                } 
                else
                {
                    SetTrainToModeToRM0(trainId);
                    LogPrintf(1u,"%d-B20\n",trainId);
                }
            } 
            else
            {
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B21\n",trainId);
            }
        }

        break;
    default:
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B22\n",trainId);
        break;
    }
}

/*
* 函数名称： CalculateTrainMaByFrontTrainHead
* 功能描述： 计算前方列车车头引起的移动授权更新
* 输入参数： const UINT16_S trainId,列车Id
*            const UINT16_S frontTrainId,前方列车ID
*            const UINT16_S acId,待处理计轴Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateTrainMaByFrontTrainHead(const UINT16_S trainId,const UINT16_S frontTrainId,const UINT16_S acId)
{
    UINT8_S trainMode = DEFAULT_ZERO;
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S acTopLink = DEFAULT_ZERO;
    UINT32_S acTopOffset = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S checkDir = DEFAULT_ZERO;
    UINT16_S backLink = DEFAULT_ZERO;
    UINT32_S backOffset = DEFAULT_ZERO;
    UINT16_S errorSwitchId = DEFAULT_ZERO;
    UINT8_S checkRtn = DEFAULT_ZERO;

    trainMode = GetTrainMode(frontTrainId);

    /*判断前方列车的状态*/
    switch (trainMode)
    {
    case TRAIN_MODE_CBTC:
    case TRAIN_MODE_TO_RM0:
        /*设置列车移动授权为前方列车车尾*/
        if (RETURN_SUCCESS == GetTrainSafeLoc(frontTrainId,&trainSafeLocStru))
        {
            SetMaTailLink(trainId,trainSafeLocStru.TrainHeadLink);
            SetMaTailOffset(trainId,trainSafeLocStru.TrainHeadOffset);
        } 
        else
        {
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-B23\n",trainId);
        }

        break;
    case TRAIN_MODE_RM:
    case TRAIN_MODE_RM0:
        /*将移动授权设置在当前计轴始端退行防护距离的位置*/
        /*查询后方计轴*/
        trainDir = GetTrainUnsafeDirection(trainId);

        if (RETURN_SUCCESS == CheckAcTopPosition(acId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
        {
            if (0x55U == trainDir)
            {
                checkDir = 0xaaU;
            } 
            else if (0xaaU == trainDir)
            {
                checkDir = 0x55U;
            } 
            else
            {
                /*不处理*/
            }

            checkRtn = CheckNextPointOnDistance(acTopLink,acTopOffset,checkDir,((UINT32_S)GetLineMaBackDistance()),&backLink,&backOffset,&errorSwitchId);

            if (0x03U == checkRtn)
            {
                SetMaTailLink(trainId,backLink);
                SetMaTailOffset(trainId,backOffset);
                SetMaEndObsType(trainId,MA_OBS_TYPE_COMM_UNCT_TRAIN);
            } 
            else if ((0x02U == checkRtn) || (0x01U == checkRtn))
            {
                SetMaTailLink(trainId,acTopLink);
                SetMaTailOffset(trainId,acTopOffset);
                SetMaEndObsType(trainId,MA_OBS_TYPE_COMM_UNCT_TRAIN);
            } 
            else
            {
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B24\n",trainId);
            }
        } 
        else
        {
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-B25\n",trainId);
        }

        break;
    default:
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B26\n",trainId);
        break;
    }
}

/*
* 函数名称： JudgeTrainMaByStationInfo
* 功能描述： 处理以站台为条件的列车的移动授权信息管理
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainMaByStationInfo(const UINT16_S trainId)
{
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S acNum = DEFAULT_ZERO;
    UINT16_S acIdBuff[ZC_TWO_POINT_AC_NUM_MAX] = {DEFAULT_ZERO};
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT16_S terminalLink = DEFAULT_ZERO;
    UINT32_S terminalOffset = DEFAULT_ZERO;
    UINT16_S trainUnSafeHeadAc = DEFAULT_ZERO;
    UINT16_S topLink = DEFAULT_ZERO;
    UINT32_S topOffset = DEFAULT_ZERO;
    UINT16_S tempRtnOfCheck = DEFAULT_ZERO;
    UINT16_S frontAcId = DEFAULT_ZERO;
    UINT16_S frontAcLink = DEFAULT_ZERO;
    UINT32_S frontAcOffset = DEFAULT_ZERO;
    UINT16_S checkLinkId = DEFAULT_ZERO;
    UINT16_S maTailLink = DEFAULT_ZERO;
    UINT32_S maTailOffset = DEFAULT_ZERO;
    UINT8_S rtnLoc = RETURN_ERROR;
    UINT8_S rtnCalLink = 0U;
    UINT8_S rtnOfNextPoint = DEFAULT_ZERO; /* 获取下一点函数的返回值 */
    UINT16_S overlapId = DEFAULT_ZERO;
    UINT16_S outSeg = DEFAULT_ZERO;
    UINT32_S outOffset = DEFAULT_ZERO;
    UINT16_S errorSwitchId = DEFAULT_ZERO;
    UINT8_S i = DEFAULT_ZERO;   
    UINT16_S tmpTrainId = DEFAULT_ZERO;
    TrainSafeLocStruct tmpTrainSafeLocStru;
    UINT8_S breakFlag = FLAG_UNSET;

    MemorySet(&acIdBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)));

    rtnLoc = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);
    trainDir = GetTrainUnsafeDirection(trainId);

    rtnCalLink = CalculatePointOfInsideLink(trainDir,GetMaTailLink(trainId),GetMaTailOffset(trainId),&checkLinkId);

    if ((RETURN_SUCCESS == rtnLoc) && (1U == rtnCalLink))
    {
        /*查询以非安全车头位置至MA终点位置的计轴区段序列*/
        if (RETURN_SUCCESS == CheckAcOrderBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,checkLinkId,trainDir,&acNum,acIdBuff))
        {
            for (cycle = DEFAULT_ZERO;cycle < acNum;cycle++)
            {
                acId = acIdBuff[(acNum - cycle) - 1U];

                tempRtnOfCheck = CheckAcBelongToStation(acId);

                if (RETURN_SUCCESS == tempRtnOfCheck)
                {
                    /* 属于站台区域,获取站台终端位置 */                   
                    if (RETURN_SUCCESS == CheckAcTerminalPosition(acId,((UINT16_S)trainDir),&terminalLink,&terminalOffset))
                    {
                        /*获取前方计轴区段*/
                        frontAcId = DEFAULT_ZERO;

                        if (1U == CheckFrontACStatus(acId,trainDir,&frontAcId))
                        {
                            /*获取前方计轴始端位置*/
                            if (RETURN_SUCCESS == CheckAcTopPosition(frontAcId,((UINT16_S)trainDir),&frontAcLink,&frontAcOffset))
                            {
                                maTailLink = GetMaTailLink(trainId);
                                maTailOffset = GetMaTailOffset(trainId);

                                if (((maTailLink == terminalLink) && (maTailOffset == terminalOffset))
                                    || ((maTailLink == frontAcLink) && (maTailOffset == frontAcOffset)))
                                {
                                    /*移动授权终点和站台终端重合,判断列车非安全车头是否位于站台内*/							
                                    trainUnSafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);

                                    if (trainUnSafeHeadAc == acId)
                                    {
                                        if (FLAG_SET == GetTrainStopArea(trainId))
                                        {
                                            /*维持当前移动授权终点*/
                                        } 
                                        else
                                        {
                                            /*未停稳,紧急制动*/
                                            SetTrainToModeToRM0(trainId);
                                            LogPrintf(1u,"%d-B27\n",trainId);
                                        }
                                    } 
                                    else
                                    {
                                        /*列车不位于站台内,回撤MA至站台始端*/
                                        /*获取站台始端位置*/
                                        if (RETURN_SUCCESS == CheckAcTopPosition(acId,((UINT16_S)trainDir),&topLink,&topOffset))
                                        {
                                            /*将移动授权回撤至站台始端*/
                                            SetMaTailLink(trainId,topLink);
                                            SetMaTailOffset(trainId,topOffset);
                                        } 
                                        else
                                        {
                                            /*紧急制动*/
                                            SetTrainToModeToRM0(trainId);
                                            LogPrintf(1u,"%d-B28\n",trainId);
                                        }
                                    }
                                } 
                                else
                                {
                                    /*判断移动授权是否位于站台区域内*/
                                    /*获取站台始端位置*/
                                    if (RETURN_SUCCESS == CheckAcTopPosition(acId,((UINT16_S)trainDir),&topLink,&topOffset))
                                    {
                                        if ((maTailLink == topLink)
                                            && (maTailOffset != topOffset))
                                        {
                                            /*将移动授权回撤至站台始端*/
                                            SetMaTailLink(trainId,topLink);
                                            SetMaTailOffset(trainId,topOffset);
                                        } 
                                        else
                                        {
                                            /*不处理*/
                                            /* 判断MA终点是否在站台轨或者沿运行方向站台轨终端到最大保护区段之间 */
                                            /* pbw 201705025 前车安全车尾在站台轨终端 */
#if 1                                        
                                            /* 遍历该该ZC内除本车以外的其他车的安全车尾位置 */
                                            breakFlag = FLAG_UNSET;

                                            for(i = DEFAULT_ZERO;i < GetTrainCurSum();i++)
                                            {
                                                tmpTrainId = GetTrainIdOfIndex(i);

                                                if (tmpTrainId != trainId)
                                                {
                                                    if (RETURN_SUCCESS == GetTrainSafeLoc(tmpTrainId,&tmpTrainSafeLocStru))
                                                    {
                                                        if ((tmpTrainSafeLocStru.TrainTailLink == maTailLink)
                                                            && (tmpTrainSafeLocStru.TrainTailOffset == maTailOffset))
                                                        {
                                                            breakFlag = FLAG_SET;
                                                            break;
                                                        }
                                                    }                               
                                                }
                                            }

                                            if ((FLAG_SET == breakFlag) 
                                                && (1u == CalPointIsOnOverlap(maTailLink,maTailOffset,trainDir,&overlapId)))
                                            {
                                                /* MA终点在保护区段内 */                      
                                                rtnOfNextPoint = CheckNextPointOnDistance(frontAcLink,frontAcOffset,trainDir,(UINT32_S)GetLineMinOverlapLength(),&outSeg,&outOffset,&errorSwitchId);

                                                if((3u == rtnOfNextPoint)
                                                    && (2u == CheckLocRelationBetweenTwoPoints(frontAcLink,frontAcOffset,maTailLink,maTailOffset,trainDir))
                                                    && (2u == CheckLocRelationBetweenTwoPoints(maTailLink,maTailOffset,outSeg,outOffset,trainDir)))
                                                {
                                                    /* 将移动授权回撤至站台始端 */
                                                    SetMaTailLink(trainId,topLink);
                                                    SetMaTailOffset(trainId,topOffset);
                                                }
                                            }
#endif             
                                        }
                                    } 
                                    else
                                    {
                                        /*紧急制动*/
                                        SetTrainToModeToRM0(trainId);
                                        LogPrintf(1u,"%d-B29\n",trainId);
                                    }
                                }
                            } 
                            else
                            {
                                /*查询失败,将MA回撤至站台始端*/
                                /*获取站台始端位置*/
                                if (RETURN_SUCCESS == CheckAcTopPosition(acId,((UINT16_S)trainDir),&topLink,&topOffset))
                                {
                                    /*将移动授权回撤至站台始端*/
                                    SetMaTailLink(trainId,topLink);
                                    SetMaTailOffset(trainId,topOffset);
                                } 
                                else
                                {
                                    /*紧急制动*/
                                    SetTrainToModeToRM0(trainId);
                                    LogPrintf(1u,"%d-B30\n",trainId);
                                }
                            }
                        } 
                        else
                        {
                            /* 不处理 */
                        }
                    } 
                    else
                    {
                        /*紧急制动*/
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-B31\n",trainId);
                    }
                } 
                else
                {
                    if (RETURN_ERROR == tempRtnOfCheck)
                    {
                        /*紧急制动*/
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-B32\n",trainId);
                    } 
                    else
                    {
                        /*不属于站台*/
                    }
                }
            }
        }
        else
        {
            JudgeCommUnCtTrainForMa(trainId);
        }
    }
    else
    {
        /* 获取位置和查找MA终点所在Link任意1个失败 */
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B33\n",trainId);
    }

}

/*
* 函数名称： CalculateObsInfoBelongToMaArea
* 功能描述： 计算移动授权范围内的障碍物信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateObsInfoBelongToMaArea(const UINT16_S trainId)
{
    UINT16_S trainMaHeadLink = DEFAULT_ZERO;
    UINT16_S trainMaTailLink = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S switchNum = DEFAULT_ZERO;
    UINT16_S switchIdBuff[ZC_TWO_POINT_SWITCH_NUM_MAX] = {DEFAULT_ZERO};
    UINT8_S psdNum = DEFAULT_ZERO;
    UINT16_S psdIdBuff[ZC_TWO_POINT_PSD_NUM_MAX] = {DEFAULT_ZERO};
    UINT8_S esbNum = DEFAULT_ZERO;
    UINT16_S esbIdBuff[ZC_TWO_POINT_ESB_NUM_MAX] = {DEFAULT_ZERO};
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S obsNum = DEFAULT_ZERO;
    ObsOfMAStruct obsOfMaStruBuff[MA_AREA_OBS_SUM_MAX];
    UINT8_S addIndex = DEFAULT_ZERO;
    UINT8_S rtnCalHeadLink = 0U;
    UINT8_S rtnCalTailLink = 0U;

    MemorySet(&switchIdBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_SWITCH_NUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_SWITCH_NUM_MAX)));
    MemorySet(&psdIdBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_PSD_NUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_PSD_NUM_MAX)));
    MemorySet(&esbIdBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_ESB_NUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_ESB_NUM_MAX)));
    MemorySet(&obsOfMaStruBuff[0],((UINT32_S)(sizeof(ObsOfMAStruct) * MA_AREA_OBS_SUM_MAX)),
        0U,((UINT32_S)(sizeof(ObsOfMAStruct) * MA_AREA_OBS_SUM_MAX)));

    trainDir = GetTrainUnsafeDirection(trainId);
    rtnCalHeadLink = CalculatePointOfInsideLink(TrainDirChangeForCheck(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),&trainMaHeadLink);
    rtnCalTailLink = CalculatePointOfInsideLink(trainDir,GetMaTailLink(trainId),GetMaTailOffset(trainId),&trainMaTailLink);

    if ((1U == rtnCalHeadLink) && (1U == rtnCalTailLink))
    {
        /*查询移动授权范围内的道岔序列*/
        if (RETURN_ERROR != CheckSwitchOrderBetweenTwoPoints(trainMaHeadLink,trainMaTailLink,
            trainDir,&switchNum,switchIdBuff))
        {
            for (cycle = DEFAULT_ZERO;cycle < switchNum;cycle++)
            {
                obsOfMaStruBuff[obsNum].ObsId = switchIdBuff[addIndex];
                obsOfMaStruBuff[obsNum].ObsType = OBS_TYPE_POINT;
                /*填写道岔的状态信息*/
                obsOfMaStruBuff[obsNum].ObsStatus = GetSwitchPosStatus(switchIdBuff[addIndex]);

                if (SWITCH_STATE_LOCK ==  GetSwitchPosStatus(switchIdBuff[addIndex]))
                {
                    obsOfMaStruBuff[obsNum].ObsLockStatus = obsOfMaStruBuff[obsNum].ObsStatus;
                } 
                else
                {
                    obsOfMaStruBuff[obsNum].ObsLockStatus = SWITCH_STATE_LOSE;
                }

                obsNum++;

                addIndex = addIndex + 2U;
            }

            /*查询PSD序列*/
            if (RETURN_ERROR != CheckPsdOrderBetweenTwoPoints(trainMaHeadLink,trainMaTailLink,
                trainDir,&psdNum,psdIdBuff))
            {
                for (cycle = DEFAULT_ZERO;cycle < psdNum;cycle++)
                {
                    obsOfMaStruBuff[obsNum].ObsId = psdIdBuff[cycle];
                    obsOfMaStruBuff[obsNum].ObsType = OBS_TYPE_PSD;

                    /*填写psd的状态信息*/
                    obsOfMaStruBuff[obsNum].ObsStatus = GetPsdStatus(psdIdBuff[cycle]);
                    obsOfMaStruBuff[obsNum].ObsLockStatus = GetPsdStatus(psdIdBuff[cycle]);
                    obsNum++;
                }

                /*查询Esb序列*/
                if (RETURN_ERROR != CheckEsbOrderBetweenTwoPoints(trainMaHeadLink,trainMaTailLink,
                    trainDir,&esbNum,esbIdBuff))
                {
                    for (cycle = DEFAULT_ZERO;cycle < esbNum;cycle++)
                    {
                        obsOfMaStruBuff[obsNum].ObsId = esbIdBuff[cycle];
                        obsOfMaStruBuff[obsNum].ObsType = OBS_TYPE_ESB;
                        /*填写esb的状态信息*/
                        obsOfMaStruBuff[obsNum].ObsStatus = GetEsbStatus(esbIdBuff[cycle]);
                        obsOfMaStruBuff[obsNum].ObsLockStatus =GetEsbStatus(esbIdBuff[cycle]);
                        obsNum++;
                    }

                    /*填写移动授权范围内的障碍物信息*/
                    SetMaObsNum(trainId,obsNum);
                    SetObsOfMAStru(trainId,obsOfMaStruBuff,obsNum);
                } 
                else
                {
                    SetTrainToModeToRM0(trainId);
                    LogPrintf(1u,"%d-B34\n",trainId);
                }
            } 
            else
            {
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B35\n",trainId);
            }
        } 
        else
        {
            JudgeCommUnCtTrainForMa(trainId);
        }
    } 
    else
    {
        /* 查找MA起点所在Link和查找MA终点所在Link任意1个失败 */
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B36\n",trainId);
    }

}

/*
* 函数名称： CalculateTsrInfoBelongToMaArea
* 功能描述： 计算移动授权范围内的临时限速信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateTsrInfoBelongToMaArea(const UINT16_S trainId)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S cycleSignal = DEFAULT_ZERO;
    UINT8_S signalZcTsrNum = DEFAULT_ZERO;
    UINT16_S tsrZcId = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    TsrOfMAStruct tsrOfMaStruBuff[MA_AREA_TSR_SUM_MAX];
    UINT8_S tsrOfMaNum = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S  sectionNum;                                   
    UINT16_S  sectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX] = {DEFAULT_ZERO};    
    UINT8_S rtnOfSectionId = DEFAULT_ZERO;
    UINT8_S superAreaNum = DEFAULT_ZERO;
    AreaInfoStruct superArea[5]; 
    AreaInfoStruct maArea;
    UINT8_S cycleSuperArea = DEFAULT_ZERO;
    UINT16_S tsrSpeed = DEFAULT_ZERO;

    /*初始化*/
    MemorySet(&tsrOfMaStruBuff[0],((UINT32_S)(sizeof(TsrOfMAStruct) * MA_AREA_TSR_SUM_MAX)),
        0U,((UINT32_S)(sizeof(TsrOfMAStruct) * MA_AREA_TSR_SUM_MAX)));
    MemorySet(&sectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TSR_SECTION_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TSR_SECTION_SUM_MAX)));
    MemorySet(&superArea[DEFAULT_ZERO],((UINT32_S)(sizeof(AreaInfoStruct)*5U)),
        DEFAULT_ZERO,((UINT32_S)(sizeof(AreaInfoStruct)*5U)));
    MemorySet(&maArea,((UINT32_S)(sizeof(AreaInfoStruct))),DEFAULT_ZERO,((UINT32_S)(sizeof(AreaInfoStruct))));

    /*获取临时限速区域*/
    trainDir = GetTrainUnsafeDirection(trainId);
    maArea.startSegId = GetMaHeadLink(trainId);
    maArea.startSegOffSet = GetMaHeadOffset(trainId);
    maArea.endSegId = GetMaTailLink(trainId);
    maArea.endSegOffSet = GetMaTailOffset(trainId);

    /*获取临时限速信息*/
    for (cycle = DEFAULT_ZERO;cycle < GetTsrOfZcSum();cycle++)
    {
        tsrZcId = GeTsrOfBelongZcId((UINT16_S)cycle);
        signalZcTsrNum = GetZcIdOfTsrNum(tsrZcId);

        for (cycleSignal = DEFAULT_ZERO;cycleSignal < signalZcTsrNum;cycleSignal++)
        {
            /*获取临时限速包含的逻辑区段信息*/
            sectionNum = GetSingleTsrDataOfSectionNum(tsrZcId,((UINT16_S)cycleSignal));
            rtnOfSectionId = GetSingleTsrDataOfSectionBuff(tsrZcId,((UINT16_S)cycleSignal),((UINT8_S)(SINGLE_TSR_SECTION_SUM_MAX)),sectionIdBuff);
            tsrSpeed = (UINT16_S)GetSingleTsrDataOfSpeed(tsrZcId,(UINT16_S)cycleSignal);

            if ((0U < sectionNum) && (RETURN_SUCCESS == rtnOfSectionId) && (0U != tsrSpeed))
            {
                /*初始化*/
                superAreaNum = DEFAULT_ZERO;
                MemorySet(&superArea[0],((UINT32_S)(sizeof(AreaInfoStruct)*5U)),DEFAULT_ZERO,((UINT32_S)(sizeof(AreaInfoStruct)*5U)));

                /*查询两个区域的重合区域*/
                if (RETURN_SUCCESS == CheckSuperpositionBetweenTwoArea(sectionNum,sectionIdBuff,maArea,trainDir,&superAreaNum,superArea))
                {
                    for (cycleSuperArea = DEFAULT_ZERO;cycleSuperArea < superAreaNum;cycleSuperArea++)
                    {
                        tsrOfMaStruBuff[tsrOfMaNum].TsrHeadLink = superArea[cycleSuperArea].startSegId;
                        tsrOfMaStruBuff[tsrOfMaNum].TsrHeadOffset = superArea[cycleSuperArea].startSegOffSet;
                        tsrOfMaStruBuff[tsrOfMaNum].TsrTailLink = superArea[cycleSuperArea].endSegId;
                        tsrOfMaStruBuff[tsrOfMaNum].TsrTailOffset = superArea[cycleSuperArea].endSegOffSet;
                        tsrOfMaStruBuff[tsrOfMaNum].TsrSpeed = tsrSpeed;
                        tsrOfMaStruBuff[tsrOfMaNum].BelongZcId = tsrZcId;
                        tsrOfMaNum++;
                    }
                } 
                else
                {
                    SetTrainToModeToRM0(trainId);
                    breakFlag = FLAG_SET;
                    LogPrintf(1u,"%d-B37\n",trainId);
                    break;
                }
            } 
            else
            {
                SetTrainToModeToRM0(trainId);
                breakFlag = FLAG_SET;
                LogPrintf(1u,"%d-B38\n",trainId);
                break;
            }
        }

        if (FLAG_SET == breakFlag)
        {
            break;
        } 
        else
        {
            /*Do nothing currently !*/
        }
    }

    if (FLAG_SET == breakFlag)
    {
        /*Do nothing currently !*/
    } 
    else
    {
        if (DEFAULT_ZERO < tsrOfMaNum)
        {
            /*填写移动授权范围内的临时限速信息*/
            SetMaTsrNum(trainId,tsrOfMaNum);
            SetTsrOfMAStru(trainId,tsrOfMaStruBuff,tsrOfMaNum);
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*
* 函数名称： JudgeReverseStateMaInfo
* 功能描述： 处理折返状态下的移动授权信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeReverseStateMaInfo(const UINT16_S trainId)
{
    UINT16_S routeIdBuff[SIZE_MAX_ROUTENUM] = {DEFAULT_ZERO};
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT16_S routeId = DEFAULT_ZERO;
    UINT16_S trainUnSafeHeadAc = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S acBelock = DEFAULT_ZERO;
    UINT8_S checkFlag = DEFAULT_ZERO;

    MemorySet(&routeIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)),0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)));

    /*获取列车匹配的进路信息*/
    if (RETURN_SUCCESS == GetTrainMatchedRouteIdBuff(trainId,routeIdBuff))
    {
        /*判断列车是否匹配进路*/
        if (DEFAULT_ZERO != routeIdBuff[DEFAULT_ZERO])
        {
            CalculateTrainMa(trainId);
        } 
        else
        {
            /*判断列车是否位于折返轨*/
            if (RETURN_SUCCESS == GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru))
            {
                trainUnSafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);
                trainDir = GetTrainUnsafeDirection(trainId);

                /*获取非安全车头位置对于的计轴区段是否属于某条办理进路*/
                acBelock = GetAcBelock(trainUnSafeHeadAc);
                checkFlag = CheckPointBelongReverseArea(trainUnSafeLocStru.TrainHeadLink);

                if ((trainUnSafeLocStru.TrainHeadLink == trainUnSafeLocStru.TrainTailLink)
                    && (RETURN_SUCCESS == checkFlag)
                    && (AC_LOCK_STATUS == acBelock))
                {
                    /*判断位于折返轨的列车是否位于某条折返进路(采用两个方向共同查询)*/
                    if (2U == CalulateAcIdBelongUseableRoute(trainUnSafeHeadAc,trainDir,&routeId))
                    {
                        /*列车当前运行方向查询进路成功*/
                    } 
                    else
                    {
                        /*列车此时已换端,采用列车当前运行方向相反方向查询进路*/
                        if (2U == CalulateAcIdBelongUseableRoute(trainUnSafeHeadAc,TrainDirChangeForCheck(trainId),&routeId))
                        {
                            /*获取进路Id*/
                        } 
                        else
                        {
                            /*不处理*/
                        }
                    }

                    /*获取进路属性*/
                    if ((LINE_REVERSE_ROUTE == GetRouteType(routeId))
                        && (trainDir != GetSignalProtectDir(GetRouteOfSingalId(routeId))))
                    {
                        /*计算折返状态下的移动授权信息*/
                        CalculaReverseStateMaInfo(trainId);
                    } 
                    else
                    {
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-B39\n",trainId);
                    }
                } 
                else
                {
                    SetTrainToModeToRM0(trainId);
                    LogPrintf(1u,"%d-B40\n",trainId);
                }
            } 
            else
            {
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B41\n",trainId);
            }
        }
    }    
}

/*
* 函数名称： CalculaReverseStateMaInfo
* 功能描述： 计算折返位置的移动授权信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculaReverseStateMaInfo(const UINT16_S trainId)
{
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S trainUnSafeHeadAc = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S acOfLink = DEFAULT_ZERO;
    UINT32_S acOfOffset = DEFAULT_ZERO;
    UINT8_S checkFlag = RETURN_ERROR;
    UINT8_S getFlag = RETURN_ERROR;
    UINT16_S maEndAcId = DEFAULT_ZERO;
    UINT16_S frontAcId = DEFAULT_ZERO;
    UINT16_S checkLinkId = DEFAULT_ZERO;
    UINT8_S rtnCheckLink = 0U;

    /*获取列车信息*/
    trainUnSafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);
    trainDir = GetTrainUnsafeDirection(trainId);
    checkFlag = CheckAcTerminalPosition(trainUnSafeHeadAc,((UINT16_S)trainDir),&acOfLink,&acOfOffset);
    getFlag = GetTrainSafeLoc(trainId,&trainSafeLocStru);

    if ((RETURN_SUCCESS == checkFlag)
        && (RETURN_SUCCESS == getFlag))
    {
        /*清除MA信息*/
        ClearSingleTrainMaInfo(trainId);

        /*申请MA数组位置*/
        SetMaStatusTrainId(trainId);
        SetMaType(trainId,NORMAL_MA_TYPE);

        /*填写MA信息*/
        SetMaHeadLink(trainId,trainSafeLocStru.TrainTailLink);
        SetMaHeadOffset(trainId,trainSafeLocStru.TrainTailOffset);
        SetMaHeadDir(trainId,trainDir);
        SetMaTailLink(trainId,acOfLink);
        SetMaTailOffset(trainId,acOfOffset);
        SetMaTailDir(trainId,trainDir);

        /* pbw 2017.8.2 增加对MA终点外方计轴区段的判断 */
        rtnCheckLink = CalculatePointOfInsideLink(trainDir,acOfLink,acOfOffset,&checkLinkId);

        if (1U == rtnCheckLink)
        {
            maEndAcId = CheckPositionBelongAc(checkLinkId);	

            if (DEFAULT_ZERO != maEndAcId)
            {
                /*查询当前计轴前方计轴区段*/
                if (RETURN_SUCCESS == CheckFrontACStatus(maEndAcId,trainDir,&frontAcId))
                {
                    if (AC_FREE_STATUS == GetAcStatusNow(frontAcId))
                    {
                        /*不处理*/
                    } 
                    else
                    {
                        /*根据前方计轴信息处理移动授权*/
                        JudgeTrainMaByAcOfFrontAcInfo(FLAG_UNSET,trainId,maEndAcId,frontAcId);
                    }
                } 
                else
                {
                    /*查询前方计轴失败,不处理*/
                }
            } 
            else
            {
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-AB10\n",trainId);
            }
        } 
        else
        {
            /* 查询MA终点内方的Link失败,不处理 */
        }   

        if (DEFAULT_ZERO != GetMaTailLink(trainId))
        {
            /*填写Ma终点类型为其他*/
            SetMaEndAttribute(trainId,MA_END_ATT_OTHER);

            /*计算移动授权是否需要调整*/
            CalculatAdjustMaEndInfo(trainId);
        } 
        else
        {
            /*不处理*/
        }

        /*计算移动授权范围内的障碍物信息*/
        if (DEFAULT_ZERO != GetMaTailLink(trainId))
        {
            CalculateObsInfoBelongToMaArea(trainId);
        }

        /*计算移动授权范围内的临时限速信息*/
        if (DEFAULT_ZERO != GetMaTailLink(trainId))
        {
            CalculateTsrInfoBelongToMaArea(trainId);
        }
    } 
    else
    {
        /*不处理*/
    }
}

/*
* 函数名称： JudgeCancellationStateMaInfo
* 功能描述： 处理注销状态下的移动授权信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeCancellationStateMaInfo(const UINT16_S trainId)
{
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S getLocFlag = RETURN_ERROR;
    UINT8_S trainOutType = DEFAULT_ZERO;
    UINT16_S prePeriodMaLink = DEFAULT_ZERO;
    UINT32_S prePeriodMaOffset = DEFAULT_ZERO;

    trainDir = GetTrainUnsafeDirection(trainId);
    getLocFlag = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);

    if ((RETURN_SUCCESS == getLocFlag) && (DEFAULT_ZERO != trainDir))
    {
        trainOutType = GetTrainOutType(trainId);

        /* 判断给车载输出的类型是否为退出CBTC申请确认 */
        if (OUT_TRAIN_TOEXITCBTC == trainOutType)
        {
            /* 填写为注销状态下的移动授权类型 */
            SetMaType(trainId,CANCELLATION_MA_TYPE);

            /* PBW,2016.7.10 为了与ATP调试需要MA终点类型 */
            /* 设置MA终点为退出CBTC区域 */
            SetMaEndAttribute(trainId,MA_END_ATT_CBTC);

            SetMaHeadLink(trainId,trainUnSafeLocStru.TrainTailLink);
            SetMaHeadOffset(trainId,trainUnSafeLocStru.TrainTailOffset);
            SetMaHeadDir(trainId,trainDir);

            /* 维持上一周期的MA终点 */
            prePeriodMaLink = GetMaTailLink(trainId);
            prePeriodMaOffset = GetMaTailOffset(trainId);

            SetMaTailLink(trainId,prePeriodMaLink);
            SetMaTailOffset(trainId,prePeriodMaOffset);
            SetMaTailDir(trainId,trainDir);

            LogPrintf(1U,"1J Cancel%d,%d,%d;%d,%d\n",trainId,MA_END_ATT_CBTC,trainOutType,prePeriodMaLink,prePeriodMaOffset);
            LogPrintf(1U,"2J Cancel%d,%d\n",trainUnSafeLocStru.TrainTailLink,trainUnSafeLocStru.TrainTailOffset);
        }
        else
        {
            /*清除MA信息*/
            ClearSingleTrainMaInfo(trainId);

            /*申请MA数组位置*/
            /*PBW,2016.7.10 没有必要,因为ClearSingleTrainMaInfo函数只是把MA的内容全置为0 */
            SetMaStatusTrainId(trainId);       

            /*填写为注销状态下的移动授权类型*/
            SetMaType(trainId,CANCELLATION_MA_TYPE);	

            /*以车头车尾为注销状态下移动授权*/
            SetMaHeadLink(trainId,trainUnSafeLocStru.TrainTailLink);
            SetMaHeadOffset(trainId,trainUnSafeLocStru.TrainTailOffset);
            SetMaHeadDir(trainId,trainDir);
            SetMaTailLink(trainId,trainUnSafeLocStru.TrainHeadLink);
            SetMaTailOffset(trainId,trainUnSafeLocStru.TrainHeadOffset);
            SetMaTailDir(trainId,trainDir);
        }        
    } 
    else
    {
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B42\n",trainId);
    }
}

/*
* 函数名称： CalculatAdjustMaEndInfo
* 功能描述： 计算是否需要调整移动授权终点并调整移动授权终点
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculatAdjustMaEndInfo(const UINT16_S trainId)
{
    UINT16_S safeProtectLink = DEFAULT_ZERO;
    UINT32_S safeProtectOffset = DEFAULT_ZERO;
    UINT16_S maEndLink = DEFAULT_ZERO;
    UINT32_S maEndOffset = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S errorSwitchId = DEFAULT_ZERO;
    UINT8_S checkRtn = DEFAULT_ZERO;
    UINT8_S safeProtectFlag = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S checkTrainId = DEFAULT_ZERO;
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S backLink = DEFAULT_ZERO;
    UINT32_S backOffset = DEFAULT_ZERO;
    UINT32_S lineMaBackDistance = DEFAULT_ZERO;

    /*查询移动授权终点向前安全防护距离的位置*/
    maEndLink = GetMaTailLink(trainId);
    maEndOffset = GetMaTailOffset(trainId);
    trainDir = GetTrainUnsafeDirection(trainId);
    lineMaBackDistance = (UINT32_S)GetLineMaBackDistance();

    if (RETURN_SUCCESS == CheckPointReclosingAtQuitCbtc(maEndLink,maEndOffset))
    {
        /*终点为退出CBTC终点,需要回撤移动授权*/
        safeProtectFlag = FLAG_SET;
    } 
    else
    {		
        checkRtn = CheckNextPointOnDistance(maEndLink,maEndOffset,trainDir,lineMaBackDistance,&safeProtectLink,&safeProtectOffset,&errorSwitchId);

        if (RETURN_ERROR == checkRtn)
        {
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-B43\n",trainId);
        } 
        else
        {
            if (0x03U == checkRtn)
            {
                for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
                {
                    checkTrainId = GetTrainIdOfIndex(cycle);

                    if (checkTrainId != trainId)
                    {
                        if (RETURN_SUCCESS == GetTrainSafeLoc(checkTrainId,&trainSafeLocStru))
                        {
                            /*判断列车安全车尾是否位于安全防护位置到移动授权终点之间*/
                            if (RETURN_SUCCESS == CheckPointBelongToArea(maEndLink,maEndOffset,safeProtectLink,safeProtectOffset,
                                trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,trainDir))
                            {
                                /* MA终点和MA终点沿列车运行方向前移安全防护距离内有其他车的安全车尾,需要回撤移动授权 */
                                safeProtectFlag = FLAG_SET;
                                break;
                            } 
                            else
                            {
                                /*不处理*/
                            }
                        }                       
                    } 
                    else
                    {
                        /*不处理*/
                    }
                }
            } 
            else
            {
                /*不需要防护*/
            }
        }
    }

    if (FLAG_SET == safeProtectFlag)
    {
        /*查询回撤点*/
        checkRtn = CheckNextPointOnDistance(maEndLink,maEndOffset,TrainDirChangeForCheck(trainId),
            lineMaBackDistance,&backLink,&backOffset,&errorSwitchId);

        if (0x03U == checkRtn)
        {
            /*更新回撤的移动授权*/
            SetMaTailLink(trainId,backLink);
            SetMaTailOffset(trainId,backOffset);
        } 
        else
        {
            /*维持当前*/
        }
    }
    else
    {
        /*维持当前*/
    }
}

/*
* 函数名称： CalculateMaEndAttribute
* 功能描述： 计算移动授权终点属性信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void CalculateMaEndAttribute(const UINT16_S trainId)
{
    UINT8_S routeOfAcNum = DEFAULT_ZERO;
    UINT16_S routeOfAcIdBuff[ROUTE_OF_AC_SUM_MAX] = {DEFAULT_ZERO};
    UINT16_S lastMatchRouteId = DEFAULT_ZERO;
    UINT16_S acTerminalLink = DEFAULT_ZERO;
    UINT32_S acTerminalOffset = DEFAULT_ZERO;
    UINT16_S matchOverlapId = DEFAULT_ZERO;
    UINT8_S getFlag = RETURN_ERROR;
    UINT16_S maTailLink = DEFAULT_ZERO;
    UINT32_S maTailOffset = DEFAULT_ZERO;
    UINT16_S trainDir = DEFAULT_ZERO;
    UINT8_S rtnGetLastRoute = RETURN_ERROR;
    UINT16_S acToplLink = DEFAULT_ZERO;
    UINT32_S acTopOffset = DEFAULT_ZERO;
    UINT8_S checkRtn = DEFAULT_ZERO;
    UINT8_S checkQuitCbtcRtn = DEFAULT_ZERO;

    MemorySet(&routeOfAcIdBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)));

    /*获取列车匹配的进路信息*/
    rtnGetLastRoute = GetTrainMatchedLastRouteId(trainId,&lastMatchRouteId);

    if ((RETURN_SUCCESS == rtnGetLastRoute) && (DEFAULT_ZERO != lastMatchRouteId))
    {
        maTailLink = GetMaTailLink(trainId);
        maTailOffset = GetMaTailOffset(trainId);

        if (LINE_REVERSE_ROUTE == GetRouteType(lastMatchRouteId))
        {
            /*获取进路最后一个计轴区段*/
            routeOfAcNum = GetRouteOfAcNum(lastMatchRouteId);
            getFlag = GetRoutOfAcIdBuff(lastMatchRouteId,ROUTE_OF_AC_SUM_MAX,routeOfAcIdBuff);

            if ((routeOfAcNum > DEFAULT_ZERO) && (RETURN_SUCCESS == getFlag))
            {
                /*获取最后一个计轴区段终点位置*/
                trainDir = (UINT16_S)GetTrainUnsafeDirection(trainId);

                /*判断MA终点与折返轨始端点位置关系来确定MA终点的属性*/
                if (1U == CheckAcTopPosition(routeOfAcIdBuff[routeOfAcNum - 1u],trainDir,&acToplLink,&acTopOffset))
                {
                    /*判断MA终点与始端点的位置关系*/
                    checkRtn = CheckLocRelationBetweenTwoPoints(maTailLink,maTailOffset,acToplLink,acTopOffset,((UINT8_S)trainDir));

                    switch (checkRtn)
                    {
                    case 0U:
                        /*查询失败,列车紧急制动*/
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-B44\n",trainId);
                        break;
                    case 1U:
                        /*当前移动授权位置更远,满足为折返进路终端条件*/
                        SetMaEndAttribute(trainId,MA_END_ATT_REVERT);
                        break;
                    case 2U:
                    case 3U:
                        /*当前折返进路始端点更远或者重合,满足为其他终端条件*/
                        SetMaEndAttribute(trainId,MA_END_ATT_OTHER);
                        break;
                    default:
                        /*查询失败,列车紧急制动*/
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-B45\n",trainId);
                        break;
                    }
                }
                else
                {
                    /*查询失败,无法获取静态数据,列车紧急制动*/
                    SetTrainToModeToRM0(trainId);
                    LogPrintf(1u,"%d-B46\n",trainId);
                }

                /*
                if (1U == CheckAcTerminalPosition(routeOfAcIdBuff[routeOfAcNum-1U],trainDir,&acTerminalLink,&acTerminalOffset))
                {
                if ((maTailLink == acTerminalLink) && (maTailOffset == acTerminalOffset))
                {
                SetMaEndAttribute(trainId,MA_END_ATT_REVERT);
                } 
                else
                {
                matchOverlapId = JudgeRouteOfLockOverlap(lastMatchRouteId);

                if (DEFAULT_ZERO != matchOverlapId)
                {
                SetMaEndAttribute(trainId,MA_END_ATT_REVERT);
                } 
                else
                {
                SetTrainToModeToRM0(trainId);
                }
                }
                } 
                else
                {
                SetTrainToModeToRM0(trainId);
                }*/
            } 
            else
            {
                /*查询失败,无法获取静态数据,列车紧急制动*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B47\n",trainId);
            }
        } 
        else
        {
            /*获取列车方向*/
            trainDir =  GetTrainUnsafeDirection(trainId);

            /*查询移动授权终点是否和某个退出CBTC区域内重合*/
            checkQuitCbtcRtn = CheckPointQuitCbtcIsFindPoint(maTailLink,maTailOffset,((UINT8_S)trainDir));

            switch (checkQuitCbtcRtn)
            {
            case 0u:
                /*查询失败,无法获取静态数据,列车紧急制动*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B48\n",trainId);
                break;
            case 1u:
                SetMaEndAttribute(trainId,MA_END_ATT_CBTC);
                break;
            case 2u:
                SetMaEndAttribute(trainId,MA_END_ATT_OTHER);
                break;
            default:
                /*查询失败,无法获取静态数据,列车紧急制动*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B49\n",trainId);
                break;
            }
        }
    } 
    else
    {
        /*查询失败,无法获取静态数据,列车紧急制动*/
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B50\n",trainId);
    }
}

/*
* 函数名称： MixObsOfMa
* 功能描述： 混合移动授权信息中的障碍物信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： ObsOfMAStruct mixObsBuff[],输出障碍物信息
* 返回值  ： RETURN_UINT8_MAX_VALUE:失败
*            [0,RETURN_UINT8_MAX_VALUE):障碍物数量
*/
UINT8_S MixObsOfMa(const UINT16_S trainId,ObsOfMAStruct mixObsBuff[])
{
    UINT8_S cycle1 = 0U;
    UINT8_S cycle2 = 0U;
    UINT8_S obsNum1 = 0U;
    UINT8_S obsNum2 = 0U;
    UINT8_S getObs2Value = 0U;
    UINT8_S getObs1Value = 0U;
    UINT16_S obsId = 0U;
    UINT8_S obsType = 0U;
    UINT8_S status = 0U;
    UINT8_S lockStatus = 0U;
    UINT8_S rtnValue = 0U;
    UINT8_S mixNum = 0U;
    ObsOfMAStruct obs1StruBuff[MA_AREA_OBS_SUM_MAX];
    ObsOfMAStruct obs2StruBuff[MA_AREA_OBS_SUM_MAX];
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT16_S belongZcId = DEFAULT_0XFF;  /* 障碍物所属的ZC编号 */

    /*初始化输出结构体数组*/
    MemorySet(&obs1StruBuff[0],((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))),
        0U,((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))));
    MemorySet(&obs2StruBuff[0],((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))),
        0U,((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))));

    /*提取MA1中障碍物信息*/
    obsNum1 = GetMaObsNum(trainId);
    getObs1Value = GetObsOfMAStru(trainId,MA_AREA_OBS_SUM_MAX,obs1StruBuff);

    /*提取MA2中障碍物信息*/
    obsNum2 = GetNextZcMaObsNum(trainId);
    getObs2Value = GetNextZcObsOfMAStru(trainId,obs2StruBuff);

    if ((RETURN_UINT8_MAX_VALUE == obsNum1) || (RETURN_UINT8_MAX_VALUE == obsNum2)
        || (RETURN_ERROR == getObs1Value) || (RETURN_ERROR == getObs2Value)
        || (NULL == mixObsBuff))
    {
        rtnValue = RETURN_UINT8_MAX_VALUE;
    }
    else
    {
        MemorySet(&mixObsBuff[0],((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))),
            0U,((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))));

        /* 获取本地ZC的ID */
        localZcId = GetLocalZcId();

        /*遍历MA1中的障碍物，提取属于移交ZC的障碍物*/
        for (cycle1=0U;cycle1 < obsNum1;cycle1++)
        {			
            obsId = obs1StruBuff[cycle1].ObsId;
            obsType = obs1StruBuff[cycle1].ObsType;
            status = obs1StruBuff[cycle1].ObsStatus;
            lockStatus = obs1StruBuff[cycle1].ObsLockStatus;
            belongZcId = DEFAULT_0XFF;

            switch (obsType)
            {
            case OBS_TYPE_ESB:
                belongZcId = GetEsbBelongZcId(obsId);
                break;
            case OBS_TYPE_PSD:
                belongZcId = GetPsdBelongZcId(obsId);
                break;
            case OBS_TYPE_POINT:
                belongZcId = GetSwitchBelongZcId(obsId);
                break;
            default:
                break;
            }

            if((DEFAULT_0XFF != belongZcId) && (localZcId == belongZcId))                 
            {
                /*加入混合后障碍物*/
                mixObsBuff[mixNum].ObsId = obsId;
                mixObsBuff[mixNum].ObsType = obsType;
                mixObsBuff[mixNum].ObsStatus = status;
                mixObsBuff[mixNum].ObsLockStatus = lockStatus;
                mixNum++;
            }
            else
            {
                /*不操作*/
            }
        } 

        /*遍历MA2中的障碍物，提取属于接管ZC的障碍物*/
        for (cycle2=0U;cycle2 < obsNum2;cycle2++)
        {			
            obsId = obs2StruBuff[cycle2].ObsId;
            obsType = obs2StruBuff[cycle2].ObsType;
            status = obs2StruBuff[cycle2].ObsStatus;
            lockStatus = obs2StruBuff[cycle2].ObsLockStatus;
            belongZcId = DEFAULT_0XFF;

            switch (obsType)
            {
            case OBS_TYPE_ESB:
                belongZcId = GetEsbBelongZcId(obsId);
                break;
            case OBS_TYPE_PSD:
                belongZcId = GetPsdBelongZcId(obsId);
                break;
            case OBS_TYPE_POINT:
                belongZcId = GetSwitchBelongZcId(obsId);
                break;
            default:
                break;
            }

            if((DEFAULT_0XFF != belongZcId) && (localZcId != belongZcId)) 
            {
                /*加入混合后障碍物*/
                mixObsBuff[mixNum].ObsId = obsId;
                mixObsBuff[mixNum].ObsType = obsType;
                mixObsBuff[mixNum].ObsStatus = status;
                mixObsBuff[mixNum].ObsLockStatus = lockStatus;
                mixNum++;
            }
            else
            {
                /*不操作*/
            }
        }

        rtnValue = mixNum;
    }

    return rtnValue;
}

/*
* 函数名称： MixTsrOfMa
* 功能描述： 混合移动授权信息中的临时限速信息
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： TsrOfMAStruct mixTsrBuff[],输出混合后的临时限速
* 返回值  ： RETURN_UINT8_MAX_VALUE:失败
*            [0,RETURN_UINT8_MAX_VALUE):临时限速数量
*/
UINT8_S MixTsrOfMa(const UINT16_S trainId,TsrOfMAStruct mixTsrBuff[])
{
    UINT8_S cycle1 = 0U;
    UINT8_S cycle2 = 0U;
    UINT8_S tsrNum1 = 0U;
    UINT8_S tsrNum2 = 0U;
    UINT8_S getTsr2Value = 0U;
    UINT8_S getTsr1Value = 0U;
    UINT16_S belongZcId = 0U;  /*临时限速对应的相邻ZCID*/
    UINT8_S rtnValue = 0U;
    UINT8_S mixNum = 0U;
    TsrOfMAStruct tsr1StruBuff[MA_AREA_TSR_SUM_MAX];
    TsrOfMAStruct tsr2StruBuff[MA_AREA_TSR_SUM_MAX];

    /*初始化输出结构体数组*/
    MemorySet(&tsr2StruBuff[0],((UINT32_S)(MA_AREA_TSR_SUM_MAX*sizeof(TsrOfMAStruct))),
        0U,((UINT32_S)(MA_AREA_TSR_SUM_MAX*sizeof(TsrOfMAStruct))));
    MemorySet(&tsr1StruBuff[0],((UINT32_S)(MA_AREA_TSR_SUM_MAX*sizeof(TsrOfMAStruct))),
        0U,((UINT32_S)(MA_AREA_TSR_SUM_MAX*sizeof(TsrOfMAStruct))));

    /*提取MA1中TSR信息*/
    tsrNum1 = GetMaTsrNum(trainId);
    getTsr1Value = GetTsrOfMAStru(trainId,MA_AREA_TSR_SUM_MAX,tsr1StruBuff);

    /*提取MA2中TSR信息*/
    tsrNum2 = GetNextZcMaTsrNum(trainId);
    getTsr2Value = GetNextZcTsrOfMAStru(trainId,tsr2StruBuff);

    if ((RETURN_UINT8_MAX_VALUE == tsrNum1) || (RETURN_UINT8_MAX_VALUE == tsrNum2)
        || (RETURN_ERROR == getTsr1Value) || (RETURN_ERROR == getTsr2Value)
        || (NULL == mixTsrBuff))
    {
        rtnValue = RETURN_UINT8_MAX_VALUE;
    }
    else
    {
        MemorySet(&mixTsrBuff[0],((UINT32_S)(MA_AREA_TSR_SUM_MAX*sizeof(TsrOfMAStruct))),
            0U,((UINT32_S)(MA_AREA_TSR_SUM_MAX*sizeof(TsrOfMAStruct))));

        /*遍历MA1中的TSR，提取属于移交ZC的TSR*/
        for (cycle1 = 0U;cycle1 < tsrNum1;cycle1++)
        {
            belongZcId = tsr1StruBuff[cycle1].BelongZcId;

            if (GetLocalZcId() == belongZcId)
            {
                /*如果所属ZC为本ZC，则写入混合后TSR中*/
                mixTsrBuff[mixNum].TsrSpeed =  tsr1StruBuff[cycle1].TsrSpeed;
                mixTsrBuff[mixNum].TsrHeadLink =  tsr1StruBuff[cycle1].TsrHeadLink;
                mixTsrBuff[mixNum].TsrHeadOffset =  tsr1StruBuff[cycle1].TsrHeadOffset;
                mixTsrBuff[mixNum].TsrTailLink =  tsr1StruBuff[cycle1].TsrTailLink;
                mixTsrBuff[mixNum].TsrTailOffset =  tsr1StruBuff[cycle1].TsrTailOffset;
                mixTsrBuff[mixNum].BelongZcId =  tsr1StruBuff[cycle1].BelongZcId;

                mixNum++;
            }
            else
            {
                /*如果已经遍历到属于接管ZC的TSR，跳出*/
                break;
            }
        }

        /*遍历MA2中的TSR，提取属于接管ZC的TSR*/
        for (cycle2=0U;cycle2 < tsrNum2;cycle2++)
        {
            belongZcId = tsr2StruBuff[cycle2].BelongZcId;

            if (GetNextZcId(trainId) == belongZcId)
            {
                /*如果所属ZC为接管ZC，则写入混合后TSR中*/
                mixTsrBuff[mixNum].TsrSpeed =  tsr2StruBuff[cycle2].TsrSpeed;
                mixTsrBuff[mixNum].TsrHeadLink =  tsr2StruBuff[cycle2].TsrHeadLink;
                mixTsrBuff[mixNum].TsrHeadOffset =  tsr2StruBuff[cycle2].TsrHeadOffset;
                mixTsrBuff[mixNum].TsrTailLink =  tsr2StruBuff[cycle2].TsrTailLink;
                mixTsrBuff[mixNum].TsrTailOffset =  tsr2StruBuff[cycle2].TsrTailOffset;
                mixTsrBuff[mixNum].BelongZcId =  tsr2StruBuff[cycle2].BelongZcId;

                mixNum++;
            }
            else
            {
                /*继续遍历*/
            }
        }

        rtnValue = mixNum;

    }

    return rtnValue;
}

/*
* 函数名称： SingleTrainHandMixMA
* 功能描述： 单辆列车混合移动授权（切换列车）
* 输入参数： const UINT16_S trainId,列车Id
* 输出参数： 无
* 返回值  ： 无
*/
void SingleTrainHandMixMA(const UINT16_S trainId)
{
    UINT8_S ma2InfoFlag = 0U;       /*MA2存在标志*/
    UINT8_S ma2Length = 0U;         /*MA2长度*/
    MaDataStruct mixedMaStru;       /*混合后MA结构体*/
    ObsOfMAStruct mixedObsBuff[MA_AREA_OBS_SUM_MAX];  /*混合后障碍物*/
    UINT8_S mixedObsNum = 0U;  /*混合后障碍物数量*/
    TsrOfMAStruct mixedTsrBuff[MA_AREA_TSR_SUM_MAX];  /*混合后临时限速*/
    UINT8_S mixedTsrNum = 0U;  /*混合后临时限速数量*/
    UINT16_S ma1HeadLink = 0U;
    UINT32_S ma1HeadOffset = 0U;
    UINT8_S ma1HeadDir = 0U;
    UINT16_S ma2TailLink = 0U;
    UINT32_S ma2TailOffset = 0U;
    UINT8_S ma2TailDir = 0U;
    UINT8_S ma2EndAttribute = 0U;
    UINT8_S obsCycle = 0U;
    UINT8_S tsrCycle = 0U;

    /*初始化*/
    MemorySet(&mixedMaStru,((UINT32_S)(sizeof(MaDataStruct))),0U,((UINT32_S)(sizeof(MaDataStruct))));
    MemorySet(&mixedObsBuff[0],((UINT32_S)(sizeof(ObsOfMAStruct) * MA_AREA_OBS_SUM_MAX)),
        0U,((UINT32_S)(sizeof(ObsOfMAStruct) * MA_AREA_OBS_SUM_MAX)));
    MemorySet(&mixedTsrBuff[0],((UINT32_S)(sizeof(TsrOfMAStruct) * MA_AREA_TSR_SUM_MAX)),
        0U,((UINT32_S)(sizeof(TsrOfMAStruct) * MA_AREA_TSR_SUM_MAX)));

    /*获取MA1的部分状态*/
    ma1HeadLink = GetMaHeadLink(trainId);
    ma1HeadOffset = GetMaHeadOffset(trainId);
    ma1HeadDir = GetMaHeadDir(trainId);

    /*获取MA2的部分状态*/
    ma2InfoFlag = GetNextZcMaInfoFlag(trainId);
    ma2Length = GetNextZcMaStatusMaLength(trainId);
    ma2TailLink = GetNextZcMaTailLink(trainId);
    ma2TailOffset = GetNextZcMaTailOffset(trainId);
    ma2TailDir = GetNextZcMaTailDir(trainId);
    ma2EndAttribute = GetNextZcMaEndAttribute(trainId);


    /*对MA2的状态进行判断*/
    if ((RETURN_UINT8_MAX_VALUE == ma2InfoFlag)	|| (RETURN_UINT8_MAX_VALUE == ma2Length) 
        || (RETURN_UINT16_MAX_VALUE == ma2TailLink) || (RETURN_UINT32_MAX_VALUE == ma2TailOffset) 
        || (RETURN_UINT8_MAX_VALUE == ma2TailDir) || (RETURN_UINT8_MAX_VALUE == ma2EndAttribute))
    {
        /*获取数据失败，将混合后MA置为空MA*/
        SetTrainToModeToRM0(trainId); 
        LogPrintf(1u,"%d-B51\n",trainId);
    }
    else if ((RETURN_UINT16_MAX_VALUE == ma1HeadLink) || (RETURN_UINT32_MAX_VALUE == ma1HeadOffset) 
        || (RETURN_UINT8_MAX_VALUE == ma1HeadDir))
    {
        /*获取数据失败，将混合后MA置为空MA*/
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B52\n",trainId);
    }
    else
    {
        if (NO_MA_TYPE == ma2InfoFlag)
        {
            /*MA2不存在,移交ZC计算MA1即为混合后MA*/
        }
        else if (ABNORMAL_MA_TYPE == ma2InfoFlag)
        {
            /*MA2为空MA，或者MA2未越过切换点,均为异常,将混合后MA置为空MA*/
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-B53\n",trainId);
        }
        else
        {
            /*可以正常混合MA,混合障碍物*/
            mixedObsNum = MixObsOfMa(trainId,mixedObsBuff);

            /*混合临时限速*/
            mixedTsrNum = MixTsrOfMa(trainId,mixedTsrBuff);

            if ((RETURN_UINT8_MAX_VALUE == mixedObsNum) || (RETURN_UINT8_MAX_VALUE == mixedTsrNum))
            {
                /*数据错误，将混合后MA置为空MA*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B54\n",trainId);
            }
            else
            {
                /*混合后MA*/
                mixedMaStru.TrainID = trainId;
                mixedMaStru.MaHeadLink = ma1HeadLink;
                mixedMaStru.MaHeadOffset = ma1HeadOffset;
                mixedMaStru.MaHeadDir = ma1HeadDir;
                mixedMaStru.MaTailLink = ma2TailLink;
                mixedMaStru.MaTailOffset = ma2TailOffset;
                mixedMaStru.MaTailDir = ma2TailDir;
                mixedMaStru.MaEndAttribute = ma2EndAttribute;

                mixedMaStru.ObsNum = mixedObsNum;
                for (obsCycle=0U;obsCycle<mixedObsNum;obsCycle++)
                {
                    mixedMaStru.ObsOfMAStru[obsCycle].ObsId = mixedObsBuff[obsCycle].ObsId;
                    mixedMaStru.ObsOfMAStru[obsCycle].ObsType = mixedObsBuff[obsCycle].ObsType;
                    mixedMaStru.ObsOfMAStru[obsCycle].ObsStatus = mixedObsBuff[obsCycle].ObsStatus;
                    mixedMaStru.ObsOfMAStru[obsCycle].ObsLockStatus = mixedObsBuff[obsCycle].ObsLockStatus;
                }

                mixedMaStru.TsrNum = mixedTsrNum;
                for (tsrCycle=0U;tsrCycle<mixedTsrNum;tsrCycle++)
                {
                    mixedMaStru.TsrOfMAStru[tsrCycle].BelongZcId = mixedTsrBuff[tsrCycle].BelongZcId;
                    mixedMaStru.TsrOfMAStru[tsrCycle].TsrHeadLink = mixedTsrBuff[tsrCycle].TsrHeadLink;
                    mixedMaStru.TsrOfMAStru[tsrCycle].TsrHeadOffset = mixedTsrBuff[tsrCycle].TsrHeadOffset;
                    mixedMaStru.TsrOfMAStru[tsrCycle].TsrTailLink = mixedTsrBuff[tsrCycle].TsrTailLink;
                    mixedMaStru.TsrOfMAStru[tsrCycle].TsrTailOffset = mixedTsrBuff[tsrCycle].TsrTailOffset;
                    mixedMaStru.TsrOfMAStru[tsrCycle].TsrSpeed = mixedTsrBuff[tsrCycle].TsrSpeed;
                }

                /*将混合后MA写入全局数据中*/
                SetMaHeadLink(trainId,mixedMaStru.MaHeadLink);
                SetMaHeadOffset(trainId,mixedMaStru.MaHeadOffset);
                SetMaHeadDir(trainId,mixedMaStru.MaHeadDir);
                SetMaTailLink(trainId,mixedMaStru.MaTailLink);
                SetMaTailOffset(trainId,mixedMaStru.MaTailOffset);
                SetMaTailDir(trainId,mixedMaStru.MaTailDir);
                SetMaEndAttribute(trainId,mixedMaStru.MaEndAttribute);
                SetMaObsNum(trainId,mixedMaStru.ObsNum);
                SetObsOfMAStru(trainId, mixedMaStru.ObsOfMAStru,mixedMaStru.ObsNum);
                SetMaTsrNum(trainId,mixedMaStru.TsrNum);
                SetTsrOfMAStru(trainId, mixedMaStru.TsrOfMAStru,mixedMaStru.TsrNum);
            }
        }
    }
}

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
UINT8_S CalPointIsOnOverlap(const UINT16_S segId,const UINT32_S offset,const UINT8_S dir,UINT16_S *OutOverlapId)
{
    UINT16_S outSegId = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT16_S overlapSum = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S overlapId = DEFAULT_ZERO;
    UINT8_S acSumOfOverlap = DEFAULT_ZERO;   /* 保护区段包含的计轴区段总数 */
    UINT8_S j = DEFAULT_ZERO;
    UINT16_S overlapAcIdBuff[OVERLAP_OF_AC_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S getFlag = RETURN_ERROR;
    UINT16_S rtnValue = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S  rtnGetStart = RETURN_ERROR;
    UINT8_S  startIndex = DEFAULT_ZERO;
    UINT16_S startSeg = DEFAULT_ZERO;
    UINT32_S startOffset = DEFAULT_ZERO;
    UINT8_S  rtnGetEnd = RETURN_ERROR;
    UINT8_S  endIndex = DEFAULT_ZERO;
    UINT16_S endSeg = DEFAULT_ZERO;
    UINT32_S endOffset = DEFAULT_ZERO;

    MemorySet(&overlapAcIdBuff[0],((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)));

    if ((NULL != OutOverlapId)  
        && ((TRAIN_UNSAFE_DIR_UP == dir) ||(TRAIN_UNSAFE_DIR_DOWN == dir)))
    {
        /* 计算此点内方所属计轴区段 */
        if (1u == CalculatePointOfInsideLink(dir,segId,offset,&outSegId))
        {
            acId = CheckPositionBelongAc(outSegId);
            overlapSum = GetOverlapSum();

            /* 遍历管辖范围的所有保护区段 */
            for (i = DEFAULT_ZERO;i < overlapSum;i++)
            {
                overlapId = GetOverlapId(i);           
                acSumOfOverlap = GetOverlapContainAcNum(overlapId);
                getFlag = GetOverlapContainAcBuff(overlapId,OVERLAP_OF_AC_SUM_MAX,overlapAcIdBuff);

                /* 遍历保护区段包含的所有计轴区段 */
                for (j = DEFAULT_ZERO;j < acSumOfOverlap;j++)
                {
                    if (acId == overlapAcIdBuff[j])
                    {
                        if (FLAG_SET == GetOverlapSwitchAttribute(overlapId))
                        {
                            /* 保护区段包含道岔 */
                            if (1u == CalulateSwtichStateOfOverlapIsNeed(overlapId))
                            {
                                *OutOverlapId = overlapId;
                            }
                            else
                            {
                                /* 包含道岔，道岔不满足要求，继续遍历*/
                            }
                        }
                        else
                        {
                            *OutOverlapId = overlapId;
                        }            
                    }
                }
            }

            if (DEFAULT_ZERO != (*OutOverlapId))
            {
                acSumOfOverlap = GetOverlapContainAcNum(overlapId);

                getFlag = GetOverlapContainAcBuff(overlapId,OVERLAP_OF_AC_SUM_MAX,overlapAcIdBuff);

                if ((DEFAULT_ZERO < acSumOfOverlap) && (RETURN_SUCCESS == getFlag))
                {
                    if (TRAIN_UNSAFE_DIR_UP == dir)
                    {
                        /* 上行 */
                        startIndex = 0u;
                        endIndex = acSumOfOverlap - 1u;
                    }
                    else 
                    {
                        /* 下行 */
                        startIndex = acSumOfOverlap - 1u;
                        endIndex = 0u;
                    }

                    rtnGetStart = CheckAcTopPosition(overlapAcIdBuff[startIndex],(UINT16_S)dir,&startSeg,&startOffset);

                    rtnGetEnd = CheckAcTerminalPosition(overlapAcIdBuff[endIndex],(UINT16_S)dir,&endSeg,&endOffset);

                    if (( segId ==  startSeg) && (offset == startOffset))
                    {
                        rtnValue = 2u;
                    }
                    else if (( segId ==  endSeg) && (offset == endOffset))
                    {
                        rtnValue = 3u;
                    }
                    else
                    {
                        rtnValue = 1u;
                    }
                }       
            }
        }
    }

    return rtnValue;   
}
