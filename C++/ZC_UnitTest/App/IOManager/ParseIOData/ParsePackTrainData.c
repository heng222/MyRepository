/************************************************************************
*
* �ļ���   ��  ParsePackTrainData.c
* ����ʱ�� ��  2015.04.14
* ����     ��  ZC��
* �������� ��  ��������г����ݹ���  
* ��  ע	��  ��
*
************************************************************************/

#include "ParsePackTrainData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../TrainManager/Train/TrainDefine.h"
#include "../CommTarget/CommTargetStatusData.h"
#include "../CommTarget/CommTargetConfigData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../../Common/Convert.h"
#include "../../LineDataManager/DR/DRDefine.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Copy.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Dmu/DmuComm/Data/SegData.h"
#include "../../TrainManager/Train/TrainStatusData.h"

ZcAndTrainIODataStruct gToTrainDataStruBuff[SIZE_MAX_LINE_TRAIN];               /*zc������ATP�����ݽṹ*/
UINT16_S gToTrainDataIdBuff[SIZE_MAX_LINE_TRAIN+1U] = {SIZE_MAX_LINE_TRAIN+1U};  /*ID��������*/
UINT8_S  gToTrainCurSum = 0U;                                                  /*ZC�������ATP���������*/

ZcAndTrainIODataStruct TrainInDataStruBuff[SIZE_MAX_LINE_TRAIN];               /*����ATP��������ݽṹ*/
UINT16_S gTrainInDataIdBuff[SIZE_MAX_LINE_TRAIN+1U] = {SIZE_MAX_LINE_TRAIN+1U};  /*ID��������*/
UINT8_S  gTrainInCurSum = 0U;                                                  /*����ATP������������*/

/*
* ���������� ��ȡ����ATP������������
* ����˵���� void
* ����ֵ  �� SIZE_MAX_LINE_TRAIN+1: ʧ��
*			>=0: ����      
*/
UINT8_S GetTrainToZcCurSum(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if (gTrainInCurSum <= SIZE_MAX_LINE_TRAIN)
	{
		rtnValue = gTrainInCurSum;
	} 
	else
	{
		rtnValue = SIZE_MAX_LINE_TRAIN+1U;
	}

	return rtnValue;
}

/*
* ������������ȡ����ATP����Zc��Id��Ӧ�г�ID
* ����˵���� const UINT8 trainIdOfIndex
* ����ֵ  �� 0: ʧ��
*			 >0: �ɹ�      
*/
UINT16_S GetTrainToZcBuffIndexOfTrainId(const UINT8_S trainIdOfIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

    if (SIZE_MAX_LINE_TRAIN < trainIdOfIndex)
    {
        rtnValue = DEFAULT_ZERO;
    } 
    else
    {
        rtnValue = TrainInDataStruBuff[trainIdOfIndex].TrainId;
    }

	return rtnValue;
}

/*
* ������������ȡ����ATP����Zc��Id��Ӧ���ݳ���
* ����˵���� const UINT8 ciIdOfIndex
* ����ֵ  �� 0: ʧ��
*			 >0: �ɹ�      
*/
UINT16_S GetTrainToZcIdDataBufLen(const UINT8_S trainIdOfIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

    if (SIZE_MAX_LINE_TRAIN < trainIdOfIndex)
    {
        rtnValue = DEFAULT_ZERO;
    } 
    else
    {        
        rtnValue = TrainInDataStruBuff[trainIdOfIndex].ValueBuffLen;
    }

	return rtnValue;
}

/*
* ���������� ��ȡ����ATP����Zc��Id��Ӧ������Ϣ
* ����˵���� const UINT8 trainIdOfIndex
* ����ֵ  �� NULL: ʧ��
*			 !NULL: �ɹ�      
*/
UINT8_S* GetTrainToZcBufDataOfIndex(const UINT8_S trainIdOfIndex)
{
	UINT8_S *pRtnValue = NULL;

    if (SIZE_MAX_LINE_TRAIN < trainIdOfIndex)
    {
        pRtnValue = NULL;
    } 
    else
    {        
        pRtnValue = TrainInDataStruBuff[trainIdOfIndex].ValueBuff;
    }

	return pRtnValue;
}

