/********************************************************
*                                                                                                            
* �� �� ���� ACStatusData.c   
* ����ʱ�䣺 2015-05-01
* ��    �ߣ� 
* ���������� ����״̬���ݹ���  
* ��  ע  ��  ��
*
********************************************************/ 
#include "ACStatusData.h"
#include "ACConfigData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../../Common/MemSet.h"

AcStatusDataStruct gAcStatusDataStruBuff[LOCAL_AC_SUM_MAX];   /*���屾ZC��������״̬�ṹ��*/
/*
* ���������� ��ȡָ��ID�������շ���
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ�ܻ����޷���
*			 0x55: ���շ������߼���������ͬ
			 0xaa: ���շ������߼��������෴
*/
UINT8_S GetAcDirection(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcDirection;
	}

	return rtnValue;
}

/*
* ���������� ����ָ��ID�������շ���
* ����˵���� const UINT16 acId, ����ID  
*            const UINT8_S acDirection
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ�ܻ����޷���
*			 RETURN_SUCCESS: �ɹ�
*/
UINT8_S SetAcDirection(const UINT16_S acId,const UINT8_S acDirection)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if ((AC_DIR_UP_STATUS == acDirection)
			|| (AC_DIR_DOWN_STATUS == acDirection)
			|| (DEFAULT_ZERO == acDirection))
		{
			gAcStatusDataStruBuff[bufIndex].AcDirection = acDirection;
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
* ���������� ��ȡָ��ID��������״̬
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ�ܻ���Ĭ��ֵ
*			 0x55: ����
*			 0xaa: δ����
*/
UINT8_S GetAcBelock(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcBelock;
	}

	return rtnValue;
}

/*
* ���������� ����ָ��ID��������״̬
* ����˵���� const UINT16 acId, ����ID 
*            const UINT8_S acBelock
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: �ɹ�
*/
UINT8_S SetAcBelock(const UINT16_S acId,const UINT8_S acBelock)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if ((AC_LOCK_STATUS == acBelock)
			|| (AC_UNLOCK_STATUS == acBelock))
		{
			gAcStatusDataStruBuff[bufIndex].AcBelock = acBelock;
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
* ���������� ��ȡָ��ID����ռ��״̬
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ�ܻ���Ĭ��ֵ
*			 0x55: ռ��
*			 0xaa: ����
*/
UINT8_S GetAcStatusNow(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcStatusNow;
	}

	return rtnValue;
}

/*
* ���������� ����ָ��ID���ᵱǰռ��״̬
* ����˵���� const UINT16 acId, ����ID 
*            const UINT8_S acStatus
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: �ɹ�
*/
UINT8_S SetAcStatusNow(const UINT16_S acId,const UINT8_S acStatus)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if ((AC_OCC_STATUS == acStatus)
			|| (AC_FREE_STATUS == acStatus))
		{
			gAcStatusDataStruBuff[bufIndex].AcStatusNow = acStatus;
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
* ���������� ��ȡָ��ID����UT��־
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 0x55: UT
*			 0xaa: ��UT
*/
UINT8_S GetAcUtFlag(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcUtFlag;
	}

	return rtnValue;
}

/*
* ���������� ����ָ��ID����UT��־
* ����˵���� const UINT16 acId, ����ID 
*            const UINT8_S acUtFlag
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: �ɹ�
*/
UINT8_S SetAcUtFlag(const UINT16_S acId,const UINT8_S acUtFlag)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if ((AC_UT_OCC_STATUS == acUtFlag)
			|| (AC_UT_FREE_STATUS == acUtFlag))
		{
			gAcStatusDataStruBuff[bufIndex].AcUtFlag = acUtFlag;
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
* ���������� ��ȡָ��ID����ARB��־
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 0x55: ARB
*			 0xaa: ��ARB
*/
UINT8_S GetAcArbFlag(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcArbFlag;
	}

	return rtnValue;
}

