/************************************************************************
*
* 文件名   ：  CommTargetLogicManager.c
* 作者     ：  ZC组
* 创建时间 ：  2015.07.14
* 功能描述 ：  通讯对象逻辑处理 
* 备  注   ：  无  
*
************************************************************************/

#include "CommTargetLogicManager.h"
#include "../../SysDataManager/SysDefine.h"
#include "CommTargetConfigData.h"
#include "CommTargetStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../LineDataManager/Switch/SwitchLogicManager.h"
#include "../../LineDataManager/Signal/SignalLogicManager.h"
#include "../../LineDataManager/AC/ACLogicManager.h"
#include "../../LineDataManager/AC/ACStatusData.h"
#include "../../LineDataManager/PSD/PSDLogicManager.h"
#include "../../LineDataManager/ESB/ESBLogicManager.h"
#include "../../LineDataManager/Overlap/OverlapLogicManager.h"
#include "../../LineDataManager/Route/RouteLogicManager.h"
#include "../../TrainManager/Train/TrainLogicManager.h"
#include "../../LineDataManager/Tsr/TsrLogicManager.h"
#include "../../TrainManager/Train/TrainStatusData.h"
#include "../../LineDataManager/DR/DRLogicManager.h"
#include "../../LineDataManager/LogicSection/LogicSectionLogicManager.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../TrainManager/MA/MAStatusData.h"
#include "../../../Common/MemSet.h"

/*
* 函数名称:  ManagerCommTargetCommCycle
* 功能描述： 管理通信对象通信周期管理
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 无
*/
void ManagerCommTargetCommCycle(void)
{
    /*处理通信CI的通信周期信息*/
    JudgeSingleCommTypeCommCyle(INNER_DEVTYPE_CI);

    /*处理通信ZC的通信周期信息*/
    JudgeSingleCommTypeCommCyle(INNER_DEVTYPE_ZC);

    /*处理通信NTP的通信周期信息*/
    JudgeSingleCommTypeCommCyle(INNER_DEVTYPE_NTP);

    /*处理通信的车载ATP的通信周期信息*/
    JudgeCommTrainCommCyle();
}

/*
* 函数名称： JudgeSingleCommTypeCommCyle
* 功能描述： 处理通信对象（除列车外）通信周期管理
* 输入参数： const UINT8 commTargetType，通信对象类型  
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeSingleCommTypeCommCyle(const UINT8_S commTargetType)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S commTargetBufIndex = DEFAULT_ZERO;
    UINT8_S singleCommTargetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX];
    UINT16_S commCycle = DEFAULT_ZERO;
    UINT8_S rtnGet = DEFAULT_ZERO;

    /*初始化*/
    MemorySet(&commTargetIdBuff[DEFAULT_ZERO],sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX,DEFAULT_ZERO,sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX);

    /*获取通信对象的数量*/
    commTargetBufIndex = GetCommTargetTypeBuffIndex(commTargetType);
    singleCommTargetNum = GetSingleCommTargetTypeSum(commTargetType);
    rtnGet = GetSingleCommTargetIdBuff(commTargetType,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff);

    if ((COMM_TYPE_SUM_MAX > commTargetBufIndex)
        && (RETURN_SUCCESS == rtnGet)
        && (SINGLE_TYPE_COMM_TARGET_SUM_MAX > singleCommTargetNum))
    {
        for (cycle = DEFAULT_ZERO;cycle < singleCommTargetNum;cycle++)
        {
            if (COMM_STATUS_NORMAL == GetCommTargetStatus(commTargetType,commTargetIdBuff[cycle]))
            {
                commCycle = GetCommTargetCycle(commTargetType,commTargetIdBuff[cycle]);

                if (DEFAULT_UINT16_VALUE != commCycle)
                {
                    SetCommTargetCycle(commTargetType,commTargetIdBuff[cycle],((UINT16_S)(commCycle+1U)));
#ifdef SYS_TYPE_WINDOWS
                    LogPrintf(1U,"17.301 commTargetType=0x%x,commTargetId=%d,commCycle=%d\n",commTargetType,commTargetIdBuff[cycle],commCycle+1);
#endif
                } 
                else
                {
                    /*不处理*/
                }
            } 
            else
            {
                /*通信状态异常,清除累加位*/
                SetCommTargetCycle(commTargetType,commTargetIdBuff[cycle],DEFAULT_ZERO);
            }
        }
    } 
    else
    {
        /*可宕机！！！！！！！！！！！*/
    }
}

