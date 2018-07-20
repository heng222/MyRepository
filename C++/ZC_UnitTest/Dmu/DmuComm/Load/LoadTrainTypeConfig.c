/********************************************************
* 
* �� �� ���� LoadTrainTypeConfig.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����TrainTypeConfig���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadTrainTypeConfig.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����TrainTypeConfig����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadTrainTypeConfigData(void)
{
    BnfTrainTypeConfigStruct* BnfTrainTypeConfigStru = NULL;/*TrainTypeConfig��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_TRAINTYPE_CONFIG_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(TRAINTYPECONFIG_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % TRAINTYPECONFIG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / TRAINTYPECONFIG_LINE_BYTE_NUM);

                /*д��TRAINTYPECONFIG��Ϣ�ṹ��ָ���ַ*/
                MallocTrainTypeConfigDataStru(tempDataNum);
                BnfTrainTypeConfigStru = GetTrainTypeConfigData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfTrainTypeConfigStru != NULL);i++)
                {
                    /*�г�����*/
                    BnfTrainTypeConfigStru[i].trainDevName = ShortFromChar(pTempData);    
                    pTempData += 2;    

                    /*�г�����*/
                    BnfTrainTypeConfigStru[i].trainType = *pTempData;    
                    pTempData += 1;    
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
