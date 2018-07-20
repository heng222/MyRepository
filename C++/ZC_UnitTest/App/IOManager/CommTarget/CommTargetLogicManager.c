/************************************************************************
*
* �ļ���   ��  CommTargetLogicManager.c
* ����     ��  ZC��
* ����ʱ�� ��  2015.07.14
* �������� ��  ͨѶ�����߼����� 
* ��  ע   ��  ��  
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
* ��������:  ManagerCommTargetCommCycle
* ���������� ����ͨ�Ŷ���ͨ�����ڹ���
* ��������� void    
* ��������� ��
* ����ֵ  �� ��
*/
void ManagerCommTargetCommCycle(void)
{
    /*����ͨ��CI��ͨ��������Ϣ*/
    JudgeSingleCommTypeCommCyle(INNER_DEVTYPE_CI);

    /*����ͨ��ZC��ͨ��������Ϣ*/
    JudgeSingleCommTypeCommCyle(INNER_DEVTYPE_ZC);

    /*����ͨ��NTP��ͨ��������Ϣ*/
    JudgeSingleCommTypeCommCyle(INNER_DEVTYPE_NTP);

    /*����ͨ�ŵĳ���ATP��ͨ��������Ϣ*/
    JudgeCommTrainCommCyle();
}

/*
* �������ƣ� JudgeSingleCommTypeCommCyle
* ���������� ����ͨ�Ŷ��󣨳��г��⣩ͨ�����ڹ���
* ��������� const UINT8 commTargetType��ͨ�Ŷ�������  
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeSingleCommTypeCommCyle(const UINT8_S commTargetType)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S commTargetBufIndex = DEFAULT_ZERO;
    UINT8_S singleCommTargetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX];
    UINT16_S commCycle = DEFAULT_ZERO;
    UINT8_S rtnGet = DEFAULT_ZERO;

    /*��ʼ��*/
    MemorySet(&commTargetIdBuff[DEFAULT_ZERO],sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX,DEFAULT_ZERO,sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX);

    /*��ȡͨ�Ŷ��������*/
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
                    /*������*/
                }
            } 
            else
            {
                /*ͨ��״̬�쳣,����ۼ�λ*/
                SetCommTargetCycle(commTargetType,commTargetIdBuff[cycle],DEFAULT_ZERO);
            }
        }
    } 
    else
    {
        /*��崻�����������������������*/
    }
}

/*
* �������ƣ� JudgeCommTrainCommCyle
* ���������� ����ͨ���г�ͨ�����ڹ���
* ��������� void    
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeCommTrainCommCyle(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTargetCycle = DEFAULT_ZERO;

    for (cycle = 1U;cycle < COMM_TRAIN_ID_MAX;cycle++)
    {
        /*�г�ͨ���У��±꼴ΪId*/
        if (COMM_STATUS_NORMAL == GetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle)))
        {
            /*��ȡͨ������λ*/
            commTargetCycle = GetCommTargetCycle(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle));

            /*ͨ���ۼ�λ+1*/
            if (DEFAULT_UINT16_VALUE != commTargetCycle)
            {
                SetCommTargetCycle(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle),((UINT16_S)(commTargetCycle + 1U)));
                /* LogPrintf(1U,"17.302 train=%d,commCycle=%d\n",cycle,(UINT16_S)(commTargetCycle + 1U)); */
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
* �������ƣ� ManageCommTargetCommStatus
* ���������� ͨ�Ŷ���ͨ��״̬����
* ��������� void    
* ��������� ��
* ����ֵ  �� ��
*/
void ManageCommTargetCommStatus(void)
{
    UINT16_S maxCommFaultCycle = DEFAULT_ZERO;  /* ���õ��ж�ĳ������ͨѶ������������� */

    /*������CIͨ�Ŷ����ͨ��״̬*/
    maxCommFaultCycle = (UINT16_S)(GetCICommCycle());
    JudgeSingleCommTypeCommStatus(INNER_DEVTYPE_CI,maxCommFaultCycle);

    /*������NZCͨ�Ŷ����ͨ��״̬*/
    maxCommFaultCycle = (UINT16_S)(GetNZcCommCycle());
    JudgeSingleCommTypeCommStatus(INNER_DEVTYPE_ZC,maxCommFaultCycle);

    /*������NTPͨ�Ŷ����ͨ��״̬*/
    JudgeNtpCommStatus();

    /*������Trainͨ�Ŷ����ͨ��״̬*/
    maxCommFaultCycle = (UINT16_S)(GetTrainAtpCommCycle());
    JudgeCommTrainCommStatus(maxCommFaultCycle);
}

