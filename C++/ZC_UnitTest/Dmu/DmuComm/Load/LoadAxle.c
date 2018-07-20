/********************************************************
* 
* �� �� ���� LoadAxle.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����Axle���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadAxle.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����Axle����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadAxleData(void)
{
    BnfAxleStruct* BnfAxleStru = NULL;/*Axle��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_AXLE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));

        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(AXLE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % AXLE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / AXLE_LINE_BYTE_NUM);

                /*д��AXLE��Ϣ�ṹ��ָ���ַ*/
                MallocAxleDataStru(tempDataNum);
                BnfAxleStru = GetAxleData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfAxleStru != NULL);i++)
                {
                    /*�������*/
                    BnfAxleStru[i].axleId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*Ӧ��������*/
                    MemoryCpy(BnfAxleStru[i].axleName,AXLE_NAME_BYTE_NUM,pTempData,AXLE_NAME_BYTE_NUM);
                    pTempData += AXLE_NAME_BYTE_NUM;

                    /*����Segƫ����*/
                    BnfAxleStru[i].axleSegOfst = LongFromChar(pTempData);          
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
