/************************************************************************
*
* 文件名   ：  LogicSectionLogicManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  逻辑区段逻辑处理
* 备  注   ：  无
*
************************************************************************/
#include "LogicSectionLogicManager.h"
#include "LogicSectionConfigData.h"
#include "LogicSectionStatusData.h"
#include "../AC/ACConfigData.h"
#include "../AC/ACStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../../Dmu/DmuComm/Data/AxleSectionData.h"
#include "../../TrainManager/Train/TrainStatusData.h"
#include "../../../Common/MemSet.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../TrainManager/Train/TrainLogicManager.h"

/*
* 功能描述： 处理故障对应的单个逻辑区段信息
* 参数说明： const UINT16 logicSectionId，逻辑区段ID    
* 返回值  ： void  
*/
void InitFailureSingleLogicSetion(const UINT16_S logicSectionId)
{
	SetLogicSectionOccStatus(logicSectionId,LOGIC_SECTION_STATE_UT);
}

/*
* 功能描述： 处理通信故障Ci对应的逻辑区段信息
* 参数说明： const UINT16 ciId，通信故障的CIID    
* 返回值  ： void  
*/
void InitFailureCiLogicSection(const UINT16_S ciId)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S logicSectionId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetLogicSectionSum();cycle++)
	{
		logicSectionId = GetLogicSectionId(cycle);

		if (GetLogicSectionBelongCiId(logicSectionId) == ciId)
		{
			InitFailureSingleLogicSetion(logicSectionId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 逻辑区段更新占用状态
* 参数说明： void    
* 返回值  ： void
*/
void UpdataLogicSectionManager(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S acId = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < GetAcCurSum();cycle++)
	{
		acId = GetAcId(cycle);

		if (GetAcBelongZcId(acId) == GetLocalZcId())
		{
			/*属于本ZC内的计轴区段,更新该计轴区段内的逻辑区段占用状态*/
			UpdateSingalAcLogicSection(acId);
		} 
		else
		{
            /*不处理*/
		}
	}
}

/*
* 功能描述： 更新单个计轴区段逻辑区段占用状态
* 参数说明： const UINT16 acId;计轴区段编号   
* 返回值  ： void
*/
void UpdateSingalAcLogicSection(const UINT16_S acId)
{
	/*初始化单个计轴内逻辑区段状态*/
	InitLogicStatusOfSingleAc(acId);

	/*更新列车占压逻辑区段状态*/
	UpdateLogicStatusOfTrain(acId);

	/*更新列车之间逻辑区段状态*/
	UpdateLogicStatusBetweenTrains(acId);
}

/*
* 功能描述： 初始化单个计轴内逻辑区段状态为UT
* 参数说明： const UINT16 acId;计轴区段编号   
* 返回值  ： void
*/
void InitLogicStatusOfSingleAc(const UINT16_S acId)
{
	UINT8_S sectionOfAcNum = 0U;
	UINT16_S sectionOfAcBuff[SIZE_MAX_SECTIONNUM] = {0U};
	UINT8_S sectionOfAcCycle = 0U;
	UINT8_S rtnOfsectionOfAcNum = 0U;
	UINT8_S arbFlag = 0U;
	UINT16_S acOccState = 0U;
	UINT8_S utRed = 0U;
	UINT8_S acTrainNum = 0U;

	MemorySet(&sectionOfAcBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTIONNUM)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTIONNUM)));

	/*查询计轴内逻辑区段序列*/
	rtnOfsectionOfAcNum = GetLineAcIncludeLogicSectionInfo(acId,&sectionOfAcNum,sectionOfAcBuff);

	if (RETURN_SUCCESS == rtnOfsectionOfAcNum)
	{
		/*获取计轴区段占用状态*/
		acOccState = GetAcStatusNow(acId);
		arbFlag = GetAcArbFlag(acId);
		utRed = GetAcUtRedundance(acId);
		acTrainNum = GetAcTrainOfAcNum(acId);

		for (sectionOfAcCycle = 0U;sectionOfAcCycle < sectionOfAcNum;sectionOfAcCycle++)
		{
			if ((FLAG_SET == arbFlag)
				|| (AC_FREE_STATUS == acOccState)
				|| ((AC_OCC_STATUS == acOccState) && (0U < utRed) && (0U < acTrainNum)))
			{
				/*初始化为空闲*/
				SetLogicSectionOccStatus(sectionOfAcBuff[sectionOfAcCycle],LOGIC_SECTION_STATE_FREE);
			}
			else
			{
				/*初始化为非通信车占用*/
				SetLogicSectionOccStatus(sectionOfAcBuff[sectionOfAcCycle],LOGIC_SECTION_STATE_UT);
			}
		}
	}
	else
	{
		/*宕机*/
	}
}

