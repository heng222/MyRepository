/************************************************************************
*
* �ļ���   ��  ParsePackProcessManager.c
* ����ʱ�� ��  2015.08.14
* ����     ��  ZC��
* �������� ��  ���������ZC���ݹ���  
* ��  ע	��  ��
*
************************************************************************/

#include "ParsePackProcessManager.h"
#include "../../../Common/CircQueueStruct.h"
#include "../IOInterfaceProcess/IOInterfaceProcess.h"
#include "../../SysDataManager/SysDefine.h"
#include "ParsePackCiData.h"
#include "ParsePackAtsData.h"
#include "ParsePackTrainData.h"
#include "ParsePackZcData.h"
#include "ParsePackNtpData.h"
#include "../../TsrManager/TsrInterface.h"/*-bye-*/
#include "../../../Common/MemSet.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/Convert.h"

/*
* ���������� ������������
* ����˵���� void
* ����ֵ  �� void      
*/
void ParseInputData(void)
{
	/*�����������������*/
	ClearInputDataProcess();

	/*����Ats��������*/
	ParseAtsToZcData();/*-bye-*/

	/*����CI��������*/
	ParseCiToZcData();

	/*��������ATP��������*/
	ParseTrainToZcData();

	/*����CI��������*/
	ParseNZcToZcData();

	/*����Ntp��������*/
	ParseNtpToZcData();
}

/*
* ���������� ����������ݴ���
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearInputDataProcess(void)
{
	/*���ATS��������*/
	ClearCycleAtsOutputData();/*-bye-*/

	/*���������������*/
	ClearCycleCiInputData();

	/*��ճ���Atp���������*/
	ClearCycleTrainInputData();

	/*�������ZC���������*/
	ClearCycleNZcInputData();

	/*���NTP���������*/
	ClearCycleNtpInputData();
}

