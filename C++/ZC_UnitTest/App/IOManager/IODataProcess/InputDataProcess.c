/************************************************************************
*
* 文件名   ：  InputDataProcess.c
* 创建时间 ：  2015.08.14
* 作者     ：  ZC组
* 功能描述 ：  解析组ZC收到的数据管理  
* 备  注	：  无
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
* 功能描述： 输入数据处理
* 参数说明： 无
* 返回值  ： 无      
*/
void InputDataProcess(void)
{
    /*处理ATS输入ZC数据*/
    ProcessTsrCommandsFromAts();/*-bye-*/
    
    /*处理CI输入ZC数据*/
    CiToZcInputDataProcess();

    /*处理相邻ZC输入数据*/
    NextZcInputDataProcess();

    /*处理车载ATP输入数据*/
    TrainToZcInputDataProcess();

    /*处理Ntp输入数据*/
    NtpToZcInputDataProcess();
}

/*
* 功能描述： 解析CI输入数据
* 参数说明： 无
* 返回值  ： 无      
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
            /*将buf信息转换为码位信息*/
            tempRtn = ParseCiInMaskDataToMaskBuf(GetCiToZcDataBuffByIndex(cycle),GetCiToZcIdDataBuffLen(cycle),
                GetReceiveToZcMaskIdMax(INNER_DEVTYPE_CI,commTargetId),maskValueBuff);

            /*解析各设备信息*/
            if (RETURN_SUCCESS == tempRtn)
            {
                /*解析当前数据*/
                if (RETURN_SUCCESS == ParseMaskValueToDeviceData(commTargetId,maskValueBuff))
                {
                    /*Do nothing currently !*/
                } 
                else
                {
                    /*设置与当前CI通信故障*/
                    SetCommTargetStatus(INNER_DEVTYPE_CI,commTargetId,COMM_STATUS_ABNORMAL);
                }
            } 
            else
            {
                /*设置与当前CI通信故障*/
                SetCommTargetStatus(INNER_DEVTYPE_CI,commTargetId,COMM_STATUS_ABNORMAL);
            }
        } 
        else
        {
            /* 获取联锁ID失败 */
        }     
    }
}

/*
* 功能描述： 解析CI输入的单帧数据
* 参数说明： const UINT8 ciInValueBuff[],输入数据
*            const UINT16_S dataLength,输入长度
*            const UINT16_S maskSum,码位总数
*            UINT8_S maskValueBuff[],输出码位
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
*/
UINT8_S ParseCiInMaskDataToMaskBuf(const UINT8_S ciInValueBuff[],const UINT16_S dataLength,const UINT16_S maskSum,UINT8_S maskValueBuff[])
{
    UINT16_S index = 1U;			    /*目标数据缓冲区下标(码位从1开始)*/
    UINT8_S resNum = DEFAULT_ZERO;                    /*余数*/
    UINT16_S cycleLength = DEFAULT_ZERO;				/*源数据缓冲区下标*/
    UINT16_S maskCycle = DEFAULT_ZERO;			    /*码位解析下标*/
    UINT8_S returnValue = DEFAULT_ZERO;               /*默认解析失败*/
    UINT8_S successFlag = DEFAULT_ZERO;               /*解析成功标志*/

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
                /*码位未解析完毕*/
                /*现默认高位存放低码位*/
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

                /*由maskSum修改为maskSum+1,为了解析最后1个码位值,*/
                /*如果要解析的码位个数刚好是8的整数倍,最后1个maskcycle=7了,不会再进循环，故判断成功要在解析之后*/
                if ((maskSum + 1U) == index)
                {
                    /*码位解析完毕*/
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
            /*解析成功*/
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
* 功能描述： 解析CI输入的码位数据到各设备数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT8_S maskValueBuff[],输入码位
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
            /*获取单个码位的信息*/
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
* 功能描述： 解析CI输入的码位数据到道岔设备位置数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskMainValue,道岔定位码位值
*            const UINT8_S maskSideValue,道岔反位码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
* 功能描述： 解析CI输入的码位数据到道岔设备锁闭数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskValue,道岔锁闭码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
* 功能描述： 解析CI输入的码位数据到信号机设备状态数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskValue,信号机状态码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
* 功能描述： 解析CI输入的码位数据到Psd设备状态数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskValue,屏蔽门状态码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
* 功能描述： 解析CI输入的码位数据到Esb设备状态数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskValue,紧急停车按钮状态码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
* 功能描述： 解析CI输入的码位数据到计轴区段设备方向数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskUpDirValue,计轴区段上行码位值
*            const UINT8_S maskDownDirValue,计轴区段下行码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
                /*调试时暂时修改为上行！！！！！！！！*/
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
                /*调试时暂时修改为下行,待和CI确认！！！！！！！！*/
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
* 功能描述： 解析CI输入的码位数据到计轴区段占用数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskValue,计轴区段占用码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
					/*由于道岔四开,设置计轴占用*/
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
* 功能描述： 解析CI输入的码位数据到计轴区段锁闭数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskValue,计轴区段锁闭状态码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
* 功能描述： 解析CI输入的码位数据到进路状态数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskValue,进路状态码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
* 功能描述： 解析CI输入的码位数据到保护区段状态数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskValue,保护区段状态码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
* 功能描述： 解析CI输入的码位数据到无人折返按钮状态数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskValue,无人折返按钮状态码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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
* 功能描述： 解析相邻ZC输入数据
* 参数说明： 无
* 返回值  ： 无      
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

        /*获取该相邻ZC输入的数据长度*/
        dataLen = GetNZcToZcIdDataBufLen(cycle);

        /*获取该相邻ZC输入的数据*/
        pDataBuff = GetNZcToZcBufDataOfIndex(cycle);

        /*解析单帧数据*/
        if ((DEFAULT_ZERO != dataLen)
            && (NULL != pDataBuff))
        {
            if (RETURN_SUCCESS == ParseNextZcInput(commTargetId,pDataBuff))
            {
                /*不处理*/
            } 
            else
            {
                /*设置与当前ZC通信故障*/
                SetCommTargetStatus(INNER_DEVTYPE_ZC,commTargetId,COMM_STATUS_ABNORMAL);
            }
        } 
        else
        {
            /*设置与当前ZC通信故障*/
            SetCommTargetStatus(INNER_DEVTYPE_ZC,commTargetId,COMM_STATUS_ABNORMAL);
        }
    }
}

