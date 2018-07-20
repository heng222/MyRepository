/************************************************************************
*
* �ļ���   ��  DataVersionConfigData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ���ݰ汾��������
* ��  ע   ��  ��
*
************************************************************************/

#include "DataVersionConfigData.h"

DataVersionStruct gLocalDataVersionStru;                 /*���屾�����ݵİ汾����Ϣ*/

/*
* ���������� ��ȡZC�Լ����ݰ汾����Ϣ
* ����˵���� const UINT8 bufSize,���buf��С
*            UINT8_S mapVersionBuff[],���ӵ�ͼ�汾�Ż�������    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			1: ��ȡ���ݳɹ�
*/
UINT8_S GetSelfDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[])
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;

	if ((SINGLE_VERSION_LEN_MAX <= bufSize)
		&& (NULL != mapVersionBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
		{
			mapVersionBuff[cycle] = gLocalDataVersionStru.SelfDataVersion[cycle];
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
* ���������� ��ȡZC��ATP�Աȵ����ݰ汾����Ϣ
* ����˵���� const UINT8 bufSize,���buf��С
*            UINT8_S mapVersionBuff[],���ӵ�ͼ�汾�Ż�������    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			1: ��ȡ���ݳɹ�
*/
UINT8_S GetZcAtpDataVersionData(const UINT8_S bufSize,UINT8_S mapVersionBuff[])
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;

    if ((SINGLE_VERSION_LEN_MAX <= bufSize)
        && (NULL != mapVersionBuff))
    {
        for (cycle = DEFAULT_ZERO;cycle < SINGLE_VERSION_LEN_MAX;cycle++)
        {
            mapVersionBuff[cycle] = gLocalDataVersionStru.ZcATPDataVersion[cycle];
        }

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}