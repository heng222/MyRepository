/*******************************************
�ļ���	��DmuDataHandle.c
����	������
����ʱ�䣺2016-10
����	��DSU��ѯ����
��ע	����
*******************************************/
#include "DmuDataHandle.h"
#include "../../../../Dmu/DmuComm/DataHandle/DmuCommDataHandle.h"
#include "../../../../Common/Convert.h"
#include "../../../../Common/Malloc.h"
#include "../../../../Common/MemSet.h"
#include "../../../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"
#include "../../../../Dmu/DmuComm/Data/StaticResSpeedData.h"
#include "../../../../Dmu/DmuComm/Data/LogicSectionData.h"
#include "../../../../Dmu/DmuComm/Data/AxleSectionData.h"
#include "../../../../Dmu/DmuComm/Data/SwitchData.h"
#include "../../../../Dmu/Read/ReadManage.h"
#include "../../../../Dmu/DmuComm/Load/LoadManage.h"
#include "../../TsrAdministrator/TsrDataAdmin.h"

/********************************�ڲ�ʹ�ú���START****************************/
static UINT8_S OrderLogicSgmt(const UINT16_S* pLogicId,UINT16_S logicNum,UINT16_S *orderpLogicId);
static UINT16_S CheckSingleLogicSgmtTSRSpeed(UINT16_S pLogicId);
static UINT8_S  CheckLastTsrValid(const UINT16_S* pLogicId,const UINT8_S logicNum);
static  UINT8_S CheakTwoLogicRule(BnfLogicSectionStruct *tempLogicSgmt1,BnfLogicSectionStruct *tempLogicSgmt2);

/********************************�ڲ�ʹ�ú���END******************************/


/*******************************************
������	��CheckLogicRealteZc
������������ѯ���߼������漰��ZC��ID
����	��UINT16* logicIds,   �߼�����ID
		  UINT8 logicNum,     �߼����θ���
		  UINT8 maxZcNum,     ZC����
���	��UINT8* pRelateZcId, ����ZCID������(ע���߼����������ĸ�ZC���Ͱ���ӦZCIDд��������)
����ֵ	��1:�ɹ���	0:ʧ��
*******************************************/
UINT8_S CheckLogicRealteZc(const UINT16_S* logicIds, UINT8_S logicNum, UINT8_S maxZcNum, UINT8_S* pRelateZcId,UINT8_S *relateZcNum)
{
	UINT8_S retVal = DEFAULT_ZERO;/*��������ֵ*/
	UINT8_S isFlag = 1u;/*1 ���ͨ��  0 ���δͨ��*/
	UINT16_S i;    /*ѭ���ñ���*/
	UINT16_S j = DEFAULT_ZERO;/*ѭ���ñ���*/
	BnfLogicSectionStruct* pTempLogicSgmtStr = NULL;  /*���ھ�̬���ݿ��е��߼����νṹ��ָ��*/
	BnfSegStruct* pTempSegStru = NULL; /*���ھ�̬���ݿ��е�Seg����ָ��*/
	UINT8_S tempZCtndex = DEFAULT_ZERO;           /*����ZC����*/

	if(( logicIds != NULL )&&( pRelateZcId != NULL)&&(relateZcNum != NULL)&&( logicNum <= LOGIC_MAX_NUM ))		/*MQH*/
	{
		/*ѭ�����ÿһ��ZCIds�İ���״̬*/
		for(i=DEFAULT_ZERO;i<maxZcNum;i++)
		{
			pRelateZcId[i]=DEFAULT_ZERO;
		}

		for (j=DEFAULT_ZERO;j<logicNum;j++)
		{
			/*���ݵ�ǰ�߼����ε�id��ȡ�߼����νṹ����Ϣ*/
			pTempLogicSgmtStr = GetIndexIdLogicSectionDataStru(logicIds[j]);
			if (NULL == pTempLogicSgmtStr)
			{
				/*ѭ�����ÿһ��ZCIds�İ���״̬*/
				for(i=DEFAULT_ZERO;i<maxZcNum;i++)
				{
					pRelateZcId[i]=DEFAULT_ZERO;
				}
				retVal = DEFAULT_ZERO;
				isFlag = DEFAULT_ZERO;

			}

			if (1u == isFlag)
			{
				/*�����߼����νṹ���ȡ�߼��������Seg�Ľṹ��*/
				pTempSegStru = GetIndexIdSegDataStru(pTempLogicSgmtStr->startSegId);

				/*��������������ZCIndex�Ƿ�Ϸ�*/
				if (pTempSegStru->segManageZCId <= maxZcNum)
				{
					pRelateZcId[tempZCtndex]=(UINT8_S)(pTempSegStru->segManageZCId);
		            tempZCtndex++;

				}
				else
				{
					/*ѭ�����ÿһ��ZCIds�İ���״̬*/
					for(i=DEFAULT_ZERO;i<maxZcNum;i++)
					{
						pRelateZcId[i]=DEFAULT_ZERO;
					}

					retVal = DEFAULT_ZERO;
					isFlag = DEFAULT_ZERO;

				}
				if(DEFAULT_ZERO == isFlag)
				{
					break;
				}
			}
			
		}

		if (1u == isFlag)
		{
			retVal = 1u;
			*relateZcNum = tempZCtndex;
		}
	}
	else
	{
		/*������ */
	}
	
	return retVal;
}

