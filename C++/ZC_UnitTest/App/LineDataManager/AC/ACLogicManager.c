/************************************************************************
*
* 文件名   ：  ACLogicManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  计轴区段的逻辑处理
* 备  注   ：  无
*
************************************************************************/

#include "ACLogicManager.h"
#include "../../SysDataManager/SysDefine.h"
#include "ACStatusData.h"
#include "ACConfigData.h"
#include "../../TrainManager/Train/TrainStatusData.h"
#include "../../TrainManager/Train/TrainLogicManager.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Common/MemSet.h"
#include "../Switch/SwitchStatusData.h"
#include "../../MaintainManager/MaintainManager.h"

/*
* 功能描述： 计算前方计轴区段内的列车运行方向（以当前计轴为参考单位）
* 参数说明： const UINT8 dirFlag,方向标记(0x55:前方计轴,0xaa:后方计轴)
*            const UINT16_S acId,当前计轴区段(预留)
*            const UINT16_S otherAcId
*            const UINT8_S dir,方向信息
* 返回值  ： 1：远离参考计轴
*            2：接近参考计轴
*            3：无方向
*            0：计算失败
*/
UINT8_S CalculateTrainDirInOtherAc(const UINT8_S dirFlag,const UINT16_S acId,const UINT16_S otherAcId,const UINT8_S dir)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S trainNumInAc = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S acTrainSeqIdBuff[SIZE_MAX_ROUTENUM] = {DEFAULT_ZERO};
    UINT8_S acDir = DEFAULT_ZERO;
    UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S cmpDir = DEFAULT_ZERO;
    UINT8_S acArbFlag = DEFAULT_ZERO;
	UINT8_S acArbRedundance = DEFAULT_ZERO;
	UINT8_S acUtRedundance = DEFAULT_ZERO;
	
    MemorySet(&acTrainSeqIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)));
    MemorySet(&trainSequenceBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
        0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));

    /*获取计轴区段内列车数量*/
    trainNumInAc = GetAcTrainOfAcNum(otherAcId);

    if (DEFAULT_ZERO == trainNumInAc)
    {
        /*计轴区段内无列车*/
        if (AC_FREE_STATUS == GetAcStatusNow(otherAcId))
        {
            if (AC_LOCK_STATUS == GetAcBelock(otherAcId))
            {
                acDir = GetAcDirection(otherAcId);
            } 
            else
            {
                acDir = DEFAULT_ZERO;
            }
        } 
        else
        {
			acArbFlag = GetAcArbFlag(otherAcId);
			acArbRedundance = GetAcArbRedundance(otherAcId);
			acUtRedundance = GetAcUtRedundance(otherAcId);
			
            if ((AC_ARB_OCC_STATUS == acArbFlag)
                || (0U < acArbRedundance)
			    || (0U < acUtRedundance ))
            {
                acDir = DEFAULT_ZERO;
            } 
            else
            {
                /* 2017.6.2,暂时将已UT无列车的情况下的计轴方向设置为0,已排除联锁与列车的输入延时的情况  
                if (AC_UT_OCC_STATUS == GetAcUtFlag(otherAcId))
                {
                    acDir = DEFAULT_ZERO;
                } 
                else
                {
                    acDir = DEFAULT_0XFF;
                }  */           
            }
        }
    } 
    else
    {
        /*获取列车序列*/
        if (RETURN_SUCCESS == GetAcTrainSequenceBuff(otherAcId,SIZE_MAX_TRAINOFAC,trainSequenceBuff))
        {
            for (cycle = DEFAULT_ZERO;cycle < trainNumInAc;cycle++)
            {
                trainDir = GetTrainUnsafeDirection(trainSequenceBuff[cycle]);

                if (DEFAULT_ZERO == cycle)
                {
                    if (1U == trainNumInAc)
                    {
                        acDir = trainDir;
                    } 
                    else
                    {
                        cmpDir = trainDir;
                    }
                } 
                else
                {
                    if (cmpDir == trainDir)
                    {
                        acDir = cmpDir;
                    } 
                    else
                    {
                        acDir = DEFAULT_0XFF;
                        break;
                    }
                }
            }
        }      
    }

    switch (acDir)
    {
    case TRAIN_UNSAFE_DIR_UP:
    case TRAIN_UNSAFE_DIR_DOWN:

        if (FLAG_SET == dirFlag)
        {
            /*前方计轴*/
            if (dir == acDir)
            {
                rtnValue = AC_DIR_FARAWAY;
            } 
            else
            {
                rtnValue = AC_DIR_CLOSED;
            }
        } 
        else if (FLAG_UNSET == dirFlag)
        {
            if (dir == acDir)
            {
                rtnValue = AC_DIR_CLOSED;
            } 
            else
            {
                rtnValue = AC_DIR_FARAWAY;
            }
        } 
        else
        {
            rtnValue = DEFAULT_ZERO;
        }

        break;

    case DEFAULT_ZERO:
        rtnValue = AC_DIR_DEFAULT;
        break;

    case DEFAULT_0XFF:
        rtnValue = DEFAULT_ZERO;
        break;

    default:
        rtnValue = DEFAULT_ZERO;
        break;
    }

    return rtnValue;
}

/*
* 功能描述： 计轴区段内列车排序
* 参数说明：无    
* 返回值  ：无
*/
void CalculateTrainOrderInAc(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnSafeLocStru;
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainOccAcNum = DEFAULT_ZERO;
    UINT16_S trainOccAcIdBuff[ZC_TWO_POINT_AC_NUM_MAX] = {DEFAULT_ZERO};
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT8_S tempFlag = DEFAULT_ZERO;
    UINT8_S cycleAc = DEFAULT_ZERO;

    MemorySet(&trainOccAcIdBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)),
                0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)));

    /*先清空所有计轴内的列车序列*/
    ClearTrainOrderInAc();

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        trainId = GetTrainIdOfIndex(cycle);
        trainDir = GetTrainUnsafeDirection(trainId);

        /*if (RETURN_SUCCESS == JudgeTrainNeedCalculate(trainId))*/
        if (RETURN_SUCCESS == JudgeTrainNeedCalculate(trainId) 
            || (DEFAULT_ZERO != GetTrainStatus(trainId)))
        {
            /*获取列车的位置信息*/
            if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
            {
                if (RETURN_ERROR == CheckAcOrderBetweenTwoPoints(trainSafeLocStru.TrainTailLink,
                    trainSafeLocStru.TrainHeadLink,trainDir,&trainOccAcNum,trainOccAcIdBuff))
                {
                    /*获取列车的非安全位置*/
                    if (RETURN_SUCCESS == GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru))
                    {
                        /*使用非安全位置查询*/
                        if (RETURN_ERROR == CheckAcOrderBetweenTwoPoints(trainUnSafeLocStru.TrainTailLink,
                            trainUnSafeLocStru.TrainHeadLink,trainDir,&trainOccAcNum,trainOccAcIdBuff))
                        {
                            /*查询失败,列车紧急制动*/
                            SetTrainToModeToRM0(trainId);
                            LogPrintf(1u,"%d-B71\n",trainId);
                        } 
                        else
                        {
                            /*更新列车占压的计轴区段信息*/
                            tempFlag = FLAG_SET;
                        }
                    }                                      
                } 
                else
                {
                    /*更新列车占压的计轴区段信息*/
                    tempFlag = FLAG_SET;
                }
            }
            else
            {
                /* 获取安全位置结构体失败,先不处理*/
            }
            

            if (FLAG_SET == tempFlag)
            {
                for (cycleAc = DEFAULT_ZERO;cycleAc < trainOccAcNum;cycleAc++)
                {
                    if (GetAcBelongZcId(trainOccAcIdBuff[cycleAc]) == GetLocalZcId())
                    {
                        CalculateTrainInSingleAc(trainId,trainOccAcIdBuff[cycleAc]);
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
            /*不排序*/
        }
    }
}

/*
* 功能描述： 单个计轴区段内列车排序
* 参数说明：const UINT16 trainId,带添加列车ID
*           const UINT16_S acId,带添加计轴区段 
* 返回值  ：无
*/
void CalculateTrainInSingleAc(const UINT16_S trainId,const UINT16_S acId)
{
    UINT8_S trainNumInAc = DEFAULT_ZERO;
    UINT16_S trainIdSeqBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};
    UINT8_S cycle = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnSafeLocStru;
    TrainSafeLocStruct acTrainUnSafeLocStru;
    UINT8_S checkRtn = DEFAULT_ZERO;
    UINT8_S insertIndex = DEFAULT_0XFF;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S getCurFlag = RETURN_ERROR;
	UINT8_S getOtherFlag = RETURN_ERROR;
	
    MemorySet(&trainIdSeqBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));

    trainNumInAc = GetAcTrainOfAcNum(acId);

    if (DEFAULT_ZERO == trainNumInAc)
    {
        trainIdSeqBuff[trainNumInAc] = trainId;
        trainNumInAc++;

        /*计轴当前无列车,直接添加列车到序列中*/
        SetAcTrainSequenceBuff(acId,trainIdSeqBuff,trainNumInAc);
    } 
    else
    {
        /*获取列车序列*/
        if (RETURN_SUCCESS == GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainIdSeqBuff))
        {
            /*判断当前列车应该插入的位置*/
            for (cycle = DEFAULT_ZERO;cycle < trainNumInAc;cycle++)
            {
                /*判断待添加列车的车头和已有列车车头的先后关系*/
				getCurFlag = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);
				getOtherFlag = GetTrainUnSafeLoc(trainIdSeqBuff[cycle],&acTrainUnSafeLocStru);
				
                if ((RETURN_SUCCESS == getCurFlag)
                    && (RETURN_SUCCESS == getOtherFlag))
                {
                    checkRtn = CheckLocRelationBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,trainUnSafeLocStru.TrainHeadOffset,
                        acTrainUnSafeLocStru.TrainHeadLink,acTrainUnSafeLocStru.TrainHeadOffset,GetTrainUnsafeDirection(trainIdSeqBuff[cycle]));

                    switch (checkRtn)
                    {
                    case 0x01U:
                    case 0x03U:
                        /*插入到前方*/
                        insertIndex = cycle;
                        breakFlag = FLAG_SET;
                        break;
                    case 0x02U:
                        /*插入后方*/
                        insertIndex = cycle+1U;
                        break;
                    default:
                        /*紧急制动,为列车添加后端？？？？？？？？？？？？？*/
                        SetTrainToModeToRM0(trainId);
						LogPrintf(1u,"%d-B3\n",trainId);
                        break;
                    }
                }
                else
                {
                    /*紧急制动,为列车添加后端？？？？？？？？？？？？？*/
                    SetTrainToModeToRM0(trainId);
					LogPrintf(1u,"%d-B4\n",trainId);
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

            /*根据插入位置插入*/
            if (DEFAULT_0XFF != insertIndex)
            {
                JudgeInsertTrainOrderInAc(trainId,acId,insertIndex);
            } 
            else
            {
                /*不处理*/
            }		
        } 
        else
        {
            /*紧急制动,为列车添加后端？？？？？？？？？？？？？*/
            SetTrainToModeToRM0(trainId);
			LogPrintf(1u,"%d-B5\n",trainId);
        }
    }
}

