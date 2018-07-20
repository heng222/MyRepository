/*******************************************
 * �ļ���	��  LoadZcTimeConfig.h
 * ��  ��	��  ZC��
 * ����ʱ��	��  2015-5-25
 * ��������	��	����ZcTimeConfig����
 * ��  ע	��  ��	
*******************************************/
#include "LoadZcTimeConfig.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"


/*******************************************
* ���������� ����ZcTimeConfig����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadZcTimeConfigData(void)
{
	INT8_S retVal = 0;/*��������ֵ*/
	UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
	UINT8_S indexId = 0U;/*�ṹ���±�*/
	UINT32_S tempDataLen = 0U;
	UINT16_S tempDataNum = 0U;/*���ݱ������*/
	UINT16_S i = 0U;/*ѭ��ʹ��*/
    BnfZcTimeConfigStruct* BnfZcTimeConfigStru = NULL;/*ZcTimeConfig��Ϣ�ṹ��ָ��*/

	/*��ȡ����*/
	retVal = GetConfigDataLen(((UINT8_S)(ZC_CONFIG_TYPE)),((UINT8_S)(ZC_TIME_CONFIG_DATA_ID)),&tempDataLen,&indexId);

	if((0 == retVal)&&(((UINT16_S)tempDataLen) > 0U))
	{
		pTempData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(UINT32_S)(tempDataLen+50U));

        if (NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(((UINT16_S)(ZCTIMECONFIG_LINE_BYTE_NUM)),tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0U == (UINT16_S)(tempDataLen % ZCTIMECONFIG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / ZCTIMECONFIG_LINE_BYTE_NUM);

                /*д��ZCTIMECONFIG��Ϣ�ṹ��ָ���ַ*/
                MallocZcTimeConfigDataStru(tempDataNum);
                BnfZcTimeConfigStru = GetZcTimeConfigData();

                /*������Ч��ʼд��ṹ��*/
                if (BnfZcTimeConfigStru != NULL)
                {
                    for(i = 0U;i < tempDataNum;i++)
                    {
                        /*NTPУʱ���ʱ��(ms)*/	
                        BnfZcTimeConfigStru[i].errorTime = LongFromChar(pTempData);						
                        pTempData += 4U;

                        /*��ϵͳ��ʱ�ӷ�����Уʱ��ʱ����ms��*/
                        BnfZcTimeConfigStru[i].duration = LongFromChar(pTempData);						
                        pTempData += 4U;
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
