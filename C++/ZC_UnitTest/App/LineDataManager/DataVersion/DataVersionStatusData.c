/************************************************************************
*
* �ļ���   ��  DataVersionStatusData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ά������
* ��  ע   ��  ��
*
************************************************************************/
#include "DataVersionConfigData.h"

DataVersionStruct gInputDataVersionStru;                 /*������������ݰ汾����Ϣ*/

/*
* ���������� ��ȡZC�Լ��汾����Ϣ
* ����˵���� const UINT8 bufSize,���buf��С
*            UINT8_S mapVersionBuff[],���ӵ�ͼ�汾�Ż�������    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 1: ��ȡ���ݳɹ�
*/
UINT8_S GetZcSelfDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[])
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;

	if ((SINGLE_VERSION_LEN_MAX <= bufSize)
		&& (NULL != mapVersionBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
		{
			mapVersionBuff[cycle] = gInputDataVersionStru.SelfDataVersion[cycle];
		}

		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����ZC�Լ��汾����Ϣ
* ����˵���� const UINT8 bufSize,���buf��С
*            const UINT8_S mapVersionBuff[],���ӵ�ͼ�汾�Ż�������    
* ����ֵ  �� 0: ��������ʧ��
*			 1: �������ݳɹ�
*/
UINT8_S SetZcSelfDataVersionData(const UINT8_S bufSize,const UINT8_S mapVersionBuff[])
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;

	if ((SINGLE_VERSION_LEN_MAX == bufSize)
		&& (NULL != mapVersionBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
		{
			gInputDataVersionStru.SelfDataVersion[cycle] = mapVersionBuff[cycle];
		}

		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}


/*
* ���������� ���ZC���ݰ汾����Ϣ
* ����˵���� ��   
* ����ֵ  �� ��
*/
void ClearZcSelfDataVersion(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
	{
		gInputDataVersionStru.SelfDataVersion[cycle] = DEFAULT_ZERO;
	}
}
