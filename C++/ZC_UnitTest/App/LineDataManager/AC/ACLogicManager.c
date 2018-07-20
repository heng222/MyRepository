/************************************************************************
*
* �ļ���   ��  ACLogicManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �������ε��߼�����
* ��  ע   ��  ��
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
* ���������� ����ǰ�����������ڵ��г����з����Ե�ǰ����Ϊ�ο���λ��
* ����˵���� const UINT8 dirFlag,������(0x55:ǰ������,0xaa:�󷽼���)
*            const UINT16_S acId,��ǰ��������(Ԥ��)
*            const UINT16_S otherAcId
*            const UINT8_S dir,������Ϣ
* ����ֵ  �� 1��Զ��ο�����
*            2���ӽ��ο�����
*            3���޷���
*            0������ʧ��
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

    /*��ȡ�����������г�����*/
    trainNumInAc = GetAcTrainOfAcNum(otherAcId);

    if (DEFAULT_ZERO == trainNumInAc)
    {
        /*�������������г�*/
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
                /* 2017.6.2,��ʱ����UT���г�������µļ��᷽������Ϊ0,���ų��������г���������ʱ�����  
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
        /*��ȡ�г�����*/
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
            /*ǰ������*/
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
* ���������� �����������г�����
* ����˵������    
* ����ֵ  ����
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

    /*��������м����ڵ��г�����*/
    ClearTrainOrderInAc();

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        trainId = GetTrainIdOfIndex(cycle);
        trainDir = GetTrainUnsafeDirection(trainId);

        /*if (RETURN_SUCCESS == JudgeTrainNeedCalculate(trainId))*/
        if (RETURN_SUCCESS == JudgeTrainNeedCalculate(trainId) 
            || (DEFAULT_ZERO != GetTrainStatus(trainId)))
        {
            /*��ȡ�г���λ����Ϣ*/
            if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
            {
                if (RETURN_ERROR == CheckAcOrderBetweenTwoPoints(trainSafeLocStru.TrainTailLink,
                    trainSafeLocStru.TrainHeadLink,trainDir,&trainOccAcNum,trainOccAcIdBuff))
                {
                    /*��ȡ�г��ķǰ�ȫλ��*/
                    if (RETURN_SUCCESS == GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru))
                    {
                        /*ʹ�÷ǰ�ȫλ�ò�ѯ*/
                        if (RETURN_ERROR == CheckAcOrderBetweenTwoPoints(trainUnSafeLocStru.TrainTailLink,
                            trainUnSafeLocStru.TrainHeadLink,trainDir,&trainOccAcNum,trainOccAcIdBuff))
                        {
                            /*��ѯʧ��,�г������ƶ�*/
                            SetTrainToModeToRM0(trainId);
                            LogPrintf(1u,"%d-B71\n",trainId);
                        } 
                        else
                        {
                            /*�����г�ռѹ�ļ���������Ϣ*/
                            tempFlag = FLAG_SET;
                        }
                    }                                      
                } 
                else
                {
                    /*�����г�ռѹ�ļ���������Ϣ*/
                    tempFlag = FLAG_SET;
                }
            }
            else
            {
                /* ��ȡ��ȫλ�ýṹ��ʧ��,�Ȳ�����*/
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
                        /*������*/
                    }
                }
            } 
            else
            {
                /*������*/
            }
        } 
        else
        {
            /*������*/
        }
    }
}

/*
* ���������� ���������������г�����
* ����˵����const UINT16 trainId,������г�ID
*           const UINT16_S acId,����Ӽ������� 
* ����ֵ  ����
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

        /*���ᵱǰ���г�,ֱ������г���������*/
        SetAcTrainSequenceBuff(acId,trainIdSeqBuff,trainNumInAc);
    } 
    else
    {
        /*��ȡ�г�����*/
        if (RETURN_SUCCESS == GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainIdSeqBuff))
        {
            /*�жϵ�ǰ�г�Ӧ�ò����λ��*/
            for (cycle = DEFAULT_ZERO;cycle < trainNumInAc;cycle++)
            {
                /*�жϴ�����г��ĳ�ͷ�������г���ͷ���Ⱥ��ϵ*/
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
                        /*���뵽ǰ��*/
                        insertIndex = cycle;
                        breakFlag = FLAG_SET;
                        break;
                    case 0x02U:
                        /*�����*/
                        insertIndex = cycle+1U;
                        break;
                    default:
                        /*�����ƶ�,Ϊ�г���Ӻ�ˣ�������������������������*/
                        SetTrainToModeToRM0(trainId);
						LogPrintf(1u,"%d-B3\n",trainId);
                        break;
                    }
                }
                else
                {
                    /*�����ƶ�,Ϊ�г���Ӻ�ˣ�������������������������*/
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

            /*���ݲ���λ�ò���*/
            if (DEFAULT_0XFF != insertIndex)
            {
                JudgeInsertTrainOrderInAc(trainId,acId,insertIndex);
            } 
            else
            {
                /*������*/
            }		
        } 
        else
        {
            /*�����ƶ�,Ϊ�г���Ӻ�ˣ�������������������������*/
            SetTrainToModeToRM0(trainId);
			LogPrintf(1u,"%d-B5\n",trainId);
        }
    }
}

/*
* ���������� ��������г���������
* ����˵����const UINT16 trainId,������г�ID
*           const UINT16_S acId,����Ӽ�������   
*           const UINT8_S insertIndex,�����λ��
* ����ֵ  ����
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
    /*��ȡ�г�����*/
    if ((RETURN_SUCCESS == getFlag)
        && (trainNumInAc < SIZE_MAX_TRAINOFAC))
    {
        for (cycle = DEFAULT_ZERO;cycle < insertIndex;cycle++)
        {
            insertTrainIdSeqBuff[cycle] = trainIdSeqBuff[cycle];
        }

        /*�����г�*/
        insertTrainIdSeqBuff[insertIndex] = trainId;

        /*������г�*/
        for (cycle = insertIndex;cycle < trainNumInAc;cycle++)
        {
            insertTrainIdSeqBuff[cycle+1U] = trainIdSeqBuff[cycle];
        }

        /*д���µ��г�����*/
        SetAcTrainSequenceBuff(acId,insertTrainIdSeqBuff,(trainNumInAc+1U));
    }
    else
    {
        /*������*/
    }
}

