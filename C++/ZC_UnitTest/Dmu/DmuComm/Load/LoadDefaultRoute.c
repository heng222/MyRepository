/********************************************************
* 
* �� �� ���� LoadDefaultRoute.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����DefaultRoute���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadDefaultRoute.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����DefaultRoute����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadDefaultRouteData(void)
{
    BnfDefaultRouteStruct* BnfDefaultRouteStru = NULL;/*DefaultRoute��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(RUN_DATA_TYPE,RUN_DEFAULT_ROUTE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(DEFAULTROUTE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % DEFAULTROUTE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / DEFAULTROUTE_LINE_BYTE_NUM);

                /*д��DEFAULTROUTE��Ϣ�ṹ��ָ���ַ*/
                MallocDefaultRouteDataStru(tempDataNum);
                BnfDefaultRouteStru = GetDefaultRouteData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfDefaultRouteStru != NULL);i++)
                {
                    BnfDefaultRouteStru[i].indexId = ShortFromChar(pTempData);                        /*�������*/
                    pTempData += 2;

                    BnfDefaultRouteStru[i].segId = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    BnfDefaultRouteStru[i].dir = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    BnfDefaultRouteStru[i].arriveStaId = ShortFromChar(pTempData);                    
                    pTempData += 2;

                    BnfDefaultRouteStru[i].aimStaId = ShortFromChar(pTempData);                    
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
