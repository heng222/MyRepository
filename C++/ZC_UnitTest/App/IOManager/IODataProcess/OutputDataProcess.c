/************************************************************************
*
* �ļ���   ��  OutputDataProcess.c
* ����ʱ�� ��  2015.08.14
* ����     ��  ZC��
* �������� ��  ���ZC���͵����ݹ���  
* ��  ע	��  ��
*
************************************************************************/

#include "../../../Common/Convert.h"
#include "OutputDataProcess.h"
#include "../../TrainManager/Train/TrainDefine.h"
#include "../../TrainManager/Train/TrainStatusData.h"
#include "../../TrainManager/MA/MAStatusData.h"
#include "../../LineDataManager/Change/ChangeLogicManager.h"
#include "../CommTarget/CommTargetConfigData.h"
#include "../CommTarget/CommTargetStatusData.h"
#include "../../LineDataManager/Tsr/TsrStatusData.h"
#include "../ParseIOData/ParsePackIODefine.h"
#include "../../SysDataManager/SysStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../LineDataManager/Mask/MaskConfigData.h"
#include "../../LineDataManager/LogicSection/LogicSectionStatusData.h"
#include "../../LineDataManager/LogicSection/LogicSectionConfigData.h"
#include "../../LineDataManager/AC/ACStatusData.h"
#include "../../LineDataManager/AC/ACLogicManager.h"
#include "../../LineDataManager/DR/DRStatusData.h"
#include "../../LineDataManager/Signal/SignalStatusData.h"
#include "../ParseIOData/ParsePackCiData.h"
#include "../../LineDataManager/DataVersion/DataVersionConfigData.h"
#include "../../LineDataManager/Change/ChangeConfigData.h"
#include "../ParseIOData/ParsePackTrainData.h"
#include "../ParseIOData/ParsePackZcData.h"
#include "../ParseIOData/ParsePackAtsData.h"
#include "../../LineDataManager/Route/RouteStatusData.h"
#include "../../LineDataManager/Overlap/OverlapStatusData.h"
#include "../../LineDataManager/Switch/SwitchStatusData.h"
#include "../../LineDataManager/PSD/PSDStatusData.h"
#include "../../LineDataManager/ESB/ESBStatusData.h"
#include "../../LineDataManager/DR/DRStatusData.h"
#include "../../../Common/MemSet.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../LineDataManager/AC/ACConfigData.h"
#include "../../SysDataManager/SysTimeData.h"
#include "../ParseIOData/ParsePackNtpData.h"
#include "../../MaintainManager/ZcMaintainManager.h"
#include "../../TsrManager/TsrInterface.h"/*-bye-*/

#ifdef SYS_TYPE_WINDOWS
extern unsigned short gStopProRouteId;  /* ͣ����֤*/
extern unsigned char gStopProReq;
extern unsigned char gStopProResp;
extern unsigned short gDrLampId;  /* �����۷��� */
extern unsigned char gDrLampCmd;
#endif
static UINT8_S CalcCtTrainOccLogicSecBuff(const UINT16_S trainId,UINT16_S *pLogicNum,UINT16_S trainSectionOfAcBuff[]);
static UINT8_S ProcessRouteStopConfirmMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* ���������� ������ݴ���
* ����˵���� ��
* ����ֵ  �� ��      
*/
void OutputDataProcess(void)
{
#ifdef SYS_TYPE_WINDOWS
    gStopProReq = GetRouteStopReq(gStopProRouteId);
    SetRouteStopConfirm(gStopProRouteId,gStopProResp);

    if (0x55u == gDrLampCmd)
    {
        /* ���� */
        SetDRLampCommand(gDrLampId,DR_LAMP_TWINKLE_STATUS);
    }
    else if (0xaau == gDrLampCmd)
    {
        /* �ȵ� */
        SetDRLampCommand(gDrLampId,DR_LAMP_STEADY_STATUS);
    }
    else
    {

    }
#endif
    /*����ZC���CI������*/
    CiOutputDataProcess();

    /*����ZC���NZC������*/
    NZcOutputDataProcess();

    /*����ZC�������ATP������*/
    TrainOutputDataProcess();

    /*����ZC���ATS������*/
    AtsOutputDataProcess();

    /*����ZC���Ntp����*/
    NtpOutputDataProcess();
}

/*
* ���������� �������CI������
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S CiOutputDataProcess(void)
{
    UINT8_S commTragetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {0U};
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*��ʼ��*/
    MemorySet(&commTargetIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    /*��ȡͨ�Ŷ�������*/
    commTragetNum = GetSingleCommTargetTypeSum(INNER_DEVTYPE_CI);
	
    /*��ȡͨ�Ŷ���ID����*/
    tempRtn = GetSingleCommTargetIdBuff(INNER_DEVTYPE_CI,((UINT8_S)(SINGLE_TYPE_COMM_TARGET_SUM_MAX)),commTargetIdBuff);

    if (RETURN_SUCCESS == tempRtn)
    {
        for (cycle = DEFAULT_ZERO;cycle < commTragetNum;cycle++)
        {
            SingleCiOutput(commTargetIdBuff[cycle]);
        }

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �������CI������
* ����˵���� const UINT16 ciId,�����ı��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S SingleCiOutput(const UINT16_S ciId)
{
    UINT8_S dataBuff[ZC_CI_COM_BYTE_SUM_MAX] = {0U};
    UINT8_S ciIndex = DEFAULT_ZERO;
    UINT16_S maskSum = DEFAULT_ZERO;
    UINT16_S maskCycle = DEFAULT_ZERO;
    UINT16_S maskId = DEFAULT_ZERO;
    UINT8_S maskType = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {0U};
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S dataLen = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S relevanceMask = DEFAULT_ZERO;
    UINT8_S tempRtnOfCtOcc = DEFAULT_ZERO;

    /*��ʼ��*/
    MemorySet(&dataBuff[0],((UINT32_S)(SIZE_UINT8 * ZC_CI_COM_BYTE_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ZC_CI_COM_BYTE_SUM_MAX)));
    MemorySet(&deviceIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_MASK_DEVICE_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_MASK_DEVICE_SUM_MAX)));

    ciIndex = GetSendCommTargetIndex(INNER_DEVTYPE_CI,ciId);

    /*��ȡ��λ���ֵ*/
    maskSum = GetSendToOtherMaskIdMax(INNER_DEVTYPE_CI,ciId);

    if ((COMM_CI_SUM_MAX > ciIndex)
        && (DEFAULT_ZERO < maskSum))
    {
        for (maskCycle = DEFAULT_ZERO;maskCycle < maskSum;maskCycle++)
        {
            /*��ȡ������λ����Ϣ*/
            maskId = GetSendMaskId(maskCycle,INNER_DEVTYPE_CI,ciId);
            maskType = GetSendMaskType(maskId,INNER_DEVTYPE_CI,ciId);
            GetSendDeviceIdBuff(maskId,INNER_DEVTYPE_CI,ciId,SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff);
            relevanceMask = GetSendRelevanceMaskId(maskId,INNER_DEVTYPE_CI,ciId);
            deviceSum = GetSendDeviceSum(maskId,INNER_DEVTYPE_CI,ciId);

            switch (maskType)
            {
            case SECTION_CT_OCC_MASK_TYPE:
                /*�����߼�����CTռ����λ*/
                tempRtnOfCtOcc = ProcessSectionCtMask(deviceSum,deviceIdBuff);

                switch (tempRtnOfCtOcc)
                {
                case 0U:
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                    break;
                case 1U:
                    SetMaskValue(relevanceMask,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                    break;
                case 2U:
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                    SetMaskValue(relevanceMask,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                    break;
                default:
                    break;
                }
                break;
            case SECTION_TSR_MASK_TYPE:
                /*��ʱ������*/
                break;
            case AC_ARB_STATUS_MASK_TYPE:
                /*�����������ARBռ����λ*/
                if (1U == ProcessAcArbMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*������*/
                }
                break;
            case AC_STOP_STATUS_MASK_TYPE:
                /*�����������ͣ����Ϣ��λ*/
                if (1U == ProcessAcStopMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*������*/
                }
                break;
            case DR_LAMP_TWINKLE_STATUS_MASK_TYPE:
                /*���������۷���������Ϣ��λ*/
                if (1U == ProcessDrLampTwinkleMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*������*/
                }
                break;
            case DR_LAMP_STEADY_STATUS_MASK_TYPE:
                /*���������۷����ȵ���Ϣ��λ*/
                if (1U == ProcessDrLampSteadyMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*������*/
                }
                break;
            case SIGNAL_CROSS_MASK_TYPE:
                /*�����źŻ���ѹ��Ϣ��λ*/
                if (1U == ProcessSignalCrossMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*������*/
                }
                break;
            case SIGNAL_LIGHT_OFF_MASK_TYPE:
                /*�����źŻ�������Ϣ��λ*/
                if (1U == ProcessSignalLightOffMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*������*/
                }
                break;
            case ROUTE_STOP_CONFIRM_MASK_TYPE:
                if(1U == ProcessRouteStopConfirmMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                }
                break;
            default:
                break;
            }
        }

        /*��д��Ϣ��CI�������*/
        if (DEFAULT_ZERO == (maskSum % 8U))
        {
            dataLen = (UINT16_S)(maskSum / 8U);
        } 
        else
        {
            dataLen =(UINT16_S)((maskSum / 8U) + 1U);
        }

        if (RETURN_SUCCESS == PackZcToCiFrameData(dataBuff,dataLen,ciId))
        {
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

    return rtnValue;
}

/*
* ���������� ��д��λֵ
* ����˵���� const UINT16 maskId,��λID
*            const UINT16_S buffSize,�����С
*            UINT8_S dataBuff[],�������
* ����ֵ  �� 0: ��дʧ��
*			 1: ��д�ɹ�      
*/
UINT8_S SetMaskValue(const UINT16_S maskId,const UINT16_S buffSize,UINT8_S dataBuff[])
{
    UINT16_S divisor = 0U;                    /*��λ���±��Ӧ���ֽ����*/
    UINT8_S remainder = 0U;                  /*��λ���±��Ӧ���ֽ��е�Bitλ*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((maskId > 0U) && (dataBuff != NULL))
    {
        /*���������λ���±��������ö�Ӧ���ֽ����*/
        divisor = (UINT16_S)(maskId / 8U);

        /*���������λ���±�ȡ�࣬��ö�Ӧ��Bitλ*/
        remainder = (UINT8_S)(maskId % 8U);

        if (buffSize > divisor)
        {
            if (0U == remainder)
            {
                dataBuff[divisor-1U] = (UINT8_S) (dataBuff[divisor-1U] | (UINT8_S)(0x01U));
            }
            else
            {
                dataBuff[divisor] = (UINT8_S) (dataBuff[divisor] | ((UINT8_S)(((UINT8_S)0x80U) >> (remainder-1U))));
            }

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

    return rtnValue;
}

/*
* ���������� ���������CI���߼�����CT�г�ռ����λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],�豸ID����
* ����ֵ  �� 0: �߼�����UTռ��
*			 1: �߼�����CTռ��
*            2: �߼����ο���
*/
UINT8_S ProcessSectionCtMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*��ȡ�߼����ε�ռ��״̬*/
        switch (GetLogicSectionOccStatus(deviceIdBuff[DEFAULT_ZERO]))
        {
        case LOGIC_SECTION_STATE_UT:
            rtnValue = 0U;
            break;
        case LOGIC_SECTION_STATE_CT:
            rtnValue = 1U;
            break;
        case LOGIC_SECTION_STATE_FREE:
            rtnValue = 2U;
            break;
        default:
            rtnValue = 0U;
            break;
        }
    } 
    else
    {
        /*����*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* ���������� ���������CI���߼�����UT�г�ռ����λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessSectionUtMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*��ȡ�߼����ε�ռ��״̬*/
        switch (GetLogicSectionOccStatus(deviceIdBuff[DEFAULT_ZERO]))
        {
        case LOGIC_SECTION_STATE_UT:
            rtnValue = 1U;
            break;
        case LOGIC_SECTION_STATE_CT:
            rtnValue = 0U;
            break;
        case LOGIC_SECTION_STATE_FREE:
            rtnValue = 1U;
            break;
        default:
            rtnValue = 0U;
            break;
        }
    } 
    else
    {
        /*����*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* ���������� ���������CI�ļ�������ARB��λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessAcArbMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;

    for (cycle = 0U;cycle < deviceSum;cycle++)
    {
        if (AC_ARB_OCC_STATUS == GetAcArbFlag(deviceIdBuff[cycle]))
        {
            rtnValue = 1U;
            break;
        } 
        else
        {
            /*������*/
        }
    }

    return rtnValue;
}

/*
* ���������� ���������CI�ļ�������ͣ����λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessAcStopMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S i = DEFAULT_ZERO;
    UINT8_S rtn = RETURN_ERROR;

    /* pbw 2017.5.16 ��1��ͣ����λ���Թ���1��3���������� */
    if (DEFAULT_ZERO < deviceSum)
    {
        /* ��������λ���������м������� */
        for(i = DEFAULT_ZERO;i < deviceSum;i++)
        {
            /* �����������ͣ��״̬ */
            rtn = JudgeAcStopStatus(deviceIdBuff[i]);

            if(RETURN_SUCCESS == rtn)
            {
                rtnValue = 1U;
                break;
            }
        }
    } 
    else
    {
        /* ���� */
        rtnValue = 0U;
    }

    return rtnValue;

#if 0
    if ((1U == deviceSum) || (2U == deviceSum))
    {
        /*�����������ͣ��״̬*/
        switch (JudgeAcStopStatus(deviceIdBuff[DEFAULT_ZERO]))
        {
        case 0U:
            rtnValue = 0U;
            break;
        case 1U:
            rtnValue = 1U;
            break;
        default:
            rtnValue = 0U;
            break;
        }
    } 
    else
    {
        /*����*/
        rtnValue = 0U;
    }

    return rtnValue;

#endif
}

/*
* ���������� ���������CI�������۷���������λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessDrLampTwinkleMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*��ȡ�����۷�������״̬*/
        switch (GetDRLampCommand(deviceIdBuff[DEFAULT_ZERO]))
        {
        case DR_LAMP_TWINKLE_STATUS:
            rtnValue = 1U;
            break;
        case DR_LAMP_STEADY_STATUS:
            rtnValue = 0U;
            break;
        default:
            rtnValue = 0U;
            break;
        }
    } 
    else
    {
        /*����*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* ���������� ���������CI�������۷����ȵ���λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessDrLampSteadyMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*��ȡ�����۷�������״̬*/
        switch (GetDRLampCommand(deviceIdBuff[DEFAULT_ZERO]))
        {
        case DR_LAMP_TWINKLE_STATUS:
            rtnValue = 0U;
            break;
        case DR_LAMP_STEADY_STATUS:
            rtnValue = 1U;
            break;
        default:
            rtnValue = 0U;
            break;
        }
    } 
    else
    {
        /*����*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* ���������� ���������CI���źŻ���ѹ��Ϣ��λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessSignalCrossMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*��ȡ�źŻ���ѹ״̬*/
        switch (GetSignalCrossStatus(deviceIdBuff[DEFAULT_ZERO]))
        {
        case SIGNAL_TRAIN_ALREADY_CROSS:
            rtnValue = 1U;
            break;
        case SIGNAL_TRAIN_NOT_CROSS:
            rtnValue = 0U;
            break;
        default:
            rtnValue = 0U;
            break;
        }
    } 
    else
    {
        /*����*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* ���������� ���������CI���źŻ�������Ϣ��λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessSignalLightOffMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*��ȡ�źŻ�����״̬*/		
        switch (GetSignalLightOffStatus(deviceIdBuff[DEFAULT_ZERO]))
        {
        case SIGNAL_LIGHT_COMMAND:
            rtnValue = 0U;
            break;
        case SIGNAL_OFF_COMMAND:
            rtnValue = 1U;
            break;
        default:
            rtnValue = 0U;
            break;
        }

    } 
    else
    {
        /*����*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* ���������� �������NZC������
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
void NZcOutputDataProcess(void)
{
    UINT8_S commTragetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {0U};
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S cycle = 0U;

    MemorySet(&commTargetIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    /*��ȡͨ�Ŷ�������*/
    commTragetNum = GetSingleCommTargetTypeSum(INNER_DEVTYPE_ZC);

    /*��ȡͨ�Ŷ���ID����*/
    tempRtn = GetSingleCommTargetIdBuff(INNER_DEVTYPE_ZC,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff);

    if (RETURN_SUCCESS == tempRtn)
    {
        for (cycle = 0U;cycle < commTragetNum;cycle++)
        {
            NextZcOutput(commTargetIdBuff[cycle]);
        }
    } 
    else
    {
        /*������*/
    }
}