/*
* ���������� �������һ�н���������ε��г���Ϣ
* ����˵������    
* ����ֵ  ����
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
            /*��ȡ�����������г�������Ϣ*/
            lastTrainNumInAc = GetLastTrainOfAcNum(acId);
            GetLastTrainSequenceBuf(acId,SIZE_MAX_TRAINOFAC,lastTrainOrderBuff);

            /*��ȡ���᱾�����г�������Ϣ*/
            nowTrainNumInAc = GetAcTrainOfAcNum(acId);
            GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,nowTrainOrderBuff);

            if ((DEFAULT_ZERO == lastTrainNumInAc)
                && (DEFAULT_ZERO == nowTrainNumInAc))
            {
                /*����Ϊ��*/
                SetAcLastTrain(acId,DEFAULT_ZERO);
            } 
            else
            {
                if (DEFAULT_ZERO == nowTrainNumInAc)
                {
                    /*ά�������ڵ�״̬*/
                } 
                else
                {
                    /*���ñ����ڵ����һ�г�Ϊ������ü�����г�*/
                    SetAcLastTrain(acId,nowTrainOrderBuff[nowTrainNumInAc - 1U]);
                }
            }

            /*�����������г�״̬Ϊ�����ڵ�״̬*/
            SetLastTrainOfAcNum(acId,nowTrainNumInAc);
            SetLastTrainSequenceBuf(acId,nowTrainOrderBuff,nowTrainNumInAc);
        }
        else
        {
            /*������*/
        }
    }
}

/*
* ���������� �жϼ��������Ƿ����㴿��ͨ���г�ռ��״̬
* ����˵������    
* ����ֵ  ����
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
            /*��ȡ���᱾�����г�������Ϣ*/
            nowTrainNumInAc = GetAcTrainOfAcNum(acId);
            GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,nowTrainOrderBuff);

            if (DEFAULT_ZERO == nowTrainNumInAc)
            {
                switch (GetAcStatusNow(acId))
                {
                case AC_FREE_STATUS:
                    /*��ǰ�������޳�,����������η�ͨ���г�ռ��״̬*/
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
                                /*�������,����Ϊ��ͨ���г�ռ��*/
                                SetAcUtFlag(acId,AC_UT_OCC_STATUS);
                                SetAcUtRedundance(acId,DEFAULT_ZERO);
                            }
                        } 
                        else
                        {
                            /*���ݵ�ǰ��������ǰ�󷽼����жϸü������ε�ռ��״̬*/
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
                                            /*����ΪUT����״̬*/
                                            SetAcUtFlag(acId,AC_UT_FREE_STATUS);
                                            SetAcUtRedundance(acId,1U);
                                        }
                                    } 
                                    else
                                    {
                                        /*����ΪUT����״̬*/
                                        SetAcUtFlag(acId,AC_UT_FREE_STATUS);
                                        SetAcUtRedundance(acId,1U);
                                    }
                                }
                            } 
                            else
                            {
                                /*����ΪUT����״̬*/
                                SetAcUtFlag(acId,AC_UT_FREE_STATUS);
                                SetAcUtRedundance(acId,1U);
                            }
                        }
                    } 
                    else
                    {
                        /*������UTռ��,������*/
                    }
                    break;
                default:
                    break;
                }
            } 
            else
            {
                /*�Ѿ����г�����,�������λ*/
                SetAcUtRedundance(acId,DEFAULT_ZERO);
            }
        } 
        else
        {
            /*������*/
        }
    }
}

/*
* ���������� ����ǰ������������Ϣ���㵱ǰ��������
*			 �Ƿ����㴿��ͨ���г�ռ��״̬
* ����˵����const UINT8 dirFlag,������(0x55:ǰ������,0xaa:�󷽼���)
*           const UINT16_S acId,��������ID   
*           const UINT16_S otherAcId,������������ID��ǰ��/�󷽼��ᣩ
*           const UINT8_S dir,������Ϣ
* ����ֵ  ��1:���������÷�ͨ���г�ռ��״̬
*           0:���������÷�ͨ���г�ռ��״̬
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
        /*�������ο���/����UT����/arb/arb����,���������÷�ͨ���г�ռ��״̬*/
        rtnValue = RETURN_ERROR;
    } 
    else
    {
        /*��ȡ����״̬*/
        if (AC_UT_OCC_STATUS == GetAcUtFlag(otherAcId))
        {
            /*ǰ����ͨ���г�ռ��,�������÷�ͨ���г�ռ��״̬*/
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*��ȡ���������г����з���*/
            acDir = CalculateTrainDirInOtherAc(dirFlag,acId,otherAcId,dir);

            /*��ȡ���������г�������Ϣ*/
            trainNumInAc = GetAcTrainOfAcNum(otherAcId);
            GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainOrderBuff);

            if (DEFAULT_ZERO != trainNumInAc)
            {
                switch (acDir)
                {
                case AC_DIR_FARAWAY:
                    if (FLAG_SET == GetTrainSuspectTail(trainOrderBuff[trainNumInAc - 1U]))
                    {
                        /*ǰ�����һ�г���˺���Σ������,�������÷�ͨ���г�ռ��״̬*/
                        rtnValue = RETURN_SUCCESS;
                    } 
                    else
                    {
                        /*���������÷�ͨ���г�ռ��״̬*/
                        rtnValue = RETURN_ERROR;
                    }
                    break;
                case AC_DIR_CLOSED:
                    if (FLAG_SET == GetTrainSuspectHead(trainOrderBuff[DEFAULT_ZERO]))
                    {
                        /*ǰ����һ�г�ǰ�˺���Σ������,�������÷�ͨ���г�ռ��״̬*/
                        rtnValue = RETURN_SUCCESS;
                    } 
                    else
                    {
                        /*���������÷�ͨ���г�ռ��״̬*/
                        rtnValue = RETURN_ERROR;
                    }
                    break;
                default:
                    /*����ȫ��,���÷�ͨ���г�ռ��״̬*/
                    rtnValue = RETURN_SUCCESS;
                    break;
                }
            } 
            else
            {
                /*����ȫ��,���÷�ͨ���г�ռ��״̬*/
                rtnValue = RETURN_SUCCESS;
            }
        }
    }

    return rtnValue;
}