/*
* 功能描述： 更新单个计轴内单单个列车占压逻辑区段
* 参数说明： const UINT16 acId;计轴区段编号 
*            const UINT16_S trainId;列车ID   
* 返回值  ： void
*/
void UpdateLogicStatusOfSingleTrain(const UINT16_S acId,const UINT16_S trainId)
{
	UINT8_S sectionOfAcNum = 0U;
	UINT16_S sectionOfAcBuff[SIZE_MAX_SECTIONNUM] = {0U};
	UINT8_S direction = 0U;
	UINT8_S trainSectionNum = 0U;
	UINT16_S trainSectionOfAcBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
	UINT8_S sectionOfAcCycle = 0U;
	UINT8_S trainSectionCycle = 0U;
	UINT8_S trainType = 0U;
	TrainSafeLocStruct trainSafeLocStru;
	UINT8_S rtnOfTrainSafeLoc = 0U;
	UINT8_S rtnOfsectionOfAcNum = 0U;
	UINT8_S cycleDebug = DEFAULT_ZERO;

	MemorySet(&sectionOfAcBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTIONNUM)),
               0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTIONNUM)));
	MemorySet(&trainSectionOfAcBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)),
               0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)));
	MemorySet(&trainSafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));

	direction = GetTrainUnsafeDirection(trainId);
	trainType = GetTrainType(trainId);
	rtnOfTrainSafeLoc = GetTrainSafeLoc(trainId,&trainSafeLocStru);

	if ((RETURN_ERROR != direction) && (RETURN_ERROR != trainType) 
		   && (RETURN_SUCCESS== rtnOfTrainSafeLoc))
	{
		/*查询计轴内逻辑区段序列*/
		rtnOfsectionOfAcNum = GetLineAcIncludeLogicSectionInfo(acId,&sectionOfAcNum,sectionOfAcBuff);

		/*成功,查询列车占压的逻辑区段*/
		trainSectionNum = CheckLogicIdBetweenPoints(3U,trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,
								  trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset,direction,
		                          trainSectionOfAcBuff);
	
		if ((RETURN_SUCCESS == rtnOfsectionOfAcNum) && (0U < trainSectionNum))
		{
			for (sectionOfAcCycle = 0U;sectionOfAcCycle < sectionOfAcNum;sectionOfAcCycle++)
			{
				for (trainSectionCycle = 0U;trainSectionCycle < trainSectionNum;trainSectionCycle++)
				{
					if (sectionOfAcBuff[sectionOfAcCycle] == trainSectionOfAcBuff[trainSectionCycle])
					{
						/*找到列车占压的计轴区段，根据列车类型设置相应的逻辑区段*/
						if ((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType))
						{
							/*设置为通信车占用*/
							SetLogicSectionOccStatus(sectionOfAcBuff[sectionOfAcCycle],LOGIC_SECTION_STATE_CT);
						}
						else
						{
							/*设置为非通信车占用*/
							SetLogicSectionOccStatus(sectionOfAcBuff[sectionOfAcCycle],LOGIC_SECTION_STATE_UT);
						}
					}
				}
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
}

/*
* 功能描述： 更新单个计轴内单列车占压逻辑区段
* 参数说明： const UINT16 acId;计轴区段编号  
* 返回值  ： void
*/
void UpdateLogicStatusOfTrain(const UINT16_S acId)
{
	UINT8_S trainOfAcCycle = 0U;
	UINT8_S trainOfAcNum = 0U;
	UINT16_S trainSequ[SIZE_MAX_TRAINOFAC]={0U};
	UINT8_S rtnTrainSequ = 0U;

	trainOfAcNum = GetAcTrainOfAcNum(acId);
	rtnTrainSequ = GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainSequ);

	if (RETURN_SUCCESS == rtnTrainSequ)
	{
		for (trainOfAcCycle = 0U;trainOfAcCycle < trainOfAcNum;trainOfAcCycle++)
		{
			UpdateLogicStatusOfSingleTrain(acId,trainSequ[trainOfAcCycle]);
		}
	}
	else
	{
		/*宕机*/
	}
}

/*
* 功能描述： 更新单个计轴内两列车或者列车与计轴端点之间逻辑区段状态
* 参数说明： const UINT16 acId 待判断计轴ID    
* 返回值  ： void
*/
void UpdateLogicStatusBetweenTrains(const UINT16_S acId)
{
	UINT8_S trainOfAcNum = 0U;
	UINT8_S trainOfAcCycle = 0U;
	UINT8_S rtnTrainSequ = 0U;
	UINT16_S trainSequBuff[SIZE_MAX_TRAINOFAC]={0U};

	MemorySet(&trainSequBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
                 0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));

	trainOfAcNum = GetAcTrainOfAcNum(acId);
	rtnTrainSequ = GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainSequBuff);
	
	if ((DEFAULT_0XFF != trainOfAcNum) && (RETURN_ERROR != rtnTrainSequ))
	{
		for (trainOfAcCycle = 0U;trainOfAcCycle < trainOfAcNum;trainOfAcCycle++)
		{
			if (0U == trainOfAcCycle)
			{
				if (1U == trainOfAcNum)
				{
					/*说明只有一辆车，对其前方至计轴终点逻辑区段进行处理*/
					UpdateLogicStatusBeforeFirstTrain(acId,trainSequBuff[trainOfAcCycle]);

					/*说明为最后一辆车，对其后方至计轴始端逻辑区段进行处理*/
					UpdateLogicStatusRearLastTrain(acId,trainSequBuff[trainOfAcCycle]);
				} 
				else
				{
					/*说明为第一辆车，对其前方至计轴终点逻辑区段进行处理*/
					UpdateLogicStatusBeforeFirstTrain(acId,trainSequBuff[trainOfAcCycle]);
				}
			}
			else if ((trainOfAcNum-1U) == trainOfAcCycle)
			{
				/*说明为最后一辆车，对其后方和前方至计轴始端逻辑区段进行处理*/
				UpdateLogicStatusBetweenTwoTrains(trainSequBuff[trainOfAcCycle - 1U],trainSequBuff[trainOfAcCycle]);
				UpdateLogicStatusRearLastTrain(acId,trainSequBuff[trainOfAcCycle]);	
			}
			else
			{
				/*说明列车为中间列车*/
				UpdateLogicStatusBetweenTwoTrains(trainSequBuff[trainOfAcCycle - 1U],trainSequBuff[trainOfAcCycle]);
			}
		}
	}
	else
	{
		/*宕机*/
	}
}

