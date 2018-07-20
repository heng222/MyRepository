/************************************************************************
*
* �ļ���   ��  CommTargetConfigData.c
* ��  ��	��  ZC��
* ����ʱ�� ��  2015.07.14
* �������� ��  ͨѶĿ������ 
* ��  ע	��  ��
*
************************************************************************/

#include "CommTargetConfigData.h"

CommTargetConfigDataStruct gCommTargetConfigDataStru[COMM_TYPE_SUM_MAX];               /*����ͨ�Ŷ���������Ϣ*/
UINT8_S gCommTargetTypeCurSum = DEFAULT_ZERO;                                                       /*����ͨ�Ŷ�������*/

/*
* �������ƣ� GetCommTargetTypeBuffIndex
* ���������� ��ȡͨ�����ʹ洢�±�
* ��������� const UINT8 commTargetType ͨ���豸����    
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ǰ����
*/
UINT8_S GetCommTargetTypeBuffIndex(const UINT8_S commTargetType)
{
	UINT8_S rtnValue = COMM_TYPE_SUM_MAX;
	UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
	for (cycle = DEFAULT_ZERO;cycle < allCommTargetSum;cycle++)
	{
		if (gCommTargetConfigDataStru[cycle].CommTargetType == commTargetType)
		{
			rtnValue = cycle;
			break;
		} 
		else
		{
            /*������*/
		}
	}

	return rtnValue;
}

/*
* �������ƣ� GetCommTargetTypeSum
* ���������� ��ȡͨ�����;�����
* ��������� void    
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ǰ����
*/
UINT8_S GetCommTargetTypeSum(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if (gCommTargetTypeCurSum >= COMM_TYPE_SUM_MAX)
	{
		rtnValue = DEFAULT_ZERO;
	} 
	else
	{
		rtnValue = gCommTargetTypeCurSum;
	}	

	return rtnValue;
}

/*
* �������ƣ�GetSingleCommTargetTypeSum
* ���������� ��ȡĳ��ͨ���豸����
* ��������� const UINT8 commTargetType ͨ���豸���� 
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ǰ����
*/
UINT8_S GetSingleCommTargetTypeSum(const UINT8_S commTargetType)
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S commTypeIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
	commTypeIndex = GetCommTargetTypeBuffIndex(commTargetType);

	if (commTypeIndex < allCommTargetSum)
	{
		rtnValue = gCommTargetConfigDataStru[commTypeIndex].CommTargetNum;
	}
	else
	{
        /*������*/
	}
	
	return rtnValue;
}

/*
* �������ƣ� GetSingleCommTargetIdBuff
* ���������� ��ȡĳ���豸��ͨ��ID����
* ��������� const UINT8 commTargetType ͨ���豸����   
*            const UINT8_S bufSize �����С
* ��������� UINT16_S commTargetIdBuff[] �������
* ����ֵ  �� 0u: ��ȡ����ʧ��
*			 1u: ��ȡ���ݳɹ�
*/
UINT8_S GetSingleCommTargetIdBuff(const UINT8_S commTargetType,const UINT8_S bufSize,UINT16_S commTargetIdBuff[])
{
	UINT8_S commTypeIndex = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;
    UINT8_S singleCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
	commTypeIndex = GetCommTargetTypeBuffIndex(commTargetType);   
    singleCommTargetSum = GetSingleCommTargetTypeSum(commTargetType);

	if ((commTypeIndex < allCommTargetSum)
		&& (bufSize >= SINGLE_TYPE_COMM_TARGET_SUM_MAX)
		&& (commTargetIdBuff != NULL))
	{
		for (cycle = DEFAULT_ZERO;cycle < singleCommTargetSum;cycle++)
		{
			commTargetIdBuff[cycle] = gCommTargetConfigDataStru[commTypeIndex].CommTargetIdBuff[cycle];
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
* �������ƣ� GetSingleCommProtocolType
* ���������� ��ȡĳ��ͨ�Ŷ���ʹ�õ�Э������
* ��������� const UINT8 commTargetType ͨ���豸����    
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ǰ����
*/
UINT8_S GetSingleCommProtocolType(const UINT8_S commTargetType)
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S commTypeIndex = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
	commTypeIndex = GetCommTargetTypeBuffIndex(commTargetType);

	if (commTypeIndex < allCommTargetSum)
	{
		rtnValue = gCommTargetConfigDataStru[commTypeIndex].CommProtocolType;
	}
	else
	{
        /*������*/
	}

	return rtnValue;
}

/*
* �������ƣ� GetCommTargetIdInConfigData
* ���������� ��ȡͨ�Ŷ���Id�Ƿ����ڱ�ZCͨ�ŷ�Χ
* ��������� const UINT8 commTargetType, ͨѶĿ�������    
*            const UINT16_S commTargetId,ͨѶĿ��ı��
* ��������� ��
* ����ֵ  �� 0u: ������
*			 1u: ����      
*/
UINT8_S GetCommTargetIdInConfigData(const UINT8_S commTargetType, const UINT16_S commTargetId)
{
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S commTypeIndex = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S findFlag = DEFAULT_ZERO;
    UINT8_S allCommTargetSum = DEFAULT_ZERO;

    allCommTargetSum = GetCommTargetTypeSum();
	commTypeIndex = GetCommTargetTypeBuffIndex(commTargetType);

	if (commTypeIndex < allCommTargetSum)
	{
		for (cycle = DEFAULT_ZERO; cycle < gCommTargetConfigDataStru[commTypeIndex].CommTargetNum;cycle++)
		{
			if (gCommTargetConfigDataStru[commTypeIndex].CommTargetIdBuff[cycle] == commTargetId)
			{
				findFlag = FLAG_SET;
				break;
			} 
			else
			{
                /*������*/
			}
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	if (FLAG_SET == findFlag)
	{
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
