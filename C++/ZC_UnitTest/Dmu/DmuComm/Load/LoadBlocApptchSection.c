/********************************************************
* 
* �� �� ���� LoadBlocApptchSection.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����BlocApptchSection���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadBlocApptchSection.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����BlocApptchSection����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadBlocApptchSectionData(void)
{
    BnfBlocApptchSectionStruct* BnfBlocApptchSectionStru = NULL;/*BlocApptchSection��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_BLOC_APPTCH_SECTION_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(BLOCAPPTCHSECTION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % BLOCAPPTCHSECTION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / BLOCAPPTCHSECTION_LINE_BYTE_NUM);

                /*д��BLOCAPPTCHSECTION��Ϣ�ṹ��ָ���ַ*/
                MallocBlocApptchSectionDataStru(tempDataNum);
                BnfBlocApptchSectionStru = GetBlocApptchSectionData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfBlocApptchSectionStru != NULL);i++)
                {
                    BnfBlocApptchSectionStru[i].blocApptchSectionId = ShortFromChar(pTempData);                        /*�������*/
                    pTempData += 2;

                    BnfBlocApptchSectionStru[i].includeAxleSgmtNum = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    for (j = 0u;j < BLOCAPPTCHSECTION_AXLESGM_MAX_NUM; j++)
                    {
                        BnfBlocApptchSectionStru[i].includeAxleSgmtId[j] = ShortFromChar(pTempData);                    
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
