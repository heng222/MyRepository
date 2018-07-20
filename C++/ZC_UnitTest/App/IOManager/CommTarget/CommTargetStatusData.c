/************************************************************************
*
* �ļ���   ��  CommTargetStatusData.c
* ����     ��  ZC��
* ����ʱ�� ��  2015.07.14
* �������� ��  ͨѶ����״̬ 
* ��  ע   ��  ��
*
************************************************************************/

#include "CommTargetConfigData.h"
#include "CommTargetStatusData.h"
#include "../../SysDataManager/SysConfigData.h"

CommTargetDataStruct gCommTargetDataStruBuff[COMM_TYPE_SUM_MAX];               /*����ͨ�Ŷ���״̬��Ϣ�����г��������ϵͳ��*/

SingleCommTargeStruct gCommTrainDataStruBuff[COMM_TRAIN_ID_MAX];               /*ͨ���г�״̬��Ϣ*/

/*
* ���������� ��ȡͨ�Ŷ�����Ϣ
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡͨ�Ŷ�����Ϣ
*/
CommTargetDataStruct* GetCommTargetStatusData(void)
{
    return gCommTargetDataStruBuff;
}

/*
* ���������� ��ȡͨ�Ŷ���Id��Ӧ���±�
* ����˵���� const UINT8 commTargetType ����
const UINT16_S commTargetId  ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����Id��Ӧ���±�
*/
UINT8_S GetOtherCommTargetIdBuffIndex(const UINT8_S commTargetType,const UINT16_S commTargetId)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S typeBuffIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();

    if (commTargetType == INNER_DEVTYPE_TRAIN)
    {
        /*�������г�*/
        rtnValue = SINGLE_TYPE_COMM_TARGET_SUM_MAX;
    }
    else
    {
        typeBuffIndex = GetCommTargetTypeBuffIndex(commTargetType);

        if ((typeBuffIndex < allCommTargetSum) && (COMM_TARGET_ID_MAX > commTargetId))
        {
            rtnValue = gCommTargetDataStruBuff[typeBuffIndex].CommTargetIdBuff[commTargetId];
        } 
        else
        {
            /*������*/
        }
    }

    return rtnValue;
}

/*
* ���������� ��ȡĳͨ�Ŷ���ͨ���ۼ���Ϣ
* ����˵���� const UINT8 commTargetType ͨ�Ŷ�������
const UINT16_S commTargetID ͨ�Ŷ���ID    
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*			>=0: ͨ���ۼ���Ϣ
*/
UINT16_S GetCommTargetCycle(const UINT8_S commTargetType,const UINT16_S commTargetId)
{
    UINT16_S rtnValue = DEFAULT_UINT16_VALUE; 
    UINT8_S typeBuffIndex = DEFAULT_ZERO;
    UINT8_S idBuffIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();

    switch (commTargetType)
    {
    case INNER_DEVTYPE_TRAIN:
        if ((commTargetId > DEFAULT_ZERO) && (commTargetId < COMM_TRAIN_ID_MAX))
        {
            rtnValue = (UINT16_S)gCommTrainDataStruBuff[commTargetId].CommTargetCycle;
        } 
        else
        {
            /*������*/
        }
        break;
    case INNER_DEVTYPE_CI:
    case INNER_DEVTYPE_ATS:
    case INNER_DEVTYPE_ZC:
    case INNER_DEVTYPE_NTP:
        typeBuffIndex = GetCommTargetTypeBuffIndex(commTargetType);
        idBuffIndex = GetOtherCommTargetIdBuffIndex(commTargetType,commTargetId);

        if ((typeBuffIndex < allCommTargetSum) && (SINGLE_TYPE_COMM_TARGET_SUM_MAX > idBuffIndex))
        {
            rtnValue = (UINT16_S)gCommTargetDataStruBuff[typeBuffIndex].SingleCommTargeStru[idBuffIndex].CommTargetCycle;
        } 
        else
        {
            /*������*/
        }
        break;
    default:
        break;
    }

    return rtnValue;
}

