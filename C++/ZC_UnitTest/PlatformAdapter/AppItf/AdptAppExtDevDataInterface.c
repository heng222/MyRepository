/********************************************************
*                                                                                                            
* �� �� ���� AdptAppExtDevDataInterface.c   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ������Ӧ�ò�ͨ�Žӿڽṹ����Ľӿ��ļ� 
* ��    ע�� �� 
*
********************************************************/ 

#include "AdptAppExtDevDataInterface.h"
#include "../AdptHandle/AdapterExtDevInOutManage.h"
#include "../AppItf/AdptAppCommonDef.h"
#include "../AppItf/AdptAppServiceInterface.h"
#include "../PlatItf/AdptPlatServiceInterface.h"
#include "../../Common/MemSet.h"
#include "../PlatformLog/AdapterLog.h"

/* �豸��Ӧͨ��Э�����ñ� */
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

/* �豸��Ӧͨ��Э�����ñ����Ŀ */
static UINT32_S gComDevProCount = sizeof(gComDevProStruct)/sizeof(ComProCfgStruct);


static UINT8_S AdapterSndDataProtocol(UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId);
static UINT32_S AdapterRcvDataProtocol(UINT8_S* pInBuf, const UINT32_S inLen, UINT8_S* pOutBuf, const UINT32_S outMaxLen, UINT8_S devType, UINT8_S devId);

static UINT8_S AdapterGetDevProType(UINT8_S comSrcType, UINT8_S comDstType, UINT8_S * comProType);

