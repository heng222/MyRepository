/*******************************************
* �ļ���	��  ZcCommConfigData.c
* ��  ��	��  ZC��
* ����ʱ��	��  2015-5-25
* ��������	��	����ZcCommConfigData���ݹ���
* ��  ע	��  ��
*******************************************/

#include "ZcCommConfigData.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"

static BnfZcCommConfigStruct* gZcCommConfigDataStru = NULL;   /*����ZcCommConfigData���ݽṹ��*/
static UINT16_S gLineNumZcCommConfig = 0U;/*������*/

/*******************************************
* ������	��  MallocZcCommConfigDataStru
* ��������	��	��ZcCommConfigDataStru�ṹ��ָ�����ռ�
* ���룺  UINT16_S lineNum �����������
* �����  ��
* ����ֵ��  ��
*******************************************/
void MallocZcCommConfigDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0U)&&(NULL == gZcCommConfigDataStru))
    {
        gZcCommConfigDataStru = (BnfZcCommConfigStruct*)MemoryMalloc(((UINT32_S)(lineNum*sizeof(BnfZcCommConfigStruct))));
        gLineNumZcCommConfig = lineNum;
    }
}

/*******************************************
* ������	��  GetZcCommConfigData
* ��������	��	��ȡZcCommConfigData����
* ���룺  ��
* �����  ��
* ����ֵ��  BnfZcCommConfigStruct* ZcCommConfigData����ָ��
*******************************************/
BnfZcCommConfigStruct *GetZcCommConfigData(void)
{
    return gZcCommConfigDataStru;
}

/*******************************************
* ������	��  GetZcCommConfigDataInfo
* ��������	��	��ȡZcCommConfigData��Ϣ
* ���룺  ��
* �����  UINT16* lineNum  ��������
* ����ֵ�� BnfZcCommConfigStruct* ZcCommConfigData��Ϣָ��
*******************************************/
BnfZcCommConfigStruct *GetZcCommConfigDataInfo(UINT16_S* lineNum)
{
    if (NULL != lineNum)
    {
        *lineNum = gLineNumZcCommConfig;
    }
    
    return gZcCommConfigDataStru;
}
/*******************************************
* ������	��  GetZcCommConfigDataStruzcSendAtsDataCycle
* ��������	��	��ȡָ��IDZcCommConfigDataStru��ZC��ATS������������ʱ��(ms)
* ���룺  ��
* �����  ��
* ����ֵ��  UINT32_NULL: ��ȡ����ʧ��
*			!=UINT32_NULL: ZC��ATS������������ʱ��(ms)
*******************************************/
UINT32_S GetZcCommConfigDataStruzcSendAtsDataCycle(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/

    if (NULL != gZcCommConfigDataStru)
    {
        retVal = gZcCommConfigDataStru[0].zcSendAtsDataCycle;
    }
    else
    {
        /*������*/
    }
    return retVal;
}

