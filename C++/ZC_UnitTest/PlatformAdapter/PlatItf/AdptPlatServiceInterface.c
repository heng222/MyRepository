/********************************************************
* 
* �� �� ���� AdptPlatServiceInterface.c
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01 
* ���������� ������ṩ��ƽ̨��ĵײ�����⺯���Ľӿ��ļ�  
* ��    ע�� �� 
* 
********************************************************/ 

#include "AdptPlatServiceInterface.h"
#include "../../cspadpt/Vcp_Service_Interface.h"
#include "../../cspadpt/Vcp_Service_TestInterface.h"
#include "../../cspadpt/Vcp_Track_Interface.h"
#include "../AdptHandle/AdapterCommonDef.h"
#include "../../Common/MemSet.h"
#include "../../Common/Copy.h"
#include "../../Common/Convert.h"
#include "../../Common/Crc32.h"
#include "../PlatItf/AdptPlatServiceInterface.h"
#include "../AppItf/AdptAppServiceInterface.h"
#include "../AdptHandle/AdapterExtDevInOutManage.h"
#include "../AppItf/AdptAppCommonDef.h"
/*#include "../../cspadpt/Rsp1.h"*/

/*
* �������������ݲ�ͬ�豸��Ҫ������ݽ������⴦��
*           �����ATPĳЩͨ�Ŷ���Ҫ����������ͷ
* ����˵���� ��
* ȫ�ֱ����� 
* ����ֵ  �� 1 �����ط�NTP���ݣ���������
*           2 ������NTP���ݣ���������
*           0 �����������ݣ����账��
*/
UINT8_S AdptPlatOutDataHandle(UINT32_S inDevType, UINT32_S inAppId, const UINT8_S* inData, UINT32_S inLen, UINT8_S outData[], UINT32_S *pOutLen)
{
    UINT32_S index = 0u;
    UINT16_S localName = 0u;
    UINT8_S localType = 0u;
    UINT32_S crcValue = 0u;
    UINT8_S retVal = HANDLE_OUT_NOT_MICR;

    if (( NULL != inData ) && (NULL != outData) && (NULL != pOutLen))
    {

        localName = AdptAppGetLocalName();
        localType = (UINT8_S)((localName>>8u) & 0x00FFu);

        if ((localType == DEVTYPE_VOBC) && ((DEVTYPE_CI == inDevType) || 
            (DEVTYPE_ZC == inDevType) || (DEVTYPE_ATS == inDevType)|| 
            (DEVTYPE_NTP == inDevType) || (DEVTYPE_NMS == inDevType)))
        {

            /* �������ص�����ATP�����ĳЩ�豸��Ҫ�����ĸ��ֽ�ͷ���ĸ��ֽ�β */

            outData[index++] = (UINT8_S)inDevType;
            outData[index++] = (UINT8_S)inAppId;

            ShortToChar(inLen, &outData[index]);
            index += 2u;

            MemoryCpy(&outData[index], DEV_TOTAL_FRAME_LEN, inData, inLen); /*����Ҫ������ݿ�������ʱ������*/

            index = inLen + index;

            crcValue = Crc32(outData, index);

            LongToChar(crcValue, &outData[index]);

            *pOutLen = index + 4u;

            if(DEVTYPE_NTP == inDevType)
            {
                retVal = HANDLE_OUT_MICR_NTP;
               }
            else
            {
                retVal = HANDLE_OUT_MICR_DEV;
               }

        }
        else
        {
            MemoryCpy(outData, DEV_TOTAL_FRAME_LEN, inData, inLen); /*����Ҫ������ݿ�������ʱ������*/
            *pOutLen = inLen;
            retVal = HANDLE_OUT_NOT_MICR;
        }

    }

    return retVal;

}

