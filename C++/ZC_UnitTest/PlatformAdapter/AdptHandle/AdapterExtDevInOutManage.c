/********************************************************
*                                                                                                            
* 文 件 名： AdapterExtDevInOutManage.c   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 适配层处理文件 
* 备    注： 无 
*
********************************************************/ 

#include "AdapterExtDevInOutManage.h"

#include "../../Common/Copy.h"
#include "../../Common/MemSet.h"
#include "../../Common/Convert.h"
#include "../../Common/CRC32.h"
#include "../PlatItf/AdptPlatServiceInterface.h"
#include "AdapterCommonDef.h"
#include "../PlatformLog/AdapterLog.h"
#include "../AppItf/AdptAppExtDevDataInterface.h"
#include "../AppItf/AdptAppServiceInterface.h"

#include "../AppItf/AdptAppCommonDef.h"

DevComCirQueueStruct gAdapterSndDataQueue;        /*Atp对外发送设备数据的存放队列*/
DevComCirQueueStruct gAdapterRcvDataQueue;         /*Atp接收外部设备数据的存放队列*/


AdptDevCfgDetailStruct gDevCfgList[PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM];   /*通信设备配置结构体数组*/
UINT32_S gDevCfgNum = 0u;                                                               /*通信设备配置结构体数组中有效条目数*/

AdptMicrDevStruct gMicrDevStruct[MIC_R_DEV_NUM];         /* 过网关设备的信息结构体 */
UINT8_S gMicrDevNum = 0u;                                /* 过网关设备的数目 */

UINT8_S gMicrOutId = 1u;   /*  当前两系的网关的ID 默认从1开始循环 */
UINT8_S gMicrNum = 0u;     /*  配置的非NTP网关的数目 */

/* 与设备配置相关 */
static UINT32_S AdapterGetDevCfgSum(void);
static UINT8_S AdapterGetDevCfgByIndex(const UINT32_S index, UINT16_S *devType, UINT8_S *devId, UINT8_S *sysId);
static UINT32_S AdapterGetDevCfgIndex(const UINT16_S devType,const UINT8_S devId,const UINT8_S sysId);

/* 多管道处理相关 */
static UINT8_S AdapterGetDevRcvPipeNum(const UINT32_S index, UINT32_S *rcvPipeNum);
static UINT8_S AdapterGetDevSndPipeIndex(const UINT32_S index, UINT32_S *sndPipeIndex);
static UINT8_S AdapterAddDevSndPipeIndex(const UINT32_S index);

/* 通用队列处理相关 */
static UINT8_S AdapterAddDevComQueData(DevComCirQueueStruct* pCirQueueStru,const UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId);
static UINT8_S AdapterClearDevComQueData(DevComCirQueueStruct* pCirQueueStru);
static UINT32_S AdapterGetDevComQuePkgCount(DevComCirQueueStruct* pCirQueueStru);
static UINT32_S AdapterGetDevComQuePkgData(DevComCirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S*pDevType,UINT8_S* pDevId,UINT8_S* pScanFlag);
static UINT32_S AdapterScanComDevQueData(DevComCirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen, const UINT8_S destDevType, const UINT8_S destDevId);

/* 接收数据队列处理相关 */
static UINT8_S AdapterAddDevRcvQueData(const UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId);
static UINT8_S AdapterClearDevRcvQueData(void);
static UINT8_S AdapterGetExtDevStartIndex(void);

/* 发送数据队列处理相关 */
static UINT32_S AdapterGetDevSndQuePkgCount(void);
static UINT32_S AdapterGetDevSndQuePkgData(UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S* pDevType,UINT8_S* pDevId);
static UINT8_S AdapterClearDevSndQueData(void);

/* 设备通信状态记录相关 */
static void AdapterClearDevComStatus(void);
static void AdapterSetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId, const UINT8_S comFlag);

