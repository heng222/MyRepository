/************************************************************************
*
* �ļ���   ��  LogicSectionLogicManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �߼������߼�����
* ��  ע   ��  ��
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
* ���������� ������϶�Ӧ�ĵ����߼�������Ϣ
* ����˵���� const UINT16 logicSectionId���߼�����ID    
* ����ֵ  �� void  
*/
void InitFailureSingleLogicSetion(const UINT16_S logicSectionId)
{
	SetLogicSectionOccStatus(logicSectionId,LOGIC_SECTION_STATE_UT);
}

/*
* ���������� ����ͨ�Ź���Ci��Ӧ���߼�������Ϣ
* ����˵���� const UINT16 ciId��ͨ�Ź��ϵ�CIID    
* ����ֵ  �� void  
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
            /*������*/
		}
	}
}

/*
* ���������� �߼����θ���ռ��״̬
* ����˵���� void    
* ����ֵ  �� void
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
			/*���ڱ�ZC�ڵļ�������,���¸ü��������ڵ��߼�����ռ��״̬*/
			UpdateSingalAcLogicSection(acId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� ���µ������������߼�����ռ��״̬
* ����˵���� const UINT16 acId;�������α��   
* ����ֵ  �� void
*/
void UpdateSingalAcLogicSection(const UINT16_S acId)
{
	/*��ʼ�������������߼�����״̬*/
	InitLogicStatusOfSingleAc(acId);

	/*�����г�ռѹ�߼�����״̬*/
	UpdateLogicStatusOfTrain(acId);

	/*�����г�֮���߼�����״̬*/
	UpdateLogicStatusBetweenTrains(acId);
}

/*
* ���������� ��ʼ�������������߼�����״̬ΪUT
* ����˵���� const UINT16 acId;�������α��   
* ����ֵ  �� void
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

	/*��ѯ�������߼���������*/
	rtnOfsectionOfAcNum = GetLineAcIncludeLogicSectionInfo(acId,&sectionOfAcNum,sectionOfAcBuff);

	if (RETURN_SUCCESS == rtnOfsectionOfAcNum)
	{
		/*��ȡ��������ռ��״̬*/
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
				/*��ʼ��Ϊ����*/
				SetLogicSectionOccStatus(sectionOfAcBuff[sectionOfAcCycle],LOGIC_SECTION_STATE_FREE);
			}
			else
			{
				/*��ʼ��Ϊ��ͨ�ų�ռ��*/
				SetLogicSectionOccStatus(sectionOfAcBuff[sectionOfAcCycle],LOGIC_SECTION_STATE_UT);
			}
		}
	}
	else
	{
		/*崻�*/
	}
}

/*
* ���������� ���µ��������ڵ������г�ռѹ�߼�����
* ����˵���� const UINT16 acId;�������α�� 
*            const UINT16_S trainId;�г�ID   
* ����ֵ  �� void
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
		/*��ѯ�������߼���������*/
		rtnOfsectionOfAcNum = GetLineAcIncludeLogicSectionInfo(acId,&sectionOfAcNum,sectionOfAcBuff);

		/*�ɹ�,��ѯ�г�ռѹ���߼�����*/
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
						/*�ҵ��г�ռѹ�ļ������Σ������г�����������Ӧ���߼�����*/
						if ((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType))
						{
							/*����Ϊͨ�ų�ռ��*/
							SetLogicSectionOccStatus(sectionOfAcBuff[sectionOfAcCycle],LOGIC_SECTION_STATE_CT);
						}
						else
						{
							/*����Ϊ��ͨ�ų�ռ��*/
							SetLogicSectionOccStatus(sectionOfAcBuff[sectionOfAcCycle],LOGIC_SECTION_STATE_UT);
						}
					}
				}
			}
		}
		else
		{
			/*崻�*/
		}
	}
	else
	{
		/*崻�*/
	}
}

/*
* ���������� ���µ��������ڵ��г�ռѹ�߼�����
* ����˵���� const UINT16 acId;�������α��  
* ����ֵ  �� void
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
		/*崻�*/
	}
}