/*
* �������ƣ� JudgeSingleCommTypeCommStatus
* ���������� ����ͨ�Ŷ��󣨳��г��⣩ͨ��״̬����
* ��������� const UINT8 commTargetType��ͨ�Ŷ�������  
*            const UINT16_S maxCommFaultCycle����ͨ����������ͨ�Ź�������
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeSingleCommTypeCommStatus(const UINT8_S commTargetType,const UINT16_S maxCommFaultCycle)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S commTargetBufIndex = DEFAULT_ZERO;
    UINT8_S singleCommTargetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};
    UINT16_S commCycle = DEFAULT_ZERO;
    UINT8_S rtnGet = DEFAULT_ZERO;

    /*��ʼ��*/
    MemorySet(commTargetIdBuff,((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
               DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    /*��ȡͨ�Ŷ��������*/
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
                    /*������*/
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
        /*��崻�����������������������*/
    }
}

/*
* �������ƣ� JudgeNtpCommStatus
* ���������� ����NTPͨ��״̬����
* ��������� ��
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeNtpCommStatus(void)
{
    UINT8_S commTargetBufIndex = DEFAULT_ZERO;
    UINT8_S singleCommTargetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};
    UINT16_S commCycle = DEFAULT_ZERO;
    UINT8_S rtnGet = DEFAULT_ZERO;

    /*��ʼ��*/
    MemorySet(&commTargetIdBuff[DEFAULT_ZERO],((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
               DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    /*��ȡͨ�Ŷ��������*/
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
            /*����ۼ���Ϣ*/
            SetCommTargetCycle(INNER_DEVTYPE_NTP,commTargetIdBuff[DEFAULT_ZERO],DEFAULT_ZERO);
        } 
        else
        {
            /*������*/
        }
    } 
    else
    {
        /*��崻�*/
    }
}

/*
* �������ƣ� JudgeCommTrainCommStatus
* ���������� ����ͨ���г�ͨ��״̬����
* ��������� const UINT16 maxCommFaultCycle����ͨ����������ͨ�Ź�������   
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeCommTrainCommStatus(const UINT16_S maxCommFaultCycle)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTargetCycle = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnSafeLoc;

    for (cycle = 1U;cycle < COMM_TRAIN_ID_MAX;cycle++)
    {
        /*�г�ͨ���У��±꼴ΪId*/
        if (COMM_STATUS_NORMAL == GetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle)))
        {
            if (RETURN_SUCCESS == GetTrainUnSafeLoc(((UINT16_S)cycle),&trainUnSafeLoc))
            {
                /*��ȡͨ������λ*/
                commTargetCycle = GetCommTargetCycle(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle));

                /*ͨ���ۼ�λ+1*/
                if (commTargetCycle >= maxCommFaultCycle)
                {
                    SetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle),COMM_STATUS_ABNORMAL);
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
        else
        {
            /*������*/
        }
    }
}

/*
* �������ƣ� ManageCommTargetCommFailure
* ���������� ����ͨ�Ŷ���ͨ�Ź���״̬
* ��������� ��   
* ��������� ��
* ����ֵ  �� ��
*/
void ManageCommTargetCommFailure(void)
{
    /*������CIͨ�Ŷ����ͨ�Ź���*/
    JudgeSingleCommTypeCommFailure(INNER_DEVTYPE_CI);

    /*������NZCͨ�Ŷ����ͨ�Ź���*/
    JudgeSingleCommTypeCommFailure(INNER_DEVTYPE_ZC);

    /*������Trainͨ�Ŷ����ͨ�Ź���*/
    JudgeTrainCommFailure();
}

