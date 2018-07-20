/************************************************************************
*
* 文件名   ：  ParsePackZcData.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  解析和组包相邻ZC数据管理  
* 备  注	：  无
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

ZcAndNzcIODataStruct gToNZcDataStruBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX];     /*zc给车载ATP的数据结构*/
UINT16_S gToNZcDataIdBuff[COMM_TARGET_ID_MAX] = {COMM_TARGET_ID_MAX};        /*ID索引数组*/
UINT8_S  gToNZcCurSum = 0U;                                                  /*ZC输出相邻ZC的最大数量*/

ZcAndNzcIODataStruct gNZcInDataStruBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX];     /*相邻ZC输入的数据结构*/
UINT16_S gNZcInDataIdBuff[COMM_TARGET_ID_MAX] = {COMM_TARGET_ID_MAX};        /*ID索引数组*/
UINT8_S  gNZcInCurSum = 0U;                                                  /*相邻ZC输入的最大数量*/

/*
* 功能描述： 获取相邻ZC输入Zc的最大数量
* 参数说明： void
* 返回值  ：  SINGLE_TYPE_COMM_TARGET_SUM_MAX: 失败
*			>0: 数量      
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
* 功能描述：获取相邻ZC输入的数据数组下标对应的ZCID
* 参数说明： const UINT8 nZcIdOfIndex
* 返回值  ： 0: 失败
*			 >0: 成功      
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
* 功能描述：获取相邻ZC输入的数据数组下标对应的数据长度
* 参数说明： const UINT8 nZcIdOfIndex
* 返回值  ： 0: 失败
*			 >0: 成功      
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
* 功能描述： 获取NZc输入Zc的Id对应数据信息
* 参数说明： const UINT8 nZcIdOfIndex
* 返回值  ： NULL: 失败
*			 !NULL: 成功       
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
* 功能描述： 解析NZC输入的单帧数据
* 参数说明： const UINT8_S dataBuff[], 数据缓冲区
*            const UINT16_S dataLength, 数据长度
* 返回值  ： 0: 数据解析失败
*			 1: 数据解析成功      
*/
UINT8_S ParseNzcToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength)
{
    UINT8_S sourceId = DEFAULT_ZERO;
    UINT8_S tempRtn = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S copyRtn = DEFAULT_ZERO;

    if ((dataBuff != NULL) && (dataLength > 0U))
    {
        /*解析帧头,判断是否为本ZC通信的ZC*/
        sourceId = dataBuff[1];

        tempRtn = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,((UINT16_S)sourceId));

        if (RETURN_SUCCESS == tempRtn)
        {
            /*获取通信数据*/
            /*判断输入数据是否合法*/

            if (RETURN_SUCCESS == NzcInputDataValidityCheck(dataBuff,dataLength))
            {
                /* 待接口确定后写入数据 */
                /*填写源Id*/
                gNZcInDataStruBuff[gNZcInCurSum].ZcId = sourceId;

                /*获取数据长度*/
                gNZcInDataStruBuff[gNZcInCurSum].ValueBuffLen = dataLength - 4U;

                /*PBW + ZYW:add*/
                copyRtn = MemoryCpy(gNZcInDataStruBuff[gNZcInCurSum].ValueBuff,((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)),&dataBuff[4],((UINT32_S)(gNZcInDataStruBuff[gNZcInCurSum].ValueBuffLen)));

                if (0U == copyRtn)
                {
                    gNZcInDataIdBuff[sourceId] = gNZcInCurSum;

                    gNZcInCurSum++;

                    /*属于本ZC通信, 更新通信状态*/
                    SetCommTargetStatus(INNER_DEVTYPE_ZC,((UINT16_S)sourceId),COMM_STATUS_NORMAL);
                    SetCommTargetCycle(INNER_DEVTYPE_ZC,((UINT16_S)sourceId),DEFAULT_ZERO);

                    /*LogPrintf(1U,"29.202 NZc=%d,In!Sum=%d\n",sourceId,gNZcInCurSum);*/

                    /*数据无效*/
                    rtnValue = RETURN_SUCCESS;
                } 
                else
                {
                    gNZcInDataIdBuff[sourceId] = SINGLE_TYPE_COMM_TARGET_SUM_MAX;
                    gNZcInDataStruBuff[gNZcInCurSum].ValueBuffLen = DEFAULT_ZERO;
                    gNZcInDataStruBuff[gNZcInCurSum].ZcId = DEFAULT_ZERO;

                    LogPrintf(1U,"29.203 NextZc=%d,Input!gNZcInCurSum=%d,copyRtn=%d\n",sourceId,gNZcInCurSum,copyRtn);

                    /*数据无效*/
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
            /*数据无效*/
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
* 功能描述： 相邻ZC输入的单帧数据合法性检查
* 参数说明： const UINT8_S dataBuff[], 数据缓冲区
*            const UINT16_S dataLen, 数据长度
* 返回值  ： 0: 合法性检查失败
*			 1: 合法性检查成功      
*/
UINT8_S NzcInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen)
{
    UINT8_S rtnValue = 0U;
    UINT16_S checkErrorFlag = DEFAULT_ZERO;

    /* 此函数为预留内容 主要是在通讯对象校验之后的帧内容校验 */
    if ((NULL != dataBuff) && (0U < dataLen))
    {
        if ((INNER_DEVTYPE_ZC == dataBuff[0]) && ((INNER_DEVTYPE_ZC == dataBuff[2])) && (dataBuff[1] != dataBuff[3]))
        {
            /* 类型相同且ID不同 */
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
* 功能描述： 获取ZC输出给NZc的最大数量
* 参数说明： void
* 返回值  ： SINGLE_TYPE_COMM_TARGET_SUM_MAX: 失败
*			>0: 数量      
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
* 功能描述：获取输出给相邻ZC数据数组下标对应的数据长度
* 参数说明： const UINT8 nZcIdOfIndex
* 返回值  ： 0: 失败
*			 >0: 成功      
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
* 功能描述： 获取输出给相邻ZC数据数组下标对应的数据信息
* 参数说明： const UINT8 nZcIdOfIndex
* 返回值  ： NULL: 失败
*			 !NULL: 成功      
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
* 功能描述： 组相邻ZC数据
* 参数说明： const UINT8* dataBuf,数据缓存
*            const UINT16_S dataLength,数据长度
*            const UINT16_S destId, 目标ID   
* 返回值  ： RETURN_ERROR:组数据失败
*			 RETURN_SUCCESS:组数据成功      
*/
UINT8_S PackZcToNzcFrameData(const UINT8_S* dataBuf,const UINT16_S dataLength,const UINT16_S destId)
{
    UINT16_S index = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S copyRtn = 1U;

    if ((dataBuf != NULL) && (dataLength > 0U))
    {
        /*填写码位信息并组帧头*/
        if (SINGLE_TYPE_COMM_TARGET_SUM_MAX <= gToNZcCurSum)
        {            
            /*数据无效*/
            rtnValue = RETURN_ERROR;
        } 
        else
        {           
            gToNZcDataStruBuff[gToNZcCurSum].ZcId = (UINT8_S)(destId);

            /*建立索引*/
            gToNZcDataIdBuff[destId] = gToNZcCurSum;

            /*填写信息帧头信息*/
            /*填写源设备*/
            gToNZcDataStruBuff[gToNZcCurSum].ValueBuff[index] = INNER_DEVTYPE_ZC;
            index = index + 1U;

            gToNZcDataStruBuff[gToNZcCurSum].ValueBuff[index] = (UINT8_S)GetLocalZcId();
            index = index + 1U;

            /*填写目标设备*/
            gToNZcDataStruBuff[gToNZcCurSum].ValueBuff[index] = INNER_DEVTYPE_ZC;
            index = index + 1U;

            gToNZcDataStruBuff[gToNZcCurSum].ValueBuff[index] = (UINT8_S)destId;
            index = index + 1U;

            /*复制数据*/
            /*PBW,2016.5.24,相邻ZC的数据使用4个字节的帧头*/
            copyRtn = MemoryCpy(&gToNZcDataStruBuff[gToNZcCurSum].ValueBuff[index],((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX - (UINT32_S)index)),dataBuf,((UINT32_S)dataLength));

            if (1U == copyRtn)
            {
                /*清空信息*/
                gToNZcDataStruBuff[gToNZcCurSum].ZcId = 0U;		
                gToNZcDataIdBuff[destId] = SINGLE_TYPE_COMM_TARGET_SUM_MAX;
                gToNZcDataStruBuff[gToNZcCurSum].ValueBuffLen = DEFAULT_ZERO;

                rtnValue = RETURN_ERROR;
            } 
            else
            {
                /*增加数量*/
                gToNZcDataStruBuff[gToNZcCurSum].ValueBuffLen = index + dataLength;
                gToNZcCurSum++;
                rtnValue = RETURN_SUCCESS;
            }
        }
    }
    else
    {
        /*数据无效*/
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* 功能描述： 清空本周期所有相邻ZC输入信息
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearCycleNZcInputData(void)
{
    UINT8_S cycle = DEFAULT_ZERO;

    /*清空数据*/
    for (cycle = DEFAULT_ZERO;cycle < SINGLE_TYPE_COMM_TARGET_SUM_MAX;cycle++)
    {
        MemorySet(&gNZcInDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndNzcIODataStruct))),
            DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndNzcIODataStruct))));
    }

    /*清空输入数量*/
    gNZcInCurSum  = 0U;

    /*清空管理数组*/
    for (cycle = DEFAULT_ZERO;cycle < COMM_TARGET_ID_MAX;cycle++)
    {
        gNZcInDataIdBuff[cycle] = COMM_TARGET_ID_MAX;
    }
}

/*
* 功能描述： 清空本周期所有相邻ZC输出信息
* 参数说明： 无
* 返回值  ： 无      
*/
void ClearCycleNZcOutputData(void)
{
    UINT8_S cycle = DEFAULT_ZERO;

    /*清空数据*/
    for (cycle = DEFAULT_ZERO;cycle < SINGLE_TYPE_COMM_TARGET_SUM_MAX;cycle++)
    {
        MemorySet(&gToNZcDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndNzcIODataStruct))),
            DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndNzcIODataStruct))));
    }

    /*清空输出数量*/
    gToNZcCurSum  = 0U;

    /*清空管理数组*/
    for (cycle = DEFAULT_ZERO;cycle < COMM_TARGET_ID_MAX;cycle++)
    {
        gToNZcDataIdBuff[cycle] = COMM_TARGET_ID_MAX;
    }
}
