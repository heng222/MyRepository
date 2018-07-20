/********************************************************
*                                                                                                            
* �� �� ���� AdptAppExtDevDataInterface.h   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ������Ӧ�ò�ͨ�Žӿڽṹ����Ľӿ�ͷ�ļ� 
* ��    ע�� �� 
*
********************************************************/ 

#ifndef ADPT_APP_ExtDev_DATA_INTERFACE_H_
#define ADPT_APP_ExtDev_DATA_INTERFACE_H_


#include "../../Common/Copy.h"
#include "../../Common/CommonTypes.h"


#define COM_WITHOUT_PRO       0u            /* ͨ�Ų���Ҫͨ��Э�� */
#define COM_WITH_RSSP         1u            /* ͨ����Ҫͨ��RSSPЭ�� */

#define RCV_ERROR          0xFFFFFFFFu   /* Ӧ�û�ȡ���ݵ�������Ϊ��Ч���� */

typedef struct ComProCfg
{
    UINT8_S comSrcType;
    UINT8_S comDstType;
    UINT8_S protocolFlag;
}ComProCfgStruct;



#ifdef __cplusplus
extern "C" {
#endif

UINT8_S AdptAppExtDevSndData( UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId);

/*
* ���������� ��ȡ��������
* ����˵���� 
*              char* pDataBuf, ���ݻ�����
*              int dataLen, ���ݻ���������
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
*/
UINT32_S AdptAppExtDevRcvData(UINT8_S* pDataBuf, const UINT32_S dataLen, UINT8_S *pDevType, UINT8_S *pDevId);

/* 
* ������������ȡ�豸��ͨ��״̬��¼��־
* ����˵����
* ����ֵ  ��    1 ������ 0 ������
*/
UINT8_S AdptAppGetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId);


#ifdef __cplusplus
}
#endif


#endif
