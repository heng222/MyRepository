/********************************************************
* 
* �� �� ���� LoadSign.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����Sign���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadSign.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����Sign����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadSignData(void)
{
    BnfSignStruct* BnfSignStru = NULL;/*Sign��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_SIGNAL_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(SIGN_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % SIGN_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SIGN_LINE_BYTE_NUM);

                /*д��SIGN��Ϣ�ṹ��ָ���ַ*/
                MallocSignDataStru(tempDataNum);
                BnfSignStru = GetSignData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfSignStru != NULL);i++)
                {
                    /*�������*/
                    BnfSignStru[i].signId = ShortFromChar(pTempData);                        
                    pTempData += 2;
        
                    /*�źŻ�����*/
                    MemoryCpy(BnfSignStru[i].signName,SIGN_NAME_LEN,pTempData,SIGN_NAME_LEN);
                    pTempData += SIGN_NAME_LEN;

                    /*����*/
                    BnfSignStru[i].signType = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*����*/
                    BnfSignStru[i].signProperty = ShortFromChar(pTempData);                        
                    pTempData += 2;

                    /*����seg���*/     
                    BnfSignStru[i].signProtectSegId = ShortFromChar(pTempData);          
                    pTempData += 2;  
                    
                    /*����Segƫ������cm��*/
                    BnfSignStru[i].signProtectSegOffset = LongFromChar(pTempData); 
                    pTempData += 4;
                    /*��������*/
                    BnfSignStru[i].protectiveDir =  *pTempData;          
                    pTempData += 1;  
                    /*������Ϣ*/
                    BnfSignStru[i].lightInfo = LongFromChar(pTempData); 
                    pTempData += 4;
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
