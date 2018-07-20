/************************************************************************
*
* �ļ���   ��  InputDataProcess.c
* ����ʱ�� ��  2015.08.14
* ����     ��  ZC��
* �������� ��  ������ZC�յ������ݹ���  
* ��  ע	��  ��
*
************************************************************************/

#include "InputDataProcess.h"
#include "../../LineDataManager/Mask/MaskConfigData.h"
#include "../ParseIOData/ParsePackCiData.h"
#include "../../LineDataManager/Switch/SwitchStatusData.h"
#include "../../LineDataManager/Signal/SignalStatusData.h"
#include "../../LineDataManager/PSD/PSDStatusData.h"
#include "../../LineDataManager/ESB/ESBStatusData.h"
#include "../../LineDataManager/AC/ACStatusData.h"
#include "../../LineDataManager/AC/ACLogicManager.h"
#include "../../LineDataManager/AC/ACConfigData.h"
#include "../../LineDataManager/Route/RouteStatusData.h"
#include "../../LineDataManager/Overlap/OverlapStatusData.h"
#include "../../LineDataManager/DR/DRStatusData.h"
#include "../../LineDataManager/DR/DRConfigData.h"
#include "../../../Common/Convert.h"
#include "../../TrainManager/Train/TrainStatusData.h"
#include "../../TrainManager/Train/TrainLogicManager.h"
#include "../../TrainManager/MA/MAStatusData.h"
#include "../../LineDataManager/Change/ChangeLogicManager.h"
#include "../../LineDataManager/Tsr/TsrStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../LineDataManager/Tsr/TsrLogicManager.h"
#include "../../SysDataManager/SysStatusData.h"
#include "../../LineDataManager/DataVersion/DataVersionConfigData.h"
#include "../ParseIOData/ParsePackTrainData.h"
#include "../CommTarget/CommTargetStatusData.h"
#include "../ParseIOData/ParsePackZcData.h"
#include "../../LineDataManager/Change/ChangeConfigData.h"
#include "../../../Common/MemSet.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../ParseIOData/ParsePackNtpData.h"
#include "../../SysDataManager/SysTimeData.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../TsrManager/TsrInterface.h"/*-bye-*/


static UINT8_S ParseMaskValueToRouteStopReqData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

/*
* ���������� �������ݴ���
* ����˵���� ��
* ����ֵ  �� ��      
*/
void InputDataProcess(void)
{
    /*����ATS����ZC����*/
    ProcessTsrCommandsFromAts();/*-bye-*/
    
    /*����CI����ZC����*/
    CiToZcInputDataProcess();

    /*��������ZC��������*/
    NextZcInputDataProcess();

    /*������ATP��������*/
    TrainToZcInputDataProcess();

    /*����Ntp��������*/
    NtpToZcInputDataProcess();
}

/*
* ���������� ����CI��������
* ����˵���� ��
* ����ֵ  �� ��      
*/
void CiToZcInputDataProcess(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTargetId = DEFAULT_ZERO;
    UINT8_S maskValueBuff[ZC_TO_CI_MASK_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S tempRtn = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetCiToZcCurSum();cycle++)
    {
        commTargetId = GetCiToZcBuffIndexOfCiId(cycle);

        if (COMM_CI_SUM_MAX != commTargetId)
        {
            /*��buf��Ϣת��Ϊ��λ��Ϣ*/
            tempRtn = ParseCiInMaskDataToMaskBuf(GetCiToZcDataBuffByIndex(cycle),GetCiToZcIdDataBuffLen(cycle),
                GetReceiveToZcMaskIdMax(INNER_DEVTYPE_CI,commTargetId),maskValueBuff);

            /*�������豸��Ϣ*/
            if (RETURN_SUCCESS == tempRtn)
            {
                /*������ǰ����*/
                if (RETURN_SUCCESS == ParseMaskValueToDeviceData(commTargetId,maskValueBuff))
                {
                    /*Do nothing currently !*/
                } 
                else
                {
                    /*�����뵱ǰCIͨ�Ź���*/
                    SetCommTargetStatus(INNER_DEVTYPE_CI,commTargetId,COMM_STATUS_ABNORMAL);
                }
            } 
            else
            {
                /*�����뵱ǰCIͨ�Ź���*/
                SetCommTargetStatus(INNER_DEVTYPE_CI,commTargetId,COMM_STATUS_ABNORMAL);
            }
        } 
        else
        {
            /* ��ȡ����IDʧ�� */
        }     
    }
}

/*
* ���������� ����CI����ĵ�֡����
* ����˵���� const UINT8 ciInValueBuff[],��������
*            const UINT16_S dataLength,���볤��
*            const UINT16_S maskSum,��λ����
*            UINT8_S maskValueBuff[],�����λ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseCiInMaskDataToMaskBuf(const UINT8_S ciInValueBuff[],const UINT16_S dataLength,const UINT16_S maskSum,UINT8_S maskValueBuff[])
{
    UINT16_S index = 1U;			    /*Ŀ�����ݻ������±�(��λ��1��ʼ)*/
    UINT8_S resNum = DEFAULT_ZERO;                    /*����*/
    UINT16_S cycleLength = DEFAULT_ZERO;				/*Դ���ݻ������±�*/
    UINT16_S maskCycle = DEFAULT_ZERO;			    /*��λ�����±�*/
    UINT8_S returnValue = DEFAULT_ZERO;               /*Ĭ�Ͻ���ʧ��*/
    UINT8_S successFlag = DEFAULT_ZERO;               /*�����ɹ���־*/

#ifdef SYS_TYPE_WINDOWS
    LogPrintf(1U,"CI in:\n");
    LogPrintBuff(ciInValueBuff,dataLength,dataLength);
#endif

    if ((NULL != ciInValueBuff) && (NULL != maskValueBuff))
    {
        for (cycleLength = DEFAULT_ZERO; cycleLength < dataLength; cycleLength++)
        {
            for (maskCycle = 0U; maskCycle < 8U; maskCycle++)
            {		
                /*��λδ�������*/
                /*��Ĭ�ϸ�λ��ŵ���λ*/
                resNum = (UINT8_S)((ciInValueBuff[cycleLength] >> (7U-maskCycle)) % 2U);

                if (resNum == 0U)
                {
                    maskValueBuff[index] = 0U;
                    index = index + 1U;
                }
                else
                {
                    maskValueBuff[index] = 1U;
                    index = index + 1U;
                }

                /*��maskSum�޸�ΪmaskSum+1,Ϊ�˽������1����λֵ,*/
                /*���Ҫ��������λ�����պ���8��������,���1��maskcycle=7��,�����ٽ�ѭ�������жϳɹ�Ҫ�ڽ���֮��*/
                if ((maskSum + 1U) == index)
                {
                    /*��λ�������*/
                    successFlag = FLAG_SET;
                    break;
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }

            if (FLAG_SET == successFlag)
            {
                break;
            } 
            else
            {
                /*Do nothing currently !*/
            }
        }

        if (FLAG_SET == successFlag)
        {
            /*�����ɹ�*/
            returnValue = RETURN_SUCCESS;
        } 
        else
        {
            returnValue = RETURN_ERROR;
        }
    } 
    else
    {
        returnValue = RETURN_ERROR;
    }
    
    return returnValue;
}

