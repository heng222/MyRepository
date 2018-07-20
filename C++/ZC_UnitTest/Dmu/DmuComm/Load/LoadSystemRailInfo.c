/********************************************************
* 
* �� �� ���� LoadSystemRailInfo.c  
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ����SystemRailInfo���� 
* ��    ע�� �� 
* 
********************************************************/ 

#include "LoadSystemRailInfo.h"
#include "../../Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����SystemRailInfo����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadSystemRailInfoData(void)
{
    BnfSystemRailInfoStruct* BnfSystemRailInfoStru = NULL;/*SystemRailInfo��Ϣ�ṹ��ָ��*/
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
    UINT8_S indexId = 0u;/*�ṹ���±�*/
    UINT32_S tempDataLen = 0u;
    UINT16_S tempDataNum = 0u;/*���ݱ������*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    /*��ȡ����*/
    retVal = GetConfigDataLen(SYSTEM_CONFIGDATA_TYPE,SYSTEM_RAILINFO_ID,&tempDataLen,&indexId);

    if((0 == retVal)&&(tempDataLen > 0u))
    {
        pTempData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S)*(tempDataLen+50u));
        if(NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(SYSTEMRAILINFO_LINE_BYTE_NUM,tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0u == (tempDataLen % SYSTEMRAILINFO_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / SYSTEMRAILINFO_LINE_BYTE_NUM);

                /*д��SYSTEMRAILINFO��Ϣ�ṹ��ָ���ַ*/
                MallocSystemRailInfoDataStru(tempDataNum);
                BnfSystemRailInfoStru = GetSystemRailInfoData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0u;(i < tempDataNum)&&(BnfSystemRailInfoStru != NULL);i++)
                {
                    /*��ͷǰ������¶ȼ��㷶Χ*/
                    BnfSystemRailInfoStru[i].disFrontToGetGrade = LongFromChar(pTempData);
                    pTempData += 4;
                    /*��������¶ȼ��㷶Χ*/
                    BnfSystemRailInfoStru[i].disBetweenToGetGrade = ShortFromChar(pTempData);
                    pTempData += 2;    
                    /*�Ƽ��ٶ���EBI����С��ֵ(km/h)*/
                    BnfSystemRailInfoStru[i].minMarginFromEBI = *pTempData;
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
