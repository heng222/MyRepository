/*******************************************
 * �ļ���	��  LoadZcSystemConfig.h
 * ��Ȩ˵��	��  ������ģ�Ƽ����޹�˾
 * �汾��	��  1.0  
 * ����ʱ��	��  2015-5-25
 * ��������	��	����ZcSystemConfig����
 * ʹ��ע��	��  
 * �޸ļ�¼	��	
*******************************************/
#include "LoadZcSystemConfig.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"



/*
* ���������� ����ZcSystemConfig����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadZcSystemConfigData(void)
{
	INT8_S retVal = 0;/*��������ֵ*/
	UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
	UINT8_S indexId = 0U;/*�ṹ���±�*/
	UINT32_S tempDataLen = 0U;
	UINT16_S tempDataNum = 0U;/*���ݱ������*/
	UINT16_S i = 0U;/*ѭ��ʹ��*/
    BnfZcSystemConfigStruct* BnfZcSystemConfigStru = NULL;/*ZcSystemConfig��Ϣ�ṹ��ָ��*/

	/*��ȡ����*/
	retVal = GetConfigDataLen(((UINT8_S)(ZC_CONFIG_TYPE)),((UINT8_S)(ZC_SYSTEM_CONFIG_DATA_ID)),&tempDataLen,&indexId);

	if((0 == retVal)&&(((UINT16_S)tempDataLen) > 0U))
	{
		pTempData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(UINT32_S)(tempDataLen+50U));

        if (NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(((UINT16_S)(ZCSYSTEMCONFIG_LINE_BYTE_NUM)),tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0U == (UINT16_S)(tempDataLen % ZCSYSTEMCONFIG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / ZCSYSTEMCONFIG_LINE_BYTE_NUM);

                /*д��ZCSYSTEMCONFIG��Ϣ�ṹ��ָ���ַ*/
                MallocZcSystemConfigDataStru(tempDataNum);
                BnfZcSystemConfigStru = GetZcSystemConfigData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0U;(i < tempDataNum)&&(BnfZcSystemConfigStru != NULL);i++)
                {
                    /*�г�������о��루ms��*/
                    BnfZcSystemConfigStru[i].trainMaxRecedeDis = ShortFromChar(pTempData);						
                    pTempData += 2U;

                    /*��·��С���ܳ���(cm)*/
                    BnfZcSystemConfigStru[i].lineMinTrainLength = ShortFromChar(pTempData);						
                    pTempData += 2U;

                    /*��ӪҪ��ĵ�����γ���(cm)*/
                    BnfZcSystemConfigStru[i].sectionLength = LongFromChar(pTempData);						
                    pTempData += 4U;

                    /*ǰ��ɸѡ������������*/
                    BnfZcSystemConfigStru[i].axleSectionNum = ShortFromChar(pTempData);						
                    pTempData += 2U;

                    /*�������η�ͨ�ų�ռ�������ж�ʱ�䣨ms��*/
                    BnfZcSystemConfigStru[i].redunJudgmentTime = LongFromChar(pTempData);						
                    pTempData += 4U;

                    /*ZC-CI�߼�����ռ�ÿ�����λ��������*/
                    BnfZcSystemConfigStru[i].freeCodeNumSwitch = *pTempData;						
                    pTempData += 1U;

                    /*�г�CBTC�۷�ʱ�䣨ms��*/
                    BnfZcSystemConfigStru[i].trainCbtcBackTime = LongFromChar(pTempData);						
                    pTempData += 4U;

                    /*�ж��źŻ���ѹ����(cm)*/
                    BnfZcSystemConfigStru[i].signPressureDis = ShortFromChar(pTempData);						
                    pTempData += 2U;

                    /*׷�ٲ����󷽼����RM�г���ʽ*/
                    BnfZcSystemConfigStru[i].zcTrackRmTrainType = *pTempData;						
                    pTempData += 1U;
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
