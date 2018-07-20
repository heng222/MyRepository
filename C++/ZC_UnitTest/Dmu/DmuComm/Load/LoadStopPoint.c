/********************************************************
* 
* �� �� ���� LoadStopPoint.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����StopPoint���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadStopPoint.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����StopPoint����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadStopPointData(void)
{
    BnfStopPointStruct* BnfStopPointStru = NULL;/*StopPoint��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_STOPPOINT_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(STOPPOINT_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % STOPPOINT_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / STOPPOINT_LINE_BYTE_NUM);

                /*д��STOPPOINT��Ϣ�ṹ��ָ���ַ*/
                MallocStopPointDataStru(tempDataNum);
                BnfStopPointStru = GetStopPointData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfStopPointStru != NULL);i++)
                {
                    /*�������*/
                    BnfStopPointStru[i].stopPointId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*ͣ��������*/
                    BnfStopPointStru[i].attribute = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*ͣ�������÷���(16����)*/
                    BnfStopPointStru[i].dir = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*ͣ��������seg���*/
                    BnfStopPointStru[i].segId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*ͣ����Segƫ����*/
                    BnfStopPointStru[i].segOfst = LongFromChar(pTempData);                        
                    pTempData += 4;

                    /*ͣ�����ӦATO���ô���Χ*/
                    BnfStopPointStru[i].aTOParkArea = LongFromChar(pTempData);                        
                    pTempData += 4;
                    /*ͣ�����ӦATP���ô���Χ*/
                    BnfStopPointStru[i].aTPParkArea = LongFromChar(pTempData);                        
                    pTempData += 4;
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
