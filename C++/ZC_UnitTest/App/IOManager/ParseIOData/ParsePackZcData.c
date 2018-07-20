/************************************************************************
*
* �ļ���   ��  ParsePackZcData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �������������ZC���ݹ���  
* ��  ע	��  ��
*
************************************************************************/

#include "ParsePackZcData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../CommTarget/CommTargetConfigData.h"
#include "../CommTarget/CommTargetStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Convert.h"
#include "../../MaintainManager/MaintainManager.h"

ZcAndNzcIODataStruct gToNZcDataStruBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX];     /*zc������ATP�����ݽṹ*/
UINT16_S gToNZcDataIdBuff[COMM_TARGET_ID_MAX] = {COMM_TARGET_ID_MAX};        /*ID��������*/
UINT8_S  gToNZcCurSum = 0U;                                                  /*ZC�������ZC���������*/

ZcAndNzcIODataStruct gNZcInDataStruBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX];     /*����ZC��������ݽṹ*/
UINT16_S gNZcInDataIdBuff[COMM_TARGET_ID_MAX] = {COMM_TARGET_ID_MAX};        /*ID��������*/
UINT8_S  gNZcInCurSum = 0U;                                                  /*����ZC������������*/

/*
* ���������� ��ȡ����ZC����Zc���������
* ����˵���� void
* ����ֵ  ��  SINGLE_TYPE_COMM_TARGET_SUM_MAX: ʧ��
*			>0: ����      
*/
UINT8_S GetNZcToZcCurSum(void)
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (gNZcInCurSum <= SINGLE_TYPE_COMM_TARGET_SUM_MAX)
    {
        rtnValue = gNZcInCurSum;
    } 
    else
    {
        rtnValue = SINGLE_TYPE_COMM_TARGET_SUM_MAX;
    }

    return rtnValue;
}

/*
* ������������ȡ����ZC��������������±��Ӧ��ZCID
* ����˵���� const UINT8 nZcIdOfIndex
* ����ֵ  �� 0: ʧ��
*			 >0: �ɹ�      
*/
UINT16_S GetNZcToZcBuffIndexOfNZcId(const UINT8_S nZcIdOfIndex)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (COMM_TARGET_ID_MAX <= nZcIdOfIndex)
    {
        rtnValue = DEFAULT_ZERO;
    }
    else
    {
        rtnValue = gNZcInDataStruBuff[nZcIdOfIndex].ZcId;
    }

    return rtnValue;
}

/*
* ������������ȡ����ZC��������������±��Ӧ�����ݳ���
* ����˵���� const UINT8 nZcIdOfIndex
* ����ֵ  �� 0: ʧ��
*			 >0: �ɹ�      
*/
UINT16_S GetNZcToZcIdDataBufLen(const UINT8_S nZcIdOfIndex)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (COMM_TARGET_ID_MAX <= nZcIdOfIndex)
    {
        rtnValue = DEFAULT_ZERO;
    } 
    else
    {
        rtnValue = gNZcInDataStruBuff[nZcIdOfIndex].ValueBuffLen;
    }

    return rtnValue;
}

/*
* ���������� ��ȡNZc����Zc��Id��Ӧ������Ϣ
* ����˵���� const UINT8 nZcIdOfIndex
* ����ֵ  �� NULL: ʧ��
*			 !NULL: �ɹ�       
*/
UINT8_S* GetNZcToZcBufDataOfIndex(const UINT8_S nZcIdOfIndex)
{
    UINT8_S *pRtnValue = NULL;

    if (COMM_TARGET_ID_MAX <= nZcIdOfIndex)
    {
        pRtnValue = NULL;
    } 
    else
    {
        pRtnValue = gNZcInDataStruBuff[nZcIdOfIndex].ValueBuff;
    }

    return 	pRtnValue;
}

