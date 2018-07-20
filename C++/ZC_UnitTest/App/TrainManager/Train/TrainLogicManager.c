/********************************************************                                                                                                            
 �� �� ���� TrainStatusData.c   
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015-07-05
 ������ �г��߼����� 
 ��ע�� ��  
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
  ������:      SetTrainToModeToRM0
  ��������:    �г���������
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void SetTrainToModeToRM0(const UINT16_S trainId)
{
    /*��ȡ�г�����*/
    switch (GetTrainType(trainId))
    {
    case TRAIN_MODE_CBTC:
        /*�����ƶ���ȨΪ��MA*/
        ClearSingleTrainMaInfo(trainId);

        /*����MA����λ��*/
        SetMaStatusTrainId(trainId);

        SetMaType(trainId,ABNORMAL_MA_TYPE);

        /*�����г�����*/
        SetTrainType(trainId,TRAIN_MODE_TO_RM0);
        break;
    case TRAIN_MODE_TO_RM0:
        /*�����ƶ���ȨΪ��MA*/
        SetMaType(trainId,ABNORMAL_MA_TYPE);
        break;
    default:
        /*����ƶ���Ȩ���*/
        SetMaType(trainId,DEFAULT_ZERO);
        break;
    }	
}

/*************************************************
  ������:      TrainDirChangeForCheck
  ��������:    ת���г��������ڷ����ѯ
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      ת��ֵ 
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
  ������:      JudgeTrainNeedCalculate
  ��������:    �ж��г��Ƿ���Ҫ������Ӧ�ļ���
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      1U:��Ҫ
               0U:����Ҫ
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

    /* pbw 2017.8.2 ���н������ܿ� */
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
  ������:      CalculateTrainSafePos
  ��������:    �����г���ȫλ��
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void CalculateTrainSafePos(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT8_S needCalculateFlag = RETURN_ERROR;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        /*��ȡ�г�ID*/
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);
        needCalculateFlag = JudgeTrainNeedCalculate(trainId);

        if ((DEFAULT_ZERO != trainId)
            && (TRAIN_MODE_OUT != trainType)
            && (DEFAULT_ZERO != trainType)
            && (RETURN_SUCCESS == needCalculateFlag))
        {
            /*�����г���ȫ��ͷλ��*/
            CalculateTrainHeadSafePos(trainId);

            /*�����г���ȫ��βλ��*/
            CalculateTrainTailSafePos(trainId);
        } 
        else
        {
            /*������*/
        }
    }
}

/*************************************************
  ������:      CalculateTrainHeadSafePos
  ��������:    �����г���ȫ��ͷλ��
  ����:        const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      ��
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
    UINT16_S endAcOfLine = DEFAULT_ZERO;    /* ��·��ͷ�ļ������� */

	MemorySet(&trainUnsafeLocStru,(UINT32_S)(sizeof(TrainSafeLocStruct)),DEFAULT_ZERO,(UINT32_S)(sizeof(TrainSafeLocStruct)));
    MemorySet(&trainSafeLocStru,(UINT32_S)(sizeof(TrainSafeLocStruct)),DEFAULT_ZERO,(UINT32_S)(sizeof(TrainSafeLocStruct)));
	
    /*���㰲ȫλ����Ҫ�ľ���*/
    headDistance = CalculateTrainHeadDistance(trainId);

    /*��ȡ�г���Ϣ*/
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
			/* ������ */
		}

        switch (rtnOfCheck)
        {
        case 0U:
            /*��ѯʧ��*/
            SetTrainToModeToRM0(trainId);
            SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);
			LogPrintf(1u,"%d-B55\n",trainId);
            break;
        case 1U:
            /*������·��ͷ�����²�ѯʧ��*/
            /* pbw 2017.5.23 ʹ����·��ͷ���ļ������� */
            if (DEFAULT_ZERO != endAcOfLine)
            {
                if (RETURN_SUCCESS == CheckAcTerminalPosition(endAcOfLine,((UINT16_S)trainDir),&acBelongLink,&acBelongOffset))
                {
                    SetTrainSafeHeadLoc(trainId,acBelongLink,acBelongOffset);
                } 
                else
                {
                    /*��ѯʧ��*/
                    SetTrainToModeToRM0(trainId);
					
                    SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);

                    LogPrintf(1u,"%d-B56\n",trainId);
                }
            } 
            else
            {
                /*��ѯʧ��*/
                SetTrainToModeToRM0(trainId);
				
                SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);

                LogPrintf(1u,"%d-B57\n",trainId);
            }
            break;
        case 2U:
            /*���ڵ���ԭ���²�ѯʧ��*/
			for (switchCycle = 0u; switchCycle < switchNum; switchCycle++)
			{
				occStatus = JudgeSwitchBelongAcOccStatus(errorAcOfSwitchId[switchCycle]);

				if ((DEFAULT_ZERO != errorAcOfSwitchId[switchCycle])
					&& (RETURN_SUCCESS == occStatus))
				{
					/*��ѯ�г���ͷ���ڼ�������*/
					trainHeadAc = CheckPositionBelongAc(trainUnsafeLocStru.TrainHeadLink);

					if (RETURN_SUCCESS == CheckAcTerminalPosition(trainHeadAc,((UINT16_S)trainDir),&acBelongLink,&acBelongOffset))
					{
						SetTrainSafeHeadLoc(trainId,acBelongLink,acBelongOffset);
					} 
					else
					{
						/* ��ѯʧ��,����ѭ�� */
						SetTrainToModeToRM0(trainId);
						
						SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);

                        LogPrintf(1u,"%d-B58\n",trainId);

                        break;
					}
				} 
				else
				{
					/* ��ѯʧ��,����ѭ�� */
					SetTrainToModeToRM0(trainId);
					
					SetTrainSafeHeadLoc(trainId,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset);

                    LogPrintf(1u,"%d-B59\n",trainId);

                    break;
				}
			}
           
            break;
        case 3U:
            /*��ѯ�ɹ�*/
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
        /*������*/
    }

}

/*************************************************
  ������:      CalculateTrainTailSafePos
  ��������:    �����г���ȫ��βλ��
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      ��
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
    UINT16_S endAcOfLine = DEFAULT_ZERO;    /* ��·��ͷ�ļ������� */

	MemorySet(&trainUnsafeLocStru,(UINT32_S)(sizeof(TrainSafeLocStruct)),DEFAULT_ZERO,(UINT32_S)(sizeof(TrainSafeLocStruct)));
    MemorySet(&trainSafeLocStru,(UINT32_S)(sizeof(TrainSafeLocStruct)),DEFAULT_ZERO,(UINT32_S)(sizeof(TrainSafeLocStruct)));
	
    /*���㰲ȫ��βλ����Ҫ�ľ���*/
    tailDistance = CalculateTrainTailDistance(trainId);

    /*��ȡ�г���Ϣ*/
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
			/* ������ */
		}

        switch (rtnOfCheck)
        {
        case 0U:
            /*��ѯʧ��*/
            SetTrainToModeToRM0(trainId);
			
            SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

            LogPrintf(1u,"%d-B61\n",trainId);
            break;
        case 1U:
            /*������·��ͷ�����²�ѯʧ��*/
            /* pbw 2017.5.23 ʹ����·��ͷ���ļ������� */
            if (DEFAULT_ZERO != endAcOfLine)
            {
                if (RETURN_SUCCESS == CheckAcTopPosition(endAcOfLine,((UINT16_S)trainDir),&acBelongLink,&acBelongOffset))
                {
                    SetTrainSafeTailLoc(trainId,acBelongLink,acBelongOffset);
                } 
                else
                {
                    /*��ѯʧ��*/
                    SetTrainToModeToRM0(trainId);
					
                    SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

                    LogPrintf(1u,"%d-B62\n",trainId);
                }
            } 
            else
            {
                /*��ѯʧ��*/
                SetTrainToModeToRM0(trainId);
				
                SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

                LogPrintf(1u,"%d-B63\n",trainId);
            }
            break;
        case 2U:
            /*���ڵ���ԭ���²�ѯʧ��*/
			for (switchCycle = 0u; switchCycle < switchNum; switchCycle++)
			{
				occStatus = JudgeSwitchBelongAcOccStatus(errorAcOfSwitchId[switchCycle]);

				if ((DEFAULT_ZERO != errorAcOfSwitchId[switchCycle])
					&& (RETURN_SUCCESS == occStatus))
				{
					/*��ѯ�г���β���ڼ�������*/
					trainTailAc = CheckPositionBelongAc(trainUnsafeLocStru.TrainTailLink);

					if (RETURN_SUCCESS == CheckAcTopPosition(trainTailAc,((UINT16_S)(trainDir)),&acBelongLink,&acBelongOffset))
					{
						SetTrainSafeTailLoc(trainId,acBelongLink,acBelongOffset);
					} 
					else
					{
						/* ��ѯʧ��,����ѭ�� */
						SetTrainToModeToRM0(trainId);
						
						SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

                        LogPrintf(1u,"%d-B64\n",trainId);

                        break;
					}
				} 
				else
				{
					/* ��ѯʧ��,����ѭ�� */
					SetTrainToModeToRM0(trainId);
					
					SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

                    LogPrintf(1u,"%d-B65\n",trainId);

                    break;
				}
			}
            break;
        case 3U:
            /*��ѯ�ɹ�*/
            SetTrainSafeTailLoc(trainId,trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset);
            break;
        default:
            /*��ѯʧ��*/
            SetTrainToModeToRM0(trainId);
			
            SetTrainSafeTailLoc(trainId,trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

            LogPrintf(1u,"%d-B66\n",trainId);
            break;
        }
    } 
    else
    {
        /*������*/
    }
}

/*************************************************
  ������:      CalculateTrainHeadDistance
  ��������:    �����г���ȫ��ͷλ����Ҫ�ľ���
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      ����ֵ
*************************************************/
UINT32_S CalculateTrainHeadDistance(const UINT16_S trainId)
{
    UINT32_S headDistance = DEFAULT_ZERO;
    UINT32_S trainRedundancy = DEFAULT_ZERO;
    UINT16_S trainError = DEFAULT_ZERO;
    UINT16_S trainSpeed = DEFAULT_ZERO;
    UINT16_S configMaxTrainLen = DEFAULT_ZERO;
	UINT32_S commTargetCycle = DEFAULT_ZERO;  /* ͨѶ��ʱ������ */
	UINT32_S trainPrtclDelay = DEFAULT_ZERO;

    /*�����г������ӳ�ʱ��*/
	commTargetCycle = (UINT32_S)GetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId);
	trainPrtclDelay = (UINT32_S)GetTrainPrtclDelay(trainId);
	
    trainRedundancy = (UINT32_S)(((commTargetCycle + trainPrtclDelay) * 4U) / 10U);

    /*��ȡ�г���Ϣ*/
    trainError = GetTrainError(trainId);
    trainSpeed = GetTrainSpeed(trainId);

    if (RETURN_UINT16_MAX_VALUE == trainSpeed)
    {
        trainSpeed = GetLineMaxSpeed();
    } 
    else
    {
        /*������*/
    }

    /*�����г���ͷ�������*/
    headDistance = trainError + (UINT32_S)((trainSpeed * trainRedundancy) + ((GetMaxTrainTractionAcc(trainId) * (trainRedundancy * trainRedundancy)) / 2U));

    configMaxTrainLen = GetLineMaxTrainLength();

    /*�жϳ�ͷ��������Ƿ񳬹��������ֵ*/
    if(configMaxTrainLen <= headDistance)
    {
        /*����ͷ�����������Ϊ�������ֵ*/
        headDistance = configMaxTrainLen;
    }
    else
    {
        /*������*/
    }

    return headDistance;
}

/*************************************************
  ������:      CalculateTrainTailDistance
  ��������:    �����г���ȫ��βλ����Ҫ�ľ���
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      ����ֵ
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
        /*�г����ڷ�����״̬���������з�����ʵ�����з����෴*/
		retreatDistance = (UINT32_S)GetRetreatProtectDistance();
		
        tailDistance = trainError + retreatDistance;
    }
    else
    {
        /*���з�����ͬ��ֻ���ǲ�ȷ�������Ϣ*/
        tailDistance = trainError;
    }

    return tailDistance;
}

/*************************************************
  ������:      JudgeSwitchBelongAcOccStatus
  ��������:    �����г���ȫ��βλ����Ҫ�ľ���
  ����:        cosnt UINT16_S swtichId ����ID
  ���:        ��
  ����ֵ:      0u:ռ��
               1u:δռ��
*************************************************/
UINT8_S JudgeSwitchBelongAcOccStatus(const UINT16_S swtichId)
{
    UINT8_S switchBelongAcNum = DEFAULT_ZERO;
    UINT16_S switchBelongAcIdBuff[SWITCH_BELONG_AC_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;

    /*��ѯ�������ڵļ���������Ϣ*/
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
                /*������*/
            }
        }

        if (cycle == switchBelongAcNum)
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

