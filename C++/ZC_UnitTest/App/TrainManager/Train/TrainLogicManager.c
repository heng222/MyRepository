/********************************************************                                                                                                            
 文 件 名： TrainStatusData.c   
 作    者： ZC组
 创建时间： 2015-07-05
 描述： 列车逻辑处理 
 备注： 无  
********************************************************/
#include "TrainLogicManager.h"
#include "TrainStatusData.h"
#include "../../IOManager/CommTarget/CommTargetStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../LineDataManager/AC/ACStatusData.h"
#include "../../LineDataManager/AC/ACConfigData.h"
#include "../../LineDataManager/AC/ACLogicManager.h"
#include "../../LineDataManager/Switch/SwitchDefine.h"
#include "../../LineDataManager/Route/RouteConfigData.h"
#include "../../LineDataManager/Route/RouteStatusData.h"
#include "../../LineDataManager/Signal/SignalConfigData.h"
#include "../../LineDataManager/Signal/SignalStatusData.h"
#include "../../LineDataManager/Change/ChangeConfigData.h"
#include "../../LineDataManager/Switch/SwitchStatusData.h"
#include "../MA/MAStatusData.h"
#include "../../LineDataManager/Overlap/OverlapStatusData.h"
#include "../../LineDataManager/Overlap/OverlapConfigData.h"
#include "../../../Common/Copy.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataHandle.h"
#include "../../../Dmu/DmuComm/Data/StopSectionData.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"
#include "../../LineDataManager/Switch/SwitchConfigData.h"
#include "../../LineDataManager/Change/ChangeLogicManager.h"


/*************************************************
  函数名:      SetTrainToModeToRM0
  功能描述:    列车降级处理
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      无
*************************************************/
void SetTrainToModeToRM0(const UINT16_S trainId)
{
    /*获取列车类型*/
    switch (GetTrainType(trainId))
    {
    case TRAIN_MODE_CBTC:
        /*设置移动授权为空MA*/
        ClearSingleTrainMaInfo(trainId);

        /*申请MA数组位置*/
        SetMaStatusTrainId(trainId);

        SetMaType(trainId,ABNORMAL_MA_TYPE);

        /*设置列车类型*/
        SetTrainType(trainId,TRAIN_MODE_TO_RM0);
        break;
    case TRAIN_MODE_TO_RM0:
        /*设置移动授权为空MA*/
        SetMaType(trainId,ABNORMAL_MA_TYPE);
        break;
    default:
        /*清空移动授权输出*/
        SetMaType(trainId,DEFAULT_ZERO);
        break;
    }	
}

/*************************************************
  函数名:      TrainDirChangeForCheck
  功能描述:    转换列车方向用于反向查询
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      转换值 
*************************************************/
UINT8_S TrainDirChangeForCheck(const UINT16_S trainId)
{
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S rtnValue =DEFAULT_ZERO;

    trainDir = GetTrainUnsafeDirection(trainId);

    switch (trainDir)
    {
    case TRAIN_UNSAFE_DIR_UP:
        rtnValue = TRAIN_UNSAFE_DIR_DOWN;
        break;
    case TRAIN_UNSAFE_DIR_DOWN:
        rtnValue = TRAIN_UNSAFE_DIR_UP;
        break;
    default:
        break;
    }

    return rtnValue;
}

/*************************************************
  函数名:      JudgeTrainNeedCalculate
  功能描述:    判断列车是否需要进行相应的计算
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      1U:需要
               0U:不需要
*************************************************/
UINT8_S JudgeTrainNeedCalculate(const UINT16_S trainId)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT16_S trainControlZc = DEFAULT_ZERO;
    UINT8_S handoverInType = DEFAULT_ZERO;   
    UINT8_S trainInType = DEFAULT_ZERO;
    UINT8_S trainStatus = DEFAULT_ZERO;

    localZcId = GetLocalZcId();
    trainControlZc = GetTrainControlZc(trainId);
    handoverInType = GetTrainHandoverInType(trainId);
    trainInType = GetTrainInType(trainId);
    trainStatus = GetTrainStatus(trainId);

    /* pbw 2017.8.2 暂行将保留受控 */
    /*
    if ((trainControlZc == localZcId)
        || (NZC_TRAIN_HANDOVER == handoverInType)
        || (NZC_TRAIN_CONFIRMATION == handoverInType)
        || (DEFAULT_ZERO != trainInType )
        || (DEFAULT_ZERO != trainStatus))
    */
    if((trainControlZc == localZcId) 
        || (DEFAULT_ZERO != trainInType))
    {
        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      CalculateTrainSafePos
  功能描述:    计算列车安全位置
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void CalculateTrainSafePos(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT8_S needCalculateFlag = RETURN_ERROR;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        /*获取列车ID*/
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);
        needCalculateFlag = JudgeTrainNeedCalculate(trainId);

        if ((DEFAULT_ZERO != trainId)
            && (TRAIN_MODE_OUT != trainType)
            && (DEFAULT_ZERO != trainType)
            && (RETURN_SUCCESS == needCalculateFlag))
        {
            /*计算列车安全车头位置*/
            CalculateTrainHeadSafePos(trainId);

            /*计算列车安全车尾位置*/
            CalculateTrainTailSafePos(trainId);
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*************************************************
  函数名:      CalculateTrainHeadSafePos
  功能描述:    计算列车安全车头位置
  输入:        const UINT16_S trainId,列车ID
  输出:        无
  返回值:      无
*************************************************/
void CalculateTrainHeadSafePos(const UINT16_S trainId)
{
    UINT32_S headDistance = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnsafeLocStru;
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S rtnOfCheck = DEFAULT_ZERO;
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S trainHeadAc = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S acBelongLink = DEFAULT_ZERO;
    UINT32_S acBelongOffset = DEFAULT_ZERO;
    UINT8_S occStatus = DEFAULT_ZERO;
	UINT16_S errorSwitchId = DEFAULT_ZERO;
	UINT16_S errorAcOfSwitchId[SIZE_MAX_SWITCH_MUM_OF_SAFE_TRAIN] = {DEFAULT_ZERO};
	UINT8_S switchNum = DEFAULT_ZERO;
	UINT8_S switchCycle = DEFAULT_ZERO;
    UINT16_S endAcOfLine = DEFAULT_ZERO;    /* 线路尽头的计轴区段 */

	MemorySet(&trainUnsafeLocStru,(UINT32_S)(sizeof(TrainSafeLocStruct)),DEFAULT_ZERO,(UINT32_S)(sizeof(TrainSafeLocStruct)));
    MemorySet(&trainSafeLocStru,(UINT32_S)(sizeof(TrainSafeLocStruct)),DEFAULT_ZERO,(UINT32_S)(sizeof(TrainSafeLocStruct)));
	
    /*计算安全位置需要的距离*/
    headDistance = CalculateTrainHeadDistance(trainId);

    /*获取列车信息*/
    tempRtn = GetTrainUnSafeLoc(trainId,&trainUnsafeLocStru);
    trainDir = GetTrainUnsafeDirection(trainId);

    if (RETURN_SUCCESS == tempRtn)
    {
		rtnOfCheck = CalculateTrainSafeLocAcOfSwitch(1u,trainId,headDistance,trainDir,errorAcOfSwitchId,&switchNum,&endAcOfLine);
		
		if (3u == rtnOfCheck)
		{
			rtnOfCheck = CheckNextPointOnDistance(trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset,trainDir,headDistance,
				&trainSafeLocStru.TrainHeadLink,&trainSafeLocStru.TrainHeadOffset,&errorSwitchId);
		} 
		else
		{
			/* 不处理 */
		}

        switch (rtnOfCheck)
        {
        case 0U:
            /*查询失败*/
            SetTrainToModeToRM0(trainId);
            SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);
			LogPrintf(1u,"%d-B55\n",trainId);
            break;
        case 1U:
            /*由于线路尽头到导致查询失败*/
            /* pbw 2017.5.23 使用线路尽头处的计轴区段 */
            if (DEFAULT_ZERO != endAcOfLine)
            {
                if (RETURN_SUCCESS == CheckAcTerminalPosition(endAcOfLine,((UINT16_S)trainDir),&acBelongLink,&acBelongOffset))
                {
                    SetTrainSafeHeadLoc(trainId,acBelongLink,acBelongOffset);
                } 
                else
                {
                    /*查询失败*/
                    SetTrainToModeToRM0(trainId);
					
                    SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);

                    LogPrintf(1u,"%d-B56\n",trainId);
                }
            } 
            else
            {
                /*查询失败*/
                SetTrainToModeToRM0(trainId);
				
                SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);

                LogPrintf(1u,"%d-B57\n",trainId);
            }
            break;
        case 2U:
            /*由于道岔原因导致查询失败*/
			for (switchCycle = 0u; switchCycle < switchNum; switchCycle++)
			{
				occStatus = JudgeSwitchBelongAcOccStatus(errorAcOfSwitchId[switchCycle]);

				if ((DEFAULT_ZERO != errorAcOfSwitchId[switchCycle])
					&& (RETURN_SUCCESS == occStatus))
				{
					/*查询列车车头所在计轴区段*/
					trainHeadAc = CheckPositionBelongAc(trainUnsafeLocStru.TrainHeadLink);

					if (RETURN_SUCCESS == CheckAcTerminalPosition(trainHeadAc,((UINT16_S)trainDir),&acBelongLink,&acBelongOffset))
					{
						SetTrainSafeHeadLoc(trainId,acBelongLink,acBelongOffset);
					} 
					else
					{
						/* 查询失败,跳出循环 */
						SetTrainToModeToRM0(trainId);
						
						SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);

                        LogPrintf(1u,"%d-B58\n",trainId);

                        break;
					}
				} 
				else
				{
					/* 查询失败,跳出循环 */
					SetTrainToModeToRM0(trainId);
					
					SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);

                    LogPrintf(1u,"%d-B59\n",trainId);

                    break;
				}
			}
           
            break;
        case 3U:
            /*查询成功*/
            SetTrainSafeHeadLoc(trainId,trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset);

            break;
        default:
            SetTrainToModeToRM0(trainId);
			
            SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);

            LogPrintf(1u,"%d-B60\n",trainId);
            break;
        }
    } 
    else
    {
        /*不处理*/
    }

}

/*************************************************
  函数名:      CalculateTrainTailSafePos
  功能描述:    计算列车安全车尾位置
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      无
*************************************************/
void CalculateTrainTailSafePos(const UINT16_S trainId)
{
    UINT32_S tailDistance = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnsafeLocStru;
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S rtnOfCheck = DEFAULT_ZERO;
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S errorSwitchId = DEFAULT_ZERO;
    UINT16_S trainTailAc = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S acBelongLink = DEFAULT_ZERO;
    UINT32_S acBelongOffset = DEFAULT_ZERO;
    UINT8_S occStatus = DEFAULT_ZERO;
	UINT16_S errorAcOfSwitchId[SIZE_MAX_SWITCH_MUM_OF_SAFE_TRAIN] = {DEFAULT_ZERO};
	UINT8_S switchNum = DEFAULT_ZERO;
	UINT8_S switchCycle = DEFAULT_ZERO;
    UINT16_S endAcOfLine = DEFAULT_ZERO;    /* 线路尽头的计轴区段 */

	MemorySet(&trainUnsafeLocStru,(UINT32_S)(sizeof(TrainSafeLocStruct)),DEFAULT_ZERO,(UINT32_S)(sizeof(TrainSafeLocStruct)));
    MemorySet(&trainSafeLocStru,(UINT32_S)(sizeof(TrainSafeLocStruct)),DEFAULT_ZERO,(UINT32_S)(sizeof(TrainSafeLocStruct)));
	
    /*计算安全车尾位置需要的距离*/
    tailDistance = CalculateTrainTailDistance(trainId);

    /*获取列车信息*/
    tempRtn = GetTrainUnSafeLoc(trainId,&trainUnsafeLocStru);
    trainDir = GetTrainUnsafeDirection(trainId);

    if (RETURN_SUCCESS == tempRtn)
    {
		rtnOfCheck = CalculateTrainSafeLocAcOfSwitch(2u,trainId,tailDistance,trainDir,errorAcOfSwitchId,&switchNum,&endAcOfLine);

		if (3u == rtnOfCheck)
		{
			rtnOfCheck = CheckNextPointOnDistance(trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset,TrainDirChangeForCheck(trainId),tailDistance,
				&trainSafeLocStru.TrainTailLink,&trainSafeLocStru.TrainTailOffset,&errorSwitchId);
		} 
		else
		{
			/* 不处理 */
		}

        switch (rtnOfCheck)
        {
        case 0U:
            /*查询失败*/
            SetTrainToModeToRM0(trainId);
			
            SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

            LogPrintf(1u,"%d-B61\n",trainId);
            break;
        case 1U:
            /*由于线路尽头到导致查询失败*/
            /* pbw 2017.5.23 使用线路尽头处的计轴区段 */
            if (DEFAULT_ZERO != endAcOfLine)
            {
                if (RETURN_SUCCESS == CheckAcTopPosition(endAcOfLine,((UINT16_S)trainDir),&acBelongLink,&acBelongOffset))
                {
                    SetTrainSafeTailLoc(trainId,acBelongLink,acBelongOffset);
                } 
                else
                {
                    /*查询失败*/
                    SetTrainToModeToRM0(trainId);
					
                    SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

                    LogPrintf(1u,"%d-B62\n",trainId);
                }
            } 
            else
            {
                /*查询失败*/
                SetTrainToModeToRM0(trainId);
				
                SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

                LogPrintf(1u,"%d-B63\n",trainId);
            }
            break;
        case 2U:
            /*由于道岔原因导致查询失败*/
			for (switchCycle = 0u; switchCycle < switchNum; switchCycle++)
			{
				occStatus = JudgeSwitchBelongAcOccStatus(errorAcOfSwitchId[switchCycle]);

				if ((DEFAULT_ZERO != errorAcOfSwitchId[switchCycle])
					&& (RETURN_SUCCESS == occStatus))
				{
					/*查询列车车尾所在计轴区段*/
					trainTailAc = CheckPositionBelongAc(trainUnsafeLocStru.TrainTailLink);

					if (RETURN_SUCCESS == CheckAcTopPosition(trainTailAc,((UINT16_S)(trainDir)),&acBelongLink,&acBelongOffset))
					{
						SetTrainSafeTailLoc(trainId,acBelongLink,acBelongOffset);
					} 
					else
					{
						/* 查询失败,跳出循环 */
						SetTrainToModeToRM0(trainId);
						
						SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

                        LogPrintf(1u,"%d-B64\n",trainId);

                        break;
					}
				} 
				else
				{
					/* 查询失败,跳出循环 */
					SetTrainToModeToRM0(trainId);
					
					SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

                    LogPrintf(1u,"%d-B65\n",trainId);

                    break;
				}
			}
            break;
        case 3U:
            /*查询成功*/
            SetTrainSafeTailLoc(trainId,trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset);
            break;
        default:
            /*查询失败*/
            SetTrainToModeToRM0(trainId);
			
            SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

            LogPrintf(1u,"%d-B66\n",trainId);
            break;
        }
    } 
    else
    {
        /*不处理*/
    }
}

/*************************************************
  函数名:      CalculateTrainHeadDistance
  功能描述:    计算列车安全车头位置需要的距离
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      距离值
*************************************************/
UINT32_S CalculateTrainHeadDistance(const UINT16_S trainId)
{
    UINT32_S headDistance = DEFAULT_ZERO;
    UINT32_S trainRedundancy = DEFAULT_ZERO;
    UINT16_S trainError = DEFAULT_ZERO;
    UINT16_S trainSpeed = DEFAULT_ZERO;
    UINT16_S configMaxTrainLen = DEFAULT_ZERO;
	UINT32_S commTargetCycle = DEFAULT_ZERO;  /* 通讯延时周期数 */
	UINT32_S trainPrtclDelay = DEFAULT_ZERO;

    /*计算列车最大的延迟时间*/
	commTargetCycle = (UINT32_S)GetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId);
	trainPrtclDelay = (UINT32_S)GetTrainPrtclDelay(trainId);
	
    trainRedundancy = (UINT32_S)(((commTargetCycle + trainPrtclDelay) * 4U) / 10U);

    /*获取列车信息*/
    trainError = GetTrainError(trainId);
    trainSpeed = GetTrainSpeed(trainId);

    if (RETURN_UINT16_MAX_VALUE == trainSpeed)
    {
        trainSpeed = GetLineMaxSpeed();
    } 
    else
    {
        /*不处理*/
    }

    /*计算列车车头包络距离*/
    headDistance = trainError + (UINT32_S)((trainSpeed * trainRedundancy) + ((GetMaxTrainTractionAcc(trainId) * (trainRedundancy * trainRedundancy)) / 2U));

    configMaxTrainLen = GetLineMaxTrainLength();

    /*判断车头包络距离是否超过允许最大值*/
    if(configMaxTrainLen <= headDistance)
    {
        /*将车头包络距离设置为最大允许值*/
        headDistance = configMaxTrainLen;
    }
    else
    {
        /*不处理*/
    }

    return headDistance;
}

/*************************************************
  函数名:      CalculateTrainTailDistance
  功能描述:    计算列车安全车尾位置需要的距离
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      距离值
*************************************************/
UINT32_S CalculateTrainTailDistance(const UINT16_S trainId)
{
    UINT32_S tailDistance = DEFAULT_ZERO;
    UINT8_S unsafeDirection = DEFAULT_ZERO;
    UINT8_S realDirection = DEFAULT_ZERO;
    UINT32_S trainError = DEFAULT_ZERO;
	UINT32_S retreatDistance = DEFAULT_ZERO;
	
    unsafeDirection = GetTrainUnsafeDirection(trainId);
    realDirection = GetTrainRealDirection(trainId);
	trainError = (UINT32_S)GetTrainError(trainId);

    if((TRAIN_MIN_SPEED <= GetTrainSpeed(trainId))
        &&(unsafeDirection != realDirection))
    {
        /*列车处于非零速状态且期望运行方向与实际运行方向相反*/
		retreatDistance = (UINT32_S)GetRetreatProtectDistance();
		
        tailDistance = trainError + retreatDistance;
    }
    else
    {
        /*运行方向相同，只考虑不确定误差信息*/
        tailDistance = trainError;
    }

    return tailDistance;
}