/*
* 函数名称： JudgeCommTrainCommCyle
* 功能描述： 处理通信列车通信周期管理
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeCommTrainCommCyle(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTargetCycle = DEFAULT_ZERO;

    for (cycle = 1U;cycle < COMM_TRAIN_ID_MAX;cycle++)
    {
        /*列车通信中，下标即为Id*/
        if (COMM_STATUS_NORMAL == GetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle)))
        {
            /*获取通信周期位*/
            commTargetCycle = GetCommTargetCycle(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle));

            /*通信累加位+1*/
            if (DEFAULT_UINT16_VALUE != commTargetCycle)
            {
                SetCommTargetCycle(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle),((UINT16_S)(commTargetCycle + 1U)));
                /* LogPrintf(1U,"17.302 train=%d,commCycle=%d\n",cycle,(UINT16_S)(commTargetCycle + 1U)); */
            } 
            else
            {
                /*不处理*/
            }
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*
* 函数名称： ManageCommTargetCommStatus
* 功能描述： 通信对象通信状态管理
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 无
*/
void ManageCommTargetCommStatus(void)
{
    UINT16_S maxCommFaultCycle = DEFAULT_ZERO;  /* 配置的判断某个对象通讯对象最大周期数 */

    /*处理与CI通信对象的通信状态*/
    maxCommFaultCycle = (UINT16_S)(GetCICommCycle());
    JudgeSingleCommTypeCommStatus(INNER_DEVTYPE_CI,maxCommFaultCycle);

    /*处理与NZC通信对象的通信状态*/
    maxCommFaultCycle = (UINT16_S)(GetNZcCommCycle());
    JudgeSingleCommTypeCommStatus(INNER_DEVTYPE_ZC,maxCommFaultCycle);

    /*处理与NTP通信对象的通信状态*/
    JudgeNtpCommStatus();

    /*处理与Train通信对象的通信状态*/
    maxCommFaultCycle = (UINT16_S)(GetTrainAtpCommCycle());
    JudgeCommTrainCommStatus(maxCommFaultCycle);
}

