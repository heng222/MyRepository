/********************************************************
* 
* �� �� ���� LoadBlocTrgZone.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����BlocTrgZone���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadBlocTrgZone.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����BlocTrgZone����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadBlocTrgZoneData(void)
{
    BnfBlocTrgZoneStruct* BnfBlocTrgZoneStru = NULL;/*BlocTrgZone��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_BLOC_TRG_ZONE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));

        /*��ȡ����*/
        retVal = GetConfigData(BLOCTRGZONE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

        if(NULL != pTempData)
        {
            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % BLOCTRGZONE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / BLOCTRGZONE_LINE_BYTE_NUM);

                /*д��BLOCTRGZONE��Ϣ�ṹ��ָ���ַ*/
                MallocBlocTrgZoneDataStru(tempDataNum);
                BnfBlocTrgZoneStru = GetBlocTrgZoneData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfBlocTrgZoneStru != NULL);i++)
                {
                    BnfBlocTrgZoneStru[i].blocApptchSectionId = ShortFromChar(pTempData);                        /*�������*/
                    pTempData += 2;

                    BnfBlocTrgZoneStru[i].includeAxleSgmtNum = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    for (j = 0u;j < BLOCTRGZONE_AXLESGM_MAX_NUM; j++)
                    {
                        BnfBlocTrgZoneStru[i].includeAxleSgmtId[j] = ShortFromChar(pTempData);                    
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