/*************************************************
  函数名:      JudgeSwitchBelongAcOccStatus
  功能描述:    计算列车安全车尾位置需要的距离
  输入:        cosnt UINT16_S swtichId 道岔ID
  输出:        无
  返回值:      0u:占用
               1u:未占用
*************************************************/
UINT8_S JudgeSwitchBelongAcOccStatus(const UINT16_S swtichId)
{
    UINT8_S switchBelongAcNum = DEFAULT_ZERO;
    UINT16_S switchBelongAcIdBuff[SWITCH_BELONG_AC_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;

    /*查询道岔属于的计轴区段信息*/
    if (RETURN_SUCCESS == CheckSwitchBelongAc(swtichId,&switchBelongAcNum,switchBelongAcIdBuff))
    {
        for (cycle = DEFAULT_ZERO;cycle < switchBelongAcNum;cycle++)
        {
            if (AC_OCC_STATUS == GetAcStatusNow(switchBelongAcIdBuff[cycle]))
            {
                rtnValue = RETURN_ERROR;
                break;
            } 
            else
            {
                /*不处理*/
            }
        }

        if (cycle == switchBelongAcNum)
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
UINT8_S CalculateTrainSafeLocAcOfSwitch(const UINT8_S flag,const UINT16_S trainId,const UINT32_S distance,const UINT8_S dir,UINT16_S errorSwitchOrAcId[SIZE_MAX_SWITCH_MUM_OF_SAFE_TRAIN],UINT8_S * pSwitchOrAcNum,UINT16_S *endAcOfLine)
{
	UINT16_S locOfAcId = DEFAULT_ZERO;
	UINT8_S rtn = DEFAULT_ZERO;
	UINT8_S checkRtn = DEFAULT_ZERO;
	UINT16_S frontAcIdBuff[MAX_ADJACENT_LOSE_AC] = {DEFAULT_ZERO};
	UINT16_S frontAcId = DEFAULT_ZERO;
	UINT8_S frontAcNum = DEFAULT_ZERO;
	UINT8_S cycleAc = DEFAULT_ZERO;
	UINT8_S rtnOfSwitch = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;
	UINT8_S tempRtn = DEFAULT_ZERO;
	TrainSafeLocStruct trainUnsafeLocStru;
	UINT16_S pointLink = DEFAULT_ZERO;
	UINT32_S pointOffset = DEFAULT_ZERO;
	UINT8_S rtnOfLoc = DEFAULT_ZERO;
	UINT32_S checkDisRtn = DEFAULT_ZERO;
	UINT32_S addtDis = DEFAULT_ZERO;
	UINT32_S lenOfAc = DEFAULT_ZERO;
	UINT8_S checkRtnOfLenAc = DEFAULT_ZERO;
	UINT16_S calErrorSwitchId[AC_SWITCH_SUM_MAX] = {DEFAULT_ZERO};
	UINT8_S calErrorSwitchNum = DEFAULT_ZERO;
	UINT8_S cycleCalSwitch = DEFAULT_ZERO;
	UINT8_S checkDir = DEFAULT_ZERO;

    if ((NULL != pSwitchOrAcNum) && (NULL != endAcOfLine))
    {
        /*初始化输入变量*/
        (* pSwitchOrAcNum) = DEFAULT_ZERO;
        MemorySet(&trainUnsafeLocStru,(UINT32_S)(sizeof(TrainSafeLocStruct)),DEFAULT_ZERO,(UINT32_S)(sizeof(TrainSafeLocStruct)));
        (*endAcOfLine) = DEFAULT_ZERO;

        /*获取列车信息*/
        tempRtn = GetTrainUnSafeLoc(trainId,&trainUnsafeLocStru);

        /*判断列车位置所在计轴*/
        if (1u == flag)
        {
            /*车头位置*/
            locOfAcId = CheckPositionBelongAc(trainUnsafeLocStru.TrainHeadLink);
            checkDir = dir;

            /*查询计轴终端位置*/
            rtnOfLoc = CheckAcTerminalPosition(locOfAcId,(UINT16_S)dir,&pointLink,&pointOffset);
        } 
        else if (2u == flag)
        {
            /*车尾位置*/
            locOfAcId = CheckPositionBelongAc(trainUnsafeLocStru.TrainTailLink);
            checkDir = TrainDirChangeForCheck(trainId);

            /*查询计轴始端位置*/
            rtnOfLoc = CheckAcTopPosition(locOfAcId,(UINT16_S)dir,&pointLink,&pointOffset);
        } 
        else
        {
            /*输入参数校验失败*/
            rtn = 0u;
        }
    }
	
	if (RETURN_SUCCESS == rtnOfLoc)
	{
		if (1u == flag)
		{
			checkDisRtn = GetDirBothSegPointDisPlus(trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset,
				pointLink,pointOffset,checkDir,&addtDis);
		} 
		else
		{
			checkDisRtn = GetDirBothSegPointDisPlus(trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset,
				pointLink,pointOffset,checkDir,&addtDis);
		}

		if (RETURN_SUCCESS == checkDisRtn)
		{
			/*先设置为成功状态*/
			rtn = 3u;

			while (addtDis < distance)
			{
				/*获取当前确定计轴的下一个计轴区段*/
				checkRtn = CheckFrontACCanStatus(locOfAcId,checkDir,&frontAcNum,frontAcIdBuff);

				if ((RETURN_SUCCESS == checkRtn) || (3u == checkRtn))
				{
					for (cycleAc = DEFAULT_ZERO;cycleAc < frontAcNum;cycleAc++)
					{
						/*查询计轴区段对应的道岔区段*/
						rtnOfSwitch = JudgeSwitchPostionInAc(frontAcIdBuff[cycleAc],calErrorSwitchId,&calErrorSwitchNum);

						if (2u == rtnOfSwitch)
						{
							frontAcId = frontAcIdBuff[cycleAc];
							breakFlag = FLAG_SET;
						} 
						else
						{
							/*记录道岔情况*/
							if(1u == rtnOfSwitch)
							{
								for (cycleCalSwitch = 0u; cycleCalSwitch < calErrorSwitchNum; cycleCalSwitch++)
								{
									errorSwitchOrAcId[(* pSwitchOrAcNum)] = calErrorSwitchId[cycleCalSwitch];
									(* pSwitchOrAcNum)++;
								}
							}
							else
							{
								breakFlag = FLAG_UNSET;
							}
						}
					}

					if (FLAG_SET == breakFlag)
					{
						/*累加计轴长度*/
						checkRtnOfLenAc = GetLineAcLength(frontAcId,&lenOfAc);

						if (checkRtnOfLenAc == RETURN_SUCCESS)
						{
							addtDis = addtDis + lenOfAc;

							locOfAcId = frontAcId;
						} 
						else
						{
							rtn = 0u;
							break;
						}
					} 
					else
					{
						if (breakFlag == FLAG_UNSET)
						{
							rtn = 0u;
							break;
						}
						else
						{
							rtn = 2u;
							break;
						}
					}
				} 
				else
				{
					if (2u == checkRtn)
					{
						/*线路尽头导致失败*/
						rtn = 1u;

                        /* pbw 2017.5.23 返回最后线路尽头最后1个计轴区段 */                       
                        (*endAcOfLine) = locOfAcId;
					} 
					else
					{
						rtn = 0u;
					}
					
					break;
				}
			}
		} 
		else
		{
			rtn = 0u;
		}
	} 
	else
	{
		rtn = 0u;
	}

	return rtn;
}

/*************************************************
  函数名:      ManageTrainDangerousSource
  功能描述:    处理列车前方和后方危险源信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageTrainDangerousSource(void)
{
	UINT8_S cycle = DEFAULT_ZERO;
	UINT16_S trainId = DEFAULT_ZERO;
	UINT8_S trainType = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
	{
		trainId = GetTrainIdOfIndex(cycle);

		if (GetTrainControlZc(trainId) == GetLocalZcId())
		{
			/*获取列车ID*/
			if (FLAG_SET == GetTrainSuspectHead(trainId))
			{
				/*处理列车前端危险源（前方可疑区域）*/
				if (RETURN_SUCCESS == JudgeTrainHeadSuspect(trainId))
				{
					/*去除列车前方危险源标记*/
					SetTrainSuspectHead(trainId,FLAG_UNSET);

					LogPrintf(1U,"1.01 remove train[%d] suspect head!\n",trainId);
				} 
				else
				{
					/*不处理*/
				}
			} 
			else
			{
				/*判断是否需要在本周期添加列车前端危险源标记*/
				trainType = GetTrainType(trainId);

				if (((TRAIN_MODE_CBTC != trainType) && (TRAIN_MODE_TO_RM0 != trainType)))
				{
					/*车头位于本zc管辖范围内的非CBTC列车周期添加前端*/
					ManageAddTrainHeadSuspect(trainId);
				} 
				else
				{
					/*不处理*/
				}
			}
          
			if (FLAG_SET == GetTrainSuspectTail(trainId))
			{              
				/*处理列车后端危险源（后方可疑区域）*/
				if (RETURN_SUCCESS == JudgeTrainTailSuspect(trainId))
				{
					/*去除列车后方危险源标记*/
					SetTrainSuspectTail(trainId,FLAG_UNSET);

					LogPrintf(1U,"1.02 remove train[%d] suspect tail!\n",trainId);
				} 
				else
				{
					/*不处理*/
				}
			} 
			else
			{
				/*判断是否需要在本周期添加列车后方危险源标记*/			
				ManageAddTrainTailSuspect(trainId);
			}
		} 
		else
		{
			/*不处理*/
		}
	}
}

/*************************************************
  函数名:      ManageAddTrainHeadSuspect
  功能描述:    管理列车前方危险源信息（是否由于危险源而添加前方危险区域标记）
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      无
*************************************************/
void ManageAddTrainHeadSuspect(const UINT16_S trainId)
{
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainUnSafeHeadAcId = DEFAULT_ZERO;
    UINT16_S frontAcId = DEFAULT_ZERO;
    UINT8_S acDir = DEFAULT_ZERO;
    UINT8_S trainSeqIndex = DEFAULT_ZERO;
    UINT16_S trainIdInSeq = DEFAULT_ZERO;
    UINT16_S errorCode = 0U;
    UINT8_S rtnFrontAc = DEFAULT_ZERO;
    UINT8_S acStatusNow = DEFAULT_ZERO;
    UINT8_S acArbFlag = DEFAULT_ZERO;
    UINT8_S acArbRedundance = DEFAULT_ZERO;
    UINT8_S acUtRedundance = DEFAULT_ZERO;

    trainDir = GetTrainUnsafeDirection(trainId);
    trainUnSafeHeadAcId = GetTrainUnsafeTrainHeadAC(trainId);
    trainSeqIndex = GetTrainIdInTrainSequence(trainUnSafeHeadAcId,trainId);

    if ((trainSeqIndex != DEFAULT_UINT8_VALUE)
        && (SIZE_MAX_TRAINOFAC != trainSeqIndex))
    {
        if (DEFAULT_ZERO == trainSeqIndex)
        {
            /*不在本计轴内或者位于本计轴第一列*/
            rtnFrontAc = CheckFrontACStatus(trainUnSafeHeadAcId,trainDir,&frontAcId);

            if (1U == rtnFrontAc)
            {
                acDir = CalculateTrainDirInOtherAc(FLAG_SET,trainUnSafeHeadAcId,frontAcId,trainDir);

                switch (acDir)
                {
                case AC_DIR_FARAWAY:

                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(frontAcId))
                    {
                        /*前方计轴无列车*/
                    } 
                    else
                    {
                        if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(frontAcId,(GetAcTrainOfAcNum(frontAcId) - 1U),&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectTail(trainIdInSeq))
                                {
                                    /*没有后方危险区域,不添加后端可疑标记*/
                                } 
                                else
                                {
                                    /*添加前方危险区域标记*/
                                    SetTrainSuspectHead(trainId,FLAG_SET);
                                    errorCode = 0x01U;
                                }
                            }
                            else
                            {
                                /*前方最后为本列车*/
                            }
                        }                        
                    }

                    break;
                case AC_DIR_CLOSED:

                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(frontAcId))
                    {
                        /*前方计轴无列车*/
                    } 
                    else
                    {
                        if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(frontAcId,0U,&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectHead(trainIdInSeq))
                                {
                                    /*没有后方危险区域,不添加后端可疑标记*/
                                } 
                                else
                                {
                                    /*添加前方危险区域标记*/
                                    SetTrainSuspectHead(trainId,FLAG_SET);
                                    errorCode = 0x02U;
                                }
                            } 
                            else
                            {
                                /*前方最后为本列车*/
                            }
                        }                                               
                    }

                    break;
                case DEFAULT_ZERO:
                    /*计算失败,直接添加前方危险区域标记*/
                    SetTrainSuspectHead(trainId,FLAG_SET);
                    errorCode = 0x03U;
                    break;

                default:
                    acStatusNow = GetAcStatusNow(frontAcId);
                    acArbFlag = GetAcArbFlag(frontAcId);
                    acArbRedundance = GetAcArbRedundance(frontAcId);
                    acUtRedundance = GetAcUtRedundance(frontAcId);

                    if ((AC_FREE_STATUS == acStatusNow)||(FLAG_SET == acArbFlag)
                        || (DEFAULT_ZERO != acArbRedundance)||(DEFAULT_ZERO != acUtRedundance))
                    {
                        /*前方无危险区域,不添加*/
                    } 
                    else
                    {
                        /*添加前方危险区域标记*/
                        SetTrainSuspectHead(trainId,FLAG_SET);
                        errorCode = 0x04U;
                    }

                    break;
                }
            }
            else
            {
                if (2U == rtnFrontAc)
                {
                    /*由于线路尽头查询失败,不处理*/
                } 
                else
                {
                    /*添加前端危险区域标记*/
                    SetTrainSuspectHead(trainId,FLAG_SET);
                    errorCode = 0x05U;
                }
            }
        } 
        else
        {
            /*列车位于该计轴区段的中间区域,查看列车前方列车后方是否可疑*/		
            if (GetTrainIdInTrainSequenceOfIndex(trainUnSafeHeadAcId,(trainSeqIndex-1U),&trainIdInSeq))
            {
                if (FLAG_UNSET == GetTrainSuspectTail(trainIdInSeq))
                {
                    /*没有后方危险区域,不添加后端可疑标记*/
                } 
                else
                {
                    /*添加前方危险区域标记*/
                    SetTrainSuspectHead(trainId,FLAG_SET);
                    errorCode = 0x06U;
                }
            } 
            else
            {
                /*添加前方危险区域标记*/
                SetTrainSuspectHead(trainId,FLAG_SET);
                errorCode = 0x07U;
            }
        }
    } 
    else
    {
        /*添加前方危险区域标记*/
        SetTrainSuspectHead(trainId,FLAG_SET);
        errorCode = 0x08U;
    }

    if (FLAG_SET == GetTrainSuspectHead(trainId))
    {
        /*已添加前方危险区域标记,列车需要紧急制动*/
        SetTrainToModeToRM0(trainId);
		LogPrintf(1u,"%d-B67\n",trainId);
    } 
    else
    {
        /*不处理*/
    }

    if (0U == errorCode)
    {
        /*不处理*/
    } 
    else
    {
        LogPrintf(1U,"1.11 TrainId=%d,UnSHeadAcId=%d,frontAcId=%d,SuspectHead=%d,errorCode=%d\n",trainId,trainUnSafeHeadAcId,frontAcId,GetTrainSuspectHead(trainId),errorCode);
    }
}

