/********************************************************
* 
* �� �� ���� LoadConGrade.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����ConGrade���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadConGrade.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����ConGrade����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadConGradeData(void)
{
    BnfConGradeDataStruct* BnfConGradeStru = NULL;/*ConGrade��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ�������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_CONGRADE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(CONGRADE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % CONGRADE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / CONGRADE_LINE_BYTE_NUM);

                /*д��BLOCTRGZONE��Ϣ�ṹ��ָ���ַ*/
                MallocConGradeDataStru(tempDataNum);
                BnfConGradeStru = GetConGradeData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfConGradeStru != NULL);i++)
                {
                    /*�������*/
                    BnfConGradeStru[i].index = *pTempData;
                    pTempData += 1;

                    BnfConGradeStru[i].grade = ShortFromChar(pTempData);                    
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