/*
* ���������� �����������NZC������
* ����˵���� const UINT16 nZcId,ZCID
* ����ֵ  �� ��     
*/
void NextZcOutput(const UINT16_S nZcId)
{
    UINT16_S dataIndex = DEFAULT_ZERO;
    UINT8_S pBuff[ZC_NZC_COM_BYTE_SUM_MAX] = {0U};
    UINT16_S packErrorFlag = DEFAULT_ZERO;

    /*��ʼ��*/
    MemorySet(&pBuff[0],((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)),0U,((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)));

    /*�ϰ�����Ϣ���*/
    if (RETURN_SUCCESS == NextZcObsMsgPack(nZcId,pBuff,&dataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_1);
    }

    /*��ʱ������Ϣ���*/
    if (RETURN_SUCCESS == NextZcTsrMsgPack(nZcId,pBuff,&dataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_2);
    }

    /*�г���Ϣ���*/
    if (RETURN_SUCCESS == NextZcTrainAndMaMsgPack(nZcId,pBuff,&dataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_3);
    }

    /*����֡����д�뻺����*/
    if (RETURN_SUCCESS == PackZcToNzcFrameData(pBuff,dataIndex,nZcId))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_4);
    }

    LogPrintf(1U,"NZcPack Error=%d\n",packErrorFlag); 
}

/*
* ���������� д���������NZC����λ����
* ����˵���� UINT8 bitValue,��λֵ
*            UINT16_S  bitIndex,��λ�±�
*            UINT8_S baseAddr[],������ݻ���ַ
* ����ֵ  �� ��     
*/
void  WriteZcBitValue(UINT8_S bitValue,UINT16_S  bitIndex,UINT8_S baseAddr[])
{
    UINT8_S  divisor = 0U;                    /*��λ���±��Ӧ���ֽ����*/
    UINT8_S  remainder = 0U;                  /*��λ���±��Ӧ���ֽ��е�Bitλ*/
    UINT8_S  switchover = 0U;                 /*��λ��ת���м����*/

    /*���������λ���±��������ö�Ӧ���ֽ����*/
    divisor = (UINT8_S)((2U * (bitIndex - 1U)) / 8U);

    /*��ȡ����*/
    switchover = (UINT8_S)((bitIndex - 1U) / 4U);

    /*���������λ���±�ȡ�࣬��ö�Ӧ��Bitλ*/
    remainder = (UINT8_S)((2U * ((bitIndex - (switchover * 4U)) - 1U)) % 8U);


    /*��д��λֵ*/
    /*lint -e701*/
    baseAddr[divisor] =  (UINT8_S)(baseAddr[divisor] | ((UINT8_S)(bitValue << remainder)));
    /*lint +e701*/
}

/*
* ���������� �����������NZC������
* ����˵���� const UINT16 nZcId,ZCID
*			 UINT8_S *pBuff,�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�    
*/
UINT8_S NextZcObsMsgPack(const UINT16_S zcId,UINT8_S *pBuff, UINT16_S *dataIndex)
{
    UINT16_S tempDataIndex = 0U;
    UINT16_S packErrorFlag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*��ȡ���������±�*/
    tempDataIndex = (*dataIndex);

    /*�����·��Ϣ*/
    if (RETURN_SUCCESS == NextZcRouteMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_1);
    }

    /*�������������Ϣ*/
    if (RETURN_SUCCESS == NextZcOverlapMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_2);
    }

    /*����źŻ���Ϣ*/
    if (RETURN_SUCCESS == NextZcSignalMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_3);
    }

    /*���������Ϣ*/
    if (RETURN_SUCCESS == NextZcSwitchMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_4);
    }

    /*�����������Ϣ*/
    if (RETURN_SUCCESS == NextZcPsdMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_5);
    }

    /*�������ͣ����ť��Ϣ*/
    if (RETURN_SUCCESS == NextZcEsbMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_6);
    }

    /*��������۷���ť��Ϣ*/
    if (RETURN_SUCCESS == NextZcDrButtonMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_7);
    }

    /*��������۷�����Ϣ*/
    if (RETURN_SUCCESS == NextZcDrLampMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_8);
    }

    /*���������Ϣ*/
    if (RETURN_SUCCESS == NextZcAcMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*������*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_9);
    }

    if (DEFAULT_ZERO == packErrorFlag)
    {
        /*���������±�*/
        (*dataIndex) = tempDataIndex;
        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    /* LogPrintf(1U,"NextZcObsMsgPack Error=%d\n",packErrorFlag); */
    return rtnValue;
}