/*
* ����������Ӧ�÷������ݽӿ� 
* ����˵���� 
*              UINT8_S* pDataBuf, ���ݻ����� 
*              UINT32_S dataLen, ���ݳ��� 
*             UINT8_S destDevType �豸���� 
*             UINT8_S destDevId �豸ID 
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
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
* ���������� Э�鴦��������
* ����˵���� 
*              UINT8_S* pDataBuf, ���ݻ�����
*              UINT32_S dataLen, ���ݳ���
*             UINT8_S destDevType �豸���� 
*             UINT8_S destDevId �豸ID 
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
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
    UINT16_S outTsdLen = 0u;               /*Ӧ��֡�ĳ���*/
    UINT8_S outTsdBuf[DEV_TOTAL_FRAME_LEN] = {0u}; /*Ӧ��֡*/
    UINT16_S outSseLen = 0u;                /*��ʱ����֡�ĳ���*/
    UINT8_S outSseBuf[DEV_TOTAL_FRAME_LEN] = {0u};  /*��ʱ����֡*/
    UINT16_S outSsrLen = 0u;                /*��ʱӦ��֡�ĳ���*/
    UINT8_S outSsrBuf[DEV_TOTAL_FRAME_LEN] = {0u};  /*��ʱӦ��֡*/

    if (pDataBuf != NULL)
    {

        localName = AdptAppGetLocalName();
        localType = (UINT8_S)((localName>>8u) & 0x00FFu);

        /*��ʼ���ֲ�����*/
        MemorySet(&outTsdBuf[0u], sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN, 0u, sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN);
        MemorySet(&outSseBuf[0u], sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN, 0u, sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN);
        MemorySet(&outSsrBuf[0u], sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN, 0u, sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN);

        /* ��ѯͨ���豸֮���Ƿ���ҪЭ�� */
        if ( 1 == AdapterGetDevProType(localType, destDevType, &proType) )
        {
            switch (proType)
            {

                case COM_WITHOUT_PRO:

                    AdapterAddDevSndQueData(pDataBuf, dataLen, destDevType, destDevId);
                    retVal = 1u;
                    break;

                case COM_WITH_RSSP:

                    /* ͨ���豸֮����ҪЭ�������Э�鴦�� */
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
                        /* ��������֡�Ͷ�ʱ֡����2 */ 

                        AdapterAddDevSndQueData(outTsdBuf, outTsdLen, destDevType, destDevId);

                        AdapterAddDevSndQueData(outSseBuf, outSseLen, destDevType, destDevId);

                        AdapterAddDevSndQueData(outSsrBuf, outSsrLen, destDevType, destDevId);
                    }
                    else if(RSSP_PACK_TSD == proResult )
                    {

                        /* ֻ��������֡, �Ѵ��TSD������3 */
                        AdapterAddDevSndQueData(outTsdBuf, outTsdLen, destDevType, destDevId);
                    }
                    else
                    {

                        /*Э����ʧ��*/
                        AdptAppLogPrintf(1u, "RSSP pack error:%d\n", proResult);
                    }

                    retVal = 1u;
                    break;

                default:
                    /*Э���ѯʧ��*/
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
* ����������Ӧ�ý������ݽӿ�
*   �����е��������������еģ�ÿһ��ͨ�Ű��ÿһ��ͨ������һ������
*   ��Ҫ���ղ�ͬ�豸���࣬���ֳ���Э������ݽ���ͨ��������ͨ�Ű�����ݶ�����Ϊһ��������Э��Ĳ��ܺϳ�һ��
*
* ����˵���� 
*              UINT8_S* pDataBuf, ���ݻ�����
*              UINT32_S dataLen, ���ݻ���������
*             UINT8_S *pDevType �豸���� 
*             UINT8_S *pDevId �豸ID 
*
* ����ֵ  �� 
*            >0 �ҷ�0xFFFFFFFF:  ȡ���ݳɹ��ҿ��Լ���ȡ���� 
*            0xFFFFFFFF:  ��ȡ�����ݵ�������Ϊ��Ч����Э�����ʧ�ܿ��Լ���ȡ���� 
*            0: �����Ѿ�ȫ��ȡ�� 
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

        /* ���Ȼ�ȡһ֡���ݣ�ȷ�ϵ�ǰ������豸���� */
        tmpLen = AdapterGetDevRcvQuePkgData( tmpBuf, DEV_TOTAL_FRAME_LEN, &devType, &devId);

        if (tmpLen > 0u)
        {

            /* Э�鴦������ */
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
* ���������� Э�鴦���������
*   �����е��������������еģ�ÿһ��ͨ�Ű��ÿһ��ͨ������һ������
*   ��Ҫ���ղ�ͬ�豸���࣬���ֳ���Э������ݽ���ͨ��������ͨ�Ű�����ݶ�����Ϊһ��������ҪЭ��Ĳ�����
*
* ����˵���� 
*              char* pDataBuf, ���ݻ�����
*              int dataLen, ���ݻ���������
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
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

        /* ��ѯͨ���豸֮���Ƿ���ҪЭ�� */
        if ( 1u == AdapterGetDevProType(localType, devType, &proType) )
        {

            switch (proType)
            {

                case COM_WITHOUT_PRO:

                    /* ���ڲ���ҪЭ������ݣ���Ҫֻȡ��һϵ�����ݸ�Ӧ��*/
                    /* ��֮ǰ�Ѿ�ȡ�������ݰ����͸�Ӧ�� */

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

                    /* rsspЭ��Ҫ�����ݴ��һ����д��������Ҫѭ��ɨ����ȡ��ȫ�������ݺͳ�Ϊһ�� */

                    if (inLen <= DEV_TOTAL_FRAME_LEN)
                    {
                        /* �Ƚ�֮ǰ��ȡ�ĵ�һ�����ݷ��������ݻ����� */
                        MemoryCpy(&totalBuf[0u], DEV_TOTAL_RCV_FRAME_LEN, &pInBuf[0u], inLen);
                        totalLen = inLen;

                        /* ���ջ�ȡ�ĵ�һ�����ݵ��豸����ȫ��ɨ�����ݣ���������Ϊһ������ */
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
                                /* ���õĴ洢�ռ䲻�� */
                                break;
                            }

                            tmpLen = AdapterScanDevRcvQueData( &tmpBuf[0u], DEV_TOTAL_FRAME_LEN, devType, devId);
                        }
                    }
                    else
                    {
                        /* ���õĴ洢�ռ䲻�� */
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

                        /*�����ȷ��״ֵ̬Ϊ1,��·�����Ŵ���*/
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
                                /* Э�鴦��󳤶ȴ��� */
                                retLen = 0u;
                            }
                        }
                        else
                        {
                            /* Э�鴦��ʧ�� */
                            retLen = 0u;
                        }
                    }
                    else
                    {
                        /* û�л����Ҫ��������� */
                        retLen = 0u;
                    }

                    break;
            
                default:

                    /* �����ڿ��Դ�������� */
                    AdptAppLogPrintf(1u, "unknow protocol type:%d\n", proType);

                    retLen = 0u;

                    break;
            }

        }
        else
        {
            /* �޷���ù���Э��������Ч����Ϣ */
            retLen = 0u;
        }

    }
    return retLen;
}


/*
*��������: ����Դ�豸���ͺ�Ŀ���豸���ͻ�ȡ�豸ͨ��Э���־λ
*������
*����ֵ: 0 ʧ�� 1 �ɹ�
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
                /* ����ѭ������ */
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
* ������������ȡ�豸��ͨ��״̬��¼��־
* ����˵����
* ����ֵ  ��    1 ������ 0 ������
*/
UINT8_S AdptAppGetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId)
{
    UINT8_S comFlag = 0u;

    comFlag = AdapterGetDevComStatus(devType, devId, sysId);

    return comFlag;
}

