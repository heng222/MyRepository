/************************************************************************
*
* 文件名   ：  SignalLogicManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  维护管理
* 备  注   ：  无
*
************************************************************************/
#include "SignalLogicManager.h"
#include "SignalConfigData.h"
#include "SignalStatusData.h"
#include "../AC/ACConfigData.h"
#include "../AC/ACStatusData.h"
#include "../AC/ACLogicManager.h"
#include "../../TrainManager/Train/TrainStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../TrainManager/Train/TrainLogicManager.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

/*
* 功能描述： 处理通信故障Ci对应的单个信号机信息
* 参数说明： const UINT16 signalId，信号机ID    
* 返回值  ： void  
*/
void InitFailureSingleSignal(const UINT16_S signalId)
{
	SetSignalCrossStatus(signalId,SIGNAL_TRAIN_NOT_CROSS);
	SetSignalStatus(signalId,SIGNAL_STATE_STOP);
	SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
}

/*
* 功能描述： 处理通信故障Ci对应的信号机信息
* 参数说明： const UINT16 ciId，联锁ID    
* 返回值  ： void  
*/
void InitFailureCiSignal(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S signalId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetSignalSum();cycle++)
	{
		signalId = GetSignalId(cycle);

		if (ciId == GetSignalBelongCiId(signalId))
		{
			/*设置状态为安全态*/
			InitFailureSingleSignal(signalId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 处理通信故障NZc对应的信号机信息
* 参数说明： const UINT16 nZCId    
* 返回值  ： void  
*/
void InitFailureNZcSignal(const UINT16_S nZCId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S signalId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetSignalSum();cycle++)
	{
		signalId = GetSignalId(cycle);

		if ((nZCId == GetSignalBelongZcId(signalId))
			&& (FLAG_SET == GetSignalChangeAttribute(signalId)))
		{
			/*设置状态为安全态*/
			InitFailureSingleSignal(signalId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 信号机亮灭控制
* 参数说明： void
* 返回值  ： void     
*/
void SignalControl(void)
{
	UINT16_S signalCycle = 0U;
	UINT16_S tempSignalId = 0U;
    UINT16_S localZcId = DEFAULT_ZERO;           /* 本地ZC的ID */
    UINT16_S signalBelongZcId = DEFAULT_ZERO;    /* 信号机所属的ZC的ID */
    UINT8_S signalLightOffType = DEFAULT_ZERO;   /* 是否需要判断灭灯标志 */ 

    localZcId = GetLocalZcId();

	for (signalCycle = 0U; signalCycle < GetSignalSum(); signalCycle++)
	{
		/*获取信号机ID*/
		tempSignalId = GetSignalId(signalCycle);        
        signalBelongZcId = (UINT16_S)(GetSignalBelongZcId(tempSignalId));
        signalLightOffType = GetSignalLightOffType(tempSignalId);

		/*判断是否需要为本信号机ID计算亮灭命令*/
		if ((localZcId == signalBelongZcId) && (FLAG_SET == signalLightOffType))
		{
			SignalLightAndOffDeal(tempSignalId);
		}
		else
		{
			/*不处理*/
		}
	}
}

/*
* 功能描述： 信号机亮灭命令处理
* 参数说明： UINT16 signalId,信号机Id
* 返回值  ： void      
*/
void SignalLightAndOffDeal(UINT16_S signalId)
{
	UINT16_S acCycle = DEFAULT_ZERO;
	UINT8_S acNum = DEFAULT_ZERO;
	UINT16_S acIdOfApproachBuff[SIGNAL_LIGHT_OFF_AC_NUM_MAX] = {DEFAULT_ZERO};
	UINT16_S tempTrainIdBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};
	UINT8_S setFlag = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;

	/*查询信号机点灯区段包含的计轴数量*/		
	if (RETURN_ERROR == CalculateAcOfSignalLighten(signalId, &acNum, acIdOfApproachBuff))
	{
		SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
	}
	else
	{
		/*遍历计轴序列*/
		for (acCycle = 0U; acCycle < acNum; acCycle++)
		{
			if (AC_OCC_STATUS == GetAcStatusNow(acIdOfApproachBuff[acCycle]))/*判断计轴是否占用*/
			{
				/*判断计轴内是否有车*/
				if (0U != GetAcTrainOfAcNum(acIdOfApproachBuff[acCycle]))
				{
					/*设置已设置标志*/
					setFlag = FLAG_SET;

					/*获取列车序列*/
					if (RETURN_SUCCESS == GetAcTrainSequenceBuff(acIdOfApproachBuff[acCycle],SIZE_MAX_TRAINOFAC,tempTrainIdBuff))
					{
                        trainType = GetTrainType(tempTrainIdBuff[0]);

                        if ((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType))
                        {
                            /*查询信号机方向*/
                            if (RETURN_ERROR != GetSignalProtectDir(signalId))
                            {
                                /*信号机防护方向与列车运行方向是否一致*/
                                if (GetSignalProtectDir(signalId) == GetTrainUnsafeDirection(tempTrainIdBuff[0]))
                                {
                                    /*方向一致*/
                                    switch (GetSignalCbtcLightOffType(signalId))
                                    {
                                    case SIGNAL_LIGHT_COMMAND:
                                        SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
                                        break;
                                    case SIGNAL_OFF_COMMAND:
                                        SetSignalLightOffStatus(signalId,SIGNAL_OFF_COMMAND);
                                        break;
                                    default:
                                        SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
                                        break;
                                    }

                                    breakFlag = FLAG_SET;
                                }
                                else
                                {
                                    /*设置为亮状态*/
                                    SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
                                }
                            }
                            else
                            {
                                SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
                                breakFlag = FLAG_SET;
                            }
					    } 
                        else
                        {
                            /*非CBTC车*/
                            SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
                            breakFlag = FLAG_SET;
                        }
                    }                   
					else
					{
                        /* 有车但是获取列车序列失败 */
                        SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
					}									
				}
				else
				{
					/*无车，看是否非通信车占用*/
					if (AC_UT_OCC_STATUS == GetAcUtFlag(acIdOfApproachBuff[acCycle]))
					{
						/*设置已设置标志*/
						setFlag = FLAG_SET;

						/*计轴区段非通信列车占用*/
						SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
						breakFlag = FLAG_SET;
					} 
					else
					{
						/*不处理*/
					}
				}
			}
			else
			{
				/*本计轴未占用，不处理*/
			}

            if (FLAG_SET == breakFlag)
            {
                break;
            }
		}

		
		if (0U == setFlag)
		{
			/*判断信号机的亮灭状态信号机亮灭灯为默认值*/
			switch (GetSignalDefaultStatus(signalId))
			{
				case SIGNAL_LIGHT_COMMAND:
					SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
					break;
				case SIGNAL_OFF_COMMAND:
					SetSignalLightOffStatus(signalId,SIGNAL_OFF_COMMAND);
					break;
				default:
					SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
					break;
			}
		}
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 计算信号机亮灭命令处理时的计轴区段序列
* 参数说明： const UINT16 signalId,信号机Id
*            UINT8_S *acNum,计轴区段数量
*            UINT16_S acIdBuff[],计轴区段ID缓存
* 返回值  ： 0: 计算失败
*			 1: 计算成功      
*/
UINT8_S CalculateAcOfSignalLighten(const UINT16_S signalId,UINT8_S *acNum,UINT16_S acIdBuff[])
{
	UINT8_S retVal = RETURN_ERROR;/*函数返回值*/
	UINT16_S signalOutsideAcId = DEFAULT_ZERO;
	UINT8_S tempAcNum = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S signalProtectionDir = DEFAULT_ZERO;
	UINT16_S nextAcId = DEFAULT_ZERO;
	UINT32_S singleAcLength = DEFAULT_ZERO;
	UINT32_S allAcLength = DEFAULT_ZERO;
    UINT8_S flag = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;  /* 跳出循环标志 */
    UINT8_S checkRtnValue = DEFAULT_ZERO; /* 查询后方计轴区段返回值 */
	UINT8_S checkAcPosRtn = DEFAULT_ZERO;

    if ((NULL != acNum) && (NULL != acIdBuff))
    {
        /*查询信号机外方第一计轴*/
		if (1U == CheckOutsideAcOfSignal(signalId,&signalOutsideAcId))
		{
			checkAcPosRtn = JudgeAcOfSwitchPosInNeed(signalOutsideAcId);
		}
		else
		{
            /* 不处理 */  
		}

		/*判断计轴区段是否满足道岔状态*/
        if (1U == checkAcPosRtn)
        {
            if (DEFAULT_ZERO == signalOutsideAcId)
            {
                /*获取失败,直接返回失败*/
                flag = FLAG_SET;		
            } 
            else
            {
                /*添加信号机外方第一计轴*/
                acIdBuff[tempAcNum] = signalOutsideAcId;
                tempAcNum++;

                /*获取信号机防护方向*/
                signalProtectionDir = GetSignalProtectDir(signalId);

                for (cycle = DEFAULT_ZERO;cycle < (SIGNAL_LIGHT_OFF_AC_NUM_MAX - 1U);cycle++)
                {
                    /*初始化*/
                    nextAcId = DEFAULT_ZERO;
                    singleAcLength = DEFAULT_ZERO;

                    /*获取计轴区段长度*/
                    if (1U == CheckAcLength(acIdBuff[tempAcNum-1U],&singleAcLength))
                    {
                        /*累加总长度*/
                        allAcLength = allAcLength + singleAcLength;

                        if (allAcLength >= GetSignalLightLength())
                        {
                            breakFlag = FLAG_SET;
                        } 
                        else
                        {
                            /*查询下一个计轴区段*/
                            checkRtnValue = CheckRearACStatus(acIdBuff[tempAcNum-1U],signalProtectionDir,&nextAcId);

                            if ((1U == checkRtnValue) && (DEFAULT_ZERO != nextAcId))
                            {
                                acIdBuff[tempAcNum] = nextAcId;
                                tempAcNum++;
                            } 
                            else if((2U == checkRtnValue) || (3U == checkRtnValue))
                            {
                                /* 由于线路尽头或者道岔原因失败,跳出循环,返回成功 */                            
                                breakFlag = FLAG_SET;
                            }
                            else
                            {
                                /*获取失败,跳出循环,返回失败*/
                                breakFlag = FLAG_SET;
                                flag = FLAG_SET;
                            }
                        }
                    } 
                    else
                    {
                        /*获取失败,跳出循环,返回失败*/
                        breakFlag = FLAG_SET;
                        flag = FLAG_SET;
                    }

                    if (FLAG_SET == breakFlag)
                    {
                        break;
                    }
                }       
            }
        } 
        else
        {
            /*获取失败,直接返回失败*/
            flag = FLAG_SET;
        }

        /*输出查询数量*/
        (*acNum) = tempAcNum;

        if (FLAG_SET == flag)
        {
            retVal = RETURN_ERROR;
        } 
        else
        {
            retVal = RETURN_SUCCESS;
        }
    } 
    else
    {
        retVal = RETURN_ERROR;
    }
	
	return retVal;
}

/*
* 功能描述： 列车闯信号判断
* 参数说明： 无
* 返回值  ： 无     
*/
void TrainCrashSignal(void)
{
	UINT8_S trainCycle = DEFAULT_ZERO;
	UINT16_S tempTrainId = DEFAULT_ZERO;
	UINT16_S tempTrainLink = DEFAULT_ZERO;
	UINT32_S tempTrainOffset = DEFAULT_ZERO;
	TrainSafeLocStruct tempTrainSafeStru;
	UINT8_S tempDirection = DEFAULT_ZERO;
	UINT16_S tempFrontSignalId = DEFAULT_ZERO;
	UINT16_S tempSignalLink = DEFAULT_ZERO;
	UINT32_S tempSignalOffset = DEFAULT_ZERO;
	UINT16_S returnValue = DEFAULT_ZERO;
	UINT16_S tempAcAfterSignalId = DEFAULT_ZERO;
	UINT16_S trainFrontSignalId = DEFAULT_ZERO;
	UINT16_S trainHeadAC = DEFAULT_ZERO;
    UINT16_S acBelongZcId = DEFAULT_ZERO;
	UINT16_S localZcId = DEFAULT_ZERO;
	UINT8_S acBoundaryType = DEFAULT_ZERO;
	UINT8_S signalStatus = DEFAULT_ZERO;
	UINT8_S signalCrashType = DEFAULT_ZERO;
	UINT8_S signalProtectDir = DEFAULT_ZERO;
	UINT8_S trainStatus = DEFAULT_ZERO;
	UINT8_S trainType = DEFAULT_ZERO;
	UINT8_S trainSignalProtection = DEFAULT_ZERO;
	
	localZcId = GetLocalZcId();
	
	for (trainCycle = 0U; trainCycle < GetTrainCurSum(); trainCycle++)
	{		
		tempTrainId = GetTrainIdOfIndex(trainCycle);
		trainHeadAC = GetTrainTrainHeadAC(tempTrainId);
        acBelongZcId = GetAcBelongZcId(trainHeadAC);
		acBoundaryType = GetAcBoundaryType(trainHeadAC);
		
		/*判断列车车头所在计轴是否属于本ZC或共管区域*/
		if ((acBelongZcId == localZcId) ||(2U == acBoundaryType))
		{
			trainStatus = GetTrainStatus(tempTrainId);
			trainType = GetTrainType(tempTrainId);
			trainSignalProtection = GetTrainSignalProtection(tempTrainId);
			
			if ((TRAIN_MODE_CBTC == trainType) 
				&& (TRAIN_STATE_REVERSE != trainStatus) 
				&& (FLAG_UNSET == trainSignalProtection))
			{
                if (RETURN_SUCCESS == GetTrainSafeLoc(tempTrainId,&tempTrainSafeStru))
                {
                    tempTrainLink = tempTrainSafeStru.TrainHeadLink;
                    tempTrainOffset = tempTrainSafeStru.TrainHeadOffset;

                    tempDirection = GetTrainUnsafeDirection(tempTrainId);

                    /*查询与列车运行方向一致的前方信号机*/
                    if (RETURN_SUCCESS == CheckPointNearestSignalBaseDir(tempDirection,tempTrainLink, tempTrainOffset, &tempFrontSignalId))
                    {
                        trainFrontSignalId = GetTrainFrontSignal(tempTrainId);

                        signalStatus = GetSignalStatus(tempFrontSignalId);
                        signalCrashType = GetSignalCrashType(tempFrontSignalId);
                        signalProtectDir = GetSignalProtectDir(tempFrontSignalId);

                        if (0U == trainFrontSignalId)
                        {
                            /*判断本周期信号机状态*/				
                            if ((0U != tempFrontSignalId) 
                                && (SIGNAL_STATE_STOP == signalStatus) 
                                && (FLAG_SET == signalCrashType)
                                && (tempDirection == signalProtectDir))					
                            {
                                /*当前信号机状态为禁止信号*/
                                SetTrainFrontSignal(tempTrainId,tempFrontSignalId);						
                            }
                            else
                            {
                                /*允许信号，不处理*/
                            }
                        }
                        else
                        {
                            if (tempFrontSignalId == trainFrontSignalId)
                            {
                                if (SIGNAL_STATE_PASS == GetSignalStatus(trainFrontSignalId))
                                {
                                    /*已开放，无需进行闯信号防护*/
                                    SetTrainFrontSignal(tempTrainId,DEFAULT_ZERO);
                                }
                                else
                                {
                                    /*未开放*/
                                }
                            }
                            else/*本周期前方信号机发生变化*/
                            {						
                                /*查询上周期的红灯信号机本周期状态*/
                                if (SIGNAL_STATE_STOP == GetSignalStatus(trainFrontSignalId))
                                {
                                    /*查询列车前方防护信号机的位置*/
                                    tempSignalLink = 0U;
                                    tempSignalOffset = 0U;

                                    if (1U == CheckSignalPostion(GetTrainFrontSignal(tempTrainId), &tempSignalLink, &tempSignalOffset))
                                    {
                                        /*查询两点的先后顺序*/
                                        returnValue = CheckLocRelationBetweenTwoPoints(tempSignalLink, tempSignalOffset, tempTrainLink, tempTrainOffset, tempDirection);

                                        if ((1U == returnValue) || (0U == returnValue))
                                        {
                                            /*说明此时列车车头尚未越过信号机或比较两点先后顺序失败, 无需进行闯信号判断*/
                                        }
                                        else
                                        {
                                            /*说明此时列车车头安全位置已越过信号机*/
                                            /*查询信号后方第一个计轴区段*/
                                            if (1U == CheckFirstAcOfSignal(trainFrontSignalId,&tempAcAfterSignalId))
                                            {
                                                if (0U != tempAcAfterSignalId)
                                                {
                                                    if (AC_FREE_STATUS == GetAcStatusNow(tempAcAfterSignalId))/*判断本计轴是否为空闲*/
                                                    {
                                                        /*只是列车包络越过信号机，不判闯信号*/
                                                    }
                                                    else
                                                    {
                                                        /*说明此时列车已经闯入信号机内方的第一个计轴区段，判断该列车闯信号*/	
                                                        /*增加闯信号时候的方向防护*/
                                                        if(tempDirection == GetSignalProtectDir(trainFrontSignalId))
                                                        {
                                                            SetTrainSignalProtection(tempTrainId,FLAG_SET);
                                                        }
                                                        else
                                                        {
                                                            /*不处理*/
                                                        }

                                                        LogPrintf(1U,"429 429 trainDir=%d,signalProDir=%d!\n",tempDirection, GetSignalProtectDir(trainFrontSignalId));
                                                    }
                                                }
                                                else
                                                {
                                                    /*失败，认为列车闯信号*/
                                                    SetTrainSignalProtection(tempTrainId,FLAG_SET);
                                                    LogPrintf(1U,"436 436 !\n");
                                                }
                                            }								
                                        }
                                    }							
                                }
                                else
                                {
                                    /*为了解决闯红灯现象,由GetTrainSignalProtection变为GetSignalCrashType*/
                                    /*判断本周期列车前方信号机状态*/
                                    if ((0U != tempFrontSignalId) 
                                        && (SIGNAL_STATE_STOP == signalStatus) 
                                        && (FLAG_SET == signalCrashType)
                                        && (tempDirection == signalProtectDir))
                                    {
                                        /*说明该信号机当前状态为禁止信号，将该信号机设置为列车前方需要防护的信号机*/
                                        SetTrainFrontSignal(tempTrainId,tempFrontSignalId);
                                    }
                                    else
                                    {
                                        /*将列车前方防护信号机清空*/
                                        SetTrainFrontSignal(tempTrainId,0U);
                                    }							
                                }						
                            }
                        }
                    }                                    
                }				
			}
			else
			{
				/*不符合条件，不处理*/
				/* LogPrintf(1U,"3.29-453:SID=%d,Status=%d\n",GetTrainFrontSignal(tempTrainId), GetTrainStatus(tempTrainId)); */
				
				/*,为了解决在郭公庄无人折返的时候闯信号机现象*/
				/*如果列车处于折返状态,且已经存在有需要防护的信号机时候,将这个信号机设置为不需要防护*/
				if(TRAIN_STATE_REVERSE == trainStatus)
				{
					if(DEFAULT_ZERO != GetTrainFrontSignal(tempTrainId))
					{
						/*将列车前方防护信号机清空*/
						SetTrainFrontSignal(tempTrainId,0U);
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
			/*不在本ZC管辖范围，不处理*/
		}
		
		if (FLAG_SET == GetTrainSignalProtection(tempTrainId))
		{
			LogPrintf(1U,"461:cross red light %d,%d!\n",tempFrontSignalId,trainFrontSignalId);
			SetTrainToModeToRM0(tempTrainId);
			SetTrainSignalProtection(tempTrainId,FLAG_UNSET);
			SetTrainFrontSignal(tempTrainId,0U);
			LogPrintf(1u,"%d-B8\n",tempTrainId);
		}
	}
}

/*
* 功能描述： 处理列车跨压信号机状态
* 参数说明： 无
* 返回值  ： 无      
*/
void TrainAcrossSingalManager(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S signalId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetSignalSum();cycle++)
	{
		signalId = GetSignalId(cycle);

		if (FLAG_SET == GetSignalCrossType(signalId))
		{
			JudgeTrainAcrossOfSingalSignal(signalId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 单个列车跨压信号机状态处理
* 参数说明： UINT16 signalId,信号机Id
* 返回值  ： 0: 处理失败
*			 1: 处理成功      
*/
UINT8_S JudgeTrainAcrossOfSingalSignal(const UINT16_S signalId)
{
	UINT8_S trainCycle = DEFAULT_ZERO;
	UINT16_S tempTrainId = DEFAULT_ZERO;
	TrainSafeLocStruct trainSafeLocStru;
	UINT8_S trainDir = DEFAULT_ZERO;
	UINT16_S tempHeadLink = DEFAULT_ZERO;
	UINT32_S tempHeadOffset = DEFAULT_ZERO;
	UINT16_S tempObsLink = DEFAULT_ZERO;
	UINT32_S tempObsOffset = DEFAULT_ZERO;
	UINT16_S tempACAfterSignalID = DEFAULT_ZERO;
	UINT16_S errorSwitchId = DEFAULT_ZERO;
	UINT8_S returnValue = DEFAULT_ZERO;
	UINT32_S disOfTrainAcross = DEFAULT_ZERO;
	UINT8_S safeLocRtn = RETURN_ERROR;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT8_S signalProtectDir = DEFAULT_ZERO;
    UINT8_S needJudgeFlag = DEFAULT_ZERO;
	UINT8_S tHeadAndSigLoc = DEFAULT_ZERO;  /* 列车车头和信号机位置关系 */
	UINT8_S tTailAndSigLoc = DEFAULT_ZERO;  /* 列车车尾和信号机位置关系 */
	UINT16_S trainLength = DEFAULT_ZERO;    /* 列车长度 */
	UINT16_S trainAcrossSignalDis = DEFAULT_ZERO;  /* 列车跨压信号距离 */
	
	/*查询获得信号机的位置*/
	if (1U == CheckSignalPostion(signalId,&tempObsLink,&tempObsOffset))
	{
        /* 获取列车跨压信号距离 */
        trainAcrossSignalDis = GetTrainAcrossSignalDis();

        for (trainCycle = 0U; trainCycle < GetTrainCurSum(); trainCycle++)
        {
            tempTrainId = GetTrainIdOfIndex(trainCycle);

            /*计算跨压判断基准点所在的link和offset*/
            safeLocRtn = GetTrainSafeLoc(tempTrainId, &trainSafeLocStru);
            trainDir = GetTrainUnsafeDirection(tempTrainId);
            trainType = GetTrainType(tempTrainId);

            /* 信号机防护方向 */
            signalProtectDir = GetSignalProtectDir(signalId);

            /*判断本列车是否为CBTC级别的列车*/        
            if (((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType))
                && (signalProtectDir == trainDir))
            {
                /*判断该信号机是否具备某个列车跨压前提条件*/
                needJudgeFlag = JudgeTrainNeedSingalLoc(signalId,tempTrainId);

                if ((RETURN_SUCCESS == safeLocRtn) && (RETURN_SUCCESS == needJudgeFlag))
                {
                    /* 获取列车安全、非安全位置成功且需要判断跨压 */
                    trainLength = GetTrainLength(tempTrainId);

                    disOfTrainAcross = ((UINT32_S)trainLength) - ((UINT32_S)trainAcrossSignalDis);

                    if (3U == CheckNextPointOnDistance(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,
                        trainDir,disOfTrainAcross,&tempHeadLink,&tempHeadOffset,&errorSwitchId))
                    {
                        tHeadAndSigLoc = CheckLocRelationBetweenTwoPoints(tempHeadLink,tempHeadOffset,tempObsLink,tempObsOffset,trainDir);
                        tTailAndSigLoc = CheckLocRelationBetweenTwoPoints(tempObsLink,tempObsOffset,trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,trainDir);

                        /* 信号机在列车车头和车尾中间 */
                        if ((0x01U == tHeadAndSigLoc) && (0x01U == tTailAndSigLoc))
                        {
                            /*查询信号机内方第一个计轴区段ID*/
                            if (1U == CheckFirstAcOfSignal(signalId,&tempACAfterSignalID))
                            {
                                /*LogPrintf(1U,"12.003 acId=%d,acState=%d\n",tempACAfterSignalID,GetAcStatusNow(tempACAfterSignalID));*/

                                if (DEFAULT_ZERO != tempACAfterSignalID)
                                {
                                    if (AC_OCC_STATUS == GetAcStatusNow(tempACAfterSignalID))
                                    {
                                        /*说明该信号机处于跨压状态*/
                                        returnValue = RETURN_SUCCESS;
                                        break;
                                    }
                                    else
                                    {
                                        /*未跨压，继续遍历其它车*/
                                        returnValue = RETURN_ERROR;
                                    }
                                }
                                else
                                {
                                    /*未跨压，继续遍历其它车*/
                                    returnValue = RETURN_ERROR;
                                }
                            }
                            else
                            {
                                /* 查询信号机内方第1计轴区段失败 */
                            }

                        }
                        else
                        {
                            /*未跨压，继续遍历其它车*/
                            returnValue = RETURN_ERROR;
                        }
                    }                
                }
                else
                {
                    /*说明本列车不是CBTC级别的列车，无需判断跨压信号机*/
                    returnValue = RETURN_ERROR;
                }
            } 
            else
            {
                /*说明本列车不是CBTC级别的列车，无需判断跨压信号机*/
                returnValue = RETURN_ERROR;
            }
        }
	}
	
	if (RETURN_SUCCESS == returnValue)
	{
		SetSignalCrossStatus(signalId,SIGNAL_TRAIN_ALREADY_CROSS);
	}
	else
	{
		SetSignalCrossStatus(signalId,SIGNAL_TRAIN_NOT_CROSS);
	}
	
	return returnValue;
}

/*
* 功能描述： 判断列车位置是否满足该信号机的待判跨压
* 参数说明： UINT16 signalId,信号机Id
*            const UINT8_S trainId,列车Id
* 返回值  ： 0: 处理失败
*			 1: 处理成功      
*/
UINT8_S JudgeTrainNeedSingalLoc(const UINT16_S signalId, const UINT16_S trainId)
{
	TrainSafeLocStruct tempTrainSafeLocStru;
	UINT8_S trainDir = DEFAULT_ZERO;
	UINT8_S locRtn = DEFAULT_ZERO;
	UINT16_S tempObsLink = DEFAULT_ZERO;
	UINT32_S tempObsOffset = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT16_S linkIdList[5];
	UINT16_S linkNum = DEFAULT_ZERO;
	UINT8_S cycle = 0U;
	UINT16_S checkLinkId = DEFAULT_ZERO;
	UINT16_S nextLinkId = DEFAULT_ZERO;
    UINT8_S rtnCheckLink = 0U;

	/*初始化*/
	MemorySet(linkIdList,((UINT32_S)(sizeof(UINT16_S)*5U)),DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*5U)));

	/*查询获得信号机的位置*/
    if (1U == CheckSignalPostion(signalId,&tempObsLink,&tempObsOffset))
    {
        /*计算跨压判断基准点所在的link和offset*/
        locRtn = GetTrainUnSafeLoc(trainId, &tempTrainSafeLocStru);
        trainDir = GetTrainUnsafeDirection(trainId);

        if (RETURN_SUCCESS == locRtn)
        {
            if (((tempTrainSafeLocStru.TrainHeadLink == tempObsLink) || (tempTrainSafeLocStru.TrainTailLink == tempObsLink)))
            {
                rtnValue = RETURN_SUCCESS;
            } 
            else
            {
                /*向前后各查询2个LINK*/
                checkLinkId = tempObsLink;

                for (cycle = 0U; cycle < 2U; cycle++)
                {
                    rtnCheckLink = CheckFrontLink(LINESEG_CONVER_DIR,checkLinkId,&nextLinkId);

                    if ((1U == rtnCheckLink) && (DEFAULT_ZERO != nextLinkId))
                    {
                        linkIdList[linkNum] = nextLinkId;
                        linkNum = linkNum + 1U;
                        checkLinkId = nextLinkId;
                    } 
                    else
                    {
                        break;
                    }
                }

                checkLinkId = tempObsLink;
                for (cycle = 0U; cycle < 2U; cycle++)
                {
                    rtnCheckLink = CheckFrontLink(LINESEG_SAME_DIR,checkLinkId,&nextLinkId);

                    if ((RETURN_SUCCESS == rtnCheckLink) && (DEFAULT_ZERO != nextLinkId))
                    {
                        linkIdList[linkNum] = nextLinkId;
                        linkNum = linkNum + 1U;
                        checkLinkId = nextLinkId;
                    } 
                    else
                    {
                        break;
                    }
                }

                for (cycle = DEFAULT_ZERO;cycle < linkNum;cycle++)
                {
                    if ((tempTrainSafeLocStru.TrainHeadLink == linkIdList[cycle]) || (tempTrainSafeLocStru.TrainTailLink == linkIdList[cycle]))
                    {
                        rtnValue = RETURN_SUCCESS;
                        break;
                    } 
                    else
                    {
                        /*不处理*/
                    }
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
        /* 查询信号机位置失败,返回失败 */
        rtnValue = RETURN_ERROR;
    }

	return rtnValue;
}
