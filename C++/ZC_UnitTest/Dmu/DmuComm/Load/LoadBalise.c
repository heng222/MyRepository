/********************************************************
* 
* �� �� ���� LoadBalise.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����Balise���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadBalise.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����Balise����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadBaliseData(void)
{
    BnfBaliseStruct* BnfBaliseStru = NULL;/*Balise��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_BALISE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));

        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(BALISE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % BALISE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / BALISE_LINE_BYTE_NUM);

                /*д��BALISE��Ϣ�ṹ��ָ���ַ*/
                MallocBaliseDataStru(tempDataNum);
                BnfBaliseStru = GetBaliseData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfBaliseStru != NULL);i++)
                {
                    /*�������*/
                    BnfBaliseStru[i].indexId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*ID*/
                    BnfBaliseStru[i].baliseId = LongFromChar(pTempData);                        
                    pTempData += 4;
                    /*����*/
                    MemoryCpy(BnfBaliseStru[i].name,BALISE_NAME_BYTE_LEN,pTempData,BALISE_NAME_BYTE_LEN);
                    pTempData += BALISE_NAME_BYTE_LEN;
                    /*����seg���*/
                    BnfBaliseStru[i].segId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*����Segƫ������cm��*/
                    BnfBaliseStru[i].segOffset = LongFromChar(pTempData);                        
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
