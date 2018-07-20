/********************************************************
* 
* �� �� ���� LoadSystemDevComm.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����SystemDevComm���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadSystemDevComm.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����SystemDevComm����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadSystemDevCommData(void)
{
    BnfSystemDevCommStruct* BnfSystemDevCommStru = NULL;/*SystemDevComm��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S  j = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_DEV_COMM_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(SYSTEMDEVCOMM_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % SYSTEMDEVCOMM_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SYSTEMDEVCOMM_LINE_BYTE_NUM);

                /*д��SYSTEMDEVCOMM��Ϣ�ṹ��ָ���ַ*/
                MallocSystemDevCommDataStru(tempDataNum);
                BnfSystemDevCommStru = GetSystemDevCommData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfSystemDevCommStru != NULL);i++)
                {
                    
                    /*���豸���(Device_Type+Device_ID)*/    
                    BnfSystemDevCommStru[i].devName = ShortFromChar(pTempData);
                    pTempData += 2;    

                    /*ͨ�Ŷ�������*/
                    BnfSystemDevCommStru[i].commObjectNum = ShortFromChar(pTempData);
                    pTempData += 2;    

                    /*ͨ�Ŷ�����(Device_Type+Device_ID)*/
                    for (j = 0u; j < SYSTEMDEVCOMM_COMMOBJECT_MAX_NUM; j++)
                    {
                        BnfSystemDevCommStru[i].commObjectIdBuff[j] = ShortFromChar(pTempData);
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