/*
* 功能描述： 处理插入列车操作排序
* 参数说明：const UINT16 trainId,带添加列车ID
*           const UINT16_S acId,带添加计轴区段   
*           const UINT8_S insertIndex,插入的位置
* 返回值  ：无
*/
void JudgeInsertTrainOrderInAc(const UINT16_S trainId,const UINT16_S acId,const UINT8_S insertIndex)
{
    UINT8_S trainNumInAc = DEFAULT_ZERO;
    UINT16_S trainIdSeqBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};
    UINT16_S insertTrainIdSeqBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S getFlag = RETURN_ERROR;

    MemorySet(&trainIdSeqBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));
    MemorySet(&insertTrainIdSeqBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));

    trainNumInAc = GetAcTrainOfAcNum(acId);
    getFlag = GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainIdSeqBuff);

    /*PBW 2016.9.19 */
    /*获取列车序列*/
    if ((RETURN_SUCCESS == getFlag)
        && (trainNumInAc < SIZE_MAX_TRAINOFAC))
    {
        for (cycle = DEFAULT_ZERO;cycle < insertIndex;cycle++)
        {
            insertTrainIdSeqBuff[cycle] = trainIdSeqBuff[cycle];
        }

        /*插入列车*/
        insertTrainIdSeqBuff[insertIndex] = trainId;

        /*加入后方列车*/
        for (cycle = insertIndex;cycle < trainNumInAc;cycle++)
        {
            insertTrainIdSeqBuff[cycle+1U] = trainIdSeqBuff[cycle];
        }

        /*写入新的列车序列*/
        SetAcTrainSequenceBuff(acId,insertTrainIdSeqBuff,(trainNumInAc+1U));
    }
    else
    {
        /*不处理*/
    }
}

/*
* 功能描述： 计算最后一列进入计轴区段的列车信息
* 参数说明：无    
* 返回值  ：无
*/
void CalculateLastTrainToAc(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S lastTrainNumInAc = DEFAULT_ZERO;
    UINT16_S lastTrainOrderBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};
    UINT8_S nowTrainNumInAc = DEFAULT_ZERO;
    UINT16_S nowTrainOrderBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};
    UINT16_S acId = DEFAULT_ZERO;

    MemorySet(&lastTrainOrderBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));
    MemorySet(&nowTrainOrderBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));

    for (cycle = DEFAULT_ZERO;cycle < GetAcCurSum();cycle++)
    {
        acId = GetAcId((UINT16_S)cycle);

        if (GetAcBelongZcId(acId) == GetLocalZcId())
        {
            /*获取计轴上周期列车序列信息*/
            lastTrainNumInAc = GetLastTrainOfAcNum(acId);
            GetLastTrainSequenceBuf(acId,SIZE_MAX_TRAINOFAC,lastTrainOrderBuff);

            /*获取计轴本周期列车序列信息*/
            nowTrainNumInAc = GetAcTrainOfAcNum(acId);
            GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,nowTrainOrderBuff);

            if ((DEFAULT_ZERO == lastTrainNumInAc)
                && (DEFAULT_ZERO == nowTrainNumInAc))
            {
                /*设置为零*/
                SetAcLastTrain(acId,DEFAULT_ZERO);
            } 
            else
            {
                if (DEFAULT_ZERO == nowTrainNumInAc)
                {
                    /*维持上周期的状态*/
                } 
                else
                {
                    /*设置本周期的最后一列车为最后进入该计轴的列车*/
                    SetAcLastTrain(acId,nowTrainOrderBuff[nowTrainNumInAc - 1U]);
                }
            }

            /*更新上周期列车状态为本周期的状态*/
            SetLastTrainOfAcNum(acId,nowTrainNumInAc);
            SetLastTrainSequenceBuf(acId,nowTrainOrderBuff,nowTrainNumInAc);
        }
        else
        {
            /*不处理*/
        }
    }
}

/*
* 功能描述： 判断计轴区段是否满足纯非通信列车占用状态
* 参数说明：无    
* 返回值  ：无
*/
void ProcessAcUnCommTrainOccState(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S nowTrainNumInAc = DEFAULT_ZERO;
    UINT16_S nowTrainOrderBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};
    UINT16_S acId = DEFAULT_ZERO;
    UINT8_S acUtRedundance = DEFAULT_ZERO;
    UINT16_S frontAcId = DEFAULT_ZERO;
    UINT16_S rearAcId = DEFAULT_ZERO;

    MemorySet(&nowTrainOrderBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));

    for (cycle = DEFAULT_ZERO;cycle < GetAcCurSum();cycle++)
    {
        acId = GetAcId((UINT16_S)cycle);

        if (GetAcBelongZcId(acId) == GetLocalZcId())
        {
            /*获取计轴本周期列车序列信息*/
            nowTrainNumInAc = GetAcTrainOfAcNum(acId);
            GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,nowTrainOrderBuff);

            if (DEFAULT_ZERO == nowTrainNumInAc)
            {
                switch (GetAcStatusNow(acId))
                {
                case AC_FREE_STATUS:
                    /*当前计轴已无车,清除计轴区段非通信列车占用状态*/
                    SetAcUtFlag(acId,AC_UT_FREE_STATUS);
                    SetAcUtRedundance(acId,DEFAULT_ZERO);
                    break;
                case AC_OCC_STATUS:

                    if (AC_UT_OCC_STATUS != GetAcUtFlag(acId))
                    {
                        acUtRedundance = GetAcUtRedundance(acId);
                        if (DEFAULT_ZERO != acUtRedundance)
                        {
                            if (acUtRedundance < GetSectionRedundantCycle())
                            {
                                SetAcUtFlag(acId,AC_UT_FREE_STATUS);
                                SetAcUtRedundance(acId,(acUtRedundance+1U));
                            } 
                            else
                            {
                                /*冗余完成,设置为非通信列车占用*/
                                SetAcUtFlag(acId,AC_UT_OCC_STATUS);
                                SetAcUtRedundance(acId,DEFAULT_ZERO);
                            }
                        } 
                        else
                        {
                            /*根据当前计轴区段前后方计轴判断该计轴区段的占用状态*/
                            if (RETURN_SUCCESS == CheckFrontACStatus(acId,AC_DIR_UP_STATUS,&frontAcId))
                            {
                                if (RETURN_SUCCESS == JudgeAcUnCommTrainOccStateByOtherAc(FLAG_SET,acId,frontAcId,AC_DIR_UP_STATUS))
                                {
                                    SetAcUtFlag(acId,AC_UT_OCC_STATUS);
                                    SetAcUtRedundance(acId,DEFAULT_ZERO);
                                } 
                                else
                                {
                                    if (RETURN_SUCCESS == CheckRearACStatus(acId,AC_DIR_UP_STATUS,&rearAcId))
                                    {
                                        if (RETURN_SUCCESS == JudgeAcUnCommTrainOccStateByOtherAc(FLAG_UNSET,acId,rearAcId,AC_DIR_UP_STATUS))
                                        {
                                            SetAcUtFlag(acId,AC_UT_OCC_STATUS);
                                            SetAcUtRedundance(acId,DEFAULT_ZERO);
                                        } 
                                        else
                                        {
                                            /*设置为UT冗余状态*/
                                            SetAcUtFlag(acId,AC_UT_FREE_STATUS);
                                            SetAcUtRedundance(acId,1U);
                                        }
                                    } 
                                    else
                                    {
                                        /*设置为UT冗余状态*/
                                        SetAcUtFlag(acId,AC_UT_FREE_STATUS);
                                        SetAcUtRedundance(acId,1U);
                                    }
                                }
                            } 
                            else
                            {
                                /*设置为UT冗余状态*/
                                SetAcUtFlag(acId,AC_UT_FREE_STATUS);
                                SetAcUtRedundance(acId,1U);
                            }
                        }
                    } 
                    else
                    {
                        /*已设置UT占用,不处理*/
                    }
                    break;
                default:
                    break;
                }
            } 
            else
            {
                /*已经有列车序列,清除冗余位*/
                SetAcUtRedundance(acId,DEFAULT_ZERO);
            }
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*
* 功能描述： 根据前方计轴区段信息计算当前计轴区段
*			 是否满足纯非通信列车占用状态
* 参数说明：const UINT8 dirFlag,方向标记(0x55:前方计轴,0xaa:后方计轴)
*           const UINT16_S acId,计轴区段ID   
*           const UINT16_S otherAcId,其他计轴区段ID（前方/后方计轴）
*           const UINT8_S dir,方向信息
* 返回值  ：1:已满足设置非通信列车占用状态
*           0:不满足设置非通信列车占用状态
*/
UINT8_S JudgeAcUnCommTrainOccStateByOtherAc(const UINT8_S dirFlag,const UINT16_S acId,const UINT16_S otherAcId,const UINT8_S dir)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S acDir = DEFAULT_ZERO;
    UINT8_S trainNumInAc = DEFAULT_ZERO;
    UINT16_S trainOrderBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};
    UINT8_S acStatusNow = DEFAULT_ZERO;
	UINT8_S acUtRedundance =DEFAULT_ZERO;
	UINT8_S acArbFlag = DEFAULT_ZERO;
	UINT8_S acArbRedundance = DEFAULT_ZERO;
	
    MemorySet(&trainOrderBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
               0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));

	acStatusNow = GetAcStatusNow(otherAcId);
	acUtRedundance =GetAcUtRedundance(otherAcId);
	acArbFlag = GetAcArbFlag(otherAcId);
	acArbRedundance = GetAcArbRedundance(otherAcId);
	
    if ((AC_FREE_STATUS == acStatusNow)
        || (DEFAULT_ZERO != acUtRedundance)
        || (AC_ARB_OCC_STATUS == acArbFlag)
        || (DEFAULT_ZERO != acArbRedundance))
    {
        /*计轴区段空闲/或者UT冗余/arb/arb冗余,不满足设置非通信列车占用状态*/
        rtnValue = RETURN_ERROR;
    } 
    else
    {
        /*获取计轴状态*/
        if (AC_UT_OCC_STATUS == GetAcUtFlag(otherAcId))
        {
            /*前方非通信列车占用,满足设置非通信列车占用状态*/
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*获取计轴区段列车运行方向*/
            acDir = CalculateTrainDirInOtherAc(dirFlag,acId,otherAcId,dir);

            /*获取其他计轴列车序列信息*/
            trainNumInAc = GetAcTrainOfAcNum(otherAcId);
            GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainOrderBuff);

            if (DEFAULT_ZERO != trainNumInAc)
            {
                switch (acDir)
                {
                case AC_DIR_FARAWAY:
                    if (FLAG_SET == GetTrainSuspectTail(trainOrderBuff[trainNumInAc - 1U]))
                    {
                        /*前方最后一列车后端含有危险区域,满足设置非通信列车占用状态*/
                        rtnValue = RETURN_SUCCESS;
                    } 
                    else
                    {
                        /*不满足设置非通信列车占用状态*/
                        rtnValue = RETURN_ERROR;
                    }
                    break;
                case AC_DIR_CLOSED:
                    if (FLAG_SET == GetTrainSuspectHead(trainOrderBuff[DEFAULT_ZERO]))
                    {
                        /*前方第一列车前端含有危险区域,满足设置非通信列车占用状态*/
                        rtnValue = RETURN_SUCCESS;
                    } 
                    else
                    {
                        /*不满足设置非通信列车占用状态*/
                        rtnValue = RETURN_ERROR;
                    }
                    break;
                default:
                    /*导向安全侧,设置非通信列车占用状态*/
                    rtnValue = RETURN_SUCCESS;
                    break;
                }
            } 
            else
            {
                /*导向安全侧,设置非通信列车占用状态*/
                rtnValue = RETURN_SUCCESS;
            }
        }
    }

    return rtnValue;
}