/*
* ���������� ����ָ��ID����ARB��־
* ����˵���� const UINT16 acId, ����ID    
*            const UINT8_S acArbFlag
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: �ɹ�
*/
UINT8_S SetAcArbFlag(const UINT16_S acId,const UINT8_S acArbFlag)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if ((AC_ARB_FREE_STATUS == acArbFlag)
			|| (AC_ARB_OCC_STATUS == acArbFlag))
		{
			gAcStatusDataStruBuff[bufIndex].AcArbFlag = acArbFlag;
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
* ���������� ��ȡָ��ID�������һ��������г�ID
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 1: ��ȡ���ݳɹ�
*/
UINT8_S GetAcLastTrain(const UINT16_S acId,UINT16_S *trainId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
    if (NULL != trainId)
    {
        /*��ʼ���������*/
        (*trainId) = DEFAULT_ZERO;

        bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

        if (bufIndex < LOCAL_AC_SUM_MAX)
        {
            (*trainId) = gAcStatusDataStruBuff[bufIndex].LastTrainEnterAc;
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
* ���������� ����ָ��ID�������һ��������г�ID
* ����˵���� const UINT16 acId, ����ID   
*            const UINT16_S acLastTrainId�����һ�г�
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: �ɹ�
*/
UINT8_S SetAcLastTrain(const UINT16_S acId,const UINT16_S acLastTrainId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if (acLastTrainId < LINE_MAX_TRAIN_ID)
		{
			gAcStatusDataStruBuff[bufIndex].LastTrainEnterAc = acLastTrainId;
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
* ���������� ��ȡָ��ID����UT�����ʱλ
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 >=0:�����ʱλ
*/
UINT8_S GetAcUtRedundance(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcUtRedundance;
	}

	return rtnValue;
}

/*
* ���������� ����ָ��ID����UT�����־λ
* ����˵���� const UINT16 acId, ����ID  
*            const UINT8_S acUtRedundance
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: �ɹ�
*/
UINT8_S SetAcUtRedundance(const UINT16_S acId,const UINT8_S acUtRedundance)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		 gAcStatusDataStruBuff[bufIndex].AcUtRedundance = acUtRedundance;
		 rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}


/*
* ���������� ��ȡָ��ID����ARB�����ʱλ
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 >=0:�����ʱλ
*/
UINT8_S GetAcArbRedundance(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].AcArbRedundance;
	}

	return rtnValue;
}

/*
* ���������� ����ָ��ID����ARB�����־λ
* ����˵���� const UINT16 acId, ����ID  
*            const UINT8_S acArbRedundance
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: �ɹ�
*/
UINT8_S SetAcArbRedundance(const UINT16_S acId,const UINT8_S acArbRedundance)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		 gAcStatusDataStruBuff[bufIndex].AcArbRedundance = acArbRedundance;
		 rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID�����г�����
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� DEFAULT_UINT8_VALUE: ��ȡ����ʧ��
*			 >=0:�г�����
*/
UINT8_S GetAcTrainOfAcNum(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = DEFAULT_UINT8_VALUE;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].TrainOfAcNum;
	}
	else
	{
		rtnValue = DEFAULT_UINT8_VALUE;
	}

	return rtnValue;
}

