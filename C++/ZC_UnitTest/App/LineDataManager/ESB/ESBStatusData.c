/************************************************************************
*
* �ļ���   ��  ESBStatusData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����ͣ����ť״̬����
* ��  ע   ��  ��
*
************************************************************************/
#include "ESBStatusData.h"
#include "ESBConfigData.h"

EsbDataStruct gEsbDataStruBuff[ESB_LOCAL_SUM_MAX];          /*���ع���Ľ���ͣ����ť״̬��Ϣ*/

/*
* ���������� ��ȡ����ͣ����ť����
* ����˵���� void    
* ����ֵ  �� NULL: ��ȡ����ʧ��
*			 !NULL: ����ͣ����ť����
*/
EsbDataStruct* GetEsbStatusData(void)
{
	return gEsbDataStruBuff;
}

/*
* ���������� ��ȡ����ͣ����ť��ǰ״̬
* ����˵���� esbId ����ͣ����ťID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ͣ����ť״̬
*/
UINT8_S GetEsbStatus(const UINT16_S esbId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetEsbConfigBufIndex(esbId);  /*��ȡ�����±�*/

	if (bufIndex < GetEsbSum())
	{
		rtnValue = gEsbDataStruBuff[bufIndex].EsbStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ���ý���ͣ����ť��ǰ״̬
* ����˵���� esbId ����ͣ����ťID; 
*	         esbStatus ����ͣ����ť״̬    
* ����ֵ  �� 0U;ʧ��
*            1;�ɹ�
*/
UINT8_S SetEsbStatus(const UINT16_S esbId,UINT8_S esbStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetEsbConfigBufIndex(esbId);  /*��ȡ�����±�*/

	if (bufIndex < GetEsbSum())
	{
		if ((ESB_STATE_DOWN == esbStatus) || (ESB_STATE_UP == esbStatus))
		{
			gEsbDataStruBuff[bufIndex].EsbStatus = esbStatus;
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
