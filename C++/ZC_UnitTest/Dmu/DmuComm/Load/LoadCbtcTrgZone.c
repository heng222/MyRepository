/********************************************************
* 
* �� �� ���� LoadCbtcTrgZone.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����CbtcTrgZone���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadCbtcTrgZone.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����CbtcTrgZone����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadCbtcTrgZoneData(void)
{
    BnfCbtcTrgZoneStruct* BnfCbtcTrgZoneStru = NULL;/*CbtcTrgZone��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_CBTC_TRG_ZONE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));

        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(CBTCTRGZONE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % CBTCTRGZONE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / CBTCTRGZONE_LINE_BYTE_NUM);

                /*д��CBTCTRGZONE��Ϣ�ṹ��ָ���ַ*/
                MallocCbtcTrgZoneDataStru(tempDataNum);
                BnfCbtcTrgZoneStru = GetCbtcTrgZoneData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfCbtcTrgZoneStru != NULL);i++)
                {
                    BnfCbtcTrgZoneStru[i].cbtcApptchSectionId = ShortFromChar(pTempData);                        /*�������*/
                    pTempData += 2;

                    BnfCbtcTrgZoneStru[i].includeLgcZoneNum = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    for (j = 0u;j < CBTCTRGZONE_LGCZONE_MAX_NUM; j++)
                    {
                        BnfCbtcTrgZoneStru[i].includeLgcZoneId[j] = ShortFromChar(pTempData);                    
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
