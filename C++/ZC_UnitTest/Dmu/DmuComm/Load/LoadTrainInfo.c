/********************************************************
* 
* �� �� ���� LoadTrainInfo.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����TrainInfo���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadTrainInfo.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����TrainInfo����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadTrainInfoData(void)
{
    BnfTrainInfoStruct* BnfTrainInfoStru = NULL;/*TrainInfo��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_TRAININFO_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(TRAININFO_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % TRAININFO_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / TRAININFO_LINE_BYTE_NUM);

                /*д��TRAININFO��Ϣ�ṹ��ָ���ַ*/
                MallocTrainInfoDataStru(tempDataNum);
                BnfTrainInfoStru = GetTrainInfoData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfTrainInfoStru != NULL);i++)
                {
                    /*�г�����*/
                    BnfTrainInfoStru[i].trainType = *pTempData;    
                    pTempData += 1;

                    /*�г�����*/
                    BnfTrainInfoStru[i].trainLength = ShortFromChar(pTempData);    
                    pTempData += 2;    

                    /*�г����ǣ�����ٶ�*/
                    BnfTrainInfoStru[i].trainMaxTracAcc = *pTempData;    
                    pTempData += 1;    

                    /*��·��������¶ȣ���·�нǵ�����ֵ)*/
                    BnfTrainInfoStru[i].lineMaxGrade = ShortFromChar(pTempData);    
                    pTempData += 2;    

                    /*�г���ת����ϵ��*/
                    BnfTrainInfoStru[i].trainRotateRate = *pTempData;
                    pTempData += 1;

                    /*�������½����ƶ����ٶ�*/
                    BnfTrainInfoStru[i].trainWorstEbAcc = *pTempData;
                    pTempData += 1;

                    /*�����ƶ�������Чʱ�䡣������ʱ��,��λ:ms*/
                    BnfTrainInfoStru[i].timeEbBrakeBuild = ShortFromChar(pTempData);
                    pTempData += 2;

                     /*ǣ���г���ʱ��ʩ�ӽ����ƶ�ʱ���ǵ�ǣ���г���ʱ,��λ:ms*/
                    BnfTrainInfoStru[i].timeTracCut = ShortFromChar(pTempData);
                    pTempData += 2;

                    /*��·�ٶ�����*/
                    BnfTrainInfoStru[i].maxLineLimitSpeed = *pTempData;
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
