/********************************************************
*                                                                                                            
* �� �� ���� AdapterExtDevInOutManage.c   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ����㴦���ļ� 
* ��    ע�� �� 
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

DevComCirQueueStruct gAdapterSndDataQueue;        /*Atp���ⷢ���豸���ݵĴ�Ŷ���*/
DevComCirQueueStruct gAdapterRcvDataQueue;         /*Atp�����ⲿ�豸���ݵĴ�Ŷ���*/


AdptDevCfgDetailStruct gDevCfgList[PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM];   /*ͨ���豸���ýṹ������*/
UINT32_S gDevCfgNum = 0u;                                                               /*ͨ���豸���ýṹ����������Ч��Ŀ��*/

AdptMicrDevStruct gMicrDevStruct[MIC_R_DEV_NUM];         /* �������豸����Ϣ�ṹ�� */
UINT8_S gMicrDevNum = 0u;                                /* �������豸����Ŀ */

UINT8_S gMicrOutId = 1u;   /*  ��ǰ��ϵ�����ص�ID Ĭ�ϴ�1��ʼѭ�� */
UINT8_S gMicrNum = 0u;     /*  ���õķ�NTP���ص���Ŀ */

/* ���豸������� */
static UINT32_S AdapterGetDevCfgSum(void);
static UINT8_S AdapterGetDevCfgByIndex(const UINT32_S index, UINT16_S *devType, UINT8_S *devId, UINT8_S *sysId);
static UINT32_S AdapterGetDevCfgIndex(const UINT16_S devType,const UINT8_S devId,const UINT8_S sysId);

/* ��ܵ�������� */
static UINT8_S AdapterGetDevRcvPipeNum(const UINT32_S index, UINT32_S *rcvPipeNum);
static UINT8_S AdapterGetDevSndPipeIndex(const UINT32_S index, UINT32_S *sndPipeIndex);
static UINT8_S AdapterAddDevSndPipeIndex(const UINT32_S index);

/* ͨ�ö��д������ */
static UINT8_S AdapterAddDevComQueData(DevComCirQueueStruct* pCirQueueStru,const UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId);
static UINT8_S AdapterClearDevComQueData(DevComCirQueueStruct* pCirQueueStru);
static UINT32_S AdapterGetDevComQuePkgCount(DevComCirQueueStruct* pCirQueueStru);
static UINT32_S AdapterGetDevComQuePkgData(DevComCirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S*pDevType,UINT8_S* pDevId,UINT8_S* pScanFlag);
static UINT32_S AdapterScanComDevQueData(DevComCirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen, const UINT8_S destDevType, const UINT8_S destDevId);

/* �������ݶ��д������ */
static UINT8_S AdapterAddDevRcvQueData(const UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId);
static UINT8_S AdapterClearDevRcvQueData(void);
static UINT8_S AdapterGetExtDevStartIndex(void);

/* �������ݶ��д������ */
static UINT32_S AdapterGetDevSndQuePkgCount(void);
static UINT32_S AdapterGetDevSndQuePkgData(UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S* pDevType,UINT8_S* pDevId);
static UINT8_S AdapterClearDevSndQueData(void);

/* �豸ͨ��״̬��¼��� */
static void AdapterClearDevComStatus(void);
static void AdapterSetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId, const UINT8_S comFlag);

/*
* ������������ʼ���豸������Ϣ�ṹ
* ����˵���� ��
* ����ֵ  ��    1,�ɹ���0��ʧ��
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
* ������������ȡ�豸������Ϣ
* ����˵���� 
* ����ֵ  �� 1:�ɹ�  0,ʧ��
*/
UINT8_S AdapterGetDevCfgDetail(void)
{
    UINT8_S retVal = 1u;

    retVal = AdptPlatGetDevCfgDetail(PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM, gDevCfgList, &gDevCfgNum);

    return retVal;
}



/*
* ������������ȡ�豸������Ϣ����
* ����˵���� 
* ����ֵ  ���豸������Ϣ����
*/
static UINT32_S AdapterGetDevCfgSum(void)
{
    UINT32_S retVal = 0u;

    retVal = gDevCfgNum;

    return retVal;
}