/*
* ������������ȡ�豸������Ϣ
* ����˵���� 
* ����ֵ  �� 1:�ɹ�  0,ʧ��
*/
UINT8_S AdptPlatGetDevCfgDetail(const UINT32_S inListLen, AdptDevCfgDetailStruct outDevCfgDetailList[], UINT32_S* outDevNum)
{
    UINT8_S retVal = 1u;
    UINT32_S funcVal = 0u;
    UINT32_S devCfgNum = 0u;
    UINT32_S ii = 0u;
    UINT8_S micrNum = 0u;

    T_DevCfgDetail devCfgList[PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM];

    MemorySet(devCfgList, PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM * sizeof(T_DevCfgDetail),
        0u,PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM * sizeof(T_DevCfgDetail));
    devCfgNum = 0u;
    
    if((NULL == outDevCfgDetailList) || (NULL  == outDevNum))
    {
        retVal = 0u;
        
    }

    if(1u == retVal)
    {
        funcVal = F_VCP_GetDevCfgDetail(PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM, devCfgList, &devCfgNum);
        if(funcVal > devCfgNum)
        {
            /*�����ļ��е��豸��������Ҫ��ȡ���豸����(�ռ䲻��)*/
            retVal = 0u;
        }
    }

    if(1u == retVal)
    {
        if(inListLen < devCfgNum )
        {
            /*outDevCfgDetailList�Ŀռ䲻��*/
            retVal = 0u;
        }
    }

    
    if(1u == retVal)
    {
        for(ii = 0u; ii < devCfgNum;ii++)
        {
            outDevCfgDetailList[ii].devType = devCfgList[ii].BasicInfo.DevType;
            outDevCfgDetailList[ii].devId = devCfgList[ii].BasicInfo.AppId;
            outDevCfgDetailList[ii].devSysId = devCfgList[ii].BasicInfo.AccSys;

            outDevCfgDetailList[ii].rcvPipeNum = devCfgList[ii].ExInfo.RecvNum;
            outDevCfgDetailList[ii].sndPipeNum = devCfgList[ii].ExInfo.SendNum;
            outDevCfgDetailList[ii].sndPipeIndex = 0u;

            if (DEVTYPE_MIC_R == devCfgList[ii].BasicInfo.DevType)
            {
                micrNum++;
            }

        }
        *outDevNum = devCfgNum;

        AdapterSetMicrNum(micrNum);

    }

    return retVal;
}



/*
* ��������: ���ָ���豸������ ʹ��ƽ̨�ṩ����ǿ�ͽӿ� 
* ������
*            ����:
*            inDevType : �����豸���߼�����
*            inAppId   : �����豸��Ӧ��ID
*            inDevSys  : �����豸������ϵ��
*            inPipeId: ��������ͨ����
*            ioUsrBuff: ioUsrBuff ->ptrMsg,���ջ�������ַ
*                           ioUsrBuff ->allocLen,���ջ�����ÿռ�
*            ���:
*            ioUsrBuff: ioUsrBuff ->ptrMsg,���ջ�������ַ
*                         ioUsrBuff ->dataLen,���յ������ݳ���
*����ֵ: 1���ɹ���0��ʧ��
*/

UINT8_S AdptPlatUsrDataRecv(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  const UINT32_S inPipeId,
                                  AdptUsrBuffStruct* ioUsrBuff)
{
    UINT8_S retVal = 0u;
    UINT8_S rcvDataBuff[DEV_TOTAL_FRAME_LEN] = {0u};

    T_UsrBuff  vcpBuff;
    E_UsrRxStatus rtnValue;

    vcpBuff.ptrMsg = rcvDataBuff;
    vcpBuff.dataLen = 0u;
    vcpBuff.allocLen = DEV_TOTAL_FRAME_LEN;

    if(NULL == ioUsrBuff)
    {
        retVal = 0u;
    }
    else
    {
        rtnValue = F_VCP_UsrDataRecvEx(inDevType, inAppId, inDevSys, inPipeId, &vcpBuff);
		
        if(e_UsrRxLcAppNew == rtnValue)
        {
            if(ioUsrBuff->allocLen > vcpBuff.dataLen)
            {
                MemoryCpy(ioUsrBuff->ptrMsg,ioUsrBuff->allocLen,vcpBuff.ptrMsg,vcpBuff.dataLen);
                ioUsrBuff->dataLen = vcpBuff.dataLen;
                retVal = 1u;
            }
            else
            {
                /*�ռ䲻��*/
                retVal = 0u;
            }

        }
        else
        {
            /*δ���յ�����*/
            retVal = 0u;
        }

    }

    return retVal;
}


/*
* ��������: ��ָ���豸�������� ʹ��ƽ̨�ṩ����ǿ�ͽӿ�
* ������
*            ����:
*            inDevType : �����豸���߼�����
*            inAppId   : �����豸��Ӧ��ID
*            inDevSys  : �����豸������ϵ��
*            inPipeId: ��������ͨ����
*            inData:���뷢�ͻ�������ַ
*            dataLen:���뷢�����ݳ���
*            ���:
*            ��
*����ֵ: 1���ɹ���0��ʧ��
*/

