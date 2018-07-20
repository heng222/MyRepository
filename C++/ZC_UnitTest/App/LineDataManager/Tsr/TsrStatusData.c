/************************************************************************
*
* �ļ���   ��  TsrStatusData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��ʱ����״̬����
* ��  ע   ��  ��
*
************************************************************************/
#include "TsrDefine.h"
#include "TsrStatusData.h"
#include "../../SysDataManager/SysConfigData.h"

TsrDataStruct gTsrDataStruBuff[TSR_BUFF_SUM_MAX];                  /*���ع������ʱ����������Ϣ*/
UINT16_S gTsrOfZcIdBuff[LINE_ZC_SUM_MAX] = {TSR_BUFF_SUM_MAX};    /*������ʱ���٣�ZC��ӳ������*/
UINT16_S gTsrOfZcCurSum = 0U;                                     /*��ʱ���٣�ZC����ǰ����*/

/*
* ���������� ��ȡ��ZC����Χ�ڵ�ǰ��ʱ������������
*	        ����������ZC���͹������л������ڵ���ʱ���٣�
* ����˵���� void    
* ����ֵ  �� TSR_BUFF_SUM_MAX: ��ȡ����ʧ��
*			>=0: ��ǰZC��������
*/
UINT16_S GetTsrOfZcSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gTsrOfZcCurSum >= TSR_BUFF_SUM_MAX)
	{
		rtnValue = TSR_BUFF_SUM_MAX;
	} 
	else
	{
		rtnValue = gTsrOfZcCurSum;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������±��Ӧ������ZCID
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ZCID      
*/
UINT16_S GeTsrOfBelongZcId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetTsrOfZcSum())
	{
		rtnValue = gTsrDataStruBuff[bufIndex].BelongZcId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������±��Ӧ����ʱ������Ϣ
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� NULL: ��ȡ����ʧ��
*			!NULL: ��Ϣ      
*/
TsrDataStruct* GeTsrDataStructOfIndex(const UINT16_S bufIndex)
{
	TsrDataStruct* pRtnValue = DEFAULT_ZERO;

	if (bufIndex < GetTsrOfZcSum())
	{
		pRtnValue = &gTsrDataStruBuff[bufIndex];
	} 
	else
	{
		pRtnValue = NULL;
	}

	return pRtnValue;
}

/*
* ���������� ��ȡָ��ZCID��ʱ�����±�
* ����˵���� const UINT16 zcId,zcID
* ����ֵ  �� TSR_BUFF_SUM_MAX; ��ȡ����ʧ��
*			 >0;���������ɹ�
*/
UINT8_S GeZcIdOfTsrBufIndex(const UINT16_S zcId)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if ((zcId >= 1U)&&(zcId < LINE_ZC_SUM_MAX))
	{
		rtnValue = (UINT8_S)(gTsrOfZcIdBuff[zcId]);
	}
	else
	{
		rtnValue = TSR_BUFF_SUM_MAX;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ZCID��ʱ��������
* ����˵���� const UINT16 zcId,zcID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ������Ϣ     
*/
UINT8_S GetZcIdOfTsrNum(const UINT16_S zcId)
{
	UINT8_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GeZcIdOfTsrBufIndex(zcId);  /*��ȡ�����±�*/

	if (bufIndex < GetTsrOfZcSum())
	{
		rtnValue = gTsrDataStruBuff[bufIndex].TsrNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����ָ��ZC�±���ʱ��������
* ����˵���� const UINT8 tsrOfZcBufIndex,��ʱ���ٶ�Ӧ��ZC�±� 
*            const UINT8_S tsrNum,��ʱ��������
* ����ֵ  �� 0: ʧ��
*			>0: �ɹ�     
*/
UINT8_S SetZcIdOfTsrNum(const UINT8_S tsrOfZcBufIndex,const UINT8_S tsrNum)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if (tsrOfZcBufIndex < TSR_BUFF_SUM_MAX)
	{
		gTsrDataStruBuff[tsrOfZcBufIndex].TsrNum = tsrNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ZCID��Ӧ��ĳ���±��µ���ʱ���ٶ�Ӧ���ٶ�ֵ
* ����˵���� const UINT16 zcId, ZCID
*	         const UINT16_S singleBufIndex buf�±�   
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ĳ����ʱ������Ϣ(���߼�����ID����Ϊ����ֵ)      
*/
UINT8_S GetSingleTsrDataOfSpeed(const UINT16_S zcId,const UINT16_S singleBufIndex)
{
	UINT8_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GeZcIdOfTsrBufIndex(zcId);  /*��ȡ�����±�*/

	if (bufIndex < GetTsrOfZcSum())
	{
		if (singleBufIndex < gTsrDataStruBuff[bufIndex].TsrNum)
		{
			rtnValue = gTsrDataStruBuff[bufIndex].SingleTsrDataStru[singleBufIndex].Speed;
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
* ���������� ����ָ��ZCID��Ӧ��ĳ���±��µ���ʱ���ٶ�Ӧ���ٶ�ֵ
* ����˵���� const UINT8 tsrOfZcBufIndex,�洢��ʱ���ٹ�����ZCid��Ӧ�±�
*	         const UINT16_S singleBufIndex,����ZC��ʱ����buf�±�
*            const UINT16_S speed,��ʱ�����ٶ�
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ĳ����ʱ������Ϣ(���߼�����ID����Ϊ����ֵ)      
*/
UINT8_S SetSingleTsrDataOfSpeed(const UINT8_S tsrOfZcBufIndex,const UINT16_S singleBufIndex, const UINT16_S speed)
{
	UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S lineMaxTSRSpeed = DEFAULT_ZERO;
	
	lineMaxTSRSpeed = GetLineMaxTSRSpeed();
	
	if ((tsrOfZcBufIndex < TSR_BUFF_SUM_MAX)
		&& (speed <= lineMaxTSRSpeed))
	{
		gTsrDataStruBuff[tsrOfZcBufIndex].SingleTsrDataStru[singleBufIndex].Speed = (UINT8_S)(speed);

		rtnValue = RETURN_SUCCESS ;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ZCID��Ӧ��ĳ���±�����ʱ���ٶ�Ӧ���߼���������
* ����˵���� const UINT16 zcId, ZCID
*	         const UINT16_S singleBufIndex buf�±�   
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����      
*/
UINT8_S GetSingleTsrDataOfSectionNum(const UINT16_S zcId,const UINT16_S singleBufIndex)
{
	UINT8_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GeZcIdOfTsrBufIndex(zcId);  /*��ȡ�����±�*/

	if (bufIndex < GetTsrOfZcSum())
	{
		if (singleBufIndex < gTsrDataStruBuff[bufIndex].TsrNum)
		{
			rtnValue = gTsrDataStruBuff[bufIndex].SingleTsrDataStru[singleBufIndex].SectionNum;
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
* ���������� ��ȡָ��ZCID��Ӧ��ĳ���±��µ���ʱ���ٶ�Ӧ���߼�����buff
* ����˵���� const UINT16 zcId, ZCID
*			 const UINT16_S bufIndex buf�±�   
*			 const UINT8_S bufSize,�����С
*            UINT16_S sectionIdBuff[],�������
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 1: ��ȡ�ɹ�      
*/
UINT8_S GetSingleTsrDataOfSectionBuff(const UINT16_S zcId,const UINT16_S singleBufIndex,const UINT8_S bufSize,UINT16_S sectionIdBuff[])
{
	UINT8_S bufIndex = 0U;     /*�����±�*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GeZcIdOfTsrBufIndex(zcId);  /*��ȡ�����±�*/

	if ((bufIndex < GetTsrOfZcSum())
		&& (bufSize >= SINGLE_TSR_SECTION_SUM_MAX) && (NULL != sectionIdBuff))
	{
		if (singleBufIndex < gTsrDataStruBuff[bufIndex].TsrNum)
		{
			for (cycle = DEFAULT_ZERO;cycle < GetSingleTsrDataOfSectionNum(zcId,singleBufIndex);cycle++)
			{
				sectionIdBuff[cycle] = gTsrDataStruBuff[bufIndex].SingleTsrDataStru[singleBufIndex].SectionIdBuff[cycle];
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

	return rtnValue;
}

/*
* ���������� ����ָ��ZCID��Ӧ��ĳ���±��µ���ʱ���ٵ��߼�����buff
* ����˵���� const UINT8 tsrOfZcBufIndex,�洢��ʱ���ٹ�����ZCid��Ӧ�±�
*	         const UINT16_S singleBufIndex,����ZC��ʱ����buf�±�  
*            const UINT8_S sectionNum,���õ���ʱ��������
*            const UINT16_S sectionIdBuff[],���õ���ʱ���ٶ�Ӧ���߼�����Id����
* ����ֵ  �� 0: ��������ʧ��
*			 1: �������ݳɹ�      
*/
UINT8_S SetSingleTsrDataOfSectionInfo(const UINT8_S tsrOfZcBufIndex,const UINT8_S singleBufIndex,const UINT8_S sectionNum,const UINT16_S sectionIdBuff[])
{
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	if ((tsrOfZcBufIndex < TSR_BUFF_SUM_MAX)
		&& (sectionNum <= SINGLE_TSR_SECTION_SUM_MAX) && (NULL !=sectionIdBuff))
	{
		gTsrDataStruBuff[tsrOfZcBufIndex].SingleTsrDataStru[singleBufIndex].SectionNum = sectionNum;

		for (cycle = DEFAULT_ZERO;cycle < sectionNum;cycle++)
		{
			gTsrDataStruBuff[tsrOfZcBufIndex].SingleTsrDataStru[singleBufIndex].SectionIdBuff[cycle] = sectionIdBuff[cycle];
		}

		rtnValue = RETURN_SUCCESS ;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ������ʱ���ٶ�Ӧ��ZC�±�
* ����˵���� const UINT16 zcId, zcId    
* ����ֵ  �� 0: ����ʧ��
*			>0: ���óɹ�      
*/
UINT8_S AplyTsrIndexOfZcId(const UINT16_S zcId)
{
	UINT16_S bufIndex = LINE_MAX_TRAIN_ID;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GeZcIdOfTsrBufIndex(zcId);

	if (TSR_BUFF_SUM_MAX == bufIndex)
	{
		/*����*/
		if (gTsrOfZcCurSum >= TSR_BUFF_SUM_MAX)
		{
			/*�������Ϣ,����ʧ��*/
		} 
		else
		{
			/*������Ϣ*/
			gTsrDataStruBuff[gTsrOfZcCurSum].BelongZcId = zcId;
			gTsrOfZcIdBuff[zcId] = gTsrOfZcCurSum;
			gTsrOfZcCurSum++;
			rtnValue = RETURN_SUCCESS;
		}
	} 
	else
	{
		if (TSR_BUFF_SUM_MAX >= bufIndex)
		{
            rtnValue = RETURN_ERROR;			
		} 
		else
		{
            gTsrDataStruBuff[bufIndex].BelongZcId = zcId;
            rtnValue = RETURN_SUCCESS;
		}
	}

	return rtnValue;
}
