/********************************************************
* 
* �� �� ���� LoadSeg.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����Seg���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadSeg.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����Seg����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadSegData(void)
{
    BnfSegStruct* BnfSegStru = NULL;/*Seg��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(LINE_DATA_TYPE,LINE_SEG_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(SEG_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % SEG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SEG_LINE_BYTE_NUM);

                /*д��SEG��Ϣ�ṹ��ָ���ַ*/
                MallocSegDataStru(tempDataNum);
                BnfSegStru = GetSegData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfSegStru != NULL);i++)
                {
                    /*�������*/
                    BnfSegStru[i].segId = ShortFromChar(pTempData);                        
                    pTempData += 2;
                    /*���ȣ�cm)*/
                    BnfSegStru[i].length = LongFromChar(pTempData);            
                    pTempData += 4;
                    /*���˵�����*/
                    BnfSegStru[i].startPointType = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*���˵���*/
                    BnfSegStru[i].startPointId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*�յ�˵�����*/
                    BnfSegStru[i].endPointType = ShortFromChar(pTempData);          
                    pTempData += 2;
                    /*�յ�˵���*/
                    BnfSegStru[i].endPointId = ShortFromChar(pTempData);        
                    pTempData += 2;

                    /*�����������SegID*/
                    BnfSegStru[i].segStartJointMainSegId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*���������ڵ�SegID*/
                    BnfSegStru[i].segStartJointSideSegId = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*�յ��������ڵ�SegID*/
                    BnfSegStru[i].segTmnlJointMainSegId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*�յ�������ڵ�SegID*/
                    BnfSegStru[i].segTmnlJointSideSegId = ShortFromChar(pTempData);    
                    pTempData += 2;
                    /*����ZC����ID*/
                    BnfSegStru[i].segManageZCId = ShortFromChar(pTempData);                
                    pTempData += 2;
                    /*����ATS����ID*/
                    BnfSegStru[i].segManageATSId = ShortFromChar(pTempData);        
                    pTempData += 2;
                    /*��������CI����ID*/ 
                    BnfSegStru[i].segManageCIId = ShortFromChar(pTempData);        
                    pTempData += 2;

                    /*������Ϣ����*/
                    BnfSegStru[i].segResSpeed = *pTempData;        
                    pTempData += 1;
                    /*�¶���Ϣ����*/ 
                    BnfSegStru[i].grade = *pTempData;        
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