/*
* 功能描述： 更新2辆列车之间的逻辑区段状态
* 参数说明： const UINT16 trainId1;前车ID
*            const UINT16_S trainId2;后车ID
* 返回值  ： void
*/
void UpdateLogicStatusBetweenTwoTrains(const UINT16_S trainId1,const UINT16_S trainId2)
{
	UINT16_S headLink = 0U;
	UINT32_S headOffset = 0U;
	UINT16_S tailLink = 0U;
	UINT32_S tailOffset = 0U;
	TrainSafeLocStruct trainSafeLocStru1;
	TrainSafeLocStruct trainSafeLocStru2;
	UINT8_S rtnOfTrainSafeLoc1 = 0U;
	UINT8_S rtnOfTrainSafeLoc2 = 0U;
	UINT16_S logicSectionIdBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
	UINT8_S rtnOfLogicSection = 0U;
	UINT8_S rtnOfLogicSectionStatus = 0U;
	UINT8_S logicSectionCycle = 0U;
	UINT8_S direction = 0U;
	UINT8_S cycleDebug = 0U;

	MemorySet(&trainSafeLocStru1,((UINT32_S)(sizeof(TrainSafeLocStruct))),0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));
	MemorySet(&trainSafeLocStru2,((UINT32_S)(sizeof(TrainSafeLocStruct))),0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));
	MemorySet(&logicSectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)));

	rtnOfTrainSafeLoc1 = GetTrainSafeLoc(trainId1,&trainSafeLocStru1);
	rtnOfTrainSafeLoc2 = GetTrainSafeLoc(trainId2,&trainSafeLocStru2);

	if ((RETURN_SUCCESS== rtnOfTrainSafeLoc1) && (RETURN_SUCCESS== rtnOfTrainSafeLoc2))
	{
		/*获取前车的车尾位置和后车的车头位置*/
		headLink = trainSafeLocStru1.TrainTailLink;
		headOffset = trainSafeLocStru1.TrainTailOffset;
		tailLink = trainSafeLocStru2.TrainHeadLink;
		tailOffset = trainSafeLocStru2.TrainHeadOffset;
		direction = GetTrainUnsafeDirection(trainId1);

		rtnOfLogicSection = CheckLogicIdBetweenPoints(0U,tailLink,tailOffset,headLink,headOffset,direction,logicSectionIdBuff);

		if (0U < rtnOfLogicSection)
		{
			/*判断两辆车之间的逻辑区段状态*/
			rtnOfLogicSectionStatus = JudgeLogicStatusBetweenTwoTrains(trainId1,trainId2);

			if (FLAG_SET == rtnOfLogicSectionStatus)
			{
				/*置为紫光带*/
				for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
				{
					SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_UT);
				}
			}
			else if (FLAG_UNSET == rtnOfLogicSectionStatus)
			{
				/*置为空闲*/
				for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
				{
					SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_FREE);
				}
			}
			else
			{
				/*宕机*/
			}
		}
		else
		{
			/*不作处理*/
		}
	}
	else
	{
		/*宕机*/
	}
}

