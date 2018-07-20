/********************************************************
* 
* �� �� ���� LoadLogicSection.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����LogicSection���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadLogicSection.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����LogicSection����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadLogicSectionData(void)
{
    BnfLogicSectionStruct* BnfLogicSectionStru = NULL;/*LogicSection��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_LGC_SGMT_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(LOGICSECTION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % LOGICSECTION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / LOGICSECTION_LINE_BYTE_NUM);

                /*д��LOGICSECTION��Ϣ�ṹ��ָ���ַ*/
                MallocLogicSectionDataStru(tempDataNum);
                BnfLogicSectionStru = GetLogicSectionData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfLogicSectionStru != NULL);i++)
                {
                    /*�������*/
                    BnfLogicSectionStru[i].indexId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*����*/
                    MemoryCpy(BnfLogicSectionStru[i].name,LOGICSECTION_NAME_BYTE_LEN,pTempData,LOGICSECTION_NAME_BYTE_LEN);
                    pTempData += LOGICSECTION_NAME_BYTE_LEN;
                    /*�������Seg���*/     
                    BnfLogicSectionStru[i].startSegId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*�������Seg���*/     
                    BnfLogicSectionStru[i].startSegOffset = LongFromChar(pTempData);                        
                    pTempData += 4;
                    /*�յ�����Seg���*/     
                    BnfLogicSectionStru[i].endSegId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*�յ�����Seg���*/     
                    BnfLogicSectionStru[i].endSegOffset = LongFromChar(pTempData);                        
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
