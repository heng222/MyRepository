/********************************************************
* 
* �� �� ���� LoadPlatForm.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����PlatForm���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadPlatForm.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����PlatForm����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadPlatFormData(void)
{
    BnfPlatFormStruct* BnfPlatFormStru = NULL;/*PlatForm��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_PLATFORM_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(PLATFORM_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % PLATFORM_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / PLATFORM_LINE_BYTE_NUM);

                /*д��PLATFORM��Ϣ�ṹ��ָ���ַ*/
                MallocPlatFormDataStru(tempDataNum);
                BnfPlatFormStru = GetPlatFormData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfPlatFormStru != NULL);i++)
                {
                    /*վ̨ID*/
                    BnfPlatFormStru[i].platFormId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*վ̨���Ĺ����*/
                    MemoryCpy(BnfPlatFormStru[i].platFormKillPost,PLATFORM_NAME_BYTE_LEN,pTempData,PLATFORM_NAME_BYTE_LEN);
                    pTempData += PLATFORM_NAME_BYTE_LEN;

                    /*վ̨����seg���*/
                    BnfPlatFormStru[i].segId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�߼�������վ̨�����ͣ������ķ���*/
                    BnfPlatFormStru[i].dir = *pTempData;    
                    pTempData++;
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