/*
* ���������� ��������ATP����ĵ�֡����
* ����˵���� const UINT8_S dataBuff[], ���ݻ�����
*            const UINT16_S dataLength, ���ݳ���
* ����ֵ  �� 0: ���ݽ���ʧ��
*			 1: ���ݽ����ɹ�      
*/
UINT8_S ParseTrainToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength)
{
	UINT8_S sourceId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S copyRtn = DEFAULT_ZERO;
	UINT16_S headTest = DEFAULT_ZERO;
	UINT32_S headTestOffset = DEFAULT_ZERO;
	UINT16_S tailTest = DEFAULT_ZERO;
	UINT32_S tailTestOffset = DEFAULT_ZERO;
	/*
    UINT16_S controlZcId = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    */

	if ((dataBuff != NULL) && (dataLength > 0U))
	{
		/*����֡ͷ,�ж��Ƿ�Ϊ��ZCͨ�ŵĳ���ATP*/
		sourceId = dataBuff[1];

		if (sourceId < SIZE_MAX_LINE_TRAIN)
		{
			/*��ȡͨ������,�ж����������Ƿ�Ϸ�*/
			if (RETURN_SUCCESS == TrainInputDataValidityCheck(&dataBuff[0],dataLength))
			{
				/* ���ӿ�ȷ����д������ */
				/*��д�г�Id*/
				TrainInDataStruBuff[gTrainInCurSum].TrainId = sourceId;

				/*��ȡ���ݳ���*/
				TrainInDataStruBuff[gTrainInCurSum].ValueBuffLen = dataLength;
				copyRtn = MemoryCpy(TrainInDataStruBuff[gTrainInCurSum].ValueBuff,((UINT32_S)(ZC_TRAIN_COM_BYTE_SUM_MAX)),&dataBuff[0],((UINT32_S)TrainInDataStruBuff[gTrainInCurSum].ValueBuffLen));

				if (DEFAULT_ZERO == copyRtn)
				{
					gTrainInDataIdBuff[sourceId] = gTrainInCurSum;

					/*��ӡ��������*/
					headTest = ShortFromChar(&TrainInDataStruBuff[gTrainInCurSum].ValueBuff[5]);
					headTestOffset = LongFromChar(&TrainInDataStruBuff[gTrainInCurSum].ValueBuff[7]);
					tailTest = ShortFromChar(&TrainInDataStruBuff[gTrainInCurSum].ValueBuff[11]);
					tailTestOffset = LongFromChar(&TrainInDataStruBuff[gTrainInCurSum].ValueBuff[13]);

#ifdef SYS_TYPE_WINDOWS
                    LogPrintf(1U,"2.1 Train[%d]Input,Loc:%d,%d;%d,%d;InType=%d,%d,len=%d\n",sourceId,headTest,headTestOffset,tailTest,tailTestOffset,TrainInDataStruBuff[gTrainInCurSum].ValueBuff[4],gTrainInCurSum,dataLength); 
#endif					
					gTrainInCurSum++;

					/*���ڱ�ZCͨ��ATP, ����ͨ��״̬*/
					SetCommTargetStatus(INNER_DEVTYPE_TRAIN,((UINT16_S)sourceId),COMM_STATUS_NORMAL);
#if 0
					/*11.30,dnw,���Ӳ��ܱ�ZC���Ƶ��г�,������ͨ�ż�ʱλ*/
                    controlZcId = GetTrainControlZc((UINT16_S)sourceId);
                    localZcId = GetLocalZcId();

					if (localZcId == controlZcId)
					{
						SetCommTargetCycle(INNER_DEVTYPE_TRAIN,((UINT16_S)sourceId),DEFAULT_ZERO);
					} 
					else
					{
						/* ������ */
					}
#endif
                    SetCommTargetCycle(INNER_DEVTYPE_TRAIN,((UINT16_S)sourceId),DEFAULT_ZERO);

					rtnValue = RETURN_SUCCESS;
				} 
				else
				{
					gTrainInDataIdBuff[sourceId] = SIZE_MAX_LINE_TRAIN + 1U;
					TrainInDataStruBuff[gTrainInCurSum].TrainId = DEFAULT_ZERO;
					TrainInDataStruBuff[gTrainInCurSum].ValueBuffLen = DEFAULT_ZERO;
					rtnValue = RETURN_ERROR;
				}
			} 
			else
			{
				LogPrintf(1U,"Train Data Check Error!\n");
				rtnValue = RETURN_ERROR;
			}
		} 
		else
		{
			/*����150��ID���г������*/
		}
	}
	else
	{
		rtnValue =  RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� У�鳵��ATP�����������ȷ��
* ����˵���� const UINT8_S dataBuff[],��������   
*            const UINT16_S dataLen,���ݳ���
* ����ֵ  �� 0:�Ϸ���У��ʧ��
*			 1:�Ϸ���У��ɹ�      
*/
UINT8_S TrainInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen)
{
    UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S trainId = DEFAULT_ZERO;
	UINT16_S  trainHeadLink = DEFAULT_ZERO;        
	UINT32_S  trainHeadOffset = DEFAULT_ZERO;        
	UINT16_S  trainTailLink = DEFAULT_ZERO;         
	UINT32_S  trainTailOffset = DEFAULT_ZERO;        
	UINT8_S  trainRealDir = DEFAULT_ZERO;  
	UINT8_S trainUnSafeDir = DEFAULT_ZERO;
	UINT16_S checkErrorFlag = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S trainLength = DEFAULT_ZERO;
	UINT16_S twoPointDist = DEFAULT_ZERO;
    UINT16_S lineMaxSpeed = DEFAULT_ZERO;
    UINT32_S lineMaxTSRSpeed = DEFAULT_ZERO;
	UINT32_S headLinkLen = DEFAULT_ZERO;
    UINT32_S tailLinkLen = DEFAULT_ZERO;

	if ((dataBuff != NULL) && (dataLen > 0U))
	{
		/*��ȡ�г�ID*/
		trainId = (UINT16_S)(ShortFromChar(&dataBuff[addIndex]) & ((UINT16_S)0x00ffU));
		addIndex = addIndex + 2U;

		/*����ZCId*/
		addIndex = addIndex + 2U;

		/*У���г�������Ϣ*/		
		if ((TRAIN_IN_APPLY_MA == dataBuff[addIndex])
			|| (TRAIN_IN_CHANGED == dataBuff[addIndex])
			|| (TRAIN_IN_HANDOVERTOCANCEL == dataBuff[addIndex])
			|| (TRAIN_IN_REVERSETOCANCEL == dataBuff[addIndex])
			|| (TRAIN_IN_TOEXITCBTC == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_1);
            addIndex++;
		}

		/*У���г�λ����Ϣ*/
		trainHeadLink = ShortFromChar(&dataBuff[addIndex]);
		addIndex = addIndex + 2U;

		trainHeadOffset = LongFromChar(&dataBuff[addIndex]);
		addIndex = addIndex + 4U;

		trainTailLink = ShortFromChar(&dataBuff[addIndex]);
		addIndex = addIndex + 2U;

		trainTailOffset = LongFromChar(&dataBuff[addIndex]);
		addIndex = addIndex + 4U;

        headLinkLen = GetSegDataStrulength(trainHeadLink);

        tailLinkLen = GetSegDataStrulength(trainTailLink);

        if ((headLinkLen >= trainHeadOffset) && (tailLinkLen >= trainTailOffset))
        {
            /* ����λ����Ϣ�Ϸ� */
        } 
        else
        {
            checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_2);
        }
        
        /* �������з��� */
        trainUnSafeDir = dataBuff[addIndex];
        addIndex = addIndex + 1U;
        
        /* ʵ�����з��� */
        trainRealDir = dataBuff[addIndex];
        addIndex = addIndex + 1U;

		if (((TRAIN_UNSAFE_DIR_UP == trainUnSafeDir) || ((TRAIN_UNSAFE_DIR_DOWN == trainUnSafeDir))) &&
			((TRAIN_UNSAFE_DIR_UP == trainRealDir) || ((TRAIN_UNSAFE_DIR_DOWN == trainRealDir))))
		{
            /* ������ */
		} 
		else
		{
			/* ���з�����ϢУ��ʧ�� */
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_3);
		}
         
		/*��ѯ�г������Ƿ������·ʵ���������*/
		trainLength = GetTrainLength(trainId); 
		twoPointDist = (UINT16_S)CheckDistanceBetweenTwoPoints(trainTailLink,trainTailOffset,trainHeadLink,trainHeadOffset,trainUnSafeDir);
		if (trainLength >= twoPointDist)
		{
			/*������ϢУ��ɹ�*/
		} 
		else
		{
			/*������ϢУ��ʧ��*/
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_4);
		}	
        
		/*У���ʻģʽ*/
		if ((TRAIN_IN_MODE_RM == dataBuff[addIndex])
			|| (TRAIN_IN_MODE_RD == dataBuff[addIndex])
			|| (TRAIN_IN_MODE_AM == dataBuff[addIndex])
			|| (TRAIN_IN_MODE_CM == dataBuff[addIndex])
			|| (TRAIN_IN_MODE_EUM == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_5);
            addIndex++;
		}

		/*У�����м���*/
		if ((TRAIN_IN_LEVEL_BLOC == dataBuff[addIndex])
			|| (TRAIN_IN_LEVEL_CBTC == dataBuff[addIndex])
			|| (TRAIN_IN_LEVEL_IL == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_6);
            addIndex++;
		}

		/*У���г��ٶ�*/
        lineMaxSpeed = GetLineMaxSpeed();
		if (ShortFromChar(&dataBuff[addIndex]) <= lineMaxSpeed)
		{
			addIndex = addIndex + 2U;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_7);
            addIndex = addIndex + 2U;
		}

		/*У��ͣ����Ϣ*/
		if ((FLAG_SET == dataBuff[addIndex])
			|| (FLAG_UNSET == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_8);
            addIndex++;
		}

		/*������ȷ�������͵���ƫ��*/
		addIndex = addIndex + 4U;

		/*У���г������ٶ�*/
        lineMaxTSRSpeed = (((((UINT32_S)GetLineMaxTSRSpeed()) * 1000U) / 36U) & ((UINT32_S)0x0000ffffU));
		if (ShortFromChar(&dataBuff[addIndex]) <= lineMaxTSRSpeed)
		{
			addIndex = addIndex + 2U;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_9);
            addIndex = addIndex + 2U;
		}

		/*У���г���������Ϣ*/
		if ((FLAG_SET == dataBuff[addIndex])
			|| (FLAG_UNSET == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_10);
            addIndex++;
		}

		/*У���г������ƶ���Ϣ*/
		if ((FLAG_SET == dataBuff[addIndex])
			|| (FLAG_UNSET == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_11);
            addIndex++;
		}

		/*���������۷���ID*/
		addIndex = addIndex + 2U;

		/*У�������۷���״̬*/
		if ((DR_LAMP_TWINKLE_STATUS == dataBuff[addIndex])
			|| (DR_LAMP_STEADY_STATUS == dataBuff[addIndex])
			|| (DEFAULT_0XFF == dataBuff[addIndex]))
		{
			addIndex++;
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_12);
            addIndex++;
		}

		/*���������ֽ�*/
		addIndex = addIndex + 10U;

		if (addIndex == dataLen)
		{
            /*������*/
		} 
		else
		{
			checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_13);
		}
	}
	else
	{
		checkErrorFlag = (UINT16_S)(checkErrorFlag | ZC_ERROR_CODE_14);
	}

	if (DEFAULT_ZERO == checkErrorFlag)
	{
		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
        LogPrintf(1U,"TrainCheck[%d],%d,%d,%d\n",trainId,checkErrorFlag,addIndex,dataLen);
	}

	return rtnValue;
}