/*
* ���������� ����ָ��ID�����г�����
* ����˵���� const UINT16 acId, ����ID   
*            const UINT8_S acTrainOfAcNum
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: �ɹ�
*/
UINT8_S SetAcTrainOfAcNum(const UINT16_S acId,const UINT8_S acTrainOfAcNum)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		if (SIZE_MAX_TRAINOFAC >= acTrainOfAcNum)
		{
			gAcStatusDataStruBuff[bufIndex].TrainOfAcNum = acTrainOfAcNum;
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
* ���������� ��ȡָ��ID�����г�������Ϣ
* ����˵���� const UINT16 acId, ����ID    
*            const UINT8_S bufSzie,�����С
*            UINT16_S trainIdSequBuff[],�������
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS:�ɹ�
*/
UINT8_S GetAcTrainSequenceBuff(const UINT16_S acId,const UINT8_S bufSzie,UINT16_S trainIdSequBuff[])
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = 0U;
	UINT8_S cycle =0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if ((bufIndex < LOCAL_AC_SUM_MAX)
		&& (bufSzie >= SIZE_MAX_TRAINOFAC)
		&& (NULL != trainIdSequBuff))
	{
		for (cycle = 0U; cycle < GetAcTrainOfAcNum(acId);cycle++)
		{
			trainIdSequBuff[cycle] = gAcStatusDataStruBuff[bufIndex].TrainSequenceBuff[cycle];
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
* ���������� ����ָ��ID�����г�������Ϣ
* ����˵���� const UINT16 acId,
*            const UINT16_S trainIdSequBuff[],����ID
*            const UINT8_S trainNum,�г�����    
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS:�ɹ�
*/
UINT8_S SetAcTrainSequenceBuff(const UINT16_S acId,const UINT16_S trainIdSequBuff[],const UINT8_S trainNum)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = 0U;
	UINT8_S i =0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if ((bufIndex < LOCAL_AC_SUM_MAX)
		&& (SIZE_MAX_TRAINOFAC >= trainNum) && (NULL != trainIdSequBuff))
	{
		gAcStatusDataStruBuff[bufIndex].TrainOfAcNum = trainNum;

		if(DEFAULT_ZERO == trainNum)
		{
			for(i=0U;i<SIZE_MAX_TRAINOFAC;i++)
			{
				gAcStatusDataStruBuff[bufIndex].TrainSequenceBuff[i] = trainIdSequBuff[i];	
			}
		}
		else
		{
			for(i=0U;i<trainNum;i++)
			{
				gAcStatusDataStruBuff[bufIndex].TrainSequenceBuff[i] = trainIdSequBuff[i];	
			}
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
* ���������� �ж�ָ���г�IDλ�ڼ����г����е�λ��
* ����˵���� const UINT16 acId ����Id
*            const UINT16_S trainId���г�Id
* ����ֵ  �� 0xff: û���ڸü����г�������
*			 0>=: ����λ��    
*/
UINT8_S GetTrainIdInTrainSequence(const UINT16_S acId,const UINT16_S trainId)
{
	UINT16_S trainIdSequBuff[SIZE_MAX_TRAINOFAC] ={DEFAULT_ZERO};
	UINT8_S cycle = DEFAULT_UINT8_VALUE;
	UINT8_S rtnIndex = DEFAULT_ZERO;

	if (GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainIdSequBuff))
	{
		rtnIndex = DEFAULT_UINT8_VALUE;

		for (cycle = DEFAULT_ZERO;cycle < GetAcTrainOfAcNum(acId);cycle++)
		{
			if (trainIdSequBuff[cycle] == trainId)
			{
				rtnIndex = cycle;
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
		rtnIndex = DEFAULT_UINT8_VALUE;
	}

	return rtnIndex;
}

/*
* ���������� ��ѯָ�����������ڵ�ָ���±��Ӧ���г�Id
* ����˵���� const UINT16 acId ����Id
*            const UINT8_S index�������±�
*            UINT16_S *trainIdInAC������г�ID
* ����ֵ  �� RETURN_ERROR: ��ѯʧ��
*			 RETURN_SUCCESS: ��ѯ�ɹ�    
*/
UINT8_S GetTrainIdInTrainSequenceOfIndex(const UINT16_S acId,const UINT8_S index,UINT16_S *trainIdInAC)
{
	UINT16_S trainIdSequBuff[SIZE_MAX_TRAINOFAC];
	UINT8_S rtnValue = DEFAULT_ZERO;

	MemorySet(&trainIdSequBuff[0],sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC,DEFAULT_ZERO,sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC);

    if (NULL != trainIdInAC)
    {
        if (GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainIdSequBuff))
        {
            if (SIZE_MAX_TRAINOFAC <= index)
            {
                rtnValue = RETURN_ERROR;
            } 
            else
            {
                *trainIdInAC = trainIdSequBuff[index];
                rtnValue = RETURN_SUCCESS;
            }
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
* ���������� ��ȡ������ָ��ID�����г�����
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� -1: ��ȡ����ʧ��
*			 >=0:�г�����
*/
UINT8_S GetLastTrainOfAcNum(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = 0U;

	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].LastTrainOfAcNum;
	}
	else
	{
		rtnValue = DEFAULT_0XFF;
	}

	return rtnValue;
}

/*
* ���������� ����������ָ��ID�����г�����
* ����˵���� const UINT16 acId, ����ID  
*            const UINT8_S acTrainOfAcNum
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: �ɹ�
*/
UINT8_S SetLastTrainOfAcNum(const UINT16_S acId,const UINT8_S acTrainOfAcNum)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;

	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		gAcStatusDataStruBuff[bufIndex].LastTrainOfAcNum = acTrainOfAcNum;
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡ������ָ��ID�����г�������Ϣ
* ����˵���� const UINT16 acId, ����ID    
*            const UINT8_S bufSzie,�����С
*            const UINT16_S trainIdSequBuff[],�������
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS:�ɹ�
*/
UINT8_S GetLastTrainSequenceBuf(const UINT16_S acId,const UINT8_S bufSzie,UINT16_S trainIdSequBuff[])
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = 0U;
	UINT8_S cycle =0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if ((bufIndex < LOCAL_AC_SUM_MAX)
		&& (bufSzie >= SIZE_MAX_TRAINOFAC)
		&& (NULL != trainIdSequBuff))
	{
		for (cycle = 0U; cycle < GetLastTrainOfAcNum(acId);cycle++)
		{
			trainIdSequBuff[cycle] = gAcStatusDataStruBuff[bufIndex].LastTrainSequenceBuff[cycle];
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
* ���������� ����������ָ��ID�����г�������Ϣ
* ����˵���� const UINT16 acId,
*            const UINT16_S trainIdSequBuff[],����ID
*            const UINT8_S trainNum,�г�����    
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS:�ɹ�
*/
UINT8_S SetLastTrainSequenceBuf(const UINT16_S acId,const UINT16_S trainIdSequBuff[],const UINT8_S trainNum)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = 0U;
	UINT8_S i =0U;
	
	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if ((bufIndex < LOCAL_AC_SUM_MAX)
		&& (SIZE_MAX_TRAINOFAC >= trainNum) && (NULL != trainIdSequBuff))
	{
		gAcStatusDataStruBuff[bufIndex].TrainOfAcNum = trainNum;

		for(i=0U;i<trainNum;i++)
		{
			gAcStatusDataStruBuff[bufIndex].LastTrainSequenceBuff[i] = trainIdSequBuff[i];	
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
* ���������� ��ȡָ��ID�����г�����ɨ��־
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
*			 FLAG_SET:����ɨ
*			 FLAG_UNSET:δ��ɨ
*/
UINT8_S GetAcTrainCleanFlag(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_UINT8_MAX_VALUE;

	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].TrainCleanFlag;
	}

	return rtnValue;
}
/*
* ���������� ����ָ��ID�����г�����ɨ��־
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� RETURN_SUCCESS: ���óɹ�
*			 RETURN_ERROR:����ʧ��			 
*/
UINT8_S SetAcTrainCleanFlag(const UINT16_S acId,const UINT8_S cleanFlag)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;

	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{		
		gAcStatusDataStruBuff[bufIndex].TrainCleanFlag = cleanFlag;
		rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��������ɨ�г�ID
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			 >0:��ɨ�г�ID
*/
UINT16_S GetAcCleanTrainId(const UINT16_S acId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT16_S rtnValue = RETURN_ERROR;

	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{
		rtnValue = gAcStatusDataStruBuff[bufIndex].CleanTrainId;
	}

	return rtnValue;
}

/*
* ���������� ����ָ��ID��������ɨ�г�ID
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� RETURN_ERROR: ��������ʧ��
*			 RETURN_SUCCESS:���óɹ�
*/
UINT8_S SetAcCleanTrainId(const UINT16_S acId,const UINT16_S cleanTrainId)
{
	UINT16_S bufIndex = 0U;  /*�����±�*/
	UINT8_S rtnValue = RETURN_ERROR;

	bufIndex = GetAcConfigBufIndex(acId);  /*��ȡ���������±�*/

	if (bufIndex < LOCAL_AC_SUM_MAX)
	{		 
		gAcStatusDataStruBuff[bufIndex].CleanTrainId = cleanTrainId;
		rtnValue = RETURN_SUCCESS;
	}

	return rtnValue;
}

/*
* ���������� ��ȡ���������ڵĵ�һ�г�
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� RETURN_UINT16_MAX_VALUE: ��ȡ����ʧ��
*			>0: ��һ���г�ID
*/
UINT16_S GetFirstIdInTrainSequence(const UINT16_S acId)
{
	UINT8_S trainNum = 0U;
	UINT16_S rtnValue = 0U;
	UINT16_S acIndex = 0U;
	/*��ȡ�г�����*/
	trainNum = GetAcTrainOfAcNum(acId);
	acIndex = GetAcConfigBufIndex(acId);

	if ((RETURN_UINT8_MAX_VALUE != trainNum) && (0U != trainNum))
	{
		rtnValue = gAcStatusDataStruBuff[acIndex].TrainSequenceBuff[0];
	}
	else
	{
		rtnValue = RETURN_UINT16_MAX_VALUE;
	}

	return rtnValue;
}

/*
* ���������� ��ȡ���������ڵ����һ�г�
* ����˵���� const UINT16 acId, ����ID    
* ����ֵ  �� RETURN_UINT16_MAX_VALUE: ��ȡ����ʧ��
*			>0: ���һ���г�ID
*/
UINT16_S GetLastIdInTrainSequence(const UINT16_S acId)
{
	UINT8_S trainNum = 0U;
	UINT16_S rtnValue = 0U;
	UINT16_S acIndex = 0U;
	/*��ȡ�г�����*/
	trainNum = GetAcTrainOfAcNum(acId);
	acIndex = GetAcConfigBufIndex(acId);

	if ((RETURN_UINT8_MAX_VALUE != trainNum) && (0U != trainNum))
	{
		rtnValue = gAcStatusDataStruBuff[acIndex].TrainSequenceBuff[trainNum - 1U];
	}
	else
	{
		rtnValue = RETURN_UINT16_MAX_VALUE;
	}

	return rtnValue;
}
