/********************************************************                                                                                                            
 �� �� ���� TrainStatusData.c   
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015-07-01
 ������ �г�״̬���ݹ���  
 ��ע�� ��  
********************************************************/
#include "TrainStatusData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../../Common/Copy.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

TrainInfoStruct gTrainStatusDataStruBuff[SIZE_MAX_CONTROLE_TRAIN];   /*���屾ZC���Ʒ�Χ������г�����*/
UINT8_S gLocalTrainIndexBuff[SIZE_MAX_LINE_TRAIN] = {0U};			 /*�����г��������飬���鳤��Ϊ��·���ܵ�����г�ID*/
UINT8_S gTrainCurSum = 0U;									         /*��ZC��ǰ�г�����*/


/*************************************************
  ������:      GetTrainCurSum
  ��������:    ��ȡָ���г�ID������
  ����:        ��
  ���:        ��
  ����ֵ:      0U: ��ȡ����ʧ��
               <SIZE_MAX_CONTROLE_TRAIN: ���ҳɹ�
*************************************************/
UINT8_S GetTrainCurSum(void)
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (SIZE_MAX_CONTROLE_TRAIN < gTrainCurSum)
    {
        rtnValue = 0U;		
    }
    else
    {
        rtnValue = gTrainCurSum;
    }
    return rtnValue;
}

/*************************************************
  ������:      GetSingalTrainInfoOfIndex
  ��������:    ��ȡָ���г��г���Ϣ�׵�ַ
  ����:        const UINT16_S index, �����±�
  ���:        ��
  ����ֵ:      Null: ��ȡ����ʧ��
               >0: �����г���Ϣ�׵�ַ
*************************************************/
TrainInfoStruct* GetSingalTrainInfoOfIndex(const UINT16_S index)
{
    TrainInfoStruct *pRtnValue = NULL;

    if (SIZE_MAX_CONTROLE_TRAIN <= index)
    {
        pRtnValue = NULL;		
    }
    else
    {
        pRtnValue = &gTrainStatusDataStruBuff[index];
    }

    return pRtnValue;
}

