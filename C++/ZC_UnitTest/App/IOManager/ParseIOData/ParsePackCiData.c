/************************************************************************
*
* �ļ���   ��  ParsePackCiData.c
* ����ʱ�� ��  2015.08.14
* ����     ��  ZC��
* �������� ��  �����ʹ����������
* ��  ע	��  ��
*
************************************************************************/

#include "ParsePackCiData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../CommTarget/CommTargetConfigData.h"
#include "../CommTarget/CommTargetStatusData.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Convert.h"
#include "../../MaintainManager/MaintainManager.h"


ZcAndCiIODataStruct gToCiDataStruBuff[COMM_CI_SUM_MAX];                      /*zc��ci�����ݽṹ*/
UINT16_S gToCiDataIdBuff[LINE_CI_SUM_MAX] = {LINE_CI_SUM_MAX};              /*ID��������*/
UINT8_S  gToCiCurSum = 0U;                                                  /*ZC���CI���������*/

ZcAndCiIODataStruct gCiInDataStruBuff[COMM_CI_SUM_MAX];                      /*ci��������ݽṹ*/
UINT16_S gCiInDataIdBuff[LINE_CI_SUM_MAX] = {LINE_CI_SUM_MAX};              /*ID��������*/
UINT8_S  gCiInCurSum = 0U;                                                  /*CI������������*/