/*******************************************
������	��CheckSingleTSRSpeedValid
�����������ж���ʱ������ֵ�Ƿ�������õ���ʱ�����漰�����߼����ε���·����������ֵ
����	��UINT16* pLogicId   �߼�����ID
		  UINT8 logicNum     �߼���������
		  UINT8 speed       �趨��ʱ�����ٶ�
���    ����
����ֵ	��2    ���õ���ʱ������ֵ����ĳһ���߼����ε���·����������ֵ
		  1    ���õ���ʱ������ֵû�и����κ�һ���߼����ε���·����������ֵ
		  0    ��ѯʧ�ܣ������������������������Ϊ��ѯʧ�ܣ�
*******************************************/
UINT8_S CheckSingleTSRSpeedValid(const UINT16_S* pLogicId,UINT8_S logicNum,UINT8_S speed)
{
	UINT8_S retVal = DEFAULT_ZERO;/*��������ֵ*/
	UINT8_S isFlag = 1u;/*1 ���ͨ��  0 ���δͨ��*/
	UINT8_S i = DEFAULT_ZERO;/*ѭ��ʹ��*/
	UINT16_S tmpLogicSgmtTsrSpeed = DEFAULT_ZERO;/*��ʱ�����������߼���������Ӧ�ľ�̬����*/

	if( pLogicId != NULL )
	{
		/*�����ʱ�������߼����������������ֵ����ѯʧ��*/
		if (logicNum > LOGIC_MAX_NUM)
		{
			isFlag = DEFAULT_ZERO;
		}

		for (i=DEFAULT_ZERO;(i<logicNum)&&(1u == isFlag);i++)
		{
			/*��ѯ�����߼����εľ�̬��ʱ����ֵ*/
			tmpLogicSgmtTsrSpeed=CheckSingleLogicSgmtTSRSpeed(pLogicId[i]);
			/********test******/
			/*tmpLogicSgmtTsrSpeed = 2222;*/
			/*************/
			if (tmpLogicSgmtTsrSpeed != DEFAULT_ZERO)
			{	/*��ѯ�ɹ������ؾ�̬��ʱ����ֵ,������Ҫ�ٶȻ���*/
				/*chTSRSpeed�ĵ�λΪkm/h,tmpLogicSgmtTsrSpeed�ĵ�λΪcm/s*/
				if ((FLOAT32_S)speed > ((FLOAT32_S)tmpLogicSgmtTsrSpeed * 0.036))
				{	/*���õ���ʱ������ֵ����ĳһ���߼����ε���·����������ֵ������ѭ��*/
					retVal = 2u;
					break;
				} 
			}
			else
			{	/*��ѯʧ��,����ѭ��*/
				retVal = DEFAULT_ZERO;
				break;
			}

		}

		if (i == logicNum)
		{
			/*���õ���ʱ������ֵû�и����κ�һ���߼����ε���·����������ֵ*/
			retVal=1u;
		}
	}
	else
	{
		/*������ */
	}
	return retVal;
}