/*
* ���������� �������������ι�����Ϣ
* ����˵���� const UINT16 acId  
* ����ֵ  �� void  
*/
void InitFailureSingleAc(const UINT16_S acId)
{
    UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};

    MemorySet(trainSequenceBuff,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC)),
                DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC)));

    /*���ù��ϵ���ȫ״̬*/
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
* ���������� ����ͨ�Ź���Ci��Ӧ�ļ���������Ϣ
* ����˵���� const UINT16 ciId��ͨ��CiId    
* ����ֵ  �� void  
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
            /*����״̬Ϊ��ȫ̬*/
            InitFailureSingleAc(acId);
        } 
        else
        {
            /*������*/
        }
    }
}

/*
* ���������� ����ͨ�Ź���NZc��Ӧ�ļ���������Ϣ
* ����˵���� const UINT16 nZcId,ͨ��ZcId    
* ����ֵ  �� void  
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
            /*����״̬Ϊ��ȫ̬*/
            InitFailureSingleAc(acId);
        } 
        else
        {
            /*������*/
        }
    }
}

/*
* ���������� �жϼ��������Ƿ����г�ͣ��
* ����˵���� const UINT16 acId,��������ID    
* ����ֵ  �� 0:û���г�ͣ��
*            1:���г�ͣ��
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

    /*��ȡ�������г�����*/
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
			
			/*11.30,dnw,����Ϊ���м�����Ҫ���г��ǰ�ȫ��ͷռѹ�ļ�������*/
            if ((acId == unsafeTrainHeadAC)
                && (FLAG_SET == trainStopArea)
                && ((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType)))
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
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� ��ռ������ΰ������г�������Ϣ
* ����˵���� ��   
* ����ֵ  �� ��
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
            /*��ռ������г�����*/
            SetAcTrainOfAcNum(acId,DEFAULT_ZERO);
            SetAcTrainSequenceBuff(acId,trainSequenceBuff,DEFAULT_ZERO);
        } 
        else
        {
            /*������*/
        }
    }
}

