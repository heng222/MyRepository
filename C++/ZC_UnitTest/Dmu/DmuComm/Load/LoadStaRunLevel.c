/********************************************************
* 
* �� �� ���� LoadStaRunLevel.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����StaRunLevel���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadStaRunLevel.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����StaRunLevel����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadStaRunLevelData(void)
{
    BnfStaRunLevelStruct* BnfStaRunLevelStru = NULL;/*StaRunLevel��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_STA_RUN_LEVEL_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(STARUNLEVEL_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % STARUNLEVEL_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / STARUNLEVEL_LINE_BYTE_NUM);

                /*д��STARUNLEVEL��Ϣ�ṹ��ָ���ַ*/
                MallocStaRunLevelDataStru(tempDataNum);
                BnfStaRunLevelStru = GetStaRunLevelData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfStaRunLevelStru != NULL);i++)
                {
                    /*�������*/
                    BnfStaRunLevelStru[i].indexId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*���Ŀ�ĵر��*/
                    BnfStaRunLevelStru[i].startDestId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*�յ�Ŀ�ĵر��*/
                    BnfStaRunLevelStru[i].endDestId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*���м���ּ���Ŀ*/
                    BnfStaRunLevelStru[i].runLevelNum = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    for (j = 0u; j < STARUNLEVEL_LEVEL_NUM; j++)
                    {
                        /*������*/
                        BnfStaRunLevelStru[i].runLevelStru[j].levelId = ShortFromChar(pTempData);                        
                        pTempData += 2;

                        /*����1��Ӧʱ��*/
                        BnfStaRunLevelStru[i].runLevelStru[j].levelTime = ShortFromChar(pTempData);                        
                        pTempData += 2;

                        /*����1��Ӧ�ٶ�*/
                        BnfStaRunLevelStru[i].runLevelStru[j].levelSpeed = ShortFromChar(pTempData);                        
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
