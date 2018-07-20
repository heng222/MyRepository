/************************************************************************
*
* �ļ���   ��  MaskConfigData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��λ��������
* ��  ע   ��  ��
*
************************************************************************/
#include "MaskConfigData.h"

ZcCiMaskConfigDataStruct gZcToCiMaskConfigDataStruBuff[COMM_CI_SUM_MAX];                              /*ZC-CI��λ��Ϣ�ṹ��*/
UINT16_S gZcToCiIdBuff[LINE_CI_SUM_MAX] = {LINE_CI_SUM_MAX};                                         /*����ZC��Ciͨ��ID��������*/
UINT8_S  gZcToCiCurSum = 0U;                                                                         /*ZC���CI���������*/

ZcCiMaskConfigDataStruct gCiToZcMaskConfigDataStruBuff[COMM_CI_SUM_MAX];                              /*CI-ZC��λ��Ϣ�ṹ��*/
UINT16_S gCiToZiIdBuff[LINE_CI_SUM_MAX] = {LINE_CI_SUM_MAX};                                         /*CI������������*/
UINT8_S  gCiToZcCurSum = 0U;

UINT16_S gToCiConfigSignalCrossIdBuff[SINGLE_ZC_TO_CI_MASK_SUM_MAX] = {DEFAULT_ZERO};              /*���屾ZC��Ҫ������źŻ���ѹ*/
UINT16_S gSignalCrossNum = 0U;

UINT16_S gToCiConfigSignalLightOffIdBuff[SINGLE_ZC_TO_CI_MASK_SUM_MAX] = {DEFAULT_ZERO};           /*���屾ZC��Ҫ������źŻ�����*/
UINT16_S gSignalLightOffNum = 0U;