/*
* ��������: ��ȡָ���������豸�������豸ID
* ���������룬
*                const UINT32_S index,�豸��Ϣ������
*                �����
*                UINT16_S * devType,�豸����
*                UIN8 *devId,Ӧ���豸ID
*                UINT8 *sysId,ϵ��
* ����ֵ: 1���ɹ���0��ʧ��
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
* ��������: ����ָ�����豸���ͣ��豸ID,ϵ�𣬻�ȡ���豸���������ñ��е����� 
* ������ ���룬
*                  UINT16_S devType,�豸����
*                  UIN8 devId,Ӧ���豸ID
*                  UINT8 sysId,ϵ��
* ����ֵ: �豸���������ñ��е�����(����ʧ�ܷ���UINT32_MAX)
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
* ��������: ��ȡָ���������豸���չܵ���Ŀ
* ���������룬
*                const UINT32_S index,�豸��Ϣ������
*       �����
*                UINT32_S *rcvPipeNum �ܵ���Ŀ
* ����ֵ: 1���ɹ���0��ʧ��
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
            /* pbw 20180520 ������ʱд�ɹ̶�ֵ1 */
			*rcvPipeNum = 1;
            retVal = 1u;
        }
    }

    return retVal;
}



/*
* ��������: ��ȡָ���������豸�������ڴ���Ĺܵ�����
* ���������룬
*                const UINT32_S index,�豸��Ϣ������
*       �����
*                UINT32_S *sndPipeIndex �ܵ�����
* ����ֵ: 1���ɹ���0��ʧ��
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
* ��������: ��ȡָ���������豸�������ڴ���Ĺܵ�����
* ���������룬
*                const UINT32_S index,�豸��Ϣ������
*       �����
*                UINT32_S *sndPipeIndex �ܵ�����
* ����ֵ: 1���ɹ���0��ʧ��
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
* ��������: ƽ̨�ⲿ�������ݹ���
* ������
* ����ֵ: ��
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

    /* �����ϵͨ��״̬��¼��־ */
    AdapterClearDevComStatus();

    devSum = AdapterGetDevCfgSum();

    ioUsrBuff.ptrMsg = recvBuf;
    ioUsrBuff.dataLen = 0u;
    ioUsrBuff.allocLen = DEV_TOTAL_FRAME_LEN;

    start = AdapterGetExtDevStartIndex();

    for(i = start;i < devSum;i++)
    {

        /* ���������ⲿͨ���豸���ñ�,��ȡ�豸���е��豸��ʶ(�豸���ͼ�ID) */
        if(1u == AdapterGetDevCfgByIndex(i, &devType, &devId, &sysId))
        {
       
            AdapterGetDevRcvPipeNum(i, &rcvPipeNum);

            /* ÿһ��ͨ��ȡ��һ�����������ݰ����͸�Ӧ�� */
            for ( j = 0u; j < rcvPipeNum; j++ )
            {
                /* ѭ�����е�ͨ�� */
                MemorySet(ioUsrBuff.ptrMsg, ioUsrBuff.allocLen, 0, ioUsrBuff.allocLen);
                ioUsrBuff.dataLen = 0;
            
                funcVal = AdptPlatUsrDataRecv(devType, devId, sysId, j, &ioUsrBuff);

                if (1u == funcVal)
                {

                    if ((DEVTYPE_MIC_R == devType)||(DEVTYPE_MIC_NTP == devType))
                    {

                        pkgIndex = 0u;

                        /* ���յ�������ȫ������Ϊ���������ݰ� */
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
                                /* ��֤����Ϊ�����ٷ��� */

                                AdapterAddDevRcvQueData(&ioUsrBuff.ptrMsg[pkgIndex], pkgLen, pkgType, pkgId);
                                pkgIndex = pkgIndex + pkgLen + 4u;
                                AdapterSetDevComStatus(pkgType,pkgId, sysId, EXT_DEV_COM_SUC);
                            }
                            else
                            {
                                AdptAppLogPrintf(1,"pkg error:%x,%d,%d\n",pkgType,pkgId,pkgLen);
                                /* ���ݲ�Ϊ���� */
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
*��������: ƽ̨�ⲿ������ݹ���
*������
*����ֵ: 
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

    /*��ȡ������ⲿ������*/
    dataPkgNum = AdapterGetDevSndQuePkgCount();

    /*��ȡ��֡����*/
    for (ii = 0u;ii < dataPkgNum;ii++)
    {
        /*��ʼ���ֲ�����*/
        MemorySet(&chOutputDataBuff[0u], sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN,0u, sizeof(UINT8_S) * DEV_TOTAL_FRAME_LEN);

        dataLen = AdapterGetDevSndQuePkgData(chOutputDataBuff, DEV_TOTAL_FRAME_LEN, &devType, &devId);

		
        if (dataLen > 0u)
        {

            micFlag = AdptPlatOutDataHandle(devType, devId, chOutputDataBuff, dataLen, outData, &outLen);

            if ( HANDLE_OUT_MICR_DEV == micFlag )
            {
                /* �豸������ */
                devType = DEVTYPE_MIC_R;
                devId = gMicrOutId;
            }
            else if ( HANDLE_OUT_MICR_NTP == micFlag )
            {
                /* �豸��NTP���� */
                devType = DEVTYPE_MIC_NTP;
            }
            else
            {
                /* �豸�������� */
            }

            /* ��ѯ�豸��ͨ�ű��еı�� */
            devIndex1 = AdapterGetDevCfgIndex((UINT16_S)devType, devId, 1u);
            devIndex2 = AdapterGetDevCfgIndex((UINT16_S)devType, devId, 2u);

            /* ��ѯ�豸�����������ڴ���Ĺܵ���� */
            AdapterGetDevSndPipeIndex(devIndex1, &sndPipeIndex1);
            AdapterGetDevSndPipeIndex(devIndex2, &sndPipeIndex2);

  /* ??? temporary revise, discuss after */
			devIndex1 = 0u;
			devIndex2 = 0u;
			sndPipeIndex1 = 0u;
			sndPipeIndex2 = 0u;

           
		
            /*��һϵ��������*/
            if(UINT32_MAX != devIndex1)
            {
                funcVal1 = AdptPlatUsrDataSend(devType,devId,1u,sndPipeIndex1,outData,outLen);

                if (1u == funcVal1)
                {
                    AdapterAddDevSndPipeIndex(devIndex1);
                }
            }
            
            /*���ϵ��������
            if(UINT32_MAX != devIndex2)
            {
                funcVal2 = AdptPlatUsrDataSend(devType,devId,2u,sndPipeIndex2,outData,outLen);

                if (1u == funcVal2)
                {
                    AdapterAddDevSndPipeIndex(devIndex2);
                }
            }
						*/

            /* ��һ�����ص�����ͨ��������֮������һ�����ص�ͨ�������� */
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
* ���������� ��Ӷ�������
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��
*              char* pDataBuf, ���ݻ�����
*              int dataLen, ���ݳ���
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
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

        MemoryCpy(pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DataBuf, DEV_TOTAL_FRAME_LEN, pDataBuf, dataLen); /* ��������� */

        /* ��¼��ӵ����ݳ��� */
        pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DataLen = dataLen;
        pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DestDevId = destDevId;
        pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DestDevType = destDevType;
        pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].scanFlag = 0u;

        /* ����β���� */
        pCirQueueStru->TailIndex++;
        /* �������ݰ����� */
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
* ���������� �����������
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
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
            /* ��¼��ӵ����� */
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
* ���������� ��ȡ�������ݰ�����
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��    
* ����ֵ  �� ���ݰ�����
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
* ���������� ��ȡ�������ݰ�
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��
*              char* pDataBuf, ���ݻ�����
*              int dataLen, ���ݳ���    
* ����ֵ  �� 0: ʧ��
*              >0: ���ݵ��ֽڳ���
*/
static UINT32_S AdapterGetDevComQuePkgData(DevComCirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S* pDevType,UINT8_S* pDevId,UINT8_S *pScanFlag)
{
    UINT32_S realDataLen = 0u; /*��¼ʵ�����ݳ���*/
    UINT32_S retVal = 0u;

    if ((pCirQueueStru != NULL) && (pDataBuf != NULL) && (dataLen > 0u)&& (pDevType != NULL)&& (pDevId != NULL)&& (pScanFlag != NULL))
    {
        if (pCirQueueStru->DataPkgCount > 0u)
        {

            /* ���ݰ���������0 */
            realDataLen = pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DataLen; /* ��¼ʵ�����ݳ��� */

            if ((realDataLen > 0u) && (dataLen >= realDataLen))
            {

                /* ʵ�����ݳ�����Ч && ��ȡ���ݻ�����������Ч && ���ݰ���������0 */
                MemoryCpy(pDataBuf, dataLen, pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DataBuf, realDataLen);
                *pDevType = pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DestDevType;
                *pDevId = pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DestDevId;
                *pScanFlag = pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].scanFlag;

                /* ��ȡ���ݺ���ͷ���� */
                pCirQueueStru->HeadIndex++;

                if (DEV_TOTAL_FRAME_NUM == pCirQueueStru->HeadIndex)
                {
                    pCirQueueStru->HeadIndex = 0u;
                }

                /* �������ݰ����� */
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
* ���������� �����豸���ͺ��豸���ɨ�赽�����е�һ������
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��
* ����ֵ  �� 0: ʧ��
*            >0: ���ݵ��ֽڳ���
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
                    /* �������ݿռ䲻�� */
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
* ���������� ��ӽ��ն�������
* ����˵���� 
*            pDataBuf, ���ݻ�����
*            dataLen, ���ݳ���
*            destDevType,�豸����
*            destDevId,�豸ID
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
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
* ���������� ˳���ȡ���ն��е�һ�����ݰ�
* ����˵���� 
*              char* pDataBuf, ���ݻ�����
*              int dataLen, ���ݳ���    
*            pDevType,�豸����
*            pDevId,�豸ID
* ����ֵ  �� 0: ʧ��
*              >0: ���ݵ��ֽڳ���
*/
UINT32_S AdapterGetDevRcvQuePkgData(UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S* pDevType,UINT8_S* pDevId)
{
    UINT32_S retVal = 0u; /*��¼ʵ�����ݳ���*/
    UINT8_S scanFlag = 0u;

    if ((pDataBuf != NULL)&&(pDevType!= NULL)&&(pDevId!= NULL))
    {
        retVal = AdapterGetDevComQuePkgData(&gAdapterRcvDataQueue, pDataBuf, dataLen, pDevType, pDevId, &scanFlag);

        /* ȷ����ȡ������û�б�ɨ������� */
        while ((retVal > 0u) && (1u == scanFlag))
        {
            /* �����ȡ�����ݱ�ɨ��������ȡ���� */
            retVal = AdapterGetDevComQuePkgData( &gAdapterRcvDataQueue, pDataBuf, dataLen, pDevType, pDevId, &scanFlag);
        }
    }
    return retVal;
}

/*
* ���������� �����豸���ͺ��豸���ɨ����ն����е�һ������
* ����˵���� pDataBuf, ���ݻ�����
*            dataLen, ���ݳ���
*            destDevType,�豸����
*            destDevId,�豸ID
* ����ֵ  �� 0: ʧ��
*            >0: ���ݵ��ֽڳ���
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
* ���������� ������ն�������
* ����˵���� 
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
*/
static UINT8_S AdapterClearDevRcvQueData(void)
{
    UINT8_S retVal = 0u;

    retVal = AdapterClearDevComQueData(&gAdapterRcvDataQueue);

    return retVal;
}

/*
* ���������� ��ӷ��Ͷ�������
* ����˵���� 
*            pDataBuf, ���ݻ�����
*            dataLen, ���ݳ���
*            destDevType,�豸����
*            destDevId,�豸ID
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
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
* ���������� ��ȡ�������ݰ�����
* ����˵����
* ����ֵ  �� ���ݰ�����
*/
static UINT32_S AdapterGetDevSndQuePkgCount()
{

    UINT32_S retVal = 0u;
    
    retVal = AdapterGetDevComQuePkgCount(&gAdapterSndDataQueue);

    return retVal;

}


/*
* ���������� ˳���ȡ���Ͷ��е�һ�����ݰ�
* ����˵���� 
*              char* pDataBuf, ���ݻ�����
*              int dataLen, ���ݳ���    
* ����ֵ  �� 0: ʧ��
*              >0: ���ݵ��ֽڳ���
*/
static UINT32_S AdapterGetDevSndQuePkgData(UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S* pDevType,UINT8_S* pDevId)
{
    UINT32_S retVal = 0u; /*��¼ʵ�����ݳ���*/
    UINT8_S scanFlag = 0u;

    if ((pDataBuf != NULL) && (pDevType != NULL) && (pDevId != NULL))
    {
        retVal = AdapterGetDevComQuePkgData(&gAdapterSndDataQueue, pDataBuf, dataLen, pDevType, pDevId, &scanFlag);

        /* ȷ����ȡ������û�б�ɨ������� */
        while ((retVal > 0u) && (1u == scanFlag))
        {
            /* �����ȡ�����ݱ�ɨ��������ȡ���� */
            retVal = AdapterGetDevComQuePkgData( &gAdapterSndDataQueue, pDataBuf, dataLen, pDevType, pDevId, &scanFlag);
        }
    }

    return retVal;
}


/*
* ���������� ������Ͷ�������
* ����˵���� 
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
*/
static UINT8_S AdapterClearDevSndQueData(void)
{
    UINT8_S retVal = 0u;

    retVal = AdapterClearDevComQueData(&gAdapterSndDataQueue);

    return retVal;
}


/*
* ���������� ��ȡ�ⲿ�豸���豸���ñ��е���ʼλ�� 
* ����˵���� 
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
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
* ��������������豸��ͨ��״̬��¼��־
* ����˵������
* ����ֵ  ��    ��
*/
static void AdapterClearDevComStatus(void)
{
    MemorySet(gMicrDevStruct, sizeof(gMicrDevStruct), 0u, sizeof(gMicrDevStruct));
    gMicrDevNum = 0u;
}

/* 
* ���������������豸��ͨ��״̬��¼��־
* ����˵����devType �豸����
*          devId �豸ID
*           sysId ϵ��
*           comFlag ͨ��״̬��¼��־
* ����ֵ  ��    ��
*/
static void AdapterSetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId, const UINT8_S comFlag)
{
    UINT8_S i = 0u;
    
    for (i = 0u;i < gMicrDevNum;i++)
    {
        /* �жϲ��ҵ��Ѿ��չ����ݵ��豸 */
        if ((devType == gMicrDevStruct[i].devType) && (devId == gMicrDevStruct[i].devId) && (sysId == gMicrDevStruct[i].sysId))
        {
            gMicrDevStruct[i].comFlag = comFlag;
            break;
        }
    }

    /* �ж�û�չ����ݵ����豸 */
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
* ������������ȡ�豸��ͨ��״̬��¼��־
* ����˵���� devType �豸����
*           devId �豸ID
*           sysId ϵ��
* ����ֵ  ��    1 ������ 0 ������
*/
UINT8_S AdapterGetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId)
{
    UINT8_S comFlag = 0u;
    UINT8_S i = 0u;

    for (i = 0u;i < gMicrDevNum;i++)
    {
        /* �жϲ��ҵ��Ѿ��չ����ݵ��豸 */
        if ((devType == gMicrDevStruct[i].devType) && (devId == gMicrDevStruct[i].devId) && (sysId == gMicrDevStruct[i].sysId))
        {
            comFlag = gMicrDevStruct[i].comFlag;
            break;
        }
    }

    return comFlag;
}

/* 
* �������������÷�NTP���ص�����
* ����˵����micrNum �����豸������
* ����ֵ  ��    ��
*/
void AdapterSetMicrNum(const UINT8_S micrNum)
{
    gMicrNum = micrNum;
}