/*
* 功能描述：初始化设备配置信息结构
* 参数说明： 无
* 返回值  ：    1,成功，0，失败
*/
UINT8_S AdapterExtDevCfgInfoInit(void)
{
    UINT8_S retVal = 0u;
    UINT32_S size = 0u;

    gDevCfgNum = 0u;
    
    size = PLATFORM_DEV_SYS_NUM * PLATFORM_COMM_DEV_MAXSUM * sizeof(AdptDevCfgDetailStruct);
    retVal = MemorySet(gDevCfgList,size,0u,size);

    return retVal;
}

/*
* 功能描述：读取设备配置信息
* 参数说明： 
* 返回值  ： 1:成功  0,失败
*/
UINT8_S AdapterGetDevCfgDetail(void)
{
    UINT8_S retVal = 1u;

    retVal = AdptPlatGetDevCfgDetail(PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM, gDevCfgList, &gDevCfgNum);

    return retVal;
}



/*
* 功能描述：读取设备配置信息个数
* 参数说明： 
* 返回值  ：设备配置信息个数
*/
static UINT32_S AdapterGetDevCfgSum(void)
{
    UINT32_S retVal = 0u;

    retVal = gDevCfgNum;

    return retVal;
}

/*
* 功能描述: 获取指定索引的设备类型与设备ID
* 参数：输入，
*                const UINT32_S index,设备信息表索引
*                输出，
*                UINT16_S * devType,设备类型
*                UIN8 *devId,应用设备ID
*                UINT8 *sysId,系别
* 返回值: 1，成功，0，失败
*/
static UINT8_S AdapterGetDevCfgByIndex(const UINT32_S index,UINT16_S *devType,UINT8_S *devId,UINT8_S *sysId)
{
    UINT32_S devSum = 0u;
    UINT8_S retVal = 0u;

    devSum = AdapterGetDevCfgSum();

    if(index < devSum)
    {
        if((NULL != devType) && (NULL != devId) &&(NULL != sysId))
        {
            *devType = gDevCfgList[index].devType;
            *devId = gDevCfgList[index].devId;
            *sysId = gDevCfgList[index].devSysId;
            retVal = 1u;
        }
    }

    return retVal;
}

/*
* 功能描述: 根据指定的设备类型，设备ID,系别，获取此设备配置在配置表中的索引 
* 参数： 输入，
*                  UINT16_S devType,设备类型
*                  UIN8 devId,应用设备ID
*                  UINT8 sysId,系别
* 返回值: 设备配置在配置表中的索引(查找失败返回UINT32_MAX)
*/
static UINT32_S AdapterGetDevCfgIndex(const UINT16_S devType,const UINT8_S devId,const UINT8_S sysId)
{
    UINT32_S devSum = 0u;
    UINT32_S ii = 0u;
    UINT32_S retVal = UINT32_MAX;

    devSum = AdapterGetDevCfgSum();

    for(ii = 0; ii < devSum;ii++)
    {
        if((gDevCfgList[ii].devType == devType)&&(gDevCfgList[ii].devId == devId)&&(gDevCfgList[ii].devSysId == sysId))
        {
            retVal = ii;
            break;
        }
    }

    return retVal;

}


/*
* 功能描述: 获取指定索引的设备接收管道数目
* 参数：输入，
*                const UINT32_S index,设备信息表索引
*       输出，
*                UINT32_S *rcvPipeNum 管道数目
* 返回值: 1，成功，0，失败
*/
static UINT8_S AdapterGetDevRcvPipeNum(const UINT32_S index, UINT32_S *rcvPipeNum)
{
    UINT32_S devSum = 0u;
    UINT8_S retVal = 0u;

    if (rcvPipeNum != NULL)
    {
        devSum = AdapterGetDevCfgSum();
        if(index < devSum)
        {
            /*
            *rcvPipeNum = gDevCfgList[index].rcvPipeNum;
            retVal = 1u;
            */
            /* pbw 20180520 调试暂时写成固定值1 */
			*rcvPipeNum = 1;
            retVal = 1u;
        }
    }

    return retVal;
}