/*************************************************
  函数名:      ManageAddTrainTailSuspect
  功能描述:    管理列车后方危险源信息（是否由于危险源而添加后方危险区域标记）
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      无
*************************************************/
void ManageAddTrainTailSuspect(const UINT16_S trainId)
{
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainUnSafeTailAcId = DEFAULT_ZERO;
    UINT16_S rearAcId = DEFAULT_ZERO;
    UINT8_S acDir = DEFAULT_ZERO;
    UINT8_S trainSeqIndex = DEFAULT_ZERO;
    UINT16_S trainIdInSeq = DEFAULT_ZERO;
    UINT16_S errorCode = 0U;
    UINT8_S rtnRearAc = DEFAULT_ZERO;

    trainDir = GetTrainUnsafeDirection(trainId);
    trainUnSafeTailAcId = GetTrainUnsafeTrainTailAC(trainId);
    trainSeqIndex = GetTrainIdInTrainSequence(trainUnSafeTailAcId,trainId);

    if ((trainSeqIndex != DEFAULT_UINT8_VALUE)
        && (SIZE_MAX_TRAINOFAC != trainSeqIndex))
    {
        /* 非安全车尾所在区段有车 */
        if((GetAcTrainOfAcNum(trainUnSafeTailAcId)-1U) == trainSeqIndex)
        {
            /* 该车为该区段最末尾的列车,查询其后方计轴区段 */
            rtnRearAc = CheckRearACStatus(trainUnSafeTailAcId,trainDir,&rearAcId);

            if (RETURN_SUCCESS == rtnRearAc)
            {
                acDir = CalculateTrainDirInOtherAc(FLAG_UNSET,trainUnSafeTailAcId,rearAcId,trainDir);

                switch (acDir)
                {
                case AC_DIR_FARAWAY:
                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(rearAcId))
                    {
                        /*后方计轴区段无车*/
                    } 
                    else
                    {
                        if(RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(rearAcId,GetAcTrainOfAcNum(rearAcId)-1U,&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectTail(trainIdInSeq))
                                {
                                    /*不添加前方区域可疑标记*/
                                } 
                                else
                                {
                                    /*添加后方危险区域标记*/
                                    SetTrainSuspectTail(trainId,FLAG_SET);
                                    errorCode = 3U;
                                }
                            } 
                            else
                            {
                                /*后方列车为该列车*/
                            }
                        }                       
                    }
                    break;
                case AC_DIR_CLOSED:
                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(rearAcId))
                    {
                        /*后方计轴区段无车*/
                    }
                    else
                    {
                        if(RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(rearAcId,0U,&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectHead(trainIdInSeq))
                                {
                                    /*不添加前方区域可疑标记*/
                                } 
                                else
                                {
                                    /*添加后方危险区域标记*/
                                    SetTrainSuspectTail(trainId,FLAG_SET);
                                    errorCode = 4U;
                                }
                            } 
                            else
                            {
                                /*后方列车为该列车*/
                            }
                        }               
                    }
                    break;

                case DEFAULT_ZERO:
                    /*计算失败,添加后方危险区域标记*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 5U;
                    break;

                default:
                    if ((AC_FREE_STATUS == GetAcStatusNow(rearAcId))
                        || (FLAG_SET == GetAcArbFlag(rearAcId))
                        || (DEFAULT_ZERO != GetAcArbRedundance(rearAcId))
                        || (DEFAULT_ZERO != GetAcUtRedundance(rearAcId)))
                    {
                        /*不添加前方区域可疑标记*/
                    } 
                    else
                    {
                        /*添加后方危险区域标记*/
                        SetTrainSuspectTail(trainId,FLAG_SET);
                        LogPrintf(1U,"16.001 TrainId=%d,RearAcId=%d,UT=%d,State=%d\n",trainId,rearAcId,GetAcUtFlag(rearAcId),GetAcStatusNow(rearAcId));
                        errorCode = 6U;
                    }

                    break;
                }
            }
            else
            {
                if (2U == rtnRearAc)
                {
                    /*线路尽头查询失败,不处理*/
                } 
                else
                {
                    /*添加后方危险区域标记*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 7U;
                }
            }
        }
        else
        {
            /* 该列车后方还有其他列车,查看后方列车前方是否可疑 */		
            if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(trainUnSafeTailAcId,trainSeqIndex + 1U,&trainIdInSeq))
            {
                if (FLAG_UNSET == GetTrainSuspectHead(trainIdInSeq))
                {
                    /*不添加后端可疑标记*/
                } 
                else
                {
                    /*添加后方危险区域标记*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 1U;
                }
            } 
            else
            {
                /*添加后方危险区域标记*/
                SetTrainSuspectTail(trainId,FLAG_SET);
                errorCode = 2U;
            }
        }
#if 0
        if ((DEFAULT_ZERO < trainSeqIndex)
            && ((GetAcTrainOfAcNum(trainUnSafeTailAcId)-1U) > trainSeqIndex))
        {
            /*列车位于该计轴区段的中间区域,查看列车后方列车前方是否可疑*/		
            if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(trainUnSafeTailAcId,trainSeqIndex + 1U,&trainIdInSeq))
            {
                if (FLAG_UNSET == GetTrainSuspectHead(trainIdInSeq))
                {
                    /*不添加后端可疑标记*/
                } 
                else
                {
                    /*添加后方危险区域标记*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 1U;
                }
            } 
            else
            {
                /*添加后方危险区域标记*/
                SetTrainSuspectTail(trainId,FLAG_SET);
                errorCode = 2U;
            }
        } 
        else
        {
            /* 此计轴区段只有一列车 */
            rtnRearAc = CheckRearACStatus(trainUnSafeTailAcId,trainDir,&rearAcId);

            if (RETURN_SUCCESS == rtnRearAc)
            {
                acDir = CalculateTrainDirInOtherAc(FLAG_UNSET,trainUnSafeTailAcId,rearAcId,trainDir);

                switch (acDir)
                {
                case AC_DIR_FARAWAY:
                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(rearAcId))
                    {
                        /*后方计轴区段无车*/
                    } 
                    else
                    {
                        if(RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(rearAcId,GetAcTrainOfAcNum(rearAcId)-1U,&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectTail(trainIdInSeq))
                                {
                                    /*不添加前方区域可疑标记*/
                                } 
                                else
                                {
                                    /*添加后方危险区域标记*/
                                    SetTrainSuspectTail(trainId,FLAG_SET);
                                    errorCode = 3U;
                                }
                            } 
                            else
                            {
                                /*后方列车为该列车*/
                            }
                        }                       
                    }
                    break;
                case AC_DIR_CLOSED:
                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(rearAcId))
                    {
                        /*后方计轴区段无车*/
                    }
                    else
                    {
                        if(RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(rearAcId,0U,&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectHead(trainIdInSeq))
                                {
                                    /*不添加前方区域可疑标记*/
                                } 
                                else
                                {
                                    /*添加后方危险区域标记*/
                                    SetTrainSuspectTail(trainId,FLAG_SET);
                                    errorCode = 4U;
                                }
                            } 
                            else
                            {
                                /*后方列车为该列车*/
                            }
                        }               
                    }
                    break;

                case DEFAULT_ZERO:
                    /*计算失败,添加后方危险区域标记*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 5U;
                    break;

                default:
                    if ((AC_FREE_STATUS == GetAcStatusNow(rearAcId))
                        || (FLAG_SET == GetAcArbFlag(rearAcId))
                        || (DEFAULT_ZERO != GetAcArbRedundance(rearAcId))
                        || (DEFAULT_ZERO != GetAcUtRedundance(rearAcId)))
                    {
                        /*不添加前方区域可疑标记*/
                    } 
                    else
                    {
                        /*添加后方危险区域标记*/
                        SetTrainSuspectTail(trainId,FLAG_SET);
                        LogPrintf(1U,"16.001 TrainId=%d,RearAcId=%d,UT=%d,State=%d\n",trainId,rearAcId,GetAcUtFlag(rearAcId),GetAcStatusNow(rearAcId));
                        errorCode = 6U;
                    }

                    break;
                }
            }
            else
            {
                if (2U == rtnRearAc)
                {
                    /*线路尽头查询失败,不处理*/
                } 
                else
                {
                    /*添加后方危险区域标记*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 7U;
                }

            }
        }
#endif
    } 
    else
    {
        /*添加后方危险区域标记*/
        SetTrainSuspectTail(trainId,FLAG_SET);

        errorCode = 8U;
    }

    if (0U == errorCode)
    {
        /*Do nothing currently !*/
    } 
    else
    {
        LogPrintf(1U,"1.10 TrainId=%d,UnSafeTailAcId=%d,rearAcId=%d,SuspectTail=%d,errorCode=%d\n",trainId,trainUnSafeTailAcId,rearAcId,GetTrainSuspectTail(trainId),errorCode);
    }
}