/*
* 功能描述： 处理单个计轴区段故障信息
* 参数说明： const UINT16 acId  
* 返回值  ： void  
*/
void InitFailureSingleAc(const UINT16_S acId)
{
    UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};

    MemorySet(trainSequenceBuff,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC)),
                DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC)));

    /*设置故障导向安全状态*/
    SetAcDirection(acId,DEFAULT_ZERO);
    SetAcBelock(acId,AC_UNLOCK_STATUS);
    SetAcStatusNow(acId,AC_OCC_STATUS);

    SetAcUtFlag(acId,AC_UT_OCC_STATUS);
    SetAcUtRedundance(acId,DEFAULT_ZERO);
    SetAcArbFlag(acId,AC_ARB_FREE_STATUS);
    SetAcArbRedundance(acId,DEFAULT_ZERO);

    SetAcLastTrain(acId,DEFAULT_ZERO);
    SetAcTrainOfAcNum(acId,DEFAULT_ZERO);
    SetAcTrainSequenceBuff(acId,trainSequenceBuff,DEFAULT_ZERO);
    SetLastTrainOfAcNum(acId,DEFAULT_ZERO);
    SetLastTrainSequenceBuf(acId,trainSequenceBuff,DEFAULT_ZERO);
}

/*
* 功能描述： 处理通信故障Ci对应的计轴区段信息
* 参数说明： const UINT16 ciId，通信CiId    
* 返回值  ： void  
*/
void InitFailureCiAc(const UINT16_S ciId)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetAcCurSum();cycle++)
    {
        acId = GetAcId(cycle);

        if (ciId == GetAcBelongCiId(acId))
        {
            /*设置状态为安全态*/
            InitFailureSingleAc(acId);
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*
* 功能描述： 处理通信故障NZc对应的计轴区段信息
* 参数说明： const UINT16 nZcId,通信ZcId    
* 返回值  ： void  
*/
void InitFailureNZcAc(const UINT16_S nZcId)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT16_S acBelongZcId = DEFAULT_ZERO;
	UINT8_S acBoundaryType = DEFAULT_ZERO;
	
    for (cycle = DEFAULT_ZERO;cycle < GetAcCurSum();cycle++)
    {
        acId = GetAcId(cycle);
        acBelongZcId = GetAcBelongZcId(acId);
		acBoundaryType = GetAcBoundaryType(acId);
		
        if ((nZcId == acBelongZcId)
            && (FLAG_SET == acBoundaryType))
        {
            /*设置状态为安全态*/
            InitFailureSingleAc(acId);
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*
* 功能描述： 判断计轴区段是否有列车停稳
* 参数说明： const UINT16 acId,计轴区段ID    
* 返回值  ： 0:没有列车停稳
*            1:有列车停稳
*/
UINT8_S JudgeAcStopStatus(const UINT16_S acId)
{
    UINT8_S trainNum = DEFAULT_ZERO;
    UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC] ={DEFAULT_ZERO};
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT16_S unsafeTrainHeadAC = DEFAULT_ZERO;
	UINT16_S unsafeTrainTailAC = DEFAULT_ZERO;
	UINT8_S trainStopArea = DEFAULT_ZERO;
	
    MemorySet(&trainSequenceBuff[0],((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC)),
                DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC)));

    /*获取计轴内列车序列*/
    trainNum = GetAcTrainOfAcNum(acId);

    if (RETURN_SUCCESS == GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainSequenceBuff))
    {
        for (cycle = DEFAULT_ZERO;cycle < trainNum;cycle++)
        {
            trainId = trainSequenceBuff[cycle];
            trainType = GetTrainType(trainId);
            unsafeTrainHeadAC = GetTrainUnsafeTrainHeadAC(trainId);
			unsafeTrainTailAC = GetTrainUnsafeTrainTailAC(trainId);
			trainStopArea = GetTrainStopArea(trainId);
			
			/*11.30,dnw,更改为待判计轴需要是列车非安全车头占压的计轴区段*/
            if ((acId == unsafeTrainHeadAC)
                && (FLAG_SET == trainStopArea)
                && ((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType)))
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
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* 功能描述： 清空计轴区段包含的列车序列信息
* 参数说明： 无   
* 返回值  ： 无
*/
void ClearTrainOrderInAc(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};
    UINT16_S localZcId = DEFAULT_ZERO;
	UINT16_S acBelongZcId = DEFAULT_ZERO;
	
    MemorySet(trainSequenceBuff,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC)),
               DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC)));
    
	localZcId = GetLocalZcId();
    for (cycle = DEFAULT_ZERO;cycle < GetAcCurSum();cycle++)
    {
        acId = GetAcId(cycle);
        acBelongZcId = GetAcBelongZcId(acId);
		
        if (localZcId == acBelongZcId)
        {
            /*清空计轴内列车序列*/
            SetAcTrainOfAcNum(acId,DEFAULT_ZERO);
            SetAcTrainSequenceBuff(acId,trainSequenceBuff,DEFAULT_ZERO);
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*
* 功能描述： 判断计轴区段内的道岔是否满足锁闭和位置状态
* 参数说明： const UINT16 acId,计轴区段ID
* 返回值  ： 0:不满足
*            1:满足
*/
UINT8_S JudgeSwitchLockAndPostionInAc(const UINT16_S acId)
{
    UINT8_S switchNumInAc = DEFAULT_ZERO;
    SwitchInAcStruct switchInAcStruBuff[AC_SWITCH_SUM_MAX];
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    MemorySet(&switchInAcStruBuff[0],((UINT32_S)(sizeof(SwitchInAcStruct) * AC_SWITCH_SUM_MAX)),
                0U,((UINT32_S)(sizeof(SwitchInAcStruct) * AC_SWITCH_SUM_MAX)));

    /*获取计轴区段的道岔信息*/
    switchNumInAc = GetAcSwitchNum(acId);

    if (RETURN_SUCCESS == GetAcSwitchInfo(acId,AC_SWITCH_SUM_MAX,switchInAcStruBuff))
    {
        for (cycle = DEFAULT_ZERO;cycle < switchNumInAc;cycle++)
        {
            /*获取道岔的位置状态和计轴需要的状态是否一致*/
            if (switchInAcStruBuff[cycle].SwitchPostion == GetSwitchPosStatus(switchInAcStruBuff[cycle].SwitchId))
            {
                /*不处理*/
            } 
            else
            {
                breakFlag = FLAG_SET;
                break;
            }

            /*获取道岔的锁闭状态是否为锁闭*/			
            if (SWITCH_STATE_LOCK == GetSwitchLock(switchInAcStruBuff[cycle].SwitchId))
            {
                /*不处理*/
            } 
            else
            {
                breakFlag = FLAG_SET;
                break;
            }

        }

        if (FLAG_SET == breakFlag)
        {
            rtnValue = RETURN_ERROR;
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

/*
* 功能描述： 判断计轴区段内的道岔是否满足位置状态
* 参数说明： const UINT16 acId,计轴区段ID
*            UINT16_S outErrorSwitchId[AC_SWITCH_SUM_MAX],不满足条件的道岔数组
*            ,UINT8_S *outErrorSwitchNum，不满足条件的道岔数量
* 返回值  ： 0:不满足（其他原因）
*            1:不满足（道岔原因）
*            2:满足
*/
UINT8_S JudgeSwitchPostionInAc(const UINT16_S acId,UINT16_S outErrorSwitchId[AC_SWITCH_SUM_MAX],UINT8_S *outErrorSwitchNum)
{
	UINT8_S switchNumInAc = DEFAULT_ZERO;
	SwitchInAcStruct switchInAcStruBuff[AC_SWITCH_SUM_MAX];
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	MemorySet(&switchInAcStruBuff[0],((UINT32_S)(sizeof(SwitchInAcStruct) * AC_SWITCH_SUM_MAX)),
		0U,((UINT32_S)(sizeof(SwitchInAcStruct) * AC_SWITCH_SUM_MAX)));

	/*获取计轴区段的道岔信息*/
	(*outErrorSwitchNum) = DEFAULT_ZERO;
	switchNumInAc = GetAcSwitchNum(acId);

	if (RETURN_SUCCESS == GetAcSwitchInfo(acId,AC_SWITCH_SUM_MAX,switchInAcStruBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < switchNumInAc;cycle++)
		{
			/*获取道岔的位置状态和计轴需要的状态是否一致*/
			if (switchInAcStruBuff[cycle].SwitchPostion == GetSwitchPosStatus(switchInAcStruBuff[cycle].SwitchId))
			{
				/*不处理*/
			} 
			else
			{
				outErrorSwitchId[(*outErrorSwitchNum)] = switchInAcStruBuff[cycle].SwitchId;
				(*outErrorSwitchNum)++;
			}

		}

		if (0u == (*outErrorSwitchNum))
		{
			rtnValue = 2u;
		} 
		else
		{
			rtnValue = 1u;
		}
	} 
	else
	{
		rtnValue = 0u;
	}

	return rtnValue;
}


/*
* 功能描述： 若待判计轴已经判断为UT，当列车已经清扫该计轴后，将其转换为ARB
* 参数说明： 无
* 返回值  ： 无
*/
void ConvertAxleUtToArb(void)
{
    UINT16_S acCycle = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT8_S acUtFlag = DEFAULT_ZERO;
    UINT8_S acCleanFlag = DEFAULT_ZERO;
    UINT8_S acAttribute = DEFAULT_ZERO;
    UINT8_S adjacentArbCondition = DEFAULT_ZERO;

    /*遍历本ZC计轴*/
    for (acCycle = DEFAULT_ZERO;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        /*获取AC的UT标志*/
        acUtFlag = GetAcUtFlag(acId);

        /*判断计轴是否属于本ZC*/
        acAttribute = CheckAcAttribute(acId);

        if ((FLAG_SET == acAttribute) 
            && (FLAG_SET == acUtFlag))
        {
            /*获取列车已清扫标志*/
            acCleanFlag = GetAcTrainCleanFlag(acId);

            /*判断待判计轴相邻计轴情况*/
            adjacentArbCondition = CheckAdjacentAxleArbCondition(acId);

            if ((CLEAN_STATUS_ALL_OUT == acCleanFlag) 
                && (RETURN_SUCCESS == adjacentArbCondition))
            {
                /*满足以上条件，计轴判断为ARB*/
                SetAcArbFlag(acId,FLAG_SET);
                SetAcUtFlag(acId,FLAG_UNSET);
                SetAcUtRedundance(acId,DEFAULT_ZERO);
            }
            else
            {
                /*计轴维持原状*/
            }
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*
* 功能描述： 若待判计轴已经判断为ARB，当计轴占用状态变为空闲后，清除其ARB标志
* 参数说明： 无
* 返回值  ： 无
*/
void ConvertAxleArbToFree(void)
{
    UINT16_S acCycle = DEFAULT_ZERO;
    UINT8_S acArbFlag = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT8_S acStatus = DEFAULT_ZERO;
    UINT8_S acAttribute = DEFAULT_ZERO;

    /*遍历本ZC计轴*/
    for (acCycle=DEFAULT_ZERO;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        /*获取AC ARB标志*/
        acArbFlag = GetAcArbFlag(acId);

        /*获取计轴占用状态*/
        acStatus = GetAcStatusNow(acId);

        /*判断计轴是否属于本ZC*/
        acAttribute = CheckAcAttribute(acId);

        if ((FLAG_SET == acAttribute) && (AC_ARB_OCC_STATUS == acArbFlag) && (AC_FREE_STATUS == acStatus))
        {
            /*说明ARB计轴已经空闲，清除ARB标志*/
            SetAcArbFlag(acId,FLAG_UNSET);
        }
        else
        {
            /*不作处理*/
        }
    }
}

/*
* 功能描述： 判断计轴是否属于本ZC
* 参数说明： const UINT16 acId
* 返回值  ： RETURN_ERROR：失败
*			 FLAG_SET：属于本ZC
*			 FLAG_UNSET:不属于本ZC
*/
UINT8_S CheckAcAttribute(const UINT16_S acId)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S zcId = DEFAULT_ZERO;
    UINT16_S selfZcId = DEFAULT_ZERO;

    /*获取计轴所属ZC*/
    zcId = GetAcBelongZcId(acId);
    selfZcId = GetLocalZcId();

    if ((RETURN_ERROR== zcId) || (RETURN_ERROR== selfZcId))
    {
        rtnValue = RETURN_ERROR;
    }
    else
    {		
        if (zcId == selfZcId)
        {
            rtnValue = FLAG_SET;
        }
        else
        {
            rtnValue = FLAG_UNSET;
        }
    }

    return rtnValue;
}

/*
* 功能描述： 判断待判计轴两侧相邻计轴是否均满足ARB判断条件
* 参数说明： const UINT16 checkedAcId
* 返回值  ： 1：满足ARB条件
*			 0：不满足ARB条件			 
*/
UINT8_S CheckAdjacentAxleArbCondition(const UINT16_S checkedAcId)
{
    UINT8_S FrontArbConditon = DEFAULT_ZERO;
    UINT8_S RearArbConditon = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*沿正方向判断结果*/
    FrontArbConditon = CheckOneSideAxleArbCondition(checkedAcId,FORWORD_DIRCTION);

    /*沿反方向判断结果*/
    RearArbConditon = CheckOneSideAxleArbCondition(checkedAcId,NEGATIVE_DIRCTION);

    if ((RETURN_SUCCESS == FrontArbConditon) && (RETURN_SUCCESS == RearArbConditon))
    {
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* 功能描述： 待判计轴相邻计轴是否满足ARB条件
* 参数说明： const UINT16  checkedAcId, 待判计轴ID
*			 const UINT8_S direction，查询方向
* 返回值  ： 0: 不满足ARB条件
*			 1：满足ARB条件
*/
UINT8_S CheckOneSideAxleArbCondition(const UINT16_S checkedAcId,const UINT8_S direction)
{
    UINT16_S  sideDsuCheck = DEFAULT_ZERO;               /*查询后方计轴返回值*/
    UINT16_S  sideAcIdBuff[MAX_ADJACENT_LOSE_AC]={DEFAULT_ZERO};                   
    UINT8_S  sideAcNum = DEFAULT_ZERO; 
    UINT8_S rtnValue = DEFAULT_ZERO;

    MemorySet(sideAcIdBuff,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)),
                DEFAULT_ZERO,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)));

    sideDsuCheck = CheckFrontACCanStatus(checkedAcId,direction,&sideAcNum,sideAcIdBuff);

    switch (sideDsuCheck)
    {
    case 1U:
        /*成功*/
        rtnValue = CheckOneSideNormalAxleArbCondition(checkedAcId,sideAcIdBuff[0],direction);
        break;
    case 3U:
        /*由于道岔原因查询失败*/
        rtnValue = CheckOneSideLoseAxleArbCondition(sideAcIdBuff,sideAcNum);
        break;
    case 2U:
        /*由于尽头线原因失败，认为无法判断ARB*/
        rtnValue = RETURN_ERROR;
        break;
    case 0U:
        /*由于其它原因失败，认为无法判断ARB*/
        rtnValue = RETURN_ERROR;
        break;
    default:
        rtnValue = RETURN_ERROR;
        break;
    }

    return rtnValue;
}

/*
* 功能描述： 待判计轴相邻正常计轴是否满足ARB条件
* 参数说明： const UINT16  checkedAcId, 待判计轴ID
*			 const UINT16_S  adjacentAcId，相邻计轴ID
*			 const UINT8_S dir, 方向
* 返回值  ： 0: 不满足ARB条件
*			 1：满足ARB条件
*/
UINT8_S CheckOneSideNormalAxleArbCondition(const UINT16_S checkedAcId,const UINT16_S adjacentAcId,const UINT8_S dir)
{
    UINT8_S dirTrainInAc = DEFAULT_ZERO;       /*默认方向是无方向*/ 
    UINT8_S judgeARBFlag = DEFAULT_ZERO;       /*ARB判断标志位*/
    UINT8_S adjacentAcStatus = DEFAULT_ZERO;   /*相邻计轴状态*/
    UINT8_S trainNum = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S suspectedFlag = DEFAULT_ZERO;
    UINT8_S arbFlag = DEFAULT_ZERO;
    UINT8_S utFlag = DEFAULT_ZERO;
    UINT8_S arbRedundancy = DEFAULT_ZERO;
    UINT8_S utRedundancy = DEFAULT_ZERO;
    UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};

    MemorySet(&trainSequenceBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));
    adjacentAcStatus = GetAcStatusNow(adjacentAcId);

    switch (adjacentAcStatus)
    {
    case AC_FREE_STATUS:
        /*前方计轴空闲,返回可判断ARB*/
        judgeARBFlag = 1U;
        break;
    case AC_OCC_STATUS:
        /*获取列车数量*/
        trainNum = GetAcTrainOfAcNum(adjacentAcId);

        if ((0U < trainNum) && (RETURN_UINT8_MAX_VALUE != trainNum))
        {
            /*列车数量大于0*/
            /*判断本计轴区段内列车的运行方向*/
            dirTrainInAc = CalculateTrainDirInOtherAc(FLAG_SET,checkedAcId,adjacentAcId,dir);

            /*获取前方或者后方计轴的列车序列*/           
            if (RETURN_SUCCESS == GetAcTrainSequenceBuff(adjacentAcId,SIZE_MAX_TRAINOFAC,trainSequenceBuff))
            {
                switch (dirTrainInAc)
                {
                case AC_DIR_FARAWAY:
                    trainId = GetLastIdInTrainSequence(adjacentAcId);

                    if (RETURN_UINT16_MAX_VALUE != trainId)
                    {
                        suspectedFlag = GetTrainSuspectTail(trainId);

                        if (FLAG_UNSET == suspectedFlag)
                        {
                            /*为通信车且无后端可疑*/
                            judgeARBFlag = 1U;
                        }
                        else
                        {
                            judgeARBFlag = 0U;
                        }
                    }
                    else
                    {
                        /*宕机*/
                    }

                    break;
                case AC_DIR_CLOSED:
                    trainId = GetFirstIdInTrainSequence(adjacentAcId);

                    if (RETURN_UINT16_MAX_VALUE != trainId)
                    {
                        suspectedFlag = GetTrainSuspectHead(trainId);

                        if (FLAG_UNSET == suspectedFlag)
                        {
                            /*为通信车且无前端可疑*/
                            judgeARBFlag = 1U;
                        }
                        else
                        {
                            judgeARBFlag = 0U;
                        }
                    }
                    else
                    {
                        /*宕机*/
                    }

                    break;
                default:
                    judgeARBFlag = 0U;
                    break;
                }
            }         
        }
        else if (RETURN_UINT8_MAX_VALUE != trainNum)
        {
            arbFlag = GetAcArbFlag(adjacentAcId);
            utFlag = GetAcUtFlag(adjacentAcId);
            arbRedundancy = GetAcArbRedundance(adjacentAcId);
            utRedundancy = GetAcUtRedundance(adjacentAcId);

            if ((RETURN_UINT8_MAX_VALUE != arbFlag) && (RETURN_UINT8_MAX_VALUE != utFlag)
                && (RETURN_UINT8_MAX_VALUE != arbRedundancy) && (RETURN_UINT8_MAX_VALUE != utRedundancy))
            {
                if(FLAG_SET == arbFlag)
                {
                    /*可以直接判断ARB*/
                    judgeARBFlag = 1U;
                }
                else if(FLAG_SET == utFlag)
                {
                    /*不可判断ARB*/
                    judgeARBFlag = 0U;
                }
                else if(0U < utRedundancy)
                {
                    /*可判断ARB*/
                    /*zcy:注意此处需要提出限制条件*/
                    judgeARBFlag = 1U;
                }
                else
                {
                    /*该分支不可能存在*/
                    /*不可判断ARB*/
                    judgeARBFlag = 0U;
                }
            }
            else
            {
                /*宕机*/
            }
        }
        else
        {
            /*宕机*/
        }
        break;
    default:
        /*不可判断ARB*/
        judgeARBFlag = 0U;
        break;
    }

    return judgeARBFlag;
}

/*
* 功能描述： 待判计轴相邻四开计轴是否满足ARB条件
* 参数说明： const UINT16  adjacentAcId[]，相邻计轴ID
*            const UINT8_S adjacentAcNum,相邻计轴数量
* 返回值  ： 0: 不满足ARB条件
*			 1：满足ARB条件
*/
UINT8_S CheckOneSideLoseAxleArbCondition(const UINT16_S adjacentAcId[],const UINT8_S adjacentAcNum)
{
    UINT8_S i = DEFAULT_ZERO;
    UINT8_S freeAcNum = DEFAULT_ZERO;
    UINT8_S arbAcNum = DEFAULT_ZERO;
    UINT8_S acOccStatus = DEFAULT_ZERO;
    UINT8_S acArbStatus = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    for (i=DEFAULT_ZERO;i < adjacentAcNum;i++)
    {
        /*获取计轴占用状态*/
        acOccStatus = GetAcStatusNow(adjacentAcId[i]);
        acArbStatus = GetAcArbFlag(adjacentAcId[i]);

        if (AC_FREE_STATUS == acOccStatus)
        {
            freeAcNum++;
        }
        else if (FLAG_SET == acArbStatus)
        {
            arbAcNum++;
        }
        else
        {
            /*不作处理*/
        }
    }

    if ((freeAcNum == adjacentAcNum) || (arbAcNum == adjacentAcNum))
    {
        /*满足ARB判断条件*/
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }	

    return rtnValue;
}

/*
* 功能描述： 计轴由RM列车清扫状态转换
* 参数说明： 无
* 返回值  ： 无
*/
void AcCleanStatusProcess(void)
{
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT8_S acUtFlag = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S cleanFlag = DEFAULT_ZERO;

    for (i=DEFAULT_ZERO;i < GetAcCurSum();i++)
    {
        acId = GetAcId(i);

        if (GetLocalZcId() == GetAcBelongZcId(acId))
        {
            /*本ZC管辖范围内计轴区段,处理*/
            /*获取AC UT标志*/
            acUtFlag = GetAcUtFlag(acId);

            trainId = GetAcCleanTrainId(acId);

            cleanFlag = GetAcTrainCleanFlag(acId);

            if (FLAG_SET == acUtFlag)
            {
                switch (cleanFlag)
                {
                case CLEAN_STATUS_DEFAULT:
                    DefaultStatusProcess(acId);
                    break;
                case CLEAN_STATUS_HEAD_ENTRY:
                    HeadEntryStatusProcess(acId,trainId);
                    break;
                case CLEAN_STATUS_HEAD_OUT:
                    HeadOutStatusProcess(acId,trainId);
                    break;
                case CLEAN_STATUS_ALL_OUT:
                    AllOutStatusProcess(acId);
                    break;
                default:
                    break;
                }
            }
            else
            {
                /*无需进行清扫判断*/ 
                SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                SetAcCleanTrainId(acId,DEFAULT_ZERO);
            }
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*
* 功能描述： 计轴清扫默认状态处理
* 参数说明： const UINT16 acId
*		     const UINT16_S trainId
* 返回值  ： 无
*/
void DefaultStatusProcess(const UINT16_S acId)
{
    UINT16_S trainHeadAc =DEFAULT_ZERO;
    UINT16_S trainTailAc = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT16_S backAcIdBuff[MAX_ADJACENT_LOSE_AC]={DEFAULT_ZERO};
    UINT8_S backAcNum = DEFAULT_ZERO;
    UINT8_S sideDsuCheck = DEFAULT_ZERO;
    UINT8_S trainDirection = DEFAULT_ZERO;
    UINT8_S trainNum = DEFAULT_ZERO;
    UINT8_S i = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainBodyInAc = DEFAULT_ZERO;

    MemorySet(backAcIdBuff,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)),
                 DEFAULT_ZERO,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)));

    trainNum = GetTrainCurSum();

    for (i=DEFAULT_ZERO;i<trainNum;i++)
    {
        trainId = GetTrainIdOfIndex(i);

        trainHeadAc = GetTrainTrainHeadAC(trainId);
        trainTailAc = GetTrainTrainTailAC(trainId);
        trainDirection = GetTrainUnsafeDirection(trainId);
        trainType = GetTrainType(trainId);

        if ((RETURN_ERROR != trainDirection) && (RETURN_ERROR != trainType))
        {
            /*查询待判计轴后一计轴*/
            sideDsuCheck = CheckRearACCanStatus(acId,trainDirection,&backAcNum,backAcIdBuff);
#ifdef SYS_TYPE_WINDOWS

            /*LogPrintf(1U,"300.3 sideDsuCheck=%d,acId=%d,rearAcNum=%d,rearAcId[0]=%d,rearAcId[1]=%d\n",sideDsuCheck,acId,frontAcNum,backAcIdBuff[0],backAcIdBuff[1]);*/
#endif
            if (RETURN_SUCCESS == sideDsuCheck)
            {
                trainBodyInAc = JudgeTrainBodyInAc(trainId,backAcIdBuff[0]);

                if (((TRAIN_MODE_RM == trainType) || (TRAIN_MODE_RM0 == trainType))
                    && (acId == trainHeadAc) && ((backAcIdBuff[0] == trainTailAc) || (1U == trainBodyInAc)))
                {
                    /*列车类型为RM，车头位于待清扫计轴，车尾或者车身位于前一计轴*/
                    SetAcTrainCleanFlag(acId,CLEAN_STATUS_HEAD_ENTRY);
                    SetAcCleanTrainId(acId,trainId);
                    break;
                }
                else
                {
                    /*继续遍历*/
                    SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                    SetAcCleanTrainId(acId,0U);
                }
            }
            else
            {
                /*不满足判断条件*/

            }
        }
        else
        {
            /*不处理*/
        }
    }
}

/*
* 功能描述： 计轴清扫车头已进入状态处理
* 参数说明： const UINT16 acId
*		     const UINT16_S trainId
* 返回值  ： 无
*/
#if 0

void HeadEntryStatusProcess1(const UINT16 acId,const UINT16 trainId)
{
    UINT16 trainHeadAc = 0U;
    UINT16 trainTailAc = 0U;
    UINT8 trainType = 0U;
    UINT16 frontAcId[MAX_ADJACENT_LOSE_AC];
    UINT8 frontAcNum = 0U;
    UINT8 sideDsuCheck = 0U;
    UINT8 trainDirection = 0U;
    UINT8 tailSuspect = 0U;

    MemorySet(frontAcId,MAX_ADJACENT_LOSE_AC*SIZE_UINT16,0,MAX_ADJACENT_LOSE_AC*SIZE_UINT16);

    trainHeadAc = GetTrainTrainHeadAC(trainId);
    trainTailAc = GetTrainTrainTailAC(trainId);
    trainDirection = GetTrainUnsafeDirection(trainId);
    trainType = GetTrainType(trainId);
    tailSuspect = GetTrainSuspectTail(trainId);

    if ((RETURN_ERROR != trainDirection) && (RETURN_ERROR != trainType))
    {
        if ((TRAIN_MODE_RM == trainType) && (FLAG_UNSET == tailSuspect)
            && (acId == trainHeadAc) && (acId == trainTailAc))
        {
            /*说明列车已完全进入待判计轴*/
            SetAcTrainCleanFlag(acId,CLEAN_STATUS_ALL_ENTRY);
            SetAcCleanTrainId(acId,trainId);
        }
        else 
        {
            /*查询待判计轴前一计轴*/
            sideDsuCheck = CheckRearACCanStatus(acId,trainDirection,&frontAcNum,frontAcId);

            if (RETURN_SUCCESS == sideDsuCheck)
            {
                if	((TRAIN_MODE_RM == trainType) && (acId == trainHeadAc) && (frontAcId[0] == trainTailAc))
                {
                    /*列车类型为RM，车头位于待清扫计轴，车尾位于前一计轴,保持*/
                    SetAcTrainCleanFlag(acId,CLEAN_STATUS_HEAD_ENTRY);
                    SetAcCleanTrainId(acId,trainId);
                }
                else
                {
                    SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                    SetAcCleanTrainId(acId,0);
                }
            }
            else
            {
                SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                SetAcCleanTrainId(acId,0);
            }
        }
    }
}
#endif
/*
* 功能描述： 计轴清扫车头车尾均进入状态处理
* 参数说明： const UINT16 acId
*		     const UINT16 trainId
* 返回值  ： 无
*/
void HeadEntryStatusProcess(const UINT16_S acId,const UINT16_S trainId)
{
    UINT16_S trainHeadAc = 0U;
    UINT16_S trainTailAc = 0U;
    UINT8_S trainType = 0U;
    UINT16_S frontAcId[MAX_ADJACENT_LOSE_AC] = {0U};
    UINT16_S rearAcId[MAX_ADJACENT_LOSE_AC] = {0U};
    UINT8_S frontAcNum = 0U;
    UINT8_S rearAcNum = 0U;
    UINT8_S sideDsuCheck1 = 0U;
    UINT8_S sideDsuCheck2 = 0U;
    UINT8_S trainDirection = 0U;
    UINT8_S tailSuspect = 0U;
    UINT8_S trainBodyInCurAc = DEFAULT_ZERO;
    UINT8_S trainBodyInBefAc = DEFAULT_ZERO;

    MemorySet(frontAcId,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)),
                0U,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)));
    MemorySet(rearAcId,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)),
                0U,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)));

    trainHeadAc = GetTrainTrainHeadAC(trainId);
    trainTailAc = GetTrainTrainTailAC(trainId);
    trainDirection = GetTrainUnsafeDirection(trainId);
    trainType = GetTrainType(trainId);
    tailSuspect = GetTrainSuspectTail(trainId);

    if ((RETURN_ERROR != trainDirection) && (RETURN_ERROR != trainType) 
        && (RETURN_ERROR != tailSuspect))
    {
        /*查询待判计轴后一计轴*/
        sideDsuCheck1 = CheckRearACCanStatus(acId,trainDirection,&rearAcNum,rearAcId);
#ifdef SYS_TYPE_WINDOWS
        /*LogPrintf(1U,"300.1 sideDsuCheck=%d,acId=%d,rearAcNum=%d,rearAcId[0]=%d,rearAcId[1]=%d\n",sideDsuCheck1,acId,rearAcNum,rearAcId[0],rearAcId[1]);*/
#endif

        /*查询待判计轴前一计轴*/
        sideDsuCheck2 = CheckFrontACCanStatus(acId,trainDirection,&frontAcNum,frontAcId);

#ifdef SYS_TYPE_WINDOWS
        /*LogPrintf(1U,"300.2 sideDsuCheck=%d,acId=%d,frontAcNum=%d,frontAcId[0]=%d,frontAcId[1]=%d\n",sideDsuCheck2,acId,frontAcNum,frontAcId[0],frontAcId[1]);*/
#endif
        if (((TRAIN_MODE_RM == trainType)  || (TRAIN_MODE_RM0 == trainType) || (TRAIN_MODE_CBTC == trainType)) && (FLAG_UNSET == tailSuspect))
        {
            /*列车类型正确，且不带后端可疑标志*/
            if ((acId == trainHeadAc) && (acId == trainTailAc))
            {
                /*车头车尾均已进入待判计轴，保持状态*/
                SetAcTrainCleanFlag(acId,CLEAN_STATUS_HEAD_ENTRY);
                SetAcCleanTrainId(acId,trainId);
            }
            else
            {
                if ((1U == sideDsuCheck1) && (1U == sideDsuCheck2))
                {
                    trainBodyInCurAc = JudgeTrainBodyInAc(trainId,acId);
                    trainBodyInBefAc = JudgeTrainBodyInAc(trainId,rearAcId[0]);

                    if ((frontAcId[0] == trainHeadAc) && ((acId == trainTailAc) || (1U == trainBodyInCurAc)))
                    {
                        /*列车类型为RM，无后端可疑标志，车头位于待清扫计轴下一计轴，车尾或者车身位于待判计轴*/
                        SetAcTrainCleanFlag(acId,CLEAN_STATUS_HEAD_OUT);
                        SetAcCleanTrainId(acId,trainId);
                    }
                    else if ((acId == trainHeadAc) && ((rearAcId[0] == trainTailAc) || (1U == trainBodyInBefAc)))
                    {
                        /*列车类型为RM，车头位于待清扫计轴，车尾或者车身位于前一计轴,保持*/
                        SetAcTrainCleanFlag(acId,CLEAN_STATUS_HEAD_ENTRY);
                        SetAcCleanTrainId(acId,trainId);
                    }
                    else
                    {
                        /*错误，清除为默认状态*/
                        SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                        SetAcCleanTrainId(acId,0U);
                    }
                }
                else
                {
                    /*清除为默认状态*/
                    SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                    SetAcCleanTrainId(acId,0U);
                }

            }
        }
        else
        {
            /*清除为默认状态*/
            SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
            SetAcCleanTrainId(acId,0U);
        }		
    }
    else
    {
        /*清除为默认状态*/
        SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
        SetAcCleanTrainId(acId,0U);
    }
}

