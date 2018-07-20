/********************************************************
* 
* �� �� ���� LoadLineSwitchInfo.c 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����LineSwitchInfo���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadLineSwitchInfo.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����LineSwitchInfo����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadLineSwitchInfoData(void)
{
    BnfLineSwitchInfoStruct* BnfLineSwitchInfoStru = NULL;/*LineSwitchInfo��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(DIVIDPOINT_TYPE,DIVIDPOINT_LINRSWITCH_INFO_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(LINESWITCHINFO_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % LINESWITCHINFO_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / LINESWITCHINFO_LINE_BYTE_NUM);

                /*д��LINESWITCHINFO��Ϣ�ṹ��ָ���ַ*/
                MallocLineSwitchInfoDataStru(tempDataNum);
                BnfLineSwitchInfoStru = GetLineSwitchInfoData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfLineSwitchInfoStru != NULL);i++)
                {
                    /*�������*/
                    BnfLineSwitchInfoStru[i].indexId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*�л���·�ƽ�ZCID*/
                    BnfLineSwitchInfoStru[i].lineSwitchTraZcId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*�л���·�ӹ�ZCID*/
                    BnfLineSwitchInfoStru[i].lineSwitchTakeOverZcId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*�л���·����*/
                    BnfLineSwitchInfoStru[i].lineSwitchDir = *pTempData;
                    pTempData += 1;
                    /*�л���·�������seg���*/
                    BnfLineSwitchInfoStru[i].startLineSwitchInfoId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*�л���·�������segƫ��*/
                    BnfLineSwitchInfoStru[i].startSegOffset = LongFromChar(pTempData);
                    pTempData += 4;
                    /*�л�������seg���*/
                    BnfLineSwitchInfoStru[i].switchPointSegId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*�л�������segƫ��*/
                    BnfLineSwitchInfoStru[i].switchPointOffset = LongFromChar(pTempData);
                    pTempData += 4;
                    /*�л���·�յ�����seg���*/
                    BnfLineSwitchInfoStru[i].endLineSwitchInfoId = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*�л���·�յ�����segƫ��*/
                    BnfLineSwitchInfoStru[i].segEndOffset = LongFromChar(pTempData);
                    pTempData += 4;
                    /*�л�����ؽ�·���*/  
                    BnfLineSwitchInfoStru[i].relationRouteNum = ShortFromChar(pTempData);
                    pTempData += 2;
                    /*�л���·�ڰ����ĵ�����Ŀ*/ 
                    BnfLineSwitchInfoStru[i].includeSwitchNum = ShortFromChar(pTempData);
                    pTempData += 2;
                    for(j = 0u;j < LINESWITCHINFO_SWITCH_NUM;j++)
                    {
                        /*������*/
                        BnfLineSwitchInfoStru[i].switchInfoStru[j].switchId = ShortFromChar(pTempData);
                        pTempData += 2;
                        /*����״̬*/
                        BnfLineSwitchInfoStru[i].switchInfoStru[j].switchStatus = ShortFromChar(pTempData);
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