/*
* 功能描述： 更新单个计轴内第一辆车前方逻辑区段状态
* 参数说明： const UINT16 acId;计轴区段编号
*            const UINT16_S trainId;列车ID
* 返回值  ： void
*/
void UpdateLogicStatusBeforeFirstTrain(const UINT16_S acId,const UINT16_S trainId)
{
    UINT16_S headLink = 0U;
    UINT32_S headOffset = 0U;
    UINT16_S tailLink = 0U;
    UINT32_S tailOffset = 0U;
    UINT8_S direction = 0U;
    TrainSafeLocStruct trainSafeLocStru2;
    UINT8_S rtnOfTrainSafeLoc2 = 0U;
    UINT16_S logicSectionIdBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
    UINT8_S rtnOfLogicSection = 0U;
    UINT8_S suspectHead = 0U;
    UINT8_S logicSectionCycle = 0U;
    UINT8_S cycleDebug = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT16_S trainHeadAC = DEFAULT_ZERO;

    MemorySet(&trainSafeLocStru2,((UINT32_S)(sizeof(TrainSafeLocStruct))),0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));
    MemorySet(&logicSectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)),
        0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)));

    /*获取列车方向*/
    direction = GetTrainUnsafeDirection(trainId);

    /*获取计轴终端*/
    if (1U == CheckAcTerminalPosition(acId,(UINT16_S)direction,&headLink,&headOffset))
    {
        rtnOfTrainSafeLoc2 = GetTrainSafeLoc(trainId,&trainSafeLocStru2);

        /*先判断车头位置是否为当前计轴*/
        trainHeadAC = GetTrainTrainHeadAC(trainId);
        if ((RETURN_SUCCESS== rtnOfTrainSafeLoc2)
            && (trainHeadAC == acId))
        {
            /*获取车头位置*/
            /*设置终点为车头安全位置点*/
            tailLink = trainSafeLocStru2.TrainHeadLink;
            tailOffset = trainSafeLocStru2.TrainHeadOffset;	

            rtnOfLogicSection = CheckLogicIdBetweenPoints(2U,tailLink,tailOffset,headLink,headOffset,direction,logicSectionIdBuff);

            if ((0U < rtnOfLogicSection) && (RETURN_UINT8_MAX_VALUE != rtnOfLogicSection))
            {
                suspectHead = GetTrainSuspectHead(trainId);
                trainType = GetTrainType(trainId);

                if ((FLAG_SET == suspectHead) || (TRAIN_MODE_TO_RM0 == trainType))
                {
                    /*有前端可疑标志，置为紫光带*/
                    for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
                    {
                        SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_UT);
                    }
                }
                else if (FLAG_UNSET == suspectHead)
                {
                    /*无前端可疑标志，置为空闲*/
                    for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
                    {
                        SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_FREE);
                    }
                }
                else 
                {
                    /*宕机*/
                }
            }
            else if (0U == rtnOfLogicSection)
            {
                /*不作处理*/
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

    }
    else
    {
        /*宕机*/
    }
}