/*
* 功能描述: 获取指定索引的设备发送正在处理的管道索引
* 参数：输入，
*                const UINT32_S index,设备信息表索引
*       输出，
*                UINT32_S *sndPipeIndex 管道索引
* 返回值: 1，成功，0，失败
*/
static UINT8_S AdapterGetDevSndPipeIndex(const UINT32_S index, UINT32_S *sndPipeIndex)
{
    UINT32_S devSum = 0u;
    UINT8_S retVal = 0u;

    if ( sndPipeIndex != NULL )
    {
        devSum = AdapterGetDevCfgSum();
        if(index < devSum)
        {
            *sndPipeIndex = gDevCfgList[index].sndPipeIndex;
            retVal = 1u;
        }
    }

    return retVal;
}

/*
* 功能描述: 获取指定索引的设备发送正在处理的管道索引
* 参数：输入，
*                const UINT32_S index,设备信息表索引
*       输出，
*                UINT32_S *sndPipeIndex 管道索引
* 返回值: 1，成功，0，失败
*/
static UINT8_S AdapterAddDevSndPipeIndex(const UINT32_S index)
{
    UINT32_S devSum = 0u;
    UINT8_S retVal = 0u;

    devSum = AdapterGetDevCfgSum();

    if(index < devSum)
    {
        if (gDevCfgList[index].sndPipeNum == (gDevCfgList[index].sndPipeIndex + 1u))
        {
            gDevCfgList[index].sndPipeIndex = 0u;
        }
        else
        {
            gDevCfgList[index].sndPipeIndex++;
        }
        retVal = 1u;
    }

    return retVal;
}


/*
* 功能描述: 平台外部输入数据管理
* 参数：
* 返回值: 无
*/

void AdapterExtDevInDataManage(void)
{
    UINT32_S i = 0u;
    UINT32_S devSum = 0u;
    
    UINT16_S devType = 0u;
    UINT8_S devId = 0u;
    UINT8_S sysId = 0u;

    AdptUsrBuffStruct ioUsrBuff;
    UINT8_S recvBuf[DEV_TOTAL_FRAME_LEN] = {0u};
    UINT8_S funcVal = 0u;
    UINT8_S j = 0u;

    UINT32_S rcvPipeNum = 0u;
    UINT8_S tmpRet = 0u;
    UINT8_S start = 0u;

    UINT32_S pkgIndex = 0u;
    UINT32_S pkgLen = 0u;
    UINT8_S pkgType = 0u;
    UINT8_S pkgId = 0u;

    AdapterClearDevRcvQueData();

    /* 清除两系通信状态记录标志 */
    AdapterClearDevComStatus();

    devSum = AdapterGetDevCfgSum();

    ioUsrBuff.ptrMsg = recvBuf;
    ioUsrBuff.dataLen = 0u;
    ioUsrBuff.allocLen = DEV_TOTAL_FRAME_LEN;

    start = AdapterGetExtDevStartIndex();

    for(i = start;i < devSum;i++)
    {

        /* 遍历所有外部通信设备配置表,获取设备表中的设备标识(设备类型及ID) */
        if(1u == AdapterGetDevCfgByIndex(i, &devType, &devId, &sysId))
        {
       
            AdapterGetDevRcvPipeNum(i, &rcvPipeNum);

            /* 每一个通道取出一个独立的数据包发送给应用 */
            for ( j = 0u; j < rcvPipeNum; j++ )
            {
                /* 循环所有的通道 */
                MemorySet(ioUsrBuff.ptrMsg, ioUsrBuff.allocLen, 0, ioUsrBuff.allocLen);
                ioUsrBuff.dataLen = 0;
            
                funcVal = AdptPlatUsrDataRecv(devType, devId, sysId, j, &ioUsrBuff);

                if (1u == funcVal)
                {

                    if ((DEVTYPE_MIC_R == devType)||(DEVTYPE_MIC_NTP == devType))
                    {

                        pkgIndex = 0u;

                        /* 将收到的数据全部解析为单个的数据包 */
                        while( pkgIndex < ioUsrBuff.dataLen )
                        {
                            pkgType = ioUsrBuff.ptrMsg[pkgIndex];
                            pkgIndex++;
                            
                            pkgId = ioUsrBuff.ptrMsg[pkgIndex];
                            pkgIndex++;
                            
                            pkgLen = ShortFromChar(&ioUsrBuff.ptrMsg[pkgIndex]);
                            pkgIndex = pkgIndex + 2u;

                            if ((pkgIndex + pkgLen + 4u) <= ioUsrBuff.dataLen)
                            {
                                /* 保证数据为整包再发送 */

                                AdapterAddDevRcvQueData(&ioUsrBuff.ptrMsg[pkgIndex], pkgLen, pkgType, pkgId);
                                pkgIndex = pkgIndex + pkgLen + 4u;
                                AdapterSetDevComStatus(pkgType,pkgId, sysId, EXT_DEV_COM_SUC);
                            }
                            else
                            {
                                AdptAppLogPrintf(1,"pkg error:%x,%d,%d\n",pkgType,pkgId,pkgLen);
                                /* 数据不为整包 */
                                break;
                            }

                        }
                        
                    }
                    else
                    {
                        AdapterSetDevComStatus(devType,devId, sysId, EXT_DEV_COM_SUC);
                        AdapterAddDevRcvQueData(ioUsrBuff.ptrMsg, ioUsrBuff.dataLen, (UINT8_S)devType, devId);
                    }
                }

            }

        }
        else
        {
            AdptAppLogPrintf(1u,"get index %d dev type error\n", i);
        }

    }
}


