/********************************************************
*                                                                                                            
* 文 件 名： AdptAppExtDevDataInterface.c   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 适配层对应用层通信接口结构处理的接口文件 
* 备    注： 无 
*
********************************************************/ 

#include "AdptAppExtDevDataInterface.h"
#include "../AdptHandle/AdapterExtDevInOutManage.h"
#include "../AppItf/AdptAppCommonDef.h"
#include "../AppItf/AdptAppServiceInterface.h"
#include "../PlatItf/AdptPlatServiceInterface.h"
#include "../../Common/MemSet.h"
#include "../PlatformLog/AdapterLog.h"

/* 设备对应通信协议配置表 */
ComProCfgStruct gComDevProStruct[] =
{
    {DEVTYPE_VOBC, DEVTYPE_ZC, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_CI, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_ATS, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_NTP, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_MAINTAIN, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_ATP, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_ATO, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_DMI, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_RADA, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_BTM, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_NMS, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC,DEVTYPE_TESTPC,COM_WITHOUT_PRO},
    {DEVTYPE_ZC, DEVTYPE_CI, COM_WITHOUT_PRO},
    {DEVTYPE_ZC, DEVTYPE_ATS, COM_WITHOUT_PRO},
    {DEVTYPE_ZC, DEVTYPE_NTP, COM_WITHOUT_PRO},
    {DEVTYPE_ZC, DEVTYPE_DMS, COM_WITHOUT_PRO},
    {DEVTYPE_ZC, DEVTYPE_MAINTAIN, COM_WITHOUT_PRO},
    {DEVTYPE_ZC, DEVTYPE_ZC, COM_WITHOUT_PRO},       /* COM_WITH_RSSP */
    {DEVTYPE_DMS, DEVTYPE_ATS, COM_WITHOUT_PRO},
    {DEVTYPE_DMS, DEVTYPE_NTP, COM_WITHOUT_PRO},
    {DEVTYPE_DMS, DEVTYPE_MAINTAIN, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_TEST, COM_WITHOUT_PRO},
    {DEVTYPE_VOBC, DEVTYPE_RECORD,COM_WITHOUT_PRO},
    {DEVTYPE_ZC, DEVTYPE_RECORD,COM_WITHOUT_PRO},
    {DEVTYPE_DMS, DEVTYPE_RECORD,COM_WITHOUT_PRO}
};

/* 设备对应通信协议配置表的条目 */
static UINT32_S gComDevProCount = sizeof(gComDevProStruct)/sizeof(ComProCfgStruct);


static UINT8_S AdapterSndDataProtocol(UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId);
static UINT32_S AdapterRcvDataProtocol(UINT8_S* pInBuf, const UINT32_S inLen, UINT8_S* pOutBuf, const UINT32_S outMaxLen, UINT8_S devType, UINT8_S devId);

static UINT8_S AdapterGetDevProType(UINT8_S comSrcType, UINT8_S comDstType, UINT8_S * comProType);

/*
* 功能描述：应用发送数据接口 
* 参数说明： 
*              UINT8_S* pDataBuf, 数据缓冲区 
*              UINT32_S dataLen, 数据长度 
*             UINT8_S destDevType 设备类型 
*             UINT8_S destDevId 设备ID 
* 返回值  ： 1: 成功
*            0: 失败
*/
UINT8_S AdptAppExtDevSndData(UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId)
{
    UINT8_S retVal = 0u;

    if ( pDataBuf != NULL )
    {
        retVal = AdapterSndDataProtocol(pDataBuf, dataLen, destDevType, destDevId);
    }

    return retVal;
}

