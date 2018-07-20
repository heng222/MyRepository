/************************************************************************
*
* 文件名   ：  CommTargetStatusData.c
* 作者     ：  ZC组
* 创建时间 ：  2015.07.14
* 功能描述 ：  通讯对象状态 
* 备  注   ：  无
*
************************************************************************/

#include "CommTargetConfigData.h"
#include "CommTargetStatusData.h"
#include "../../SysDataManager/SysConfigData.h"

CommTargetDataStruct gCommTargetDataStruBuff[COMM_TYPE_SUM_MAX];               /*定义通信对象状态信息（除列车外的其他系统）*/

SingleCommTargeStruct gCommTrainDataStruBuff[COMM_TRAIN_ID_MAX];               /*通信列车状态信息*/

/*
* 功能描述： 获取通信对象信息
* 参数说明： void    
* 返回值  ： 0: 获取数据失败
*			>0: 获取通信对象信息
*/
CommTargetDataStruct* GetCommTargetStatusData(void)
{
    return gCommTargetDataStruBuff;
}

/*
* 功能描述： 获取通信对象Id对应的下标
* 参数说明： const UINT8 commTargetType 类型
const UINT16_S commTargetId  ID
* 返回值  ： 0: 获取数据失败
*			>0: 对象Id对应的下标
*/
UINT8_S GetOtherCommTargetIdBuffIndex(const UINT8_S commTargetType,const UINT16_S commTargetId)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S typeBuffIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();

    if (commTargetType == INNER_DEVTYPE_TRAIN)
    {
        /*不处理列车*/
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
            /*不处理*/
        }
    }

    return rtnValue;
}

/*
* 功能描述： 获取某通信对象通信累加信息
* 参数说明： const UINT8 commTargetType 通信对象类型
const UINT16_S commTargetID 通信对象ID    
* 返回值  ： 0xffff: 获取数据失败
*			>=0: 通信累加信息
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
            /*不处理*/
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
            /*不处理*/
        }
        break;
    default:
        break;
    }

    return rtnValue;
}

/*
* 功能描述： 设置某通信对象通信累加信息
* 参数说明： const UINT8 commTargetType 通信对象类型
const UINT16_S commTargetID 通信对象ID  
const UINT16_S commTargetCycle 通信对象累加信息    
* 返回值  ： 0: 设置失败
*			 1: 设置成功
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
* 功能描述： 获取某通信对象状态信息
* 参数说明： const UINT8 commTargetType 通信对象类型
const UINT16_S commTargetID 通信对象ID      
* 返回值  ： 0: 获取数据失败
*			>=0: 状态信息
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
            /*不处理*/
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
            /*不处理*/
        }
        break;
    default:
        break;
    }

    return rtnValue;
}

/*
* 功能描述： 设置某通信对象状态信息
* 参数说明： const UINT8 commTargetType 通信对象类型
const UINT16_S commTargetID 通信对象ID    
const UINT8_S commTargetStatus 通信对象状态信息 
* 返回值  ： 0: 设置失败
*			 1: 设置成功
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
* 功能描述： 获取某通信对象通信对象输入信息时的周期号
* 参数说明： const UINT8 commTargetType 通信对象类型
const UINT16_S commTargetID 通信对象ID     
* 返回值  ：  0: 获取数据失败
*			>=0: 通信对象输入信息时的周期号
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
            /*不处理*/
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
            /*不处理*/
        }
        break;
    default:
        break;
    }

    return rtnValue;
}

/*
* 功能描述： 设置某通信对象周期信息
* 参数说明：const UINT8 commTargetType 通信对象类型
const UINT16_S commTargetID 通信对象ID  
const UINT32_S commTargetCycleNum 通信对象周期信息    
* 返回值  ： 0: 设置失败
*			 1: 设置成功
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
* 功能描述： 清除某个列车的通信及时信息和状态信息
* 参数说明： const UINT16_S trainId,列车ID    
* 返回值  ： 无
*/
void ClearOneTrainCommCycleAndStatus(const UINT16_S trainId)
{
	gCommTrainDataStruBuff[trainId].CommTargetCycle = DEFAULT_ZERO;
	gCommTrainDataStruBuff[trainId].CommTargetStatus = DEFAULT_ZERO;
}