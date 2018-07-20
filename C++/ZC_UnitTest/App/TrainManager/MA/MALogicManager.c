/********************************************************                                                                                                            
*
* �� �� ���� MALogicManager.c
* ��    �ߣ� ZC��
* ����ʱ�䣺 2015-04-18
* ����    �� �ƶ���Ȩ�߼����� 
* ��ע    �� �� 
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
* �������ƣ� ManageTrainMaInfo
* ���������� �г����ƶ���Ȩ��Ϣ����
* ��������� ��
* ��������� ��
* ����ֵ  �� ��
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
                /*�����ƶ���Ȩ*/
                CalculateTrainMa(trainId);

                break;
            case TRAIN_STATE_HANDOVER:
                /*�ƽ�״̬�ƶ���Ȩ����*/
                JudgeHandOverTrain(trainId);

                break;
            case TRAIN_STATE_REVERSE:
                /*�����۷�״̬�µ��ƶ���Ȩ*/
                JudgeReverseStateMaInfo(trainId);

                break;
            case TRAIN_STATE_CANCELLATION:
                /*����ע��״̬�ƶ���Ȩ*/
                JudgeCancellationStateMaInfo(trainId);

                break;
            case TRAIN_STATE_FAILURE:
                /*�������״̬�ƶ���Ȩ*/
                JudgeTrainStateFailure(trainId);
                break;	
            default:
                /*���г���������״̬ʱ,����ƶ���Ȩ��Ϣ*/
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
                    /*�������״̬�ƶ���Ȩ*/
                    JudgeTrainStateFailure(trainId);
                } 
                else
                {
                    /*ά�ֿ�MA��Ϣ*/
                }
                break;
            case TRAIN_MODE_OUT:

                if (TRAIN_STATE_CANCELLATION == trainStatus)
                {
                    /*����ע��״̬�ƶ���Ȩ*/
                    JudgeCancellationStateMaInfo(trainId);
                } 
                else
                {
                    /*�������״̬�ƶ���Ȩ*/
                    JudgeTrainStateFailure(trainId);
                }
                break;
            default:
                /*���MA��Ϣ*/
                DeleteSingleTrainMaInfo(trainId);
                break;
            }
        }
    }	
}

/*
* �������ƣ� JudgeTrainStateFailure
* ���������� ����״̬�г�����
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeTrainStateFailure(const UINT16_S trainId)
{
    /*����״̬��������г��ƶ���Ȩ��Ϣ*/
    ClearSingleTrainMaInfo(trainId);

    /*����MA����Ϊ��MA*/
    SetMaType(trainId,ABNORMAL_MA_TYPE);

    LogPrintf(1U,"24.001 TrainId=%d,State Failure!\n",trainId);
}

/*
* �������ƣ� JudgeHandOverTrain
* ���������� �ƽ�״̬�µ��ƶ���Ȩ����
* ��������� const UINT16_S trainId,�г�ID
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeHandOverTrain(const UINT16_S trainId)
{
    UINT8_S trainHandOverInType = DEFAULT_ZERO;

    /*�ȼ��㱾ZC���ƶ���Ȩ*/
    CalculateTrainMa(trainId);

    trainHandOverInType = GetTrainHandoverInType(trainId);

    /*�ж��Ƿ��������ZC���ƶ���Ȩ��Ϣ*/
    if ((NZC_TRAIN_CONFIRMATION == trainHandOverInType)
        || (NZC_TRAIN_HADTOOKOVER == trainHandOverInType))
    {
        if (LINE_MAX_TRAIN_ID != GetNextZcMaStatusBufIndex(trainId))
        {
            /*����ƶ���Ȩ*/
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
        /*������*/
    }
}


/*
* �������ƣ� CalculateTrainMa
* ���������� �г����ƶ���Ȩ��Ϣ����
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void CalculateTrainMa(const UINT16_S trainId)
{
    TrainSafeLocStruct trainSafeLocStru;

    /*���MA��Ϣ*/
    ClearSingleTrainMaInfo(trainId);

    /*����MA����λ��*/
    SetMaStatusTrainId(trainId);
    SetMaType(trainId,NORMAL_MA_TYPE);

    /*�Խ�·�ͽ�·�ı�������Ϊ��׼�����ƶ���Ȩ�յ���Ϣ*/
    JudgeTrainMaByRouteInfo(trainId);

    /* LogPrintf(1U,"13.01A %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    /*�Խ�·�ⷽ��������Ϊ��׼�����ƶ���Ȩ��Ϣ*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {      
        JudgeTrainMaByOutwardAcInfo(trainId);     
    }
    else
    {
        /*������*/
    }

    /* LogPrintf(1U,"13.01B %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    /*�Ե�ǰMA����Χ�ڼ���������ϢΪ��׼�����ƶ���Ȩ�յ���Ϣ*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {
        JudgeTrainMaByAcInfo(trainId);
    }
    else
    {
        /*������*/
    }

    /* LogPrintf(1U,"13.01C %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */ 
    /*��վ̨Ϊ��׼�����ƶ���Ȩ�յ���Ϣ*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {
        JudgeTrainMaByStationInfo(trainId);
    }
    else
    {
        /*������*/
    }

    /* LogPrintf(1U,"13.01D %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    /*�����ƶ���Ȩ�����Ϣ*/
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
        /*��дMa�յ�����*/
        CalculateMaEndAttribute(trainId);

        /*�����ƶ���Ȩ�Ƿ���Ҫ����*/
        CalculatAdjustMaEndInfo(trainId);
    } 
    else
    {
        /*������*/
    }

    /* LogPrintf(1U,"13.01F %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    /*�����ƶ���Ȩ��Χ�ڵ��ϰ�����Ϣ*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {
        CalculateObsInfoBelongToMaArea(trainId);
    }
    else
    {
        /*������*/
    }

    /* LogPrintf(1U,"13.01G %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
    /*�����ƶ���Ȩ��Χ�ڵ���ʱ������Ϣ*/
    if (DEFAULT_ZERO != GetMaTailLink(trainId))
    {
        CalculateTsrInfoBelongToMaArea(trainId);
    }
    else
    {
        /*������*/
    }

    /* LogPrintf(1U,"13.01H %d,0x%x,%d,%d,%d,%d\n",trainId,GetMaType(trainId),GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId)); */
}