/*
* ���������� ���µ������������г������г������˵�֮���߼�����״̬
* ����˵���� const UINT16 acId ���жϼ���ID    
* ����ֵ  �� void
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
					/*˵��ֻ��һ����������ǰ���������յ��߼����ν��д���*/
					UpdateLogicStatusBeforeFirstTrain(acId,trainSequBuff[trainOfAcCycle]);

					/*˵��Ϊ���һ�����������������ʼ���߼����ν��д���*/
					UpdateLogicStatusRearLastTrain(acId,trainSequBuff[trainOfAcCycle]);
				} 
				else
				{
					/*˵��Ϊ��һ����������ǰ���������յ��߼����ν��д���*/
					UpdateLogicStatusBeforeFirstTrain(acId,trainSequBuff[trainOfAcCycle]);
				}
			}
			else if ((trainOfAcNum-1U) == trainOfAcCycle)
			{
				/*˵��Ϊ���һ����������󷽺�ǰ��������ʼ���߼����ν��д���*/
				UpdateLogicStatusBetweenTwoTrains(trainSequBuff[trainOfAcCycle - 1U],trainSequBuff[trainOfAcCycle]);
				UpdateLogicStatusRearLastTrain(acId,trainSequBuff[trainOfAcCycle]);	
			}
			else
			{
				/*˵���г�Ϊ�м��г�*/
				UpdateLogicStatusBetweenTwoTrains(trainSequBuff[trainOfAcCycle - 1U],trainSequBuff[trainOfAcCycle]);
			}
		}
	}
	else
	{
		/*崻�*/
	}
}

/*
* ���������� ����2���г�֮����߼�����״̬
* ����˵���� const UINT16 trainId1;ǰ��ID
*            const UINT16_S trainId2;��ID
* ����ֵ  �� void
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
		/*��ȡǰ���ĳ�βλ�úͺ󳵵ĳ�ͷλ��*/
		headLink = trainSafeLocStru1.TrainTailLink;
		headOffset = trainSafeLocStru1.TrainTailOffset;
		tailLink = trainSafeLocStru2.TrainHeadLink;
		tailOffset = trainSafeLocStru2.TrainHeadOffset;
		direction = GetTrainUnsafeDirection(trainId1);

		rtnOfLogicSection = CheckLogicIdBetweenPoints(0U,tailLink,tailOffset,headLink,headOffset,direction,logicSectionIdBuff);

		if (0U < rtnOfLogicSection)
		{
			/*�ж�������֮����߼�����״̬*/
			rtnOfLogicSectionStatus = JudgeLogicStatusBetweenTwoTrains(trainId1,trainId2);

			if (FLAG_SET == rtnOfLogicSectionStatus)
			{
				/*��Ϊ�Ϲ��*/
				for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
				{
					SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_UT);
				}
			}
			else if (FLAG_UNSET == rtnOfLogicSectionStatus)
			{
				/*��Ϊ����*/
				for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
				{
					SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_FREE);
				}
			}
			else
			{
				/*崻�*/
			}
		}
		else
		{
			/*��������*/
		}
	}
	else
	{
		/*崻�*/
	}
}