/*******************************************
������	��CheckSingleLogicSgmtTSRSpeed
�����������󵥸��߼����εľ�̬����ֵ
����	��UINT16 pLogicId  �߼�����id
���	����
����ֵ	��0x00: ��ѯʧ�ܣ�
		  !0: ���߼���������Ӧ�ľ�̬����ֵ;
*******************************************/
static UINT16_S CheckSingleLogicSgmtTSRSpeed(UINT16_S pLogicId)
{
	UINT16_S retVal = DEFAULT_ZERO;
	BnfLogicSectionStruct *logicSgmtStru = NULL;
	UINT16_S tempLimitSpeed = DEFAULT_ZERO;/*����ֵ*/
	UINT16_S retLimitSpeed = DEFAULT_ZERO;/*���ص���ʱ����ֵ*/
	UINT8_S i = DEFAULT_ZERO;/*ѭ��ʹ��*/

	/*���ù������ҵ��߼����α�*/
	logicSgmtStru = GetIndexIdLogicSectionDataStru(pLogicId);

	if (NULL != logicSgmtStru)
	{
		if (logicSgmtStru->startSegId == logicSgmtStru->endSegId)
		{
			retVal = GetSegIdOfLimitSpeed(logicSgmtStru->startSegId,logicSgmtStru->startSegOffset,logicSgmtStru->endSegOffset,&tempLimitSpeed);
			retLimitSpeed = tempLimitSpeed;
		}
		else
		{
			/*��ȡ���SEG������ֵ*/
			retVal = GetSegIdOfLimitSpeed(logicSgmtStru->startSegId,logicSgmtStru->startSegOffset,GetSegDataStrulength(logicSgmtStru->startSegId),&tempLimitSpeed);

			if (1u == retVal)
			{
				retLimitSpeed = tempLimitSpeed;
				for (i = DEFAULT_ZERO; i < logicSgmtStru->includeSegIdNum; i++)
				{
					if ((logicSgmtStru->segIdBuff[i] == logicSgmtStru->startSegId)||(logicSgmtStru->segIdBuff[i] == logicSgmtStru->endSegId))
					{
					    /* Do nothing */
					}
					else
					{
						retVal = GetSegIdOfLimitSpeed(logicSgmtStru->segIdBuff[i],DEFAULT_ZERO,GetSegDataStrulength(logicSgmtStru->segIdBuff[i]),&tempLimitSpeed);
						if ((1u == retVal)&&(tempLimitSpeed < retLimitSpeed))
						{
							retLimitSpeed = tempLimitSpeed;
						}
					}
				}
			}

			/*��ȡ�յ�SEG������ֵ*/
			retVal = GetSegIdOfLimitSpeed(logicSgmtStru->endSegId,DEFAULT_ZERO,logicSgmtStru->endSegOffset,&tempLimitSpeed);
			if ((1u == retVal)&&(tempLimitSpeed < retLimitSpeed))
			{
				retLimitSpeed = tempLimitSpeed;
			}
		}

	}


	return retLimitSpeed;
}

/*******************************************
������	��CheckSingleTsrLogicIdsValid
�����������ж���ʱ�����������߼����ε���Ч��
����	��UINT16* pLogicId   �߼�����ID
		  UINT8 logicNum     �߼���������
���	����
����ֵ	��1: ����ʱ������ͬʱ������ͬһ����Ķ�λ�ͷ�λ��
		  2: ����ʱ�����ڵ��߼����β�����;
		  3: ����ʱ�����ڴ���ID���Ϸ����߼�����;
		  4: ����ԭ��ʧ��
		  0:�ɹ�
*******************************************/
UINT8_S CheckSingleTsrLogicIdsValid(UINT16_S* pLogicId,UINT8_S logicNum)
{
	UINT8_S retVal = DEFAULT_ZERO;/*��������ֵ*/
	UINT16_S orderpLogicId[LOGIC_MAX_NUM] = {DEFAULT_ZERO};

	/*��ʱ�������߼����θ�������*/
	if((pLogicId != NULL ) && (logicNum <= LOGIC_MAX_NUM))
	{
		/*�ж����õ���ʱ�������߼������Ƿ����ǰ���õķ��������ͻ*/
		retVal = CheckLastTsrValid(pLogicId,logicNum);
		if( 0u == retVal)
		{
			/*�ж����õ���ʱ�������߼������Ƿ��������ͻ*/
			retVal = OrderLogicSgmt(pLogicId,(UINT16_S)logicNum,orderpLogicId);
		}
		
	}

	return retVal;
}