/*************************************************
  函数名:      JudgeTrainHeadSuspect
  功能描述:    判断是否可以去除列车前方危险源信息
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      1u：处理成功（前方无危险源）
               0u：处理失败（前方存在危险源）
*************************************************/
UINT8_S JudgeTrainHeadSuspect(const UINT16_S trainId)
{
    TrainSafeLocStruct trainUnsafeLocStru;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainUnSafeHeadAcId = DEFAULT_ZERO;
    UINT16_S frontAcId = DEFAULT_ZERO;
    UINT16_S acLink = DEFAULT_ZERO;
    UINT32_S acOffset = DEFAULT_ZERO;
    UINT32_S distanceOfPoint = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S getFlag = RETURN_ERROR;
    UINT8_S checkFlag = RETURN_ERROR;	      /* 找到前方计轴区段标志*/
    UINT32_S lineMinTrainLength = DEFAULT_ZERO;
    UINT8_S acStatusNow = DEFAULT_ZERO;
    UINT16_S trainError = DEFAULT_ZERO;       /* 测距误差 */
    UINT16_S backLink = DEFAULT_ZERO;       /* 前端筛选的Link */
    UINT32_S backOffset = DEFAULT_ZERO;     /* 前端筛选的偏移量 */
    UINT16_S errorSwitchId = DEFAULT_ZERO;
    UINT8_S  backPointFlag = DEFAULT_ZERO;    
    UINT8_S checkAcEndFlag = RETURN_ERROR;    /* 获取计轴区段终点标志 */


    trainDir = GetTrainUnsafeDirection(trainId);
    trainUnSafeHeadAcId = GetTrainUnsafeTrainHeadAC(trainId);   
    getFlag = GetTrainUnSafeLoc(trainId,&trainUnsafeLocStru);
    checkFlag = CheckFrontACStatus(trainUnSafeHeadAcId,trainDir,&frontAcId);
    trainError = GetTrainError(trainId);

    if ((RETURN_SUCCESS == getFlag) && (RETURN_SUCCESS == checkFlag))
    {
        /* 沿运行方向反向查找某个点 */
        backPointFlag = CheckNextPointOnDistance(trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset,
                                                  TrainDirChangeForCheck(trainId),(UINT32_S)trainError,&backLink,&backOffset,&errorSwitchId);

        /* 查询沿运行方向终端位置 */
        checkAcEndFlag = CheckAcTerminalPosition(trainUnSafeHeadAcId,((UINT16_S)trainDir),&acLink,&acOffset);
        
        /*LogPrintf(1U,"Suspect Head ;%d,%d,%d,%d,%d,%d,%d,%d,%d\n",trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset,backLink,backOffset,
                                       errorSwitchOrAcId,backPointFlag,checkAcEndFlag,acLink,acOffset);*/
        if ((3U == backPointFlag) && (RETURN_SUCCESS == checkAcEndFlag))
        {
            distanceOfPoint = CheckDistanceBetweenTwoPoints(backLink,backOffset,acLink,acOffset,trainDir);
            lineMinTrainLength = (UINT32_S)GetLineMinTrainLength();
            acStatusNow = GetAcStatusNow(frontAcId);

            /*LogPrintf(1U,"Suspect Head1 %d,%d,%d\n",distanceOfPoint,lineMinTrainLength,acStatusNow);*/
            if ((distanceOfPoint < lineMinTrainLength)
                && (AC_FREE_STATUS == acStatusNow))
            {
                /*距离小于线路最小列车长度且前方计轴区段空闲*/
                rtnValue = RETURN_SUCCESS;
            } 
            else
            {
                rtnValue = RETURN_ERROR;
            }
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      JudgeTrainTailSuspect
  功能描述:    判断是否可以去除列车后方危险源信息
  输入:        const UINT16_S trainId 列车ID
  输出:        无
  返回值:      1u：处理成功（后方无危险源）
               0u：处理失败（后方存在危险源）
*************************************************/
UINT8_S JudgeTrainTailSuspect(const UINT16_S trainId)
{
    TrainSafeLocStruct trainSafeLocStru;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainSafeTailAcId = DEFAULT_ZERO;
    UINT16_S rearAcId = DEFAULT_ZERO;
    UINT16_S acLink = DEFAULT_ZERO;
    UINT32_S acOffset = DEFAULT_ZERO;
    UINT32_S distanceOfPoint = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S getFlag = RETURN_ERROR;
    UINT8_S checkFlag = RETURN_ERROR;	
    UINT32_S lineMinTrainLength = DEFAULT_ZERO;
    UINT8_S acStatusNow = DEFAULT_ZERO;

    trainDir = GetTrainUnsafeDirection(trainId);
    trainSafeTailAcId = GetTrainTrainTailAC(trainId);
    getFlag = GetTrainSafeLoc(trainId,&trainSafeLocStru);
    checkFlag = CheckRearACStatus(trainSafeTailAcId,trainDir,&rearAcId);

    if ((RETURN_SUCCESS == getFlag) && (RETURN_SUCCESS == checkFlag))
    {
        /*查询沿运行方向起点位置*/
        if (RETURN_SUCCESS == CheckAcTopPosition(trainSafeTailAcId,((UINT16_S)trainDir),&acLink,&acOffset))
        {
            distanceOfPoint = CheckDistanceBetweenTwoPoints(acLink,acOffset,trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,trainDir);
            lineMinTrainLength = (UINT32_S)GetLineMinTrainLength();
            acStatusNow = GetAcStatusNow(rearAcId);

            if ((distanceOfPoint < lineMinTrainLength)
                && (AC_FREE_STATUS == acStatusNow))
            {
                /*距离小于线路最小列车长度且前方计轴区段空闲*/
                rtnValue = RETURN_SUCCESS;
            } 
            else
            {
                rtnValue = RETURN_ERROR;
            }
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      CalulateTrainLocToAcInfo
  功能描述:    计算列车占压的安全和非安全计轴区段
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void CalulateTrainLocToAcInfo(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    TrainSafeLocStruct trainSafeLocStru;
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT16_S checkAcId = DEFAULT_ZERO;
    UINT8_S needFlag = RETURN_ERROR;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        /*获取列车ID*/
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);
        needFlag = JudgeTrainNeedCalculate(trainId);

        if ((DEFAULT_ZERO != trainId)
            && (TRAIN_MODE_OUT != trainType)
            && (DEFAULT_ZERO != trainType)
            && ((RETURN_SUCCESS == needFlag)))
        {
            /*获取列车安全位置信息*/
            if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
            {
                /*计算安全位置所在计轴区段*/
                checkAcId = CheckPositionBelongAc(trainSafeLocStru.TrainHeadLink);
                SetTrainTrainHeadAC(trainId,checkAcId);

                checkAcId = CheckPositionBelongAc(trainSafeLocStru.TrainTailLink);
                SetTrainTrainTailAC(trainId,checkAcId);
            } 
            else
            {
                /*获取失败,导向安全*/
                SetTrainTrainHeadAC(trainId,DEFAULT_ZERO);
                SetTrainTrainTailAC(trainId,DEFAULT_ZERO);
            }

            /*获取列车非安全位置信息*/
            if (RETURN_SUCCESS == GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru))
            {
                /*计算非安全位置所在计轴区段*/
                checkAcId = CheckPositionBelongAc(trainUnSafeLocStru.TrainHeadLink);
                SetTrainUnsafeTrainHeadAC(trainId,checkAcId);

                checkAcId = CheckPositionBelongAc(trainUnSafeLocStru.TrainTailLink);
                SetTrainUnsafeTrainTailAC(trainId,checkAcId);
            } 
            else
            {
                /*获取失败,导向安全*/
                SetTrainUnsafeTrainHeadAC(trainId,DEFAULT_ZERO);
                SetTrainUnsafeTrainTailAC(trainId,DEFAULT_ZERO);
            }
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*************************************************
  函数名:      CalculateCommTrainMatchingRoute
  功能描述:    计算通信列车是否能匹配上可用的进路信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void CalculateCommTrainMatchingRoute(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT8_S mathRouteCycle = DEFAULT_ZERO;
    UINT16_S mathRouteIdBuff[SIZE_MAX_ROUTENUM] = {DEFAULT_ZERO};
    UINT8_S mathRouteNum = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        /*获取列车ID*/
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);

        /*判断该列车类型是否满足进路匹配条件*/
        if((TRAIN_MODE_IN == trainType) || (TRAIN_MODE_RM == trainType)
            ||(TRAIN_MODE_RM0 == trainType) || (TRAIN_MODE_CBTC == trainType))
        {
            /*清空列车上周期匹配的进路信息*/
            MemorySet(mathRouteIdBuff,sizeof(UINT16_S)*SIZE_MAX_ROUTENUM,DEFAULT_ZERO,sizeof(UINT16_S)*SIZE_MAX_ROUTENUM);
            SetTrainMatchedRouteIdBuf(trainId,mathRouteIdBuff,DEFAULT_ZERO);
            mathRouteNum = 0U;

            /*循环列车管理数组中匹配进路数组*/
            for(mathRouteCycle = DEFAULT_ZERO;mathRouteCycle < SIZE_MAX_ROUTENUM;mathRouteCycle++)
            {
                if (MatchTrainSingleRoute(trainId,mathRouteCycle,mathRouteIdBuff))
                {
                    /*匹配成功,继续匹配下一条进路*/
                    mathRouteNum++;
                } 
                else
                {
                    /*匹配失败,跳出进路匹配*/
                    break;
                }
            }

            /*填写匹配进路信息*/
            SetTrainMatchedRouteIdBuf(trainId,mathRouteIdBuff,mathRouteNum);

           /* LogPrintf(1U,"14.01 TrainId=%d,MathNum=%d,MathRoute=%d,%d,%d\n",trainId,mathRouteNum,mathRouteIdBuff[0],mathRouteIdBuff[1],mathRouteIdBuff[2]); */
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*************************************************
  函数名:      MatchTrainSingleRoute
  功能描述:    计算通信列车是否能匹配上可用的进路信息
  输入:        const UINT16_S trainId,待匹配列车ID
  输出:        UINT8_S matchRouteIndex,匹配进路的下标
               UINT16_S mathRouteIdBuff[],匹配进路的ID数组
  返回值:      0u:匹配失败
               1u:匹配成功
*************************************************/
UINT8_S MatchTrainSingleRoute(const UINT16_S trainId,UINT8_S matchRouteIndex,UINT16_S matchRouteIdBuff[])
{
    UINT16_S mathAcId = DEFAULT_ZERO;
    UINT16_S trainSafeTailAc = DEFAULT_ZERO;
    UINT16_S trainUnSafeTrailAc = DEFAULT_ZERO;
    UINT16_S lastAcIdInRoute = DEFAULT_ZERO;
    UINT16_S tailMathRouteId = DEFAULT_ZERO;
    UINT16_S headMathRouteId = DEFAULT_ZERO;
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT16_S trainUnSafeHeadAc = DEFAULT_ZERO;
    UINT16_S canMathRouteId = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S matchFlag = RETURN_ERROR;
    UINT16_S tmpLastRouteId = DEFAULT_ZERO;
     
    if (NULL != matchRouteIdBuff)
    {
        /*获取列车方向*/
        trainDir = GetTrainUnsafeDirection(trainId);

        /*判断*/
        if (DEFAULT_ZERO == matchRouteIndex)
        {
            /*查看列车车尾所在计轴区段*/
            trainSafeTailAc = GetTrainTrainTailAC(trainId);
            trainUnSafeTrailAc = GetTrainUnsafeTrainTailAC(trainId);

            if (DEFAULT_ZERO != trainSafeTailAc)
            {
                /*使用安全车尾位置作为查询条件*/
                mathAcId = trainSafeTailAc;
            } 
            else
            {
                if (DEFAULT_ZERO != trainUnSafeTrailAc)
                {
                    /*使用非安全车尾位置作为查询条件*/
                    mathAcId = trainUnSafeTrailAc;
                } 
                else
                {
                    mathAcId = DEFAULT_ZERO;
                }
            }

            /*判断计轴是否属于可匹配进路*/
            tempRtn = CalulateAcIdBelongUseableRoute(mathAcId,trainDir,&tailMathRouteId);

            switch (tempRtn)
            {
            case 0U:
                /*查询非安全车头是否属于可匹配的进路*/
                trainUnSafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);

                switch (CalulateAcIdBelongUseableRoute(trainUnSafeHeadAc,trainDir,&headMathRouteId))
                {
                case 0U:
                    /*接近匹配。。。。。。。。。。。。。。。。可以干掉，先留着*/
                    /* CalculateBeCloseRouteMatch(trainId,&canMathRouteId); */

                    /*查询车头前方计轴是否可匹配*/
                    canMathRouteId = DEFAULT_ZERO;

                    if (RETURN_SUCCESS == MatchTrainHeadFrontAcInRoute(trainUnSafeHeadAc,trainId,&canMathRouteId))
                    {
                        /* 匹配进路成功 */
                    }
                    else
                    {
                        canMathRouteId = DEFAULT_ZERO;
                    }
                    break;
                case 1U:
                    /*完成匹配，匹配失败*/
                    canMathRouteId = DEFAULT_ZERO;
                    break;
                case 2U:
                    /*可完成匹配*/
                    canMathRouteId = headMathRouteId;
                    break;
                default:
                    /*完成匹配，匹配失败*/
                    canMathRouteId = DEFAULT_ZERO;
                    break;
                }
                break;

            case 1U:
                /*完成匹配，匹配失败*/
                canMathRouteId = DEFAULT_ZERO;
                break;

            case 2U:
                /*车尾可匹配，检查非安全车头是否可以被匹配*/
                trainUnSafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);

                if (2U == CalulateAcIdBelongUseableRoute(trainUnSafeHeadAc,trainDir,&headMathRouteId))
                {
                    /*可完成匹配*/
                    /*同时匹配了车尾和车头的进路，默认用车尾匹配上的进路*/
                    canMathRouteId = tailMathRouteId;
                } 
                else
                {
                    canMathRouteId = DEFAULT_ZERO;
                }
                break;
            default:
                canMathRouteId = DEFAULT_ZERO;
                break;
            }
        } 
        else
        {
            /* 匹配进路中的上一条进路ID */
            tmpLastRouteId = matchRouteIdBuff[matchRouteIndex - 1U];

            /* 查询上一条进路类型 */
            if (LINE_REVERSE_ROUTE == GetRouteType(tmpLastRouteId))
            {
                /*不再往前匹配下一条进路*/
            } 
            else
            {
                /* 获取上一条进路的最后一个计轴区段 */           
                if (RETURN_SUCCESS == GetRoutOfAcIdFromIndex(tmpLastRouteId,(GetRouteOfAcNum(tmpLastRouteId) - 1U),&lastAcIdInRoute))
                {
                    matchFlag = MatchTrainHeadFrontAcInRoute(lastAcIdInRoute,trainId,&tailMathRouteId);

                    if ((DEFAULT_ZERO != lastAcIdInRoute) && (RETURN_SUCCESS == matchFlag))
                    {
                        /*可以被匹配*/
                        canMathRouteId = tailMathRouteId;
                    } 
                    else
                    {
                        canMathRouteId = DEFAULT_ZERO;
                    }
                }            
            }
        }

        if ((DEFAULT_ZERO != canMathRouteId))
        {
            if (RETURN_SUCCESS == CalulateRouteMathToTrain(canMathRouteId,trainId))
            {
                matchRouteIdBuff[matchRouteIndex] = canMathRouteId;
                matchRouteIndex = matchRouteIndex + 1U;
                rtnValue = RETURN_SUCCESS;
            } 
            else
            {
                rtnValue = RETURN_ERROR;
            }
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
   

    return rtnValue;
}

/*************************************************
  函数名:      MatchTrainHeadFrontAcInRoute
  功能描述:    计算通信列车是否能匹配上可用的进路信息
  输入:        const UINT16_S trainHeadAcId,列车车头计轴区段ID
               const UINT16_S trainId,待匹配列车Id
  输出:        UINT16_S *pMatchRouteId,匹配进路信息
  返回值:      0u:匹配失败
               1u:匹配成功
*************************************************/
UINT8_S MatchTrainHeadFrontAcInRoute(const UINT16_S trainHeadAcId,const UINT16_S trainId,UINT16_S *pMatchRouteId)
{
    UINT16_S frontAcId = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S signalIdOfRoute = DEFAULT_ZERO;
    UINT16_S trainMatchRouteId = DEFAULT_ZERO;

    if (NULL != pMatchRouteId)
    {
        /*获取列车方向*/
        trainDir = GetTrainUnsafeDirection(trainId);

        /*查询列车车头所在计轴前方计轴区段*/
        if (RETURN_SUCCESS == CheckFrontACStatus(trainHeadAcId,trainDir,&frontAcId))
        {
            /*判断前方计轴区段是否属于某个可匹配的进路*/
            if (2U == CalulateAcIdBelongUseableRoute(frontAcId,trainDir,&trainMatchRouteId))
            {
                /*获取进路的始端信号机*/
                signalIdOfRoute = GetRouteOfSingalId(trainMatchRouteId);

                if (RETURN_ERROR != signalIdOfRoute)
                {
                    if (trainDir == GetSignalProtectDir(signalIdOfRoute))
                    {
                        switch (GetSignalStatus(signalIdOfRoute))
                        {
                        case SIGNAL_STATE_PASS:
                            /*信号机开放,直接匹配*/
                            (*pMatchRouteId) = trainMatchRouteId;
                            rtnValue = RETURN_SUCCESS;
                            break;
                        case SIGNAL_STATE_STOP:
                            /*信号机未开放,判断列车是否已越过该红灯信号机*/
                            if (1U == CalculateSignalLocBetweenTrainLoc(trainId,signalIdOfRoute))
                            {
                                (*pMatchRouteId) = trainMatchRouteId;
                                rtnValue = RETURN_SUCCESS;
                            } 
                            else
                            {
                                (*pMatchRouteId) = DEFAULT_ZERO;
                                rtnValue = RETURN_ERROR;
                            }
                            break;
                        default:
                            (*pMatchRouteId) = DEFAULT_ZERO;
                            rtnValue = RETURN_ERROR;
                            break;
                        }

                    } 
                    else
                    {
                        rtnValue = RETURN_ERROR;
                    }			
                } 
                else
                {
                    rtnValue = RETURN_ERROR;
                }
            } 
            else
            {
                rtnValue = RETURN_ERROR;
            }
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }
   
    return rtnValue;
}

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
UINT8_S CalculateSignalLocBetweenTrainLoc(const UINT16_S trainId,const UINT16_S signalId)
{
    UINT16_S signalLink = DEFAULT_ZERO;
    UINT32_S signalOffset = DEFAULT_ZERO;
    TrainSafeLocStruct trainSafeLocStru;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S checkFlag = RETURN_ERROR;
    UINT8_S getFlag = RETURN_ERROR;
    UINT8_S relationValueHead = DEFAULT_ZERO;
    UINT8_S relationValueTail = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;

    /*获取信号机位置和列车安全位置*/
    checkFlag = CheckSignalPostion(signalId,&signalLink,&signalOffset);
    getFlag = GetTrainSafeLoc(trainId, &trainSafeLocStru);

    if ((RETURN_SUCCESS == checkFlag) && (RETURN_SUCCESS == getFlag))
    {
        trainDir = GetTrainUnsafeDirection(trainId);

        relationValueHead = CheckLocRelationBetweenTwoPoints(signalLink,signalOffset,
            trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset,trainDir);

        relationValueTail = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,
            signalLink,signalOffset,trainDir);

        if ((RETURN_ERROR != relationValueHead)
            && (RETURN_ERROR != relationValueTail))
        {
            if (((2U == relationValueHead)|| (3U == relationValueHead))
                && ((2U == relationValueTail)||(3U == relationValueTail)))
            {
                /*信号机位于列车位置之间*/
                rtnValue = 1U;
            } 
            else
            {
                rtnValue = 2U;
            }
        } 
        else
        {
            rtnValue = 0U;
        }
    } 
    else
    {
        rtnValue = 0U;
    }

    return rtnValue;
}

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
UINT8_S CalulateAcIdBelongUseableRoute(const UINT16_S acId,const UINT8_S dir,UINT16_S *pMathRouteId)
{
#if 0
    UINT8_S acNumInRoute = DEFAULT_ZERO;
    UINT16_S acIdInRouteBuff[ROUTE_OF_AC_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S routeCycle = DEFAULT_ZERO;
    UINT8_S acCycle = DEFAULT_ZERO;
    UINT16_S routeId = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S lockAcCycle = DEFAULT_ZERO;
    UINT8_S lockAcStartIndex = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S routeStatus = DEFAULT_ZERO;
    UINT16_S signalOfRoute = DEFAULT_ZERO;
    UINT8_S routeAreaType = DEFAULT_ZERO;
    UINT8_S signalProtectDir = DEFAULT_ZERO;

    MemorySet(&acIdInRouteBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)),0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)));

    if (NULL != pMathRouteId)
    {
        /*这段代码是想知道acId属不属于进路和在这个计轴区段之后的计轴区段是否满足条件*/
        for (routeCycle = DEFAULT_ZERO;routeCycle < GetRouteSum();routeCycle++)
        {
            /*获取进路Id*/
            routeId = GetRouteId((UINT16_S)routeCycle);
            signalOfRoute = GetRouteOfSingalId(routeId);
            routeAreaType = GetRouteAreaType(routeId);
            routeStatus = GetRouteStatus(routeId);
            signalProtectDir = GetSignalProtectDir(signalOfRoute);

            if ((ROUTE_STATE_SET == routeStatus) && (dir == signalProtectDir))
            {
                /*获取进路包含的配置计轴信息*/
                acNumInRoute = GetRouteOfAcNum(routeId);

                /*设置检索下标*/
                lockAcStartIndex = DEFAULT_UINT8_VALUE;
                breakFlag = DEFAULT_ZERO;

                if (RETURN_SUCCESS == GetRoutOfAcIdBuff(routeId,ROUTE_OF_AC_SUM_MAX,acIdInRouteBuff))
                {             
                    for (acCycle = DEFAULT_ZERO;acCycle < acNumInRoute;acCycle++)
                    {
                        if (acIdInRouteBuff[acCycle] == acId)
                        {
                            /*说明已办理的进路内计轴和当前计轴匹配*/
                            lockAcStartIndex = acCycle;
                            break;
                        }
                        else
                        {
                            /*不处理*/
                        }
                    }

                }    

                /*判断计轴锁闭状态是否满足匹配条件*/
                if (DEFAULT_UINT8_VALUE != lockAcStartIndex)
                {
                    for (lockAcCycle = lockAcStartIndex+1U;lockAcCycle < acNumInRoute;lockAcCycle++)
                    {
                        if (AC_UNLOCK_STATUS == GetAcBelock(acIdInRouteBuff[lockAcCycle]))
                        {
                            /*含有未锁闭的计轴区段,跳出*/
                            breakFlag = FLAG_SET;
                            break;
                        } 
                        else
                        {
                            /*不处理*/
                        }

                        /*检查计轴区段对应的道岔是否锁闭且在规定位置*/
                        if (RETURN_SUCCESS == JudgeSwitchLockAndPostionInAc(acIdInRouteBuff[lockAcCycle]))
                        {
                            /*不处理*/
                        } 
                        else
                        {
                            /*计轴包含道岔不满足匹配条件,跳出*/
                            breakFlag = FLAG_SET;
                            break;
                        }

                        if (CI_TRAIN_DEPOT_TYPE == routeAreaType)
                        {
                            /*车辆段进路的区段需要满足未占用条件*/
                            if (AC_OCC_STATUS == GetAcStatusNow(acIdInRouteBuff[lockAcCycle]))
                            {
                                /*车辆段或者停车场进路内不允许包含其他列车*/
                                breakFlag = FLAG_SET;
                                break;
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
                    breakFlag = FLAG_UNSET;
                }

                if (FLAG_SET == breakFlag)
                {
                    /*属于进路,但不满足匹配条件*/
                    rtnValue = 1U;                  
                    break; 
                    
                } 
                else
                {
                    if (FLAG_UNSET == breakFlag)
                    {
                        /*不属于进路*/
                        rtnValue = 0U;
                    } 
                    else
                    {
                        /*满足匹配条件*/
                        (*pMathRouteId) = routeId;
                        rtnValue = 2U;
                        break;
                    }
                }

            } 
            else
            {
                /* 不属于可用进路 */
                rtnValue = 0U;
            }	
        }
    }
    

    return rtnValue;
#endif
    UINT8_S acNumInRoute = DEFAULT_ZERO;
    UINT16_S acIdInRouteBuff[ROUTE_OF_AC_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S routeCycle = DEFAULT_ZERO;
    UINT8_S acCycle = DEFAULT_ZERO;
    UINT16_S routeId = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S lockAcCycle = DEFAULT_ZERO;
    UINT8_S lockAcStartIndex = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S routeStatus = DEFAULT_ZERO;
    UINT16_S signalOfRoute = DEFAULT_ZERO;
    UINT8_S routeAreaType = DEFAULT_ZERO;
    UINT8_S signalProtectDir = DEFAULT_ZERO;
    UINT8_S findFlag = DEFAULT_ZERO;

    MemorySet(&acIdInRouteBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)),0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)));

    if (NULL != pMathRouteId)
    {
        /* 判断acId属不属于进路和在这个计轴区段之后的计轴区段是否满足条件 */
        for (routeCycle = DEFAULT_ZERO;routeCycle < GetRouteSum();routeCycle++)
        {
            /* 获取进路Id */
            routeId = GetRouteId((UINT16_S)routeCycle);
            signalOfRoute = GetRouteOfSingalId(routeId);
            routeAreaType = GetRouteAreaType(routeId);
            routeStatus = GetRouteStatus(routeId);
            signalProtectDir = GetSignalProtectDir(signalOfRoute);

            if ((ROUTE_STATE_SET == routeStatus) && (dir == signalProtectDir))
            {
                /* 获取进路包含的配置计轴信息 */
                acNumInRoute = GetRouteOfAcNum(routeId);

                /* 设置检索下标 */
                lockAcStartIndex = DEFAULT_UINT8_VALUE;
                findFlag = DEFAULT_ZERO;

                if (RETURN_SUCCESS == GetRoutOfAcIdBuff(routeId,ROUTE_OF_AC_SUM_MAX,acIdInRouteBuff))
                {             
                    for (acCycle = DEFAULT_ZERO;acCycle < acNumInRoute;acCycle++)
                    {
                        if (acIdInRouteBuff[acCycle] == acId)
                        {
                            /* 说明已建立的进路内计轴和当前计轴匹配 */
                            lockAcStartIndex = acCycle;
                            breakFlag = DEFAULT_ZERO;

                            /* 已建立的进路包含查询的计轴区段，判断进路内这个计轴区段的前方所有计轴区段情况 */
                            for (lockAcCycle = lockAcStartIndex+1U;lockAcCycle < acNumInRoute;lockAcCycle++)
                            {
                                if (AC_UNLOCK_STATUS == GetAcBelock(acIdInRouteBuff[lockAcCycle]))
                                {
                                    /* 含有未锁闭的计轴区段,跳出遍历进路内其他计轴区段的循环 */
                                    breakFlag = FLAG_SET;
                                    break;
                                } 
                                else
                                {
                                    /* 不处理 */
                                }

                                /* 检查计轴区段对应的道岔是否锁闭且在规定位置 */
                                if (RETURN_SUCCESS == JudgeSwitchLockAndPostionInAc(acIdInRouteBuff[lockAcCycle]))
                                {
                                    /* 不处理 */
                                } 
                                else
                                {
                                    /* 计轴包含道岔不满足匹配条件,跳出遍历进路内其他计轴区段的循环 */
                                    breakFlag = FLAG_SET;
                                    break;
                                }

                                if (CI_TRAIN_DEPOT_TYPE == routeAreaType)
                                {
                                    /* 车辆段进路的区段需要满足未占用条件 */
                                    if (AC_OCC_STATUS == GetAcStatusNow(acIdInRouteBuff[lockAcCycle]))
                                    {
                                        /* 车辆段或者停车场进路内不允许包含其他列车,跳出遍历进路内其他计轴区段的循环 */
                                        breakFlag = FLAG_SET;
                                        break;
                                    } 
                                    else
                                    {
                                        /* 不处理 */
                                    }
                                } 
                                else
                                {
                                    /* 不处理 */
                                }
                            }

                            if (FLAG_SET == breakFlag)
                            {
                                /* 在已建立的进路内的计轴区段包含的查询的计轴区段,但其余下的计轴区段不满足条件 */
                                rtnValue = 1u;
                                break;
                            }
                            else
                            {
                                /* 满足匹配条件 */
                                (*pMathRouteId) = routeId;
                                rtnValue = 2u;
                                findFlag = FLAG_SET;
                                break;
                            }
                        }
                        else
                        {
                            /* 继续遍历已建立进路内余下的计轴区段 */
                        }
                    }   

                    if (FLAG_SET == findFlag)
                    {
                        /* 已经找到，跳出遍历进路的循环 */
                        break;
                    }
                }
            } 
            else
            {
                /* 不属于可用进路,继续遍历 */
            }	
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:      CalulateRouteMathToTrain
  功能描述:    计算指定列车ID是否能匹配指定进路
  输入:        const UINT16_S routeId,进路ID
               const UINT16_S trainId,列车ID
  输出:        无
  返回值:      0u:匹配失败
               1u:匹配成功
*************************************************/
UINT8_S CalulateRouteMathToTrain(const UINT16_S routeId,const UINT16_S trainId)
{
    UINT16_S routeSignalId = DEFAULT_ZERO;
    UINT8_S signalProtectDir = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*进路检查*/
    routeSignalId = GetRouteOfSingalId(routeId);

    /*获取信号机的防护方向*/
    signalProtectDir = GetSignalProtectDir(routeSignalId);

    /*是否需要判断锁闭方向和列车期望运行方向一致？？？？？*/
    if (signalProtectDir == GetTrainUnsafeDirection(trainId))
    {
        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      CalculateBeCloseRouteMatch
  功能描述:    计算指定列车ID是否能按进路接近匹配原则匹配指定进路
  输入:        const UINT16_S routeId,进路ID
  输出:        UINT16_S *pMathRouteId,可以匹配的进路ID
  返回值:      0u:匹配失败
               1u:匹配成功
*************************************************/
UINT8_S CalculateBeCloseRouteMatch(const UINT16_S trainId,UINT16_S *pMatchRouteId)
{
    TrainSafeLocStruct trainUnsafeLocStru;
    UINT16_S frontSignalId = DEFAULT_ZERO;
    UINT16_S cycleRoute = DEFAULT_ZERO;
    UINT16_S routeId = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S checkFlag = DEFAULT_ZERO;
    UINT8_S routeStatus = DEFAULT_ZERO;
    UINT16_S routeOfSingalId = DEFAULT_ZERO;
    UINT8_S integralityFlag = RETURN_ERROR;

    if (NULL != pMatchRouteId)
    {
        (*pMatchRouteId) = DEFAULT_ZERO;

        if (RETURN_SUCCESS == GetTrainUnSafeLoc(trainId,&trainUnsafeLocStru))
        {
            /*查询离列车车头前方最近的同向信号机*/
            trainDir = GetTrainUnsafeDirection(trainId);
            checkFlag = CheckPointNearestSignalBaseDir(trainDir,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset,&frontSignalId);

            if (RETURN_SUCCESS == checkFlag)
            {
                if (SIGNAL_STATE_PASS == GetSignalStatus(frontSignalId))
                {
                    for (cycleRoute = DEFAULT_ZERO ;cycleRoute < GetRouteSum();cycleRoute++)
                    {
                        /*获取进路Id*/
                        routeId = GetRouteId(cycleRoute);
                        routeStatus = GetRouteStatus(routeId);
                        routeOfSingalId = GetRouteOfSingalId(routeId);
                        integralityFlag = CalculateRouteAcLockStatusIntegrality(routeId);

                        if ((ROUTE_STATE_SET == routeStatus)
                            && (frontSignalId == routeOfSingalId)
                            && (RETURN_SUCCESS == integralityFlag))
                        {
                            /*满足匹配条件*/
                            (*pMatchRouteId) = routeId;
                            rtnValue = RETURN_SUCCESS;
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
                    rtnValue = RETURN_ERROR;
                }
            } 
            else
            {
                rtnValue = RETURN_ERROR;
            }
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*************************************************
  函数名:      CalculateRouteAcLockStatusIntegrality
  功能描述:    计算指定进路内计轴区段的锁闭完整性
  输入:        const UINT16_S routeId,进路ID
  输出:        无
  返回值:      0u:未完整锁闭
               1u:完整锁闭
*************************************************/
UINT8_S CalculateRouteAcLockStatusIntegrality(const UINT16_S routeId)
{
    UINT8_S acNumInRoute = DEFAULT_ZERO;
    UINT16_S acIdInRouteBuff[ROUTE_OF_AC_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S acCycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S acIdRtn = RETURN_ERROR;

    MemorySet(&acIdInRouteBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)));

	/*获取进路包含的配置计轴信息*/
	acNumInRoute = GetRouteOfAcNum(routeId);
	acIdRtn = GetRoutOfAcIdBuff(routeId,ROUTE_OF_AC_SUM_MAX,acIdInRouteBuff);
	
    /*判断计轴锁闭状态是否满足匹配条件*/
    if (RETURN_SUCCESS == acIdRtn)
    {
        for (acCycle = DEFAULT_ZERO;acCycle < acNumInRoute;acCycle++)
        {
            if (AC_UNLOCK_STATUS == GetAcBelock(acIdInRouteBuff[acCycle]))
            {
                /*含有未锁闭的计轴区段,跳出*/
                break;
            } 
            else
            {
                /*不处理*/
            }
        }

        if (acNumInRoute == acCycle)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:      ManageTrainTypeTransform
  功能描述:    管理列车类型转换
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageTrainTypeTransform(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT8_S checkRtn = DEFAULT_ZERO;
    UINT8_S trainMode = DEFAULT_ZERO;
    UINT8_S trainInType = DEFAULT_ZERO;
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S changePointLink = DEFAULT_ZERO;
    UINT32_S changePointOffset = DEFAULT_ZERO;
    UINT16_S changeLineId = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT16_S trainControlZc = DEFAULT_ZERO;
    UINT16_S commTargetCycle = DEFAULT_ZERO;
    UINT8_S getLocFlag = RETURN_ERROR;
    UINT8_S trainStatus = DEFAULT_ZERO;
    UINT8_S trainLevel = DEFAULT_ZERO;
	UINT8_S headQuitCbtcArea = RETURN_ERROR;
	UINT8_S tailQuitCbtcArea = RETURN_ERROR;
	UINT8_S trainDir = DEFAULT_ZERO;

    localZcId =GetLocalZcId();

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        /*获取列车ID*/
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);
        trainInType = GetTrainInType(trainId);
        trainMode = GetTrainMode(trainId);
        trainControlZc = GetTrainControlZc(trainId);
        commTargetCycle = GetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId);
        trainLevel = GetTrainLevel(trainId);

        if ((DEFAULT_ZERO == commTargetCycle)
            && (trainControlZc == localZcId))
        {
            /*说明本周期列车通信正常*/
            switch (trainType)
            {
            case DEFAULT_ZERO:
            case TRAIN_MODE_IN:	
                getLocFlag = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);			
                if ((TRAIN_IN_APPLY_MA == trainInType)
                    && (RETURN_SUCCESS == getLocFlag))
                {
                    /*查询列车车头非安全位置是否越过转换轨*/
                    checkRtn = CheckPointBelongToZHG(trainUnSafeLocStru.TrainHeadLink);

                    switch (checkRtn)
                    {
                    case 0U:
                        /*查询失败,清空列车类型*/
                        SetTrainType(trainId,DEFAULT_ZERO);
                        break;
                    case 2U:
                        /*查询成功,不位于转换轨内*/
                        SetTrainType(trainId,TRAIN_MODE_RM);
                        SetTrainSuspectHead(trainId,FLAG_SET);
                        SetTrainSuspectTail(trainId,FLAG_SET);
                        break;
                    case 1U:
                        /*查询成功,位于转换轨内*/
                        SetTrainType(trainId,TRAIN_MODE_IN);
                        SetTrainSuspectHead(trainId,FLAG_SET);
                        SetTrainSuspectTail(trainId,FLAG_SET);
                        break;
                    default:
                        /*其他未知情况,清空列车类型*/
                        SetTrainType(trainId,DEFAULT_ZERO);
                        break;
                    }

                    /*列车状态该用移动状态判断？？？*/
                    trainStatus = GetTrainStatus(trainId);
                    if ((TRAIN_MODE_IN == trainType)
                        && (DEFAULT_ZERO != trainStatus))
                    {
                        if((TRAIN_IN_LEVEL_CBTC == trainLevel )
                            &&((TRAIN_IN_MODE_AM == trainMode) || (TRAIN_IN_MODE_CM == trainMode)))
                        {
                            /*列车已经升级为CBTC级别,设置相应级别*/
                            SetTrainType(trainId,TRAIN_MODE_CBTC);
                        }
                        else
                        {
                            /*列车尚未升级，维持之前的列车类型*/
                        }
                    } 
                    else
                    {
                        /*不处理*/
                    }
                } 
                else
                {
                    /*维持当前类型*/
                }
                break;
            case TRAIN_MODE_RM:
            case TRAIN_MODE_RM0:
                /*判断列车是否已收到ZC的移动授权信息而升级为CBTC级别下CM或AM模式*/

                if((TRAIN_IN_LEVEL_CBTC == trainLevel)
                    &&((TRAIN_IN_MODE_AM == trainMode) || (TRAIN_IN_MODE_CM == trainMode)))
                {
                    /*列车已经升级为CBTC级别,设置相应级别*/
                    SetTrainType(trainId,TRAIN_MODE_CBTC);
                }
                else
                {
                    /*列车尚未升级，维持之前的列车类型*/
                }
                break;
            case TRAIN_MODE_TO_RM0:
                if (TRAIN_IN_LEVEL_CBTC != trainLevel)
                {
                    /*说明此时列车已按下确认降级按钮,对列车类型进行降级处理*/
                    SetTrainType(trainId, TRAIN_MODE_RM0);
                    SetTrainSuspectHead(trainId,FLAG_SET);
                } 
                else
                {
                    /*不处理*/
                }
                break;
            case TRAIN_MODE_CBTC:
                if (TRAIN_IN_LEVEL_CBTC != trainLevel)
                {
                    /*判断列车是否处于折返状态且输入的列车级别为IL模式为RD*/
                    if ((TRAIN_IN_CHANGED == trainInType)
                        && (TRAIN_IN_LEVEL_IL == trainLevel)
                        && (TRAIN_IN_MODE_RD == trainMode))
                    {
                        /*维持CBTC*/
                        /*PBW,20160526,输出换端完成确认*/							
                        SetTrainOutType(trainId,OUT_TRAIN_CHANGED);
                        LogPrintf(1U,"OUT_TRAIN_CHANGED 2\n");
                    } 
                    else
                    {
                        /*将列车直接设置为RM类型列车且前后端可疑*/
                        SetTrainType(trainId,TRAIN_MODE_RM);
                        SetTrainSuspectHead(trainId,FLAG_SET);
                        SetTrainSuspectTail(trainId,FLAG_SET);
                        LogPrintf(1U,"21.001 Train=%d,Level Down!\n",trainId);
                    }
                } 
                else
                {
                    /*列车输入的是CBTC级别且获取列车安全位置信息成功*/
                    if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
                    {
                        switch (trainInType)
                        {
                        case TRAIN_IN_TOEXITCBTC:

							trainDir = GetTrainUnsafeDirection(trainId);

                            headQuitCbtcArea = CheckPointQuitCbtcIsFindPoint(trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset,trainDir);
                            tailQuitCbtcArea = CheckPointQuitCbtcIsFindPoint(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,trainDir);

                            LogPrintf(1U,"3 ExitCbtc %d,%d,%d",headQuitCbtcArea,tailQuitCbtcArea,trainType);
                            if ((RETURN_SUCCESS == headQuitCbtcArea) && (RETURN_SUCCESS == tailQuitCbtcArea))
                            {
                                /*列车完全位于退出CBTC区域*/
                                SetTrainType(trainId,TRAIN_MODE_OUT);
                            } 
                            else
                            {
                                /* 不处理 */
                            }
                            break;
                        case TRAIN_IN_APPLY_MA:
                            if (localZcId == GetAcBelongZcId(GetTrainUnsafeTrainHeadAC(trainId)))
                            {
                                /*非安全车头所在计轴属于本ZC*/
                            } 
                            else
                            {
                                /*非安全车头所在计轴不属于本ZC*/
                                changeLineId = GetTrainChangeLineId(trainId);
                                if (DEFAULT_ZERO != changeLineId)
                                {
                                    changePointLink = GetChangeLineChangePointLink(changeLineId);
                                    changePointOffset = GetChangeLineChangePointOffset(changeLineId);

                                    checkRtn = CheckLocRelationBetweenTwoPoints(changePointLink,changePointOffset,trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,GetTrainUnsafeDirection(trainId));

                                    if (0x02U == checkRtn)
                                    {
                                        SetTrainType(trainId,TRAIN_MODE_OUT);
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
                            break;
                        case TRAIN_IN_HANDOVERTOCANCEL:
                            changeLineId = GetTrainChangeLineId(trainId);
                            if (DEFAULT_ZERO != changeLineId)
                            {
                                changePointLink = GetChangeLineChangePointLink(changeLineId);
                                changePointOffset = GetChangeLineChangePointOffset(changeLineId);

                                checkRtn = CheckLocRelationBetweenTwoPoints(changePointLink,changePointOffset,trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,GetTrainUnsafeDirection(trainId));

                                if (0x02U == checkRtn)
                                {
                                    SetTrainType(trainId,TRAIN_MODE_OUT);
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
                            break;
                        default:
                            break;
                        }
                    } 
                    else
                    {
                        /* 不处理 */
                    }
                }
                break;
            case TRAIN_MODE_OUT:
                break;
            default:
                break;
            }
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*************************************************
  函数名:      ManageTrainStatusTransform
  功能描述:    管理列车状态转换信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageTrainStatusTransform(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainInType = DEFAULT_ZERO;
    UINT8_S trainStatus = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        trainId = GetTrainIdOfIndex(cycle);
        trainInType = GetTrainInType(trainId);
        trainStatus = GetTrainStatus(trainId);

        if (DEFAULT_ZERO == GetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId))
        {
            /*清空列车输出*/
            switch (trainStatus)
            {
            case DEFAULT_ZERO:
                JudgeTrainDefaultStatusTransform(trainId);
                break;

            case TRAIN_STATE_MOVING:
                JudgeTrainStateMovingTransform(trainId);
                break;

            case TRAIN_STATE_HANDOVER:
                JudgeTrainHandOverTransform(trainId);
                break;

            case TRAIN_STATE_TAKEOVER:
                JudgeTrainTakeOverTransform(trainId);
                break;

            case TRAIN_STATE_REVERSE:
                JudgeTrainReverseTransform(trainId);
                break;

            case TRAIN_STATE_CANCELLATION:
                /* 不进行状态转换 */
                break;

            case TRAIN_STATE_FAILURE:
                /* 不进行状态转换 */
                break;
            default:
                break;
            }
        } 
        else
        {
            /*退出的列车/本周期未输入信息的列车不进行处理*/
        }

        /* LogPrintf(1U,"15.01 TrainId=%d,StatusIn=%d,InType=%d,StatusOut=%d,cycle=%d\n",trainId,trainStatus,trainInType,GetTrainStatus(trainId),GetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId)); */
    }
}

/*************************************************
  函数名:      ManageOutTrainType
  功能描述:    管理列车输出状态信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageOutTrainType(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT16_S changeLineId = DEFAULT_ZERO;
	UINT8_S trainStatus = DEFAULT_ZERO;
    UINT8_S trainInType = DEFAULT_ZERO;
	UINT16_S localZcId = DEFAULT_ZERO;
	UINT16_S acBelongZcId = DEFAULT_ZERO;
	UINT16_S handOverZcId = DEFAULT_ZERO;
	UINT16_S takeOverZcId = DEFAULT_ZERO;
	
	localZcId = GetLocalZcId();
	
    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        trainId = GetTrainIdOfIndex(cycle);
		trainStatus = GetTrainStatus(trainId);
		trainInType = GetTrainInType(trainId);

        switch (trainStatus)
        {
        case TRAIN_STATE_MOVING:
            changeLineId = GetTrainChangeLineId(trainId);

            if (DEFAULT_ZERO == changeLineId)
            {
                if(TRAIN_IN_CHANGED != trainInType)
                {
                    SetTrainOutType(trainId,OUT_TRAIN_MOVING);
                }
                else if(TRAIN_IN_MODE_RD == GetTrainMode(trainId))
                {
                    /*PBW.20160526,列车输入换端完成且为RD模式,设置列车输出类型为换端完成确认*/					
                    SetTrainOutType(trainId,OUT_TRAIN_CHANGED);	
                    LogPrintf(1U,"OUT_TRAIN_CHANGED 1\n");												
                }
                else
                {
                    /*不处理*/
                }
            }
            else
            {
				acBelongZcId = GetAcBelongZcId(GetTrainUnsafeTrainHeadAC(trainId));
				
                if ((TRAIN_IN_APPLY_MA == trainInType)
                    && (localZcId == acBelongZcId))
                {
					handOverZcId = GetChangeLineHandOverZcId(changeLineId);
					takeOverZcId = GetChangeLineTakeOverZcId(changeLineId);
					
                    if (localZcId == takeOverZcId)
                    {
                        /*接管ZC内*/
                        SetTrainOutType(trainId,OUT_TRAIN_MOVING);
                    } 
                    else if (localZcId == handOverZcId)
                    {
                        /*移交ZC内,需要相邻ZC通信正常才输出*/
                        if (DEFAULT_ZERO == GetCommTargetCycle(INNER_DEVTYPE_ZC,takeOverZcId))
                        {
                            SetTrainOutType(trainId,OUT_TRAIN_MOVING);
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
            break;
        case TRAIN_STATE_CANCELLATION:
            switch (trainInType)
            {
            case TRAIN_IN_TOEXITCBTC:
                LogPrintf(1U,"1 ExitCbtc:%d,%d,%d",trainStatus,trainInType,GetTrainOutType(trainId));
                SetTrainOutType(trainId,OUT_TRAIN_TOEXITCBTC);
                break;
            case TRAIN_IN_HANDOVERTOCANCEL:
                SetTrainOutType(trainId,OUT_TRAIN_HANDOVERTOCANCEL);
                break;
            default:			
			   /* 不处理 */
                break;
            }
            break;
        case TRAIN_STATE_REVERSE:
            switch (trainInType)
            {
            case TRAIN_IN_APPLY_MA:
                SetTrainOutType(trainId,OUT_TRAIN_MOVING);
                break;
            case TRAIN_IN_CHANGED:
                SetTrainOutType(trainId,OUT_TRAIN_CHANGED);
				LogPrintf(1U,"OUT_TRAIN_CHANGED 3\n");
                break;
            case TRAIN_IN_REVERSETOCANCEL:
                SetTrainOutType(trainId,OUT_TRAIN_REVERSETOCANCEL);
                break;
            default:
			    /* 不处理 */
                break;
            }
            break;
		case TRAIN_STATE_HANDOVER:
            switch(trainInType)
            {
            case TRAIN_IN_APPLY_MA:
                /*pbw 2016.10.23 添加处理移交状态分支 */
                SetTrainOutType(trainId,OUT_TRAIN_MOVING);
                break;
            default:			
                /* 不处理 */
                break;
            }
            break;
        default:
		    /* 不处理 */
            break;
        }
    }

}

/*************************************************
  函数名:      ManageNZcOutTrainType
  功能描述:    管理列车相邻ZC输出状态信息
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageNZcOutTrainType(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
	UINT8_S trainHandoverInType = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        /*获取列车信息*/
        trainId = GetTrainIdOfIndex(cycle);
		trainHandoverInType=GetTrainHandoverInType(trainId);

        switch (trainHandoverInType)
        {
        case NZC_TRAIN_DEFAULT:
            /*无状态*/
            JudegeNZcDefaultStatusTransform(trainId);
            break;

        case NZC_TRAIN_HANDOVER:
            /*移交申请状态*/
            JudegeNZcHandStatusTransform(trainId);
            break;

        case NZC_TRAIN_CONFIRMATION:
            /*移交申请确认状态*/
            JudgeNZcConfirmationStatusTransform(trainId);
            break;

        case NZC_TRAIN_MANAGENOHAND:
            /*移交未切换*/
#if 0
            /*相邻ZC输出状态为无状态*/
            /* pbw 2017.6.6 尝试非CBTC列车切换的时候，ZC内列车信息不一致场景 */
            if(GetTrainControlZc(trainId) != GetLocalZcId())
            {
                SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);	
            }
            else
            {
                SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOTAKE);	
            }
            /*
            SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);	
            */
#else
            JudgeNZcManagenohandStatusTransform(trainId);
#endif
            break;

        case NZC_TRAIN_MANAGENOTAKE:
            /*接管未切换*/
            /*相邻ZC输出状态为无状态*/
            SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
            break;

        case NZC_TRAIN_HADTOOKOVER:
            /*已接管*/
            /*相邻ZC输出状态为无状态*/
            SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
            break;

        default:
            /*维持当前状态*/

            break;
        }
    }
}

/*************************************************
  函数名:      JudegeNZcDefaultStatusTransform
  功能描述:    处理相邻ZC输入状态为无状态或者跨压切换点的下的相邻ZC输出转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudegeNZcDefaultStatusTransform(const UINT16_S trainId)
{
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S changeLink = DEFAULT_ZERO;
    UINT32_S changeOffset = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainChangeLineId = DEFAULT_ZERO;
    UINT8_S checkTrainHeadRtn = DEFAULT_ZERO;
    UINT8_S checkTrainTailRtn = DEFAULT_ZERO;
    UINT8_S trainState = DEFAULT_ZERO;
    UINT16_S handoverZcId = DEFAULT_ZERO;
    UINT16_S takeoverZcId = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT16_S trainControlZc = DEFAULT_ZERO;
    UINT8_S rtnGetLoc = RETURN_ERROR;

    /*获取列车信息*/
    trainChangeLineId = GetTrainChangeLineId(trainId);
    trainState = GetTrainStatus(trainId);
    trainDir = GetTrainUnsafeDirection(trainId);

    if (DEFAULT_ZERO != trainChangeLineId)
    {
        if (TRAIN_STATE_HANDOVER == trainState)
        {
            /*有切换线路且状态为移交状态,输出信息为移交申请*/
            SetTrainHandoverOutType(trainId,NZC_TRAIN_HANDOVER);
        } 
        else
        {
            changeLink = GetChangeLineChangePointLink(trainChangeLineId);
            changeOffset = GetChangeLineChangePointOffset(trainChangeLineId);
            handoverZcId = GetChangeLineHandOverZcId(trainChangeLineId);
            takeoverZcId = GetChangeLineTakeOverZcId(trainChangeLineId);
            localZcId = GetLocalZcId();
            rtnGetLoc = GetTrainSafeLoc(trainId,&trainSafeLocStru);

            if (RETURN_SUCCESS == rtnGetLoc)
            {
                /*判断列车安全车尾是否越过切换点*/
                checkTrainTailRtn = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,changeLink,changeOffset,trainDir);

                if (1U == checkTrainTailRtn)
                {
                    /*安全车尾已越过分界点且还位于切换线路内*/
                    if (handoverZcId == localZcId)
                    {
                        /*本ZC在该分界点为移交角色,相邻ZC输出状态为无状态*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    } 
                    else if (takeoverZcId == localZcId)
                    {
                        /*本ZC在该分界点为接管角色,相邻ZC输出状态为接管未切换*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOTAKE);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    } 
                    else
                    {
                        /*相邻ZC输出状态为无状态*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    }
                } 
                else
                {
                    /*判断列车安全车头是否越过切换点*/
                    checkTrainHeadRtn = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset,changeLink,changeOffset,trainDir);

                    if (2U == checkTrainHeadRtn)
                    {
                        /*安全车头未越过切换点且不处于切换状态,相邻ZC输出信息为移交未切换*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOHAND);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    } 
                    else
                    {
                        trainControlZc = GetTrainControlZc(trainId);

                        if ((1U == checkTrainHeadRtn)
                            && (2U == checkTrainTailRtn)
                            && (trainControlZc == localZcId))
                        {
                            /*车头越过但车尾未越过切换点,受控ZC是本ZC*/
                            if (handoverZcId == localZcId)
                            {
                                /*本ZC在该分界点为移交角色*/
                                SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOHAND);
                                SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                            } 
                            else if (takeoverZcId == localZcId)
                            {
                                /*本ZC在该分界点为接管角色*/
                                SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOTAKE);
                                SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                            } 
                            else
                            {
                                /*相邻ZC输出状态为无状态*/
                                SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                                SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                            }
                        } 
                        else
                        {
                            /*相邻ZC输出状态为无状态*/
                            SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                            SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                        }
                    }
                }
            }
        }
    } 
    else
    {
        /*相邻ZC输出状态为无状态*/
        SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
    }
}

/*************************************************
  函数名:      JudegeNZcHandStatusTransform
  功能描述:    处理相邻ZC输入状态为移交申请状态的下的相邻ZC输出转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudegeNZcHandStatusTransform(const UINT16_S trainId)
{
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S changeLink = DEFAULT_ZERO;
    UINT32_S changeOffset = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainChangeLineId = DEFAULT_ZERO;
    UINT8_S checkTrainHeadRtn = DEFAULT_ZERO;
    UINT8_S checkTrainTailRtn = DEFAULT_ZERO;
    UINT8_S trainState = DEFAULT_ZERO;
	UINT16_S localZcId = DEFAULT_ZERO;
    UINT16_S trainControlZc = DEFAULT_ZERO;
	UINT8_S rtnLoc = RETURN_ERROR;

    /*获取列车信息*/
    trainChangeLineId = GetTrainChangeLineId(trainId);
    trainState = GetTrainStatus(trainId);
    trainDir = GetTrainUnsafeDirection(trainId);
    rtnLoc = GetTrainSafeLoc(trainId,&trainSafeLocStru);

    if (((TRAIN_STATE_MOVING == trainState) || (TRAIN_STATE_TAKEOVER == trainState))
        && (DEFAULT_ZERO != trainChangeLineId))
    {
        changeLink = GetChangeLineChangePointLink(trainChangeLineId);
        changeOffset = GetChangeLineChangePointOffset(trainChangeLineId);			

        if (RETURN_SUCCESS == rtnLoc)
        {
            /*判断列车安全车尾是否越过切换点*/
            checkTrainTailRtn = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,changeLink,changeOffset,trainDir);

            localZcId = GetLocalZcId();
            trainControlZc = GetTrainControlZc(trainId);

            /* 安全车尾越过分界点 */
            if (0x01U == checkTrainTailRtn)
            {         
                if (localZcId == trainControlZc)
                {
                    /*车尾已越过切换点,相邻ZC输出信息为接管未切换*/
                    SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOTAKE);
                    SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                } 
                else
                {
                    /*清空为无状态*/
                    SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                    SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                }
            } 
            else
            {
                /*判断车头是否越过切换点*/
                checkTrainHeadRtn = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset,changeLink,changeOffset,trainDir);

                if ((0x01U == checkTrainHeadRtn)
                    && (localZcId == trainControlZc)
                    && (TRAIN_STATE_MOVING == trainState))
                {
                    /*越过切换点且受控已变为本ZC*/
                    SetTrainHandoverOutType(trainId,NZC_TRAIN_HADTOOKOVER);
                    SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                } 
                else
                {
                    SetTrainHandoverOutType(trainId,NZC_TRAIN_CONFIRMATION);
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
        if (DEFAULT_ZERO == trainChangeLineId)
        {
            /*清空为无状态*/
            SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
            SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
        } 
        else
        {
            /*维持状态*/
        }
    }
}

/*************************************************
  函数名:      JudgeNZcConfirmationStatusTransform
  功能描述:    处理相邻ZC输入状态为移交申请确认状态的下的相邻ZC输出转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeNZcConfirmationStatusTransform(const UINT16_S trainId)
{
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT16_S changeLink = DEFAULT_ZERO;
    UINT32_S changeOffset = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainChangeLineId = DEFAULT_ZERO;
    UINT8_S checkTrainHeadRtn = DEFAULT_ZERO;
    UINT8_S trainState = DEFAULT_ZERO;
	UINT16_S localZcId = DEFAULT_ZERO;
    UINT16_S trainControlZc = DEFAULT_ZERO;
	UINT8_S trainInType = DEFAULT_ZERO;
	UINT8_S rtnLoc = RETURN_ERROR;

    /*获取列车信息*/
    trainChangeLineId = GetTrainChangeLineId(trainId);
    trainState = GetTrainStatus(trainId);
    trainDir = GetTrainUnsafeDirection(trainId);
    rtnLoc = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);
	trainControlZc = GetTrainControlZc(trainId);


	localZcId = GetLocalZcId();

    if (DEFAULT_ZERO == trainChangeLineId)
    {
        /*清除相邻ZC输出位信息*/
        SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
    } 
    else
    {
        if (TRAIN_STATE_HANDOVER == trainState)
        {
            /*维持状态*/
        } 
        else
        {
            if (RETURN_SUCCESS == rtnLoc)
            {
                /*判断车头是否越过切换点*/
                checkTrainHeadRtn = CheckLocRelationBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,trainUnSafeLocStru.TrainHeadOffset,changeLink,changeOffset,trainDir);

                if (0x01U == checkTrainHeadRtn)
                {
                    /*越过切换点且受控仍为本ZC(移交ZC)*/
                    trainInType = GetTrainInType(trainId);

                    if ((DEFAULT_ZERO != trainInType)
                        && (trainControlZc == localZcId))
                    {
                        /*车头越过切换点且该列车还申请MA,相邻ZC输出信息为移交未切换*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOHAND);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    } 
                    else
                    {
                        /*车头越过切换点且受控已不是本ZC或者无列车输入信息,清除相邻ZC输出信息*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    }
                } 
                else
                {
                    /*车头未越过切换点且不为移交状态列车,相邻ZC输出信息为移交未切换*/
                    SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOHAND);
                    SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                }
            }          
        }
    }
}

/*************************************************
  函数名:      JudgeNZcManagenohandStatusTransform
  功能描述:    处理相邻ZC输入状态为移交未切换状态的下的相邻ZC输出转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeNZcManagenohandStatusTransform(const UINT16_S trainId)
{
	TrainSafeLocStruct trainUnSafeLocStru;
	UINT16_S changeLink = DEFAULT_ZERO;
	UINT32_S changeOffset = DEFAULT_ZERO;
	UINT8_S trainDir = DEFAULT_ZERO;
	UINT16_S trainChangeLineId = DEFAULT_ZERO;
	UINT8_S checkTrainHeadRtn = DEFAULT_ZERO;
	UINT16_S localZcId = DEFAULT_ZERO;
	UINT16_S trainControlZc = DEFAULT_ZERO;
	UINT8_S trainInType = DEFAULT_ZERO;
	UINT8_S rtnLoc = RETURN_ERROR;
	UINT8_S trainState = DEFAULT_ZERO;

	/*获取列车信息*/
	trainChangeLineId = GetTrainChangeLineId(trainId);
	trainDir = GetTrainUnsafeDirection(trainId);
	rtnLoc = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);
	trainControlZc = GetTrainControlZc(trainId);
	trainState = GetTrainStatus(trainId);

	localZcId = GetLocalZcId();

	if (DEFAULT_ZERO == trainChangeLineId)
	{
		/*清除相邻ZC输出位信息*/
		SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
		SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
	} 
	else
	{
		if ((RETURN_SUCCESS == rtnLoc)
			&& (DEFAULT_ZERO == trainState))
		{
			changeLink = GetChangeLineChangePointLink(trainChangeLineId);
			changeOffset = GetChangeLineChangePointOffset(trainChangeLineId);

			/*判断车头是否越过切换点*/
			checkTrainHeadRtn = CheckLocRelationBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,trainUnSafeLocStru.TrainHeadOffset,changeLink,changeOffset,trainDir);

			if (0x01U == checkTrainHeadRtn)
			{
				/*越过切换点且受控仍为本ZC(接管ZC)*/
				trainInType = GetTrainInType(trainId);

				if ((DEFAULT_ZERO != trainInType)
					&& (trainControlZc == localZcId))
				{
					/*车头越过切换点且该列车已开始申请MA,相邻ZC输出信息为接管未切换*/
					SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOTAKE);
					SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
				} 
				else
				{
					/*车头越过切换点且受控已不是本ZC或者无列车输入信息,清除相邻ZC输出信息*/
					SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
					SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
				}
			} 
			else
			{
				/*车头未越过切换点,清除相邻ZC输出信息*/
				SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
				SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
			}
		} 
        else
        {
            /*清除相邻ZC输出位信息*/
            SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
            SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
        }
	}
}