/*
* ���������� ����CI����ĵ�֡����
* ����˵���� const UINT8 dataBuff[], ���ݻ�����
*            const UINT16_S dataLength, ���ݳ���
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseCiToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength)
{
	UINT8_S sourceId = DEFAULT_ZERO;
	UINT8_S tempRtn = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S copyRtn = DEFAULT_ZERO;
    UINT8_S checkRtn = DEFAULT_ZERO;

	if ((dataBuff != NULL) && (dataLength > 0U))
	{
		/*����֡ͷ,�ж��Ƿ�Ϊ��ZCͨ�ŵ�CI*/
		sourceId = dataBuff[1];
		tempRtn = GetCommTargetIdInConfigData(INNER_DEVTYPE_CI,((UINT16_S)sourceId));
		checkRtn = CiInputDataValidityCheck(dataBuff,dataLength);

		if ((RETURN_SUCCESS == tempRtn) && (1U == checkRtn))
		{
			/*��ȡͨ������*/
			if ((LINE_CI_SUM_MAX == gCiInDataIdBuff[sourceId]) && (LINE_CI_SUM_MAX > gCiInCurSum))
			{
				/*��дId��Ϣ*/
				gCiInDataStruBuff[gCiInCurSum].CiId = sourceId;

				/*��ȡ���ݳ���*/
				gCiInDataStruBuff[gCiInCurSum].MaskValueBuffLen = dataLength - 4U;
				
				copyRtn = MemoryCpy(gCiInDataStruBuff[gCiInCurSum].MaskValueBuff,((UINT32_S)(ZC_TO_CI_MASK_SUM_MAX)),&dataBuff[4],((UINT32_S)gCiInDataStruBuff[gCiInCurSum].MaskValueBuffLen));

				if (0U == copyRtn)
				{
					/*��������*/
					gCiInDataIdBuff[sourceId] = gCiInCurSum;

					/*��������*/
					gCiInCurSum++;

					/*���ڱ�ZCͨ��Ci, ����ͨ��״̬*/
					SetCommTargetStatus(INNER_DEVTYPE_CI,((UINT16_S)sourceId),COMM_STATUS_NORMAL);
					SetCommTargetCycle(INNER_DEVTYPE_CI,((UINT16_S)sourceId),DEFAULT_ZERO);

					rtnValue = RETURN_SUCCESS;
				} 
				else
				{
					/*�����Ϣ*/
					gCiInDataIdBuff[sourceId] = LINE_CI_SUM_MAX;
					gCiInDataStruBuff[gCiInCurSum].CiId = DEFAULT_ZERO;
					gCiInDataStruBuff[gCiInCurSum].MaskValueBuffLen = DEFAULT_ZERO;
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
			/*������Ч*/
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		/*������Ч*/
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� У��CI�����������ȷ��
* ����˵���� const UINT8_S dataBuff[],��������   
*            const UINT16_S dataLen,���ݳ���
* ����ֵ  �� 0:�Ϸ���У��ʧ��
*			 1:�Ϸ���У��ɹ�      
*/
UINT8_S CiInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen)
{
    UINT8_S rtnValue = 0U;

    if((NULL != dataBuff) && (dataLen > 0U))
    {
        if ((INNER_DEVTYPE_CI == dataBuff[0]) && (INNER_DEVTYPE_ZC == dataBuff[2]))
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
        rtnValue = 0U;
    }

    return rtnValue;
}
/*
* ���������� ��ȡCi����Zc���������
* ����˵���� void
* ����ֵ  �� 0: ʧ��
*			 >0: ����      
*/
UINT8_S GetCiToZcCurSum(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if ((gCiInCurSum > 0U) && (COMM_CI_SUM_MAX >= gCiInCurSum))
	{
		rtnValue = gCiInCurSum; 
	} 
	else
	{
		rtnValue = DEFAULT_ZERO;
	}

	return rtnValue;
}

/*
* ������������ȡCi����Zc��Id��ӦCIid
* ����˵���� const UINT8 ciIdOfIndex
* ����ֵ  �� COMM_CI_SUM_MAX: ʧ��
*			 >=0U: �ɹ�      
*/
UINT16_S GetCiToZcBuffIndexOfCiId(const UINT8_S ciIdOfIndex)
{
	UINT16_S rtnValue = COMM_CI_SUM_MAX;

    if (COMM_CI_SUM_MAX <= ciIdOfIndex)
    {
        rtnValue = COMM_CI_SUM_MAX;
    } 
    else
    {
        rtnValue = (UINT16_S)gCiInDataStruBuff[ciIdOfIndex].CiId;
    }

	return rtnValue;
}
/*
* ������������ȡCi����Zc��Id��Ӧ���ݳ���
* ����˵���� const UINT8 ciIdOfIndex
* ����ֵ  �� 0: ʧ��
*			 >0: �ɹ�      
*/
UINT16_S GetCiToZcIdDataBuffLen(const UINT8_S ciIdOfIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (COMM_CI_SUM_MAX <= ciIdOfIndex)
	{
        rtnValue = DEFAULT_ZERO;
    } 
	else
	{
        rtnValue = gCiInDataStruBuff[ciIdOfIndex].MaskValueBuffLen;
	}

	return rtnValue;
}

/*
* ���������� ��ȡCi����Zc��Id��Ӧ�±�
* ����˵���� const UINT8 ciIdOfIndex
* ����ֵ  �� NULL: ʧ��
*			 ��NULL: �ɹ�      
*/
UINT8_S* GetCiToZcDataBuffByIndex(const UINT8_S ciIdOfIndex)
{
	UINT8_S *pRtnBuff = NULL;

    if (COMM_CI_SUM_MAX <= ciIdOfIndex)
    {
        pRtnBuff = NULL;
    } 
    else
    {
        pRtnBuff = gCiInDataStruBuff[ciIdOfIndex].MaskValueBuff;
    }

	return pRtnBuff;
}

/*
* ���������� ��������Ci�ĵ�֡����
* ����˵����  const UINT8_S dataBuff[], ���ݻ�����
*             UINT16_S dataLength, ���ݳ���
*             UINT16_S destId, Ŀ��CI�豸ID
* ����ֵ  �� 0: ���ݴ��ʧ��
*			 1: ���ݴ���ɹ�      
*/
UINT8_S PackZcToCiFrameData(const UINT8_S dataBuff[], UINT16_S dataLength,UINT16_S destId)
{
	UINT16_S index = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S copyRtn = 1U;

	if ((dataBuff != NULL) && (dataLength > 0U))
	{
		/*��д��λ��Ϣ����֡ͷ*/
		if (LINE_CI_SUM_MAX <= gToCiCurSum)
		{
            /*������Ч*/
            rtnValue = RETURN_ERROR;			
		}
		else
		{			
            gToCiDataStruBuff[gToCiCurSum].CiId = (UINT8_S)destId;

            /*��������*/
            gCiInDataIdBuff[destId] = gToCiCurSum;

            /*��д��Ϣ֡ͷ��Ϣ*/
            /*��дԴ�豸*/
            gToCiDataStruBuff[gToCiCurSum].MaskValueBuff[index] = INNER_DEVTYPE_ZC;
            index = index + 1U;

            gToCiDataStruBuff[gToCiCurSum].MaskValueBuff[index] = (UINT8_S)GetLocalZcId();
            index = index + 1U;

            /*��дĿ���豸*/
            gToCiDataStruBuff[gToCiCurSum].MaskValueBuff[index] = INNER_DEVTYPE_CI;
            index = index + 1U;

            gToCiDataStruBuff[gToCiCurSum].MaskValueBuff[index] = (UINT8_S)destId;
            index = index + 1U;

            gToCiDataStruBuff[gToCiCurSum].MaskValueBuffLen = dataLength + index;

            /*��������*/
            copyRtn = MemoryCpy(&gToCiDataStruBuff[gToCiCurSum].MaskValueBuff[index],((UINT32_S)(ZC_TO_CI_MASK_SUM_MAX)),dataBuff,((UINT32_S)dataLength));

            if (1U == copyRtn)
            {
                /*�����Ϣ*/
                gToCiDataStruBuff[gToCiCurSum].CiId = 0U;		
                gCiInDataIdBuff[destId] = LINE_CI_SUM_MAX;
                gToCiDataStruBuff[gToCiCurSum].MaskValueBuffLen = DEFAULT_ZERO;

                rtnValue = RETURN_ERROR;
            } 
            else
            {
                /*��������*/
                gToCiCurSum++;
                rtnValue = RETURN_SUCCESS;
            }
		}	
	}
	else
	{
		/*������Ч*/
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡZC���CI���������
* ����˵���� void
* ����ֵ  �� 0: ʧ��
*			 >0: �ɹ�     
*/
UINT8_S GetToCiCurSum(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if ((gToCiCurSum > 0U) && (COMM_CI_SUM_MAX >= gToCiCurSum))
	{
		rtnValue = gToCiCurSum; 
	} 
	else
	{
		rtnValue = DEFAULT_ZERO;
	}

	return rtnValue;
}

/*
* ���������� ��ȡZC���CI��Id���ݳ���
* ����˵���� const UINT8 ciIdOfIndex
* ����ֵ  �� 0: ʧ��
*			 >0: �ɹ�      
*/
UINT16_S GetToCiIdDataBuffLen(const UINT8_S ciIdOfIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((COMM_CI_SUM_MAX <= ciIdOfIndex))
	{
        rtnValue = DEFAULT_ZERO;
	} 
	else
	{       
        rtnValue = gToCiDataStruBuff[ciIdOfIndex].MaskValueBuffLen;
	}

	return rtnValue;
}

/*
* ���������� ��ȡZC���CI��Id��Ӧ�±�����
* ����˵���� const UINT8 ciIdOfIndex
* ����ֵ  �� NULL: ʧ��
*			 ��NULL: �ɹ�      
*/
UINT8_S* GetToCiDataBuffByIndex(const UINT8_S ciIdOfIndex)
{
	UINT8_S *pRtnBuff = NULL;

    if (COMM_CI_SUM_MAX <= ciIdOfIndex)
    {
        pRtnBuff = NULL;
    } 
    else
    {
        pRtnBuff = gToCiDataStruBuff[ciIdOfIndex].MaskValueBuff;
    }

	return pRtnBuff;
}


/*
* ���������� ��ձ��������������CI������Ϣ
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearCycleCiInputData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	/*�������*/
	for (cycle = 0U;cycle < COMM_CI_SUM_MAX;cycle++)
	{
		MemorySet(&gCiInDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndCiIODataStruct))),
                   DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndCiIODataStruct))));
	}
	
	/*�����������*/
	gCiInCurSum = 0U;

	/*��չ�������*/
	for (cycle = 0U;cycle < LINE_CI_SUM_MAX;cycle++)
	{
		gCiInDataIdBuff[cycle] = LINE_CI_SUM_MAX;
	}
}

/*
* ���������� ��ձ��������������CI������Ϣ
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearCycleCiOutputData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	/*�������*/
	for (cycle = 0U;cycle < COMM_CI_SUM_MAX;cycle++)
	{
		MemorySet(&gToCiDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndCiIODataStruct))),
                     DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndCiIODataStruct))));
	}

	/*����������*/
	gToCiCurSum = 0U;

	/*��չ�������*/
	for (cycle = 0U;cycle < LINE_CI_SUM_MAX;cycle++)
	{
		gToCiDataIdBuff[cycle] = LINE_CI_SUM_MAX;
	}
}
