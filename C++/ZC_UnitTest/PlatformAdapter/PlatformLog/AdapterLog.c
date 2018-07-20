/********************************************************
*                                                                                                            
* �� �� ���� AdapterLog.c   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ������ṩ��ƽ̨�����־��¼�ӿ��ļ� 
* ��    ע�� �� 
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
* ���������� ��ӡlog��Ϣ
* ����˵���� ��
* ����ֵ  �� 0:  ʧ��
*            1: �ɹ�
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
                /* Ԥ��Ϊ����log��¼��ʽ������д�ļ�֮�� */
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
* ���������� ������������ת��Ϊ�ַ��� 
* ����˵����dataBuf�����뻺���� 
*                            bufLength ���뻺�����ܴ�С 
*                            dataLength,��Ҫת���ĳ��� 
*��������ֵ��0,ת������  1��ת������  
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
* ���������� ���������־������
* ����˵���� ��
* ����ֵ  �� void
*/
void AdptAppLogBufPeriodClear()
{
    MemorySet(gMaintainDataArr, MAX_LOG_LEN, 0u, MAX_LOG_LEN);
    gMaintainLen = 0u;
}

/*
* ���������� �������ά����Ϣ�������� 
* ����˵���� UINT8_S destDevType,const UINT8_S destDevId
* ����ֵ  �� void
*/
void AdptAppLogDataPack(const UINT8_S destDevType,const UINT8_S destDevId)
{

    AdptAppLogRecordPack(destDevType, destDevId, gMaintainDataArr, gMaintainLen);

    AdptAppLogBufPeriodClear();

}


/*
* ���������� �������ά����Ϣ����¼���� 
* ����˵���� UINT8_S destDevType,const UINT8_S destDevId, const UINT8_S* logBuff, const UINT32_S logLen 
* ����ֵ  �� void
*/
void AdptAppLogRecordPack(const UINT8_S destDevType,const UINT8_S destDevId, const UINT8_S* logBuff, const UINT32_S logLen)
{
    UINT32_S index = 0u;                  /* ����ά����Ϣλ���α� */

    UINT8_S logBuf[DEV_TOTAL_FRAME_LEN] = {0u};
    UINT32_S i = 0u;

    UINT16_S localName = 0u;                /* �豸���� */
    UINT8_S localType = 0u;                 /* �豸���� */
    UINT8_S localId = 0u;                  /* �豸ID */

    UINT16_S endName = 0u;                 /* �������ƣ������ATP ATO  */
    UINT8_S endId = 0u;                    /* ����Ϊһ�˻���� */
    UINT8_S sysId = 0u;                    /* ����Ϊһϵ���ϵ */

    UINT8_S pkgNum = 0u;                   /* �ܰ���  */
    UINT32_S dataLeft = 0u;                /* ʣ���ֽ���  */

    UINT8_S pkgIndex = 1u;                 /* �ְ���� */

    UINT32_S pkgHead = 0u;                 /* �ְ���ͬ���ּ�¼ */

    UINT16_S pkgMaxLen = 0u;               /* ÿһ���ְ���󳤶� */

    UINT16_S crc16 = 0u;
    UINT32_S year = 0u, month = 0u, day = 0u, hour = 0u, min = 0u, sec = 0u;

    UINT8_S localSysId = 0u;
    UINT8_S masterSysId = 0u;

    /* 20180520 ��ʱע��
    localSysId = AdptAppGetSystemId();
    masterSysId = AdptAppGetMasterId();
    */

    /*��ϵΪ��ϵ*/
    /* if(localSysId == masterSysId) */
    if(1)
    {

        /* ����׼������ */
        pkgMaxLen = DEV_TOTAL_FRAME_LEN - LOG_RECORD_HEAD_LEN;

        localName = AdptAppGetLocalName();
        localType = (UINT8_S)((localName>>8u) & 0x00FFu);
        localId = (UINT8_S)(localName & 0x00FFu);

        if ((DEVTYPE_VOBC == localType)||(DEVTYPE_ATO == localType))
        {
            /* ���豸����һ�˶��˲��ʱ */
            endName = AdptAppGetTrainName();
            endId = (UINT8_S)(endName & 0x00FFu);
        }
        else
        {
            /* ���豸������һ�˶��˲�𣬼�¼Ϊ0 */
            endId = 0u;
        }

        /* ��¼һϵ��ϵ��Ϣ */
		/* pbw 20180520 ��ʱע�� 
        sysId = (UINT8_S)AdptAppGetSystemId();
        */

        /* ����ְ����������һ�����ĳ��� */
        pkgNum = logLen / pkgMaxLen;
        dataLeft = logLen % pkgMaxLen;
        if (dataLeft > 0u)
        {
            pkgNum++;
        }

        /* ���ݴ������ */

        /* ��д�������� */
        logBuf[i++] = LOG_RECORD_TYPE;

        /* ��дЭ��汾�� */
        logBuf[i++] = LOG_RECORD_VER;

        /* ��дʱ�䣬����1970���������ʱ���� */
		/* pbw 20180520 ��ʱ���� */
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

        /* ��д�豸���� */
        logBuf[i++] = localType;

        /* ��д�г�ID */
        logBuf[i++] = localId;

        /* ��д�˺�ϵ����Ϣ */
        logBuf[i++] = (UINT8_S)((endId<<4u) + sysId);

        /* ��дԤ��λ9���ֽ�0 */
        i = i + 9u;


        /* ��дϵͳ���ں� */
        LongToChar(AdptAppCycNum(), &logBuf[i]);
        i = i + 4u;

        /* ��д�ְ����� */
        logBuf[i++] = pkgNum;

        pkgHead = i;

        while((logLen - index) > 0)
        {

            i = pkgHead;

            /* ��д�������ְ�������� */
            logBuf[i++] = pkgIndex;

            pkgIndex++;

            if ((logLen - index) > pkgMaxLen)
            {

                /* ��д��־���ݳ��ȣ����������ֶ� */
                ShortToChar(pkgMaxLen, &logBuf[i]);
                i = i + 2u;

                /* ��д��־ԭ���� */
                MemoryCpy(&logBuf[i], pkgMaxLen, &logBuff[index], pkgMaxLen);
                i = i + pkgMaxLen;
                index = index + pkgMaxLen;

            }
            else
            {
                /* ��д��־���ݳ��ȣ����������ֶ� */
                ShortToChar((logLen - index), &logBuf[i]);
                i = i + 2u;

                /* ��д��־ԭ���� */
                MemoryCpy(&logBuf[i], pkgMaxLen, &logBuff[index], (logLen - index));
                i = i + (logLen - index);
                index = index + (logLen - index);

            }

            /* ��д��־����CRCУ���� */
            crc16 = Crc16(logBuf, i);
            /* ��д��־���ݳ��ȣ����������ֶ� */
            ShortToChar(crc16, &logBuf[i]);
            i = i + 2u;

            AdptAppExtDevSndData(&logBuf[0u], i, destDevType, destDevId);

        }
    }
    else
    {
        /* logΪ��̫������ʱ��SMG��Ҫ�жϱ�ϵ������������������ݻ��� */
    }

}

