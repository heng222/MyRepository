/********************************************************
* 
* �� �� ���� LoadRoute.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����Route���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadRoute.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����Route����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadRouteData(void)
{
    BnfRouteStruct* BnfRouteStru = NULL;/*Route��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_ROUTE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(ROUTE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % ROUTE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / ROUTE_LINE_BYTE_NUM);

                /*д��ROUTE��Ϣ�ṹ��ָ���ַ*/
                MallocRouteDataStru(tempDataNum);
                BnfRouteStru = GetRouteData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfRouteStru != NULL);i++)
                {
                    /*�������*/
                    BnfRouteStru[i].routeId = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*��·����*/
                    MemoryCpy(BnfRouteStru[i].routeName,ROUTE_NAME_BYTE_LEN,pTempData,ROUTE_NAME_BYTE_LEN);
                    pTempData += ROUTE_NAME_BYTE_LEN;
                    /*��·����*/
                    BnfRouteStru[i].routeType = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*��ʼ�źŻ����*/
                    BnfRouteStru[i].startSignalId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*��ֹ�źŻ����*/
                    BnfRouteStru[i].endSignalId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*��������������Ŀ*/
                    BnfRouteStru[i].includeAxleSecNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*�������α��*/
                    for(j = 0u;j < ROUTE_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].AxleSec[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;  
                    }
                    /*����������Ŀ*/
                    BnfRouteStru[i].protectSecNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*�������α��*/
                    for(j = 0u;j < ROUTE_PROTECT_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].protectSecId[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;  
                    }

                    /*��ʽ�ӽ�������Ŀ*/    
                    BnfRouteStru[i].blogAccessSegNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*��ʽ�ӽ����α��*/
                    for(j = 0u;j < ROTRE_ACCESS_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].blogAccessSegId[j] = ShortFromChar(pTempData);                        
                        pTempData += 2; 
                    }
                    /*CBTC�ӽ�������Ŀ*/
                    BnfRouteStru[i].cbtcAccessSegNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*CBTC�ӽ����α��*/
                    for(j = 0u;j < ROTRE_ACCESS_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].cbtcAccessSegId[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;  
                    }

                    /*��ʽ������������*/
                    BnfRouteStru[i].blocTrgAreaNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*��ʽ��������ID*/
                    for(j = 0u;j < ROUTE_TRG_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].blocTrgAreaId[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;   
                    }

                    /*CBTC������������*/
                    BnfRouteStru[i].cbtcTrgAreaNum = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*CBTC��������ID*/
                    for(j = 0u;j < ROUTE_TRG_SEC_MAX_NUM;j++)
                    {
                        BnfRouteStru[i].cbtcTrgAreaId[j] = ShortFromChar(pTempData);                        
                        pTempData += 2;  
                    }
                    /*����CI������*/
                    BnfRouteStru[i].manageCI = ShortFromChar(pTempData);                        
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
