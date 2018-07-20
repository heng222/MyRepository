/********************************************************
* 
* �� �� ���� LoadAxleSection.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����AxleSection���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadAxleSection.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����AxleSection����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadAxleSectionData(void)
{
    BnfAxleSectionStruct* BnfAxleSectionStru = NULL;/*AxleSection��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*д��ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_AXLE_SGMT_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(AXLESECTION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % AXLESECTION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / AXLESECTION_LINE_BYTE_NUM);

                /*д��AXLESECTION��Ϣ�ṹ��ָ���ַ*/
                MallocAxleSectionDataStru(tempDataNum);
                BnfAxleSectionStru = GetAxleSectionData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfAxleSectionStru != NULL);i++)
                {
                    /*�������*/
                    BnfAxleSectionStru[i].indexId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*Ӧ��������*/
                    MemoryCpy(BnfAxleSectionStru[i].axleStcName,AXLESECTION_NAME_BYTE_NUM,pTempData,AXLESECTION_NAME_BYTE_NUM);
                    pTempData += AXLESECTION_NAME_BYTE_NUM;
                    /*����Seg��Ŀ*/     
                    BnfAxleSectionStru[i].includeSegNum = ShortFromChar(pTempData);          
                    pTempData += 2;  
                    
                    /*Seg���*/
                    for(j = 0u;j<AXLESECTION_SEG_MAX_NUM;j++)
                    {
                        BnfAxleSectionStru[i].segIdBuff[j] = ShortFromChar(pTempData);          
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