/*
* ���������� �������ZC�����ϰ����·������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcRouteMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    tempDataIndex = (*dataIndex);

    /*��ȡ��λ��Ϣ*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_ROUTE,&localObsNum);
    pObsStru  = GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_ROUTE);

    if (NULL != pObsStru )
    {
        /*��д�����·����*/
        ShortToChar(localObsNum, &pBuff[tempDataIndex]);
        tempDataIndex = tempDataIndex + 2U;

        /*�����·��Ϣ*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*��ȡ��·״̬*/
            switch (GetRouteStatus(obsId))
            {
            case ROUTE_STATE_SET:
                WriteZcBitValue(0x01U,bitIndex,&pBuff[tempDataIndex]);
                break;
            case ROUTE_STATE_UNSET:
                WriteZcBitValue(0x02U,bitIndex,&pBuff[tempDataIndex]);
                break;
            default:
                WriteZcBitValue(0x00U,bitIndex,&pBuff[tempDataIndex]);
                break;
            }

        }

        tempDataIndex += (((UINT16_S)((2U * localObsNum) / 8U)) + 1U);

        /*��������±�*/
        (*dataIndex) = tempDataIndex;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �������ZC�����ϰ���������Σ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcOverlapMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    tempDataIndex = (*dataIndex);

    /*��ȡ��λ��Ϣ*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_OVERLAP,&localObsNum);
    pObsStru  =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_OVERLAP);

    /*��д����ϰ�������*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*�������������Ϣ*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*��ȡ��������״̬*/
            switch (GetOverlapStatus(obsId))
            {
            case OVERLAP_STATE_SET:
                WriteZcBitValue(0x01U,bitIndex,&pBuff[tempDataIndex]);
                break;
            case OVERLAP_STATE_UNSET:
                WriteZcBitValue(0x02U,bitIndex,&pBuff[tempDataIndex]);
                break;
            default:
                WriteZcBitValue(0x00U,bitIndex,&pBuff[tempDataIndex]);
                break;
            }       
        }

        tempDataIndex += (((2U * localObsNum) / 8U) + 1U);

        /*��������±�*/
        (*dataIndex) = tempDataIndex;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �������ZC�����ϰ���źŻ�������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcSignalMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    tempDataIndex = (*dataIndex);

    /*��ȡ��λ��Ϣ*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_SIGNAL,&localObsNum);
    pObsStru =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_SIGNAL);

    /*��д����ϰ�������*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*����źŻ���Ϣ*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*��ȡ�źŻ�״̬*/
            switch (GetSignalStatus(obsId))
            {
            case SIGNAL_STATE_PASS:
                WriteZcBitValue(0x01U,bitIndex,&pBuff[tempDataIndex]);
                break;
            case SIGNAL_STATE_STOP:
                WriteZcBitValue(0x02U,bitIndex,&pBuff[tempDataIndex]);
                break;
            default:
                WriteZcBitValue(0x00U,bitIndex,&pBuff[tempDataIndex]);
                break;
            }

        }

        tempDataIndex += (((2U * localObsNum) / 8U) + 1U);

        /*��������±�*/
        (*dataIndex) = tempDataIndex;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �������ZC�����ϰ����������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcSwitchMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S stateBitIndex = DEFAULT_ZERO;
    UINT16_S lockBitIndex = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    tempDataIndex = (*dataIndex);

    /*��ȡ��λ��Ϣ*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_POINT,&localObsNum);
    pObsStru =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_POINT);

    /*��д����ϰ�������*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*���������Ϣ*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            stateBitIndex = pObsStru[i].StateBitIndex;

            /*��ȡ����λ��״̬*/
            switch (GetSwitchPosStatus(obsId))
            {
            case SWITCH_STATE_MAIN:
                WriteZcBitValue(0x01U,stateBitIndex,&pBuff[tempDataIndex]);
                break;
            case SWITCH_STATE_SIDE:
                WriteZcBitValue(0x02U,stateBitIndex,&pBuff[tempDataIndex]);
                break;
            case SWITCH_STATE_LOSE:
                WriteZcBitValue(0x03U,stateBitIndex,&pBuff[tempDataIndex]);
                break;
            default:
                WriteZcBitValue(0x00U,stateBitIndex,&pBuff[tempDataIndex]);
                break;
            }

            lockBitIndex = pObsStru [i].LockBitIndex;

            /*��ȡ��������״̬*/
            switch (GetSwitchLock(obsId))
            {
            case SWITCH_STATE_LOCK:
                WriteZcBitValue(0x02U,lockBitIndex,&pBuff[tempDataIndex]);
                break;
            case SWITCH_STATE_UNLOCK:
                WriteZcBitValue(0x01U,lockBitIndex,&pBuff[tempDataIndex]);
                break;
            default:
                WriteZcBitValue(0x00U,lockBitIndex,&pBuff[tempDataIndex]);
                break;
            }

        }

        tempDataIndex += (((4U * localObsNum) / 8U) + 1U);

        /*��������±�*/
        (*dataIndex) = tempDataIndex;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �������ZC�����ϰ�������ţ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcPsdMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    tempDataIndex = (*dataIndex);

    /*��ȡ��λ��Ϣ*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_PSD,&localObsNum);
    pObsStru =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_PSD);

    /*��д����ϰ�������*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*�����������Ϣ*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*��ȡ������״̬*/
            switch (GetPsdStatus(obsId))
            {
            case PSD_STATE_CLOSE:
                WriteZcBitValue(0x01U,bitIndex,&pBuff[tempDataIndex]);
                break;
            case PSD_STATE_OPEN:
                WriteZcBitValue(0x02U,bitIndex,&pBuff[tempDataIndex]);
                break;
            default:
                WriteZcBitValue(0x00U,bitIndex,&pBuff[tempDataIndex]);
                break;
            }          
        }

        tempDataIndex += (((2U * localObsNum) / 8U) + 1U);

        /*��������±�*/
        (*dataIndex) = tempDataIndex;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �������ZC�����ϰ������ͣ����ť������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcEsbMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    tempDataIndex = (*dataIndex);

    /*��ȡ��λ��Ϣ*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_ESB,&localObsNum);
    pObsStru  =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_ESB);

    /*��д����ϰ�������*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*�������ͣ����ť��Ϣ*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*��ȡ����ͣ����ť״̬*/
            switch (GetEsbStatus(obsId))
            {
            case ESB_STATE_UP:
                WriteZcBitValue(0x01U,bitIndex,&pBuff[tempDataIndex]);
                break;
            case ESB_STATE_DOWN:
                WriteZcBitValue(0x02U,bitIndex,&pBuff[tempDataIndex]);
                break;
            default:
                WriteZcBitValue(0x00U,bitIndex,&pBuff[tempDataIndex]);
                break;
            }          
        }

        tempDataIndex += (((2U * localObsNum) / 8U) + 1U);

        /*��������±�*/
        (*dataIndex) = tempDataIndex;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �������ZC�����ϰ�������۷���ť������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcDrButtonMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru  = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    tempDataIndex = (*dataIndex);

    /*��ȡ��λ��Ϣ*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_DRB,&localObsNum);
    pObsStru  =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_DRB);

    /*��д����ϰ�������*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*��������۷���ť��Ϣ*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*��ȡ�������۷���ť״̬*/
            switch (GetDRButtonStatus(obsId))
            {
            case DR_BUTTON_STATE_UP:
                WriteZcBitValue(0x01U,bitIndex,&pBuff[tempDataIndex]);
                break;
            case DR_BUTTON_STATE_DOWN:
                WriteZcBitValue(0x02U,bitIndex,&pBuff[tempDataIndex]);
                break;
            default:
                WriteZcBitValue(0x00U,bitIndex,&pBuff[tempDataIndex]);
                break;
            }
        }

        tempDataIndex += (((2U * localObsNum) / 8U) + 1U);

        /*��������±�*/
        (*dataIndex) = tempDataIndex;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �������ZC�����ϰ�������۷��ƣ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcDrLampMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    tempDataIndex = (*dataIndex);

    /*��ȡ��λ��Ϣ*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_DRL,&localObsNum);
    pObsStru  =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_DRL);

    /*��д����ϰ�������*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*��������۷�����Ϣ*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*��ȡ�����۷���״̬*/
            switch (GetDRLampCommand(obsId))
            {
            case DR_LAMP_STEADY_STATUS:
                WriteZcBitValue(0x01U,bitIndex,&pBuff[tempDataIndex]);
                break;
            case DR_LAMP_TWINKLE_STATUS:
                WriteZcBitValue(0x02U,bitIndex,&pBuff[tempDataIndex]);
                break;
            default:
                WriteZcBitValue(0x00U,bitIndex,&pBuff[tempDataIndex]);
                break;
            }      
        }

        tempDataIndex += (((2U * localObsNum) / 8U) + 1U);

        /*��������±�*/
        (*dataIndex) = tempDataIndex;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �������ZC�����ϰ���������Σ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcAcMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S i = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru  = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S trainNumInAc = DEFAULT_ZERO;
    UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC] = {0U};
    UINT8_S cycleTrain = DEFAULT_ZERO;

    MemorySet(&trainSequenceBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)),
        0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_TRAINOFAC)));

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        tempDataIndex = (*dataIndex);

        /*��ȡ��λ��Ϣ*/
        if (RETURN_SUCCESS == GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_AC,&localObsNum))
        {
            pObsStru  =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_AC);

            /*��д����ϰ�������*/
            ShortToChar(localObsNum, &pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if (NULL != pObsStru )
            {
                /*�������������Ϣ*/
                for (i = 0U;i < localObsNum;i++)
                {
                    obsId = pObsStru[i].ObsId;
                    bitIndex = pObsStru[i].StateBitIndex;

                    /*��ȡ�������η���״̬*/
                    switch (GetAcDirection(obsId))
                    {
                    case AC_DIR_UP_STATUS:
                        WriteZcBitValue(0x02U,bitIndex,&pBuff[tempDataIndex]);
                        break;
                    case AC_DIR_DOWN_STATUS:
                        WriteZcBitValue(0x01U,bitIndex,&pBuff[tempDataIndex]);
                        break;
                    default:
                        WriteZcBitValue(0x01U,bitIndex,&pBuff[tempDataIndex]);
                        break;
                    }

                    /*��ȡ��������ռ��״̬*/
                    switch (GetAcStatusNow(obsId))
                    {
                    case AC_OCC_STATUS:
                        WriteZcBitValue(0x02U,bitIndex+1U,&pBuff[tempDataIndex]);
                        break;
                    case AC_FREE_STATUS:
                        WriteZcBitValue(0x01U,bitIndex+1U,&pBuff[tempDataIndex]);
                        break;
                    default:
                        WriteZcBitValue(0x02U,bitIndex+1U,&pBuff[tempDataIndex]);
                        break;
                    }              

                    /*��ȡ������������״̬*/
                    switch (GetAcBelock(obsId))
                    {
                    case AC_UNLOCK_STATUS:
                        WriteZcBitValue(0x01U,bitIndex+2U,&pBuff[tempDataIndex]);
                        break;
                    case AC_LOCK_STATUS:
                        WriteZcBitValue(0x02U,bitIndex+2U,&pBuff[tempDataIndex]);
                        break;
                    default:
                        WriteZcBitValue(0x03U,bitIndex+2U,&pBuff[tempDataIndex]);
                        break;
                    }

                    /*��ȡ��������UT״̬*/
                    switch (GetAcUtFlag(obsId))
                    {
                    case AC_UT_FREE_STATUS:
                        WriteZcBitValue(0x01U,bitIndex+3U,&pBuff[tempDataIndex]);
                        break;
                    case AC_UT_OCC_STATUS:
                        WriteZcBitValue(0x02U,bitIndex+3U,&pBuff[tempDataIndex]);
                        break;
                    default:
                        WriteZcBitValue(0x02U,bitIndex+3U,&pBuff[tempDataIndex]);
                        break;
                    }

                    /*��ȡ��������arb״̬*/
                    switch (GetAcArbFlag(obsId))
                    {
                    case AC_ARB_FREE_STATUS:
                        WriteZcBitValue(0x01U,bitIndex+4U,&pBuff[tempDataIndex]);
                        break;
                    case AC_ARB_OCC_STATUS:
                        WriteZcBitValue(0x02U,bitIndex+4U,&pBuff[tempDataIndex]);
                        break;
                    default:
                        WriteZcBitValue(0x01U,bitIndex+4U,&pBuff[tempDataIndex]);
                        break;
                    }

                    /*����2���ֽ�״̬��Ϣ*/
                    tempDataIndex = tempDataIndex + 2U;

                    /*��дUT������Ϣ*/
                    pBuff[tempDataIndex] = GetAcUtRedundance(obsId);
                    tempDataIndex = tempDataIndex + 1U;

                    /*��дARB������Ϣ*/
                    pBuff[tempDataIndex] = GetAcArbRedundance(obsId);
                    tempDataIndex = tempDataIndex + 1U;

                    /*��д�г�����*/
                    trainNumInAc = GetAcTrainOfAcNum(obsId);
                    pBuff[tempDataIndex] = trainNumInAc;
                    tempDataIndex = tempDataIndex + 1U;

                    /*��ȡ�������г�����*/
                    if (RETURN_SUCCESS == GetAcTrainSequenceBuff(obsId,SIZE_MAX_TRAINOFAC,trainSequenceBuff))
                    {
                        for (cycleTrain = DEFAULT_ZERO;cycleTrain < trainNumInAc;cycleTrain++)
                        {
                            /*��д�������г�����*/
                            ShortToChar(trainSequenceBuff[cycleTrain], &pBuff[tempDataIndex]);
                            tempDataIndex = tempDataIndex + 2U;
                        }
                    } 
                    else
                    {
                        /* ������ */
                    }

                }

                /*��������±�*/
                (*dataIndex) = tempDataIndex;

                rtnValue = RETURN_SUCCESS;
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

/*
* ���������� �������ZC������ʱ��������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcTsrMsgPack(const UINT16_S zcId,UINT8_S pBuff[], UINT16_S *dataIndex)
{
    UINT8_S tsrNum = DEFAULT_ZERO;
    UINT8_S tsrSpeed = DEFAULT_ZERO;
    UINT16_S logicNum = DEFAULT_ZERO;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S cycleTsr = DEFAULT_ZERO;
    UINT8_S cycleLogic = DEFAULT_ZERO;
    UINT16_S  sectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX] = {0U};
    UINT8_S zcIndexInTsr = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT16_S countTsrNum = DEFAULT_ZERO;
    UINT16_S cycleOfChangeAreaLogic = DEFAULT_ZERO;
    UINT16_S changeAreaLogicNum = DEFAULT_ZERO;
    UINT16_S changeAreaLogicIdBuff[CHANGE_AREA_LOGIC_MAX] = {0U};
    UINT8_S changeAreaRtn = DEFAULT_ZERO;
    UINT8_S cycleTsrOfLogic = DEFAULT_ZERO;
    UINT8_S flagWrite = DEFAULT_ZERO;
    UINT16_S tsrNumIndex = DEFAULT_ZERO;

    MemorySet(&sectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TSR_SECTION_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TSR_SECTION_SUM_MAX)));

    localZcId = GetLocalZcId();

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*��ȡ�л���·�߼�����*/
        changeAreaRtn = CalculatChangeAreaLogicInfoOfZc(zcId,&changeAreaLogicNum,changeAreaLogicIdBuff);

        /*��ȡ�±�*/
        tempDataIndex = (*dataIndex);

        /*������ʱ���ٸ����±�*/
        tsrNumIndex = tempDataIndex;
        tempDataIndex = tempDataIndex + 1u;

        /*��ȡ�洢��Tsr�ṹ�и�ZCid��Ӧ�±�*/
        zcIndexInTsr = GeZcIdOfTsrBufIndex(localZcId);

        if (zcIndexInTsr < TSR_BUFF_SUM_MAX)
        {
            /*��ȡ��ʱ���ٸ���*/
            tsrNum = GetZcIdOfTsrNum(localZcId);

            for (cycleTsr = 0U;cycleTsr < tsrNum;cycleTsr++)
            {
                /*��ȡ������ʱ�����ٶ�*/
                tsrSpeed = GetSingleTsrDataOfSpeed(localZcId,((UINT16_S)cycleTsr));

                /*��ȡ������ʱ���ٰ������߼�������Ϣ*/
                logicNum = GetSingleTsrDataOfSectionNum(localZcId,((UINT16_S)cycleTsr));

                if (RETURN_SUCCESS == GetSingleTsrDataOfSectionBuff(localZcId,((UINT16_S)cycleTsr),SINGLE_TSR_SECTION_SUM_MAX,sectionIdBuff))
                {
                    if (RETURN_ERROR == changeAreaRtn)
                    {
                        /*��ȡʧ��,��д�������߼�����*/
                        /*�����ʱ������Ϣ*/
                        ShortToChar(((UINT16_S)tsrSpeed), &pBuff[tempDataIndex]);
                        tempDataIndex = tempDataIndex + 2U;

                        ShortToChar(logicNum, &pBuff[tempDataIndex]);
                        tempDataIndex = tempDataIndex + 2U;

                        for (cycleLogic = DEFAULT_ZERO;cycleLogic < logicNum;cycleLogic++)
                        {
                            ShortToChar(sectionIdBuff[cycleLogic], &pBuff[tempDataIndex]);
                            tempDataIndex = tempDataIndex + 2U;
                        }

                        countTsrNum++;
                    } 
                    else
                    {
                        /*��ѯ�ɹ�,�ж��Ƿ���л������غ�*/
                        for (cycleOfChangeAreaLogic = DEFAULT_ZERO;cycleOfChangeAreaLogic < changeAreaLogicNum;cycleOfChangeAreaLogic++)
                        {
                            for (cycleTsrOfLogic = DEFAULT_ZERO;cycleTsrOfLogic < logicNum;cycleTsrOfLogic++)
                            {
                                if (changeAreaLogicIdBuff[cycleOfChangeAreaLogic] == sectionIdBuff[cycleTsrOfLogic])
                                {
                                    /*���غ�,��д��ʱ����*/
                                    /*�����ʱ������Ϣ*/
                                    ShortToChar(((UINT16_S)tsrSpeed), &pBuff[tempDataIndex]);
                                    tempDataIndex = tempDataIndex + 2U;

                                    ShortToChar(logicNum, &pBuff[tempDataIndex]);
                                    tempDataIndex = tempDataIndex + 2U;

                                    for (cycleLogic = DEFAULT_ZERO;cycleLogic < logicNum;cycleLogic++)
                                    {
                                        ShortToChar(sectionIdBuff[cycleLogic], &pBuff[tempDataIndex]);
                                        tempDataIndex = tempDataIndex + 2U;
                                    }

                                    countTsrNum++;
                                    flagWrite = FLAG_SET;
                                    break;
                                } 
                                else
                                {
                                    /* �������� */
                                }
                            }

                            if (flagWrite == FLAG_SET)
                            {
                                break;
                            } 
                            else
                            {
                                /* ������ */
                            }
                        }
                    }
                }
                else
                {
                    /* ������ */
                }       
            }	
        } 
        else
        {
            /*Do nothing currently !*/
        }

        /*��д��ʱ��������*/
        pBuff[tsrNumIndex] = (UINT8_S)countTsrNum;

        /*�����±�*/
        (*dataIndex) = tempDataIndex;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �����������NZC���г�����
* ����˵���� const UINT16 trainId,�г�ID
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�     
*/
UINT8_S NextZcTrainMsgPack(const UINT16_S trainId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT8_S retVal = RETURN_ERROR;/*��������ֵ*/
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S getValue = DEFAULT_ZERO;
    TrainInfoStruct singleTrainInfoSrtu;
    UINT16_S trainCommCycle = DEFAULT_ZERO;
    UINT8_S trainCommStatus = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*��ȡ�±�*/
        tempDataIndex = (*dataIndex);

        getValue = GetSingleTrainInfo(trainId,&singleTrainInfoSrtu);
        trainCommCycle = GetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId);
        trainCommStatus = GetCommTargetStatus(INNER_DEVTYPE_TRAIN,trainId);

        /*��д�г�����*/
        if ((RETURN_ERROR != getValue)
            && (DEFAULT_UINT16_VALUE != trainCommCycle)
            && (DEFAULT_UINT8_VALUE != trainCommStatus))
        {
            pBuff[tempDataIndex] = singleTrainInfoSrtu.TrainType;
            tempDataIndex = tempDataIndex + 1U;

            /*��д��ǰ�ܿ�ZCID*/
            ShortToChar(singleTrainInfoSrtu.TrainControlZC,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);	

            /*��д�г���ǰ���ں�*/
            LongToChar(singleTrainInfoSrtu.TrainCycle,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);	

            /*��д�г�ͨ�ż�ʱλ*/
            pBuff[tempDataIndex] = (UINT8_S)trainCommCycle;
            tempDataIndex = tempDataIndex + 1U;

            /*��д������ZC��ͨ��״̬*/
            pBuff[tempDataIndex] = trainCommStatus;	
            tempDataIndex = tempDataIndex + 1U;

            /*��д�г�ǰ�˿��ɱ�־*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.SuspectHead;	
            tempDataIndex = tempDataIndex + 1U;

            /*��д�г���˿��ɱ�־*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.SuspectTail;	
            tempDataIndex = tempDataIndex + 1U;

            /*��д�г���ȫ��ͷ���ڼ�������*/
            ShortToChar(singleTrainInfoSrtu.TrainHeadAC,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*��д�г���ȫβ���ڼ�������*/
            ShortToChar(singleTrainInfoSrtu.TrainTailAC,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*��д�г��ǰ�ȫ��ͷ���ڼ�������*/
            ShortToChar(singleTrainInfoSrtu.TrainUnsafeHeadAC,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*��д�г��ǰ�ȫβ���ڼ�������*/
            ShortToChar(singleTrainInfoSrtu.TrainUnsafeTailAC,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*��д�г�ǰ����Ҫ�������źŻ�*/
            ShortToChar(singleTrainInfoSrtu.TrainFrontSignal,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*��д�г������źŻ�������־*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.SignalProtection;	
            tempDataIndex = tempDataIndex + 1U;

            /*��д�г���ȫλ�ýṹ��*/
            ShortToChar(singleTrainInfoSrtu.TrainSafeLocStru.TrainHeadLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            LongToChar(singleTrainInfoSrtu.TrainSafeLocStru.TrainHeadOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            ShortToChar(singleTrainInfoSrtu.TrainSafeLocStru.TrainTailLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            LongToChar(singleTrainInfoSrtu.TrainSafeLocStru.TrainTailOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*��д�г��ǰ�ȫλ�ýṹ��*/
            ShortToChar(singleTrainInfoSrtu.TrainUnSafeLocStru.TrainHeadLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            LongToChar(singleTrainInfoSrtu.TrainUnSafeLocStru.TrainHeadOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            ShortToChar(singleTrainInfoSrtu.TrainUnSafeLocStru.TrainTailLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            LongToChar(singleTrainInfoSrtu.TrainUnSafeLocStru.TrainTailOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*��ȷ�����͵���ƫ��*/
            ShortToChar(singleTrainInfoSrtu.TrainError,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*��д�г�ͷ���ǰ�ȫλ�ö�Ӧ���������з���*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainUnsafeDirection;
            tempDataIndex = tempDataIndex + 1U;

            /*��д�г�ͷ���ǰ�ȫλ��ʵ�����з���*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainRealDirection;
            tempDataIndex = tempDataIndex + 1U;

            /*��д�г���ʻģʽ��Ϣ*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainMode;
            tempDataIndex = tempDataIndex + 1U;

            /*��д�г����м�����Ϣ*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainLevel;
            tempDataIndex = tempDataIndex + 1U;

            /*��д�г�ʵ���ٶ���Ϣ*/
            ShortToChar(singleTrainInfoSrtu.TrainSpeed,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*��д�г�ͣ������ͣ����Ϣ*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainStopArea;
            tempDataIndex = tempDataIndex + 1U;

            /*��д�г������Ա�ʾ��*/		
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainIntegrity;
            tempDataIndex = tempDataIndex + 1U;

            /*��д�г�����ͣ����ʾ��Ϣ*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainEmergency;
            tempDataIndex = tempDataIndex + 1U;

            /*�����±�*/
            (*dataIndex) = tempDataIndex;
            retVal = RETURN_SUCCESS;
        }
        else
        {
            retVal = RETURN_ERROR;
        }
    } 
    else
    {
        retVal = RETURN_ERROR;
    }

    return retVal;
}

/*
* ���������� �����������NZC���г��ƶ���Ȩ����
* ����˵���� const UINT16 trainId,�г�ID
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�       
*/
UINT8_S NextZcMaMsgPack(const UINT16_S trainId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S getValue = DEFAULT_ZERO;
    UINT8_S i = DEFAULT_ZERO;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT8_S obsType = DEFAULT_ZERO;
    MaDataStruct singleMaDataStru;
    UINT16_S maLenIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*��ȡ�±�*/
        tempDataIndex = (*dataIndex);

        /*����ma�����±�*/
        maLenIndex = tempDataIndex;
        tempDataIndex++;

        getValue = GeSingleMaInfo(trainId,&singleMaDataStru);

        if (RETURN_ERROR != getValue)
        {
            /*��дMA�յ�����*/
            pBuff[tempDataIndex] = singleMaDataStru.MaEndAttribute;
            tempDataIndex = tempDataIndex + 1U;

            /*��дMA���*/
            ShortToChar(singleMaDataStru.MaHeadLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*��дMA���Offset*/
            LongToChar(singleMaDataStru.MaHeadOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*��дMA��㷽��*/
            pBuff[tempDataIndex] = singleMaDataStru.MaHeadDir;
            tempDataIndex = tempDataIndex + 1U;

            /*��дMA�յ�*/
            ShortToChar(singleMaDataStru.MaTailLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*��дMA���Offset*/
            LongToChar(singleMaDataStru.MaTailOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*��дMA��㷽��*/
            pBuff[tempDataIndex] = singleMaDataStru.MaTailDir;
            tempDataIndex = tempDataIndex + 1U;

            /*��дMA��Χ�ڵ��ϰ�������*/
            pBuff[tempDataIndex] = singleMaDataStru.ObsNum;
            tempDataIndex = tempDataIndex + 1U;

            /*ѭ����дMA��Χ�ڵ��ϰ���*/
            for(i = 0U;i < singleMaDataStru.ObsNum;i++)
            {			
                obsId = singleMaDataStru.ObsOfMAStru[i].ObsId;
                obsType = singleMaDataStru.ObsOfMAStru[i].ObsType;

                /*��дMA��Χ���ϰ��������*/
                pBuff[tempDataIndex] = obsType;
                tempDataIndex = tempDataIndex + 1U;

                /*��дMA��Χ���ϰ����ID*/
                ShortToChar(obsId,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

                /*��ȡ�ϰ��������*/
                switch(obsType)
                {
                case  OBS_TYPE_ESB:
                    {
                        /*˵�����ϰ���Ϊվ̨�����رհ�ť*/
                        /*��дMA��Χ���ϰ��ﵱǰ״̬*/
                        pBuff[tempDataIndex]= GetEsbStatus(obsId);
                        tempDataIndex = tempDataIndex + 1U;

                        /*��дMA��Χ���ϰ��������״̬��ESP������״̬����д��ǰ״̬*/
                        pBuff[tempDataIndex]= GetEsbStatus(obsId);
                        tempDataIndex = tempDataIndex + 1U;

                        break;
                    }

                case  OBS_TYPE_PSD:
                    {
                        /*˵�����ϰ���Ϊվ̨��ȫ��*/
                        /*��дMA��Χ���ϰ��ﵱǰ״̬*/
                        pBuff[tempDataIndex]= GetPsdStatus(obsId);
                        tempDataIndex = tempDataIndex + 1U;

                        /*��дMA��Χ���ϰ��������״̬��PSD������״̬����д��ǰ״̬*/
                        pBuff[tempDataIndex]= GetPsdStatus(obsId);
                        tempDataIndex = tempDataIndex + 1U;

                        break;
                    }

                case  OBS_TYPE_POINT:
                    {
                        /*˵�����ϰ���Ϊ����*/
                        /*��дMA��Χ���ϰ��ﵱǰ״̬*/
                        pBuff[tempDataIndex]= GetSwitchPosStatus(obsId);
                        tempDataIndex = tempDataIndex + 1U;

                        /*��дMA��Χ���ϰ��������״̬*/
                        /*�жϱ�����ǰ�Ƿ�����*/
                        if(FLAG_SET == GetSwitchLock(obsId))
                        {
                            /*˵��������ǰ��������״̬����дΪ��ǰ״̬*/
                            pBuff[tempDataIndex]= GetSwitchPosStatus(obsId);
                            tempDataIndex = tempDataIndex + 1U;
                        }
                        else
                        {
                            /*˵��������ǰδ���գ���дΪ�Ŀ����ݶ���*/
                            pBuff[tempDataIndex] = (UINT8_S)SWITCH_STATE_LOSE;
                            tempDataIndex = tempDataIndex + 1U;
                        }

                        break;
                    }

                default:
                    {
                        /*˵���ϰ������ʹ���*/
                        break;
                    }
                }
            }

            /*��дMA��Χ�ڵ���ʱ��������*/
            pBuff[tempDataIndex] = singleMaDataStru.TsrNum;
            tempDataIndex = tempDataIndex + 1U;

            /*ѭ������MA��Χ�ڵ���ʱ������Ϣ*/
            for(i = 0U;i < singleMaDataStru.TsrNum;i++)
            {
                /*��дMA��Χ����ʱ����ֵ*/
                ShortToChar(singleMaDataStru.TsrOfMAStru[i].TsrSpeed,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

                /*��д��ʱ������MA��Χ�غϵ�ʼ��Link*/
                ShortToChar(singleMaDataStru.TsrOfMAStru[i].TsrHeadLink,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

                /*��д��ʱ������MA��Χ�غϵ�ʼ��Offset*/
                LongToChar(singleMaDataStru.TsrOfMAStru[i].TsrHeadOffset,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

                /*��д��ʱ������MA��Χ�غϵ��ն�Link*/
                ShortToChar(singleMaDataStru.TsrOfMAStru[i].TsrTailLink,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

                /*��д��ʱ������MA��Χ�غϵ��ն�Offset*/
                LongToChar(singleMaDataStru.TsrOfMAStru[i].TsrTailOffset,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 4U);
            }

            /*��дMA����*/
            pBuff[maLenIndex] = (UINT8_S)(tempDataIndex - maLenIndex);

            /*�����±�*/
            (*dataIndex) = tempDataIndex;

            rtnValue = RETURN_SUCCESS;
        }
        else
        {
            /*��дMA����*/
            pBuff[maLenIndex] = DEFAULT_ZERO;
            rtnValue = RETURN_ERROR;
        }
    } 
    else
    {       
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� �����������NZC���г����ƶ���Ȩ����
* ����˵���� const UINT16 zcId,ZC��ID(Ԥ��)
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� RETURN_ERROR,����ʧ��
*            RETURN_SUCCESS,����ɹ�       
*/
UINT8_S NextZcTrainAndMaMsgPack(const UINT16_S zcId,UINT8_S pBuff[], UINT16_S *dataIndex)
{
    UINT8_S trainCurNum = 0U;
    UINT8_S i = 0U;
    UINT16_S trainId = 0U;
    UINT8_S trainHandOutType = 0U;
    UINT8_S changeTrainNum = 0U;
    UINT16_S tempDataIndex = 0U;
    UINT8_S maType = 0U;
    UINT16_S trainNumIndex = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if((NULL != pBuff) && (NULL != dataIndex))
    {
        /*��ȡ�±�*/
        tempDataIndex = (*dataIndex);

        /*Ԥ���г������ֶ�*/
        trainNumIndex = tempDataIndex;
        tempDataIndex += 1U;

        trainCurNum = GetTrainCurSum();

        if (SIZE_MAX_LINE_TRAIN != trainCurNum)
        {
            /*���������г�*/
            for (i = 0U;i < trainCurNum;i++)
            {
                trainId = GetTrainIdOfIndex(i);

                if (RETURN_ERROR != trainId)
                {
                    trainHandOutType = GetTrainHandoverOutType(trainId);

                    if (RETURN_UINT8_MAX_VALUE != trainHandOutType)
                    {
                        if (NZC_TRAIN_DEFAULT != trainHandOutType)
                        {
                            /*�����г�����*/
                            changeTrainNum += 1U;

                            /*��д�г�ID*/
                            ShortToChar(trainId,&pBuff[tempDataIndex]);
                            tempDataIndex += 2U;
                            /*��Ϣ֡����*/
                            pBuff[tempDataIndex] = trainHandOutType;
                            tempDataIndex += 1U;

                            if ((NZC_TRAIN_HANDOVER == trainHandOutType) || (NZC_TRAIN_MANAGENOHAND == trainHandOutType)
                                || (NZC_TRAIN_MANAGENOTAKE == trainHandOutType) || (NZC_TRAIN_HADTOOKOVER == trainHandOutType) )
                            {
                                /*��д�г����ڱ�־*/
                                pBuff[tempDataIndex] = FLAG_SET;
                                tempDataIndex += 1U;

                                /*�����г���Ϣ�������*/
                                NextZcTrainMsgPack(trainId,pBuff,&tempDataIndex);

                                /*�������MA��Ϣ�����MA������*/
                                pBuff[tempDataIndex] = FLAG_UNSET;
                                tempDataIndex += 1U;
                            }
                            else
                            {
                                /*��д�г����ڱ�־*/
                                pBuff[tempDataIndex] = FLAG_UNSET;
                                tempDataIndex += 1U;

                                /*��дMA��Ϣ���ڱ�־*/
                                pBuff[tempDataIndex] = FLAG_SET;
                                tempDataIndex += 1U;

                                /*��дMA����*/
                                maType = GetMaType(trainId);
                                switch (maType)
                                {
                                case NO_MA_TYPE:
                                case ABNORMAL_MA_TYPE:
                                    /*��дMA��Ϣ����*/
                                    pBuff[tempDataIndex] = maType;
                                    tempDataIndex += 1U;

                                    /*��дMA����Ϊ0������*/
                                    pBuff[tempDataIndex] = 0U;
                                    tempDataIndex += 1U;
                                    break;

                                case NORMAL_MA_TYPE:
                                    /*��дMA��Ϣ����*/
                                    pBuff[tempDataIndex] = maType;
                                    tempDataIndex += 1U;

                                    /*����MA��Ϣ�������*/
                                    NextZcMaMsgPack(trainId,pBuff,&tempDataIndex);
                                    break;

                                default:
                                    /*��дMA��Ϣ����*/
                                    pBuff[tempDataIndex] = ABNORMAL_MA_TYPE;
                                    tempDataIndex += 1U;

                                    /*��дMA����Ϊ0������*/
                                    pBuff[tempDataIndex] = 0U;
                                    tempDataIndex += 1U;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            /*�г����ڷ��л����״̬,��������*/
                        }
                    }
                    else
                    {
                        breakFlag = FLAG_SET;					
                        break;
                    }
                }
                else
                {
                    breakFlag = FLAG_SET;
                    break;
                }

            }
        }

        if (FLAG_SET == breakFlag)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            /*��д�г�����*/
            pBuff[trainNumIndex] = changeTrainNum;

            /*��ȡ�±�*/
            (*dataIndex) = tempDataIndex;

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
* ���������� �������Ntp������
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S NtpOutputDataProcess(void)
{
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT16_S commCycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    MemorySet(&commTargetIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    tempRtn = GetSingleCommTargetIdBuff(INNER_DEVTYPE_NTP,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff);

    if ((RETURN_SUCCESS == tempRtn)
        && (DEFAULT_ZERO != commTargetIdBuff[DEFAULT_ZERO]))
    {
        /*��֯Ntp�������*/
        /*�ж��Ƿ���Ҫ����Уʱ*/
        if (ZC_INIT_NTP_TIME_SUCC_FLAG_UNSET == GetNtpTimeSuccFlag())
        {
            /*��Ҫ����Уʱ����*/
            NtpOutputDataPack(commTargetIdBuff[DEFAULT_ZERO]);
        } 
        else
        {
            commCycle = GetCommTargetCycle(INNER_DEVTYPE_NTP,commTargetIdBuff[DEFAULT_ZERO]);

            if ((DEFAULT_ZERO == (commCycle % GetSendNtpApplyCycle()))
                && (DEFAULT_ZERO != commCycle))
            {
                /*��Ҫ����Уʱ����*/
                NtpOutputDataPack(commTargetIdBuff[DEFAULT_ZERO]);
            } 
            else
            {
                /*������*/
            }
        }
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    if (RETURN_ERROR == rtnValue)
    {
        /*Do nothing currently !*/
    }
    else
    {
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*
* ���������� ��֡��Ntp������
* ����˵���� const UINT16 commId��ID��Ϣ
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S NtpOutputDataPack(const UINT16_S commId)
{
    UINT8_S dataBuff[ZC_NTP_COM_BYTE_SUM_MAX] = {0U};
    UINT16_S dataIndex = DEFAULT_ZERO;
    UINT32_S localTime = DEFAULT_ZERO;
    UINT32_S originateTimestamp = DEFAULT_ZERO;
    UINT8_S ntpTimeZoneDiff = DEFAULT_ZERO;
    UINT32_S ntpApplyOfLocalTime = DEFAULT_ZERO;
    NTPTimeStruct tempNtpTimeStru;
    NTPTimeStruct *pRtnNtpTimeStru = NULL;
    UINT8_S rtnValue = DEFAULT_ZERO;

    MemorySet(&dataBuff[0],((UINT32_S)(sizeof(UINT8_S)* ZC_NTP_COM_BYTE_SUM_MAX)),0U,((UINT32_S)(sizeof(UINT8_S)* ZC_NTP_COM_BYTE_SUM_MAX)));
    MemorySet(&tempNtpTimeStru,((UINT32_S)(sizeof(NTPTimeStruct))),DEFAULT_ZERO,((UINT32_S)(sizeof(NTPTimeStruct))));

    /*��ȡ����*/
    localTime = GetLocalNtpTime();
    ntpTimeZoneDiff = GetNtpTimeZoneDiff();
    ntpApplyOfLocalTime = GetNtpApplyOfLocalTime();

    originateTimestamp = (UINT32_S)((localTime- (3600U * ntpTimeZoneDiff)) + ((UINT32_S)(TIME_DIFF_1970)));
    SetNtpApplyOfLocalTime(originateTimestamp);

    tempNtpTimeStru.Integer = originateTimestamp;
    SetTransmitTimestamp(tempNtpTimeStru);

    /*������УʱģʽΪ27*/
    SetWorkMode(27U);

    /*��д��Ϣ*/
    dataBuff[dataIndex] = GetWorkMode();
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = GetStratum();
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    /*��дNTPУʱ���ص���ʱ��Դ������ʱ��*/
    LongToChar(DEFAULT_ZERO,&dataBuff[dataIndex]);
    dataIndex = dataIndex + 4U;

    /*��дNTPУʱϵͳʱ����������ο�ʱ�ӵ�������*/
    LongToChar(DEFAULT_ZERO,&dataBuff[dataIndex]);
    dataIndex = dataIndex + 4U;

    /*��дNTPУʱ�ο�ʱ��Դ�ı�ʶ*/
    dataBuff[dataIndex] = (UINT8_S)DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = (UINT8_S)DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = (UINT8_S)DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = (UINT8_S)DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    /*ϵͳʱ�����һ�α��趨����µ�ʱ��*/
    pRtnNtpTimeStru = GetReferenceTimestamp();

    if (NULL != pRtnNtpTimeStru)
    {
        LongToChar(pRtnNtpTimeStru->Integer,&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        LongToChar(pRtnNtpTimeStru->Fractional,&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    /*�������յ����������뿪���صı���ʱ��*/
    pRtnNtpTimeStru = GetOriginateTimestamp();

    if ((NULL != pRtnNtpTimeStru)
        && (RETURN_ERROR != rtnValue))
    {
        LongToChar(pRtnNtpTimeStru->Integer,&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        LongToChar(pRtnNtpTimeStru->Fractional,&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    /*�����ĵ���������ķ�����ʱ��*/
    pRtnNtpTimeStru = GetReceiveTimestamp();

    if ((NULL != pRtnNtpTimeStru)
        && (RETURN_ERROR != rtnValue))
    {
        LongToChar(pRtnNtpTimeStru->Integer,&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        LongToChar(pRtnNtpTimeStru->Fractional,&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    /*Ӧ�����뿪�������ķ�����ʱ��*/
    pRtnNtpTimeStru = GetTransmitTimestamp();

    if ((NULL != pRtnNtpTimeStru)
        && (RETURN_ERROR != rtnValue))
    {
        LongToChar(pRtnNtpTimeStru->Integer,&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        LongToChar(pRtnNtpTimeStru->Fractional,&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    /*��д��Ϣ*/
    if (RETURN_SUCCESS == PackZcToNtpFrameData(dataBuff,dataIndex,commId))
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
* ���������� �����������ATP������
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S TrainOutputDataProcess(void)
{
    UINT16_S commTragetNum = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT16_S needDeleteMaNum = DEFAULT_ZERO;
    UINT16_S needDeleteMaIdBuff[COMM_TRAIN_SUM_MAX] = {0U};
    UINT8_S trainOutType = DEFAULT_ZERO;
    UINT8_S trainInType = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;

    MemorySet(&needDeleteMaIdBuff[0],((UINT32_S)(COMM_TRAIN_SUM_MAX*sizeof(UINT16_S))),
        0U,((UINT32_S)(COMM_TRAIN_SUM_MAX*sizeof(UINT16_S))));

    /*��ȡͨ�Ŷ�������*/
    commTragetNum = GetMaStatusSum();

    for (cycle = 0U;cycle < commTragetNum;cycle++)
    {
        trainId = GetMaStatusTrainId((UINT16_S)cycle);
        trainOutType = GetTrainOutType(trainId);
        trainInType = GetTrainInType(trainId);
        trainType = GetTrainType(trainId);

        /*LogPrintf(1U,"2511:%d,%d,%d,%d\n",GetTrainOutType(trainId),GetTrainInType(trainId),GetTrainType(trainId),GetMaType(trainId));*/
        if ((DEFAULT_ZERO != trainOutType) || (DEFAULT_ZERO != trainInType)
            || (DEFAULT_ZERO != trainType))
        {
            if (DEFAULT_ZERO != trainOutType)
            {
                /*�г�������Ͳ�Ϊ��*/
                switch (GetMaType(trainId))
                {
                case NORMAL_MA_TYPE:
                    /*�����ƶ���Ȩ��֯*/
                    NormalMaOutputProcess(trainId,trainOutType);

                    break;
                case ABNORMAL_MA_TYPE:
                    /*�����ƶ��ƶ���Ȩ��֯*/
                    AbnormalMaOutputProcess(trainId);

                    break;
                case 0:
                    /*������*/
                    break;
                default:
                    break;
                }
            } 
            else
            {
                /*�г��������Ϊ��,�����*/
            }
        } 
        else
        {
            /*˵���г���Ϣ��ɾ��,MA��Ϣ������,����MA��Ϣ*/
            switch (GetMaType(trainId))
            {
            case ABNORMAL_MA_TYPE:
                /*�����ƶ��ƶ���Ȩ��֯*/
                AbnormalMaOutputProcess(trainId);
                break;
            case CANCELLATION_MA_TYPE:
                /*ע�����ƶ���ȨΪ��ͷ��β,���������һ����,��Ϊ�г��ṹ���Ѿ�ɾ��,����Ҫ����һ������*/
                LogPrintf(1U,"trainOutType=%d,end=%d\n",GetTrainOutType(trainId),GetMaEndAttribute(trainId));
                if (MA_END_ATT_CBTC == GetMaEndAttribute(trainId))
                {
                    /* �۷�ʱ���µ�ע��״̬��,�����˳�CBTC����ȷ�� */
                    NormalMaOutputProcess(trainId,OUT_TRAIN_TOEXITCBTC);
                } 
                else
                {
                    /* �л�ʱ���µ�ע��״̬��,��ע������ȷ�� */
                    NormalMaOutputProcess(trainId,OUT_TRAIN_HANDOVERTOCANCEL);
                }

                break;
            default:
                break;
            }
            LogPrintf(1U,"25.001 TrainId=%d,%d,MaType=%d\n",trainId,GetTrainOutType(trainId),GetMaType(trainId));

            /*��¼��Ҫ���MA��Ϣ���г�Id*/
            needDeleteMaIdBuff[needDeleteMaNum] = trainId;
            needDeleteMaNum = needDeleteMaNum + 1U;	
        }
    }

    for (cycle = DEFAULT_ZERO;cycle < needDeleteMaNum;cycle++)
    {
        /*ɾ�����г���MA��Ϣ*/
        DeleteSingleTrainMaInfo(needDeleteMaIdBuff[cycle]);
    }

    return rtnValue;
}

/*
* ���������� �����ƶ���Ȩ�����֯
* ����˵���� const UINT16 trainId ,�г���ID
*            const UINT8_S trainOutType,�г��������
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S NormalMaOutputProcess(const UINT16_S trainId,const UINT8_S trainOutType)
{
    UINT8_S  *pTempBuf = NULL; 
    UINT16_S addIndex = DEFAULT_ZERO;
    UINT8_S dataBuff[ZC_NZC_COM_BYTE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S tempNum = DEFAULT_ZERO;
    ObsOfMAStruct obsOfMAStru[MA_AREA_OBS_SUM_MAX];
    TsrOfMAStruct tsrOfMAStru[MA_AREA_TSR_SUM_MAX];
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S maLenIndex = DEFAULT_ZERO;

    /*��ʼ��*/
    MemorySet(obsOfMAStru,((UINT32_S)(sizeof(ObsOfMAStruct)*MA_AREA_OBS_SUM_MAX)),
        DEFAULT_ZERO,((UINT32_S)(sizeof(ObsOfMAStruct)*MA_AREA_OBS_SUM_MAX)));
    MemorySet(tsrOfMAStru,((UINT32_S)(sizeof(TsrOfMAStruct)*MA_AREA_TSR_SUM_MAX)),
        DEFAULT_ZERO,((UINT32_S)(sizeof(TsrOfMAStruct)*MA_AREA_TSR_SUM_MAX)));
    MemorySet(&dataBuff[0],((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)),0U,((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)));

    if (DEFAULT_ZERO != trainId)
    {
        /*��дͳһ��Ϣ*/
        UnifiedMaOutputInfoProcess(trainId,trainOutType,&addIndex,dataBuff);

        /*����Ma����*/
        maLenIndex = addIndex;
        addIndex++;

        /*��д�ƶ���Ȩ�յ�����*/
        dataBuff[addIndex] = GetMaEndAttribute(trainId);
        addIndex = addIndex + 1U;

        /*��дMA���link*/
        pTempBuf = &dataBuff[addIndex];
        ShortToChar(GetMaHeadLink(trainId),pTempBuf);
        addIndex = addIndex + 2U;

        /* LogPrintf(1U,"22.001 TrainId=%d,Ma Info:%d,%d;%d,%d,EndType=%d\n",trainId,GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId),GetMaEndAttribute(trainId)); */

        /*��дMA���offset*/
        pTempBuf = &dataBuff[addIndex];
        LongToChar(GetMaHeadOffset(trainId),pTempBuf);
        addIndex = addIndex + 4U;

        /*��дMA��㷽��*/
        dataBuff[addIndex] = GetMaHeadDir(trainId);
        addIndex = addIndex + 1U;

        /*��дMA�յ�link*/
        pTempBuf = &dataBuff[addIndex];
        ShortToChar(GetMaTailLink(trainId),pTempBuf);
        addIndex = addIndex + 2U;

        /*��дMA�յ�offset*/
        pTempBuf = &dataBuff[addIndex];
        LongToChar(GetMaTailOffset(trainId),pTempBuf);
        addIndex = addIndex + 4U;

        /*��дMA�յ㷽��*/
        dataBuff[addIndex] = GetMaTailDir(trainId);
        addIndex = addIndex + 1U;

        /*��дMA��Χ�ڵ��ϰ�������*/
        tempNum = GetMaObsNum(trainId);
        dataBuff[addIndex] = tempNum;
        addIndex = addIndex + 1U;

        if (RETURN_SUCCESS == GetObsOfMAStru(trainId,MA_AREA_OBS_SUM_MAX,obsOfMAStru))
        {
            for (cycle = DEFAULT_ZERO;cycle < tempNum;cycle++)
            {
                /*��д�ϰ�����Ϣ*/
                dataBuff[addIndex] = obsOfMAStru[cycle].ObsType;
                addIndex = addIndex + 1U;

                pTempBuf = &dataBuff[addIndex];
                ShortToChar(obsOfMAStru[cycle].ObsId,pTempBuf);
                addIndex = addIndex + 2U;

                dataBuff[addIndex] = obsOfMAStru[cycle].ObsStatus;
                addIndex = addIndex + 1U;

                dataBuff[addIndex] = obsOfMAStru[cycle].ObsLockStatus;
                addIndex = addIndex + 1U;
            }
        } 
        else
        {
            /* �ݲ����� */
        }

        /*��дMA��Χ�ڵ���ʱ��������*/
        tempNum = GetMaTsrNum(trainId);
        dataBuff[addIndex] = tempNum;
        addIndex = addIndex + 1U;

        if (RETURN_SUCCESS == GetTsrOfMAStru(trainId,MA_AREA_TSR_SUM_MAX,tsrOfMAStru))
        {
            for (cycle = DEFAULT_ZERO;cycle < tempNum;cycle++)
            {
                /*��д��ʱ������Ϣ*/
                pTempBuf = &dataBuff[addIndex];
                ShortToChar(tsrOfMAStru[cycle].TsrSpeed,pTempBuf);
                addIndex = addIndex + 2U;

                pTempBuf = &dataBuff[addIndex];
                ShortToChar(tsrOfMAStru[cycle].TsrHeadLink,pTempBuf);
                addIndex = addIndex + 2U;

                pTempBuf = &dataBuff[addIndex];
                LongToChar(tsrOfMAStru[cycle].TsrHeadOffset,pTempBuf);
                addIndex = addIndex + 4U;

                pTempBuf = &dataBuff[addIndex];
                ShortToChar(tsrOfMAStru[cycle].TsrTailLink,pTempBuf);
                addIndex = addIndex + 2U;

                pTempBuf = &dataBuff[addIndex];
                LongToChar(tsrOfMAStru[cycle].TsrTailOffset,pTempBuf);
                addIndex = addIndex + 4U;
            }
        } 
        else
        {
            /* �ݲ����� */
        }

        /*��дma����*/
        dataBuff[maLenIndex] =(UINT8_S) ((addIndex - maLenIndex) - 1U);

        addIndex = addIndex + 4U;


        /*Ԥ��20���ֽڵı���λ*/
        addIndex = (UINT16_S)(addIndex + 20U);

        /*�������*/
        if (RETURN_SUCCESS == PackZcToTrainFrameData(dataBuff,addIndex,trainId))
        {
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

    return rtnValue;
}

/*
* ���������������ƶ��ƶ���Ȩ�����֯
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S AbnormalMaOutputProcess(const UINT16_S trainId)
{
    UINT8_S  *pTempBuf = NULL; 
    UINT16_S addIndex = DEFAULT_ZERO;
    UINT8_S dataBuff[ZC_NZC_COM_BYTE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S trainOutType = DEFAULT_ZERO;

    MemorySet(&dataBuff[0],((UINT32_S)(SIZE_UINT8 * ZC_NZC_COM_BYTE_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT8 * ZC_NZC_COM_BYTE_SUM_MAX)));

    if (DEFAULT_ZERO != trainId)
    {
        /*��дͳһ��Ϣ*/
        trainOutType = GetTrainOutType(trainId);
        UnifiedMaOutputInfoProcess(trainId,trainOutType,&addIndex,dataBuff);

        /*��MA��Ϣ֡��������Ϊ��*/
        dataBuff[addIndex] = DEFAULT_ZERO;
        addIndex = addIndex + 1U;

        /*��дZC״̬��Ϣ*/
        pTempBuf = &dataBuff[addIndex];
        LongToChar(DEFAULT_UINT32_VALUE,pTempBuf);
        addIndex = addIndex + 4U;

        /*Ԥ��20���ֽڵı���λ*/
        addIndex = addIndex + 20U;

        LogPrintf(1U,"22.002 TrainId=%d,Error Ma Info:%d,%d;%d,%d,EndType=%d\n",trainId,GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId),GetMaEndAttribute(trainId));

        /*�������*/
        if (RETURN_SUCCESS == PackZcToTrainFrameData(dataBuff,addIndex,trainId))
        {
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

    return rtnValue;
}



/*
* ����������ͳһ���ƶ���Ȩ�����Ϣ��֯
* ����˵���� const UINT16 trainId,�г�ID
*            const UINT8_S trainOutType,�г��������
*            UINT16_S * addIndex,�����±�
*            UINT8_S dataBuff[],��������
* ����ֵ  �� ��      
*/
void UnifiedMaOutputInfoProcess(const UINT16_S trainId,const UINT8_S trainOutType,UINT16_S *addIndex,UINT8_S dataBuff[])
{
    UINT8_S  *pTempBuf = NULL; 
    UINT16_S index = DEFAULT_ZERO;
    UINT8_S tempVersion[SINGLE_VERSION_LEN_MAX] = {0U};			
    UINT8_S cycle = 0U;	
    TrainSafeLocStruct trainUnsafeLocStr;
    UINT16_S drButtonId = DEFAULT_ZERO;
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S drButtonState = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;

    MemorySet(&tempVersion[0],((UINT32_S)(SINGLE_VERSION_LEN_MAX)),0U,((UINT32_S)(SINGLE_VERSION_LEN_MAX)));

    if ((NULL != addIndex) && (NULL != dataBuff))
    {
        index = (*addIndex);

        /*��дԴ��Ϣ*/
        dataBuff[index] = (UINT8_S)INNER_DEVTYPE_ZC;
        index = index + 1U;

        dataBuff[index] = (UINT8_S)GetLocalZcId();
        index = index + 1U;

        /*��дĿ����Ϣ*/
        dataBuff[index] = (UINT8_S)INNER_DEVTYPE_TRAIN;
        index = index + 1U;

        dataBuff[index] = (UINT8_S)trainId;
        index = index + 1U;

        /*��д�ƶ���Ȩ�������*/
        /*dataBuff[index] = GetTrainOutType(trainId);*/
        dataBuff[index] = trainOutType;
        index = index + 1U;

        /*����,������4���ֽ�CRC32*/
        /* index = index + 4U; */

        /*��дZC��ATP�Ƚϵ����ݰ汾����Ϣ*/
        if (RETURN_SUCCESS == GetZcAtpDataVersionData(SINGLE_VERSION_LEN_MAX,tempVersion))
        {
            for (cycle = 0U;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
            {
                dataBuff[index] = tempVersion[cycle];
                index = index + 1U;
            }
        }
        else
        {
            /* ��������д */
            index = index + SINGLE_VERSION_LEN_MAX;
        }

        if (RETURN_SUCCESS == GetTrainUnSafeLoc(trainId,&trainUnsafeLocStr))
        {
            tempRtn = CheckPointBelongDrButtonId(trainUnsafeLocStr.TrainHeadLink,trainUnsafeLocStr.TrainHeadOffset,&drButtonId);
        }
        else
        {
            drButtonId = 0U;
        }

        /*��д�����۷���ťID*/
        pTempBuf = &dataBuff[index];
        ShortToChar(drButtonId,pTempBuf);
        index = index + 2U;

        /*��д�����۷���ť״̬*/
        drButtonState = GetDRButtonStatus(drButtonId);
        if (DEFAULT_ZERO != drButtonState)
        {
            dataBuff[index] = drButtonState;
            index = index + 1U;
        } 
        else
        {
            dataBuff[index] = DEFAULT_0XFF;
            index = index + 1U;
        }

        /*��д��һ����¼ZCid*/
        if (TRAIN_STATE_HANDOVER == GetTrainStatus(trainId))
        {
            nextZcId = GetChangeLineTakeOverZcId(GetTrainChangeLineId(trainId));

            if (DEFAULT_ZERO == nextZcId)
            {
                pTempBuf = &dataBuff[index];
                ShortToChar(DEFAULT_UINT16_VALUE,pTempBuf);
                index = index + 2U;
            } 
            else
            {					    
                nextZcId = (UINT16_S)(nextZcId | (UINT16_S)(0x1e00U));

                pTempBuf = &dataBuff[index];
                ShortToChar(nextZcId,pTempBuf);
                index = index + 2U;
            }
        } 
        else
        {
            pTempBuf = &dataBuff[index];
            ShortToChar(DEFAULT_UINT16_VALUE,pTempBuf);
            index = index + 2U;
        }

        /* LogPrintf(1U,"23.001 TrainId=%d,outType=%d, Ma NextZcId=%d\n",trainId,trainOutType,ShortFromChar(&dataBuff[index-2U]));*/

        /*��������±�*/
        (*addIndex) = index;
    } 
    else
    {
        /* ������ */
    }

}

/*
* ���������� �������Ats������
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S AtsOutputDataProcess(void)/*-bye-*/
{
	UINT16_S AllTrainNum = DEFAULT_ZERO;
    UINT16_S AllTrainNumIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT32_S zcCycle = DEFAULT_ZERO;
    UINT32_S zCToATSCycleCycle = DEFAULT_ZERO;
    UINT8_S remainderValue = DEFAULT_ZERO;
	UINT8_S dataBuff[ZC_ATS_COM_BYTE_SUM_MAX] = {0U};
	UINT16_S bufIndex = DEFAULT_ZERO;
	UINT16_S msgType = DEFAULT_ZERO;
	UINT16_S reserve = DEFAULT_ZERO;
	
    MemorySet(&dataBuff[0],((UINT32_S)(SIZE_UINT8 * ZC_ATS_COM_BYTE_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT8 * ZC_ATS_COM_BYTE_SUM_MAX)));

    zcCycle = GetZcCycle();
    zCToATSCycleCycle = (UINT32_S)GetZCToATSCycleCycle();
    remainderValue = (UINT8_S)( zcCycle % zCToATSCycleCycle);

    if (DEFAULT_ZERO == remainderValue)
    {
		/*-bye- ���ա�ZC-ATS�ӿ�˵���顷�޸Ĵ���*/
		bufIndex += 2u;/*���������ܳ���2�ֽڣ�������д*/

		msgType = 0x0065U;
		ShortToChar(msgType, &dataBuff[bufIndex]);/*��������*/
		bufIndex += 2U;
			
		ShortToChar(reserve, &dataBuff[bufIndex]);/*Ԥ��*/
		bufIndex += 2U;

		ShortToChar(msgType, &dataBuff[bufIndex]);/*��������*/
		bufIndex += 2U;

        dataBuff[bufIndex] = (UINT8_S)GetLocalZcId();
        bufIndex += 1U;

        AllTrainNumIndex = bufIndex;/*�����г�����1�ֽڣ�������д*/
        bufIndex += 1U;

        /*��CBTC�г���Ϣ*/
        AllTrainNum = SectionOccFromCbtcTrain(&bufIndex,dataBuff);

        /*���CBTC�г���Ϣ*/
        AllTrainNum += SectionOccFromUnCbtcTrain(&bufIndex,dataBuff);

        /*��д�г�����*/
        dataBuff[AllTrainNumIndex] = (UINT8_S)AllTrainNum;

		/*�����ܳ���*/
		ShortToChar(bufIndex, &dataBuff[DEFAULT_ZERO]);

        if (RETURN_SUCCESS == PackZcToAtsFrameData(dataBuff,bufIndex))
        {
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

	ProcessTsrCommandsToAts();/*-bye-*/

    return rtnValue;
}

/*
* ���������� CBTC�г�ռ���߼�������֡
* ����˵���� UINT16 *addIndex,�����С;
*            UINT8_S dataBuff[],�������;
* ����ֵ  �� 0>=:�г�����     
*/
UINT8_S SectionOccFromCbtcTrain(UINT16_S *addIndex,UINT8_S dataBuff[])
{
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S trainType = DEFAULT_ZERO;
    UINT16_S tempIndex = DEFAULT_ZERO;
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S trainSectionNum = DEFAULT_ZERO;
    UINT16_S trainSectionOfAcBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
    UINT8_S cycleSection = DEFAULT_ZERO;
    UINT8_S cbtcTrainNum = DEFAULT_ZERO;
    UINT16_S  unsafeTrainHeadAC = DEFAULT_ZERO;
    UINT16_S unsafeTrainTailAC = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT16_S headAcInZcId = DEFAULT_ZERO;
    UINT16_S tailAcInZcId = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S safeHeadLink = DEFAULT_ZERO;  /* ��ȫ��ͷ����Link */
    UINT32_S safeHeadOffset = DEFAULT_ZERO;  /* ��ȫ��ͷ����ƫ���� */
    UINT16_S safeTailLink = DEFAULT_ZERO;  /* ��ȫ��β����Link */
    UINT32_S safeTailOffset = DEFAULT_ZERO;  /* ��ȫ��β����ƫ���� */
    UINT8_S acNum = 0U;
    UINT16_S acBuff[ZC_TWO_POINT_AC_NUM_MAX] = {0U};
    UINT8_S i = DEFAULT_ZERO;
    UINT16_S tmpStartLink = DEFAULT_ZERO;  /* ��ȫ��ͷ����Link */
    UINT32_S tmpStartOffset = DEFAULT_ZERO;  /* ��ȫ��ͷ����ƫ���� */
    UINT16_S tmpEndLink = DEFAULT_ZERO;  /* ��ȫ��β����Link */
    UINT32_S tmpEndOffset = DEFAULT_ZERO;  /* ��ȫ��β����ƫ���� */
    UINT8_S  rtnLogicIdNum = DEFAULT_ZERO;   /*�����߼����κ�������ֵ */
    UINT16_S sectionBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
    UINT16_S secOccIndex = DEFAULT_ZERO;
    UINT8_S  j = DEFAULT_ZERO;

    MemorySet(&trainSectionOfAcBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)),
        0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)));
    MemorySet(&acBuff[0],((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ZC_TWO_POINT_AC_NUM_MAX)));

    if ((NULL != addIndex) && (NULL != dataBuff))
    {
        tempIndex = (*addIndex);

        localZcId = GetLocalZcId();

        /*��д�г���Ϣ*/
        for (cycle = 0U;cycle < GetTrainCurSum();cycle++)
        {
#if 1
            /*��ȡ�г���Ϣ*/
            trainId = GetTrainIdOfIndex(cycle);
            trainType = GetTrainType(trainId);	
            unsafeTrainHeadAC = GetTrainUnsafeTrainHeadAC(trainId);
            unsafeTrainTailAC = GetTrainUnsafeTrainTailAC(trainId);
            headAcInZcId = GetAcBelongZcId(unsafeTrainHeadAC);
            tailAcInZcId = GetAcBelongZcId(unsafeTrainTailAC);

            if (((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType))
                && ((localZcId == headAcInZcId ) || (localZcId == tailAcInZcId)))
            {
                /*�г�λ�ڱ�ZC��Ͻ��Χ�ڵļ�������*/
                MemorySet(&trainSafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),
                    0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));
                trainSectionNum = 0u;

                /* ��ȡ�г��ķ����λ����Ϣ */
                trainDir = GetTrainUnsafeDirection(trainId);

                /*��ȡ�г���ȫλ����Ϣ*/
                if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
                {
                    safeHeadLink = trainSafeLocStru.TrainHeadLink ;
                    safeHeadOffset = trainSafeLocStru.TrainHeadOffset;
                    safeTailLink = trainSafeLocStru.TrainTailLink;
                    safeTailOffset = trainSafeLocStru.TrainTailOffset;

                    LogPrintf(1u,"Crash-U[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,safeHeadLink,safeHeadOffset,safeTailLink,safeTailOffset);
                    if (safeHeadLink == safeTailLink)
                    {
                        /*��ѯ�г�ռѹ���߼�����*/
                        trainSectionNum = CheckLogicIdBetweenPoints(3U,safeTailLink,safeTailOffset,
                            safeHeadLink,safeHeadOffset,trainDir,trainSectionOfAcBuff);
                        LogPrintf(1u,"Crash-V[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,safeHeadLink,safeHeadOffset,safeTailLink,safeTailOffset);

                    }
                    else
                    {                    
                        /* ��ѯ��β����ͷ��ռѹ�ļ������� */
                        if(1u == CheckAcOrderBetweenTwoPoints(safeTailLink,safeHeadLink,trainDir,&acNum,acBuff))
                        {
                            for (i = DEFAULT_ZERO;i < acNum;i++)
                            {
                                if(0u == i)
                                {
                                    tmpStartLink = safeTailLink;
                                    tmpStartOffset = safeTailOffset;

                                    if(RETURN_SUCCESS == CheckAcTerminalPosition(acBuff[i],(UINT16_S)trainDir,&tmpEndLink,&tmpEndOffset))
                                    {
                                        rtnLogicIdNum = CheckLogicIdBetweenPoints(3U,tmpStartLink,tmpStartLink,
                                            tmpEndLink,tmpEndOffset,trainDir,&trainSectionOfAcBuff[trainSectionNum]);

                                        if(0xffu != rtnLogicIdNum)
                                        {
                                            trainSectionNum += rtnLogicIdNum;
                                        }
                                        LogPrintf(1u,"Crash-W[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,tmpStartLink,tmpStartOffset,tmpEndLink,tmpEndOffset);
                                    }

                                }
                                else if(i == acNum - 1u)
                                {
                                    tmpEndLink = safeHeadLink;
                                    tmpEndOffset = safeHeadOffset;

                                    if(RETURN_SUCCESS == CheckAcTopPosition(acBuff[i],(UINT16_S)trainDir,&tmpStartLink,&tmpStartOffset))
                                    {
                                        rtnLogicIdNum = CheckLogicIdBetweenPoints(3U,tmpStartLink,tmpStartLink,
                                            tmpEndLink,tmpEndOffset,trainDir,&trainSectionOfAcBuff[trainSectionNum]);

                                        if(0xffu != rtnLogicIdNum)
                                        {
                                            trainSectionNum += rtnLogicIdNum;
                                        }
                                        LogPrintf(1u,"Crash-X[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,tmpStartLink,tmpStartOffset,tmpEndLink,tmpEndOffset);
                                    }
                                }
                                else
                                {
                                    if((RETURN_SUCCESS == CheckAcTopPosition(acBuff[i],(UINT16_S)trainDir,&tmpStartLink,&tmpStartOffset))
                                        && (RETURN_SUCCESS == CheckAcTerminalPosition(acBuff[i],(UINT16_S)trainDir,&tmpEndLink,&tmpEndOffset)))
                                    {
                                        rtnLogicIdNum = CheckLogicIdBetweenPoints(3U,tmpStartLink,tmpStartLink,
                                            tmpEndLink,tmpEndOffset,trainDir,&trainSectionOfAcBuff[trainSectionNum]);

                                        if(0xffu != rtnLogicIdNum)
                                        {
                                            trainSectionNum += rtnLogicIdNum;
                                        }
                                        LogPrintf(1u,"Crash-Y[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,tmpStartLink,tmpStartOffset,tmpEndLink,tmpEndOffset);
                                    }

                                }
                            }
                        }
                    }
                    LogPrintf(1u,"Crash-Z[%d],%d,%d\n",trainId,rtnLogicIdNum,trainSectionNum);

                    /* ���� */
                    j = 0u;
                    for (cycleSection = 0U;cycleSection < trainSectionNum;cycleSection++)
                    {
                        if (RETURN_SUCCESS == CalulateSwtichStateOfAcIsNeed(GetLogicSectionBelongAcId(trainSectionOfAcBuff[cycleSection])))
                        {
                            sectionBuff[j] = trainSectionOfAcBuff[cycleSection];
                            j = j + 1u;
                        }
                    }

                    if (0xffU != trainSectionNum)
                    {
                        /*��д�г�ID*/
                        dataBuff[tempIndex] = (UINT8_S)trainId;
                        tempIndex = tempIndex + 1U;

                        /*��д�г�����*/
                        dataBuff[tempIndex] = (UINT8_S)TO_ATS_LOGIC_SECTION_CT_OCC;
                        tempIndex = tempIndex + 1U;

                        /*��дռѹ�߼����θ���*/
                        /*
                        secOccIndex = tempIndex;
                        */

                        dataBuff[tempIndex] = j;
                        tempIndex = tempIndex + 1U;

                        LogPrintf(1u,"\n");
                        for (cycleSection = 0U;cycleSection < j;cycleSection++)
                        {
                            ShortToChar(sectionBuff[cycleSection],&dataBuff[tempIndex]);
                            tempIndex = (UINT16_S)(tempIndex + 2U);

                            LogPrintf(1u,"%d-",trainSectionOfAcBuff[cycleSection]);
                        }

                        LogPrintf(1u,"\n");
                        cbtcTrainNum++;
                    } 
                    else
                    {
                        /* �߼�������������,������ */
                    }
                } 
                else
                {
                    /* ��ȡ�г�λ��ʧ��,������ */
                }              
            } 
            else
            {
                /* �г����Ͳ�����Ҫ������г�λ�ò��ڱ�ZC,������ */
            }
#else
            trainId = GetTrainIdOfIndex(cycle);
            trainType = GetTrainType(trainId);	
            unsafeTrainHeadAC = GetTrainUnsafeTrainHeadAC(trainId);
            unsafeTrainTailAC = GetTrainUnsafeTrainTailAC(trainId);
            headAcInZcId = GetAcBelongZcId(unsafeTrainHeadAC);
            tailAcInZcId = GetAcBelongZcId(unsafeTrainTailAC);

            trainSectionNum = 0u;

            if (((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType))
                && ((localZcId == headAcInZcId ) || (localZcId == tailAcInZcId)))
            {
                CalcCtTrainOccLogicSecBuff(trainId,&trainSectionNum,trainSectionOfAcBuff);
            }

            if (0xffU != trainSectionNum)
            {
                /*��д�г�ID*/
                dataBuff[tempIndex] = (UINT8_S)trainId;
                tempIndex = tempIndex + 1U;

                /*��д�г�����*/
                dataBuff[tempIndex] = (UINT8_S)TO_ATS_LOGIC_SECTION_CT_OCC;
                tempIndex = tempIndex + 1U;

                /*��дռѹ�߼����θ���*/
                dataBuff[tempIndex] = (UINT8_S)trainSectionNum;
                tempIndex = tempIndex + 1U;

                LogPrintf(1u,"\n");
                for (cycleSection = 0U;cycleSection < trainSectionNum;cycleSection++)
                {
                    ShortToChar(trainSectionOfAcBuff[cycleSection],&dataBuff[tempIndex]);
                    tempIndex = (UINT16_S)(tempIndex + 2U);

                    LogPrintf(1u,"%d-",trainSectionOfAcBuff[cycleSection]);
                }
                LogPrintf(1u,"\n");
                cbtcTrainNum++;
            } 
            else
            {
                /* �߼�������������,������ */
            }
#endif


        }

        /*����±�*/
        (*addIndex) = tempIndex;

    } 
    else
    {
        /* ������ */
    }

    return cbtcTrainNum;
}

/*
* ���������� ��CBTC�г�ռ���߼�������֡
* ����˵���� UINT16 *addIndex,�����С;
*            UINT8_S dataBuff[],�������;
* ����ֵ  �� 0>=:�г�����     
*/
UINT8_S SectionOccFromUnCbtcTrain(UINT16_S *addIndex,UINT8_S dataBuff[])
{
    UINT16_S tempIndex = DEFAULT_ZERO;
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S acId = DEFAULT_ZERO;
    UINT16_S  logicSectionNum = DEFAULT_ZERO;                            
    UINT16_S logicSectionIdBuff[SIZE_MAX_SECTIONNUM] = {0U};    
    UINT8_S cycleLogicSection = DEFAULT_ZERO;
    UINT8_S utOccFlag = DEFAULT_ZERO;
    UINT8_S occLogicSectionNum = DEFAULT_ZERO;
    UINT16_S occLogicSectionNumIndex = DEFAULT_ZERO;
    UINT8_S unCbtcTrainNum = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT16_S acBelongZcId = DEFAULT_ZERO;

    if ((NULL != addIndex) && (NULL != dataBuff))
    {
        tempIndex = (*addIndex);

        localZcId = GetLocalZcId();
        for (cycle = 0U;cycle < GetAcCurSum();cycle++)
        {
            acId = GetAcId(cycle);      
            acBelongZcId = GetAcBelongZcId(acId);

            if (localZcId == acBelongZcId)
            {
                /*���ڱ�ZC*/
                utOccFlag = DEFAULT_ZERO;
                occLogicSectionNum = DEFAULT_ZERO;
                MemorySet(&logicSectionIdBuff[0],((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_SECTIONNUM)),
                    0U,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_SECTIONNUM)));

                logicSectionNum = GetAcLogicSectionNum(acId);

                if (1U == GetAcLogicSectionIdBuf(acId,SIZE_MAX_SECTIONNUM,logicSectionIdBuff))
                {
                    for (cycleLogicSection = DEFAULT_ZERO;cycleLogicSection < logicSectionNum;cycleLogicSection++)
                    {
                        if (LOGIC_SECTION_STATE_UT == GetLogicSectionOccStatus(logicSectionIdBuff[cycleLogicSection]))
                        {
                            utOccFlag = FLAG_SET;
                            break;
                        } 
                        else
                        {
                            /*������*/
                        }
                    }

                    if (FLAG_SET == utOccFlag)
                    {
                        /*��д�г�ID*/
                        dataBuff[tempIndex] = (UINT8_S)DEFAULT_ZERO;
                        tempIndex = tempIndex + 1U;

                        /*��д�г�����*/
                        dataBuff[tempIndex] = (UINT8_S)TO_ATS_LOGIC_SECTION_UT_OCC;
                        tempIndex = tempIndex + 1U;

                        occLogicSectionNumIndex = tempIndex;
                        tempIndex = tempIndex + 1U;

                        for (cycleLogicSection = DEFAULT_ZERO;cycleLogicSection < logicSectionNum;cycleLogicSection++)
                        {
                            if (LOGIC_SECTION_STATE_UT == GetLogicSectionOccStatus(logicSectionIdBuff[cycleLogicSection]))
                            {
                                ShortToChar(logicSectionIdBuff[cycleLogicSection],&dataBuff[tempIndex]);
                                tempIndex = (UINT16_S)(tempIndex + 2U);

                                occLogicSectionNum++;
                            } 
                            else
                            {
                                /*Do nothing currently !*/
                            }
                        }

                        /*��д����*/
                        dataBuff[occLogicSectionNumIndex] = occLogicSectionNum;

                        unCbtcTrainNum++;
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

        /*����±�*/
        (*addIndex) = tempIndex;
    } 
    else
    {
        /*������*/
    }

    return unCbtcTrainNum;
}

/*
* ���������� ����CBTC�г�ռ���߼�����
* ����˵���� const UINT16_S trainId,�г�ID
*          UINT16_S *pLogicNum,���ռ�õ��߼���������
*          UINT16_S trainSectionOfAcBuff[],���ռ�õ��߼���������
* ����ֵ  �� 1u,�ɹ�
*          0u,ʧ��
*/
static UINT8_S CalcCtTrainOccLogicSecBuff(const UINT16_S trainId,UINT16_S *pLogicNum,UINT16_S trainSectionOfAcBuff[])
{
    UINT8_S rtn = RETURN_ERROR;
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S safeHeadLink = DEFAULT_ZERO;  /* ��ȫ��ͷ����Link */
    UINT32_S safeHeadOffset = DEFAULT_ZERO;  /* ��ȫ��ͷ����ƫ���� */
    UINT16_S safeTailLink = DEFAULT_ZERO;  /* ��ȫ��β����Link */
    UINT32_S safeTailOffset = DEFAULT_ZERO;  /* ��ȫ��β����ƫ���� */
    UINT8_S acNum = 0U;
    UINT16_S acBuff[ZC_TWO_POINT_AC_NUM_MAX] = {0U};
    UINT8_S i = DEFAULT_ZERO;
    UINT16_S tmpStartLink = DEFAULT_ZERO;  /* ��ȫ��ͷ����Link */
    UINT32_S tmpStartOffset = DEFAULT_ZERO;  /* ��ȫ��ͷ����ƫ���� */
    UINT16_S tmpEndLink = DEFAULT_ZERO;  /* ��ȫ��β����Link */
    UINT32_S tmpEndOffset = DEFAULT_ZERO;  /* ��ȫ��β����ƫ���� */
    UINT8_S j = DEFAULT_ZERO;
    UINT8_S trainSectionNum = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainHeadAc = DEFAULT_ZERO;
    UINT16_S trainTailAc = DEFAULT_ZERO;
    UINT8_S acSwitchNum = DEFAULT_ZERO;
    UINT8_S  rtnLogicIdNum = DEFAULT_ZERO;   /*�����߼����κ�������ֵ */
    UINT16_S sectionBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};

    MemorySet(&sectionBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)),
        0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)));
    MemorySet(&trainSafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),
        0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));

    if ((RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
        && (NULL != pLogicNum) && (NULL != trainSectionOfAcBuff))
    {     
        (*pLogicNum)=0u;

        /* ��ȡ�г��ķ����λ����Ϣ */
        trainDir = GetTrainUnsafeDirection(trainId);
        trainHeadAc = GetTrainTrainHeadAC(trainId);
        trainTailAc = GetTrainTrainTailAC(trainId);

        safeHeadLink = trainSafeLocStru.TrainHeadLink ;
        safeHeadOffset = trainSafeLocStru.TrainHeadOffset;
        safeTailLink = trainSafeLocStru.TrainTailLink;
        safeTailOffset = trainSafeLocStru.TrainTailOffset;

        if (trainHeadAc == trainTailAc)
        {
            /*��ѯ�г�ռѹ���߼�����*/
            trainSectionNum = CheckLogicIdBetweenPoints(3U,safeTailLink,safeTailOffset,
                safeHeadLink,safeHeadOffset,trainDir,sectionBuff);

            LogPrintf(1u,"Crash-V[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,safeTailLink,safeTailOffset,safeHeadLink,safeTailOffset);
        }
        else
        {                    
            /* ��ѯ��β����ͷ��ռѹ�ļ������� */
            if(1u == CheckAcOrderBetweenTwoPoints(safeTailLink,safeHeadLink,trainDir,&acNum,acBuff))
            {
                for (i = DEFAULT_ZERO;i < acNum;i++)
                {
                    if(0u == i)
                    {
                        tmpStartLink = safeTailLink;
                        tmpStartOffset = safeTailOffset;

                        if(RETURN_SUCCESS == CheckAcTerminalPosition(acBuff[i],(UINT16_S)trainDir,&tmpEndLink,&tmpEndOffset))
                        {
                            rtnLogicIdNum = CheckLogicIdBetweenPoints(3U,tmpStartLink,tmpStartOffset,
                                tmpEndLink,tmpEndOffset,trainDir,&sectionBuff[trainSectionNum]);

                            if(0xffu != rtnLogicIdNum)
                            {
                                trainSectionNum += rtnLogicIdNum;
                            }

                            LogPrintf(1u,"Crash-W[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,tmpStartLink,tmpStartOffset,tmpEndLink,tmpEndOffset);
                        }
                    }
                    else if(i == acNum - 1u)
                    {
                        tmpEndLink = safeHeadLink;
                        tmpEndOffset = safeHeadOffset;

                        if(RETURN_SUCCESS == CheckAcTopPosition(acBuff[i],(UINT16_S)trainDir,&tmpStartLink,&tmpStartOffset))
                        {
                            rtnLogicIdNum = CheckLogicIdBetweenPoints(3U,tmpStartLink,tmpStartOffset,
                                tmpEndLink,tmpEndOffset,trainDir,&sectionBuff[trainSectionNum]);

                            if(0xffu != rtnLogicIdNum)
                            {
                                trainSectionNum += rtnLogicIdNum;
                            }

                            LogPrintf(1u,"Crash-X[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,tmpStartLink,tmpStartOffset,tmpEndLink,tmpEndOffset);
                        }
                    }
                    else
                    {
                        if((RETURN_SUCCESS == CheckAcTopPosition(acBuff[i],(UINT16_S)trainDir,&tmpStartLink,&tmpStartOffset))
                            && (RETURN_SUCCESS == CheckAcTerminalPosition(acBuff[i],(UINT16_S)trainDir,&tmpEndLink,&tmpEndOffset)))
                        {
                            rtnLogicIdNum = CheckLogicIdBetweenPoints(3U,tmpStartLink,tmpStartOffset,
                                tmpEndLink,tmpEndOffset,trainDir,&sectionBuff[trainSectionNum]);

                            if(0xffu != rtnLogicIdNum)
                            {
                                trainSectionNum += rtnLogicIdNum;
                            }

                            LogPrintf(1u,"Crash-Y[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,tmpStartLink,tmpStartOffset,tmpEndLink,tmpEndOffset);

                        }
                    }

                    LogPrintf(1u,"Crash-Z[%d],%d,%d\n",trainId,rtnLogicIdNum,trainSectionNum);
                }
            }
        }

        /* ���˲������������߼����� */
        if ((DEFAULT_ZERO < trainSectionNum ) && (((UINT8_S)SIZE_MAX_SECTION_OF_TRAIN) >= trainSectionNum))
        {               
            for (j = DEFAULT_ZERO;j < trainSectionNum;j++)
            {
                LogPrintf(1u,"\n");

                if (RETURN_SUCCESS == CalulateSwtichStateOfAcIsNeed(GetLogicSectionBelongAcId(sectionBuff[j])))
                {
                    LogPrintf(1u,"%d-",sectionBuff[j]);
                    trainSectionOfAcBuff[(*pLogicNum)] = sectionBuff[j];

                    (*pLogicNum) = (*pLogicNum) + 1u;
                }
            }

            rtn = RETURN_SUCCESS;
        }
    }

    return rtn;
}

/*
* ���������� ���������CI�Ľ�·ͣ����֤ȷ����λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
static UINT8_S ProcessRouteStopConfirmMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*��ȡ�źŻ�����״̬*/		
        switch (GetRouteStopConfirm(deviceIdBuff[DEFAULT_ZERO]))
        {
        case ROUTE_STOP_CONFIRM_UNSET:
            rtnValue = 0U;
            break;
        case ROUTE_STOP_CONFIRM_SET:
            rtnValue = 1U;
            break;
        default:
            rtnValue = 0U;
            break;
        }

    } 
    else
    {
        /*����*/
        rtnValue = 0U;
    }

    return rtnValue;
}