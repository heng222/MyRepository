/********************************************************
* 
* �� �� ���� LoadTrainControlLevel.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����TrainControlLevel���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadTrainControlLevel.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����TrainControlLevel����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadTrainControlLevelData(void)
{
    BnfTrainControlLevelStruct* BnfTrainControlLevelStru = NULL;/*TrainControlLevel��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_TRAIN_CONTROL_LEVEL_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(TRAINCONTROLLEVEL_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % TRAINCONTROLLEVEL_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / TRAINCONTROLLEVEL_LINE_BYTE_NUM);

                /*д��TRAINCONTROLLEVEL��Ϣ�ṹ��ָ���ַ*/
                MallocTrainControlLevelDataStru(tempDataNum);
                BnfTrainControlLevelStru = GetTrainControlLevelData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfTrainControlLevelStru != NULL);i++)
                {
                    /*�������*/
                    BnfTrainControlLevelStru[i].indexId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�������seg���*/
                    BnfTrainControlLevelStru[i].startSegId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�������Segƫ����*/
                    BnfTrainControlLevelStru[i].startOffset = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*�յ�����seg���*/
                    BnfTrainControlLevelStru[i].endSegId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�յ�����Segƫ����*/
                    BnfTrainControlLevelStru[i].endOffset = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*��CBTC�����г����з���*/
                    BnfTrainControlLevelStru[i].dir = ShortFromChar(pTempData);    
                    pTempData += 2;

                }
            }
            else
            {
                /*���ݳ��ȴ���*/
                retVal = -1;
            }
        
        }
    }

    return retVal;
}
