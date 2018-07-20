/********************************************************
*                                                                                                            
* 文 件 名： AdapterLog.c   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 适配层提供给平台层的日志记录接口文件 
* 备    注： 无 
*
********************************************************/ 

#include "AdapterLog.h"
#include <stdarg.h>

#include "../../Common/MemSet.h"
#include "../../Common/Copy.h"
#include "../AdptHandle/AdapterCommonDef.h"
#include "../AppItf/AdptAppExtDevDataInterface.h"
#include "../AppItf/AdptAppCommonDef.h"
#include "../AppItf/AdptAppServiceInterface.h"
#include "../../Common/Convert.h"

extern int vsprintf(CHAR_S *buff,const CHAR_S *format, va_list paraList);

static UINT8_S gMaintainDataArr[MAX_LOG_LEN] = {0u};
static UINT32_S gMaintainLen = 0u;

static UINT8_S gTempArr[MAX_LOG_LEN] = {0u};



/*
* 功能描述： 打印log信息
* 参数说明： 无
* 返回值  ： 0:  失败
*            1: 成功
*/
UINT8_S AdptAppLogPrintf(UINT8_S chRunSystem, const CHAR_S * lpszFormat, ...)
{
    UINT8_S retVal = 0u;
    va_list arg_ptr;
    INT32_S n = 0;

    UINT32_S useLen = 0u;

    if ( NULL != lpszFormat )
    {
        useLen = MAX_LOG_LEN - gMaintainLen;

        va_start(arg_ptr,lpszFormat);
        n = vsprintf((CHAR_S *)&gTempArr[0u],lpszFormat, arg_ptr);
        va_end(arg_ptr);
        
        if(n  <= 0)
        {
            retVal = 0u;
        }
        else
        {
            if (1u == chRunSystem)
            {
                if((UINT32_S)n >= useLen)
                {
                    MemoryCpy(&gMaintainDataArr[gMaintainLen], useLen, gTempArr, useLen);
                    gMaintainLen += useLen;
                }
                else
                {
                    MemoryCpy(&gMaintainDataArr[gMaintainLen], useLen, gTempArr, (UINT32_S)n);
                    gMaintainLen  += ((UINT32_S)n);
                }
                retVal = 1u;
            }
            else
            {
                /* 预留为其他log记录方式，比如写文件之类 */
                retVal = 0u;
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
* 功能描述： 将缓冲区数据转化为字符串 
* 参数说明：dataBuf，输入缓冲区 
*                            bufLength 输入缓冲区总大小 
*                            dataLength,需要转化的长度 
*函数返回值：0,转化错误  1，转化正常  
*/
UINT8_S AdptAppLogPrintBuff(const UINT8_S dataBuf[],const UINT16_S bufLength, const UINT16_S dataLength )
{

    UINT16_S i = 0u;
    UINT8_S retVal = 0u;

    if (( dataBuf != NULL ) && (bufLength >= dataLength))
    {
        for (i = 0u; i < dataLength; i++)
        {
            AdptAppLogPrintf(1u,"%x ", dataBuf[i]);
        }
        AdptAppLogPrintf(1u,"\n");

        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }

    return retVal;

}

/*
* 功能描述： 周期清空日志缓冲区
* 参数说明： 无
* 返回值  ： void
*/
void AdptAppLogBufPeriodClear()
{
    MemorySet(gMaintainDataArr, MAX_LOG_LEN, 0u, MAX_LOG_LEN);
    gMaintainLen = 0u;
}

/*
* 功能描述： 打包发送维护信息，调试用 
* 参数说明： UINT8_S destDevType,const UINT8_S destDevId
* 返回值  ： void
*/
void AdptAppLogDataPack(const UINT8_S destDevType,const UINT8_S destDevId)
{

    AdptAppLogRecordPack(destDevType, destDevId, gMaintainDataArr, gMaintainLen);

    AdptAppLogBufPeriodClear();

}


/*
* 功能描述： 打包发送维护信息，记录仪用 
* 参数说明： UINT8_S destDevType,const UINT8_S destDevId, const UINT8_S* logBuff, const UINT32_S logLen 
* 返回值  ： void
*/
void AdptAppLogRecordPack(const UINT8_S destDevType,const UINT8_S destDevId, const UINT8_S* logBuff, const UINT32_S logLen)
{
    UINT32_S index = 0u;                  /* 处理维护信息位置游标 */

    UINT8_S logBuf[DEV_TOTAL_FRAME_LEN] = {0u};
    UINT32_S i = 0u;

    UINT16_S localName = 0u;                /* 设备名称 */
    UINT8_S localType = 0u;                 /* 设备类型 */
    UINT8_S localId = 0u;                  /* 设备ID */

    UINT16_S endName = 0u;                 /* 本端名称，针对于ATP ATO  */
    UINT8_S endId = 0u;                    /* 本端为一端或二端 */
    UINT8_S sysId = 0u;                    /* 本端为一系或二系 */

    UINT8_S pkgNum = 0u;                   /* 总包数  */
    UINT32_S dataLeft = 0u;                /* 剩余字节数  */

    UINT8_S pkgIndex = 1u;                 /* 分包序号 */

    UINT32_S pkgHead = 0u;                 /* 分包相同部分记录 */

    UINT16_S pkgMaxLen = 0u;               /* 每一包分包最大长度 */

    UINT16_S crc16 = 0u;
    UINT32_S year = 0u, month = 0u, day = 0u, hour = 0u, min = 0u, sec = 0u;

    UINT8_S localSysId = 0u;
    UINT8_S masterSysId = 0u;

    /* 20180520 暂时注释
    localSysId = AdptAppGetSystemId();
    masterSysId = AdptAppGetMasterId();
    */

    /*本系为主系*/
    /* if(localSysId == masterSysId) */
    if(1)
    {

        /* 数据准备过程 */
        pkgMaxLen = DEV_TOTAL_FRAME_LEN - LOG_RECORD_HEAD_LEN;

        localName = AdptAppGetLocalName();
        localType = (UINT8_S)((localName>>8u) & 0x00FFu);
        localId = (UINT8_S)(localName & 0x00FFu);

        if ((DEVTYPE_VOBC == localType)||(DEVTYPE_ATO == localType))
        {
            /* 当设备存在一端二端差别时 */
            endName = AdptAppGetTrainName();
            endId = (UINT8_S)(endName & 0x00FFu);
        }
        else
        {
            /* 当设备不存在一端二端差别，记录为0 */
            endId = 0u;
        }

        /* 记录一系二系信息 */
		/* pbw 20180520 暂时注释 
        sysId = (UINT8_S)AdptAppGetSystemId();
        */

        /* 计算分包总数和最后一个包的长度 */
        pkgNum = logLen / pkgMaxLen;
        dataLeft = logLen % pkgMaxLen;
        if (dataLeft > 0u)
        {
            pkgNum++;
        }

        /* 数据打包过程 */

        /* 填写数据类型 */
        logBuf[i++] = LOG_RECORD_TYPE;

        /* 填写协议版本号 */
        logBuf[i++] = LOG_RECORD_VER;

        /* 填写时间，距离1970年的年月日时分秒 */
		/* pbw 20180520 暂时屏蔽 */
		/*
        AdptAppCalendarClkGet(&year,&month,&day,&hour,&min,&sec);
        year = year - 1970u;
        */
        logBuf[i++] = (UINT8_S)year;
        logBuf[i++] = (UINT8_S)month;
        logBuf[i++] = (UINT8_S)day;
        logBuf[i++] = (UINT8_S)hour;
        logBuf[i++] = (UINT8_S)min;
        logBuf[i++] = (UINT8_S)sec;

        /* 填写设备类型 */
        logBuf[i++] = localType;

        /* 填写列车ID */
        logBuf[i++] = localId;

        /* 填写端和系别信息 */
        logBuf[i++] = (UINT8_S)((endId<<4u) + sysId);

        /* 填写预留位9个字节0 */
        i = i + 9u;


        /* 填写系统周期号 */
        LongToChar(AdptAppCycNum(), &logBuf[i]);
        i = i + 4u;

        /* 填写分包总数 */
        logBuf[i++] = pkgNum;

        pkgHead = i;

        while((logLen - index) > 0)
        {

            i = pkgHead;

            /* 填写本包被分包数据序号 */
            logBuf[i++] = pkgIndex;

            pkgIndex++;

            if ((logLen - index) > pkgMaxLen)
            {

                /* 填写日志内容长度，不包含本字段 */
                ShortToChar(pkgMaxLen, &logBuf[i]);
                i = i + 2u;

                /* 填写日志原内容 */
                MemoryCpy(&logBuf[i], pkgMaxLen, &logBuff[index], pkgMaxLen);
                i = i + pkgMaxLen;
                index = index + pkgMaxLen;

            }
            else
            {
                /* 填写日志内容长度，不包含本字段 */
                ShortToChar((logLen - index), &logBuf[i]);
                i = i + 2u;

                /* 填写日志原内容 */
                MemoryCpy(&logBuf[i], pkgMaxLen, &logBuff[index], (logLen - index));
                i = i + (logLen - index);
                index = index + (logLen - index);

            }

            /* 填写日志内容CRC校验码 */
            crc16 = Crc16(logBuf, i);
            /* 填写日志内容长度，不包含本字段 */
            ShortToChar(crc16, &logBuf[i]);
            i = i + 2u;

            AdptAppExtDevSndData(&logBuf[0u], i, destDevType, destDevId);

        }
    }
    else
    {
        /* log为以太网配置时候，SMG需要判断备系不输出，否则会出现数据混乱 */
    }

}

