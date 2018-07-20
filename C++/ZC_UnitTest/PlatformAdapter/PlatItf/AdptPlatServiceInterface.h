/********************************************************
* 
* �� �� ���� AdptPlatServiceInterface.h
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01 
* ���������� ������ṩ��ƽ̨��ĵײ�����⺯���Ľӿ�ͷ�ļ�  
* ��    ע�� �� 
* 
********************************************************/ 

#ifndef ADPTPLAT_SERVICE_INTERFACE_H_
#define ADPTPLAT_SERVICE_INTERFACE_H_

#include "AdptPlatBasicTypeDefinition.h"
#include "../../Common/CommonTypes.h"

#define MAX_REV_PIPE_NUM  15u
#define MAX_SND_PIPE_NUM  15u

/* ��ƽ̨ͨ���豸���ñ���ƽ̨���豸������ʼ���� */
#define VCP_DMS_START_INDEX  4u
#define VCP_ZC_START_INDEX  4u
#define VCP_ATP_START_INDEX  12u

/* ��ϵͨ��״̬��¼ */
#define EXT_DEV_COM_SUC  1u      /* 1������ */
#define EXT_DEV_COM_FAIL  0u      /* 0������ */

#define RSSP_PACK_ERROR_ID         0u  /* ��������ݽ��շ����ͻ�ʶ��� */
#define RSSP_PACK_ERROR_LEN        1u  /* ������ݳ��ȴ������������ */
#define RSSP_PACK_TSD_SSE_SSR      2u  /* ���TSD�Ͷ�ʱ֡(SSR��SSE) */
#define RSSP_PACK_TSD              3u  /* �Ѵ��TSD */

#define RSSP_PARSE_ERROR_ID         0u  /* ��������ݽ��շ����ͻ�ʶ��� */
#define RSSP_PARSE_ERROR_LEN        1u  /* �������ݳ��ȴ������������ */
#define RSSP_PARSE_SSE_SSR          2u  /* ���ն�ʱ֡(SSR��SSE) */
#define RSSP_PARSE_RSD              3u  /* ����RSD */

#define RSSP_PACK_SSR_LEN    25u           /*SSR������*/
#define RSSP_PACK_SSE_LEN    20u           /*SSE������*/

#define MIC_R_DEV_NUM        200u      /* �������豸������Ŀ */

#define HANDLE_OUT_NOT_MICR  0u         /* ����������ݲ������� */
#define HANDLE_OUT_MICR_DEV  1u         /* ����������ݹ�����Ϊ��NTP */
#define HANDLE_OUT_MICR_NTP  2u         /* ����������ݹ�����ΪNTP */

/*�����豸������ϸ��Ϣ*/
typedef struct AdptDevCfgDetail
{
    UINT16_S  devType;               
    UINT8_S   devId;
    UINT8_S   devSysId;
    UINT32_S   rcvPipeNum;      /*[4 byte] �豸���չܵ��� */
    UINT32_S   sndPipeNum;      /*[4 byte] �豸���͹ܵ��� */
    UINT32_S   sndPipeIndex;
}AdptDevCfgDetailStruct;

typedef struct AdptUsrBuff
{
  UINT8_S* ptrMsg  ;  /* �����ַ     */
  UINT32_S dataLen ;  /* �������ݳ��� */
  UINT32_S allocLen;  /* ������䳤�� */
}AdptUsrBuffStruct;


/*�����豸������ϸ��Ϣ*/
typedef struct AdptMicr
{
    UINT16_S  devType;
    UINT8_S   devId;
    UINT8_S   sysId;
    UINT8_S   comFlag;        /* ͨ��״̬��¼��־��1������0������ */
}AdptMicrDevStruct;


/*����USR���͵���������Ϣע�ắ��*/
typedef void (*AdptTrackDataGet)(UINT8_S* inBuffAddr, UINT32_S inBuffLen, UINT32_S* outSendLen);

/*����USR���յ���������Ϣע�ắ��*/
typedef void (*AdptTrackDataSet)(UINT8_S* inBuffAddr, UINT32_S inRecvLen);


