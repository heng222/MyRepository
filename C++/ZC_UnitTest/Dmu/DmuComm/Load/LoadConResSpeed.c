/********************************************************
* 
* �� �� ���� LoadConResSpeed.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����ConResSpeed���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadConResSpeed.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����ConResSpeed����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadConResSpeedData(void)
{
    BnfConResSpeedStruct* BnfConResSpeedStru = NULL;/*ConResSpeed��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_CONRESSPEED_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(CONRESSPEED_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % CONRESSPEED_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / CONRESSPEED_LINE_BYTE_NUM);

                /*д��BLOCTRGZONE��Ϣ�ṹ��ָ���ַ*/
                MallocConResSpeedDataStru(tempDataNum);
                BnfConResSpeedStru = GetConResSpeedData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfConResSpeedStru != NULL);i++)
                {
                    /*�������*/
                    BnfConResSpeedStru[i].index = *pTempData;                        
                    pTempData += 1;

                    BnfConResSpeedStru[i].resSpeed = ShortFromChar(pTempData);                    
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
