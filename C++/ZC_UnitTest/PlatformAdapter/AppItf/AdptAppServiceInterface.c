/********************************************************
*                                                                                                            
* �� �� ���� AdptAppServiceInterface.c   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ������Ӧ�ò�Ľӿ��ļ� 
* ��    ע�� �� 
*
********************************************************/ 

#include "AdptAppServiceInterface.h"
#include "../PlatItf/AdptPlatServiceInterface.h"
#include "../AdptHandle/AdapterExtDevInOutManage.h"
#include "../PlatformLog/AdapterLog.h"
#include "../../Common/MemSet.h"
#include "../PlatItf/AdptPlatFileInterface.h"
#include "../PlatItf/AdptPlatServiceInterface.h "
#include "../../cspadpt/Vcp_Service_TestInterface.h"



UINT16_S gLocalName = 0u;
UINT16_S gTrainName = 0u;

/*
* �����������ṩ��Ӧ���豸ͨ�ų�ʼ���ӿں���
* ����˵���� 
*                           ���룬
*                           ��
*                           �����
*                           ��
* ����ֵ  ��  1 �ɹ� 
*           0 ʧ�� 
*/
UINT8_S  AdptAppExtDevInit(void)
{
    UINT8_S retVal = 0u;

    retVal = AdapterExtDevCfgInfoInit();          /*��ʼ���豸������Ϣ�ṹ*/

    if(1 == retVal)
    {
        retVal = AdapterGetDevCfgDetail(); /*��ȡ�豸������Ϣ*/
    }

    return retVal;
}



/*
* �����������ⲿ�豸���մ��� 
* ����˵���� 
*                           ���룬
*                           ��
*                           �����
*                           ��
* ����ֵ  ��  ��
*/
void  AdptAppExtDevInDataManage(void)
{
    AdapterExtDevInDataManage();

}


/*
* �����������ⲿ�豸���ݽ��մ��� 
* ����˵���� 
*                           ���룬
*                           ��
*                           �����
*                           ��
* ����ֵ  ��  ��
*/
void AdptAppExtDevOutDataManage(void)
{
    AdapterExtDevOutDataManage();
}



/*
*��������: ��������ӿ�
* ������
*            ����:
*            inDevType : �����豸���߼�����
*            inAppId   : �����豸��Ӧ��ID
*            inDevSys  : �����豸������ϵ��
*            ioUsrBuff: ioUsrBuff ->ptrMsg,���ջ�������ַ
*                           ioUsrBuff ->allocLen,���ջ�����ÿռ�
*            ���:
*            ioUsrBuff: ioUsrBuff ->ptrMsg,���ջ�������ַ
*                         ioUsrBuff ->dataLen,���յ������ݳ���
*����ֵ: 1���ɹ���0��ʧ��
*/

UINT8_S AdptAppUsrDataRecv(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  AdptUsrBuffStruct* ioUsrBuff)
{
    UINT8_S retVal = 0u;

    if ( ioUsrBuff != NULL )
    {
        retVal = AdptPlatUsrDataRecv(inDevType, inAppId, inDevSys, 0u, ioUsrBuff);
    }

    return retVal;
}


/*
*��������: ��������ӿ�
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

UINT8_S AdptAppUsrDataSend(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  const UINT8_S*  inData,
                                  const UINT32_S dataLen)
{
    UINT8_S retVal = 0u;

    if ( inData != NULL )
    {
        retVal = AdptPlatUsrDataSend(inDevType, inAppId, inDevSys, 0u, inData, dataLen);
    }

    return retVal;
}




/*
* �����������ṩ��Ӧ��ͨ��ƽ̨ǰ��巢�͵�������(ͨ������)�Ľӿ�
* ����˵���� 
*                           ���룬
*                           const UINT8* const inData�����ͻ����� 
*                           const UINT32 inDataLen���������ݳ���
*                           �����
*                           ��
* ����ֵ  �� 1:�������ҷ��ͳɹ� 
*                          0:(����ʧ�� || ���ͻ�������ַΪNULL || ���ͳ���Ϊ0)
*/


UINT8_S AdptAppUsrDataWatch(const UINT8_S* const inData,
                                    const UINT32_S inDataLen)
{
    UINT8_S retVal = 0u;

    if ( inData != NULL )
    {
        retVal = AdptPlatUsrDataWatch(inData,inDataLen);
    }

    return retVal;
}


