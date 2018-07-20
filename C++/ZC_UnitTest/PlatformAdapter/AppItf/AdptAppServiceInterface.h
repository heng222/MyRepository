/********************************************************
*                                                                                                            
* �� �� ���� AdptAppServiceInterface.h   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ������Ӧ�ò�Ľӿ�ͷ�ļ� 
* ��    ע�� �� 
*
********************************************************/ 

#ifndef ADPT_APP_SERVICE_INTERFACE_H_
#define ADPT_APP_SERVICE_INTERFACE_H_


#include "../../Common/CommonTypes.h"
#include "../PlatItf/AdptPlatBasicTypeDefinition.h"
#include "../PlatItf/AdptPlatServiceInterface.h"


#define RSSP_CFG_MAX_LEN           10000u                /* RSSPЭ�������ļ���󳤶� */
#define RSSP_CFG_NAME           "RSSR.bin"                /* RSSPЭ�������ļ��� */

#ifdef __cplusplus
extern "C" {
#endif
/*
* �����������ṩ��Ӧ���豸ͨ�ų�ʼ���ӿں���
* ����˵���� 
*                           ���룬
*                           ��
*                           �����
*                           ��
* ����ֵ  ��  ��
*/
UINT8_S  AdptAppExtDevInit(void);



/*
* �����������ṩ��Ӧ�÷��͸������豸���ݵķ��ͽӿں���
* ����˵���� 
*                           ���룬
*                           ��
*                           �����
*                           ��
* ����ֵ  ��  ��
*/
void  AdptAppExtDevInDataManage(void);


/*
* �����������ṩ��Ӧ�ý��������豸���ݵĽӿں���
* ����˵���� 
*                           ���룬
*                           ��
*                           �����
*                           ��
* ����ֵ  ��  ��
*/
void AdptAppExtDevOutDataManage(void);




/*
*��������: ��������ӿ�
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

UINT8_S AdptAppUsrDataRecv(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  AdptUsrBuffStruct* ioUsrBuff);


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
                                  const UINT32_S dataLen);


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
                                    const UINT32_S inDataLen);


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
UINT8_S AdptAppUsrDataRecvMutual(AdptCellMsgStruct* const ioMsg);

/*
* �����������ṩ��Ӧ����ϵͬ��ʱ��ϵ�����ݷ��ͽӿں���
* ����˵��������,
*                            const void* const inData���������ݻ�����
*                            const UINT32 inDataLen,�������ݳ���
* ����ֵ      :  1,�ɹ� ��0��ʧ��
*/
UINT8_S AdptAppUsrDataSendMutual(const void* const inData, const UINT32_S inDataLen);


/*
* �����������ṩ��Ӧ����ʹƽ̨崻��Ľӿں���
* ����˵����const UINT32 errNo ����Ҫ��¼�Ĵ�����
* ����ֵ      :  ��
*/
void  AdptAppUsrHaltSystem(const UINT32_S errNo);



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
UINT8_S AdptAppInquiryDevStatus(const UINT32_S devType,const UINT32_S devId,const UINT32_S sysId);



/*
* �����������ṩ�� Ӧ�û�ȡƽ̨���ڿ�ʼϵͳʱ�ӵĽӿں���
* ����˵���� 
*                         ���룬��
*                         �����
*                                    UINT32 *sec����
*                                    UINT32 * msec, ����
* ����ֵ  �� ��
*/

void AdptAppSystemClkGet(UINT32_S *sec, UINT32_S *msec);

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
void  AdptAppCalendarClkGet(UINT32_S *year,UINT32_S * month,UINT32_S * day,UINT32_S *hour,UINT32_S *min,UINT32_S *sec);

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
UINT8_S  AdptAppCalendarClkSet(UINT32_S year,UINT32_S month,UINT32_S day,UINT32_S hour,UINT32_S min,UINT32_S sec);

/*
* �����������ṩ�� Ӧ�û�ȡ��ǰ����ϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)�ӿں���
* ����˵���� ��
* ȫ�ֱ����� 
* ����ֵ  �� ��ǰ����ϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)
*/
UINT32_S AdptAppGetSystemId(void);
/*
* �����������ṩ�� Ӧ�û�ȡ��ϵϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)�ӿں���
* ����˵���� ��
* ȫ�ֱ����� 
* ����ֵ  ��  ��ϵϵ����Ϣ(0x01 ,Iϵ;0x02,IIϵ)
*/
UINT32_S AdptAppGetMasterId(void);




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
                               AdptTrackDataSet inDataSet);


