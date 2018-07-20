/************************************************************************
*
* �ļ���   ��  PSDStatusData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ������״̬����
* ��  ע   ��  ��
*
************************************************************************/
#include "PSDStatusData.h"
#include "PSDConfigData.h"

PsdDataStruct gPsdDataStruBuff[PSD_LOCAL_SUM_MAX];             /*���屾�ع����������״̬��������*/

/*
* ���������� ��ȡ����������
* ����˵���� void    
* ����ֵ  �� NULL: ��ȡ����ʧ��
*			 !NULL: ����������
*/
PsdDataStruct* GetPsdStatusData(void)
{
	return gPsdDataStruBuff;
}

/*
* ���������� ��ȡ�����ŵ�ǰ״̬
* ����˵���� psdId ������ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ������״̬
*/
UINT8_S GetPsdStatus(const UINT16_S psdId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetPsdConfigBufIndex(psdId);  /*��ȡ�����±�*/

	if (bufIndex < GetPsdSum())
	{
		rtnValue = gPsdDataStruBuff[bufIndex].PsdStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ���������ŵ�ǰ״̬
* ����˵���� psdId ������ID; 
	            psdStatus ������״̬    
* ����ֵ  �� ��
*/
UINT8_S SetPsdStatus(const UINT16_S psdId,UINT8_S psdStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetPsdConfigBufIndex(psdId);  /*��ȡ�����±�*/

	if (bufIndex < GetPsdSum())
	{
		if ((PSD_STATE_CLOSE == psdStatus) || (PSD_STATE_OPEN == psdStatus))
		{
			gPsdDataStruBuff[bufIndex].PsdStatus = psdStatus;
			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