/*
* 功能描述： 更新单个计轴内最后一辆车后方逻辑区段状态
* 参数说明： const UINT16 acId;计轴区段编号
*            const UINT16_S trainId;列车ID
* 返回值  ： void
*/
void UpdateLogicStatusRearLastTrain(const UINT16_S acId,const UINT16_S trainId)
{
    UINT16_S tailLink = 0U;
    UINT32_S tailOffset = 0U;
    UINT16_S startLink = 0U;
    UINT32_S startOffset = 0U;
    UINT8_S direction = 0U;
    TrainSafeLocStruct trainSafeLocStru1;
    UINT8_S rtnOfTrainSafeLoc1 = 0U;
    UINT16_S logicSectionIdBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
    UINT8_S rtnOfLogicSection = 0U;
    UINT8_S suspectTail = 0U;
    UINT8_S logicSectionCycle = 0U;
    UINT8_S cycleDebug = 0U;
    UINT16_S trainTailAC = DEFAULT_ZERO;

    MemorySet(&trainSafeLocStru1,((UINT32_S)(sizeof(TrainSafeLocStruct))),0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));
    MemorySet(&logicSectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)),
        0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)));

    /*获取列车方向*/
    direction = GetTrainUnsafeDirection(trainId);

    /*获取计轴始端*/
    if (1U == CheckAcTopPosition(acId,(UINT16_S)direction,&startLink,&startOffset))
    {
        rtnOfTrainSafeLoc1 = GetTrainSafeLoc(trainId,&trainSafeLocStru1);

        trainTailAC = GetTrainTrainTailAC(trainId);

        if ((RETURN_SUCCESS== rtnOfTrainSafeLoc1)
            && (trainTailAC == acId))
        {
            /*获取前车的车尾位置*/
            tailLink = trainSafeLocStru1.TrainTailLink;
            tailOffset = trainSafeLocStru1.TrainTailOffset;

            rtnOfLogicSection = CheckLogicIdBetweenPoints(1U,startLink,startOffset,tailLink,tailOffset,direction,logicSectionIdBuff);

            if ((0U < rtnOfLogicSection) && (RETURN_UINT8_MAX_VALUE != rtnOfLogicSection))
            {
                suspectTail = GetTrainSuspectTail(trainId);

                if (FLAG_SET == suspectTail)
                {
                    /*有后端可疑标志，置为紫光带*/
                    for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
                    {
                        SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_UT);
                    }
                }
                else if (FLAG_UNSET == suspectTail)
                {
                    /*无后端可疑标志，置为空闲*/
                    for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
                    {
                        SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_FREE);
                    }
                }
                else 
                {
                    /*宕机*/
                }
            }
            else if (0U == rtnOfLogicSection)
            {
                /*不作处理*/
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
    }
    else
    {
        /*宕机*/
    }
}