/*
* ���������� ��ȡZC�������Atp���������
* ����˵���� void
* ����ֵ  �� SIZE_MAX_LINE_TRAIN+1: ʧ��
*			 >0: �ɹ�      
*/
UINT8_S GetToTrainCurSum(void)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if (gToTrainCurSum <= SIZE_MAX_LINE_TRAIN)
	{
		rtnValue =  gToTrainCurSum;
	} 
	else
	{
		rtnValue =  SIZE_MAX_LINE_TRAIN + 1U;
	}

	return rtnValue;
}

/*
* ���������� ��ȡZC�������ATP��Id��Ӧ���ݳ���
* ����˵���� const UINT8 trainIdOfIndex
* ����ֵ  �� 0: ʧ��
*			 >0: �ɹ�      
*/
UINT16_S GetToTrainIdDataBufLen(const UINT8_S trainIdOfIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

    if (SIZE_MAX_LINE_TRAIN < trainIdOfIndex)
    {
        rtnValue = DEFAULT_ZERO;
    } 
    else
    {
        rtnValue = gToTrainDataStruBuff[trainIdOfIndex].ValueBuffLen;
    }

	return rtnValue;
}

/*
* ���������� ��ȡZC�������Atp��Id�±��Ӧ������
* ����˵���� const UINT8 trainIdOfIndex
* ����ֵ  �� NULL: ʧ��
*			 !NULL: �ɹ�      
*/
UINT8_S* GetToTrainBufDataOfIndex(const UINT8_S trainIdOfIndex)
{
	UINT8_S *pRtnValue = NULL;

	if (SIZE_MAX_LINE_TRAIN < trainIdOfIndex)
	{
		pRtnValue = NULL;
	} 
	else
	{
        pRtnValue = gToTrainDataStruBuff[trainIdOfIndex].ValueBuff;
	}

	return pRtnValue;
}