/*
* 功能描述： 计轴清扫车头出清状态处理
* 参数说明： const UINT16 acId
*		     const UINT16_S trainId
* 返回值  ： 无
*/
void HeadOutStatusProcess(const UINT16_S acId,const UINT16_S trainId)
{
    UINT16_S trainHeadAc = 0U;
    UINT16_S trainTailAc = 0U;
    UINT8_S trainType = 0U;
    UINT16_S frontAcId[MAX_ADJACENT_LOSE_AC] = {0U};
    UINT8_S frontAcNum = 0U;
    UINT8_S sideDsuCheck = 0U;
    UINT8_S trainDirection = 0U;
    UINT8_S tailSuspect = 0U;
    UINT8_S judgeFlag = DEFAULT_ZERO;
	
    MemorySet(frontAcId,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)),
               0U,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)));

    trainHeadAc = GetTrainTrainHeadAC(trainId);
    trainTailAc = GetTrainTrainTailAC(trainId);
    trainDirection = GetTrainUnsafeDirection(trainId);
    trainType = GetTrainType(trainId);
    tailSuspect = GetTrainSuspectTail(trainId);

    if ((RETURN_ERROR != trainDirection) && (RETURN_ERROR != trainType) 
        && (RETURN_ERROR != tailSuspect))
    {
        /*查询待判计轴前一计轴*/
        sideDsuCheck = CheckFrontACCanStatus(acId,trainDirection,&frontAcNum,frontAcId);

#ifdef SYS_TYPE_WINDOWS
        /*LogPrintf(1U,"300.4 sideDsuCheck=%d,acId=%d,backAcNum=%d,frontAcId[0]=%d,frontAcId[1]=%d\n",sideDsuCheck,acId,backAcNum,frontAcId[0],frontAcId[1]);*/
#endif
        if (1U == sideDsuCheck)
        {
			judgeFlag = JudgeTrainBodyInAc(trainId,acId);
			
            if (((TRAIN_MODE_RM == trainType)  || (TRAIN_MODE_RM0 == trainType) || (TRAIN_MODE_CBTC == trainType)) 
				&& (FLAG_UNSET == tailSuspect)
                && (frontAcId[0] == trainTailAc) 
				&& (acId != trainHeadAc) 
				&& (2U == judgeFlag))
            {
                /*车尾位于下一计轴，车头和车身均不位于待判计轴，说明列车已经出清待判计轴*/
                /*列车类型为RM，无后端可疑标志，车头车尾均位于待清扫计轴下一计轴*/
                SetAcTrainCleanFlag(acId,CLEAN_STATUS_ALL_OUT);
                SetAcCleanTrainId(acId,trainId);
            }
            else if (((TRAIN_MODE_RM == trainType)  || (TRAIN_MODE_RM0 == trainType) || (TRAIN_MODE_CBTC == trainType)) 
				     && (FLAG_UNSET == tailSuspect)
                     && (frontAcId[0] != trainTailAc))
                /*else if (((TRAIN_MODE_RM == trainType) || (TRAIN_MODE_CBTC == trainType)) && (FLAG_UNSET == tailSuspect)
                && (acId == trainTailAc))*/
            {
                /*zcy:条件暂时改为车尾不位于下一计轴，但条件比较宽松，可能不够严密，后续需要继续考虑;原条件在列车跨压3个计轴时存在问题*/
                /*车尾仍然处于待判计轴，说明列车尚未出清待判计轴*/
                /*列车类型为RM，无后端可疑标志，车头位于待清扫计轴下一计轴，车尾位于待判计轴*/
                SetAcTrainCleanFlag(acId,CLEAN_STATUS_HEAD_OUT);
                SetAcCleanTrainId(acId,trainId);
            }
            else
            {
                /*清除为默认状态*/
                SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                SetAcCleanTrainId(acId,0U);
            }
        }
        else
        {
            /*清除为默认状态*/
            SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
            SetAcCleanTrainId(acId,0U);
        }
    }
    else
    {
        /*清除为默认状态*/
        SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
        SetAcCleanTrainId(acId,0U);
    }
}

