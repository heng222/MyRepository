/********************************************************
* 
* �� �� ���� LoadAr.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����Ar���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadAr.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����Ar����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadArData(void)
{
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    BnfArStruct* bnfArStru = NULL;/*Ar��Ϣ�ṹ��ָ��*/
    

    /*��ȡ����*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_AR_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S) * (tempDataLen+50u));

        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(AR_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % AR_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / AR_LINE_BYTE_NUM);

                /*д��AR��Ϣ�ṹ��ָ���ַ*/
                MallocArDataStru(tempDataNum);
                bnfArStru = GetArData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(bnfArStru != NULL);i++)
                {
                    /*�������*/
                    bnfArStru[i].arId = ShortFromChar(pTempData);                        
                    pTempData += 2; 
                    /*�����۷�����վ̨���*/
                    bnfArStru[i].startPlartformId = ShortFromChar(pTempData);                        
                    pTempData += 2; 
                    /*�����۷�������Ӧͣ������*/
                    bnfArStru[i].arInStopPointId = ShortFromChar(pTempData);                        
                    pTempData += 2; 
                    /*�����۷����˵��Ӧͣ������*/
                    bnfArStru[i].revertPointId = ShortFromChar(pTempData);                        
                    pTempData += 2; 
                    /*�����۷��˳�վ̨���*/
                    bnfArStru[i].endPlartformId = ShortFromChar(pTempData);                        
                    pTempData += 2; 
                    /*�����۷��˳����Ӧͣ������*/
                    bnfArStru[i].aROutStopPointId = ShortFromChar(pTempData);                        
                    pTempData += 2;     
                    /*�����۷���ID*/
                    bnfArStru[i].aRLampID = ShortFromChar(pTempData);                        
                    pTempData += 2;     
                    /*�����۷���ťID*/
                    bnfArStru[i].aRButtonId = ShortFromChar(pTempData);                        
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
