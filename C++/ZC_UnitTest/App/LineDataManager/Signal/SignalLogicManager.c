/************************************************************************
*
* �ļ���   ��  SignalLogicManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ά������
* ��  ע   ��  ��
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
* ���������� ����ͨ�Ź���Ci��Ӧ�ĵ����źŻ���Ϣ
* ����˵���� const UINT16 signalId���źŻ�ID    
* ����ֵ  �� void  
*/
void InitFailureSingleSignal(const UINT16_S signalId)
{
	SetSignalCrossStatus(signalId,SIGNAL_TRAIN_NOT_CROSS);
	SetSignalStatus(signalId,SIGNAL_STATE_STOP);
	SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
}

/*
* ���������� ����ͨ�Ź���Ci��Ӧ���źŻ���Ϣ
* ����˵���� const UINT16 ciId������ID    
* ����ֵ  �� void  
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
			/*����״̬Ϊ��ȫ̬*/
			InitFailureSingleSignal(signalId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� ����ͨ�Ź���NZc��Ӧ���źŻ���Ϣ
* ����˵���� const UINT16 nZCId    
* ����ֵ  �� void  
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
			/*����״̬Ϊ��ȫ̬*/
			InitFailureSingleSignal(signalId);
		} 
		else
		{
            /*������*/
		}
	}
}

/*
* ���������� �źŻ��������
* ����˵���� void
* ����ֵ  �� void     
*/
void SignalControl(void)
{
	UINT16_S signalCycle = 0U;
	UINT16_S tempSignalId = 0U;
    UINT16_S localZcId = DEFAULT_ZERO;           /* ����ZC��ID */
    UINT16_S signalBelongZcId = DEFAULT_ZERO;    /* �źŻ�������ZC��ID */
    UINT8_S signalLightOffType = DEFAULT_ZERO;   /* �Ƿ���Ҫ�ж���Ʊ�־ */ 

    localZcId = GetLocalZcId();

	for (signalCycle = 0U; signalCycle < GetSignalSum(); signalCycle++)
	{
		/*��ȡ�źŻ�ID*/
		tempSignalId = GetSignalId(signalCycle);        
        signalBelongZcId = (UINT16_S)(GetSignalBelongZcId(tempSignalId));
        signalLightOffType = GetSignalLightOffType(tempSignalId);

		/*�ж��Ƿ���ҪΪ���źŻ�ID������������*/
		if ((localZcId == signalBelongZcId) && (FLAG_SET == signalLightOffType))
		{
			SignalLightAndOffDeal(tempSignalId);
		}
		else
		{
			/*������*/
		}
	}
}