/*
* 函数名称： JudgeSingleCommTypeCommStatus
* 功能描述： 处理通信对象（除列车外）通信状态管理
* 输入参数： const UINT8 commTargetType，通信对象类型  
*            const UINT16_S maxCommFaultCycle，该通信类型最大的通信故障周期
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeSingleCommTypeCommStatus(const UINT8_S commTargetType,const UINT16_S maxCommFaultCycle)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S commTargetBufIndex = DEFAULT_ZERO;
    UINT8_S singleCommTargetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};
    UINT16_S commCycle = DEFAULT_ZERO;
    UINT8_S rtnGet = DEFAULT_ZERO;

    /*初始化*/
    MemorySet(commTargetIdBuff,((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
               DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    /*获取通信对象的数量*/
    commTargetBufIndex = GetCommTargetTypeBuffIndex(commTargetType);
    singleCommTargetNum = GetSingleCommTargetTypeSum(commTargetType);
    rtnGet = GetSingleCommTargetIdBuff(commTargetType,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff);

    if ((COMM_TYPE_SUM_MAX > commTargetBufIndex)
        && (RETURN_SUCCESS == rtnGet)
        && (SINGLE_TYPE_COMM_TARGET_SUM_MAX > singleCommTargetNum))
    {
        for (cycle = DEFAULT_ZERO;cycle < singleCommTargetNum;cycle++)
        {
            if (COMM_STATUS_NORMAL == GetCommTargetStatus(commTargetType,commTargetIdBuff[cycle]))
            {
                commCycle = GetCommTargetCycle(commTargetType,commTargetIdBuff[cycle]);

                if (commCycle >= maxCommFaultCycle)
                {
                    SetCommTargetStatus(commTargetType,commTargetIdBuff[cycle],COMM_STATUS_ABNORMAL);
                } 
                else
                {
                    /*不处理*/
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
        /*可宕机！！！！！！！！！！！*/
    }
}

/*
* 函数名称： JudgeNtpCommStatus
* 功能描述： 处理NTP通信状态管理
* 输入参数： 无
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeNtpCommStatus(void)
{
    UINT8_S commTargetBufIndex = DEFAULT_ZERO;
    UINT8_S singleCommTargetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};
    UINT16_S commCycle = DEFAULT_ZERO;
    UINT8_S rtnGet = DEFAULT_ZERO;

    /*初始化*/
    MemorySet(&commTargetIdBuff[DEFAULT_ZERO],((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
               DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    /*获取通信对象的数量*/
    commTargetBufIndex = GetCommTargetTypeBuffIndex(INNER_DEVTYPE_NTP);
    singleCommTargetNum = GetSingleCommTargetTypeSum(INNER_DEVTYPE_NTP);
    rtnGet = GetSingleCommTargetIdBuff(INNER_DEVTYPE_NTP,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff);

    if ((COMM_TYPE_SUM_MAX > commTargetBufIndex)
        && (RETURN_SUCCESS == rtnGet)
        && (1U == singleCommTargetNum))
    {
        commCycle = GetCommTargetCycle(INNER_DEVTYPE_NTP,commTargetIdBuff[DEFAULT_ZERO]);

        if (commCycle > ((UINT16_S)(GetSendNtpApplyCycle() + 1U)))
        {
            /*清空累加信息*/
            SetCommTargetCycle(INNER_DEVTYPE_NTP,commTargetIdBuff[DEFAULT_ZERO],DEFAULT_ZERO);
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        /*可宕机*/
    }
}

/*
* 函数名称： JudgeCommTrainCommStatus
* 功能描述： 处理通信列车通信状态管理
* 输入参数： const UINT16 maxCommFaultCycle，该通信类型最大的通信故障周期   
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeCommTrainCommStatus(const UINT16_S maxCommFaultCycle)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTargetCycle = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnSafeLoc;

    for (cycle = 1U;cycle < COMM_TRAIN_ID_MAX;cycle++)
    {
        /*列车通信中，下标即为Id*/
        if (COMM_STATUS_NORMAL == GetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle)))
        {
            if (RETURN_SUCCESS == GetTrainUnSafeLoc(((UINT16_S)cycle),&trainUnSafeLoc))
            {
                /*获取通信周期位*/
                commTargetCycle = GetCommTargetCycle(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle));

                /*通信累加位+1*/
                if (commTargetCycle >= maxCommFaultCycle)
                {
                    SetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle),COMM_STATUS_ABNORMAL);
                } 
                else
                {
                    /*不处理*/
                }
            } 
            else
            {
                /*不处理*/
            }
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*
* 函数名称： ManageCommTargetCommFailure
* 功能描述： 处理通信对象通信故障状态
* 输入参数： 无   
* 输出参数： 无
* 返回值  ： 无
*/
void ManageCommTargetCommFailure(void)
{
    /*处理与CI通信对象的通信故障*/
    JudgeSingleCommTypeCommFailure(INNER_DEVTYPE_CI);

    /*处理与NZC通信对象的通信故障*/
    JudgeSingleCommTypeCommFailure(INNER_DEVTYPE_ZC);

    /*处理与Train通信对象的通信故障*/
    JudgeTrainCommFailure();
}

/*
* 函数名称： JudgeSingleCommTypeCommFailure
* 功能描述： 判断单个通信对象通信故障状态
* 输入参数： const UINT8 commTargetType,通讯对象类型   
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeSingleCommTypeCommFailure(const UINT8_S commTargetType)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S commTargetBufIndex = DEFAULT_ZERO;
    UINT8_S singleCommTargetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S rtnGet = DEFAULT_ZERO;

    /*初始化*/
    MemorySet(&commTargetIdBuff[DEFAULT_ZERO],((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
               DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    /*获取通信对象的数量*/
    commTargetBufIndex = GetCommTargetTypeBuffIndex(commTargetType);
    singleCommTargetNum = GetSingleCommTargetTypeSum(commTargetType);
    rtnGet = GetSingleCommTargetIdBuff(commTargetType,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff);

    if ((COMM_TYPE_SUM_MAX > commTargetBufIndex)
        && (RETURN_SUCCESS == rtnGet)
        && (SINGLE_TYPE_COMM_TARGET_SUM_MAX > singleCommTargetNum))
    {
        for (cycle = DEFAULT_ZERO;cycle < singleCommTargetNum;cycle++)
        {
            if (COMM_STATUS_ABNORMAL == GetCommTargetStatus(commTargetType,commTargetIdBuff[cycle]))
            {
                switch (commTargetType)
                {
                case INNER_DEVTYPE_CI:
                    ProcessCiCommFailure(commTargetIdBuff[cycle]);
                    SetCommTargetStatus(INNER_DEVTYPE_CI,commTargetIdBuff[cycle],DEFAULT_ZERO);
                    LogPrintf(1U,"17.101 CI=%d,Comm Error!\n",commTargetIdBuff[cycle]);
                    break;

                case INNER_DEVTYPE_ZC:
                    ProcessZcCommFailure(commTargetIdBuff[cycle]);
                    SetCommTargetStatus(INNER_DEVTYPE_ZC,commTargetIdBuff[cycle],DEFAULT_ZERO);
                    LogPrintf(1U,"17.201 nZC=%d,Comm Error!\n",commTargetIdBuff[cycle]);
                    break;

                default:
                    break;
                }
            } 
            else
            {
                /*Do nothing currently !*/
            }
        }
    } 
    else
    {
        /*可宕机！！！！！！！！！！！*/
    }
}

/*
* 函数名称： ProcessCiCommFailure
* 功能描述： 判断单个CI通信对象通信故障状态
* 输入参数： const UINT16 commCiId,通讯CI的ID   
* 输出参数： 无
* 返回值  ： 无
*/
void ProcessCiCommFailure(const UINT16_S commCiId)
{
    /*处理本CI范围内的道岔区段状态*/
    InitFailureCiSwitch(commCiId);

    /*处理本CI范围内的信号机状态*/
    InitFailureCiSignal(commCiId);

    /*处理本CI范围内的屏蔽门状态*/
    InitFailureCiPsd(commCiId);

    /*处理本CI范围内的紧急停车按钮状态*/
    InitFailureCiEsb(commCiId);

    /*处理本CI范围内的计轴区段状态*/
    InitFailureCiAc(commCiId);

    /*处理本CI范围内的逻辑区段状态*/
    InitFailureCiLogicSection(commCiId);

    /*处理本CI范围内的保护区段状态*/
    InitFailureCiOverlap(commCiId);

    /*处理本CI范围内的进路状态*/
    InitFailureCiRoute(commCiId);

    /*处理本CI范围内的无人折返按钮状态*/
    InitFailureCiDrButoon(commCiId);

    /*处理本CI范围内的无人折返灯状态*/
    InitFailureCiDrLamp(commCiId);

    /*处理本CI范围内的列车状态*/
    JudgeTrainInfoOfCiCommFailure(commCiId);
}

/*
* 函数名称： ProcessZcCommFailure
* 功能描述： 判断单个ZC通信对象通信故障状态
* 输入参数： const UINT16 commZcId,通讯ZC的ID   
* 输出参数： 无
* 返回值  ： 无
*/
void ProcessZcCommFailure(const UINT16_S commZcId)
{
    /*处理本NZc范围内的道岔区段状态*/
    InitFailureNZcSwitch(commZcId);

    /*处理本NZc范围内的信号机状态*/
    InitFailureNZcSignal(commZcId);

    /*处理本NZc范围内的屏蔽门状态*/
    InitFailureNZcPsd(commZcId);

    /*处理本NZc范围内的紧急停车按钮状态*/
    InitFailureNZcEsb(commZcId);

    /*处理本NZc范围内的计轴区段状态*/
    InitFailureNZcAc(commZcId);

    /*处理本NZc范围内的保护区段状态*/
    InitFailureNZcOverlap(commZcId);

    /*处理本NZc范围内的进路状态*/
    InitFailureNZcRoute(commZcId);

    /*处理本NZc范围内的无人折返按钮状态*/
    InitFailureNZcDrButton(commZcId);

    /*处理本NZc范围内的无人折返灯状态*/
    InitFailureNZcDrLamp(commZcId);

    /*处理通信Nzc范围内的临时限速*/
    DeleteSingleZcTsrInfo(commZcId);

    /*处理本NZc范围内的列车状态*/
    JudgeTrainInfoOfNZcCommFailure(commZcId);
}

/*
* 函数名称： JudgeTrainCommFailure
* 功能描述： 判断列车通信故障状态
* 输入参数： 无   
* 输出参数： 无
* 返回值  ： 无
*/
void JudgeTrainCommFailure(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnSafeLocStru;

    /*初始化*/
    MemorySet(&trainUnSafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),DEFAULT_ZERO,((UINT32_S)(sizeof(TrainSafeLocStruct))));

    for (cycle = 1U;cycle < COMM_TRAIN_ID_MAX;cycle++)
    {
        /*列车通信中，下标即为Id*/
        if (COMM_STATUS_ABNORMAL == GetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle)))
        {
            if (RETURN_SUCCESS == GetTrainUnSafeLoc(((UINT16_S)cycle),&trainUnSafeLocStru))
            {
                /*处理列车通信故障*/
                ProcessTrainCommFailure((UINT16_S)cycle);
                LogPrintf(1U,"17.001 TrainId=%d,Comm Error!\n",cycle);
            } 
            else
            {
                /*不处理*/
            }

            /*设置列车故障状态*/
            SetTrainStatus(((UINT16_S)cycle),TRAIN_STATE_FAILURE);

            /*清除列车通信状态*/
            SetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle),DEFAULT_ZERO);

        } 
        else
        {
            /*Do nothing currently !*/
        }
    }
}

/*
* 函数名称： ProcessTrainCommFailure
* 功能描述： 判断单个列车通信故障状态
* 输入参数： const UINT16 commTrainId,通讯列车ID   
* 输出参数： 无
* 返回值  ： 无
*/
void ProcessTrainCommFailure(const UINT16_S commTrainId)
{
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S trainOccAcNum = DEFAULT_ZERO;
    UINT16_S trainOccAcIdBuff[ZC_TWO_POINT_AC_NUM_MAX] = {DEFAULT_ZERO};
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S frontTrainId = DEFAULT_ZERO;
    UINT16_S rearTrainId = DEFAULT_ZERO;

    /*初始化*/
    MemorySet(&trainUnSafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),DEFAULT_ZERO,((UINT32_S)(sizeof(TrainSafeLocStruct))));
    MemorySet(&trainOccAcIdBuff[DEFAULT_ZERO],((UINT32_S)(sizeof(UINT16_S)*ZC_TWO_POINT_AC_NUM_MAX)),
               DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*ZC_TWO_POINT_AC_NUM_MAX)));

    /*获取列车信息*/
    trainDir = GetTrainUnsafeDirection(commTrainId);

    if (RETURN_SUCCESS == GetTrainUnSafeLoc(commTrainId,&trainUnSafeLocStru))
    {
        tempRtn = CheckAcOrderBetweenTwoPoints(trainUnSafeLocStru.TrainTailLink,trainUnSafeLocStru.TrainHeadLink,trainDir,&trainOccAcNum,trainOccAcIdBuff);

        if ((2U == tempRtn) || (1U == tempRtn))
        {
            /*处理列车占压的计轴区段*/
            for (cycle = DEFAULT_ZERO;cycle < trainOccAcNum;cycle++)
            {
                /*获取计轴区段内列车序列信息*/
                if (DEFAULT_ZERO == cycle)
                {
                    /*车尾所在计轴区段*/
                    rearTrainId = FindRearTrainOfTrainCommFailure(commTrainId,trainOccAcIdBuff[cycle]);

                    if ((DEFAULT_ZERO != rearTrainId)
                        && (commTrainId != rearTrainId))
                    {
                        SetTrainToModeToRM0(rearTrainId);

                        LogPrintf(1U,"17.002 Find rearTrainId=%d!\n",rearTrainId);
                        LogPrintf(1u,"%d-B72\n",rearTrainId);
                    } 
                    else
                    {
                        /*不处理*/
                    }
                } 
                else
                {
                    /*不处理*/
                }

                if (cycle == (trainOccAcNum - 1U))
                {
                    /*车头所在计轴区段*/
                    frontTrainId = FindFrontTrainOfTrainCommFailure(commTrainId,trainOccAcIdBuff[cycle]);

                    if ((DEFAULT_ZERO != frontTrainId)
                        && (commTrainId != frontTrainId))
                    {
                        SetTrainSuspectTail(frontTrainId,FLAG_SET);

                        LogPrintf(1U,"17.003 Find frontTrainId=%d!\n",frontTrainId);
                    } 
                    else
                    {
                        /*不处理*/
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
            /*不处理*/
        }
    } 
    else
    {
        /* 不处理 */
    }    
}

/*
* 函数名称： FindFrontTrainOfTrainCommFailure
* 功能描述： 查找故障列车前方列车（车头所在计轴和车头所在计轴前方计轴）
* 输入参数： const UINT16 trainId,列车的ID 
*            const UINT16_S acId,车头所在计轴区段
* 输出参数： 无
* 返回值  ： 0:未查到列车
*           >0:列车Id
*/
UINT16_S FindFrontTrainOfTrainCommFailure(const UINT16_S trainId,const UINT16_S acId)
{
    UINT16_S frontAcId = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC];
    UINT8_S trainNumInAc = DEFAULT_ZERO;
    UINT16_S frontTrainId = DEFAULT_ZERO;
    UINT8_S trainSeqInAc = DEFAULT_ZERO;
    UINT8_S trainNumInFrontAc = DEFAULT_ZERO;
    UINT8_S frontAcDir = DEFAULT_ZERO;
    UINT16_S frontAcTrainId = DEFAULT_ZERO;
    UINT8_S getFlag = RETURN_ERROR;
	
    /*初始化*/
    MemorySet(&trainSequenceBuff[DEFAULT_ZERO],sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC,DEFAULT_ZERO,sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC);

    trainSeqInAc = GetTrainIdInTrainSequence(acId,trainId);
    trainDir = GetTrainUnsafeDirection(trainId);

    /*获取计轴区段列车数量*/
    trainNumInAc = GetAcTrainOfAcNum(acId);

    if ((DEFAULT_UINT8_VALUE != trainSeqInAc)
        && (DEFAULT_ZERO < trainNumInAc))
    {
        if (DEFAULT_ZERO == trainSeqInAc)
        {
            /*第一列车,查询前方计轴第后列车*/
            tempRtn = CheckFrontACStatus(acId,trainDir,&frontAcId);

            if ((RETURN_SUCCESS == tempRtn)
                && (DEFAULT_ZERO != frontAcId))
            {
                /*获取前方计轴区段列车数量*/
                trainNumInFrontAc = GetAcTrainOfAcNum(frontAcId);

                if ((DEFAULT_ZERO < trainNumInFrontAc)
                    && (DEFAULT_UINT8_VALUE != trainNumInFrontAc))
                {
                    frontAcDir = CalculateTrainDirInOtherAc(FLAG_SET,acId,frontAcId,trainDir);             
					getFlag = GetAcTrainSequenceBuff(frontAcId,SIZE_MAX_TRAINOFAC,trainSequenceBuff);
					
                    if ((AC_DIR_FARAWAY == frontAcDir) && (RETURN_SUCCESS == getFlag))
                    {
                        /*获取前方计轴第一不为自身的列车ID*/
                        for (cycle = DEFAULT_ZERO;cycle < trainNumInFrontAc;cycle++)
                        {
                            frontAcTrainId = trainSequenceBuff[(trainNumInFrontAc - cycle) - 1U];

                            if (trainId != frontAcTrainId)
                            {
                                frontTrainId = frontAcTrainId;
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
                else
                {
                    /*不处理*/
                }
            } 
            else
            {
                /*无车,不处理*/
            }
        } 
        else
        {
            /*不是本计轴第一列车,获取该计轴上一列车ID*/
            if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(acId,(trainSeqInAc - 1U),&frontTrainId))
            {
                /*Do nothing currently !*/
            } 
            else
            {
                frontTrainId = DEFAULT_ZERO;
            }
        }

    } 
    else
    {
        /*不处理*/
    }

    return frontTrainId;
}

/*
* 函数名称： FindRearTrainOfTrainCommFailure
* 功能描述： 查找故障列车后方列车（车头所在计轴和车头所在计轴前方计轴）
* 输入参数： const UINT16 trainId,列车的ID 
*            const UINT16_S acId,车尾所在计轴区段
* 输出参数： 无
* 返回值  ： 0 :未查到列车
*            >0:列车Id
*/
UINT16_S FindRearTrainOfTrainCommFailure(const UINT16_S trainId,const UINT16_S acId)
{
    UINT16_S rearAcId = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC];
    UINT8_S trainNumInAc = DEFAULT_ZERO;
    UINT16_S rearTrainId = DEFAULT_ZERO;
    UINT8_S trainSeqInAc = DEFAULT_ZERO;
    UINT8_S trainNumInRearAc = DEFAULT_ZERO;
    UINT8_S rearAcDir = DEFAULT_ZERO;
    UINT8_S getFlag = RETURN_ERROR;
	
    /*初始化*/
    MemorySet(&trainSequenceBuff[DEFAULT_ZERO],sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC,DEFAULT_ZERO,sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC);

    trainSeqInAc = GetTrainIdInTrainSequence(acId,trainId);
    trainDir = GetTrainUnsafeDirection(trainId);

    /*获取计轴区段列车数量*/
    trainNumInAc = GetAcTrainOfAcNum(acId);

    if ((DEFAULT_UINT8_VALUE != trainSeqInAc)
        && (DEFAULT_ZERO < trainNumInAc))
    {
        if (trainSeqInAc == (trainNumInAc - 1U))
        {
            /*最后一列车,查询后方计轴第一列车*/
            tempRtn = CheckRearACStatus(acId,trainDir,&rearAcId);

            if ((RETURN_SUCCESS == tempRtn)
                && (DEFAULT_ZERO != rearAcId))
            {
                /*获取后方计轴区段列车数量*/
                trainNumInRearAc = GetAcTrainOfAcNum(rearAcId);

                if ((DEFAULT_ZERO < trainNumInRearAc)
                    && (DEFAULT_UINT8_VALUE != trainNumInRearAc))
                {
                    rearAcDir = CalculateTrainDirInOtherAc(FLAG_UNSET,acId,rearAcId,trainDir);
                    getFlag = GetAcTrainSequenceBuff(rearAcId,SIZE_MAX_TRAINOFAC,trainSequenceBuff);
					
                    if ((AC_DIR_CLOSED == rearAcDir) && (RETURN_SUCCESS == getFlag))
                    {
                        /*获取后方计轴第一个不为自身的列车ID*/
                        for (cycle = DEFAULT_ZERO;cycle < trainNumInRearAc;cycle++)
                        {
                            if (trainId != trainSequenceBuff[cycle])
                            {
                                rearTrainId = trainSequenceBuff[cycle];
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
                else
                {
                    /*不处理*/
                }
            } 
            else
            {
                /*无车,不处理*/
            }
        } 
        else
        {
            /*不是本计轴最后一列车,获取该计轴下一列车ID*/
            if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(acId,((UINT8_S)(trainSeqInAc + 1U)),&rearTrainId))
            {
                /*Do nothing currently !*/
            } 
            else
            {
                rearTrainId = DEFAULT_ZERO;
            }
        }

    } 
    else
    {
        /*Do nothing currently !*/
    }

    return rearTrainId;
}



