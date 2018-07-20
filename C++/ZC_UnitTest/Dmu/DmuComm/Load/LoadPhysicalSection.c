/********************************************************
* 
* �� �� ���� LoadPhysicalSection.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����PhysicalSection���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadPhysicalSection.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����PhysicalSection����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadPhysicalSectionData(void)
{
    BnfPhysicalSectionStruct* BnfPhysicalSectionStru = NULL;/*PhysicalSection��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*��������д��ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_PHYSICAL_SGMT_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(PHYSICALSECTION_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % PHYSICALSECTION_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / PHYSICALSECTION_LINE_BYTE_NUM);

                /*д��PHYSICALSECTION��Ϣ�ṹ��ָ���ַ*/
                MallocPhysicalSectionDataStru(tempDataNum);
                BnfPhysicalSectionStru = GetPhysicalSectionData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfPhysicalSectionStru != NULL);i++)
                {
                    /*�������*/
                    BnfPhysicalSectionStru[i].physicalStcId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*����*/
                    MemoryCpy(BnfPhysicalSectionStru[i].name,PHYSICALSECTION_NAME_BYTE_NUM,pTempData,PHYSICALSECTION_NAME_BYTE_NUM);
                    pTempData += PHYSICALSECTION_NAME_BYTE_NUM;

                    /*��������������Ŀ*/     
                    BnfPhysicalSectionStru[i].includeAxleScNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*������*/
                    for(j = 0u;j < PHYSICALSECTION_AXLEID_MAX_NUM;j++)
                    {
                        BnfPhysicalSectionStru[i].axleIdBuff[j] = ShortFromChar(pTempData);                        
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