/*
* 功能描述： 解析相邻ZC输入单帧数据
* 参数说明： const UINT16 zcId,ZC的编号
*            const UINT8_S pBuff[]
* 返回值  ： 0: 失败
*            1: 成功
*/
UINT8_S ParseNextZcInput(const UINT16_S zcId,const UINT8_S pBuff[])
{
    UINT16_S dataIndex = DEFAULT_ZERO;
    UINT16_S parseErrorFlag = DEFAULT_ZERO;
    UINT8_S  rtnValue = DEFAULT_ZERO;

    if (NULL != pBuff)
    {
        /*解析障碍物信息*/
        if (RETURN_SUCCESS == NextZcObsMsgParse(zcId,pBuff,&dataIndex))
        {
            /*不处理*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_1);
        }

        /*解析临时限速信息*/
        if (RETURN_SUCCESS == NextZcTsrMsgParse(zcId,pBuff,&dataIndex))
        {
            /*不处理*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_2);
        }

        /*解析列车和MA信息*/
        if (RETURN_SUCCESS == NextZcTrainAndMaMsgParse(zcId,pBuff,&dataIndex))
        {
            /*不处理*/
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
* 功能描述： 解析相邻ZC输入障碍物数据
* 参数说明： const UINT16_S zcId,ZC的编号
*            const UINT8_S *pBuff,
*            UINT16_S *dataIndex,输入数据的下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcObsMsgParse(const UINT16_S zcId,const UINT8_S *pBuff,UINT16_S *dataIndex)
{
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT16_S parseErrorFlag = DEFAULT_ZERO;
    UINT8_S  rtnValue = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*获取输入数据下标*/
        tempDataIndex = (*dataIndex);

        /*解析进路信息*/
        if (RETURN_SUCCESS == NextZcRouteMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*不处理*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_1);
        }

        /*解析保护区段信息*/
        if (RETURN_SUCCESS == NextZcOverLapMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*不处理*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_2);
        }

        /*解析信号机信息*/
        if (RETURN_SUCCESS == NextZcSignalMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*不处理*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_3);
        }

        /*解析道岔信息*/
        if (RETURN_SUCCESS == NextZcSwitchMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*不处理*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_4);
        }

        /*解析屏蔽门信息*/
        if (RETURN_SUCCESS == NextZcPsdMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*不处理*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_5);
        }

        /*解析紧急停车按钮信息*/
        if (RETURN_SUCCESS == NextZcEsbMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*不处理*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_6);
        }

        /*解析无人折返按钮信息*/
        if (RETURN_SUCCESS == NextZcDrButtonMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*不处理*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_7);
        }

        /*解析无人折返灯信息*/
        if (RETURN_SUCCESS == NextZcDrLampMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*不处理*/
        } 
        else
        {
            parseErrorFlag = (UINT16_S)(parseErrorFlag | ZC_ERROR_CODE_8);
        }

        /*解析计轴信息*/
        if (RETURN_SUCCESS == NextZcAcMsgParse(zcId,pBuff,&tempDataIndex))
        {
            /*不处理*/
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
        /*设置数据下标*/
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
* 功能描述： 读取相邻ZC输入障碍物码位数据
* 参数说明： const UINT16_S bitIndex, 码位值
*            const UINT16_S baseBufIndex,缓存基础下标
*            const UINT8_S baseAddr[]，缓存数组
* 返回值  ： 码位值
*/
UINT8_S GetZcBitValue(const UINT16_S bitIndex, const UINT16_S baseBufIndex,const UINT8_S baseAddr[])
{
    UINT8_S  divisor = DEFAULT_ZERO;                    /*码位表下标对应的字节序号*/
    UINT8_S  remainder = DEFAULT_ZERO;                  /*码位表下表对应的字节中的Bit位*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*对输入的码位表下标相除，获得对应的字节序号*/
    divisor = (UINT8_S)(baseBufIndex + ((2U * (bitIndex - 1U)) / 8U));

    /*对输入的码位表下标取余，获得对应的Bit位*/
    remainder = (UINT8_S)((2U * (bitIndex - 1U)) % 8U);

    if (NULL != baseAddr)
    {
        rtnValue = (UINT8_S)((UINT8_S)(baseAddr[divisor] >> remainder) & ((UINT8_S)0x03U));
    }
    
    return rtnValue;
}

/*
* 功能描述： 解析相邻ZC输入障碍物（进路）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

        /*获取码位信息*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_ROUTE,&localObsNum))
        {
            pObsStru  = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_ROUTE);

            /*获取输入数据中进路数量*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*解析进路信息*/
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

                /*输出数组下标*/
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
* 功能描述： 解析相邻ZC输入障碍物（保护区段）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

        /*获取码位信息*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_OVERLAP,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_OVERLAP);

            /*获取输入数据中保护区段数量*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru )
                && (inputObsNum == localObsNum))
            {
                /*解析保护区段信息*/
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

                /*输出数组下标*/
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
* 功能描述： 解析相邻ZC输入障碍物（信号机）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

        /*获取码位信息*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_SIGNAL,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_SIGNAL);

            /*获取输入数据中信号机数量*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru )
                && (inputObsNum == localObsNum))
            {
                /*解析信号机信息*/
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

                /*输出数组下标*/
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
* 功能描述： 解析相邻ZC输入障碍物（道岔）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

        /*获取码位信息*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_POINT,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_POINT);

            /*获取输入数据中道岔数量*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru )
                && (inputObsNum == localObsNum))
            {
                /*解析道岔信息*/
                for (cycleSwitch = DEFAULT_ZERO;cycleSwitch < localObsNum;cycleSwitch++)
                {
                    obsId = pObsStru [cycleSwitch].ObsId;
                    stateBitIndex = pObsStru[cycleSwitch].StateBitIndex;
                    lockBitIndex = pObsStru[cycleSwitch].LockBitIndex;

                    /*获取道岔位置状态信息*/
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

                    /*获取道岔锁闭信息*/
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

                /*输出数组下标*/
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
* 功能描述： 解析相邻ZC输入障碍物（屏蔽门）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

        /*获取码位信息*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_PSD,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_PSD);

            /*获取输入数据中屏蔽门数量*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*解析屏蔽门信息*/
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

                /*输出数组下标*/
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
* 功能描述： 解析相邻ZC输入障碍物（紧急停车按钮）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

        /*获取码位信息*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_ESB,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_ESB);

            /*获取输入数据中紧急停车按钮数量*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*解析紧急停车按钮信息*/
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

                /*输出数组下标*/
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
* 功能描述： 解析相邻ZC输入障碍物（无人折返按钮）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

        /*获取码位信息*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_DRB,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_DRB);

            /*获取输入数据中无人折返按钮数量*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*解析无人折返按钮信息*/
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

                /*输出数组下标*/
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
* 功能描述： 解析相邻ZC输入障碍物（无人折返灯）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

        /*获取码位信息*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_DRL,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_DRL);

            /*获取输入数据中无人折返灯数量*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*解析无人折返灯信息*/
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

                /*输出数组下标*/
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
* 功能描述： 解析相邻ZC输入障碍物（计轴区段）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

        /*获取码位信息*/
        if (RETURN_SUCCESS == GetObsBitTableNum(zcId,GetLocalZcId(),OBS_TYPE_AC,&localObsNum))
        {
            pObsStru = GetObsBitTableStrInfo(zcId,GetLocalZcId(),OBS_TYPE_AC);

            /*获取输入数据中计轴区段数量*/
            inputObsNum = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if ((NULL != pObsStru)
                && (inputObsNum == localObsNum))
            {
                /*解析计轴区段信息*/
                for (cycle = DEFAULT_ZERO;cycle < localObsNum;cycle++)
                {
                    obsId = pObsStru[cycle].ObsId;
                    bitIndex = pObsStru[cycle].StateBitIndex;

                    /*获取计轴区段方向*/
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

                    /*获取计轴区段占用/空闲*/
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

                    /*获取计轴区段锁闭*/
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

                    /*获取计轴区段UT状态*/
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

                    /*获取计轴区段ARB状态*/
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

                    /*所有状态包含在2个字节中,预留6个bit位*/
                    tempDataIndex += 2U;

                    SetAcUtRedundance(obsId,pBuff[tempDataIndex]);
                    tempDataIndex = tempDataIndex + 1U;

                    SetAcArbRedundance(obsId,pBuff[tempDataIndex]);
                    tempDataIndex = tempDataIndex + 1U;

                    /*列车序列*/
                    trainNumInAc = pBuff[tempDataIndex];
                    tempDataIndex = tempDataIndex + 1U;

                    for (cycleTrain = DEFAULT_ZERO;cycleTrain < trainNumInAc;cycleTrain++)
                    {
                        trainSequenceBuff[cycleTrain] = ShortFromChar(&pBuff[tempDataIndex]);
                        tempDataIndex += 2U;
                    }

                    SetAcTrainSequenceBuff(obsId,trainSequenceBuff,trainNumInAc);
                }

                /*输出数组下标*/
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
* 功能描述： 解析相邻ZC输入临时限速数据
* 参数说明： const UINT16 zcId,zcId
*            const UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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
        /*获取下标*/
        tempDataIndex = (*dataIndex);

        /*先申请Tsr下标*/
        AplyTsrIndexOfZcId(zcId);

        /*获取存储的Tsr结构中该ZCid对应下标*/
        zcIndexInTsr = GeZcIdOfTsrBufIndex(zcId);

        /*解析临时限速个数*/
        tsrNum = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        if (zcIndexInTsr < TSR_BUFF_SUM_MAX)
        {
            /*清空该ZC对应的临时限速信息*/
            DeleteSingleZcTsrInfo(zcId);

            for (cycleTsr = DEFAULT_ZERO;cycleTsr < tsrNum;cycleTsr++)
            {
                tsrSpeed = ShortFromChar(&pBuff[tempDataIndex]);
                tempDataIndex = tempDataIndex + 2U;

                /*获取单个临时限速包含的逻辑区段数量*/
                logicNum = ShortFromChar(&pBuff[tempDataIndex]);
                tempDataIndex = tempDataIndex + 2U;

                for (cycleLogic = DEFAULT_ZERO;cycleLogic < logicNum;cycleLogic++)
                {
                    sectionIdBuff[cycleLogic] = ShortFromChar(&pBuff[tempDataIndex]);
                    tempDataIndex = tempDataIndex + 2U;
                }

                /* 设置临时限速值 */
                SetSingleTsrDataOfSpeed(zcIndexInTsr,((UINT16_S)cycleTsr),tsrSpeed);

                /* 设置临时限速包含的逻辑区段 */
                SetSingleTsrDataOfSectionInfo(zcIndexInTsr,cycleTsr,(UINT8_S)logicNum,sectionIdBuff);
            }

            /*设置临时限速总数*/
            SetZcIdOfTsrNum(zcIndexInTsr,tsrNum);

            /*设置下标*/
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
* 功能描述： 解析相邻ZC输入单帧数据中列车信息
* 参数说明： const UINT16_S trainId,列车的ID
*            const UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcTrainMsgParse(const UINT16_S trainId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S setValue = DEFAULT_ZERO;
    TrainInfoStruct singleTrainInfoStru;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
	UINT16_S controlZc = DEFAULT_ZERO;
	
    /*初始化*/
    MemorySet(&singleTrainInfoStru,((UINT32_S)(sizeof(TrainInfoStruct))),
                DEFAULT_ZERO,((UINT32_S)(sizeof(TrainInfoStruct))));

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*获取输入下标*/
        tempDataIndex = (*dataIndex);

        /*填写列车ID*/
        singleTrainInfoStru.TrainID = trainId;

        /*解析列车类型*/
        singleTrainInfoStru.TrainType = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*解析当前受控ZCID*/
        singleTrainInfoStru.TrainControlZC = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);	

        /*解析列车当前周期号*/
        singleTrainInfoStru.TrainCycle = LongFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);	

        /*解析列车通信计时位*/
        setValue = SetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId,((UINT16_S)pBuff[tempDataIndex]));
        tempDataIndex = tempDataIndex + 1U;

        /*解析车载ATP与ZC的通信状态*/
        setValue &= SetCommTargetStatus(INNER_DEVTYPE_TRAIN,trainId,pBuff[tempDataIndex]);
        tempDataIndex = tempDataIndex + 1U;
		
        /*解析列车前端可疑标志*/
        singleTrainInfoStru.SuspectHead = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*解析列车后端可疑标志*/
        singleTrainInfoStru.SuspectTail = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*解析列车安全车头所在计轴区段*/
        singleTrainInfoStru.TrainHeadAC = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*解析列车安全车尾所在计轴区段*/
        singleTrainInfoStru.TrainTailAC = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*解析列车非安全车头所在计轴区段*/
        singleTrainInfoStru.TrainUnsafeHeadAC = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*解析列车非安全车尾所在计轴区段*/
        singleTrainInfoStru.TrainUnsafeTailAC = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*解析列车前方需要防护的信号机*/
        singleTrainInfoStru.TrainFrontSignal = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*解析列车闯过信号机防护标志*/
        singleTrainInfoStru.SignalProtection = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*解析列车安全位置结构体*/
        singleTrainInfoStru.TrainSafeLocStru.TrainHeadLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        singleTrainInfoStru.TrainSafeLocStru.TrainHeadOffset = LongFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        singleTrainInfoStru.TrainSafeLocStru.TrainTailLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        singleTrainInfoStru.TrainSafeLocStru.TrainTailOffset = LongFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        /*填写列车非安全位置结构体*/
        singleTrainInfoStru.TrainUnSafeLocStru.TrainHeadLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        singleTrainInfoStru.TrainUnSafeLocStru.TrainHeadOffset = LongFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        singleTrainInfoStru.TrainUnSafeLocStru.TrainTailLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        singleTrainInfoStru.TrainUnSafeLocStru.TrainTailOffset = LongFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        /*不确定误差和倒溜偏差*/
        singleTrainInfoStru.TrainError = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*填写列车头部非安全位置对应的期望运行方向*/
        singleTrainInfoStru.TrainUnsafeDirection = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*填写列车头部非安全位置实际运行方向*/
        singleTrainInfoStru.TrainRealDirection = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*填写列车驾驶模式信息*/
        singleTrainInfoStru.TrainMode = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*填写列车运行级别信息*/
        singleTrainInfoStru.TrainLevel = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*填写列车实际速度信息*/
        singleTrainInfoStru.TrainSpeed = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*填写列车停车区域停稳信息*/
        singleTrainInfoStru.TrainStopArea = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*填写列车完整性标示码*/		
        singleTrainInfoStru.TrainIntegrity = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*填写列车紧急停车标示信息*/
        singleTrainInfoStru.TrainEmergency = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        localZcId = GetLocalZcId();
        controlZc = GetTrainControlZc(trainId);

        if (controlZc == localZcId)
        {         
            /*列车的受控ZC已变为本ZC,不再在相邻ZC输入中更新列车信息*/
            if (localZcId != singleTrainInfoStru.TrainControlZC)
            {
                setValue &= SetSingleTrainNextZcInputDataInfo(trainId,&singleTrainInfoStru);
            }
        } 
        else
        {
            /*设置列车信息*/
            setValue &= SetSingleTrainNextZcInputDataInfo(trainId,&singleTrainInfoStru);
        }

        if (RETURN_SUCCESS == setValue)
        {
            /*设置输出下标*/
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
* 功能描述： 解析相邻ZC输入单帧数据中列车移动授权信息
* 参数说明： const UINT16_S zcId,相邻ZC的编号
*            const UINT16_S trainId,列车的ID
*            const UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcMaMsgParse(const UINT16_S zcId,const UINT16_S trainId,const UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S cycleMaMsg = DEFAULT_ZERO;
    NextZcMaDataStruct singleMaData;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S tsrSpeed = DEFAULT_ZERO;         /* 临时限速的速度值 */
    UINT16_S tsrStartLink = DEFAULT_ZERO;     /* 临时限速的起点所处link */
    UINT32_S tsrStartOffset = DEFAULT_ZERO;   /* 临时限速的起点所处offset */
    UINT16_S tsrEndLink = DEFAULT_ZERO;       /* 临时限速的终点所处link */
    UINT32_S tsrEndOffset = DEFAULT_ZERO;     /* 临时限速的终点所处offset */
    UINT8_S  tsrSum = DEFAULT_ZERO;           /* 属于相邻ZC的临时限速个数 */

    /*初始化*/
    MemorySet(&singleMaData,((UINT32_S)(sizeof(NextZcMaDataStruct))),
                DEFAULT_ZERO,((UINT32_S)(sizeof(NextZcMaDataStruct))));

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*获取输入下标*/
        tempDataIndex = (*dataIndex);

        /*MA终点障碍物类型*/
        singleMaData.MaEndAttribute = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*解析MA起点*/
        singleMaData.MaHeadLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*解析MA起点Offset*/
        singleMaData.MaHeadOffset = LongFromChar(&pBuff[tempDataIndex]);	
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        /*解析MA起点方向*/
        singleMaData.MaHeadDir = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*解析MA终点*/
        singleMaData.MaTailLink = ShortFromChar(&pBuff[tempDataIndex]);
        tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

        /*填写MA终点Offset*/
        singleMaData.MaTailOffset = LongFromChar(&pBuff[tempDataIndex]);	
        tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

        /*填写MA终点方向*/
        singleMaData.MaTailDir = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*填写MA范围内的障碍物数量*/
        singleMaData.ObsNum = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*循环解析MA范围内的障碍物*/
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

        /*解析MA范围内的临时限速数量*/
        tsrSum = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

		
        /*循环解析MA范围内的临时限速信息*/
        for(cycleMaMsg = DEFAULT_ZERO;cycleMaMsg < tsrSum;cycleMaMsg++)
        {                   
            /*解析MA范围内临时限速值*/
            tsrSpeed = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*解析临时限速与MA范围重合的始端Link*/
            tsrStartLink = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*解析临时限速与MA范围重合的始端Offset*/
            tsrStartOffset = LongFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*解析临时限速与MA范围重合的终端Link*/
            tsrEndLink = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*解析临时限速与MA范围重合的终端Offset*/
            tsrEndOffset = LongFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /* 因接管ZC的MA信息当中有属于移交ZC的临时限速,需要过滤 */
            if (RETURN_ERROR == CheckMaTsrInLocalZc(tsrStartLink,tsrStartOffset,tsrEndLink,tsrEndOffset))
            {
                /* 不属于本ZC,填写相邻ZC的编号 */
                singleMaData.TsrOfMAStru[cycleMaMsg].BelongZcId = zcId;

                /* 填写临时限速相关信息 */
                singleMaData.TsrOfMAStru[cycleMaMsg].TsrSpeed = tsrSpeed;
                singleMaData.TsrOfMAStru[cycleMaMsg].TsrHeadLink = tsrStartLink;
                singleMaData.TsrOfMAStru[cycleMaMsg].TsrHeadOffset = tsrStartOffset;
                singleMaData.TsrOfMAStru[cycleMaMsg].TsrTailLink = tsrEndLink;
                singleMaData.TsrOfMAStru[cycleMaMsg].TsrTailOffset = tsrEndOffset;

                /* 限速的数量加1 */
                singleMaData.TsrNum++;
            }
            

#if 0
            singleMaData.TsrOfMAStru[cycleMaMsg].TsrSpeed = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*解析临时限速与MA范围重合的始端Link*/
            singleMaData.TsrOfMAStru[cycleMaMsg].TsrHeadLink = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*解析临时限速与MA范围重合的始端Offset*/
            singleMaData.TsrOfMAStru[cycleMaMsg].TsrHeadOffset = LongFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*解析临时限速与MA范围重合的终端Link*/
            singleMaData.TsrOfMAStru[cycleMaMsg].TsrTailLink = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*解析临时限速与MA范围重合的终端Offset*/
            singleMaData.TsrOfMAStru[cycleMaMsg].TsrTailOffset = LongFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);
#endif
        }

        /*设置相应的信息*/
        rtnValue = SetNextZcMaHeadLink(trainId,singleMaData.MaHeadLink);
        rtnValue *= SetNextZcMaHeadOffset(trainId,singleMaData.MaHeadOffset);
        rtnValue *= SetNextZcMaHeadDir(trainId,singleMaData.MaHeadDir);
        rtnValue *= SetNextZcMaTailLink(trainId,singleMaData.MaTailLink);
        rtnValue *= SetNextZcMaTailOffset(trainId,singleMaData.MaTailOffset);
        rtnValue *= SetNextZcMaTailDir(trainId,singleMaData.MaTailDir);
        rtnValue *= SetNextZcMaEndAttribute(trainId,singleMaData.MaEndAttribute);
        rtnValue *= SetNextZcObsOfMAStru(trainId,singleMaData.ObsOfMAStru,singleMaData.ObsNum);
		/*pbw 20161021增加设置临时限速的数目*/
        rtnValue *=SetNextZcMaTsrNum(trainId,singleMaData.TsrNum);
        rtnValue *= SetNextZcTsrOfMAStru(trainId,singleMaData.TsrOfMAStru,singleMaData.TsrNum);

        /*设置输出下标*/
        (*dataIndex) = tempDataIndex;
    } 
    else
    {
        rtnValue = 0U;
    }
   
    return rtnValue;
}

/*
* 功能描述： 解析相邻ZC输入单帧数据中列车和移动授权信息
* 参数说明： const UINT16_S zcId,ZC的ID
*            const UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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
		/*11.30,dnw,对处于输入ZC控制的列车进行通信计时位控制*/
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
				/* 不处理 */
			}
		}

        /*获取输入下标*/
        tempDataIndex = (*dataIndex);

        /*解析列车数量字段*/
        changeTrainNum = pBuff[tempDataIndex];
        tempDataIndex = tempDataIndex + 1U;

        /*遍历所有列车信息*/
        for (cycleTrain = DEFAULT_ZERO;cycleTrain < changeTrainNum;cycleTrain++)
        {
            trainId = ShortFromChar(&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            trainHandInType = pBuff[tempDataIndex];	
            tempDataIndex = tempDataIndex + 1U;

            /*解析列车存在标志*/
            trainExistFlag = pBuff[tempDataIndex];
            tempDataIndex = tempDataIndex + 1U;

            if (FLAG_SET == trainExistFlag)
            {
                if (RETURN_SUCCESS == NextZcTrainMsgParse(trainId,pBuff,&tempDataIndex))	 
                {
                    if (RETURN_SUCCESS == SetTrainHandoverInType(trainId,trainHandInType))
                    {
                        /*不处理*/
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
                /*不处理*/
                if (RETURN_SUCCESS == SetTrainHandoverInType(trainId,trainHandInType))
                {
                    /*不处理*/
                } 
                else
                {
                    breakFlag = FLAG_SET;
                }
            }

            /*解析MA存在标志*/
            maExistFlag = pBuff[tempDataIndex];
            tempDataIndex = tempDataIndex + 1U;

            LogPrintf(1U,"19.001 tId=%d,inty=%d,tEx=%d,maEx=%d\n",trainId,trainHandInType,trainExistFlag,maExistFlag);

            if (FLAG_SET == maExistFlag)
            {
                /*申请相邻ZC输入信息在本地的空间*/
                SetNextZcMaStatusTrainId(trainId);

                /*填写相关信息*/
                SetNextZcHandOutType(trainId,trainHandInType);
                SetNextZcId(trainId,zcId);

                /*解析MA类型*/
                maType = pBuff[tempDataIndex];
                tempDataIndex = tempDataIndex + 1U;

                /*解析MA长度*/
                maLength = pBuff[tempDataIndex];
                tempDataIndex = tempDataIndex + 1U;
                SetNextZcMaStatusMaLength(trainId,maLength);

                if (DEFAULT_ZERO < maLength)
                {
                    if (RETURN_SUCCESS == NextZcMaMsgParse(zcId,trainId,pBuff,&tempDataIndex))
                    {
                        /*设置相邻ZC的MA类型*/
                        SetNextZcMaInfoFlag(trainId,maType);
                    } 
                    else
                    {
                        /*清除相邻ZC输入的MA信息*/
                        ClearNextZcSingleTrainMaInfo(trainId);

                        /*设置相邻ZC的MA类型*/
                        SetNextZcMaInfoFlag(trainId,ABNORMAL_MA_TYPE);
                        breakFlag = FLAG_SET;
                    }
                }
                else
                {
                    /*清除相邻ZC输入的MA信息*/
                    ClearNextZcSingleTrainMaInfo(trainId);

                    if ((ABNORMAL_MA_TYPE == maType)
                        || (NO_MA_TYPE == maType))
                    {
                        /*设置相邻ZC的MA类型*/
                        SetNextZcMaInfoFlag(trainId,maType);
                    } 
                    else
                    {
                        /*设置相邻ZC的MA类型*/
                        SetNextZcMaInfoFlag(trainId,ABNORMAL_MA_TYPE);
                    }
                }
            }
            else
            {
                /*删除相邻ZC输入的MA信息*/
                DeleteNextZcSingleTrainMaInfo(trainId);
            }
        }

        if (FLAG_SET == breakFlag)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            /*设置输出下标*/
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
* 功能描述： 处理Ntp输入ZC的数据
* 参数说明： 无
* 返回值  ： 无      
*/
void NtpToZcInputDataProcess(void)
{
    UINT16_S dataLen = DEFAULT_ZERO;
    UINT8_S *dataBuff = NULL;
    UINT16_S dataIndex = DEFAULT_ZERO;
    NTPTimeStruct tempNtpTimeStru;
    UINT32_S timeBuff[6] = {0u};
	
    /*初始化*/
    MemorySet(&tempNtpTimeStru,((UINT32_S)(sizeof(NTPTimeStruct))),
                DEFAULT_ZERO,((UINT32_S)(sizeof(NTPTimeStruct))));

    /*获取Ntp输入数据长度*/
    dataLen = GetNtpToZcDataLen();

    /*获取输入输出*/
    dataBuff = GetNtpToZcDataBuff();

    if ((dataLen > DEFAULT_ZERO)
        && (NULL != dataBuff))
    {
        /*解析Ntp输入数据*/
        /*解析闰秒数，版本号，工作模式*/
        SetWorkMode(dataBuff[dataIndex]);
        dataIndex = dataIndex + 1U;

        /*解析系统时钟的准确度*/
        SetStratum(dataBuff[dataIndex]);
        dataIndex = dataIndex + 1U;

        /*跳过其他信息*/
        dataIndex = dataIndex + 14U;

        /*解析系统时钟最后一次被设定或更新的时间*/
        /*MemorySet(&tempNtpTimeStru,sizeof(NTPTimeStruct),DEFAULT_ZERO,sizeof(NTPTimeStruct));*/

        tempNtpTimeStru.Integer =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        tempNtpTimeStru.Fractional =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        SetReferenceTimestamp(tempNtpTimeStru);

        /*解析服务器收到的请求报文离开本地的本地时间*/
        /*MemorySet(&tempNtpTimeStru,sizeof(NTPTimeStruct),DEFAULT_ZERO,sizeof(NTPTimeStruct));*/

        tempNtpTimeStru.Integer =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        tempNtpTimeStru.Fractional =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        SetOriginateTimestamp(tempNtpTimeStru);

        /*请求报文到达服务器的服务器时间*/
        /*MemorySet(&tempNtpTimeStru,sizeof(NTPTimeStruct),DEFAULT_ZERO,sizeof(NTPTimeStruct));*/

        tempNtpTimeStru.Integer =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        tempNtpTimeStru.Fractional =  LongFromChar(&dataBuff[dataIndex]);
        dataIndex = dataIndex + 4U;

        SetReceiveTimestamp(tempNtpTimeStru);

        /*应答报文离开服务器的服务器时间*/
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
        /*校时函数*/
        CalculateNtpTime();

		/*After
		Seconds2Calendar(GetLocalNtpTime(),timeBuff);
		LogPrintf(1U,"After:%d-%d-%d-%d-%d-%d\n",timeBuff[0],timeBuff[1],timeBuff[2],timeBuff[3],timeBuff[4],timeBuff[5]);
		printf("Af %d-%d-%d %d-%d-%d\n",timeBuff[0],timeBuff[1],timeBuff[2],timeBuff[3],timeBuff[4],timeBuff[5]);*/
    } 
    else
    {
        /*本周期无输入*/
    }
}

/*
* 功能描述： 解析车载ATP输入的单帧数据
* 参数说明： 无
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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

        /*获取该列车输入的数据长度*/
        dataLen = GetTrainToZcIdDataBufLen(cycle);

        /*获取该列车输入的数据*/
        pDataBuff = GetTrainToZcBufDataOfIndex(cycle);

        /*解析单帧数据*/
        if ((DEFAULT_ZERO != dataLen)
            && (NULL != pDataBuff))
        {
            if (RETURN_SUCCESS == UpdateTrainInputData(commTargetId,dataLen,pDataBuff))
            {
                /*不处理*/
            } 
            else
            {
                SetTrainToModeToRM0(commTargetId);
				LogPrintf(1u,"%d-B1\n",commTargetId);
            }
        } 
        else
        {
            /*不处理*/
        }
    }
}

/*
* 功能描述： 更新列车输入数据
* 参数说明： const UINT16_S trainId,列车ID            
*            const UINT16_S dataLen,数据长度(预留)
*            const UINT8_S *pDataBuff,数据缓存
* 返回值  ： 0: 失败
*　　　　　　1; 成功
*/
UINT8_S UpdateTrainInputData(const UINT16_S trainId,const UINT16_S dataLen,const UINT8_S pDataBuff[])
{
    UINT16_S  drLampID = DEFAULT_ZERO;                   
    UINT8_S  drLampStatus = DEFAULT_ZERO;              
    UINT16_S addIndex = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    TrainInfoStruct singleTrainInfoStru;

    /*初始化*/
    MemorySet(&singleTrainInfoStru,((UINT32_S)(sizeof(TrainInfoStruct))),
                DEFAULT_ZERO,((UINT32_S)(sizeof(TrainInfoStruct))));

    if (NULL != pDataBuff)
    {
        /*跳过4字节通信信息*/
        addIndex = addIndex + 4U;

        /*设置列车Id*/
        singleTrainInfoStru.TrainID = trainId;

        /*解析列车运行信息*/
        singleTrainInfoStru.TrainInType = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*解析列车非安全位置信息*/
        singleTrainInfoStru.TrainUnSafeLocStru.TrainHeadLink = ShortFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 2U;

        singleTrainInfoStru.TrainUnSafeLocStru.TrainHeadOffset = LongFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 4U;

        singleTrainInfoStru.TrainUnSafeLocStru.TrainTailLink = ShortFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 2U;

        singleTrainInfoStru.TrainUnSafeLocStru.TrainTailOffset = LongFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 4U;

        /*解析列车头部非安全位置对应的期望运行方向*/
        singleTrainInfoStru.TrainUnsafeDirection = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*解析列车头部非安全位置实际运行方向*/
        singleTrainInfoStru.TrainRealDirection = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*解析列车驾驶模式信息*/
        singleTrainInfoStru.TrainMode = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*解析列车运行级别信息*/
        singleTrainInfoStru.TrainLevel = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*解析列车实际速度信息*/
        singleTrainInfoStru.TrainSpeed = ShortFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 2U;

        /*解析列车在停车区域的停稳信息，停车区域指站台，折返轨或转换轨*/
        singleTrainInfoStru.TrainStopArea = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*解析列车不确定性误差（定位误差）*/
        singleTrainInfoStru.TrainError = ShortFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 2U;

        /*跳过列车倒溜偏差（列车累计退行量）*/
        addIndex = addIndex + 2U;

        /*跳过列车限制速度（紧急制动触发速度）*/
        addIndex = addIndex + 2U;

        /*解析列车完整性标示码*/
        singleTrainInfoStru.TrainIntegrity= pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*解析紧急制动状态信息*/
        singleTrainInfoStru.TrainEmergency = pDataBuff[addIndex];
        addIndex = addIndex + 1U;

        /*解析站台无人折返灯ID*/
        drLampID = ShortFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 2U;

        /*解析站台无人折返灯状态*/
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
                /*不处理*/
            }
        } 
        else
        {
            /*不处理*/
        }

        /*跳过车载ATP的工作状态和故障信息*/
        addIndex = addIndex + 4U;

        /*解析列车当前受控ZC的ID*/
        singleTrainInfoStru.TrainControlZC = (UINT16_S)(ShortFromChar(&pDataBuff[addIndex]) & ((UINT16_S)0x00ffU));
        addIndex = addIndex + 2U;

        /*跳过数据发送时的本地时间（车载ATP当前周期号）*/
        singleTrainInfoStru.TrainCycle = LongFromChar(&pDataBuff[addIndex]);
        addIndex = addIndex + 4U;

        /*设置列车信息*/
        if (SetSingleTrainInputDataInfo(trainId,&singleTrainInfoStru))
        {
            /*将数组下标变量返回*/
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
* 功能描述： 解析CI输入的码位数据到进路停车保证请求数据中
* 参数说明： const UINT16 commTargetId,通信CIid
*            const UINT16_S maskId,码位ID
*            const UINT8_S maskValue,进路状态码位值
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
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