/*************************************************
  ������:      CalculateTrainSafeLocAcOfSwitch
  ��������:    �����г���ȫλ�û�����Ҫ�ľ���ļ����ڵ�����߾�ͷ�����
  ����:        const UINT8_S flag,��־��Ϣ(1u:��ͷ��2u:��β)
               const UINT32_S distance,����ֵ
               const UINT8_S dir,����
  ���:        UINT16_S errorSwitchOrAcId[SIZE_MAX_SWITCH_MUM_OF_SAFE_TRAIN],���������˹�ϵ������
               UINT8_S * pSwitchOrAcNum,���������˹�ϵ���������
               UINT16_S *endAcOfLine,��ͷ�߼������α��
  ����ֵ:      0x03u��λ�ü���ɹ�
               0x02u��λ�ü���ʧ�ܣ�ԭ�����λ�ô���,errorSwitchOrAcIdΪ���������˹�ϵ������;pSwitchOrAcNumΪ���������˹�ϵ�����������
               0x01u��λ�ü���ʧ�ܣ�ԭ����·��ͷ,endAcOfLine,��ͷ�߼������α�ţ�
               0x00u��λ�ü���ʧ�ܣ�����ԭ��
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
        /*��ʼ���������*/
        (* pSwitchOrAcNum) = DEFAULT_ZERO;
        MemorySet(&trainUnsafeLocStru,(UINT32_S)(sizeof(TrainSafeLocStruct)),DEFAULT_ZERO,(UINT32_S)(sizeof(TrainSafeLocStruct)));
        (*endAcOfLine) = DEFAULT_ZERO;

        /*��ȡ�г���Ϣ*/
        tempRtn = GetTrainUnSafeLoc(trainId,&trainUnsafeLocStru);

        /*�ж��г�λ�����ڼ���*/
        if (1u == flag)
        {
            /*��ͷλ��*/
            locOfAcId = CheckPositionBelongAc(trainUnsafeLocStru.TrainHeadLink);
            checkDir = dir;

            /*��ѯ�����ն�λ��*/
            rtnOfLoc = CheckAcTerminalPosition(locOfAcId,(UINT16_S)dir,&pointLink,&pointOffset);
        } 
        else if (2u == flag)
        {
            /*��βλ��*/
            locOfAcId = CheckPositionBelongAc(trainUnsafeLocStru.TrainTailLink);
            checkDir = TrainDirChangeForCheck(trainId);

            /*��ѯ����ʼ��λ��*/
            rtnOfLoc = CheckAcTopPosition(locOfAcId,(UINT16_S)dir,&pointLink,&pointOffset);
        } 
        else
        {
            /*�������У��ʧ��*/
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
			/*������Ϊ�ɹ�״̬*/
			rtn = 3u;

			while (addtDis < distance)
			{
				/*��ȡ��ǰȷ���������һ����������*/
				checkRtn = CheckFrontACCanStatus(locOfAcId,checkDir,&frontAcNum,frontAcIdBuff);

				if ((RETURN_SUCCESS == checkRtn) || (3u == checkRtn))
				{
					for (cycleAc = DEFAULT_ZERO;cycleAc < frontAcNum;cycleAc++)
					{
						/*��ѯ�������ζ�Ӧ�ĵ�������*/
						rtnOfSwitch = JudgeSwitchPostionInAc(frontAcIdBuff[cycleAc],calErrorSwitchId,&calErrorSwitchNum);

						if (2u == rtnOfSwitch)
						{
							frontAcId = frontAcIdBuff[cycleAc];
							breakFlag = FLAG_SET;
						} 
						else
						{
							/*��¼�������*/
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
						/*�ۼӼ��᳤��*/
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
						/*��·��ͷ����ʧ��*/
						rtn = 1u;

                        /* pbw 2017.5.23 ���������·��ͷ���1���������� */                       
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
  ������:      ManageTrainDangerousSource
  ��������:    �����г�ǰ���ͺ�Σ��Դ��Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
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
			/*��ȡ�г�ID*/
			if (FLAG_SET == GetTrainSuspectHead(trainId))
			{
				/*�����г�ǰ��Σ��Դ��ǰ����������*/
				if (RETURN_SUCCESS == JudgeTrainHeadSuspect(trainId))
				{
					/*ȥ���г�ǰ��Σ��Դ���*/
					SetTrainSuspectHead(trainId,FLAG_UNSET);

					LogPrintf(1U,"1.01 remove train[%d] suspect head!\n",trainId);
				} 
				else
				{
					/*������*/
				}
			} 
			else
			{
				/*�ж��Ƿ���Ҫ�ڱ���������г�ǰ��Σ��Դ���*/
				trainType = GetTrainType(trainId);

				if (((TRAIN_MODE_CBTC != trainType) && (TRAIN_MODE_TO_RM0 != trainType)))
				{
					/*��ͷλ�ڱ�zc��Ͻ��Χ�ڵķ�CBTC�г��������ǰ��*/
					ManageAddTrainHeadSuspect(trainId);
				} 
				else
				{
					/*������*/
				}
			}
          
			if (FLAG_SET == GetTrainSuspectTail(trainId))
			{              
				/*�����г����Σ��Դ���󷽿�������*/
				if (RETURN_SUCCESS == JudgeTrainTailSuspect(trainId))
				{
					/*ȥ���г���Σ��Դ���*/
					SetTrainSuspectTail(trainId,FLAG_UNSET);

					LogPrintf(1U,"1.02 remove train[%d] suspect tail!\n",trainId);
				} 
				else
				{
					/*������*/
				}
			} 
			else
			{
				/*�ж��Ƿ���Ҫ�ڱ���������г���Σ��Դ���*/			
				ManageAddTrainTailSuspect(trainId);
			}
		} 
		else
		{
			/*������*/
		}
	}
}

/*************************************************
  ������:      ManageAddTrainHeadSuspect
  ��������:    �����г�ǰ��Σ��Դ��Ϣ���Ƿ�����Σ��Դ�����ǰ��Σ�������ǣ�
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      ��
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
            /*���ڱ������ڻ���λ�ڱ������һ��*/
            rtnFrontAc = CheckFrontACStatus(trainUnSafeHeadAcId,trainDir,&frontAcId);

            if (1U == rtnFrontAc)
            {
                acDir = CalculateTrainDirInOtherAc(FLAG_SET,trainUnSafeHeadAcId,frontAcId,trainDir);

                switch (acDir)
                {
                case AC_DIR_FARAWAY:

                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(frontAcId))
                    {
                        /*ǰ���������г�*/
                    } 
                    else
                    {
                        if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(frontAcId,(GetAcTrainOfAcNum(frontAcId) - 1U),&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectTail(trainIdInSeq))
                                {
                                    /*û�к�Σ������,����Ӻ�˿��ɱ��*/
                                } 
                                else
                                {
                                    /*���ǰ��Σ��������*/
                                    SetTrainSuspectHead(trainId,FLAG_SET);
                                    errorCode = 0x01U;
                                }
                            }
                            else
                            {
                                /*ǰ�����Ϊ���г�*/
                            }
                        }                        
                    }

                    break;
                case AC_DIR_CLOSED:

                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(frontAcId))
                    {
                        /*ǰ���������г�*/
                    } 
                    else
                    {
                        if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(frontAcId,0U,&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectHead(trainIdInSeq))
                                {
                                    /*û�к�Σ������,����Ӻ�˿��ɱ��*/
                                } 
                                else
                                {
                                    /*���ǰ��Σ��������*/
                                    SetTrainSuspectHead(trainId,FLAG_SET);
                                    errorCode = 0x02U;
                                }
                            } 
                            else
                            {
                                /*ǰ�����Ϊ���г�*/
                            }
                        }                                               
                    }

                    break;
                case DEFAULT_ZERO:
                    /*����ʧ��,ֱ�����ǰ��Σ��������*/
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
                        /*ǰ����Σ������,�����*/
                    } 
                    else
                    {
                        /*���ǰ��Σ��������*/
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
                    /*������·��ͷ��ѯʧ��,������*/
                } 
                else
                {
                    /*���ǰ��Σ��������*/
                    SetTrainSuspectHead(trainId,FLAG_SET);
                    errorCode = 0x05U;
                }
            }
        } 
        else
        {
            /*�г�λ�ڸü������ε��м�����,�鿴�г�ǰ���г����Ƿ����*/		
            if (GetTrainIdInTrainSequenceOfIndex(trainUnSafeHeadAcId,(trainSeqIndex-1U),&trainIdInSeq))
            {
                if (FLAG_UNSET == GetTrainSuspectTail(trainIdInSeq))
                {
                    /*û�к�Σ������,����Ӻ�˿��ɱ��*/
                } 
                else
                {
                    /*���ǰ��Σ��������*/
                    SetTrainSuspectHead(trainId,FLAG_SET);
                    errorCode = 0x06U;
                }
            } 
            else
            {
                /*���ǰ��Σ��������*/
                SetTrainSuspectHead(trainId,FLAG_SET);
                errorCode = 0x07U;
            }
        }
    } 
    else
    {
        /*���ǰ��Σ��������*/
        SetTrainSuspectHead(trainId,FLAG_SET);
        errorCode = 0x08U;
    }

    if (FLAG_SET == GetTrainSuspectHead(trainId))
    {
        /*�����ǰ��Σ��������,�г���Ҫ�����ƶ�*/
        SetTrainToModeToRM0(trainId);
		LogPrintf(1u,"%d-B67\n",trainId);
    } 
    else
    {
        /*������*/
    }

    if (0U == errorCode)
    {
        /*������*/
    } 
    else
    {
        LogPrintf(1U,"1.11 TrainId=%d,UnSHeadAcId=%d,frontAcId=%d,SuspectHead=%d,errorCode=%d\n",trainId,trainUnSafeHeadAcId,frontAcId,GetTrainSuspectHead(trainId),errorCode);
    }
}

/*************************************************
  ������:      ManageAddTrainTailSuspect
  ��������:    �����г���Σ��Դ��Ϣ���Ƿ�����Σ��Դ����Ӻ�Σ�������ǣ�
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      ��
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
        /* �ǰ�ȫ��β���������г� */
        if((GetAcTrainOfAcNum(trainUnSafeTailAcId)-1U) == trainSeqIndex)
        {
            /* �ó�Ϊ��������ĩβ���г�,��ѯ��󷽼������� */
            rtnRearAc = CheckRearACStatus(trainUnSafeTailAcId,trainDir,&rearAcId);

            if (RETURN_SUCCESS == rtnRearAc)
            {
                acDir = CalculateTrainDirInOtherAc(FLAG_UNSET,trainUnSafeTailAcId,rearAcId,trainDir);

                switch (acDir)
                {
                case AC_DIR_FARAWAY:
                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(rearAcId))
                    {
                        /*�󷽼��������޳�*/
                    } 
                    else
                    {
                        if(RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(rearAcId,GetAcTrainOfAcNum(rearAcId)-1U,&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectTail(trainIdInSeq))
                                {
                                    /*�����ǰ��������ɱ��*/
                                } 
                                else
                                {
                                    /*��Ӻ�Σ��������*/
                                    SetTrainSuspectTail(trainId,FLAG_SET);
                                    errorCode = 3U;
                                }
                            } 
                            else
                            {
                                /*���г�Ϊ���г�*/
                            }
                        }                       
                    }
                    break;
                case AC_DIR_CLOSED:
                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(rearAcId))
                    {
                        /*�󷽼��������޳�*/
                    }
                    else
                    {
                        if(RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(rearAcId,0U,&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectHead(trainIdInSeq))
                                {
                                    /*�����ǰ��������ɱ��*/
                                } 
                                else
                                {
                                    /*��Ӻ�Σ��������*/
                                    SetTrainSuspectTail(trainId,FLAG_SET);
                                    errorCode = 4U;
                                }
                            } 
                            else
                            {
                                /*���г�Ϊ���г�*/
                            }
                        }               
                    }
                    break;

                case DEFAULT_ZERO:
                    /*����ʧ��,��Ӻ�Σ��������*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 5U;
                    break;

                default:
                    if ((AC_FREE_STATUS == GetAcStatusNow(rearAcId))
                        || (FLAG_SET == GetAcArbFlag(rearAcId))
                        || (DEFAULT_ZERO != GetAcArbRedundance(rearAcId))
                        || (DEFAULT_ZERO != GetAcUtRedundance(rearAcId)))
                    {
                        /*�����ǰ��������ɱ��*/
                    } 
                    else
                    {
                        /*��Ӻ�Σ��������*/
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
                    /*��·��ͷ��ѯʧ��,������*/
                } 
                else
                {
                    /*��Ӻ�Σ��������*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 7U;
                }
            }
        }
        else
        {
            /* ���г��󷽻��������г�,�鿴���г�ǰ���Ƿ���� */		
            if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(trainUnSafeTailAcId,trainSeqIndex + 1U,&trainIdInSeq))
            {
                if (FLAG_UNSET == GetTrainSuspectHead(trainIdInSeq))
                {
                    /*����Ӻ�˿��ɱ��*/
                } 
                else
                {
                    /*��Ӻ�Σ��������*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 1U;
                }
            } 
            else
            {
                /*��Ӻ�Σ��������*/
                SetTrainSuspectTail(trainId,FLAG_SET);
                errorCode = 2U;
            }
        }
