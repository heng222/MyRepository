/********************************************************
* 
* �� �� ���� LoadPoint.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����Point���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadPoint.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����Point����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadPointData(void)
{
    BnfPointStruct* BnfPointStru = NULL;/*Point��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_POINT_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(POINT_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % POINT_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / POINT_LINE_BYTE_NUM);

                /*д��POINT��Ϣ�ṹ��ָ���ַ*/
                MallocPointDataStru(tempDataNum);
                BnfPointStru = GetPointData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfPointStru != NULL);i++)
                {
                    /*�������*/
                    BnfPointStru[i].indexId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*����*/
                    MemoryCpy(BnfPointStru[i].name,POINT_MAX_NAME_LEN,pTempData,POINT_MAX_NAME_LEN);
                    pTempData += POINT_MAX_NAME_LEN;
                    /*���������*/
                    MemoryCpy(BnfPointStru[i].startPathwayName,POINT_MAX_NAME_LEN,pTempData,POINT_MAX_NAME_LEN);
                    pTempData += POINT_MAX_NAME_LEN;
                    /*�����(cm)*/
                    BnfPointStru[i].location = LongFromChar(pTempData);                
                    pTempData += 4;
                    /*������*/  
                    BnfPointStru[i].pointType = ShortFromChar(pTempData);            
                    pTempData += 2;

                    /*����������ڵ�ID*/
                    BnfPointStru[i].startJointMainLkId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*���������ڵ�ID*/
                    BnfPointStru[i].startJointSideLkId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*�յ��������ڵ�ID*/
                    BnfPointStru[i].tmnlJointMainLkId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*�յ�������ڵ�ID*/
                    BnfPointStru[i].tmnlJointSideLkId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*����ZC������*/
                    BnfPointStru[i].manageZCId = ShortFromChar(pTempData);                
                    pTempData += 2;
                    /*����ATS������*/
                    BnfPointStru[i].manageATSId = ShortFromChar(pTempData);                
                    pTempData += 2;
                    /*��������CI������*/ 
                    BnfPointStru[i].manageCIId = ShortFromChar(pTempData);        
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