/*************************************************
  函数名:      JudgeTrainDefaultStatusTransform
  功能描述:    处理默认状态的转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainDefaultStatusTransform(const UINT16_S trainId)
{
	UINT8_S trainType = DEFAULT_ZERO;
	UINT8_S trainInType = DEFAULT_ZERO;
	UINT8_S trainSuspectHead = DEFAULT_ZERO;
	UINT8_S matchRouteNum =DEFAULT_ZERO;
	UINT8_S checkFlag = RETURN_ERROR;
	
	/* 获取列车信息 */
	trainType = GetTrainType(trainId);
	trainInType = GetTrainInType(trainId);
	trainSuspectHead = GetTrainSuspectHead(trainId);
	matchRouteNum = GetMatchRouteNum(trainId);
	checkFlag = CheckTrainLocSwitchLockState(trainId);
	 
    switch (trainType)
    {
    case TRAIN_MODE_CBTC:
        if (NZC_TRAIN_HANDOVER == GetTrainHandoverInType(trainId))
        {
            SetTrainStatus(trainId,TRAIN_STATE_TAKEOVER);
        } 
        else
        {
            /*不处理*/
        }
        break;
    case TRAIN_MODE_IN:
    case TRAIN_MODE_RM:
    case TRAIN_MODE_RM0:
        if ((DEFAULT_ZERO != trainInType)
            && (FLAG_UNSET == trainSuspectHead)
            && (DEFAULT_ZERO < matchRouteNum)
            && (RETURN_SUCCESS == checkFlag))
        {
            SetTrainStatus(trainId,TRAIN_STATE_MOVING);
        } 
        else
        {
            /*不处理*/
        }
        break;
    default:
        break;
    }
}