/*
* ���������� ��ȡ����豸�ܸ���
* ����˵���� const UINT8 destSystemType Ŀ��ϵͳ����  
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �豸��ǰ����
*/
UINT8_S GetSendCommTargetNum(const UINT8_S destSystemType)
{
	UINT8_S returnValue = 0U;

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		if (gZcToCiCurSum >= COMM_CI_SUM_MAX)
		{
			returnValue = 0U;
		} 
		else
		{
			returnValue = gZcToCiCurSum;
		}
		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡĳ���豸��Ӧ�ķ����±�
* ����˵���� const UINT8 destSystemType Ŀ��ϵͳ����  
			 const UINT16_S destSystemId Ŀ��ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ͨ���豸���±�
*/
UINT8_S GetSendCommTargetIndex(const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT8_S returnValue = 0U;

	switch (destSystemType)
	{
		case INNER_DEVTYPE_CI:
            if ((destSystemId >= 1U)&&(destSystemId < LINE_CI_SUM_MAX ))
			{
				returnValue = (UINT8_S)gZcToCiIdBuff[destSystemId];
			}
			else
			{
				returnValue = COMM_CI_SUM_MAX;
			}
			break;

		default:
			returnValue = COMM_CI_SUM_MAX;
			break;
	}

	return returnValue;
}

/*
* ���������� ��ȡ��λ��Ϣ��������
* ����˵���� const UINT8 destSystemType Ŀ��ϵͳ���� 
*			 const UINT16_S destSystemId Ŀ��ϵͳId
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��λ��Ϣ��ǰ����
*/
UINT16_S GetSendToOtherMaskSum(const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (destSystemType)
	{
		case INNER_DEVTYPE_CI:
			commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

			if (commTargetIndex < GetSendCommTargetNum(destSystemType))
			{
				returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskCurSum;
			} 
			else
			{
				returnValue = 0U;
			}
			
			break;

		default:
			returnValue = 0U;
			break;
	}

	return returnValue;
}

/*
* ���������� ��ȡ��λID���ֵ
* ����˵���� const UINT8 destSystemType Ŀ��ϵͳ����
*			 const UINT16_S destSystemId Ŀ��ϵͳId
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��λID���ֵ
*/
UINT16_S GetSendToOtherMaskIdMax(const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{
			returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskIdMax;
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ZC����ָ��ϵͳ��λ����
* ����˵���� const UINT8 sourceSystemType, Դϵͳ����
*			 const UINT16_S sourceSystemId ԴϵͳID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��λ����      
*/
UINT16_S GetReceiveToZcMaskSum(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (sourceSystemType)
	{
		case INNER_DEVTYPE_CI:
			commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

			if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskCurSum;
			} 
			else
			{
				returnValue = 0U;
			}

			break;

		default:
			returnValue = 0U;
			break;
	}

	return returnValue;
}

/*
* ���������� ��ȡ��λID���ֵ
* ����˵���� const UINT8 destSystemType Դϵͳ����  
*			 const UINT16_S sourceSystemId ԴϵͳID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��λID���ֵ
*/
UINT16_S GetReceiveToZcMaskIdMax(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskIdMax;
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡ���͸�������ϵͳָ�������±��Ӧ����λ�±�
* ����˵���� const UINT16 bufIndex, �����±�
			 const UINT8_S destSystemType, Ŀ��ϵͳ����
			 const UINT16_S destSystemId Ŀ��ϵͳId
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��λ�±�     
*/
UINT16_S GetSendMaskId(const UINT16_S bufIndex,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{		
			if (bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
			{
				returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].MaskId;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ID��λ������
* ����˵���� const UINT16 maskId,��λID
*			 const UINT8_S destSystemType, Ŀ��ϵͳ����
*		     const UINT16_S destSystemId Ŀ��ϵͳId
* ����ֵ  �� ZC_TO_CI_MASK_SUM_MAX; ��ȡ����ʧ��
*			 >=0U;���������ɹ�
*/
UINT16_S GetSendMaskBufIndex(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (destSystemType)
	{
		case INNER_DEVTYPE_CI:
			commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

			if (commTargetIndex < GetSendCommTargetNum(destSystemType))
			{
				if ((maskId >= 1U)&&(maskId < ZC_TO_CI_MASK_SUM_MAX))
				{
					returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskIdBuff[maskId];
				}
				else
				{
					returnValue = ZC_TO_CI_MASK_SUM_MAX;
				}
			} 
			else
			{
				returnValue = ZC_TO_CI_MASK_SUM_MAX;
			}

			break;

		default:
			returnValue = ZC_TO_CI_MASK_SUM_MAX;
			break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ID��λ����λ����
* ����˵���� const UINT16 maskId,��λID
*			 const UINT8_S destSystemType, Ŀ��ϵͳ����
*			 const UINT16_S destSystemId Ŀ��ϵͳId
* ����ֵ  �� 0 : ��ȡ����ʧ��
*			 >0U; ��λ������Ϣ
*/
UINT8_S GetSendMaskType(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*�����±�*/

	switch (destSystemType)
	{
		case INNER_DEVTYPE_CI:
			commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

			if (commTargetIndex < GetSendCommTargetNum(destSystemType))
			{
				bufIndex = GetSendMaskBufIndex(maskId,destSystemType,destSystemId);  /*��ȡ�����±�*/			

				if (bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
				{
					returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].MaskType;
				}
				else
				{
					returnValue = RETURN_ERROR;
				}
			} 
			else
			{
				returnValue = 0U;
			}

			break;

		default:
			returnValue = 0U;
			break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ID��λ���豸����
* ����˵���� const UINT16 maskId,��λID
*			 const UINT8_S destSystemType, Ŀ��ϵͳ����
*			 const UINT16_S destSystemId Ŀ��ϵͳId
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 >0 �豸������Ϣ
*/
UINT8_S GetSendDeviceType(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*�����±�*/

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{
			bufIndex = GetSendMaskBufIndex(maskId,destSystemType,destSystemId);  /*��ȡ�����±�*/			

			if (bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
			{
				returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceType;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ID��λ���豸����
* ����˵���� const UINT16 maskId,��λID
*				const UINT8_S destSystemType, Ŀ��ϵͳ����
*				const UINT16_S destSystemId Ŀ��ϵͳId
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 >0 �豸����
*/
UINT8_S GetSendDeviceSum(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*�����±�*/

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{
			bufIndex = GetSendMaskBufIndex(maskId,destSystemType,destSystemId);  /*��ȡ�����±�*/			

			if (bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
			{
				returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceSum;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ID��λ���豸ID����
* ����˵���� const UINT16 maskId,��λID
*		     const UINT8_S destSystemType, Ŀ��ϵͳ����
*			 const UINT16_S destSystemId Ŀ��ϵͳId
*			 const UINT8_S bufSize,�����С
*			 UINT16_S deviceIdBuff[],�������
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 1: �ɹ�
*/
UINT8_S GetSendDeviceIdBuff(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId,const UINT8_S bufSize,UINT16_S deviceIdBuff[])
{
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = 0U;
	UINT8_S cycle = 0U;

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{
			bufIndex = GetSendMaskBufIndex(maskId,destSystemType,destSystemId);  /*��ȡ�����±�*/			

			if ((bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
				&& (bufSize >= SINGLE_MASK_DEVICE_SUM_MAX)
				&& (deviceIdBuff != NULL))
			{
				for (cycle = 0U;cycle < GetSendDeviceSum(maskId,destSystemType,destSystemId);cycle++)
				{
					deviceIdBuff[cycle] = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceIdBuff[cycle];
				}
				rtnValue = RETURN_SUCCESS ;
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

		break;

	default:
		rtnValue = RETURN_ERROR;
		break;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��λ�Ĺ�����λId
* ����˵���� const UINT16 maskId,��λID
*			 const UINT8_S destSystemType, Ŀ��ϵͳ����
*			 const UINT16_S destSystemId Ŀ��ϵͳId
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 >0 ������λID
*/
UINT16_S GetSendRelevanceMaskId(const UINT16_S maskId,const UINT8_S destSystemType,const UINT16_S destSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*�����±�*/

	switch (destSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetSendCommTargetIndex(destSystemType,destSystemId);

		if (commTargetIndex < GetSendCommTargetNum(destSystemType))
		{
			bufIndex = GetSendMaskBufIndex(maskId,destSystemType,destSystemId);  /*��ȡ�����±�*/			

			if (bufIndex < GetSendToOtherMaskSum(destSystemType,destSystemId))
			{
				returnValue = gZcToCiMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].RelevanceMaskId;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡ�����豸�ܸ���
* ����˵���� const UINT8 sourceSystemId ԴϵͳID  
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �豸��ǰ����
*/
UINT8_S GetReceiveCommTargetNum(const UINT8_S sourceSystemId)
{
	UINT8_S returnValue = 0U;

	switch (sourceSystemId)
	{
	case INNER_DEVTYPE_CI:
		if (gCiToZcCurSum >= COMM_CI_SUM_MAX)
		{
			returnValue = 0U;
		} 
		else
		{
			returnValue = gCiToZcCurSum;
		}
		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡ����ĳ���豸���±�
* ����˵���� const UINT8 sourceSystemType Դϵͳ����  
*			 const UINT16_S sourceSystemId ԴĿ��ID
* ����ֵ  �� COMM_CI_SUM_MAX: ��ȡ����ʧ��
*			>0: ͨѶ������±�
*/
UINT8_S GetReceiveCommTargetIndex(const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT8_S returnValue = 0U;

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		if ((sourceSystemId >= 1U)&&(sourceSystemId < LINE_CI_SUM_MAX))
		{
			returnValue = (UINT8_S)gCiToZiIdBuff[sourceSystemId];
		}
		else
		{
			returnValue = COMM_CI_SUM_MAX;
		}
		break;

	default:
		returnValue = COMM_CI_SUM_MAX;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ�����������±��Ӧ����λ�±�
* ����˵���� const UINT16 bufIndex, �����±�
*			 const UINT8_S sourceSystemType, Դϵͳ����
*			 const UINT8_S sourceSystemId ԴϵͳID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��λID     
*/
UINT16_S GetReceiveMaskId(const UINT16_S bufIndex,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{			
			if (bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].MaskId;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ID��λ������
* ����˵���� const UINT16 maskId,��λID
*			 const UINT8_S sourceSystemType, Դϵͳ����
*			 const UINT16_S sourceSystemId ԴϵͳID
* ����ֵ  �� CI_TO_ZC_MASK_SUM_MAX: ��ȡ����ʧ��
*			 >0 ���������ɹ�
*/
UINT16_S GetReceiveMaskBufIndex(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			if ((maskId >= 1U)&&(maskId < CI_TO_ZC_MASK_SUM_MAX))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskIdBuff[maskId];
			}
			else
			{
				returnValue = CI_TO_ZC_MASK_SUM_MAX;
			}
		} 
		else
		{
			returnValue = CI_TO_ZC_MASK_SUM_MAX;
		}

		break;

	default:
		returnValue = CI_TO_ZC_MASK_SUM_MAX;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ID��λ����λ����
* ����˵���� const UINT16 maskId,��λID
*			const UINT8_S sourceSystemType, Դϵͳ����
*			const UINT16_S sourceSystemId ԴϵͳID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 >0 ��λ������Ϣ
*/
UINT8_S GetReceiveMaskType(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*�����±�*/

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			bufIndex = GetReceiveMaskBufIndex(maskId,sourceSystemType,sourceSystemId);  /*��ȡ�����±�*/			

			if (bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].MaskType;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ID��λ���豸����
* ����˵���� const UINT16 maskId,��λID
*			 const UINT8_S sourceSystemType, Դϵͳ����
*			 const UINT16_S sourceSystemId ԴϵͳID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 >0:�豸������Ϣ
*/
UINT8_S GetReceiveDeviceType(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*�����±�*/

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			bufIndex = GetReceiveMaskBufIndex(maskId,sourceSystemType,sourceSystemId);  /*��ȡ�����±�*/			

			if (bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceType;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ID��λ���豸����
* ����˵���� const UINT16 maskId,��λID
*			 const UINT8_S sourceSystemType, Դϵͳ����
*			 const UINT16_S sourceSystemId ԴϵͳID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 >0 �豸����
*/
UINT8_S GetReceiveDeviceSum(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT8_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*�����±�*/

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			bufIndex = GetReceiveMaskBufIndex(maskId,sourceSystemType,sourceSystemId);  /*��ȡ�����±�*/			

			if (bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceSum;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡָ��ID��λ���豸ID����
* ����˵���� const UINT16 maskId,��λID
*			 const UINT8_S sourceSystemType, Դϵͳ����
*			 const UINT16_S sourceSystemId ԴϵͳID
*			 const UINT8_S bufSize,�����С
*			 UINT16_S deviceIdBuff[],�������
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 1: ��ȡ���ݳɹ�
*/
UINT8_S GetReceiveDeviceIdBuff(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId,const UINT8_S bufSize,UINT16_S deviceIdBuff[])
{
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S cycle = 0U;
	UINT8_S rtnValue = 0U;

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			bufIndex = GetReceiveMaskBufIndex(maskId,sourceSystemType,sourceSystemId);  /*��ȡ�����±�*/			

			if ((bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
				&& (bufSize >= SINGLE_MASK_DEVICE_SUM_MAX)
				&& (deviceIdBuff != NULL))
			{
				for (cycle = 0U;cycle < GetReceiveDeviceSum(maskId,sourceSystemType,sourceSystemId);cycle++)
				{
					deviceIdBuff[cycle] = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].DeviceIdBuff[cycle];
				}
				rtnValue = RETURN_SUCCESS ;
			}
			else
			{
				rtnValue = RETURN_ERROR ;
			}
		} 
		else
		{
			rtnValue = RETURN_ERROR ;
		}

		break;

	default:
		rtnValue = RETURN_ERROR ;
		break;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��λ�Ĺ�����λId
* ����˵���� const UINT16 maskId,��λID
*			 const UINT8_S sourceSystemType, Դϵͳ����
*			 const UINT16_S sourceSystemId ԴϵͳID
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 >0 ������λID
*/
UINT16_S GetReceiveRelevanceMaskId(const UINT16_S maskId,const UINT8_S sourceSystemType,const UINT16_S sourceSystemId)
{
	UINT16_S returnValue = 0U;
	UINT8_S commTargetIndex = 0U;
	UINT16_S bufIndex = 0U;     /*�����±�*/

	switch (sourceSystemType)
	{
	case INNER_DEVTYPE_CI:
		commTargetIndex = GetReceiveCommTargetIndex(sourceSystemType,sourceSystemId);

		if (commTargetIndex < GetReceiveCommTargetNum(sourceSystemType))
		{
			bufIndex = GetReceiveMaskBufIndex(maskId,sourceSystemType,sourceSystemId);  /*��ȡ�����±�*/			

			if (bufIndex < GetReceiveToZcMaskSum(sourceSystemType,sourceSystemId))
			{
				returnValue = gCiToZcMaskConfigDataStruBuff[commTargetIndex].MaskConfigDataStru[bufIndex].RelevanceMaskId;
			}
			else
			{
				returnValue = RETURN_ERROR;
			}
		} 
		else
		{
			returnValue = 0U;
		}

		break;

	default:
		returnValue = 0U;
		break;
	}

	return returnValue;
}

/*
* ���������� ��ȡ��ZC�������źŻ���ѹ�����źŻ���
* ����˵���� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����
*/
UINT16_S GetMaskOfSignalCorssNum(void)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

	if (gSignalCrossNum < SINGLE_ZC_TO_CI_MASK_SUM_MAX)
	{
		rtnValue = gSignalCrossNum;
	} 
	else
	{
		rtnValue = DEFAULT_ZERO;
	}

    return rtnValue;
}

/*
* ���������� ��ȡ��ZC�������źŻ���ѹ�����źŻ�Id��Ϣ
* ����˵���� const UINT16 buffSize,buff��С
*            UINT16_S signalIdBuff[],�źŻ�IdBuff
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ���ݳɹ�
*/
UINT8_S GetMaskOfSignalCorssIdBuff(const UINT16_S buffSize,UINT16_S signalIdBuff[])
{
	UINT16_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO; 

	if ((buffSize >= SINGLE_ZC_TO_CI_MASK_SUM_MAX) && (NULL != signalIdBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < GetMaskOfSignalCorssNum();cycle++)
		{
			signalIdBuff[cycle] = gToCiConfigSignalCrossIdBuff[cycle];
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
* ���������� ��ȡ��ZC�������źŻ����������źŻ���
* ����˵���� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����
*/
UINT16_S GetMaskOfSignalLightOffNum(void)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

	if (gSignalLightOffNum < SINGLE_ZC_TO_CI_MASK_SUM_MAX)
	{
		rtnValue = gSignalLightOffNum;
	} 
	else
	{
		rtnValue = DEFAULT_ZERO;
	}

    return rtnValue;
}

/*
* ���������� ��ȡ��ZC�������źŻ����������źŻ�Id��Ϣ
* ����˵���� const UINT16 buffSize,buff��С
*            UINT16_S signalIdBuff[],�źŻ�IdBuff
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ���ݳɹ�
*/
UINT8_S GetMaskOfSignalLightOffIdBuff(const UINT16_S buffSize,UINT16_S signalIdBuff[])
{
	UINT16_S cycle = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

	if ((buffSize >= SINGLE_ZC_TO_CI_MASK_SUM_MAX) && (NULL != signalIdBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < GetMaskOfSignalLightOffNum();cycle++)
		{
			signalIdBuff[cycle] = gToCiConfigSignalLightOffIdBuff[cycle];
		}

		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

    return rtnValue;
}