/*
* �����������ṩ��Ӧ�û�ȡƽ̨���ںŵĽӿں���
* ����˵������
* ����ֵ      :    ƽ̨���ں�
*/
UINT32_S AdptAppCycNum(void);

/*
* �����������ṩ��Ӧ������ϵͳ���ƵĽӿں���
* ����˵����localName ϵͳ����  
* ����ֵ      :    
*/
void AdptAppSetLocalName(UINT16_S localName);

/*
* �����������ṩ��Ӧ�û�ȡϵͳ���ƵĽӿں���
* ����˵������
* ����ֵ      :    ϵͳ���� 
*/
UINT16_S AdptAppGetLocalName(void);


/*
* ����������RsspЭ����г�ʼ�� 
* ����˵����selfDevId�����豸����inCfgLen�������ݳ��ȣ�inCfgBuf�������ݻ����� 
* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptAppRsspInit(const UINT16_S selfDevId);

/*
* ����������RsspЭ���������ʱ�� 
* ����˵������
* ����ֵ      :    ��
*/
void AdptAppRsspUpdateClock(void);

/*
* ����������RsspЭ���ȡͬ������
* ����˵����bufͬ�����ݻ����� 
* ����ֵ      :    ͬ�����ݳ��� 
*/
UINT16_S AdptAppRsspGetSynData(UINT8_S *buf);

/*
* ����������RsspЭ�鴫��ͬ������
* ����˵����bufͬ�����ݻ����� ,���ݳ��� 
* ����ֵ      :    ͬ�����ݳ��� 
*/
void AdptAppRsspSetSynData(UINT8_S *buf, UINT16_S len);

/*
* �����������������豸���͡��豸ʶ��Ŷ�Ӧ����·��Ϊ�ر�״̬�� 
*                            Э��ջ���ܾ���Ӧ�豸�������ݡ� 
* ����˵����dstDevId�豸��
* ����ֵ      :    1 �ɹ��� 0ʧ�� 
*/
UINT8_S AdptAppRsspClose(const UINT16_S dstDevId);

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
UINT8_S AdptAppPlugSwVersionGet(const UINT32_S  inDevType,
                                  const UINT32_S  inAppId,
                                  const UINT32_S  inAccSys,
                                  UINT32_S* const plugAppVer,
                                  UINT32_S* const plugCommVer);

/*
* �����������ṩ��Ӧ������ϵͳһ�˶������Ľӿں���
* �������ֳ���ATP ATO�豸һ�˶��ˣ����Ϊ�����豸����Ҫ���ô˺���
* ����˵����TrainName ϵͳ����  
* ����ֵ      :    
*/
void AdptAppSetTrainName(UINT16_S TrainName);

/*
* �����������ṩ��Ӧ�û�ȡϵͳһ�˶������Ľӿں���
* ����˵������
* ����ֵ      :    ϵͳ���� 
*/
UINT16_S AdptAppGetTrainName(void);

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
void AdptAppTestSystemClkGet(UINT32_S *sec, UINT32_S *msec);

/*******************************************************************************
* ����������������ת��Ϊ����ʱ��    
* ���������const UINT32_S Seconds(��1970��1��1��0ʱ��ʼ������,�Ѿ�Ĭ��תΪ����ʱ��)
* ���������UINT8 *pCalenderBuff   ʱ������:������ʱ����
* ����ֵ��  1-�ɹ�;0-ʧ��;
********************************************************************************/
UINT8_S Seconds2Calendar(UINT32_S seconds, UINT32_S *pCalenderBuff);

/*******************************************************************************
* ����������������ʱ��ת��Ϊ���� 
* ���������UINT8 *pCalenderBuff   ʱ������:������ʱ���� 
* ����������� 
* ����ֵ��  UINT32_S Seconds(��1970��1��1��0ʱ��ʼ������) 
*           >0 �ɹ�;0ʧ��; 
********************************************************************************/
UINT32_S CalendarToSeconds(UINT32_S *pCalenderBuff);


#ifdef __cplusplus
}
#endif


#endif
