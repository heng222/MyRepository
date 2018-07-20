/********************************************************
* 
* �� �� ���� LoadTrainStation.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����TrainStation���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadTrainStation.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����TrainStation����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadTrainStationData(void)
{
    BnfTrainStationStruct* BnfTrainStationStru = NULL;/*TrainStation��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_TRAIN_STATION_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(TRAINSTATION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % TRAINSTATION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / TRAINSTATION_LINE_BYTE_NUM);

                /*д��TRAINSTATION��Ϣ�ṹ��ָ���ַ*/
                MallocTrainStationDataStru(tempDataNum);
                BnfTrainStationStru = GetTrainStationData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfTrainStationStru != NULL);i++)
                {
                    /*��վID*/
                    BnfTrainStationStru[i].stationId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*��վ����*/
                    MemoryCpy(BnfTrainStationStru[i].name,TRAINSTATION_NAME_BYTE_LEN,pTempData,TRAINSTATION_NAME_BYTE_LEN);
                    pTempData += TRAINSTATION_NAME_BYTE_LEN;
                    /*��վ����վ̨��Ŀ*/
                    BnfTrainStationStru[i].includeStationNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*վ̨���*/
                    for(j =0u;j < TRAINSTATION_ID_MAX_NUM;j++)
                    {
                        BnfTrainStationStru[i].stationIdBuff[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;
                    }
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