/*
* �������ƣ� JudgeSingleCommTypeCommFailure
* ���������� �жϵ���ͨ�Ŷ���ͨ�Ź���״̬
* ��������� const UINT8 commTargetType,ͨѶ��������   
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeSingleCommTypeCommFailure(const UINT8_S commTargetType)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S commTargetBufIndex = DEFAULT_ZERO;
    UINT8_S singleCommTargetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S rtnGet = DEFAULT_ZERO;

    /*��ʼ��*/
    MemorySet(&commTargetIdBuff[DEFAULT_ZERO],((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
               DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    /*��ȡͨ�Ŷ��������*/
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
        /*��崻�����������������������*/
    }
}

/*
* �������ƣ� ProcessCiCommFailure
* ���������� �жϵ���CIͨ�Ŷ���ͨ�Ź���״̬
* ��������� const UINT16 commCiId,ͨѶCI��ID   
* ��������� ��
* ����ֵ  �� ��
*/
void ProcessCiCommFailure(const UINT16_S commCiId)
{
    /*����CI��Χ�ڵĵ�������״̬*/
    InitFailureCiSwitch(commCiId);

    /*����CI��Χ�ڵ��źŻ�״̬*/
    InitFailureCiSignal(commCiId);

    /*����CI��Χ�ڵ�������״̬*/
    InitFailureCiPsd(commCiId);

    /*����CI��Χ�ڵĽ���ͣ����ť״̬*/
    InitFailureCiEsb(commCiId);

    /*����CI��Χ�ڵļ�������״̬*/
    InitFailureCiAc(commCiId);

    /*����CI��Χ�ڵ��߼�����״̬*/
    InitFailureCiLogicSection(commCiId);

    /*����CI��Χ�ڵı�������״̬*/
    InitFailureCiOverlap(commCiId);

    /*����CI��Χ�ڵĽ�·״̬*/
    InitFailureCiRoute(commCiId);

    /*����CI��Χ�ڵ������۷���ť״̬*/
    InitFailureCiDrButoon(commCiId);

    /*����CI��Χ�ڵ������۷���״̬*/
    InitFailureCiDrLamp(commCiId);

    /*����CI��Χ�ڵ��г�״̬*/
    JudgeTrainInfoOfCiCommFailure(commCiId);
}

/*
* �������ƣ� ProcessZcCommFailure
* ���������� �жϵ���ZCͨ�Ŷ���ͨ�Ź���״̬
* ��������� const UINT16 commZcId,ͨѶZC��ID   
* ��������� ��
* ����ֵ  �� ��
*/
void ProcessZcCommFailure(const UINT16_S commZcId)
{
    /*����NZc��Χ�ڵĵ�������״̬*/
    InitFailureNZcSwitch(commZcId);

    /*����NZc��Χ�ڵ��źŻ�״̬*/
    InitFailureNZcSignal(commZcId);

    /*����NZc��Χ�ڵ�������״̬*/
    InitFailureNZcPsd(commZcId);

    /*����NZc��Χ�ڵĽ���ͣ����ť״̬*/
    InitFailureNZcEsb(commZcId);

    /*����NZc��Χ�ڵļ�������״̬*/
    InitFailureNZcAc(commZcId);

    /*����NZc��Χ�ڵı�������״̬*/
    InitFailureNZcOverlap(commZcId);

    /*����NZc��Χ�ڵĽ�·״̬*/
    InitFailureNZcRoute(commZcId);

    /*����NZc��Χ�ڵ������۷���ť״̬*/
    InitFailureNZcDrButton(commZcId);

    /*����NZc��Χ�ڵ������۷���״̬*/
    InitFailureNZcDrLamp(commZcId);

    /*����ͨ��Nzc��Χ�ڵ���ʱ����*/
    DeleteSingleZcTsrInfo(commZcId);

    /*����NZc��Χ�ڵ��г�״̬*/
    JudgeTrainInfoOfNZcCommFailure(commZcId);
}

/*
* �������ƣ� JudgeTrainCommFailure
* ���������� �ж��г�ͨ�Ź���״̬
* ��������� ��   
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeTrainCommFailure(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    TrainSafeLocStruct trainUnSafeLocStru;

    /*��ʼ��*/
    MemorySet(&trainUnSafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),DEFAULT_ZERO,((UINT32_S)(sizeof(TrainSafeLocStruct))));

    for (cycle = 1U;cycle < COMM_TRAIN_ID_MAX;cycle++)
    {
        /*�г�ͨ���У��±꼴ΪId*/
        if (COMM_STATUS_ABNORMAL == GetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle)))
        {
            if (RETURN_SUCCESS == GetTrainUnSafeLoc(((UINT16_S)cycle),&trainUnSafeLocStru))
            {
                /*�����г�ͨ�Ź���*/
                ProcessTrainCommFailure((UINT16_S)cycle);
                LogPrintf(1U,"17.001 TrainId=%d,Comm Error!\n",cycle);
            } 
            else
            {
                /*������*/
            }

            /*�����г�����״̬*/
            SetTrainStatus(((UINT16_S)cycle),TRAIN_STATE_FAILURE);

            /*����г�ͨ��״̬*/
            SetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)cycle),DEFAULT_ZERO);

        } 
        else
        {
            /*Do nothing currently !*/
        }
    }
}

