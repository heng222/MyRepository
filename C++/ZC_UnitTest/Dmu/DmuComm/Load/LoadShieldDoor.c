/********************************************************
* 
* �� �� ���� LoadShieldDoor.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����ShieldDoor���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadShieldDoor.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����ShieldDoor����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadShieldDoorData(void)
{
    BnfShieldDoorStruct* BnfShieldDoorStru = NULL;/*ShieldDoor��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_SHIELD_DOOR_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(SHIELDDOOR_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % SHIELDDOOR_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SHIELDDOOR_LINE_BYTE_NUM);

                /*д��SHIELDDOOR��Ϣ�ṹ��ָ���ַ*/
                MallocShieldDoorDataStru(tempDataNum);
                BnfShieldDoorStru = GetShieldDoorData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfShieldDoorStru != NULL);i++)
                {
                    /*�������*/
                    BnfShieldDoorStru[i].shieldDoorId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*����*/
                    MemoryCpy(BnfShieldDoorStru[i].name,SHIELDDOOR_NAME_BYTE_LEN,pTempData,SHIELDDOOR_NAME_BYTE_LEN);
                    pTempData += SHIELDDOOR_NAME_BYTE_LEN;
                    /*ͣ��������*/
                    BnfShieldDoorStru[i].stationId = ShortFromChar(pTempData);                        
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
