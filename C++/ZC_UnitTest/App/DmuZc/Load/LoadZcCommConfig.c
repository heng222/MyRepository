/*******************************************
 * �ļ���	��  LoadZcCommConfig.h
 * ��  ��	��  ZC��
 * ����ʱ��	��  2015-5-25
 * ��������	��	����ZcCommConfig����
 * ��  ע	��  ��
*******************************************/
#include "LoadZcCommConfig.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"

/*******************************************
* ������	��
* ���������� ����ZcCommConfig����
* ����˵���� void
* ����ֵ  �� 0:�ɹ�
			-2 ���ݳ��ȴ���
*			-1 ����ָ��Ϊ��
			1�ӿڷ�������
			2������������ͺͱ���Ŵ���
*
*
*/
INT8_S LoadZcCommConfigData(void)
{
	INT8_S retVal = 0;/*��������ֵ*/
	UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
	UINT8_S indexId = 0U;/*�ṹ���±�*/
	UINT32_S tempDataLen = 0U;
	UINT16_S tempDataNum = 0U;/*���ݱ������*/
	UINT16_S i = 0U;/*ѭ��ʹ��*/
    BnfZcCommConfigStruct* BnfZcCommConfigStru = NULL;/*ZcCommConfig��Ϣ�ṹ��ָ��*/

	/*��ȡ����*/
	retVal = GetConfigDataLen(((UINT8_S)(ZC_CONFIG_TYPE)),((UINT8_S)(ZC_COMM_CONFIG_DATA_ID)),&tempDataLen,&indexId);

	if((0 == retVal)&&(((UINT16_S)tempDataLen) > 0U))
	{
		pTempData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(UINT32_S)(tempDataLen+50U));

        if (NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(((UINT16_S)(ZCCOMMCONFIG_LINE_BYTE_NUM)),tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0U == (UINT16_S)(tempDataLen % ZCCOMMCONFIG_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / ZCCOMMCONFIG_LINE_BYTE_NUM);

                /*д��ZCCOMMCONFIG��Ϣ�ṹ��ָ���ַ*/
                MallocZcCommConfigDataStru(tempDataNum);
                BnfZcCommConfigStru = GetZcCommConfigData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0U;(i < tempDataNum)&&(BnfZcCommConfigStru != NULL);i++)
                {
                    /*ZC��ATS������������ʱ��(ms)*/
                    BnfZcCommConfigStru[i].zcSendAtsDataCycle = LongFromChar(pTempData);						
                    pTempData += 4U;
                }
            }
            else
            {
                /*���ݳ��ȴ���*/
                retVal = -2;
            }
        } 
        else
        {
            retVal = -1;
        }	
	}
    else
    {
        retVal = 2;
    }

	return retVal;
}