#if 0
        if ((DEFAULT_ZERO < trainSeqIndex)
            && ((GetAcTrainOfAcNum(trainUnSafeTailAcId)-1U) > trainSeqIndex))
        {
            /*�г�λ�ڸü������ε��м�����,�鿴�г����г�ǰ���Ƿ����*/		
            if (RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(trainUnSafeTailAcId,trainSeqIndex + 1U,&trainIdInSeq))
            {
                if (FLAG_UNSET == GetTrainSuspectHead(trainIdInSeq))
                {
                    /*����Ӻ�˿��ɱ��*/
                } 
                else
                {
                    /*��Ӻ�Σ��������*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 1U;
                }
            } 
            else
            {
                /*��Ӻ�Σ��������*/
                SetTrainSuspectTail(trainId,FLAG_SET);
                errorCode = 2U;
            }
        } 
        else
        {
            /* �˼�������ֻ��һ�г� */
            rtnRearAc = CheckRearACStatus(trainUnSafeTailAcId,trainDir,&rearAcId);

            if (RETURN_SUCCESS == rtnRearAc)
            {
                acDir = CalculateTrainDirInOtherAc(FLAG_UNSET,trainUnSafeTailAcId,rearAcId,trainDir);

                switch (acDir)
                {
                case AC_DIR_FARAWAY:
                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(rearAcId))
                    {
                        /*�󷽼��������޳�*/
                    } 
                    else
                    {
                        if(RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(rearAcId,GetAcTrainOfAcNum(rearAcId)-1U,&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectTail(trainIdInSeq))
                                {
                                    /*�����ǰ��������ɱ��*/
                                } 
                                else
                                {
                                    /*��Ӻ�Σ��������*/
                                    SetTrainSuspectTail(trainId,FLAG_SET);
                                    errorCode = 3U;
                                }
                            } 
                            else
                            {
                                /*���г�Ϊ���г�*/
                            }
                        }                       
                    }
                    break;
                case AC_DIR_CLOSED:
                    if (DEFAULT_ZERO == GetAcTrainOfAcNum(rearAcId))
                    {
                        /*�󷽼��������޳�*/
                    }
                    else
                    {
                        if(RETURN_SUCCESS == GetTrainIdInTrainSequenceOfIndex(rearAcId,0U,&trainIdInSeq))
                        {
                            if (trainId != trainIdInSeq)
                            {
                                if (FLAG_UNSET == GetTrainSuspectHead(trainIdInSeq))
                                {
                                    /*�����ǰ��������ɱ��*/
                                } 
                                else
                                {
                                    /*��Ӻ�Σ��������*/
                                    SetTrainSuspectTail(trainId,FLAG_SET);
                                    errorCode = 4U;
                                }
                            } 
                            else
                            {
                                /*���г�Ϊ���г�*/
                            }
                        }               
                    }
                    break;

                case DEFAULT_ZERO:
                    /*����ʧ��,��Ӻ�Σ��������*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 5U;
                    break;

                default:
                    if ((AC_FREE_STATUS == GetAcStatusNow(rearAcId))
                        || (FLAG_SET == GetAcArbFlag(rearAcId))
                        || (DEFAULT_ZERO != GetAcArbRedundance(rearAcId))
                        || (DEFAULT_ZERO != GetAcUtRedundance(rearAcId)))
                    {
                        /*�����ǰ��������ɱ��*/
                    } 
                    else
                    {
                        /*��Ӻ�Σ��������*/
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
                    /*��·��ͷ��ѯʧ��,������*/
                } 
                else
                {
                    /*��Ӻ�Σ��������*/
                    SetTrainSuspectTail(trainId,FLAG_SET);
                    errorCode = 7U;
                }

            }
        }
#endif
    } 
    else
    {
        /*��Ӻ�Σ��������*/
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
  ������:      JudgeTrainHeadSuspect
  ��������:    �ж��Ƿ����ȥ���г�ǰ��Σ��Դ��Ϣ
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      1u������ɹ���ǰ����Σ��Դ��
               0u������ʧ�ܣ�ǰ������Σ��Դ��
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
    UINT8_S checkFlag = RETURN_ERROR;	      /* �ҵ�ǰ���������α�־*/
    UINT32_S lineMinTrainLength = DEFAULT_ZERO;
    UINT8_S acStatusNow = DEFAULT_ZERO;
    UINT16_S trainError = DEFAULT_ZERO;       /* ������ */
    UINT16_S backLink = DEFAULT_ZERO;       /* ǰ��ɸѡ��Link */
    UINT32_S backOffset = DEFAULT_ZERO;     /* ǰ��ɸѡ��ƫ���� */
    UINT16_S errorSwitchId = DEFAULT_ZERO;
    UINT8_S  backPointFlag = DEFAULT_ZERO;    
    UINT8_S checkAcEndFlag = RETURN_ERROR;    /* ��ȡ���������յ��־ */


    trainDir = GetTrainUnsafeDirection(trainId);
    trainUnSafeHeadAcId = GetTrainUnsafeTrainHeadAC(trainId);   
    getFlag = GetTrainUnSafeLoc(trainId,&trainUnsafeLocStru);
    checkFlag = CheckFrontACStatus(trainUnSafeHeadAcId,trainDir,&frontAcId);
    trainError = GetTrainError(trainId);

    if ((RETURN_SUCCESS == getFlag) && (RETURN_SUCCESS == checkFlag))
    {
        /* �����з��������ĳ���� */
        backPointFlag = CheckNextPointOnDistance(trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset,
                                                  TrainDirChangeForCheck(trainId),(UINT32_S)trainError,&backLink,&backOffset,&errorSwitchId);

        /* ��ѯ�����з����ն�λ�� */
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
                /*����С����·��С�г�������ǰ���������ο���*/
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
  ������:      JudgeTrainTailSuspect
  ��������:    �ж��Ƿ����ȥ���г���Σ��Դ��Ϣ
  ����:        const UINT16_S trainId �г�ID
  ���:        ��
  ����ֵ:      1u������ɹ�������Σ��Դ��
               0u������ʧ�ܣ��󷽴���Σ��Դ��
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
        /*��ѯ�����з������λ��*/
        if (RETURN_SUCCESS == CheckAcTopPosition(trainSafeTailAcId,((UINT16_S)trainDir),&acLink,&acOffset))
        {
            distanceOfPoint = CheckDistanceBetweenTwoPoints(acLink,acOffset,trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,trainDir);
            lineMinTrainLength = (UINT32_S)GetLineMinTrainLength();
            acStatusNow = GetAcStatusNow(rearAcId);

            if ((distanceOfPoint < lineMinTrainLength)
                && (AC_FREE_STATUS == acStatusNow))
            {
                /*����С����·��С�г�������ǰ���������ο���*/
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
  ������:      CalulateTrainLocToAcInfo
  ��������:    �����г�ռѹ�İ�ȫ�ͷǰ�ȫ��������
  ����:        ��
  ���:        ��
  ����ֵ:      ��
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
        /*��ȡ�г�ID*/
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);
        needFlag = JudgeTrainNeedCalculate(trainId);

        if ((DEFAULT_ZERO != trainId)
            && (TRAIN_MODE_OUT != trainType)
            && (DEFAULT_ZERO != trainType)
            && ((RETURN_SUCCESS == needFlag)))
        {
            /*��ȡ�г���ȫλ����Ϣ*/
            if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
            {
                /*���㰲ȫλ�����ڼ�������*/
                checkAcId = CheckPositionBelongAc(trainSafeLocStru.TrainHeadLink);
                SetTrainTrainHeadAC(trainId,checkAcId);

                checkAcId = CheckPositionBelongAc(trainSafeLocStru.TrainTailLink);
                SetTrainTrainTailAC(trainId,checkAcId);
            } 
            else
            {
                /*��ȡʧ��,����ȫ*/
                SetTrainTrainHeadAC(trainId,DEFAULT_ZERO);
                SetTrainTrainTailAC(trainId,DEFAULT_ZERO);
            }

            /*��ȡ�г��ǰ�ȫλ����Ϣ*/
            if (RETURN_SUCCESS == GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru))
            {
                /*����ǰ�ȫλ�����ڼ�������*/
                checkAcId = CheckPositionBelongAc(trainUnSafeLocStru.TrainHeadLink);
                SetTrainUnsafeTrainHeadAC(trainId,checkAcId);

                checkAcId = CheckPositionBelongAc(trainUnSafeLocStru.TrainTailLink);
                SetTrainUnsafeTrainTailAC(trainId,checkAcId);
            } 
            else
            {
                /*��ȡʧ��,����ȫ*/
                SetTrainUnsafeTrainHeadAC(trainId,DEFAULT_ZERO);
                SetTrainUnsafeTrainTailAC(trainId,DEFAULT_ZERO);
            }
        } 
        else
        {
            /*������*/
        }
    }
}

/*************************************************
  ������:      CalculateCommTrainMatchingRoute
  ��������:    ����ͨ���г��Ƿ���ƥ���Ͽ��õĽ�·��Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
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
        /*��ȡ�г�ID*/
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);

        /*�жϸ��г������Ƿ������·ƥ������*/
        if((TRAIN_MODE_IN == trainType) || (TRAIN_MODE_RM == trainType)
            ||(TRAIN_MODE_RM0 == trainType) || (TRAIN_MODE_CBTC == trainType))
        {
            /*����г�������ƥ��Ľ�·��Ϣ*/
            MemorySet(mathRouteIdBuff,sizeof(UINT16_S)*SIZE_MAX_ROUTENUM,DEFAULT_ZERO,sizeof(UINT16_S)*SIZE_MAX_ROUTENUM);
            SetTrainMatchedRouteIdBuf(trainId,mathRouteIdBuff,DEFAULT_ZERO);
            mathRouteNum = 0U;

            /*ѭ���г�����������ƥ���·����*/
            for(mathRouteCycle = DEFAULT_ZERO;mathRouteCycle < SIZE_MAX_ROUTENUM;mathRouteCycle++)
            {
                if (MatchTrainSingleRoute(trainId,mathRouteCycle,mathRouteIdBuff))
                {
                    /*ƥ��ɹ�,����ƥ����һ����·*/
                    mathRouteNum++;
                } 
                else
                {
                    /*ƥ��ʧ��,������·ƥ��*/
                    break;
                }
            }

            /*��дƥ���·��Ϣ*/
            SetTrainMatchedRouteIdBuf(trainId,mathRouteIdBuff,mathRouteNum);

           /* LogPrintf(1U,"14.01 TrainId=%d,MathNum=%d,MathRoute=%d,%d,%d\n",trainId,mathRouteNum,mathRouteIdBuff[0],mathRouteIdBuff[1],mathRouteIdBuff[2]); */
        } 
        else
        {
            /*������*/
        }
    }
}