/*******************************************
������	��OrderLogicSgmt
�������������߼�������������
����	��UINT16 pLogicId[DSU_TSRSECTIOM_NUM]  ����������
		  UINT16 logicNum             �������߼����θ���
���	:UINT16 *OrderpLogicId   ����������
���	��UINT16 *OrderpLogicId   ����������
����ֵ	��1: ����ʱ������ͬʱ������ͬһ����Ķ�λ�ͷ�λ��
		  2: ����ʱ�����ڵ��߼����β�����;
		  3: ����ʱ�����ڴ���ID���Ϸ����߼�����;
		  4: ����ԭ��ʧ��
		  0:�ɹ�
*******************************************/
static UINT8_S OrderLogicSgmt(const UINT16_S* pLogicId,UINT16_S logicNum,UINT16_S *orderpLogicId)
{
	UINT8_S i,j;    /*ѭ������*/
	UINT8_S errorRetVal = DEFAULT_ZERO;/*1 �д��󷵻� 0 �޴��󷵻�*/
	BnfLogicSectionStruct *logicSgmtAhead,*logicSgmtRear,*tLogicSgmt;   /*�߼�������ʱ����*/
	BnfLogicSectionStruct *tempLogicSgmt1,*tempLogicSgmt2;   /*�߼�������ʱ����*/
	BnfAxleSectionStruct  *tempAxleSgmt1,*tempAxleSgmt2;

	UINT8_S bReturnValue = 4u;
	UINT8_S tmpNum;	/*ѭ������--���ڱ��������������ڼ�������*/
	const UINT8_S AxlelogicNum = 3u;	/*�����������ڼ����������������Ϊ3*/

	UINT8_S isFind;
	UINT8_S aheadFlag= 1u;
	UINT8_S rearFlag= 1u;
	UINT16_S logicSgmeCount;
	UINT16_S logicLineNum = DEFAULT_ZERO;/*�߼���������*/
	
	if(( pLogicId != NULL) && ( orderpLogicId != NULL ) && ( logicNum <= LOGIC_MAX_NUM))
	{
		tempLogicSgmt1 = GetLogicSectionDataInfo(&logicLineNum);	/*��ȡ�߼����ε�����������*/
		/*�жϴ�������߼��������������������߼������Ƿ������ͬһ����Ķ�λ�ͷ�λ*/
		for(i=DEFAULT_ZERO;i<(logicNum-1u)&&(DEFAULT_ZERO == errorRetVal);i++)
		{
			tempLogicSgmt1 = GetIndexIdLogicSectionDataStru(pLogicId[i]);
			for(j=i+1u;j<logicNum;j++)
			{
				tempLogicSgmt2 =  GetIndexIdLogicSectionDataStru(pLogicId[j]);
				/*���߼����β�����ͬһ�������������غ�linkʱ����ͬʱ������ͬһ����Ķ�λ�ͷ�λ*/
				if(tempLogicSgmt1->belongAxleSecId != tempLogicSgmt2->belongAxleSecId)
				{
					if((tempLogicSgmt1->startSegId == tempLogicSgmt2->startSegId)
						|| (tempLogicSgmt1->endSegId == tempLogicSgmt2->endSegId))
					{
						/*���ش�����*/
						bReturnValue = 1u;
						errorRetVal = 1u;
						break;
					}
				}
			}
		}
		/*�ҵ���ǰ���߼�����*/
		logicSgmtAhead = GetIndexIdLogicSectionDataStru(pLogicId[0]);
		tLogicSgmt = logicSgmtAhead;
		while((DEFAULT_ZERO == errorRetVal)&&(aheadFlag))
		{
			tempAxleSgmt1 = GetIndexIdAxleSectionDataStru(logicSgmtAhead->belongAxleSecId);
			/*logicSgmtAheadΪ���ڼ������εĵ�һ���߼�����*/
			if(logicSgmtAhead->indexId == tempAxleSgmt1->logicSecId[0])
			{
				/*�����Ϊ0*/
				isFind = DEFAULT_ZERO;
				/*����logicSgmtAheadΪ���ڼ������ε�������ڼ�����������*/
				for (tmpNum=DEFAULT_ZERO;tmpNum<AxlelogicNum;tmpNum++)
				{
					/*�������δ���*/
					if (tempAxleSgmt1->orgnAxleSgmtId[tmpNum] != UINT16_MAX)
					{

						/*tempAxleSgmt2Ϊ����ǰһ����������*/
						tempAxleSgmt2 = GetIndexIdAxleSectionDataStru(tempAxleSgmt1->orgnAxleSgmtId[tmpNum]);
						/*��tLogicSgmtΪ����ǰһ���������ε���һ���߼�����*/
						/*���е������ʱ���߼����κͼ�������Ϊͬһ��*/
						tLogicSgmt = GetIndexIdLogicSectionDataStru(tempAxleSgmt2->logicSecId[tempAxleSgmt2->includeLogicAxleSecNum-1u]);
						/*�������飬���tLogicSgmt�߼������Ƿ�������������У�Ѱ�ұ�־��Ϊ1*/

						for(i=DEFAULT_ZERO;i<logicNum;i++)
						{
							/*�ڵĻ�����ǰ����Ѱ�ң�Ѱ�ұ����Ϊ1*/
							if(tLogicSgmt->indexId == pLogicId[i])
							{
								logicSgmtAhead = tLogicSgmt;
								isFind = 1u;
								break;
							}
						}

					} 
					else
					{
						/*������һ��������ڼ�������*/
					}
				}
				/*�����������isfind==0��
				1.���������ڼ�������ȫ��Ϊ0xffff--��Ϊ��·���
				2.��ȫΪ0xffff--����·���
				���������δ�����·��ʱ���������ε����һ���߼����ζ����ڴ�������߼�����������*/
				if (isFind == DEFAULT_ZERO)
				{ 
					/*�˳�whileѭ��*/
					aheadFlag = DEFAULT_ZERO;
					break;
				} 
				else
				{
					/*û���ҵ���һ���߼����Σ�����*/
				}
			}

			else
			{
				/*tLogicSgmtΪ��ʼ�������߼�����*/
				tLogicSgmt = GetIndexIdLogicSectionDataStru(logicSgmtAhead->mainOrgnLogicSgmtId);
				/*�������飬��tempLogicSgmt�߼������Ƿ��������������*/
				isFind = DEFAULT_ZERO;
				for(i=DEFAULT_ZERO;i<logicNum;i++)
				{
					/*�ڵĻ�����ǰ����Ѱ��*/
					if(tLogicSgmt->indexId == pLogicId[i])
					{
						logicSgmtAhead = tLogicSgmt;
						isFind = 1u;
						break;
					}
				}
				if(DEFAULT_ZERO == isFind)
				{
					/*�ҵ�����ǰ��*/
					aheadFlag = DEFAULT_ZERO;
				}
			}
		}

		logicSgmeCount = DEFAULT_ZERO;
		orderpLogicId[logicSgmeCount] = logicSgmtAhead->indexId;
		logicSgmtRear = logicSgmtAhead;
		tLogicSgmt = logicSgmtAhead;
		/*��β����*/
		while((DEFAULT_ZERO == errorRetVal)&&(rearFlag))
		{
			tempAxleSgmt1 = GetIndexIdAxleSectionDataStru(logicSgmtRear->belongAxleSecId);
			/*logicSgmtRearΪ���ڼ������ε����һ���߼�����*/
			if(logicSgmtRear->indexId == tempAxleSgmt1->logicSecId[tempAxleSgmt1->includeLogicAxleSecNum-1u])
			{
				/*�����Ϊ0*/
				isFind = DEFAULT_ZERO;
				/*����logicSgmtAheadΪ���ڼ������ε�������ڼ�����������*/
				for (tmpNum=DEFAULT_ZERO;tmpNum<AxlelogicNum;tmpNum++)
				{
					/*�������δ���*/
					if (tempAxleSgmt1->tmnlAxleSgmtId[tmpNum] != UINT16_MAX)
					{
						/*tempAxleSgmt2Ϊ���ں�һ����������*/
						tempAxleSgmt2 = GetIndexIdAxleSectionDataStru(tempAxleSgmt1->tmnlAxleSgmtId[tmpNum]);
						/*��tLogicSgmtΪ���ں�һ���������εĵ�һ���߼�����*/
						/*���е������ʱ���߼����κͼ�������Ϊͬһ��*/
						tLogicSgmt = GetIndexIdLogicSectionDataStru(tempAxleSgmt2->logicSecId[0]);
						/*�������飬���tLogicSgmt�߼������Ƿ�������������У�Ѱ�ұ�־��Ϊ1*/

						for(i=DEFAULT_ZERO;i<logicNum;i++)
						{
							/*�ڵĻ����������Ѱ�ң�Ѱ�ұ����Ϊ1*/
							if(tLogicSgmt->indexId == pLogicId[i])
							{
								logicSgmtRear = tLogicSgmt;
								logicSgmeCount++;
								orderpLogicId[logicSgmeCount] = logicSgmtRear->indexId;
								isFind = 1u;
								break;
							}
						}

					} 
					else
					{
						/*������һ��������ڼ�������*/
					}
				}
				/*�����������isfind==0��
				1.���������ڼ�������ȫ��Ϊ0xffff--��Ϊ��·���
				2.��ȫΪ0xffff--����·���
				���������δ�����·��ʱ���������ε����һ���߼����ζ����ڴ�������߼�����������*/
				if (isFind == DEFAULT_ZERO)
				{ 
					/*�˳�whileѭ��*/
					rearFlag = DEFAULT_ZERO;
					break;
				} 
				else
				{
					/*û���ҵ����һ���߼����Σ�����*/
				}
			}

			else
			{
				/*tLogicSgmtΪ�ն������߼�����*/
				tLogicSgmt = GetIndexIdLogicSectionDataStru(logicSgmtRear->mainTmnlLogicSgmtId);
				/*�������飬��tempLogicSgmt�߼������Ƿ��������������*/
				isFind = DEFAULT_ZERO;
				for(i=DEFAULT_ZERO;i<logicNum;i++)
				{
					/*�ڵĻ���������*/
					if(tLogicSgmt->indexId == pLogicId[i])
					{
						logicSgmtRear = tLogicSgmt;
						logicSgmeCount++;
						orderpLogicId[logicSgmeCount] = logicSgmtRear->indexId;
						isFind = 1u;
						break;
					}
				}
				if(DEFAULT_ZERO == isFind)
				{
					/*�ҵ�������*/
					rearFlag = DEFAULT_ZERO;
				}
			}
		}

		if(DEFAULT_ZERO == errorRetVal)
		{
			if(logicNum==(logicSgmeCount+1u))
			{
				/*�½ű�+1 = ����*/
				bReturnValue = DEFAULT_ZERO;
				
			}
			else
			{
				/*���ش�����*/
				bReturnValue = 2u;
			}
		}
	}
	else
	{
		/*���ش�����*/
		bReturnValue = 4u;
	}
	return bReturnValue;
}

