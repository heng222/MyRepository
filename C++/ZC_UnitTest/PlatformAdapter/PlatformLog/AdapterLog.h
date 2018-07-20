/********************************************************
*                                                                                                            
* �� �� ���� AdapterLog.h   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ������ṩ��ƽ̨�����־��¼�ӿ�ͷ�ļ� 
* ��    ע�� �� 
*
********************************************************/ 

#ifndef ADAPTER_LOG_H_
#define ADAPTER_LOG_H_

#include "../../Common/CommonTypes.h"
#include "../../Common/CRC16.h"
#include "../AdptHandle/AdapterExtDevInOutManage.h"
#include "../PlatItf/AdptPlatServiceInterface.h"

#define MAX_LOG_LEN (DEV_TOTAL_FRAME_LEN*MAX_SND_PIPE_NUM)

#define LOG_RECORD_TYPE 0xFFu      /* log record �������� */
#define LOG_RECORD_HEAD_LEN 30u    /* log record ͷ����(����β��CRC16) */
#define LOG_RECORD_VER 1u          /* log record �汾�� */


#ifdef __cplusplus
extern "C" {
#endif



/*
* ���������� ��ӡlog��Ϣ
* ����˵���� ��
* ����ֵ  �� -1:  ʧ��
*            !=-1: �ɹ�
*/
UINT8_S AdptAppLogPrintf(UINT8_S chRunSystem, const CHAR_S * lpszFormat, ...);

/*
* ���������� ������������ת��Ϊ�ַ���
* ����˵����UINT8 *dataBuf������ַ���(�������) 
            const UINT16 dataLength,��Ҫת���ĳ���
            const UINT16 useLen,���ÿռ�
*��������ֵ��0,ת������  1��ת������  2,�ռ䲻��
*/
UINT8_S AdptAppLogPrintBuff(const UINT8_S dataBuf[],const UINT16_S bufLength, const UINT16_S dataLength );

/*
* ���������� ���������־������
* ����˵���� ��
* ����ֵ  �� void
*/
void AdptAppLogBufPeriodClear(void);


/*
* ���������� �������ά����Ϣ�������� 
* ����˵���� UINT8_S destDevType,const UINT8_S destDevId
* ����ֵ  �� void
*/
void AdptAppLogDataPack(const UINT8_S destDevType,const UINT8_S destDevId);

/*
* ���������� �������ά����Ϣ����¼���� 
* ����˵���� UINT8_S destDevType,const UINT8_S destDevId, const UINT8_S* logBuff, const UINT32_S logLen 
* ����ֵ  �� void
*/
void AdptAppLogRecordPack(const UINT8_S destDevType,const UINT8_S destDevId, const UINT8_S* logBuff, const UINT32_S logLen);


#ifdef __cplusplus
}
#endif

#endif