UINT8_S AdptPlatUsrDataSend(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  const UINT32_S inPipeId,
                                  const UINT8_S*  inData,
                                  const UINT32_S dataLen)
{

    UINT8_S retVal = 1u;/*��������ֵ*/
    E_UsrTxStatus sndResult = e_UsrTxErrData;

    if ( (NULL == inData) || (0u == dataLen) )
    {
        retVal = 0u;
    }
    else
    {

        sndResult = F_VCP_UsrDataSendEx(inDevType, inAppId, inDevSys, inPipeId, inData, dataLen);

        if (e_UsrTxSuccess == sndResult)
        {
            retVal = 1u;
        } 
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}




/*
* ����������ͨ��ƽ̨ǰ��巢�͵�������(ͨ������)
* ����˵���� 
*                           ���룬const UINT8_S* const inData�����ͻ����� const UINT32 inDataLen���������ݳ���
*                           �������
* ����ֵ  �� 1:�������ҷ��ͳɹ�  0,(����ʧ�� || ���ͻ�������ַΪNULL || ���ͳ���Ϊ0)
*/

UINT8_S AdptPlatUsrDataWatch(const UINT8_S* const inData,
                                    const UINT32_S inDataLen)
{
    UINT8_S retVal = 1u;
    E_SysBool valFVcp = e_TRUE;

    if((NULL != inData) && (0u != inDataLen))
    {
         valFVcp = F_VCP_UsrDataWatch(inData,inDataLen);
         if(e_TRUE == valFVcp)
         {
            retVal = 1u;
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
* ������������ϵͬ��ʱ��ϵ�����ݽ��սӿں���
* ����˵��������:
*                            AdptCellMsgStruct* const ioMsg
*                            ioMsg.ptrMsg,�������ݻ�����
*                            ioMsg.dataLen ,���ջ��������ÿռ�
*                            ��� :
*                            AdptCellMsgStruct* const ioMsg
*                            ioMsg.ptrMsg,�������ݴ�Ż�����
*                            ioMsg.dataLen ,�������ݳ���
*
* ����ֵ      :  1,�ɹ� ��0��ʧ��
*/
UINT8_S AdptPlatUsrDataRecvMutual(AdptCellMsgStruct* const ioMsg)
{
    UINT8_S retVal = 1u;
    E_UsrRxStatus result = e_UsrRxLcEmpty;
    T_CellMsg rcvMsg;
    UINT8_S buff[DEV_TOTAL_FRAME_LEN] = {0u};

    rcvMsg.ptrMsg = buff;
    rcvMsg.dataLen = 0u;

    if(NULL == ioMsg)
    {
        retVal = 0u;
    }

    if(1u == retVal)
    {
        result = F_VCP_UsrDataRecvMutual(&rcvMsg);

        if(e_UsrRxLcAppNew != result)
        {
            /*δ���յ�����*/
            retVal = 0u;
        }
    }

    if(1u == retVal)
    {
        if(ioMsg->dataLen < rcvMsg.dataLen)
        {
            /*�ռ䲻��*/
            retVal = 0u;
        }
    }

    if(1u == retVal)
    {
        MemoryCpy(ioMsg->ptrMsg,DEV_TOTAL_FRAME_LEN,rcvMsg.ptrMsg,rcvMsg.dataLen);
        ioMsg->dataLen = rcvMsg.dataLen;
    }

    return retVal;
}


/*
* ������������ϵͬ��ʱ��ϵ�����ݷ��ͽӿں���
* ����˵��������,
*                            const void* const inData���������ݻ�����
*                            const UINT32 inDataLen,�������ݳ���
* ����ֵ      :  1,�ɹ� ��0��ʧ��
*/

UINT8_S AdptPlatUsrDataSendMutual(const void* const inData, const UINT32_S inDataLen)
{
    UINT8_S retVal = 1u;
    E_SysBool sndResult;

    if(NULL == inData )
    {
        retVal = 0u;
    }

    if(1u == retVal)
    {
        sndResult = F_VCP_UsrDataSendMutual(inData, inDataLen);

        if (e_TRUE == sndResult)
        {
            retVal = 1u;
        } 
        else
        {
            retVal = 0u;
        }
    }
    return retVal;
}




/*
* ������������ʹƽ̨崻��Ľӿں���
* ����˵����const UINT32 errNo ����Ҫ��¼�Ĵ�����
* ����ֵ      :  ��
*/
void AdptPlatUsrHaltSystem(const UINT32_S inErrCode)
{
    F_VCP_UsrHaltSystem(inErrCode);
}



/*
* ������������ȡ�豸״̬
* ����˵���� 
*                           ���룬const UINT8_S devType���豸����; const UINT8_S devId���豸ID;const UINT8_S sysId,�豸ID
*                           �������
* ����ֵ  �� �豸״̬

*/

UINT8_S AdptPlatInquiryDevStatus(const UINT32_S devType,const UINT32_S devId,const UINT32_S sysId)
{
    UINT8_S retVal = DEV_STATE_NORMAL;

    T_SysDevInf devStaStr;

    devStaStr = F_VCP_InquiryDevStatus(devType,devId,sysId);

    if(e_SysDevNotExist == devStaStr.Status)
    {
        retVal = DEV_STATE_EXIST_NO;
    }
    else if(e_SysDevInit == devStaStr.Status)
    {
        retVal = DEV_STATE_INIT;
    }
    else if(e_SysDevNormal == devStaStr.Status)
    {
        retVal = DEV_STATE_NORMAL;
    }
    else if(e_SysDevTesting == devStaStr.Status)
    {
        retVal = DEV_STATE_SELFCHECK;
    }
    else if(e_SysDevFault == devStaStr.Status)
    {
        retVal = DEV_STATE_FAULT;
    }
    else
    {
        retVal = DEV_STATE_FAULT;
    }

    return retVal;
}


/*
* ������������ȡƽ̨���ڿ�ʼϵͳʱ�ӵĽӿں���
* ����˵���� 
*                         ���룬��
*                         �����
*                         UINT32 *sec����
*                         UINT32 * msec, ����
* ����ֵ  �� ��
*/
void AdptPlatSystemClkGet(UINT32_S *sec, UINT32_S *msec)
{
    T_SysClk outSysClk;

    if((NULL != sec ) && (NULL != msec))
    {
        F_VCP_SystemClkGet(&outSysClk);
        *sec = outSysClk.Sec;
        *msec = (UINT32_S)((FLOAT32_S)outSysClk.uSec * 0.001);
    }

}


/*
* ������������ȡϵͳ����ʱ��Ľӿں���
* ����˵���� 
*                           ���룬��
*                           �����
*                                UINT32 *year����
*                                UINT32 * month, ��
*                                UINT32 * day,     ��
*                                UINT32 *hour,     ʱ
*                                UINT32 *min,      ��
*                                UINT32 *sec,      ��
*                                (��Чֵ:0xFFFF)
* ����ֵ  �� ��
*/
void  AdptPlatCalendarClkGet(UINT32_S *year, UINT32_S * month, UINT32_S * day, UINT32_S *hour, UINT32_S *min, UINT32_S *sec)
{

    T_CalendarClk outClk;
    if((NULL != year ) && (NULL != month )&& (NULL != day )&& (NULL != hour )&& (NULL != min )&& (NULL != sec ))
    {
        if(e_TRUE == F_VCP_CalendarClkGet(&outClk))
        {
            *year = outClk.Year;
            *month = outClk.Mon;
            *day = outClk.Day;
            *hour = outClk.Hour;
            *min = outClk.Min;
            *sec = outClk.Sec;
        }
        else
        {
            *year = 0xFFFFu;
            *month = 0xFFFFu;
            *day = 0xFFFFu;
            *hour = 0xFFFFu;
            *min = 0xFFFFu;
            *sec = 0xFFFFu;
        }

    }

}

/*
* ���������� ����ϵͳ����ʱ��ӿں���
* ����˵���� 
*                           ���룬
*                                UINT32 year����
*                                UINT32 month, ��
*                                UINT32 day,     ��
*                                UINT32 hour,     ʱ
*                                UINT32 min,      ��
*                                UINT32 sec,      ��
*                           �������
* ����ֵ  �� 1���ɹ�  0��ʧ��
*/

UINT8_S AdptPlatCalendarClkSet(UINT32_S year, UINT32_S month, UINT32_S day, UINT32_S hour, UINT32_S min, UINT32_S sec)
{
    UINT8_S retVal = 0;

    T_CalendarClk inClk;

    inClk.Year = year;
    inClk.Mon = month;
    inClk.Day= day;
    inClk.Hour= hour;
    inClk.Min= min;
    inClk.Sec = sec;

    if(e_TRUE == F_VCP_CalendarClkSet(&inClk))
    {
        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }

    return retVal;

}


/*
* ������������ȡ��ǰ����ϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)�ӿں���
* ����˵���� ��
* ȫ�ֱ����� 
* ����ֵ  �� ��ǰ����ϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)
*/

UINT32_S AdptPlatGetSystemId(void)
{
    UINT32_S sysId = 0u;

    F_VCP_GetSystemId(&sysId);           /*��ȡ��ϵϵ��:0x01 ,Iϵ;0x02,IIϵ*/

    return sysId;
}

/*
* ������������ȡ��ϵϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)�ӿں���
* ����˵���� ��
* ȫ�ֱ����� 
* ����ֵ  ��  ��ϵϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)
*/
UINT32_S AdptPlatGetMasterId(void)
{
    UINT32_S masterId = 0u;

    F_VCP_GetMasterId(&masterId);           /*��ȡ��ϵϵ��:0x01 ,Iϵ;0x02,IIϵ*/

    return masterId;
}

/*
* �����������ṩ��Ӧ�õ���ע��ӿں���
* ����˵����const UINT32 inMaxLen, ע����󵹻����ݳ���;
*                            const UINT32 inInterval,ע��ǿ�Ƶ������ڼ��;
*                            AdptTrackDataGet inDataGet, ע���ȡUSR�������ݺ���
*                            AdptTrackDataSet inDataSe,tע������USR�������ݺ���
* ����ֵ      :    1,�ɹ� 0,ʧ��
*/
UINT8_S AdptPlatTrackRegister(const UINT32_S inMaxLen, const UINT32_S inInterval,
                   AdptTrackDataGet inDataGet, AdptTrackDataSet inDataSet)
{
    UINT8_S retVal = 0u;
    E_SysBool FuncVal = e_FALSE;

    if((NULL != inDataGet) && (NULL != inDataSet))
    {
        FuncVal =  F_VCP_TrackRegister(inMaxLen,inInterval,(F_TrackDataGet)inDataGet,(F_TrackDataSet)inDataSet);
        if(e_TRUE == FuncVal)
        {
            retVal = 1u;
        }
        else
        {
            retVal = 0u;
        }
    }

    return retVal;

}


/*
* ������������ȡƽ̨���ںŵĽӿں���
* ����˵������
* ����ֵ      :    ƽ̨���ں�
*/
UINT32_S AdptPlatCycNum(void)
{
    UINT32_S cycleNum = 0u;

    cycleNum = F_VCP_Test_GetCycleNum();

    return cycleNum;
}


/*
* ����������RsspЭ����г�ʼ�� 
* ����˵����selfDevId�����豸����inCfgLen�������ݳ��ȣ�inCfgBuf�������ݻ����� 
* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptPlatRsspInit(const UINT16_S selfDevId, const UINT16_S inCfgLen, UINT8_S *inCfgBuf)
{
    UINT8_S retVal = 1u;
#if 0 /* TODO INIT RSSP */
    E_Bool temp = r_FALSE;

    UINT16_S i = 0;

    if (inCfgBuf != NULL)
    {

        temp = Rsp1_Init((const UShort)selfDevId, (const UShort)inCfgLen, (UTiny *)inCfgBuf);

        if (r_TRUE == temp)
        {
            retVal = 1u;
        }
        else
        {
            retVal = 0u;
        }
    }
#endif
    return retVal;
}


/*
* ����������RsspЭ���������ʱ�� 
* ����˵������
* ����ֵ      :    ��
*/
void AdptPlatRsspUpdateClock(void)
{
#if 0
    Rsp1_UpdateClock();
#endif
    return;
}

/*
* ����������RsspЭ���ȡͬ������
* ����˵����bufͬ�����ݻ����� 
* ����ֵ      :    ͬ�����ݳ��� 
*/
UINT16_S AdptPlatRsspGetSynData(UINT8_S *buf)
{
    UINT16_S retVal = 0u;
#if 0	/* TODO: Get status data of rssp */
    if (buf != NULL)
    {
        retVal = (UINT16_S)Rsp1_GetSynData((UTiny *)buf);
    }
#endif
    return retVal;
}

/*
* ����������RsspЭ�鴫��ͬ������
* ����˵����bufͬ�����ݻ����� ,���ݳ��� 
* ����ֵ      :    ͬ�����ݳ��� 
*/
void AdptPlatRsspSetSynData(UINT8_S *buf, UINT16_S len)
{
#if 0	/* TODO:sys rssp data */
    if (buf != NULL)
    {
        Rsp1_SetSynData((UTiny *)buf, (const UShort)len);
    }
#endif
    return;
}

/*
* ����������RsspЭ�������� 
* ����˵����inDstDevId�豸����inLen���볤�ȣ�inBuf�������ݣ�
*                     outTsdLenӦ�����ݳ��ȣ�outTsdBufӦ�����ݣ�outSsLen��ʱ֡���ȣ�outSsBuf��ʱ֡����
* ����ֵ      :    0���ʹ���1 ���ȴ���2δ���TSD��3�Ѵ��TSD 
*/
UINT8_S AdptPlatRsspPackData(const UINT16_S inDstDevId, const UINT16_S inLen, UINT8_S *inBuf,
        UINT16_S *outTsdLen, UINT8_S *outTsdBuf,UINT16_S *outSseLen, UINT8_S *outSseBuf,UINT16_S *outSsrLen, UINT8_S *outSsrBuf)
{
    UINT8_S proResult = 1u;
#if 0 /* TODO: Snd data by rssp */
    S_Msg inMsg;
    S_Msg outMsg;
    S_SsMsg outSseMsg;
    S_SsMsg outSsrMsg;

    if ((inBuf != NULL)&&(outTsdLen != NULL)&&(outTsdBuf != NULL)&&(outSseLen != NULL)&&(outSseBuf != NULL)&&(outSsrLen != NULL)&&(outSsrBuf != NULL))
    {
        MemorySet(&inMsg, sizeof(S_Msg), 0u, sizeof(S_Msg));
        MemorySet(&outMsg, sizeof(S_Msg), 0u, sizeof(S_Msg));
        MemorySet(&outSseMsg, sizeof(S_SsMsg), 0u, sizeof(S_SsMsg));
        MemorySet(&outSsrMsg, sizeof(S_SsMsg), 0u, sizeof(S_SsMsg));

        if (0u == MemoryCpy(&inMsg.buff, c_BUFF_SIZE, inBuf, inLen))
        {
            inMsg.length = inLen;

            proResult = (UINT8_S)Rsp1_PackageData(inDstDevId, &inMsg, &outMsg, &outSseMsg, &outSsrMsg);

            MemoryCpy(outTsdBuf, DEV_TOTAL_FRAME_LEN, &outMsg.buff[0u], outMsg.length);
            *outTsdLen = outMsg.length;

            MemoryCpy(outSseBuf, DEV_TOTAL_FRAME_LEN, &outSseMsg.buff[0u], outSseMsg.length);
            *outSseLen = outSseMsg.length;

            MemoryCpy(outSsrBuf, DEV_TOTAL_FRAME_LEN, &outSsrMsg.buff[0u], outSsrMsg.length);
            *outSsrLen = outSsrMsg.length;
        }
        else
        {
            /* �ڴ治�㣬�ݲ����� */
        }

    }
#endif
    return proResult;
}

/*
* ����������RsspЭ��������  
* ����˵����inDstDevId�豸����inLen���볤�ȣ�inBuf�������ݣ�
*                     outLenӦ�����ݳ��ȣ�outBufӦ������ 
* ����ֵ      :    0���ʹ���1 ���ȴ���2 SSE or SSR��3 RSD 
*/
UINT8_S AdptPlatRsspParseData(const UINT16_S inDstDevId, const UINT16_S inLen, UINT8_S *inBuf,
        UINT16_S *outLen, UINT8_S *outBuf)
{
    UINT8_S proRet = 0u;
#if 0 /* TODO: rcv data */
    if ((inBuf != NULL)&&(outLen != NULL)&&(outBuf != NULL))
    {
        proRet = (UINT8_S)Rsp1_CheckPackage((const UShort)inDstDevId, (const UShort)inLen, (UTiny *)inBuf, 
            (UShort*)outLen, (UTiny *)outBuf);
    }
#endif
    return proRet;
}

/*
* ����������RsspЭ���ȡ��·��Ϣ 
* ����˵����inDstDevId�豸����timeDiff ʱ��� 
* ����ֵ      :    0�رգ�1���� 
*/
UINT8_S AdptPlatRsspGetChaStat(const UINT16_S inDstDevId, UINT16_S *timeDiff)
{
    UINT8_S status = 1u;
/* todo get Rssp Link Status */
#if 0
    E_Bool temp = r_FALSE;

    if (timeDiff != NULL)
    {
        temp = Rsp1_GetChanelStatus((const UShort)inDstDevId, (UShort *)timeDiff);

        if (r_TRUE == temp)
        {
            status = 1u;
        }
        else
        {
            status = 0u;
        }
    }
#endif
    return status;
}

/*
* �����������������豸���͡��豸ʶ��Ŷ�Ӧ����·��Ϊ�ر�״̬�� 
*                            Э��ջ���ܾ���Ӧ�豸�������ݡ� 
* ����˵����dstDevId�豸��
* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptPlatRsspClose(const UINT16_S dstDevId)
{
    UINT8_S retVal = 1u;
#if 0    /* todo Rssp close */	
    E_Bool temp = r_FALSE;
 
    temp = Rsp1_Close((const UShort)dstDevId);

    if (r_TRUE == temp)
    {
        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }
#endif
    return retVal;
}

/*
* �����������������豸���͡��豸ʶ��Ŷ�Ӧ����·��Ϊ��״̬�� 
*                            Э��ջ�������Ӧ�豸�������ݡ� 
* ����˵����dstDevId�豸��
* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptPlatRsspOpen(const UINT16_S dstDevId)
{
    UINT8_S retVal = 1u;
#if 0    /* todo Rssp close */
    E_Bool temp = r_FALSE;
    
    temp = Rsp1_Open((const UShort)dstDevId);

    if (r_TRUE == temp)
    {
        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }
#endif
    return retVal;
}

/*
* ������������ѯ�������������汾��ͨ������汾
* ����˵����
*Para    : inDevType      : �����豸���߼�����
*            inAppId        : �����豸��Ӧ�ñ��
*            inAccSys       : �����豸����ϵ���ʶ
*            plugAppVer : �����������汾
*            plugCommVer : ���ͨѶ����汾

*          |  �汾��ʶ  |  �汾����  |  ������  |  �汾���  |
*          |-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|
*          �汾��ʶ��'V'
*          �汾���ͣ�'A' - 'Z'
*          �汾��ţ�1 - 15
*          �����ţ���ʽ�汾��0
*                    ���԰汾��'a' - 'z'
*
*          ��ʾʾ����
*          0x56 -> 'V'
*          0x43 -> 'C'
*          0x61 -> 'a'
*          0x56430001UL -> V.C.0001   ��ʽ��
*          0x56436101UL -> V.C.0001a  ���԰�


* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptPlatPlugSwVersionGet(const UINT32_S  inDevType,
                                  const UINT32_S  inAppId,
                                  const UINT32_S  inAccSys,
                                  UINT32_S* const plugAppVer,
                                  UINT32_S* const plugCommVer)
{
    UINT8_S retVal = 0u;
 #if 0 /* TODO����ȡ�忨״̬ */   
    E_SysBool funVal = e_TRUE;

    if((NULL != plugAppVer) && (NULL != plugCommVer))
    {
            *plugAppVer = 0u;
            *plugCommVer = 0u;
            funVal  = F_VCP_InquirySwVersion(inDevType,inAppId,inAccSys,plugAppVer,plugCommVer);
            if(e_TRUE == funVal)
            {
                retVal = 1u;
            }
    }
#endif	
    return retVal;

}

/*
* ������������ȡƽ̨ϵͳʱ�ӵĽӿں��� 
*         ע������ݻ�ȡΪϵͳ��ǰʱ�䣬�������ڴ�ӡ��־ʹ�� 
* ����˵���� 
*                         ���룬��
*                         �����
*                         UINT32 *sec����
*                         UINT32 * msec, ����
* ����ֵ  �� �� 
*/
void AdptPlatTestSystemClkGet(UINT32_S *sec, UINT32_S *msec)
{
#if 0	/* TODO: Get time */
    T_SysClk outSysClk;

    if((NULL != sec ) && (NULL != msec))
    {
        outSysClk = F_VCP_Test_GetSysClk();

        *sec = outSysClk.Sec;
        *msec = (UINT32_S)((FLOAT32_S)outSysClk.uSec * 0.001);
    }
#endif	
}
