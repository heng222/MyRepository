/********************************************************
* 
* �� �� ���� LoadStaticResSpeed.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����StaticResSpeed���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadStaticResSpeed.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����StaticResSpeed����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadStaticResSpeedData(void)
{
    BnfStaticResSpeedStruct* BnfStaticResSpeedStru = NULL;/*StaticResSpeed��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_STATIC_RES_SPEED_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(STATICRESSPEED_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % STATICRESSPEED_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / STATICRESSPEED_LINE_BYTE_NUM);

                /*д��STATICRESSPEED��Ϣ�ṹ��ָ���ַ*/
                MallocStaticResSpeedDataStru(tempDataNum);
                BnfStaticResSpeedStru = GetStaticResSpeedData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfStaticResSpeedStru != NULL);i++)
                {
                    /*�������*/
                    BnfStaticResSpeedStru[i].staticResSpeedId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*��������������Seg���*/
                    BnfStaticResSpeedStru[i].segId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*�������Segƫ����(cm)*/
                    BnfStaticResSpeedStru[i].orgnSegOfst = LongFromChar(pTempData);                        
                    pTempData += 4;
                    /*�յ�����Segƫ����(cm)*/
                    BnfStaticResSpeedStru[i].tmnlSegOfst = LongFromChar(pTempData);                        
                    pTempData += 4;

                    /*��������ID*/
                    BnfStaticResSpeedStru[i].relateSwitchId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*��̬����ֵ*/
                    BnfStaticResSpeedStru[i].staticSpeed = ShortFromChar(pTempData);                        
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