/*
* ���������� ����CI�������λ���ݵ����豸������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT8_S maskValueBuff[],������λ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToDeviceData(const UINT16_S commTargetId,const UINT8_S maskValueBuff[])
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S maskId = DEFAULT_ZERO;
    UINT8_S maskType = DEFAULT_ZERO;
    UINT16_S relevanceMaskId = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (NULL != maskValueBuff)
    {
        for (cycle = DEFAULT_ZERO;cycle < GetReceiveToZcMaskSum(INNER_DEVTYPE_CI,commTargetId);cycle++)
        {
            /*��ȡ������λ����Ϣ*/
            maskId = GetReceiveMaskId(cycle,INNER_DEVTYPE_CI,commTargetId);
            maskType = GetReceiveMaskType(maskId,INNER_DEVTYPE_CI,commTargetId);

            switch (maskType)
            {
            case SWITCH_FRONT_MASK_TYPE:
                relevanceMaskId = GetReceiveRelevanceMaskId(maskId,INNER_DEVTYPE_CI,commTargetId);
                rtnValue = ParseMaskValueToSwitchPostData(commTargetId,maskId,maskValueBuff[maskId],maskValueBuff[relevanceMaskId]);

                break;

            case SWITCH_LOCK_MASK_TYPE:
                rtnValue = ParseMaskValueToSwitchLockData(commTargetId,maskId,maskValueBuff[maskId]);

                break;

            case SIGNAL_STATUS_MASK_TYPE:
                rtnValue = ParseMaskValueToSignalStatusData(commTargetId,maskId,maskValueBuff[maskId]);

                break;

            case PSD_STATUS_MASK_TYPE:
                rtnValue = ParseMaskValueToPsdStatusData(commTargetId,maskId,maskValueBuff[maskId]);

                break;

            case ESB_STATUS_MASK_TYPE:
                rtnValue = ParseMaskValueToEsbStatusData(commTargetId,maskId,maskValueBuff[maskId]);

                break;

            case AC_UP_DIR_MASK_TYPE:
                relevanceMaskId = GetReceiveRelevanceMaskId(maskId,INNER_DEVTYPE_CI,commTargetId);
                rtnValue = ParseMaskValueToACDirData(commTargetId,maskId,maskValueBuff[maskId],maskValueBuff[relevanceMaskId]);

                break;

            case AC_OCC_STATUS_MASK_TYPE :
                rtnValue = ParseMaskValueToAcOccStatusData(commTargetId,maskId,maskValueBuff[maskId]);

                break;

            case AC_LOCK_STATUS_MASK_TYPE :
                rtnValue = ParseMaskValueToAcLockStatusData(commTargetId,maskId,maskValueBuff[maskId]);

                break;

            case ROUTE_STATUS_MASK_TYPE :
                rtnValue = ParseMaskValueToRouteStatusData(commTargetId,maskId,maskValueBuff[maskId]);

                break;

            case OVERLAP_STATUS_MASK_TYPE :
                rtnValue = ParseMaskValueToOverlapStatusData(commTargetId,maskId,maskValueBuff[maskId]);

                break;

            case DR_BUTTON_STATUS_MASK_TYPE :
                rtnValue = ParseMaskValueToDRButtonStatusData(commTargetId,maskId,maskValueBuff[maskId]);

                break;
            case ROUTE_STOP_REQUEST_MASK_TYPE:
                rtnValue = ParseMaskValueToRouteStopReqData(commTargetId,maskId,maskValueBuff[maskId]);

                break;
            default:
                break;
            }

            if (RETURN_SUCCESS == rtnValue)
            {
                /*Do nothing currently !*/
            } 
            else
            {
                break;
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
* ���������� ����CI�������λ���ݵ������豸λ��������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskMainValue,����λ��λֵ
*            const UINT8_S maskSideValue,����λ��λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToSwitchPostData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskMainValue,const UINT8_S maskSideValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S switchStatus = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId,SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {
        switch (maskMainValue)
        {
        case 0U:
            switch (maskSideValue)
            {
            case 0U:
                switchStatus = SWITCH_STATE_LOSE;
                break;
            case 1U:
                switchStatus = SWITCH_STATE_SIDE;
                break;
            default:
                switchStatus = SWITCH_STATE_LOSE;
                break;
            }
            break;
        case 1U:
            switch (maskSideValue)
            {
            case 0U:
                switchStatus = SWITCH_STATE_MAIN;
                break;
            case 1U:
                switchStatus = SWITCH_STATE_LOSE;
                break;
            default:
                switchStatus = SWITCH_STATE_LOSE;
                break;
            }
            break;
        default:
            switchStatus = SWITCH_STATE_LOSE;
            break;
        }

        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {
            rtnValue &= SetSwitchPosStatus(deviceIdBuff[cycle],switchStatus);
        }
    } 
    else
    {
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* ���������� ����CI�������λ���ݵ������豸����������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskValue,����������λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToSwitchLockData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S switchLockStatus = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId,SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {
        switch (maskValue)
        {
        case 0U:
            switchLockStatus = SWITCH_STATE_UNLOCK;
            break;
        case 1U:
            switchLockStatus = SWITCH_STATE_LOCK;
            break;
        default:
            switchLockStatus = SWITCH_STATE_UNLOCK;
            break;
        }

        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {
            rtnValue &= SetSwitchLock(deviceIdBuff[cycle],switchLockStatus);
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
   
    return rtnValue;
}

/*
* ���������� ����CI�������λ���ݵ��źŻ��豸״̬������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskValue,�źŻ�״̬��λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToSignalStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S signalStatus = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId, SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {
        switch (maskValue)
        {
        case 0U:
            signalStatus = SIGNAL_STATE_STOP;
            break;
        case 1U:
            signalStatus = SIGNAL_STATE_PASS;
            break;
        default:
            signalStatus = SIGNAL_STATE_STOP;
            break;
        }

        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {
            rtnValue &= SetSignalStatus(deviceIdBuff[cycle],signalStatus);
        }
    } 
    else
    {
        rtnValue = 0U;
    }
   
    return rtnValue;
}

/*
* ���������� ����CI�������λ���ݵ�Psd�豸״̬������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskValue,������״̬��λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToPsdStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S psdStatus = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId, SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {
        switch (maskValue)
        {
        case 0U:
            psdStatus = PSD_STATE_OPEN;
            break;
        case 1U:
            psdStatus = PSD_STATE_CLOSE;
            break;
        default:
            psdStatus = PSD_STATE_OPEN;
            break;
        }

        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {
            rtnValue &= SetPsdStatus(deviceIdBuff[cycle],psdStatus);
        }
    } 
    else
    {
        rtnValue = 0U;
    }
    
    return rtnValue;
}

/*
* ���������� ����CI�������λ���ݵ�Esb�豸״̬������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskValue,����ͣ����ť״̬��λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToEsbStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S esbStatus = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId, SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {
        switch (maskValue)
        {
        case 1U:
            esbStatus = ESB_STATE_UP;
            break;
        case 0U:
            esbStatus = ESB_STATE_DOWN;
            break;
        default:
            esbStatus = ESB_STATE_DOWN;
            break;
        }

        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {
            rtnValue &= SetEsbStatus(deviceIdBuff[cycle],esbStatus);
        }
    } 
    else
    {
        rtnValue = 0U;
    }
    
    return rtnValue;
}

/*
* ���������� ����CI�������λ���ݵ����������豸����������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskUpDirValue,��������������λֵ
*            const UINT8_S maskDownDirValue,��������������λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToACDirData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskUpDirValue,const UINT8_S maskDownDirValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S acDir = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId, SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {
        switch (maskUpDirValue)
        {
        case 0U:
            switch (maskDownDirValue)
            {
            case 0U:
                acDir = DEFAULT_ZERO;
                break;
            case 1U:
                /*����ʱ��ʱ�޸�Ϊ���У���������������*/
                acDir = AC_DIR_UP_STATUS;
                break;
            default:
                acDir = DEFAULT_ZERO;
                break;
            }
            break;
        case 1U:
            switch (maskDownDirValue)
            {
            case 0U:
                /*����ʱ��ʱ�޸�Ϊ����,����CIȷ�ϣ���������������*/
                acDir = AC_DIR_DOWN_STATUS;
                break;
            case 1U:
                acDir = DEFAULT_ZERO;
                break;
            default:
                acDir = DEFAULT_ZERO;
                break;
            }
            break;
        default:
            acDir = DEFAULT_ZERO;
            break;
        }

        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {
            if (RETURN_SUCCESS ==JudgeAcOfSwitchPosInNeed(deviceIdBuff[cycle]))
            {
                rtnValue &= SetAcDirection(deviceIdBuff[cycle],acDir);
            } 
            else
            {
                rtnValue &= SetAcDirection(deviceIdBuff[cycle],DEFAULT_ZERO);
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
* ���������� ����CI�������λ���ݵ���������ռ��������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskValue,��������ռ����λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToAcOccStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S acOccStatus = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId, SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {

        switch (maskValue)
        {
        case 0U:
            acOccStatus = AC_OCC_STATUS;
            break;
        case 1U:
            acOccStatus = AC_FREE_STATUS;
            break;
        default:
            acOccStatus = AC_OCC_STATUS;
            break;
        }


        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {
            if (JudgeAcOfSwitchPosInNeed(deviceIdBuff[cycle]))
            {
                rtnValue &= SetAcStatusNow(deviceIdBuff[cycle],acOccStatus);
            } 
            else
            {
				if (FLAG_SET == CheckAcOfSwitchPosIsSK(deviceIdBuff[cycle]))
				{
					/*���ڵ����Ŀ�,���ü���ռ��*/
					rtnValue &= SetAcStatusNow(deviceIdBuff[cycle],acOccStatus);
				} 
				else
				{
					rtnValue &= SetAcStatusNow(deviceIdBuff[cycle],AC_FREE_STATUS);
				}
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
* ���������� ����CI�������λ���ݵ�������������������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskValue,������������״̬��λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToAcLockStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S acLockStatus = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);
    
    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId, SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {
        switch (maskValue)
        {
        case 0U:
            acLockStatus = AC_UNLOCK_STATUS;
            break;
        case 1U:
            acLockStatus = AC_LOCK_STATUS;
            break;
        default:
            acLockStatus = AC_UNLOCK_STATUS;
            break;
        }

        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {           
            if (JudgeAcOfSwitchPosInNeed(deviceIdBuff[cycle]))
            {
                rtnValue &= SetAcBelock(deviceIdBuff[cycle],acLockStatus);
            } 
            else
            {
                rtnValue &= SetAcBelock(deviceIdBuff[cycle],AC_UNLOCK_STATUS);
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
* ���������� ����CI�������λ���ݵ���·״̬������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskValue,��·״̬��λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToRouteStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S routeStatus = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId, SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {
        switch (maskValue)
        {
        case 0U:
            routeStatus = ROUTE_STATE_UNSET;
            break;
        case 1U:
            routeStatus = ROUTE_STATE_SET;
            break;
        default:
            routeStatus = ROUTE_STATE_UNSET;
            break;
        }

        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {
            rtnValue &= SetRouteStatus(deviceIdBuff[cycle],routeStatus);
        }
    } 
    else
    {
        rtnValue = 0U;
    }
    
    return rtnValue;
}

/*
* ���������� ����CI�������λ���ݵ���������״̬������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskValue,��������״̬��λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToOverlapStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S overlapStatus = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

   if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId, SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
   {
       switch (maskValue)
       {
       case 0U:
           overlapStatus = OVERLAP_STATE_UNSET;
           break;
       case 1U:
           overlapStatus = OVERLAP_STATE_SET;
           break;
       default:
           overlapStatus = OVERLAP_STATE_UNSET;
           break;
       }

       for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
       {
           rtnValue &= SetOverlapStatus(deviceIdBuff[cycle],overlapStatus);
       }
   } 
   else
   {
       rtnValue = 0U;
   }
    
    return rtnValue;
}

/*
* ���������� ����CI�������λ���ݵ������۷���ť״̬������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskValue,�����۷���ť״̬��λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseMaskValueToDRButtonStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S drButtonStatus = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId, SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {
        switch (maskValue)
        {
        case 0U:
            drButtonStatus = DR_BUTTON_STATE_UP;
            break;
        case 1U:
            drButtonStatus = DR_BUTTON_STATE_DOWN;
            break;
        default:
            drButtonStatus =DR_BUTTON_STATE_UP;
            break;
        }

        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {
            rtnValue &= SetDRButtonStatus(deviceIdBuff[cycle],drButtonStatus);
        }
    } 
    else
    {
        rtnValue = 0U;
    }
    
    return rtnValue;
}

/*
* ���������� ��������ZC��������
* ����˵���� ��
* ����ֵ  �� ��      
*/
void NextZcInputDataProcess(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTargetId = DEFAULT_ZERO;
    UINT8_S *pDataBuff = NULL;
    UINT16_S dataLen = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetNZcToZcCurSum();cycle++)
    {
        commTargetId = GetNZcToZcBuffIndexOfNZcId(cycle);

        /*��ȡ������ZC��������ݳ���*/
        dataLen = GetNZcToZcIdDataBufLen(cycle);

        /*��ȡ������ZC���������*/
        pDataBuff = GetNZcToZcBufDataOfIndex(cycle);

        /*������֡����*/
        if ((DEFAULT_ZERO != dataLen)
            && (NULL != pDataBuff))
        {
            if (RETURN_SUCCESS == ParseNextZcInput(commTargetId,pDataBuff))
            {
                /*������*/
            } 
            else
            {
                /*�����뵱ǰZCͨ�Ź���*/
                SetCommTargetStatus(INNER_DEVTYPE_ZC,commTargetId,COMM_STATUS_ABNORMAL);
            }
        } 
        else
        {
            /*�����뵱ǰZCͨ�Ź���*/
            SetCommTargetStatus(INNER_DEVTYPE_ZC,commTargetId,COMM_STATUS_ABNORMAL);
        }
    }
}

/*
* ���������� ��������ZC���뵥֡����
* ����˵���� const UINT16 zcId,ZC�ı��
*            const UINT8_S pBuff[]
* ����ֵ  �� 0: ʧ��
*            1: �ɹ�
*/
UINT8_S ParseNextZcInput(const UINT16_S zcId,const UINT8_S pBuff[])
{
    UINT16_S dataIndex = DEFAULT_ZERO;
    UINT16_S parseErrorFlag = DEFAULT_ZERO;
    UINT8_S  rtnValue = DEFAULT_ZERO;

    if (NULL != pBuff)
    {
        /*�����ϰ�����Ϣ*/
        if (RETURN_SUCCESS == NextZcObsMsgParse(zcId,pBuff,&dataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_1);
        }

        /*������ʱ������Ϣ*/
        if (RETURN_SUCCESS == NextZcTsrMsgParse(zcId,pBuff,&dataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_2);
        }

        /*�����г���MA��Ϣ*/
        if (RETURN_SUCCESS == NextZcTrainAndMaMsgParse(zcId,pBuff,&dataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_3);
        }

        if (DEFAULT_ZERO == parseErrorFlag)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {		
            rtnValue = RETURN_ERROR;

            LogPrintf(1U,"ParNZcIn %d E=%d\n",zcId,parseErrorFlag);
        }       
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� ��������ZC�����ϰ�������
* ����˵���� const UINT16_S zcId,ZC�ı��
*            const UINT8_S *pBuff,
*            UINT16_S *dataIndex,�������ݵ��±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcObsMsgParse(const UINT16_S zcId,const UINT8_S *pBuff,UINT16_S *dataIndex)
{
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT16_S parseErrorFlag = DEFAULT_ZERO;
    UINT8_S  rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*��ȡ���������±�*/
        tempDataIndex = (*dataIndex);

        /*������·��Ϣ*/
        if (RETURN_SUCCESS == NextZcRouteMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_1);
        }

        /*��������������Ϣ*/
        if (RETURN_SUCCESS == NextZcOverLapMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_2);
        }

        /*�����źŻ���Ϣ*/
        if (RETURN_SUCCESS == NextZcSignalMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_3);
        }

        /*����������Ϣ*/
        if (RETURN_SUCCESS == NextZcSwitchMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_4);
        }

        /*������������Ϣ*/
        if (RETURN_SUCCESS == NextZcPsdMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_5);
        }

        /*��������ͣ����ť��Ϣ*/
        if (RETURN_SUCCESS == NextZcEsbMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_6);
        }

        /*���������۷���ť��Ϣ*/
        if (RETURN_SUCCESS == NextZcDrButtonMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_7);
        }

        /*���������۷�����Ϣ*/
        if (RETURN_SUCCESS == NextZcDrLampMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_8);
        }

        /*����������Ϣ*/
        if (RETURN_SUCCESS == NextZcAcMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*������*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_9);
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;

        parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_10);
    }

    if (DEFAULT_ZERO == parseErrorFlag)
    {
        /*���������±�*/
        (*dataIndex) = tempDataIndex;
        rtnValue = RETURN_SUCCESS;
    } 
    else
    {		
        rtnValue = RETURN_ERROR;

        LogPrintf(1U,"NZcObsPar %d E=%d\n",zcId,parseErrorFlag);

    }
   
    return rtnValue;
}

