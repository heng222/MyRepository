/************************************************************************
*
* 文件名   ：  OutputDataProcess.c
* 创建时间 ：  2015.08.14
* 作者     ：  ZC组
* 功能描述 ：  打包ZC发送的数据管理  
* 备  注	：  无
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
extern unsigned short gStopProRouteId;  /* 停车保证*/
extern unsigned char gStopProReq;
extern unsigned char gStopProResp;
extern unsigned short gDrLampId;  /* 无人折返灯 */
extern unsigned char gDrLampCmd;
#endif
static UINT8_S CalcCtTrainOccLogicSecBuff(const UINT16_S trainId,UINT16_S *pLogicNum,UINT16_S trainSectionOfAcBuff[]);
static UINT8_S ProcessRouteStopConfirmMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* 功能描述： 输出数据处理
* 参数说明： 无
* 返回值  ： 无      
*/
void OutputDataProcess(void)
{
#ifdef SYS_TYPE_WINDOWS
    gStopProReq = GetRouteStopReq(gStopProRouteId);
    SetRouteStopConfirm(gStopProRouteId,gStopProResp);

    if (0x55u == gDrLampCmd)
    {
        /* 闪灯 */
        SetDRLampCommand(gDrLampId,DR_LAMP_TWINKLE_STATUS);
    }
    else if (0xaau == gDrLampCmd)
    {
        /* 稳灯 */
        SetDRLampCommand(gDrLampId,DR_LAMP_STEADY_STATUS);
    }
    else
    {

    }
#endif
    /*处理ZC输出CI的数据*/
    CiOutputDataProcess();

    /*处理ZC输出NZC的数据*/
    NZcOutputDataProcess();

    /*处理ZC输出车载ATP的数据*/
    TrainOutputDataProcess();

    /*处理ZC输出ATS的数据*/
    AtsOutputDataProcess();

    /*处理ZC输出Ntp数据*/
    NtpOutputDataProcess();
}

/*
* 功能描述： 组输出给CI的数据
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S CiOutputDataProcess(void)
{
    UINT8_S commTragetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {0U};
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*初始化*/
    MemorySet(&commTargetIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    /*获取通信对象数量*/
    commTragetNum = GetSingleCommTargetTypeSum(INNER_DEVTYPE_CI);
	
    /*获取通信对象ID数组*/
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
* 功能描述： 组输出给CI的数据
* 参数说明： const UINT16 ciId,联锁的编号
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
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

    /*初始化*/
    MemorySet(&dataBuff[0],((UINT32_S)(SIZE_UINT8 * ZC_CI_COM_BYTE_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * ZC_CI_COM_BYTE_SUM_MAX)));
    MemorySet(&deviceIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_MASK_DEVICE_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_MASK_DEVICE_SUM_MAX)));

    ciIndex = GetSendCommTargetIndex(INNER_DEVTYPE_CI,ciId);

    /*获取码位最大值*/
    maskSum = GetSendToOtherMaskIdMax(INNER_DEVTYPE_CI,ciId);

    if ((COMM_CI_SUM_MAX > ciIndex)
        && (DEFAULT_ZERO < maskSum))
    {
        for (maskCycle = DEFAULT_ZERO;maskCycle < maskSum;maskCycle++)
        {
            /*获取单个码位的信息*/
            maskId = GetSendMaskId(maskCycle,INNER_DEVTYPE_CI,ciId);
            maskType = GetSendMaskType(maskId,INNER_DEVTYPE_CI,ciId);
            GetSendDeviceIdBuff(maskId,INNER_DEVTYPE_CI,ciId,SINGLE_MASK_DEVICE_SUM_MAX,deviceIdBuff);
            relevanceMask = GetSendRelevanceMaskId(maskId,INNER_DEVTYPE_CI,ciId);
            deviceSum = GetSendDeviceSum(maskId,INNER_DEVTYPE_CI,ciId);

            switch (maskType)
            {
            case SECTION_CT_OCC_MASK_TYPE:
                /*处理逻辑区段CT占用码位*/
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
                /*暂时不处理*/
                break;
            case AC_ARB_STATUS_MASK_TYPE:
                /*处理计轴区段ARB占用码位*/
                if (1U == ProcessAcArbMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*不处理*/
                }
                break;
            case AC_STOP_STATUS_MASK_TYPE:
                /*处理计轴区段停稳信息码位*/
                if (1U == ProcessAcStopMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*不处理*/
                }
                break;
            case DR_LAMP_TWINKLE_STATUS_MASK_TYPE:
                /*处理无人折返灯闪灯信息码位*/
                if (1U == ProcessDrLampTwinkleMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*不处理*/
                }
                break;
            case DR_LAMP_STEADY_STATUS_MASK_TYPE:
                /*处理无人折返灯稳灯信息码位*/
                if (1U == ProcessDrLampSteadyMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*不处理*/
                }
                break;
            case SIGNAL_CROSS_MASK_TYPE:
                /*处理信号机跨压信息码位*/
                if (1U == ProcessSignalCrossMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*不处理*/
                }
                break;
            case SIGNAL_LIGHT_OFF_MASK_TYPE:
                /*处理信号机亮灭信息码位*/
                if (1U == ProcessSignalLightOffMask(deviceSum,deviceIdBuff))
                {
                    SetMaskValue(maskId,ZC_CI_COM_BYTE_SUM_MAX,dataBuff);
                } 
                else
                {
                    /*不处理*/
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

        /*填写信息至CI输出数组*/
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
* 功能描述： 填写码位值
* 参数说明： const UINT16 maskId,码位ID
*            const UINT16_S buffSize,数组大小
*            UINT8_S dataBuff[],输出数组
* 返回值  ： 0: 填写失败
*			 1: 填写成功      
*/
UINT8_S SetMaskValue(const UINT16_S maskId,const UINT16_S buffSize,UINT8_S dataBuff[])
{
    UINT16_S divisor = 0U;                    /*码位表下标对应的字节序号*/
    UINT8_S remainder = 0U;                  /*码位表下表对应的字节中的Bit位*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    if ((maskId > 0U) && (dataBuff != NULL))
    {
        /*对输入的码位表下标相除，获得对应的字节序号*/
        divisor = (UINT16_S)(maskId / 8U);

        /*对输入的码位表下标取余，获得对应的Bit位*/
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
* 功能描述： 处理输入给CI的逻辑区段CT列车占用码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],设备ID数组
* 返回值  ： 0: 逻辑区段UT占用
*			 1: 逻辑区段CT占用
*            2: 逻辑区段空闲
*/
UINT8_S ProcessSectionCtMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*获取逻辑区段的占用状态*/
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
        /*错误*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* 功能描述： 处理输入给CI的逻辑区段UT列车占用码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessSectionUtMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*获取逻辑区段的占用状态*/
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
        /*错误*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* 功能描述： 处理输入给CI的计轴区段ARB码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
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
            /*不处理*/
        }
    }

    return rtnValue;
}

/*
* 功能描述： 处理输入给CI的计轴区段停稳码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessAcStopMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S i = DEFAULT_ZERO;
    UINT8_S rtn = RETURN_ERROR;

    /* pbw 2017.5.16 因1个停稳码位可以关联1至3个计轴区段 */
    if (DEFAULT_ZERO < deviceSum)
    {
        /* 遍历该码位关联的所有计轴区段 */
        for(i = DEFAULT_ZERO;i < deviceSum;i++)
        {
            /* 计算计轴区段停稳状态 */
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
        /* 错误 */
        rtnValue = 0U;
    }

    return rtnValue;

#if 0
    if ((1U == deviceSum) || (2U == deviceSum))
    {
        /*计算计轴区段停稳状态*/
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
        /*错误*/
        rtnValue = 0U;
    }

    return rtnValue;

#endif
}

/*
* 功能描述： 处理输入给CI的无人折返灯闪灯码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessDrLampTwinkleMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*获取无人折返灯命令状态*/
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
        /*错误*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* 功能描述： 处理输入给CI的无人折返灯稳灯码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessDrLampSteadyMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*获取无人折返灯命令状态*/
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
        /*错误*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* 功能描述： 处理输入给CI的信号机跨压信息码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessSignalCrossMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*获取信号机跨压状态*/
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
        /*错误*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* 功能描述： 处理输入给CI的信号机亮灭信息码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessSignalLightOffMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*获取信号机亮灭状态*/		
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
        /*错误*/
        rtnValue = 0U;
    }

    return rtnValue;
}