/*
*功能描述: 平台外部输出数据管理
*参数：
*返回值: 
*/

void AdapterExtDevOutDataManage(void)
{
    UINT8_S devType = 0u;
    UINT8_S devId = 0u;
    UINT8_S scanFlag = 0u;

    UINT16_S localName = 0u;
    UINT8_S localType = 0u;
    UINT8_S proType = 0u;
    UINT16_S dstName = 0u;

    UINT32_S devIndex1 = 0u;
    UINT32_S devIndex2 = 0u;

    UINT8_S funcVal1 = 0u;
    UINT8_S funcVal2 = 0u;

    UINT8_S ii = 0u;
    UINT32_S dataLen = 0u;
    UINT8_S  chOutputDataBuff[DEV_TOTAL_FRAME_LEN] = {0u};

    UINT32_S sndPipeIndex1 = 0u;
    UINT32_S sndPipeIndex2 = 0u;

    UINT32_S dataPkgNum = 0u;

    UINT8_S micFlag = 0u;
    UINT32_S outLen = 0u;
    UINT8_S outData[DEV_TOTAL_FRAME_LEN] = {0u};

    localName = AdptAppGetLocalName();
    localType = (UINT8_S)((localName>>8u) & 0x00FFu);

    /*获取输出给外部的数据*/
    dataPkgNum = AdapterGetDevSndQuePkgCount();

    /*获取单帧数据*/
    for (ii = 0u;ii < dataPkgNum;ii++)
    {
        /*初始化局部变量*/
        MemorySet(&chOutputDataBuff[0u], sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN,0u, sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN);

        dataLen = AdapterGetDevSndQuePkgData(chOutputDataBuff, DEV_TOTAL_FRAME_LEN, &devType, &devId);

		
        if (dataLen > 0u)
        {

            micFlag = AdptPlatOutDataHandle(devType, devId, chOutputDataBuff, dataLen, outData, &outLen);

            if ( HANDLE_OUT_MICR_DEV == micFlag )
            {
                /* 设备过网关 */
                devType = DEVTYPE_MIC_R;
                devId = gMicrOutId;
            }
            else if ( HANDLE_OUT_MICR_NTP == micFlag )
            {
                /* 设备过NTP网关 */
                devType = DEVTYPE_MIC_NTP;
            }
            else
            {
                /* 设备不过网关 */
            }

            /* 查询设备在通信表中的编号 */
            devIndex1 = AdapterGetDevCfgIndex((UINT16_S)devType, devId, 1u);
            devIndex2 = AdapterGetDevCfgIndex((UINT16_S)devType, devId, 2u);

            /* 查询设备发送数据正在处理的管道编号 */
            AdapterGetDevSndPipeIndex(devIndex1, &sndPipeIndex1);
            AdapterGetDevSndPipeIndex(devIndex2, &sndPipeIndex2);

  /* ??? temporary revise, discuss after */
			devIndex1 = 0u;
			devIndex2 = 0u;
			sndPipeIndex1 = 0u;
			sndPipeIndex2 = 0u;

           
		
            /*向一系发送数据*/
            if(UINT32_MAX != devIndex1)
            {
                funcVal1 = AdptPlatUsrDataSend(devType,devId,1u,sndPipeIndex1,outData,outLen);

                if (1u == funcVal1)
                {
                    AdapterAddDevSndPipeIndex(devIndex1);
                }
            }
            
            /*向二系发送数据
            if(UINT32_MAX != devIndex2)
            {
                funcVal2 = AdptPlatUsrDataSend(devType,devId,2u,sndPipeIndex2,outData,outLen);

                if (1u == funcVal2)
                {
                    AdapterAddDevSndPipeIndex(devIndex2);
                }
            }
						*/

            /* 当一个网关的所有通道放满了之后，向下一个网关的通道放数据 */
            if ((DEVTYPE_MIC_R == devType)&&
                (0u == gDevCfgList[devIndex1].sndPipeIndex))
            {
                if ( gMicrOutId < (gMicrNum/2) )
                {
                    gMicrOutId++;
                }
                else
                {
                    gMicrOutId = 1u;
                }
            }
        }

    }



    AdapterClearDevSndQueData();

}