/*
* ���������� �жϼ��������ڵĵ����Ƿ��������պ�λ��״̬
* ����˵���� const UINT16 acId,��������ID
* ����ֵ  �� 0:������
*            1:����
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

    /*��ȡ�������εĵ�����Ϣ*/
    switchNumInAc = GetAcSwitchNum(acId);

    if (RETURN_SUCCESS == GetAcSwitchInfo(acId,AC_SWITCH_SUM_MAX,switchInAcStruBuff))
    {
        for (cycle = DEFAULT_ZERO;cycle < switchNumInAc;cycle++)
        {
            /*��ȡ�����λ��״̬�ͼ�����Ҫ��״̬�Ƿ�һ��*/
            if (switchInAcStruBuff[cycle].SwitchPostion == GetSwitchPosStatus(switchInAcStruBuff[cycle].SwitchId))
            {
                /*������*/
            } 
            else
            {
                breakFlag = FLAG_SET;
                break;
            }

            /*��ȡ���������״̬�Ƿ�Ϊ����*/			
            if (SWITCH_STATE_LOCK == GetSwitchLock(switchInAcStruBuff[cycle].SwitchId))
            {
                /*������*/
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
* ���������� �жϼ��������ڵĵ����Ƿ�����λ��״̬
* ����˵���� const UINT16 acId,��������ID
*            UINT16_S outErrorSwitchId[AC_SWITCH_SUM_MAX],�����������ĵ�������
*            ,UINT8_S *outErrorSwitchNum�������������ĵ�������
* ����ֵ  �� 0:�����㣨����ԭ��
*            1:�����㣨����ԭ��
*            2:����
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

	/*��ȡ�������εĵ�����Ϣ*/
	(*outErrorSwitchNum) = DEFAULT_ZERO;
	switchNumInAc = GetAcSwitchNum(acId);

	if (RETURN_SUCCESS == GetAcSwitchInfo(acId,AC_SWITCH_SUM_MAX,switchInAcStruBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < switchNumInAc;cycle++)
		{
			/*��ȡ�����λ��״̬�ͼ�����Ҫ��״̬�Ƿ�һ��*/
			if (switchInAcStruBuff[cycle].SwitchPostion == GetSwitchPosStatus(switchInAcStruBuff[cycle].SwitchId))
			{
				/*������*/
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
* ���������� �����м����Ѿ��ж�ΪUT�����г��Ѿ���ɨ�ü���󣬽���ת��ΪARB
* ����˵���� ��
* ����ֵ  �� ��
*/
void ConvertAxleUtToArb(void)
{
    UINT16_S acCycle = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT8_S acUtFlag = DEFAULT_ZERO;
    UINT8_S acCleanFlag = DEFAULT_ZERO;
    UINT8_S acAttribute = DEFAULT_ZERO;
    UINT8_S adjacentArbCondition = DEFAULT_ZERO;

    /*������ZC����*/
    for (acCycle = DEFAULT_ZERO;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        /*��ȡAC��UT��־*/
        acUtFlag = GetAcUtFlag(acId);

        /*�жϼ����Ƿ����ڱ�ZC*/
        acAttribute = CheckAcAttribute(acId);

        if ((FLAG_SET == acAttribute) 
            && (FLAG_SET == acUtFlag))
        {
            /*��ȡ�г�����ɨ��־*/
            acCleanFlag = GetAcTrainCleanFlag(acId);

            /*�жϴ��м������ڼ������*/
            adjacentArbCondition = CheckAdjacentAxleArbCondition(acId);

            if ((CLEAN_STATUS_ALL_OUT == acCleanFlag) 
                && (RETURN_SUCCESS == adjacentArbCondition))
            {
                /*�������������������ж�ΪARB*/
                SetAcArbFlag(acId,FLAG_SET);
                SetAcUtFlag(acId,FLAG_UNSET);
                SetAcUtRedundance(acId,DEFAULT_ZERO);
            }
            else
            {
                /*����ά��ԭ״*/
            }
        } 
        else
        {
            /*������*/
        }
    }
}

/*
* ���������� �����м����Ѿ��ж�ΪARB��������ռ��״̬��Ϊ���к������ARB��־
* ����˵���� ��
* ����ֵ  �� ��
*/
void ConvertAxleArbToFree(void)
{
    UINT16_S acCycle = DEFAULT_ZERO;
    UINT8_S acArbFlag = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT8_S acStatus = DEFAULT_ZERO;
    UINT8_S acAttribute = DEFAULT_ZERO;

    /*������ZC����*/
    for (acCycle=DEFAULT_ZERO;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        /*��ȡAC ARB��־*/
        acArbFlag = GetAcArbFlag(acId);

        /*��ȡ����ռ��״̬*/
        acStatus = GetAcStatusNow(acId);

        /*�жϼ����Ƿ����ڱ�ZC*/
        acAttribute = CheckAcAttribute(acId);

        if ((FLAG_SET == acAttribute) && (AC_ARB_OCC_STATUS == acArbFlag) && (AC_FREE_STATUS == acStatus))
        {
            /*˵��ARB�����Ѿ����У����ARB��־*/
            SetAcArbFlag(acId,FLAG_UNSET);
        }
        else
        {
            /*��������*/
        }
    }
}

/*
* ���������� �жϼ����Ƿ����ڱ�ZC
* ����˵���� const UINT16 acId
* ����ֵ  �� RETURN_ERROR��ʧ��
*			 FLAG_SET�����ڱ�ZC
*			 FLAG_UNSET:�����ڱ�ZC
*/
UINT8_S CheckAcAttribute(const UINT16_S acId)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S zcId = DEFAULT_ZERO;
    UINT16_S selfZcId = DEFAULT_ZERO;

    /*��ȡ��������ZC*/
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
* ���������� �жϴ��м����������ڼ����Ƿ������ARB�ж�����
* ����˵���� const UINT16 checkedAcId
* ����ֵ  �� 1������ARB����
*			 0��������ARB����			 
*/
UINT8_S CheckAdjacentAxleArbCondition(const UINT16_S checkedAcId)
{
    UINT8_S FrontArbConditon = DEFAULT_ZERO;
    UINT8_S RearArbConditon = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*���������жϽ��*/
    FrontArbConditon = CheckOneSideAxleArbCondition(checkedAcId,FORWORD_DIRCTION);

    /*�ط������жϽ��*/
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
* ���������� ���м������ڼ����Ƿ�����ARB����
* ����˵���� const UINT16  checkedAcId, ���м���ID
*			 const UINT8_S direction����ѯ����
* ����ֵ  �� 0: ������ARB����
*			 1������ARB����
*/
UINT8_S CheckOneSideAxleArbCondition(const UINT16_S checkedAcId,const UINT8_S direction)
{
    UINT16_S  sideDsuCheck = DEFAULT_ZERO;               /*��ѯ�󷽼��᷵��ֵ*/
    UINT16_S  sideAcIdBuff[MAX_ADJACENT_LOSE_AC]={DEFAULT_ZERO};                   
    UINT8_S  sideAcNum = DEFAULT_ZERO; 
    UINT8_S rtnValue = DEFAULT_ZERO;

    MemorySet(sideAcIdBuff,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)),
                DEFAULT_ZERO,((UINT32_S)(MAX_ADJACENT_LOSE_AC*SIZE_UINT16)));

    sideDsuCheck = CheckFrontACCanStatus(checkedAcId,direction,&sideAcNum,sideAcIdBuff);

    switch (sideDsuCheck)
    {
    case 1U:
        /*�ɹ�*/
        rtnValue = CheckOneSideNormalAxleArbCondition(checkedAcId,sideAcIdBuff[0],direction);
        break;
    case 3U:
        /*���ڵ���ԭ���ѯʧ��*/
        rtnValue = CheckOneSideLoseAxleArbCondition(sideAcIdBuff,sideAcNum);
        break;
    case 2U:
        /*���ھ�ͷ��ԭ��ʧ�ܣ���Ϊ�޷��ж�ARB*/
        rtnValue = RETURN_ERROR;
        break;
    case 0U:
        /*��������ԭ��ʧ�ܣ���Ϊ�޷��ж�ARB*/
        rtnValue = RETURN_ERROR;
        break;
    default:
        rtnValue = RETURN_ERROR;
        break;
    }

    return rtnValue;
}

/*
* ���������� ���м����������������Ƿ�����ARB����
* ����˵���� const UINT16  checkedAcId, ���м���ID
*			 const UINT16_S  adjacentAcId�����ڼ���ID
*			 const UINT8_S dir, ����
* ����ֵ  �� 0: ������ARB����
*			 1������ARB����
*/
UINT8_S CheckOneSideNormalAxleArbCondition(const UINT16_S checkedAcId,const UINT16_S adjacentAcId,const UINT8_S dir)
{
    UINT8_S dirTrainInAc = DEFAULT_ZERO;       /*Ĭ�Ϸ������޷���*/ 
    UINT8_S judgeARBFlag = DEFAULT_ZERO;       /*ARB�жϱ�־λ*/
    UINT8_S adjacentAcStatus = DEFAULT_ZERO;   /*���ڼ���״̬*/
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
        /*ǰ���������,���ؿ��ж�ARB*/
        judgeARBFlag = 1U;
        break;
    case AC_OCC_STATUS:
        /*��ȡ�г�����*/
        trainNum = GetAcTrainOfAcNum(adjacentAcId);

        if ((0U < trainNum) && (RETURN_UINT8_MAX_VALUE != trainNum))
        {
            /*�г���������0*/
            /*�жϱ������������г������з���*/
            dirTrainInAc = CalculateTrainDirInOtherAc(FLAG_SET,checkedAcId,adjacentAcId,dir);

            /*��ȡǰ�����ߺ󷽼�����г�����*/           
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
                            /*Ϊͨ�ų����޺�˿���*/
                            judgeARBFlag = 1U;
                        }
                        else
                        {
                            judgeARBFlag = 0U;
                        }
                    }
                    else
                    {
                        /*崻�*/
                    }

                    break;
                case AC_DIR_CLOSED:
                    trainId = GetFirstIdInTrainSequence(adjacentAcId);

                    if (RETURN_UINT16_MAX_VALUE != trainId)
                    {
                        suspectedFlag = GetTrainSuspectHead(trainId);

                        if (FLAG_UNSET == suspectedFlag)
                        {
                            /*Ϊͨ�ų�����ǰ�˿���*/
                            judgeARBFlag = 1U;
                        }
                        else
                        {
                            judgeARBFlag = 0U;
                        }
                    }
                    else
                    {
                        /*崻�*/
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
                    /*����ֱ���ж�ARB*/
                    judgeARBFlag = 1U;
                }
                else if(FLAG_SET == utFlag)
                {
                    /*�����ж�ARB*/
                    judgeARBFlag = 0U;
                }
                else if(0U < utRedundancy)
                {
                    /*���ж�ARB*/
                    /*zcy:ע��˴���Ҫ�����������*/
                    judgeARBFlag = 1U;
                }
                else
                {
                    /*�÷�֧�����ܴ���*/
                    /*�����ж�ARB*/
                    judgeARBFlag = 0U;
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
        break;
    default:
        /*�����ж�ARB*/
        judgeARBFlag = 0U;
        break;
    }

    return judgeARBFlag;
}

/*
* ���������� ���м��������Ŀ������Ƿ�����ARB����
* ����˵���� const UINT16  adjacentAcId[]�����ڼ���ID
*            const UINT8_S adjacentAcNum,���ڼ�������
* ����ֵ  �� 0: ������ARB����
*			 1������ARB����
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
        /*��ȡ����ռ��״̬*/
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
            /*��������*/
        }
    }

    if ((freeAcNum == adjacentAcNum) || (arbAcNum == adjacentAcNum))
    {
        /*����ARB�ж�����*/
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }	

    return rtnValue;
}

/*
* ���������� ������RM�г���ɨ״̬ת��
* ����˵���� ��
* ����ֵ  �� ��
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
            /*��ZC��Ͻ��Χ�ڼ�������,����*/
            /*��ȡAC UT��־*/
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
                /*���������ɨ�ж�*/ 
                SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                SetAcCleanTrainId(acId,DEFAULT_ZERO);
            }
        } 
        else
        {
            /*������*/
        }
    }
}