/*
* 功能描述： 组输出给NZC的数据
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
void NZcOutputDataProcess(void)
{
    UINT8_S commTragetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {0U};
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S cycle = 0U;

    MemorySet(&commTargetIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    /*获取通信对象数量*/
    commTragetNum = GetSingleCommTargetTypeSum(INNER_DEVTYPE_ZC);

    /*获取通信对象ID数组*/
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
        /*不处理*/
    }
}

/*
* 功能描述： 组输出给单个NZC的数据
* 参数说明： const UINT16 nZcId,ZCID
* 返回值  ： 无     
*/
void NextZcOutput(const UINT16_S nZcId)
{
    UINT16_S dataIndex = DEFAULT_ZERO;
    UINT8_S pBuff[ZC_NZC_COM_BYTE_SUM_MAX] = {0U};
    UINT16_S packErrorFlag = DEFAULT_ZERO;

    /*初始化*/
    MemorySet(&pBuff[0],((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)),0U,((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)));

    /*障碍物信息组包*/
    if (RETURN_SUCCESS == NextZcObsMsgPack(nZcId,pBuff,&dataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_1);
    }

    /*临时限速信息组包*/
    if (RETURN_SUCCESS == NextZcTsrMsgPack(nZcId,pBuff,&dataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_2);
    }

    /*列车信息组包*/
    if (RETURN_SUCCESS == NextZcTrainAndMaMsgPack(nZcId,pBuff,&dataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_3);
    }

    /*将单帧数据写入缓存区*/
    if (RETURN_SUCCESS == PackZcToNzcFrameData(pBuff,dataIndex,nZcId))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_4);
    }

    LogPrintf(1U,"NZcPack Error=%d\n",packErrorFlag); 
}

/*
* 功能描述： 写输出给单个NZC的码位数据
* 参数说明： UINT8 bitValue,码位值
*            UINT16_S  bitIndex,码位下标
*            UINT8_S baseAddr[],输出数据基地址
* 返回值  ： 无     
*/
void  WriteZcBitValue(UINT8_S bitValue,UINT16_S  bitIndex,UINT8_S baseAddr[])
{
    UINT8_S  divisor = 0U;                    /*码位表下标对应的字节序号*/
    UINT8_S  remainder = 0U;                  /*码位表下标对应的字节中的Bit位*/
    UINT8_S  switchover = 0U;                 /*码位表转换中间变量*/

    /*对输入的码位表下标相除，获得对应的字节序号*/
    divisor = (UINT8_S)((2U * (bitIndex - 1U)) / 8U);

    /*获取数据*/
    switchover = (UINT8_S)((bitIndex - 1U) / 4U);

    /*对输入的码位表下标取余，获得对应的Bit位*/
    remainder = (UINT8_S)((2U * ((bitIndex - (switchover * 4U)) - 1U)) % 8U);


    /*填写码位值*/
    /*lint -e701*/
    baseAddr[divisor] =  (UINT8_S)(baseAddr[divisor] | ((UINT8_S)(bitValue << remainder)));
    /*lint +e701*/
}

