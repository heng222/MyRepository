/********************************************************
* 
* �� �� ���� LoadEmergStopButton.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����EmergStopButton���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadEmergStopButton.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����EmergStopButton����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadEmergStopButtonData(void)
{
    BnfEmergStopButtonStruct* BnfEmergStopButtonStru = NULL;/*EmergStopButton��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_EMERG_STOP_BUTTON_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(EMERGSTOPBUTTON_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % EMERGSTOPBUTTON_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / EMERGSTOPBUTTON_LINE_BYTE_NUM);

                /*д��EMERGSTOPBUTTON��Ϣ�ṹ��ָ���ַ*/
                MallocEmergStopButtonDataStru(tempDataNum);
                BnfEmergStopButtonStru = GetEmergStopButtonData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfEmergStopButtonStru != NULL);i++)
                {
                    /*�������*/
                    BnfEmergStopButtonStru[i].emergStopButtonId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*����*/
                    MemoryCpy(BnfEmergStopButtonStru[i].name,EMERGSTOPBUTTON_NAME_BYTE_LEN,pTempData,EMERGSTOPBUTTON_NAME_BYTE_LEN);
                    pTempData += EMERGSTOPBUTTON_NAME_BYTE_LEN;
                    /*ͣ��������*/
                    BnfEmergStopButtonStru[i].stationId = ShortFromChar(pTempData);                        
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
