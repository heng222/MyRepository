/********************************************************
* 
* �� �� ���� LoadSwitch.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ����������  ����Switch���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadSwitch.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����Switch����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadSwitchData(void)
{
    BnfSwitchStruct* BnfSwitchStru = NULL;/*Switch��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_SWITCH_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(SWITCH_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % SWITCH_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SWITCH_LINE_BYTE_NUM);

                /*д��SWITCH��Ϣ�ṹ��ָ���ַ*/
                MallocSwitchDataStru(tempDataNum);
                BnfSwitchStru = GetSwitchData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfSwitchStru != NULL);i++)
                {
                    /*�������*/
                    BnfSwitchStru[i].switchId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*��������*/
                    MemoryCpy(BnfSwitchStru[i].switchName,SWITCH_NAME_LEN,pTempData,SWITCH_NAME_LEN);
                    pTempData += SWITCH_NAME_LEN;

                    /*����������*/     
                    BnfSwitchStru[i].switchOtherId = ShortFromChar(pTempData);          
                    pTempData += 2;  
                    /*����*/
                    BnfSwitchStru[i].dir = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*��λSegID*/
                    BnfSwitchStru[i].locSegId = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*��λSegID*/
                    BnfSwitchStru[i].antiSegId = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*���SegID*/
                    BnfSwitchStru[i].joinSegId = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*�������̬����*/
                    BnfSwitchStru[i].switchSideResSpeed = ShortFromChar(pTempData);           /*�������̬����*/
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