/*
* ���������� ������ɨĬ��״̬����
* ����˵���� const UINT16 acId
*		     const UINT16_S trainId
* ����ֵ  �� ��
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
            /*��ѯ���м����һ����*/
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
                    /*�г�����ΪRM����ͷλ�ڴ���ɨ���ᣬ��β���߳���λ��ǰһ����*/
                    SetAcTrainCleanFlag(acId,CLEAN_STATUS_HEAD_ENTRY);
                    SetAcCleanTrainId(acId,trainId);
                    break;
                }
                else
                {
                    /*��������*/
                    SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                    SetAcCleanTrainId(acId,0U);
                }
            }
            else
            {
                /*�������ж�����*/

            }
        }
        else
        {
            /*������*/
        }
    }
}

/*
* ���������� ������ɨ��ͷ�ѽ���״̬����
* ����˵���� const UINT16 acId
*		     const UINT16_S trainId
* ����ֵ  �� ��
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
            /*˵���г�����ȫ������м���*/
            SetAcTrainCleanFlag(acId,CLEAN_STATUS_ALL_ENTRY);
            SetAcCleanTrainId(acId,trainId);
        }
        else 
        {
            /*��ѯ���м���ǰһ����*/
            sideDsuCheck = CheckRearACCanStatus(acId,trainDirection,&frontAcNum,frontAcId);

            if (RETURN_SUCCESS == sideDsuCheck)
            {
                if	((TRAIN_MODE_RM == trainType) && (acId == trainHeadAc) && (frontAcId[0] == trainTailAc))
                {
                    /*�г�����ΪRM����ͷλ�ڴ���ɨ���ᣬ��βλ��ǰһ����,����*/
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
* ���������� ������ɨ��ͷ��β������״̬����
* ����˵���� const UINT16 acId
*		     const UINT16 trainId
* ����ֵ  �� ��
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
        /*��ѯ���м����һ����*/
        sideDsuCheck1 = CheckRearACCanStatus(acId,trainDirection,&rearAcNum,rearAcId);
#ifdef SYS_TYPE_WINDOWS
        /*LogPrintf(1U,"300.1 sideDsuCheck=%d,acId=%d,rearAcNum=%d,rearAcId[0]=%d,rearAcId[1]=%d\n",sideDsuCheck1,acId,rearAcNum,rearAcId[0],rearAcId[1]);*/
#endif

        /*��ѯ���м���ǰһ����*/
        sideDsuCheck2 = CheckFrontACCanStatus(acId,trainDirection,&frontAcNum,frontAcId);

#ifdef SYS_TYPE_WINDOWS
        /*LogPrintf(1U,"300.2 sideDsuCheck=%d,acId=%d,frontAcNum=%d,frontAcId[0]=%d,frontAcId[1]=%d\n",sideDsuCheck2,acId,frontAcNum,frontAcId[0],frontAcId[1]);*/
#endif
        if (((TRAIN_MODE_RM == trainType)  || (TRAIN_MODE_RM0 == trainType) || (TRAIN_MODE_CBTC == trainType)) && (FLAG_UNSET == tailSuspect))
        {
            /*�г�������ȷ���Ҳ�����˿��ɱ�־*/
            if ((acId == trainHeadAc) && (acId == trainTailAc))
            {
                /*��ͷ��β���ѽ�����м��ᣬ����״̬*/
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
                        /*�г�����ΪRM���޺�˿��ɱ�־����ͷλ�ڴ���ɨ������һ���ᣬ��β���߳���λ�ڴ��м���*/
                        SetAcTrainCleanFlag(acId,CLEAN_STATUS_HEAD_OUT);
                        SetAcCleanTrainId(acId,trainId);
                    }
                    else if ((acId == trainHeadAc) && ((rearAcId[0] == trainTailAc) || (1U == trainBodyInBefAc)))
                    {
                        /*�г�����ΪRM����ͷλ�ڴ���ɨ���ᣬ��β���߳���λ��ǰһ����,����*/
                        SetAcTrainCleanFlag(acId,CLEAN_STATUS_HEAD_ENTRY);
                        SetAcCleanTrainId(acId,trainId);
                    }
                    else
                    {
                        /*�������ΪĬ��״̬*/
                        SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                        SetAcCleanTrainId(acId,0U);
                    }
                }
                else
                {
                    /*���ΪĬ��״̬*/
                    SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                    SetAcCleanTrainId(acId,0U);
                }

            }
        }
        else
        {
            /*���ΪĬ��״̬*/
            SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
            SetAcCleanTrainId(acId,0U);
        }		
    }
    else
    {
        /*���ΪĬ��״̬*/
        SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
        SetAcCleanTrainId(acId,0U);
    }
}