/*
* �����������ṩ��Ӧ����ϵͬ��ʱ��ϵ�����ݽ��սӿں���
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
UINT8_S AdptAppUsrDataRecvMutual(AdptCellMsgStruct* const ioMsg)
{
    UINT8_S result = 0u;

    if ( ioMsg != NULL )
    {
        result = AdptPlatUsrDataRecvMutual(ioMsg);
    }

    return result;

}


/*
* �����������ṩ��Ӧ����ϵͬ��ʱ��ϵ�����ݷ��ͽӿں���
* ����˵��������,
*                            const void* const inData���������ݻ�����
*                            const UINT32 inDataLen,�������ݳ���
* ����ֵ      :  1,�ɹ� ��0��ʧ��
*/
UINT8_S AdptAppUsrDataSendMutual(const void* const inData, const UINT32_S inDataLen)
{
    UINT8_S result = 0u;

    if ( inData != NULL )
    {
        result = AdptPlatUsrDataSendMutual(inData, inDataLen);
    }

    return result;
}



/*
* �����������ṩ��Ӧ����ʹƽ̨崻��Ľӿں���
* ����˵����const UINT32 errNo ����Ҫ��¼�Ĵ�����
* ����ֵ      :  ��
*/
void  AdptAppUsrHaltSystem(const UINT32_S errNo)
{
    printf("Halt! %x\n",errNo);
    AdptAppLogPrintf(1u, "Halt! %x\n",errNo);
    AdptPlatUsrHaltSystem(errNo);
}



/*
* �����������ṩ��Ӧ�û�ȡƽ̨����豸״̬�Ľӿں���
* ����˵���� 
*                           ���룬
*                           const UINT8 devType���豸����; 
*                           const UINT8 devId���豸ID;
*                           const UINT8 sysId,�豸ID
*                           �������
* ����ֵ  �� �豸״̬
                            1,�豸������
                   2,�豸��ʼ��
                   4,�豸����״̬
                   5,�豸����״̬ 
                   6,�豸�Լ�
*/
UINT8_S AdptAppInquiryDevStatus(const UINT32_S devType,const UINT32_S devId,const UINT32_S sysId)
{
    UINT8_S retVal = 0u;

    retVal = AdptPlatInquiryDevStatus(devType,devId,sysId);

    return retVal;
}



/*
* �����������ṩ�� Ӧ�û�ȡƽ̨���ڿ�ʼϵͳʱ�ӵĽӿں���
* ����˵���� 
*                         ���룬��
*                         �����
*                                    UINT32 *sec����
*                                    UINT32 * msec, ����
* ����ֵ  �� ��
*/

void AdptAppSystemClkGet(UINT32_S *sec, UINT32_S *msec)
{
    if (( sec != NULL ) && ( msec != NULL ))
    {
        AdptPlatSystemClkGet(sec, msec);
    }
}

/*
* �����������ṩ��Ӧ�û�ȡϵͳ����ʱ��Ľӿں���
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
void  AdptAppCalendarClkGet(UINT32_S *year,UINT32_S * month,UINT32_S * day,UINT32_S *hour,UINT32_S *min,UINT32_S *sec)
{
    if (( year != NULL ) && ( month != NULL ) && ( day != NULL ) && ( hour != NULL ) && ( min != NULL ) && ( sec != NULL ))
    {
        AdptPlatCalendarClkGet(year,month,day,hour,min,sec);
    }
}

/*
* ���������� �ṩ��Ӧ������ϵͳ����ʱ��ӿں���
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
UINT8_S  AdptAppCalendarClkSet(UINT32_S year,UINT32_S month,UINT32_S day,UINT32_S hour,UINT32_S min,UINT32_S sec)
{
    UINT8_S retVal = 0u;

    retVal = AdptPlatCalendarClkSet(year, month, day, hour, min, sec);

    return retVal;

}

/*
* �����������ṩ�� Ӧ�û�ȡ��ǰ����ϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)�ӿں���
* ����˵���� ��
* ȫ�ֱ����� 
* ����ֵ  �� ��ǰ����ϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)
*/
UINT32_S AdptAppGetSystemId(void)
{
    UINT32_S sysId = 0u;

    sysId = AdptPlatGetSystemId();         /*��ȡ��ϵϵ��:0x01 ,Iϵ;0x02,IIϵ*/

    return sysId;
}

