/************************************************************************
*
* �ļ���   ��  DataVersionConfigData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ���ݰ汾��������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef DATA_VERSION_CONFIG_DATA_H_
#define DATA_VERSION_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "DataVersionDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*���嵥�����ݰ汾*/
typedef struct DataVersionStruct
{
	UINT8_S  SelfDataVersion[SINGLE_VERSION_LEN_MAX];      /* ZC�Լ��õ����ݰ汾��Ϣ */
    UINT8_S  ZcATPDataVersion[SINGLE_VERSION_LEN_MAX];     /* ZC��ATP���ݰ汾��Ϣ */
}DataVersionStruct;

/*
* ���������� ��ȡZC�Լ����ݰ汾����Ϣ
* ����˵���� const UINT8 bufSize,���buf��С
*            UINT8_S mapVersionBuff[],���ӵ�ͼ�汾�Ż�������    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			1: ��ȡ���ݳɹ�
*/
UINT8_S GetSelfDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[]);

/*
* ���������� ��ȡZC��ATP�Աȵ����ݰ汾����Ϣ
* ����˵���� const UINT8 bufSize,���buf��С
*            UINT8_S mapVersionBuff[],���ӵ�ͼ�汾�Ż�������    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			1: ��ȡ���ݳɹ�
*/
UINT8_S GetZcAtpDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[]);

#ifdef __cplusplus
}
#endif

#endif