/*
* 功能描述： 协议处理发送数据
* 参数说明： 
*              UINT8_S* pDataBuf, 数据缓冲区
*              UINT32_S dataLen, 数据长度
*             UINT8_S destDevType 设备类型 
*             UINT8_S destDevId 设备ID 
* 返回值  ： 1: 成功
*            0: 失败
*/
static UINT8_S AdapterSndDataProtocol(UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId)
{
    UINT8_S retVal = 0u;
    UINT16_S localName = 0u;
    UINT8_S localType = 0u;
    UINT8_S proType = 0u;
    UINT16_S dstName = 0u;
    UINT8_S proResult = 0u;
    UINT16_S timeDiff = 0u;
    UINT8_S rsspStatus = 0u;
    UINT16_S outTsdLen = 0u;               /*应用帧的长度*/
    UINT8_S outTsdBuf[DEV_TOTAL_FRAME_LEN] = {0u}; /*应用帧*/
    UINT16_S outSseLen = 0u;                /*对时请求帧的长度*/
    UINT8_S outSseBuf[DEV_TOTAL_FRAME_LEN] = {0u};  /*对时请求帧*/
    UINT16_S outSsrLen = 0u;                /*对时应答帧的长度*/
    UINT8_S outSsrBuf[DEV_TOTAL_FRAME_LEN] = {0u};  /*对时应答帧*/

    if (pDataBuf != NULL)
    {

        localName = AdptAppGetLocalName();
        localType = (UINT8_S)((localName>>8u) & 0x00FFu);

        /*初始化局部变量*/
        MemorySet(&outTsdBuf[0u], sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN, 0u, sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN);
        MemorySet(&outSseBuf[0u], sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN, 0u, sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN);
        MemorySet(&outSsrBuf[0u], sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN, 0u, sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN);

        /* 查询通信设备之间是否需要协议 */
        if ( 1 == AdapterGetDevProType(localType, destDevType, &proType) )
        {
            switch (proType)
            {

                case COM_WITHOUT_PRO:

                    AdapterAddDevSndQueData(pDataBuf, dataLen, destDevType, destDevId);
                    retVal = 1u;
                    break;

                case COM_WITH_RSSP:

                    /* 通信设备之间需要协议则进行协议处理 */
                    dstName = (UINT16_S)((destDevType << 8u) + destDevId);

                    AdptAppLogPrintBuff(pDataBuf, DEV_TOTAL_FRAME_LEN, dataLen);

                    proResult = AdptPlatRsspPackData(dstName, (UINT16_S)dataLen, pDataBuf, 
                                               &outTsdLen, &outTsdBuf[0u],
                                               &outSseLen, &outSseBuf[0u],
                                               &outSsrLen, &outSsrBuf[0u]);

                    rsspStatus = AdptPlatRsspGetChaStat(dstName,&timeDiff);

                    AdptAppLogPrintf(1u,"RSSP snd: %x %d %d %d %d %d %d\n", dstName, proResult, rsspStatus,dataLen, outTsdLen,outSseLen,outSsrLen);
                    AdptAppLogPrintBuff(outTsdBuf, DEV_TOTAL_FRAME_LEN, outTsdLen);

                    if(RSSP_PACK_TSD_SSE_SSR == proResult )
                    {
                        /* 存在数据帧和对时帧返回2 */ 

                        AdapterAddDevSndQueData(outTsdBuf, outTsdLen, destDevType, destDevId);

                        AdapterAddDevSndQueData(outSseBuf, outSseLen, destDevType, destDevId);

                        AdapterAddDevSndQueData(outSsrBuf, outSsrLen, destDevType, destDevId);
                    }
                    else if(RSSP_PACK_TSD == proResult )
                    {

                        /* 只存在数据帧, 已打包TSD，返回3 */
                        AdapterAddDevSndQueData(outTsdBuf, outTsdLen, destDevType, destDevId);
                    }
                    else
                    {

                        /*协议打包失败*/
                        AdptAppLogPrintf(1u, "RSSP pack error:%d\n", proResult);
                    }

                    retVal = 1u;
                    break;

                default:
                    /*协议查询失败*/
                    AdptAppLogPrintf(1u, "Protoocl type error:%d\n", proType);
                    retVal = 0u;
                    break;
            }

        }
        else
        {
            /*AdptAppLogPrintf(1,"get protocol type error\n");*/
            retVal = 0u;
        }
    }
    else
    {
        retVal = 0u;
    }
    return retVal;
}