/*
* ���������� �źŻ����������
* ����˵���� UINT16 signalId,�źŻ�Id
* ����ֵ  �� void      
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

	/*��ѯ�źŻ�������ΰ����ļ�������*/		
	if (RETURN_ERROR == CalculateAcOfSignalLighten(signalId, &acNum, acIdOfApproachBuff))
	{
		SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
	}
	else
	{
		/*������������*/
		for (acCycle = 0U; acCycle < acNum; acCycle++)
		{
			if (AC_OCC_STATUS == GetAcStatusNow(acIdOfApproachBuff[acCycle]))/*�жϼ����Ƿ�ռ��*/
			{
				/*�жϼ������Ƿ��г�*/
				if (0U != GetAcTrainOfAcNum(acIdOfApproachBuff[acCycle]))
				{
					/*���������ñ�־*/
					setFlag = FLAG_SET;

					/*��ȡ�г�����*/
					if (RETURN_SUCCESS == GetAcTrainSequenceBuff(acIdOfApproachBuff[acCycle],SIZE_MAX_TRAINOFAC,tempTrainIdBuff))
					{
                        trainType = GetTrainType(tempTrainIdBuff[0]);

                        if ((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType))
                        {
                            /*��ѯ�źŻ�����*/
                            if (RETURN_ERROR != GetSignalProtectDir(signalId))
                            {
                                /*�źŻ������������г����з����Ƿ�һ��*/
                                if (GetSignalProtectDir(signalId) == GetTrainUnsafeDirection(tempTrainIdBuff[0]))
                                {
                                    /*����һ��*/
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
                                    /*����Ϊ��״̬*/
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
                            /*��CBTC��*/
                            SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
                            breakFlag = FLAG_SET;
                        }
                    }                   
					else
					{
                        /* �г����ǻ�ȡ�г�����ʧ�� */
                        SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
					}									
				}
				else
				{
					/*�޳������Ƿ��ͨ�ų�ռ��*/
					if (AC_UT_OCC_STATUS == GetAcUtFlag(acIdOfApproachBuff[acCycle]))
					{
						/*���������ñ�־*/
						setFlag = FLAG_SET;

						/*�������η�ͨ���г�ռ��*/
						SetSignalLightOffStatus(signalId,SIGNAL_LIGHT_COMMAND);
						breakFlag = FLAG_SET;
					} 
					else
					{
						/*������*/
					}
				}
			}
			else
			{
				/*������δռ�ã�������*/
			}

            if (FLAG_SET == breakFlag)
            {
                break;
            }
		}

		
		if (0U == setFlag)
		{
			/*�ж��źŻ�������״̬�źŻ������ΪĬ��ֵ*/
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
            /*������*/
		}
	}
}

/*
* ���������� �����źŻ����������ʱ�ļ�����������
* ����˵���� const UINT16 signalId,�źŻ�Id
*            UINT8_S *acNum,������������
*            UINT16_S acIdBuff[],��������ID����
* ����ֵ  �� 0: ����ʧ��
*			 1: ����ɹ�      
*/
UINT8_S CalculateAcOfSignalLighten(const UINT16_S signalId,UINT8_S *acNum,UINT16_S acIdBuff[])
{
	UINT8_S retVal = RETURN_ERROR;/*��������ֵ*/
	UINT16_S signalOutsideAcId = DEFAULT_ZERO;
	UINT8_S tempAcNum = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S signalProtectionDir = DEFAULT_ZERO;
	UINT16_S nextAcId = DEFAULT_ZERO;
	UINT32_S singleAcLength = DEFAULT_ZERO;
	UINT32_S allAcLength = DEFAULT_ZERO;
    UINT8_S flag = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;  /* ����ѭ����־ */
    UINT8_S checkRtnValue = DEFAULT_ZERO; /* ��ѯ�󷽼������η���ֵ */
	UINT8_S checkAcPosRtn = DEFAULT_ZERO;

    if ((NULL != acNum) && (NULL != acIdBuff))
    {
        /*��ѯ�źŻ��ⷽ��һ����*/
		if (1U == CheckOutsideAcOfSignal(signalId,&signalOutsideAcId))
		{
			checkAcPosRtn = JudgeAcOfSwitchPosInNeed(signalOutsideAcId);
		}
		else
		{
            /* ������ */  
		}

		/*�жϼ��������Ƿ��������״̬*/
        if (1U == checkAcPosRtn)
        {
            if (DEFAULT_ZERO == signalOutsideAcId)
            {
                /*��ȡʧ��,ֱ�ӷ���ʧ��*/
                flag = FLAG_SET;		
            } 
            else
            {
                /*����źŻ��ⷽ��һ����*/
                acIdBuff[tempAcNum] = signalOutsideAcId;
                tempAcNum++;

                /*��ȡ�źŻ���������*/
                signalProtectionDir = GetSignalProtectDir(signalId);

                for (cycle = DEFAULT_ZERO;cycle < (SIGNAL_LIGHT_OFF_AC_NUM_MAX - 1U);cycle++)
                {
                    /*��ʼ��*/
                    nextAcId = DEFAULT_ZERO;
                    singleAcLength = DEFAULT_ZERO;

                    /*��ȡ�������γ���*/
                    if (1U == CheckAcLength(acIdBuff[tempAcNum-1U],&singleAcLength))
                    {
                        /*�ۼ��ܳ���*/
                        allAcLength = allAcLength + singleAcLength;

                        if (allAcLength >= GetSignalLightLength())
                        {
                            breakFlag = FLAG_SET;
                        } 
                        else
                        {
                            /*��ѯ��һ����������*/
                            checkRtnValue = CheckRearACStatus(acIdBuff[tempAcNum-1U],signalProtectionDir,&nextAcId);

                            if ((1U == checkRtnValue) && (DEFAULT_ZERO != nextAcId))
                            {
                                acIdBuff[tempAcNum] = nextAcId;
                                tempAcNum++;
                            } 
                            else if((2U == checkRtnValue) || (3U == checkRtnValue))
                            {
                                /* ������·��ͷ���ߵ���ԭ��ʧ��,����ѭ��,���سɹ� */                            
                                breakFlag = FLAG_SET;
                            }
                            else
                            {
                                /*��ȡʧ��,����ѭ��,����ʧ��*/
                                breakFlag = FLAG_SET;
                                flag = FLAG_SET;
                            }
                        }
                    } 
                    else
                    {
                        /*��ȡʧ��,����ѭ��,����ʧ��*/
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
            /*��ȡʧ��,ֱ�ӷ���ʧ��*/
            flag = FLAG_SET;
        }

        /*�����ѯ����*/
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
* ���������� �г����ź��ж�
* ����˵���� ��
* ����ֵ  �� ��     
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
		
		/*�ж��г���ͷ���ڼ����Ƿ����ڱ�ZC�򹲹�����*/
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

                    /*��ѯ���г����з���һ�µ�ǰ���źŻ�*/
                    if (RETURN_SUCCESS == CheckPointNearestSignalBaseDir(tempDirection,tempTrainLink, tempTrainOffset, &tempFrontSignalId))
                    {
                        trainFrontSignalId = GetTrainFrontSignal(tempTrainId);

                        signalStatus = GetSignalStatus(tempFrontSignalId);
                        signalCrashType = GetSignalCrashType(tempFrontSignalId);
                        signalProtectDir = GetSignalProtectDir(tempFrontSignalId);

                        if (0U == trainFrontSignalId)
                        {
                            /*�жϱ������źŻ�״̬*/				
                            if ((0U != tempFrontSignalId) 
                                && (SIGNAL_STATE_STOP == signalStatus) 
                                && (FLAG_SET == signalCrashType)
                                && (tempDirection == signalProtectDir))					
                            {
                                /*��ǰ�źŻ�״̬Ϊ��ֹ�ź�*/
                                SetTrainFrontSignal(tempTrainId,tempFrontSignalId);						
                            }
                            else
                            {
                                /*�����źţ�������*/
                            }
                        }
                        else
                        {
                            if (tempFrontSignalId == trainFrontSignalId)
                            {
                                if (SIGNAL_STATE_PASS == GetSignalStatus(trainFrontSignalId))
                                {
                                    /*�ѿ��ţ�������д��źŷ���*/
                                    SetTrainFrontSignal(tempTrainId,DEFAULT_ZERO);
                                }
                                else
                                {
                                    /*δ����*/
                                }
                            }
                            else/*������ǰ���źŻ������仯*/
                            {						
                                /*��ѯ�����ڵĺ���źŻ�������״̬*/
                                if (SIGNAL_STATE_STOP == GetSignalStatus(trainFrontSignalId))
                                {
                                    /*��ѯ�г�ǰ�������źŻ���λ��*/
                                    tempSignalLink = 0U;
                                    tempSignalOffset = 0U;

                                    if (1U == CheckSignalPostion(GetTrainFrontSignal(tempTrainId), &tempSignalLink, &tempSignalOffset))
                                    {
                                        /*��ѯ������Ⱥ�˳��*/
                                        returnValue = CheckLocRelationBetweenTwoPoints(tempSignalLink, tempSignalOffset, tempTrainLink, tempTrainOffset, tempDirection);

                                        if ((1U == returnValue) || (0U == returnValue))
                                        {
                                            /*˵����ʱ�г���ͷ��δԽ���źŻ���Ƚ������Ⱥ�˳��ʧ��, ������д��ź��ж�*/
                                        }
                                        else
                                        {
                                            /*˵����ʱ�г���ͷ��ȫλ����Խ���źŻ�*/
                                            /*��ѯ�źź󷽵�һ����������*/
                                            if (1U == CheckFirstAcOfSignal(trainFrontSignalId,&tempAcAfterSignalId))
                                            {
                                                if (0U != tempAcAfterSignalId)
                                                {
                                                    if (AC_FREE_STATUS == GetAcStatusNow(tempAcAfterSignalId))/*�жϱ������Ƿ�Ϊ����*/
                                                    {
                                                        /*ֻ���г�����Խ���źŻ������д��ź�*/
                                                    }
                                                    else
                                                    {
                                                        /*˵����ʱ�г��Ѿ������źŻ��ڷ��ĵ�һ���������Σ��жϸ��г����ź�*/	
                                                        /*���Ӵ��ź�ʱ��ķ������*/
                                                        if(tempDirection == GetSignalProtectDir(trainFrontSignalId))
                                                        {
                                                            SetTrainSignalProtection(tempTrainId,FLAG_SET);
                                                        }
                                                        else
                                                        {
                                                            /*������*/
                                                        }

                                                        LogPrintf(1U,"429 429 trainDir=%d,signalProDir=%d!\n",tempDirection, GetSignalProtectDir(trainFrontSignalId));
                                                    }
                                                }
                                                else
                                                {
                                                    /*ʧ�ܣ���Ϊ�г����ź�*/
                                                    SetTrainSignalProtection(tempTrainId,FLAG_SET);
                                                    LogPrintf(1U,"436 436 !\n");
                                                }
                                            }								
                                        }
                                    }							
                                }
                                else
                                {
                                    /*Ϊ�˽�����������,��GetTrainSignalProtection��ΪGetSignalCrashType*/
                                    /*�жϱ������г�ǰ���źŻ�״̬*/
                                    if ((0U != tempFrontSignalId) 
                                        && (SIGNAL_STATE_STOP == signalStatus) 
                                        && (FLAG_SET == signalCrashType)
                                        && (tempDirection == signalProtectDir))
                                    {
                                        /*˵�����źŻ���ǰ״̬Ϊ��ֹ�źţ������źŻ�����Ϊ�г�ǰ����Ҫ�������źŻ�*/
                                        SetTrainFrontSignal(tempTrainId,tempFrontSignalId);
                                    }
                                    else
                                    {
                                        /*���г�ǰ�������źŻ����*/
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
				/*������������������*/
				/* LogPrintf(1U,"3.29-453:SID=%d,Status=%d\n",GetTrainFrontSignal(tempTrainId), GetTrainStatus(tempTrainId)); */
				
				/*,Ϊ�˽���ڹ���ׯ�����۷���ʱ���źŻ�����*/
				/*����г������۷�״̬,���Ѿ���������Ҫ�������źŻ�ʱ��,������źŻ�����Ϊ����Ҫ����*/
				if(TRAIN_STATE_REVERSE == trainStatus)
				{
					if(DEFAULT_ZERO != GetTrainFrontSignal(tempTrainId))
					{
						/*���г�ǰ�������źŻ����*/
						SetTrainFrontSignal(tempTrainId,0U);
					}
				}
				else
				{
                    /*������*/
				}
			}
		}
		else
		{
			/*���ڱ�ZC��Ͻ��Χ��������*/
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
* ���������� �����г���ѹ�źŻ�״̬
* ����˵���� ��
* ����ֵ  �� ��      
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
            /*������*/
		}
	}
}

/*
* ���������� �����г���ѹ�źŻ�״̬����
* ����˵���� UINT16 signalId,�źŻ�Id
* ����ֵ  �� 0: ����ʧ��
*			 1: ����ɹ�      
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
	UINT8_S tHeadAndSigLoc = DEFAULT_ZERO;  /* �г���ͷ���źŻ�λ�ù�ϵ */
	UINT8_S tTailAndSigLoc = DEFAULT_ZERO;  /* �г���β���źŻ�λ�ù�ϵ */
	UINT16_S trainLength = DEFAULT_ZERO;    /* �г����� */
	UINT16_S trainAcrossSignalDis = DEFAULT_ZERO;  /* �г���ѹ�źž��� */
	
	/*��ѯ����źŻ���λ��*/
	if (1U == CheckSignalPostion(signalId,&tempObsLink,&tempObsOffset))
	{
        /* ��ȡ�г���ѹ�źž��� */
        trainAcrossSignalDis = GetTrainAcrossSignalDis();

        for (trainCycle = 0U; trainCycle < GetTrainCurSum(); trainCycle++)
        {
            tempTrainId = GetTrainIdOfIndex(trainCycle);

            /*�����ѹ�жϻ�׼�����ڵ�link��offset*/
            safeLocRtn = GetTrainSafeLoc(tempTrainId, &trainSafeLocStru);
            trainDir = GetTrainUnsafeDirection(tempTrainId);
            trainType = GetTrainType(tempTrainId);

            /* �źŻ��������� */
            signalProtectDir = GetSignalProtectDir(signalId);

            /*�жϱ��г��Ƿ�ΪCBTC������г�*/        
            if (((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType))
                && (signalProtectDir == trainDir))
            {
                /*�жϸ��źŻ��Ƿ�߱�ĳ���г���ѹǰ������*/
                needJudgeFlag = JudgeTrainNeedSingalLoc(signalId,tempTrainId);

                if ((RETURN_SUCCESS == safeLocRtn) && (RETURN_SUCCESS == needJudgeFlag))
                {
                    /* ��ȡ�г���ȫ���ǰ�ȫλ�óɹ�����Ҫ�жϿ�ѹ */
                    trainLength = GetTrainLength(tempTrainId);

                    disOfTrainAcross = ((UINT32_S)trainLength) - ((UINT32_S)trainAcrossSignalDis);

                    if (3U == CheckNextPointOnDistance(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,
                        trainDir,disOfTrainAcross,&tempHeadLink,&tempHeadOffset,&errorSwitchId))
                    {
                        tHeadAndSigLoc = CheckLocRelationBetweenTwoPoints(tempHeadLink,tempHeadOffset,tempObsLink,tempObsOffset,trainDir);
                        tTailAndSigLoc = CheckLocRelationBetweenTwoPoints(tempObsLink,tempObsOffset,trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,trainDir);

                        /* �źŻ����г���ͷ�ͳ�β�м� */
                        if ((0x01U == tHeadAndSigLoc) && (0x01U == tTailAndSigLoc))
                        {
                            /*��ѯ�źŻ��ڷ���һ����������ID*/
                            if (1U == CheckFirstAcOfSignal(signalId,&tempACAfterSignalID))
                            {
                                /*LogPrintf(1U,"12.003 acId=%d,acState=%d\n",tempACAfterSignalID,GetAcStatusNow(tempACAfterSignalID));*/

                                if (DEFAULT_ZERO != tempACAfterSignalID)
                                {
                                    if (AC_OCC_STATUS == GetAcStatusNow(tempACAfterSignalID))
                                    {
                                        /*˵�����źŻ����ڿ�ѹ״̬*/
                                        returnValue = RETURN_SUCCESS;
                                        break;
                                    }
                                    else
                                    {
                                        /*δ��ѹ����������������*/
                                        returnValue = RETURN_ERROR;
                                    }
                                }
                                else
                                {
                                    /*δ��ѹ����������������*/
                                    returnValue = RETURN_ERROR;
                                }
                            }
                            else
                            {
                                /* ��ѯ�źŻ��ڷ���1��������ʧ�� */
                            }

                        }
                        else
                        {
                            /*δ��ѹ����������������*/
                            returnValue = RETURN_ERROR;
                        }
                    }                
                }
                else
                {
                    /*˵�����г�����CBTC������г��������жϿ�ѹ�źŻ�*/
                    returnValue = RETURN_ERROR;
                }
            } 
            else
            {
                /*˵�����г�����CBTC������г��������жϿ�ѹ�źŻ�*/
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
* ���������� �ж��г�λ���Ƿ�������źŻ��Ĵ��п�ѹ
* ����˵���� UINT16 signalId,�źŻ�Id
*            const UINT8_S trainId,�г�Id
* ����ֵ  �� 0: ����ʧ��
*			 1: ����ɹ�      
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

	/*��ʼ��*/
	MemorySet(linkIdList,((UINT32_S)(sizeof(UINT16_S)*5U)),DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*5U)));

	/*��ѯ����źŻ���λ��*/
    if (1U == CheckSignalPostion(signalId,&tempObsLink,&tempObsOffset))
    {
        /*�����ѹ�жϻ�׼�����ڵ�link��offset*/
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
                /*��ǰ�����ѯ2��LINK*/
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
                        /*������*/
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
        /* ��ѯ�źŻ�λ��ʧ��,����ʧ�� */
        rtnValue = RETURN_ERROR;
    }

	return rtnValue;
}
