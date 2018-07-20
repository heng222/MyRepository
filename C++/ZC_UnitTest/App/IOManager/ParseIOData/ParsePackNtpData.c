/************************************************************************
*
* �ļ���   ��  ParsePackNtpData.c
* ����ʱ�� ��  2014.04.14
* ����     ��  ZC��
* �������� ��  �������Ntp���ݹ���  
* ��  ע	��  ��
*
************************************************************************/

#include "ParsePackNtpData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../CommTarget/CommTargetStatusData.h"
#include "../CommTarget/CommTargetConfigData.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"
#include "../../SysDataManager/SysConfigData.h"

ZcAndNtpIODataStruct gNtpToZcDataStru;            /*Ntp���͸�ZC������*/
ZcAndNtpIODataStruct gZcToNtpDataStru;            /*ZC���͸�Ntp������*/

/*
* ���������� ��ȡNtp�����ZC�����ݳ���
* ����˵���� ��
* ����ֵ  �� 0: ��ȡʧ��
*			 >0: ���ݳ���      
*/
UINT16_S GetNtpToZcDataLen(void)
{
	return gNtpToZcDataStru.ValueBuffLen;
}

/*
* ���������� ��ȡNtp�����ZC��������Ϣ
* ����˵���� ��
* ����ֵ  ��  NULL: ��ȡʧ��
*			 !NULL: ��ȡ�ɹ�     
*/
UINT8_S* GetNtpToZcDataBuff(void)
{
	return gNtpToZcDataStru.ValueBuff;
}


/*
* ���������� ��ȡZC�����Ntp�����ݳ���
* ����˵���� ��
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 >0: ���ݳ���      
*/
UINT16_S GetZcToNtpDataLen(void)
{
	return gZcToNtpDataStru.ValueBuffLen;
}

/*
* ���������� ��ȡZC�����Ntp��������Ϣ
* ����˵���� ��
* ����ֵ  �� NULL: ��ȡʧ��
*			 !NULL: ��ȡ�ɹ�      
*/
UINT8_S* GetZcToNtpDataBuff(void)
{
	return gZcToNtpDataStru.ValueBuff;
}

/*
* ���������� ����Ntp����ĵ�֡����
* ����˵���� const UINT8_S dataBuff[], ���ݻ�����
*            const UINT16_S dataLength, ���ݳ���
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseNtpToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength)
{
	UINT8_S sourceId = DEFAULT_ZERO;
	UINT8_S tempRtn = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S rtnCpy = DEFAULT_ZERO;

	if ((dataBuff != NULL) && (dataLength > 0U))
	{
		/*����֡ͷ,NtpĬ��IDΪ1*/
		sourceId = 1U;

		tempRtn = GetCommTargetIdInConfigData(INNER_DEVTYPE_NTP,((UINT16_S)sourceId));

		if (RETURN_SUCCESS == tempRtn)
		{
			/*��ȡͨ������*/
			gNtpToZcDataStru.NtpId = sourceId;

			gNtpToZcDataStru.ValueBuffLen = dataLength;

			rtnCpy = MemoryCpy(gNtpToZcDataStru.ValueBuff,((UINT32_S)(ZC_NTP_COM_BYTE_SUM_MAX)),&dataBuff[0],((UINT32_S)dataLength));

			if (0U == rtnCpy)
			{
				/*���ڱ�ZCͨ��NTP, ����ͨ��״̬*/
				SetCommTargetStatus(INNER_DEVTYPE_NTP,((UINT16_S)sourceId),COMM_STATUS_NORMAL);
				SetCommTargetCycle(INNER_DEVTYPE_NTP,((UINT16_S)sourceId),DEFAULT_ZERO);
				rtnValue = RETURN_SUCCESS;
			} 
			else
			{
				gNtpToZcDataStru.ValueBuffLen = 0U;
				rtnValue = RETURN_ERROR;
			}
		} 
		else
		{
			/*������Ч*/
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}
	
	return rtnValue;
}

/*
* ���������� ��Ntp֡����
* ����˵���� UINT8* dataBuff,��������   
*            const UINT16_S dataLen,���ݳ���
*            const UINT16_S commNtpId,ͨ�ŵ�NtpId(Ԥ��)
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S PackZcToNtpFrameData(const UINT8_S* dataBuff,const UINT16_S dataLen,const UINT16_S commNtpId)
{
	UINT16_S index = 0U;/*�α�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

    gZcToNtpDataStru.ValueBuff[index]= INNER_DEVTYPE_ZC;
    index = index + 1U;

	gZcToNtpDataStru.ValueBuff[index]= (UINT8_S)GetLocalZcId();
    index = index + 1U;

	gZcToNtpDataStru.ValueBuff[index]= INNER_DEVTYPE_NTP;
    index = index + 1U;

	gZcToNtpDataStru.ValueBuff[index]= 1U;
    index = index + 1U;
	
	if (dataBuff != NULL)
	{
		/*�����ӿ�����*/
		if (0U == MemoryCpy(&gZcToNtpDataStru.ValueBuff[index],((UINT32_S)(ZC_NTP_COM_BYTE_SUM_MAX - (UINT32_S)index)),dataBuff,((UINT32_S)dataLen)))
		{
			/*��д������Ϣ*/
			gZcToNtpDataStru.ValueBuffLen = index + dataLen;

            rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			/*����������*/
			gZcToNtpDataStru.ValueBuffLen = 0U;

			rtnValue = RETURN_ERROR;
		}

		
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ձ��������������Ntp������Ϣ
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearCycleNtpInputData(void)
{
	MemorySet(&gNtpToZcDataStru,((UINT32_S)(sizeof(ZcAndNtpIODataStruct))),
                 DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndNtpIODataStruct))));
}

/*
* ���������� ��ձ��������������Ntp������Ϣ
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearCycleNtpOutputData(void)
{
	MemorySet(&gZcToNtpDataStru,((UINT32_S)(sizeof(ZcAndNtpIODataStruct))),
                 DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndNtpIODataStruct))));
}