/*
* ���������� ����NZC����ĵ�֡����
* ����˵���� const UINT8_S dataBuff[], ���ݻ�����
*            const UINT16_S dataLength, ���ݳ���
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseNzcToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength)
{
    UINT8_S sourceId = DEFAULT_ZERO;
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S copyRtn = DEFAULT_ZERO;

    if ((dataBuff != NULL) && (dataLength > 0U))
    {
        /*����֡ͷ,�ж��Ƿ�Ϊ��ZCͨ�ŵ�ZC*/
        sourceId = dataBuff[1];

        tempRtn = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,((UINT16_S)sourceId));

        if (RETURN_SUCCESS == tempRtn)
        {
            /*��ȡͨ������*/
            /*�ж����������Ƿ�Ϸ�*/

            if (RETURN_SUCCESS == NzcInputDataValidityCheck(dataBuff,dataLength))
            {
                /* ���ӿ�ȷ����д������ */
                /*��дԴId*/
                gNZcInDataStruBuff[gNZcInCurSum].ZcId = sourceId;

                /*��ȡ���ݳ���*/
                gNZcInDataStruBuff[gNZcInCurSum].ValueBuffLen = dataLength - 4U;

                /*PBW + ZYW:add*/
                copyRtn = MemoryCpy(gNZcInDataStruBuff[gNZcInCurSum].ValueBuff,((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)),&dataBuff[4],((UINT32_S)(gNZcInDataStruBuff[gNZcInCurSum].ValueBuffLen)));

                if (0U == copyRtn)
                {
                    gNZcInDataIdBuff[sourceId] = gNZcInCurSum;

                    gNZcInCurSum++;

                    /*���ڱ�ZCͨ��, ����ͨ��״̬*/
                    SetCommTargetStatus(INNER_DEVTYPE_ZC,((UINT16_S)sourceId),COMM_STATUS_NORMAL);
                    SetCommTargetCycle(INNER_DEVTYPE_ZC,((UINT16_S)sourceId),DEFAULT_ZERO);

                    /*LogPrintf(1U,"29.202 NZc=%d,In!Sum=%d\n",sourceId,gNZcInCurSum);*/

                    /*������Ч*/
                    rtnValue = RETURN_SUCCESS;
                } 
                else
                {
                    gNZcInDataIdBuff[sourceId] = SINGLE_TYPE_COMM_TARGET_SUM_MAX;
                    gNZcInDataStruBuff[gNZcInCurSum].ValueBuffLen = DEFAULT_ZERO;
                    gNZcInDataStruBuff[gNZcInCurSum].ZcId = DEFAULT_ZERO;

                    LogPrintf(1U,"29.203 NextZc=%d,Input!gNZcInCurSum=%d,copyRtn=%d\n",sourceId,gNZcInCurSum,copyRtn);

                    /*������Ч*/
                    rtnValue = RETURN_ERROR;
                }
            } 
            else
            {
                LogPrintf(1U,"29.204 NextZc=%d,Input Data Error\n",sourceId,gNZcInCurSum);
            }
        } 
        else
        {
            /*������Ч*/
            rtnValue = RETURN_ERROR;

            LogPrintf(1U,"29.204 NextZc=%d,Not Comm Zc\n",sourceId,gNZcInCurSum);
        }

    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� ����ZC����ĵ�֡���ݺϷ��Լ��
* ����˵���� const UINT8_S dataBuff[], ���ݻ�����
*            const UINT16_S dataLen, ���ݳ���
* ����ֵ  �� 0: �Ϸ��Լ��ʧ��
*			 1: �Ϸ��Լ��ɹ�      
*/
UINT8_S NzcInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen)
{
    UINT8_S rtnValue = 0U;
    UINT16_S checkErrorFlag = DEFAULT_ZERO;

    /* �˺���ΪԤ������ ��Ҫ����ͨѶ����У��֮���֡����У�� */
    if ((NULL != dataBuff) && (0U < dataLen))
    {
        if ((INNER_DEVTYPE_ZC == dataBuff[0]) && ((INNER_DEVTYPE_ZC == dataBuff[2])) && (dataBuff[1] != dataBuff[3]))
        {
            /* ������ͬ��ID��ͬ */
            rtnValue = 1U;
        } 
        else
        {
             rtnValue = 0U;
             checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_1);
        }       
    }
    else
    {
        rtnValue = 0U;
        checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_2);
    }

    /*LogPrintf(1U,"NZcInDataCheck[%d] Error=%d\n",dataBuff[1],checkErrorFlag);*/
    return rtnValue;
}

/*
* ���������� ��ȡZC�����NZc���������
* ����˵���� void
* ����ֵ  �� SINGLE_TYPE_COMM_TARGET_SUM_MAX: ʧ��
*			>0: ����      
*/
UINT8_S GetZcToNZcCurSum(void)
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (gToNZcCurSum <= SINGLE_TYPE_COMM_TARGET_SUM_MAX)
    {
        rtnValue = gToNZcCurSum;
    } 
    else
    {
        rtnValue = SINGLE_TYPE_COMM_TARGET_SUM_MAX;
    }

    return rtnValue;
}

/*
* ������������ȡ���������ZC���������±��Ӧ�����ݳ���
* ����˵���� const UINT8 nZcIdOfIndex
* ����ֵ  �� 0: ʧ��
*			 >0: �ɹ�      
*/
UINT16_S GetZcToNZcIdDataBufLen(const UINT8_S nZcIdOfIndex)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (COMM_TARGET_ID_MAX <= nZcIdOfIndex)
    {
        rtnValue = DEFAULT_ZERO;       
    } 
    else
    {
        rtnValue = gToNZcDataStruBuff[nZcIdOfIndex].ValueBuffLen;
    }

    return rtnValue;
}