/*
* ���������� ����CI��������
* ����˵���� void
* ����ֵ  �� 1,��ӳɹ�
*            0,���ʧ��     
*/
UINT8_S ParseCiToZcData(void)
{
	CirQueueStruct *ciToZcDataQueueStru = NULL;
	UINT32_S pkgCount = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT32_S dataLen = DEFAULT_ZERO;
	UINT8_S tempDataBuff[ZC_CI_COM_BYTE_SUM_MAX] = {0U};
	UINT8_S breakFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ȡCI��ZC����������*/
	ciToZcDataQueueStru = GetCiToZcDataQueueStru();

	/*�ж��Ƿ�*/
	if (ciToZcDataQueueStru != NULL)
	{
		pkgCount = GetQueuePkgCount(ciToZcDataQueueStru); /*��ȡ�������ݰ�����*/

		for (cycle = 0U; cycle < pkgCount; cycle++)
		{
			/*��ճ���*/
			dataLen = DEFAULT_ZERO;
			MemorySet(tempDataBuff,((UINT32_S)(ZC_CI_COM_BYTE_SUM_MAX)),0U,((UINT32_S)(ZC_CI_COM_BYTE_SUM_MAX)));

			/*��ȡһ֡����*/
			dataLen = GetQueuePkgData(ciToZcDataQueueStru, tempDataBuff, DATA_LEN_MAX); 

			if (dataLen > 0U)
			{ 
				/*��ȡ�ɹ�*/
				ParseCiToZcFrameData(tempDataBuff, (UINT16_S)dataLen); 

				/*��ӡ�յ�CI����*/
				/*LogPrintf(1U,"29.001 CI [%d] Input,len=%d!!!\n",tempDataBuff[1],dataLen);*/
			}
			else
			{
				breakFlag = FLAG_SET;
				break;
			}
		}

		if (FLAG_SET == breakFlag)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
		
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��������ATP��������
* ����˵���� void
* ����ֵ  �� 1,��ӳɹ�
*            0,���ʧ��      
*/
UINT8_S ParseTrainToZcData(void)
{
	CirQueueStruct *pTrainToZcDataQueueStru = NULL;
	UINT32_S pkgCount = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT32_S dataLen = DEFAULT_ZERO;
	UINT8_S tempDataBuff[ZC_TRAIN_COM_BYTE_SUM_MAX] = {0U};
	UINT8_S breakFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ȡ����ATP��ZC����������*/
	pTrainToZcDataQueueStru = GetTrainToZcDataQueueStru();

	/*�ж��Ƿ�*/
	if (pTrainToZcDataQueueStru != NULL)
	{
		pkgCount = GetQueuePkgCount(pTrainToZcDataQueueStru); /*��ȡ�������ݰ�����*/

		for (cycle = 0U; cycle < pkgCount; cycle++)
		{
			/*��ճ���*/
			dataLen = DEFAULT_ZERO;
			MemorySet(tempDataBuff,((UINT32_S)(ZC_TRAIN_COM_BYTE_SUM_MAX)),DEFAULT_ZERO,((UINT32_S)(ZC_TRAIN_COM_BYTE_SUM_MAX)));

			/*��ȡһ֡����*/
			dataLen = GetQueuePkgData(pTrainToZcDataQueueStru, tempDataBuff, DATA_LEN_MAX); 

			if (dataLen > 0U)
			{ 
				/*��ȡ�ɹ�*/
				ParseTrainToZcFrameData(tempDataBuff, (UINT16_S)dataLen); 
			}
			else
			{
				breakFlag = FLAG_SET;
				break;
			}
		}

		if (FLAG_SET == breakFlag)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����NZc��������
* ����˵���� void
* ����ֵ  �� 1,��ӳɹ�
*            0,���ʧ��      
*/
/*����CI��������*/
UINT8_S ParseNZcToZcData(void)
{
	CirQueueStruct *pNzcToZcDataQueueStru = NULL;
	UINT32_S pkgCount = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT32_S dataLen = DEFAULT_ZERO;
	UINT8_S tempDataBuff[ZC_NZC_COM_BYTE_SUM_MAX];
	UINT8_S breakFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ȡ����ATP��ZC����������*/
	pNzcToZcDataQueueStru = GetNZcToZcDataQueueStru();

	/*�ж��Ƿ�*/
	if (pNzcToZcDataQueueStru != NULL)
	{
		pkgCount = GetQueuePkgCount(pNzcToZcDataQueueStru); /*��ȡ�������ݰ�����*/

		for (cycle = DEFAULT_ZERO; cycle < pkgCount; cycle++)
		{
			/*��ճ���*/
			dataLen = DEFAULT_ZERO;
			MemorySet(tempDataBuff,((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)),DEFAULT_ZERO,((UINT32_S)(ZC_NZC_COM_BYTE_SUM_MAX)));

			/*��ȡһ֡����*/
			dataLen = GetQueuePkgData(pNzcToZcDataQueueStru, tempDataBuff, DATA_LEN_MAX); 

			if (dataLen > 0U)
			{ 
				/*��ȡ�ɹ�*/
				ParseNzcToZcFrameData(tempDataBuff,(UINT16_S)dataLen); 
				/*LogPrintf(1U,"29.201  ParseNZc=%d,Input Data!\n",tempDataBuff[16]);*/
			}
			else
			{
				breakFlag = FLAG_SET;
				break;
			}
		}

		if (FLAG_SET == breakFlag)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}

	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����ats��������
* ����˵���� void
* ����ֵ  �� �ɹ����������ݰ�������    
*/
UINT8_S ParseAtsToZcData(void)/*-bye-*/
{
	UINT8_S pktQuan = DEFAULT_ZERO;
	pktQuan = Tsr_ParseIncomingDatas();/*-bye-*/
	return pktQuan;
}


/*
* ���������� ����Ntp��������
* ����˵���� void
* ����ֵ  �� 1,��ӳɹ�
*            0,���ʧ��      
*/
UINT8_S ParseNtpToZcData(void)
{
	CirQueueStruct *pNtpToZcDataQueueStru = NULL;
	UINT32_S pkgCount = DEFAULT_ZERO;
	UINT8_S cycle = DEFAULT_ZERO;
	UINT32_S dataLen = DEFAULT_ZERO;
	UINT8_S tempDataBuff[ZC_NTP_COM_BYTE_SUM_MAX] = {DEFAULT_ZERO};
	UINT8_S breakFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ȡNtp��ZC����������*/
	pNtpToZcDataQueueStru = GetNtpToZcDataQueueStru();

	/*�ж��Ƿ�*/
	if (pNtpToZcDataQueueStru != NULL)
	{
		pkgCount = GetQueuePkgCount(pNtpToZcDataQueueStru); /*��ȡ�������ݰ�����*/

		for (cycle = DEFAULT_ZERO; cycle < pkgCount; cycle++)
		{
			/*��ճ���*/
			dataLen = DEFAULT_ZERO;
			MemorySet(tempDataBuff,((UINT32_S)(ZC_NTP_COM_BYTE_SUM_MAX)),DEFAULT_ZERO,((UINT32_S)(ZC_NTP_COM_BYTE_SUM_MAX)));

			/*��ȡһ֡����*/
			dataLen = GetQueuePkgData(pNtpToZcDataQueueStru, tempDataBuff, DATA_LEN_MAX); 

			if (dataLen > 0U)
			{ 
				/*��ȡ�ɹ�,��������*/
				ParseNtpToZcFrameData(tempDataBuff, (UINT16_S)dataLen); 
			}
			else
			{
				breakFlag = FLAG_SET;
				break;
			}
		}

		if (FLAG_SET == breakFlag)
		{
			rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
		}

	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��֡�������
* ����˵���� void
* ����ֵ  �� void      
*/
void PackOutputData(void)
{
	/*��֡�����CI������*/
	PackZcToCiData();

	/*��֡�����ATS������*/
	PackZcToAtsData();

	/*��֡���������ATP������*/
	PackZcToTrainData();

	/*��֡�����NZc������*/
	PackZcToNZcData();

	/*��֡�����Ntp������*/
	PackZcToNtpData();
	
	/*��ձ������������*/
	ClearOutputDataProcess();
}

/*
* ���������� ���������ݴ���
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearOutputDataProcess(void)
{
	/*��������������*/
	ClearCycleCiOutputData();

	/*��ճ���Atp���������*/
	ClearCycleTrainOutputData();

	/*�������ZC���������*/
	ClearCycleNZcOutputData();

	/*���Ats���������*/
	ClearCycleAtsOutputData();

	/*���Ntp���������*/
	ClearCycleNtpOutputData();
}

/*
* ���������� ��֡�����CI������
* ����˵���� void
* ����ֵ  �� 1,��ӳɹ�
*            0,���ʧ��
*/
UINT8_S PackZcToCiData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;
	CirQueueStruct* pZcToCiQueueStru = NULL;            /*�������ݶ���*/
	UINT32_S realDataLen = DEFAULT_ZERO;
	UINT8_S *pTempDataBuff = NULL;                     /*��ʱ���ݻ�����*/
    UINT8_S rtnValue = 0U;

	pZcToCiQueueStru = GetZcToCiDataQueueStru();

	for (cycle = 0U;cycle < GetToCiCurSum();cycle++)
	{
		realDataLen = (UINT32_S)GetToCiIdDataBuffLen(cycle);
		pTempDataBuff = GetToCiDataBuffByIndex(cycle);

		if ((realDataLen > 0U) && (NULL != pTempDataBuff))
		{
			if(0 == AddQueueData(pZcToCiQueueStru, pTempDataBuff, realDataLen))
            {
                rtnValue = 1U;
            }
            else
            {
                rtnValue = 0U;
            }
		}
		else
		{
            /*������*/
		}	
	}

	return rtnValue;
}

/*
* ���������� ��֡���������ATP������
* ����˵���� void
* ����ֵ  �� 1,��ӳɹ�
*            0,���ʧ��     
*/
UINT8_S PackZcToTrainData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;
	CirQueueStruct* pZcToTrainQueueStru = NULL;            /*�������ݶ���*/
	UINT32_S realDataLen = DEFAULT_ZERO;
	UINT8_S *pTempDataBuff = NULL;                     /*��ʱ���ݻ�����*/
    UINT8_S rtnValue = 0U;

	pZcToTrainQueueStru = GetZcToTrainDataQueueStru();

	for (cycle = 0U;cycle < GetToTrainCurSum();cycle++)
	{
		realDataLen = (UINT32_S)GetToTrainIdDataBufLen(cycle);
		pTempDataBuff = GetToTrainBufDataOfIndex(cycle);

		if ((realDataLen > 0U) && (NULL != pTempDataBuff))
		{
			if (0 == AddQueueData(pZcToTrainQueueStru, pTempDataBuff, realDataLen))
			{
                rtnValue = 1U;
			} 
			else
			{
                rtnValue = 0U;
			}
			
		}
		else
		{
            /*������*/
		}	
	}

	return rtnValue;
}

/*
* ���������� ��֡�����Ntp������
* ����˵���� void
* ����ֵ  �� 1,��ӳɹ�
*            0,���ʧ��      
*/
UINT8_S PackZcToNtpData(void)
{
	CirQueueStruct* pZcToNtpQueueStru = NULL;            /*�������ݶ���*/
	UINT32_S realDataLen = DEFAULT_ZERO;
	UINT8_S *tempDataBuf = NULL;                     /*��ʱ���ݻ�����*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	pZcToNtpQueueStru = GetZcToNtpDataQueueStru();
	realDataLen = (UINT32_S)GetZcToNtpDataLen();
	tempDataBuf = GetZcToNtpDataBuff();
    
	if ((realDataLen > 0U) 
		&& (NULL != tempDataBuf)
		&& (NULL != pZcToNtpQueueStru))
	{
		if (0 == AddQueueData(pZcToNtpQueueStru, tempDataBuf, realDataLen))
		{
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

/*
* ���������� ��֡�����NZc������
* ����˵���� void
* ����ֵ  �� 1,��ӳɹ�
*            0,���ʧ��      
*/
UINT8_S PackZcToNZcData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;
	CirQueueStruct* pZcToNZcQueueStru = NULL;            /*�������ݶ���*/
	UINT32_S realDataLen = DEFAULT_ZERO;
	UINT8_S *pTempDataBuff = NULL;                     /*��ʱ���ݻ�����*/
    UINT8_S rtnValue = DEFAULT_ZERO;

	pZcToNZcQueueStru = GetZcToNZcDataQueueStru();

	for (cycle = DEFAULT_ZERO;cycle < GetZcToNZcCurSum();cycle++)
	{
		realDataLen = (UINT32_S)GetZcToNZcIdDataBufLen(cycle);
		pTempDataBuff = GetZcToNZcBufDataOfIndex(cycle);

		if ((realDataLen > 0U) && (NULL != pTempDataBuff))
		{
			if(0 == AddQueueData(pZcToNZcQueueStru, pTempDataBuff, realDataLen))
            {
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
	}

	return rtnValue;
}

/*
* ���������� ��֡�����Ats������
* ����˵���� void
* ����ֵ  ��  void   
*/
void PackZcToAtsData(void)/*-bye-*/
{
	PackTsrCommandsToAts();/*-bye-*/
}