/*
* 功能描述： 添加队列数据
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针
*              char* pDataBuf, 数据缓冲区
*              int dataLen, 数据长度
* 返回值  ： 1: 成功
*            0: 失败
*/
static UINT8_S AdapterAddDevComQueData(DevComCirQueueStruct* pCirQueueStru,const UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId)
{
    UINT8_S retVal = 0u;

    if ((pCirQueueStru != NULL) && (pDataBuf != NULL) && (dataLen > 0u) && (dataLen <= DEV_TOTAL_FRAME_LEN) && (pCirQueueStru->DataPkgCount != DEV_TOTAL_FRAME_NUM))
    {
        if (DEV_TOTAL_FRAME_NUM == pCirQueueStru->TailIndex)
        {
            pCirQueueStru->TailIndex = 0u;
        }

        MemoryCpy(pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DataBuf, DEV_TOTAL_FRAME_LEN, pDataBuf, dataLen); /* 添加新数据 */

        /* 记录添加的数据长度 */
        pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DataLen = dataLen;
        pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DestDevId = destDevId;
        pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DestDevType = destDevType;
        pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].scanFlag = 0u;

        /* 增加尾索引 */
        pCirQueueStru->TailIndex++;
        /* 增加数据包个数 */
        pCirQueueStru->DataPkgCount++;

        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }
    
    return retVal;
}



/*
* 功能描述： 清除队列数据
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针
* 返回值  ： 1: 成功
*            0: 失败
*/
static UINT8_S AdapterClearDevComQueData(DevComCirQueueStruct* pCirQueueStru)
{
    UINT8_S i = 0u;
    UINT8_S retVal = 0u;

    if (pCirQueueStru != NULL)
    {

        for (i = 0u;i < DEV_TOTAL_FRAME_NUM;i++)
        {
            MemorySet(pCirQueueStru->DataCellStru[i].DataBuf, DEV_TOTAL_FRAME_LEN, 0u, DEV_TOTAL_FRAME_LEN); 
            /* 记录添加的数据 */
            pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DataLen = 0u; 
            pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DestDevId = 0u;
            pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DestDevType = 0u;
            pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].scanFlag = 0u;
        }

        pCirQueueStru->HeadIndex = 0u;
        pCirQueueStru->TailIndex = 0u;
        pCirQueueStru->DataPkgCount = 0u;

        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }
    return retVal;
}


/*
* 功能描述： 获取队列数据包个数
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针    
* 返回值  ： 数据包个数
*/
static UINT32_S AdapterGetDevComQuePkgCount(DevComCirQueueStruct* pCirQueueStru)
{
    UINT32_S retVal = 0u;

    if ( pCirQueueStru != NULL )
    {
        retVal = pCirQueueStru->DataPkgCount;
    }
    
    return retVal;
}


