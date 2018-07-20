/*******************************************
 * �ļ���	��  ZcTimeConfigData.c
 * �汾��	��  1.0  
 * ����ʱ��	��  2015-5-25
 * ��������	��	����ZcTimeConfigData���ݹ���
 * ʹ��ע��	��  
 * �޸ļ�¼	��	
*******************************************/

#include "ZcTimeConfigData.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"

static BnfZcTimeConfigStruct* gZcTimeConfigDataStru = NULL;   /*����ZcTimeConfigData���ݽṹ��*/
static UINT16_S gLineNumZcTimeConfig = 0U;/*������*/


/*
* ���������� ��ZcTimeConfigDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16 lineNum �����������
* ����ֵ  �� void
*/
void MallocZcTimeConfigDataStru(UINT16_S lineNum)
{
	if ((lineNum > 0U)&&(NULL == gZcTimeConfigDataStru))
	{
		gZcTimeConfigDataStru = (BnfZcTimeConfigStruct*)MemoryMalloc(((UINT32_S)(lineNum*sizeof(BnfZcTimeConfigStruct))));
		gLineNumZcTimeConfig = lineNum;
	}
}

/*
* ���������� ��ȡZcTimeConfigData����
* ����˵����
* ����ֵ  �� 
			BnfZcTimeConfigStruct*
*/
BnfZcTimeConfigStruct *GetZcTimeConfigData(void)
{
	return gZcTimeConfigDataStru;
}


/*
* ���������� ��ȡZcTimeConfigData��Ϣ
* ����˵�����������:UINT16* lineNum  ��������
* ����ֵ  �� 
			BnfZcTimeConfigStruct*
*/
BnfZcTimeConfigStruct *GetZcTimeDataInfo(UINT16_S* lineNum)
{
    if (NULL != lineNum)
    {
        (*lineNum) = gLineNumZcTimeConfig;
    }
	
	return gZcTimeConfigDataStru;
}
/*
** ���������� ��ȡNTPУʱ���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*			<UINT32_NULL: NTPУʱ���ʱ��(ms)
*/ 
UINT32_S GetZcTimeNtprrorTime(void)
{
	UINT32_S retVal = UINT32_NULL;/*��������ֵ*/

	if (NULL != gZcTimeConfigDataStru)
	{
		retVal = gZcTimeConfigDataStru[0].errorTime;
	}
	else
	{
        /*Do nothing currently !*/
	}
	return retVal;
}

/*
** ���������� ��ȡ��ϵͳ��ʱ�ӷ�����Уʱ��ʱ����ms��
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*			<UINT32_NULL: ��ϵͳ��ʱ�ӷ�����Уʱ��ʱ����ms��
*/ 
UINT32_S GetZcTimeSystemDuration(void)
{
	UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
	if (NULL != gZcTimeConfigDataStru)
	{
		retVal = gZcTimeConfigDataStru[0].duration;
	}
	else
	{
        /*Do nothing currently !*/
	}
	return retVal;
}