/*
* 功能描述： 计轴清扫车头车尾均出清状态处理
* 参数说明： const UINT16 acId
*		     const UINT16_S trainId
* 返回值  ： 无
*/
void AllOutStatusProcess(const UINT16_S acId)
{
    /*列车完成进入下一计轴，仅一周期有效*/
    /*清除为默认状态*/
    SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
    SetAcCleanTrainId(acId,0U);
}


/*
* 功能描述： 计轴UT判断主函数
* 参数说明： 无
* 返回值  ： 无
*/
void JudgeAxleUT(void)
{
    /*将空闲计轴转换为UT状态*/
    ConvertAxleFreetoUT();

    /*将ARB计轴转换为UT状态*/
    ConvertAxleArbToUt();

    /*处理道岔区域中UT计轴和ARB计轴状态不一致现象*/
    ConvertSwitchAxleArbToUt();

    /*空闲计轴清除UT标志*/
    ConvertAxleUtToFree();
}

/*
* 功能描述： 计轴ARB判断主函数
* 参数说明： 无
* 返回值  ： 无
*/
void JudgeAxleARB(void)
{
    /*将UT计轴转换为ARB状态*/
    ConvertAxleUtToArb();

    /*空闲计轴清除ARB标志*/
    ConvertAxleArbToFree();
}