/*
* �������ƣ� JudgeTrainMaByRouteInfo
* ���������� �����Խ�·Ϊ�������г����ƶ���Ȩ��Ϣ����
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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

    /*��ȡ��·���һ����·*/
    rtnGetLastRoute = GetTrainMatchedLastRouteId(trainId,&lastRouteId);

    if ((DEFAULT_ZERO != lastRouteId) && (RETURN_SUCCESS == rtnGetLastRoute))
    {
        /*��ȡ��·������Ϣ*/
        if (RETURN_SUCCESS == GetRoutOfAcIdFromIndex(lastRouteId,(GetRouteOfAcNum(lastRouteId) - 1U),&lastAcIdOfRoute))
        {
            trainDir = GetTrainUnsafeDirection(trainId);

            if (RETURN_SUCCESS == CheckAcTerminalPosition(lastAcIdOfRoute,((UINT16_S)trainDir),&acOfLinkId,&acOfLinkOffset))
            {
                /*��ȡ��·��Ӧ�ı�������*/
                matchOverlapId = JudgeRouteOfLockOverlap(lastRouteId);

                if (DEFAULT_ZERO != matchOverlapId)
                {
                    /*��ȡ����������Ϣ*/
                    overlapOfAcNum = GetOverlapContainAcNum(matchOverlapId);

                    if (RETURN_SUCCESS == GetOverlapContainAcBuff(matchOverlapId,OVERLAP_OF_AC_SUM_MAX,overlapAcIdBuff))
                    {
                        /*�жϸñ��������Ƿ����*/
                        if (RETURN_SUCCESS == JudgeOverlapOfAcFree(overlapOfAcNum,overlapAcIdBuff))
                        {
                            /*��ѯ�������γ���*/
                            if (RETURN_SUCCESS == CalulateOverlapLength(overlapOfAcNum,overlapAcIdBuff,&overlapLength))
                            {
                                /*��ȡ��·���һ�����������յ�λ��*/
                                lineMinOverlapLength = (UINT32_S)GetLineMinOverlapLength();
                                checkFlag = CheckNextPointOnDistance(acOfLinkId,acOfLinkOffset,trainDir,lineMinOverlapLength,&maEndLink,&maEndOffset,&errorSwitchId);

                                if ((overlapLength > lineMinOverlapLength) && (3U == checkFlag))
                                {
                                    /*��MA�յ�����Ϊ��С�ı������γ���λ��*/
                                    SetMaTailLink(trainId,maEndLink);
                                    SetMaTailOffset(trainId,maEndOffset);
                                } 
                                else
                                {
                                    /*��MA�յ������ڱ��������յ�*/
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
                                /*��MA�յ������ڽ�·�ն��յ�*/
                                SetMaTailLink(trainId,acOfLinkId);
                                SetMaTailOffset(trainId,acOfLinkOffset);
                            }
                        } 
                        else
                        {
                            /*��MA�յ������ڽ�·�ն��յ�*/
                            SetMaTailLink(trainId,acOfLinkId);
                            SetMaTailOffset(trainId,acOfLinkOffset);
                        }
                    } 
                    else
                    {
                        /*��MA�յ������ڽ�·�ն��յ�*/
                        SetMaTailLink(trainId,acOfLinkId);
                        SetMaTailOffset(trainId,acOfLinkOffset);
                    }
                } 
                else
                {
                    /*��MA�յ������ڽ�·�ն��յ�*/
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
            /*�ܿ�ZCΪ��ZC,�����ƶ�*/
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-S13\n",trainId);
        } 
        else
        {
            /*��Ϊ��ZC����,����Ma����Ϊ��MA*/
            SetMaType(trainId,NO_MA_TYPE);
        }
    }
}

/*
* �������ƣ� JudgeRouteOfLockOverlap
* ���������� �жϽ�·�Ƿ�������գ������ı�������
* ��������� const UINT16_S routeId,�г�Id
* ��������� ��
* ����ֵ  �� 0u:��overlap
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

    /*�жϸý�·�Ƿ���б�������*/
    routeOverlapNum = GetRouteOfOverlapNum(routeId);

    if (routeOverlapNum > DEFAULT_ZERO)
    {
        GetRoutOfOverlapIdBuff(routeId,ROUTE_OF_OVERLAP_SUM_MAX,routeOverlapIdBuff);

        for (cycleOverlp = DEFAULT_ZERO;cycleOverlp < routeOverlapNum;cycleOverlp++)
        {
            /*�жϱ��������Ƿ��������*/
            switchAttribute = (UINT8_S)(GetOverlapSwitchAttribute(routeOverlapIdBuff[cycleOverlp]));

            if (FLAG_SET == switchAttribute)
            {
                /*��ȡ��������*/
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
                    /*������*/
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
        /*������*/
    }

    return rtnValue;
}

/*
* �������ƣ� JudgeOverlapOfAcFree
* ���������� �жϱ������ι����ļ��������Ƿ����
* ��������� const UINT8_S overlapOfAcNum,�������ΰ����ļ�������
*            const UINT16_S overlapAcIdBuff[]���������ΰ����ļ���ID
* ��������� ��
* ����ֵ  �� RETURN_SUCCESS:����
*			 RETURN_ERROR:�ǿ���
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
                /*������*/
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
            /*������*/
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* �������ƣ� CalulateOverlapLength
* ���������� �жϱ������ι����ļ��������Ƿ����
* ��������� const UINT8_S overlapOfAcNum,�������ΰ����ļ�������
*            const UINT16_S overlapAcIdBuff[]���������ΰ����ļ���ID
* ��������� UINT32_S *overlapLength,����
* ����ֵ  �� RETURN_SUCCESS:����ɹ�
*			 RETURN_ERROR  :����ʧ��
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
            /*������*/
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* �������ƣ� JudgeTrainMaByOutwardAcInfo
* ���������� �Խ�·���߱��������ⷽһ������������ϢΪ��׼�����ƶ���Ȩ��Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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
        /*��ȡ�ƶ���Ȩ�յ�������������*/
        trainDir = GetTrainUnsafeDirection(trainId);
        rtnCheckLink = CalculatePointOfInsideLink(trainDir,GetMaTailLink(trainId),GetMaTailOffset(trainId),&checkLinkId);

        if (1U == rtnCheckLink)
        {
            maEndAcId = CheckPositionBelongAc(checkLinkId);	

            if (DEFAULT_ZERO != maEndAcId)
            {
                /*��ѯ��ǰ����ǰ����������*/
                if (RETURN_SUCCESS == CheckFrontACStatus(maEndAcId,trainDir,&frontAcId))
                {
                    if (AC_FREE_STATUS == GetAcStatusNow(frontAcId))
                    {
                        /*������*/
                    } 
                    else
                    {
                        /*����ǰ��������Ϣ�����ƶ���Ȩ*/
                        JudgeTrainMaByAcOfFrontAcInfo(FLAG_UNSET,trainId,maEndAcId,frontAcId);
                    }
                } 
                else
                {
                    /*��ѯǰ������ʧ��,������*/
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
            /* ��ѯMA�յ��ڷ���Linkʧ��,������ */
        }            
    } 
    else
    {
        /*���������г������������,������*/
    }
}

/*
* �������ƣ� CalculateAcOrderHaveOtherTrain
* ���������� �жϴӳ�ͷ��MA�յ�����������Ƿ���������г�/����ռ��
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� 0u:�����������г�/����ռ��
*            1u:���������г�/����ռ��
*            2u:��������ѽ���
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
        /*��ѯ�Էǰ�ȫ��ͷλ����MA�յ�λ�õļ�����������*/
        if (RETURN_SUCCESS == CheckAcOrderBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,checkLinkId,trainDir,&acNum,acIdBuff))
        {          
            /*ͨ���������Ϣ�������ƶ���Ȩ��Ϣ*/
            for (cycle = DEFAULT_ZERO;cycle < acNum;cycle++)
            {
                trainIdInAcIndex = GetTrainIdInTrainSequence(acIdBuff[cycle],trainId);

                if (DEFAULT_ZERO == cycle)
                {
                    if (DEFAULT_UINT8_VALUE == trainIdInAcIndex)
                    {
                        if (GetAcBelongZcId(acIdBuff[cycle]) == GetLocalZcId())
                        {
                            /*��һ�����������г�����,�����ڸ����,����ȫ��*/
                            SetTrainToModeToRM0(trainId);
                            rtnValue = 2U;
                            LogPrintf(1u,"%d-B11\n",trainId);
                        } 
                        else
                        {
                            /*����ZC�ļ�������,������*/
                        }

                    }
                    else
                    {
                        if (DEFAULT_ZERO == trainIdInAcIndex)
                        {
                            /*��һ�г�,��������*/
                        } 
                        else
                        {
                            /*���ǵ�һ�г�,˵�����������г�*/
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
                            /*������ͨ���г�ռ�ü�������,ֱ�ӷ��ذ���ռ��*/
                            rtnValue = 1U;
                            break;
                        } 
                        else
                        {
                            /*��������*/
                        }
                    } 
                    else
                    {
                        if ((DEFAULT_UINT8_VALUE != acTrainNum))
                        {
                            if (DEFAULT_UINT8_VALUE == trainIdInAcIndex)
                            {
                                /*�����᲻�������г�,˵�����������г�*/
                                rtnValue = 1U;
                                break;
                            }
                            else
                            {
                                if (DEFAULT_ZERO == trainIdInAcIndex)
                                {
                                    /*��һ�г�,��������*/
                                } 
                                else
                                {
                                    /*���ǵ�һ�г�,˵�����������г�*/
                                    rtnValue = 1U;
                                    break;
                                }
                            }
                        } 
                        else
                        {
                            /*��������*/
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
        /* ������ */
    }

    return rtnValue;
}

/*
* �������ƣ� JudgeTrainMaByAcInfo
* ���������� �Լ���������ϢΪ��׼�����ƶ���Ȩ��Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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
        /*��ѯ�Էǰ�ȫ��ͷλ����MA�յ�λ�õļ�����������*/
        if (RETURN_SUCCESS == CheckAcOrderBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,checkLinkId,trainDir,&acNum,acIdBuff))
        {
            /*ͨ���������Ϣ�������ƶ���Ȩ��Ϣ*/
            for (cycle = DEFAULT_ZERO;cycle < acNum;cycle++)
            {
                trainIdInAcIndex = GetTrainIdInTrainSequence(acIdBuff[cycle],trainId);

                if (DEFAULT_UINT8_VALUE == trainIdInAcIndex)
                {
                    if (DEFAULT_ZERO != cycle)
                    {
                        /*���г���λ�ڸü���������*/
                        if (RETURN_ERROR == JudgeTrainMaByAcOfFrontAcInfo(FLAG_SET,trainId,acIdBuff[cycle-1U],acIdBuff[cycle]))
                        {
                            /*������һ����������*/
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
                            /*��һ�����������г�����,�����ڸ����,����ȫ��*/
                            SetTrainToModeToRM0(trainId);
                            LogPrintf(1u,"%d-S14\n",trainId);
                        } 
                        else
                        {
                            /*����ZC���᲻����*/
                        }

                    }
                } 
                else
                {
                    /*���г���λ�ڸü���������*/
                    /*�ж��г��Ƿ�λ�ڸü����ڵ�һ�г���*/
                    if (DEFAULT_ZERO == trainIdInAcIndex)
                    {
                        /*������ѯ��һ����������*/
                    } 
                    else
                    {
                        /*��ȡ�ü�������ǰ���г���Ϣ*/
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
        /* ��ȡλ�úͲ���MA�յ�����Link����1��ʧ�� */
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-S15\n",trainId);
    }
}

/*
* �������ƣ� JudgeCommUnCtTrainForMa
* ���������� �ж��Ƿ�����׷�ٷ�ͨ���г�����MA�س�Ӱ����������
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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
            /*����ƶ���Ȩ�Ƿ�λ�ڷǰ�ȫ��ͷ��*/
            rtnTemp = CheckLocRelationBetweenTwoPoints(GetMaTailLink(trainId),GetMaTailOffset(trainId),
                trainUnSafeLocStru.TrainHeadLink,trainUnSafeLocStru.TrainHeadOffset,trainDir);

            if ((2U == rtnTemp) || (3U == rtnTemp))
            {
                /*ǰ��Ϊ�ǰ�ȫ��ͷλ��,������*/
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
* �������ƣ� JudgeTrainMaByAcOfFrontAcInfo
* ���������� ����ǰ�����������ڵ��г��Ե�ǰ�г��ƶ���Ȩ��Ӱ��
* ��������� const UINT8_S flagType,(������Ϣ:0x55,����ǰ���������г���Ϣ;0xaa,������ǰ���������г���Ϣ)
*            const UINT16_S trainId,�г�Id
*            const UINT16_S acId,��ǰ����
*            const UINT16_S frontAcId,ǰ����������    
* ��������� ��
* ����ֵ  �� RETURN_SUCCESS,����ɹ�
*            RETURN_ERROR  ,����ʧ��
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
    UINT8_S trainSumOnAc = DEFAULT_ZERO;   /*pbw,ǰ�������������г���Ŀ*/
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
    /* pbw,2017.7.14,�����ֽ�����źŻ���������������ͨ�ţ��ڷֽ�����ڼ��ᳵ������,
    ��ǰ����������UTռ�����г� */
    if ((AC_UT_OCC_STATUS == GetAcUtFlag(frontAcId)))
    {
        /* �����ͨ���г�ռ�ã���ѯ�󷽼������� */
        if ((RETURN_SUCCESS == CheckRearACStatus(frontAcId,trainDir,&rearAcId))
            && (DEFAULT_ZERO != trainSafeHeadAc))
        {
            /*�жϺ󷽼����Ƿ����г���ȫ��ͷռѹ����*/
            if (rearAcId == trainSafeHeadAc)
            {
                /*�г���Ҫ�����ƶ�*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-S1\n",trainId);
            } 
            else
            {
                /*���ƶ���Ȩ�ŵ��󷽼����ʼ��λ��*/
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
                /* �޳� */
                if(DEFAULT_ZERO < GetAcUtRedundance(frontAcId))
                {
                    /* pbw,2017.7.19 ռ���޳�������UTռ��֮ǰ����ʱ��,MA�յ�Ϊ�ü�������ʼ�� */
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
                /* ǰ�����������г�(����ռ�á����ο���2�����) */
                trainDirInAc = CalculateTrainDirInOtherAc(FLAG_SET,acId,frontAcId,trainDir);

                if ((DEFAULT_ZERO == trainDirInAc)
                    || (AC_DIR_DEFAULT == trainDirInAc))
                {
                    /*���г����ж��޷�����߼���ʧ�ܣ�����ȫ��*/
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
                        /*��ѯ�󷽼�������*/
                        if ((RETURN_SUCCESS == CheckRearACStatus(frontAcId,trainDir,&rearAcId))
                            && (DEFAULT_ZERO != trainSafeHeadAc))
                        {
                            /*�жϺ󷽼����Ƿ����г���ȫ��ͷռѹ�������Ƿ���к��Σ������*/
                            if (AC_DIR_FARAWAY == trainDirInAc)
                            {
                                if (FLAG_SET == GetTrainSuspectTail(frontTrainId))
                                {
                                    if (rearAcId == trainSafeHeadAc)
                                    {
                                        /*�г���Ҫ�����ƶ�*/
                                        SetTrainToModeToRM0(trainId);
                                        LogPrintf(1u,"%d-S5\n",trainId);
                                    } 
                                    else
                                    {
                                        /*���ƶ���Ȩ�ŵ��󷽼����ʼ��λ��*/
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
                                        /*����ǰ���г�������ƶ���Ȩ����*/
                                        CalculateTrainMaByFrontTrainTail(trainId,frontTrainId,frontAcId);
                                    } 
                                    else
                                    {
                                        /*������*/
                                    }
                                }
                            } 
                            else
                            {
                                if (FLAG_SET == GetTrainSuspectHead(trainId))
                                {
                                    if (rearAcId == trainSafeHeadAc)
                                    {
                                        /*�г���Ҫ�����ƶ�*/
                                        SetTrainToModeToRM0(trainId);
                                        LogPrintf(1u,"%d-S7\n",trainId);
                                    } 
                                    else
                                    {
                                        /*���ƶ���Ȩ�ŵ��󷽼����ʼ��λ��*/
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
                                        /*����ǰ���г�������ƶ���Ȩ����*/
                                        CalculateTrainMaByFrontTrainHead(trainId,frontTrainId,frontAcId);
                                    } 
                                    else
                                    {
                                        /* pbw 2017.7.17 */
                                        if (RETURN_SUCCESS == CheckAcTopPosition(rearAcId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
                                        {
                                            /*��·�ⷽ�ļ��������ڵ��г���ǰ�˿��ɱ��,�س��ƶ���Ȩ*/
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
                            /*�г���Ҫ�����ƶ�*/
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
            /* ����,ֱ�ӷ���ʧ�� 
            rtnValue = RETURN_ERROR;
        }*/
    }	


#else
    if ((AC_UT_OCC_STATUS == GetAcUtFlag(frontAcId))
        && (DEFAULT_ZERO == trainSumOnAc))
        /*
        if ((AC_UT_OCC_STATUS == GetAcUtFlag(frontAcId)))*/
    {
        /*�����ͨ���г�ռ�ã���ѯ�󷽼�������*/
        if ((RETURN_SUCCESS == CheckRearACStatus(frontAcId,trainDir,&rearAcId))
            && (DEFAULT_ZERO != trainSafeHeadAc))
        {
            /*�жϺ󷽼����Ƿ����г���ȫ��ͷռѹ����*/
            if (rearAcId == trainSafeHeadAc)
            {
                /*�г���Ҫ�����ƶ�*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-S1\n",trainId);
            } 
            else
            {
                /*���ƶ���Ȩ�ŵ��󷽼����ʼ��λ��*/
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
        /*����ǰ���г�������ƶ���Ȩ�ı�*/
        /*��ȡǰ�����������һ�г�*/
        if((DEFAULT_UINT8_VALUE == trainSumOnAc) || (DEFAULT_ZERO == trainSumOnAc))
        {
            /*�޳�*/
            /*pbw ���ӻ�ȡʧ�ܵķ�֧*/
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            trainDirInAc = CalculateTrainDirInOtherAc(FLAG_SET,acId,frontAcId,trainDir);

            if ((DEFAULT_ZERO == trainDirInAc)
                || (AC_DIR_DEFAULT == trainDirInAc))
            {
                /*���г����ж��޷�����߼���ʧ�ܣ�����ȫ��*/
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
                    /*��ѯ�󷽼�������*/
                    if ((RETURN_SUCCESS == CheckRearACStatus(frontAcId,trainDir,&rearAcId))
                        && (DEFAULT_ZERO != trainSafeHeadAc))
                    {
                        /*�жϺ󷽼����Ƿ����г���ȫ��ͷռѹ�������Ƿ���к��Σ������*/
                        if (AC_DIR_FARAWAY == trainDirInAc)
                        {
                            if (FLAG_SET == GetTrainSuspectTail(frontTrainId))
                            {
                                if (rearAcId == trainSafeHeadAc)
                                {
                                    /*�г���Ҫ�����ƶ�*/
                                    SetTrainToModeToRM0(trainId);
                                    LogPrintf(1u,"%d-S5\n",trainId);
                                } 
                                else
                                {
                                    /*���ƶ���Ȩ�ŵ��󷽼����ʼ��λ��*/
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
                                    /*����ǰ���г�������ƶ���Ȩ����*/
                                    CalculateTrainMaByFrontTrainTail(trainId,frontTrainId,frontAcId);
                                } 
                                else
                                {
                                    /*������*/
                                }
                            }
                        } 
                        else
                        {
                            if (FLAG_SET == GetTrainSuspectHead(trainId))
                            {
                                if (rearAcId == trainSafeHeadAc)
                                {
                                    /*�г���Ҫ�����ƶ�*/
                                    SetTrainToModeToRM0(trainId);
                                    LogPrintf(1u,"%d-S7\n",trainId);
                                } 
                                else
                                {
                                    /*���ƶ���Ȩ�ŵ��󷽼����ʼ��λ��*/
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
                                    /*����ǰ���г�������ƶ���Ȩ����*/
                                    CalculateTrainMaByFrontTrainHead(trainId,frontTrainId,frontAcId);
                                } 
                                else
                                {
                                    /* pbw 2017.7.17 */
                                    if (RETURN_SUCCESS == CheckAcTopPosition(rearAcId,((UINT16_S)trainDir),&acTopLink,&acTopOffset))
                                    {
                                        /*��·�ⷽ�ļ��������ڵ��г���ǰ�˿��ɱ��,�س��ƶ���Ȩ*/
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
                        /*�г���Ҫ�����ƶ�*/
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
* �������ƣ� JudgeTrainMaByAcOfSameAcInfo
* ���������� ����ͬ���������ڵ��г��Ե�ǰ�г��ƶ���Ȩ��Ӱ��
* ��������� const UINT16_S trainId,�г�Id
*            const UINT16_S acId���г�ռѹ��������
*            const UINT8_S frontTrainIndex��ǰ���г����������±�
* ��������� ��
* ����ֵ  �� ��
*/
void JudgeTrainMaByAcOfSameAcInfo(const UINT16_S trainId,const UINT16_S acId,const UINT8_S frontTrainIndex)
{
    UINT16_S frontTrainId = DEFAULT_ZERO;

    if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(acId,frontTrainIndex,&frontTrainId))
    {
        if (FLAG_SET == GetTrainSuspectTail(frontTrainId))
        {
            /*ǰ���г�����˿���,���г���Ҫֱ�ӽ����ƶ�*/
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-B15\n",trainId);
        } 
        else
        {
            /*����ǰ���г�������ƶ���Ȩ�ı�*/
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
* �������ƣ� CalculateTrainMaByFrontTrainTail
* ���������� ����ǰ���г���β������ƶ���Ȩ����
* ��������� const UINT16_S trainId,�г�Id
*            const UINT16_S frontTrainId,ǰ���г�ID
*            const UINT16_S acId,���������Id
* ��������� ��
* ����ֵ  �� ��
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

    /*�ж�ǰ���г���״̬*/
    switch (trainType)
    {
    case TRAIN_MODE_CBTC:
    case TRAIN_MODE_TO_RM0:
        /*�����г��ƶ���ȨΪǰ���г���β*/
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
            /*���ƶ���Ȩ�����ڵ�ǰ����ʼ�����з��������λ��*/
            /*��ѯ�󷽼���*/
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
                /*�����г��ƶ���ȨΪǰ���г���β*/
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
* �������ƣ� CalculateTrainMaByFrontTrainHead
* ���������� ����ǰ���г���ͷ������ƶ���Ȩ����
* ��������� const UINT16_S trainId,�г�Id
*            const UINT16_S frontTrainId,ǰ���г�ID
*            const UINT16_S acId,���������Id
* ��������� ��
* ����ֵ  �� ��
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

    /*�ж�ǰ���г���״̬*/
    switch (trainMode)
    {
    case TRAIN_MODE_CBTC:
    case TRAIN_MODE_TO_RM0:
        /*�����г��ƶ���ȨΪǰ���г���β*/
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
        /*���ƶ���Ȩ�����ڵ�ǰ����ʼ�����з��������λ��*/
        /*��ѯ�󷽼���*/
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
                /*������*/
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
* �������ƣ� JudgeTrainMaByStationInfo
* ���������� ������վ̨Ϊ�������г����ƶ���Ȩ��Ϣ����
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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
    UINT8_S rtnOfNextPoint = DEFAULT_ZERO; /* ��ȡ��һ�㺯���ķ���ֵ */
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
        /*��ѯ�Էǰ�ȫ��ͷλ����MA�յ�λ�õļ�����������*/
        if (RETURN_SUCCESS == CheckAcOrderBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,checkLinkId,trainDir,&acNum,acIdBuff))
        {
            for (cycle = DEFAULT_ZERO;cycle < acNum;cycle++)
            {
                acId = acIdBuff[(acNum - cycle) - 1U];

                tempRtnOfCheck = CheckAcBelongToStation(acId);

                if (RETURN_SUCCESS == tempRtnOfCheck)
                {
                    /* ����վ̨����,��ȡվ̨�ն�λ�� */                   
                    if (RETURN_SUCCESS == CheckAcTerminalPosition(acId,((UINT16_S)trainDir),&terminalLink,&terminalOffset))
                    {
                        /*��ȡǰ����������*/
                        frontAcId = DEFAULT_ZERO;

                        if (1U == CheckFrontACStatus(acId,trainDir,&frontAcId))
                        {
                            /*��ȡǰ������ʼ��λ��*/
                            if (RETURN_SUCCESS == CheckAcTopPosition(frontAcId,((UINT16_S)trainDir),&frontAcLink,&frontAcOffset))
                            {
                                maTailLink = GetMaTailLink(trainId);
                                maTailOffset = GetMaTailOffset(trainId);

                                if (((maTailLink == terminalLink) && (maTailOffset == terminalOffset))
                                    || ((maTailLink == frontAcLink) && (maTailOffset == frontAcOffset)))
                                {
                                    /*�ƶ���Ȩ�յ��վ̨�ն��غ�,�ж��г��ǰ�ȫ��ͷ�Ƿ�λ��վ̨��*/							
                                    trainUnSafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);

                                    if (trainUnSafeHeadAc == acId)
                                    {
                                        if (FLAG_SET == GetTrainStopArea(trainId))
                                        {
                                            /*ά�ֵ�ǰ�ƶ���Ȩ�յ�*/
                                        } 
                                        else
                                        {
                                            /*δͣ��,�����ƶ�*/
                                            SetTrainToModeToRM0(trainId);
                                            LogPrintf(1u,"%d-B27\n",trainId);
                                        }
                                    } 
                                    else
                                    {
                                        /*�г���λ��վ̨��,�س�MA��վ̨ʼ��*/
                                        /*��ȡվ̨ʼ��λ��*/
                                        if (RETURN_SUCCESS == CheckAcTopPosition(acId,((UINT16_S)trainDir),&topLink,&topOffset))
                                        {
                                            /*���ƶ���Ȩ�س���վ̨ʼ��*/
                                            SetMaTailLink(trainId,topLink);
                                            SetMaTailOffset(trainId,topOffset);
                                        } 
                                        else
                                        {
                                            /*�����ƶ�*/
                                            SetTrainToModeToRM0(trainId);
                                            LogPrintf(1u,"%d-B28\n",trainId);
                                        }
                                    }
                                } 
                                else
                                {
                                    /*�ж��ƶ���Ȩ�Ƿ�λ��վ̨������*/
                                    /*��ȡվ̨ʼ��λ��*/
                                    if (RETURN_SUCCESS == CheckAcTopPosition(acId,((UINT16_S)trainDir),&topLink,&topOffset))
                                    {
                                        if ((maTailLink == topLink)
                                            && (maTailOffset != topOffset))
                                        {
                                            /*���ƶ���Ȩ�س���վ̨ʼ��*/
                                            SetMaTailLink(trainId,topLink);
                                            SetMaTailOffset(trainId,topOffset);
                                        } 
                                        else
                                        {
                                            /*������*/
                                            /* �ж�MA�յ��Ƿ���վ̨����������з���վ̨���ն˵���󱣻�����֮�� */
                                            /* pbw 201705025 ǰ����ȫ��β��վ̨���ն� */
#if 1                                        
                                            /* �����ø�ZC�ڳ�����������������İ�ȫ��βλ�� */
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
                                                /* MA�յ��ڱ��������� */                      
                                                rtnOfNextPoint = CheckNextPointOnDistance(frontAcLink,frontAcOffset,trainDir,(UINT32_S)GetLineMinOverlapLength(),&outSeg,&outOffset,&errorSwitchId);

                                                if((3u == rtnOfNextPoint)
                                                    && (2u == CheckLocRelationBetweenTwoPoints(frontAcLink,frontAcOffset,maTailLink,maTailOffset,trainDir))
                                                    && (2u == CheckLocRelationBetweenTwoPoints(maTailLink,maTailOffset,outSeg,outOffset,trainDir)))
                                                {
                                                    /* ���ƶ���Ȩ�س���վ̨ʼ�� */
                                                    SetMaTailLink(trainId,topLink);
                                                    SetMaTailOffset(trainId,topOffset);
                                                }
                                            }
#endif             
                                        }
                                    } 
                                    else
                                    {
                                        /*�����ƶ�*/
                                        SetTrainToModeToRM0(trainId);
                                        LogPrintf(1u,"%d-B29\n",trainId);
                                    }
                                }
                            } 
                            else
                            {
                                /*��ѯʧ��,��MA�س���վ̨ʼ��*/
                                /*��ȡվ̨ʼ��λ��*/
                                if (RETURN_SUCCESS == CheckAcTopPosition(acId,((UINT16_S)trainDir),&topLink,&topOffset))
                                {
                                    /*���ƶ���Ȩ�س���վ̨ʼ��*/
                                    SetMaTailLink(trainId,topLink);
                                    SetMaTailOffset(trainId,topOffset);
                                } 
                                else
                                {
                                    /*�����ƶ�*/
                                    SetTrainToModeToRM0(trainId);
                                    LogPrintf(1u,"%d-B30\n",trainId);
                                }
                            }
                        } 
                        else
                        {
                            /* ������ */
                        }
                    } 
                    else
                    {
                        /*�����ƶ�*/
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-B31\n",trainId);
                    }
                } 
                else
                {
                    if (RETURN_ERROR == tempRtnOfCheck)
                    {
                        /*�����ƶ�*/
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-B32\n",trainId);
                    } 
                    else
                    {
                        /*������վ̨*/
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
        /* ��ȡλ�úͲ���MA�յ�����Link����1��ʧ�� */
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B33\n",trainId);
    }

}

/*
* �������ƣ� CalculateObsInfoBelongToMaArea
* ���������� �����ƶ���Ȩ��Χ�ڵ��ϰ�����Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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
        /*��ѯ�ƶ���Ȩ��Χ�ڵĵ�������*/
        if (RETURN_ERROR != CheckSwitchOrderBetweenTwoPoints(trainMaHeadLink,trainMaTailLink,
            trainDir,&switchNum,switchIdBuff))
        {
            for (cycle = DEFAULT_ZERO;cycle < switchNum;cycle++)
            {
                obsOfMaStruBuff[obsNum].ObsId = switchIdBuff[addIndex];
                obsOfMaStruBuff[obsNum].ObsType = OBS_TYPE_POINT;
                /*��д�����״̬��Ϣ*/
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

            /*��ѯPSD����*/
            if (RETURN_ERROR != CheckPsdOrderBetweenTwoPoints(trainMaHeadLink,trainMaTailLink,
                trainDir,&psdNum,psdIdBuff))
            {
                for (cycle = DEFAULT_ZERO;cycle < psdNum;cycle++)
                {
                    obsOfMaStruBuff[obsNum].ObsId = psdIdBuff[cycle];
                    obsOfMaStruBuff[obsNum].ObsType = OBS_TYPE_PSD;

                    /*��дpsd��״̬��Ϣ*/
                    obsOfMaStruBuff[obsNum].ObsStatus = GetPsdStatus(psdIdBuff[cycle]);
                    obsOfMaStruBuff[obsNum].ObsLockStatus = GetPsdStatus(psdIdBuff[cycle]);
                    obsNum++;
                }

                /*��ѯEsb����*/
                if (RETURN_ERROR != CheckEsbOrderBetweenTwoPoints(trainMaHeadLink,trainMaTailLink,
                    trainDir,&esbNum,esbIdBuff))
                {
                    for (cycle = DEFAULT_ZERO;cycle < esbNum;cycle++)
                    {
                        obsOfMaStruBuff[obsNum].ObsId = esbIdBuff[cycle];
                        obsOfMaStruBuff[obsNum].ObsType = OBS_TYPE_ESB;
                        /*��дesb��״̬��Ϣ*/
                        obsOfMaStruBuff[obsNum].ObsStatus = GetEsbStatus(esbIdBuff[cycle]);
                        obsOfMaStruBuff[obsNum].ObsLockStatus =GetEsbStatus(esbIdBuff[cycle]);
                        obsNum++;
                    }

                    /*��д�ƶ���Ȩ��Χ�ڵ��ϰ�����Ϣ*/
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
        /* ����MA�������Link�Ͳ���MA�յ�����Link����1��ʧ�� */
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B36\n",trainId);
    }

}

/*
* �������ƣ� CalculateTsrInfoBelongToMaArea
* ���������� �����ƶ���Ȩ��Χ�ڵ���ʱ������Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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

    /*��ʼ��*/
    MemorySet(&tsrOfMaStruBuff[0],((UINT32_S)(sizeof(TsrOfMAStruct) * MA_AREA_TSR_SUM_MAX)),
        0U,((UINT32_S)(sizeof(TsrOfMAStruct) * MA_AREA_TSR_SUM_MAX)));
    MemorySet(&sectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TSR_SECTION_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TSR_SECTION_SUM_MAX)));
    MemorySet(&superArea[DEFAULT_ZERO],((UINT32_S)(sizeof(AreaInfoStruct)*5U)),
        DEFAULT_ZERO,((UINT32_S)(sizeof(AreaInfoStruct)*5U)));
    MemorySet(&maArea,((UINT32_S)(sizeof(AreaInfoStruct))),DEFAULT_ZERO,((UINT32_S)(sizeof(AreaInfoStruct))));

    /*��ȡ��ʱ��������*/
    trainDir = GetTrainUnsafeDirection(trainId);
    maArea.startSegId = GetMaHeadLink(trainId);
    maArea.startSegOffSet = GetMaHeadOffset(trainId);
    maArea.endSegId = GetMaTailLink(trainId);
    maArea.endSegOffSet = GetMaTailOffset(trainId);

    /*��ȡ��ʱ������Ϣ*/
    for (cycle = DEFAULT_ZERO;cycle < GetTsrOfZcSum();cycle++)
    {
        tsrZcId = GeTsrOfBelongZcId((UINT16_S)cycle);
        signalZcTsrNum = GetZcIdOfTsrNum(tsrZcId);

        for (cycleSignal = DEFAULT_ZERO;cycleSignal < signalZcTsrNum;cycleSignal++)
        {
            /*��ȡ��ʱ���ٰ������߼�������Ϣ*/
            sectionNum = GetSingleTsrDataOfSectionNum(tsrZcId,((UINT16_S)cycleSignal));
            rtnOfSectionId = GetSingleTsrDataOfSectionBuff(tsrZcId,((UINT16_S)cycleSignal),((UINT8_S)(SINGLE_TSR_SECTION_SUM_MAX)),sectionIdBuff);
            tsrSpeed = (UINT16_S)GetSingleTsrDataOfSpeed(tsrZcId,(UINT16_S)cycleSignal);

            if ((0U < sectionNum) && (RETURN_SUCCESS == rtnOfSectionId) && (0U != tsrSpeed))
            {
                /*��ʼ��*/
                superAreaNum = DEFAULT_ZERO;
                MemorySet(&superArea[0],((UINT32_S)(sizeof(AreaInfoStruct)*5U)),DEFAULT_ZERO,((UINT32_S)(sizeof(AreaInfoStruct)*5U)));

                /*��ѯ����������غ�����*/
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
            /*��д�ƶ���Ȩ��Χ�ڵ���ʱ������Ϣ*/
            SetMaTsrNum(trainId,tsrOfMaNum);
            SetTsrOfMAStru(trainId,tsrOfMaStruBuff,tsrOfMaNum);
        } 
        else
        {
            /*������*/
        }
    }
}

/*
* �������ƣ� JudgeReverseStateMaInfo
* ���������� �����۷�״̬�µ��ƶ���Ȩ��Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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

    /*��ȡ�г�ƥ��Ľ�·��Ϣ*/
    if (RETURN_SUCCESS == GetTrainMatchedRouteIdBuff(trainId,routeIdBuff))
    {
        /*�ж��г��Ƿ�ƥ���·*/
        if (DEFAULT_ZERO != routeIdBuff[DEFAULT_ZERO])
        {
            CalculateTrainMa(trainId);
        } 
        else
        {
            /*�ж��г��Ƿ�λ���۷���*/
            if (RETURN_SUCCESS == GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru))
            {
                trainUnSafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);
                trainDir = GetTrainUnsafeDirection(trainId);

                /*��ȡ�ǰ�ȫ��ͷλ�ö��ڵļ��������Ƿ�����ĳ�������·*/
                acBelock = GetAcBelock(trainUnSafeHeadAc);
                checkFlag = CheckPointBelongReverseArea(trainUnSafeLocStru.TrainHeadLink);

                if ((trainUnSafeLocStru.TrainHeadLink == trainUnSafeLocStru.TrainTailLink)
                    && (RETURN_SUCCESS == checkFlag)
                    && (AC_LOCK_STATUS == acBelock))
                {
                    /*�ж�λ���۷�����г��Ƿ�λ��ĳ���۷���·(������������ͬ��ѯ)*/
                    if (2U == CalulateAcIdBelongUseableRoute(trainUnSafeHeadAc,trainDir,&routeId))
                    {
                        /*�г���ǰ���з����ѯ��·�ɹ�*/
                    } 
                    else
                    {
                        /*�г���ʱ�ѻ���,�����г���ǰ���з����෴�����ѯ��·*/
                        if (2U == CalulateAcIdBelongUseableRoute(trainUnSafeHeadAc,TrainDirChangeForCheck(trainId),&routeId))
                        {
                            /*��ȡ��·Id*/
                        } 
                        else
                        {
                            /*������*/
                        }
                    }

                    /*��ȡ��·����*/
                    if ((LINE_REVERSE_ROUTE == GetRouteType(routeId))
                        && (trainDir != GetSignalProtectDir(GetRouteOfSingalId(routeId))))
                    {
                        /*�����۷�״̬�µ��ƶ���Ȩ��Ϣ*/
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
* �������ƣ� CalculaReverseStateMaInfo
* ���������� �����۷�λ�õ��ƶ���Ȩ��Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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

    /*��ȡ�г���Ϣ*/
    trainUnSafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);
    trainDir = GetTrainUnsafeDirection(trainId);
    checkFlag = CheckAcTerminalPosition(trainUnSafeHeadAc,((UINT16_S)trainDir),&acOfLink,&acOfOffset);
    getFlag = GetTrainSafeLoc(trainId,&trainSafeLocStru);

    if ((RETURN_SUCCESS == checkFlag)
        && (RETURN_SUCCESS == getFlag))
    {
        /*���MA��Ϣ*/
        ClearSingleTrainMaInfo(trainId);

        /*����MA����λ��*/
        SetMaStatusTrainId(trainId);
        SetMaType(trainId,NORMAL_MA_TYPE);

        /*��дMA��Ϣ*/
        SetMaHeadLink(trainId,trainSafeLocStru.TrainTailLink);
        SetMaHeadOffset(trainId,trainSafeLocStru.TrainTailOffset);
        SetMaHeadDir(trainId,trainDir);
        SetMaTailLink(trainId,acOfLink);
        SetMaTailOffset(trainId,acOfOffset);
        SetMaTailDir(trainId,trainDir);

        /* pbw 2017.8.2 ���Ӷ�MA�յ��ⷽ�������ε��ж� */
        rtnCheckLink = CalculatePointOfInsideLink(trainDir,acOfLink,acOfOffset,&checkLinkId);

        if (1U == rtnCheckLink)
        {
            maEndAcId = CheckPositionBelongAc(checkLinkId);	

            if (DEFAULT_ZERO != maEndAcId)
            {
                /*��ѯ��ǰ����ǰ����������*/
                if (RETURN_SUCCESS == CheckFrontACStatus(maEndAcId,trainDir,&frontAcId))
                {
                    if (AC_FREE_STATUS == GetAcStatusNow(frontAcId))
                    {
                        /*������*/
                    } 
                    else
                    {
                        /*����ǰ��������Ϣ�����ƶ���Ȩ*/
                        JudgeTrainMaByAcOfFrontAcInfo(FLAG_UNSET,trainId,maEndAcId,frontAcId);
                    }
                } 
                else
                {
                    /*��ѯǰ������ʧ��,������*/
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
            /* ��ѯMA�յ��ڷ���Linkʧ��,������ */
        }   

        if (DEFAULT_ZERO != GetMaTailLink(trainId))
        {
            /*��дMa�յ�����Ϊ����*/
            SetMaEndAttribute(trainId,MA_END_ATT_OTHER);

            /*�����ƶ���Ȩ�Ƿ���Ҫ����*/
            CalculatAdjustMaEndInfo(trainId);
        } 
        else
        {
            /*������*/
        }

        /*�����ƶ���Ȩ��Χ�ڵ��ϰ�����Ϣ*/
        if (DEFAULT_ZERO != GetMaTailLink(trainId))
        {
            CalculateObsInfoBelongToMaArea(trainId);
        }

        /*�����ƶ���Ȩ��Χ�ڵ���ʱ������Ϣ*/
        if (DEFAULT_ZERO != GetMaTailLink(trainId))
        {
            CalculateTsrInfoBelongToMaArea(trainId);
        }
    } 
    else
    {
        /*������*/
    }
}

/*
* �������ƣ� JudgeCancellationStateMaInfo
* ���������� ����ע��״̬�µ��ƶ���Ȩ��Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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

        /* �жϸ���������������Ƿ�Ϊ�˳�CBTC����ȷ�� */
        if (OUT_TRAIN_TOEXITCBTC == trainOutType)
        {
            /* ��дΪע��״̬�µ��ƶ���Ȩ���� */
            SetMaType(trainId,CANCELLATION_MA_TYPE);

            /* PBW,2016.7.10 Ϊ����ATP������ҪMA�յ����� */
            /* ����MA�յ�Ϊ�˳�CBTC���� */
            SetMaEndAttribute(trainId,MA_END_ATT_CBTC);

            SetMaHeadLink(trainId,trainUnSafeLocStru.TrainTailLink);
            SetMaHeadOffset(trainId,trainUnSafeLocStru.TrainTailOffset);
            SetMaHeadDir(trainId,trainDir);

            /* ά����һ���ڵ�MA�յ� */
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
            /*���MA��Ϣ*/
            ClearSingleTrainMaInfo(trainId);

            /*����MA����λ��*/
            /*PBW,2016.7.10 û�б�Ҫ,��ΪClearSingleTrainMaInfo����ֻ�ǰ�MA������ȫ��Ϊ0 */
            SetMaStatusTrainId(trainId);       

            /*��дΪע��״̬�µ��ƶ���Ȩ����*/
            SetMaType(trainId,CANCELLATION_MA_TYPE);	

            /*�Գ�ͷ��βΪע��״̬���ƶ���Ȩ*/
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
* �������ƣ� CalculatAdjustMaEndInfo
* ���������� �����Ƿ���Ҫ�����ƶ���Ȩ�յ㲢�����ƶ���Ȩ�յ�
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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

    /*��ѯ�ƶ���Ȩ�յ���ǰ��ȫ���������λ��*/
    maEndLink = GetMaTailLink(trainId);
    maEndOffset = GetMaTailOffset(trainId);
    trainDir = GetTrainUnsafeDirection(trainId);
    lineMaBackDistance = (UINT32_S)GetLineMaBackDistance();

    if (RETURN_SUCCESS == CheckPointReclosingAtQuitCbtc(maEndLink,maEndOffset))
    {
        /*�յ�Ϊ�˳�CBTC�յ�,��Ҫ�س��ƶ���Ȩ*/
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
                            /*�ж��г���ȫ��β�Ƿ�λ�ڰ�ȫ����λ�õ��ƶ���Ȩ�յ�֮��*/
                            if (RETURN_SUCCESS == CheckPointBelongToArea(maEndLink,maEndOffset,safeProtectLink,safeProtectOffset,
                                trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,trainDir))
                            {
                                /* MA�յ��MA�յ����г����з���ǰ�ư�ȫ�������������������İ�ȫ��β,��Ҫ�س��ƶ���Ȩ */
                                safeProtectFlag = FLAG_SET;
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
            } 
            else
            {
                /*����Ҫ����*/
            }
        }
    }

    if (FLAG_SET == safeProtectFlag)
    {
        /*��ѯ�س���*/
        checkRtn = CheckNextPointOnDistance(maEndLink,maEndOffset,TrainDirChangeForCheck(trainId),
            lineMaBackDistance,&backLink,&backOffset,&errorSwitchId);

        if (0x03U == checkRtn)
        {
            /*���»س����ƶ���Ȩ*/
            SetMaTailLink(trainId,backLink);
            SetMaTailOffset(trainId,backOffset);
        } 
        else
        {
            /*ά�ֵ�ǰ*/
        }
    }
    else
    {
        /*ά�ֵ�ǰ*/
    }
}

/*
* �������ƣ� CalculateMaEndAttribute
* ���������� �����ƶ���Ȩ�յ�������Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
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

    /*��ȡ�г�ƥ��Ľ�·��Ϣ*/
    rtnGetLastRoute = GetTrainMatchedLastRouteId(trainId,&lastMatchRouteId);

    if ((RETURN_SUCCESS == rtnGetLastRoute) && (DEFAULT_ZERO != lastMatchRouteId))
    {
        maTailLink = GetMaTailLink(trainId);
        maTailOffset = GetMaTailOffset(trainId);

        if (LINE_REVERSE_ROUTE == GetRouteType(lastMatchRouteId))
        {
            /*��ȡ��·���һ����������*/
            routeOfAcNum = GetRouteOfAcNum(lastMatchRouteId);
            getFlag = GetRoutOfAcIdBuff(lastMatchRouteId,ROUTE_OF_AC_SUM_MAX,routeOfAcIdBuff);

            if ((routeOfAcNum > DEFAULT_ZERO) && (RETURN_SUCCESS == getFlag))
            {
                /*��ȡ���һ�����������յ�λ��*/
                trainDir = (UINT16_S)GetTrainUnsafeDirection(trainId);

                /*�ж�MA�յ����۷���ʼ�˵�λ�ù�ϵ��ȷ��MA�յ������*/
                if (1U == CheckAcTopPosition(routeOfAcIdBuff[routeOfAcNum - 1u],trainDir,&acToplLink,&acTopOffset))
                {
                    /*�ж�MA�յ���ʼ�˵��λ�ù�ϵ*/
                    checkRtn = CheckLocRelationBetweenTwoPoints(maTailLink,maTailOffset,acToplLink,acTopOffset,((UINT8_S)trainDir));

                    switch (checkRtn)
                    {
                    case 0U:
                        /*��ѯʧ��,�г������ƶ�*/
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-B44\n",trainId);
                        break;
                    case 1U:
                        /*��ǰ�ƶ���Ȩλ�ø�Զ,����Ϊ�۷���·�ն�����*/
                        SetMaEndAttribute(trainId,MA_END_ATT_REVERT);
                        break;
                    case 2U:
                    case 3U:
                        /*��ǰ�۷���·ʼ�˵��Զ�����غ�,����Ϊ�����ն�����*/
                        SetMaEndAttribute(trainId,MA_END_ATT_OTHER);
                        break;
                    default:
                        /*��ѯʧ��,�г������ƶ�*/
                        SetTrainToModeToRM0(trainId);
                        LogPrintf(1u,"%d-B45\n",trainId);
                        break;
                    }
                }
                else
                {
                    /*��ѯʧ��,�޷���ȡ��̬����,�г������ƶ�*/
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
                /*��ѯʧ��,�޷���ȡ��̬����,�г������ƶ�*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B47\n",trainId);
            }
        } 
        else
        {
            /*��ȡ�г�����*/
            trainDir =  GetTrainUnsafeDirection(trainId);

            /*��ѯ�ƶ���Ȩ�յ��Ƿ��ĳ���˳�CBTC�������غ�*/
            checkQuitCbtcRtn = CheckPointQuitCbtcIsFindPoint(maTailLink,maTailOffset,((UINT8_S)trainDir));

            switch (checkQuitCbtcRtn)
            {
            case 0u:
                /*��ѯʧ��,�޷���ȡ��̬����,�г������ƶ�*/
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
                /*��ѯʧ��,�޷���ȡ��̬����,�г������ƶ�*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B49\n",trainId);
                break;
            }
        }
    } 
    else
    {
        /*��ѯʧ��,�޷���ȡ��̬����,�г������ƶ�*/
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B50\n",trainId);
    }
}

/*
* �������ƣ� MixObsOfMa
* ���������� ����ƶ���Ȩ��Ϣ�е��ϰ�����Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� ObsOfMAStruct mixObsBuff[],����ϰ�����Ϣ
* ����ֵ  �� RETURN_UINT8_MAX_VALUE:ʧ��
*            [0,RETURN_UINT8_MAX_VALUE):�ϰ�������
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
    UINT16_S belongZcId = DEFAULT_0XFF;  /* �ϰ���������ZC��� */

    /*��ʼ������ṹ������*/
    MemorySet(&obs1StruBuff[0],((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))),
        0U,((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))));
    MemorySet(&obs2StruBuff[0],((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))),
        0U,((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))));

    /*��ȡMA1���ϰ�����Ϣ*/
    obsNum1 = GetMaObsNum(trainId);
    getObs1Value = GetObsOfMAStru(trainId,MA_AREA_OBS_SUM_MAX,obs1StruBuff);

    /*��ȡMA2���ϰ�����Ϣ*/
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

        /* ��ȡ����ZC��ID */
        localZcId = GetLocalZcId();

        /*����MA1�е��ϰ����ȡ�����ƽ�ZC���ϰ���*/
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
                /*�����Ϻ��ϰ���*/
                mixObsBuff[mixNum].ObsId = obsId;
                mixObsBuff[mixNum].ObsType = obsType;
                mixObsBuff[mixNum].ObsStatus = status;
                mixObsBuff[mixNum].ObsLockStatus = lockStatus;
                mixNum++;
            }
            else
            {
                /*������*/
            }
        } 

        /*����MA2�е��ϰ����ȡ���ڽӹ�ZC���ϰ���*/
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
                /*�����Ϻ��ϰ���*/
                mixObsBuff[mixNum].ObsId = obsId;
                mixObsBuff[mixNum].ObsType = obsType;
                mixObsBuff[mixNum].ObsStatus = status;
                mixObsBuff[mixNum].ObsLockStatus = lockStatus;
                mixNum++;
            }
            else
            {
                /*������*/
            }
        }

        rtnValue = mixNum;
    }

    return rtnValue;
}

/*
* �������ƣ� MixTsrOfMa
* ���������� ����ƶ���Ȩ��Ϣ�е���ʱ������Ϣ
* ��������� const UINT16_S trainId,�г�Id
* ��������� TsrOfMAStruct mixTsrBuff[],�����Ϻ����ʱ����
* ����ֵ  �� RETURN_UINT8_MAX_VALUE:ʧ��
*            [0,RETURN_UINT8_MAX_VALUE):��ʱ��������
*/
UINT8_S MixTsrOfMa(const UINT16_S trainId,TsrOfMAStruct mixTsrBuff[])
{
    UINT8_S cycle1 = 0U;
    UINT8_S cycle2 = 0U;
    UINT8_S tsrNum1 = 0U;
    UINT8_S tsrNum2 = 0U;
    UINT8_S getTsr2Value = 0U;
    UINT8_S getTsr1Value = 0U;
    UINT16_S belongZcId = 0U;  /*��ʱ���ٶ�Ӧ������ZCID*/
    UINT8_S rtnValue = 0U;
    UINT8_S mixNum = 0U;
    TsrOfMAStruct tsr1StruBuff[MA_AREA_TSR_SUM_MAX];
    TsrOfMAStruct tsr2StruBuff[MA_AREA_TSR_SUM_MAX];

    /*��ʼ������ṹ������*/
    MemorySet(&tsr2StruBuff[0],((UINT32_S)(MA_AREA_TSR_SUM_MAX*sizeof(TsrOfMAStruct))),
        0U,((UINT32_S)(MA_AREA_TSR_SUM_MAX*sizeof(TsrOfMAStruct))));
    MemorySet(&tsr1StruBuff[0],((UINT32_S)(MA_AREA_TSR_SUM_MAX*sizeof(TsrOfMAStruct))),
        0U,((UINT32_S)(MA_AREA_TSR_SUM_MAX*sizeof(TsrOfMAStruct))));

    /*��ȡMA1��TSR��Ϣ*/
    tsrNum1 = GetMaTsrNum(trainId);
    getTsr1Value = GetTsrOfMAStru(trainId,MA_AREA_TSR_SUM_MAX,tsr1StruBuff);

    /*��ȡMA2��TSR��Ϣ*/
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

        /*����MA1�е�TSR����ȡ�����ƽ�ZC��TSR*/
        for (cycle1 = 0U;cycle1 < tsrNum1;cycle1++)
        {
            belongZcId = tsr1StruBuff[cycle1].BelongZcId;

            if (GetLocalZcId() == belongZcId)
            {
                /*�������ZCΪ��ZC����д���Ϻ�TSR��*/
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
                /*����Ѿ����������ڽӹ�ZC��TSR������*/
                break;
            }
        }

        /*����MA2�е�TSR����ȡ���ڽӹ�ZC��TSR*/
        for (cycle2=0U;cycle2 < tsrNum2;cycle2++)
        {
            belongZcId = tsr2StruBuff[cycle2].BelongZcId;

            if (GetNextZcId(trainId) == belongZcId)
            {
                /*�������ZCΪ�ӹ�ZC����д���Ϻ�TSR��*/
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
                /*��������*/
            }
        }

        rtnValue = mixNum;

    }

    return rtnValue;
}

/*
* �������ƣ� SingleTrainHandMixMA
* ���������� �����г�����ƶ���Ȩ���л��г���
* ��������� const UINT16_S trainId,�г�Id
* ��������� ��
* ����ֵ  �� ��
*/
void SingleTrainHandMixMA(const UINT16_S trainId)
{
    UINT8_S ma2InfoFlag = 0U;       /*MA2���ڱ�־*/
    UINT8_S ma2Length = 0U;         /*MA2����*/
    MaDataStruct mixedMaStru;       /*��Ϻ�MA�ṹ��*/
    ObsOfMAStruct mixedObsBuff[MA_AREA_OBS_SUM_MAX];  /*��Ϻ��ϰ���*/
    UINT8_S mixedObsNum = 0U;  /*��Ϻ��ϰ�������*/
    TsrOfMAStruct mixedTsrBuff[MA_AREA_TSR_SUM_MAX];  /*��Ϻ���ʱ����*/
    UINT8_S mixedTsrNum = 0U;  /*��Ϻ���ʱ��������*/
    UINT16_S ma1HeadLink = 0U;
    UINT32_S ma1HeadOffset = 0U;
    UINT8_S ma1HeadDir = 0U;
    UINT16_S ma2TailLink = 0U;
    UINT32_S ma2TailOffset = 0U;
    UINT8_S ma2TailDir = 0U;
    UINT8_S ma2EndAttribute = 0U;
    UINT8_S obsCycle = 0U;
    UINT8_S tsrCycle = 0U;

    /*��ʼ��*/
    MemorySet(&mixedMaStru,((UINT32_S)(sizeof(MaDataStruct))),0U,((UINT32_S)(sizeof(MaDataStruct))));
    MemorySet(&mixedObsBuff[0],((UINT32_S)(sizeof(ObsOfMAStruct) * MA_AREA_OBS_SUM_MAX)),
        0U,((UINT32_S)(sizeof(ObsOfMAStruct) * MA_AREA_OBS_SUM_MAX)));
    MemorySet(&mixedTsrBuff[0],((UINT32_S)(sizeof(TsrOfMAStruct) * MA_AREA_TSR_SUM_MAX)),
        0U,((UINT32_S)(sizeof(TsrOfMAStruct) * MA_AREA_TSR_SUM_MAX)));

    /*��ȡMA1�Ĳ���״̬*/
    ma1HeadLink = GetMaHeadLink(trainId);
    ma1HeadOffset = GetMaHeadOffset(trainId);
    ma1HeadDir = GetMaHeadDir(trainId);

    /*��ȡMA2�Ĳ���״̬*/
    ma2InfoFlag = GetNextZcMaInfoFlag(trainId);
    ma2Length = GetNextZcMaStatusMaLength(trainId);
    ma2TailLink = GetNextZcMaTailLink(trainId);
    ma2TailOffset = GetNextZcMaTailOffset(trainId);
    ma2TailDir = GetNextZcMaTailDir(trainId);
    ma2EndAttribute = GetNextZcMaEndAttribute(trainId);


    /*��MA2��״̬�����ж�*/
    if ((RETURN_UINT8_MAX_VALUE == ma2InfoFlag)	|| (RETURN_UINT8_MAX_VALUE == ma2Length) 
        || (RETURN_UINT16_MAX_VALUE == ma2TailLink) || (RETURN_UINT32_MAX_VALUE == ma2TailOffset) 
        || (RETURN_UINT8_MAX_VALUE == ma2TailDir) || (RETURN_UINT8_MAX_VALUE == ma2EndAttribute))
    {
        /*��ȡ����ʧ�ܣ�����Ϻ�MA��Ϊ��MA*/
        SetTrainToModeToRM0(trainId); 
        LogPrintf(1u,"%d-B51\n",trainId);
    }
    else if ((RETURN_UINT16_MAX_VALUE == ma1HeadLink) || (RETURN_UINT32_MAX_VALUE == ma1HeadOffset) 
        || (RETURN_UINT8_MAX_VALUE == ma1HeadDir))
    {
        /*��ȡ����ʧ�ܣ�����Ϻ�MA��Ϊ��MA*/
        SetTrainToModeToRM0(trainId);
        LogPrintf(1u,"%d-B52\n",trainId);
    }
    else
    {
        if (NO_MA_TYPE == ma2InfoFlag)
        {
            /*MA2������,�ƽ�ZC����MA1��Ϊ��Ϻ�MA*/
        }
        else if (ABNORMAL_MA_TYPE == ma2InfoFlag)
        {
            /*MA2Ϊ��MA������MA2δԽ���л���,��Ϊ�쳣,����Ϻ�MA��Ϊ��MA*/
            SetTrainToModeToRM0(trainId);
            LogPrintf(1u,"%d-B53\n",trainId);
        }
        else
        {
            /*�����������MA,����ϰ���*/
            mixedObsNum = MixObsOfMa(trainId,mixedObsBuff);

            /*�����ʱ����*/
            mixedTsrNum = MixTsrOfMa(trainId,mixedTsrBuff);

            if ((RETURN_UINT8_MAX_VALUE == mixedObsNum) || (RETURN_UINT8_MAX_VALUE == mixedTsrNum))
            {
                /*���ݴ��󣬽���Ϻ�MA��Ϊ��MA*/
                SetTrainToModeToRM0(trainId);
                LogPrintf(1u,"%d-B54\n",trainId);
            }
            else
            {
                /*��Ϻ�MA*/
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

                /*����Ϻ�MAд��ȫ��������*/
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
* �������ƣ� CalPointIsOnOverlap
* ���������� ����1���Ƿ�λ�ڱ���������
* ��������� const UINT16_S segId, seg���
*          const UINT32_S offset,segƫ����
*          const UINT8_S dir,����
* ��������� UINT16_S *OutOverlapId,�������α��
* ����ֵ  �� 0:ʧ��
*          1��λ�ڱ��������ڲ�(�������˵�)
*          2: λ�������з��򱣻��������
*          3: λ�������з��򱣻������յ�
*/
UINT8_S CalPointIsOnOverlap(const UINT16_S segId,const UINT32_S offset,const UINT8_S dir,UINT16_S *OutOverlapId)
{
    UINT16_S outSegId = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT16_S overlapSum = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S overlapId = DEFAULT_ZERO;
    UINT8_S acSumOfOverlap = DEFAULT_ZERO;   /* �������ΰ����ļ����������� */
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
        /* ����˵��ڷ������������� */
        if (1u == CalculatePointOfInsideLink(dir,segId,offset,&outSegId))
        {
            acId = CheckPositionBelongAc(outSegId);
            overlapSum = GetOverlapSum();

            /* ������Ͻ��Χ�����б������� */
            for (i = DEFAULT_ZERO;i < overlapSum;i++)
            {
                overlapId = GetOverlapId(i);           
                acSumOfOverlap = GetOverlapContainAcNum(overlapId);
                getFlag = GetOverlapContainAcBuff(overlapId,OVERLAP_OF_AC_SUM_MAX,overlapAcIdBuff);

                /* �����������ΰ��������м������� */
                for (j = DEFAULT_ZERO;j < acSumOfOverlap;j++)
                {
                    if (acId == overlapAcIdBuff[j])
                    {
                        if (FLAG_SET == GetOverlapSwitchAttribute(overlapId))
                        {
                            /* �������ΰ������� */
                            if (1u == CalulateSwtichStateOfOverlapIsNeed(overlapId))
                            {
                                *OutOverlapId = overlapId;
                            }
                            else
                            {
                                /* ����������������Ҫ�󣬼�������*/
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
                        /* ���� */
                        startIndex = 0u;
                        endIndex = acSumOfOverlap - 1u;
                    }
                    else 
                    {
                        /* ���� */
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