/*
* ���������� ����ĳͨ�Ŷ���ͨ���ۼ���Ϣ
* ����˵���� const UINT8 commTargetType ͨ�Ŷ�������
const UINT16_S commTargetID ͨ�Ŷ���ID  
const UINT16_S commTargetCycle ͨ�Ŷ����ۼ���Ϣ    
* ����ֵ  �� 0: ����ʧ��
*			 1: ���óɹ�
*/
UINT8_S SetCommTargetCycle(const UINT8_S commTargetType,const UINT16_S commTargetId, const UINT16_S commTargetCycle)
{
    UINT8_S rtnValue = DEFAULT_ZERO; 
    UINT8_S typeBuffIndex = DEFAULT_ZERO;
    UINT8_S idBuffIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
    switch (commTargetType)
    {
    case INNER_DEVTYPE_TRAIN:
        if ((commTargetId > DEFAULT_ZERO) 
            && (commTargetId < COMM_TRAIN_ID_MAX))
        {
            gCommTrainDataStruBuff[commTargetId].CommTargetCycle = commTargetCycle;
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
        break;
    case INNER_DEVTYPE_CI:
    case INNER_DEVTYPE_ATS:
    case INNER_DEVTYPE_ZC:
    case INNER_DEVTYPE_NTP:
        typeBuffIndex = GetCommTargetTypeBuffIndex(commTargetType);
        idBuffIndex = GetOtherCommTargetIdBuffIndex(commTargetType,commTargetId);

        if ((typeBuffIndex < allCommTargetSum) && (SINGLE_TYPE_COMM_TARGET_SUM_MAX > idBuffIndex))
        {
            gCommTargetDataStruBuff[typeBuffIndex].SingleCommTargeStru[idBuffIndex].CommTargetCycle = commTargetCycle;
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
        break;
    default:
        break;
    }

    return rtnValue;
}

/*
* ���������� ��ȡĳͨ�Ŷ���״̬��Ϣ
* ����˵���� const UINT8 commTargetType ͨ�Ŷ�������
const UINT16_S commTargetID ͨ�Ŷ���ID      
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>=0: ״̬��Ϣ
*/
UINT8_S GetCommTargetStatus(const UINT8_S commTargetType,const UINT16_S commTargetId)
{
    UINT8_S rtnValue = DEFAULT_UINT8_VALUE; 
    UINT8_S typeBuffIndex = DEFAULT_ZERO;
    UINT8_S idBuffIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();

    switch (commTargetType)
    {
    case INNER_DEVTYPE_TRAIN:
        if ((commTargetId > DEFAULT_ZERO) && (commTargetId < COMM_TRAIN_ID_MAX))
        {
            rtnValue = gCommTrainDataStruBuff[commTargetId].CommTargetStatus;
        } 
        else
        {
            /*������*/
        }
        break;
    case INNER_DEVTYPE_CI:
    case INNER_DEVTYPE_ATS:
    case INNER_DEVTYPE_ZC:
    case INNER_DEVTYPE_NTP:
        typeBuffIndex = GetCommTargetTypeBuffIndex(commTargetType);
        idBuffIndex = GetOtherCommTargetIdBuffIndex(commTargetType,commTargetId);

        if ((typeBuffIndex < allCommTargetSum) && (SINGLE_TYPE_COMM_TARGET_SUM_MAX > idBuffIndex))
        {
            rtnValue = gCommTargetDataStruBuff[typeBuffIndex].SingleCommTargeStru[idBuffIndex].CommTargetStatus;
        } 
        else
        {
            /*������*/
        }
        break;
    default:
        break;
    }

    return rtnValue;
}

/*
* ���������� ����ĳͨ�Ŷ���״̬��Ϣ
* ����˵���� const UINT8 commTargetType ͨ�Ŷ�������
const UINT16_S commTargetID ͨ�Ŷ���ID    
const UINT8_S commTargetStatus ͨ�Ŷ���״̬��Ϣ 
* ����ֵ  �� 0: ����ʧ��
*			 1: ���óɹ�
*/
UINT8_S SetCommTargetStatus(const UINT8_S commTargetType,const UINT16_S commTargetId, const UINT8_S commTargetStatus)
{
    UINT8_S rtnValue = DEFAULT_ZERO; 
    UINT8_S typeBuffIndex = DEFAULT_ZERO;
    UINT8_S idBuffIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();

    switch (commTargetType)
    {
    case INNER_DEVTYPE_TRAIN:
        if ((commTargetId > DEFAULT_ZERO) 
            && (commTargetId < COMM_TRAIN_ID_MAX)
            && ((COMM_STATUS_NORMAL == commTargetStatus) || (COMM_STATUS_ABNORMAL == commTargetStatus) || (DEFAULT_ZERO == commTargetStatus)))
        {
            gCommTrainDataStruBuff[commTargetId].CommTargetStatus = commTargetStatus;
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
        break;
    case INNER_DEVTYPE_CI:
    case INNER_DEVTYPE_ATS:
    case INNER_DEVTYPE_ZC:
    case INNER_DEVTYPE_NTP:
        typeBuffIndex = GetCommTargetTypeBuffIndex(commTargetType);
        idBuffIndex = GetOtherCommTargetIdBuffIndex(commTargetType,commTargetId);

        if ((typeBuffIndex < allCommTargetSum) 
            && (SINGLE_TYPE_COMM_TARGET_SUM_MAX > idBuffIndex)
            && ((COMM_STATUS_NORMAL == commTargetStatus) || (COMM_STATUS_ABNORMAL == commTargetStatus)  || (DEFAULT_ZERO == commTargetStatus)))
        {
            gCommTargetDataStruBuff[typeBuffIndex].SingleCommTargeStru[idBuffIndex].CommTargetStatus = commTargetStatus;
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
        break;
    default:
        break;
    }

    return rtnValue;
}

/*
* ���������� ��ȡĳͨ�Ŷ���ͨ�Ŷ���������Ϣʱ�����ں�
* ����˵���� const UINT8 commTargetType ͨ�Ŷ�������
const UINT16_S commTargetID ͨ�Ŷ���ID     
* ����ֵ  ��  0: ��ȡ����ʧ��
*			>=0: ͨ�Ŷ���������Ϣʱ�����ں�
*/
UINT32_S GetCommTargetCycleNum(const UINT8_S commTargetType,const UINT16_S commTargetId)
{
    UINT32_S rtnValue = DEFAULT_UINT32_VALUE; 
    UINT8_S typeBuffIndex = DEFAULT_ZERO;
    UINT8_S idBuffIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();

    switch (commTargetType)
    {
    case INNER_DEVTYPE_TRAIN:
        if ((commTargetId > DEFAULT_ZERO) && (commTargetId < COMM_TRAIN_ID_MAX))
        {
            rtnValue = gCommTrainDataStruBuff[commTargetId].CommTargetCycleNum;
        } 
        else
        {
            /*������*/
        }
        break;
    case INNER_DEVTYPE_CI:
    case INNER_DEVTYPE_ATS:
    case INNER_DEVTYPE_ZC:
    case INNER_DEVTYPE_NTP:
        typeBuffIndex = GetCommTargetTypeBuffIndex(commTargetType);
        idBuffIndex = GetOtherCommTargetIdBuffIndex(commTargetType,commTargetId);

        if ((typeBuffIndex < allCommTargetSum) && (SINGLE_TYPE_COMM_TARGET_SUM_MAX > idBuffIndex))
        {
            rtnValue = gCommTargetDataStruBuff[typeBuffIndex].SingleCommTargeStru[idBuffIndex].CommTargetCycleNum;
        } 
        else
        {
            /*������*/
        }
        break;
    default:
        break;
    }

    return rtnValue;
}

/*
* ���������� ����ĳͨ�Ŷ���������Ϣ
* ����˵����const UINT8 commTargetType ͨ�Ŷ�������
const UINT16_S commTargetID ͨ�Ŷ���ID  
const UINT32_S commTargetCycleNum ͨ�Ŷ���������Ϣ    
* ����ֵ  �� 0: ����ʧ��
*			 1: ���óɹ�
*/
UINT8_S SetCommTargetCycleNum(const UINT8_S commTargetType,const UINT16_S commTargetId, const UINT32_S commTargetCycleNum)
{
    UINT8_S rtnValue = DEFAULT_ZERO; 
    UINT8_S typeBuffIndex = DEFAULT_ZERO;
    UINT8_S idBuffIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
    switch (commTargetType)
    {
    case INNER_DEVTYPE_TRAIN:
        if ((commTargetId > DEFAULT_ZERO) 
            && (commTargetId < COMM_TRAIN_ID_MAX)
            && (DEFAULT_UINT32_VALUE > commTargetCycleNum))
        {
            gCommTrainDataStruBuff[commTargetId].CommTargetCycle = commTargetCycleNum;
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
        break;
    case INNER_DEVTYPE_CI:
    case INNER_DEVTYPE_ATS:
    case INNER_DEVTYPE_ZC:
    case INNER_DEVTYPE_NTP:
        typeBuffIndex = GetCommTargetTypeBuffIndex(commTargetType);
        idBuffIndex = GetOtherCommTargetIdBuffIndex(commTargetType,commTargetId);

        if ((typeBuffIndex < allCommTargetSum) 
            && (SINGLE_TYPE_COMM_TARGET_SUM_MAX > idBuffIndex)
            && (DEFAULT_UINT32_VALUE > commTargetCycleNum))
        {
            gCommTargetDataStruBuff[typeBuffIndex].SingleCommTargeStru[idBuffIndex].CommTargetCycle = commTargetCycleNum;
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
        break;
    default:
        break;
    }

    return rtnValue;
}

/*
* ���������� ���ĳ���г���ͨ�ż�ʱ��Ϣ��״̬��Ϣ
* ����˵���� const UINT16_S trainId,�г�ID    
* ����ֵ  �� ��
*/
void ClearOneTrainCommCycleAndStatus(const UINT16_S trainId)
{
	gCommTrainDataStruBuff[trainId].CommTargetCycle = DEFAULT_ZERO;
	gCommTrainDataStruBuff[trainId].CommTargetStatus = DEFAULT_ZERO;
}