/*
* 功能描述： 若待判计轴有空闲变为占用，或者列车通过后维持占用，将其设置为冗余UT
* 参数说明： 无
* 返回值  ： 无
*/
void ConvertAxleFreetoUT(void)
{
    UINT16_S acCycle = 0U;
    UINT8_S acArbFlag = 0U;
    UINT16_S acId = 0U;
    UINT8_S acStatus = 0U;
    UINT8_S acAttribute = 0U;
    UINT8_S acUtFlag = 0U;
    UINT8_S acUtRedunce = 0U;
    UINT8_S trainNum = 0U;

    /*遍历本ZC计轴*/
    for (acCycle = 0U;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        /*获取AC UT冗余计时位*/
        acUtRedunce = GetAcUtRedundance(acId);

        /*获取计轴列车数量状态*/
        trainNum = GetAcTrainOfAcNum(acId);

        /*判断计轴是否属于本ZC*/
        acAttribute = CheckAcAttribute(acId);

        /*对已经处于UT冗余状态的计轴进行处理*/
        if (FLAG_SET == acAttribute)
        {
            if (0U != acUtRedunce)
            {
                if (0U != trainNum)
                {
                    /*说明列车已经进入计轴，结束冗余*/
                    SetAcUtRedundance(acId,0U);
                }
                else
                {
                    /*占用无车时，将计轴设置为冗余UT*/
                    SetAcUtRedundance(acId,acUtRedunce + 1U);
                }

                /*说明计轴处于冗余UT过程中*/
                if (GetSectionRedundantCycle() <= acUtRedunce)
                {
                    /*冗余时间到，将冗余计轴设置为UT*/
                    SetAcUtFlag(acId,AC_UT_OCC_STATUS);
                    SetAcUtRedundance(acId,0U);
                }
            }
            else
            {
                /*未处于UT状态*/
            }
        }
        else
        {
            /*不作处理*/
        }
    }

    /*遍历本ZC计轴*/
    for (acCycle = 0U;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        /*获取AC ARB标志*/
        acArbFlag = GetAcArbFlag(acId);

        /*获取AC UT标志*/
        acUtFlag = GetAcUtFlag(acId);

        /*获取AC UT冗余计时位*/
        acUtRedunce = GetAcUtRedundance(acId);

        /*获取计轴占用状态*/
        acStatus = GetAcStatusNow(acId);

        /*获取计轴列车数量状态*/
        trainNum = GetAcTrainOfAcNum(acId);

        /*判断计轴是否属于本ZC*/
        acAttribute = CheckAcAttribute(acId);

        if ((FLAG_SET == acAttribute) 
            && (AC_ARB_OCC_STATUS != acArbFlag)
            && (AC_UT_OCC_STATUS != acUtFlag) 
            && (0U == acUtRedunce) 
            && (AC_OCC_STATUS == acStatus) 
            && (0U == trainNum))
        {
            /*占用无车时，将计轴设置为冗余UT*/
            SetAcUtRedundance(acId,1U);
        }
        else
        {
            /*不作处理*/
        }
    }
}