/*
* 功能描述： 判断两列通信车之间的逻辑区段状态
* 参数说明： const UINT16 trainId1;前车ID
*            const UINT16_S trainId2;后车ID  
* 返回值  ： 0x55 紫光带
*			 0xaa 空闲			 
*			 0    失败
*/
UINT8_S JudgeLogicStatusBetweenTwoTrains(const UINT16_S trainId1,const UINT16_S trainId2)
{
	UINT8_S suspectTail = 0U;
	UINT8_S suspectHead = 0U;
	UINT8_S rtnValue = 0U;
	
	suspectTail = GetTrainSuspectTail(trainId1);
	suspectHead = GetTrainSuspectHead(trainId2);

	if ((RETURN_ERROR != suspectTail) && (RETURN_ERROR != suspectHead))
	{
		switch (suspectTail)
		{
		case FLAG_SET:
			 /*前方列车有后端可疑，不论后方列车如何，均需要置紫光带*/
			rtnValue = FLAG_SET;
			break;
		case FLAG_UNSET:
			/*前方列车无后端可疑，检查后方列车情况*/
			switch (suspectHead)
			{
			case FLAG_SET:
				rtnValue = FLAG_SET;
				break;
			case FLAG_UNSET:
				rtnValue = FLAG_UNSET;
				break;
			default:
				rtnValue = 0U;
				break;
			}
			break;	
		default:
			rtnValue = 0U;
			break;
		}

	}
	else
	{
		/*失败*/
		rtnValue = 0U;
	}

	return rtnValue;
}