/*************************************************
  ������:      MatchTrainSingleRoute
  ��������:    ����ͨ���г��Ƿ���ƥ���Ͽ��õĽ�·��Ϣ
  ����:        const UINT16_S trainId,��ƥ���г�ID
  ���:        UINT8_S matchRouteIndex,ƥ���·���±�
               UINT16_S mathRouteIdBuff[],ƥ���·��ID����
  ����ֵ:      0u:ƥ��ʧ��
               1u:ƥ��ɹ�
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
        /*��ȡ�г�����*/
        trainDir = GetTrainUnsafeDirection(trainId);

        /*�ж�*/
        if (DEFAULT_ZERO == matchRouteIndex)
        {
            /*�鿴�г���β���ڼ�������*/
            trainSafeTailAc = GetTrainTrainTailAC(trainId);
            trainUnSafeTrailAc = GetTrainUnsafeTrainTailAC(trainId);

            if (DEFAULT_ZERO != trainSafeTailAc)
            {
                /*ʹ�ð�ȫ��βλ����Ϊ��ѯ����*/
                mathAcId = trainSafeTailAc;
            } 
            else
            {
                if (DEFAULT_ZERO != trainUnSafeTrailAc)
                {
                    /*ʹ�÷ǰ�ȫ��βλ����Ϊ��ѯ����*/
                    mathAcId = trainUnSafeTrailAc;
                } 
                else
                {
                    mathAcId = DEFAULT_ZERO;
                }
            }

            /*�жϼ����Ƿ����ڿ�ƥ���·*/
            tempRtn = CalulateAcIdBelongUseableRoute(mathAcId,trainDir,&tailMathRouteId);

            switch (tempRtn)
            {
            case 0U:
                /*��ѯ�ǰ�ȫ��ͷ�Ƿ����ڿ�ƥ��Ľ�·*/
                trainUnSafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);

                switch (CalulateAcIdBelongUseableRoute(trainUnSafeHeadAc,trainDir,&headMathRouteId))
                {
                case 0U:
                    /*�ӽ�ƥ�䡣���������������������������������Ըɵ���������*/
                    /* CalculateBeCloseRouteMatch(trainId,&canMathRouteId); */

                    /*��ѯ��ͷǰ�������Ƿ��ƥ��*/
                    canMathRouteId = DEFAULT_ZERO;

                    if (RETURN_SUCCESS == MatchTrainHeadFrontAcInRoute(trainUnSafeHeadAc,trainId,&canMathRouteId))
                    {
                        /* ƥ���·�ɹ� */
                    }
                    else
                    {
                        canMathRouteId = DEFAULT_ZERO;
                    }
                    break;
                case 1U:
                    /*���ƥ�䣬ƥ��ʧ��*/
                    canMathRouteId = DEFAULT_ZERO;
                    break;
                case 2U:
                    /*�����ƥ��*/
                    canMathRouteId = headMathRouteId;
                    break;
                default:
                    /*���ƥ�䣬ƥ��ʧ��*/
                    canMathRouteId = DEFAULT_ZERO;
                    break;
                }
                break;

            case 1U:
                /*���ƥ�䣬ƥ��ʧ��*/
                canMathRouteId = DEFAULT_ZERO;
                break;

            case 2U:
                /*��β��ƥ�䣬���ǰ�ȫ��ͷ�Ƿ���Ա�ƥ��*/
                trainUnSafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);

                if (2U == CalulateAcIdBelongUseableRoute(trainUnSafeHeadAc,trainDir,&headMathRouteId))
                {
                    /*�����ƥ��*/
                    /*ͬʱƥ���˳�β�ͳ�ͷ�Ľ�·��Ĭ���ó�βƥ���ϵĽ�·*/
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
            /* ƥ���·�е���һ����·ID */
            tmpLastRouteId = matchRouteIdBuff[matchRouteIndex - 1U];

            /* ��ѯ��һ����·���� */
            if (LINE_REVERSE_ROUTE == GetRouteType(tmpLastRouteId))
            {
                /*������ǰƥ����һ����·*/
            } 
            else
            {
                /* ��ȡ��һ����·�����һ���������� */           
                if (RETURN_SUCCESS == GetRoutOfAcIdFromIndex(tmpLastRouteId,(GetRouteOfAcNum(tmpLastRouteId) - 1U),&lastAcIdInRoute))
                {
                    matchFlag = MatchTrainHeadFrontAcInRoute(lastAcIdInRoute,trainId,&tailMathRouteId);

                    if ((DEFAULT_ZERO != lastAcIdInRoute) && (RETURN_SUCCESS == matchFlag))
                    {
                        /*���Ա�ƥ��*/
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
  ������:      MatchTrainHeadFrontAcInRoute
  ��������:    ����ͨ���г��Ƿ���ƥ���Ͽ��õĽ�·��Ϣ
  ����:        const UINT16_S trainHeadAcId,�г���ͷ��������ID
               const UINT16_S trainId,��ƥ���г�Id
  ���:        UINT16_S *pMatchRouteId,ƥ���·��Ϣ
  ����ֵ:      0u:ƥ��ʧ��
               1u:ƥ��ɹ�
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
        /*��ȡ�г�����*/
        trainDir = GetTrainUnsafeDirection(trainId);

        /*��ѯ�г���ͷ���ڼ���ǰ����������*/
        if (RETURN_SUCCESS == CheckFrontACStatus(trainHeadAcId,trainDir,&frontAcId))
        {
            /*�ж�ǰ�����������Ƿ�����ĳ����ƥ��Ľ�·*/
            if (2U == CalulateAcIdBelongUseableRoute(frontAcId,trainDir,&trainMatchRouteId))
            {
                /*��ȡ��·��ʼ���źŻ�*/
                signalIdOfRoute = GetRouteOfSingalId(trainMatchRouteId);

                if (RETURN_ERROR != signalIdOfRoute)
                {
                    if (trainDir == GetSignalProtectDir(signalIdOfRoute))
                    {
                        switch (GetSignalStatus(signalIdOfRoute))
                        {
                        case SIGNAL_STATE_PASS:
                            /*�źŻ�����,ֱ��ƥ��*/
                            (*pMatchRouteId) = trainMatchRouteId;
                            rtnValue = RETURN_SUCCESS;
                            break;
                        case SIGNAL_STATE_STOP:
                            /*�źŻ�δ����,�ж��г��Ƿ���Խ���ú���źŻ�*/
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
  ������:      CalculateSignalLocBetweenTrainLoc
  ��������:    �����źŻ���λ���Ƿ�λ���г���ͷ��β֮��
  ����:        const UINT16_S trainId,�г�ID
               const UINT16_S signalId,�źŻ�ID
  ���:        ��
  ����ֵ:      0u:�Ƚ�ʧ��
               1u:λ���г���ͷ��βλ��֮��
               2u:��λ���г���ͷ��βλ��֮��
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

    /*��ȡ�źŻ�λ�ú��г���ȫλ��*/
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
                /*�źŻ�λ���г�λ��֮��*/
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
  ������:      CalulateAcIdBelongUseableRoute
  ��������:    ����ͨ���г��Ƿ���ƥ���Ͽ��õĽ�·��Ϣ
  ����:        const UINT16_S acId,��������ID
               const UINT8_S dir,ƥ���·����
  ���:        UINT16_S *pMathRouteId,�����ƥ���· 
  ����ֵ:      0u:���᲻���ڰ����·
               1u:�������ڰ����·����·���ɱ�ƥ��
               2u:�������ڰ����·�ҽ�·�ɱ�ƥ��
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
        /*��δ�������֪��acId�������ڽ�·���������������֮��ļ��������Ƿ���������*/
        for (routeCycle = DEFAULT_ZERO;routeCycle < GetRouteSum();routeCycle++)
        {
            /*��ȡ��·Id*/
            routeId = GetRouteId((UINT16_S)routeCycle);
            signalOfRoute = GetRouteOfSingalId(routeId);
            routeAreaType = GetRouteAreaType(routeId);
            routeStatus = GetRouteStatus(routeId);
            signalProtectDir = GetSignalProtectDir(signalOfRoute);

            if ((ROUTE_STATE_SET == routeStatus) && (dir == signalProtectDir))
            {
                /*��ȡ��·���������ü�����Ϣ*/
                acNumInRoute = GetRouteOfAcNum(routeId);

                /*���ü����±�*/
                lockAcStartIndex = DEFAULT_UINT8_VALUE;
                breakFlag = DEFAULT_ZERO;

                if (RETURN_SUCCESS == GetRoutOfAcIdBuff(routeId,ROUTE_OF_AC_SUM_MAX,acIdInRouteBuff))
                {             
                    for (acCycle = DEFAULT_ZERO;acCycle < acNumInRoute;acCycle++)
                    {
                        if (acIdInRouteBuff[acCycle] == acId)
                        {
                            /*˵���Ѱ���Ľ�·�ڼ���͵�ǰ����ƥ��*/
                            lockAcStartIndex = acCycle;
                            break;
                        }
                        else
                        {
                            /*������*/
                        }
                    }

                }    

                /*�жϼ�������״̬�Ƿ�����ƥ������*/
                if (DEFAULT_UINT8_VALUE != lockAcStartIndex)
                {
                    for (lockAcCycle = lockAcStartIndex+1U;lockAcCycle < acNumInRoute;lockAcCycle++)
                    {
                        if (AC_UNLOCK_STATUS == GetAcBelock(acIdInRouteBuff[lockAcCycle]))
                        {
                            /*����δ���յļ�������,����*/
                            breakFlag = FLAG_SET;
                            break;
                        } 
                        else
                        {
                            /*������*/
                        }

                        /*���������ζ�Ӧ�ĵ����Ƿ��������ڹ涨λ��*/
                        if (RETURN_SUCCESS == JudgeSwitchLockAndPostionInAc(acIdInRouteBuff[lockAcCycle]))
                        {
                            /*������*/
                        } 
                        else
                        {
                            /*���������������ƥ������,����*/
                            breakFlag = FLAG_SET;
                            break;
                        }

                        if (CI_TRAIN_DEPOT_TYPE == routeAreaType)
                        {
                            /*�����ν�·��������Ҫ����δռ������*/
                            if (AC_OCC_STATUS == GetAcStatusNow(acIdInRouteBuff[lockAcCycle]))
                            {
                                /*�����λ���ͣ������·�ڲ�������������г�*/
                                breakFlag = FLAG_SET;
                                break;
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
                    breakFlag = FLAG_UNSET;
                }

                if (FLAG_SET == breakFlag)
                {
                    /*���ڽ�·,��������ƥ������*/
                    rtnValue = 1U;                  
                    break; 
                    
                } 
                else
                {
                    if (FLAG_UNSET == breakFlag)
                    {
                        /*�����ڽ�·*/
                        rtnValue = 0U;
                    } 
                    else
                    {
                        /*����ƥ������*/
                        (*pMathRouteId) = routeId;
                        rtnValue = 2U;
                        break;
                    }
                }

            } 
            else
            {
                /* �����ڿ��ý�· */
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
        /* �ж�acId�������ڽ�·���������������֮��ļ��������Ƿ��������� */
        for (routeCycle = DEFAULT_ZERO;routeCycle < GetRouteSum();routeCycle++)
        {
            /* ��ȡ��·Id */
            routeId = GetRouteId((UINT16_S)routeCycle);
            signalOfRoute = GetRouteOfSingalId(routeId);
            routeAreaType = GetRouteAreaType(routeId);
            routeStatus = GetRouteStatus(routeId);
            signalProtectDir = GetSignalProtectDir(signalOfRoute);

            if ((ROUTE_STATE_SET == routeStatus) && (dir == signalProtectDir))
            {
                /* ��ȡ��·���������ü�����Ϣ */
                acNumInRoute = GetRouteOfAcNum(routeId);

                /* ���ü����±� */
                lockAcStartIndex = DEFAULT_UINT8_VALUE;
                findFlag = DEFAULT_ZERO;

                if (RETURN_SUCCESS == GetRoutOfAcIdBuff(routeId,ROUTE_OF_AC_SUM_MAX,acIdInRouteBuff))
                {             
                    for (acCycle = DEFAULT_ZERO;acCycle < acNumInRoute;acCycle++)
                    {
                        if (acIdInRouteBuff[acCycle] == acId)
                        {
                            /* ˵���ѽ����Ľ�·�ڼ���͵�ǰ����ƥ�� */
                            lockAcStartIndex = acCycle;
                            breakFlag = DEFAULT_ZERO;

                            /* �ѽ����Ľ�·������ѯ�ļ������Σ��жϽ�·������������ε�ǰ�����м���������� */
                            for (lockAcCycle = lockAcStartIndex+1U;lockAcCycle < acNumInRoute;lockAcCycle++)
                            {
                                if (AC_UNLOCK_STATUS == GetAcBelock(acIdInRouteBuff[lockAcCycle]))
                                {
                                    /* ����δ���յļ�������,����������·�������������ε�ѭ�� */
                                    breakFlag = FLAG_SET;
                                    break;
                                } 
                                else
                                {
                                    /* ������ */
                                }

                                /* ���������ζ�Ӧ�ĵ����Ƿ��������ڹ涨λ�� */
                                if (RETURN_SUCCESS == JudgeSwitchLockAndPostionInAc(acIdInRouteBuff[lockAcCycle]))
                                {
                                    /* ������ */
                                } 
                                else
                                {
                                    /* ���������������ƥ������,����������·�������������ε�ѭ�� */
                                    breakFlag = FLAG_SET;
                                    break;
                                }

                                if (CI_TRAIN_DEPOT_TYPE == routeAreaType)
                                {
                                    /* �����ν�·��������Ҫ����δռ������ */
                                    if (AC_OCC_STATUS == GetAcStatusNow(acIdInRouteBuff[lockAcCycle]))
                                    {
                                        /* �����λ���ͣ������·�ڲ�������������г�,����������·�������������ε�ѭ�� */
                                        breakFlag = FLAG_SET;
                                        break;
                                    } 
                                    else
                                    {
                                        /* ������ */
                                    }
                                } 
                                else
                                {
                                    /* ������ */
                                }
                            }

                            if (FLAG_SET == breakFlag)
                            {
                                /* ���ѽ����Ľ�·�ڵļ������ΰ����Ĳ�ѯ�ļ�������,�������µļ������β��������� */
                                rtnValue = 1u;
                                break;
                            }
                            else
                            {
                                /* ����ƥ������ */
                                (*pMathRouteId) = routeId;
                                rtnValue = 2u;
                                findFlag = FLAG_SET;
                                break;
                            }
                        }
                        else
                        {
                            /* ���������ѽ�����·�����µļ������� */
                        }
                    }   

                    if (FLAG_SET == findFlag)
                    {
                        /* �Ѿ��ҵ�������������·��ѭ�� */
                        break;
                    }
                }
            } 
            else
            {
                /* �����ڿ��ý�·,�������� */
            }	
        }
    }

    return rtnValue;
}

/*************************************************
  ������:      CalulateRouteMathToTrain
  ��������:    ����ָ���г�ID�Ƿ���ƥ��ָ����·
  ����:        const UINT16_S routeId,��·ID
               const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      0u:ƥ��ʧ��
               1u:ƥ��ɹ�
*************************************************/
UINT8_S CalulateRouteMathToTrain(const UINT16_S routeId,const UINT16_S trainId)
{
    UINT16_S routeSignalId = DEFAULT_ZERO;
    UINT8_S signalProtectDir = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*��·���*/
    routeSignalId = GetRouteOfSingalId(routeId);

    /*��ȡ�źŻ��ķ�������*/
    signalProtectDir = GetSignalProtectDir(routeSignalId);

    /*�Ƿ���Ҫ�ж����շ�����г��������з���һ�£���������*/
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
  ������:      CalculateBeCloseRouteMatch
  ��������:    ����ָ���г�ID�Ƿ��ܰ���·�ӽ�ƥ��ԭ��ƥ��ָ����·
  ����:        const UINT16_S routeId,��·ID
  ���:        UINT16_S *pMathRouteId,����ƥ��Ľ�·ID
  ����ֵ:      0u:ƥ��ʧ��
               1u:ƥ��ɹ�
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
            /*��ѯ���г���ͷǰ�������ͬ���źŻ�*/
            trainDir = GetTrainUnsafeDirection(trainId);
            checkFlag = CheckPointNearestSignalBaseDir(trainDir,trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset,&frontSignalId);

            if (RETURN_SUCCESS == checkFlag)
            {
                if (SIGNAL_STATE_PASS == GetSignalStatus(frontSignalId))
                {
                    for (cycleRoute = DEFAULT_ZERO ;cycleRoute < GetRouteSum();cycleRoute++)
                    {
                        /*��ȡ��·Id*/
                        routeId = GetRouteId(cycleRoute);
                        routeStatus = GetRouteStatus(routeId);
                        routeOfSingalId = GetRouteOfSingalId(routeId);
                        integralityFlag = CalculateRouteAcLockStatusIntegrality(routeId);

                        if ((ROUTE_STATE_SET == routeStatus)
                            && (frontSignalId == routeOfSingalId)
                            && (RETURN_SUCCESS == integralityFlag))
                        {
                            /*����ƥ������*/
                            (*pMatchRouteId) = routeId;
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
  ������:      CalculateRouteAcLockStatusIntegrality
  ��������:    ����ָ����·�ڼ������ε�����������
  ����:        const UINT16_S routeId,��·ID
  ���:        ��
  ����ֵ:      0u:δ��������
               1u:��������
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

	/*��ȡ��·���������ü�����Ϣ*/
	acNumInRoute = GetRouteOfAcNum(routeId);
	acIdRtn = GetRoutOfAcIdBuff(routeId,ROUTE_OF_AC_SUM_MAX,acIdInRouteBuff);
	
    /*�жϼ�������״̬�Ƿ�����ƥ������*/
    if (RETURN_SUCCESS == acIdRtn)
    {
        for (acCycle = DEFAULT_ZERO;acCycle < acNumInRoute;acCycle++)
        {
            if (AC_UNLOCK_STATUS == GetAcBelock(acIdInRouteBuff[acCycle]))
            {
                /*����δ���յļ�������,����*/
                break;
            } 
            else
            {
                /*������*/
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
  ������:      ManageTrainTypeTransform
  ��������:    �����г�����ת��
  ����:        ��
  ���:        ��
  ����ֵ:      ��
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
        /*��ȡ�г�ID*/
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
            /*˵���������г�ͨ������*/
            switch (trainType)
            {
            case DEFAULT_ZERO:
            case TRAIN_MODE_IN:	
                getLocFlag = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);			
                if ((TRAIN_IN_APPLY_MA == trainInType)
                    && (RETURN_SUCCESS == getLocFlag))
                {
                    /*��ѯ�г���ͷ�ǰ�ȫλ���Ƿ�Խ��ת����*/
                    checkRtn = CheckPointBelongToZHG(trainUnSafeLocStru.TrainHeadLink);

                    switch (checkRtn)
                    {
                    case 0U:
                        /*��ѯʧ��,����г�����*/
                        SetTrainType(trainId,DEFAULT_ZERO);
                        break;
                    case 2U:
                        /*��ѯ�ɹ�,��λ��ת������*/
                        SetTrainType(trainId,TRAIN_MODE_RM);
                        SetTrainSuspectHead(trainId,FLAG_SET);
                        SetTrainSuspectTail(trainId,FLAG_SET);
                        break;
                    case 1U:
                        /*��ѯ�ɹ�,λ��ת������*/
                        SetTrainType(trainId,TRAIN_MODE_IN);
                        SetTrainSuspectHead(trainId,FLAG_SET);
                        SetTrainSuspectTail(trainId,FLAG_SET);
                        break;
                    default:
                        /*����δ֪���,����г�����*/
                        SetTrainType(trainId,DEFAULT_ZERO);
                        break;
                    }

                    /*�г�״̬�����ƶ�״̬�жϣ�����*/
                    trainStatus = GetTrainStatus(trainId);
                    if ((TRAIN_MODE_IN == trainType)
                        && (DEFAULT_ZERO != trainStatus))
                    {
                        if((TRAIN_IN_LEVEL_CBTC == trainLevel )
                            &&((TRAIN_IN_MODE_AM == trainMode) || (TRAIN_IN_MODE_CM == trainMode)))
                        {
                            /*�г��Ѿ�����ΪCBTC����,������Ӧ����*/
                            SetTrainType(trainId,TRAIN_MODE_CBTC);
                        }
                        else
                        {
                            /*�г���δ������ά��֮ǰ���г�����*/
                        }
                    } 
                    else
                    {
                        /*������*/
                    }
                } 
                else
                {
                    /*ά�ֵ�ǰ����*/
                }
                break;
            case TRAIN_MODE_RM:
            case TRAIN_MODE_RM0:
                /*�ж��г��Ƿ����յ�ZC���ƶ���Ȩ��Ϣ������ΪCBTC������CM��AMģʽ*/

                if((TRAIN_IN_LEVEL_CBTC == trainLevel)
                    &&((TRAIN_IN_MODE_AM == trainMode) || (TRAIN_IN_MODE_CM == trainMode)))
                {
                    /*�г��Ѿ�����ΪCBTC����,������Ӧ����*/
                    SetTrainType(trainId,TRAIN_MODE_CBTC);
                }
                else
                {
                    /*�г���δ������ά��֮ǰ���г�����*/
                }
                break;
            case TRAIN_MODE_TO_RM0:
                if (TRAIN_IN_LEVEL_CBTC != trainLevel)
                {
                    /*˵����ʱ�г��Ѱ���ȷ�Ͻ�����ť,���г����ͽ��н�������*/
                    SetTrainType(trainId, TRAIN_MODE_RM0);
                    SetTrainSuspectHead(trainId,FLAG_SET);
                } 
                else
                {
                    /*������*/
                }
                break;
            case TRAIN_MODE_CBTC:
                if (TRAIN_IN_LEVEL_CBTC != trainLevel)
                {
                    /*�ж��г��Ƿ����۷�״̬��������г�����ΪILģʽΪRD*/
                    if ((TRAIN_IN_CHANGED == trainInType)
                        && (TRAIN_IN_LEVEL_IL == trainLevel)
                        && (TRAIN_IN_MODE_RD == trainMode))
                    {
                        /*ά��CBTC*/
                        /*PBW,20160526,����������ȷ��*/							
                        SetTrainOutType(trainId,OUT_TRAIN_CHANGED);
                        LogPrintf(1U,"OUT_TRAIN_CHANGED 2\n");
                    } 
                    else
                    {
                        /*���г�ֱ������ΪRM�����г���ǰ��˿���*/
                        SetTrainType(trainId,TRAIN_MODE_RM);
                        SetTrainSuspectHead(trainId,FLAG_SET);
                        SetTrainSuspectTail(trainId,FLAG_SET);
                        LogPrintf(1U,"21.001 Train=%d,Level Down!\n",trainId);
                    }
                } 
                else
                {
                    /*�г��������CBTC�����һ�ȡ�г���ȫλ����Ϣ�ɹ�*/
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
                                /*�г���ȫλ���˳�CBTC����*/
                                SetTrainType(trainId,TRAIN_MODE_OUT);
                            } 
                            else
                            {
                                /* ������ */
                            }
                            break;
                        case TRAIN_IN_APPLY_MA:
                            if (localZcId == GetAcBelongZcId(GetTrainUnsafeTrainHeadAC(trainId)))
                            {
                                /*�ǰ�ȫ��ͷ���ڼ������ڱ�ZC*/
                            } 
                            else
                            {
                                /*�ǰ�ȫ��ͷ���ڼ��᲻���ڱ�ZC*/
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
                                        /*������*/
                                    }
                                } 
                                else
                                {
                                    /*������*/
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
                                    /*������*/
                                }
                            } 
                            else
                            {
                                /*������*/
                            }
                            break;
                        default:
                            break;
                        }
                    } 
                    else
                    {
                        /* ������ */
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
            /*������*/
        }
    }
}

/*************************************************
  ������:      ManageTrainStatusTransform
  ��������:    �����г�״̬ת����Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
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
            /*����г����*/
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
                /* ������״̬ת�� */
                break;

            case TRAIN_STATE_FAILURE:
                /* ������״̬ת�� */
                break;
            default:
                break;
            }
        } 
        else
        {
            /*�˳����г�/������δ������Ϣ���г������д���*/
        }

        /* LogPrintf(1U,"15.01 TrainId=%d,StatusIn=%d,InType=%d,StatusOut=%d,cycle=%d\n",trainId,trainStatus,trainInType,GetTrainStatus(trainId),GetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId)); */
    }
}

/*************************************************
  ������:      ManageOutTrainType
  ��������:    �����г����״̬��Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
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
                    /*PBW.20160526,�г����뻻�������ΪRDģʽ,�����г��������Ϊ�������ȷ��*/					
                    SetTrainOutType(trainId,OUT_TRAIN_CHANGED);	
                    LogPrintf(1U,"OUT_TRAIN_CHANGED 1\n");												
                }
                else
                {
                    /*������*/
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
                        /*�ӹ�ZC��*/
                        SetTrainOutType(trainId,OUT_TRAIN_MOVING);
                    } 
                    else if (localZcId == handOverZcId)
                    {
                        /*�ƽ�ZC��,��Ҫ����ZCͨ�����������*/
                        if (DEFAULT_ZERO == GetCommTargetCycle(INNER_DEVTYPE_ZC,takeOverZcId))
                        {
                            SetTrainOutType(trainId,OUT_TRAIN_MOVING);
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
			   /* ������ */
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
			    /* ������ */
                break;
            }
            break;
		case TRAIN_STATE_HANDOVER:
            switch(trainInType)
            {
            case TRAIN_IN_APPLY_MA:
                /*pbw 2016.10.23 ��Ӵ����ƽ�״̬��֧ */
                SetTrainOutType(trainId,OUT_TRAIN_MOVING);
                break;
            default:			
                /* ������ */
                break;
            }
            break;
        default:
		    /* ������ */
            break;
        }
    }

}

/*************************************************
  ������:      ManageNZcOutTrainType
  ��������:    �����г�����ZC���״̬��Ϣ
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ManageNZcOutTrainType(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
	UINT8_S trainHandoverInType = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        /*��ȡ�г���Ϣ*/
        trainId = GetTrainIdOfIndex(cycle);
		trainHandoverInType=GetTrainHandoverInType(trainId);

        switch (trainHandoverInType)
        {
        case NZC_TRAIN_DEFAULT:
            /*��״̬*/
            JudegeNZcDefaultStatusTransform(trainId);
            break;

        case NZC_TRAIN_HANDOVER:
            /*�ƽ�����״̬*/
            JudegeNZcHandStatusTransform(trainId);
            break;

        case NZC_TRAIN_CONFIRMATION:
            /*�ƽ�����ȷ��״̬*/
            JudgeNZcConfirmationStatusTransform(trainId);
            break;

        case NZC_TRAIN_MANAGENOHAND:
            /*�ƽ�δ�л�*/
#if 0
            /*����ZC���״̬Ϊ��״̬*/
            /* pbw 2017.6.6 ���Է�CBTC�г��л���ʱ��ZC���г���Ϣ��һ�³��� */
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
            /*�ӹ�δ�л�*/
            /*����ZC���״̬Ϊ��״̬*/
            SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
            break;

        case NZC_TRAIN_HADTOOKOVER:
            /*�ѽӹ�*/
            /*����ZC���״̬Ϊ��״̬*/
            SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
            break;

        default:
            /*ά�ֵ�ǰ״̬*/

            break;
        }
    }
}

/*************************************************
  ������:      JudegeNZcDefaultStatusTransform
  ��������:    ��������ZC����״̬Ϊ��״̬���߿�ѹ�л�����µ�����ZC���ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
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

    /*��ȡ�г���Ϣ*/
    trainChangeLineId = GetTrainChangeLineId(trainId);
    trainState = GetTrainStatus(trainId);
    trainDir = GetTrainUnsafeDirection(trainId);

    if (DEFAULT_ZERO != trainChangeLineId)
    {
        if (TRAIN_STATE_HANDOVER == trainState)
        {
            /*���л���·��״̬Ϊ�ƽ�״̬,�����ϢΪ�ƽ�����*/
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
                /*�ж��г���ȫ��β�Ƿ�Խ���л���*/
                checkTrainTailRtn = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,changeLink,changeOffset,trainDir);

                if (1U == checkTrainTailRtn)
                {
                    /*��ȫ��β��Խ���ֽ���һ�λ���л���·��*/
                    if (handoverZcId == localZcId)
                    {
                        /*��ZC�ڸ÷ֽ��Ϊ�ƽ���ɫ,����ZC���״̬Ϊ��״̬*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    } 
                    else if (takeoverZcId == localZcId)
                    {
                        /*��ZC�ڸ÷ֽ��Ϊ�ӹܽ�ɫ,����ZC���״̬Ϊ�ӹ�δ�л�*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOTAKE);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    } 
                    else
                    {
                        /*����ZC���״̬Ϊ��״̬*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    }
                } 
                else
                {
                    /*�ж��г���ȫ��ͷ�Ƿ�Խ���л���*/
                    checkTrainHeadRtn = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset,changeLink,changeOffset,trainDir);

                    if (2U == checkTrainHeadRtn)
                    {
                        /*��ȫ��ͷδԽ���л����Ҳ������л�״̬,����ZC�����ϢΪ�ƽ�δ�л�*/
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
                            /*��ͷԽ������βδԽ���л���,�ܿ�ZC�Ǳ�ZC*/
                            if (handoverZcId == localZcId)
                            {
                                /*��ZC�ڸ÷ֽ��Ϊ�ƽ���ɫ*/
                                SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOHAND);
                                SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                            } 
                            else if (takeoverZcId == localZcId)
                            {
                                /*��ZC�ڸ÷ֽ��Ϊ�ӹܽ�ɫ*/
                                SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOTAKE);
                                SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                            } 
                            else
                            {
                                /*����ZC���״̬Ϊ��״̬*/
                                SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                                SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                            }
                        } 
                        else
                        {
                            /*����ZC���״̬Ϊ��״̬*/
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
        /*����ZC���״̬Ϊ��״̬*/
        SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
    }
}

/*************************************************
  ������:      JudegeNZcHandStatusTransform
  ��������:    ��������ZC����״̬Ϊ�ƽ�����״̬���µ�����ZC���ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
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

    /*��ȡ�г���Ϣ*/
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
            /*�ж��г���ȫ��β�Ƿ�Խ���л���*/
            checkTrainTailRtn = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,changeLink,changeOffset,trainDir);

            localZcId = GetLocalZcId();
            trainControlZc = GetTrainControlZc(trainId);

            /* ��ȫ��βԽ���ֽ�� */
            if (0x01U == checkTrainTailRtn)
            {         
                if (localZcId == trainControlZc)
                {
                    /*��β��Խ���л���,����ZC�����ϢΪ�ӹ�δ�л�*/
                    SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOTAKE);
                    SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                } 
                else
                {
                    /*���Ϊ��״̬*/
                    SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                    SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                }
            } 
            else
            {
                /*�жϳ�ͷ�Ƿ�Խ���л���*/
                checkTrainHeadRtn = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset,changeLink,changeOffset,trainDir);

                if ((0x01U == checkTrainHeadRtn)
                    && (localZcId == trainControlZc)
                    && (TRAIN_STATE_MOVING == trainState))
                {
                    /*Խ���л������ܿ��ѱ�Ϊ��ZC*/
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
            /* ������ */
        }        
    } 
    else
    {
        if (DEFAULT_ZERO == trainChangeLineId)
        {
            /*���Ϊ��״̬*/
            SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
            SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
        } 
        else
        {
            /*ά��״̬*/
        }
    }
}