/*******************************************
������	��	CheckLastTsrValid
����������  �����õ��߼������Ƿ��������õ��߼����δ��ڹ���ִ�
����	��  UINT16 pLogicId[DSU_TSRSECTIOM_NUM]  ����������
            UINT8_S logicNum             �������߼����θ���	
���	:   ��
����ֵ	��  1: ����ʱ�������������õ��߼�����ͬһ����Ķ�λ�ͷ�λ��
		    0:�ɹ�
*******************************************/
static UINT8_S  CheckLastTsrValid(const UINT16_S* pLogicId,const UINT8_S logicNum)
{
	Tsr_DataStru_Set_Stru* tempTsrDataStru = NULL;
	BnfLogicSectionStruct *tempLogicSgmt1,*tempLogicSgmt2;   /*�߼�������ʱ����*/
	UINT8_S ii = DEFAULT_ZERO;
	UINT8_S jj = DEFAULT_ZERO;
	UINT8_S kk = DEFAULT_ZERO;
	UINT16_S waitLogicNum = DEFAULT_ZERO;
	UINT8_S retValue = DEFAULT_ZERO;
	UINT8_S retRule = 0u;
	UINT8_S isFalg = 1u;

	if(( pLogicId != NULL)&&(logicNum <= LOGIC_MAX_NUM ))
	{
		tempTsrDataStru = GetTsrDataAdmin();
		/*�жϴ�����߼���Ŀ����Ҫ���õ��߼�����Ŀ��������ѭ�����������*/
		if(waitLogicNum <= logicNum)
		{
			for(ii = DEFAULT_ZERO;ii < (tempTsrDataStru->TsrQuan)&&(isFalg == 1u);ii++)
			{
				for(jj = DEFAULT_ZERO;(jj < tempTsrDataStru->CellTsrData[ii].LogicSecQuan)&&(isFalg == 1u);jj++)
				{
					tempLogicSgmt1 = GetIndexIdLogicSectionDataStru(tempTsrDataStru->CellTsrData[ii].LogicSecId[jj]);
				
					for(kk = DEFAULT_ZERO;(kk < logicNum)&&(isFalg == 1u);kk++)
					{
						tempLogicSgmt2 =  GetIndexIdLogicSectionDataStru(pLogicId[kk]);
						/*���߼����β�����ͬһ�������������غ�linkʱ����ͬʱ������ͬһ����Ķ�λ�ͷ�λ*/
						retRule = CheakTwoLogicRule(tempLogicSgmt1,tempLogicSgmt2);
						if( retRule == 1u)
						{
							isFalg =0u;
							retValue = 1u ;
						}						
					}

				}
	
			}
		}
		else
		{
			for(ii = DEFAULT_ZERO;(ii < logicNum)&&(isFalg == 1u);ii++)
			{
				tempLogicSgmt1 =  GetIndexIdLogicSectionDataStru(pLogicId[ii]);

				for(jj = DEFAULT_ZERO;jj < (tempTsrDataStru->TsrQuan)&&(isFalg == 1u);jj++)
				{
					for(kk = DEFAULT_ZERO;(kk < tempTsrDataStru->CellTsrData[jj].LogicSecQuan)&&(isFalg == 1u);kk++)
					{
						tempLogicSgmt2 = GetIndexIdLogicSectionDataStru(tempTsrDataStru->CellTsrData[jj].LogicSecId[kk]);
						/*���߼����β�����ͬһ�������������غ�linkʱ����ͬʱ������ͬһ����Ķ�λ�ͷ�λ*/
						retRule = CheakTwoLogicRule(tempLogicSgmt1,tempLogicSgmt2);
						if( retRule == 1u)
						{
							isFalg =0u;
							retValue = 1u ;
						}	
					}
				}
			}
		
		}
	
	}
	return retValue;
}