/*
* ���������� ��ȡ���������ZC���������±��Ӧ��������Ϣ
* ����˵���� const UINT8 nZcIdOfIndex
* ����ֵ  �� NULL: ʧ��
*			 !NULL: �ɹ�      
*/
UINT8_S* GetZcToNZcBufDataOfIndex(const UINT8_S nZcIdOfIndex)
{
    UINT8_S *pRtnValue = NULL;

    if (COMM_TARGET_ID_MAX <= nZcIdOfIndex)
    {
        pRtnValue = NULL;        
    } 
    else
    {
        pRtnValue = gToNZcDataStruBuff[nZcIdOfIndex].ValueBuff;
    }

    return pRtnValue;
}

/*
* ���������� ������ZC����
* ����˵���� const UINT8* dataBuf,���ݻ���
*            const UINT16_S dataLength,���ݳ���
*            const UINT16_S destId, Ŀ��ID   
* ����ֵ  �� RETURN_ERROR:������ʧ��
*			 RETURN_SUCCESS:�����ݳɹ�      
*/
UINT8_S PackZcToNzcFrameData(const UINT8_S* dataBuf,const UINT16_S dataLength,const UINT16_S destId)
{
    UINT16_S index = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S copyRtn = 1U;

    if ((dataBuf != NULL) && (dataLength > 0U))
    {
        /*��д��λ��Ϣ����֡ͷ*/
        if (SINGLE_TYPE_COMM_TARGET_SUM_MAX <= gToNZcCurSum)
        {            
            /*������Ч*/
            rtnValue = RETURN_ERROR;
        } 
        else
        {           
            gToNZcDataStruBuff[gToNZcCurSum].ZcId = (UINT8_S)(destId);

            /*��������*/
            gToNZcDataIdBuff[destId] = gToNZcCurSum;

            /*��д��Ϣ֡ͷ��Ϣ*/
            /*��дԴ�豸*/
            gToNZcDataStruBuff[gToNZcCurSum].ValueBuff[index] = INNER_DEVTYPE_ZC;
            index = index + 1U;

            gToNZcDataStruBuff[gToNZcCurSum].ValueBuff[index] = (UINT8_S)GetLocalZcId();
            index = index + 1U;

            /*��дĿ���豸*/
            gToNZcDataStruBuff[gToNZcCurSum].ValueBuff[index] = INNER_DEVTYPE_ZC;
            index = index + 1U;

            gToNZcDataStruBuff[gToNZcCurSum].ValueBuff[index] = (UINT8_S)destId;
            index = index + 1U;

            /*��������*/
            /*PBW,2016.5.24,����ZC������ʹ��4���ֽڵ�֡ͷ*/
            copyRtn = MemoryCpy(&gToNZcDataStruBuff[gToNZcCurSum].ValueBuff[index],((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX - (UINT32_S)index)),dataBuf,((UINT32_S)dataLength));

            if (1U == copyRtn)
            {
                /*�����Ϣ*/
                gToNZcDataStruBuff[gToNZcCurSum].ZcId = 0U;		
                gToNZcDataIdBuff[destId] = SINGLE_TYPE_COMM_TARGET_SUM_MAX;
                gToNZcDataStruBuff[gToNZcCurSum].ValueBuffLen = DEFAULT_ZERO;

                rtnValue = RETURN_ERROR;
            } 
            else
            {
                /*��������*/
                gToNZcDataStruBuff[gToNZcCurSum].ValueBuffLen = index + dataLength;
                gToNZcCurSum++;
                rtnValue = RETURN_SUCCESS;
            }
        }
    }
    else
    {
        /*������Ч*/
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� ��ձ�������������ZC������Ϣ
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearCycleNZcInputData(void)
{
    UINT8_S cycle = DEFAULT_ZERO;

    /*�������*/
    for (cycle = DEFAULT_ZERO;cycle < SINGLE_TYPE_COMM_TARGET_SUM_MAX;cycle++)
    {
        MemorySet(&gNZcInDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndNzcIODataStruct))),
            DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndNzcIODataStruct))));
    }

    /*�����������*/
    gNZcInCurSum  = 0U;

    /*��չ�������*/
    for (cycle = DEFAULT_ZERO;cycle < COMM_TARGET_ID_MAX;cycle++)
    {
        gNZcInDataIdBuff[cycle] = COMM_TARGET_ID_MAX;
    }
}

/*
* ���������� ��ձ�������������ZC�����Ϣ
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearCycleNZcOutputData(void)
{
    UINT8_S cycle = DEFAULT_ZERO;

    /*�������*/
    for (cycle = DEFAULT_ZERO;cycle < SINGLE_TYPE_COMM_TARGET_SUM_MAX;cycle++)
    {
        MemorySet(&gToNZcDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndNzcIODataStruct))),
            DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndNzcIODataStruct))));
    }

    /*����������*/
    gToNZcCurSum  = 0U;

    /*��չ�������*/
    for (cycle = DEFAULT_ZERO;cycle < COMM_TARGET_ID_MAX;cycle++)
    {
        gToNZcDataIdBuff[cycle] = COMM_TARGET_ID_MAX;
    }
}