/*************************************************
  函数名:      JudgeTrainStateMovingTransform
  功能描述:    处理STATE_MOVING状态列车状态的转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainStateMovingTransform(const UINT16_S trainId)
{
    UINT16_S trainChangeLineId = DEFAULT_ZERO;
    UINT16_S trainMaTailLink = DEFAULT_ZERO;
    UINT32_S trainMaTailOffset = DEFAULT_ZERO;
    UINT16_S changeLink = DEFAULT_ZERO;
    UINT32_S changeOffset = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S checkRtn = DEFAULT_ZERO;
    UINT16_S routeIdBuff[SIZE_MAX_ROUTENUM] = {DEFAULT_ZERO};
	UINT8_S trainType = DEFAULT_ZERO;
	UINT8_S trainInType = DEFAULT_ZERO;
	UINT8_S trainSuspectHead = DEFAULT_ZERO;
	UINT8_S matchRouteNum =DEFAULT_ZERO;
	UINT8_S checkFlag = RETURN_ERROR;	
    UINT16_S handoverZcId = DEFAULT_ZERO;
	UINT16_S localZcId = DEFAULT_ZERO;
	
	MemorySet(&routeIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)));
	
	/* 获取列车信息 */
	trainType = GetTrainType(trainId);
	trainInType = GetTrainInType(trainId);
	trainSuspectHead = GetTrainSuspectHead(trainId);
	matchRouteNum = GetMatchRouteNum(trainId);
	checkFlag = CheckTrainLocSwitchLockState(trainId);
    
    if (TRAIN_MODE_CBTC == trainType)
    {
       /* LogPrintf(1U,"15.05 TrainId=%d,TrainIntype=%d,TrainStatus=%d\n",trainId,trainInType,GetTrainStatus(trainId)); */
        switch (trainInType)
        {
        case TRAIN_IN_APPLY_MA:		
            trainChangeLineId = GetTrainChangeLineId(trainId);
			handoverZcId = GetChangeLineHandOverZcId(trainChangeLineId);
			localZcId = GetLocalZcId();
            if ((DEFAULT_ZERO != trainChangeLineId)
                && (handoverZcId == localZcId))
            {
                /*获取信息*/
                trainMaTailLink = GetMaTailLink(trainId);
                trainMaTailOffset = GetMaTailOffset(trainId);
                changeLink = GetChangeLineChangePointLink(trainChangeLineId);
                changeOffset = GetChangeLineChangePointOffset(trainChangeLineId);
                trainDir = GetTrainUnsafeDirection(trainId);

                /*判断列车的移动授权信息是否已到达切换点或者越过切换点*/
                checkRtn = CheckLocRelationBetweenTwoPoints(trainMaTailLink,trainMaTailOffset,changeLink,changeOffset,trainDir);

                if ((0x02U == checkRtn) || (RETURN_ERROR == checkRtn))
                {
                    /*未越过*/
                } 
                else
                {
                    /*越过,设置列车为移交状态*/
                    SetTrainStatus(trainId,TRAIN_STATE_HANDOVER);
                }
            } 
            else
            {
                /*不处理*/
            }
            break;
        case TRAIN_IN_TOEXITCBTC:
               /*不处理*/
            break;
        case TRAIN_IN_REVERSETOCANCEL:

            if (RETURN_SUCCESS == GetTrainMatchedRouteIdBuff(trainId,routeIdBuff))
            {
                if (LINE_REVERSE_ROUTE == GetRouteType(routeIdBuff[DEFAULT_ZERO]))
                {
                    /*列车完全位于折返进路当中*/
                    SetTrainStatus(trainId,TRAIN_STATE_REVERSE);
                } 
                else
                {
                    /*不处理*/
                }
            }          
            LogPrintf(1U,"15.02 TrainId=%d,Status=%d,StatusOut=%d\n",trainId,GetTrainStatus(trainId));
            break;
        default:
            break;
        }
    } 
    else
    {
        /*PBW,2016.7.8 增加对列车已经为TRAIN_MODE_OUT的处理*/
        if ((TRAIN_MODE_OUT == trainType) && (TRAIN_IN_TOEXITCBTC == trainInType))
        {
            /*列车完全位于退出CBTC区域*/
            SetTrainStatus(trainId,TRAIN_STATE_CANCELLATION);
            LogPrintf(1U,"22 ExitCbtc:%d,%d",trainInType,GetTrainStatus(trainId));                
        } 

        /*不为CBTC列车*/
        if ((FLAG_UNSET == trainSuspectHead)
            && (DEFAULT_ZERO < matchRouteNum)
            && (RETURN_SUCCESS == checkFlag))
        {
            /*不处理*/
        } 
        else
        {
            /*清空状态位*/
            SetTrainStatus(trainId,DEFAULT_ZERO);
            LogPrintf(1U,"15.10 TrainId=%d,SHead=0x%x,%d,%d,Clear TrainStatus!\n",trainId,trainSuspectHead,matchRouteNum,checkFlag);
        }
    }
}

/*************************************************
  函数名:      JudgeTrainHandOverTransform
  功能描述:    处理STATE_HANDOVER状态列车状态的转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainHandOverTransform(const UINT16_S trainId)
{
    UINT16_S trainChangeLineId = DEFAULT_ZERO;
    UINT16_S trainMaTailLink = DEFAULT_ZERO;
    UINT32_S trainMaTailOffset = DEFAULT_ZERO;
    UINT16_S changeLink = DEFAULT_ZERO;
    UINT32_S changeOffset = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S checkRtn = DEFAULT_ZERO;
    TrainSafeLocStruct trainSafeLocStru;

    trainChangeLineId = GetTrainChangeLineId(trainId);

    if (DEFAULT_ZERO == trainChangeLineId)
    {
        /*无切换线路,直接转换为正常模式*/
        SetTrainStatus(trainId,TRAIN_STATE_MOVING);
    } 
    else
    {
        /*获取列车安全位置*/
        if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
        {
            changeLink = GetChangeLineChangePointLink(trainChangeLineId);
            changeOffset = GetChangeLineChangePointOffset(trainChangeLineId);
            trainDir = GetTrainUnsafeDirection(trainId);

            checkRtn = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,
                changeLink,changeOffset,trainDir);

            if (2U == checkRtn)
            {
                /*车尾未越过分界点*/
                if (GetChangeLineHandOverZcId(trainChangeLineId) == GetLocalZcId())
                {
                    /*获取信息*/
                    trainMaTailLink = GetMaTailLink(trainId);
                    trainMaTailOffset = GetMaTailOffset(trainId);			

                    /*判断列车的移动授权信息是否已到达切换点或者越过切换点*/
                    checkRtn = CheckLocRelationBetweenTwoPoints(trainMaTailLink,trainMaTailOffset,changeLink,changeOffset,trainDir);

                    if ((0x02U == checkRtn) || (RETURN_ERROR == checkRtn))
                    {
                        /*未越过,不满足切换条件,转换为正常模式*/
                        SetTrainStatus(trainId,TRAIN_STATE_MOVING);
                    } 
                    else
                    {
                        /*越过,维持移交状态*/
                    }
                } 
                else
                {
                    /*不处理*/
                }
            } 
            else
            {
                /*车尾越过分界点*/
                if ((1U == checkRtn) || (3U == checkRtn))
                {
                    if (TRAIN_IN_HANDOVERTOCANCEL == GetTrainInType(trainId))
                    {
                        /*列车申请切换注销,车尾越过或者重合切换点,设置列车状态为注销状态*/
                        SetTrainStatus(trainId,TRAIN_STATE_CANCELLATION);
                    } 
                    else
                    {
                        /*列车未申请注销,车尾越过切换点,设置为故障状态,发送空MA,删除列车信息*/
                        /* SetTrainStatus(trainId,TRAIN_STATE_FAILURE); */
                        /* pbw 2017.8.4 车与接管ZC未建立通信 让车维持移交状态 */
                        if(GetTrainControlZc(trainId) != GetChangeLineHandOverZcId(trainChangeLineId))
                        {
                            SetTrainStatus(trainId,TRAIN_STATE_FAILURE);
                        }
                    }
                } 
                else
                {
                    SetTrainToModeToRM0(trainId);
					LogPrintf(1u,"%d-B68\n",trainId);
                }
            }
        } 
        else
        {
            SetTrainToModeToRM0(trainId);
			LogPrintf(1u,"%d-B69\n",trainId);
        }
    }
}