/*
* 功能描述：应用接收数据接口
*   队列中的数据是无序排列的，每一个通信板的每一个通道都有一包数据
*   需要按照不同设备归类，区分出过协议的数据将其通道和两个通信板的数据都整合为一包，不过协议的不能合成一包
*
* 参数说明： 
*              UINT8_S* pDataBuf, 数据缓冲区
*              UINT32_S dataLen, 数据缓冲区长度
*             UINT8_S *pDevType 设备类型 
*             UINT8_S *pDevId 设备ID 
*
* 返回值  ： 
*            >0 且非0xFFFFFFFF:  取数据成功且可以继续取数据 
*            0xFFFFFFFF:  获取了数据但是数据为无效，如协议解析失败可以继续取数据 
*            0: 数据已经全部取出 
*/
UINT32_S AdptAppExtDevRcvData(UINT8_S* pDataBuf, const UINT32_S dataLen, UINT8_S *pDevType, UINT8_S *pDevId)
{
    UINT32_S retLen = 0u;

    UINT8_S tmpBuf[DEV_TOTAL_FRAME_LEN] = {0u};
    UINT32_S tmpLen = 0u;

    UINT8_S outBuf[DEV_TOTAL_FRAME_LEN] = {0u};
    UINT32_S outLen = 0u;

    UINT8_S devType = 0u;
    UINT8_S devId = 0u;

    if ((pDataBuf != NULL) && (pDevType != NULL) && (pDevId != NULL))
    {

        /* 首先获取一帧数据，确认当前处理的设备类型 */
        tmpLen = AdapterGetDevRcvQuePkgData( tmpBuf, DEV_TOTAL_FRAME_LEN, &devType, &devId);

        if (tmpLen > 0u)
        {

            /* 协议处理数据 */
            outLen = AdapterRcvDataProtocol(tmpBuf, tmpLen, outBuf, DEV_TOTAL_FRAME_LEN, devType, devId);

            if (outLen > 0u)
            {
                if (0u == MemoryCpy(pDataBuf, dataLen, outBuf, outLen))
                {
                    retLen = outLen;
                }
                else
                {
                    retLen = RCV_ERROR;
                }
            }
            else
            {
                retLen = RCV_ERROR;
            }
        }
        else
        {
            retLen = 0u;
        }

        *pDevType = devType;
        *pDevId = devId;

    }
    else
    {
        retLen = 0u;
    }

    return retLen;
}

/*
* 功能描述： 协议处理接收数据
*   队列中的数据是无序排列的，每一个通信板的每一个通道都有一包数据
*   需要按照不同设备归类，区分出过协议的数据将其通道和两个通信板的数据都整合为一包，不需要协议的不处理
*
* 参数说明： 
*              char* pDataBuf, 数据缓冲区
*              int dataLen, 数据缓冲区长度
* 返回值  ： 1: 成功
*            0: 失败
*/
static UINT32_S AdapterRcvDataProtocol(UINT8_S* pInBuf, const UINT32_S inLen, UINT8_S* pOutBuf, const UINT32_S outMaxLen, UINT8_S devType, UINT8_S devId)
{
    UINT32_S retLen = 0u;

    UINT8_S tmpBuf[DEV_TOTAL_FRAME_LEN] = {0u};
    UINT32_S tmpLen = 0u;

    UINT8_S totalBuf[DEV_TOTAL_RCV_FRAME_LEN] = {0u};
    UINT32_S totalLen = 0u;

    UINT8_S proType = 0u;
    UINT16_S timeDiff = 0u;
    UINT8_S rsspStatus = 0u;
    UINT8_S proRet = 0u;

    UINT8_S outBuf[DEV_TOTAL_FRAME_LEN] = {0u};
    UINT16_S outLen = 0u;

    UINT16_S localName = 0u;
    UINT8_S localType = 0u;
    UINT16_S dstName = 0u;

    localName = AdptAppGetLocalName();
    localType = (UINT8_S)((localName>>8u) & 0x00FFu);

    totalLen = 0u;
    MemorySet(&totalBuf[0u], DEV_TOTAL_RCV_FRAME_LEN, 0u, DEV_TOTAL_RCV_FRAME_LEN);

    MemorySet(&tmpBuf[0u], DEV_TOTAL_FRAME_LEN, 0u, DEV_TOTAL_FRAME_LEN);

    if ((pOutBuf != NULL)&&(pInBuf != NULL))
    {

        /* 查询通信设备之间是否需要协议 */
        if ( 1u == AdapterGetDevProType(localType, devType, &proType) )
        {

            switch (proType)
            {

                case COM_WITHOUT_PRO:

                    /* 对于不需要协议的数据，需要只取出一系的数据给应用*/
                    /* 将之前已经取出的数据包发送给应用 */

                    if (0u == MemoryCpy(pOutBuf, outMaxLen, pInBuf, inLen))
                    {
                        retLen = inLen;
                    }
                    else
                    {
                        retLen = 0u;
                    }
    
                    break;
            
                case COM_WITH_RSSP:

                    /* rssp协议要求将数据打包一起进行处理，因此需要循环扫描提取出全部的数据和成为一包 */

                    if (inLen <= DEV_TOTAL_FRAME_LEN)
                    {
                        /* 先将之前获取的第一包数据放入总数据缓存中 */
                        MemoryCpy(&totalBuf[0u], DEV_TOTAL_RCV_FRAME_LEN, &pInBuf[0u], inLen);
                        totalLen = inLen;

                        /* 按照获取的第一包数据的设备进行全部扫描数据，最终整合为一包数据 */
                        tmpLen = AdapterScanDevRcvQueData( &tmpBuf[0u], DEV_TOTAL_FRAME_LEN, devType, devId);

                        while (tmpLen > 0u)
                        {
                            if ((totalLen + tmpLen) <= DEV_TOTAL_RCV_FRAME_LEN)
                            {
                                MemoryCpy(&totalBuf[totalLen], DEV_TOTAL_RCV_FRAME_LEN - totalLen, &tmpBuf[0u], tmpLen);
                                totalLen = totalLen + tmpLen;
                            }
                            else
                            {
                                /* 可用的存储空间不足 */
                                break;
                            }

                            tmpLen = AdapterScanDevRcvQueData( &tmpBuf[0u], DEV_TOTAL_FRAME_LEN, devType, devId);
                        }
                    }
                    else
                    {
                        /* 可用的存储空间不足 */
                        AdptAppLogPrintf(1u,"inLen error %d\n", inLen);
                    }

                    if (totalLen > 0u)
                    {
                        dstName = (UINT16_S)((devType << 8u) + devId);

                        AdptAppLogPrintBuff(totalBuf, DEV_TOTAL_RCV_FRAME_LEN, totalLen);

                        proRet = AdptPlatRsspParseData(dstName, (UINT16_S)totalLen, &totalBuf[0u], &outLen, &outBuf[0u]);
                        rsspStatus = AdptPlatRsspGetChaStat(dstName, &timeDiff);

                        AdptAppLogPrintf(1u,"RSSP Rcv: %x %d %d %d %d\n",dstName, totalLen,outLen,proRet,rsspStatus);
                        AdptAppLogPrintBuff(outBuf, DEV_TOTAL_FRAME_LEN, outLen);

                        /*解包正确且状态值为1,链路正常才处理*/
                        if((1u == rsspStatus) && ((RSSP_PARSE_SSE_SSR == proRet) || (RSSP_PARSE_RSD == proRet)))
                        {
                            if (outLen > 0u)
                            {
                                if (0u == MemoryCpy(pOutBuf, outMaxLen, outBuf, outLen))
                                {
                                    retLen = outLen;
                                }
                                else
                                {
                                    retLen = 0u;
                                }
                            }
                            else
                            {
                                /* 协议处理后长度错误 */
                                retLen = 0u;
                            }
                        }
                        else
                        {
                            /* 协议处理失败 */
                            retLen = 0u;
                        }
                    }
                    else
                    {
                        /* 没有获得需要处理的数据 */
                        retLen = 0u;
                    }

                    break;
            
                default:

                    /* 不属于可以处理的类型 */
                    AdptAppLogPrintf(1u, "unknow protocol type:%d\n", proType);

                    retLen = 0u;

                    break;
            }

        }
        else
        {
            /* 无法获得关于协议配置有效的信息 */
            retLen = 0u;
        }

    }
    return retLen;
}


