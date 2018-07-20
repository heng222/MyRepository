/********************************************************
* 
* �� �� ���� LoadCommFailTime.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����CommFailTime���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadCommFailTime.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����CommFailTime����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadCommFailTimeData(void)
{
    BnfCommFailTimeStruct* BnfCommFailTimeStru = NULL;/*CommFailTime��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_COMMFAILTIME_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(COMMFAILTIME_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % COMMFAILTIME_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / COMMFAILTIME_LINE_BYTE_NUM);

                /*д��COMMFAILTIME��Ϣ�ṹ��ָ���ַ*/
                MallocCommFailTimeDataStru(tempDataNum);
                BnfCommFailTimeStru = GetCommFailTimeData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfCommFailTimeStru != NULL);i++)
                {
                    /*ATP��ZCͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].atpToZcCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ZC��ATPͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].zcToAtpCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;
                    

                    /*ATP��CIͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].atpToCiCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*CI��ATPͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].ciToAtpCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ATP��ATSͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].atpToAtsCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ATS��ATPͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].atsToAtpCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ZC��DMSͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].zcToDmsCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*DMS��ZCͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].dmsToZcCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ZC��CIͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].zcToCiCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;
                    
                    /*CI��ZCͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].ciToZcCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*DMS��ATSͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].dmsToAtsCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ATS��DMSͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].atsToDmsCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ZC��ATSͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].zcToAtsCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*ZC��ZCͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].zcToZcCommFailTime = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*CI��CIͨ�Ź���ʱ��*/
                    BnfCommFailTimeStru[i].ciToCiCommFailTime = LongFromChar(pTempData);    
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