/*
* ���������� ��ȡ����ZC�����ϰ�����λ����
* ����˵���� const UINT16_S bitIndex, ��λֵ
*            const UINT16_S baseBufIndex,��������±�
*            const UINT8_S baseAddr[]����������
* ����ֵ  �� ��λֵ
*/
UINT8_S GetZcBitValue(const UINT16_S bitIndex, const UINT16_S baseBufIndex,const UINT8_S baseAddr[])
{
    UINT8_S  divisor = DEFAULT_ZERO;                    /*��λ���±��Ӧ���ֽ����*/
    UINT8_S  remainder = DEFAULT_ZERO;                  /*��λ���±��Ӧ���ֽ��е�Bitλ*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*���������λ���±��������ö�Ӧ���ֽ����*/
    divisor = (UINT8_S)(baseBufIndex + ((2U * (bitIndex - 1U)) / 8U));

    /*���������λ���±�ȡ�࣬��ö�Ӧ��Bitλ*/
    remainder = (UINT8_S)((2U * (bitIndex - 1U)) % 8U);

    if (NULL != baseAddr)
    {
        rtnValue = (UINT8_S)((UINT8_S)(baseAddr[divisor] >> remainder) & ((UINT8_S)0x03U));
    }
    
    return rtnValue;
}

/*
* ���������� ��������ZC�����ϰ����·������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcRouteMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S cycleRoute = DEFAULT_ZERO;
    UINT8_S bitValue = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    UINT16_S inputObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        tempDataIndex = (*dataIndex);

        /*��ȡ��λ��Ϣ*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_ROUTE,&localObsNum))
        {
            pObsStru  = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_ROUTE);

            /*��ȡ���������н�·����*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*������·��Ϣ*/
                for (cycleRoute = DEFAULT_ZERO;cycleRoute < localObsNum;cycleRoute++)
                {
                    obsId = pObsStru[cycleRoute].ObsId;
                    bitIndex = pObsStru[cycleRoute].StateBitIndex;
                    bitValue = GetZcBitValue(bitIndex,tempDataIndex,pBuff);

                    switch (bitValue)
                    {
                    case 0x01U:
                        SetRouteStatus(obsId,ROUTE_STATE_SET);
                        break;
                    case 0x02U:
                        SetRouteStatus(obsId,ROUTE_STATE_UNSET);
                        break;
                    case 0x00U:
                        SetRouteStatus(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetRouteStatus(obsId,DEFAULT_ZERO);
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
        }      
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*
* ���������� ��������ZC�����ϰ���������Σ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcOverLapMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S cycleOverLap = DEFAULT_ZERO;
    UINT8_S bitValue = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    UINT16_S inputObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        tempDataIndex = (*dataIndex);

        /*��ȡ��λ��Ϣ*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_OVERLAP,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_OVERLAP);

            /*��ȡ���������б�����������*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru )
                && (inputObsNum == localObsNum))
            {
                /*��������������Ϣ*/
                for (cycleOverLap = DEFAULT_ZERO;cycleOverLap < localObsNum;cycleOverLap++)
                {
                    obsId = pObsStru[cycleOverLap].ObsId;
                    bitIndex = pObsStru[cycleOverLap].StateBitIndex;
                    bitValue = GetZcBitValue(bitIndex,tempDataIndex,pBuff);

                    switch (bitValue)
                    {
                    case 0x01U:
                        SetOverlapStatus(obsId,OVERLAP_STATE_SET);
                        break;
                    case 0x02U:
                        SetOverlapStatus(obsId,OVERLAP_STATE_UNSET);
                        break;
                    case 0x00U:
                        SetOverlapStatus(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetOverlapStatus(obsId,DEFAULT_ZERO);
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
        }       
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*
* ���������� ��������ZC�����ϰ���źŻ�������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcSignalMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S cycleSignal = DEFAULT_ZERO;
    UINT8_S bitValue = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    UINT16_S inputObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        tempDataIndex = (*dataIndex);

        /*��ȡ��λ��Ϣ*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_SIGNAL,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_SIGNAL);

            /*��ȡ�����������źŻ�����*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru )
                && (inputObsNum == localObsNum))
            {
                /*�����źŻ���Ϣ*/
                for (cycleSignal = DEFAULT_ZERO;cycleSignal < localObsNum;cycleSignal++)
                {
                    obsId = pObsStru [cycleSignal].ObsId;
                    bitIndex = pObsStru[cycleSignal].StateBitIndex;
                    bitValue = GetZcBitValue(bitIndex,tempDataIndex,pBuff);

                    switch (bitValue)
                    {
                    case 0x01U:
                        SetSignalStatus(obsId,SIGNAL_STATE_PASS);
                        break;
                    case 0x02U:
                        SetSignalStatus(obsId,SIGNAL_STATE_STOP);
                        break;
                    case 0x00U:
                        SetSignalStatus(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetSignalStatus(obsId,DEFAULT_ZERO);
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
        }       
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
    

    return rtnValue;
}

/*
* ���������� ��������ZC�����ϰ����������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcSwitchMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S stateBitIndex = DEFAULT_ZERO;
    UINT16_S lockBitIndex = DEFAULT_ZERO;
    UINT16_S cycleSwitch = DEFAULT_ZERO;
    UINT8_S bitValue = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    UINT16_S inputObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        tempDataIndex = (*dataIndex);

        /*��ȡ��λ��Ϣ*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_POINT,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_POINT);

            /*��ȡ���������е�������*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru )
                && (inputObsNum == localObsNum))
            {
                /*����������Ϣ*/
                for (cycleSwitch = DEFAULT_ZERO;cycleSwitch < localObsNum;cycleSwitch++)
                {
                    obsId = pObsStru [cycleSwitch].ObsId;
                    stateBitIndex = pObsStru[cycleSwitch].StateBitIndex;
                    lockBitIndex = pObsStru[cycleSwitch].LockBitIndex;

                    /*��ȡ����λ��״̬��Ϣ*/
                    bitValue = GetZcBitValue(stateBitIndex,tempDataIndex,pBuff);

                    switch (bitValue)
                    {
                    case 0x01U:
                        SetSwitchPosStatus(obsId,SWITCH_STATE_MAIN);
                        break;
                    case 0x02U:
                        SetSwitchPosStatus(obsId,SWITCH_STATE_SIDE);
                        break;
                    case 0x03U:
                        SetSwitchPosStatus(obsId,SWITCH_STATE_LOSE);
                        break;
                    default:
                        SetSwitchPosStatus(obsId,SWITCH_STATE_LOSE);
                        break;
                    }

                    /*��ȡ����������Ϣ*/
                    bitValue = GetZcBitValue(lockBitIndex,tempDataIndex,pBuff);

                    switch (bitValue)
                    {
                    case 0x01U:
                        SetSwitchLock(obsId,SWITCH_STATE_UNLOCK);
                        break;
                    case 0x02U:
                        SetSwitchLock(obsId,SWITCH_STATE_LOCK);
                        break;
                    case 0x00U:
                        SetSwitchLock(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetSwitchLock(obsId,DEFAULT_ZERO);
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
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
    

    return rtnValue;
}

/*
* ���������� ��������ZC�����ϰ�������ţ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcPsdMsgParse(const UINT16_S zcId,const UINT8_S pBuff[], UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S cyclePsd = DEFAULT_ZERO;
    UINT8_S bitValue = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    UINT16_S inputObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        tempDataIndex = (*dataIndex);

        /*��ȡ��λ��Ϣ*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_PSD,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_PSD);

            /*��ȡ��������������������*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*������������Ϣ*/
                for (cyclePsd = DEFAULT_ZERO;cyclePsd < localObsNum;cyclePsd++)
                {
                    obsId = pObsStru[cyclePsd].ObsId;
                    bitIndex = pObsStru[cyclePsd].StateBitIndex;
                    bitValue = GetZcBitValue(bitIndex,tempDataIndex,pBuff);

                    switch (bitValue)
                    {
                    case 0x01U:
                        SetPsdStatus(obsId,PSD_STATE_CLOSE);
                        break;
                    case 0x02U:
                        SetPsdStatus(obsId,PSD_STATE_OPEN);
                        break;
                    case 0x00U:
                        SetPsdStatus(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetPsdStatus(obsId,DEFAULT_ZERO);
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
        }     
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*
* ���������� ��������ZC�����ϰ������ͣ����ť������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcEsbMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S cycleEsb = DEFAULT_ZERO;
    UINT8_S bitValue = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    UINT16_S inputObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        tempDataIndex = (*dataIndex);

        /*��ȡ��λ��Ϣ*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_ESB,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_ESB);

            /*��ȡ���������н���ͣ����ť����*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*��������ͣ����ť��Ϣ*/
                for (cycleEsb = DEFAULT_ZERO;cycleEsb < localObsNum;cycleEsb++)
                {
                    obsId = pObsStru[cycleEsb].ObsId;
                    bitIndex = pObsStru[cycleEsb].StateBitIndex;
                    bitValue = GetZcBitValue(bitIndex,tempDataIndex,pBuff);

                    switch (bitValue)
                    {
                    case 0x01U:
                        SetEsbStatus(obsId,ESB_STATE_UP);
                        break;
                    case 0x02U:
                        SetEsbStatus(obsId,ESB_STATE_DOWN);
                        break;
                    case 0x00U:
                        SetEsbStatus(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetEsbStatus(obsId,DEFAULT_ZERO);
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
        }      
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*
* ���������� ��������ZC�����ϰ�������۷���ť������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcDrButtonMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S cycleDrButton = DEFAULT_ZERO;
    UINT8_S bitValue = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    UINT16_S inputObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru  = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        tempDataIndex = (*dataIndex);

        /*��ȡ��λ��Ϣ*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_DRB,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_DRB);

            /*��ȡ���������������۷���ť����*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*���������۷���ť��Ϣ*/
                for (cycleDrButton = DEFAULT_ZERO;cycleDrButton < localObsNum;cycleDrButton++)
                {
                    obsId = pObsStru[cycleDrButton].ObsId;
                    bitIndex = pObsStru[cycleDrButton].StateBitIndex;
                    bitValue = GetZcBitValue(bitIndex,tempDataIndex,pBuff);

                    switch (bitValue)
                    {
                    case 0x01U:
                        SetDRButtonStatus(obsId,DR_BUTTON_STATE_UP);
                        break;
                    case 0x02U:
                        SetDRButtonStatus(obsId,DR_BUTTON_STATE_DOWN);
                        break;
                    case 0x00U:
                        SetDRButtonStatus(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetDRButtonStatus(obsId,DEFAULT_ZERO);
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
        }        
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*
* ���������� ��������ZC�����ϰ�������۷��ƣ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcDrLampMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S cycleDrLamp = DEFAULT_ZERO;
    UINT8_S bitValue = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    UINT16_S inputObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        tempDataIndex = (*dataIndex);

        /*��ȡ��λ��Ϣ*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_DRL,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_DRL);

            /*��ȡ���������������۷�������*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*���������۷�����Ϣ*/
                for (cycleDrLamp = DEFAULT_ZERO;cycleDrLamp < localObsNum;cycleDrLamp++)
                {
                    obsId = pObsStru[cycleDrLamp].ObsId;
                    bitIndex = pObsStru[cycleDrLamp].StateBitIndex;
                    bitValue = GetZcBitValue(bitIndex,tempDataIndex,pBuff);

                    switch (bitValue)
                    {
                    case 0x01U:
                        SetDRLampCommand(obsId,DR_LAMP_STEADY_STATUS);
                        break;
                    case 0x02U:
                        SetDRLampCommand(obsId,DR_LAMP_TWINKLE_STATUS);
                        break;
                    case 0x00U:
                        SetDRLampCommand(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetDRLampCommand(obsId,DEFAULT_ZERO);
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
        }     
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
    
    return rtnValue;
}

/*
* ���������� ��������ZC�����ϰ���������Σ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcAcMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S bitIndex = DEFAULT_ZERO;
    UINT16_S cycle = DEFAULT_ZERO;
    UINT8_S bitValue = DEFAULT_ZERO;
    UINT16_S localObsNum = DEFAULT_ZERO;
    UINT16_S inputObsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsStru = NULL;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S trainNumInAc = DEFAULT_ZERO;
    UINT8_S cycleTrain = DEFAULT_ZERO;
    UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};

    MemorySet(&trainSequenceBuff[0],((UINT32_S)(SIZE_UINT16*SIZE_MAX_TRAINOFAC)),
                DEFAULT_ZERO,((UINT32_S)(SIZE_UINT16*SIZE_MAX_TRAINOFAC)));

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        tempDataIndex = (*dataIndex);

        /*��ȡ��λ��Ϣ*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_AC,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_AC);

            /*��ȡ���������м�����������*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*��������������Ϣ*/
                for (cycle = DEFAULT_ZERO;cycle < localObsNum;cycle++)
                {
                    obsId = pObsStru[cycle].ObsId;
                    bitIndex = pObsStru[cycle].StateBitIndex;

                    /*��ȡ�������η���*/
                    bitValue = GetZcBitValue(bitIndex,tempDataIndex,pBuff);
                    switch (bitValue)
                    {
                    case 0x01U:
                        SetAcDirection(obsId,AC_DIR_DOWN_STATUS);
                        break;
                    case 0x02U:
                        SetAcDirection(obsId,AC_DIR_UP_STATUS);
                        break;
                    case 0x00U:
                        SetAcDirection(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetAcDirection(obsId,DEFAULT_ZERO);
                        break;
                    }	

                    /*��ȡ��������ռ��/����*/
                    bitValue = GetZcBitValue(bitIndex + 1U,tempDataIndex,pBuff);
                    switch (bitValue)
                    {
                    case 0x01U:
                        SetAcStatusNow(obsId,AC_FREE_STATUS);
                        break;
                    case 0x02U:
                        SetAcStatusNow(obsId,AC_OCC_STATUS);
                        break;
                    case 0x00U:
                        SetAcStatusNow(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetAcStatusNow(obsId,DEFAULT_ZERO);
                        break;
                    }

                    /*��ȡ������������*/
                    bitValue = GetZcBitValue(bitIndex + 2U,tempDataIndex,pBuff);
                    switch (bitValue)
                    {
                    case 0x01U:
                        SetAcBelock(obsId,AC_UNLOCK_STATUS);
                        break;
                    case 0x02U:
                        SetAcBelock(obsId,AC_LOCK_STATUS);
                        break;
                    case 0x00U:
                        SetAcBelock(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetAcBelock(obsId,DEFAULT_ZERO);
                        break;
                    }	

                    /*��ȡ��������UT״̬*/
                    bitValue = GetZcBitValue(bitIndex + 3U,tempDataIndex,pBuff);
                    switch (bitValue)
                    {
                    case 0x01U:
                        SetAcUtFlag(obsId,AC_UT_FREE_STATUS);
                        break;
                    case 0x02U:
                        SetAcUtFlag(obsId,AC_UT_OCC_STATUS);
                        break;
                    case 0x00U:
                        SetAcUtFlag(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetAcUtFlag(obsId,DEFAULT_ZERO);
                        break;
                    }

                    /*��ȡ��������ARB״̬*/
                    bitValue = GetZcBitValue(bitIndex + 4U,tempDataIndex,pBuff);
                    switch (bitValue)
                    {
                    case 0x01U:
                        SetAcArbFlag(obsId,AC_ARB_FREE_STATUS);
                        break;
                    case 0x02U:
                        SetAcArbFlag(obsId,AC_ARB_OCC_STATUS);
                        break;
                    case 0x00U:
                        SetAcArbFlag(obsId,DEFAULT_ZERO);
                        break;
                    default:
                        SetAcArbFlag(obsId,DEFAULT_ZERO);
                        break;
                    }

                    /*����״̬������2���ֽ���,Ԥ��6��bitλ*/
                    tempDataIndex += 2U;

                    SetAcUtRedundance(obsId,pBuff[tempDataIndex]);
                    tempDataIndex = tempDataIndex + 1U;

                    SetAcArbRedundance(obsId,pBuff[tempDataIndex]);
                    tempDataIndex = tempDataIndex + 1U;

                    /*�г�����*/
                    trainNumInAc = pBuff[tempDataIndex];
                    tempDataIndex = tempDataIndex + 1U;

                    for (cycleTrain = DEFAULT_ZERO;cycleTrain < trainNumInAc;cycleTrain++)
                    {
                        trainSequenceBuff[cycleTrain] = ShortFromChar(&pBuff[tempDataIndex]);
                        tempDataIndex += 2U;
                    }

                    SetAcTrainSequenceBuff(obsId,trainSequenceBuff,trainNumInAc);
                }

                /*��������±�*/
                (*dataIndex) = tempDataIndex;

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

/*
* ���������� ��������ZC������ʱ��������
* ����˵���� const UINT16 zcId,zcId
*            const UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcTsrMsgParse(const UINT16_S zcId,const UINT8_S pBuff[], UINT16_S *dataIndex)
{
    UINT8_S tsrNum = DEFAULT_ZERO;
    UINT16_S tsrSpeed = DEFAULT_ZERO;
    UINT16_S logicNum = DEFAULT_ZERO;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S cycleTsr = DEFAULT_ZERO;
    UINT8_S cycleLogic = DEFAULT_ZERO;
    UINT16_S  sectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S zcIndexInTsr = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    MemorySet(&sectionIdBuff[0],((UINT32_S)(SIZE_UINT16*SINGLE_TSR_SECTION_SUM_MAX)),
                DEFAULT_ZERO,((UINT32_S)(SIZE_UINT16*SINGLE_TSR_SECTION_SUM_MAX)));

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*��ȡ�±�*/
        tempDataIndex = (*dataIndex);

        /*������Tsr�±�*/
        AplyTsrIndexOfZcId(zcId);

        /*��ȡ�洢��Tsr�ṹ�и�ZCid��Ӧ�±�*/
        zcIndexInTsr = GeZcIdOfTsrBufIndex(zcId);

        /*������ʱ���ٸ���*/
        tsrNum = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        if (zcIndexInTsr < TSR_BUFF_SUM_MAX)
        {
            /*��ո�ZC��Ӧ����ʱ������Ϣ*/
            DeleteSingleZcTsrInfo(zcId);

            for (cycleTsr = DEFAULT_ZERO;cycleTsr < tsrNum;cycleTsr++)
            {
                tsrSpeed = ShortFromChar(&pBuff[tempDataIndex]);
                tempDataIndex = tempDataIndex + 2U;

                /*��ȡ������ʱ���ٰ������߼���������*/
                logicNum = ShortFromChar(&pBuff[tempDataIndex]);
                tempDataIndex = tempDataIndex + 2U;

                for (cycleLogic = DEFAULT_ZERO;cycleLogic < logicNum;cycleLogic++)
                {
                    sectionIdBuff[cycleLogic] = ShortFromChar(&pBuff[tempDataIndex]);
                    tempDataIndex = tempDataIndex + 2U;
                }

                /* ������ʱ����ֵ */
                SetSingleTsrDataOfSpeed(zcIndexInTsr,((UINT16_S)cycleTsr),tsrSpeed);

                /* ������ʱ���ٰ������߼����� */
                SetSingleTsrDataOfSectionInfo(zcIndexInTsr,cycleTsr,(UINT8_S)logicNum,sectionIdBuff);
            }

            /*������ʱ��������*/
            SetZcIdOfTsrNum(zcIndexInTsr,tsrNum);

            /*�����±�*/
            (*dataIndex) = tempDataIndex;

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
* ���������� ��������ZC���뵥֡�������г���Ϣ
* ����˵���� const UINT16_S trainId,�г���ID
*            const UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcTrainMsgParse(const UINT16_S trainId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S setValue = DEFAULT_ZERO;
    TrainInfoStruct singleTrainInfoStru;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
	UINT16_S controlZc = DEFAULT_ZERO;
	
    /*��ʼ��*/
    MemorySet(&singleTrainInfoStru,((UINT32_S)(sizeof(TrainInfoStruct))),
                DEFAULT_ZERO,((UINT32_S)(sizeof(TrainInfoStruct))));

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*��ȡ�����±�*/
        tempDataIndex = (*dataIndex);

        /*��д�г�ID*/
        singleTrainInfoStru.TrainID = trainId;

        /*�����г�����*/
        singleTrainInfoStru.TrainType = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*������ǰ�ܿ�ZCID*/
        singleTrainInfoStru.TrainControlZC = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);	

        /*�����г���ǰ���ں�*/
        singleTrainInfoStru.TrainCycle = LongFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);	

        /*�����г�ͨ�ż�ʱλ*/
        setValue = SetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId,((UINT16_S)pBuff[tempDataIndex]));
        tempDataIndex = tempDataIndex + 1U;

        /*��������ATP��ZC��ͨ��״̬*/
        setValue &= SetCommTargetStatus(INNER_DEVTYPE_TRAIN,trainId,pBuff[tempDataIndex]);
        tempDataIndex = tempDataIndex + 1U;
		
        /*�����г�ǰ�˿��ɱ�־*/
        singleTrainInfoStru.SuspectHead = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*�����г���˿��ɱ�־*/
        singleTrainInfoStru.SuspectTail = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*�����г���ȫ��ͷ���ڼ�������*/
        singleTrainInfoStru.TrainHeadAC = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*�����г���ȫ��β���ڼ�������*/
        singleTrainInfoStru.TrainTailAC = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*�����г��ǰ�ȫ��ͷ���ڼ�������*/
        singleTrainInfoStru.TrainUnsafeHeadAC = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*�����г��ǰ�ȫ��β���ڼ�������*/
        singleTrainInfoStru.TrainUnsafeTailAC = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*�����г�ǰ����Ҫ�������źŻ�*/
        singleTrainInfoStru.TrainFrontSignal = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*�����г������źŻ�������־*/
        singleTrainInfoStru.SignalProtection = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*�����г���ȫλ�ýṹ��*/
        singleTrainInfoStru.TrainSafeLocStru.TrainHeadLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        singleTrainInfoStru.TrainSafeLocStru.TrainHeadOffset = LongFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        singleTrainInfoStru.TrainSafeLocStru.TrainTailLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        singleTrainInfoStru.TrainSafeLocStru.TrainTailOffset = LongFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        /*��д�г��ǰ�ȫλ�ýṹ��*/
        singleTrainInfoStru.TrainUnSafeLocStru.TrainHeadLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        singleTrainInfoStru.TrainUnSafeLocStru.TrainHeadOffset = LongFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        singleTrainInfoStru.TrainUnSafeLocStru.TrainTailLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        singleTrainInfoStru.TrainUnSafeLocStru.TrainTailOffset = LongFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        /*��ȷ�����͵���ƫ��*/
        singleTrainInfoStru.TrainError = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*��д�г�ͷ���ǰ�ȫλ�ö�Ӧ���������з���*/
        singleTrainInfoStru.TrainUnsafeDirection = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*��д�г�ͷ���ǰ�ȫλ��ʵ�����з���*/
        singleTrainInfoStru.TrainRealDirection = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*��д�г���ʻģʽ��Ϣ*/
        singleTrainInfoStru.TrainMode = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*��д�г����м�����Ϣ*/
        singleTrainInfoStru.TrainLevel = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*��д�г�ʵ���ٶ���Ϣ*/
        singleTrainInfoStru.TrainSpeed = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*��д�г�ͣ������ͣ����Ϣ*/
        singleTrainInfoStru.TrainStopArea = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*��д�г������Ա�ʾ��*/		
        singleTrainInfoStru.TrainIntegrity = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*��д�г�����ͣ����ʾ��Ϣ*/
        singleTrainInfoStru.TrainEmergency = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        localZcId = GetLocalZcId();
        controlZc = GetTrainControlZc(trainId);

        if (controlZc == localZcId)
        {         
            /*�г����ܿ�ZC�ѱ�Ϊ��ZC,����������ZC�����и����г���Ϣ*/
            if (localZcId != singleTrainInfoStru.TrainControlZC)
            {
                setValue &= SetSingleTrainNextZcInputDataInfo(trainId,&singleTrainInfoStru);
            }
        } 
        else
        {
            /*�����г���Ϣ*/
            setValue &= SetSingleTrainNextZcInputDataInfo(trainId,&singleTrainInfoStru);
        }

        if (RETURN_SUCCESS == setValue)
        {
            /*��������±�*/
            (*dataIndex) = tempDataIndex;

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
* ���������� ��������ZC���뵥֡�������г��ƶ���Ȩ��Ϣ
* ����˵���� const UINT16_S zcId,����ZC�ı��
*            const UINT16_S trainId,�г���ID
*            const UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcMaMsgParse(const UINT16_S zcId,const UINT16_S trainId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S cycleMaMsg = DEFAULT_ZERO;
    NextZcMaDataStruct singleMaData;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S tsrSpeed = DEFAULT_ZERO;         /* ��ʱ���ٵ��ٶ�ֵ */
    UINT16_S tsrStartLink = DEFAULT_ZERO;     /* ��ʱ���ٵ��������link */
    UINT32_S tsrStartOffset = DEFAULT_ZERO;   /* ��ʱ���ٵ��������offset */
    UINT16_S tsrEndLink = DEFAULT_ZERO;       /* ��ʱ���ٵ��յ�����link */
    UINT32_S tsrEndOffset = DEFAULT_ZERO;     /* ��ʱ���ٵ��յ�����offset */
    UINT8_S  tsrSum = DEFAULT_ZERO;           /* ��������ZC����ʱ���ٸ��� */

    /*��ʼ��*/
    MemorySet(&singleMaData,((UINT32_S)(sizeof(NextZcMaDataStruct))),
                DEFAULT_ZERO,((UINT32_S)(sizeof(NextZcMaDataStruct))));

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*��ȡ�����±�*/
        tempDataIndex = (*dataIndex);

        /*MA�յ��ϰ�������*/
        singleMaData.MaEndAttribute = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*����MA���*/
        singleMaData.MaHeadLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*����MA���Offset*/
        singleMaData.MaHeadOffset = LongFromChar(&pBuff[tempDataIndex]);	
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        /*����MA��㷽��*/
        singleMaData.MaHeadDir = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*����MA�յ�*/
        singleMaData.MaTailLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*��дMA�յ�Offset*/
        singleMaData.MaTailOffset = LongFromChar(&pBuff[tempDataIndex]);	
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        /*��дMA�յ㷽��*/
        singleMaData.MaTailDir = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*��дMA��Χ�ڵ��ϰ�������*/
        singleMaData.ObsNum = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*ѭ������MA��Χ�ڵ��ϰ���*/
        for(cycleMaMsg = DEFAULT_ZERO;cycleMaMsg < singleMaData.ObsNum;cycleMaMsg++)
        {		
            singleMaData.ObsOfMAStru[cycleMaMsg].ObsType = pBuff[tempDataIndex];
            tempDataIndex = tempDataIndex + 1U;

            singleMaData.ObsOfMAStru[cycleMaMsg].ObsId = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            singleMaData.ObsOfMAStru[cycleMaMsg].ObsStatus = pBuff[tempDataIndex];
            tempDataIndex = tempDataIndex + 1U;

            singleMaData.ObsOfMAStru[cycleMaMsg].ObsLockStatus = pBuff[tempDataIndex];
            tempDataIndex = tempDataIndex + 1U;
        }

        /*����MA��Χ�ڵ���ʱ��������*/
        tsrSum = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

		
        /*ѭ������MA��Χ�ڵ���ʱ������Ϣ*/
        for(cycleMaMsg = DEFAULT_ZERO;cycleMaMsg < tsrSum;cycleMaMsg++)
        {                   
            /*����MA��Χ����ʱ����ֵ*/
            tsrSpeed = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*������ʱ������MA��Χ�غϵ�ʼ��Link*/
            tsrStartLink = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*������ʱ������MA��Χ�غϵ�ʼ��Offset*/
            tsrStartOffset = LongFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*������ʱ������MA��Χ�غϵ��ն�Link*/
            tsrEndLink = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*������ʱ������MA��Χ�غϵ��ն�Offset*/
            tsrEndOffset = LongFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /* ��ӹ�ZC��MA��Ϣ�����������ƽ�ZC����ʱ����,��Ҫ���� */
            if (RETURN_ERROR == CheckMaTsrInLocalZc(tsrStartLink,tsrStartOffset,tsrEndLink,tsrEndOffset))
            {
                /* �����ڱ�ZC,��д����ZC�ı�� */
                singleMaData.TsrOfMAStru[cycleMaMsg].BelongZcId = zcId;

                /* ��д��ʱ���������Ϣ */
                singleMaData.TsrOfMAStru[cycleMaMsg].TsrSpeed = tsrSpeed;
                singleMaData.TsrOfMAStru[cycleMaMsg].TsrHeadLink = tsrStartLink;
                singleMaData.TsrOfMAStru[cycleMaMsg].TsrHeadOffset = tsrStartOffset;
                singleMaData.TsrOfMAStru[cycleMaMsg].TsrTailLink = tsrEndLink;
                singleMaData.TsrOfMAStru[cycleMaMsg].TsrTailOffset = tsrEndOffset;

                /* ���ٵ�������1 */
                singleMaData.TsrNum++;
            }
            

#if 0
            singleMaData.TsrOfMAStru[cycleMaMsg].TsrSpeed = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*������ʱ������MA��Χ�غϵ�ʼ��Link*/
            singleMaData.TsrOfMAStru[cycleMaMsg].TsrHeadLink = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*������ʱ������MA��Χ�غϵ�ʼ��Offset*/
            singleMaData.TsrOfMAStru[cycleMaMsg].TsrHeadOffset = LongFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*������ʱ������MA��Χ�غϵ��ն�Link*/
            singleMaData.TsrOfMAStru[cycleMaMsg].TsrTailLink = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*������ʱ������MA��Χ�غϵ��ն�Offset*/
            singleMaData.TsrOfMAStru[cycleMaMsg].TsrTailOffset = LongFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);
#endif
        }

        /*������Ӧ����Ϣ*/
        rtnValue = SetNextZcMaHeadLink(trainId,singleMaData.MaHeadLink);
        rtnValue *= SetNextZcMaHeadOffset(trainId,singleMaData.MaHeadOffset);
        rtnValue *= SetNextZcMaHeadDir(trainId,singleMaData.MaHeadDir);
        rtnValue *= SetNextZcMaTailLink(trainId,singleMaData.MaTailLink);
        rtnValue *= SetNextZcMaTailOffset(trainId,singleMaData.MaTailOffset);
        rtnValue *= SetNextZcMaTailDir(trainId,singleMaData.MaTailDir);
        rtnValue *= SetNextZcMaEndAttribute(trainId,singleMaData.MaEndAttribute);
        rtnValue *= SetNextZcObsOfMAStru(trainId,singleMaData.ObsOfMAStru,singleMaData.ObsNum);
		/*pbw 20161021����������ʱ���ٵ���Ŀ*/
        rtnValue *=SetNextZcMaTsrNum(trainId,singleMaData.TsrNum);
        rtnValue *= SetNextZcTsrOfMAStru(trainId,singleMaData.TsrOfMAStru,singleMaData.TsrNum);

        /*��������±�*/
        (*dataIndex) = tempDataIndex;
    } 
    else
    {
        rtnValue = 0U;
    }
   
    return rtnValue;
}

/*
* ���������� ��������ZC���뵥֡�������г����ƶ���Ȩ��Ϣ
* ����˵���� const UINT16_S zcId,ZC��ID
*            const UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcTrainAndMaMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT8_S cycleTrain = DEFAULT_ZERO;
    UINT16_S trainId = DEFAULT_ZERO;
    UINT8_S trainHandInType = DEFAULT_ZERO;
    UINT8_S changeTrainNum = DEFAULT_ZERO;
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S trainExistFlag = DEFAULT_ZERO;
    UINT8_S maExistFlag = DEFAULT_ZERO;
    UINT8_S maType = DEFAULT_ZERO;
    UINT8_S maLength = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S cycleCommTrain = DEFAULT_ZERO;
	UINT8_S trainNumInZc = DEFAULT_ZERO;
	UINT16_S trainIdInZc = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
		/*11.30,dnw,�Դ�������ZC���Ƶ��г�����ͨ�ż�ʱλ����*/
		trainNumInZc = GetTrainCurSum();

		for (cycleCommTrain = DEFAULT_ZERO; cycleCommTrain < trainNumInZc; cycleCommTrain++)
		{
			trainIdInZc = GetTrainIdOfIndex(cycleCommTrain);

			if (GetTrainControlZc(trainIdInZc) == zcId)
			{
				SetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainIdInZc,((UINT16_S)GetTrainAtpCommCycle()));
			} 
			else
			{
				/* ������ */
			}
		}

        /*��ȡ�����±�*/
        tempDataIndex = (*dataIndex);

        /*�����г������ֶ�*/
        changeTrainNum = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*���������г���Ϣ*/
        for (cycleTrain = DEFAULT_ZERO;cycleTrain < changeTrainNum;cycleTrain++)
        {
            trainId = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            trainHandInType = pBuff[tempDataIndex];	
            tempDataIndex = tempDataIndex + 1U;

            /*�����г����ڱ�־*/
            trainExistFlag = pBuff[tempDataIndex];
            tempDataIndex = tempDataIndex + 1U;

            if (FLAG_SET == trainExistFlag)
            {
                if (RETURN_SUCCESS == NextZcTrainMsgParse(trainId,pBuff,&tempDataIndex))	 
                {
                    if (RETURN_SUCCESS == SetTrainHandoverInType(trainId,trainHandInType))
                    {
                        /*������*/
                    } 
                    else
                    {
                        breakFlag = FLAG_SET;
                    }
                } 
                else
                {
                    breakFlag = FLAG_SET;
                }
            }
            else
            {
                /*������*/
                if (RETURN_SUCCESS == SetTrainHandoverInType(trainId,trainHandInType))
                {
                    /*������*/
                } 
                else
                {
                    breakFlag = FLAG_SET;
                }
            }

            /*����MA���ڱ�־*/
            maExistFlag = pBuff[tempDataIndex];
            tempDataIndex = tempDataIndex + 1U;

            LogPrintf(1U,"19.001 tId=%d,inty=%d,tEx=%d,maEx=%d\n",trainId,trainHandInType,trainExistFlag,maExistFlag);

            if (FLAG_SET == maExistFlag)
            {
                /*��������ZC������Ϣ�ڱ��صĿռ�*/
                SetNextZcMaStatusTrainId(trainId);

                /*��д�����Ϣ*/
                SetNextZcHandOutType(trainId,trainHandInType);
                SetNextZcId(trainId,zcId);

                /*����MA����*/
                maType = pBuff[tempDataIndex];
                tempDataIndex = tempDataIndex + 1U;

                /*����MA����*/
                maLength = pBuff[tempDataIndex];
                tempDataIndex = tempDataIndex + 1U;
                SetNextZcMaStatusMaLength(trainId,maLength);

                if (DEFAULT_ZERO < maLength)
                {
                    if (RETURN_SUCCESS == NextZcMaMsgParse(zcId,trainId,pBuff,&tempDataIndex))
                    {
                        /*��������ZC��MA����*/
                        SetNextZcMaInfoFlag(trainId,maType);
                    } 
                    else
                    {
                        /*�������ZC�����MA��Ϣ*/
                        ClearNextZcSingleTrainMaInfo(trainId);

                        /*��������ZC��MA����*/
                        SetNextZcMaInfoFlag(trainId,ABNORMAL_MA_TYPE);
                        breakFlag = FLAG_SET;
                    }
                }
                else
                {
                    /*�������ZC�����MA��Ϣ*/
                    ClearNextZcSingleTrainMaInfo(trainId);

                    if ((ABNORMAL_MA_TYPE == maType)
                        || (NO_MA_TYPE == maType))
                    {
                        /*��������ZC��MA����*/
                        SetNextZcMaInfoFlag(trainId,maType);
                    } 
                    else
                    {
                        /*��������ZC��MA����*/
                        SetNextZcMaInfoFlag(trainId,ABNORMAL_MA_TYPE);
                    }
                }
            }
            else
            {
                /*ɾ������ZC�����MA��Ϣ*/
                DeleteNextZcSingleTrainMaInfo(trainId);
            }
        }

        if (FLAG_SET == breakFlag)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            /*��������±�*/
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
* ���������� ����Ntp����ZC������
* ����˵���� ��
* ����ֵ  �� ��      
*/
void NtpToZcInputDataProcess(void)
{
    UINT16_S dataLen = DEFAULT_ZERO;
    UINT8_S *dataBuff = NULL;
    UINT16_S dataIndex = DEFAULT_ZERO;
    NTPTimeStruct tempNtpTimeStru;
    UINT32_S timeBuff[6] = {0u};
	
    /*��ʼ��*/
    MemorySet(&tempNtpTimeStru,((UINT32_S)(sizeof(NTPTimeStruct))),
                DEFAULT_ZERO,((UINT32_S)(sizeof(NTPTimeStruct))));

    /*��ȡNtp�������ݳ���*/
    dataLen = GetNtpToZcDataLen();

    /*��ȡ�������*/
    dataBuff = GetNtpToZcDataBuff();

    if ((dataLen > DEFAULT_ZERO)
        && (NULL != dataBuff))
    {
        /*����Ntp��������*/
        /*�������������汾�ţ�����ģʽ*/
        SetWorkMode(dataBuff[dataIndex]);
        dataIndex = dataIndex + 1U;

        /*����ϵͳʱ�ӵ�׼ȷ��*/
        SetStratum(dataBuff[dataIndex]);
        dataIndex = dataIndex + 1U;

        /*����������Ϣ*/
        dataIndex = dataIndex + 14U;

        /*����ϵͳʱ�����һ�α��趨����µ�ʱ��*/
        /*MemorySet(&tempNtpTimeStru,sizeof(NTPTimeStruct),DEFAULT_ZERO,sizeof(NTPTimeStruct));*/

        tempNtpTimeStru.Integer =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        tempNtpTimeStru.Fractional =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        SetReferenceTimestamp(tempNtpTimeStru);

        /*�����������յ����������뿪���صı���ʱ��*/
        /*MemorySet(&tempNtpTimeStru,sizeof(NTPTimeStruct),DEFAULT_ZERO,sizeof(NTPTimeStruct));*/

        tempNtpTimeStru.Integer =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        tempNtpTimeStru.Fractional =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        SetOriginateTimestamp(tempNtpTimeStru);

        /*�����ĵ���������ķ�����ʱ��*/
        /*MemorySet(&tempNtpTimeStru,sizeof(NTPTimeStruct),DEFAULT_ZERO,sizeof(NTPTimeStruct));*/

        tempNtpTimeStru.Integer =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        tempNtpTimeStru.Fractional =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        SetReceiveTimestamp(tempNtpTimeStru);

        /*Ӧ�����뿪�������ķ�����ʱ��*/
        /*MemorySet(&tempNtpTimeStru,sizeof(NTPTimeStruct),DEFAULT_ZERO,sizeof(NTPTimeStruct));*/

        tempNtpTimeStru.Integer =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        tempNtpTimeStru.Fractional =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        SetTransmitTimestamp(tempNtpTimeStru);

		/*Before
        Seconds2Calendar(GetLocalNtpTime(),timeBuff);
		LogPrintf(1U,"Before:%d-%d-%d-%d-%d-%d\n",timeBuff[0],timeBuff[1],timeBuff[2],timeBuff[3],timeBuff[4],timeBuff[5]);
		printf("B %d-%d-%d %d-%d-%d\n",timeBuff[0],timeBuff[1],timeBuff[2],timeBuff[3],timeBuff[4],timeBuff[5]);*/
        /*Уʱ����*/
        CalculateNtpTime();

		/*After
		Seconds2Calendar(GetLocalNtpTime(),timeBuff);
		LogPrintf(1U,"After:%d-%d-%d-%d-%d-%d\n",timeBuff[0],timeBuff[1],timeBuff[2],timeBuff[3],timeBuff[4],timeBuff[5]);
		printf("Af %d-%d-%d %d-%d-%d\n",timeBuff[0],timeBuff[1],timeBuff[2],timeBuff[3],timeBuff[4],timeBuff[5]);*/
    } 
    else
    {
        /*������������*/
    }
}

/*
* ���������� ��������ATP����ĵ�֡����
* ����˵���� ��
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
void TrainToZcInputDataProcess(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTargetId = DEFAULT_ZERO;
    UINT8_S *pDataBuff = NULL;
    UINT16_S dataLen = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < GetTrainToZcCurSum();cycle++)
    {
        commTargetId = GetTrainToZcBuffIndexOfTrainId(cycle);

        /*��ȡ���г���������ݳ���*/
        dataLen = GetTrainToZcIdDataBufLen(cycle);

        /*��ȡ���г����������*/
        pDataBuff = GetTrainToZcBufDataOfIndex(cycle);

        /*������֡����*/
        if ((DEFAULT_ZERO != dataLen)
            && (NULL != pDataBuff))
        {
            if (RETURN_SUCCESS == UpdateTrainInputData(commTargetId,dataLen,pDataBuff))
            {
                /*������*/
            } 
            else
            {
                SetTrainToModeToRM0(commTargetId);
				LogPrintf(1u,"%d-B1\n",commTargetId);
            }
        } 
        else
        {
            /*������*/
        }
    }
}

/*
* ���������� �����г���������
* ����˵���� const UINT16_S trainId,�г�ID            
*            const UINT16_S dataLen,���ݳ���(Ԥ��)
*            const UINT8_S *pDataBuff,���ݻ���
* ����ֵ  �� 0: ʧ��
*������������1; �ɹ�
*/
UINT8_S UpdateTrainInputData(const UINT16_S trainId,const UINT16_S dataLen,const UINT8_S pDataBuff[])
{
    UINT16_S  drLampID = DEFAULT_ZERO;                   
    UINT8_S  drLampStatus = DEFAULT_ZERO;              
    UINT16_S addIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    TrainInfoStruct singleTrainInfoStru;

    /*��ʼ��*/
    MemorySet(&singleTrainInfoStru,((UINT32_S)(sizeof(TrainInfoStruct))),
                DEFAULT_ZERO,((UINT32_S)(sizeof(TrainInfoStruct))));

    if (NULL != pDataBuff)
    {
        /*����4�ֽ�ͨ����Ϣ*/
        addIndex = addIndex + 4U;

        /*�����г�Id*/
        singleTrainInfoStru.TrainID = trainId;

        /*�����г�������Ϣ*/
        singleTrainInfoStru.TrainInType = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*�����г��ǰ�ȫλ����Ϣ*/
        singleTrainInfoStru.TrainUnSafeLocStru.TrainHeadLink = ShortFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 2U;

        singleTrainInfoStru.TrainUnSafeLocStru.TrainHeadOffset = LongFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 4U;

        singleTrainInfoStru.TrainUnSafeLocStru.TrainTailLink = ShortFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 2U;

        singleTrainInfoStru.TrainUnSafeLocStru.TrainTailOffset = LongFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 4U;

        /*�����г�ͷ���ǰ�ȫλ�ö�Ӧ���������з���*/
        singleTrainInfoStru.TrainUnsafeDirection = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*�����г�ͷ���ǰ�ȫλ��ʵ�����з���*/
        singleTrainInfoStru.TrainRealDirection = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*�����г���ʻģʽ��Ϣ*/
        singleTrainInfoStru.TrainMode = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*�����г����м�����Ϣ*/
        singleTrainInfoStru.TrainLevel = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*�����г�ʵ���ٶ���Ϣ*/
        singleTrainInfoStru.TrainSpeed = ShortFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 2U;

        /*�����г���ͣ�������ͣ����Ϣ��ͣ������ָվ̨���۷����ת����*/
        singleTrainInfoStru.TrainStopArea = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*�����г���ȷ��������λ��*/
        singleTrainInfoStru.TrainError = ShortFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 2U;

        /*�����г�����ƫ��г��ۼ���������*/
        addIndex = addIndex + 2U;

        /*�����г������ٶȣ������ƶ������ٶȣ�*/
        addIndex = addIndex + 2U;

        /*�����г������Ա�ʾ��*/
        singleTrainInfoStru.TrainIntegrity= pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*���������ƶ�״̬��Ϣ*/
        singleTrainInfoStru.TrainEmergency = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*����վ̨�����۷���ID*/
        drLampID = ShortFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 2U;

        /*����վ̨�����۷���״̬*/
        drLampStatus = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        if (DEFAULT_ZERO != drLampID)
        {
            if (DR_LAMP_LOCAL_SUM_MAX > GetDRLampConfigBufIndex(drLampID))
            {
                rtnValue *=SetDRLampCommand(drLampID,drLampStatus);
                rtnValue *=SetDRLampOfTrainId(drLampID,trainId);
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

        /*��������ATP�Ĺ���״̬�͹�����Ϣ*/
        addIndex = addIndex + 4U;

        /*�����г���ǰ�ܿ�ZC��ID*/
        singleTrainInfoStru.TrainControlZC = (UINT16_S)(ShortFromChar(&pDataBuff[addIndex]) & ((UINT16_S)0x00ffU));
        addIndex = addIndex + 2U;

        /*�������ݷ���ʱ�ı���ʱ�䣨����ATP��ǰ���ںţ�*/
        singleTrainInfoStru.TrainCycle = LongFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 4U;

        /*�����г���Ϣ*/
        if (SetSingleTrainInputDataInfo(trainId,&singleTrainInfoStru))
        {
            /*�������±��������*/
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
* ���������� ����CI�������λ���ݵ���·ͣ����֤����������
* ����˵���� const UINT16 commTargetId,ͨ��CIid
*            const UINT16_S maskId,��λID
*            const UINT8_S maskValue,��·״̬��λֵ
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
static UINT8_S ParseMaskValueToRouteStopReqData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue)
{
    UINT8_S deviceSum = DEFAULT_ZERO;
    UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX] = {DEFAULT_ZERO};
    UINT8_S routeStopReq = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;

    deviceSum = GetReceiveDeviceSum(maskId,INNER_DEVTYPE_CI,commTargetId);

    if (RETURN_SUCCESS == GetReceiveDeviceIdBuff(maskId,INNER_DEVTYPE_CI,commTargetId, SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff))
    {
        switch (maskValue)
        {
        case 0U:
            routeStopReq = ROUTE_STOP_REQ_UNSET;
            break;
        case 1U:
            routeStopReq = ROUTE_STOP_REQ_SET;
            break;
        default:
            routeStopReq = ROUTE_STOP_REQ_UNSET;
            break;
        }

        for (cycle = DEFAULT_ZERO;cycle < deviceSum;cycle++)
        {
            rtnValue &= SetRouteStopReq(deviceIdBuff[cycle],routeStopReq);
        }
    } 
    else
    {
        rtnValue = 0U;
    }

    return rtnValue;
}