/*
* ���������� ���µ��������ڵ�һ����ǰ���߼�����״̬
* ����˵���� const UINT16 acId;�������α��
*            const UINT16_S trainId;�г�ID
* ����ֵ  �� void
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

    /*��ȡ�г�����*/
    direction = GetTrainUnsafeDirection(trainId);

    /*��ȡ�����ն�*/
    if (1U == CheckAcTerminalPosition(acId,(UINT16_S)direction,&headLink,&headOffset))
    {
        rtnOfTrainSafeLoc2 = GetTrainSafeLoc(trainId,&trainSafeLocStru2);

        /*���жϳ�ͷλ���Ƿ�Ϊ��ǰ����*/
        trainHeadAC = GetTrainTrainHeadAC(trainId);
        if ((RETURN_SUCCESS== rtnOfTrainSafeLoc2)
            && (trainHeadAC == acId))
        {
            /*��ȡ��ͷλ��*/
            /*�����յ�Ϊ��ͷ��ȫλ�õ�*/
            tailLink = trainSafeLocStru2.TrainHeadLink;
            tailOffset = trainSafeLocStru2.TrainHeadOffset;	

            rtnOfLogicSection = CheckLogicIdBetweenPoints(2U,tailLink,tailOffset,headLink,headOffset,direction,logicSectionIdBuff);

            if ((0U < rtnOfLogicSection) && (RETURN_UINT8_MAX_VALUE != rtnOfLogicSection))
            {
                suspectHead = GetTrainSuspectHead(trainId);
                trainType = GetTrainType(trainId);

                if ((FLAG_SET == suspectHead) || (TRAIN_MODE_TO_RM0 == trainType))
                {
                    /*��ǰ�˿��ɱ�־����Ϊ�Ϲ��*/
                    for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
                    {
                        SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_UT);
                    }
                }
                else if (FLAG_UNSET == suspectHead)
                {
                    /*��ǰ�˿��ɱ�־����Ϊ����*/
                    for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
                    {
                        SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_FREE);
                    }
                }
                else 
                {
                    /*崻�*/
                }
            }
            else if (0U == rtnOfLogicSection)
            {
                /*��������*/
            }
            else
            {
                /*崻�*/
            }
        }
        else
        {
            /*崻�*/
        }

    }
    else
    {
        /*崻�*/
    }
}

/*
* ���������� ���µ������������һ�������߼�����״̬
* ����˵���� const UINT16 acId;�������α��
*            const UINT16_S trainId;�г�ID
* ����ֵ  �� void
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

    /*��ȡ�г�����*/
    direction = GetTrainUnsafeDirection(trainId);

    /*��ȡ����ʼ��*/
    if (1U == CheckAcTopPosition(acId,(UINT16_S)direction,&startLink,&startOffset))
    {
        rtnOfTrainSafeLoc1 = GetTrainSafeLoc(trainId,&trainSafeLocStru1);

        trainTailAC = GetTrainTrainTailAC(trainId);

        if ((RETURN_SUCCESS== rtnOfTrainSafeLoc1)
            && (trainTailAC == acId))
        {
            /*��ȡǰ���ĳ�βλ��*/
            tailLink = trainSafeLocStru1.TrainTailLink;
            tailOffset = trainSafeLocStru1.TrainTailOffset;

            rtnOfLogicSection = CheckLogicIdBetweenPoints(1U,startLink,startOffset,tailLink,tailOffset,direction,logicSectionIdBuff);

            if ((0U < rtnOfLogicSection) && (RETURN_UINT8_MAX_VALUE != rtnOfLogicSection))
            {
                suspectTail = GetTrainSuspectTail(trainId);

                if (FLAG_SET == suspectTail)
                {
                    /*�к�˿��ɱ�־����Ϊ�Ϲ��*/
                    for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
                    {
                        SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_UT);
                    }
                }
                else if (FLAG_UNSET == suspectTail)
                {
                    /*�޺�˿��ɱ�־����Ϊ����*/
                    for (logicSectionCycle=0U;logicSectionCycle<rtnOfLogicSection;logicSectionCycle++)
                    {
                        SetLogicSectionOccStatus(logicSectionIdBuff[logicSectionCycle],LOGIC_SECTION_STATE_FREE);
                    }
                }
                else 
                {
                    /*崻�*/
                }
            }
            else if (0U == rtnOfLogicSection)
            {
                /*��������*/
            }
            else
            {
                /*崻�*/
            }
        } 
        else
        {
            /*崻�*/
        }
    }
    else
    {
        /*崻�*/
    }
}

/*
* ���������� �ж�����ͨ�ų�֮����߼�����״̬
* ����˵���� const UINT16 trainId1;ǰ��ID
*            const UINT16_S trainId2;��ID  
* ����ֵ  �� 0x55 �Ϲ��
*			 0xaa ����			 
*			 0    ʧ��
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
			 /*ǰ���г��к�˿��ɣ����ۺ��г���Σ�����Ҫ���Ϲ��*/
			rtnValue = FLAG_SET;
			break;
		case FLAG_UNSET:
			/*ǰ���г��޺�˿��ɣ������г����*/
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
		/*ʧ��*/
		rtnValue = 0U;
	}

	return rtnValue;
}