/*
* ���������� ������ɨ��ͷ����״̬����
* ����˵���� const UINT16 acId
*		     const UINT16_S trainId
* ����ֵ  �� ��
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
        /*��ѯ���м���ǰһ����*/
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
                /*��βλ����һ���ᣬ��ͷ�ͳ������λ�ڴ��м��ᣬ˵���г��Ѿ�������м���*/
                /*�г�����ΪRM���޺�˿��ɱ�־����ͷ��β��λ�ڴ���ɨ������һ����*/
                SetAcTrainCleanFlag(acId,CLEAN_STATUS_ALL_OUT);
                SetAcCleanTrainId(acId,trainId);
            }
            else if (((TRAIN_MODE_RM == trainType)  || (TRAIN_MODE_RM0 == trainType) || (TRAIN_MODE_CBTC == trainType)) 
				     && (FLAG_UNSET == tailSuspect)
                     && (frontAcId[0] != trainTailAc))
                /*else if (((TRAIN_MODE_RM == trainType) || (TRAIN_MODE_CBTC == trainType)) && (FLAG_UNSET == tailSuspect)
                && (acId == trainTailAc))*/
            {
                /*zcy:������ʱ��Ϊ��β��λ����һ���ᣬ�������ȽϿ��ɣ����ܲ������ܣ�������Ҫ��������;ԭ�������г���ѹ3������ʱ��������*/
                /*��β��Ȼ���ڴ��м��ᣬ˵���г���δ������м���*/
                /*�г�����ΪRM���޺�˿��ɱ�־����ͷλ�ڴ���ɨ������һ���ᣬ��βλ�ڴ��м���*/
                SetAcTrainCleanFlag(acId,CLEAN_STATUS_HEAD_OUT);
                SetAcCleanTrainId(acId,trainId);
            }
            else
            {
                /*���ΪĬ��״̬*/
                SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
                SetAcCleanTrainId(acId,0U);
            }
        }
        else
        {
            /*���ΪĬ��״̬*/
            SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
            SetAcCleanTrainId(acId,0U);
        }
    }
    else
    {
        /*���ΪĬ��״̬*/
        SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
        SetAcCleanTrainId(acId,0U);
    }
}

/*
* ���������� ������ɨ��ͷ��β������״̬����
* ����˵���� const UINT16 acId
*		     const UINT16_S trainId
* ����ֵ  �� ��
*/
void AllOutStatusProcess(const UINT16_S acId)
{
    /*�г���ɽ�����һ���ᣬ��һ������Ч*/
    /*���ΪĬ��״̬*/
    SetAcTrainCleanFlag(acId,CLEAN_STATUS_DEFAULT);
    SetAcCleanTrainId(acId,0U);
}


/*
* ���������� ����UT�ж�������
* ����˵���� ��
* ����ֵ  �� ��
*/
void JudgeAxleUT(void)
{
    /*�����м���ת��ΪUT״̬*/
    ConvertAxleFreetoUT();

    /*��ARB����ת��ΪUT״̬*/
    ConvertAxleArbToUt();

    /*�������������UT�����ARB����״̬��һ������*/
    ConvertSwitchAxleArbToUt();

    /*���м������UT��־*/
    ConvertAxleUtToFree();
}

/*
* ���������� ����ARB�ж�������
* ����˵���� ��
* ����ֵ  �� ��
*/
void JudgeAxleARB(void)
{
    /*��UT����ת��ΪARB״̬*/
    ConvertAxleUtToArb();

    /*���м������ARB��־*/
    ConvertAxleArbToFree();
}