/*************************************************
  函数名:      JudgeTrainTakeOverTransform
  功能描述:    处理STATE_TAKEOVER状态列车状态的转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainTakeOverTransform(const UINT16_S trainId)
{
    UINT16_S trainChangeLineId = DEFAULT_ZERO;
    UINT16_S changeLink = DEFAULT_ZERO;
    UINT32_S changeOffset = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S checkRtn = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT16_S routeIdBuff[SIZE_MAX_ROUTENUM] = {DEFAULT_ZERO};
    UINT8_S routeNum = DEFAULT_ZERO;
    UINT8_S trainInType = DEFAULT_ZERO;
	UINT16_S unsafeHeadLink = DEFAULT_ZERO;
    UINT32_S unsafeHeadOffset = DEFAULT_ZERO;
    UINT8_S rtnGetLoc = RETURN_ERROR;
    UINT8_S rtnGetMatchedRoute = RETURN_ERROR;

    MemorySet(&routeIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)));

    /*获取列车信息*/
    trainChangeLineId = GetTrainChangeLineId(trainId);
    trainDir = GetTrainUnsafeDirection(trainId);
    changeLink = GetChangeLineChangePointLink(trainChangeLineId);
    changeOffset = GetChangeLineChangePointOffset(trainChangeLineId);
    rtnGetLoc = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);
    rtnGetMatchedRoute = GetTrainMatchedRouteIdBuff(trainId,routeIdBuff);
    routeNum = GetMatchRouteNum(trainId);
    trainInType = GetTrainInType(trainId);
	
    if ((RETURN_SUCCESS == rtnGetLoc) && (RETURN_SUCCESS == rtnGetMatchedRoute))
    {
        /*判断列车的非安全车头是否已到越过达切换点*/
        unsafeHeadLink = trainUnSafeLocStru.TrainHeadLink;
        unsafeHeadOffset = trainUnSafeLocStru.TrainHeadOffset;

        checkRtn = CheckLocRelationBetweenTwoPoints(unsafeHeadLink,unsafeHeadOffset,changeLink,changeOffset,trainDir);

        if ((0x01U == checkRtn)
            && (TRAIN_IN_APPLY_MA == trainInType)
            && (DEFAULT_ZERO != routeIdBuff[DEFAULT_ZERO])
            && (DEFAULT_ZERO < routeNum))
        {
            /*列车非安全车头越过切换点,列车输入移动授权请求且本ZC成功匹配进路给列车*/
            if(FLAG_UNSET ==  GetTrainSuspectHead(trainId))
            {
                /* 2017.8.22 添加前端危险标识的限制条件 */
                SetTrainStatus(trainId,TRAIN_STATE_MOVING);
            }
            else
            {
                /* 清空列车状态 */
                SetTrainStatus(trainId,DEFAULT_ZERO);
            }           
        } 
        else
        {
            /*不转换*/
        }
    } 
    else
    {
        /*不转换*/
    }
    
}

/*************************************************
  函数名:      JudgeTrainReverseTransform
  功能描述:    处理STATE_REVERSE状态列车状态的转换
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainReverseTransform(const UINT16_S trainId)
{
    UINT16_S routeIdBuff[SIZE_MAX_ROUTENUM] = {DEFAULT_ZERO};
    UINT8_S trainInType = DEFAULT_ZERO;
    UINT8_S rtnGetMatchedRoute = RETURN_ERROR;
    UINT8_S routeType = DEFAULT_ZERO;

    MemorySet(&routeIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)),
        0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)));

    /*获取列车信息*/
    rtnGetMatchedRoute = GetTrainMatchedRouteIdBuff(trainId,routeIdBuff);
    routeType = GetRouteType(routeIdBuff[DEFAULT_ZERO]); 

    if ((RETURN_SUCCESS == rtnGetMatchedRoute) 
        && (DEFAULT_ZERO != routeIdBuff[DEFAULT_ZERO]))
    {
        /* 列车输入类型 */
        trainInType = GetTrainInType(trainId);

        /*折返状态下匹配的第一条进路不为折返进路*/
        if (((TRAIN_IN_CHANGED == trainInType) || (TRAIN_IN_APPLY_MA == trainInType)))
        {
            /*列车发送换端完成申请/或者未收到换端完成而收到申请MA,列车匹配进路成功*/
            SetTrainStatus(trainId,TRAIN_STATE_MOVING);
        } 
        else
        {
            /*不转换*/
        }
    } 
    else
    {
        /*不转换*/
    }

    LogPrintf(1U,"15.03 TrainId=%d,Status=%d,TrainInType=%d,routeId=%d\n",trainId,GetTrainStatus(trainId),GetTrainInType(trainId),routeIdBuff[DEFAULT_ZERO]);
}

/*************************************************
  函数名:      CheckTrainLocSwitchLockState
  功能描述:    检查车身范围内的道岔锁闭状态
  输入:        const UINT16_S trainId,列车Id
  输出:        无
  返回值:      0u：锁闭异常
               1u：锁闭正常
*************************************************/
UINT8_S CheckTrainLocSwitchLockState(const UINT16_S trainId)
{
    TrainSafeLocStruct trainSafeLocStru;	
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S acNum = DEFAULT_ZERO;
    UINT16_S acIdBuff[ZC_TWO_POINT_AC_NUM_MAX] = {DEFAULT_ZERO};
    UINT8_S checkRtn = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S switchNum = DEFAULT_ZERO;
    SwitchInAcStruct switchInAcStruBuff[AC_SWITCH_SUM_MAX];
    UINT8_S cycleSwtich = DEFAULT_ZERO;
    UINT8_S breakFalg = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S getFlag = RETURN_ERROR;
	UINT8_S locRtn = RETURN_ERROR;

    MemorySet(acIdBuff,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)),
               0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)));
    MemorySet(switchInAcStruBuff,((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX)),
               0U,((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX)));

    /*获取列车相关信息*/
    locRtn = GetTrainSafeLoc(trainId,&trainSafeLocStru);

    trainDir = GetTrainUnsafeDirection(trainId);

    /*查询列车安全位置占压的计轴区段信息*/
    checkRtn = CheckAcOrderBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainHeadLink,
        trainDir,&acNum,acIdBuff);

    if ((RETURN_SUCCESS == locRtn) && (RETURN_SUCCESS == checkRtn)
        && (DEFAULT_ZERO < acNum))
    {
        /*获取计轴区段包含的道岔*/
        for (cycle = DEFAULT_ZERO;cycle < acNum;cycle++)
        {
            /*获取计轴区段包含的道岔*/
            switchNum = GetAcSwitchNum(acIdBuff[cycle]);
            getFlag = GetAcSwitchInfo(acIdBuff[cycle],AC_SWITCH_SUM_MAX,switchInAcStruBuff);
			
            if ((DEFAULT_UINT8_VALUE != switchNum)
                && (RETURN_SUCCESS == getFlag))
            {
                for (cycleSwtich = DEFAULT_ZERO;cycleSwtich < switchNum;cycleSwtich++)
                {
                    if (RETURN_ERROR != GetSwitchLock(switchInAcStruBuff[cycleSwtich].SwitchId))
                    {
                        /*不处理*/
                    } 
                    else
                    {
                        rtnValue = RETURN_ERROR;
                        breakFalg = FLAG_SET;
                        break;
                    }
                }
            } 
            else
            {
                rtnValue = RETURN_ERROR;
            }

            if (FLAG_SET == breakFalg)
            {
                break;
            } 
            else
            {
                /*不处理*/
            }
        }

        if (FLAG_SET == breakFalg)
        {
            /*不处理*/
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      JudgeTrainLocalInChangeLine
  功能描述:    检查列车是否位于本ZC切换线路的移交ZC范围内
  输入:        const UINT16_S trainId,列车Id
  输出:        UINT16_S *pOutChangeLineId,输出的切换线路ID
  返回值:      0u：不属于
               1u：属于
*************************************************/
UINT8_S JudgeTrainLocalInChangeLine(const UINT16_S trainId,UINT16_S *pOutChangeLineId)
{
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S changeLineId = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;

    if (NULL != pOutChangeLineId)
    {
        (*pOutChangeLineId) = DEFAULT_ZERO;

        /*获取列车安全位置信息*/
        if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
        {
            if (GetLineSegBelongZcId(trainSafeLocStru.TrainHeadLink) == GetLocalZcId())
            {
                for (cycle = DEFAULT_ZERO;cycle < GetChangeLineSum();cycle++)
                {
                    changeLineId = GetChangeLineId(cycle);

                    if (RETURN_SUCCESS == CheckPointBelongTocondominiumLineOfHand(changeLineId,trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset))
                    {
                        /*属于该切换线路的移交ZC范围内*/
                        rtnValue = RETURN_SUCCESS;
                        (*pOutChangeLineId) = changeLineId;
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
                /*不属于本ZC*/
            }
        } 
        else
        {
            /*Do nothing currently !*/
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*************************************************
  函数名:      JudgeTrainInfoOfCiCommFailure
  功能描述:    处于由于CI通信故障导致的列车信息变化
  输入:        const UINT16_S ciId,联锁ID
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainInfoOfCiCommFailure(const UINT16_S ciId)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT16_S trainUnsafeHeadAc = DEFAULT_ZERO;
    UINT16_S acBelongCiId = DEFAULT_ZERO;
	
    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        trainId = GetTrainIdOfIndex(cycle);        
        trainUnsafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);
        
        if (DEFAULT_ZERO != trainUnsafeHeadAc)
        {
			trainType = GetTrainType(trainId);
			acBelongCiId = GetAcBelongCiId(trainUnsafeHeadAc);
			
            if (((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType))
                && (ciId == acBelongCiId))
            {
                /*在本CI范围内的列车紧急制动*/
                SetTrainToModeToRM0(trainId);
				LogPrintf(1u,"%d-B70\n",trainId);
            } 
            else
            {
                /*不处理*/
            }
        } 
        else
        {
            if (DEFAULT_ZERO != trainId)
            {
                SetTrainStatus(trainId,TRAIN_STATE_FAILURE);
            } 
            else
            {
                /*不处理*/
            }
        }
    }
}

/*************************************************
  函数名:      JudgeTrainInfoOfNZcCommFailure
  功能描述:    处于由于相邻Zc通信故障导致的列车信息变化
  输入:        const UINT16_S nZcId,相邻ZcId
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainInfoOfNZcCommFailure(const UINT16_S nZcId)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainStatus = DEFAULT_ZERO;
    UINT16_S changeLineId = DEFAULT_ZERO;
    UINT16_S changeLink = DEFAULT_ZERO;
    UINT32_S changeOffset = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnSafeLocStru;
    UINT8_S checkRtn = DEFAULT_ZERO;
    UINT16_S takeOverZcId = DEFAULT_ZERO;
	
    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        trainId = GetTrainIdOfIndex(cycle);
        trainStatus = GetTrainStatus(trainId);

        if ((TRAIN_STATE_HANDOVER == trainStatus)
            || (TRAIN_STATE_TAKEOVER == trainStatus))
        {
            changeLineId = GetTrainChangeLineId(trainId);
			takeOverZcId = GetChangeLineTakeOverZcId(changeLineId);

            if ((DEFAULT_ZERO != changeLineId) && (takeOverZcId == nZcId))
            {
                /*清除相邻ZC的移动授权信息*/
                DeleteNextZcSingleTrainMaInfo(trainId);

                /*查询列车车头是否越过分界点*/
                if (RETURN_SUCCESS == GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru))
                {
                    changeLink = GetChangeLineChangePointLink(changeLineId);
                    changeOffset = GetChangeLineChangePointOffset(changeLineId);

                    checkRtn = CheckLocRelationBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,trainUnSafeLocStru.TrainHeadOffset,changeLink,changeOffset,
                        GetTrainUnsafeDirection(trainId));

                    switch (checkRtn)
                    {
                    case 1U:
                        /*越过,不处理*/
                        break;
                    case 2U:
                    case 3U:
                        /*未越过*/
                        if (TRAIN_STATE_HANDOVER == trainStatus)
                        {
                            SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                        } 
                        else
                        {
                            /*接管状态,车头未越过切换点,将列车信息删除*/
                            DeleteSingleTrainInfo(trainId);

							/*11.30,清除通信状态信息*/
							ClearOneTrainCommCycleAndStatus(trainId);
                        }
                        break;
                    default:
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                        break;
                    }
                }
                else
                {
                    /* 不处理 */
                }               
            } 
            else
            {
                /* 不处理 */
            }
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*************************************************
  函数名:      CalculateTrainInChangeLineId
  功能描述:    计算列车是否位于某个切换线路
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void CalculateTrainInChangeLineId(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        /*获取列车ID*/
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);

        if ((TRAIN_MODE_CBTC == trainType)
            || (TRAIN_MODE_TO_RM0 == trainType))
        {
            /*获取列车是否位于某个切换线路中,并设置切换线路*/
            SetTrainChangeLineId(trainId , JudgeSignalTrainChangeLineId(trainId));	
        } 
        else
        {
            SetTrainChangeLineId(trainId,DEFAULT_ZERO);
        }
    }
}