/*
* 功能描述： 若待判计轴已经判断为ARB，当非通信列车接近或者占用该计轴后，将其转换为UT
* 参数说明： 无
* 返回值  ： 无
*/
void ConvertAxleArbToUt(void)
{
    UINT16_S acCycle = 0U;
    UINT16_S acId = 0U;
    UINT8_S acArbFlag = 0U;
    UINT8_S acAttribute = 0U;
    UINT8_S adjacentUtCondition = 0U;

    /*遍历本ZC计轴*/
    for (acCycle = 0U;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        if (RETURN_ERROR != acId)
        {
            /*获取AC UT标志*/
            acArbFlag = GetAcArbFlag(acId);

            /*判断计轴是否属于本ZC*/
            acAttribute = CheckAcAttribute(acId);

            /*判断待判计轴相邻计轴情况*/
            adjacentUtCondition = CheckAdjacentAxleUtCondition(acId);

            if ((FLAG_SET == acAttribute) && (FLAG_SET == acArbFlag)
                && (RETURN_SUCCESS == adjacentUtCondition))
            {
                /*满足以上条件，将计轴ARB状态转换为UT*/
                SetAcArbFlag(acId,FLAG_UNSET);
                SetAcUtFlag(acId,FLAG_SET);
                SetAcUtRedundance(acId,0U);
            }
            else
            {
                /*计轴维持原状*/
            }
        }
        else
        {
            /*宕机*/
        }
    }
}

/*
* 功能描述： 若待判计轴已经判断为UT，当计轴占用状态变为空闲后，清除其UT标志
* 参数说明： 无
* 返回值  ： 无
*/
void ConvertAxleUtToFree(void)
{
    UINT16_S acCycle = 0U;
    UINT8_S acUtFlag = 0U;
    UINT16_S acId = 0U;
    UINT8_S acStatus = 0U;
    UINT8_S acAttribute = 0U;

    /*遍历本ZC计轴*/
    for (acCycle = 0U;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        /*获取AC ARB标志*/
        acUtFlag = GetAcUtFlag(acId);

        /*获取计轴占用状态*/
        acStatus = GetAcStatusNow(acId);

        /*判断计轴是否属于本ZC*/
        acAttribute = CheckAcAttribute(acId);

        if ((FLAG_SET == acAttribute) 
            && (AC_UT_OCC_STATUS == acUtFlag) 
            && (AC_FREE_STATUS == acStatus))
        {
            /*说明UT计轴已经空闲，清除UT标志*/
            SetAcUtFlag(acId,FLAG_UNSET);
            SetAcUtRedundance(acId,0U);
        }
        else
        {
            /*不作处理*/
        }
    }
}