/*
* ���������� �����м����п��б�Ϊռ�ã������г�ͨ����ά��ռ�ã���������Ϊ����UT
* ����˵���� ��
* ����ֵ  �� ��
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

    /*������ZC����*/
    for (acCycle = 0U;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        /*��ȡAC UT�����ʱλ*/
        acUtRedunce = GetAcUtRedundance(acId);

        /*��ȡ�����г�����״̬*/
        trainNum = GetAcTrainOfAcNum(acId);

        /*�жϼ����Ƿ����ڱ�ZC*/
        acAttribute = CheckAcAttribute(acId);

        /*���Ѿ�����UT����״̬�ļ�����д���*/
        if (FLAG_SET == acAttribute)
        {
            if (0U != acUtRedunce)
            {
                if (0U != trainNum)
                {
                    /*˵���г��Ѿ�������ᣬ��������*/
                    SetAcUtRedundance(acId,0U);
                }
                else
                {
                    /*ռ���޳�ʱ������������Ϊ����UT*/
                    SetAcUtRedundance(acId,acUtRedunce + 1U);
                }

                /*˵�����ᴦ������UT������*/
                if (GetSectionRedundantCycle() <= acUtRedunce)
                {
                    /*����ʱ�䵽���������������ΪUT*/
                    SetAcUtFlag(acId,AC_UT_OCC_STATUS);
                    SetAcUtRedundance(acId,0U);
                }
            }
            else
            {
                /*δ����UT״̬*/
            }
        }
        else
        {
            /*��������*/
        }
    }

    /*������ZC����*/
    for (acCycle = 0U;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        /*��ȡAC ARB��־*/
        acArbFlag = GetAcArbFlag(acId);

        /*��ȡAC UT��־*/
        acUtFlag = GetAcUtFlag(acId);

        /*��ȡAC UT�����ʱλ*/
        acUtRedunce = GetAcUtRedundance(acId);

        /*��ȡ����ռ��״̬*/
        acStatus = GetAcStatusNow(acId);

        /*��ȡ�����г�����״̬*/
        trainNum = GetAcTrainOfAcNum(acId);

        /*�жϼ����Ƿ����ڱ�ZC*/
        acAttribute = CheckAcAttribute(acId);

        if ((FLAG_SET == acAttribute) 
            && (AC_ARB_OCC_STATUS != acArbFlag)
            && (AC_UT_OCC_STATUS != acUtFlag) 
            && (0U == acUtRedunce) 
            && (AC_OCC_STATUS == acStatus) 
            && (0U == trainNum))
        {
            /*ռ���޳�ʱ������������Ϊ����UT*/
            SetAcUtRedundance(acId,1U);
        }
        else
        {
            /*��������*/
        }
    }
}

/*
* ���������� �����м����Ѿ��ж�ΪARB������ͨ���г��ӽ�����ռ�øü���󣬽���ת��ΪUT
* ����˵���� ��
* ����ֵ  �� ��
*/
void ConvertAxleArbToUt(void)
{
    UINT16_S acCycle = 0U;
    UINT16_S acId = 0U;
    UINT8_S acArbFlag = 0U;
    UINT8_S acAttribute = 0U;
    UINT8_S adjacentUtCondition = 0U;

    /*������ZC����*/
    for (acCycle = 0U;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        if (RETURN_ERROR != acId)
        {
            /*��ȡAC UT��־*/
            acArbFlag = GetAcArbFlag(acId);

            /*�жϼ����Ƿ����ڱ�ZC*/
            acAttribute = CheckAcAttribute(acId);

            /*�жϴ��м������ڼ������*/
            adjacentUtCondition = CheckAdjacentAxleUtCondition(acId);

            if ((FLAG_SET == acAttribute) && (FLAG_SET == acArbFlag)
                && (RETURN_SUCCESS == adjacentUtCondition))
            {
                /*��������������������ARB״̬ת��ΪUT*/
                SetAcArbFlag(acId,FLAG_UNSET);
                SetAcUtFlag(acId,FLAG_SET);
                SetAcUtRedundance(acId,0U);
            }
            else
            {
                /*����ά��ԭ״*/
            }
        }
        else
        {
            /*崻�*/
        }
    }
}

/*
* ���������� �����м����Ѿ��ж�ΪUT��������ռ��״̬��Ϊ���к������UT��־
* ����˵���� ��
* ����ֵ  �� ��
*/
void ConvertAxleUtToFree(void)
{
    UINT16_S acCycle = 0U;
    UINT8_S acUtFlag = 0U;
    UINT16_S acId = 0U;
    UINT8_S acStatus = 0U;
    UINT8_S acAttribute = 0U;

    /*������ZC����*/
    for (acCycle = 0U;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        /*��ȡAC ARB��־*/
        acUtFlag = GetAcUtFlag(acId);

        /*��ȡ����ռ��״̬*/
        acStatus = GetAcStatusNow(acId);

        /*�жϼ����Ƿ����ڱ�ZC*/
        acAttribute = CheckAcAttribute(acId);

        if ((FLAG_SET == acAttribute) 
            && (AC_UT_OCC_STATUS == acUtFlag) 
            && (AC_FREE_STATUS == acStatus))
        {
            /*˵��UT�����Ѿ����У����UT��־*/
            SetAcUtFlag(acId,FLAG_UNSET);
            SetAcUtRedundance(acId,0U);
        }
        else
        {
            /*��������*/
        }
    }
}

