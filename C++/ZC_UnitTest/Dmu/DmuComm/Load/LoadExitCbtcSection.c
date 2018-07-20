/********************************************************
* 
* �� �� ���� LoadExitCbtcSection.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����ExitCbtcSection���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadExitCbtcSection.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����ExitCbtcSection����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadExitCbtcSectionData(void)
{
    BnfExitCbtcSectionStruct* BnfExitCbtcSectionStru = NULL;/*ExitCbtcSection��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_EXIT_CBTC_SECTION_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(EXITCBTCSECTION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % EXITCBTCSECTION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / EXITCBTCSECTION_LINE_BYTE_NUM);

                /*д��EXITCBTCSECTION��Ϣ�ṹ��ָ���ַ*/
                MallocExitCbtcSectionDataStru(tempDataNum);
                BnfExitCbtcSectionStru = GetExitCbtcSectionData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfExitCbtcSectionStru != NULL);i++)
                {
                    BnfExitCbtcSectionStru[i].indexId = ShortFromChar(pTempData);                        /*�������*/
                    pTempData += 2;

                    BnfExitCbtcSectionStru[i].dir = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    BnfExitCbtcSectionStru[i].attribute = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    BnfExitCbtcSectionStru[i].startOffset = LongFromChar(pTempData);                    
                    pTempData += 4;

                    BnfExitCbtcSectionStru[i].endOffSet = LongFromChar(pTempData);                    
                    pTempData += 4;

                    BnfExitCbtcSectionStru[i].segNum = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    for(j = 0u;j < EXITCBTCSECTION_SEG_MAX_NUM;j++)
                    {
                        BnfExitCbtcSectionStru[i].segInfoBuff[j] = ShortFromChar(pTempData);                    
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
