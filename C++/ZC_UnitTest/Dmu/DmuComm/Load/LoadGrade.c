/********************************************************
* 
* �� �� ���� LoadGrade.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����Grade���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadGrade.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����Grade����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadGradeData(void)
{
    BnfGradeStruct* BnfGradeStru = NULL;/*Grade��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_GRADE_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));

        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(GRADE_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % GRADE_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / GRADE_LINE_BYTE_NUM);

                /*д��GRADE��Ϣ�ṹ��ָ���ַ*/
                MallocGradeDataStru(tempDataNum);
                BnfGradeStru = GetGradeData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfGradeStru != NULL);i++)
                {
                    /*�������*/
                    BnfGradeStru[i].gradeId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�¶��������Seg���*/
                    BnfGradeStru[i].orgnSegId = ShortFromChar(pTempData);    
                    pTempData += 2;    

                    /*�¶��������Segƫ����*/
                    BnfGradeStru[i].orgnSegOfst = LongFromChar(pTempData);    
                    pTempData += 4;

                    /*�¶��յ�����Seg���*/
                    BnfGradeStru[i].tmnlSegId = ShortFromChar(pTempData);    
                    pTempData += 2;
                    
                    /*�¶��յ�����Segƫ����*/
                    BnfGradeStru[i].tmnlSegOfst = LongFromChar(pTempData);    
                    pTempData += 4;

                    BnfGradeStru[i].orgnRelatePointId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*��������¶ȱ��*/
                    BnfGradeStru[i].orgnJointMainGradeId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�������¶ȱ��*/
                    BnfGradeStru[i].orgnJointSideGradeId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    BnfGradeStru[i].tmnlRelatePointId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�յ������¶ȱ��*/
                    BnfGradeStru[i].tmnlJointMainGradeId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�յ�����¶ȱ��*/    
                    BnfGradeStru[i].tmnlJointSideGradeId = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�¶�ֵ*/
                    BnfGradeStru[i].gradValue = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�¶��������·�߼��������б����*/
                    BnfGradeStru[i].inclineDir = ShortFromChar(pTempData);    
                    pTempData += 2;

                    /*�����߰뾶*/
                    BnfGradeStru[i].radius = LongFromChar(pTempData);    
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
