/************************************************************************
*
* �ļ���   ��  CommTargetInitManager.c
* ����     ��  ZC��
* ����ʱ�� ��  2015.07.14
* �������� ��  ͨѶĿ���ʼ��
* ��  ע   ��  �� 
*
************************************************************************/

#include "CommTargetInitManager.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../../Dmu/DmuComm/Data/SystemDevCommData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "CommTargetConfigData.h"
#include "CommTargetStatusData.h"

extern CommTargetConfigDataStruct gCommTargetConfigDataStru[COMM_TYPE_SUM_MAX];           /*����ͨ�Ŷ���������Ϣ*/
extern UINT8_S gCommTargetTypeCurSum;                                                       /*����ͨ�Ŷ�������*/

extern CommTargetDataStruct gCommTargetDataStruBuff[COMM_TYPE_SUM_MAX];                       /*����ͨ�Ŷ���״̬��Ϣ�����г��������ϵͳ��*/
extern SingleCommTargeStruct gCommTrainDataStruBuff[COMM_TRAIN_ID_MAX];                       /*����ͨ���г�״̬��Ϣ*/

/*
* �������ƣ� InitCommTargetInfo
* ���������� ��ʼ��ͨ�Ŷ����ϵ
* ��������� void    
* ��������� ��
* ����ֵ  �� 0u: ��ʼ��ʧ��
*			 1u: ��ʼ���ɹ�
*/
UINT8_S InitCommTargetInfo(void)
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (RETURN_SUCCESS == InitOtherCommTargetInfo())
    {
        InitTrainCommTargetInfo();

        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* �������ƣ� InitOtherCommTargetInfo
* ���������� ��ʼ������ͨ�Ŷ��󣨷��г�����ͨ�Ź�ϵ
* ��������� void   
* ��������� ��
* ����ֵ  �� 0u: ��ʼ��ʧ��
*			 1u: ��ʼ���ɹ�
*/
UINT8_S InitOtherCommTargetInfo(void)
{
    UINT16_S tempZcId = DEFAULT_ZERO;
    BnfSystemDevCommStruct *pBnfSystemDevCommStru = NULL;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTragetId = DEFAULT_ZERO;
    UINT8_S commTragetType = DEFAULT_ZERO;
    UINT8_S commTragetIndex = DEFAULT_ZERO;
    UINT8_S singleCommNum = DEFAULT_ZERO;
    UINT8_S breakFalg = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;

    /*��ȡ��ZC��Id*/
    tempZcId = (UINT16_S)INNER_DEVTYPE_ZC;
    localZcId = GetLocalZcId();
    localZcId = (UINT16_S)((UINT16_S)(tempZcId << 8) | localZcId);

    /*��ȡ��ZCͨ�ŵ��豸��ϵ*/
    pBnfSystemDevCommStru = GetIndexIdSystemDevCommDataStru(localZcId);

    /*��������ͨ�Ŷ�������*/
    gCommTargetTypeCurSum = (UINT8_S)DEFAULT_ZERO;

    if (NULL != pBnfSystemDevCommStru)
    {
        for (cycle = DEFAULT_ZERO;cycle < pBnfSystemDevCommStru->commObjectNum;cycle++)
        {
            /*��ȡͨ���豸����*/
            commTragetType = (UINT8_S)((pBnfSystemDevCommStru->commObjectIdBuff[cycle] & ((UINT16_S)0xff00U)) >> 8);

            /*ͨ�Ŷ���ID*/
            commTragetId = (UINT16_S)(pBnfSystemDevCommStru->commObjectIdBuff[cycle] & ((UINT16_S)0x00ffU));

            /*��ȡͨ�Ŷ����±�*/
            commTragetIndex = GetCommTargetTypeBuffIndex(commTragetType);

            if (COMM_TYPE_SUM_MAX != commTragetIndex)
            {
                /*�����Ѱ��������Ӹ�����ͨ����Ϣ*/
                singleCommNum = gCommTargetConfigDataStru[commTragetIndex].CommTargetNum;

                if (singleCommNum < SINGLE_TYPE_COMM_TARGET_SUM_MAX)
                {
                    /*������ö�*/
                    gCommTargetConfigDataStru[commTragetIndex].CommTargetIdBuff[singleCommNum] = commTragetId;
                    gCommTargetConfigDataStru[commTragetIndex].CommTargetNum++;

                    /*���״̬��*/
                    gCommTargetDataStruBuff[commTragetIndex].SingleCommTargeStru[singleCommNum].CommTargetId = commTragetId;
                    gCommTargetDataStruBuff[commTragetIndex].SingleCommTargeStru[singleCommNum].CommTargetStatus = DEFAULT_ZERO;
                    gCommTargetDataStruBuff[commTragetIndex].SingleCommTargeStru[singleCommNum].CommTargetCycle = DEFAULT_ZERO;
                    gCommTargetDataStruBuff[commTragetIndex].CommTargetIdBuff[commTragetId] = singleCommNum;
                    gCommTargetDataStruBuff[commTragetIndex].CommTargetNum++;
                } 
                else
                {
                    /*�޷�������,����ʧ��*/
                    rtnValue = RETURN_ERROR;
                    breakFalg = FLAG_SET;
                    break;
                }

            } 
            else
            {
                /*����δ���������Ӹ�����ͨ����Ϣ*/
                if (((UINT8_S)(COMM_TYPE_SUM_MAX-1U)) > gCommTargetTypeCurSum)
                {
                    /*����δ���������Ӹ�����ͨ����Ϣ*/
                    /*������ö�*/
                    gCommTargetConfigDataStru[gCommTargetTypeCurSum].CommTargetType = commTragetType;
                    gCommTargetConfigDataStru[gCommTargetTypeCurSum].CommTargetNum = DEFAULT_ZERO;
                    gCommTargetConfigDataStru[gCommTargetTypeCurSum].CommTargetIdBuff[DEFAULT_ZERO] = (UINT16_S)(pBnfSystemDevCommStru->commObjectIdBuff[cycle] & ((UINT16_S)0x00ffU));
                    gCommTargetConfigDataStru[gCommTargetTypeCurSum].CommTargetNum++;


                    /*���״̬��*/
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].CommTargetType = commTragetType;
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].CommTargetNum = DEFAULT_ZERO;
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].SingleCommTargeStru[DEFAULT_ZERO].CommTargetId = commTragetId;
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].SingleCommTargeStru[DEFAULT_ZERO].CommTargetStatus = DEFAULT_ZERO;
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].SingleCommTargeStru[DEFAULT_ZERO].CommTargetCycle = DEFAULT_ZERO;
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].CommTargetIdBuff[commTragetId] = DEFAULT_ZERO;				
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].CommTargetNum++;

                    gCommTargetTypeCurSum++;
                } 
                else
                {
                    /*�޷�������,����ʧ��*/
                    rtnValue = RETURN_ERROR;
                    breakFalg = FLAG_SET;
                    break;
                }
            }
        }

        if (FLAG_SET != breakFalg)
        {
            rtnValue = RETURN_SUCCESS;
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

/*
* �������ƣ� InitTrainCommTargetInfo
* ���������� ��ʼ���г�ͨ�Ŷ����ͨ�Ź�ϵ
* ��������� void    
* ��������� ��
* ����ֵ  �� ��
*/
void InitTrainCommTargetInfo(void)
{
    UINT8_S cycle = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < COMM_TRAIN_ID_MAX;cycle++)
    {
        gCommTrainDataStruBuff[cycle].CommTargetId = cycle;
        gCommTrainDataStruBuff[cycle].CommTargetStatus = DEFAULT_ZERO;
        gCommTrainDataStruBuff[cycle].CommTargetCycle = DEFAULT_ZERO;
        gCommTrainDataStruBuff[cycle].CommTargetCycleNum = DEFAULT_ZERO;
    }
}