/*
* �������ƣ� ProcessTrainCommFailure
* ���������� �жϵ����г�ͨ�Ź���״̬
* ��������� const UINT16 commTrainId,ͨѶ�г�ID   
* ��������� ��
* ����ֵ  �� ��
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

    /*��ʼ��*/
    MemorySet(&trainUnSafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),DEFAULT_ZERO,((UINT32_S)(sizeof(TrainSafeLocStruct))));
    MemorySet(&trainOccAcIdBuff[DEFAULT_ZERO],((UINT32_S)(sizeof(UINT16_S)*ZC_TWO_POINT_AC_NUM_MAX)),
               DEFAULT_ZERO,((UINT32_S)(sizeof(UINT16_S)*ZC_TWO_POINT_AC_NUM_MAX)));

    /*��ȡ�г���Ϣ*/
    trainDir = GetTrainUnsafeDirection(commTrainId);

    if (RETURN_SUCCESS == GetTrainUnSafeLoc(commTrainId,&trainUnSafeLocStru))
    {
        tempRtn = CheckAcOrderBetweenTwoPoints(trainUnSafeLocStru.TrainTailLink,trainUnSafeLocStru.TrainHeadLink,trainDir,&trainOccAcNum,trainOccAcIdBuff);

        if ((2U == tempRtn) || (1U == tempRtn))
        {
            /*�����г�ռѹ�ļ�������*/
            for (cycle = DEFAULT_ZERO;cycle < trainOccAcNum;cycle++)
            {
                /*��ȡ�����������г�������Ϣ*/
                if (DEFAULT_ZERO == cycle)
                {
                    /*��β���ڼ�������*/
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
                        /*������*/
                    }
                } 
                else
                {
                    /*������*/
                }

                if (cycle == (trainOccAcNum - 1U))
                {
                    /*��ͷ���ڼ�������*/
                    frontTrainId = FindFrontTrainOfTrainCommFailure(commTrainId,trainOccAcIdBuff[cycle]);

                    if ((DEFAULT_ZERO != frontTrainId)
                        && (commTrainId != frontTrainId))
                    {
                        SetTrainSuspectTail(frontTrainId,FLAG_SET);

                        LogPrintf(1U,"17.003 Find frontTrainId=%d!\n",frontTrainId);
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
        else
        {
            /*������*/
        }
    } 
    else
    {
        /* ������ */
    }    
}

/*
* �������ƣ� FindFrontTrainOfTrainCommFailure
* ���������� ���ҹ����г�ǰ���г�����ͷ���ڼ���ͳ�ͷ���ڼ���ǰ�����ᣩ
* ��������� const UINT16 trainId,�г���ID 
*            const UINT16_S acId,��ͷ���ڼ�������
* ��������� ��
* ����ֵ  �� 0:δ�鵽�г�
*           >0:�г�Id
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
	
    /*��ʼ��*/
    MemorySet(&trainSequenceBuff[DEFAULT_ZERO],sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC,DEFAULT_ZERO,sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC);

    trainSeqInAc = GetTrainIdInTrainSequence(acId,trainId);
    trainDir = GetTrainUnsafeDirection(trainId);

    /*��ȡ���������г�����*/
    trainNumInAc = GetAcTrainOfAcNum(acId);

    if ((DEFAULT_UINT8_VALUE != trainSeqInAc)
        && (DEFAULT_ZERO < trainNumInAc))
    {
        if (DEFAULT_ZERO == trainSeqInAc)
        {
            /*��һ�г�,��ѯǰ������ں��г�*/
            tempRtn = CheckFrontACStatus(acId,trainDir,&frontAcId);

            if ((RETURN_SUCCESS == tempRtn)
                && (DEFAULT_ZERO != frontAcId))
            {
                /*��ȡǰ�����������г�����*/
                trainNumInFrontAc = GetAcTrainOfAcNum(frontAcId);

                if ((DEFAULT_ZERO < trainNumInFrontAc)
                    && (DEFAULT_UINT8_VALUE != trainNumInFrontAc))
                {
                    frontAcDir = CalculateTrainDirInOtherAc(FLAG_SET,acId,frontAcId,trainDir);             
					getFlag = GetAcTrainSequenceBuff(frontAcId,SIZE_MAX_TRAINOFAC,trainSequenceBuff);
					
                    if ((AC_DIR_FARAWAY == frontAcDir) && (RETURN_SUCCESS == getFlag))
                    {
                        /*��ȡǰ�������һ��Ϊ������г�ID*/
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
            else
            {
                /*�޳�,������*/
            }
        } 
        else
        {
            /*���Ǳ������һ�г�,��ȡ�ü�����һ�г�ID*/
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
        /*������*/
    }

    return frontTrainId;
}

/*
* �������ƣ� FindRearTrainOfTrainCommFailure
* ���������� ���ҹ����г����г�����ͷ���ڼ���ͳ�ͷ���ڼ���ǰ�����ᣩ
* ��������� const UINT16 trainId,�г���ID 
*            const UINT16_S acId,��β���ڼ�������
* ��������� ��
* ����ֵ  �� 0 :δ�鵽�г�
*            >0:�г�Id
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
	
    /*��ʼ��*/
    MemorySet(&trainSequenceBuff[DEFAULT_ZERO],sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC,DEFAULT_ZERO,sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC);

    trainSeqInAc = GetTrainIdInTrainSequence(acId,trainId);
    trainDir = GetTrainUnsafeDirection(trainId);

    /*��ȡ���������г�����*/
    trainNumInAc = GetAcTrainOfAcNum(acId);

    if ((DEFAULT_UINT8_VALUE != trainSeqInAc)
        && (DEFAULT_ZERO < trainNumInAc))
    {
        if (trainSeqInAc == (trainNumInAc - 1U))
        {
            /*���һ�г�,��ѯ�󷽼����һ�г�*/
            tempRtn = CheckRearACStatus(acId,trainDir,&rearAcId);

            if ((RETURN_SUCCESS == tempRtn)
                && (DEFAULT_ZERO != rearAcId))
            {
                /*��ȡ�󷽼��������г�����*/
                trainNumInRearAc = GetAcTrainOfAcNum(rearAcId);

                if ((DEFAULT_ZERO < trainNumInRearAc)
                    && (DEFAULT_UINT8_VALUE != trainNumInRearAc))
                {
                    rearAcDir = CalculateTrainDirInOtherAc(FLAG_UNSET,acId,rearAcId,trainDir);
                    getFlag = GetAcTrainSequenceBuff(rearAcId,SIZE_MAX_TRAINOFAC,trainSequenceBuff);
					
                    if ((AC_DIR_CLOSED == rearAcDir) && (RETURN_SUCCESS == getFlag))
                    {
                        /*��ȡ�󷽼����һ����Ϊ������г�ID*/
                        for (cycle = DEFAULT_ZERO;cycle < trainNumInRearAc;cycle++)
                        {
                            if (trainId != trainSequenceBuff[cycle])
                            {
                                rearTrainId = trainSequenceBuff[cycle];
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
                        /*������*/
                    }
                } 
                else
                {
                    /*������*/
                }
            } 
            else
            {
                /*�޳�,������*/
            }
        } 
        else
        {
            /*���Ǳ��������һ�г�,��ȡ�ü�����һ�г�ID*/
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