/*************************************************
  函数名:      JudgeSignalTrainChangeLineId
  功能描述:    计算列车是否位于某个切换线路
  输入:        const UINT16_S trainId,列车ID
  输出:        无
  返回值:      0u:不位于切换线路内
               >0u:位于切换区域内
*************************************************/
UINT16_S JudgeSignalTrainChangeLineId(const UINT16_S trainId)
{
    UINT16_S rtnChangeLineId = DEFAULT_ZERO;
    UINT16_S changeLineId = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S startLink = DEFAULT_ZERO;
    UINT32_S startOffset = DEFAULT_ZERO;
    UINT16_S endLink = DEFAULT_ZERO;
    UINT32_S endOffset = DEFAULT_ZERO;
    UINT8_S trainOccAcNum = DEFAULT_ZERO;
    UINT16_S trainOccAcIdBuff[ZC_TWO_POINT_AC_NUM_MAX] = {DEFAULT_ZERO};
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainUnsafeHeadAc = DEFAULT_ZERO;

    MemorySet(&trainOccAcIdBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)),
                0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)));

    /*获取列车方向信息*/
    trainDir = GetTrainUnsafeDirection(trainId);
    trainUnsafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);

    for (cycle = DEFAULT_ZERO;cycle < GetChangeLineSum();cycle++)
    {
        /*获取切换线路ID*/
        changeLineId = GetChangeLineId((UINT16_S)cycle);

        if (trainDir == GetChangeLineDir(changeLineId))
        {
            /*判断切换线路的道岔是否满足条件*/
            if (RETURN_SUCCESS == CalculateChangeLineSwtichPosInNeed(changeLineId))
            {
                /*初始化*/
                trainOccAcNum = DEFAULT_ZERO;
                MemorySet(trainOccAcIdBuff,sizeof(UINT16_S)*ZC_TWO_POINT_AC_NUM_MAX,DEFAULT_ZERO,sizeof(UINT16_S)*ZC_TWO_POINT_AC_NUM_MAX);

                /*获取切换线路信息*/
                startLink = GetChangeLineStartLink(changeLineId);
                startOffset = GetChangeLineStartOffset(changeLineId);
                endLink = GetChangeLineChangePointLink(changeLineId);
                endOffset = GetChangeLineChangePointOffset(changeLineId);

                if (RETURN_SUCCESS == CheckAcOrderBetweenTwoPoints(startLink,endLink,trainDir,&trainOccAcNum,trainOccAcIdBuff))
                {
                    if (RETURN_SUCCESS == JudgeSingleAcInAcOrder(trainUnsafeHeadAc,trainOccAcNum,trainOccAcIdBuff))
                    {
                        /*查询到该切换线路可用*/
                        rtnChangeLineId = changeLineId;
                        break;
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
        else
        {
            /*不处理*/
        }
    }

    return rtnChangeLineId;
}

/*************************************************
  函数名:      CalculateChangeLineSwtichPosInNeed
  功能描述:    计算切换线路的道岔是否在需要的位置
  输入:        const UINT16_S changeLineId,切换线路ID
  输出:        无
  返回值:      0u:不满足
               1u:满足
*************************************************/
UINT8_S CalculateChangeLineSwtichPosInNeed(const UINT16_S changeLineId)
{
    UINT8_S switchNum = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    ChangeLineSwitchStruct switchStruBuff[CHANGE_LINE_SWITCH_MAX]; /*本切换线路对应的道岔数据*/
    UINT8_S flag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    MemorySet(&switchStruBuff[0],((UINT32_S)(sizeof(ChangeLineSwitchStruct) * CHANGE_LINE_SWITCH_MAX)),
                0U,((UINT32_S)(sizeof(ChangeLineSwitchStruct) * CHANGE_LINE_SWITCH_MAX)));

    switchNum = GetChangeLineSwitchNum(changeLineId);

    if (RETURN_SUCCESS == GetChangeLineSwitchStruct(changeLineId,CHANGE_LINE_SWITCH_MAX,switchStruBuff))
    {
        flag = FLAG_UNSET;

        for (cycle = DEFAULT_ZERO;cycle < switchNum;cycle++)
        {
            if (GetLocalZcId() == GetSwitchBelongZcId(switchStruBuff[cycle].SwitchId))
            {
                if (switchStruBuff[cycle].SwitchNeedStatus == GetSwitchPosStatus(switchStruBuff[cycle].SwitchId))
                {
                    /*道岔满足条件*/
                } 
                else
                {
                    flag = FLAG_SET;
                    break;
                }
            } 
            else
            {
                /*不属于本ZC*/
            }
        }
    } 
    else
    {
        /*不处理*/
    }

    if (FLAG_UNSET == flag)
    {
        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      JudgeTrainChangeId
  功能描述:    设置所有列车的切换线路ID
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void JudgeTrainChangeId(void)
{
    UINT8_S cycle = 0U;
    UINT8_S trainNum = 0U;
    UINT16_S changeLineId = 0U;
    UINT16_S trainId = 0U;

    trainNum = GetTrainCurSum();

    for (cycle = 0U;cycle < trainNum;cycle++)
    {
        trainId = GetTrainIdOfIndex(cycle);

        changeLineId = JudgeSingleTrainChangeId(trainId);

        if (DEFAULT_UINT8_VALUE != changeLineId)
        {
            SetTrainChangeLineId(trainId,changeLineId);
        }
        else
        {
            /*宕机*/
        }
    }
}

/*************************************************
  函数名:      JudgeSingleTrainChangeId
  功能描述:    查找单个列车能匹配上的切换线路的ID
  输入:        const UINT16_S trainId,列车ID
  输出:        无
  返回值:      >0u:切换区域ID
               0u:不在切换区域
               0xffu:失败
*************************************************/
UINT8_S JudgeSingleTrainChangeId(const UINT16_S trainId)
{
    UINT16_S startAcId = 0U;
    UINT16_S changeLineId = 0U;
    UINT8_S direction = 0U;
    UINT8_S outAcNum = 0U;
    UINT16_S outAcIdBuff[CHANGE_AREA_AC_MAX] = {0U};
    UINT8_S ret = 0U;
    UINT16_S switchSquBuff[CHANGE_AREA_AC_MAX] = {0U};
    ChangeLineSwitchStruct changeLineSwitchSquBuff[CHANGE_LINE_SWITCH_MAX];
    UINT8_S acNum = 0U;
    UINT16_S acBuff[CHANGE_AREA_AC_MAX] = {0U};
    UINT8_S ret2 = 0U;
    UINT8_S ret3 = 0U;
    UINT8_S rtnValue = 0U;
    UINT8_S cycle = 0U;
    UINT8_S changeNum = 0U;

    MemorySet(&outAcIdBuff[0],((UINT32_S)(SIZE_UINT16 * CHANGE_AREA_AC_MAX)),
               0U,((UINT32_S)(SIZE_UINT16 * CHANGE_AREA_AC_MAX)));
    MemorySet(&switchSquBuff[0],((UINT32_S)(SIZE_UINT16 * CHANGE_AREA_AC_MAX)),
               0U,((UINT32_S)(SIZE_UINT16 * CHANGE_AREA_AC_MAX)));
    MemorySet(changeLineSwitchSquBuff,((UINT32_S)(sizeof(ChangeLineSwitchStruct)*CHANGE_LINE_SWITCH_MAX)),
               0U,((UINT32_S)(sizeof(ChangeLineSwitchStruct)*CHANGE_LINE_SWITCH_MAX)));	
    MemorySet(&acBuff[0],((UINT32_S)(SIZE_UINT16 * CHANGE_AREA_AC_MAX)),
               0U,((UINT32_S)(SIZE_UINT16 * CHANGE_AREA_AC_MAX)));

    startAcId = JudgetrainStartIdInChange(trainId);

    if (0U == startAcId)
    {
        rtnValue = 0U;
    }
    else
    {
        direction = GetTrainUnsafeDirection(trainId);

        /*查询起始计轴到共管区域终点之间的计轴序列*/
        ret = JudgeAcSquToChangeEnd(startAcId,direction,&outAcNum,outAcIdBuff);

        /*遍历所有的切换区域*/
        changeNum = (UINT8_S)(GetChangeLineSum());

        if ((DEFAULT_ZERO < changeNum) && (RETURN_ERROR != direction))
        {	
            for (cycle = 0U;cycle < changeNum;cycle++)
            {
                /*遍历所有的切换区域*/
                changeLineId = GetChangeLineId((UINT16_S)cycle);

                if (direction == GetChangeLineDir(changeLineId))
                {
                    /*查询切换区域中的计轴序列*/
                    ret2 = CheckAcOrderAccordLineSwitchId(changeLineId, &acNum,acBuff);

                    if (RETURN_SUCCESS == ret2)
                    {
                        ret3 = JudgeRelationBetweenAcSqu(outAcNum,outAcIdBuff,acNum,acBuff);

                        if (RETURN_SUCCESS == ret3)
                        {
                            rtnValue = (UINT8_S)(changeLineId);
                            break;
                        }
                        else
                        {
                            /*继续遍历*/
                        }
                    }
                    else
                    {
                        /*失败*/
                        rtnValue = DEFAULT_UINT8_VALUE;
                        break;
                    }
                } 
                else
                {
                    /*方向不一致,遍历下一个切换线路*/
                }
            }
        }
        else
        {
            /*失败*/
            rtnValue = DEFAULT_UINT8_VALUE;
        }
    }

    return rtnValue;
}

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
UINT8_S JudgeRelationBetweenAcSqu(const UINT8_S acNum1,const UINT16_S acSqu1[],const UINT8_S acNum2,const UINT16_S acSqu2[])
{
    UINT8_S cycle1 = 0U;
    UINT8_S cycle2 = 0U;
    UINT8_S sum = 0U;
    UINT8_S rtnValue = 0U;

    if ((0U != acNum1) && (0U != acNum2)
         && (NULL != acSqu1) && (NULL != acSqu2))
    {
        for (cycle1=0U;cycle1<acNum1;cycle1++)
        {
            for (cycle2=0U;cycle2<acNum2;cycle2++)
            {
                if (acSqu1[cycle1] == acSqu2[cycle2])
                {
                    /*找到相同的计轴，跳出*/
                    sum ++;
                    break;
                }
                else
                {
                    /*继续遍历*/
                }
            }
        }

        if (sum == acNum1)
        {
            rtnValue = RETURN_SUCCESS;
        }       
    }
    else
    {
        /* 输入参数中的2个数量参数:1、任意1个为0;2、2个都为0*/
        rtnValue = RETURN_ERROR;
    }
  
    return rtnValue;
}

/*************************************************
  函数名:      JudgeSwitchStatusInChangeLine
  功能描述:    查找计轴序列内包含的道岔序列状态与切换区域状态的一致性
  输入:        const UINT16_S switchSquBuff[CHANGE_LINE_SWITCH_MAX],输入道岔序列
  			   const UINT8_S switchNum，输入道岔数量
  输出:        无
  返回值:      >0u:符合的切换区域ID
               0u: 失败
*************************************************/
UINT8_S JudgeSwitchStatusInChangeLine(const UINT16_S switchSquBuff[],const UINT8_S switchNum)
{
    UINT8_S changeNum = 0U;
    UINT8_S cycle = 0U;
    UINT8_S cycle1 = 0U;
    UINT8_S cycle2 = 0U;
    UINT8_S changeDir = 0U;
    ChangeLineSwitchStruct changeLineSwitchSquBuff[CHANGE_LINE_SWITCH_MAX];
    UINT8_S changeLineSwitchNum = 0U;
    UINT8_S switchStatus = 0U;
    UINT8_S rtnValue = 0U;
    UINT8_S checkSwitchNum = 0U;
    UINT16_S changeLineId = 0U;

    MemorySet(changeLineSwitchSquBuff,((UINT32_S)(sizeof(ChangeLineSwitchStruct)*CHANGE_LINE_SWITCH_MAX)),
                 0U,((UINT32_S)(sizeof(ChangeLineSwitchStruct)*CHANGE_LINE_SWITCH_MAX)));

    if (NULL != switchSquBuff)
    {
        changeNum = (UINT8_S)(GetChangeLineSum());

        for (cycle1=0U;cycle1<changeNum;cycle1++)
        {
            /*遍历所有的切换区域*/
            changeLineId = GetChangeLineId((UINT16_S)cycle1);

            changeDir = GetChangeLineDir(changeLineId);
            /*获取道岔数量和序列*/
            changeLineSwitchNum = GetChangeLineSwitchStruct(changeLineId,CHANGE_LINE_SWITCH_MAX,changeLineSwitchSquBuff);

            if (DEFAULT_UINT8_VALUE != changeLineSwitchNum)
            {
                checkSwitchNum = 0U;

                for (cycle=0U;cycle<switchNum;cycle++)
                {
                    for (cycle2=0U;cycle2<changeLineSwitchNum;cycle2++)
                    {
                        /*获取道岔状态*/
                        switchStatus = GetSwitchStatus(switchSquBuff[cycle]);

                        if ((switchSquBuff[cycle] == changeLineSwitchSquBuff[cycle2].SwitchId) && (changeLineSwitchSquBuff[cycle2].SwitchNeedStatus == switchStatus))
                        {
                            /*记录已经找到的正确的道岔数量*/
                            checkSwitchNum ++;							
                        }
                        else
                        {
                            /*继续遍历*/
                        }
                    }
                }

                if (checkSwitchNum == switchNum)
                {
                    /*说明在该切换区域已经找到全部道岔，且状态与要求状态一致，该切换区域即为需要的切换区域*/
                    rtnValue = (UINT8_S)(changeLineId);
                    break;
                }
                else
                {
                    /*继续遍历其它切换区域*/
                }						
            }
            else 
            {
                /*宕机*/
                rtnValue = 0U;
                break;
            }
        }
    } 
    else
    {
        /*宕机*/
        rtnValue = 0U;
    }
    
    return rtnValue;
}

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
UINT8_S JudgeSwitchIdInAcSqu(const UINT16_S acSquBuff[],const UINT8_S acNum,UINT16_S switchSquBuff[],UINT8_S *pSwitchNum)
{
    UINT8_S cycle = 0U;
    UINT8_S cycle1 = 0U;
    UINT8_S ret = 0U;
    UINT16_S checkSwitchBuff[AC_SWITCH_SUM_MAX]={0U};
    UINT8_S checkNum = 0U;
    UINT8_S rtnValue = RETURN_SUCCESS;
    
    MemorySet(&checkSwitchBuff[0],((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX)),
                0U,((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX)));

    if ((NULL != acSquBuff) && (NULL != switchSquBuff) && (NULL != pSwitchNum))
    {
        *pSwitchNum = 0U;

        for (cycle=0U;cycle<acNum;cycle++)
        {
            MemorySet(&checkSwitchBuff[0],((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX)),
                0U,((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX)));

            /*获取计轴包含的道岔*/
            ret = GetLineAcIncludeSwitchInfo(acSquBuff[cycle],&checkNum,checkSwitchBuff);

            if (RETURN_SUCCESS == ret)
            {
                for (cycle1=0U;cycle1<checkNum;cycle1++)
                {
                    switchSquBuff[(*pSwitchNum)] = checkSwitchBuff[cycle1];
                    (*pSwitchNum)++;
                }			
            }
            else
            {
                /*返回失败*/
                rtnValue = RETURN_ERROR;
            }
        }
    } 
    else
    {
        /*返回失败*/
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*************************************************
  函数名:      JudgetrainStartIdInChange
  功能描述:    查找列车位于共管区域的起始计轴
  输入:        const UINT16_S trainId,列车ID
  输出:        无
  返回值:      起始计轴区段ID
*************************************************/
UINT16_S JudgetrainStartIdInChange(const UINT16_S trainId)
{
    UINT8_S ret = 0U;
    UINT16_S startAcId = 0U;
    TrainSafeLocStruct trainSafeLocStru;
    UINT8_S trainDir = 0U;
    UINT8_S checkRtn = 0U;
    UINT8_S acNum = 0U;
    UINT16_S acIdBuff[ZC_TWO_POINT_AC_NUM_MAX]={0U};
    UINT8_S i = 0U;

    MemorySet(&acIdBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)));
  
    trainDir = GetTrainUnsafeDirection(trainId);

    ret = JudgeTrainLocInChangeLine(trainId);

    switch (ret)
    {
    case 0U:
        startAcId = 0U;
        break;
    case 1U:
        /* 车头车尾均在切换区域 */
        startAcId = GetTrainTrainTailAC(trainId);
        break;
    case 2U:		
        /*查询列车安全位置占压的计轴区段信息*/	
        if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
        {
            checkRtn = CheckAcOrderBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainHeadLink,
                trainDir,&acNum,acIdBuff);

            if ((RETURN_SUCCESS == checkRtn)
                && (acNum > 0U))
            {
                /*取出车身位于共管区域内的第一个计轴*/
                for (i = 0U;i < acNum;i++)
                {
                    /*判断计轴是否位于切换区域内*/
                    ret = JudgeAcIsInChangeLine(acIdBuff[i],trainDir);

                    if (RETURN_SUCCESS == ret)
                    {
                        startAcId = acIdBuff[i];
                        break;
                    }
                    else
                    {
                        /*继续遍历*/
                    }
                }
            }
            else
            {
                startAcId = 0U;
            }
        } 
        else
        {
            startAcId = 0U;
        }   
        break;
    case 3U:
        startAcId = GetTrainTrainTailAC(trainId);
        break;
    case 4U:
        startAcId = 0U;
        break;
    default:
        startAcId = 0U;
        break;
    }

    return startAcId;
}

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
UINT8_S JudgeTrainLocInChangeLine(const UINT16_S trainId)
{
    UINT16_S headAcId = 0U;
    UINT16_S tailAcId = 0U;
    UINT8_S ret1 = 0U;
    UINT8_S ret2 = 0U;
    UINT8_S rtnValue = 0U;
    UINT8_S trainDir = 0U;

    /*获取车头占压计轴ID*/
    headAcId = GetTrainTrainHeadAC(trainId);
    tailAcId = GetTrainTrainTailAC(trainId);

    trainDir = GetTrainUnsafeDirection(trainId);

    ret1 = JudgeAcIsInChangeLine(headAcId,trainDir);
    ret2 = JudgeAcIsInChangeLine(tailAcId,trainDir);	

    if ((RETURN_SUCCESS == ret1) && (RETURN_SUCCESS == ret2))
    {
        /*说明车头车尾均位于切换区域内*/
        rtnValue = 1U;
    }
    else if ((RETURN_SUCCESS == ret1) && (RETURN_ERROR == ret2))
    {
        /*说明车头位于切换区域内，车尾均位于切换区域外*/
        rtnValue = 2U;
    }
    else if ((RETURN_ERROR == ret1) && (RETURN_SUCCESS == ret2))
    {
        /*说明车头位于切换区域外，车尾均位于切换区域内*/
        rtnValue = 3U;
    }
    else if ((RETURN_ERROR == ret1) && (RETURN_ERROR == ret2))
    {
        /*列车位于切换区域外*/
        rtnValue = 4U;
    }
    else
    {
        /*失败*/
        rtnValue = 0U;
    }

    return rtnValue;
}

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
UINT8_S JudgeAcSquToChangeEnd(const UINT16_S acId,const UINT8_S direction,UINT8_S *pOutAcNum,UINT16_S acSquBuff[])
{
    UINT8_S cycle = 0U;
    UINT16_S nextAcId = 0U;
    UINT16_S startAcId = 0U;
    UINT8_S acNum = 0U;
    UINT8_S rtnOfJudgeACIsChangeEnd = 0U;
    UINT8_S rtnValue = 0U;

    if ((NULL != pOutAcNum) && (NULL != acSquBuff))
    {
        /*判断起始计轴本身是否属于切换区域终端*/
        rtnOfJudgeACIsChangeEnd = JudgeACIsChangeEnd(acId,direction);

        if (FLAG_SET == rtnOfJudgeACIsChangeEnd)
        {
            acSquBuff[acNum] = acId;	
            acNum = acNum + 1U;

            rtnValue =  RETURN_SUCCESS;
        }
        else if (FLAG_UNSET == rtnOfJudgeACIsChangeEnd)
        {
            startAcId = acId;

            /*填写列车占压计轴区段*/
            acSquBuff[acNum] = acId;
            acNum = acNum + 1U;

            for (cycle=0U;cycle < CHANGE_AREA_AC_MAX;cycle++)
            {
                /*获取指定计轴的下一计轴*/
                if (RETURN_SUCCESS == CheckFrontACStatus(startAcId,direction,&nextAcId))
                {
                    /*写入该计轴区段*/
                    acSquBuff[acNum] = nextAcId;
                    acNum = acNum + 1U;

                    /*判断该计轴是否为终点计轴*/
                    rtnOfJudgeACIsChangeEnd = JudgeACIsChangeEnd(nextAcId,direction);

                    if (FLAG_SET == rtnOfJudgeACIsChangeEnd)
                    {
                        rtnValue = RETURN_SUCCESS;
                        break;
                    }
                    else if (FLAG_UNSET == rtnOfJudgeACIsChangeEnd)
                    {
                        /*继续查找*/
                        startAcId = nextAcId;
                    }
                    else
                    {
                        /*失败*/
                        rtnValue = 0U;
                        break;
                    }
                }
                else
                {
                    /*找不到相邻计轴，结束*/
                    rtnValue = RETURN_SUCCESS;
                    break;
                }
            }
        }
        else
        {
            /*失败*/
            rtnValue = RETURN_ERROR;
        }

        (*pOutAcNum) = acNum;
    } 
    else
    {
        /*失败*/
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*************************************************
  函数名:      ManageDeleteTrainInfo
  功能描述:    管理需要删除列车信息函数（对需要删除的列车进行删除）
  输入:        无
  输出:        无
  返回值:      无
*************************************************/
void ManageDeleteTrainInfo(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT8_S trainState = DEFAULT_ZERO;
    UINT16_S needDeleteMaNum = DEFAULT_ZERO;
    UINT16_S needDeleteMaIdBuff[COMM_TRAIN_SUM_MAX] = {0U};
    UINT8_S trainInType = DEFAULT_ZERO;   /* 列车输入给ZC的信息 */

    MemorySet(&needDeleteMaIdBuff[0],((UINT32_S)(SIZE_UINT16 * COMM_TRAIN_SUM_MAX)),
                0U,((UINT32_S)(SIZE_UINT16 * COMM_TRAIN_SUM_MAX)));

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);
        trainState = GetTrainStatus(trainId);
        trainInType = GetTrainInType(trainId);

        if ((TRAIN_MODE_OUT == trainType)
            || (TRAIN_STATE_CANCELLATION == trainState)
            || (TRAIN_STATE_FAILURE == trainState)
            || (DEFAULT_ZERO == trainType))
        {
            /*记录该列车ID*/
            needDeleteMaIdBuff[needDeleteMaNum] = trainId;
            needDeleteMaNum++;
        } 
        else
        {
            /*不处理*/
        }
    }

    for (cycle = 0U;cycle < needDeleteMaNum;cycle++)
    {
        /*清除列车信息*/
        DeleteSingleTrainInfo(needDeleteMaIdBuff[cycle]);

		/*11.30,清除通信状态信息*/
		ClearOneTrainCommCycleAndStatus(needDeleteMaIdBuff[cycle]);

        /* pbw 2017.6.5 */
        /*删除相邻ZC输入的MA信息*/
        DeleteNextZcSingleTrainMaInfo(needDeleteMaIdBuff[cycle]);
    }
}