/*************************************************
  ������:      JudgeNZcConfirmationStatusTransform
  ��������:    ��������ZC����״̬Ϊ�ƽ�����ȷ��״̬���µ�����ZC���ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
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

    /*��ȡ�г���Ϣ*/
    trainChangeLineId = GetTrainChangeLineId(trainId);
    trainState = GetTrainStatus(trainId);
    trainDir = GetTrainUnsafeDirection(trainId);
    rtnLoc = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);
	trainControlZc = GetTrainControlZc(trainId);


	localZcId = GetLocalZcId();

    if (DEFAULT_ZERO == trainChangeLineId)
    {
        /*�������ZC���λ��Ϣ*/
        SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
    } 
    else
    {
        if (TRAIN_STATE_HANDOVER == trainState)
        {
            /*ά��״̬*/
        } 
        else
        {
            if (RETURN_SUCCESS == rtnLoc)
            {
                /*�жϳ�ͷ�Ƿ�Խ���л���*/
                checkTrainHeadRtn = CheckLocRelationBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,trainUnSafeLocStru.TrainHeadOffset,changeLink,changeOffset,trainDir);

                if (0x01U == checkTrainHeadRtn)
                {
                    /*Խ���л������ܿ���Ϊ��ZC(�ƽ�ZC)*/
                    trainInType = GetTrainInType(trainId);

                    if ((DEFAULT_ZERO != trainInType)
                        && (trainControlZc == localZcId))
                    {
                        /*��ͷԽ���л����Ҹ��г�������MA,����ZC�����ϢΪ�ƽ�δ�л�*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOHAND);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    } 
                    else
                    {
                        /*��ͷԽ���л������ܿ��Ѳ��Ǳ�ZC�������г�������Ϣ,�������ZC�����Ϣ*/
                        SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
                        SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                    }
                } 
                else
                {
                    /*��ͷδԽ���л����Ҳ�Ϊ�ƽ�״̬�г�,����ZC�����ϢΪ�ƽ�δ�л�*/
                    SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOHAND);
                    SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                }
            }          
        }
    }
}

