/************************************************************************
*
* �ļ���   ��  PSDConfigData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��������������
* ��  ע   ��  ��
*
************************************************************************/
#include "PSDConfigData.h"

PsdConfigDataStruct gPsdConfigDataStruBuff[PSD_LOCAL_SUM_MAX];          /*���ع����������������Ϣ*/
UINT16_S gPsdIdBuff[PSD_SUM_MAX] = {PSD_LOCAL_SUM_MAX};                                /*����������ӳ������*/
UINT16_S gPsdCurSum = 0U;                                              /*�����ŵ�ǰ����*/
                                                
/*
* ���������� ��ȡ�����Ź�������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �����ŵ�ǰ����
*/
UINT16_S GetPsdSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gPsdCurSum >= PSD_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gPsdCurSum;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������±��Ӧ��������ID
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ������ID      
*/
UINT16_S GetPsdId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetPsdSum())
	{
		rtnValue = gPsdConfigDataStruBuff[bufIndex].PsdId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID������������
* ����˵���� const UINT16 psbId,������ID
* ����ֵ  �� PSD_LOCAL_SUM_MAX; ��ȡ����ʧ��
*			  >=0U;���������ɹ�
*/
UINT16_S GetPsdConfigBufIndex(const UINT16_S psdId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((psdId >= 1U) && (psdId < PSD_SUM_MAX))
	{
		rtnValue = gPsdIdBuff[psdId];
	}
	else
	{
		rtnValue = PSD_LOCAL_SUM_MAX;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��IDվ̨��������������ID
* ����˵���� const UINT16 psbId,������ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������ID      
*/
UINT8_S GetPsdBelongCiId(const UINT16_S psdId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetPsdConfigBufIndex(psdId);  /*��ȡ�����±�*/

	if (bufIndex < GetPsdSum())
	{
		rtnValue = gPsdConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID����������ZcID
* ����˵���� const UINT16 psbId, ������ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ZcID      
*/
UINT8_S GetPsdBelongZcId(const UINT16_S psdId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetPsdConfigBufIndex(psdId);  /*��ȡ�����±�*/

	if (bufIndex < GetPsdSum())
	{
		rtnValue = gPsdConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�����Ź�����������
* ����˵���� const UINT16 psbId, ������ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT16_S GetPsdChangeAttribute(const UINT16_S psdId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetPsdConfigBufIndex(psdId);  /*��ȡ�����±�*/

	if (bufIndex < GetPsdSum())
	{
		rtnValue = gPsdConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