/*
* �����������ṩ�� Ӧ�û�ȡ��ϵϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)�ӿں���
* ����˵���� ��
* ȫ�ֱ����� 
* ����ֵ  ��  ��ϵϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)
*/
UINT32_S AdptAppGetMasterId(void)
{
    UINT32_S masterId = 0u;

    masterId = AdptPlatGetMasterId();         /*��ȡ��ϵϵ��:0x01 ,Iϵ;0x02,IIϵ*/

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
UINT8_S AdptAppTrackRegister(const UINT32_S inMaxLen,
                               const UINT32_S inInterval,
                               AdptTrackDataGet inDataGet,
                               AdptTrackDataSet inDataSet)
{
    UINT8_S result = 0u;

    result = AdptPlatTrackRegister(inMaxLen, inInterval, inDataGet, inDataSet);

    return result;
}


/*
* �����������ṩ��Ӧ�û�ȡƽ̨���ںŵĽӿں���
* ����˵������
* ����ֵ      :    ƽ̨���ں�
*/
UINT32_S AdptAppCycNum(void)
{
    UINT32_S cycleNum = 0u;
    UpdataRunCycNum(cycleNum);
    return cycleNum;
}


/*
* �����������ṩ��Ӧ������ϵͳ���ƵĽӿں���
* ����˵����localName ϵͳ����  
* ����ֵ      :    
*/
void AdptAppSetLocalName(UINT16_S localName)
{

    gLocalName = localName;

}

/*
* �����������ṩ��Ӧ�û�ȡϵͳ���ƵĽӿں���
* ����˵������
* ����ֵ      :    ϵͳ���� 
*/
UINT16_S AdptAppGetLocalName(void)
{

    return gLocalName;

}


/*
* ����������RsspЭ����г�ʼ�� 
* ����˵����selfDevId�����豸�� 
* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptAppRsspInit(const UINT16_S selfDevId)
{
    UINT8_S retVal = 0u;
    UINT8_S fileBuff[RSSP_CFG_MAX_LEN] = {0u};
    UINT8_S fileStatus = 0u;
    UINT32_S fileLen = 0u;
    FILEType fileHandle;

    MemorySet(fileBuff,RSSP_CFG_MAX_LEN,0u,RSSP_CFG_MAX_LEN);

    fileStatus = AdptPlatFileOpen(RSSP_CFG_NAME, 0u, &fileHandle);

    if ( 1u == fileStatus )
    {
        fileLen = AdptPlatFileRead(fileHandle, RSSP_CFG_NAME, &fileBuff[0u], RSSP_CFG_MAX_LEN);

        if ( fileLen > 0u )
        {
            retVal = AdptPlatRsspInit(selfDevId, fileLen,&fileBuff[0u]);
        }
    }

    return retVal;
}

/*
* ����������RsspЭ���������ʱ�� 
* ����˵������
* ����ֵ      :    ��
*/
void AdptAppRsspUpdateClock(void)
{

    AdptPlatRsspUpdateClock();

    return;
}

/*
* ����������RsspЭ���ȡͬ������
* ����˵����bufͬ�����ݻ����� 
* ����ֵ      :    ͬ�����ݳ��� 
*/
UINT16_S AdptAppRsspGetSynData(UINT8_S *buf)
{
    UINT16_S retVal = 0u;

    if (buf != NULL)
    {
        retVal = AdptPlatRsspGetSynData(buf);
    }

    return retVal;
}

/*
* ����������RsspЭ�鴫��ͬ������
* ����˵����bufͬ�����ݻ����� ,���ݳ��� 
* ����ֵ      :    ͬ�����ݳ��� 
*/
void AdptAppRsspSetSynData(UINT8_S *buf, UINT16_S len)
{

    if (buf != NULL)
    {
        AdptPlatRsspSetSynData(buf, len);
    }

    return;
}

/*
* �����������������豸���͡��豸ʶ��Ŷ�Ӧ����·��Ϊ�ر�״̬�� 
*                            Э��ջ���ܾ���Ӧ�豸�������ݡ� 
* ����˵����dstDevId�豸��
* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptAppRsspClose(const UINT16_S dstDevId)
{
    UINT8_S retVal = 0u;

    retVal = AdptPlatRsspClose(dstDevId);

    return retVal;
}

/*
* �����������ṩ��Ӧ�ò�ѯ�������������汾��ͨ������汾
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
UINT8_S AdptAppPlugSwVersionGet(const UINT32_S  inDevType,
                                  const UINT32_S  inAppId,
                                  const UINT32_S  inAccSys,
                                  UINT32_S* const plugAppVer,
                                  UINT32_S* const plugCommVer)
{

    UINT8_S retVal = 0u;
    
    UINT8_S funVal = 0u;

    if((NULL != plugAppVer) && (NULL != plugCommVer))
    {
        *plugAppVer = 0u;
        *plugCommVer = 0u;
        funVal  = AdptPlatPlugSwVersionGet(inDevType,inAppId,inAccSys,plugAppVer,plugCommVer);
        if(1u == funVal)
        {
            retVal = 1u;
        }
    }
    return retVal;

}

/*
* �����������ṩ��Ӧ������ϵͳһ�˶������Ľӿں���
* �������ֳ���ATP ATO�豸һ�˶��ˣ����Ϊ�����豸����Ҫ���ô˺���
* ����˵����TrainName ϵͳ����  
* ����ֵ      :    
*/
void AdptAppSetTrainName(UINT16_S TrainName)
{
    gTrainName = TrainName;
}

/*
* �����������ṩ��Ӧ�û�ȡϵͳһ�˶������Ľӿں���
* ����˵������
* ����ֵ      :    ϵͳ���� 
*/
UINT16_S AdptAppGetTrainName(void)
{
    return gTrainName;
}

/*
* ������������ȡƽ̨ϵͳʱ�ӵĽӿں���
*                 ע������ݻ�ȡΪϵͳ��ǰʱ�䣬�������ڴ�ӡ��־ʹ�� 
* ����˵���� 
*                         ���룬��
*                         �����
*                                    UINT32 *sec����
*                                    UINT32 * msec, ����
* ����ֵ  �� ��
*/
void AdptAppTestSystemClkGet(UINT32_S *sec, UINT32_S *msec)
{
    if (( sec != NULL ) && ( msec != NULL ))
    {
        AdptPlatTestSystemClkGet(sec, msec);
    }
}

/*******************************************************************************
* ����������������ת��Ϊ����ʱ��    
* ���������const UINT32_S Seconds(��1970��1��1��0ʱ��ʼ������,�Ѿ�Ĭ��תΪ����ʱ��)
* ���������UINT8 *pCalenderBuff   ʱ������:������ʱ����
* ����ֵ��  1-�ɹ�;0-ʧ��;
********************************************************************************/
UINT8_S Seconds2Calendar(UINT32_S seconds, UINT32_S *pCalenderBuff)
{
    UINT8_S   retVal = 1u;                /*�������ķ���ֵ*/
    const UINT8_S days[12u] = {31u,28u,31u,30u,31u,30u,31u,31u,30u,31u,30u,31u};    

    UINT32_S     fourYearsCal = 0u;            /*��������ʱ�õ���ʱ�����������Ŀ*/
    UINT32_S     yearsCal = 0u;                /*�����������������*/
    UINT32_S     hourPerYear = 0u;            /*ÿ���Сʱ��*/
    UINT32_S     month = 0u;                /*�·�*/
    UINT32_S     day = 0u;                /*����*/
    UINT32_S     hour = 0u;                /*ʱ*/
    UINT32_S     min = 0u;                /*��*/
    UINT32_S     sec = 0u;                /*��*/
    UINT32_S    secondsTemp = 0u;

    if (NULL != pCalenderBuff)
    {

        /*�õ�����Ϣ*/
        sec = seconds%60u;

        /*�õ�����Ϣ*/
        seconds /= 60u;
        min = seconds%60u;

        /*�õ�Сʱ��*/
        seconds /= 60u;

        /*ȡ��ȥ���ٸ�����,ÿ������ 1461*24 Сʱ = 35064 Сʱ*/
        fourYearsCal = (seconds / 35064u);
        yearsCal = (fourYearsCal << 2u) + 70u;

        /*������ʣ�µ�Сʱ��*/
        seconds %= 35064u;

        hourPerYear = 8760u; /*һ���Сʱ�� 365 * 24 = 8760 */ 
        /*У������Ӱ������,����һ����ʣ�µ�Сʱ��*/
        while(seconds > hourPerYear)
        {    
            /*�ж�����*/
            if ((yearsCal & 3u) == 0u)        
            {            
                /*������,һ�����24Сʱ,��һ�� */           
                hourPerYear += 24u;        
            } 

            if (seconds < hourPerYear)        
            {            
                break;        
            } 

            yearsCal += 1u;        
            seconds -= hourPerYear;    

            hourPerYear = 8760u; /*һ���Сʱ�� 365 * 24 = 8760 */ 
        }

        /*�õ���ǰʱ�̵�Сʱ*/
        hour = seconds%24u;
        seconds /= 24u;

        /*�ٶ�Ϊ����,+1��Ϊ��1��ʼ����*/
        seconds++; 

        /*У����������,�����·�,����*/
        if ((yearsCal & 3u) == 0u)
        {        
            if (seconds > 60u)        
            {
                seconds--;    
            }
            else if (seconds == 60u)            
            {                
                month = 1u;
                day = 29u;

                /*��[0,99]��ʾ���20XX��*/
                yearsCal = yearsCal + 1900u;
                if(yearsCal < 2000u)
                {
                    retVal = 0u;
                }

                pCalenderBuff[0u] = yearsCal;
                pCalenderBuff[1u] = month + 1u;
                pCalenderBuff[2u] = day;
                pCalenderBuff[3u] = hour;
                pCalenderBuff[4u] = min;
                pCalenderBuff[5u] = sec;
            }    
            else
            {
                /*SecondsС��60ʱ,�޲���*/
            }
        }


        /*��������,�·ݴ�0��11 */
        #if 0
        for (month = 0; days[month] < seconds; month+=1)    
        {          
            seconds -= days[month];    
        }
        day = seconds;  

        #else
        secondsTemp = seconds;
        for(month = 0u;month < 12u; month++)
        {
            if(secondsTemp <= days[month])
            {
                break;
            }

            secondsTemp = secondsTemp - days[month];
        }
        day = secondsTemp;  
        #endif

    
        /*��[0,99]��ʾ���20XX��*/
        yearsCal = yearsCal + 1900u;
        if(yearsCal < 2000u)
        {
            retVal = 0u;
        }

        /*��BCD���ʾ������ʱ����*/
        pCalenderBuff[0u] = yearsCal;
        pCalenderBuff[1u] = month + 1u;
        pCalenderBuff[2u] = day;
        pCalenderBuff[3u] = hour;
        pCalenderBuff[4u] = min;
        pCalenderBuff[5u] = sec;
    }

    return retVal;
}

/*******************************************************************************
* ����������������ʱ��ת��Ϊ���� 
* ���������UINT8 *pCalenderBuff   ʱ������:������ʱ���� 
* ����������� 
* ����ֵ��  UINT32_S Seconds(��1970��1��1��0ʱ��ʼ������) 
*           >0 �ɹ�;0ʧ��; 
********************************************************************************/
UINT32_S CalendarToSeconds(UINT32_S * pCalenderBuff)
{
    UINT32_S i = 0u;
    UINT32_S years = 0u;                /* ���� */
    UINT32_S month = 0u;                /* �·� */
    UINT32_S day = 0u;                  /* ���� */
    UINT32_S hour = 0u;                 /* ʱ */
    UINT32_S min = 0u;                  /* �� */
    UINT32_S sec = 0u;                  /* �� */
    UINT32_S allHours = 0u;             /* ȫ����Сʱ�� */
    UINT32_S allSeconds = 0u;           /* ȫ�������� */
    UINT8_S days[12u] = {31u, 28u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u};  /* ʮ�����·ݶ�Ӧ������ */

    if (pCalenderBuff != NULL)
    {
        /* ȡ��������ʱ���� */
        years = pCalenderBuff[0u];
        month = pCalenderBuff[1u] - 1u;
        day = pCalenderBuff[2u] - 1u;
        hour = pCalenderBuff[3u];
        min = pCalenderBuff[4u];
        sec = pCalenderBuff[5u];

        if(years < 1970u)
        {
            allSeconds = 0u;
        }
        else
        {
            /* ��ʱ��1970�꿪ʼ���� */
            for (i = 1970u; i < years; i++)
            {
                /*�ж�����*/
                if ((i & 3u) == 0u)
                {
                    /* ������,һ�����24Сʱ */
                    allHours += 24u;
                }
            }

            /* ���㱾�꣬��2�·ݵ����������Ƿ�Ϊ�������һ�� */
            if ((years & 3u) == 0u)
            {
                days[1u] = 29u;
            }

            years = years - 1970u;
            allHours = allHours + years * 365u * 24u;

            for (i = 0u; i < month; i++)
            {
                /* ��ͬ�·����� */
                allHours = allHours + days[i] * 24u;
            }

            allHours = allHours + day * 24u + hour;

            allSeconds = allHours * 60u * 60u + min * 60u + sec;

        }
    }

    return allSeconds;
}