/*
* ���������� �ڱ������ڣ��Աȱ������г�ռѹ���߼����κͻ����������ռѹ���߼����Σ�
�ж��Ƿ����غϲ���
* ����˵���� const UINT16 preSectionId[]  ������ռѹ�߼�����
*			 const UINT16_S oldSectionId[]   ����������ռѹ�߼�����
*			 UINT8_S preSectionNum      ������ռѹ�߼���������
*			 UINT8_S oldSectionNum       ������ռѹ�߼���������
* ����ֵ  �� RETURN_SUCCESS �غ�
*			 RETURN_ERROR ���غ�			 
*/
/*�߼������غ����жϺ���*/
UINT8_S JudgeLogicSectionSuperPosition(const UINT16_S preSectionId[],const UINT16_S oldSectionId[],UINT8_S preSectionNum,UINT8_S oldSectionNum)
{
	UINT8_S preSectionCycle = 0U;   /*ѭ������*/
	UINT8_S oldSectionCycle = 0U;   /*ѭ������*/
	UINT8_S rtnValue = RETURN_ERROR;

    if ((NULL != preSectionId) && (NULL != oldSectionId))
    {
        /*ѭ�������������г�ռѹ���߼�����*/
        for(preSectionCycle = 0U; preSectionCycle < preSectionNum; preSectionCycle++)
        { 
            /*ѭ�������������г�ռѹ���߼�����*/
            for(oldSectionCycle = 0U; oldSectionCycle < oldSectionNum; oldSectionCycle++)
            {
                /*�жϱ������г�ռѹ���߼����κͻ����������ռѹ���߼������Ƿ����غϲ���*/
                if(preSectionId[preSectionCycle] == oldSectionId[oldSectionCycle])
                {
                    rtnValue = RETURN_SUCCESS;
                    break;
                }
                else
                {
                    /*����*/
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
* ���������� �г�ռѹ�߼����������Լ�飬����⵽�������󣬿��Ʊ�ZC崻�
* ����˵���� ��
* ����ֵ  �� 0:������У��ʧ��
*            1:������У��ɹ�
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

			/*��ȡ�г��������߼�����*/
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
				/*��ѯ�г�ռѹ���߼�����*/
				rtnOfLogicSection = CheckLogicIdBetweenPoints(3U,trainSafeLoc.TrainTailLink,trainSafeLoc.TrainTailOffset,
					trainSafeLoc.TrainHeadLink,trainSafeLoc.TrainHeadOffset,direction,logicSectionIdBuff);

				if (DEFAULT_0XFF != rtnOfLogicSection)
				{
                    localZcId = GetLocalZcId();
                    trainHeadAcInZcId =  GetAcBelongZcId(trainHeadAc);
                    trainTailAcInZcId = GetAcBelongZcId(trainTailAc);

					if ((localZcId == trainHeadAcInZcId) || (localZcId == trainTailAcInZcId))
					{
						/*�����г���ͷ���߳�β���ڱ�ZCʱ���Ž����߼������������ж�*/
						if (DEFAULT_ZERO != preSectionNum)
						{
							rtnOfSuperPosition = JudgeLogicSectionSuperPosition(preSectionIdBuff,logicSectionIdBuff,preSectionNum,rtnOfLogicSection);

							if (RETURN_ERROR == rtnOfSuperPosition)
							{
								/*ִ��崻�����*/
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
							/*�����µ�ռ������*/
							SetTrainPreSectionId(trainId,logicSectionIdBuff,rtnOfLogicSection);
						}
					}
					else
					{
						/*�����߼������������ж�*/
					}
				}
				else
				{
					/*�г������ƶ�*/
					SetTrainToModeToRM0(trainId);
					LogPrintf(1u,"%d-B6\n",trainId);
				}
			}
			else
			{
				/*�г������ƶ�*/
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
		/*崻�*/
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}


