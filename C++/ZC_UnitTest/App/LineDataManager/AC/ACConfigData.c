/********************************************************
*                                                                                                            
* �� �� ���� ACConfigData.c   
* ����ʱ�䣺 2015-05-01
* ��    �ߣ� 
* ���������� �����������ݹ���  
* ��  ע  ��  ��
*
********************************************************/ 

#include "ACConfigData.h"


AcConfigDataStruct gAcConfigDataStruBuff[LOCAL_AC_SUM_MAX];   /*���屾ZC�����������ýṹ��*/
UINT16_S gLocalAcIndexBuff[AC_SUM_MAX] = {LOCAL_AC_SUM_MAX}; /*���屾ZC�����±�����*/
UINT16_S gAcCurSum = 0U;									 /*��ZC���ᵱǰ����*/

/*
* ���������� ��ȡָ��ID����������
* ����˵���� const UINT16 acId, ����ID
* ����ֵ  �� LOCAL_AC_SUM_MAX �� AC_SUM_MAX: ��ȡ����ʧ��
*			<LOCAL_AC_SUM_MAX: ���ҳɹ�
*/
UINT16_S GetAcConfigBufIndex(const UINT16_S acId)
{
	UINT16_S rtnIndex = LOCAL_AC_SUM_MAX;

	if ((1U <= acId) && (acId < AC_SUM_MAX))
	{
		rtnIndex = gLocalAcIndexBuff[acId];
    }

	return rtnIndex;
}

/*
* ���������� ��ȡ���ᵱǰ����
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ��������ʧ��
*			>0: ���ᵱǰ����
*/
UINT16_S GetAcCurSum(void)
{
	UINT16_S rtnSum = 0U;

    if (LOCAL_AC_SUM_MAX >= gAcCurSum)
    {
        rtnSum =  gAcCurSum;
    }

	return rtnSum;
}

/*
* ���������� ��ȡָ�������±��Ӧ�ļ�������ID
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ACID      
*/
UINT16_S GetAcId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (LOCAL_AC_SUM_MAX > GetAcCurSum())
	{
		rtnValue = gAcConfigDataStruBuff[bufIndex].AcId;
	} 

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID������������ID
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������ID      
*/
UINT16_S GetAcBelongCiId(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT16_S rtnCiId = 0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnCiId = gAcConfigDataStruBuff[bufIndex].BelongCiId;
	}

	return rtnCiId;
}

/*
* ���������� ��ȡָ��ID��������Zc ID
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ZC ID      
*/
UINT16_S GetAcBelongZcId(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT16_S rtnZcId = 0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnZcId = gAcConfigDataStruBuff[bufIndex].BelongZcId;
	}

	return rtnZcId;
}

/*
* ���������� ��ȡָ��ID������������
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 0x55-������������
*			 0xaa-��������������   
*/
UINT8_S GetAcType(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtntype = 0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtntype = gAcConfigDataStruBuff[bufIndex].AcType;
	}

	return rtntype;
}

/*
* ���������� ��ȡָ��ID����߽������
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0:������
*            FLAG_SET:����
*/
UINT8_S GetAcBoundaryType(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtntype = 0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtntype = gAcConfigDataStruBuff[bufIndex].ChangeAttribute;
	}

	return rtntype;
}

/*
* ���������� ��ȡָ��ID��������ĵ�������
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0xff: ��ȡ����ʧ��
*			 >=0: ��������  
*/
UINT8_S GetAcSwitchNum(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtntype = 0xffU;

	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtntype = gAcConfigDataStruBuff[bufIndex].SwitchNum;
	}

	return rtntype;
}

/*
* ���������� ��ȡָ��ID��������ĵ�����Ϣ
* ����˵���� const UINT16 acId, ����ID 
*            const UINT8_S bufSize,��С
*            SwitchInAcStruct switchInAcStruBuff[],������Ϣ
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 1: ��ȡ���ݳɹ�   
*/
UINT8_S GetAcSwitchInfo(const UINT16_S acId,const UINT8_S bufSize,SwitchInAcStruct switchInAcStruBuff[])
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S swtichNum = DEFAULT_ZERO;
	UINT8_S rtnValue = RETURN_ERROR;

	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/
	swtichNum = GetAcSwitchNum(acId);

	if ((bufIndex < LOCAL_AC_SUM_MAX)
		&& (bufSize >=  swtichNum) && (NULL != switchInAcStruBuff))
	{
		for (cycle = DEFAULT_ZERO;cycle < swtichNum;cycle++)
		{
			switchInAcStruBuff[cycle].SwitchId = gAcConfigDataStruBuff[bufIndex].SwitchInAcStru[cycle].SwitchId;
			switchInAcStruBuff[cycle].SwitchPostion = gAcConfigDataStruBuff[bufIndex].SwitchInAcStru[cycle].SwitchPostion;
		}
		rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ���������ΰ������߼���������
* ����˵���� const UINT16 acId, ��������Id    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����      
*/
UINT16_S GetAcLogicSectionNum(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT16_S rtnValue = 0U;

	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = (UINT16_S)(gAcConfigDataStruBuff[bufIndex].LogicSectionNum);
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ���������ΰ������߼�����Id����
* ����˵���� const UINT16 bufIndex, �����±�    
*            const UINT16_S bufSize,��������С
*            UINT16_S logicSectionIdBuff[],�������
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 1: ��ȡ�ɹ�      
*/
UINT8_S GetAcLogicSectionIdBuf(const UINT16_S acId,const UINT16_S bufSize,UINT16_S logicSectionIdBuff[])
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT16_S logicSectionNum = DEFAULT_ZERO;
    UINT8_S  rtnValue = 0U;

	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/
	logicSectionNum = GetAcLogicSectionNum(acId);

    if (NULL != logicSectionIdBuff)
    {
        if ((bufIndex < LOCAL_AC_SUM_MAX)
            && (bufSize >=  SIZE_MAX_SECTIONNUM))
        {
            for (cycle = DEFAULT_ZERO;cycle < logicSectionNum;cycle++)
            {
                logicSectionIdBuff[cycle] = gAcConfigDataStruBuff[bufIndex].LogicSectionIdBuff[cycle];
            }

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