/*************************************************
  ������:      JudgeNZcManagenohandStatusTransform
  ��������:    ��������ZC����״̬Ϊ�ƽ�δ�л�״̬���µ�����ZC���ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
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

	/*��ȡ�г���Ϣ*/
	trainChangeLineId = GetTrainChangeLineId(trainId);
	trainDir = GetTrainUnsafeDirection(trainId);
	rtnLoc = GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru);
	trainControlZc = GetTrainControlZc(trainId);
	trainState = GetTrainStatus(trainId);

	localZcId = GetLocalZcId();

	if (DEFAULT_ZERO == trainChangeLineId)
	{
		/*�������ZC���λ��Ϣ*/
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

			/*�жϳ�ͷ�Ƿ�Խ���л���*/
			checkTrainHeadRtn = CheckLocRelationBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,trainUnSafeLocStru.TrainHeadOffset,changeLink,changeOffset,trainDir);

			if (0x01U == checkTrainHeadRtn)
			{
				/*Խ���л������ܿ���Ϊ��ZC(�ӹ�ZC)*/
				trainInType = GetTrainInType(trainId);

				if ((DEFAULT_ZERO != trainInType)
					&& (trainControlZc == localZcId))
				{
					/*��ͷԽ���л����Ҹ��г��ѿ�ʼ����MA,����ZC�����ϢΪ�ӹ�δ�л�*/
					SetTrainHandoverOutType(trainId,NZC_TRAIN_MANAGENOTAKE);
					SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
				} 
				else
				{
					/*��ͷԽ���л������ܿ��Ѳ��Ǳ�ZC�������г�������Ϣ,�������ZC�����Ϣ*/
					SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
					SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
				}
			} 
			else
			{
				/*��ͷδԽ���л���,�������ZC�����Ϣ*/
				SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
				SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
			}
		} 
        else
        {
            /*�������ZC���λ��Ϣ*/
            SetTrainHandoverOutType(trainId,NZC_TRAIN_DEFAULT);
            SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
        }
	}
}

/*************************************************
  ������:      JudgeTrainDefaultStatusTransform
  ��������:    ����Ĭ��״̬��ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeTrainDefaultStatusTransform(const UINT16_S trainId)
{
	UINT8_S trainType = DEFAULT_ZERO;
	UINT8_S trainInType = DEFAULT_ZERO;
	UINT8_S trainSuspectHead = DEFAULT_ZERO;
	UINT8_S matchRouteNum =DEFAULT_ZERO;
	UINT8_S checkFlag = RETURN_ERROR;
	
	/* ��ȡ�г���Ϣ */
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
            /*������*/
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
            /*������*/
        }
        break;
    default:
        break;
    }
}

/*************************************************
  ������:      JudgeTrainStateMovingTransform
  ��������:    ����STATE_MOVING״̬�г�״̬��ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
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
	
	/* ��ȡ�г���Ϣ */
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
                /*��ȡ��Ϣ*/
                trainMaTailLink = GetMaTailLink(trainId);
                trainMaTailOffset = GetMaTailOffset(trainId);
                changeLink = GetChangeLineChangePointLink(trainChangeLineId);
                changeOffset = GetChangeLineChangePointOffset(trainChangeLineId);
                trainDir = GetTrainUnsafeDirection(trainId);

                /*�ж��г����ƶ���Ȩ��Ϣ�Ƿ��ѵ����л������Խ���л���*/
                checkRtn = CheckLocRelationBetweenTwoPoints(trainMaTailLink,trainMaTailOffset,changeLink,changeOffset,trainDir);

                if ((0x02U == checkRtn) || (RETURN_ERROR == checkRtn))
                {
                    /*δԽ��*/
                } 
                else
                {
                    /*Խ��,�����г�Ϊ�ƽ�״̬*/
                    SetTrainStatus(trainId,TRAIN_STATE_HANDOVER);
                }
            } 
            else
            {
                /*������*/
            }
            break;
        case TRAIN_IN_TOEXITCBTC:
               /*������*/
            break;
        case TRAIN_IN_REVERSETOCANCEL:

            if (RETURN_SUCCESS == GetTrainMatchedRouteIdBuff(trainId,routeIdBuff))
            {
                if (LINE_REVERSE_ROUTE == GetRouteType(routeIdBuff[DEFAULT_ZERO]))
                {
                    /*�г���ȫλ���۷���·����*/
                    SetTrainStatus(trainId,TRAIN_STATE_REVERSE);
                } 
                else
                {
                    /*������*/
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
        /*PBW,2016.7.8 ���Ӷ��г��Ѿ�ΪTRAIN_MODE_OUT�Ĵ���*/
        if ((TRAIN_MODE_OUT == trainType) && (TRAIN_IN_TOEXITCBTC == trainInType))
        {
            /*�г���ȫλ���˳�CBTC����*/
            SetTrainStatus(trainId,TRAIN_STATE_CANCELLATION);
            LogPrintf(1U,"22 ExitCbtc:%d,%d",trainInType,GetTrainStatus(trainId));                
        } 

        /*��ΪCBTC�г�*/
        if ((FLAG_UNSET == trainSuspectHead)
            && (DEFAULT_ZERO < matchRouteNum)
            && (RETURN_SUCCESS == checkFlag))
        {
            /*������*/
        } 
        else
        {
            /*���״̬λ*/
            SetTrainStatus(trainId,DEFAULT_ZERO);
            LogPrintf(1U,"15.10 TrainId=%d,SHead=0x%x,%d,%d,Clear TrainStatus!\n",trainId,trainSuspectHead,matchRouteNum,checkFlag);
        }
    }
}

