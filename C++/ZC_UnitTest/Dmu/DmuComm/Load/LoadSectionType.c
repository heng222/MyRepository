/********************************************************
* 
* �� �� ���� LoadSectionType.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����SectionType���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadSectionType.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����SectionType����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadSectionTypeData(void)
{
    BnfSectionTypeStruct* BnfSectionTypeStru = NULL;/*SectionType��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_SECTION_TYPE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(SECTIONTYPE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % SECTIONTYPE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SECTIONTYPE_LINE_BYTE_NUM);

                /*д��SECTIONTYPE��Ϣ�ṹ��ָ���ַ*/
                MallocSectionTypeDataStru(tempDataNum);
                BnfSectionTypeStru = GetSectionTypeData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfSectionTypeStru != NULL);i++)
                {
                    BnfSectionTypeStru[i].indexId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*��������*/
                    BnfSectionTypeStru[i].sectionType = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*����ID*/
                    BnfSectionTypeStru[i].sectionId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*��������*/
                    BnfSectionTypeStru[i].sectionProperty = *pTempData;                        
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