/*
* 功能描述： 获取队列数据包
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针
*              char* pDataBuf, 数据缓冲区
*              int dataLen, 数据长度    
* 返回值  ： 0: 失败
*              >0: 数据的字节长度
*/
static UINT32_S AdapterGetDevComQuePkgData(DevComCirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S* pDevType,UINT8_S* pDevId,UINT8_S *pScanFlag)
{
    UINT32_S realDataLen = 0u; /*记录实际数据长度*/
    UINT32_S retVal = 0u;

    if ((pCirQueueStru != NULL) && (pDataBuf != NULL) && (dataLen > 0u)&& (pDevType != NULL)&& (pDevId != NULL)&& (pScanFlag != NULL))
    {
        if (pCirQueueStru->DataPkgCount > 0u)
        {

            /* 数据包个数大于0 */
            realDataLen = pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DataLen; /* 记录实际数据长度 */

            if ((realDataLen > 0u) && (dataLen >= realDataLen))
            {

                /* 实际数据长度有效 && 获取数据缓冲区长度有效 && 数据包个数大于0 */
                MemoryCpy(pDataBuf, dataLen, pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DataBuf, realDataLen);
                *pDevType = pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DestDevType;
                *pDevId = pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DestDevId;
                *pScanFlag = pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].scanFlag;

                /* 提取数据后处理头索引 */
                pCirQueueStru->HeadIndex++;

                if (DEV_TOTAL_FRAME_NUM == pCirQueueStru->HeadIndex)
                {
                    pCirQueueStru->HeadIndex = 0u;
                }

                /* 减少数据包个数 */
                pCirQueueStru->DataPkgCount--;

                retVal = realDataLen;
            }
            else
            {
                retVal = 0u;
            }
        }
        else
        {
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
* 功能描述： 按照设备类型和设备编号扫描到队列中的一包数据
* 参数说明： CirQueueStruct* pCirQueueStru, 环形队列指针
* 返回值  ： 0: 失败
*            >0: 数据的字节长度
*/
static UINT32_S AdapterScanComDevQueData(DevComCirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen, const UINT8_S destDevType, const UINT8_S destDevId)
{
    UINT32_S i = 0u;
    UINT32_S retVal = 0u;
    UINT32_S index = 0u;

    if ((pCirQueueStru != NULL) && (pDataBuf != NULL) && (dataLen > 0u))
    {
        index = pCirQueueStru->HeadIndex;

        for (i = 0u;i < pCirQueueStru->DataPkgCount;i++)
        {

            if ((destDevType == pCirQueueStru->DataCellStru[index].DestDevType) &&
                (destDevId == pCirQueueStru->DataCellStru[index].DestDevId)&&
                (0u == pCirQueueStru->DataCellStru[index].scanFlag))
            {

                if (dataLen >= pCirQueueStru->DataCellStru[index].DataLen)
                {

                    MemoryCpy(pDataBuf, dataLen, pCirQueueStru->DataCellStru[index].DataBuf, pCirQueueStru->DataCellStru[index].DataLen);
                    pCirQueueStru->DataCellStru[index].scanFlag = 1u;
                    retVal = pCirQueueStru->DataCellStru[index].DataLen;

                    break;
                }
                else
                {
                    /* 接收数据空间不足 */
                    retVal = 0u;
                }
            }

            index ++;
            if (DEV_TOTAL_FRAME_NUM == index)
            {
                index = 0u;
            }
        }

    }
    else
    {
        retVal = 0u;
    }

    return retVal;
}



/*
* 功能描述： 添加接收队列数据
* 参数说明： 
*            pDataBuf, 数据缓冲区
*            dataLen, 数据长度
*            destDevType,设备类型
*            destDevId,设备ID
* 返回值  ： 1: 成功
*            0: 失败
*/
static UINT8_S AdapterAddDevRcvQueData(const UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId)
{
    UINT8_S retVal = 0u;

    if (pDataBuf != NULL)
    {
        retVal = AdapterAddDevComQueData(&gAdapterRcvDataQueue, pDataBuf, dataLen, destDevType, destDevId);
    }

    return retVal;
}


/*
* 功能描述： 顺序获取接收队列的一个数据包
* 参数说明： 
*              char* pDataBuf, 数据缓冲区
*              int dataLen, 数据长度    
*            pDevType,设备类型
*            pDevId,设备ID
* 返回值  ： 0: 失败
*              >0: 数据的字节长度
*/
UINT32_S AdapterGetDevRcvQuePkgData(UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S* pDevType,UINT8_S* pDevId)
{
    UINT32_S retVal = 0u; /*记录实际数据长度*/
    UINT8_S scanFlag = 0u;

    if ((pDataBuf != NULL)&&(pDevType!= NULL)&&(pDevId!= NULL))
    {
        retVal = AdapterGetDevComQuePkgData(&gAdapterRcvDataQueue, pDataBuf, dataLen, pDevType, pDevId, &scanFlag);

        /* 确保获取的数据没有被扫描出来过 */
        while ((retVal > 0u) && (1u == scanFlag))
        {
            /* 如果获取的数据被扫描过则继续取数据 */
            retVal = AdapterGetDevComQuePkgData( &gAdapterRcvDataQueue, pDataBuf, dataLen, pDevType, pDevId, &scanFlag);
        }
    }
    return retVal;
}

/*
* 功能描述： 按照设备类型和设备编号扫描接收队列中的一包数据
* 参数说明： pDataBuf, 数据缓冲区
*            dataLen, 数据长度
*            destDevType,设备类型
*            destDevId,设备ID
* 返回值  ： 0: 失败
*            >0: 数据的字节长度
*/
UINT32_S AdapterScanDevRcvQueData(UINT8_S* pDataBuf, UINT32_S dataLen, const UINT8_S destDevType, const UINT8_S destDevId)
{

    UINT32_S retVal = 0u;

    if (pDataBuf != NULL)
    {
        retVal = AdapterScanComDevQueData(&gAdapterRcvDataQueue, pDataBuf, dataLen, destDevType, destDevId);
    }

    return retVal;
}


/*
* 功能描述： 清除接收队列数据
* 参数说明： 
* 返回值  ： 1: 成功
*            0: 失败
*/
static UINT8_S AdapterClearDevRcvQueData(void)
{
    UINT8_S retVal = 0u;

    retVal = AdapterClearDevComQueData(&gAdapterRcvDataQueue);

    return retVal;
}

/*
* 功能描述： 添加发送队列数据
* 参数说明： 
*            pDataBuf, 数据缓冲区
*            dataLen, 数据长度
*            destDevType,设备类型
*            destDevId,设备ID
* 返回值  ： 1: 成功
*            0: 失败
*/
UINT8_S AdapterAddDevSndQueData(const UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId)
{
    UINT8_S retVal = 0u;

    if (pDataBuf != NULL)
    {
        retVal = AdapterAddDevComQueData(&gAdapterSndDataQueue, pDataBuf, dataLen, destDevType, destDevId);
    }

    return retVal;
}



/*
* 功能描述： 获取发送数据包个数
* 参数说明：
* 返回值  ： 数据包个数
*/
static UINT32_S AdapterGetDevSndQuePkgCount()
{

    UINT32_S retVal = 0u;
    
    retVal = AdapterGetDevComQuePkgCount(&gAdapterSndDataQueue);

    return retVal;

}


/*
* 功能描述： 顺序获取发送队列的一个数据包
* 参数说明： 
*              char* pDataBuf, 数据缓冲区
*              int dataLen, 数据长度    
* 返回值  ： 0: 失败
*              >0: 数据的字节长度
*/
static UINT32_S AdapterGetDevSndQuePkgData(UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S* pDevType,UINT8_S* pDevId)
{
    UINT32_S retVal = 0u; /*记录实际数据长度*/
    UINT8_S scanFlag = 0u;

    if ((pDataBuf != NULL) && (pDevType != NULL) && (pDevId != NULL))
    {
        retVal = AdapterGetDevComQuePkgData(&gAdapterSndDataQueue, pDataBuf, dataLen, pDevType, pDevId, &scanFlag);

        /* 确保获取的数据没有被扫描出来过 */
        while ((retVal > 0u) && (1u == scanFlag))
        {
            /* 如果获取的数据被扫描过则继续取数据 */
            retVal = AdapterGetDevComQuePkgData( &gAdapterSndDataQueue, pDataBuf, dataLen, pDevType, pDevId, &scanFlag);
        }
    }

    return retVal;
}


/*
* 功能描述： 清除发送队列数据
* 参数说明： 
* 返回值  ： 1: 成功
*            0: 失败
*/
static UINT8_S AdapterClearDevSndQueData(void)
{
    UINT8_S retVal = 0u;

    retVal = AdapterClearDevComQueData(&gAdapterSndDataQueue);

    return retVal;
}


/*
* 功能描述： 获取外部设备在设备配置表中的起始位置 
* 参数说明： 
* 返回值  ： 1: 成功
*            0: 失败
*/
static UINT8_S AdapterGetExtDevStartIndex(void)
{
    UINT8_S retVal = 0u;

    UINT16_S localName = 0u;
    UINT8_S localType = 0u;

    localName = AdptAppGetLocalName();
    localType = (UINT8_S)((localName>>8u) & 0x00FFu);

    if (localType == DEVTYPE_DMS)
    {
        retVal = VCP_DMS_START_INDEX;
    }
    else if (localType == DEVTYPE_ZC)
    {
        retVal = VCP_ZC_START_INDEX;

    }
    else if (localType == DEVTYPE_VOBC)
    {
        retVal = VCP_ATP_START_INDEX;
    }
    else
    {
        retVal = 0u;
    }

    return retVal;
}


/* 
* 功能描述：清除设备的通信状态记录标志
* 参数说明：无
* 返回值  ：    无
*/
static void AdapterClearDevComStatus(void)
{
    MemorySet(gMicrDevStruct, sizeof(gMicrDevStruct), 0u, sizeof(gMicrDevStruct));
    gMicrDevNum = 0u;
}

/* 
* 功能描述：设置设备的通信状态记录标志
* 参数说明：devType 设备类型
*          devId 设备ID
*           sysId 系别
*           comFlag 通信状态记录标志
* 返回值  ：    无
*/
static void AdapterSetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId, const UINT8_S comFlag)
{
    UINT8_S i = 0u;
    
    for (i = 0u;i < gMicrDevNum;i++)
    {
        /* 判断查找到已经收过数据的设备 */
        if ((devType == gMicrDevStruct[i].devType) && (devId == gMicrDevStruct[i].devId) && (sysId == gMicrDevStruct[i].sysId))
        {
            gMicrDevStruct[i].comFlag = comFlag;
            break;
        }
    }

    /* 判断没收过数据的新设备 */
    if ((i == gMicrDevNum) && (i < (MIC_R_DEV_NUM - 1u) ))
    {
        gMicrDevStruct[i].devType = devType;
        gMicrDevStruct[i].devId = devId;
        gMicrDevStruct[i].sysId = sysId;
        gMicrDevStruct[i].comFlag = comFlag;
        gMicrDevNum++;
    }

}

/* 
* 功能描述：获取设备的通信状态记录标志
* 参数说明： devType 设备类型
*           devId 设备ID
*           sysId 系别
* 返回值  ：    1 有数据 0 无数据
*/
UINT8_S AdapterGetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId)
{
    UINT8_S comFlag = 0u;
    UINT8_S i = 0u;

    for (i = 0u;i < gMicrDevNum;i++)
    {
        /* 判断查找到已经收过数据的设备 */
        if ((devType == gMicrDevStruct[i].devType) && (devId == gMicrDevStruct[i].devId) && (sysId == gMicrDevStruct[i].sysId))
        {
            comFlag = gMicrDevStruct[i].comFlag;
            break;
        }
    }

    return comFlag;
}

/* 
* 功能描述：设置非NTP网关的数量
* 参数说明：micrNum 网关设备的数量
* 返回值  ：    无
*/
void AdapterSetMicrNum(const UINT8_S micrNum)
{
    gMicrNum = micrNum;
}