#ifdef __cplusplus
extern "C" {
#endif

/* ����ǰ�������ݽ���ĳЩ����Ĵ�����ATP�з��͹����ص��豸Ҫ�����Ҫ�� */
UINT8_S AdptPlatOutDataHandle(UINT32_S inDevType, UINT32_S inAppId, const UINT8_S *inData, UINT32_S inLen, UINT8_S outData[], UINT32_S *pOutLen);


/*
* ������������ȡ�豸������Ϣ
* ����˵���� 
* ����ֵ  �� 1:�ɹ�  0,ʧ��
*/
UINT8_S AdptPlatGetDevCfgDetail(const UINT32_S inListLen, AdptDevCfgDetailStruct outDevCfgDetailList[], UINT32_S* outDevNum);



/*
*��������: ��ȡUDPͨ���豸����
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
                                  AdptUsrBuffStruct* ioUsrBuff);



/*
*��������: ��ȡUDPͨ���豸����
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
                                  const UINT8_S * inData,
                                  const UINT32_S dataLen);




/*
* ����������ͨ��ƽ̨ǰ��巢�͵�������(ͨ������)
* ����˵���� 
*                           ���룬const UINT8* const inData�����ͻ����� const UINT32 inDataLen���������ݳ���
*                           �������
* ����ֵ  �� 1:�������ҷ��ͳɹ�  0,(����ʧ�� || ���ͻ�������ַΪNULL || ���ͳ���Ϊ0)
*/

UINT8_S AdptPlatUsrDataWatch(const UINT8_S* const inData,
                                    const UINT32_S inDataLen);



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
UINT8_S AdptPlatUsrDataRecvMutual(AdptCellMsgStruct* const ioMsg);



/*
* ������������ϵͬ��ʱ��ϵ�����ݷ��ͽӿں���
* ����˵��������,
*                            const void* const inData���������ݻ�����
*                            const UINT32 inDataLen,�������ݳ���
* ����ֵ      :  1,�ɹ� ��0��ʧ��
*/

UINT8_S AdptPlatUsrDataSendMutual(const void* const inData, const UINT32_S inDataLen);




/*
* ������������ʹƽ̨崻��Ľӿں���
* ����˵����const UINT32 errNo ����Ҫ��¼�Ĵ�����
* ����ֵ      :  ��
*/
void AdptPlatUsrHaltSystem(const UINT32_S inErrCode);




/*
* ������������ȡ�豸״̬
* ����˵���� 
*                           ���룬const UINT8 devType���豸����; const UINT8 devId���豸ID;const UINT8 sysId,�豸ID
*                           �������
* ����ֵ  �� �豸״̬

*/

UINT8_S AdptPlatInquiryDevStatus(const UINT32_S devType,const UINT32_S devId,const UINT32_S sysId);



/*
* ������������ȡƽ̨���ڿ�ʼϵͳʱ�ӵĽӿں���
* ����˵���� 
*                         ���룬��
*                         �����
*                         UINT32 *sec����
*                         UINT32 * msec, ����
* ����ֵ  �� ��
*/
void AdptPlatSystemClkGet(UINT32_S *sec, UINT32_S *msec);



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
void  AdptPlatCalendarClkGet(UINT32_S *year, UINT32_S * month, UINT32_S * day, UINT32_S *hour, UINT32_S *min, UINT32_S *sec);


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

UINT8_S AdptPlatCalendarClkSet(UINT32_S year, UINT32_S month, UINT32_S day, UINT32_S hour, UINT32_S min, UINT32_S sec);


/*
* ������������ȡ��ǰ����ϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)�ӿں���
* ����˵���� ��
* ȫ�ֱ����� 
* ����ֵ  �� ��ǰ����ϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)
*/

UINT32_S AdptPlatGetSystemId(void);

/*
* ������������ȡ��ϵϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)�ӿں���
* ����˵���� ��
* ȫ�ֱ����� 
* ����ֵ  ��  ��ϵϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)
*/
UINT32_S AdptPlatGetMasterId(void);

/*
* �����������ṩ��Ӧ�õ���ע��ӿں���
* ����˵����const UINT32 inMaxLen, ע����󵹻����ݳ���;
*                            const UINT32 inInterval,ע��ǿ�Ƶ������ڼ��;
*                            AdptTrackDataGet inDataGet, ע���ȡUSR�������ݺ���
*                            AdptTrackDataSet inDataSe,tע������USR�������ݺ���
* ����ֵ      :    1,�ɹ� 0,ʧ��
*/
UINT8_S AdptPlatTrackRegister(const UINT32_S inMaxLen, const UINT32_S inInterval,
                   AdptTrackDataGet inDataGet, AdptTrackDataSet inDataSet);


/*
* ������������ȡƽ̨���ںŵĽӿں���
* ����˵������
* ����ֵ      :    ƽ̨���ں�
*/
UINT32_S AdptPlatCycNum(void);

/*
* ����������RsspЭ����г�ʼ�� 
* ����˵����selfDevId�����豸����inCfgLen�������ݳ��ȣ�inCfgBuf�������ݻ����� 
* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptPlatRsspInit(const UINT16_S selfDevId, const UINT16_S inCfgLen, UINT8_S *inCfgBuf);

/*
* ����������RsspЭ���������ʱ�� 
* ����˵������
* ����ֵ      :    ��
*/
void AdptPlatRsspUpdateClock(void);

/*
* ����������RsspЭ���ȡͬ������
* ����˵����bufͬ�����ݻ����� 
* ����ֵ      :    ͬ�����ݳ��� 
*/
UINT16_S AdptPlatRsspGetSynData(UINT8_S *buf);

/*
* ����������RsspЭ�鴫��ͬ������
* ����˵����bufͬ�����ݻ����� ,���ݳ��� 
* ����ֵ      :    ͬ�����ݳ��� 
*/
void AdptPlatRsspSetSynData(UINT8_S *buf, UINT16_S len);


/*
* ����������RsspЭ�������� 
* ����˵����inDstDevId�豸����inLen���볤�ȣ�inBuf�������ݣ�
*                     outTsdLenӦ�����ݳ��ȣ�outTsdBufӦ�����ݣ�outSsLen��ʱ֡���ȣ�outSsBuf��ʱ֡����
* ����ֵ      :    0���ʹ���1 ���ȴ���2δ���TSD��3�Ѵ��TSD 
*/
UINT8_S AdptPlatRsspPackData(const UINT16_S inDstDevId, const UINT16_S inLen, UINT8_S *inBuf,
        UINT16_S *outTsdLen, UINT8_S *outTsdBuf,UINT16_S *outSseLen, UINT8_S *outSseBuf,UINT16_S *outSsrLen, UINT8_S *outSsrBuf);

/*
* ����������RsspЭ��������  
* ����˵����inDstDevId�豸����inLen���볤�ȣ�inBuf�������ݣ�
*                     outLenӦ�����ݳ��ȣ�outBufӦ������ 
* ����ֵ      :    0���ʹ���1 ���ȴ���2 SSE or SSR��3 RSD 
*/
UINT8_S AdptPlatRsspParseData(const UINT16_S inDstDevId, const UINT16_S inLen, UINT8_S *inBuf,
        UINT16_S *outLen, UINT8_S *outBuf);

/*
* ����������RsspЭ���ȡ��·��Ϣ 
* ����˵����inDstDevId�豸����timeDiff ʱ��� 
* ����ֵ      :    0�رգ�1���� 
*/
UINT8_S AdptPlatRsspGetChaStat(const UINT16_S inDstDevId, UINT16_S *timeDiff);

/*
* �����������������豸���͡��豸ʶ��Ŷ�Ӧ����·��Ϊ��״̬�� 
*                            Э��ջ�������Ӧ�豸�������ݡ� 
* ����˵����dstDevId�豸��
* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptPlatRsspOpen(const UINT16_S dstDevId);

/*
* �����������������豸���͡��豸ʶ��Ŷ�Ӧ����·��Ϊ�ر�״̬�� 
*                            Э��ջ���ܾ���Ӧ�豸�������ݡ� 
* ����˵����dstDevId�豸��
* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptPlatRsspClose(const UINT16_S dstDevId);

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
UINT8_S AdptPlatPlugSwVersionGet(const UINT32_S  inDevType,
                                  const UINT32_S  inAppId,
                                  const UINT32_S  inAccSys,
                                  UINT32_S* const plugAppVer,
                                  UINT32_S* const plugCommVer);


/*
* ������������ȡƽ̨���ڿ�ʼϵͳʱ�ӵĽӿں���
*          ע������ݻ�ȡΪϵͳ��ǰʱ�䣬�������ڴ�ӡ��־ʹ�� 
* ����˵���� 
*                         ���룬��
*                         �����
*                         UINT32 *sec����
*                         UINT32 * msec, ����
* ����ֵ  �� ��
*/
void AdptPlatTestSystemClkGet(UINT32_S *sec, UINT32_S *msec);

#ifdef __cplusplus
}
#endif

#endif