/*******************************************
������  ��	CheakTwoLogicRule
����������  �ж��Ƿ�Ϊͬһ����Ķ�λ�ͷ�λ
����    ��  BnfLogicSectionStruct *tempLogicSgmt1  �߼����α����ݽṹ��
			BnfLogicSectionStruct *tempLogicSgmt2  �߼����α����ݽṹ��
���    :   ��
����ֵ  ��  0 ��Ϊͬһ����Ķ�λ�ͷ�λ
			1 ��ͬһ����Ķ�λ�ͷ�λ
*******************************************/
static  UINT8_S CheakTwoLogicRule(BnfLogicSectionStruct *tempLogicSgmt1,BnfLogicSectionStruct *tempLogicSgmt2)
{
	UINT8_S  retValue =0u;
	/*���߼����β�����ͬһ�������������غ�linkʱ����ͬʱ������ͬһ����Ķ�λ�ͷ�λ*/
	if(tempLogicSgmt1->belongAxleSecId != tempLogicSgmt2->belongAxleSecId)
	{
		if((tempLogicSgmt1->startSegId == tempLogicSgmt2->startSegId)
			|| (tempLogicSgmt1->endSegId == tempLogicSgmt2->endSegId))
		{
			retValue = 1u ;
		}
	}
	return retValue;
}

