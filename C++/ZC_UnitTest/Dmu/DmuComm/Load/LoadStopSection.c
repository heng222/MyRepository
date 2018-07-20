/********************************************************
* 
* �� �� ���� LoadStopSection.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����StopSection���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadStopSection.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����StopSection����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadStopSectionData(void)
{
    BnfStopSectionStruct* BnfStopSectionStru = NULL;/*StopSection��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_STOPSECTION_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(STOPSECTION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % STOPSECTION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / STOPSECTION_LINE_BYTE_NUM);

                /*д��STOPSECTION��Ϣ�ṹ��ָ���ַ*/
                MallocStopSectionDataStru(tempDataNum);
                BnfStopSectionStru = GetStopSectionData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfStopSectionStru != NULL);i++)
                {
                    /*�������*/
                    BnfStopSectionStru[i].stopSectionId = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*������վ����*/
                    MemoryCpy(BnfStopSectionStru[i].stationName,STOPSECTION_STATION_NAME_LEN,pTempData,STOPSECTION_STATION_NAME_LEN);
                    pTempData +=STOPSECTION_STATION_NAME_LEN;
                    /*Ŀ�ĵر��*/
                    MemoryCpy(BnfStopSectionStru[i].bDesId,STOPSECTION_DEST_CODE_LEN,pTempData,STOPSECTION_DEST_CODE_LEN);
                    pTempData +=STOPSECTION_DEST_CODE_LEN;
                    /*ͣ������seg���*/
                    BnfStopSectionStru[i].segId = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*ͣ����������*/
                    BnfStopSectionStru[i].sttribute = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*վ̨��Сͣվʱ��*/
                    BnfStopSectionStru[i].minParkTime = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*վ̨���ͣվʱ��*/
                    BnfStopSectionStru[i].maxParkTime = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*վ̨Ĭ��ͣվʱ��*/
                    BnfStopSectionStru[i].parkTime = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*վ̨���ŷ�ʽ*/
                    BnfStopSectionStru[i].doorOpenMode = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*վ̨����ʱ����*/
                    BnfStopSectionStru[i].doorOpenTime = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*վ̨���ŷ�ʽ*/
                    BnfStopSectionStru[i].doorCloseMode = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*վ̨����ʱ����*/
                    BnfStopSectionStru[i].doorCloseTime = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*վ̨Ĭ��ͣ��ʱ��*/
                    BnfStopSectionStru[i].parkSteadyTime = ShortFromChar(pTempData);    
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
