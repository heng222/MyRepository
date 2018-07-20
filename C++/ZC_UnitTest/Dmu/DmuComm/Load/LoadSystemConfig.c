/********************************************************
* 
* �� �� ���� LoadSystemConfig.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����SystemConfig���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadSystemConfig.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����SystemConfig����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadSystemConfigData(void)
{
    BnfSystemConfigStruct* BnfSystemConfigStru = NULL;/*SystemConfig��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_CONFIGDATA_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(SYSTEMCONFIG_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % SYSTEMCONFIG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SYSTEMCONFIG_LINE_BYTE_NUM);

                /*д��SYSTEMCONFIG��Ϣ�ṹ��ָ���ַ*/
                MallocSystemConfigDataStru(tempDataNum);
                BnfSystemConfigStru = GetSystemConfigData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfSystemConfigStru != NULL);i++)
                {
                    /*ϵͳ��������ٶ�*/
                    BnfSystemConfigStru[i].maxLineLimitSpeed = *pTempData;    
                    pTempData += 1;

                    /*��ʱ�����������*/
                    BnfSystemConfigStru[i].maxTsrSpeed = *pTempData;    
                    pTempData += 1;

                    /*NTPУʱʱ����*/
                    BnfSystemConfigStru[i].mimeZoneDifference = *pTempData;    
                    pTempData += 1;

                    /*��ȫ��������*/
                    BnfSystemConfigStru[i].safeBackDistance = ShortFromChar(pTempData);    
                    pTempData += 2;    

                    /*ϵͳ������󱣻����γ���*/
                    BnfSystemConfigStru[i].maxOverlapLength = ShortFromChar(pTempData);    
                    pTempData += 2;    

                    /*seg�߼�����������*/
                    BnfSystemConfigStru[i].segLogicDirUpAndDown = *pTempData;    
                    pTempData += 1;    

                    /*RM����ֵ*/
                    BnfSystemConfigStru[i].rmLimitSpeed = ShortFromChar(pTempData);    
                    pTempData += 2;    
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
