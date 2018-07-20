/********************************************************
* 
* �� �� ���� LoadSystemAccTable.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����SystemAccTable���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadSystemAccTable.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����SystemAccTable����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadSystemAccTableData(void)
{
    BnfSystemAccTableStruct* BnfSystemAccTableStru = NULL;/*SystemAccTable��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_ACCTABLE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(SYSTEMACCTABLE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % SYSTEMACCTABLE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SYSTEMACCTABLE_LINE_BYTE_NUM);

                /*д��SYSTEMACCTABLE��Ϣ�ṹ��ָ���ַ*/
                MallocSystemAccTableDataStru(tempDataNum);
                BnfSystemAccTableStru = GetSystemAccTableData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfSystemAccTableStru != NULL);i++)
                {
                    /*�г�����*/
                    BnfSystemAccTableStru[i].trainType = *pTempData;
                    pTempData += 1;

                    /*�ֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h*/
                    BnfSystemAccTableStru[i].lowerLimitSpeed = *pTempData;
                    pTempData += 1;

                    /*�ֶ��ٶ����ޡ����ݳ����ṩ��ǣ���������߷ֶεó�����λkm/h*/
                    BnfSystemAccTableStru[i].upperLimitSpeed = *pTempData;
                    pTempData += 1;

                    /*�ֶμ��ٶ�ֵ�����ݳ����ṩ��ǣ���������߷ֶεó�����λcm/s2*/
                    BnfSystemAccTableStru[i].accValue = *pTempData;
                    pTempData += 1;
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