/*
* ���������� �鳵��ATP����
* ����˵���� const UINT8* dataBuff,���ݻ���
*            const UINT16_S dataLength,���ݳ���
*            const UINT16_S destId, Ŀ��ID   
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S PackZcToTrainFrameData(const UINT8_S* dataBuff,const UINT16_S dataLength,const UINT16_S destId)
{
	UINT16_S index = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S copyRtn = 1U;

	if ((dataBuff != NULL) && (dataLength > 0U))
	{
		/*��д��λ��Ϣ����֡ͷ*/
        if (SIZE_MAX_LINE_TRAIN <= gToTrainCurSum)
        {
            /*������Ч*/
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            gToTrainDataStruBuff[gToTrainCurSum].TrainId = (UINT8_S)destId;

            /*��������*/
            gToTrainDataIdBuff[destId] = gToTrainCurSum;

            /*��д��Ϣ֡ͷ��Ϣ*/
            /*��дԴ�豸*/
            gToTrainDataStruBuff[gToTrainCurSum].ValueBuff[index] = INNER_DEVTYPE_ZC;
            index = index + 1U;

            gToTrainDataStruBuff[gToTrainCurSum].ValueBuff[index] = (UINT8_S)GetLocalZcId();
            index = index + 1U;

            /*��дĿ���豸*/
            gToTrainDataStruBuff[gToTrainCurSum].ValueBuff[index] = INNER_DEVTYPE_TRAIN;
            index = index + 1U;

            gToTrainDataStruBuff[gToTrainCurSum].ValueBuff[index] = (UINT8_S)destId;
            index = index + 1U;

            gToTrainDataStruBuff[gToTrainCurSum].ValueBuffLen = dataLength;   /*dataLength + index*/

            /*��������*/
            /* ͳһ�������Ѿ���Դ���͡�ԴID��Ŀ�����͡�Ŀ��ID��4���ֽ���д��,���±��0��ʼ */
            copyRtn = MemoryCpy(&gToTrainDataStruBuff[gToTrainCurSum].ValueBuff[0],((UINT32_S)(ZC_TRAIN_COM_BYTE_SUM_MAX - (UINT32_S)index)),dataBuff,((UINT32_S)dataLength));

            if (1U == copyRtn)
            {
                /*�����Ϣ*/
                gToTrainDataStruBuff[gToTrainCurSum].TrainId = 0U;		
                gToTrainDataIdBuff[destId] = LINE_CI_SUM_MAX;
                gToTrainDataStruBuff[gToTrainCurSum].ValueBuffLen = DEFAULT_ZERO;

                rtnValue = RETURN_ERROR;
            } 
            else
            {
                /*��������*/
                gToTrainCurSum++;
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
* ���������� ��ձ��������г���Atp������Ϣ
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearCycleTrainInputData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	/*�������*/
	for (cycle = DEFAULT_ZERO;cycle < SIZE_MAX_LINE_TRAIN;cycle++)
	{
		MemorySet(&TrainInDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndTrainIODataStruct))),
                    DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndTrainIODataStruct))));
	}

	/*�����������*/
	gTrainInCurSum = 0U;

	/*��չ�������*/
	for (cycle = 0U;cycle < (SIZE_MAX_LINE_TRAIN + 1U);cycle++)
	{
		gTrainInDataIdBuff[cycle] = SIZE_MAX_LINE_TRAIN + 1U;
	}
}

/*
* ���������� ��ձ������������������Atp��Ϣ
* ����˵���� ��
* ����ֵ  �� ��      
*/
void ClearCycleTrainOutputData(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	/*�������*/
	for (cycle = DEFAULT_ZERO;cycle < SIZE_MAX_LINE_TRAIN;cycle++)
	{
		MemorySet(&gToTrainDataStruBuff[cycle],((UINT32_S)(sizeof(ZcAndTrainIODataStruct))),
                     DEFAULT_ZERO,((UINT32_S)(sizeof(ZcAndTrainIODataStruct))));
	}

	/*����������*/
	gToTrainCurSum = 0U;

	/*��չ�������*/
	for (cycle = 0U;cycle < (SIZE_MAX_LINE_TRAIN + 1U);cycle++)
	{
		gToTrainDataIdBuff[cycle] = SIZE_MAX_LINE_TRAIN + 1U;
	}
}