/*
* 功能描述： 组输出给单个NZC的数据
* 参数说明： const UINT16 nZcId,ZCID
*			 UINT8_S *pBuff,输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功    
*/
UINT8_S NextZcObsMsgPack(const UINT16_S zcId,UINT8_S *pBuff, UINT16_S *dataIndex)
{
    UINT16_S tempDataIndex = 0U;
    UINT16_S packErrorFlag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*获取输入数据下标*/
    tempDataIndex = (*dataIndex);

    /*组包进路信息*/
    if (RETURN_SUCCESS == NextZcRouteMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_1);
    }

    /*组包保护区段信息*/
    if (RETURN_SUCCESS == NextZcOverlapMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_2);
    }

    /*组包信号机信息*/
    if (RETURN_SUCCESS == NextZcSignalMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_3);
    }

    /*组包道岔信息*/
    if (RETURN_SUCCESS == NextZcSwitchMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_4);
    }

    /*组包屏蔽门信息*/
    if (RETURN_SUCCESS == NextZcPsdMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_5);
    }

    /*组包紧急停车按钮信息*/
    if (RETURN_SUCCESS == NextZcEsbMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_6);
    }

    /*组包无人折返按钮信息*/
    if (RETURN_SUCCESS == NextZcDrButtonMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_7);
    }

    /*组包无人折返灯信息*/
    if (RETURN_SUCCESS == NextZcDrLampMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_8);
    }

    /*组包计轴信息*/
    if (RETURN_SUCCESS == NextZcAcMsgPack(zcId,pBuff,&tempDataIndex))
    {
        /*不处理*/
    } 
    else
    {
        packErrorFlag = (UINT16_S)(packErrorFlag | ZC_ERROR_CODE_9);
    }

    if (DEFAULT_ZERO == packErrorFlag)
    {
        /*设置数据下标*/
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
* 功能描述： 组包相邻ZC输入障碍物（进路）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

    /*获取码位信息*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_ROUTE,&localObsNum);
    pObsStru  = GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_ROUTE);

    if (NULL != pObsStru )
    {
        /*填写输出进路数量*/
        ShortToChar(localObsNum, &pBuff[tempDataIndex]);
        tempDataIndex = tempDataIndex + 2U;

        /*组包进路信息*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*获取进路状态*/
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

        /*输出数组下标*/
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
* 功能描述： 组包相邻ZC输入障碍物（保护区段）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

    /*获取码位信息*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_OVERLAP,&localObsNum);
    pObsStru  =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_OVERLAP);

    /*填写输出障碍物数量*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*组包保护区段信息*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*获取保护区段状态*/
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

        /*输出数组下标*/
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
* 功能描述： 组包相邻ZC输入障碍物（信号机）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

    /*获取码位信息*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_SIGNAL,&localObsNum);
    pObsStru =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_SIGNAL);

    /*填写输出障碍物数量*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*组包信号机信息*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*获取信号机状态*/
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

        /*输出数组下标*/
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
* 功能描述： 组包相邻ZC输入障碍物（道岔）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

    /*获取码位信息*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_POINT,&localObsNum);
    pObsStru =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_POINT);

    /*填写输出障碍物数量*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*组包道岔信息*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            stateBitIndex = pObsStru[i].StateBitIndex;

            /*获取道岔位置状态*/
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

            /*获取道岔锁闭状态*/
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

        /*输出数组下标*/
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
* 功能描述： 组包相邻ZC输入障碍物（屏蔽门）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

    /*获取码位信息*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_PSD,&localObsNum);
    pObsStru =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_PSD);

    /*填写输出障碍物数量*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*组包屏蔽门信息*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*获取屏蔽门状态*/
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

        /*输出数组下标*/
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
* 功能描述： 组包相邻ZC输入障碍物（紧急停车按钮）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

    /*获取码位信息*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_ESB,&localObsNum);
    pObsStru  =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_ESB);

    /*填写输出障碍物数量*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*组包紧急停车按钮信息*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*获取紧急停车按钮状态*/
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

        /*输出数组下标*/
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
* 功能描述： 组包相邻ZC输入障碍物（无人折返按钮）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

    /*获取码位信息*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_DRB,&localObsNum);
    pObsStru  =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_DRB);

    /*填写输出障碍物数量*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*组包无人折返按钮信息*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*获取我无人折返按钮状态*/
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

        /*输出数组下标*/
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
* 功能描述： 组包相邻ZC输入障碍物（无人折返灯）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

    /*获取码位信息*/
    GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_DRL,&localObsNum);
    pObsStru  =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_DRL);

    /*填写输出障碍物数量*/
    ShortToChar(localObsNum, &pBuff[tempDataIndex]);
    tempDataIndex = tempDataIndex + 2U;

    if (NULL != pObsStru )
    {
        /*组包无人折返灯信息*/
        for (i = 0U;i < localObsNum;i++)
        {
            obsId = pObsStru[i].ObsId;
            bitIndex = pObsStru[i].StateBitIndex;

            /*获取无人折返灯状态*/
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

        /*输出数组下标*/
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
* 功能描述： 组包相邻ZC输入障碍物（计轴区段）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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

        /*获取码位信息*/
        if (RETURN_SUCCESS == GetObsBitTableNum(GetLocalZcId(),zcId,OBS_TYPE_AC,&localObsNum))
        {
            pObsStru  =  GetObsBitTableStrInfo(GetLocalZcId(),zcId,OBS_TYPE_AC);

            /*填写输出障碍物数量*/
            ShortToChar(localObsNum, &pBuff[tempDataIndex]);
            tempDataIndex = tempDataIndex + 2U;

            if (NULL != pObsStru )
            {
                /*组包计轴区段信息*/
                for (i = 0U;i < localObsNum;i++)
                {
                    obsId = pObsStru[i].ObsId;
                    bitIndex = pObsStru[i].StateBitIndex;

                    /*获取计轴区段方向状态*/
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

                    /*获取计轴区段占用状态*/
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

                    /*获取计轴区段锁闭状态*/
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

                    /*获取计轴区段UT状态*/
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

                    /*获取计轴区段arb状态*/
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

                    /*跳过2个字节状态信息*/
                    tempDataIndex = tempDataIndex + 2U;

                    /*填写UT冗余信息*/
                    pBuff[tempDataIndex] = GetAcUtRedundance(obsId);
                    tempDataIndex = tempDataIndex + 1U;

                    /*填写ARB冗余信息*/
                    pBuff[tempDataIndex] = GetAcArbRedundance(obsId);
                    tempDataIndex = tempDataIndex + 1U;

                    /*填写列车数量*/
                    trainNumInAc = GetAcTrainOfAcNum(obsId);
                    pBuff[tempDataIndex] = trainNumInAc;
                    tempDataIndex = tempDataIndex + 1U;

                    /*获取计轴内列车序列*/
                    if (RETURN_SUCCESS == GetAcTrainSequenceBuff(obsId,SIZE_MAX_TRAINOFAC,trainSequenceBuff))
                    {
                        for (cycleTrain = DEFAULT_ZERO;cycleTrain < trainNumInAc;cycleTrain++)
                        {
                            /*填写计轴内列车序列*/
                            ShortToChar(trainSequenceBuff[cycleTrain], &pBuff[tempDataIndex]);
                            tempDataIndex = tempDataIndex + 2U;
                        }
                    } 
                    else
                    {
                        /* 不处理 */
                    }

                }

                /*输出数组下标*/
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
* 功能描述： 组包相邻ZC输入临时限速数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
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
        /*获取切换线路逻辑区段*/
        changeAreaRtn = CalculatChangeAreaLogicInfoOfZc(zcId,&changeAreaLogicNum,changeAreaLogicIdBuff);

        /*获取下标*/
        tempDataIndex = (*dataIndex);

        /*缓存临时限速个数下标*/
        tsrNumIndex = tempDataIndex;
        tempDataIndex = tempDataIndex + 1u;

        /*获取存储的Tsr结构中该ZCid对应下标*/
        zcIndexInTsr = GeZcIdOfTsrBufIndex(localZcId);

        if (zcIndexInTsr < TSR_BUFF_SUM_MAX)
        {
            /*获取临时限速个数*/
            tsrNum = GetZcIdOfTsrNum(localZcId);

            for (cycleTsr = 0U;cycleTsr < tsrNum;cycleTsr++)
            {
                /*获取单个临时限速速度*/
                tsrSpeed = GetSingleTsrDataOfSpeed(localZcId,((UINT16_S)cycleTsr));

                /*获取单个临时限速包含的逻辑区段信息*/
                logicNum = GetSingleTsrDataOfSectionNum(localZcId,((UINT16_S)cycleTsr));

                if (RETURN_SUCCESS == GetSingleTsrDataOfSectionBuff(localZcId,((UINT16_S)cycleTsr),SINGLE_TSR_SECTION_SUM_MAX,sectionIdBuff))
                {
                    if (RETURN_ERROR == changeAreaRtn)
                    {
                        /*获取失败,填写完整的逻辑区段*/
                        /*组包临时限速信息*/
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
                        /*查询成功,判断是否和切换区域重合*/
                        for (cycleOfChangeAreaLogic = DEFAULT_ZERO;cycleOfChangeAreaLogic < changeAreaLogicNum;cycleOfChangeAreaLogic++)
                        {
                            for (cycleTsrOfLogic = DEFAULT_ZERO;cycleTsrOfLogic < logicNum;cycleTsrOfLogic++)
                            {
                                if (changeAreaLogicIdBuff[cycleOfChangeAreaLogic] == sectionIdBuff[cycleTsrOfLogic])
                                {
                                    /*有重合,填写临时限速*/
                                    /*组包临时限速信息*/
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
                                    /* 继续遍历 */
                                }
                            }

                            if (flagWrite == FLAG_SET)
                            {
                                break;
                            } 
                            else
                            {
                                /* 不处理 */
                            }
                        }
                    }
                }
                else
                {
                    /* 不处理 */
                }       
            }	
        } 
        else
        {
            /*Do nothing currently !*/
        }

        /*填写临时限速总数*/
        pBuff[tsrNumIndex] = (UINT8_S)countTsrNum;

        /*设置下标*/
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
* 功能描述： 组输出给单个NZC的列车数据
* 参数说明： const UINT16 trainId,列车ID
*            UINT8_S pBuff[],缓存数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功     
*/
UINT8_S NextZcTrainMsgPack(const UINT16_S trainId,UINT8_S pBuff[],UINT16_S *dataIndex)
{
    UINT8_S retVal = RETURN_ERROR;/*函数返回值*/
    UINT16_S tempDataIndex = DEFAULT_ZERO;
    UINT8_S getValue = DEFAULT_ZERO;
    TrainInfoStruct singleTrainInfoSrtu;
    UINT16_S trainCommCycle = DEFAULT_ZERO;
    UINT8_S trainCommStatus = DEFAULT_ZERO;

    if ((NULL != pBuff) && (NULL != dataIndex))
    {
        /*获取下标*/
        tempDataIndex = (*dataIndex);

        getValue = GetSingleTrainInfo(trainId,&singleTrainInfoSrtu);
        trainCommCycle = GetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId);
        trainCommStatus = GetCommTargetStatus(INNER_DEVTYPE_TRAIN,trainId);

        /*填写列车类型*/
        if ((RETURN_ERROR != getValue)
            && (DEFAULT_UINT16_VALUE != trainCommCycle)
            && (DEFAULT_UINT8_VALUE != trainCommStatus))
        {
            pBuff[tempDataIndex] = singleTrainInfoSrtu.TrainType;
            tempDataIndex = tempDataIndex + 1U;

            /*填写当前受控ZCID*/
            ShortToChar(singleTrainInfoSrtu.TrainControlZC,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);	

            /*填写列车当前周期号*/
            LongToChar(singleTrainInfoSrtu.TrainCycle,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);	

            /*填写列车通信计时位*/
            pBuff[tempDataIndex] = (UINT8_S)trainCommCycle;
            tempDataIndex = tempDataIndex + 1U;

            /*填写车载与ZC的通信状态*/
            pBuff[tempDataIndex] = trainCommStatus;	
            tempDataIndex = tempDataIndex + 1U;

            /*填写列车前端可疑标志*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.SuspectHead;	
            tempDataIndex = tempDataIndex + 1U;

            /*填写列车后端可疑标志*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.SuspectTail;	
            tempDataIndex = tempDataIndex + 1U;

            /*填写列车安全车头所在计轴区段*/
            ShortToChar(singleTrainInfoSrtu.TrainHeadAC,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*填写列车安全尾所在计轴区段*/
            ShortToChar(singleTrainInfoSrtu.TrainTailAC,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*填写列车非安全车头所在计轴区段*/
            ShortToChar(singleTrainInfoSrtu.TrainUnsafeHeadAC,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*填写列车非安全尾所在计轴区段*/
            ShortToChar(singleTrainInfoSrtu.TrainUnsafeTailAC,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*填写列车前方需要防护的信号机*/
            ShortToChar(singleTrainInfoSrtu.TrainFrontSignal,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*填写列车闯过信号机防护标志*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.SignalProtection;	
            tempDataIndex = tempDataIndex + 1U;

            /*填写列车安全位置结构体*/
            ShortToChar(singleTrainInfoSrtu.TrainSafeLocStru.TrainHeadLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            LongToChar(singleTrainInfoSrtu.TrainSafeLocStru.TrainHeadOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            ShortToChar(singleTrainInfoSrtu.TrainSafeLocStru.TrainTailLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            LongToChar(singleTrainInfoSrtu.TrainSafeLocStru.TrainTailOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*填写列车非安全位置结构体*/
            ShortToChar(singleTrainInfoSrtu.TrainUnSafeLocStru.TrainHeadLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            LongToChar(singleTrainInfoSrtu.TrainUnSafeLocStru.TrainHeadOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            ShortToChar(singleTrainInfoSrtu.TrainUnSafeLocStru.TrainTailLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            LongToChar(singleTrainInfoSrtu.TrainUnSafeLocStru.TrainTailOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*不确定误差和倒溜偏差*/
            ShortToChar(singleTrainInfoSrtu.TrainError,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*填写列车头部非安全位置对应的期望运行方向*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainUnsafeDirection;
            tempDataIndex = tempDataIndex + 1U;

            /*填写列车头部非安全位置实际运行方向*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainRealDirection;
            tempDataIndex = tempDataIndex + 1U;

            /*填写列车驾驶模式信息*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainMode;
            tempDataIndex = tempDataIndex + 1U;

            /*填写列车运行级别信息*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainLevel;
            tempDataIndex = tempDataIndex + 1U;

            /*填写列车实际速度信息*/
            ShortToChar(singleTrainInfoSrtu.TrainSpeed,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*填写列车停车区域停稳信息*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainStopArea;
            tempDataIndex = tempDataIndex + 1U;

            /*填写列车完整性标示码*/		
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainIntegrity;
            tempDataIndex = tempDataIndex + 1U;

            /*填写列车紧急停车标示信息*/
            pBuff[tempDataIndex] =singleTrainInfoSrtu.TrainEmergency;
            tempDataIndex = tempDataIndex + 1U;

            /*设置下标*/
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
* 功能描述： 组输出给单个NZC的列车移动授权数据
* 参数说明： const UINT16 trainId,列车ID
*            UINT8_S pBuff[],缓存数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功       
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
        /*获取下标*/
        tempDataIndex = (*dataIndex);

        /*缓存ma长度下标*/
        maLenIndex = tempDataIndex;
        tempDataIndex++;

        getValue = GeSingleMaInfo(trainId,&singleMaDataStru);

        if (RETURN_ERROR != getValue)
        {
            /*填写MA终点类型*/
            pBuff[tempDataIndex] = singleMaDataStru.MaEndAttribute;
            tempDataIndex = tempDataIndex + 1U;

            /*填写MA起点*/
            ShortToChar(singleMaDataStru.MaHeadLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*填写MA起点Offset*/
            LongToChar(singleMaDataStru.MaHeadOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*填写MA起点方向*/
            pBuff[tempDataIndex] = singleMaDataStru.MaHeadDir;
            tempDataIndex = tempDataIndex + 1U;

            /*填写MA终点*/
            ShortToChar(singleMaDataStru.MaTailLink,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

            /*填写MA起点Offset*/
            LongToChar(singleMaDataStru.MaTailOffset,&pBuff[tempDataIndex]);
            tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

            /*填写MA起点方向*/
            pBuff[tempDataIndex] = singleMaDataStru.MaTailDir;
            tempDataIndex = tempDataIndex + 1U;

            /*填写MA范围内的障碍物数量*/
            pBuff[tempDataIndex] = singleMaDataStru.ObsNum;
            tempDataIndex = tempDataIndex + 1U;

            /*循环填写MA范围内的障碍物*/
            for(i = 0U;i < singleMaDataStru.ObsNum;i++)
            {			
                obsId = singleMaDataStru.ObsOfMAStru[i].ObsId;
                obsType = singleMaDataStru.ObsOfMAStru[i].ObsType;

                /*填写MA范围内障碍物的类型*/
                pBuff[tempDataIndex] = obsType;
                tempDataIndex = tempDataIndex + 1U;

                /*填写MA范围内障碍物的ID*/
                ShortToChar(obsId,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

                /*提取障碍物的类型*/
                switch(obsType)
                {
                case  OBS_TYPE_ESB:
                    {
                        /*说明本障碍物为站台紧急关闭按钮*/
                        /*填写MA范围内障碍物当前状态*/
                        pBuff[tempDataIndex]= GetEsbStatus(obsId);
                        tempDataIndex = tempDataIndex + 1U;

                        /*填写MA范围内障碍物的联锁状态，ESP无联锁状态，填写当前状态*/
                        pBuff[tempDataIndex]= GetEsbStatus(obsId);
                        tempDataIndex = tempDataIndex + 1U;

                        break;
                    }

                case  OBS_TYPE_PSD:
                    {
                        /*说明本障碍物为站台安全门*/
                        /*填写MA范围内障碍物当前状态*/
                        pBuff[tempDataIndex]= GetPsdStatus(obsId);
                        tempDataIndex = tempDataIndex + 1U;

                        /*填写MA范围内障碍物的联锁状态，PSD无联锁状态，填写当前状态*/
                        pBuff[tempDataIndex]= GetPsdStatus(obsId);
                        tempDataIndex = tempDataIndex + 1U;

                        break;
                    }

                case  OBS_TYPE_POINT:
                    {
                        /*说明本障碍物为道岔*/
                        /*填写MA范围内障碍物当前状态*/
                        pBuff[tempDataIndex]= GetSwitchPosStatus(obsId);
                        tempDataIndex = tempDataIndex + 1U;

                        /*填写MA范围内障碍物的联锁状态*/
                        /*判断本道岔当前是否锁闭*/
                        if(FLAG_SET == GetSwitchLock(obsId))
                        {
                            /*说明本道岔当前处于锁闭状态，填写为当前状态*/
                            pBuff[tempDataIndex]= GetSwitchPosStatus(obsId);
                            tempDataIndex = tempDataIndex + 1U;
                        }
                        else
                        {
                            /*说明本道岔当前未锁闭，填写为四开（暂定）*/
                            pBuff[tempDataIndex] = (UINT8_S)SWITCH_STATE_LOSE;
                            tempDataIndex = tempDataIndex + 1U;
                        }

                        break;
                    }

                default:
                    {
                        /*说明障碍物类型错误*/
                        break;
                    }
                }
            }

            /*填写MA范围内的临时限速数量*/
            pBuff[tempDataIndex] = singleMaDataStru.TsrNum;
            tempDataIndex = tempDataIndex + 1U;

            /*循环天下MA范围内的临时限速信息*/
            for(i = 0U;i < singleMaDataStru.TsrNum;i++)
            {
                /*填写MA范围内临时限速值*/
                ShortToChar(singleMaDataStru.TsrOfMAStru[i].TsrSpeed,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

                /*填写临时限速与MA范围重合的始端Link*/
                ShortToChar(singleMaDataStru.TsrOfMAStru[i].TsrHeadLink,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

                /*填写临时限速与MA范围重合的始端Offset*/
                LongToChar(singleMaDataStru.TsrOfMAStru[i].TsrHeadOffset,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 4U);

                /*填写临时限速与MA范围重合的终端Link*/
                ShortToChar(singleMaDataStru.TsrOfMAStru[i].TsrTailLink,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 2U);

                /*填写临时限速与MA范围重合的终端Offset*/
                LongToChar(singleMaDataStru.TsrOfMAStru[i].TsrTailOffset,&pBuff[tempDataIndex]);
                tempDataIndex = (UINT16_S)(tempDataIndex + 4U);
            }

            /*填写MA长度*/
            pBuff[maLenIndex] = (UINT8_S)(tempDataIndex - maLenIndex);

            /*设置下标*/
            (*dataIndex) = tempDataIndex;

            rtnValue = RETURN_SUCCESS;
        }
        else
        {
            /*填写MA长度*/
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
* 功能描述： 组输出给单个NZC的列车和移动授权数据
* 参数说明： const UINT16 zcId,ZC的ID(预留)
*            UINT8_S pBuff[],缓存数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： RETURN_ERROR,处理失败
*            RETURN_SUCCESS,处理成功       
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
        /*获取下标*/
        tempDataIndex = (*dataIndex);

        /*预留列车数量字段*/
        trainNumIndex = tempDataIndex;
        tempDataIndex += 1U;

        trainCurNum = GetTrainCurSum();

        if (SIZE_MAX_LINE_TRAIN != trainCurNum)
        {
            /*遍历所有列车*/
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
                            /*计算列车数量*/
                            changeTrainNum += 1U;

                            /*填写列车ID*/
                            ShortToChar(trainId,&pBuff[tempDataIndex]);
                            tempDataIndex += 2U;
                            /*信息帧类型*/
                            pBuff[tempDataIndex] = trainHandOutType;
                            tempDataIndex += 1U;

                            if ((NZC_TRAIN_HANDOVER == trainHandOutType) || (NZC_TRAIN_MANAGENOHAND == trainHandOutType)
                                || (NZC_TRAIN_MANAGENOTAKE == trainHandOutType) || (NZC_TRAIN_HADTOOKOVER == trainHandOutType) )
                            {
                                /*填写列车存在标志*/
                                pBuff[tempDataIndex] = FLAG_SET;
                                tempDataIndex += 1U;

                                /*调用列车信息组包函数*/
                                NextZcTrainMsgPack(trainId,pBuff,&tempDataIndex);

                                /*无需调用MA信息组包，MA不存在*/
                                pBuff[tempDataIndex] = FLAG_UNSET;
                                tempDataIndex += 1U;
                            }
                            else
                            {
                                /*填写列车存在标志*/
                                pBuff[tempDataIndex] = FLAG_UNSET;
                                tempDataIndex += 1U;

                                /*填写MA信息存在标志*/
                                pBuff[tempDataIndex] = FLAG_SET;
                                tempDataIndex += 1U;

                                /*填写MA长度*/
                                maType = GetMaType(trainId);
                                switch (maType)
                                {
                                case NO_MA_TYPE:
                                case ABNORMAL_MA_TYPE:
                                    /*填写MA信息类型*/
                                    pBuff[tempDataIndex] = maType;
                                    tempDataIndex += 1U;

                                    /*填写MA长度为0，结束*/
                                    pBuff[tempDataIndex] = 0U;
                                    tempDataIndex += 1U;
                                    break;

                                case NORMAL_MA_TYPE:
                                    /*填写MA信息类型*/
                                    pBuff[tempDataIndex] = maType;
                                    tempDataIndex += 1U;

                                    /*调用MA信息组包函数*/
                                    NextZcMaMsgPack(trainId,pBuff,&tempDataIndex);
                                    break;

                                default:
                                    /*填写MA信息类型*/
                                    pBuff[tempDataIndex] = ABNORMAL_MA_TYPE;
                                    tempDataIndex += 1U;

                                    /*填写MA长度为0，结束*/
                                    pBuff[tempDataIndex] = 0U;
                                    tempDataIndex += 1U;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            /*列车处于非切换相关状态,不作处理*/
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
            /*填写列车数量*/
            pBuff[trainNumIndex] = changeTrainNum;

            /*获取下标*/
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
* 功能描述： 组输出给Ntp的数据
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
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
        /*组织Ntp输出数据*/
        /*判断是否需要周期校时*/
        if (ZC_INIT_NTP_TIME_SUCC_FLAG_UNSET == GetNtpTimeSuccFlag())
        {
            /*需要发送校时申请*/
            NtpOutputDataPack(commTargetIdBuff[DEFAULT_ZERO]);
        } 
        else
        {
            commCycle = GetCommTargetCycle(INNER_DEVTYPE_NTP,commTargetIdBuff[DEFAULT_ZERO]);

            if ((DEFAULT_ZERO == (commCycle % GetSendNtpApplyCycle()))
                && (DEFAULT_ZERO != commCycle))
            {
                /*需要发送校时申请*/
                NtpOutputDataPack(commTargetIdBuff[DEFAULT_ZERO]);
            } 
            else
            {
                /*不处理*/
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
* 功能描述： 组帧给Ntp的数据
* 参数说明： const UINT16 commId，ID信息
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
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

    /*获取数据*/
    localTime = GetLocalNtpTime();
    ntpTimeZoneDiff = GetNtpTimeZoneDiff();
    ntpApplyOfLocalTime = GetNtpApplyOfLocalTime();

    originateTimestamp = (UINT32_S)((localTime- (3600U * ntpTimeZoneDiff)) + ((UINT32_S)(TIME_DIFF_1970)));
    SetNtpApplyOfLocalTime(originateTimestamp);

    tempNtpTimeStru.Integer = originateTimestamp;
    SetTransmitTimestamp(tempNtpTimeStru);

    /*先设置校时模式为27*/
    SetWorkMode(27U);

    /*填写信息*/
    dataBuff[dataIndex] = GetWorkMode();
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = GetStratum();
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    /*填写NTP校时本地到主时钟源的往返时间*/
    LongToChar(DEFAULT_ZERO,&dataBuff[dataIndex]);
    dataIndex = dataIndex + 4U;

    /*填写NTP校时系统时钟相对于主参考时钟的最大误差*/
    LongToChar(DEFAULT_ZERO,&dataBuff[dataIndex]);
    dataIndex = dataIndex + 4U;

    /*填写NTP校时参考时钟源的标识*/
    dataBuff[dataIndex] = (UINT8_S)DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = (UINT8_S)DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = (UINT8_S)DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    dataBuff[dataIndex] = (UINT8_S)DEFAULT_ZERO;
    dataIndex = dataIndex + 1U;

    /*系统时钟最后一次被设定或更新的时间*/
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

    /*服务器收到的请求报文离开本地的本地时间*/
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

    /*请求报文到达服务器的服务器时间*/
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

    /*应答报文离开服务器的服务器时间*/
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

    /*填写信息*/
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
* 功能描述： 组输出给车载ATP的数据
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
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

    /*获取通信对象数量*/
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
                /*列车输出类型不为零*/
                switch (GetMaType(trainId))
                {
                case NORMAL_MA_TYPE:
                    /*正常移动授权组织*/
                    NormalMaOutputProcess(trainId,trainOutType);

                    break;
                case ABNORMAL_MA_TYPE:
                    /*紧急制动移动授权组织*/
                    AbnormalMaOutputProcess(trainId);

                    break;
                case 0:
                    /*不处理*/
                    break;
                default:
                    break;
                }
            } 
            else
            {
                /*列车输出类型为零,不输出*/
            }
        } 
        else
        {
            /*说明列车信息已删除,MA信息还存在,发送MA信息*/
            switch (GetMaType(trainId))
            {
            case ABNORMAL_MA_TYPE:
                /*紧急制动移动授权组织*/
                AbnormalMaOutputProcess(trainId);
                break;
            case CANCELLATION_MA_TYPE:
                /*注销的移动授权为车头车尾,按正常输出一周期,因为列车结构体已经删除,故需要传入一个常量*/
                LogPrintf(1U,"trainOutType=%d,end=%d\n",GetTrainOutType(trainId),GetMaEndAttribute(trainId));
                if (MA_END_ATT_CBTC == GetMaEndAttribute(trainId))
                {
                    /* 折返时导致的注销状态下,发送退出CBTC申请确认 */
                    NormalMaOutputProcess(trainId,OUT_TRAIN_TOEXITCBTC);
                } 
                else
                {
                    /* 切换时导致的注销状态下,发注销申请确认 */
                    NormalMaOutputProcess(trainId,OUT_TRAIN_HANDOVERTOCANCEL);
                }

                break;
            default:
                break;
            }
            LogPrintf(1U,"25.001 TrainId=%d,%d,MaType=%d\n",trainId,GetTrainOutType(trainId),GetMaType(trainId));

            /*记录需要清除MA信息的列车Id*/
            needDeleteMaIdBuff[needDeleteMaNum] = trainId;
            needDeleteMaNum = needDeleteMaNum + 1U;	
        }
    }

    for (cycle = DEFAULT_ZERO;cycle < needDeleteMaNum;cycle++)
    {
        /*删除该列车的MA信息*/
        DeleteSingleTrainMaInfo(needDeleteMaIdBuff[cycle]);
    }

    return rtnValue;
}

/*
* 功能描述： 正常移动授权输出组织
* 参数说明： const UINT16 trainId ,列车的ID
*            const UINT8_S trainOutType,列车输出类型
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
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

    /*初始化*/
    MemorySet(obsOfMAStru,((UINT32_S)(sizeof(ObsOfMAStruct)*MA_AREA_OBS_SUM_MAX)),
        DEFAULT_ZERO,((UINT32_S)(sizeof(ObsOfMAStruct)*MA_AREA_OBS_SUM_MAX)));
    MemorySet(tsrOfMAStru,((UINT32_S)(sizeof(TsrOfMAStruct)*MA_AREA_TSR_SUM_MAX)),
        DEFAULT_ZERO,((UINT32_S)(sizeof(TsrOfMAStruct)*MA_AREA_TSR_SUM_MAX)));
    MemorySet(&dataBuff[0],((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)),0U,((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)));

    if (DEFAULT_ZERO != trainId)
    {
        /*填写统一信息*/
        UnifiedMaOutputInfoProcess(trainId,trainOutType,&addIndex,dataBuff);

        /*缓存Ma长度*/
        maLenIndex = addIndex;
        addIndex++;

        /*填写移动授权终点属性*/
        dataBuff[addIndex] = GetMaEndAttribute(trainId);
        addIndex = addIndex + 1U;

        /*填写MA起点link*/
        pTempBuf = &dataBuff[addIndex];
        ShortToChar(GetMaHeadLink(trainId),pTempBuf);
        addIndex = addIndex + 2U;

        /* LogPrintf(1U,"22.001 TrainId=%d,Ma Info:%d,%d;%d,%d,EndType=%d\n",trainId,GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId),GetMaEndAttribute(trainId)); */

        /*填写MA起点offset*/
        pTempBuf = &dataBuff[addIndex];
        LongToChar(GetMaHeadOffset(trainId),pTempBuf);
        addIndex = addIndex + 4U;

        /*填写MA起点方向*/
        dataBuff[addIndex] = GetMaHeadDir(trainId);
        addIndex = addIndex + 1U;

        /*填写MA终点link*/
        pTempBuf = &dataBuff[addIndex];
        ShortToChar(GetMaTailLink(trainId),pTempBuf);
        addIndex = addIndex + 2U;

        /*填写MA终点offset*/
        pTempBuf = &dataBuff[addIndex];
        LongToChar(GetMaTailOffset(trainId),pTempBuf);
        addIndex = addIndex + 4U;

        /*填写MA终点方向*/
        dataBuff[addIndex] = GetMaTailDir(trainId);
        addIndex = addIndex + 1U;

        /*填写MA范围内的障碍物数量*/
        tempNum = GetMaObsNum(trainId);
        dataBuff[addIndex] = tempNum;
        addIndex = addIndex + 1U;

        if (RETURN_SUCCESS == GetObsOfMAStru(trainId,MA_AREA_OBS_SUM_MAX,obsOfMAStru))
        {
            for (cycle = DEFAULT_ZERO;cycle < tempNum;cycle++)
            {
                /*填写障碍物信息*/
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
            /* 暂不处理 */
        }

        /*填写MA范围内的临时限速数量*/
        tempNum = GetMaTsrNum(trainId);
        dataBuff[addIndex] = tempNum;
        addIndex = addIndex + 1U;

        if (RETURN_SUCCESS == GetTsrOfMAStru(trainId,MA_AREA_TSR_SUM_MAX,tsrOfMAStru))
        {
            for (cycle = DEFAULT_ZERO;cycle < tempNum;cycle++)
            {
                /*填写临时限速信息*/
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
            /* 暂不处理 */
        }

        /*填写ma长度*/
        dataBuff[maLenIndex] =(UINT8_S) ((addIndex - maLenIndex) - 1U);

        addIndex = addIndex + 4U;


        /*预留20个字节的保留位*/
        addIndex = (UINT16_S)(addIndex + 20U);

        /*输出数据*/
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
* 功能描述：紧急制动移动授权输出组织
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
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
        /*填写统一信息*/
        trainOutType = GetTrainOutType(trainId);
        UnifiedMaOutputInfoProcess(trainId,trainOutType,&addIndex,dataBuff);

        /*将MA信息帧长度设置为空*/
        dataBuff[addIndex] = DEFAULT_ZERO;
        addIndex = addIndex + 1U;

        /*填写ZC状态信息*/
        pTempBuf = &dataBuff[addIndex];
        LongToChar(DEFAULT_UINT32_VALUE,pTempBuf);
        addIndex = addIndex + 4U;

        /*预留20个字节的保留位*/
        addIndex = addIndex + 20U;

        LogPrintf(1U,"22.002 TrainId=%d,Error Ma Info:%d,%d;%d,%d,EndType=%d\n",trainId,GetMaHeadLink(trainId),GetMaHeadOffset(trainId),GetMaTailLink(trainId),GetMaTailOffset(trainId),GetMaEndAttribute(trainId));

        /*输出数据*/
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
* 功能描述：统一的移动授权输出信息组织
* 参数说明： const UINT16 trainId,列车ID
*            const UINT8_S trainOutType,列车输出类型
*            UINT16_S * addIndex,缓存下标
*            UINT8_S dataBuff[],缓存数组
* 返回值  ： 无      
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

        /*填写源信息*/
        dataBuff[index] = (UINT8_S)INNER_DEVTYPE_ZC;
        index = index + 1U;

        dataBuff[index] = (UINT8_S)GetLocalZcId();
        index = index + 1U;

        /*填写目标信息*/
        dataBuff[index] = (UINT8_S)INNER_DEVTYPE_TRAIN;
        index = index + 1U;

        dataBuff[index] = (UINT8_S)trainId;
        index = index + 1U;

        /*填写移动授权输出类型*/
        /*dataBuff[index] = GetTrainOutType(trainId);*/
        dataBuff[index] = trainOutType;
        index = index + 1U;

        /*调试,先跳过4个字节CRC32*/
        /* index = index + 4U; */

        /*填写ZC和ATP比较的数据版本号信息*/
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
            /* 跳过不填写 */
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

        /*填写无人折返按钮ID*/
        pTempBuf = &dataBuff[index];
        ShortToChar(drButtonId,pTempBuf);
        index = index + 2U;

        /*填写无人折返按钮状态*/
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

        /*填写下一个登录ZCid*/
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

        /*输出数组下标*/
        (*addIndex) = index;
    } 
    else
    {
        /* 不处理 */
    }

}

/*
* 功能描述： 组输出给Ats的数据
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
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
		/*-bye- 按照《ZC-ATS接口说明书》修改代码*/
		bufIndex += 2u;/*跳过报文总长度2字节，后面填写*/

		msgType = 0x0065U;
		ShortToChar(msgType, &dataBuff[bufIndex]);/*报文类型*/
		bufIndex += 2U;
			
		ShortToChar(reserve, &dataBuff[bufIndex]);/*预留*/
		bufIndex += 2U;

		ShortToChar(msgType, &dataBuff[bufIndex]);/*报文类型*/
		bufIndex += 2U;

        dataBuff[bufIndex] = (UINT8_S)GetLocalZcId();
        bufIndex += 1U;

        AllTrainNumIndex = bufIndex;/*跳过列车个数1字节，后面填写*/
        bufIndex += 1U;

        /*组CBTC列车信息*/
        AllTrainNum = SectionOccFromCbtcTrain(&bufIndex,dataBuff);

        /*组非CBTC列车信息*/
        AllTrainNum += SectionOccFromUnCbtcTrain(&bufIndex,dataBuff);

        /*填写列车数量*/
        dataBuff[AllTrainNumIndex] = (UINT8_S)AllTrainNum;

		/*报文总长度*/
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
* 功能描述： CBTC列车占用逻辑区段组帧
* 参数说明： UINT16 *addIndex,数组大小;
*            UINT8_S dataBuff[],输出数组;
* 返回值  ： 0>=:列车数量     
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
    UINT16_S safeHeadLink = DEFAULT_ZERO;  /* 安全车头所处Link */
    UINT32_S safeHeadOffset = DEFAULT_ZERO;  /* 安全车头所处偏移量 */
    UINT16_S safeTailLink = DEFAULT_ZERO;  /* 安全车尾所处Link */
    UINT32_S safeTailOffset = DEFAULT_ZERO;  /* 安全车尾所处偏移量 */
    UINT8_S acNum = 0U;
    UINT16_S acBuff[ZC_TWO_POINT_AC_NUM_MAX] = {0U};
    UINT8_S i = DEFAULT_ZERO;
    UINT16_S tmpStartLink = DEFAULT_ZERO;  /* 安全车头所处Link */
    UINT32_S tmpStartOffset = DEFAULT_ZERO;  /* 安全车头所处偏移量 */
    UINT16_S tmpEndLink = DEFAULT_ZERO;  /* 安全车尾所处Link */
    UINT32_S tmpEndOffset = DEFAULT_ZERO;  /* 安全车尾所处偏移量 */
    UINT8_S  rtnLogicIdNum = DEFAULT_ZERO;   /*计算逻辑区段函数返回值 */
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

        /*填写列车信息*/
        for (cycle = 0U;cycle < GetTrainCurSum();cycle++)
        {
#if 1
            /*获取列车信息*/
            trainId = GetTrainIdOfIndex(cycle);
            trainType = GetTrainType(trainId);	
            unsafeTrainHeadAC = GetTrainUnsafeTrainHeadAC(trainId);
            unsafeTrainTailAC = GetTrainUnsafeTrainTailAC(trainId);
            headAcInZcId = GetAcBelongZcId(unsafeTrainHeadAC);
            tailAcInZcId = GetAcBelongZcId(unsafeTrainTailAC);

            if (((TRAIN_MODE_CBTC == trainType) || (TRAIN_MODE_TO_RM0 == trainType))
                && ((localZcId == headAcInZcId ) || (localZcId == tailAcInZcId)))
            {
                /*列车位于本ZC管辖范围内的计轴区段*/
                MemorySet(&trainSafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),
                    0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));
                trainSectionNum = 0u;

                /* 获取列车的方向和位置信息 */
                trainDir = GetTrainUnsafeDirection(trainId);

                /*获取列车安全位置信息*/
                if (RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
                {
                    safeHeadLink = trainSafeLocStru.TrainHeadLink ;
                    safeHeadOffset = trainSafeLocStru.TrainHeadOffset;
                    safeTailLink = trainSafeLocStru.TrainTailLink;
                    safeTailOffset = trainSafeLocStru.TrainTailOffset;

                    LogPrintf(1u,"Crash-U[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,safeHeadLink,safeHeadOffset,safeTailLink,safeTailOffset);
                    if (safeHeadLink == safeTailLink)
                    {
                        /*查询列车占压的逻辑区段*/
                        trainSectionNum = CheckLogicIdBetweenPoints(3U,safeTailLink,safeTailOffset,
                            safeHeadLink,safeHeadOffset,trainDir,trainSectionOfAcBuff);
                        LogPrintf(1u,"Crash-V[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,safeHeadLink,safeHeadOffset,safeTailLink,safeTailOffset);

                    }
                    else
                    {                    
                        /* 查询车尾到车头的占压的计轴区段 */
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

                    /* 过滤 */
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
                        /*填写列车ID*/
                        dataBuff[tempIndex] = (UINT8_S)trainId;
                        tempIndex = tempIndex + 1U;

                        /*填写列车类型*/
                        dataBuff[tempIndex] = (UINT8_S)TO_ATS_LOGIC_SECTION_CT_OCC;
                        tempIndex = tempIndex + 1U;

                        /*填写占压逻辑区段个数*/
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
                        /* 逻辑区段数量不对,不处理 */
                    }
                } 
                else
                {
                    /* 获取列车位置失败,不处理 */
                }              
            } 
            else
            {
                /* 列车类型不符合要求或者列车位置不在本ZC,不处理 */
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
                /*填写列车ID*/
                dataBuff[tempIndex] = (UINT8_S)trainId;
                tempIndex = tempIndex + 1U;

                /*填写列车类型*/
                dataBuff[tempIndex] = (UINT8_S)TO_ATS_LOGIC_SECTION_CT_OCC;
                tempIndex = tempIndex + 1U;

                /*填写占压逻辑区段个数*/
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
                /* 逻辑区段数量不对,不处理 */
            }
#endif


        }

        /*输出下标*/
        (*addIndex) = tempIndex;

    } 
    else
    {
        /* 不处理 */
    }

    return cbtcTrainNum;
}

/*
* 功能描述： 非CBTC列车占用逻辑区段组帧
* 参数说明： UINT16 *addIndex,数组大小;
*            UINT8_S dataBuff[],输出数组;
* 返回值  ： 0>=:列车数量     
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
                /*属于本ZC*/
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
                            /*不处理*/
                        }
                    }

                    if (FLAG_SET == utOccFlag)
                    {
                        /*填写列车ID*/
                        dataBuff[tempIndex] = (UINT8_S)DEFAULT_ZERO;
                        tempIndex = tempIndex + 1U;

                        /*填写列车类型*/
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

                        /*填写数量*/
                        dataBuff[occLogicSectionNumIndex] = occLogicSectionNum;

                        unCbtcTrainNum++;
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
            } 
            else
            {
                /*不处理*/
            }
        }

        /*输出下标*/
        (*addIndex) = tempIndex;
    } 
    else
    {
        /*不处理*/
    }

    return unCbtcTrainNum;
}

/*
* 功能描述： 计算CBTC列车占用逻辑区段
* 参数说明： const UINT16_S trainId,列车ID
*          UINT16_S *pLogicNum,输出占用的逻辑区段数量
*          UINT16_S trainSectionOfAcBuff[],输出占用的逻辑区段数组
* 返回值  ： 1u,成功
*          0u,失败
*/
static UINT8_S CalcCtTrainOccLogicSecBuff(const UINT16_S trainId,UINT16_S *pLogicNum,UINT16_S trainSectionOfAcBuff[])
{
    UINT8_S rtn = RETURN_ERROR;
    TrainSafeLocStruct trainSafeLocStru;
    UINT16_S safeHeadLink = DEFAULT_ZERO;  /* 安全车头所处Link */
    UINT32_S safeHeadOffset = DEFAULT_ZERO;  /* 安全车头所处偏移量 */
    UINT16_S safeTailLink = DEFAULT_ZERO;  /* 安全车尾所处Link */
    UINT32_S safeTailOffset = DEFAULT_ZERO;  /* 安全车尾所处偏移量 */
    UINT8_S acNum = 0U;
    UINT16_S acBuff[ZC_TWO_POINT_AC_NUM_MAX] = {0U};
    UINT8_S i = DEFAULT_ZERO;
    UINT16_S tmpStartLink = DEFAULT_ZERO;  /* 安全车头所处Link */
    UINT32_S tmpStartOffset = DEFAULT_ZERO;  /* 安全车头所处偏移量 */
    UINT16_S tmpEndLink = DEFAULT_ZERO;  /* 安全车尾所处Link */
    UINT32_S tmpEndOffset = DEFAULT_ZERO;  /* 安全车尾所处偏移量 */
    UINT8_S j = DEFAULT_ZERO;
    UINT8_S trainSectionNum = DEFAULT_ZERO;
    UINT8_S trainDir = DEFAULT_ZERO;
    UINT16_S trainHeadAc = DEFAULT_ZERO;
    UINT16_S trainTailAc = DEFAULT_ZERO;
    UINT8_S acSwitchNum = DEFAULT_ZERO;
    UINT8_S  rtnLogicIdNum = DEFAULT_ZERO;   /*计算逻辑区段函数返回值 */
    UINT16_S sectionBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};

    MemorySet(&sectionBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)),
        0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)));
    MemorySet(&trainSafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),
        0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));

    if ((RETURN_SUCCESS == GetTrainSafeLoc(trainId,&trainSafeLocStru))
        && (NULL != pLogicNum) && (NULL != trainSectionOfAcBuff))
    {     
        (*pLogicNum)=0u;

        /* 获取列车的方向和位置信息 */
        trainDir = GetTrainUnsafeDirection(trainId);
        trainHeadAc = GetTrainTrainHeadAC(trainId);
        trainTailAc = GetTrainTrainTailAC(trainId);

        safeHeadLink = trainSafeLocStru.TrainHeadLink ;
        safeHeadOffset = trainSafeLocStru.TrainHeadOffset;
        safeTailLink = trainSafeLocStru.TrainTailLink;
        safeTailOffset = trainSafeLocStru.TrainTailOffset;

        if (trainHeadAc == trainTailAc)
        {
            /*查询列车占压的逻辑区段*/
            trainSectionNum = CheckLogicIdBetweenPoints(3U,safeTailLink,safeTailOffset,
                safeHeadLink,safeHeadOffset,trainDir,sectionBuff);

            LogPrintf(1u,"Crash-V[%d],%d,%d,%d-%d,%d-%d\n",trainId,rtnLogicIdNum,trainSectionNum,safeTailLink,safeTailOffset,safeHeadLink,safeTailOffset);
        }
        else
        {                    
            /* 查询车尾到车头的占压的计轴区段 */
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

        /* 过滤不符合条件的逻辑区段 */
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
* 功能描述： 处理输入给CI的进路停车保证确认码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[SINGLE_MASK_DEVICE_SUM_MAX],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
static UINT8_S ProcessRouteStopConfirmMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (1U == deviceSum)
    {
        /*获取信号机亮灭状态*/		
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
        /*错误*/
        rtnValue = 0U;
    }

    return rtnValue;
}