/*************************************************
  ������:      JudgeTrainHandOverTransform
  ��������:    ����STATE_HANDOVER״̬�г�״̬��ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
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
        /*���л���·,ֱ��ת��Ϊ����ģʽ*/
        SetTrainStatus(trainId,TRAIN_STATE_MOVING);
    } 
    else
    {
        /*��ȡ�г���ȫλ��*/
        if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
        {
            changeLink = GetChangeLineChangePointLink(trainChangeLineId);
            changeOffset = GetChangeLineChangePointOffset(trainChangeLineId);
            trainDir = GetTrainUnsafeDirection(trainId);

            checkRtn = CheckLocRelationBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset,
                changeLink,changeOffset,trainDir);

            if (2U == checkRtn)
            {
                /*��βδԽ���ֽ��*/
                if (GetChangeLineHandOverZcId(trainChangeLineId) == GetLocalZcId())
                {
                    /*��ȡ��Ϣ*/
                    trainMaTailLink = GetMaTailLink(trainId);
                    trainMaTailOffset = GetMaTailOffset(trainId);			

                    /*�ж��г����ƶ���Ȩ��Ϣ�Ƿ��ѵ����л������Խ���л���*/
                    checkRtn = CheckLocRelationBetweenTwoPoints(trainMaTailLink,trainMaTailOffset,changeLink,changeOffset,trainDir);

                    if ((0x02U == checkRtn) || (RETURN_ERROR == checkRtn))
                    {
                        /*δԽ��,�������л�����,ת��Ϊ����ģʽ*/
                        SetTrainStatus(trainId,TRAIN_STATE_MOVING);
                    } 
                    else
                    {
                        /*Խ��,ά���ƽ�״̬*/
                    }
                } 
                else
                {
                    /*������*/
                }
            } 
            else
            {
                /*��βԽ���ֽ��*/
                if ((1U == checkRtn) || (3U == checkRtn))
                {
                    if (TRAIN_IN_HANDOVERTOCANCEL == GetTrainInType(trainId))
                    {
                        /*�г������л�ע��,��βԽ�������غ��л���,�����г�״̬Ϊע��״̬*/
                        SetTrainStatus(trainId,TRAIN_STATE_CANCELLATION);
                    } 
                    else
                    {
                        /*�г�δ����ע��,��βԽ���л���,����Ϊ����״̬,���Ϳ�MA,ɾ���г���Ϣ*/
                        /* SetTrainStatus(trainId,TRAIN_STATE_FAILURE); */
                        /* pbw 2017.8.4 ����ӹ�ZCδ����ͨ�� �ó�ά���ƽ�״̬ */
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
  ������:      JudgeTrainTakeOverTransform
  ��������:    ����STATE_TAKEOVER״̬�г�״̬��ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
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

    /*��ȡ�г���Ϣ*/
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
        /*�ж��г��ķǰ�ȫ��ͷ�Ƿ��ѵ�Խ�����л���*/
        unsafeHeadLink = trainUnSafeLocStru.TrainHeadLink;
        unsafeHeadOffset = trainUnSafeLocStru.TrainHeadOffset;

        checkRtn = CheckLocRelationBetweenTwoPoints(unsafeHeadLink,unsafeHeadOffset,changeLink,changeOffset,trainDir);

        if ((0x01U == checkRtn)
            && (TRAIN_IN_APPLY_MA == trainInType)
            && (DEFAULT_ZERO != routeIdBuff[DEFAULT_ZERO])
            && (DEFAULT_ZERO < routeNum))
        {
            /*�г��ǰ�ȫ��ͷԽ���л���,�г������ƶ���Ȩ�����ұ�ZC�ɹ�ƥ���·���г�*/
            if(FLAG_UNSET ==  GetTrainSuspectHead(trainId))
            {
                /* 2017.8.22 ���ǰ��Σ�ձ�ʶ���������� */
                SetTrainStatus(trainId,TRAIN_STATE_MOVING);
            }
            else
            {
                /* ����г�״̬ */
                SetTrainStatus(trainId,DEFAULT_ZERO);
            }           
        } 
        else
        {
            /*��ת��*/
        }
    } 
    else
    {
        /*��ת��*/
    }
    
}

/*************************************************
  ������:      JudgeTrainReverseTransform
  ��������:    ����STATE_REVERSE״̬�г�״̬��ת��
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      ��
*************************************************/
void JudgeTrainReverseTransform(const UINT16_S trainId)
{
    UINT16_S routeIdBuff[SIZE_MAX_ROUTENUM] = {DEFAULT_ZERO};
    UINT8_S trainInType = DEFAULT_ZERO;
    UINT8_S rtnGetMatchedRoute = RETURN_ERROR;
    UINT8_S routeType = DEFAULT_ZERO;

    MemorySet(&routeIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)),
        0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)));

    /*��ȡ�г���Ϣ*/
    rtnGetMatchedRoute = GetTrainMatchedRouteIdBuff(trainId,routeIdBuff);
    routeType = GetRouteType(routeIdBuff[DEFAULT_ZERO]); 

    if ((RETURN_SUCCESS == rtnGetMatchedRoute) 
        && (DEFAULT_ZERO != routeIdBuff[DEFAULT_ZERO]))
    {
        /* �г��������� */
        trainInType = GetTrainInType(trainId);

        /*�۷�״̬��ƥ��ĵ�һ����·��Ϊ�۷���·*/
        if (((TRAIN_IN_CHANGED == trainInType) || (TRAIN_IN_APPLY_MA == trainInType)))
        {
            /*�г����ͻ����������/����δ�յ�������ɶ��յ�����MA,�г�ƥ���·�ɹ�*/
            SetTrainStatus(trainId,TRAIN_STATE_MOVING);
        } 
        else
        {
            /*��ת��*/
        }
    } 
    else
    {
        /*��ת��*/
    }

    LogPrintf(1U,"15.03 TrainId=%d,Status=%d,TrainInType=%d,routeId=%d\n",trainId,GetTrainStatus(trainId),GetTrainInType(trainId),routeIdBuff[DEFAULT_ZERO]);
}

/*************************************************
  ������:      CheckTrainLocSwitchLockState
  ��������:    ��鳵��Χ�ڵĵ�������״̬
  ����:        const UINT16_S trainId,�г�Id
  ���:        ��
  ����ֵ:      0u�������쳣
               1u����������
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

    /*��ȡ�г������Ϣ*/
    locRtn = GetTrainSafeLoc(trainId,&trainSafeLocStru);

    trainDir = GetTrainUnsafeDirection(trainId);

    /*��ѯ�г���ȫλ��ռѹ�ļ���������Ϣ*/
    checkRtn = CheckAcOrderBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainHeadLink,
        trainDir,&acNum,acIdBuff);

    if ((RETURN_SUCCESS == locRtn) && (RETURN_SUCCESS == checkRtn)
        && (DEFAULT_ZERO < acNum))
    {
        /*��ȡ�������ΰ����ĵ���*/
        for (cycle = DEFAULT_ZERO;cycle < acNum;cycle++)
        {
            /*��ȡ�������ΰ����ĵ���*/
            switchNum = GetAcSwitchNum(acIdBuff[cycle]);
            getFlag = GetAcSwitchInfo(acIdBuff[cycle],AC_SWITCH_SUM_MAX,switchInAcStruBuff);
			
            if ((DEFAULT_UINT8_VALUE != switchNum)
                && (RETURN_SUCCESS == getFlag))
            {
                for (cycleSwtich = DEFAULT_ZERO;cycleSwtich < switchNum;cycleSwtich++)
                {
                    if (RETURN_ERROR != GetSwitchLock(switchInAcStruBuff[cycleSwtich].SwitchId))
                    {
                        /*������*/
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
                /*������*/
            }
        }

        if (FLAG_SET == breakFalg)
        {
            /*������*/
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
  ������:      JudgeTrainLocalInChangeLine
  ��������:    ����г��Ƿ�λ�ڱ�ZC�л���·���ƽ�ZC��Χ��
  ����:        const UINT16_S trainId,�г�Id
  ���:        UINT16_S *pOutChangeLineId,������л���·ID
  ����ֵ:      0u��������
               1u������
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

        /*��ȡ�г���ȫλ����Ϣ*/
        if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
        {
            if (GetLineSegBelongZcId(trainSafeLocStru.TrainHeadLink) == GetLocalZcId())
            {
                for (cycle = DEFAULT_ZERO;cycle < GetChangeLineSum();cycle++)
                {
                    changeLineId = GetChangeLineId(cycle);

                    if (RETURN_SUCCESS == CheckPointBelongTocondominiumLineOfHand(changeLineId,trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset))
                    {
                        /*���ڸ��л���·���ƽ�ZC��Χ��*/
                        rtnValue = RETURN_SUCCESS;
                        (*pOutChangeLineId) = changeLineId;
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
                /*�����ڱ�ZC*/
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
  ������:      JudgeTrainInfoOfCiCommFailure
  ��������:    ��������CIͨ�Ź��ϵ��µ��г���Ϣ�仯
  ����:        const UINT16_S ciId,����ID
  ���:        ��
  ����ֵ:      ��
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
                /*�ڱ�CI��Χ�ڵ��г������ƶ�*/
                SetTrainToModeToRM0(trainId);
				LogPrintf(1u,"%d-B70\n",trainId);
            } 
            else
            {
                /*������*/
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
                /*������*/
            }
        }
    }
}

/*************************************************
  ������:      JudgeTrainInfoOfNZcCommFailure
  ��������:    ������������Zcͨ�Ź��ϵ��µ��г���Ϣ�仯
  ����:        const UINT16_S nZcId,����ZcId
  ���:        ��
  ����ֵ:      ��
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
                /*�������ZC���ƶ���Ȩ��Ϣ*/
                DeleteNextZcSingleTrainMaInfo(trainId);

                /*��ѯ�г���ͷ�Ƿ�Խ���ֽ��*/
                if (RETURN_SUCCESS == GetTrainUnSafeLoc(trainId,&trainUnSafeLocStru))
                {
                    changeLink = GetChangeLineChangePointLink(changeLineId);
                    changeOffset = GetChangeLineChangePointOffset(changeLineId);

                    checkRtn = CheckLocRelationBetweenTwoPoints(trainUnSafeLocStru.TrainHeadLink,trainUnSafeLocStru.TrainHeadOffset,changeLink,changeOffset,
                        GetTrainUnsafeDirection(trainId));

                    switch (checkRtn)
                    {
                    case 1U:
                        /*Խ��,������*/
                        break;
                    case 2U:
                    case 3U:
                        /*δԽ��*/
                        if (TRAIN_STATE_HANDOVER == trainStatus)
                        {
                            SetTrainHandoverInType(trainId,NZC_TRAIN_DEFAULT);
                        } 
                        else
                        {
                            /*�ӹ�״̬,��ͷδԽ���л���,���г���Ϣɾ��*/
                            DeleteSingleTrainInfo(trainId);

							/*11.30,���ͨ��״̬��Ϣ*/
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
                    /* ������ */
                }               
            } 
            else
            {
                /* ������ */
            }
        } 
        else
        {
            /*������*/
        }
    }
}

/*************************************************
  ������:      CalculateTrainInChangeLineId
  ��������:    �����г��Ƿ�λ��ĳ���л���·
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void CalculateTrainInChangeLineId(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainCurSum();cycle++)
    {
        /*��ȡ�г�ID*/
        trainId = GetTrainIdOfIndex(cycle);
        trainType = GetTrainType(trainId);

        if ((TRAIN_MODE_CBTC == trainType)
            || (TRAIN_MODE_TO_RM0 == trainType))
        {
            /*��ȡ�г��Ƿ�λ��ĳ���л���·��,�������л���·*/
            SetTrainChangeLineId(trainId , JudgeSignalTrainChangeLineId(trainId));	
        } 
        else
        {
            SetTrainChangeLineId(trainId,DEFAULT_ZERO);
        }
    }
}

/*************************************************
  ������:      JudgeSignalTrainChangeLineId
  ��������:    �����г��Ƿ�λ��ĳ���л���·
  ����:        const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      0u:��λ���л���·��
               >0u:λ���л�������
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

    /*��ȡ�г�������Ϣ*/
    trainDir = GetTrainUnsafeDirection(trainId);
    trainUnsafeHeadAc = GetTrainUnsafeTrainHeadAC(trainId);

    for (cycle = DEFAULT_ZERO;cycle < GetChangeLineSum();cycle++)
    {
        /*��ȡ�л���·ID*/
        changeLineId = GetChangeLineId((UINT16_S)cycle);

        if (trainDir == GetChangeLineDir(changeLineId))
        {
            /*�ж��л���·�ĵ����Ƿ���������*/
            if (RETURN_SUCCESS == CalculateChangeLineSwtichPosInNeed(changeLineId))
            {
                /*��ʼ��*/
                trainOccAcNum = DEFAULT_ZERO;
                MemorySet(trainOccAcIdBuff,sizeof(UINT16_S)*ZC_TWO_POINT_AC_NUM_MAX,DEFAULT_ZERO,sizeof(UINT16_S)*ZC_TWO_POINT_AC_NUM_MAX);

                /*��ȡ�л���·��Ϣ*/
                startLink = GetChangeLineStartLink(changeLineId);
                startOffset = GetChangeLineStartOffset(changeLineId);
                endLink = GetChangeLineChangePointLink(changeLineId);
                endOffset = GetChangeLineChangePointOffset(changeLineId);

                if (RETURN_SUCCESS == CheckAcOrderBetweenTwoPoints(startLink,endLink,trainDir,&trainOccAcNum,trainOccAcIdBuff))
                {
                    if (RETURN_SUCCESS == JudgeSingleAcInAcOrder(trainUnsafeHeadAc,trainOccAcNum,trainOccAcIdBuff))
                    {
                        /*��ѯ�����л���·����*/
                        rtnChangeLineId = changeLineId;
                        break;
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
        else
        {
            /*������*/
        }
    }

    return rtnChangeLineId;
}

/*************************************************
  ������:      CalculateChangeLineSwtichPosInNeed
  ��������:    �����л���·�ĵ����Ƿ�����Ҫ��λ��
  ����:        const UINT16_S changeLineId,�л���·ID
  ���:        ��
  ����ֵ:      0u:������
               1u:����
*************************************************/
UINT8_S CalculateChangeLineSwtichPosInNeed(const UINT16_S changeLineId)
{
    UINT8_S switchNum = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    ChangeLineSwitchStruct switchStruBuff[CHANGE_LINE_SWITCH_MAX]; /*���л���·��Ӧ�ĵ�������*/
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
                    /*������������*/
                } 
                else
                {
                    flag = FLAG_SET;
                    break;
                }
            } 
            else
            {
                /*�����ڱ�ZC*/
            }
        }
    } 
    else
    {
        /*������*/
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
  ������:      JudgeTrainChangeId
  ��������:    ���������г����л���·ID
  ����:        ��
  ���:        ��
  ����ֵ:      ��
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
            /*崻�*/
        }
    }
}