/*
*功能描述: 按照源设备类型和目的设备类型获取设备通信协议标志位
*参数：
*返回值: 0 失败 1 成功
*/
static UINT8_S AdapterGetDevProType(UINT8_S comSrcType, UINT8_S comDstType, UINT8_S * pComProType)
{
    UINT32_S i = 0u;
    UINT8_S rtnValue = 0u;

    if ( pComProType != NULL )
    {
        for (i = 0u;i < gComDevProCount;i++)
        {
            if ((gComDevProStruct[i].comSrcType == comSrcType)&&(gComDevProStruct[i].comDstType == comDstType))
            {
                *pComProType = gComDevProStruct[i].protocolFlag;
                rtnValue = 1u;
            }
            else if ((gComDevProStruct[i].comSrcType == comDstType)&&(gComDevProStruct[i].comDstType == comSrcType))
            {
                *pComProType = gComDevProStruct[i].protocolFlag;
                rtnValue = 1u;
            }
            else
            {
                /* 继续循环查找 */
            }

            if ( 1u == rtnValue )
            {
                break;
            }
        }
    }
    else
    {
        rtnValue = 0u;
    }

    return rtnValue;
}

/* 
* 功能描述：获取设备的通信状态记录标志
* 参数说明：
* 返回值  ：    1 有数据 0 无数据
*/
UINT8_S AdptAppGetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId)
{
    UINT8_S comFlag = 0u;

    comFlag = AdapterGetDevComStatus(devType, devId, sysId);

    return comFlag;
}

