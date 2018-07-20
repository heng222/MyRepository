/************************************************************************
*
* �ļ���   ��  ParsePackAtsData.c
* ����ʱ�� ��  2014.04.14
* ����     ��  ZC��
* �������� ��  �������ATS���ݹ���  
* ��  ע   ��  ��
*
************************************************************************/

#include "ParsePackAtsData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../CommTarget/CommTargetConfigData.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"

ZcAndAtsIODataStruct gZcToAtsDataStru;                     /*ZC��ATS����*/

/*
* ������������ȡ�����ATS���������±��Ӧ�����ݳ���
* ����˵���� ��
* ����ֵ  �� ZC��ATS�����ݳ���     
*/
UINT16_S GetZcToAtsIdDataBufLen(void)
{
	return gZcToAtsDataStru.ValueBuffLen;
}

/*
* ���������� ��ȡ�����Ats���������±��Ӧ��������Ϣ
* ����˵���� ��
* ����ֵ  ��ZC��ATS��������׵�ַ      
*/
UINT8_S* GetZcToAtsDataBuff(void)
{
	return gZcToAtsDataStru.ValueBuff;
}

/*
* ���������� ��ZC��ATS����
* ����˵���� const UINT8* dataBuf,��������   
*            const UINT16_S dataLen,���ݳ���
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S PackZcToAtsFrameData(const UINT8_S* dataBuf,const UINT16_S dataLen)/*-bye- ɾ���˵���������*/
{
	UINT8_S rtnValue= DEFAULT_ZERO;

	if (dataBuf != NULL)
	{
		/*-bye- ���ա�ZC-ATS�ӿ�˵���顷�޸Ĵ���*/

		/*�����ӿ�����*/
		if (0U == MemoryCpy(&gZcToAtsDataStru.ValueBuff[DEFAULT_ZERO],(UINT32_S)ZC_ATS_COM_BYTE_SUM_MAX,dataBuf,((UINT32_S)dataLen)))
		{
			/*��д������Ϣ*/
			gZcToAtsDataStru.ValueBuffLen = dataLen;

            rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			/*����������*/
			gZcToAtsDataStru.ValueBuffLen = 0U;

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
* ���������� ��ձ�����Ats�����Ϣ
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearCycleAtsOutputData(void)
{
	MemorySet(&gZcToAtsDataStru,((UINT32_S)(sizeof(ZcAndAtsIODataStruct))),
                DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndAtsIODataStruct))));
}
