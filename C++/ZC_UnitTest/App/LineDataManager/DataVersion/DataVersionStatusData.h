/************************************************************************
*
* �ļ���   ��  DataVersionStatusData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ���ݰ汾
* ��  ע   ��  ��
*
************************************************************************/
#ifndef DATA_VERSION_STATUS_DATA_H_
#define DATA_VERSION_STATUS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "DataVersionDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* ���������� ��ȡZC�Լ��汾����Ϣ
* ����˵���� const UINT8 bufSize,���buf��С
*            UINT8_S mapVersionBuff[],���ӵ�ͼ�汾�Ż�������    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 1: ��ȡ���ݳɹ�
*/
UINT8_S GetZcSelfDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[]);

/*
* ���������� ����ZC�Լ��汾����Ϣ
* ����˵���� const UINT8 bufSize,���buf��С
*            const UINT8_S mapVersionBuff[],���ӵ�ͼ�汾�Ż�������    
* ����ֵ  �� 0: ��������ʧ��
*			 1: �������ݳɹ�
*/
UINT8_S SetZcSelfDataVersionData(const UINT8_S bufSize,const UINT8_S mapVersionBuff[]);	

/*
* ���������� ���ZC���ݰ汾����Ϣ
* ����˵���� ��   
* ����ֵ  �� ��
*/
void ClearZcSelfDataVersion(void);

	
#ifdef __cplusplus
}
#endif

#endif