/*
* 功能描述： 在本函数内，对比本周期列车占压的逻辑区段和缓存的上周期占压的逻辑区段，
判断是否有重合部分
* 参数说明： const UINT16 preSectionId[]  上周期占压逻辑区段
*			 const UINT16_S oldSectionId[]   本周期周期占压逻辑区段
*			 UINT8_S preSectionNum      上周期占压逻辑区段数量
*			 UINT8_S oldSectionNum       本周期占压逻辑区段数量
* 返回值  ： RETURN_SUCCESS 重合
*			 RETURN_ERROR 无重合			 
*/
/*逻辑区段重合性判断函数*/
UINT8_S JudgeLogicSectionSuperPosition(const UINT16_S preSectionId[],const UINT16_S oldSectionId[],UINT8_S preSectionNum,UINT8_S oldSectionNum)
{
	UINT8_S preSectionCycle = 0U;   /*循环变量*/
	UINT8_S oldSectionCycle = 0U;   /*循环变量*/
	UINT8_S rtnValue = RETURN_ERROR;

    if ((NULL != preSectionId) && (NULL != oldSectionId))
    {
        /*循环遍历本周期列车占压的逻辑区段*/
        for(preSectionCycle = 0U; preSectionCycle < preSectionNum; preSectionCycle++)
        { 
            /*循环遍历上周期列车占压的逻辑区段*/
            for(oldSectionCycle = 0U; oldSectionCycle < oldSectionNum; oldSectionCycle++)
            {
                /*判断本周期列车占压的逻辑区段和缓存的上周期占压的逻辑区段是否有重合部分*/
                if(preSectionId[preSectionCycle] == oldSectionId[oldSectionCycle])
                {
                    rtnValue = RETURN_SUCCESS;
                    break;
                }
                else
                {
                    /*继续*/
                }
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
* 功能描述： 列车占压逻辑区段连续性检查，当检测到不连续后，控制本ZC宕机
* 参数说明： 无
* 返回值  ： 0:连续性校验失败
*            1:连续性校验成功
*/
UINT8_S JudgeTrainLogicContinuity(void)
{
	UINT8_S cycle = 0U;
	UINT8_S trainNum = 0U;
	UINT16_S trainId = 0U;
	UINT16_S trainHeadAc = 0U;
	UINT16_S trainTailAc = 0U;
	TrainSafeLocStruct trainSafeLoc;
	UINT8_S rtnOfGetTrainSafeLoc = 0U;
	UINT8_S rtnOfLogicSection = 0U;
	UINT8_S direction = 0U;
	UINT16_S logicSectionIdBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
	UINT8_S preSectionNum = 0U;
	UINT16_S preSectionIdBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
	UINT8_S rtnOfPreSection = 0U;
	UINT8_S rtnOfSuperPosition = 0U;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT16_S trainHeadAcInZcId = DEFAULT_ZERO;
    UINT16_S trainTailAcInZcId = DEFAULT_ZERO;

	MemorySet(&trainSafeLoc,((UINT32_S)(sizeof(TrainSafeLocStruct))),0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));
	MemorySet(&logicSectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)));
	MemorySet(&preSectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)),
                0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)));

	trainNum = GetTrainCurSum();

	if (SIZE_MAX_LINE_TRAIN != trainNum)
	{
		for (cycle=0U;cycle < trainNum;cycle++)
		{
			trainId = GetTrainIdOfIndex(cycle);
			trainHeadAc = GetTrainTrainHeadAC(trainId);
			trainTailAc = GetTrainTrainTailAC(trainId);
			rtnOfGetTrainSafeLoc = GetTrainSafeLoc(trainId,&trainSafeLoc);
			direction = GetTrainUnsafeDirection(trainId);

			/*获取列车上周期逻辑区段*/
			preSectionNum = GetTrainPreSectionNum(trainId);
			rtnOfPreSection = GetTrainPreSectionId(trainId,preSectionIdBuff);

			if ((RETURN_ERROR != trainId) 
				&& (RETURN_ERROR != trainHeadAc)
				&& (RETURN_ERROR != trainTailAc) 
				&& (RETURN_SUCCESS == rtnOfGetTrainSafeLoc) 
				&& (DEFAULT_ZERO != direction)
				&& (RETURN_UINT8_MAX_VALUE != preSectionNum) 
				&& (RETURN_SUCCESS == rtnOfPreSection))
			{
				/*查询列车占压的逻辑区段*/
				rtnOfLogicSection = CheckLogicIdBetweenPoints(3U,trainSafeLoc.TrainTailLink,trainSafeLoc.TrainTailOffset,
					trainSafeLoc.TrainHeadLink,trainSafeLoc.TrainHeadOffset,direction,logicSectionIdBuff);

				if (DEFAULT_0XFF != rtnOfLogicSection)
				{
                    localZcId = GetLocalZcId();
                    trainHeadAcInZcId =  GetAcBelongZcId(trainHeadAc);
                    trainTailAcInZcId = GetAcBelongZcId(trainTailAc);

					if ((localZcId == trainHeadAcInZcId) || (localZcId == trainTailAcInZcId))
					{
						/*仅当列车车头或者车尾属于本ZC时，才进行逻辑区段连续性判断*/
						if (DEFAULT_ZERO != preSectionNum)
						{
							rtnOfSuperPosition = JudgeLogicSectionSuperPosition(preSectionIdBuff,logicSectionIdBuff,preSectionNum,rtnOfLogicSection);

							if (RETURN_ERROR == rtnOfSuperPosition)
							{
								/*执行宕机操作*/
								rtnValue = RETURN_ERROR;
								breakFlag = FLAG_SET;
								break;
							}
							else
							{
								SetTrainPreSectionId(trainId,logicSectionIdBuff,rtnOfLogicSection);
							}
						} 
						else
						{
							/*设置新的占用类型*/
							SetTrainPreSectionId(trainId,logicSectionIdBuff,rtnOfLogicSection);
						}
					}
					else
					{
						/*不作逻辑区段连续性判断*/
					}
				}
				else
				{
					/*列车紧急制动*/
					SetTrainToModeToRM0(trainId);
					LogPrintf(1u,"%d-B6\n",trainId);
				}
			}
			else
			{
				/*列车紧急制动*/
				SetTrainToModeToRM0(trainId);
				LogPrintf(1u,"%d-B7\n",trainId);
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
		/*宕机*/
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}