/*************************************************
  ������:      GetTrainIdOfIndex
  ��������:    ��ȡָ�������ŵ��г�ID
  ����:        const UINT8_S index, �г�ID���±�
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               <SIZE_MAX_CONTROLE_TRAIN: ���ҳɹ�
*************************************************/
UINT16_S GetTrainIdOfIndex(const UINT8_S index)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (SIZE_MAX_CONTROLE_TRAIN <= index)
    {
        rtnValue = RETURN_ERROR;		
    }
    else
    {
        rtnValue = gTrainStatusDataStruBuff[index].TrainID;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainStatusBufIndex
  ��������:    ��ȡָ���г�ID������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               <SIZE_MAX_LINE_TRAIN: ���ҳɹ�
*************************************************/
UINT8_S GetTrainStatusBufIndex(const UINT16_S trainId)
{
    UINT8_S rtnIndex = RETURN_UINT8_MAX_VALUE;

    if ((1U <= trainId) && (trainId < SIZE_MAX_LINE_TRAIN))
    {
        rtnIndex = gLocalTrainIndexBuff[trainId];
    }

    return rtnIndex;
}

/*************************************************
  ������:      GetSingleTrainInfo
  ��������:    ��ȡָ���г�ID�г���Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        TrainInfoStruct *pSingleTrainInfo, �г���Ϣ�ṹ��
  ����ֵ:      RETURN_ERROR:   ��ȡ����ʧ��
               RETURN_SUCCESS: ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetSingleTrainInfo(const UINT16_S trainId,TrainInfoStruct *pSingleTrainInfo)
{
    UINT8_S rtnIndex = 0U;
    UINT8_S getBufIndex = 0U;

    getBufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != getBufIndex) && (NULL != pSingleTrainInfo))
    {
        MemoryCpy(pSingleTrainInfo,(UINT32_S)(sizeof(TrainInfoStruct)),&gTrainStatusDataStruBuff[getBufIndex],(UINT32_S)(sizeof(TrainInfoStruct)));
        rtnIndex = RETURN_SUCCESS;
    }
    else
    {
        rtnIndex = RETURN_ERROR;
    }

    return rtnIndex;
}

/*************************************************
  ������:      SetSingleTrainNextZcInputDataInfo
  ��������:    ��������ZC�����ָ���г�ID�г���Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const TrainInfoStruct *pSingleTrainInfo, �г���Ϣ�ṹ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��������ʧ��
               RETURN_SUCCESS: �������ݳɹ�
*************************************************/
UINT8_S SetSingleTrainNextZcInputDataInfo(const UINT16_S trainId,const TrainInfoStruct *pSingleTrainInfo)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S getBufIndex = 0U;
    UINT8_S trainIndex = DEFAULT_ZERO;
    UINT8_S copyRtn = DEFAULT_ZERO;

    getBufIndex = AllotTrainIndex(trainId);

    if ((SIZE_MAX_CONTROLE_TRAIN != getBufIndex) && (NULL != pSingleTrainInfo))
    {
        trainIndex = GetTrainStatusBufIndex(trainId);

        if (RETURN_UINT8_MAX_VALUE == trainIndex)
        {
            /*�г���������*/
            gTrainCurSum++;
            gLocalTrainIndexBuff[trainId] = getBufIndex;
        } 
        else
        {
            /*������*/
        }

        /*��������*/
        gTrainStatusDataStruBuff[getBufIndex].TrainID = trainId;
        gTrainStatusDataStruBuff[getBufIndex].TrainType = pSingleTrainInfo->TrainType;
        gTrainStatusDataStruBuff[getBufIndex].TrainControlZC = pSingleTrainInfo->TrainControlZC;
        gTrainStatusDataStruBuff[getBufIndex].TrainCycle = pSingleTrainInfo->TrainCycle;
        gTrainStatusDataStruBuff[getBufIndex].SuspectHead = pSingleTrainInfo->SuspectHead;
        gTrainStatusDataStruBuff[getBufIndex].SuspectTail = pSingleTrainInfo->SuspectTail;
        gTrainStatusDataStruBuff[getBufIndex].TrainHeadAC = pSingleTrainInfo->TrainHeadAC;
        gTrainStatusDataStruBuff[getBufIndex].TrainTailAC = pSingleTrainInfo->TrainTailAC;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnsafeHeadAC = pSingleTrainInfo->TrainUnsafeHeadAC;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnsafeTailAC = pSingleTrainInfo->TrainUnsafeTailAC;
        gTrainStatusDataStruBuff[getBufIndex].TrainFrontSignal = pSingleTrainInfo->TrainFrontSignal;
        gTrainStatusDataStruBuff[getBufIndex].SignalProtection = pSingleTrainInfo->SignalProtection;

        gTrainStatusDataStruBuff[getBufIndex].TrainSafeLocStru.TrainHeadLink = pSingleTrainInfo->TrainSafeLocStru.TrainHeadLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainSafeLocStru.TrainHeadOffset = pSingleTrainInfo->TrainSafeLocStru.TrainHeadOffset;
        gTrainStatusDataStruBuff[getBufIndex].TrainSafeLocStru.TrainTailLink = pSingleTrainInfo->TrainSafeLocStru.TrainTailLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainSafeLocStru.TrainTailOffset = pSingleTrainInfo->TrainSafeLocStru.TrainTailOffset;

        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainHeadLink = pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainHeadOffset = pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadOffset;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainTailLink = pSingleTrainInfo->TrainUnSafeLocStru.TrainTailLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainTailOffset = pSingleTrainInfo->TrainUnSafeLocStru.TrainTailOffset;

        gTrainStatusDataStruBuff[getBufIndex].TrainError = pSingleTrainInfo->TrainError;
        gTrainStatusDataStruBuff[getBufIndex].TrainRealDirection = pSingleTrainInfo->TrainRealDirection;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnsafeDirection = pSingleTrainInfo->TrainUnsafeDirection;
        gTrainStatusDataStruBuff[getBufIndex].TrainMode = pSingleTrainInfo->TrainMode;
        gTrainStatusDataStruBuff[getBufIndex].TrainLevel = pSingleTrainInfo->TrainLevel;
        gTrainStatusDataStruBuff[getBufIndex].TrainSpeed = pSingleTrainInfo->TrainSpeed;
        gTrainStatusDataStruBuff[getBufIndex].TrainStopArea = pSingleTrainInfo->TrainStopArea;
        gTrainStatusDataStruBuff[getBufIndex].TrainEmergency = pSingleTrainInfo->TrainEmergency;
        gTrainStatusDataStruBuff[getBufIndex].TrainIntegrity = pSingleTrainInfo->TrainIntegrity;	

        /* LogPrintf(1U,"20.002 train=%d,U[%d,%d;%d,%d],S[%d,%d,%d,%d];getBufIndex=%d\n",trainId,
        pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadLink,pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadOffset,
        pSingleTrainInfo->TrainUnSafeLocStru.TrainTailLink,pSingleTrainInfo->TrainUnSafeLocStru.TrainTailOffset,
        pSingleTrainInfo->TrainSafeLocStru.TrainHeadLink,pSingleTrainInfo->TrainSafeLocStru.TrainHeadOffset,
        pSingleTrainInfo->TrainSafeLocStru.TrainTailLink,pSingleTrainInfo->TrainSafeLocStru.TrainTailOffset,
        getBufIndex); */


        rtnValue =  RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetSingleTrainInputDataInfo
  ��������:    �����г�������Ϣ��ָ���г�ID�г���Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const TrainInfoStruct *pSingleTrainInfo, �г���Ϣ�ṹ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��������ʧ��
               RETURN_SUCCESS: �������ݳɹ�
*************************************************/
UINT8_S SetSingleTrainInputDataInfo(const UINT16_S trainId,const TrainInfoStruct *pSingleTrainInfo)
{
    UINT8_S rtnIndex = 0U;
    UINT8_S getBufIndex = 0U;
    UINT8_S trainIndex = DEFAULT_ZERO;

    /* �����±� */
    getBufIndex = AllotTrainIndex(trainId);

    if ((SIZE_MAX_CONTROLE_TRAIN != getBufIndex) && (NULL != pSingleTrainInfo))
    {
        trainIndex = GetTrainStatusBufIndex(trainId);

        if (RETURN_UINT8_MAX_VALUE == trainIndex)
        {
            /*�г���������*/
            gTrainCurSum++;
            gLocalTrainIndexBuff[trainId] = getBufIndex;
        } 
        else
        {
            /*������*/
        }

        /*��������*/
        gTrainStatusDataStruBuff[getBufIndex].TrainID = trainId;
        gTrainStatusDataStruBuff[getBufIndex].TrainInType = pSingleTrainInfo->TrainInType;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainHeadLink = pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainHeadOffset = pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadOffset;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainTailLink = pSingleTrainInfo->TrainUnSafeLocStru.TrainTailLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainTailOffset = pSingleTrainInfo->TrainUnSafeLocStru.TrainTailOffset;
        gTrainStatusDataStruBuff[getBufIndex].TrainRealDirection = pSingleTrainInfo->TrainRealDirection;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnsafeDirection = pSingleTrainInfo->TrainUnsafeDirection;
        gTrainStatusDataStruBuff[getBufIndex].TrainMode = pSingleTrainInfo->TrainMode;
        gTrainStatusDataStruBuff[getBufIndex].TrainLevel = pSingleTrainInfo->TrainLevel;
        gTrainStatusDataStruBuff[getBufIndex].TrainSpeed = pSingleTrainInfo->TrainSpeed;
        gTrainStatusDataStruBuff[getBufIndex].TrainStopArea = pSingleTrainInfo->TrainStopArea;
        gTrainStatusDataStruBuff[getBufIndex].TrainError = pSingleTrainInfo->TrainError;
        gTrainStatusDataStruBuff[getBufIndex].TrainEmergency = pSingleTrainInfo->TrainEmergency;
        gTrainStatusDataStruBuff[getBufIndex].TrainIntegrity = pSingleTrainInfo->TrainIntegrity;
        gTrainStatusDataStruBuff[getBufIndex].TrainControlZC = pSingleTrainInfo->TrainControlZC;
        gTrainStatusDataStruBuff[getBufIndex].TrainCycle = pSingleTrainInfo->TrainCycle;

        /*Ϊ�˽�����������,*/
        gTrainStatusDataStruBuff[getBufIndex].SignalProtection =FLAG_UNSET;

        /*LogPrintf(1U,"20.001 train=%d,%d,%d;%d,%d;getBufIndex=%d\n",trainId,pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadLink,
        pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadOffset,pSingleTrainInfo->TrainUnSafeLocStru.TrainTailLink,
        pSingleTrainInfo->TrainUnSafeLocStru.TrainTailOffset,getBufIndex);*/

        rtnIndex = RETURN_SUCCESS;
    }
    else
    {
        rtnIndex = RETURN_ERROR;
    }

    return rtnIndex;
}

/*************************************************
  ������:      GetTrainControlZc
  ��������:    ��ȡָ���г��ܿ�ZC
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               <RETURN_UINT8_MAX_VALUE: ��ȡ���ݳɹ�
*************************************************/
UINT16_S GetTrainControlZc(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainControlZC;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainControlZc
  ��������:    ����ָ���г��ܿ�ZC
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S zcId, ZC�ı��
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��������ʧ��
               RETURN_SUCCESS: �������ݳɹ�
*************************************************/
UINT8_S SetTrainControlZc(const UINT16_S trainId,const UINT16_S zcId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainControlZC = zcId;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainCycle
  ��������:    ��ȡָ���г����ں�
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡ����ʧ��
               >0:             ��ȡ���ݳɹ�
*************************************************/
UINT32_S GetTrainCycle(const UINT16_S trainId)
{
    UINT32_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainCycle;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainCycle
  ��������:    ����ָ���г����ں�
  ����:        const UINT16_S trainId, �г�ID
               const UINT32_S trainCycle�� �г����ں�
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainCycle(const UINT16_S trainId,const UINT32_S trainCycle)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainCycle = trainCycle;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainType
  ��������:    ��ȡָ���г�����
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainType(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainType;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainType
  ��������:    ����ָ���г�����
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainType, �г�����
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainType(const UINT16_S trainId,const UINT8_S trainType)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainType = trainType;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainSuspectHead
  ��������:    ��ȡָ���г�ǰ�˿��ɱ�־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainSuspectHead(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].SuspectHead;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainSuspectHead
  ��������:    ����ָ���г�ǰ�˿��ɱ�־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S suspectHead, �г�ǰ�˿��ɱ�־
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainSuspectHead(const UINT16_S trainId,const UINT8_S suspectHead)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].SuspectHead = suspectHead;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainSuspectTail
  ��������:    ��ȡָ���г���˿��ɱ�־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainSuspectTail(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].SuspectTail;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainSuspectTail
  ��������:    ����ָ���г���˿��ɱ�־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S suspectTail, �г���˿��ɱ�־
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainSuspectTail(const UINT16_S trainId,const UINT8_S suspectTail)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].SuspectTail = suspectTail;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainTrainHeadAC
  ��������:    ��ȡָ���г���ͷ���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡ����ʧ��
               >0:             ���óɹ�
*************************************************/
UINT16_S GetTrainTrainHeadAC(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainHeadAC;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainTrainHeadAC
  ��������:    ����ָ���г���ͷ���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainHeadAC, ��ͷ���ڵļ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainTrainHeadAC(const UINT16_S trainId,const UINT16_S trainHeadAC)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainHeadAC = trainHeadAC;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainTrainTailAC
  ��������:    ��ȡָ���г���β���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT16_S GetTrainTrainTailAC(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainTailAC;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainTrainTailAC
  ��������:    ����ָ���г���β���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainTailAC, �г���β���ڼ���
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainTrainTailAC(const UINT16_S trainId,const UINT16_S trainTailAC)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainTailAC = trainTailAC;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainUnsafeTrainHeadAC
  ��������:    ��ȡָ���г��ǰ�ȫ��ͷ���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT16_S GetTrainUnsafeTrainHeadAC(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainUnsafeHeadAC;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainUnsafeTrainHeadAC
  ��������:    ����ָ���г��ǰ�ȫ��ͷ���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainUnsafeHeadAC, �г��ǰ�ȫ��ͷ���ڼ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainUnsafeTrainHeadAC(const UINT16_S trainId,const UINT16_S trainUnsafeHeadAC)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainUnsafeHeadAC = trainUnsafeHeadAC;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainUnsafeTrainTailAC
  ��������:    ��ȡָ���г��ǰ�ȫ��β���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               RETURN_SUCCESS: ��ȡ�ɹ�
*************************************************/
UINT16_S GetTrainUnsafeTrainTailAC(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainUnsafeTailAC;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainUnsafeTrainTailAC
  ��������:    ��ȡָ���г��ǰ�ȫ��β���ڼ�������
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainUnsafeTailAC, �г��ǰ�ȫ��β���ڼ�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainUnsafeTrainTailAC(const UINT16_S trainId,const UINT16_S trainUnsafeTailAC)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainUnsafeTailAC = trainUnsafeTailAC;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainFrontSignal
  ��������:    ��ȡָ���г�ǰ����Ҫ�����źŻ�
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT16_S GetTrainFrontSignal(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainFrontSignal;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainFrontSignal
  ��������:    ����ָ���г�ǰ����Ҫ�����źŻ�
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainFrontSignal, �г�ǰ���źŻ�
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ����ʧ��
               RETURN_SUCCESS: ���óɹ�
*************************************************/
UINT8_S SetTrainFrontSignal(const UINT16_S trainId,const UINT16_S trainFrontSignal)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainFrontSignal = trainFrontSignal;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainSignalProtection
  ��������:    ��ȡָ���г����źű�־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:   ��ȡʧ��
               >0:             ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainSignalProtection(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].SignalProtection;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainSignalProtection
  ��������:    ����ָ���г����źű�־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S signalProtection, �г����źŻ�������־
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainSignalProtection(const UINT16_S trainId,const UINT8_S signalProtection)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].SignalProtection = signalProtection;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainCommStatus
  ��������:    ��ȡָ���г�ͨ����·״̬
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ��ȡʧ��
               >0:              ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainCommStatus(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].CommStatus;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainCommStatus
  ��������:    ����ָ���г�ͨ����·״̬
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S commStatus, �г�ͨ����·״̬
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainCommStatus(const UINT16_S trainId,const UINT8_S commStatus)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].CommStatus = commStatus;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainCommRedundancy
  ��������:    ��ȡָ���г�ͨ�ż�ʱλ
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ��ȡʧ��
               >0:              ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainCommRedundancy(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].CommRedundancy;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainCommRedundancy
  ��������:    ����ָ���г�ͨ�ż�ʱλ
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S commRedundancy, �г�ͨ�ż�ʱλ
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainCommRedundancy(const UINT16_S trainId,const UINT8_S commRedundancy)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].CommRedundancy = commRedundancy;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainPrtclDelay
  ��������:    ��ȡָ���г�ͨ��Э���ӳ�ʱ��
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ��ȡʧ��
               >0:              ��ȡ�ɹ�
*************************************************/
UINT8_S GetTrainPrtclDelay(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].PrtclDelay;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainPrtclDelay
  ��������:    ����ָ���г�ͨ��Э���ӳ�ʱ��
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S prtclDelay, �г�ͨ��Э���ӳ�ʱ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainPrtclDelay(const UINT16_S trainId,const UINT8_S prtclDelay)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].PrtclDelay = prtclDelay;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainStatus
  ��������:    ��ȡָ���г�״̬
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainStatus(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainStatus;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainPrtclDelay
  ��������:    ����ָ���г�״̬
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainStatus, �г��г�״̬
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainStatus(const UINT16_S trainId,const UINT8_S trainStatus)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainStatus = trainStatus;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainInType
  ��������:    ��ȡָ���г���������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainInType(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainInType;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainInType
  ��������:    ����ָ���г���������
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainInType, �г���������
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainInType(const UINT16_S trainId,const UINT8_S trainInType)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainInType = trainInType;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainOutType
  ��������:    ��ȡָ���г��������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainOutType(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainOutType;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainOutType
  ��������:    ����ָ���г��������
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainOutType, �г��������
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainOutType(const UINT16_S trainId,const UINT8_S trainOutType)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainOutType = trainOutType;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainHandoverInType
  ��������:    ��ȡָ������ZC��������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainHandoverInType(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].HandoverInType;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainHandoverInType
  ��������:    ����ָ���г�����ZC��������
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S handoverInType, �г�����ZC��������
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainHandoverInType(const UINT16_S trainId,const UINT8_S handoverInType)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].HandoverInType = handoverInType;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainHandoverOutType
  ��������:    ��ȡָ������ZC�������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainHandoverOutType(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_UINT8_MAX_VALUE;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].HandoverOutType;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainHandoverOutType
  ��������:    ����ָ���г�����ZC�������
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S handoverOutType, �г�����ZC�������
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainHandoverOutType(const UINT16_S trainId,const UINT8_S handoverOutType)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].HandoverOutType = handoverOutType;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainUnsafeDirection
  ��������:    ��ȡָ���г��������з���
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainUnsafeDirection(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainUnsafeDirection;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainUnsafeDirection
  ��������:    ����ָ���г��������з���
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainUnsafeDirection, �г��������з���
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainUnsafeDirection(const UINT16_S trainId,const UINT8_S trainUnsafeDirection)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainUnsafeDirection = trainUnsafeDirection;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainRealDirection
  ��������:    ��ȡָ���г�ʵ�����з���
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainRealDirection(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainRealDirection;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainRealDirection
  ��������:    ����ָ���г�ʵ�����з���
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainRealDirection, �г�ʵ�����з���
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainRealDirection(const UINT16_S trainId,const UINT8_S trainRealDirection)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainRealDirection = trainRealDirection;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainMode
  ��������:    ��ȡָ���г�ģʽ
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainMode(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainMode;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainMode
  ��������:    ����ָ���г�ģʽ
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainMode, �г��г�ģʽ
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainMode(const UINT16_S trainId,const UINT8_S trainMode)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainMode = trainMode;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainLevel
  ��������:    ��ȡָ���г�����
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainLevel(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainLevel;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainMode
  ��������:    ����ָ���г�����
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainLevel, �г��г�����
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainLevel(const UINT16_S trainId,const UINT8_S trainLevel)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainLevel = trainLevel;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainSpeed
  ��������:    ��ȡָ���г��ٶ�
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT16_S GetTrainSpeed(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_UINT16_MAX_VALUE;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainSpeed;
    }

    return rtnValue;
}  

/*************************************************
  ������:      SetTrainSpeed
  ��������:    ����ָ���г��ٶ�
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainSpeed, �г��ٶ�
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainSpeed(const UINT16_S trainId,const UINT16_S trainSpeed)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainSpeed = trainSpeed;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainStopArea
  ��������:    ��ȡָ���г�ͣ�ȱ�־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainStopArea(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainStopArea;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainStopArea
  ��������:    ����ָ���г�ͣ�ȱ�־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainStopArea, �г�ͣ�ȱ�־
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainStopArea(const UINT16_S trainId,const UINT8_S trainStopArea)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainStopArea = trainStopArea;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainEmergency
  ��������:    ��ȡָ���г������Ա�־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainIntegrity(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainIntegrity;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainIntegrity
  ��������:    ����ָ���г������Ա�־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainIntegrity, �г������Ա�־
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainIntegrity(const UINT16_S trainId,const UINT8_S trainIntegrity)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainIntegrity = trainIntegrity;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainEmergency
  ��������:    ��ȡָ���г�����ͣ����־
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR: ��ȡ����ʧ��
               >0:           ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainEmergency(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainEmergency;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainEmergency
  ��������:    ����ָ���г�����ͣ����־
  ����:        const UINT16_S trainId, �г�ID
               const UINT8_S trainEmergency, �г�����ͣ����־
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainEmergency(const UINT16_S trainId,const UINT8_S trainEmergency)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainEmergency = trainEmergency;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetMatchRouteNum
  ��������:    ��ȡָ���г���ƥ���·����
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      >=0,����
*************************************************/
UINT8_S GetMatchRouteNum(const UINT16_S trainId)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].MatchRouteNum;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainMatchedRouteIdBuff
  ��������:    ��ȡָ���г���ƥ���·��Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        UINT16_S routeIdBuff[], ƥ��Ľ�·�ı��
  ����ֵ:      RETURN_ERROR:    ��ȡ����ʧ��
               RETURN_SUCCESS:  ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainMatchedRouteIdBuff(const UINT16_S trainId,UINT16_S routeIdBuff[])
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;
    UINT8_S k = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex) &&(NULL != routeIdBuff))
    {
        for(k=0U;k<SIZE_MAX_ROUTENUM;k++)
        {
            routeIdBuff[k] = gTrainStatusDataStruBuff[bufIndex].MatchedRouteIDBuff[k];
        }
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainMatchedLastRouteId
  ��������:    ��ȡָ���г���ƥ������һ����·��Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        UINT16_S *pLastRouteId, ���һ����·Id
  ����ֵ:      RETURN_ERROR:    ��ȡ����ʧ��
               RETURN_SUCCESS:  ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainMatchedLastRouteId(const UINT16_S trainId,UINT16_S *pLastRouteId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;
    UINT8_S routeNum = DEFAULT_ZERO;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (NULL != pLastRouteId)
    {
        if ((RETURN_UINT8_MAX_VALUE != bufIndex) )
        {
            routeNum = gTrainStatusDataStruBuff[bufIndex].MatchRouteNum;

            if ((SIZE_MAX_ROUTENUM >= routeNum) && (DEFAULT_ZERO < routeNum))
            {
                (*pLastRouteId) = gTrainStatusDataStruBuff[bufIndex].MatchedRouteIDBuff[routeNum - 1U];
                rtnValue = RETURN_SUCCESS;
            } 
            else
            {
                (*pLastRouteId) = 0U;
                rtnValue = RETURN_ERROR;
            }

        }
        else
        {
            (*pLastRouteId) = 0U;
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
  ������:      SetTrainMatchedRouteIdBuf
  ��������:    ����ָ���г���ƥ���·��Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S routeIdBuff[] ��·ID����
               const UINT8_S routeNum ��·����
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainMatchedRouteIdBuf(const UINT16_S trainId,const UINT16_S routeIdBuff[],const UINT8_S routeNum)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;
    UINT8_S k = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex)
        && (routeNum <= SIZE_MAX_ROUTENUM) && (NULL != routeIdBuff))
    {
        gTrainStatusDataStruBuff[bufIndex].MatchRouteNum = 0U;

        if (DEFAULT_ZERO == routeNum)
        {
            for(k=0U;k<SIZE_MAX_ROUTENUM;k++)
            {
                gTrainStatusDataStruBuff[bufIndex].MatchedRouteIDBuff[k] = DEFAULT_ZERO;
            }
        } 
        else
        {
            for(k=0U;k<routeNum;k++)
            {
                gTrainStatusDataStruBuff[bufIndex].MatchedRouteIDBuff[k] = routeIdBuff[k];
                gTrainStatusDataStruBuff[bufIndex].MatchRouteNum++;
            }
        }

        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainSafeLoc
  ��������:    ��ȡָ���г��л���·ID
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ��ȡ����ʧ��
               >0:              ��ȡ���ݳɹ�
*************************************************/
UINT16_S GetTrainChangeLineId(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].ChangeLineId;
    }

    return rtnValue;
}  

/*************************************************
  ������:      SetTrainChangeLineId
  ��������:    ����ָ���г��л���·ID
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S changeLineId, �г��л���·ID
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainChangeLineId(const UINT16_S trainId,const UINT16_S changeLineId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].ChangeLineId = changeLineId;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainSafeLoc
  ��������:    ��ȡָ���г���ȫλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        TrainSafeLocStruct *pTrainSafeLocStru, �г�λ����Ϣ�ṹ��
  ����ֵ:      RETURN_ERROR:    ��ȡ����ʧ��
               RETURN_SUCCESS:  ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainSafeLoc(const UINT16_S trainId,TrainSafeLocStruct *pTrainSafeLocStru)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;


    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex)
        && (NULL != pTrainSafeLocStru))
    {
        pTrainSafeLocStru->TrainHeadLink = gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadLink;
        pTrainSafeLocStru->TrainHeadOffset = gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadOffset;
        pTrainSafeLocStru->TrainTailLink = gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailLink;
        pTrainSafeLocStru->TrainTailOffset = gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailOffset;

        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainSafeLoc
  ��������:    ����ָ���г���ȫλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
               TrainSafeLocStruct *pTrainSafeLocStru, �г�λ�ýṹ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainSafeLoc(const UINT16_S trainId,const TrainSafeLocStruct *pTrainSafeLocStru)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex)
        && (NULL != pTrainSafeLocStru))
    {
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadLink = pTrainSafeLocStru->TrainHeadLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadOffset = pTrainSafeLocStru->TrainHeadOffset;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailLink = pTrainSafeLocStru->TrainTailLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailOffset = pTrainSafeLocStru->TrainTailOffset;
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainSafeHeadLoc
  ��������:    ����ָ���г���ȫ��ͷλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainSafeHeadLink, ��ȫ��ͷlink
               const UINT32_S trainSafeHeadOffset, ��ȫ��ͷoffset
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainSafeHeadLoc(const UINT16_S trainId,const UINT16_S trainSafeHeadLink,const UINT32_S trainSafeHeadOffset)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;


    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadLink = trainSafeHeadLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadOffset = trainSafeHeadOffset;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainSafeTailLoc
  ��������:    ����ָ���г���ȫ��βλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainSafeTailLink, ��ȫ��βlink
               const UINT32_S trainSafeTailOffset, ��ȫ��βoffset
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainSafeTailLoc(const UINT16_S trainId,const UINT16_S trainSafeTailLink,const UINT32_S trainSafeTailOffset)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;


    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailLink = trainSafeTailLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailOffset = trainSafeTailOffset;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainUnSafeLoc
  ��������:    ��ȡָ���г��ǰ�ȫλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        TrainSafeLocStruct *pTrainUnSafeLocStru, �г�λ����Ϣ�ṹ��
  ����ֵ:      RETURN_ERROR:    ��ȡ����ʧ��
               RETURN_SUCCESS:  ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainUnSafeLoc(const UINT16_S trainId,TrainSafeLocStruct *pTrainUnSafeLocStru)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex)
        && (NULL != pTrainUnSafeLocStru))
    {
        pTrainUnSafeLocStru->TrainHeadLink = gTrainStatusDataStruBuff[bufIndex].TrainUnSafeLocStru.TrainHeadLink;
        pTrainUnSafeLocStru->TrainHeadOffset = gTrainStatusDataStruBuff[bufIndex].TrainUnSafeLocStru.TrainHeadOffset;
        pTrainUnSafeLocStru->TrainTailLink = gTrainStatusDataStruBuff[bufIndex].TrainUnSafeLocStru.TrainTailLink;
        pTrainUnSafeLocStru->TrainTailOffset = gTrainStatusDataStruBuff[bufIndex].TrainUnSafeLocStru.TrainTailOffset;
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainUnSafeLoc
  ��������:    ����ָ���г��ǰ�ȫλ����Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const TrainSafeLocStruct trainUnSafeLocStru, λ����Ϣ�ṹ��
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainUnSafeLoc(const UINT16_S trainId,const TrainSafeLocStruct trainUnSafeLocStru)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadLink = trainUnSafeLocStru.TrainHeadLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadOffset = trainUnSafeLocStru.TrainHeadOffset;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailLink = trainUnSafeLocStru.TrainTailLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailOffset = trainUnSafeLocStru.TrainTailOffset;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainError
  ��������:    ��ȡָ���г�ID��ȷ�����
  ����:        const UINT16_S trainId, �г�ID
  ���:        UINT16_S sectionIdBuff[], �߼�����ID����
  ����ֵ:      TRAIN_ERROR_MAX_NUM:      ��ȡ����ʧ��
               >0:    ��ȡ���ݳɹ�
*************************************************/
UINT16_S GetTrainError(const UINT16_S trainId)
{
    UINT16_S rtnValue = TRAIN_ERROR_MAX_NUM;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainError;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainError
  ��������:    ����ָ���г�ID��ȷ�����
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S trainError, ��ȷ�����
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainError(const UINT16_S trainId, const UINT16_S trainError)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        gTrainStatusDataStruBuff[bufIndex].TrainError = trainError;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      AllotTrainIndex
  ��������:    ����ȷ���г�����Ļ����±�
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      SIZE_MAX_CONTROLE_TRAIN: �����±�ʧ��
               (0,SIZE_MAX_CONTROLE_TRAIN): �����±�ɹ�
*************************************************/
UINT8_S AllotTrainIndex(const UINT16_S trainId)
{
    UINT8_S rtnValue = SIZE_MAX_CONTROLE_TRAIN;
    UINT16_S trainIndex = DEFAULT_ZERO;

    trainIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != trainIndex)
    {
        /*�ѷ����±�*/
        rtnValue = (UINT8_S)(trainIndex);
    } 
    else
    {
        /*δ�����±�*/
        /*�жϵ�ǰ�ѹ�Ͻ�г�����*/
        if (GetTrainCurSum() < SIZE_MAX_CONTROLE_TRAIN)
        {
            /*С���ܹ�Ͻ���г�����,�����Է����±�洢�г�����*/
            rtnValue = GetTrainCurSum();
        } 
        else
        {
            rtnValue = SIZE_MAX_CONTROLE_TRAIN;
        }
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainPreSectionId
  ��������:    ��ȡָ���г��������߼�����ID
  ����:        const UINT16_S trainId, �г�ID
  ���:        UINT16_S sectionIdBuff[], �߼�����ID����
  ����ֵ:      RETURN_ERROR:      ��ȡ����ʧ��
               RETURN_SUCCESS:    ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainPreSectionId(const UINT16_S trainId,UINT16_S sectionIdBuff[])
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;
    UINT8_S k = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex) && (NULL != sectionIdBuff))
    {
        for(k=0U;k<SIZE_MAX_SECTION_OF_TRAIN;k++)
        {
            sectionIdBuff[k] = gTrainStatusDataStruBuff[bufIndex].PreSectionIdBuff[k];
        }
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:      GetTrainPreSectionNum
  ��������:    ��ȡָ���г��������߼���������
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      RETURN_UINT8_MAX_VALUE:      ��ȡ����ʧ��
               [0,RETURN_UINT8_MAX_VALUE):  ��ȡ���ݳɹ�
*************************************************/
UINT8_S GetTrainPreSectionNum(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].PreSectionNum;
    }
    else
    {
        rtnValue = RETURN_UINT8_MAX_VALUE;
    }

    return rtnValue;
}

/*************************************************
  ������:      SetTrainPreSectionId
  ��������:    ����ָ���г��������߼�������Ϣ
  ����:        const UINT16_S trainId, �г�ID
               const UINT16_S sectionIdBuff[], �߼�����ID����
               const UINT8_S sectionNum, �߼����ε�����
  ���:        ��
  ����ֵ:      RETURN_ERROR:    ����ʧ��
               RETURN_SUCCESS:  ���óɹ�
*************************************************/
UINT8_S SetTrainPreSectionId(const UINT16_S trainId,const UINT16_S sectionIdBuff[],const UINT8_S sectionNum)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;
    UINT8_S k = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex)
        && (sectionNum <= SIZE_MAX_SECTION_OF_TRAIN))
    {
        gTrainStatusDataStruBuff[bufIndex].PreSectionNum = DEFAULT_ZERO;

        for(k=0U;k < sectionNum;k++)
        {
            gTrainStatusDataStruBuff[bufIndex].PreSectionIdBuff[k] = sectionIdBuff[k];
        }

        gTrainStatusDataStruBuff[bufIndex].PreSectionNum = sectionNum;

        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:      DeleteSingleTrainInfo
  ��������:    ɾ�������г���Ϣ
  ����:        const UINT16_S trainId, �г�ID
  ���:        ��
  ����ֵ:      ��
*************************************************/
void DeleteSingleTrainInfo(const UINT16_S trainId)
{
    UINT8_S bufIndex = 0U;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnCpy = 1U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    /* �ж��±�ֵ */
    if (RETURN_UINT8_MAX_VALUE == bufIndex)
    {
        /*������*/
    } 
    else
    {
        /*�����Ϣ*/
        if (bufIndex == (GetTrainCurSum() - 1U))
        {
            MemorySet(&gTrainStatusDataStruBuff[bufIndex],((UINT32_S)(sizeof(TrainInfoStruct))),
                0U,((UINT32_S)(sizeof(TrainInfoStruct))));
        } 
        else
        {
            for (cycle = bufIndex + 1U;cycle < GetTrainCurSum();cycle++)
            {
                rtnCpy = MemoryCpy(&gTrainStatusDataStruBuff[cycle - 1U],((UINT32_S)(sizeof(TrainInfoStruct))),
                    &gTrainStatusDataStruBuff[cycle],((UINT32_S)(sizeof(TrainInfoStruct))));

                if (0U == rtnCpy)
                {
                    /*������������*/
                    gLocalTrainIndexBuff[gTrainStatusDataStruBuff[cycle - 1U].TrainID] = cycle - 1U;
                }
                else
                {
                    /* ����ʧ�� */
                }
            }

            /*������һ��*/
            MemorySet(&gTrainStatusDataStruBuff[gTrainCurSum - 1U],((UINT32_S)(sizeof(TrainInfoStruct))),
                0U,((UINT32_S)(sizeof(TrainInfoStruct))));
        }

        if (gTrainCurSum > 0U)
        {
            gTrainCurSum--;
        } 
        else
        {
            gTrainCurSum = 0U;
        }

        gLocalTrainIndexBuff[trainId] = RETURN_UINT8_MAX_VALUE;
    }
}