/*
* 功能描述： 判断待判计轴两侧相邻计轴是否可满足UT判断条件
* 参数说明： const UINT16 checkedAcId
* 返回值  ： 1：满足UT条件
*			 0：不满足UT条件			 
*/
UINT8_S CheckAdjacentAxleUtCondition(const UINT16_S checkedAcId)
{
    UINT8_S FrontArbConditon = 0U;
    UINT8_S RearArbConditon = 0U;
    UINT8_S rtnValue = 0U;

    /*沿正方向判断结果*/
    FrontArbConditon = CheckOneSideAxleArbCondition(checkedAcId,FORWORD_DIRCTION);

    /*沿反方向判断结果*/
    RearArbConditon = CheckOneSideAxleArbCondition(checkedAcId,NEGATIVE_DIRCTION);

    if ((RETURN_ERROR == FrontArbConditon) || (RETURN_ERROR == RearArbConditon))
    {
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* 功能描述： 判断单个计轴区段是否位于计轴序列内
* 参数说明： const UINT16 acId, 待查计轴
*            const UINT8_S acOrderNum, 计轴序列数量
*            const UINT16_S acOrderBuff[], 计轴序列
* 返回值  ： 1：位于
*			 0：不位于			 
*/
UINT8_S JudgeSingleAcInAcOrder(const UINT16_S acId,const UINT8_S acOrderNum,const UINT16_S acOrderBuff[])
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (NULL != acOrderBuff)
    {
        /*遍历信息*/
        for (cycle = DEFAULT_ZERO;cycle < acOrderNum;cycle++)
        {
            if (acId == acOrderBuff[cycle])
            {
                rtnValue = 1U;
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
        rtnValue = 0U;
    }
    
    return rtnValue;
}

/*
* 功能描述： 计算输入的计轴是否满足道岔状态（锁闭和位置）
* 参数说明： const UINT16 acId，计轴区段ID   
* 返回值  ： 0:不满足条件
*            1:满足条件
*/
UINT8_S CalulateSwtichStateOfAcIsNeed(const UINT16_S acId)
{
    UINT8_S  acSwitchNum = DEFAULT_ZERO;                                   /*计轴区段包含的道岔数量*/
    SwitchInAcStruct acSwitchInAcStruBuff[AC_SWITCH_SUM_MAX]; /*计轴区段包含的道岔信息*/
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S switchInfoRtn = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S switchLock = DEFAULT_ZERO;
	UINT8_S switchPosStatus = DEFAULT_ZERO;
	
    MemorySet(&acSwitchInAcStruBuff[0],((UINT32_S)(sizeof(SwitchInAcStruct)*AC_SWITCH_SUM_MAX)),
        0U,((UINT32_S)(sizeof(SwitchInAcStruct)*AC_SWITCH_SUM_MAX)));

    /*获取计轴区段道岔信息*/
    acSwitchNum = GetAcSwitchNum(acId);
    switchInfoRtn = GetAcSwitchInfo(acId,AC_SWITCH_SUM_MAX,acSwitchInAcStruBuff);

    if ((DEFAULT_UINT8_VALUE != acSwitchNum)
        && (RETURN_SUCCESS == switchInfoRtn))
    {
        if (DEFAULT_ZERO != acSwitchNum)
        {
            for (cycle = DEFAULT_ZERO;cycle < acSwitchNum;cycle++)
            {
				switchPosStatus = GetSwitchPosStatus(acSwitchInAcStruBuff[cycle].SwitchId);
				switchLock = GetSwitchLock(acSwitchInAcStruBuff[cycle].SwitchId);
				
                if ((switchPosStatus == acSwitchInAcStruBuff[cycle].SwitchPostion)
                    && (SWITCH_STATE_LOCK == switchLock))
                {
                    /*Do nothing currently !*/
                } 
                else
                {
                    breakFlag = FLAG_SET;
                    break;
                }
            }

            if (FLAG_SET == breakFlag)
            {
                rtnValue = RETURN_ERROR;
            } 
            else
            {
                rtnValue = RETURN_SUCCESS;
            }
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

/*
* 功能描述： 遍历本ZC所有的计轴区段，如果包含道岔，且某一个计轴为UT，将其关联的ARB计轴设置为UT
* 参数说明： 无   
* 返回值  ： 无
*/
void ConvertSwitchAxleArbToUt(void)
{
    UINT16_S acCycle = 0U;
    UINT16_S acId = 0U;

    /*遍历本ZC计轴*/
    for (acCycle = 0U;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        if (RETURN_ERROR == ConvertSingleSwitchAxleArbToUt(acId))
        {
            /*宕机*/
        }
    }
}

/*
* 功能描述： 遍历道岔计轴区段，如果道岔区段某一个计轴为UT，将其关联的ARB计轴设置为UT
* 参数说明： const UINT16 acId，计轴区段ID   
* 返回值  ： 0:失败
*            1:成功
*/
UINT8_S ConvertSingleSwitchAxleArbToUt(const UINT16_S acId)
{
    UINT8_S utFlag = 0U;
    UINT8_S rtnValue = 1U;
    UINT8_S checkAcNum = 0U;
    UINT16_S checkAcBuff[SWITCH_BELONG_AC_SUM_MAX * 5U] = {0U};
    UINT8_S i = 0U;
    UINT8_S ret = 0U;
    UINT8_S arbFlag = 0U;

    MemorySet(&checkAcBuff[0],((UINT32_S)(SIZE_UINT16 * SWITCH_BELONG_AC_SUM_MAX * 5U)),
                 0U,((UINT32_S)(SIZE_UINT16 * SWITCH_BELONG_AC_SUM_MAX * 5U)));

    utFlag = GetAcUtFlag(acId);

    if (AC_UT_OCC_STATUS == utFlag)
    {
        /*如果输入计轴为UT，查询其关联的其它计轴*/
        ret = CheckRelatedAcOfInputAc(acId,&checkAcNum,checkAcBuff);

        if (RETURN_SUCCESS == ret)
        {
            for (i=0U;i<checkAcNum;i++)
            {
                arbFlag = GetAcArbFlag(checkAcBuff[i]);

                if ((checkAcBuff[i] != acId) && (AC_ARB_OCC_STATUS == arbFlag))
                {
                    /*如果不为输入计轴，且已判断为ARB，则将其转换为UT*/
                    SetAcUtFlag(checkAcBuff[i],AC_UT_OCC_STATUS);
                }
                else
                {
                    /*继续遍历*/
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
        /*无需处理*/
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*
* 功能描述： 遍历道岔计轴区段，如果道岔区段某一个计轴为UT，将其关联的ARB计轴设置为UT
* 参数说明： const UINT16 acId，计轴区段ID  
*            UINT8_S *relatedAcNum,计轴区段数量
*            UINT16_S relatedAcId[SWITCH_BELONG_AC_SUM_MAX*5],计轴区段数组
* 返回值  ： 0:不满足条件
*            1:满足条件
*/
UINT8_S CheckRelatedAcOfInputAc(const UINT16_S acId,UINT8_S *relatedAcNum,UINT16_S relatedAcId[SWITCH_BELONG_AC_SUM_MAX * 5U])
{
    UINT8_S getSwitchNum = 0U;
    UINT16_S getSwitchInfoBuff[AC_SWITCH_SUM_MAX * 2U] = {0U};
    UINT8_S checkAcNum = 0U;
    UINT16_S checkAcBuff[SWITCH_BELONG_AC_SUM_MAX] = {0U};
    UINT8_S cycle = 0U;
    UINT8_S cycle2 = 0U;
    UINT8_S ret1 = 0U;
    UINT8_S ret2 = 0U;
    UINT8_S rtnValue = RETURN_SUCCESS;

    MemorySet(&getSwitchInfoBuff[0],((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX * 2U)),
                0U,((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX * 2U)));
    MemorySet(&checkAcBuff[0],((UINT32_S)(SIZE_UINT16 * SWITCH_BELONG_AC_SUM_MAX)),
                0U,((UINT32_S)(SIZE_UINT16 * SWITCH_BELONG_AC_SUM_MAX)));

    /*查询计轴包含的道岔信息*/
    ret1 = GetLineAcIncludeSwitchInfo(acId,&getSwitchNum,getSwitchInfoBuff);

    if ((RETURN_SUCCESS == ret1) && (NULL != relatedAcNum) && (NULL != relatedAcId))
    {
        for (cycle=0U;cycle<getSwitchNum;cycle++)
        {
            /*查询道岔包含的计轴数量*/
            ret2 = CheckSwitchBelongAc(getSwitchInfoBuff[cycle],&checkAcNum,checkAcBuff);

            if (RETURN_SUCCESS == ret2)
            {
                for (cycle2=0U;cycle2<checkAcNum;cycle2++)
                {
                    /*收集指定计轴关联的所有计轴*/
                    relatedAcId[*relatedAcNum] = checkAcBuff[cycle2];
                    (*relatedAcNum) ++;
                }
            }
            else
            {
                /*返回失败*/
                *relatedAcNum = 0U;				
                rtnValue = 0U;
                break;
            }
        }
    }
    else
    {
        /*返回失败*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* 功能描述： 判断列车车身（非车头车尾）是否位于指定计轴上
* 参数说明： const UINT16 trainId
const UINT16_S acId，计轴区段ID   
* 返回值  ： 0:是被
*            1:位于指定计轴
*            2：不位于指定计轴
*/
UINT8_S JudgeTrainBodyInAc(const UINT16_S trainId,const UINT16_S acId)
{
    UINT16_S headLink = 0U;
    UINT16_S tailLink = 0U;
    UINT8_S dir = 0U;
    TrainSafeLocStruct trainSafeLoc;
    UINT8_S acNum = 0U;
    UINT16_S acBuff[ZC_TWO_POINT_AC_NUM_MAX] = {0U};
    UINT8_S ret = 0U;
    UINT8_S i = 0U;
    UINT16_S headAcId = 0U;
    UINT16_S tailAcId = 0U;
    UINT8_S rtnValue = 0U;

    MemorySet(&trainSafeLoc,((UINT32_S)(sizeof(TrainSafeLocStruct))),
                 0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));
    MemorySet(&acBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)));

    GetTrainSafeLoc(trainId,&trainSafeLoc);

    headLink = trainSafeLoc.TrainHeadLink;
    tailLink = trainSafeLoc.TrainTailLink;
    dir = GetTrainUnsafeDirection(trainId);
    headAcId = GetTrainTrainHeadAC(trainId);
    tailAcId= GetTrainTrainTailAC(trainId);

    ret = CheckAcOrderBetweenTwoPoints(tailLink,headLink,dir,&acNum,acBuff);

    if (RETURN_SUCCESS == ret)
    {
        rtnValue = 2U;

        for (i = 0U;i < acNum;i++)
        {
            if ((acBuff[i] == acId) && (acBuff[i] != headAcId) && (acBuff[i] != tailAcId))
            {
                rtnValue = 1U;
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
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* 功能描述： 判断当前计轴区段是否满足要求的道岔位置状态
* 参数说明： const UINT16 acId 计轴Id
* 返回值  ： 0: 不满足道岔状态
*			 1: 满足道岔状态    
*/
UINT8_S JudgeAcOfSwitchPosInNeed(const UINT16_S acId)
{
	UINT8_S switchNumInAc = DEFAULT_ZERO;
	SwitchInAcStruct switchInAcStruBuff[AC_SWITCH_SUM_MAX];
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = RETURN_SUCCESS;
	UINT16_S switchId = DEFAULT_ZERO;
	UINT8_S switchPosNeed = DEFAULT_ZERO;
	UINT8_S switchPosNow = DEFAULT_ZERO;
	UINT8_S tempRtn = DEFAULT_ZERO;

	/*获取计轴内道岔信息*/
	switchNumInAc = GetAcSwitchNum(acId);
	tempRtn = GetAcSwitchInfo(acId,AC_SWITCH_SUM_MAX,switchInAcStruBuff);

	if (RETURN_ERROR == tempRtn)
	{
		rtnValue = RETURN_ERROR;
	} 
	else
	{
		for (cycle = DEFAULT_ZERO;cycle < switchNumInAc;cycle++)
		{
			/*获取道岔相关ID和应该有的位置信息*/
			switchId = switchInAcStruBuff[cycle].SwitchId;
			switchPosNeed = switchInAcStruBuff[cycle].SwitchPostion;

			/*获取道岔当前的状态*/
			switchPosNow = GetSwitchPosStatus(switchId);

			if (switchPosNow == switchPosNeed)
			{
				/*位置状态满足条件*/
			} 
			else
			{
				rtnValue = RETURN_ERROR;
				break;
			}
		}
	}

	return rtnValue;
}


/*
* 功能描述： 判断当前计轴区段道岔位置状态是否为四开状态
* 参数说明： const UINT16 acId 计轴Id
* 返回值  ： FLAG_UNSET: 非四开状态
*			 FLAG_SET: 四开状态    
*/
UINT8_S CheckAcOfSwitchPosIsSK(const UINT16_S acId)
{
	UINT8_S switchNumInAc = DEFAULT_ZERO;
	SwitchInAcStruct switchInAcStruBuff[AC_SWITCH_SUM_MAX];
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = RETURN_SUCCESS;
	UINT16_S switchId = DEFAULT_ZERO;
	UINT8_S switchPosNow = DEFAULT_ZERO;
	UINT8_S tempRtn = DEFAULT_ZERO;

	/*获取计轴内道岔信息*/
	switchNumInAc = GetAcSwitchNum(acId);
	tempRtn = GetAcSwitchInfo(acId,AC_SWITCH_SUM_MAX,switchInAcStruBuff);

	if (RETURN_ERROR == tempRtn)
	{
		rtnValue = FLAG_SET;
	} 
	else
	{
		for (cycle = DEFAULT_ZERO;cycle < switchNumInAc;cycle++)
		{
			/*获取道岔相关ID和应该有的位置信息*/
			switchId = switchInAcStruBuff[cycle].SwitchId;

			/*获取道岔当前的状态*/
			switchPosNow = GetSwitchPosStatus(switchId);

			if (switchPosNow == SWITCH_STATE_LOSE)
			{
				/*位置状态满足四开条件*/
				rtnValue = FLAG_SET;
				break;
			} 
			else
			{
				rtnValue = FLAG_UNSET;
			}
		}
	}

	return rtnValue;
}