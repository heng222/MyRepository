/*******************************************
 * �ļ���	��  LoadZcSignInfo.h
 * ��  ��	��  ZC��
 * ����ʱ��	��  2015-5-25
 * ��������	��	����ZcSignInfo����
 * ��  ע	��  ��
*******************************************/
#include "LoadZcSignInfo.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Malloc.h"


/*******************************************
* ���������� ����ZcSignInfo����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadZcSignInfoData(void)
{
	INT8_S retVal = 0;/*��������ֵ*/
	UINT8_S* pTempData = NULL;/*��ʱ�洢����*/
	UINT8_S indexId = 0U;/*�ṹ���±�*/
	UINT32_S tempDataLen = 0U;
	UINT16_S tempDataNum = 0U;/*���ݱ������*/
	UINT16_S i = 0U;/*ѭ��ʹ��*/
    BnfZcSignInfoStruct* BnfZcSignInfoStru = NULL;/*ZcSignInfo��Ϣ�ṹ��ָ��*/

	/*��ȡ����*/
	retVal = GetConfigDataLen(((UINT8_S)(ZC_DATA_TYPE)),((UINT8_S)(ZC_SIGN_INFO_ID)),&tempDataLen,&indexId);

	if((0 == retVal) && (((UINT16_S)tempDataLen) > 0U))
	{
		pTempData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(UINT32_S)(tempDataLen+50U));

        if (NULL != pTempData)
        {
            /*��ȡ����*/
            retVal = GetConfigData(((UINT16_S)(ZCSIGNINFO_LINE_BYTE_NUM)),tempDataLen,indexId,pTempData);

            /*��������*/
            /*�ж����ݳ����Ƿ�Ϊ������*/
            if((0 == retVal)&&(0U == (UINT16_S)(tempDataLen % ZCSIGNINFO_LINE_BYTE_NUM)))
            {
                tempDataNum = (UINT16_S)(tempDataLen / ZCSIGNINFO_LINE_BYTE_NUM);

                /*д��ZCSIGNINFO��Ϣ�ṹ��ָ���ַ*/
                MallocZcSignInfoDataStru(tempDataNum);
                BnfZcSignInfoStru = GetZcSignInfoData();

                /*������Ч��ʼд��ṹ��*/
                for(i = 0U;(i < tempDataNum)&&(BnfZcSignInfoStru != NULL);i++)
                {
                    /*�źŻ�ID*/
                    BnfZcSignInfoStru[i].signId = ShortFromChar(pTempData);						
                    pTempData += 2U;

                    /*���źű�־*/
                    BnfZcSignInfoStru[i].throughSignFlag = ShortFromChar(pTempData);
                    pTempData += 2U;

                    /*�����־*/
                    BnfZcSignInfoStru[i].lightFlag = ShortFromChar(pTempData);
                    pTempData += 2U;
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