/*************************************************
  ������:      JudgeSingleTrainChangeId
  ��������:    ���ҵ����г���ƥ���ϵ��л���·��ID
  ����:        const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      >0u:�л�����ID
               0u:�����л�����
               0xffu:ʧ��
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

        /*��ѯ��ʼ���ᵽ���������յ�֮��ļ�������*/
        ret = JudgeAcSquToChangeEnd(startAcId,direction,&outAcNum,outAcIdBuff);

        /*�������е��л�����*/
        changeNum = (UINT8_S)(GetChangeLineSum());

        if ((DEFAULT_ZERO < changeNum) && (RETURN_ERROR != direction))
        {	
            for (cycle = 0U;cycle < changeNum;cycle++)
            {
                /*�������е��л�����*/
                changeLineId = GetChangeLineId((UINT16_S)cycle);

                if (direction == GetChangeLineDir(changeLineId))
                {
                    /*��ѯ�л������еļ�������*/
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
                            /*��������*/
                        }
                    }
                    else
                    {
                        /*ʧ��*/
                        rtnValue = DEFAULT_UINT8_VALUE;
                        break;
                    }
                } 
                else
                {
                    /*����һ��,������һ���л���·*/
                }
            }
        }
        else
        {
            /*ʧ��*/
            rtnValue = DEFAULT_UINT8_VALUE;
        }
    }

    return rtnValue;
}

/*************************************************
  ������:      JudgeRelationBetweenAcSqu
  ��������:    �ж�������������֮��Ĺ�ϵ���������1��ȫ����������2�У����سɹ������򣬷���ʧ��
  ����:        const UINT8 acNum1,��������1����
  			   const UINT16_S acSqu1[CHANGE_AREA_AC_MAX]����������1ID
  			   const UINT8_S acNum1,��������2����
     		   const UINT16_S acSqu1[CHANGE_AREA_AC_MAX]����������2ID
  ���:        ��
  ����ֵ:      1u:����
               0u:������
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
                    /*�ҵ���ͬ�ļ��ᣬ����*/
                    sum ++;
                    break;
                }
                else
                {
                    /*��������*/
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
        /* ��������е�2����������:1������1��Ϊ0;2��2����Ϊ0*/
        rtnValue = RETURN_ERROR;
    }
  
    return rtnValue;
}

/*************************************************
  ������:      JudgeSwitchStatusInChangeLine
  ��������:    ���Ҽ��������ڰ����ĵ�������״̬���л�����״̬��һ����
  ����:        const UINT16_S switchSquBuff[CHANGE_LINE_SWITCH_MAX],�����������
  			   const UINT8_S switchNum�������������
  ���:        ��
  ����ֵ:      >0u:���ϵ��л�����ID
               0u: ʧ��
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
            /*�������е��л�����*/
            changeLineId = GetChangeLineId((UINT16_S)cycle1);

            changeDir = GetChangeLineDir(changeLineId);
            /*��ȡ��������������*/
            changeLineSwitchNum = GetChangeLineSwitchStruct(changeLineId,CHANGE_LINE_SWITCH_MAX,changeLineSwitchSquBuff);

            if (DEFAULT_UINT8_VALUE != changeLineSwitchNum)
            {
                checkSwitchNum = 0U;

                for (cycle=0U;cycle<switchNum;cycle++)
                {
                    for (cycle2=0U;cycle2<changeLineSwitchNum;cycle2++)
                    {
                        /*��ȡ����״̬*/
                        switchStatus = GetSwitchStatus(switchSquBuff[cycle]);

                        if ((switchSquBuff[cycle] == changeLineSwitchSquBuff[cycle2].SwitchId) && (changeLineSwitchSquBuff[cycle2].SwitchNeedStatus == switchStatus))
                        {
                            /*��¼�Ѿ��ҵ�����ȷ�ĵ�������*/
                            checkSwitchNum ++;							
                        }
                        else
                        {
                            /*��������*/
                        }
                    }
                }

                if (checkSwitchNum == switchNum)
                {
                    /*˵���ڸ��л������Ѿ��ҵ�ȫ��������״̬��Ҫ��״̬һ�£����л�����Ϊ��Ҫ���л�����*/
                    rtnValue = (UINT8_S)(changeLineId);
                    break;
                }
                else
                {
                    /*�������������л�����*/
                }						
            }
            else 
            {
                /*崻�*/
                rtnValue = 0U;
                break;
            }
        }
    } 
    else
    {
        /*崻�*/
        rtnValue = 0U;
    }
    
    return rtnValue;
}

/*************************************************
  ������:      JudgeSwitchIdInAcSqu
  ��������:    ���Ҽ��������ڰ����ĵ�������
  ����:        const UINT16_S acSquBuff[CHANGE_AREA_AC_MAX], ������������
  			   const UINT8_S acNum, ������������
  ���:        UINT16_S switchSquBuff[CHANGE_LINE_SWITCH_MAX]�������������
               UINT8_S *pSwitchNum�������������
  ����ֵ:      RETURN_SUCCESS:�ɹ�
               RETURN_ERROR: ʧ��
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

            /*��ȡ��������ĵ���*/
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
                /*����ʧ��*/
                rtnValue = RETURN_ERROR;
            }
        }
    } 
    else
    {
        /*����ʧ��*/
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*************************************************
  ������:      JudgetrainStartIdInChange
  ��������:    �����г�λ�ڹ����������ʼ����
  ����:        const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      ��ʼ��������ID
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
        /* ��ͷ��β�����л����� */
        startAcId = GetTrainTrainTailAC(trainId);
        break;
    case 2U:		
        /*��ѯ�г���ȫλ��ռѹ�ļ���������Ϣ*/	
        if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
        {
            checkRtn = CheckAcOrderBetweenTwoPoints(trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainHeadLink,
                trainDir,&acNum,acIdBuff);

            if ((RETURN_SUCCESS == checkRtn)
                && (acNum > 0U))
            {
                /*ȡ������λ�ڹ��������ڵĵ�һ������*/
                for (i = 0U;i < acNum;i++)
                {
                    /*�жϼ����Ƿ�λ���л�������*/
                    ret = JudgeAcIsInChangeLine(acIdBuff[i],trainDir);

                    if (RETURN_SUCCESS == ret)
                    {
                        startAcId = acIdBuff[i];
                        break;
                    }
                    else
                    {
                        /*��������*/
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
  ������:      JudgeTrainLocInChangeLine
  ��������:    �ж��г�λ���л������λ��
  ����:        const UINT16_S trainId,�г�ID
  ���:        ��
  ����ֵ:      0u ʧ��
               1u ��ͷ��β��λ���л�������
               2u ��ͷλ���л������ڣ���β��λ���л�������
               3u ��ͷλ���л������⣬��β��λ���л�������
               4u �г�λ���л�������
*************************************************/
UINT8_S JudgeTrainLocInChangeLine(const UINT16_S trainId)
{
    UINT16_S headAcId = 0U;
    UINT16_S tailAcId = 0U;
    UINT8_S ret1 = 0U;
    UINT8_S ret2 = 0U;
    UINT8_S rtnValue = 0U;
    UINT8_S trainDir = 0U;

    /*��ȡ��ͷռѹ����ID*/
    headAcId = GetTrainTrainHeadAC(trainId);
    tailAcId = GetTrainTrainTailAC(trainId);

    trainDir = GetTrainUnsafeDirection(trainId);

    ret1 = JudgeAcIsInChangeLine(headAcId,trainDir);
    ret2 = JudgeAcIsInChangeLine(tailAcId,trainDir);	

    if ((RETURN_SUCCESS == ret1) && (RETURN_SUCCESS == ret2))
    {
        /*˵����ͷ��β��λ���л�������*/
        rtnValue = 1U;
    }
    else if ((RETURN_SUCCESS == ret1) && (RETURN_ERROR == ret2))
    {
        /*˵����ͷλ���л������ڣ���β��λ���л�������*/
        rtnValue = 2U;
    }
    else if ((RETURN_ERROR == ret1) && (RETURN_SUCCESS == ret2))
    {
        /*˵����ͷλ���л������⣬��β��λ���л�������*/
        rtnValue = 3U;
    }
    else if ((RETURN_ERROR == ret1) && (RETURN_ERROR == ret2))
    {
        /*�г�λ���л�������*/
        rtnValue = 4U;
    }
    else
    {
        /*ʧ��*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*************************************************
  ������:      JudgeAcSquToChangeEnd
  ��������:    ��ȡָ�����ᵽ�л������ն˵ļ�������
  ����:        const UINT16_S acId  ��ʼ����ID
               const UINT8_S direction ����
  ���:        UINT8_S *pOutAcNum ���ؼ�������
               UINT16_S acSquBuff[CHANGE_AREA_AC_MAX] ���ؼ�������
  ����ֵ:      RETURN_ERROR ʧ��
               RETURN_SUCCESS �ɹ�
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
        /*�ж���ʼ���᱾���Ƿ������л������ն�*/
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

            /*��д�г�ռѹ��������*/
            acSquBuff[acNum] = acId;
            acNum = acNum + 1U;

            for (cycle=0U;cycle < CHANGE_AREA_AC_MAX;cycle++)
            {
                /*��ȡָ���������һ����*/
                if (RETURN_SUCCESS == CheckFrontACStatus(startAcId,direction,&nextAcId))
                {
                    /*д��ü�������*/
                    acSquBuff[acNum] = nextAcId;
                    acNum = acNum + 1U;

                    /*�жϸü����Ƿ�Ϊ�յ����*/
                    rtnOfJudgeACIsChangeEnd = JudgeACIsChangeEnd(nextAcId,direction);

                    if (FLAG_SET == rtnOfJudgeACIsChangeEnd)
                    {
                        rtnValue = RETURN_SUCCESS;
                        break;
                    }
                    else if (FLAG_UNSET == rtnOfJudgeACIsChangeEnd)
                    {
                        /*��������*/
                        startAcId = nextAcId;
                    }
                    else
                    {
                        /*ʧ��*/
                        rtnValue = 0U;
                        break;
                    }
                }
                else
                {
                    /*�Ҳ������ڼ��ᣬ����*/
                    rtnValue = RETURN_SUCCESS;
                    break;
                }
            }
        }
        else
        {
            /*ʧ��*/
            rtnValue = RETURN_ERROR;
        }

        (*pOutAcNum) = acNum;
    } 
    else
    {
        /*ʧ��*/
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*************************************************
  ������:      ManageDeleteTrainInfo
  ��������:    ������Ҫɾ���г���Ϣ����������Ҫɾ�����г�����ɾ����
  ����:        ��
  ���:        ��
  ����ֵ:      ��
*************************************************/
void ManageDeleteTrainInfo(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT8_S trainState = DEFAULT_ZERO;
    UINT16_S needDeleteMaNum = DEFAULT_ZERO;
    UINT16_S needDeleteMaIdBuff[COMM_TRAIN_SUM_MAX] = {0U};
    UINT8_S trainInType = DEFAULT_ZERO;   /* �г������ZC����Ϣ */

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
            /*��¼���г�ID*/
            needDeleteMaIdBuff[needDeleteMaNum] = trainId;
            needDeleteMaNum++;
        } 
        else
        {
            /*������*/
        }
    }

    for (cycle = 0U;cycle < needDeleteMaNum;cycle++)
    {
        /*����г���Ϣ*/
        DeleteSingleTrainInfo(needDeleteMaIdBuff[cycle]);

		/*11.30,���ͨ��״̬��Ϣ*/
		ClearOneTrainCommCycleAndStatus(needDeleteMaIdBuff[cycle]);

        /* pbw 2017.6.5 */
        /*ɾ������ZC�����MA��Ϣ*/
        DeleteNextZcSingleTrainMaInfo(needDeleteMaIdBuff[cycle]);
    }
}