/*
* ���������� �жϴ��м����������ڼ����Ƿ������UT�ж�����
* ����˵���� const UINT16 checkedAcId
* ����ֵ  �� 1������UT����
*			 0��������UT����			 
*/
UINT8_S CheckAdjacentAxleUtCondition(const UINT16_S checkedAcId)
{
    UINT8_S FrontArbConditon = 0U;
    UINT8_S RearArbConditon = 0U;
    UINT8_S rtnValue = 0U;

    /*���������жϽ��*/
    FrontArbConditon = CheckOneSideAxleArbCondition(checkedAcId,FORWORD_DIRCTION);

    /*�ط������жϽ��*/
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
* ���������� �жϵ������������Ƿ�λ�ڼ���������
* ����˵���� const UINT16 acId, �������
*            const UINT8_S acOrderNum, ������������
*            const UINT16_S acOrderBuff[], ��������
* ����ֵ  �� 1��λ��
*			 0����λ��			 
*/
UINT8_S JudgeSingleAcInAcOrder(const UINT16_S acId,const UINT8_S acOrderNum,const UINT16_S acOrderBuff[])
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (NULL != acOrderBuff)
    {
        /*������Ϣ*/
        for (cycle = DEFAULT_ZERO;cycle < acOrderNum;cycle++)
        {
            if (acId == acOrderBuff[cycle])
            {
                rtnValue = 1U;
                break;
            } 
            else
            {
                /*������*/
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
* ���������� ��������ļ����Ƿ��������״̬�����պ�λ�ã�
* ����˵���� const UINT16 acId����������ID   
* ����ֵ  �� 0:����������
*            1:��������
*/
UINT8_S CalulateSwtichStateOfAcIsNeed(const UINT16_S acId)
{
    UINT8_S  acSwitchNum = DEFAULT_ZERO;                                   /*�������ΰ����ĵ�������*/
    SwitchInAcStruct acSwitchInAcStruBuff[AC_SWITCH_SUM_MAX]; /*�������ΰ����ĵ�����Ϣ*/
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S switchInfoRtn = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S switchLock = DEFAULT_ZERO;
	UINT8_S switchPosStatus = DEFAULT_ZERO;
	
    MemorySet(&acSwitchInAcStruBuff[0],((UINT32_S)(sizeof(SwitchInAcStruct)*AC_SWITCH_SUM_MAX)),
        0U,((UINT32_S)(sizeof(SwitchInAcStruct)*AC_SWITCH_SUM_MAX)));

    /*��ȡ�������ε�����Ϣ*/
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
* ���������� ������ZC���еļ������Σ��������������ĳһ������ΪUT�����������ARB��������ΪUT
* ����˵���� ��   
* ����ֵ  �� ��
*/
void ConvertSwitchAxleArbToUt(void)
{
    UINT16_S acCycle = 0U;
    UINT16_S acId = 0U;

    /*������ZC����*/
    for (acCycle = 0U;acCycle < GetAcCurSum();acCycle++)
    {
        acId = GetAcId(acCycle);

        if (RETURN_ERROR == ConvertSingleSwitchAxleArbToUt(acId))
        {
            /*崻�*/
        }
    }
}

/*
* ���������� ��������������Σ������������ĳһ������ΪUT�����������ARB��������ΪUT
* ����˵���� const UINT16 acId����������ID   
* ����ֵ  �� 0:ʧ��
*            1:�ɹ�
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
        /*����������ΪUT����ѯ���������������*/
        ret = CheckRelatedAcOfInputAc(acId,&checkAcNum,checkAcBuff);

        if (RETURN_SUCCESS == ret)
        {
            for (i=0U;i<checkAcNum;i++)
            {
                arbFlag = GetAcArbFlag(checkAcBuff[i]);

                if ((checkAcBuff[i] != acId) && (AC_ARB_OCC_STATUS == arbFlag))
                {
                    /*�����Ϊ������ᣬ�����ж�ΪARB������ת��ΪUT*/
                    SetAcUtFlag(checkAcBuff[i],AC_UT_OCC_STATUS);
                }
                else
                {
                    /*��������*/
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
        /*���账��*/
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*
* ���������� ��������������Σ������������ĳһ������ΪUT�����������ARB��������ΪUT
* ����˵���� const UINT16 acId����������ID  
*            UINT8_S *relatedAcNum,������������
*            UINT16_S relatedAcId[SWITCH_BELONG_AC_SUM_MAX*5],������������
* ����ֵ  �� 0:����������
*            1:��������
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

    /*��ѯ��������ĵ�����Ϣ*/
    ret1 = GetLineAcIncludeSwitchInfo(acId,&getSwitchNum,getSwitchInfoBuff);

    if ((RETURN_SUCCESS == ret1) && (NULL != relatedAcNum) && (NULL != relatedAcId))
    {
        for (cycle=0U;cycle<getSwitchNum;cycle++)
        {
            /*��ѯ��������ļ�������*/
            ret2 = CheckSwitchBelongAc(getSwitchInfoBuff[cycle],&checkAcNum,checkAcBuff);

            if (RETURN_SUCCESS == ret2)
            {
                for (cycle2=0U;cycle2<checkAcNum;cycle2++)
                {
                    /*�ռ�ָ��������������м���*/
                    relatedAcId[*relatedAcNum] = checkAcBuff[cycle2];
                    (*relatedAcNum) ++;
                }
            }
            else
            {
                /*����ʧ��*/
                *relatedAcNum = 0U;				
                rtnValue = 0U;
                break;
            }
        }
    }
    else
    {
        /*����ʧ��*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* ���������� �ж��г������ǳ�ͷ��β���Ƿ�λ��ָ��������
* ����˵���� const UINT16 trainId
const UINT16_S acId����������ID   
* ����ֵ  �� 0:�Ǳ�
*            1:λ��ָ������
*            2����λ��ָ������
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
                /*������*/
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
* ���������� �жϵ�ǰ���������Ƿ�����Ҫ��ĵ���λ��״̬
* ����˵���� const UINT16 acId ����Id
* ����ֵ  �� 0: ���������״̬
*			 1: �������״̬    
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

	/*��ȡ�����ڵ�����Ϣ*/
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
			/*��ȡ�������ID��Ӧ���е�λ����Ϣ*/
			switchId = switchInAcStruBuff[cycle].SwitchId;
			switchPosNeed = switchInAcStruBuff[cycle].SwitchPostion;

			/*��ȡ����ǰ��״̬*/
			switchPosNow = GetSwitchPosStatus(switchId);

			if (switchPosNow == switchPosNeed)
			{
				/*λ��״̬��������*/
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
* ���������� �жϵ�ǰ�������ε���λ��״̬�Ƿ�Ϊ�Ŀ�״̬
* ����˵���� const UINT16 acId ����Id
* ����ֵ  �� FLAG_UNSET: ���Ŀ�״̬
*			 FLAG_SET: �Ŀ�״̬    
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

	/*��ȡ�����ڵ�����Ϣ*/
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
			/*��ȡ�������ID��Ӧ���е�λ����Ϣ*/
			switchId = switchInAcStruBuff[cycle].SwitchId;

			/*��ȡ����ǰ��״̬*/
			switchPosNow = GetSwitchPosStatus(switchId);

			if (switchPosNow == SWITCH_STATE_LOSE)
			{
				/*λ��״̬�����Ŀ�����*/
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